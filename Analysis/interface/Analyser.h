#ifndef Analyser_h
#define Analyser_h

// class to run an event loop on StoppedHSCP ntuples

#include "StoppedHSCP/Analysis/interface/StoppedHSCPEvent.h"
#include "StoppedHSCP/Analysis/interface/Cuts.h"
#include "StoppedHSCP/Analysis/interface/Histogrammer.h"
#include "StoppedHSCP/Analysis/interface/LhcFills.h"

#include "TFile.h"
#include "TTree.h"
#include "TChain.h"

#include <string>
#include <vector>
#include <fstream>

class Analyser {
 
 public:

  Analyser(std::vector<std::string> ifiles, std::string ofile, std::vector<unsigned> runs, bool isMC, bool useDigiCuts=false);
  ~Analyser();

  // get TTree from file
  void setup();

  // reset event pointer
  void reset();

  // set up for watched events
  void readWatchedEvents();

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

  // 
  bool isWatchedEvent();
  
  // loop over events
  void loop(Long64_t maxEvents_=-1);

  // calculate lifetime of an event
  double eventLifetime(unsigned run, unsigned bx);

 private:

  bool isMC_;

  std::vector<std::string> ifiles_;
  //TFile file_;
  //TTree* tree_;
  TChain* ch_;

  StoppedHSCPEvent* event_;

  Long64_t nEvents_;
  Long64_t iEvent_;

  Cuts cuts_;

  Histogrammer histogrammer_;

  LhcFills fills_;

  std::vector< std::pair< unsigned, unsigned > > watchedEvents_;
  std::ofstream eventFile_;
  std::ofstream pickFile_;
  std::ofstream dumpFile_;
  std::ofstream lifetimeFile_;


};

#endif
