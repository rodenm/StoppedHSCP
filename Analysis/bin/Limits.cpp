
#include "RooRealVar.h"
#include "RooArgSet.h"
#include "RooUniform.h"
#include "RooAddPdf.h"
#include "RooExtendPdf.h"
#include "RooGaussian.h"
#include "RooDataSet.h"
#include "RooStats/HybridCalculator.h"
#include "RooStats/HypoTestInverter.h"
#include "RooStats/HypoTestInverterResult.h"

#include "TFile.h"
#include "TH1D.h"

#include <cmath>

using namespace RooStats;

double countingExperiment95CLUpperLimit (int nObserved, double bkgMean, double bkgSigma, int nToys=500) {
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

void usage() {
    std::cout << "Usage : statistics <dataset>" << std::endl;
}


// 
int main(int argc, char* argv[]) {

  if (argc < 2) {
    std::cout << "Insufficient arguments" << std::endl;
    usage();
    exit(1);
  }

  // options
  for (int i=1; i<argc; ++i) {
    // check option flags
    std::string opt = argv[i];
    if (opt=="-h") {
      usage();
      exit(0);
    }
  }

  // arguments
  std::string dataset = std::string(argv[argc-1]);
  std::cout << "Calculating statistics for " << dataset << std::endl;

  // search dataset files
  std::string hfilename(dataset);
  hfilename += std::string("/selectedRuns.root");
  TFile hfile(hfilename.c_str());

  std::string rfilename(dataset);
  rfilename += std::string("/");
  rfilename += std::string(dataset);
  rfilename += std::string("_byRun.root");
  TFile rfile(rfilename.c_str());

  // get search dataset numbers
  TH1D* hncutcum = (TH1D*) hfile.Get("Cuts/hncutcum");
  int nObserved=hncutcum->GetBinContent(12);

  TH1D* hlivetime = (TH1D*) rfile.Get("hlivetime");
  double livetime=hlivetime->Integral();

  // get background numbers
  // TODO - open BG files and get these numbers
  int bgCounts = 20;
  double bgLivetime = 174687.0;
  double bgRate = ((double) bgCounts) / bgLivetime;
  double bgRateStatErr = sqrt( (double) bgCounts) / bgLivetime;

  // expected background
  double bgMean = (bgRate * livetime);
  double bgSigma=1.;

  // other params
  int nToys=500;

  // 95% CL
  double cl95 = countingExperiment95CLUpperLimit (nObserved, bgMean, bgSigma, nToys);

  // print results
  std::cout << std::endl;
  std::cout << "Background dataset" << std::endl;
  std::cout << "Livetime         : " << bgLivetime << std::endl;
  std::cout << "Counts           : " << bgCounts << std::endl;
  std::cout << "Rate             : " << bgRate << " +/- " << bgRateStatErr << std::endl;
  std::cout << std::endl;
  std::cout << "Search dataset" << std::endl;
  std::cout << "Live time        : " << livetime << std::endl;
  std::cout << "N exp BG         : " << bgMean << " +/- " << bgSigma << std::endl;
  std::cout << "N observed       : " << nObserved << std::endl;
  std::cout << std::endl;
  std::cout << "Results" << std::endl;
  std::cout << "95 CL limit      : " << cl95 << std::endl;

  return 0;

}
