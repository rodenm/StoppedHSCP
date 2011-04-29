
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

  // time
  hbx_ = new TH1D("hbgbx", "BX number", 3564, 0., 3564.);

}


void BeamGasHistograms::fill(StoppedHSCPEvent& event) {

  hbx_->Fill(event.bx);
}


void BeamGasHistograms::save() {

  hbx_->Write("",TObject::kOverwrite);
}


void BeamGasHistograms::summarise() {


}
