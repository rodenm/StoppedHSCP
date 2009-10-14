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


void LeadingJetHisto(TChain* chain) {

  // count number of events selected
  unsigned nSelected = 0;

  // create custom event object
  //  gSystem->Load("libStoppedHSCPAnalysis");
  StoppedHSCPEvent *event   = new StoppedHSCPEvent();
  chain->SetBranchAddress("events",&event);
  
  // loop over events
  Int_t nentries = (Int_t)chain->GetEntries();  
  std::cout << "Going to run over : " << nentries << " events" << std::endl;

  // histogram
  TH1D* jete = new TH1D("jete", "Leading jet E", 200, 0., 100.);
  TH1D* jetpos = new TH1D("jetpos", "Leading jet position", 20, 0., 20.);

  for (Int_t i=0;i<nentries; i++) {

    chain->GetEntry(i);
    
    double emax = 0.;
    unsigned pos = 0;

    for (unsigned j=0; j<event->nJets(); ++j) {
      if (event->getJet(j).e > emax) {
	emax = event->getJet(j).e;
	pos = j;
      }
    }

    jete->Fill(emax);
    jetpos->Fill(pos);

  }

}
