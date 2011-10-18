#ifndef RunReducedHistograms_h
#define RunReducedHistograms_h


// a set of histograms that are filled for each Run

#include "StoppedHSCP/Analysis/interface/Cuts.h"

#include "StoppedHSCP/Ntuples/interface/StoppedHSCPEvent.h"
#include "StoppedHSCP/Ntuples/interface/LhcFills.h"

#include "TFile.h"
#include "TH1D.h"
#include "TH2D.h"

#include <vector>
#include <TKey.h>

#include "StoppedHSCP/Ntuples/interface/Constants.h"

#include "TMath.h"

#include <sstream>
#include <iostream>
#include <map>

class TDirectory;

class RunReducedHistograms {

 public:

  RunReducedHistograms(TFile* outputfile, 
		       std::vector<std::string> ifiles,  
		       LhcFills* fills);
  ~RunReducedHistograms();


  // shouldn't be necessary
  void save();

  // summarise
  void summarise();

 private:

  LhcFills *fills_;
  TDirectory* base_;
  
  TH1D* hEventsPerRun_;
  TH1D* hLSPerRun_;
  TH1D* hLiveTimePerRun_;

};

#endif

