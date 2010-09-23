#include "StoppedHSCP/Statistics/interface/CountingExperiment.h"

#include <math.h>
#include <iostream>

#include "Math/ProbFuncMathCore.h"
#include "Math/PdfFuncMathCore.h"
#include "Math/QuantFuncMathCore.h"

#include "TH1D.h"
#include "TRandom2.h"

using namespace std;

namespace {
  double getMean (const std::vector<double>& fLimits, 
		  const std::vector<double>& fWeights) {
    double sumWeights = 0;
    double sumXs = 0;
    for (unsigned i = 0; i < fLimits.size(); ++i) {
      sumXs += fLimits[i]*fWeights[i];
      sumWeights += fWeights[i];
    }
    return sumXs/sumWeights;
  }
  
  double getSideRMS (int fSide, double fMean,
		     const std::vector<double>& fLimits, 
		     const std::vector<double>& fWeights) {
    double sumWeights = 0;
    double sumDX2s = 0;
    for (unsigned i = 0; i < fLimits.size(); ++i) {
      if (fSide * (fLimits[i]-fMean) >=0) {
	sumDX2s += (fLimits[i]-fMean)*(fLimits[i]-fMean)*fWeights[i];
	sumWeights += fWeights[i];
      }
    }
    return sumWeights > 0 ? sqrt (sumDX2s/sumWeights) : 0;
  }
  
  
  double getQuantile (double fProbability, 
		      const std::vector<double>& fLimits, 
		      const std::vector<double>& fWeights) {
    // make sorted list
    std::vector<double> limits (fLimits);
    std::vector<double> weights (fWeights);
    // bubble sort
    bool goexit = false;
    while (!goexit) {
      int i = int(limits.size()) - 1;
      while (--i >= 0) {
	if (limits[i] > limits[i+1]) { // swap
	  swap (limits[i], limits[i+1]);
	  swap (weights[i], weights[i+1]);
	  break;
	}
	if (i == 0) goexit = true;
      }
    }
    // get integral
    double integral = 0;
    for (unsigned i = 0; i < weights.size(); ++i) integral += weights[i];
    
    // search for quantile
    double target = integral * fProbability;
    double sum = 0;
    unsigned iPlus = 0;
    for (; (iPlus < weights.size()) && ((sum+=weights [iPlus]) < target); ++iPlus) {}
    if (iPlus == 0) {
      std::cout << "Quantile " << fProbability << " is on the low edge" <<  std::endl;
      return limits[0];
    }
    if (sum < target) {
      std::cout << "Quantile " << fProbability << " is on the high edge" <<  std::endl;
      return limits.back();
    }
    // make linear extrapolation
    return limits[iPlus]-(sum-target)/weights[iPlus]*(limits[iPlus]-limits[iPlus-1]);
  }
  
}


CountingExperiment::CountingExperiment (double fBackground, double fBackgroundSigma, double fScale, double fScaleSigma) 
  : mBackground (fBackground),
    mBackgroundSigma (fBackgroundSigma),
    mScale (fScale),
    mScaleSigma (fScaleSigma)
{}

CountingExperiment::~CountingExperiment () {}

vector<double> CountingExperiment::cl95ExpectedLimit () {
  double smearing = 1.;
  std::vector <int> vObserved;
  std::vector <double> vWeight;
  std::vector <double> vLimit;
  int maxNegBckg = int(floor(background()));
  double precision = 1.e-3*ROOT::Math::poisson_pdf(maxNegBckg, background());
  double sumAll = 0;
  int nSampling = 100;
  double dSumpling = 5*backgroundSigma()/nSampling;
  
  for (int i = maxNegBckg; i >= 0; --i) {
    cout << "cl95limit... " << i << endl;
    Double_t s95 = cl95limit (i);
    cout << "nObserved/limit: " << i << '/' << s95 << endl;
    vObserved.push_back (i);
    vLimit.push_back (s95);
    vWeight.push_back (0);
    int iSample = nSampling;
    while (--iSample >= 0) {
      for (int iSide = -1; iSide <= 1; iSide+=2) {
	double sampledBkg = background() + smearing*iSide*(iSample+0.5)*dSumpling;
	if (sampledBkg < 0) continue;
	double bkgWeight = ROOT::Math::normal_pdf(sampledBkg, backgroundSigma(), background())*ROOT::Math::poisson_pdf (i, sampledBkg);
	//	std::cout << "sampledBkg/bkgWeight: " << sampledBkg << '/' << bkgWeight << ' ' << i << std::endl;
	vWeight.back() += bkgWeight;
      }
    }
    sumAll += vWeight.back()*vLimit.back();
    if (vWeight.back() < precision) break;
  }
  for (int i = maxNegBckg+1; ; ++i) {
    cout << "cl95limit... " << i << endl;
    Double_t s95 = cl95limit (i);
    cout << "nObserved/limit: " << i << '/' << s95 << endl;
    vObserved.push_back (i);
    vLimit.push_back (s95);
    vWeight.push_back (0);
    int iSample = nSampling;
    while (--iSample >= 0) {
      for (int iSide = -1; iSide <= 1; iSide+=2) {
	double sampledBkg = background() + smearing*iSide*(iSample+0.5)*dSumpling;
	if (sampledBkg < 0) continue;
	double bkgWeight = ROOT::Math::normal_pdf(sampledBkg, backgroundSigma(), background())*ROOT::Math::poisson_pdf (i, sampledBkg);
	//	std::cout << "sampledBkg/bkgWeight: " << sampledBkg << '/' << bkgWeight << ' ' << i << std::endl;
	vWeight.back() += bkgWeight;
      }
    }
    sumAll += vWeight.back()*vLimit.back();
    if (vWeight.back() < precision) break;
  }
  
  // make median/quantiles
  double median = getQuantile (0.5, vLimit, vWeight);
  double sigma1Minus = getQuantile (ROOT::Math::normal_cdf (-1), vLimit, vWeight);
  double sigma1Plus = getQuantile (ROOT::Math::normal_cdf (1), vLimit, vWeight);
  double sigma2Minus = getQuantile (ROOT::Math::normal_cdf (-2), vLimit, vWeight);
  double sigma2Plus = getQuantile (ROOT::Math::normal_cdf (2), vLimit, vWeight);
  
  std::cout << "CLAQuantile->" << "median:" << median 
	    << " -+1sigma: - " << sigma1Minus << " + " << sigma1Plus
	    << " -+2sigma: - " << sigma2Minus << " + " << sigma2Plus
	    << std::endl;
  
  double mean = getMean (vLimit, vWeight);
  double msigma = getSideRMS (-1, mean, vLimit, vWeight);
  double psigma = getSideRMS (1, mean, vLimit, vWeight);
  std::cout << "MEAN:" << mean
	    << " -sigma:" << msigma
	    << " +sigma:" << psigma
	    << " +-1sigma band: [" << mean-msigma << ',' << mean+psigma << ']'
	    << std::endl;
  
  std::vector<double> result;
  result.push_back(median);
  result.push_back(sigma1Minus);
  result.push_back(sigma1Plus);
  result.push_back(sigma2Minus);
  result.push_back(sigma2Plus);
  result.push_back(mean);
  result.push_back(mean-msigma);
  result.push_back(mean+psigma);
  result.push_back(mean-2*msigma);
  result.push_back(mean+2*psigma);
  return result;
}

double CountingExperiment::coverage (double fTrueSignal, double fPrecision) {
  int maxCounters = int (floor (1./fPrecision/fPrecision + 0.5));
  double nEventsTrue = fTrueSignal/scale() + background();
  const int nToys = 100 * maxCounters; // consider 99% maximum
  int counter = 0;
  TRandom2 rndm;
  int iToy = 0;
  for (; iToy < nToys; ++iToy) {
    double bkg = -1;
    while (bkg < 0) bkg = rndm.Gaus(background(), backgroundSigma());
    double scl = -1;
    while (scl < 1e-2) scl = rndm.Gaus(scale(), scaleSigma());
    CountingExperiment* instance = clone (bkg, backgroundSigma(),scl, scaleSigma());
    int nEvents = rndm.Poisson (nEventsTrue);
    double cl95Toy = instance->cl95limit (nEvents);
    delete instance;
    // cout << iToy << '/' << nEvents << '/' << fTrueSignal << '/' << cl95Toy << '/' << counter << endl;
    if (fTrueSignal >= cl95Toy) ++counter;
    if (counter >= maxCounters) {
      iToy += int (floor(0.5*iToy/maxCounters+0.5));
      break;
    }
    if (counter==0 && iToy >= 3*100) break; // nothing in 1%
  }
  return 1. - double(counter)/double(iToy);
}

TH1D* CountingExperiment::plotCoverage (const char* fId, int fBins, double fMinSignal, double fMaxSignal, bool fShowProgress)  {
  TH1D* result = new TH1D (fId, "Coverage", fBins, fMinSignal, fMaxSignal);
  if (fShowProgress) cout << endl; 
  for (int i = 1; i <= result->GetNbinsX(); ++i) {
    result->SetBinContent (i, coverage (result->GetBinCenter(i)));
    if (fShowProgress) cout << '.' << flush;
  }
  if (fShowProgress) cout << endl;
  result->SetStats (false);
  return result;
}
