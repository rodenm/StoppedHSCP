#include "StoppedHSCP/Analysis/interface/FillHistograms.h"

#include "TMath.h"

#include <sstream>
#include <iostream>

FillHistograms::FillHistograms(TFile* file, Cuts* cuts) :
  cuts_(cuts),
  base_(),
  fills_(0),
  hbx_(0),
  horb_(0),
  hlb_(0)
{
 
  // create directory structure
  file->mkdir("fills");
  base_ = file->GetDirectory("fills");

  // these histograms will be booked on the fly
  //  book();

}


FillHistograms::~FillHistograms() {

  // print list of fills found
  sort(fills_.begin(), fills_.end());
  std::cout << std::endl;
  std::cout << "Fills : ";
  for (unsigned i=0; i<fills_.size(); ++i) {
    std::cout << fills_.at(i);
    if (i<fills_.size()-1) std::cout << ",";
  }
  std::cout << std::endl;

  // clean up memory
  std::vector<TH1D*>::iterator itr;

  for (itr=hbx_.begin(); itr!=hbx_.end(); ++itr) delete (*itr);
  for (itr=horb_.begin(); itr!=horb_.end(); ++itr) delete (*itr);
  for (itr=hlb_.begin(); itr!=hlb_.end(); ++itr) delete (*itr);

  hbx_.clear();
  horb_.clear();
  hlb_.clear();

}



void FillHistograms::book(unsigned long fill) {

  // check if this run has already been booked and bail if so
  std::vector<unsigned long>::const_iterator itr = find(fills_.begin(), fills_.end(), fill);
  if (itr != fills_.end()) return;

  std::cout << "Creating histograms for new fill #" << fill << std::endl;

  // set up new run directory 
  std::stringstream fillstr;
  fillstr << fill;
  base_->mkdir(fillstr.str().c_str());

  // resize vectors if need be, without creating histograms
  if (hbx_.size() < fill+1) hbx_.resize(fill+1, 0);
  if (horb_.size() < fill+1) horb_.resize(fill+1, 0);
  if (hlb_.size() < fill+1) hlb_.resize(fill+1, 0);

  // and book histograms
  hbx_.at(fill) = new TH1D((std::string("hbx")+fillstr.str()).c_str(), "BX number", 3564, 0., 3564.);
  horb_.at(fill) = new TH1D((std::string("horb")+fillstr.str()).c_str(), "Orbit number", 100, 0., 10000.);
  hlb_.at(fill) = new TH1D((std::string("hlb")+fillstr.str()).c_str(), "Lumi block", 5000, 0., 5000.);
  
  // record the fact we booked this fill already
  fills_.push_back(fill);

}


void FillHistograms::fill(StoppedHSCPEvent& event) {

  // get fill number
  unsigned long fill = event.fill;

  // book histos
  book(fill);
  
  // fill histos
  hbx_.at(fill)->Fill(event.bx);
  horb_.at(fill)->Fill(event.orbit);
  hlb_.at(fill)->Fill(event.lb);

}


void FillHistograms::save() {

  // loop over fills
  std::vector<unsigned long>::const_iterator itr;
  for (itr=fills_.begin(); itr!=fills_.end(); ++itr) {

    // cd to directory
    std::stringstream fillstr;
    fillstr << (*itr);
    base_->cd(fillstr.str().c_str());

    // save histograms
    hbx_.at(*itr)->Write("",TObject::kOverwrite);
    horb_.at(*itr)->Write("",TObject::kOverwrite);
    hlb_.at(*itr)->Write("",TObject::kOverwrite);

  }

}


void FillHistograms::summarise() {

}
