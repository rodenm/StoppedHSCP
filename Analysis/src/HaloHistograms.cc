
#include "StoppedHSCP/Analysis/interface/HaloHistograms.h"

#include "TMath.h"

#include <sstream>
#include <iostream>

HaloHistograms::HaloHistograms(TFile* file, Cuts* cuts) :
  cuts_(cuts),
  base_()
{
 
  // create directory structure
  file->mkdir("halo");
  base_ = file->GetDirectory("halo");

  book();

  noHaloNoBxCuts_.push_back(4);
  noHaloNoBxCuts_.push_back(2);

  noHaloNoBxNoN90Cuts_.push_back(4);
  noHaloNoBxNoN90Cuts_.push_back(2);
  noHaloNoBxNoN90Cuts_.push_back(10);

  noHaloNoBxNoJetCuts_.push_back(4);
  noHaloNoBxNoJetCuts_.push_back(2);
  noHaloNoBxNoJetCuts_.push_back(8);

  noHaloNoBxNoN90NoJetCuts_.push_back(4);
  noHaloNoBxNoN90NoJetCuts_.push_back(2);
  noHaloNoBxNoN90NoJetCuts_.push_back(8);
  noHaloNoBxNoN90NoJetCuts_.push_back(10);

}

HaloHistograms::~HaloHistograms() {

}



void HaloHistograms::book() {

  base_->cd("");

  // halo identified events
  hbx_ = new TH1D("hhalobx", "BX number", 3564, 0., 3564.);
  hjete_ = new TH1D("hhalojete", "Jet E", 50, 0., 100.);
  hjeteta_ = new TH1D("hhalojeteta", "Leading jet #eta", 70, -3.5, 3.5);
  hjetphi_ = new TH1D("hhalojetphi", "Leading jet #phi", 72, -1 * TMath::Pi(),  TMath::Pi());
  hjetetaphi_ = new TH2D("hhalojetetaphi", "Leading jet pos", 70, -3.5, 3.5, 72, -1 * TMath::Pi(),  TMath::Pi());
  hjetn90_ = new TH1D("hhalojetn90", "Leading jet N90", 25, 0., 25.);

  hnm1bx_ = new TH1D("hhalonm1bx", "BX number", 3564, 0., 3564.);
  hnm1jete_ = new TH1D("hhalonm1jete", "Jet E", 50, 0., 100.);
  hnm1jeteta_ = new TH1D("hhalonm1jeteta", "Leading jet #eta", 70, -3.5, 3.5);
  hnm1jetphi_ = new TH1D("hhalonm1jetphi", "Leading jet #phi", 72, -1 * TMath::Pi(),  TMath::Pi());
  hnm1jetetaphi_ = new TH2D("hhalonm1jetetaphi", "Leading jet pos", 70, -3.5, 3.5, 72, -1 * TMath::Pi(),  TMath::Pi());
  hnm1jetn90_ = new TH1D("hhalonm1jetn90", "Leading jet N90", 25, 0., 25.);

  // BX-1 distributions
  hBXm1nm1eta_ = new TH1D("hhaloBXm1nm1eta", "Leading jet #eta", 70, -3.5, 3.5);

  // BX-1 no n90 distributions
  hBXm1nm1n90_ = new TH1D("hhaloBXm1nm1n90", "Leading jet N90", 25, 0., 25.);

  hBXm1nm2eta_ = new TH1D("hhaloBXm1nm2eta", "Leading jet #eta", 70, -3.5, 3.5);

}


void HaloHistograms::fill(StoppedHSCPEvent& event) {

  if (!cuts_->haloVeto()) {

    // all halo events
    hbx_->Fill(event.bx);

    if (event.jet_N > 0) {
      hjete_->Fill(event.jetE[0]);
      hjeteta_->Fill(event.jetEta[0]);
      hjetphi_->Fill(event.jetPhi[0]);
      hjetetaphi_->Fill(event.jetEta[0], event.jetPhi[0]);
      hjetn90_->Fill(event.jetN90[0]);
      
    }

    // halo events passing all others cuts 
    if (cuts_->cutNMinusOne(4)) {

      hnm1bx_->Fill(event.bx);
      
      if (event.jet_N > 0) {
	hnm1jete_->Fill(event.jetE[0]);
	hnm1jeteta_->Fill(event.jetEta[0]);
	hnm1jetphi_->Fill(event.jetPhi[0]);
	hnm1jetetaphi_->Fill(event.jetEta[0], event.jetPhi[0]);
	hnm1jetn90_->Fill(event.jetN90[0]);
	
      }
    }
    
    // halo events in BX -1
    if (event.bxWrtBunch==-1) {

      // jet eta
      if (cuts_->cutNMinusSome(noHaloNoBxNoJetCuts_) && event.jet_N>0 && event.jetE[0]>70.) {
	hBXm1nm1eta_->Fill(event.jetEta[0]);
      }

      // jet n90
      if (cuts_->cutNMinusSome(noHaloNoBxNoN90Cuts_)) {
	if (event.jet_N > 0) {
	  hBXm1nm1n90_->Fill(event.jetN90[0]);
	}
      }

      // jet eta before n90 and jet cuts
      if (cuts_->cutNMinusSome(noHaloNoBxNoN90NoJetCuts_)) {
	hBXm1nm2eta_->Fill(event.jetEta[0]);
      }

    }

  }

}


void HaloHistograms::save() {

  base_->cd("");

  hbx_->Write("",TObject::kOverwrite);
  hjete_->Write("",TObject::kOverwrite);
  hjeteta_->Write("",TObject::kOverwrite);
  hjetphi_->Write("",TObject::kOverwrite);
  hjetetaphi_->Write("",TObject::kOverwrite);
  hjetn90_->Write("",TObject::kOverwrite);

  hnm1bx_->Write("",TObject::kOverwrite);
  hnm1jete_->Write("",TObject::kOverwrite);
  hnm1jeteta_->Write("",TObject::kOverwrite);
  hnm1jetphi_->Write("",TObject::kOverwrite);
  hnm1jetetaphi_->Write("",TObject::kOverwrite);
  hnm1jetn90_->Write("",TObject::kOverwrite);
  hBXm1nm1eta_->Write("",TObject::kOverwrite);
  hBXm1nm1n90_->Write("",TObject::kOverwrite);
  hBXm1nm2eta_->Write("",TObject::kOverwrite);

}


void HaloHistograms::summarise() {


}
