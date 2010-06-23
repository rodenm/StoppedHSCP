#include "StoppedHSCP/ToyMC/interface/Reducer.h"

#include <iostream>
#include "Math/ProbFuncMathCore.h"
#include "Math/QuantFuncMathCore.h"
#include "TMath.h"



Reducer::Reducer(const std::vector<Experiment> &input)
        : exps(input)
{
}

TGraph *Reducer::getEfficiencyPlot()
{
    double xpoints[1000], ypoints[1000];
    int counter = 0;
    for (cit = exps.begin(); cit != exps.end(); cit++)
    {
             xpoints[counter] = cit->lifetime;
             ypoints[counter] = cit->nSig_d / cit->nGeneratedDecays;
             counter++;
    }

    return new TGraph(counter, xpoints, ypoints);
}

TGraph *Reducer::getVetoesPlot() {
  double xpoints[1000], ypoints[1000];
  int counter = 0;
  
  for (cit = exps.begin(); cit != exps.end(); cit++)
    {
      xpoints[counter] = cit->lifetime;
      ypoints[counter] = cit->nVetoes/ cit->nSig_d;
      counter++;
    }

  return new TGraph(counter, xpoints, ypoints);
}

TGraph *Reducer::getZbPlot(double lifetime)
{
  double xpoints[1000], ypoints[1000];
  int counter = 0;

  for (cit = exps.begin(); cit != exps.end(); cit++)
    {
      if (cit->lifetime != lifetime) continue;

      xpoints[counter] = cit->runningTime;
      double Pb = ROOT::Math::poisson_cdf_c(cit->nSig + cit->nBg, cit->nExpectedBg);
      ypoints[counter] = ROOT::Math::normal_quantile_c(Pb/2, 1);
      counter++;
    }

  /*
  std::cerr << "Returning Discovery TGraph with " << counter << " points."
	    << std::endl
	    << "7 coord is " << xpoints[1] << ", "
	    << ypoints[1] << std::endl;
  */
  return new TGraph(counter, xpoints, ypoints);
}

TGraph *Reducer::getExclusionPlot(double mass)
{
  double xpoints[100];
  double ypoints[100];
  unsigned point=0;

  for (cit = exps.begin(); cit != exps.end(); cit++)
    if (cit->mass == mass) {
      xpoints[point] = cit->lifetime;

      double o_s, o_b, s, b, a_s, a_b, b_s, b_b;
      a_s = a_b = 1000000000;
      b_s = b_b = 0;
      unsigned int iterations = 0;
      double ratio = 0;

      o_s = s = cit->nSig;
      o_b = b = cit->nExpectedBg;

      while (1) {
        if (++iterations > 1000) {ratio = s/o_s; break;}
        double p = ROOT::Math::poisson_cdf(cit->nBg, s+b);
        if (p > 0.05) {
          b_s = s;
          s = (s+a_s)/2;
          if (s > (b_s != 0 ? b_s*2 : 1)) {
            s = (b_s != 0 ? b_s*2 : 1);
          }
        }
        else if (p < 0.05) {
          a_s = s;
          s = (s+b_s)/2;
        }
      }

      // stopping efficiency assumes 300 GeV mass
      double cSection = ratio * cit->crossSection * 0.162 * 1e34;
      cSection = -TMath::Log10(cSection);

      ypoints[point] =
        TMath::Power(cSection, 3) * (7.22597) +
        TMath::Power(cSection, 2) * (-9.36011 ) +
        cSection         * (195.055 ) +
        282.299;
      
      ++point;
    }
  return new TGraph(point, xpoints, ypoints);
}

TGraph *Reducer::getCrossSectionPlot(double mass, bool projection)
{
  double xpoints[100];
  double ypoints[100];
  unsigned point=0;

  for (cit = exps.begin(); cit != exps.end(); cit++)
    if (cit->mass == mass) {
      xpoints[point] = cit->lifetime;

      //      double o_s, o_b, s, b, a_s, a_b, b_s, b_b;
      //       a_s = a_b = 1000000000;
      //       b_s = b_b = 0;
      //      unsigned int iterations = 0;
      //      double ratio = 0;

      double nObs = cit->nObs;
      double nSExp = cit->nSig_d;
      double nBExp = cit->nExpectedBg;
      double errBExp = (cit->errBgRate/cit->bgRate) * cit->nExpectedBg;
      double cl95 = 0.;
      unsigned nToys = 500;

      if (projection) {
	//	cl95 = countingExperiment95CLUpperLimit(nBExp, nBExp+nSExp, errBExp, nToys);
      }
      else {
	//	cl95 = countingExperiment95CLUpperLimit(nObs, nBExp+nSExp, errBExp, nToys);
      }

      double sigma=(cl95 / nSExp) * cit->crossSection;

      std::cout << "Exclusion plot :" << std::endl;
      std::cout << "s=" << nSExp << "\tb=" << nBExp << "\terrb=" << errBExp << std::endl;
      std::cout << "N_cl95=" << cl95 << "\tsigma=" << sigma << std::endl;

//       while (1) {
//         if (++iterations > 1000) {ratio = s/o_s; break;}
// 	double p = 0;
// 	if (projection)
// 	  p = ROOT::Math::poisson_cdf(cit->nExpectedBg, s+b);
// 	else
// 	  p = ROOT::Math::poisson_cdf(cit->nObs, s+b);

//         if (p > 0.05) {
//           b_s = s;
//           s = (s+a_s)/2;
//           if (s > (b_s != 0 ? b_s*2 : 1)) {
//             s = (b_s != 0 ? b_s*2 : 1);
//           }
//         }
//         else if (p < 0.05) {
//           a_s = s;
//           s = (s+b_s)/2;
//         }
//       }

      // stopping efficiency assumes 300 GeV mass
      /*
      double cSection = ratio * cit->crossSection * 0.162 * 1e34;
      cSection = -TMath::Log10(cSection);

      ypoints[point] =
        TMath::Power(cSection, 3) * (7.22597) +
        TMath::Power(cSection, 2) * (-9.36011 ) +
        cSection         * (195.055 ) +
        282.299;
      */
      ypoints[point] = sigma;
      ++point;
    }
  return new TGraph(point, xpoints, ypoints);
}
