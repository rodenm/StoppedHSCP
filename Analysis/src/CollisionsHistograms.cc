
#include "StoppedHSCP/Analysis/interface/CollisionsHistograms.h"

#include "TMath.h"

#include <sstream>
#include <iostream>

CollisionsHistograms::CollisionsHistograms(TFile* file, Cuts* cuts) :
  cuts_(cuts),
  base_()
{
 
  // create directory structure
  file->mkdir("collisions");
  base_ = file->GetDirectory("collisions");

  book();

}

CollisionsHistograms::~CollisionsHistograms() {

}



void CollisionsHistograms::book() {

  base_->cd("");

  // time
  hbx_ = new TH1D("hcollbx", "BX number", 3564, 0., 3564.);

}


void CollisionsHistograms::fill(StoppedHSCPEvent& event) {

  hbx_->Fill(event.bx);
}


void CollisionsHistograms::save() {

  base_->cd("");

  hbx_->Write("",TObject::kOverwrite);

}


void CollisionsHistograms::summarise() {


}
