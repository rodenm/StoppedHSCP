#ifndef Analyser_h
#define Analyser_h

// class to run an event loop on StoppedHSCP ntuples

#include "StoppedHSCP/Analysis/interface/StoppedHSCPEvent.h"
#include "StoppedHSCP/Analysis/interface/Cuts.h"
#include "StoppedHSCP/Analysis/interface/Histogrammer.h"

#include "TFile.h"
#include "TTree.h"

#include <string>
#include <vector>
#include <fstream>

class Analyser {
 
 public:

  Analyser(std::string ifile, std::string ofile, std::vector<unsigned> runs, bool isMC);
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
  void loop();

 private:

  bool isMC_;

  TFile file_;
  TTree* tree_;
  StoppedHSCPEvent* event_;

  Long64_t nEvents_;
  Long64_t iEvent_;

  Cuts cuts_;

  Histogrammer histogrammer_;

  std::vector< std::pair< unsigned, unsigned > > watchedEvents_;
  std::ofstream eventFile_;
  std::ofstream dumpFile_;


};

#endif
