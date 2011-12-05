
#include "StoppedHSCP/Analysis/interface/MultiHistogram1D.h"

#include <iostream>
#include <sstream>

MultiHistogram1D::MultiHistogram1D() {

}

// copy constructor
// MultiHistogram1D::MultiHistogram1D(const MultiHistogram1D& mh,
// 				   TFile* file,
// 				   std::string name,
// 				   std::string title) {

//   // name
//   name_ = name;
//   std::cout << "Creating MultiHistogram1D " << name << std::endl;

//   // dir
//   file->mkdir(name_.c_str());
//   dir_ = file->GetDirectory(name_.c_str());
//   dir_->cd();

//   // title
//   if (title=="") title_ = mh.title();
//   else title_ = title;

//   // histo params
//   nbins_ = mh.nbins();
//   min_   = mh.min();
//   max_   = mh.max();

//   // copy histograms
//   for (unsigned i=0; i<mh.size(); ++i) {

//     // resize histo container if needed
//     if (histos_.size() < i+1) histos_.resize(i+1, 0);

//     // copy histogram if it exists
//     if (mh.histogram(i) != 0) {

//       histos_.at(i) = (TH1D*) mh.histogram(i)->Clone(name_.c_str());
    
//       // set title
//       histos_.at(i)->SetTitle(title_.c_str());

//     }

//   }

// }

// MultiHistogram1D::MultiHistogram1D(TDirectory* file, 
// 				   std::string name, 
// 				   std::string title,
// 				   unsigned nbins,
// 				   double min,
// 				   double max) :
//   name_(name),
//   title_(title),
//   nbins_(nbins),
//   min_(min),
//   max_(max)
// {

//   file->mkdir(name.c_str());
//   dir_ = file->GetDirectory(name.c_str());

// }


MultiHistogram1D::~MultiHistogram1D() {

  std::vector<TH1D*>::iterator itr;
  for (itr=histos_.begin(); itr!=histos_.end(); ++itr) {
    if (*itr != 0) delete (*itr);
  }

}


void MultiHistogram1D::setup(TDirectory* file, 
			    std::string name, 
			    std::string title,
			    unsigned nbins,
			    double min,
			    double max) {
  name_ = name;
  title_ = title;
  nbins_ = nbins;
  min_ = min;
  max_ = max;
  file->mkdir(name.c_str());
  dir_ = file->GetDirectory(name.c_str());
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
    dir_->cd();
    histos_.at(index) = new TH1D((name_+istr).c_str(), title_.c_str(), nbins_, min_, max_);
  }
  
  // fill histogram
  if (weight > 0.) {
    histos_.at(index)->Fill(value, weight);
  }

}

void MultiHistogram1D::save() {

  std::cout << "Saving " << name_ << " histograms.  size=" << histos_.size() << std::endl;

  dir_->cd();

  // loop over fills
  std::vector<TH1D*>::const_iterator itr;
  for (itr=histos_.begin(); itr!=histos_.end(); ++itr) {
    if (*itr != 0) (*itr)->Write("",TObject::kOverwrite);
  }

}


void MultiHistogram1D::print(std::ostream& os) {

  os << "MultiHistogram1D : " << name_ << std::endl;

  os << "  Title    : " << title_ << std::endl;
  os << "  Nbins    : " << nbins_ << std::endl;
  os << "  xmin     : " << min_ << std::endl;
  os << "  xmax     : " << max_ << std::endl;
  os << "  size     : " << histos_.size() << std::endl;
  os << std::endl;

}
