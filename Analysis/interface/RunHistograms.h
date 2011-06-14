#ifndef RunHistograms_h
#define RunHistograms_h


// a set of histograms that are filled for each Run

#include "StoppedHSCP/Analysis/interface/Cuts.h"

#include "StoppedHSCP/Ntuples/interface/StoppedHSCPEvent.h"
#include "StoppedHSCP/Ntuples/interface/LhcFills.h"

#include "TFile.h"
#include "TH1D.h"
#include "TH2D.h"

#include <vector>

class TDirectory;

class RunHistograms {

 public:

  RunHistograms(TFile* file, Cuts* cuts, LhcFills* fills);
  ~RunHistograms();

  // book the per-run histograms
  void book(unsigned long run);

  // fill them
  void fill(StoppedHSCPEvent& event);

  // save them
  void save();

  // summarise
  void summarise();

 private:

  Cuts* cuts_;
  LhcFills* fills_;

  TDirectory* base_;

  std::vector<unsigned long> runs_;

  std::vector<unsigned long> nEvts_;

  std::vector<TH1D*> hlb_;

};

#endif

