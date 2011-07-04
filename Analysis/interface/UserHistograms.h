#ifndef UserHistograms_h
#define UserHistograms_h


#include "StoppedHSCP/Analysis/interface/Cuts.h"

#include "StoppedHSCP/Ntuples/interface/StoppedHSCPEvent.h"

#include "TFile.h"
#include "TH1D.h"
#include "TH2D.h"

#include <vector>

class TDirectory;

class UserHistograms {

 public:

  UserHistograms(TFile* file, Cuts* cuts);
  ~UserHistograms();

  void book();

  void fill(StoppedHSCPEvent& event);

  void save();

  void summarise();


 private:

  Cuts* cuts_;
  TDirectory* base_;
  // User histograms added here
  TH1D* Nevents_;

  TH1D* OldiPhiFrac_;
  TH1D* NewiPhiFrac_;
  TH1D* iPhiFracDiff_;
  TH2D* NewVsOldiPhiFrac_;
};

#endif

