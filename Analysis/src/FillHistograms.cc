#include "StoppedHSCP/Analysis/interface/FillHistograms.h"

#include "TMath.h"

#include <sstream>
#include <iostream>

FillHistograms::FillHistograms(TFile* file, std::string name, Cuts* cuts) :
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


FillHistograms::~FillHistograms() {

}



void FillHistograms::book() {

}


void FillHistograms::fill(StoppedHSCPEvent& event) {

}


void FillHistograms::save() {

}
