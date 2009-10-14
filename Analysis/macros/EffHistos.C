// make N-1 efficiency histograms

#include <iostream>

// root headers
#include "TSystem.h"
#include "TChain.h"
#include "TFile.h"
#include "TTree.h"
#include "TPDF.h"
#include "TPostScript.h"
#include "TCanvas.h"
#include "TH1D.h"

// custom headers
#include "interface/StoppedHSCPEvent.h"

#include "macros/Cuts.C"

void EffHistos(TChain* chain, char* filename, double time) {

  //Create a new file + a clone of old tree in new file
  TFile *file = new TFile(filename,"recreate");


  // setup for errors
  TH1::SetDefaultSumw2();

  // create histograms
  TH1D* hEffJetE = new TH1D("hEffJetE", "N-1 jet E", 100, 0., 200.);
  TH1D* hEffJetEta = new TH1D("hEffJetEta", "N-1 jet #eta", 70, -3.0, 3.0);
  TH1D* hEffJetN90 = new TH1D("hEffJetN90", "N-1 jet n90", 25, 0., 25.);
  TH1D* hEffJetN60 = new TH1D("hEffJetN60", "N-1 jet n60", 25, 0., 25.);
  TH1D* hEffMuVeto = new TH1D("hEffMuVeto", "N-1 #mu veto", 5, 0., 5.);
  
  // create custom event object
  //  gSystem->Load("libStoppedHSCPAnalysis");
  StoppedHSCPEvent *evt   = new StoppedHSCPEvent();
  chain->SetBranchAddress("events",&evt);
  
  // loop over events
  Int_t nentries = (Int_t)chain->GetEntries();  
  for (Int_t i=0;i<nentries; i++) {

    chain->GetEntry(i);

    if (Cut(evt, 0x1e)) hEffJetE->Fill(evt->getJet(0).e);
    if (Cut(evt, 0x1d)) hEffJetEta->Fill(evt->getJet(0).eta);
    if (Cut(evt, 0x1b)) hEffJetN60->Fill(evt->getJet(0).n60);
    if (Cut(evt, 0x17)) hEffJetN90->Fill(evt->getJet(0).n90);
    if (Cut(evt, 0xf)) hEffMuVeto->Fill(evt->nMuons());

  }

  hEffJetE->Scale(1/time);
  hEffJetEta->Scale(1/time);
  hEffJetN90->Scale(1/time);
  hEffJetN60->Scale(1/time);
  hEffMuVeto->Scale(1/time);

  hEffJetE->Write();
  hEffJetEta->Write();
  hEffJetN90->Write();
  hEffJetN60->Write();
  hEffMuVeto->Write();


  delete file;

}


void EffPlots(char* rootfile, char* psfile) {
  
  TFile file(rootfile,"read");

  TPostScript* ps = new TPostScript(psfile, 112);
  TCanvas* canvas = new TCanvas("canvas");
  canvas->SetLogy();

  TH1D* hEffJetE = (TH1D*)file.Get("hEffJetE");
  hEffJetE->Draw("HIST");
  canvas->Update();

  TH1D* hEffJetEta = (TH1D*)file.Get("hEffJetEta");
  hEffJetEta->Draw("HIST");
  canvas->Update();

  TH1D* hEffJetN90 = (TH1D*)file.Get("hEffJetN90");
  hEffJetN90->Draw("HIST");
  canvas->Update();

  TH1D* hEffJetN60 = (TH1D*)file.Get("hEffJetN60");
  hEffJetN60->Draw("HIST");
  canvas->Update();

  TH1D* hEffMuVeto = (TH1D*)file.Get("hEffMuVeto");
  hEffMuVeto->Draw("HIST");
  canvas->Update();

  ps->Close();
  
}
