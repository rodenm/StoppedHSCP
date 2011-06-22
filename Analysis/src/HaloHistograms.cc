
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

  base_->cd("");

  // time
  hbx_ = new TH1D("hhalobx", "BX number", 3564, 0., 3564.);
  hjete_ = new TH1D("hjete", "Jet E", 50, 0., 100.);

}


void HaloHistograms::fill(StoppedHSCPEvent& event) {

  if (!cuts_->haloVeto()) {

    hbx_->Fill(event.bx);

    if (event.jet_N > 0) hjete_->Fill(event.jetE[0]);

  }
}


void HaloHistograms::save() {

  base_->cd("");

  hbx_->Write("",TObject::kOverwrite);
  hjete_->Write("",TObject::kOverwrite);

}


void HaloHistograms::summarise() {


}
