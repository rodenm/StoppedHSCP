/* --------------------------------------------------------------------------------
 Bayesian 95% CL limit and expected (average) 95% CL limit calculator for Poisson statistics
 This code is based on original cl95cms.c written Greg Landsberg
 Modifyed by Fedor Ratnikov
 
-------------------------------------------------------------------------------- */
#include <iostream>
#include <stdlib.h>
#include "TMath.h"
#include "TRandom2.h"
#include "TF1.h"
#include "TH2D.h"
#include "TArrow.h"
#include "TCanvas.h"
#include "Math/ProbFuncMathCore.h"
#include "Math/PdfFuncMathCore.h"
#include "Math/QuantFuncMathCore.h"

using namespace std;

static Double_t A0, sA, B0, sB, epsilon, MaxSig = 100.;
static Double_t MinLike = 1.e-6, Precision = 1.e-5;
static Int_t N;
static bool lGauss = kFALSE, plot = kFALSE;
static Int_t I = 0;
static Double_t sigma_a = 0., sigma_b = 0., tau_a = 0., tau_b = 0.;

Double_t Likelihood(Double_t *x, Double_t *p);
Double_t Inner(Double_t *x, Double_t *par);
Double_t Outer(Double_t *x, Double_t *p);
Double_t Poisson(Double_t Mu, Int_t n);

Double_t CL95(Double_t ilum, Double_t slum, Double_t eff, Double_t seff, Double_t bck, Double_t sbck, Int_t n, Bool_t gauss, Int_t bckmodel)
{
	Double_t xmax = MaxSig;
	Double_t x[1], p[1];
//
	A0 = ilum*eff;
	sA = sqrt(ilum*seff*ilum*seff + eff*slum*eff*slum);
	B0 = bck;
	sB = sbck;
	epsilon = TMath::Max(Precision/ilum,1.e-4);
	//
	lGauss = gauss;
	if (n == 0) lGauss = kFALSE;
	
	if (!gauss) 
	{
		if (bckmodel < 0 || bckmodel > 2) 
		{
			cout << "Incorrect nuissance parameter integration model. Gaussian will be used." << endl;
			bckmodel = 0;
		}
		if (plot) cout << "Poisson 95% CL limit with "; 
		I = bckmodel;
		if (bckmodel == 0) 
		{
			if (plot) cout << "Gaussian ";
		}
		else if (bckmodel == 1) // Lognormal distribution is used
		{
			if (B0 > 0) sigma_b = TMath::Log(1. + sB/B0);
			sigma_a = TMath::Log(1. + sA/A0);
			if (plot) cout << "Lognormal ";
		} 
		else if (bckmodel == 2) // Gamma distribution is used
		{
			if (plot) cout << "Gamma ";
			if (sA > 0) 
			{
				sigma_a = 1. + A0*A0/sA/sA;
				tau_a = A0/sA/sA;
			}
			if (sB > 0) 
			{
				sigma_b = 1. + B0*B0/sB/sB;
				tau_b = B0/sB/sB;
			}
		}		   
	} else if (plot) cout << "Gaussian 95% CL limit with Gaussian ";
	if (plot) cout << "nuisance parameter integration will be used" << endl;
	//
	N = n;
	x[0] = xmax;
	p[0] = 0.;
	//
	Double_t delta = (Likelihood(x,p) - MinLike)/MinLike;
	while (delta > 0)
	{
		if (plot) cout << "delta = " << delta << endl; 
		
		xmax = 2.*xmax;
		x[0] = xmax;
		delta = (Likelihood(x,p) - MinLike)/MinLike;
	}
	//
	Double_t x1 = 0, x2 = xmax;
	while (fabs(delta) > epsilon) 
	{      
		if (delta > 0) x1 = x[0];
		else x2 = x[0];
		x[0] = (x1 + x2)/2.;
		delta = (Likelihood(x,p) - MinLike)/MinLike;
	}         
	xmax = x[0];
	//
	Int_t i = 0;
	if (xmax > 1)
	{
		while (xmax > 10.)
		{
			xmax /= 10.;
			i++;
		}
		xmax = (Int_t)(xmax + 1)*pow(10,i);
	}
	else
	{
		while (xmax < 1.)
		{
			xmax *= 10.;
			i++;
		}
		xmax = (Int_t)(xmax + 1)*pow(10,-i);
	}
	//
	TF1 like("Likelihood",Likelihood,0.,xmax,0);
	if (plot) cout << "Likelihood function is evaluated over [0," << xmax << "] " << endl;
	//
	Double_t Norm = like.Integral(0.,xmax,p,epsilon);
	if (plot) cout << "likelihood normalization: " << Norm << endl;
	//
	//	Double_t x1, x2, delta;	
	x1 = 0;
	x2 = xmax;
	xmax = (x1 + x2)/2.;
	delta = like.Integral(0,xmax,p,epsilon)/Norm - 0.95;
	//
	while (fabs(delta) > epsilon) 
	{
		if (delta < 0) x1 = xmax;
		else x2 = xmax;
		xmax = (x1 + x2)/2.;
		delta = like.Integral(0,xmax,p,epsilon)/Norm - 0.95;
	}         
	
	x[0] = like.GetMaximumX(0.,MaxSig);
	if (plot)
	{
		TCanvas c("Likelihood");
		like.Draw();
		TArrow arrow(xmax,Likelihood(x,p)/7.,xmax,0,0.04);
		arrow.SetLineWidth(3);
		arrow.Draw();
		c.Print("Likelihood.eps");
	}
	if (plot) cout << "Upper 95% C.L. limit on signal = " << xmax << " pb" << endl;
	//
	return xmax;
}

Double_t Likelihood(Double_t *x, Double_t *p)
{
	Double_t retval = 0.;
	if (sB == 0.)
	{
		if (sA == 0.) 
		{
			if (lGauss) retval = TMath::Gaus(N-B0-x[0]*A0,0.,TMath::Sqrt(N),kTRUE);
			else retval = Poisson(B0+x[0]*A0,N);
		}
		else 
		{
			Double_t par[2];
			//		  TF1 *in = new TF1("Inner",Inner,0.,TMath::Max(A0 + 5.*sA,2);
			TF1 *in = new TF1("Inner",Inner,0.,A0 + 5.*sA,2);
			par[0]=B0;  // background value
			par[1]=x[0];  // signal cross section value
			if (I == 0)
			{
				Double_t low = A0 > 5.*sA ? A0 - 5.*sA : 0.;
				retval = in->Integral(low,A0+5.*sA,par,epsilon);
			} else {
				Double_t low = 0., high = A0 + 5.*sA, tmp = 1.;
				while (tmp > epsilon)
				{	 
					tmp = in->Integral(low,high,par,epsilon);
					retval += tmp;
					low = high;
					high *= 2;
				}
			} 
			delete in;
		}
	}
	else
	{
		//	  TF1 *out = new TF1("Outer",Outer,0.,TMath::Max(B0 + 5.*sB,1000.),1);   
		TF1 *out = new TF1("Outer",Outer,0.,B0 + 5.*sB,1);   
		if (I == 0)
		{
			Double_t low = B0 > 5.*sB ? B0 - 5.*sB : 0.;
			retval = out->Integral(low,B0+5.*sB,x,epsilon);
		} else {
			Double_t low = 0., high = B0 + 5.*sB, tmp = 1.;
			while (tmp > epsilon)
			{	 
				tmp = out->Integral(low,high,x,epsilon);
				retval += tmp;
				low = high;
				high *= 2;
			}
		}
		delete out;
	}
	return retval;
}

Double_t Outer(Double_t *x, Double_t *p)
{
	Double_t retval;
	if (sA == 0.) 
	{
		if (lGauss) retval = TMath::Gaus(x[0],B0,sB,kTRUE)*TMath::Gaus(N-x[0]-p[0]*A0,0.,TMath::Sqrt(N),kTRUE);
		else if (I == 0) retval = TMath::Gaus(x[0],B0,sB,kTRUE)*Poisson(x[0]+p[0]*A0,N);
		else if (I == 1) retval = TMath::LogNormal(x[0], sigma_b, 0., B0)*Poisson(x[0]+p[0]*A0,N);
		else if (I == 2) retval = TMath::GammaDist(x[0], sigma_b, 0., 1./tau_b)*Poisson(x[0]+p[0]*A0,N);
		else return 0;
	}
	else 
	{
		Double_t par[2];
		//	   TF1 *in = new TF1("Inner",Inner,0.,TMath::Max(A0 + 5.*sA,1000.),2);
		TF1 *in = new TF1("Inner",Inner,0.,A0 + 5.*sA,2);
		par[0]=x[0];  // background value
		par[1]=p[0];  // signal cross section value
		Double_t low = A0 > 5.*sA ? A0 - 5.*sA : 0.;
		if (I == 0) retval = TMath::Gaus(x[0],B0,sB,kTRUE)*in->Integral(low,A0+5.*sA,par,epsilon);
		else if (I == 1) retval = TMath::LogNormal(x[0], sigma_b, 0., B0)*in->Integral(0.,A0+5.*sA,par,epsilon);
		else if (I == 2) retval = TMath::GammaDist(x[0], sigma_b, 0., 1./tau_b)*in->Integral(0.,A0+5.*sA,par,epsilon);
		else return 0;
		delete in;
	}
	return retval;
}

Double_t Inner(Double_t *x, Double_t *par)
{
    Double_t sigma, B;
	//
    B = par[0];
    sigma = par[1];
    if (lGauss) return TMath::Gaus(x[0],A0,sA,kTRUE)*TMath::Gaus(N-B-sigma*x[0],0.,TMath::Sqrt(N),kTRUE);
    else if (I == 0) return TMath::Gaus(x[0],A0,sA,kTRUE)*Poisson(B+sigma*x[0],N);
	else if (I == 1) return TMath::LogNormal(x[0], sigma_a, 0., A0)*Poisson(B+sigma*x[0],N);
	else if (I == 2) return TMath::GammaDist(x[0], sigma_a, 0., 1./tau_a)*Poisson(B+sigma*x[0],N);
	else return 0;
}

Double_t Poisson(Double_t Mu, Int_t n) {
  return n >= 0 ? ROOT::Math::poisson_pdf(unsigned(n), Mu) : 0;
}


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
  return sqrt (sumDX2s/sumWeights);
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
//     double mysum = 0;
//     for (unsigned i = 0; i < weights.size(); ++i) {
//       cout << "data: " << i << ' ' << limits[i] 
//   	 << ' ' << weights[i]/integral 
//   	 << ' ' << (mysum+=weights[i]/integral) << endl;
//     }

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

std::vector<double> CLA(Double_t ilum, Double_t slum, Double_t eff, Double_t seff, Double_t bck, Double_t sbck, Int_t bckint)
{
  double smearing = 1.;
   plot = kFALSE;
   std::vector <int> vObserved;
   std::vector <double> vWeight;
   std::vector <double> vLimit;
   int maxNegBckg = int(floor(bck));
   double precision = 1.e-3*Poisson(bck,maxNegBckg);
   double sumAll = 0;
   int nSampling = 100;
   double dSumpling = 5*sbck/nSampling;

   for (int i = maxNegBckg; i >= 0; --i) {
     Double_t s95 = CL95(ilum, slum, eff, seff, bck, sbck, i, kFALSE, bckint);
     vObserved.push_back (i);
     vLimit.push_back (s95);
     vWeight.push_back (0);
     int iSample = nSampling;
     while (--iSample >= 0) {
       for (int iSide = -1; iSide <= 1; iSide+=2) {
	 double sampledBkg = bck + smearing*iSide*(iSample+0.5)*dSumpling;
	 if (sampledBkg < 0) continue;
	 double bkgWeight = ROOT::Math::normal_pdf(sampledBkg, sbck, bck)*ROOT::Math::poisson_pdf (i, sampledBkg);
	 //       std::cout << "sampledBkg/bkgWeight: " << sampledBkg << '/' << bkgWeight << ' ' << i << std::endl;
	 vWeight.back() += bkgWeight;
       }
     }
     sumAll += vWeight.back()*vLimit.back();
     if (vWeight.back() < precision) break;
   }
   for (int i = maxNegBckg+1; ; ++i) {
     Double_t s95 = CL95(ilum, slum, eff, seff, bck, sbck, i, kFALSE, bckint);
     vObserved.push_back (i);
     vLimit.push_back (s95);
     vWeight.push_back (0);
     int iSample = nSampling;
     while (--iSample >= 0) {
       for (int iSide = -1; iSide <= 1; iSide+=2) {
	 double sampledBkg = bck + smearing*iSide*(iSample+0.5)*dSumpling;
	 if (sampledBkg < 0) continue;
	 double bkgWeight = ROOT::Math::normal_pdf(sampledBkg, sbck, bck)*ROOT::Math::poisson_pdf (i, sampledBkg);
	 //       std::cout << "sampledBkg/bkgWeight: " << sampledBkg << '/' << bkgWeight << ' ' << i << std::endl;
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

   std::cout << "CLAQuanyile->" << "median:" << median 
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

double poissonMeanMax (int nObserved, double probability, double precision) {
  double xMin = nObserved;
  double xMax = nObserved > 0 ? 2*nObserved : 1;
  while (ROOT::Math::poisson_pdf (nObserved, xMax) > probability) xMax *= 2;
  while (1) {
    double x = 0.5*(xMin+xMax);
    double delta = (probability - ROOT::Math::poisson_pdf (nObserved, x)) / probability;
    std::cout << "poissonMeanMax-> " << nObserved << '/' << probability << '/' << precision
	      << " xmin/xmax/x/delta: " << xMin << '/' << xMax << '/' <<  x << '/' << delta
	      << std::endl; 
    if (fabs(delta) < precision) return x;
    if (delta > 0) {
      xMax = x;
    }
    else {
      xMin = x;
    }
  }
}

std::vector<TH2D*> CLCoverage(Double_t bck, Double_t sBck, Int_t nObserved, Int_t bckint)
// run coverage test for the model
{
  int nBinsB = 9;
  int nBinsS = 9;
  // scan ranges
  double precision = 1e-3;
  double muBMin = bck + ROOT::Math::normal_quantile (precision, sBck);
  if (muBMin < 0) muBMin = 0;
  double muBMax = bck + ROOT::Math::normal_quantile_c (precision, sBck);
  double dMuB = (muBMax-muBMin)/nBinsB;
  double muSMin = 0;
  double muSMax = poissonMeanMax (nObserved, precision, precision);
  double dMuS = (muSMax-muSMin)/nBinsS;

  char buffer[1024];
  sprintf (buffer, "Coverage: N_{observed}=%d, #mu_{bkg}=%5.1f+-%4.1f; #mu_{background}; #mu_{signal}", nObserved, bck, sBck);
  
  TH2D* h_coverageBS = new TH2D ("h_coverageBS", buffer, 
				 nBinsB+1, muBMin-0.5*dMuB, muBMax+0.5*dMuB,
				 nBinsS+1, muSMin-0.5*dMuS, muSMax+0.5*dMuS
				 );
  
  sprintf (buffer, "Probability to get N_{observed}=%d: #mu_{bkg}=%5.1f+-%4.1f; #mu_{background}; #mu_{signal}", nObserved, bck, sBck);
  TH2D* h_NeventsBS = new TH2D ("h_NeventsBS", buffer,
				nBinsB+1, muBMin-0.5*dMuB, muBMax+0.5*dMuB,
				nBinsS+1, muSMin-0.5*dMuS, muSMax+0.5*dMuS
				);
  
  TRandom2 rndm;
  for (int iS = 0; iS <= nBinsS; ++iS) {
    double muS = muSMin + iS*dMuS; 
    for (int iB = 0; iB <= nBinsB; ++iB) {
      double muB = muBMin + iB*dMuB;
      if (muB < 0) continue;
      double coverage = 0;
      double fitNObserved = 0;
      int nToy = 1000;
      for (int iToy = 0; iToy < nToy; ++iToy) {
	int nToyObserved = rndm.Poisson(muS+muB);
	double toyLimit = CL95 (1, 0, 1, 0, muB, 0.35*muB, nToyObserved, 0, bckint);
	//double toyLimit = CL95 (1, 0, 1, 0, bck, sBck, nToyObserved, 0, bckint);
	if (toyLimit > muS) coverage += 1.;
	if (nToyObserved == nObserved) fitNObserved += 1.;
      }
      coverage /= nToy;
      fitNObserved /= nToy;
      std::cout << "covarege-> " << iS << '/' << iB
		<< " s/b:" << muS << '/' << muB
		<< " coverage:" << coverage
		<< " prob Observed:" << fitNObserved
		<< std::endl;
      h_coverageBS->Fill (muB, muS, coverage);
      h_NeventsBS->Fill (muB, muS, fitNObserved);
    }
  }
  
  std::vector<TH2D*> result;
  result.push_back(h_coverageBS);
  result.push_back(h_NeventsBS);
  return result;
}
