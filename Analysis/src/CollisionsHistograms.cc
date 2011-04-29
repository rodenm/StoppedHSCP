
#include "StoppedHSCP/Analysis/interface/CollisionsHistograms.h"

#include "TMath.h"

#include <sstream>
#include <iostream>

CollisionsHistograms::CollisionsHistograms(TFile* file, Cuts* cuts) :
  cuts_(cuts),
  base_()
{
 
  // create directory structure
  file->mkdir("halo");
  base_ = file->GetDirectory("halo");

  book();

}

CollisionsHistograms::~CollisionsHistograms() {

}



void CollisionsHistograms::book() {

  // time
  hbx_ = new TH1D("hbx", "BX number", 3564, 0., 3564.);

}


void CollisionsHistograms::fill(StoppedHSCPEvent& event) {

  hbx_->Fill(event.bx);
}


void CollisionsHistograms::save() {

  hbx_->Write("",TObject::kOverwrite);
}


void CollisionsHistograms::summarise() {


}