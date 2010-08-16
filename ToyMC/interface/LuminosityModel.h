
#ifndef LuminosityModel_h
#define LuminosityModel_h

#include <vector>
#include "TCanvas.h"

struct lumi_info {
  unsigned int run, ls;
  double lumi, cms_sensitivity;
};

class LuminosityModel {

 public:
  LuminosityModel();
  double operator[](unsigned int) const;
  unsigned int size() const;
  
  void build_from_file(const char *);
  void build_from_cycle(unsigned int, unsigned int, unsigned int, double);

  TCanvas *draw() const;

  std::vector<struct lumi_info> lumis;

};

#endif
