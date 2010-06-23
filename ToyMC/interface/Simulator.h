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
  
  void setupLumi();
  void run(Experiment &);

  std::map<std::string, TH1D *> run_specific_plots;

  void writeOutLifetimeFit();

 protected:
  void clearPlots();
  void setupPlots();
  
  void setupBxStructure(unsigned int);
  void setupLifetimeBxMasking(double);

  void simulateSignal(Experiment &);
  void simulateBackground(Experiment &);

  void sendEventToLifetimeFit(unsigned int, unsigned int, unsigned int);

  bool collisionHasL1A(double rate);
  bool isTriggerBlocked(const Experiment &e, unsigned int, unsigned int);

  double countingExperiment95CLUpperLimitHybrid(int nObserved, double bkgMean, double bkgSigma, int nToys);

  unsigned int bx_struct;
  unsigned int bxs_on, bxs_off;
  bool beam[NBXS_PER_ORBIT];
  std::vector<bool> parasitic;//bad bunches to look inside
  std::vector<bool> lifetimeMask; //bunches too far from collision
  std::vector<unsigned int> on_bxs;

  Luminosity_Model lumis_by_section;
  //std::vector<double> lumis_by_section;

  TFile lifetimeFitOutput;
  TTree t;

  int event[3];
  int _ls, _bx, _orbit;

  TRandom3 rndm;
};

#endif
