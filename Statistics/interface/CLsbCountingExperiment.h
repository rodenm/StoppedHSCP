#ifndef CLsbCountingExperiment_h
#define CLsbCountingExperiment_h

#include "StoppedHSCP/Statistics/interface/CountingExperiment.h"

class CLsbCountingExperiment : public CountingExperiment {
 public:
  CLsbCountingExperiment (double fBackground, double fBackgroundSigma, double fScale, double fScaleSigma);
  virtual ~CLsbCountingExperiment();
  virtual double cl95limit (int nObserved, bool fPlot = false);
  virtual CountingExperiment* clone(double fBackground, double fBackgroundSigma, double fScale, double fScaleSigma) const;
 private:
};

#endif
