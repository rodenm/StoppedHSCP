
#include "StoppedHSCP/Analysis/interface/ControlHistograms.h"

#include "TMath.h"

#include <sstream>
#include <iostream>

ControlHistograms::ControlHistograms(TFile* file, Cuts* cuts) :
  cuts_(cuts),
  base_()
{
 
  // create directory structure
  file->mkdir("control");
  base_ = file->GetDirectory("control");

  book();

}

ControlHistograms::~ControlHistograms() {

}



void ControlHistograms::book() {

  base_->cd("");

  // time
  hbx_ = new TH1D("hcbx", "BX number", 3564, 0., 3564.);
  hbxrel_ = new TH1D("hcbxrel", "BX wrt collision", 11, -5.5, 5.5);

  // HF quantities
  hehfp_ = new TH1D("hcehfp", "Energy HF+", 100, 0., 200.);
  hehfm_ = new TH1D("hcehfm", "Energy HF-", 100, 0., 200.);
  hehf_ = new TH1D("hcehf", "Energy HF total", 100, 0., 200.);

  // track quantities
  hntrk_ = new TH1D("hbgntrk", "N tracks", 20, -0.5, 19.5);

}


void ControlHistograms::fill(StoppedHSCPEvent& event) {

  // check this is a control trigger event
  //  if (cuts_->controlTrigger()) {

    hbx_->Fill(event.bx);
    hbxrel_->Fill(event.bxWrtCollision);

    hehfp_->Fill(event.hfPlusTotalE);
    hehfm_->Fill(event.hfMinusTotalE);
    hehf_->Fill(event.hfPlusTotalE + event.hfMinusTotalE);
    
    hntrk_->Fill(event.track_N);

    //  }

}


void ControlHistograms::save() {

  base_->cd("");

  hbx_->Write("",TObject::kOverwrite);
  hbxrel_->Write("",TObject::kOverwrite);

  hehfp_->Write("",TObject::kOverwrite);
  hehfm_->Write("",TObject::kOverwrite);
  hehf_->Write("",TObject::kOverwrite);
  
  hntrk_->Write("",TObject::kOverwrite);


}


void ControlHistograms::summarise() {


}
