#ifndef CL95CMSCountingExperiment_h
#define CL95CMSCountingExperiment_h

#include "StoppedHSCP/Statistics/interface/CountingExperiment.h"

class CL95CMSCountingExperiment : public CountingExperiment {
 public:
  enum BackgroundModel {
    gaussian = 0,
    lognormal = 1,
    gamma = 2
  };
  CL95CMSCountingExperiment (double fBackground, double fBackgroundSigma, double fScale, double fScaleSigma, BackgroundModel fModel = gaussian);
  virtual ~CL95CMSCountingExperiment();
  virtual double cl95limit (int nObserved, bool fPlot = false);
  virtual CountingExperiment* clone(double fBackground, double fBackgroundSigma, double fScale, double fScaleSigma) const;
 private:
  BackgroundModel mBkgModel;
};

#endif
