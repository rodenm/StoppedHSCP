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

#include "StoppedHSCP/Analysis/interface/LhcFills.h"


class Simulator {
 public:
  Simulator();
  ~Simulator();
  
  // set up
  void setParameters(Experiment* e);
  void setupLumi();
  void setFillScheme(unsigned fill);
  void setupLifetimeBxMasking();
  void setupObservedEvents();

  // run MC simulation
  void simulateSignal();
  void simulateBackground();
  void calculateExpectedBG();
  void calculateObservedEvents();
  void calculateLimit();

  // make plots for debugging etc
  //  void makeBXMaskPlot();  // 


  // print out for debugging
  void printMaskInfo();

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

  // 
  unsigned fill_;    // fill used for filling scheme
  unsigned nColls_, nMasks_, nLifetimeMasks_;
  std::vector<bool> collisions_;            // bool for each BX, true if collision
  std::vector<bool> masks_;                  // bool for each BX, true if masked (BX +/-1)
  std::vector<bool> lifetimeMasks_;          // bool for each BX, true if masked for lifetime
  
  // output stuff
  TTree tree_;
  int event_[3];
  long int ls_, bx_, orbit_;

};

#endif
