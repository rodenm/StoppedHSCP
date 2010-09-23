#include "StoppedHSCP/Statistics/interface/CL95CMSCountingExperiment.h"
#include "cl95cms.icc"

CL95CMSCountingExperiment::CL95CMSCountingExperiment (double fBackground, double fBackgroundSigma, double fScale, double fScaleSigma, BackgroundModel fModel) 
  : CountingExperiment (fBackground, fBackgroundSigma, fScale, fScaleSigma),
    mBkgModel (fModel)
{
}

CL95CMSCountingExperiment::~CL95CMSCountingExperiment() {
}

double CL95CMSCountingExperiment::cl95limit (int nObserved, bool fPlot) {
  plot = fPlot ? kTRUE : kFALSE;
  return CL95 (1., 0., scale(), scaleSigma(), background(), backgroundSigma(), nObserved, int(mBkgModel));
}

CountingExperiment* CL95CMSCountingExperiment::clone(double fBackground, double fBackgroundSigma, double fScale, double fScaleSigma) const {
  return new CL95CMSCountingExperiment (fBackground, fBackgroundSigma, fScale, fScaleSigma, mBkgModel);
}

