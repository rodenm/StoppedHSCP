#ifndef Analyser_h
#define Analyser_h

// class to run an event loop on StoppedHSCP ntuples

#include "StoppedHSCP/Analysis/interface/Cuts.h"
#include "StoppedHSCP/Analysis/interface/Histograms.h"
#include "StoppedHSCP/Analysis/interface/ControlHistograms.h"
#include "StoppedHSCP/Analysis/interface/RunHistograms.h"
#include "StoppedHSCP/Analysis/interface/RunReducedHistograms.h"
#include "StoppedHSCP/Analysis/interface/FillHistograms.h"
#include "StoppedHSCP/Analysis/interface/HaloHistograms.h"
#include "StoppedHSCP/Analysis/interface/BeamGasHistograms.h"
#include "StoppedHSCP/Analysis/interface/CollisionsHistograms.h"
#include "StoppedHSCP/Analysis/interface/CosmicsHistograms.h"
#include "StoppedHSCP/Analysis/interface/NoiseHistograms.h"
#include "StoppedHSCP/Analysis/interface/SignalHistograms.h"

#include "StoppedHSCP/Ntuples/interface/StoppedHSCPEvent.h"
#include "StoppedHSCP/Ntuples/interface/LhcFills.h"

#include "TFile.h"
//#include "TTree.h"
#include "TChain.h"

#include <string>
#include <vector>
#include <fstream>

class Analyser {
 
 public:

  Analyser(std::vector<std::string> ifiles, 
	   std::string ofile, 
	   bool isMC,
	   unsigned cutVersion,
	   bool doControl,
	   bool doSearch);

  ~Analyser();

  // get TTree from file
  void setup();

  // reset event pointer
  void reset();

  // set up for watched events
  void readWatchedEvents();

  // get number of events
  unsigned long nEvents() { return nEvents_; }

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
  void loop(ULong64_t maxEvents_=0);

  // calculate lifetime of an event
  //  double eventLifetime(unsigned run, unsigned bx);

 private:

  bool isMC_;
  bool doControl_;
  bool doSearch_;

  // input files, chains etc
  std::vector<std::string> ifiles_;
  TChain* chain_;

  unsigned long nEvents_;
  unsigned long iEvent_;

  // output file
  TFile ofile_;

  // the event
  StoppedHSCPEvent* event_;

  // the cuts
  Cuts cuts_;

  // general histograms
  Histograms histograms_;
  ControlHistograms controlHistos_;
  HaloHistograms haloHistos_;
  BeamGasHistograms beamGasHistos_;
  CollisionsHistograms collisionsHistos_;
  CosmicsHistograms cosmicsHistos_;
  NoiseHistograms noiseHistos_;
  SignalHistograms signalHistos_;
  
  // "per-run" histograms
  RunHistograms runHistos_;
  
  // "per-run" summary histograms used to correctly normalized "reduced" ntuples
  RunReducedHistograms* runReducedHistos_;

  // "per-fill" histograms
  FillHistograms fillHistos_;

  /// LHC fills (for run/fill mapping)
  LhcFills fills_;

  // list of events we watching for
  std::vector< std::pair< unsigned long, unsigned long> > watchedEvents_;

  // log files
  std::ofstream eventFile_;
  std::ofstream pickFile_;
  std::ofstream dumpFile_;
  std::ofstream lifetimeFile_;

  TFile *outfile_;
  std::string outfilename_;
};

#endif
