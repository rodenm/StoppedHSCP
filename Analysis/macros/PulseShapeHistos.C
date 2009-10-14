
#include <string.h>
#include <iostream>

#include "TChain.h"
#include "TCanvas.h"
#include "TPDF.h"
#include "TPostScript.h"
#include "TH2D.h"
#include "TFile.h"

#include "interface/StoppedHSCPEvent.h"
#include "interface/PulseShape.h"

void PulseShapeHistos(TChain* chain, char* filename, double time) {

  // create output file
  TFile *newfile = new TFile(filename,"recreate");
  
  // histograms
  TH1D* hppos = new TH1D("peak", "Peak position", 10., 0., 10.);
  TH2D* h1 = new TH2D("r1r2", "", 100, 0., 1., 100, 0., 1.);
  TH2D* h2 = new TH2D("rpro", "", 100, 0., 1., 100, 0., 1.);
  TH1D* hpeak = new TH1D("peakfrac", "", 100, 0., 1.);
  TH1D* houter = new TH1D("outfrac", "", 100, 0., 1.);

  // create custom event object
  //  gSystem->Load("libStoppedHSCPAnalysis");
  StoppedHSCPEvent *evt   = new StoppedHSCPEvent();
  chain->SetBranchAddress("events",&evt);
  
  // loop over events
  Int_t nentries = (Int_t)chain->GetEntries();  
  std::cout << "Going to run over : " << nentries << " events" << std::endl;

  for (Int_t i=0;i<nentries; i++) {

    chain->GetEntry(i);
    
    PulseShape ps;
    ps.addJet(evt, 0);

    hppos->Fill(ps.getPeak());
    hpeak->Fill(ps.getP0ToTotal(), 1./time);
    houter->Fill(ps.getOuterToTotal(), 1./time);
    h1->Fill(ps.getP2ToP1(), ps.getP1ToP0(), 1./time);
    h2->Fill(ps.getP0ToTotal(), ps.getOuterToTotal(), 1./time);
    
  }

  hppos->Write();
  hpeak->Write();
  houter->Write();
  h1->Write();
  h2->Write();

  delete newfile;

}


void PulseShapePlots(char* rootfile, char* psfile) {

  TFile file(rootfile,"read");

  TPostScript* ps = new TPostScript(psfile, 112);
  TCanvas* canvas = new TCanvas("canvas");

  canvas->SetLogz();

  TH1D* hppos = (TH1D*)file.Get("peak");
  hppos->SetXTitle("sample");
  hppos->SetYTitle("Hz");
  hppos->Draw("HIST");
  canvas->Update();

  TH1D* hpeak = (TH1D*)file.Get("peakfrac");
  hpeak->SetXTitle("s_{peak}/s_{total}");
  hpeak->SetYTitle("Hz");
  hpeak->Draw("HIST");
  canvas->Update();

  TH1D* hout = (TH1D*)file.Get("outfrac");
  hout->SetXTitle("s_{outer}/s_{total}");
  hout->SetYTitle("Hz");
  hout->Draw("HIST");
  canvas->Update();

  TH2D* h1 = (TH2D*)file.Get("r1r2");
  h1->SetXTitle("BX_{+2}/BX_{+1}");
  h1->SetYTitle("BX_{+1}/BX_{0}");
  h1->SetZTitle("Hz");
  h1->Draw("COLZ");
  canvas->Update();

  TH2D* h2 = (TH2D*)file.Get("rpro");
  h2->SetXTitle("s_{peak}/s_{total}");
  h2->SetYTitle("s_{outer}/s_{total}");
  h2->SetZTitle("Hz");
  h2->Draw("COLZ");
  canvas->Update();

  ps->Close();

}

