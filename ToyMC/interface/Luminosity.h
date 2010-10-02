
#ifndef Luminosity_h
#define Luminosity_h

#include <vector>
#include "TCanvas.h"

struct LumiBlock {
  unsigned long run;
  unsigned long ls;
  double lumi;
  bool good;
};

class Luminosity {

 public:
  Luminosity();
  ~Luminosity();

  // how many blocks
  unsigned int size() const;

  // get lumiblock
  LumiBlock block(unsigned long i) const { return lumis_.at(i); }

  // get integrated luminosity for a block (pb^-1)
  double luminosity(unsigned long int i) const { return lumis_.at(i).lumi; }

  // was CMS sensitive for this block
  bool cmsSensitive(unsigned long int i) const { return lumis_.at(i).good; }
  
  // build model from file, for a list of runs
  void buildFromFile(std::vector<unsigned long> runs, 
		     bool useHists,
		     std::string goodLSFile,
		     unsigned lumiFirstRun,
		     unsigned lumiLastRun);

  // generate model from parameters
  void buildFromModel(unsigned int cycles, 
		      unsigned int units_on, 
		      unsigned int units_off,
		      double amt);

  double getTotalLumi() { return totalLumi; }

  // make plots
  void makePlots() const;

  void dump(ostream& o, bool full);

 private:

  std::vector<struct LumiBlock> lumis_;

  double totalLumi;
  unsigned nGoodLS;

};

#endif
