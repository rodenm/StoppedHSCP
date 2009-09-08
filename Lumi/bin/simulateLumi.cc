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
  // global constants
  const unsigned BUNCHES_IN_ORBIT = 3564;
  const unsigned ORBITS_IN_NIBBLE = 0x1000;
  const unsigned ORBITS_IN_LS = 0x100000;
  double BX = 24.95e-9; // ns
  // secondary constants
  const double SECTION_TIME = BX*BUNCHES_IN_ORBIT*ORBITS_IN_LS;
  const double ORBIT_TIME = BX*BUNCHES_IN_ORBIT;


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

  struct RSStatus {
    int run;
    int section;
    double startTime;
    unsigned firstOrbit;
    unsigned orbits;
    double instantLumi [BUNCHES_IN_ORBIT];
    bool liveData;

    void newSection () {
    section += 1;
    startTime += orbits*ORBIT_TIME;
    firstOrbit += orbits;
    orbits = 0;
    }

    void newRun () {
    run += 1;
    section = 0;
    firstOrbit = 0;
    }
void fillLumiData (LumiSectionHeader* fHeader, LumiSummary* fSummary, LumiDetail* fDetail) {
      double unfilledBunchThreshold = 1.e20; // instant luminosity considered as empty (trigger) bunch
      int unfilledBunches = 0;
      double averageInstantLumi = 0;
      
      for (unsigned iBX = 0; iBX < BUNCHES_IN_ORBIT; ++iBX) {
	fDetail->ETLumi[iBX] = instantLumi [iBX];
	fDetail->ETLumiErr[iBX] = instantLumi [iBX] * 0.1; // whatever
	fDetail->ETLumiQlty[iBX] = 1;
	fDetail->ETBXNormalization[iBX] = 1;
	for (size_t i = 0; i < 2; ++i) {
	  fDetail->OccLumi[i][iBX] = fDetail->ETLumi[iBX];
	  fDetail->OccLumiErr[i][iBX] = fDetail->OccLumi[i][iBX] * 0.1;
	  fDetail->OccLumiQlty[i][iBX] = 1;
	  fDetail->OccBXNormalization[i][iBX] = 1;
	}
	averageInstantLumi += fDetail->ETLumi[iBX] / BUNCHES_IN_ORBIT;
	if (fDetail->ETLumi[iBX] < unfilledBunchThreshold) ++unfilledBunches;
      }
      
      fSummary->DeadtimeNormalization = 1.;
      fSummary->LHCNormalization = 1.;
      fSummary->InstantLumi = averageInstantLumi;
      fSummary->InstantLumiErr = fSummary->InstantLumi * 0.1; // whatever
      fSummary->InstantLumiQlty = 1;
      
      fSummary->InstantETLumi = fSummary->InstantLumi;
      fSummary->InstantETLumiErr = fSummary->InstantLumiErr;
      fSummary->InstantETLumiQlty = 1;
      fSummary->ETNormalization = 1;
      
      for (size_t i = 0; i < 2; ++i) { 
	fSummary->InstantOccLumi[i] = fSummary->InstantLumi;
	fSummary->InstantOccLumiErr[i] = fSummary->InstantLumiErr;
	fSummary->InstantOccLumiQlty[i] = 0;
	fSummary->OccNormalization[i] = 1;
	fSummary->lumiNoise[i] = 0;
      }
      
      // timestamp of ~1 nibble later of actual ls start
      double sectionTimeStamp = startTime + ORBITS_IN_NIBBLE*ORBIT_TIME;
      fHeader->timestamp = int (floor (sectionTimeStamp));
      fHeader->timestamp_micros = int (floor ((sectionTimeStamp-fHeader->timestamp)*1e6));
      fHeader->runNumber = run;
      fHeader->sectionNumber = section;
      fHeader->startOrbit = firstOrbit;
      fHeader->numOrbits = orbits;
      fHeader->numBunches = BUNCHES_IN_ORBIT;
      fHeader->numUnfilledBunches = unfilledBunches;
      fHeader->numHLXs = fHeader->numOrbits; // whatever
      fHeader->bCMSLive = liveData;
      fHeader->bOC0 = fHeader->bCMSLive;
    }
  };

}

int main (int argc, char *argv[]) {
  double BEAM_LIFETIME = 20. * 3600; // seconds
  double LUMI_START = 1.e32;
  double LUMI_ABORT = 5.e31;
  double LUMI_VARIATIONS = 0.6; // min
  double BUNCH_LUMI_VARIATIONS = 0.5; // sigma
  double RESTART_TIME_MIN = 2. * 3600; // seconds
  double RESTART_TIME_MAX = 12. * 3600; // seconds
  time_t START_TIME = 1234567890;
  time_t END_TIME = START_TIME + 30*24*3600; // 30 days
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

  // initialization
  RSStatus currentStatus;
  currentStatus.run = FIRST_RUN;
  currentStatus.section = 0;
  currentStatus.startTime = START_TIME;
  currentStatus.firstOrbit = 0; // to be calculated
  currentStatus.orbits = 0;
  currentStatus.liveData = false;

  // start time simulation
  bool startNewRun = true;

  while (1) {
    if (startNewRun) {
      // filling period - continue dumping empty sections
      double fillTime = random.Uniform (RESTART_TIME_MIN, RESTART_TIME_MAX);
      while (fillTime > 0) {
	int orbits = ORBITS_IN_LS;
	if (fillTime < SECTION_TIME) {
	  orbits = int (floor (fillTime / ORBIT_TIME));
	  fillTime = 0;
	}
	else {
	  fillTime -= SECTION_TIME;
	}
	// new empty section
	currentStatus.newSection ();
	currentStatus.orbits = orbits;
	currentStatus.liveData = false;
	for (size_t i = 0; i < BUNCHES_IN_ORBIT; ++i) {
	  currentStatus.instantLumi[i] = 0.;
	}
	currentStatus.fillLumiData (newHeader, newSummary, newDetail);
	outTree->Fill (); // dump new section
      }

      // new run
      currentStatus.newRun();
      
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
    double endsectionLumiDrop = exp (-ORBIT_TIME * orbits / BEAM_LIFETIME);
    if (endsectionLumiDrop < LUMI_ABORT/startLumi) { // stop section and run
      orbits = int (floor (BEAM_LIFETIME * log (startLumi / LUMI_ABORT) / ORBIT_TIME));
      endsectionLumiDrop =  exp (-ORBIT_TIME * orbits / BEAM_LIFETIME);
      startNewRun = true;
      //      std::cout << "new run " << endsectionLumiDrop << '/' << LUMI_ABORT << '/' << startLumi << '/' << orbits << std::endl;
    }
    
    currentStatus.newSection ();
    currentStatus.orbits = orbits;
    currentStatus.liveData = true;
    for (size_t i = 0; i < BUNCHES_IN_ORBIT; ++i) {
      currentStatus.instantLumi[i] = instantLumi [i] * 0.5 * (1.+ endsectionLumiDrop);
      instantLumi [i] *= endsectionLumiDrop; // propagate ongoing lumi
    }
    currentStatus.fillLumiData (newHeader, newSummary, newDetail);
    outTree->Fill (); // dump new section

    if (currentStatus.startTime > END_TIME) {
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
