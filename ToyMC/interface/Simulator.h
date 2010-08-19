#ifndef SIMULATOR_H
#define SIMULATOR_H

#include <iostream>
#include <map>
#include <string>
#include <vector>
#include "TH1D.h"
#include "TRandom3.h"
#include "TTree.h"
#include "TFile.h"
#include "StoppedHSCP/ToyMC/interface/Experiment.h"
#include "StoppedHSCP/ToyMC/interface/Luminosity.h"

#include "StoppedHSCP/Analysis/interface/LhcFills.h"

static const unsigned int NBXS_PER_ORBIT = 3564;
static const double TIME_PER_BUNCH = 25e-9;
static const double TIME_PER_ORBIT = 
  8.91e-5;
//NBXS_PER_ORBIT * TIME_PER_BUNCH;
//static const unsigned int NORBITS_PER_LS = 1048576; //2^20
static const unsigned int NORBITS_PER_LS = 262144; //2^18
static const double TIME_PER_LS =
  8.91e-5 * 262144;
//    8.91e-5 * 1048576;
//TIME_PER_ORBIT * NORBITS_PER_LS;


class Simulator {
 public:
  Simulator();
  ~Simulator() { clearPlots(); }
  
  void setupLumi(std::vector<unsigned long> fillsToSimulate);
  void run(Experiment &);

  std::map<std::string, TH1D *> run_specific_plots;

  void writeOutLifetimeFit();

  void clearPlots();
  void setupPlots();
  
  void setupBxStructure(unsigned int);
  void setFillScheme(unsigned fill);
  void setupLifetimeBxMasking(double);

  void simulateSignal(Experiment &);
  void simulateBackground(Experiment &);

  void sendEventToLifetimeFit(unsigned int, unsigned int, unsigned int);

  bool collisionHasL1A(double rate);
  bool isTriggerBlocked(const Experiment &e, unsigned int, unsigned int);

  //  double countingExpt95CLUpperLimitHybrid(int nObserved, double bkgMean, double bkgSigma, int nToys);
 private:

  // random numbers
  TRandom3 random_;

  // LHC bunch structure
  LhcFills fills_;

  // luminosity delivered
  Luminosity lumi_;

  // local info used for bunch structure
  unsigned int beamStructure_;  // number of filled BXs?
  unsigned int nBxOn_;          // think this is just a cross-check
  unsigned int nBxOff_;         // think this is just a cross-check
  bool beam_[NBXS_PER_ORBIT];   // whether each bucket in the orbit is filled or not
  std::vector<bool> maskedBXs_;    // bad bunches to look inside
  std::vector<bool> lifetimeMask_; // bunches too far from collision
  std::vector<unsigned int> collisions_;  // BXs of collisions

  // output stuff
  TFile lifetimeFitOutput_;
  TTree tree_;

  int event_[3];
  long int ls_, bx_, orbit_;

};

#endif
