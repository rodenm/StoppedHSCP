#ifndef Histogrammer_h
#define Histogrammer_h

#include "StoppedHSCP/Analysis/interface/Histograms.h"

#include "TFile.h"


#include <map>

class Cuts;
class LhcFills;

class Histogrammer {
 public:

  Histogrammer(std::string filename, std::vector<unsigned> runs, Cuts* cuts);
  ~Histogrammer();
  
  // fill histograms
  void fill(StoppedHSCPEvent& event);

  // fill non-event histograms
  void fillCollisionsHistos(unsigned run, LhcFills* fills);

  // save them
  void save();


 private:

  TFile file_;

  Histograms hists_;

  std::vector<unsigned> runs_;
  std::vector<Histograms> runHists_;

};

#endif
