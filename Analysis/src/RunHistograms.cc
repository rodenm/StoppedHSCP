#include "StoppedHSCP/Analysis/interface/RunHistograms.h"

#include "TMath.h"

#include <sstream>
#include <iostream>

RunHistograms::RunHistograms(TFile* file, std::string name, Cuts* cuts) :
  cuts_(cuts),
  base_()
{
 
  // create directory structure
  file->mkdir(name.c_str());
  base_ = file->GetDirectory(name.c_str());
  base_->mkdir("NoCuts");  
  base_->mkdir("Cuts");

  book();

}


RunHistograms::~RunHistograms() {

}



void RunHistograms::book() {

}


void RunHistograms::fill(StoppedHSCPEvent& event) {

}


void RunHistograms::save() {

}
