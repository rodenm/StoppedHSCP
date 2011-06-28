
#include "StoppedHSCP/Analysis/interface/SignalHistograms.h"

#include "TMath.h"

#include <sstream>
#include <iostream>

SignalHistograms::SignalHistograms(TFile* file, Cuts* cuts) :
  cuts_(cuts),
  base_()
{
 
  // create directory structure
  file->mkdir("signal");
  base_ = file->GetDirectory("signal");

  book();

}

SignalHistograms::~SignalHistograms() {

}



void SignalHistograms::book() {

  base_->cd("");

  // time
  hbx_ = new TH1D("hsbx", "BX number", 3564, 0., 3564.);
  hrelbx_ = new TH1D("hsrelbx", "BX wrt coll", 200, -200.5, +199.5);
  hjete_ = new TH1D("hsjete", "Jet E", 50, 0., 100.);
  hjeteta_ = new TH1D("hsjeteta", "Leading jet #eta", 70, -3.5, 3.5);
  hjetphi_ = new TH1D("hsjetphi", "Leading jet #phi", 72, -1 * TMath::Pi(),  TMath::Pi());
  hjetetaphi_ = new TH2D("hsjetetaphi", "Leading jet pos", 70, -3.5, 3.5, 72, -1 * TMath::Pi(),  TMath::Pi());

}


void SignalHistograms::fill(StoppedHSCPEvent& event) {


  if (cuts_->cut()) {

    hbx_->Fill(event.bx);
    hrelbx_->Fill(event.bxWrtCollision);

    hjete_->Fill(event.jetE[0]);
    hjeteta_->Fill(event.jetEta[0]);
    hjetphi_->Fill(event.jetPhi[0]);
    hjetetaphi_->Fill(event.jetEta[0], event.jetPhi[0]);

  }

}


void SignalHistograms::save() {

  base_->cd("");

  hbx_->Write("",TObject::kOverwrite);
  hrelbx_->Write("",TObject::kOverwrite);

}


void SignalHistograms::summarise() {


}
