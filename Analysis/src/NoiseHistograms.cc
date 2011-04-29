
#include "StoppedHSCP/Analysis/interface/NoiseHistograms.h"

#include "TMath.h"

#include <sstream>
#include <iostream>

NoiseHistograms::NoiseHistograms(TFile* file, Cuts* cuts) :
  cuts_(cuts),
  base_()
{
 
  // create directory structure
  file->mkdir("halo");
  base_ = file->GetDirectory("halo");

  book();

}

NoiseHistograms::~NoiseHistograms() {

}



void NoiseHistograms::book() {

  // time
  hbx_ = new TH1D("hbx", "BX number", 3564, 0., 3564.);

}


void NoiseHistograms::fill(StoppedHSCPEvent& event) {

  hbx_->Fill(event.bx);
}


void NoiseHistograms::save() {

  hbx_->Write("",TObject::kOverwrite);
}


void NoiseHistograms::summarise() {


}
