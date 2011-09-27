

// this class stores an indexed collection of histograms
// all saved to a folder

#include "TDirectory.h"
#include "TH1D.h"

#include <vector>

class MultiHistogram1D {

 public:

  MultiHistogram1D(TDirectory* file, 
		   std::string name, 
		   std::string title,
		   unsigned nbins,
		   double min,
		   double max);

  ~MultiHistogram1D();

  void fill(unsigned index, double value, double weight=0.);

  void save();

 private:

  TDirectory* dir_;

  std::string name_;
  std::string title_;
  unsigned nbins_;
  double min_;
  double max_;
  
  std::vector<TH1D*> histos_;

};
