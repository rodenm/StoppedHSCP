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

  // Sample Histograms
  /*
  Nevents_ = new TH1D("Nevents","Number of events processed",1,0.5,1.5);
  OldiPhiFrac_= new TH1D("OldiPhiFrac","(Old) iPhi Fraction variable",880,-0.1,2.1);
  NewiPhiFrac_= new TH1D("NewiPhiFrac","(New) iPhi Fraction variable",880,-0.1,2.1);
  NewVsOldiPhiFrac_ = new TH2D("NewVsOldiPhiFrac","New iPhi Fraction vs Old iPhi Fraction; Old iPhi Fraction; New iPhi Fraction",880,-0.1,2.1,880,-0.1,2.1);
  iPhiFracDiff_ = new TH1D("iPhiFracDiff","1-(new iPhiFrac)/(old iPhiFrac)",1000,-0.05,0.05);
  */
}

void UserHistograms::fill(StoppedHSCPEvent& event) {
  /*
  Nevents_->Fill(1);
  double oldl=event.leadingIPhiFraction();
  double newl=event.leadingIPhiFractionValue;
  OldiPhiFrac_->Fill(oldl);
  NewiPhiFrac_->Fill(newl);
  iPhiFracDiff_->Fill(1-newl/oldl);
  NewVsOldiPhiFrac_->Fill(oldl, newl);
  if (oldl!=newl)
    std::cout <<"ERROR!  Old and new values differ!  old = "<<oldl<<"  new = "<<newl<<std::endl;
  return;
  */
}


void UserHistograms::save() {
  //std::cout <<"SAVING USER HISTS"<<std::endl;
  base_->cd("");
  /*
  Nevents_->Write("",TObject::kOverwrite);
  OldiPhiFrac_->Write();
  NewiPhiFrac_->Write();
  iPhiFracDiff_->Write();
  NewVsOldiPhiFrac_->Write();
  */
}


void UserHistograms::summarise() {


}
