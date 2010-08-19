
#ifndef LuminosityModel_h
#define LuminosityModel_h

#include <vector>
#include "TCanvas.h"

struct lumi_info {
  unsigned long run, ls;
  double lumi, cms_sensitivity;
};

class LuminosityModel {

 public:
  LuminosityModel();
  double operator[](unsigned int) const;
  unsigned int size() const;
  
  // build model from file, for a list of runs
  void build_from_file(std::vector<unsigned long> runs);

  // generate model from parameters
  void build_from_cycle(unsigned int, unsigned int, unsigned int, double);

  TCanvas *draw() const;

  std::vector<struct lumi_info> lumis;

};

#endif
