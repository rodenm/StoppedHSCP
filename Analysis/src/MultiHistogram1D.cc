
#include "StoppedHSCP/Analysis/interface/MultiHistogram1D.h"

#include <iostream>
#include <sstream>

MultiHistogram1D::MultiHistogram1D(TDirectory* file, 
				   std::string name, 
				   std::string title,
				   unsigned nbins,
				   double min,
				   double max) :
  name_(name),
  title_(title),
  nbins_(nbins),
  min_(min),
  max_(max)
{

  file->mkdir(name.c_str());
  dir_ = file->GetDirectory(name.c_str());

}


MultiHistogram1D::~MultiHistogram1D() {

  std::vector<TH1D*>::iterator itr;
  for (itr=histos_.begin(); itr!=histos_.end(); ++itr) {
    if (*itr != 0) delete (*itr);
  }

  histos_.clear();

}


void MultiHistogram1D::fill(unsigned index, double value, double weight) {

  std::stringstream ss;
  ss << index;
  std::string istr = ss.str();

  // create new histogram if needed
  if (histos_.size() < index+1) {
    histos_.resize(index+1, 0);
  }

  if (histos_.at(index)==0) {
    histos_.at(index) = new TH1D((name_+istr).c_str(), title_.c_str(), nbins_, min_, max_);
  }
  
  // fill histogram
  if (weight>0.) {
    histos_.at(index)->Fill(value, weight);
  }
  else {
    histos_.at(index)->Fill(value);
  }

}

void MultiHistogram1D::save() {

  dir_->cd();

  // loop over fills
  std::vector<TH1D*>::const_iterator itr;
  for (itr=histos_.begin(); itr!=histos_.end(); ++itr) {
    if (*itr != 0) (*itr)->Write("",TObject::kOverwrite);
  }

}
