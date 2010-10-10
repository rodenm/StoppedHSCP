#ifndef EXPERIMENT_H
#define EXPERIMENT_H

#include "TObject.h"

#include <iostream>

class Experiment : public TObject
{
public:

  Experiment(std::string file="");
  ~Experiment();

  void summary (ostream& o);

  // particle parameters
  double mass;
  double crossSection;
  double lifetime;

  // analysis parameters
  double signalEff;
  double signalEff_e;
  double bgRate;
  double bgRate_e;
  double scaleUncert;
  bool optimizeTimeCut;

  // experiment parameters
  std::string histFile;
  std::string lumiFile;
  unsigned lumiFirstRun;
  unsigned lumiLastRun;
  std::string jsonFile;
  std::vector<unsigned long> fills;
  std::string eventsFile;

  // Toy parameters
  unsigned nTrialsSignal;
  unsigned nTrialsBackground;
  bool simulateExpt;
  std::string fillScheme;
  double beamOnTime;
  double beamOffTime;
  double instLumi;
  double runningTime;

  //outputs
  double livetime;
  double effLumi;
  double effLumi_e;
  double expSignal;
  double expSignal_e;
  double expBackground;
  double expBackground_e;
  unsigned nObserved;
  
  // Toy results
  unsigned nDecays_MC;
  unsigned nObs_MC;
  unsigned nSig_MC;
  unsigned nBG_MC;
  
  // limits
  double limit95cl;
  double expLimit;
  double expLim1SigLo;
  double expLim1SigHi;
  double expLim2SigLo;
  double expLim2SigHi;

  ClassDef(Experiment,2);

};

std::ostream &operator<<(std::ostream &o, const Experiment &e);


#endif // EXPERIMENT_H
