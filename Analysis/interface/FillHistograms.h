#ifndef FillHistograms_h
#define FillHistograms_h


// a set of histograms that are filled for each Fill

#include "StoppedHSCP/Analysis/interface/Cuts.h"

#include "StoppedHSCP/Ntuples/interface/StoppedHSCPEvent.h"
#include "StoppedHSCP/Ntuples/interface/LhcFills.h"

#include "TFile.h"
#include "TH1D.h"
#include "TH2D.h"

#include <vector>

class TDirectory;

class FillHistograms {

 public:

  FillHistograms(TFile* file, Cuts* cuts, LhcFills* fills);
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

  LhcFills* lhcFills_;

  std::vector<unsigned long> fills_;

  std::vector<unsigned long> nEvts_;
  std::vector< std::pair<unsigned long, unsigned long> > lb_;
  std::vector<unsigned long> nLB_;
  std::vector< std::vector<unsigned long> > nm1_;  // nm1(cut, fill);
  std::vector<unsigned long> nFin_;

  std::vector<unsigned long> nm1Test0_;
  std::vector<unsigned long> nm1Test1_;
  std::vector<unsigned long> nm1Test2_;
  std::vector<unsigned long> nm1Test3_;
  std::vector<unsigned long> nm1Test4_;
  std::vector<unsigned long> nm1Test5_;
  std::vector<unsigned long> nm1Test6_;

  std::vector<TH1D*> hbx_;
  std::vector<TH1D*> hrelbx_;
  std::vector<TH1D*> hrelbxvtx_;
  std::vector<TH1D*> hrelbxhalo_;
  std::vector<TH1D*> hrelbxbg_;
  std::vector<TH1D*> hrelbxcos_;
  std::vector<TH1D*> hrelbxnoise_;
  std::vector<TH1D*> hrelbxnoid_;
  std::vector<TH1D*> hbxB_;
  std::vector<TH1D*> hnm1_;
  std::vector<TH1D*> hcolls_;
  std::vector<TH1D*> hbunches_;
  std::vector<TH1D*> hnormrelbx_;


};

#endif

