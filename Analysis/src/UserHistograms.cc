#include "StoppedHSCP/Analysis/interface/UserHistograms.h"

#include "TMath.h"

#include <sstream>
#include <iostream>

/*
  UserHistograms allows users to add diagnostic, etc. histograms in a separate directory without affecting any of the default analysis histogram scripts.


*/

UserHistograms::UserHistograms(TFile* file, Cuts* cuts) :
  cuts_(cuts),
  base_()
{
 
  // create directory structure
  file->mkdir("UserHists");
  base_ = file->GetDirectory("UserHists");

  book();
}

UserHistograms::~UserHistograms() {

}



void UserHistograms::book() {

  base_->cd("");

  // Sample Histogram
  Nevents_ = new TH1D("Nevents","Number of events processed",1,0.5,1.5);

}

void UserHistograms::fill(StoppedHSCPEvent& event) {

  Nevents_->Fill(1);

  return;
}


void UserHistograms::save() {
  //std::cout <<"SAVING USER HISTS"<<std::endl;
  base_->cd("");
  Nevents_->Write("",TObject::kOverwrite);
}


void UserHistograms::summarise() {


}
