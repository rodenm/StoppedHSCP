
#include "StoppedHSCP/Analysis/interface/BeamGasHistograms.h"

#include "TMath.h"

#include <sstream>
#include <iostream>

BeamGasHistograms::BeamGasHistograms(TFile* file, Cuts* cuts) :
  cuts_(cuts),
  base_()
{
 
  // create directory structure
  file->mkdir("halo");
  base_ = file->GetDirectory("halo");

  book();

}

BeamGasHistograms::~BeamGasHistograms() {

}



void BeamGasHistograms::book() {

  // time
  hbx_ = new TH1D("hbx", "BX number", 3564, 0., 3564.);

}


void BeamGasHistograms::fill(StoppedHSCPEvent& event) {

  hbx_->Fill(event.bx);
}


void BeamGasHistograms::save() {

  hbx_->Write("",TObject::kOverwrite);
}


void BeamGasHistograms::summarise() {


}
