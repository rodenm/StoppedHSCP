#ifndef BasicAnalyser_h
#define BasicAnalyser_h

// class to run an event loop on StoppedHSCP ntuples
// gives access to common cut code and LHC filling scheme information

#include "StoppedHSCP/Analysis/interface/StoppedHSCPEvent.h"
#include "StoppedHSCP/Analysis/interface/Cuts.h"
#include "StoppedHSCP/Analysis/interface/LhcFills.h"

#include "TFile.h"
#include "TTree.h"

#include <string>
#include <vector>
#include <fstream>

class BasicAnalyser {
 
 public:

  BasicAnalyser(const std::string& ifile, const bool isMC);
  ~BasicAnalyser();

  // get TTree from file
  void setup();

  // reset event pointer
  void reset();

  // get number of events
  Long64_t nEvents() { return nEvents_; }

  // access current event data
  StoppedHSCPEvent* event() { return event_; }

  // get next event
  void nextEvent();

  // print event
  void printEvent();

  // print important values
  void printCutValues(ostream& o);

  // get cuts
  const Cuts& cuts() { return cuts_; }


 protected:

  bool isMC_;

  TFile file_;
  TTree* tree_;
  StoppedHSCPEvent* event_;

  Long64_t nEvents_;
  Long64_t iEvent_;

  Cuts cuts_;
  LhcFills fills_;

};

#endif
