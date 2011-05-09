
#include "StoppedHSCP/Analysis/interface/BeamGasHistograms.h"

#include "TMath.h"

#include <sstream>
#include <iostream>

BeamGasHistograms::BeamGasHistograms(TFile* file, Cuts* cuts) :
  cuts_(cuts),
  base_()
{
 
  // create directory structure
  file->mkdir("beamgas");
  base_ = file->GetDirectory("beamgas");

  book();

}

BeamGasHistograms::~BeamGasHistograms() {

}



void BeamGasHistograms::book() {

  base_->cd("");

  // events with HF energy
  hbx_ = new TH1D("hbgbx", "BX number", 3564, 0., 3564.);



}


void BeamGasHistograms::fill(StoppedHSCPEvent& event) {

  // all events

  // events failing HF veto
  if (!cuts_->hfVeto()) {

    hbx_->Fill(event.bx);

  }

}


void BeamGasHistograms::save() {

  base_->cd("");

  hbx_->Write("",TObject::kOverwrite);

}


void BeamGasHistograms::summarise() {


}
