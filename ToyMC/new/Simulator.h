#ifndef SIMULATOR_H
#define SIMULATOR_H

#include <iostream>
#include <map>
#include <string>
#include <vector>
#include "TH1D.h"
#include "TRandom3.h"
#include "Experiment.h"

class Simulator {
 public:
  Simulator();
  ~Simulator() { clearPlots(); }
  
  void setupLumi(std::istream &);
  void run(Experiment &);

  std::map<std::string, TH1D *> run_specific_plots;

 protected:
  void clearPlots();
  void setupPlots();
  
  void setupBxStructure(unsigned int);

  void simulateSignal(Experiment &);
  void simulateBackground(Experiment &);

  static const unsigned int NBXS_PER_ORBIT = 3564;
  static const double TIME_PER_BUNCH = 25e-9;
  static const double TIME_PER_ORBIT = 
    8.91e-5;
    //NBXS_PER_ORBIT * TIME_PER_BUNCH;
  static const unsigned int NORBITS_PER_LS = 1048576; //2^20
  static const double TIME_PER_LS =
    8.91e-5 * 1048576;
    //TIME_PER_ORBIT * NORBITS_PER_LS;

  unsigned int bx_struct;
  unsigned int bxs_on, bxs_off;
  bool beam[NBXS_PER_ORBIT];
  std::vector<unsigned int> on_bxs;

  std::vector<double> lumis_by_section;

  TRandom3 rndm;
};

#endif
