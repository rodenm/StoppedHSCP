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

  double upperLimitCountingCLS (double signal, int nObserved, double bkgMean, double bkgSigma, double scaleSigma) {
    // Cousins-Highland approach
    TRandom2 rndm;
    int nToys = 1000;
    //double nGeObserved = 0;
    double CLb = 0;
    double CLsb = 0;
    for (int iToy = 0; iToy < nToys; ++iToy) {
      double bkg = rndm.Gaus (bkgMean, bkgSigma);
      while (bkg < 0) bkg = rndm.Gaus (bkgMean, bkgSigma);
      double scale = rndm.Gaus (1., scaleSigma);
      while (scale <= 0) scale = rndm.Gaus (1., scaleSigma);
      CLb += ROOT::Math::poisson_cdf (nObserved, bkg); // poisson_cdf(x, lambda) - (15,14.2)
      CLsb += ROOT::Math::poisson_cdf (nObserved, bkg + signal * scale); // poisson_cdf(x, lambda) = (15,14.2+37.5+1)
    }
    return 1-CLsb/CLb;
  }
  
}


CLsCountingExperiment::CLsCountingExperiment (double fBackground, double fBackgroundSigma, double fScale, double fScaleSigma) 
  :  CountingExperiment (fBackground, fBackgroundSigma, fScale, fScaleSigma)
{}

CLsCountingExperiment::~CLsCountingExperiment() {}

double CLsCountingExperiment::cl95limit (int nObserved, bool fPlot) {
  //std::cout << "======================================" << std::endl;
  double targetCL = 0.95;  
  double sMin = 0;
  double sMax = nObserved > 0 ? 2.5*nObserved : 2.5;
  while (1) {
    double cls = upperLimitCountingCLS (sMax, nObserved, background(), backgroundSigma(), scaleSigma()/scale());   
    if (cls > targetCL) break;
    sMax *=2;
  }

  //std::cout << "Finished setting sMax: " << sMax << std::endl;
  vector<double>* signalIterations = fPlot ? new vector<double> : 0;
  vector<double>* cl95Iterations = fPlot ? new vector<double> : 0;
  
  double sThis = 0;
  while (1) {
    sThis = 0.5*(sMin+sMax);
    double cls = upperLimitCountingCLS (sThis, nObserved, background(), backgroundSigma(), scaleSigma()/scale());
    //std::cout << "upperLimitCountingCLS95-> min/max/sThis: " << sMin << '/' << sMax << '/' << sThis 
    //  	      << " CLS:" << cls << std::endl; 
    if ((fabs(cls - targetCL) < 1e-5) || (0.5*(sMax-sMin)/(sMax+sMin) < 1e-4)) break;
    if (cls > targetCL) sMax = sThis;
    else sMin = sThis;
    if (fPlot) {
      signalIterations->push_back(sThis*scale());
      cl95Iterations->push_back(cls);
    }
  }
  //std::cout << "Finished setting sMin & sMax: " << sMin << "    " << sMax << std::endl;

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

