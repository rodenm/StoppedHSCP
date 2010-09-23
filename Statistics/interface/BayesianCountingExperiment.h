#ifndef BayesianCountingExperiment_h
#define BayesianCountingExperiment_h

#include "StoppedHSCP/Statistics/interface/CountingExperiment.h"

#include <vector>

namespace RooStats {
  class BayesianCalculator;
}
class TObject;
class RooDataSet;

class BayesianCountingExperiment : public CountingExperiment {
 public:
  BayesianCountingExperiment (double fBackground, double fBackgroundSigma, double fScale, double fScaleSigma);
  virtual ~BayesianCountingExperiment();
  virtual double cl95limit (int nObserved, bool fPlot = false);
  virtual CountingExperiment* clone(double fBackground, double fBackgroundSigma, double fScale, double fScaleSigma) const;
  void print ();
 private:
  RooStats::BayesianCalculator* mCalculator;
  RooDataSet* mDataset;
  std::vector<TObject*> mOwnObjects;
};

#endif
