
#include "StoppedHSCP/Analysis/interface/CosmicsHistograms.h"

#include "TMath.h"

#include <sstream>
#include <iostream>

CosmicsHistograms::CosmicsHistograms(TFile* file, Cuts* cuts) :
  cuts_(cuts),
  base_()
{
 
  // create directory structure
  file->mkdir("cosmics");
  base_ = file->GetDirectory("cosmics");

  book();

}

CosmicsHistograms::~CosmicsHistograms() {

}



void CosmicsHistograms::book() {

  base_->cd("");

  // time
  hbx_ = new TH1D("hcosbx", "BX number", 3564, 0., 3564.);
  hjete_ = new TH1D("hcosjete", "Jet E", 50, 0., 100.);
  hjeteta_ = new TH1D("hcosjeteta", "Leading jet #eta", 70, -3.5, 3.5);
  hjetphi_ = new TH1D("hcosjetphi", "Leading jet #phi", 72, -1 * TMath::Pi(),  TMath::Pi());
  hjetetaphi_ = new TH2D("hcosjetetaphi", "Leading jet pos", 70, -3.5, 3.5, 72, -1 * TMath::Pi(),  TMath::Pi());

  hnm1bx_ = new TH1D("hcosnm1bx", "BX number", 3564, 0., 3564.);
  hnm1jete_ = new TH1D("hcosnm1jete", "Jet E", 50, 0., 100.);
  hnm1jeteta_ = new TH1D("hcosnm1jeteta", "Leading jet #eta", 70, -3.5, 3.5);
  hnm1jetphi_ = new TH1D("hcosnm1jetphi", "Leading jet #phi", 72, -1 * TMath::Pi(),  TMath::Pi());
  hnm1jetetaphi_ = new TH2D("hcosnm1jetetaphi", "Leading jet pos", 70, -3.5, 3.5, 72, -1 * TMath::Pi(),  TMath::Pi());

}


void CosmicsHistograms::fill(StoppedHSCPEvent& event) {

  // events passing halo veto but not cosmic veto
  if (!cuts_->cosmicVeto() && cuts_->haloVeto()) {

    hbx_->Fill(event.bx);

    if (event.jet_N > 0) {
      hjete_->Fill(event.jetE[0]);
      hjeteta_->Fill(event.jetEta[0]);
      hjetphi_->Fill(event.jetPhi[0]);
      hjetetaphi_->Fill(event.jetEta[0], event.jetPhi[0]);
    }

  }

  // N-1 noise
  if (cuts_->cutNMinusOne(5)) {

    hnm1bx_->Fill(event.bx);
    
    if (event.jet_N > 0) {
      hnm1jete_->Fill(event.jetE[0]);
      hnm1jeteta_->Fill(event.jetEta[0]);
      hnm1jetphi_->Fill(event.jetPhi[0]);
      hnm1jetetaphi_->Fill(event.jetEta[0], event.jetPhi[0]);
    }

  }


}


void CosmicsHistograms::save() {

  base_->cd("");

  hbx_->Write("",TObject::kOverwrite);
  hjete_->Write("",TObject::kOverwrite);
  hjeteta_->Write("",TObject::kOverwrite);
  hjetphi_->Write("",TObject::kOverwrite);
  hjetetaphi_->Write("",TObject::kOverwrite);

  hnm1bx_->Write("",TObject::kOverwrite);
  hnm1jete_->Write("",TObject::kOverwrite);
  hnm1jeteta_->Write("",TObject::kOverwrite);
  hnm1jetphi_->Write("",TObject::kOverwrite);
  hnm1jetetaphi_->Write("",TObject::kOverwrite);


}


void CosmicsHistograms::summarise() {


}
