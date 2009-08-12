#include <math.h>
#include <iostream>
#include <vector>
#include <string>

#include "StoppedHSCP/Lumi/interface/LUMIObjects.h"
#include "StoppedHSCP/Lumi/interface/LumiObjects.h"

#include "TSystem.h"
#include "TFile.h"
#include "TChain.h"
#include "TTree.h"
#include "TBranch.h"
#include "TRandom2.h"

#include "FWCore/FWLite/interface/AutoLibraryLoader.h"

using namespace shscp;

namespace {
  unsigned fill_n (bool* fAllBunches, unsigned iCurrent, unsigned fNumber, bool fContent) {
    for (unsigned i = 0; i < fNumber; ++i) fAllBunches [iCurrent++] = fContent;
    return iCurrent;
  }
  
  unsigned fill_72b8e_n (bool* fAllBunches, unsigned iCurrent, unsigned fNumber) {
    for (unsigned i = 0; i < fNumber; ++i) {
      iCurrent = fill_n (fAllBunches, iCurrent, 72, true);
      iCurrent = fill_n (fAllBunches, iCurrent, 8, false);
    }
    return iCurrent;
  }
  
  unsigned fill_empty_n (bool* fAllBunches, unsigned iCurrent, unsigned fNumber) {
    return fill_n (fAllBunches, iCurrent, fNumber, false);
  }
}

int main (int argc, char *argv[]) {
  const unsigned BUNCHES_IN_ORBIT = 3564;
  const unsigned ORBITS_IN_NIBBLE = 0x800;
  const unsigned ORBITS_IN_LS = 0x80000;
  double BEAM_LIFETIME = 20. * 3600; // seconds
  double LUMI_START = 1.e32;
  double LUMI_ABORT = 5.e31;
  double LUMI_VARIATIONS = 0.6; // min
  double BUNCH_LUMI_VARIATIONS = 0.5; // sigma
  double RESTART_TIME_MIN = 2. * 3600; // seconds
  double RESTART_TIME_MAX = 12. * 3600; // seconds
  double BX = 24.95e-9; // ns
  time_t START_TIME = 1234567890;
  time_t RUN_TIME = 30*24*3600; // 30 days
  unsigned FIRST_RUN = 100000;
  bool FILL_DETAILS = false;

  // random numbers
  TRandom2 random;

  // output NTUPLE
  gSystem->Load("libFWCoreFWLite.so");
  AutoLibraryLoader::enable();

  TFile outFile ("toy_lumi.root", "RECREATE");
  // TFile outFile ("toy_lumi_detail.root", "RECREATE");
  TTree *outTree = new TTree("LumiTree","LumiTree");
  
  LumiSectionHeader* newHeader = new LumiSectionHeader;
  outTree->Branch("Header", "shscp::LumiSectionHeader", &newHeader, 64000, 1);

  LumiSummary* newSummary = new LumiSummary;
  outTree->Branch("Summary", "shscp::LumiSummary", &newSummary, 64000, 1);

  LumiDetail* newDetail = new LumiDetail;
  if (FILL_DETAILS) outTree->Branch("Detail", "shscp::LumiDetail", &newDetail, 64000, 1);



  // make bunch structure
  bool filledBunches [BUNCHES_IN_ORBIT];
  unsigned  iCurrent = 0;
  // 234 334 334 334
  iCurrent = fill_72b8e_n (filledBunches, iCurrent, 2);
  iCurrent = fill_empty_n (filledBunches, iCurrent, 30);
  iCurrent = fill_72b8e_n (filledBunches, iCurrent, 3);
  iCurrent = fill_empty_n (filledBunches, iCurrent, 30);
  iCurrent = fill_72b8e_n (filledBunches, iCurrent, 4);
  iCurrent = fill_empty_n (filledBunches, iCurrent, 31);

  for (unsigned i = 0; i < 3; ++i) {
    iCurrent = fill_72b8e_n (filledBunches, iCurrent, 3);
    iCurrent = fill_empty_n (filledBunches, iCurrent, 30);
    iCurrent = fill_72b8e_n (filledBunches, iCurrent, 3);
    iCurrent = fill_empty_n (filledBunches, iCurrent, 30);
    iCurrent = fill_72b8e_n (filledBunches, iCurrent, 4);
    iCurrent = fill_empty_n (filledBunches, iCurrent, 31);
  }

  iCurrent = fill_empty_n (filledBunches, iCurrent, 80);

  unsigned nBunches = iCurrent;

  std::cout << "Total bunches: " << nBunches << std::endl;
  if (nBunches != BUNCHES_IN_ORBIT) {
    std::cout << "Expected total bunches: " << BUNCHES_IN_ORBIT << " - EXIT" << std::endl;
    return 1;
  }
  unsigned nFilled = 0;
  for (unsigned i = 0; i < nBunches; ++i) if (filledBunches [i]) ++nFilled;
  std::cout << "Filled bunches: " << nFilled << std::endl;

  double instantLumi [BUNCHES_IN_ORBIT];

  // time simulation
  double currentTimeOffset = 0;
  unsigned currentOrbit = 0;
  unsigned run = FIRST_RUN;
  unsigned section = 1;
  bool startNewRun = true;
  while (1) {
    if (startNewRun) {
      run += 1;
      // filling
      currentTimeOffset += random.Uniform (RESTART_TIME_MIN, RESTART_TIME_MAX);
      currentOrbit = 1;
      section = 1;
      
      // fill bunches
      double lumibx = LUMI_START * (nBunches * BX) / nFilled * random.Uniform (LUMI_VARIATIONS, 1.);
      for (unsigned i = 0; i < nBunches; ++i) {
	instantLumi [i] = filledBunches [i] ? lumibx / BX * random.Gaus (1., BUNCH_LUMI_VARIATIONS) : 0;
	if (instantLumi [i] < 0.) instantLumi [i] = 0;
      }
      startNewRun = false;
    }
    // start new section
    double startLumi = 0;
    for (unsigned iBX = 0; iBX < nBunches; ++iBX) startLumi += instantLumi [iBX] / nBunches;

    // find section end
    int orbits = ORBITS_IN_LS;
    double endsectionLumiDrop = exp (-BX*BUNCHES_IN_ORBIT * orbits / BEAM_LIFETIME);
    if (endsectionLumiDrop < LUMI_ABORT/startLumi) { // stop section and run
      orbits = int (floor (BEAM_LIFETIME * log (startLumi / LUMI_ABORT) / BX /  BUNCHES_IN_ORBIT));
      endsectionLumiDrop =  exp (-BX*BUNCHES_IN_ORBIT * orbits / BEAM_LIFETIME);
      startNewRun = true;
      //      std::cout << "new run " << endsectionLumiDrop << '/' << LUMI_ABORT << '/' << startLumi << '/' << orbits << std::endl;
    }
    // Dump lumi section
    double averageInstantLumi = 0;
    for (unsigned iBX = 0; iBX < nBunches; ++iBX) {
      newDetail->ETLumi[iBX] = instantLumi [iBX] * 0.5 * (1.+ endsectionLumiDrop);
      instantLumi [iBX] *= endsectionLumiDrop; // update lumi
      newDetail->ETLumiErr[iBX] = instantLumi [iBX] * 0.1; // whatever
      newDetail->ETLumiQlty[iBX] = 1;
      newDetail->ETBXNormalization[iBX] = 1;
      for (size_t i = 0; i < 2; ++i) {
	newDetail->OccLumi[i][iBX] = newDetail->ETLumi[iBX];
	newDetail->OccLumiErr[i][iBX] = newDetail->OccLumi[i][iBX] * 0.1;
	newDetail->OccLumiQlty[i][iBX] = 1;
	newDetail->OccBXNormalization[i][iBX] = 1;
      }
      averageInstantLumi += newDetail->ETLumi[iBX] / nBunches;
    }
    
    newSummary->DeadtimeNormalization = 1.;
    newSummary->LHCNormalization = 1.;
    newSummary->InstantLumi = averageInstantLumi;
    newSummary->InstantLumiErr = newSummary->InstantLumi * 0.1; // whatever
    newSummary->InstantLumiQlty = 1;
    newSummary->InstantETLumi = newSummary->InstantLumi;
    newSummary->InstantETLumiErr = newSummary->InstantLumiErr;
    newSummary->InstantETLumiQlty = 1;
    newSummary->ETNormalization = 1;
    for (size_t i = 0; i < 2; ++i) { 
      newSummary->InstantOccLumi[i] = newSummary->InstantLumi;
      newSummary->InstantOccLumiErr[i] = newSummary->InstantLumiErr;
      newSummary->InstantOccLumiQlty[i] = 0;
      newSummary->OccNormalization[i] = 1;
      newSummary->lumiNoise[i] = 0;
    }

    // timestamp of ~1 nibble later of actual ls start
    double sectionTimeStamp = START_TIME + currentTimeOffset + ORBITS_IN_NIBBLE*BUNCHES_IN_ORBIT*BX;
    newHeader->timestamp = int (floor (sectionTimeStamp));
    newHeader->timestamp_micros = int (floor ((sectionTimeStamp-newHeader->timestamp)*1e6));
    newHeader->runNumber = run;
    newHeader->sectionNumber = section;
    newHeader->startOrbit = currentOrbit;
    newHeader->numOrbits = orbits;
    newHeader->numBunches = BUNCHES_IN_ORBIT;
    newHeader->numHLXs = newHeader->numOrbits; // whatever
    newHeader->bCMSLive = true;
    newHeader->bOC0 = true;
    
    outTree->Fill (); // dump new section
//     std::cout << "Dump run " << newHeader->runNumber 
// 	      << ", section " << newHeader->sectionNumber 
// 	      << ", timestamp " << newHeader->timestamp 
// 	      << ", time offset " << currentTimeOffset
// 	      << ", orbits " << newHeader->numOrbits
// 	      << ", LUMI " << newSummary->InstantLumi
// 	      << std::endl;
    // update stamps
    currentTimeOffset += BX * BUNCHES_IN_ORBIT * orbits;
    currentOrbit += orbits;
    section += 1;

    if (currentTimeOffset > RUN_TIME) {
      break; // we are done
    }
  }

  outTree->Write();
  outFile.Close();

  delete newDetail;
  delete newSummary;
  delete newHeader;
  return 0;
}
