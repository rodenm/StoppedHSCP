#ifndef BeamGasHistograms_h
#define BeamGasHistograms_h


#include "StoppedHSCP/Analysis/interface/Cuts.h"

#include "StoppedHSCP/Ntuples/interface/StoppedHSCPEvent.h"

#include "TFile.h"
#include "TH1D.h"
#include "TH2D.h"

#include <vector>

class TDirectory;

class BeamGasHistograms {

 public:

  BeamGasHistograms(TFile* file, Cuts* cuts);
  ~BeamGasHistograms();

  void book();

  void fill(StoppedHSCPEvent& event);

  void save();

  void summarise();

 private:

  Cuts* cuts_;
  TDirectory* base_;

  TH1D* hehfp_;
  TH1D* hehfm_;
  TH1D* hehf_;

  TH1D* hntrk_;

  TH1D* hbx_;

};

#endif

