//
// ToyStoppedHSCP
// Jim Brooke
//
// Class to run stopped HSCP toy MC
// Based on code from Ken/Ben/Fedor/Chris
//

// system
#include <vector>
#include <fstream>

// ROOT headers
#include "TGraphAsymmErrors.h"

// my headers
#include "interface/Experiment.h"


class TGraph;
class TMultiGraph;
class TH1D;
class TH2D;
class TTree;
class TFile;


class ToyStoppedHSCP {
public:

  ToyStoppedHSCP(char * rootfile, char * logfile);
  ~ToyStoppedHSCP();

  // setup bunch structure
  void setupBunchStructure(int bx_struct);  // use 2808 for now

  // one experiment and add to vector
  void run(Experiment exp);

  // number of experiments
  unsigned nExperiments() { return experiments_.size(); }

  // get vector of experiments
  std::vector<Experiment> getExperiments() { return experiments_; }

  // get experiment
  Experiment getExperiment(unsigned i) { 
    if (i<experiments_.size()) return experiments_.at(i);
    else return Experiment();
  }


  // files
  void save();


  // get plot of significance as fn of running time for given mass/lifetime
  // expt : 0 = combined, 1 = beam gap, 2 = interfill
  TGraph * getLifetimeCurve(double mass, double lifetime, unsigned expt);

  // get multi-graph of nominal value + upper/lower bounds
  TGraphAsymmErrors getTimeCurveWithUncertainty(double mass, double lifetime, unsigned expt);

  TMultiGraph* getTimeCurveBand(double mass, double lifetime, unsigned expt);

  // get plot of significance as fn of mass for a given lifetime/running time
  // expt : 0 = combined, 1 = beam gap, 2 = interfill
  TGraph * getMassCurve(double runtime, double lifetime, unsigned expt);

  // get 2D plot of significance as fn of mass/lifetime for a given running time
  // expt : 0 = combined, 1 = beam gap, 2 = interfill
  void get2DMassLifetimePlot(double runtime, unsigned expt, TH2D *);

private:

  // some constants
  static const unsigned nBucketsPerOrbit_;
  static const double   bunchCrossingTime_;
  static const unsigned nOrbitsPerDay_;


  int bunchStruct;    // LHC filling pattern 
  unsigned bxs_on;
  unsigned bxs_off;
  unsigned char beam[3564];

  TH1D* hBxStruct_;

  TH1D* hdecays;
  TH1D* hdecaysReg;
  TH1D* hperday;
  TH1D* hinday;

  // log file
  ofstream lfile_;

  // root file
  TFile* tfile_;
  
  // TTree
  TTree* ttree_;

  // single experiment result
  //  Experiment expt_;

  // Multiple experiment parameters
  std::vector<Experiment> experiments_;

};
