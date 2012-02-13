#ifndef BasicAnalyser_h
#define BasicAnalyser_h

// class to run an event loop on StoppedHSCP ntuples

#include "StoppedHSCP/Analysis/interface/Cuts.h"
#include "StoppedHSCP/Analysis/interface/Livetime.h"
#include "StoppedHSCP/Ntuples/interface/StoppedHSCPEvent.h"
#include "StoppedHSCP/Ntuples/interface/LhcFills.h"

#include "TFile.h"
//#include "TTree.h"
#include "TChain.h"

#include <string>
#include <vector>
#include <fstream>

class BasicAnalyser {
 
 public:

  BasicAnalyser(int argc, char* argv[]);

  ~BasicAnalyser();

  // get TTree from file
  void setup();

  // reset event pointer
  void reset();

  // get number of events
  unsigned long nEvents() { return nEvents_; }

  // access current event data
  StoppedHSCPEvent* event() { return event_; }

  // get next event
  void nextEvent();

  // print event
  void printEvent();

  // print cut values
  void printCutValues(ostream& o);

  // get cuts
  const Cuts& cuts() { return cuts_; }

  // loop over events
  virtual void loop();

 protected:

  // are we running on MC or not?
  bool isMC_;

  // input files, chains etc
  std::vector<std::string> ifiles_;
  TChain* chain_;

  unsigned long nEvents_;
  unsigned long maxEvents_;
  unsigned long iEvent_;

  // output file
  std::string outdir_;
  std::string ofilename_;
  TFile* ofile_;

  // the event
  StoppedHSCPEvent* event_;

  // the cuts
  Cuts cuts_;

  // the fill structure (temporarily useful)
  LhcFills lhcFills_;

  // livetime calculator
  Livetime livetime_;

};

#endif
