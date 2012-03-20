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

#include "StoppedHSCP/ToyMC/interface/Luminosity.h"
#include "StoppedHSCP/ToyMC/interface/Events.h"
#include "StoppedHSCP/ToyMC/interface/Experiment.h"

#include "StoppedHSCP/Ntuples/interface/LhcFills.h"


class Simulator {
 public:
  Simulator();
  ~Simulator();
  
  // set up
  void setParameters(Experiment* e);
  void setupLumi(bool buildFromDB, bool lumiCalc2, bool useHists, std::string file);
  void setFillScheme(unsigned fill);
  void setupLifetimeMask();
  void setupObservedEvents();

  // run MC simulation
  void simulateSignal(unsigned firstFill, unsigned lastFill);
  void simulateBackground(unsigned firstFill, unsigned lastFill);
  void calculateExpectedBG(unsigned firstFill, unsigned lastFill);
  void calculateObservedEvents(unsigned firstFill, unsigned lastFill);
  void calculateLimit();

  // make plots for debugging etc
  //  void makeBXMaskPlot();  // 


  // print out for debugging
  void printMaskInfo(unsigned fill);

/*   // not clear what these are for */
/*   bool collisionHasL1A(double rate); */
/*   bool isTriggerBlocked(const Experiment &e, unsigned int, unsigned int); */

/*   // plots (move elsewhere!) */
/*   void clearPlots(); */
/*   void setupPlots(); */
/*   std::map<std::string, TH1D *> run_specific_plots; */

/*   // lifetime fit (move elsewhere!) */
/*   void sendEventToLifetimeFit(unsigned int, unsigned int, unsigned int); */
/*   void writeOutLifetimeFit(); */

  LhcFills& getLhcFills() { return fills_; }

  Luminosity& getLuminosity() { return lumi_; }

  void reset() {
    effLumi_ = 0.;
    nObs_    = 0;
    nExp_    = 0.;
    nExp_e_  = 0.;
  }

  double getEffLumi() { return effLumi_; }
  unsigned getNObs() { return nObs_; }
  double getNExp() { return nExp_; }
  unsigned getNExpErr() { return nExp_e_; }

 private:

  // random numbers
  TRandom3 random_;

  // parameters
  Experiment* expt_;

  // LHC bunch structure
  LhcFills fills_;

  // luminosity delivered
  Luminosity lumi_;

  // observed events
  Events events_;

  // current fill.  stored twice for future compatibility
/*   unsigned prodFill_; */
/*   unsigned decayFill_; */

  // lifetime masking - TODO move to LhcFills class
/*   unsigned nLifetimeMasks_; */
/*   std::vector<bool> lifetimeMasks_;          // bool for each BX, true if masked for lifetime */
  
  double effLumi_;
  unsigned nObs_;
  double nExp_;
  double nExp_e_;

  // output stuff
  TTree tree_;
  int event_[3];
  long int ls_, bx_, orbit_;

};

#endif
