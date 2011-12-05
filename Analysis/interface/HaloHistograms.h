#ifndef HaloHistograms_h
#define HaloHistograms_h

#include "StoppedHSCP/Analysis/interface/MultiHistogram1D.h"

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

  std::vector<unsigned> noHaloNoBxCuts_;
  std::vector<unsigned> noHaloNoBxNoN90Cuts_;
  std::vector<unsigned> noHaloNoBxNoJetCuts_;
  std::vector<unsigned> noHaloNoBxNoN90NoJetCuts_;

  TH1D* hbx_;
  TH1D* hjete_;
  TH1D* hjeteta_;
  TH1D* hjetphi_;
  TH2D* hjetetaphi_;
  TH1D* hjetn90_;

  // N-1 distributions
  TH1D* hnm1bx_;
  TH1D* hnm1jete_;
  TH1D* hnm1jeteta_;
  TH1D* hnm1jetphi_;
  TH2D* hnm1jetetaphi_;
  TH1D* hnm1jetn90_;  

  // BX-1 no jet cut
  TH1D* hBXm1nm1eta_;

  // BX-1 no n90
  TH1D* hBXm1nm1n90_;

  // BX-1 no jet, no n90
  TH1D* hBXm1nm2eta_;

};

#endif

