// based on ROOT tutorial copytree3.C

#include <iostream>

// root headers
#include "TSystem.h"
#include "TChain.h"
#include "TFile.h"
#include "TTree.h"

// custom headers
#include "interface/StoppedHSCPEvent.h"

#include "macros/Cuts.C"

void WriteSelection(TChain* chain, const char* filename, unsigned cuts, Int_t nmax=999999999) {

  // count number of events selected
  unsigned nSelected = 0;

  // create custom event object
  //  gSystem->Load("libStoppedHSCPAnalysis");
  StoppedHSCPEvent *event   = new StoppedHSCPEvent();
  chain->SetBranchAddress("events",&event);
  
  //Create a new file + a clone of old tree in new file
  TFile *newfile = new TFile(filename,"recreate");
  TTree *newtree = chain->CloneTree(0);

  // loop over events
  Int_t nentries = (Int_t)chain->GetEntries();  
  std::cout << "Going to run over : " << nentries << " events" << std::endl;

  for (Int_t i=0;i<nentries && i<nmax; i++) {

    chain->GetEntry(i);
    
    // fill new tree if current event passes cuts
    if ( Cut(event, cuts) ) {
      newtree->Fill();
      nSelected++;
    }
    //    event->Clear();

  }

  // save tree and close file
  newtree->Print();
  newtree->AutoSave();
  delete newfile;

  std::cout << "Selected " << nSelected << " events" << std::endl;

}
