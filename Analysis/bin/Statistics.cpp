
#include "RooRealVar.h"
#include "RooArgSet.h"
#include "RooUniform.h"
#include "RooAddPdf.h"
#include "RooExtendPdf.h"
#include "RooGaussian.h"
#include "RooDataSet.h"
#include "RooStats/HybridCalculator.h"
#include "RooStats/HypoTestInvertor.h"
#include "RooStats/HypoTestInvertorResult.h"

using namespace RooStats;

double CountingExperiment95CLUpperLimit (int nObserved, double bkgMean, double bkgSigma, int nToys=500) {
  // expect nothing beyond 5 sigma
  double bkgMaxExpected = bkgMean+5*bkgSigma; // 5 sigma
  double signalMaxExpected = nObserved+5*sqrt(double(nObserved))-bkgMean+5*bkgSigma;
  // variables
  RooRealVar signal ("signal", "signal", 0, 0, signalMaxExpected);
  RooRealVar bkg ("bkg", "bkg", bkgMean, 0, bkgMaxExpected);
  RooRealVar flatUnit ("flatUnit","flatUnit",0.,1.);
  // sets
  RooArgSet nuisPar (bkg);
  RooArgSet poi (signal);
  // constants
  RooRealVar bkgMeanVar ("bkgMean", "bkgMean", bkgMean);
  RooRealVar bkgSigmaVar ("bkgSigma", "bkgSigma", bkgSigma);
  // PDFs
  RooUniform signalPdf ("signalPdf","signalPdf",flatUnit);
  RooUniform backgroundPdf ("backgroundPdf","backgroundPdf",flatUnit);
  RooAddPdf modelPdf ("model","model",RooArgList(signalPdf,backgroundPdf),RooArgList(signal,bkg));
  RooExtendPdf modelBkgPdf ("modelBkg","modelBkg",backgroundPdf,bkg);
  RooGaussian priorBkgPdf ("priorBkg","priorBkg",bkg,bkgMeanVar,bkgSigmaVar);
  
  RooDataSet* data =  modelPdf.generate(flatUnit, nObserved);
  
  HybridCalculator hc(*data, modelPdf, modelBkgPdf, &nuisPar, &priorBkgPdf);
  hc.SetTestStatistic(2); // # of events
  hc.SetNumberOfToys(nToys);
  hc.UseNuisance(true);                            
  HypoTestInverter myInverter(hc,signal);
  double targetP = 0.05; // 95% C.L.
  myInverter.RunAutoScan(0, signalMaxExpected, targetP, 0.1*targetP);  
  HypoTestInverterResult* results = myInverter.GetInterval();
  results->SetConfidenceLevel (1-2.*targetP);
  double upperLimit = results->UpperLimit();
  delete data;
  // delete results;
  return upperLimit;
}

int main(int argc, char* argv[]) {

  return 0;

}
