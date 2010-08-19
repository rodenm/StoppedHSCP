
#ifndef Luminosity_h
#define Luminosity_h

#include <vector>
#include "TCanvas.h"

struct LumiBlock {
  unsigned long run;
  unsigned long ls;
  double lumi;  // what fucking units?
  double cmsSensitivity;
};

class Luminosity {

 public:
  Luminosity();
  ~Luminosity();

  // access lumi value
  //  double operator[](unsigned int) const;

  // how many blocks
  unsigned int size() const;

  // get luminosity for a block
  double luminosity(unsigned long int i) const { return lumis_.at(i).lumi; }

  // was CMS sensitive for this block
  bool cmsSensitive(unsigned long int i) const { return lumis_.at(i).cmsSensitivity > 0.01; }
  
  // build model from file, for a list of runs
  void buildFromFile(std::vector<unsigned long> runs);

  // generate model from parameters
  void buildFromModel(unsigned int cycles, 
		      unsigned int units_on, 
		      unsigned int units_off,
		      double amt);

  // make plots
  void makePlots() const;

 private:

  std::vector<struct LumiBlock> lumis_;

};

#endif
