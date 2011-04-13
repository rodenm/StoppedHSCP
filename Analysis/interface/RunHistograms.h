#ifndef RunHistograms_h
#define RunHistograms_h


// a set of histograms that are filled for each Run

#include "StoppedHSCP/Analysis/interface/StoppedHSCPEvent.h"
#include "StoppedHSCP/Analysis/interface/Cuts.h"

#include "TFile.h"
#include "TH1D.h"
#include "TH2D.h"

#include <vector>

class TDirectory;

class RunHistograms {

 public:

  RunHistograms(TFile* file, Cuts* cuts);
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
  TDirectory* base_;

  std::vector<unsigned long> runs_;

  std::vector<TH1D*> hbx_;
  std::vector<TH1D*> horb_;
  std::vector<TH1D*> hlb_;

};

#endif

