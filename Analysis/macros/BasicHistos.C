
// plot some basic distributions

#include "TChain.h"
#include "TCanvas.h"
#include "TPDF.h"
#include "TH1.h"
#include "TFile.h"


void BasicHistos(TChain* chain) {

  //Create a new file + a clone of old tree in new file
  TFile *file = new TFile("BasicHistos.root","recreate");

  // setup for errors
  TH1::SetDefaultSumw2();

  // normalisation constants
  Int_t nEvents = (Int_t)chain->GetEntries();
  double time = 178244;
  double rate = nEvents/time;
  
  TH1D* hbx = new TH1D("hbx", "BX number", 3564, 0., 3564.);  
  chain->Draw("event.orbit>>hbx");
  hbx->Scale(rate/hbx->Integral());
  
  TH1D* horb = new TH1D("horb", "Orbit number", 100, 0., 10000.);  
  chain->Draw("event.bx>>horb");
  
  TH1D* hls = new TH1D("hls", "Lumi section", 100, 0., 1000.);  
  chain->Draw("event.lumisection>>hls");
  
  TH1D* hjete = new TH1D("hjete", "Leading jet energy", 100, 0., 10000.);
  hjete->Scale(rate/hjete->Integral());
  chain->Draw("jets.e[0]>>hjete");
  
  TH1D* hjeteta = new TH1D("hjeteta", "Leading jet #eta", 70, -3.5, 3.5);
  hjeteta->Scale(rate/hjeteta->Integral());
  chain->Draw("jets.eta[0]>>hjeteta", "(jets.e[0])>20.");

  TH1D* hjetphi = new TH1D("hjetphi", "Leading jet #phi", 60, -3.4151, 3.4151);
  hjetphi->Scale(rate/hjetphi->Integral());
  chain->Draw("jets.phi[0]>>hjetphi", "(jets.e[0])>20.");

  TH1D* hjetem = new TH1D("hjetem", "Leading jet ECAL energy", 100, 0., 2000.);
  hjetem->Scale(rate/hjetem->Integral());
  chain->Draw("jets.eEm[0]>>hjetem");

  TH1D* hjethad = new TH1D("hjethad", "Leading jet HCAL energy", 100, 0., 10000.);
  hjethad->Scale(rate/hjethad->Integral());
  chain->Draw("jets.eHad[0]>>hjethad");

  TH1D* hjetn60 = new TH1D("hjetn60", "Leading jet N60", 100, 0., 50.);
  hjetn60->Scale(rate/hjetn60->Integral());
  chain->Draw("jets.n60[0]>>hjetn60");

  TH1D* hjetn90 = new TH1D("hjetn90", "Leading jet N90", 100, 0., 50.);
  hjetn90->Scale(rate/hjetn90->Integral());
  chain->Draw("jets.n90[0]>>hjetn90");


  // muons
  TH1D* hnmu = new TH1D("hnmu", "N muons", 4, -0.5, 3.5);
  hnmu->Scale(rate/hnmu->Integral());
  chain->Draw("nMuons>>hnmu");

  TH1D* hmupt = new TH1D("hmupt", "Leading muon p_t", 100, 0., 1000.);
  hmupt->Scale(rate/hmupt->Integral());
  chain->Draw("muons.pt[0]>>hmupt");


  // towers
  TH1D* hntow = new TH1D("hntow", "N towers", 100, 0., 100.);
  hntow->Scale(rate/hntow->Integral());
  chain->Draw("nTowers>>hntow");
  
  TH1D* htowe = new TH1D("htowe", "Leading tower energy", 100, 0., 10000.);
  htowe->Scale(rate/htowe->Integral());
  chain->Draw("towers.e[0]>>htowe");

  TH1D* htowem = new TH1D("htowem", "Leading tower ECAL energy", 100, 0., 2000.);
  htowem->Scale(rate/htowem->Integral());
  chain->Draw("towers.eEm[0]>>htowem");

  TH1D* htowhad = new TH1D("htowhad", "Leading tower HCAL energy", 100, 0., 10000.);
  htowhad->Scale(rate/htowhad->Integral());
  chain->Draw("towers.eHad[0]>>htowhad");
  
  hbx->Write();
  horb->Write();
  hls->Write();
  hjete->Write();
  hjeteta->Write();
  hjetphi->Write();
  hjetem->Write();
  hjethad->Write();
  hjetn60->Write();
  hjetn90->Write();
  hnmu->Write();
  hmupt->Write();
  hntow->Write();
  htowe->Write();
  htowem->Write();
  htowhad->Write();

  delete file;

}

void BasicPlots() {

  TFile file("BasicHistos.root","read");


  TPDF* pdf = new TPDF("BasicPlots.pdf");
  TCanvas* canvas = new TCanvas("canvas");

  TH1D* hbx = (TH1D*)file.Get("hbx");
  hbx->SetTitle("BX number");
  hbx->SetXTitle("N_{BX}");
  hbx->SetYTitle("Hz");
  hbx->Draw();
  canvas->Update();

  TH1D* horb = (TH1D*)file.Get("horb");
  horb->Draw();
  canvas->Update();

  TH1D* hls = (TH1D*)file.Get("hls");
  hls->Draw();
  canvas->Update();

  TH1D* hjete = (TH1D*)file.Get("hjete");
  hjete->SetXTitle("E (GeV)");
  hjete->SetYTitle("Hz / 200 GeV");
  hjete->Draw();
  canvas->Update();

  TH1D* hjeteta = (TH1D*)file.Get("hjeteta");
  hjeteta->SetXTitle("#eta");
  hjeteta->SetYTitle("Hz / 0.1");
  hjeteta->Draw();
  canvas->Update();

  TH1D* hjetphi = (TH1D*)file.Get("hjetphi");
  hjetphi->SetXTitle("#phi");
  hjetphi->SetYTitle("Hz");
  hjetphi->Draw();
  canvas->Update();

  TH1D* hjetem = (TH1D*)file.Get("hjetem");
  hjetem->SetXTitle("E_{ECAL} / GeV");
  hjetem->SetYTitle("Hz");
  hjetem->Draw();
  canvas->Update();

  TH1D* hjethad = (TH1D*)file.Get("hjethad");
  hjethad->SetXTitle("E_{HCAL} / GeV");
  hjethad->SetYTitle("Hz / 200 GeV");
  hjethad->Draw();
  canvas->Update();

  TH1D* hjetn60 = (TH1D*)file.Get("hjetn60");
  hjetn60->SetXTitle("n60");
  hjetn60->SetYTitle("N");
  hjetn60->Draw();
  canvas->Update();

  TH1D* hjetn90 = (TH1D*)file.Get("hjetn90");
  hjetn90->SetXTitle("n90");
  hjetn90->SetYTitle("N");
  hjetn90->Draw();
  canvas->Update();

  TH1D* hnmu = (TH1D*)file.Get("hnmu");
  hnmu->SetXTitle("N_{#mu}");
  hnmu->SetYTitle("Hz");
  hnmu->Draw();
  canvas->Update();

  TH1D* hmupt = (TH1D*)file.Get("hmupt");
  hmupt->SetXTitle("N_{#mu}");
  hmupt->SetYTitle("Hz / 10 GeV");
  hmupt->Draw();
  canvas->Update();

  TH1D* hntow = (TH1D*)file.Get("hntow");
  hntow->SetXTitle("N_{towers}");
  hntow->SetYTitle("Hz");
  hntow->Draw();
  canvas->Update();

  TH1D* htowe = (TH1D*)file.Get("htowe");
  htowe->SetXTitle("E (GeV)");
  htowe->SetYTitle("Hz / 50 GeV");
  htowe->Draw();
  canvas->Update();

  TH1D* htowem = (TH1D*)file.Get("htowem");
  htowem->SetXTitle("E (GeV)");
  htowem->SetYTitle("Hz / 20 GeV");
  htowem->Draw();
  canvas->Update();

  TH1D* htowhad = (TH1D*)file.Get("htowhad");
  htowhad->SetXTitle("E (GeV)");
  htowhad->SetYTitle("Hz / 100 GeV");
  htowhad->Draw();
  canvas->Update();

  pdf->Close();

}
