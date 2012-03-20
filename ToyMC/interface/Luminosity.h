
#ifndef Luminosity_h
#define Luminosity_h

#include "StoppedHSCP/ToyMC/interface/jsonxx.h"

#include <vector>
#include "TCanvas.h"
#include "TFile.h"



struct LumiBlock {
  unsigned long id;
  unsigned long run;
  unsigned long ls;
  unsigned long orbit;
  double lumi;
  bool good;
  time_t timestamp;
};

class Luminosity {

 public:

  static const double LUMIFILE_TO_PB;
  static const double THRESHOLD;

  typedef std::vector<LumiBlock>::const_iterator const_iterator;

 public:
  Luminosity();
  ~Luminosity();

  // setup first

  // open good LS file
  void openGoodLSFile(bool useHists,
		      std::string goodLSFile);

  bool goodData(unsigned run, unsigned ls);

  // build model from the database
  void buildFromDB(std::vector<unsigned long> runs,
		   bool useHists,
		   std::string goodLSFile,
		   unsigned lumiFirstRun,
		   unsigned lumiLastRun);

  // build model from file, for a list of runs
  void buildFromFile(std::string filename,
		     std::vector<unsigned long> runs, 
		     bool useHists,
		     std::string goodLSFile,
		     unsigned lumiFirstRun,
		     unsigned lumiLastRun);

  // build model from file, compatible with lumiCalc2 output
  void buildFromFile2(std::string filename,
		      std::vector<unsigned long> runs, 
		      bool useHists,
		      std::string goodLSFile,
		      unsigned lumiFirstRun,
		      unsigned lumiLastRun);
  
  // generate model from parameters
  void buildFromModel(unsigned int cycles, 
		      unsigned int units_on, 
		      unsigned int units_off,
		      double amt);


  // access methods

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

  double getTotalLumi() { return totalLumi_; }

  // make plots
  void makePlots() const;

  // print out
  void dump(ostream& o, bool full);

 private:

  // good lumi information - either histogram file or JSON file
  bool useHists_;
  TFile* histFile_;
  jsonxx::Object goodLumis_;

  // the lumi data structure
  std::vector<struct LumiBlock> lumis_;

  // summary info
  double totalLumi_;
  unsigned nGoodLS_;

};

#endif
