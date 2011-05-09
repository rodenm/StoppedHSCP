
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

}

NoiseHistograms::~NoiseHistograms() {

}



void NoiseHistograms::book() {

  base_->cd("");

  // time
  hbx_ = new TH1D("hnoisebx", "BX number", 3564, 0., 3564.);

}


void NoiseHistograms::fill(StoppedHSCPEvent& event) {

  hbx_->Fill(event.bx);
}


void NoiseHistograms::save() {

  base_->cd("");

  hbx_->Write("",TObject::kOverwrite);

}


void NoiseHistograms::summarise() {


}
