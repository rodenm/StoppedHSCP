
// plot some basic distributions

#include <string.h>
#include <iostream>

#include "TChain.h"
#include "TCanvas.h"
#include "TPDF.h"
#include "TPostScript.h"
#include "TH1.h"
#include "TFile.h"
#include "TMath.h"

void BasicHistos(TChain* chain, char* filename, double time) {

  // Create output file
  TFile *file = new TFile(filename,"recreate");

  // setup for errors
  TH1::SetDefaultSumw2();

  // normalisation constants
  Int_t nEvents = (Int_t)chain->GetEntries();
  //  double rate = nEvents/time;
  double scale = 1/time;  


  // time
//   TH1D* hbx = new TH1D("hbx", "BX number", 3564, 0., 3564.);  
//   chain->Draw("event.bx>>hbx");
//   hbx->Scale(scale);
  
//   TH1D* horb = new TH1D("horb", "Orbit number", 100, 0., 10000.);  
//   chain->Draw("event.orbit>>horb");
  
//   TH1D* hls = new TH1D("hls", "Lumi section", 100, 0., 1000.);  
//   chain->Draw("event.lumisection>>hls");


  // trigger
//   TH1D* hl1et = new TH1D("hl1et", "Leading L1 jet E_{t}", 100, 0., 200.);  
//   chain->Draw("l1Jets[0].et>>hl1et");
//   hl1et->Scale(scale);

//   TH1D* hl1eta = new TH1D("hl1eta", "Leading L1 jet #eta", 70, -3.5, 3.5);  
//   chain->Draw("l1Jets[0].eta>>hl1eta");
//   hl1eta->Scale(scale);

//   TH1D* hl1phi = new TH1D("hl1phi", "Leading L1 jet #phi", 60, TMath::Pi()*-1., TMath::Pi());  
//   chain->Draw("l1Jets[0].phi>>hl1phi");
//   hl1phi->Scale(scale);
  
//   TH1D* hhlte = new TH1D("hhlte", "Leading HLT jet energy", 100, 0., 200.);  
//   chain->Draw("hltJets[0].e>>hhlte");
//   hhlte->Scale(scale);

//   TH1D* hhlteta = new TH1D("hhlteta", "Leading HLT jet #eta", 70, -3.5, 3.5);  
//   chain->Draw("hltJets[0].eta>>hhlteta");
//   hhlteta->Scale(scale);

//   TH1D* hhltphi = new TH1D("hhltphi", "Leading HLT jet #phi", 60, TMath::Pi()*-1., TMath::Pi());
//   chain->Draw("hltJets[0].phi>>hhltphi");
//   hhltphi->Scale(scale);


  // jets
  TH1D* hjete = new TH1D("hjete", "Leading jet energy", 100, 0., 1000.);
  chain->Draw("LeadingCenJetEnergy>>hjete");
  hjete->Scale(scale);

  TH1D* hjete2 = new TH1D("hjete2", "Leading jet energy (zoom)", 100, 0., 200.);
  chain->Draw("LeadingCenJetEnergy>>hjete2");
  hjete2->Scale(scale);
  
  TH1D* hjeteta = new TH1D("hjeteta", "Leading jet #eta", 70, -3.5, 3.5);
  chain->Draw("LeadingCenJetEta>>hjeteta");
  hjeteta->Scale(scale);

  TH1D* hjetphi = new TH1D("hjetphi", "Leading jet #phi", 60, -3.4151, 3.4151);
  chain->Draw("LeadingCenJetPhi>>hjetphi");
  hjetphi->Scale(scale);

  TH1D* hjetem = new TH1D("hjetem", "Leading jet ECAL energy", 100, 0., 200.);
  chain->Draw("LeadingCenJetEmInEB>>hjetem");
  hjetem->Scale(scale);

  TH1D* hjethad = new TH1D("hjethad", "Leading jet HCAL energy", 100, 0., 200.);
  chain->Draw("LeadingCenJetHadInHB>>hjethad");
  hjethad->Scale(scale);

  TH1D* hjetn60 = new TH1D("hjetn60", "Leading jet N60", 50, 0., 50.);
  chain->Draw("LaedingCenJetn60>>hjetn60");
  hjetn60->Scale(scale);

  TH1D* hjetn90 = new TH1D("hjetn90", "Leading jet N90", 50, 0., 50.);
  chain->Draw("LeadingCenJetn90>>hjetn90");
  hjetn90->Scale(scale);


  // muons
  TH1D* hnmu = new TH1D("hnmu", "N muons", 4, -0.5, 3.5);
  chain->Draw("NoOfMuons>>hnmu");
  hnmu->Scale(scale);

//   TH1D* hmupt = new TH1D("hmupt", "Leading muon pt", 100, 0., 100.);
//   chain->Draw("muons.pt[0]>>hmupt");
//   hmupt->Scale(scale);


  // towers
//   TH1D* hntow = new TH1D("hntow", "N towers", 100, 0., 100.);
//   chain->Draw("nTower>>hntow");
//   hntow->Scale(scale);
  
//   TH1D* htowe = new TH1D("htowe", "Leading tower energy", 100, 0., 200.);
//   chain->Draw("towers.e[0]>>htowe");
//   htowe->Scale(scale);

//   TH1D* htowem = new TH1D("htowem", "Leading tower ECAL energy", 100, 0., 200.);
//   chain->Draw("towers.eEm[0]>>htowem");
//   htowem->Scale(scale);

//   TH1D* htowhad = new TH1D("htowhad", "Leading tower HCAL energy", 100, 0., 200.);
//   chain->Draw("towers.eHad[0]>>htowhad");
//   htowhad->Scale(scale);
  
//   hl1et->Write();
//   hl1eta->Write();
//   hl1phi->Write();
//   hhlte->Write();
//   hhlteta->Write();
//   hhltphi->Write();
//   hbx->Write();
//   horb->Write();
//   hls->Write();
  hjete->Write();
  hjete2->Write();
  hjeteta->Write();
  hjetphi->Write();
  hjetem->Write();
  hjethad->Write();
  hjetn60->Write();
  hjetn90->Write();
  hnmu->Write();
//   hmupt->Write();
//   hntow->Write();
//   htowe->Write();
//   htowem->Write();
//   htowhad->Write();

  delete file;

}

void BasicPlots(char* rootfile, char* psfile) {

  TFile file(rootfile,"read");

  TPostScript* ps = new TPostScript(psfile);
  TCanvas* canvas = new TCanvas("canvas");

  canvas->SetLogy();


//   TH1D* hbx = (TH1D*)file.Get("hbx");
//   hbx->SetTitle("BX number");
//   hbx->SetXTitle("N_{BX}");
//   hbx->SetYTitle("Hz");
//   hbx->Draw("HIST");
//   canvas->Update();

//   TH1D* horb = (TH1D*)file.Get("horb");
//   horb->Draw("HIST");
//   canvas->Update();

// //   TH1D* hls = (TH1D*)file.Get("hls");
// //   hls->Draw("HIST");
// //   canvas->Update();

//   // L1
//   TH1D* hl1et = (TH1D*)file.Get("hl1et");
//   hl1et->SetXTitle("E (GeV)");
//   hl1et->SetYTitle("Hz / 2 GeV");
//   hl1et->Draw("HIST");
//   canvas->Update();

//   TH1D* hl1eta = (TH1D*)file.Get("hl1eta");
//   hl1eta->SetXTitle("#eta");
//   hl1eta->SetYTitle("Hz / 0.1");
//   hl1eta->Draw("HIST");
//   canvas->Update();

//   TH1D* hl1phi = (TH1D*)file.Get("hl1phi");
//   hl1phi->SetXTitle("#phi");
//   hl1phi->SetYTitle("Hz / #pi/30");
//   hl1phi->Draw("HIST");
//   canvas->Update();

//   // HLT
//   TH1D* hhlte = (TH1D*)file.Get("hhlte");
//   hhlte->SetXTitle("E (GeV)");
//   hhlte->SetYTitle("Hz / 2 GeV");
//   hhlte->Draw("HIST");
//   canvas->Update();

//   TH1D* hhlteta = (TH1D*)file.Get("hhlteta");
//   hhlteta->SetXTitle("#eta");
//   hhlteta->SetYTitle("Hz / 0.1");
//   hhlteta->Draw("HIST");
//   canvas->Update();

//   TH1D* hhltphi = (TH1D*)file.Get("hhltphi");
//   hhltphi->SetXTitle("#phi");
//   hhltphi->SetYTitle("Hz / #pi/30");
//   hhltphi->Draw("HIST");
//   canvas->Update();

  // Jets
  TH1D* hjete = (TH1D*)file.Get("hjete2");
  hjete->SetXTitle("E (GeV)");
  hjete->SetYTitle("Hz / 2 GeV");
  hjete->Draw("HIST");
  canvas->Update();

  TH1D* hjeteta = (TH1D*)file.Get("hjeteta");
  hjeteta->SetXTitle("#eta");
  hjeteta->SetYTitle("Hz / 0.1");
  hjeteta->Draw("HIST");
  canvas->Update();

  TH1D* hjetphi = (TH1D*)file.Get("hjetphi");
  hjetphi->SetXTitle("#phi");
  hjetphi->SetYTitle("Hz / #pi/30");
  hjetphi->Draw("HIST");
  canvas->Update();

  TH1D* hjetem = (TH1D*)file.Get("hjetem");
  hjetem->SetXTitle("E_{ECAL} (GeV)");
  hjetem->SetYTitle("Hz / 2 GeV");
  hjetem->Draw("HIST");
  canvas->Update();

  TH1D* hjethad = (TH1D*)file.Get("hjethad");
  hjethad->SetXTitle("E_{HCAL} / GeV");
  hjethad->SetYTitle("Hz / 2 GeV");
  hjethad->Draw("HIST");
  canvas->Update();

  TH1D* hjetn60 = (TH1D*)file.Get("hjetn60");
  hjetn60->SetXTitle("n60");
  hjetn60->SetYTitle("N");
  hjetn60->Draw("HIST");
  canvas->Update();

  TH1D* hjetn90 = (TH1D*)file.Get("hjetn90");
  hjetn90->SetXTitle("n90");
  hjetn90->SetYTitle("N");
  hjetn90->Draw("HIST");
  canvas->Update();

  TH1D* hnmu = (TH1D*)file.Get("hnmu");
  hnmu->SetXTitle("N_{#mu}");
  hnmu->SetYTitle("Hz");
  hnmu->Draw("HIST");
  canvas->Update();

//   TH1D* hmupt = (TH1D*)file.Get("hmupt");
//   hmupt->SetXTitle("p_{t}^{#mu}");
//   hmupt->SetYTitle("Hz / 1 GeV");
//   hmupt->Draw("HIST");
//   canvas->Update();

//   TH1D* hntow = (TH1D*)file.Get("hntow");
//   hntow->SetXTitle("N_{towers}");
//   hntow->SetYTitle("Hz");
//   hntow->Draw("HIST");
//   canvas->Update();

//   TH1D* htowe = (TH1D*)file.Get("htowe");
//   htowe->SetXTitle("E (GeV)");
//   htowe->SetYTitle("Hz / 2 GeV");
//   htowe->Draw("HIST");
//   canvas->Update();

//   TH1D* htowem = (TH1D*)file.Get("htowem");
//   htowem->SetXTitle("E (GeV)");
//   htowem->SetYTitle("Hz / 2 GeV");
//   htowem->Draw("HIST");
//   canvas->Update();

//   TH1D* htowhad = (TH1D*)file.Get("htowhad");
//   htowhad->SetXTitle("E (GeV)");
//   htowhad->SetYTitle("Hz / 2 GeV");
//   htowhad->Draw("HIST");
//   canvas->Update();

  ps->Close();

}
