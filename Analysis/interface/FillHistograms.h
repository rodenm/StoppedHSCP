#ifndef FillHistograms_h
#define FillHistograms_h


// a set of histograms that are filled for each Fill

#include "StoppedHSCP/Analysis/interface/StoppedHSCPEvent.h"
#include "StoppedHSCP/Analysis/interface/Cuts.h"

#include "TFile.h"
#include "TH1D.h"
#include "TH2D.h"

#include <vector>

class TDirectory;

class FillHistograms {

 public:

  FillHistograms(TFile* file, Cuts* cuts);
  ~FillHistograms();

  void book(unsigned long fill);

  void fill(StoppedHSCPEvent& event);

  void fillCollisionsHisto(std::vector<unsigned> colls);
  void fillMaskHisto(std::vector<bool> mask);

  void save();

  void summarise();

 private:

  Cuts* cuts_;
  TDirectory* base_;

  std::vector<unsigned long> fills_;

  std::vector<TH1D*> hbx_;
  std::vector<TH1D*> horb_;
  std::vector<TH1D*> hlb_;

  TH1D* hjete_;

};

#endif

