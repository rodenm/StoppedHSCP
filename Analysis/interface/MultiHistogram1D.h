

// this class stores an indexed collection of histograms
// all saved to a folder

#include "TDirectory.h"
#include "TH1D.h"
#include "TFile.h"

#include <vector>

class MultiHistogram1D {

 public:

  MultiHistogram1D();

  // copy constructor
/*   MultiHistogram1D(const MultiHistogram1D& mh, */
/* 		   TFile* file, */
/* 		   std::string name, */
/* 		   std::string title=""); */

  //  MultiHistogram1D(TDirectory* file=0, 
  //		   std::string name=std::string(""), 
  //		   std::string title=std::string(""),
  //		   unsigned nbins=0,
  //		   double min=0.,
  //		   double max=0.);

  ~MultiHistogram1D();

  void setup(TDirectory* file, 
	     std::string name, 
	     std::string title,
	     unsigned nbins,
	     double min,
	     double max);

  void fill(unsigned index, double value, double weight=1.);

  void save();

  const TH1D* histogram(unsigned index) const {
    if (index < histos_.size() && histos_.at(index)!=0) return histos_.at(index); 
    else return 0;
  }

  TH1D* hist(unsigned index) {
    if (index < histos_.size() && histos_.at(index)!=0) return histos_.at(index);
    else return 0;
  }

  std::string name() const { return name_; }

  std::string title() const { return title_; }

  unsigned nbins() const { return nbins_; }

  double min() const { return min_; }
  
  double max() const { return max_; }

  unsigned size() const { return histos_.size(); }

  void print(std::ostream& os);

 private:

  TDirectory* dir_;

  std::string name_;
  std::string title_;
  unsigned nbins_;
  double min_;
  double max_;
  
  std::vector<TH1D*> histos_;

};
