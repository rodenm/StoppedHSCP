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

  FillHistograms(TFile* file, std::string name, Cuts* cuts);
  ~FillHistograms();

  void book();

  void fill(StoppedHSCPEvent& event);

  void fillCollisionsHisto(std::vector<unsigned> colls);
  void fillMaskHisto(std::vector<bool> mask);

  void save();

  void cutAxisLabels(TH1D* h);

  TH1D rateDist(TH1D&, unsigned nbins);

 private:

  Cuts* cuts_;
  TDirectory* base_;

  TH1D* hjete_;

};

#endif

