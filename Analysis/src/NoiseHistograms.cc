
#include "StoppedHSCP/Analysis/interface/NoiseHistograms.h"

#include "TMath.h"

#include <sstream>
#include <iostream>

NoiseHistograms::NoiseHistograms(TFile* file, Cuts* cuts) :
  cuts_(cuts),
  base_()
{
 
  // create directory structure
  file->mkdir("noise");
  base_ = file->GetDirectory("noise");

  book();

  nm1cuts_.push_back(6); // noise veto
  nm1cuts_.push_back(9); // n60
  nm1cuts_.push_back(11); // nTowIPhi
  nm1cuts_.push_back(12); // iPhiFrac

}

NoiseHistograms::~NoiseHistograms() {

}



void NoiseHistograms::book() {

  base_->cd("");

  // time
  hbx_ = new TH1D("hnoisebx", "BX number", 3564, 0., 3564.);
  hjete_ = new TH1D("hnoisejete", "Jet E", 50, 0., 100.);
  hjeteta_ = new TH1D("hnoisejeteta", "Leading jet #eta", 70, -3.5, 3.5);
  hjetphi_ = new TH1D("hnoisejetphi", "Leading jet #phi", 72, -1 * TMath::Pi(),  TMath::Pi());
  hjetetaphi_ = new TH2D("hnoisejetetaphi", "Leading jet pos", 70, -3.5, 3.5, 72, -1 * TMath::Pi(),  TMath::Pi());

  hnm1bx_ = new TH1D("hnoisenm1bx", "BX number", 3564, 0., 3564.);
  hnm1jete_ = new TH1D("hnoisenm1jete", "Jet E", 50, 0., 100.);
  hnm1jeteta_ = new TH1D("hnoisenm1jeteta", "Leading jet #eta", 70, -3.5, 3.5);
  hnm1jetphi_ = new TH1D("hnoisenm1jetphi", "Leading jet #phi", 72, -1 * TMath::Pi(),  TMath::Pi());
  hnm1jetetaphi_ = new TH2D("hnoisenm1jetetaphi", "Leading jet pos", 70, -3.5, 3.5, 72, -1 * TMath::Pi(),  TMath::Pi());

}


void NoiseHistograms::fill(StoppedHSCPEvent& event) {

  // noise tagged events
  if (!event.noiseFilterResult) {

    hbx_->Fill(event.bx);
    
    if (event.jet_N > 0) {
      hjete_->Fill(event.jetE[0]);
      hjeteta_->Fill(event.jetEta[0]);
      hjetphi_->Fill(event.jetPhi[0]);
      hjetetaphi_->Fill(event.jetEta[0], event.jetPhi[0]);
    }

  }

  // N-1 noise
  if (cuts_->cutNMinusSome(nm1cuts_)) {

    hnm1bx_->Fill(event.bx);
    
    if (event.jet_N > 0) {
      hnm1jete_->Fill(event.jetE[0]);
      hnm1jeteta_->Fill(event.jetEta[0]);
      hnm1jetphi_->Fill(event.jetPhi[0]);
      hnm1jetetaphi_->Fill(event.jetEta[0], event.jetPhi[0]);
    }

  }


}


void NoiseHistograms::save() {

  base_->cd("");

  hbx_->Write("",TObject::kOverwrite);
  hjeteta_->Write("",TObject::kOverwrite);
  hjetphi_->Write("",TObject::kOverwrite);
  hjetetaphi_->Write("",TObject::kOverwrite);

  hnm1bx_->Write("",TObject::kOverwrite);
  hnm1jete_->Write("",TObject::kOverwrite);
  hnm1jeteta_->Write("",TObject::kOverwrite);
  hnm1jetphi_->Write("",TObject::kOverwrite);
  hnm1jetetaphi_->Write("",TObject::kOverwrite);

}


void NoiseHistograms::summarise() {


}
