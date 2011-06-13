#ifndef HaloHistograms_h
#define HaloHistograms_h


#include "StoppedHSCP/Analysis/interface/Cuts.h"

#include "StoppedHSCP/Ntuples/interface/StoppedHSCPEvent.h"

#include "TFile.h"
#include "TH1D.h"
#include "TH2D.h"

#include <vector>

class TDirectory;

class HaloHistograms {

 public:

  HaloHistograms(TFile* file, Cuts* cuts);
  ~HaloHistograms();

  void book();

  void fill(StoppedHSCPEvent& event);

  void save();

  void summarise();

 private:

  Cuts* cuts_;
  TDirectory* base_;

  TH1D* hbx_;

};

#endif

