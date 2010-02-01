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

#include "FWCore/FWLite/interface/AutoLibraryLoader.h"

using namespace shscp;
using namespace HCAL_HLX;

inline void importLumi (const std::vector<std::string>& inFileNames, 
			const std::string& outFileName, 
			bool oldFormat = false) {
  
  gSystem->Load("libFWCoreFWLite.so");
  AutoLibraryLoader::enable();

  TChain inChain ("HLXData");
  for (size_t i = 0; i < inFileNames.size (); ++i) {
    inChain.AddFile (inFileNames[i].c_str());
  std::cout << "Input file-> " << inFileNames[i] << std::endl;
  }
  
  LUMI_SECTION_HEADER* oldHeader = new LUMI_SECTION_HEADER;
  inChain.SetBranchAddress("Header.", &oldHeader);

  LUMI_SUMMARY* oldSummary = new LUMI_SUMMARY;
  inChain.SetBranchAddress("Summary.", &oldSummary);

  LUMI_DETAIL* oldDetail = new LUMI_DETAIL;
  inChain.SetBranchAddress("Detail.", &oldDetail);


  TFile outFile (outFileName.c_str(), "RECREATE");
  TTree *outTree = new TTree("LumiTree","LumiTree");
  
  LumiSectionHeader* newHeader = new LumiSectionHeader;
  outTree->Branch("Header", "shscp::LumiSectionHeader", &newHeader, 64000, 1);

  LumiSummary* newSummary = new LumiSummary;
  outTree->Branch("Summary", "shscp::LumiSummary", &newSummary, 64000, 1);

  LumiDetail* newDetail = new LumiDetail;
  outTree->Branch("Detail", "shscp::LumiDetail", &newDetail, 64000, 1);


  int64_t nEvents = inChain.GetEntries();
  for (int64_t iEvent = 0; iEvent < nEvents; ++iEvent) {
    inChain.GetEvent (iEvent);

    newHeader->timestamp = oldFormat ? 0 : oldHeader->timestamp;
    newHeader->timestamp_micros = oldFormat ? 0 : oldHeader->timestamp_micros;
    newHeader->runNumber = oldHeader->runNumber;   // Run number
    newHeader->sectionNumber = oldHeader->sectionNumber; // Section number
    newHeader->startOrbit = oldHeader->startOrbit;  // Start orbit of lumi section
    newHeader->numOrbits = oldHeader->numOrbits;   // Total number of orbits recorded in lumi section
    newHeader->numBunches = oldHeader->numBunches;  // Total number of bunches (from start of orbit)
    newHeader->numHLXs = oldHeader->numHLXs;     // Number of HLXs in lumi section
    newHeader->bCMSLive = oldFormat ? true : oldHeader->bCMSLive;    // Is CMS taking data?
    newHeader->bOC0 = oldFormat ? true : oldHeader->bOC0;        // Was section initialised by an OC0?

    
    newSummary->DeadtimeNormalization = oldSummary->DeadtimeNormalization; 
    newSummary->LHCNormalization = oldSummary->LHCNormalization; // recieved from LHC 
    newSummary->InstantLumi = oldSummary->InstantLumi;
    newSummary->InstantLumiErr = oldSummary->InstantLumiErr;
    newSummary->InstantLumiQlty = oldSummary->InstantLumiQlty;
    newSummary->InstantETLumi = oldSummary->InstantETLumi;
    newSummary->InstantETLumiErr = oldSummary->InstantETLumiErr;
    newSummary->InstantETLumiQlty = oldSummary->InstantETLumiQlty;
    newSummary->ETNormalization = oldSummary->ETNormalization;  // Calculated
    for (size_t i = 0; i < 2; ++i) { 
      newSummary->InstantOccLumi[i] = oldSummary->InstantOccLumi[i];
      newSummary->InstantOccLumiErr[i] = oldSummary->InstantOccLumiErr[i];
      newSummary->InstantOccLumiQlty[i] = oldSummary->InstantOccLumiQlty[i];
      newSummary->OccNormalization[i] = oldSummary->OccNormalization[i];
      newSummary->lumiNoise[i] = oldSummary->lumiNoise[i];
    }

    for (size_t iBX = 0; iBX < HCAL_HLX_MAX_BUNCHES; ++iBX) {
      newDetail->LHCLumi[iBX] = oldDetail->LHCLumi[iBX]; // Sum of LHC.data over all HLX's
      newDetail->ETLumi[iBX] = oldDetail->ETLumi[iBX];
      newDetail->ETLumiErr[iBX] = oldDetail->ETLumiErr[iBX];
      newDetail->ETLumiQlty[iBX] = oldDetail->ETLumiQlty[iBX];
      newDetail->ETBXNormalization[iBX] = oldDetail->ETBXNormalization[iBX];
      for (size_t i = 0; i < 2; ++i) {
	newDetail->OccLumi[i][iBX] = oldDetail->OccLumi[i][iBX];
	newDetail->OccLumiErr[i][iBX] = oldDetail->OccLumiErr[i][iBX];
	newDetail->OccLumiQlty[i][iBX] = oldDetail->OccLumiQlty[i][iBX];
	newDetail->OccBXNormalization[i][iBX] = oldDetail->OccBXNormalization[i][iBX];
      }
    }
    outTree->Fill ();
  }
  outTree->Write();
  outFile.Close();
  //delete outTree;
  delete newDetail;
  delete newSummary;
  delete newHeader;
  delete oldDetail;
  delete oldSummary;
  delete oldHeader;
  return;
}
