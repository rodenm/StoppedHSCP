
// plot some basic distributions

#include "TChain.h"
#include "TCanvas.h"
#include "TPDF.h"
#include "TH1.h"

void BasicPlots(TChain* chain) {

  TPDF* pdf = new TPDF("BasicPlots.pdf");
  TCanvas* canvas = new TCanvas("canvas");
  //  canvas->Clear();

  // setup for errors
  TH1::SetDefaultSumw2();

  // normalisation constants
  
  Int_t nEvents = (Int_t)chain->GetEntries();
  double rate = 3.5;

  // 

  // plots

  // timing
  //  chain->Draw("event.id");
  //  canvas->Update();
  
  TH1D* hbx = new TH1D("hbx", "BX number", 3564, -0.5, 3563.5);  
  chain->Draw("event.bx>>hbx");
  hbx->SetTitle("BX number");
  hbx->SetXTitle("N_{BX}");
  hbx->Scale(rate/nEvents);
  hbx->SetYTitle("Hz");
  canvas->Update();
  
  chain->Draw("event.orbit");
  canvas->Update();
  
  chain->Draw("event.lumisection");
  canvas->Update();
  
  chain->Draw("event.run");
  canvas->Update();
  
  chain->Draw("event.timestamp");
  canvas->Update();
  
  // jets
  chain->Draw("nJets");
  canvas->Update();
  
  chain->Draw("jets.e[0]");
  canvas->SetLogy();
  canvas->Update();

  TH1D* hjete = new TH1D("hjete", "Leading jet energy", 100, 0., 20000.);
  hjete->SetXTitle("E (GeV)");
  hjete->Scale(rate/nEvents);
  hjete->SetYTitle("Hz / 200 GeV");
  chain->Draw("jets.e[0]>>hjete");
  canvas->SetLogy();
  canvas->Update();
  
  TH1D* hjeteta = new TH1D("hjeteta", "Leading jet #eta", 70, -3.5, 3.5);
  hjeteta->SetXTitle("#eta");
  hjeteta->Scale(rate/nEvents);
  hjeteta->SetYTitle("Hz / 0.1");
  chain->Draw("jets.eta[0]>>hjeteta", "(jets.e[0])>20.");
  canvas->Update();

  TH1D* hjetphi = new TH1D("hjetphi", "Leading jet #phi", 60, -3.4151, 3.4151);
  hjetphi->SetXTitle("#phi");
  hjetphi->Scale(rate/nEvents);
  hjetphi->SetYTitle("Hz");
  chain->Draw("jets.phi[0]>>hjetphi", "(jets.e[0])>20.");
  canvas->Update();

  TH1D* hjetem = new TH1D("hjetem", "Leading jet ECAL energy", 100, 0., 2000.);
  hjetem->SetXTitle("E_{ECAL} / GeV");
  hjetem->Scale(rate/nEvents);
  hjetem->SetYTitle("Hz");
  chain->Draw("jets.eEm[0]>>hjetem");
  canvas->Update();

  TH1D* hjethad = new TH1D("hjethad", "Leading jet HCAL energy", 100, 0., 20000.);
  hjethad->SetXTitle("E_{HCAL} / GeV");
  hjethad->Scale(rate/nEvents);
  hjethad->SetYTitle("Hz / 200 GeV");
  chain->Draw("jets.eHad[0]>>hjethad");
  canvas->Update();

  // muons
  TH1D* hnmu = new TH1D("hnmu", "N muons", 4, -0.5, 3.5);
  hnmu->SetXTitle("N_{#mu}");
  hnmu->Scale(rate/nEvents);
  hnmu->SetYTitle("Hz");
  chain->Draw("nMuons>>hnmu");
  canvas->SetLogy(0);
  canvas->Update();

  TH1D* hmupt = new TH1D("hmupt", "Leading muon p_t", 100, 0., 1000.);
  hmupt->SetXTitle("N_{#mu}");
  hmupt->Scale(rate/nEvents);
  hmupt->SetYTitle("Hz / 10 GeV");
  chain->Draw("muons.pt[0]>>hmupt");
  canvas->SetLogy();
  canvas->Update();

  // towers
  TH1D* hntow = new TH1D("hntow", "N towers", 100, 0., 100.);
  hntow->SetXTitle("N_{towers}");
  hntow->Scale(rate/nEvents);
  hntow->SetYTitle("Hz");
  chain->Draw("nTowers>>hntow");
  canvas->Update();
  
  TH1D* htowe = new TH1D("htowe", "Leading tower energy", 100, 0., 5000.);
  htowe->SetXTitle("E (GeV)");
  htowe->Scale(rate/nEvents);
  htowe->SetYTitle("Hz / 50 GeV");
  chain->Draw("towers.e[0]>>htowe");
  canvas->Update();

  TH1D* htowem = new TH1D("htowem", "Leading tower ECAL energy", 100, 0., 2000.);
  htowem->SetXTitle("E (GeV)");
  htowem->Scale(rate/nEvents);
  htowem->SetYTitle("Hz / 20 GeV");
  chain->Draw("towers.eEm[0]>>htowem");
  canvas->Update();

  TH1D* htowhad = new TH1D("htowhad", "Leading tower HCAL energy", 100, 0., 10000.);
  htowhad->SetXTitle("E (GeV)");
  htowhad->Scale(rate/nEvents);
  htowhad->SetYTitle("Hz / 100 GeV");
  chain->Draw("towers.eHad[0]>>htowhad");
  canvas->Update();

  pdf->Close();
  
}

