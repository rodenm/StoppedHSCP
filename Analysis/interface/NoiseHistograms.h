#ifndef NoiseHistograms_h
#define NoiseHistograms_h


#include "StoppedHSCP/Analysis/interface/Cuts.h"

#include "StoppedHSCP/Ntuples/interface/StoppedHSCPEvent.h"

#include "TFile.h"
#include "TH1D.h"
#include "TH2D.h"

#include <vector>

class TDirectory;

class NoiseHistograms {

 public:

  NoiseHistograms(TFile* file, Cuts* cuts);
  ~NoiseHistograms();

  void book();

  void fill(StoppedHSCPEvent& event);

  void save();

  void summarise();

 private:

  Cuts* cuts_;
  TDirectory* base_;

  std::vector<unsigned> nm1cuts_;

  TH1D* hbx_;
  TH1D* hjete_;
  TH1D* hjeteta_;
  TH1D* hjetphi_;
  TH2D* hjetetaphi_;

  TH1D* hnm1bx_;
  TH1D* hnm1jete_;
  TH1D* hnm1jeteta_;
  TH1D* hnm1jetphi_;
  TH2D* hnm1jetetaphi_;

};

#endif

