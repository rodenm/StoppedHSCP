#include "StoppedHSCP/Statistics/interface/BayesianCountingExperiment.h"

#include "RVersion.h"
#if ROOT_VERSION_CODE >= ROOT_VERSION(5,27,0)

#include "RooRealVar.h"
#include "RooProduct.h"
#include "RooAddition.h"
#include "RooDataSet.h"
#include "RooUniform.h"
#include "RooGaussian.h"
#include "RooPoisson.h"
#include "RooAddPdf.h"
#include "RooProdPdf.h"
#include "RooPlot.h"
#include "RooMsgService.h"

#include "RooStats/BayesianCalculator.h"
#include "RooStats/SimpleInterval.h"
#include "TCanvas.h"

#include "Math/ProbFuncMathCore.h"
#include "Math/PdfFuncMathCore.h"
#include "Math/QuantFuncMathCore.h"


using namespace std;
using namespace RooFit;
using namespace RooStats;

namespace {
  double poissonUpperLimit (int nObserved, double precision) {
    double min = 0;
    double max = nObserved > 0 ?  nObserved : 1.;
    while (ROOT::Math::poisson_cdf (nObserved, max) >  precision) {
      min = max;
      max *= 2;
    }
    while (1) {
      double mid = 0.5 * (min + max);
      double prob = ROOT::Math::poisson_cdf (nObserved, mid);
      if (fabs(prob/precision - 1.) < 1.e-2) return mid;
      if (prob > precision) min = mid;
      else max = mid;
    }
  }
}

BayesianCountingExperiment::BayesianCountingExperiment (double fBackground, double fBackgroundSigma, double fScale, double fScaleSigma) 
  :  CountingExperiment (fBackground, fBackgroundSigma, fScale, fScaleSigma),
  mCalculator (0),
  mDataset (0)
{
 // normalize scale
  double expectedScaleSigma = scaleSigma() / scale();
  // resolve zero uncertainties
  if (expectedScaleSigma <= 0) expectedScaleSigma = 1.e-5;
  double expectedBkgSigma  = backgroundSigma();
  if (expectedBkgSigma <= 0) expectedBkgSigma = 1.e-5;
  // get limits
  const double rangePrecision = 1.e-5;
  double minBkg = background () + ROOT::Math::normal_quantile (rangePrecision, expectedBkgSigma);
  if (minBkg <= 0) minBkg = 0;
  double maxBkg =  background () + ROOT::Math::normal_quantile_c (rangePrecision, expectedBkgSigma);
  double minScale = 1. + ROOT::Math::normal_quantile (rangePrecision, expectedScaleSigma);
  if (minScale <= 0) minScale = 1e-2;
  double maxScale = 1. + ROOT::Math::normal_quantile_c (rangePrecision, expectedScaleSigma);
  double maxRange = poissonUpperLimit (int (floor(background ()))+1, rangePrecision);
  double maxRangeTarget = poissonUpperLimit (int (floor(maxRange))+1, rangePrecision);
  double maxRangeEvents = maxRangeTarget;
  // variables
  RooRealVar* target = new RooRealVar("target", "target", 0, 0, maxRangeTarget); 
  mOwnObjects.push_back(target);
  RooRealVar* scaleVar = new RooRealVar("scaleVar", "scaleVar", 1., minScale, maxScale);
  mOwnObjects.push_back(scaleVar);
  RooProduct* signal = new RooProduct("signal", "signal", RooArgSet (*target, *scaleVar));
  mOwnObjects.push_back(signal);
  RooRealVar* bkg = new RooRealVar("bkg", "bkg", background(), minBkg, maxBkg);
  mOwnObjects.push_back(bkg);
  RooAddition* signalPlusBackground = new RooAddition ("signalPlusBackground","signalPlusBackground",RooArgSet (*signal, *bkg));
  mOwnObjects.push_back(signalPlusBackground);
  RooRealVar* nEvents = new RooRealVar("nEvents","nEvents",0, 0.,maxRangeEvents);
  mOwnObjects.push_back(nEvents);
  // sets
  RooArgSet* nuisPar = new RooArgSet(*bkg, *scaleVar);
  mOwnObjects.push_back(nuisPar);
  RooArgSet* poi = new RooArgSet(*target);
  mOwnObjects.push_back(poi);
  // constants
  RooRealVar* bkgMeanVar = new RooRealVar("bkgMean", "bkgMean", background ());
  mOwnObjects.push_back(bkgMeanVar);
  RooRealVar* bkgSigmaVar = new RooRealVar("bkgSigma", "bkgSigma", expectedBkgSigma);
  mOwnObjects.push_back(bkgSigmaVar);
  RooRealVar* scaleMeanVar = new RooRealVar("scaleMean", "scaleMean", 1.);
  mOwnObjects.push_back(scaleMeanVar);
  RooRealVar* scaleSigmaVar = new RooRealVar("scaleSigma", "scaleSigma", expectedScaleSigma);
  mOwnObjects.push_back(scaleSigmaVar);
  // PDFs
  RooPoisson* modelPdf = new RooPoisson ("model","model",*nEvents, *signalPlusBackground);
  mOwnObjects.push_back(modelPdf);
  RooUniform* signalPrior = new RooUniform("signalPrior","signalPrior",*signal);
  mOwnObjects.push_back(signalPrior);
  RooGaussian* priorBkgPdf = new RooGaussian("priorBkg","priorBkg",*bkg,*bkgMeanVar,*bkgSigmaVar);
  mOwnObjects.push_back(priorBkgPdf);
  RooGaussian* priorScalePdf = new RooGaussian("priorScale","priorScale",*scaleVar,*scaleMeanVar,*scaleSigmaVar);
  mOwnObjects.push_back(priorScalePdf);
  RooProdPdf* prior = new RooProdPdf("prior","prior", RooArgList(*signalPrior, *priorBkgPdf, *priorScalePdf));
  mOwnObjects.push_back(prior);
  
  // create a data set with n observed events
  mDataset = new RooDataSet ("data","",*nEvents);
  // to suppress messgaes when pdf goes to zero
  // RooMsgService::instance().setGlobalKillBelow(RooFit::FATAL) ;
  RooMsgService::instance().setGlobalKillBelow(RooFit::WARNING);

  mCalculator = new BayesianCalculator (*mDataset, *modelPdf, RooArgSet(*poi), *prior, nuisPar);
  mCalculator->SetLeftSideTailFraction (0.);
  mCalculator->SetConfidenceLevel(0.95);
}

BayesianCountingExperiment::~BayesianCountingExperiment() {
  delete mCalculator;
  delete mDataset;
  int i = int (mOwnObjects.size());
  while (--i >= 0) delete mOwnObjects[i];
}

double BayesianCountingExperiment::cl95limit (int nObserved, bool fPlot) {
  mDataset->reset();
  RooRealVar* nEventsVar = dynamic_cast<RooRealVar*>(mDataset->get()->first());
  if (!nEventsVar) {
    cout << "BayesianCountingExperiment::cl95limit-> Wrong type of the dataset arg" << endl;
    return 0;
  }
  nEventsVar->setVal (nObserved);
  mDataset->add (*nEventsVar);
  mCalculator->SetData (*mDataset);
  
  SimpleInterval* interval = mCalculator->GetInterval();
  double result = interval->UpperLimit()*scale();
  if (fPlot) {
    RooPlot * plot = mCalculator->GetPosteriorPlot();
    plot->Draw();
  }
  delete interval;
  return result;
}

CountingExperiment* BayesianCountingExperiment::clone(double fBackground, double fBackgroundSigma, double fScale, double fScaleSigma) const {
  return new BayesianCountingExperiment (fBackground, fBackgroundSigma, fScale, fScaleSigma);
}


void BayesianCountingExperiment::print () {
  mCalculator->Print();
  mDataset->Print ();
  for (unsigned i = 0; i < mOwnObjects.size(); ++i) mOwnObjects[i]->Print();
}

#else // not implemented

#include <iostream>
using namespace std;

BayesianCountingExperiment::BayesianCountingExperiment (double fBackground, double fBackgroundSigma, double fScale, double fScaleSigma) 
  : CountingExperiment (fBackground, fBackgroundSigma, fScale, fScaleSigma)
{
  cerr << "BayesianCountingExperiment is not implemented in ROOT < 5.27" << endl;
}

BayesianCountingExperiment::~BayesianCountingExperiment() {}

double BayesianCountingExperiment::cl95limit (int nObserved, bool fPlot) {
  cerr << "BayesianCountingExperiment is not implemented in ROOT < 5.27" << endl;
  return 0;
}

CountingExperiment* BayesianCountingExperiment::clone(double fBackground, double fBackgroundSigma, double fScale, double fScaleSigma) const {
  cerr << "BayesianCountingExperiment is not implemented in ROOT < 5.27" << endl;
  return 0;
}

void BayesianCountingExperiment::print () {
  cerr << "BayesianCountingExperiment is not implemented in ROOT < 5.27" << endl;
}

#endif
