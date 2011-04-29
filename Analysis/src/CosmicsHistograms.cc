
#include "StoppedHSCP/Analysis/interface/CosmicsHistograms.h"

#include "TMath.h"

#include <sstream>
#include <iostream>

CosmicsHistograms::CosmicsHistograms(TFile* file, Cuts* cuts) :
  cuts_(cuts),
  base_()
{
 
  // create directory structure
  file->mkdir("halo");
  base_ = file->GetDirectory("halo");

  book();

}

CosmicsHistograms::~CosmicsHistograms() {

}



void CosmicsHistograms::book() {

  // time
  hbx_ = new TH1D("hbx", "BX number", 3564, 0., 3564.);

}


void CosmicsHistograms::fill(StoppedHSCPEvent& event) {

  hbx_->Fill(event.bx);
}


void CosmicsHistograms::save() {

  hbx_->Write("",TObject::kOverwrite);
}


void CosmicsHistograms::summarise() {


}
