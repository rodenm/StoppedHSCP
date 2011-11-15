
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

  static const double LUMIFILE_TO_PB;
  static const double THRESHOLD;

  typedef std::vector<LumiBlock>::const_iterator const_iterator;

 public:
  Luminosity();
  ~Luminosity();

  // STL access operators
  unsigned int size() const;
  LumiBlock at(unsigned long i) const { return lumis_.at(i); }
  Luminosity::const_iterator begin() { return lumis_.begin(); }
  Luminosity::const_iterator end() { return lumis_.end(); }
  Luminosity::const_iterator beginRun(unsigned run);
  Luminosity::const_iterator endRun(unsigned run);

  // get lumiblock
  LumiBlock block(unsigned long i) const { return lumis_.at(i); }

  // get run
  unsigned run(unsigned long i) const { return lumis_.at(i).run; }

  // get integrated luminosity for a block (pb^-1)
  double luminosity(unsigned long int i) const { return lumis_.at(i).lumi; }

  // was CMS sensitive for this block
  bool cmsSensitive(unsigned long int i) const { return lumis_.at(i).good; }
  
  // build model from the database
  void buildFromDB(unsigned lumiFirstRun,
		   unsigned lumiLastRun);

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
