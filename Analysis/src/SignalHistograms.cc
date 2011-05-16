
#include "StoppedHSCP/Analysis/interface/SignalHistograms.h"

#include "TMath.h"

#include <sstream>
#include <iostream>

SignalHistograms::SignalHistograms(TFile* file, Cuts* cuts) :
  cuts_(cuts),
  base_()
{
 
  // create directory structure
  file->mkdir("signal");
  base_ = file->GetDirectory("signal");

  book();

}

SignalHistograms::~SignalHistograms() {

}



void SignalHistograms::book() {

  base_->cd("");

  // time
  hbx_ = new TH1D("hsbx", "BX number", 3564, 0., 3564.);
  hrelbx_ = new TH1D("hsrelbx", "BX wrt coll", 200, -200.5, +199.5);

}


void SignalHistograms::fill(StoppedHSCPEvent& event) {

  hbx_->Fill(event.bx);
}


void SignalHistograms::save() {

  base_->cd("");

  hbx_->Write("",TObject::kOverwrite);
  hrelbx_->Write("",TObject::kOverwrite);

}


void SignalHistograms::summarise() {


}
