#ifndef CountingExperiment_h
#define CountingExperiment_h

#include <vector>

class CountingExperiment {
 public:
  CountingExperiment (double fBackground, double fBackgroundSigma, double fScale, double fScaleSigma);
  virtual ~CountingExperiment ();
  double background () const {return mBackground;}
  double backgroundSigma () const {return mBackgroundSigma;}
  double scale () const {return mScale;}
  double scaleSigma () const {return mScaleSigma;}

  virtual double cl95limit (int nObserved, bool fPlot = false) = 0;
  std::vector<double>  cl95ExpectedLimit ();
  double coverage (double fTrueSignal, double fPrecision = 0.2);
  virtual CountingExperiment* clone(double fBackground, double fBackgroundSigma, double fScale, double fScaleSigma) = 0;
 private:
  double mBackground;
  double mBackgroundSigma;
  double mScale;
  double mScaleSigma;
};
#endif
