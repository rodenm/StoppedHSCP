#include "StoppedHSCP/Statistics/interface/CLsCountingExperiment.h"

#include <math.h>

#include <iostream>
#include <vector>

#include "Math/ProbFuncMathCore.h"
#include "Math/PdfFuncMathCore.h"
#include "Math/QuantFuncMathCore.h"
#include "Math/SpecFuncMathCore.h"
#include "TRandom2.h"
#include "TCanvas.h"
#include "TGraph.h"
#include "TAxis.h"
#include "TArrow.h"

using namespace std;

namespace {
int limitedPoisson (double mu, int nMax, TRandom* rndm) {
  const int maxSize = 1000;
  if (double(nMax) > mu || nMax > maxSize-1) {
    int result = nMax+1;
    while ((result = rndm->Poisson (mu)) > nMax) {}
    return result;
  }
  double pdfC [maxSize];
  double p = exp(-mu);
  pdfC [0] = exp(-mu);
  for (int i = 1; i <= nMax; ++i) {
    p *= mu/i;
    pdfC [i] = pdfC [i-1] + p;
  }
  double pick = rndm->Uniform (pdfC [nMax]);
  for (int i = 0; i <= nMax; ++i) {
    if (pick < pdfC [i]) return i;
  }
  std::cerr << "limitedPoisson-> we should never get here" << std::endl;
  return 0;
}

double upperLimitCountingCLS (double signal, int nObserved, double bkgMean, double bkgSigma, double scaleSigma) {
  // Cousins-Highland approach
  TRandom2 rndm;
  int nToys = 1000;
  double nGeObserved = 0;
  for (int iToy = 0; iToy < nToys; ++iToy) {
    double bkg = rndm.Gaus (bkgMean, bkgSigma);
    while (bkg < 0) bkg = rndm.Gaus (bkgMean, bkgSigma);
    int nBkg = limitedPoisson (bkg, nObserved, &rndm);
    double scale = rndm.Gaus (1., scaleSigma);
    while (scale <= 0) scale = rndm.Gaus (1., scaleSigma);
    nGeObserved += ROOT::Math::poisson_cdf_c (nObserved-nBkg, signal * scale);
  }
//   std::cout << "upperLimitCountingCLS-> " 
// 	    << signal << '/' << nObserved << '/' << bkgMean << '/' << bkgSigma << '/' << scaleSigma 
// 	    << " nlo/ntoy/cls: " << nGeObserved << '/' << nToys << '/' << double (nGeObserved) / nToys << std::endl;
  return double (nGeObserved) / nToys;
}

}


CLsCountingExperiment::CLsCountingExperiment (double fBackground, double fBackgroundSigma, double fScale, double fScaleSigma) 
  :  CountingExperiment (fBackground, fBackgroundSigma, fScale, fScaleSigma)
{}

CLsCountingExperiment::~CLsCountingExperiment() {}

double CLsCountingExperiment::cl95limit (int nObserved, bool fPlot) {
  double targetCL = 0.95;  
  double sMin = 0;
  double sMax = nObserved > 0 ? 2.5*nObserved : 2.5;
  while (1) {
    double cls = upperLimitCountingCLS (sMax, nObserved, background(), backgroundSigma(), scaleSigma()/scale());
    if (cls > targetCL) break;
    sMax *=2;
  }
  vector<double>* signalIterations = fPlot ? new vector<double> : 0;
  vector<double>* cl95Iterations = fPlot ? new vector<double> : 0;
  
  double sThis = 0;
  while (1) {
    sThis = 0.5*(sMin+sMax);
    double cls = upperLimitCountingCLS (sThis, nObserved, background(), backgroundSigma(), scaleSigma()/scale());
    //      std::cout << "upperLimitCountingCLS95-> min/max/sThis: " << sMin << '/' << sMax << '/' << sThis 
    //  	      << " CLS:" << cls << std::endl; 
    if ((fabs(cls - targetCL) < 1e-5) || (0.5*(sMax-sMin)/(sMax+sMin) < 1e-4)) break;
    if (cls > targetCL) sMax = sThis;
    else sMin = sThis;
    if (fPlot) {
      signalIterations->push_back(sThis*scale());
      cl95Iterations->push_back(cls);
    }
  }
  if (fPlot) { // draw graph
    const int maxIterations = 20;
    double iSignal [maxIterations];
    double iCL [maxIterations];
    int nPoints = 0;
    int nIterations = signalIterations->size();
    for (; nPoints < maxIterations; ++nPoints) {
      if (nPoints >= nIterations) break;
      iSignal[nPoints] =  (*signalIterations) [nIterations-nPoints-1];
      iCL[nPoints] = 1. - (*cl95Iterations) [nIterations-nPoints-1];
    }
    TCanvas c("CLs iterations");
    cout << nPoints << '/' << iSignal[0] << '/' << iCL[0] << endl;
    TGraph graph (nPoints, iSignal, iCL);
    graph.GetXaxis()->SetTitle("signal");
    graph.GetYaxis()->SetTitle("1-95%CLs limit");
    graph.SetMarkerStyle(5);;
    graph.Draw("alp");
    TArrow arrow(iSignal[0],0.05,iSignal[0],graph.GetYaxis()->GetXmin(),0.02);
    arrow.SetLineColor(kRed);
    arrow.SetLineWidth(3);
    arrow.Draw();
    c.Print ("CLs_Counting_experiment.eps");
  }
  return sThis*scale();
}

CountingExperiment* CLsCountingExperiment::clone(double fBackground, double fBackgroundSigma, double fScale, double fScaleSigma) const {
  return new CLsCountingExperiment (fBackground, fBackgroundSigma, fScale, fScaleSigma);
}

