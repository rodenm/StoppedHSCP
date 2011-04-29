
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

}

HaloHistograms::~HaloHistograms() {

}



void HaloHistograms::book() {

  // time
  hbx_ = new TH1D("hbx", "BX number", 3564, 0., 3564.);

}


void HaloHistograms::fill(StoppedHSCPEvent& event) {

  hbx_->Fill(event.bx);
}


void HaloHistograms::save() {

  hbx_->Write("",TObject::kOverwrite);
}


void HaloHistograms::summarise() {


}