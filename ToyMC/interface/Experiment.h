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
  unsigned nTrialsSignal;        // usually 100
  unsigned nTrialsBackground;    // usually 100
  bool simulateExpt;
  std::string fillScheme;
  double beamOnTime;
  double beamOffTime;
  double instLumi;
  double runningTime;

  //outputs from Simulator.cc
  double livetime;                // trigger livetime in seconds
  double effLumi;                 // lumi with live trigger
  double effLumi_e;
  double expSignal;               // calculated with signal toy MC: nObs/nDecays*efficiency, usually 0
  double expSignal_e;
  double expBackground;           // expected background scaled by lifetime hyposthesis
  double expBackground_e;
  unsigned nObserved;             // analysis count (15 for 2012) scaled by lifetime hypothesis
  
  // Toy results
  unsigned nDecays_MC;
  unsigned nObs_MC;
  unsigned nSig_MC;
  unsigned nBG_MC;
  
  // limits from CLsCountingExperiment, calculated in Simulator::calculateLimits()
  double limit95cl;               // observed limit - with 95% prob we could have seen this # of events
  double expLimit;                // expected limit - with 95% prob we expected to see this # of events
  double expLim1SigLo;
  double expLim1SigHi;
  double expLim2SigLo;
  double expLim2SigHi;

  ClassDef(Experiment,2);

};

std::ostream &operator<<(std::ostream &o, const Experiment &e);


#endif // EXPERIMENT_H
