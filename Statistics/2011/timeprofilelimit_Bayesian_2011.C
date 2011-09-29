
#ifndef __CINT__

#include "Math/SpecFuncMathCore.h"
#include "RooGlobalFunc.h"
#endif
#include "RooMsgService.h"
#include "RooDataSet.h"
#include "RooRealVar.h"
#include "RooGaussian.h"
#include "RooAddPdf.h"
#include "RooProdPdf.h"
#include "RooAddition.h"
#include "RooProduct.h"
#include "TCanvas.h"
#include "RooChebychev.h"
#include "RooPolynomial.h"
#include "RooAbsPdf.h"
#include "RooExtendPdf.h"
#include "RooFit.h"
#include "RooFitResult.h"
#include "RooPlot.h"
#include "RooAbsArg.h"
#include "RooWorkspace.h"
#include "RooMCStudy.h"
#include "RooStats/ProfileLikelihoodCalculator.h"
#include "RooStats/LikelihoodIntervalPlot.h"
#include "RooStats/HypoTestResult.h"
#include "TRandom2.h"
#include "TH2D.h"
#include "TPaveText.h"
#include "TLegend.h"
#include <string>
#include <sstream>
#include <fstream>

#include "RooHCSPInOrbitPdf.h"

namespace {
  void makeBeams (const string& fFile, vector<double>* fBeam1, vector<double>* fBeam2) {
    ifstream input (fFile.c_str());
    *fBeam1 = vector<double> (3564, 0);
    *fBeam2 = vector<double> (3564, 0);
    double sum1 = 0;
    double sum2 = 0;
    while (input) {
      string line;
      if (getline (input, line)) {
	if (line[0] == '#') continue;
	int i1, i2, rfBucket, bunchSpace, bunchesInTrain, spaceSPS, psTrains;
	string ringName;
	double population;
	istringstream inLine (line);
	inLine >> i1 >> i2 >> ringName >> rfBucket >> bunchSpace >> bunchesInTrain >> spaceSPS >> psTrains >> population;
	bool beam1 =  ringName.find ("_1") != string::npos;
	vector<double>* beam = beam1 ? fBeam1 : fBeam2;
	int ibx0 = (rfBucket / 10) + 1;
	int trainOffset = spaceSPS / 25;
	int step = bunchSpace / 25;
	for (int train = 0; train < psTrains; ++train) {
	  int ibx = ibx0 + trainOffset * train;
	  for (int i = 0; i < bunchesInTrain; ++i) {
	    (*beam)[ibx] = population;
	    if (beam1) sum1 += population;
	    else sum2 += population;
	    ibx += step;
	  }
	}
      }
    }
    if (sum1) for (size_t i = 1; i < fBeam1->size(); ++i) (*fBeam1)[i] /= sum1;
    if (sum2) for (size_t i = 1; i < fBeam2->size(); ++i) (*fBeam2)[i] /= sum2;
  }

  void fillBunchStructure (RooHCSPInOrbitPdf& signal, const vector<double>& beam1, const vector<double>& beam2, double integratedLumi = 1.) {
    std::vector<double> collisionBunches (beam1.size(), 0);
    double sumAll = 0;
    std::vector<int> parasiticBunches;
    for (unsigned i = 0; i < beam1.size(); ++i) {
      double lumi = beam1[i] * beam2[i];
      collisionBunches [i] = lumi;
      sumAll += lumi;
      if ((lumi <= 0) && ((beam1[i]+beam2[i]) > 0)) parasiticBunches.push_back (i); 
    }
    for (unsigned i = 0; i < parasiticBunches.size(); ++i) {
      signal.setInsensitive(parasiticBunches[i]-2);
      signal.setInsensitive(parasiticBunches[i]-1);
      signal.setInsensitive(parasiticBunches[i]);
      signal.setInsensitive(parasiticBunches[i]+1);
      signal.setInsensitive(parasiticBunches[i]+2);
    }
    for (unsigned i = 0; i < collisionBunches.size(); ++i) {
      if (collisionBunches[i] > 0) {
	signal.setInsensitive(i-2);
	signal.setInsensitive(i-1);
	signal.setInstantLumi(i, collisionBunches[i] / sumAll * integratedLumi);
	signal.setInsensitive(i+1);
	signal.setInsensitive(i+2);
      }
    }
  }
}
  class MyLikelihood {
  public:
    MyLikelihood (const RooHCSPInOrbitPdf* fSignal, const RooHCSPBkgInOrbitPdf* fBkg, RooRealVar* fBX, double fLumi) 
      : mSignal (fSignal),
	mBackground (fBkg),
	mBX (fBX),
	mSignalNorm (0.),
	mBkgNorm (0.),
	mLumi(fLumi)
    {}

    bool setData (double fData) {
      if (mSignal->getSensitive (int (floor (fData+0.5)))) {
	mData.push_back (fData);
	return true;
      }
      return false;
    }

    int eventsNumber () const {return int(mData.size());}

    double getLikelyhood (double fSignal, double fBackground) {
      cout << "getLikelyhood-> " << fSignal << '/' << fBackground << endl;
      if (fSignal < 0 || fBackground < 0 || fSignal+fBackground <= 0) return 0;
      double result = 1.;
      if (mSignalNorm <= 0) mSignalNorm = mSignal->analyticalIntegral(1, 0);
      if (mBkgNorm <= 0) mBkgNorm = mBackground->analyticalIntegral(1, 0);
      cout << "getLikelyhood-> Normalization " << mSignalNorm << '/' << mBkgNorm << endl;
      double signalFraction = fSignal / (fSignal+fBackground);
      double backgroundFraction = 1. - signalFraction;
      for (int iData = 0; iData < int(mData.size()); ++iData) {
	*mBX = mData[iData];
	double pdf = signalFraction * mSignal->evaluate() / mSignalNorm 
	  + backgroundFraction * mBackground->evaluate() / mBkgNorm;
	cout << iData << "-> " << mSignal->evaluate() << '/' << mBackground->evaluate() << "->"  << pdf << '/' << result << endl;
	result *= pdf;
      }
      cout << "getLikelyhood-> result 1 " << result << endl;
      result *= ROOT::Math::poisson_pdf (mData.size(), fSignal+fBackground);
      return result;
    }

    double getLogLikelyhood (double fSignal, double fBackground) {
      if (fSignal < 0 || fBackground < 0 || fSignal+fBackground <= 0) return 0;
      double result = 0;
      if (mSignalNorm <= 0) mSignalNorm = mSignal->analyticalIntegral(1, 0);
      if (mBkgNorm <= 0) mBkgNorm = mBackground->analyticalIntegral(1, 0);
      double signalFraction = fSignal / (fSignal+fBackground);
      double backgroundFraction = 1. - signalFraction;
      for (int iData = 0; iData < int(mData.size()); ++iData) {
	*mBX = mData[iData];
	double pdf = signalFraction * mSignal->evaluate() / mSignalNorm 
	  + backgroundFraction * mBackground->evaluate() / mBkgNorm;
	result += log(pdf);
      }
      result += log (ROOT::Math::poisson_pdf (mData.size(), fSignal+fBackground));
      return result;
    }

    const RooHCSPInOrbitPdf* signalPdf () {return mSignal;}

    const RooHCSPBkgInOrbitPdf* backgroundPdf () {return mBackground;}

    double getLumi () {return mLumi;}
    const RooRealVar& bxVar () const {return *mBX;}
    const std::vector <double>& data () const {return mData;}

  private:
    const RooHCSPInOrbitPdf* mSignal;
    const RooHCSPBkgInOrbitPdf* mBackground;
    RooRealVar* mBX;
    std::vector <double> mData;
    double mSignalNorm;
    double mBkgNorm;
    double mLumi;
  }; 

std::vector<double> makeSignalPdf (const std::vector<double>& fSignalScan, 
				   const std::vector<double>& fBackgroundScan,
				   MyLikelihood& fLikelihood,
				   double fRelativeScaleUncertainty);

MyLikelihood* makeFillStructure (const string& scheme, double lumi, RooRealVar& bx, RooRealVar& logtau);

void plotFill (MyLikelihood& fLH);

using namespace std;
using namespace RooFit;

double get95BayesianLimit (const std::string& stats, double fLifetime) {
  RooRealVar bx ("bx", "bx", -0.5, double(BX_IN_ORBIT)-0.5,"bxs");
  RooRealVar logtau ("logtau","log(lifetime)",log (fLifetime) ,log(1.e-10),log (1.e10));
  std::cout << "tau: " << fLifetime << ", logtau: " << logtau.getVal() << std::endl;

  std::vector <MyLikelihood*> fills;
  MyLikelihood* mlh = 0;

  mlh = makeFillStructure ("50ns_228b+1small_214_12_180_36bpi8inj.beam", 4.60, bx, logtau); 
  mlh->setData(903);
  mlh->setData(2431);
  fills.push_back (mlh);
  
  mlh = makeFillStructure ("50ns_336b+1small_322_12_288_36bpi11inj.beam", 17.67, bx, logtau); 
  fills.push_back (mlh);
  
  mlh = makeFillStructure ("50ns_480b+1small_424_12_468_36bpi15inj.beam", 85.63, bx, logtau); 
  mlh->setData(3453);
  mlh->setData(2951);
  mlh->setData(3423);
  mlh->setData(2658);
  mlh->setData(1508);
  // mlh->setData();
  fills.push_back (mlh);
  plotFill (*mlh);
  
  
  mlh = makeFillStructure ("50ns_624b+1small_598_16_576_72bpi11inj_b.beam", 7.82, bx, logtau); 
  fills.push_back (mlh);
  
  double maxXsec = 20;
  int xSecBins = 500;
  std::vector<double> xSecGrid;
  for (int i = 0; i < xSecBins; ++i) xSecGrid.push_back ((i+0.5)*maxXsec/xSecBins);

  std::vector<double> combinedPdf (xSecBins, 1.);
  double sumLumi = 0;
  
  for (size_t iFill = 0; iFill < fills.size(); ++iFill) {
    double lumi = fills[iFill]->getLumi();
    int nEvents = fills[iFill]->eventsNumber ();
    double timeEfficiency =  fills[iFill]->signalPdf()->offLumiFraction ();
    std::vector<double> bkgGrid;
    double maxBkg = nEvents;
    while (ROOT::Math::poisson_cdf (nEvents, maxBkg) > 1e-4) maxBkg += 1.;
    int bkgBins = 500;
    for (int i = 0; i < bkgBins; ++i) bkgGrid.push_back ((i+0.5)*maxBkg/bkgBins);
    std::vector<double> signalGrid;
    for (int i = 0; i < xSecBins; ++i) signalGrid.push_back (xSecGrid[i]*lumi*timeEfficiency);
    std::vector<double> componentPdf = makeSignalPdf (signalGrid, bkgGrid, *fills[iFill], 0.086);
    for (int i = 0; i < xSecBins; ++i) combinedPdf[i] *= componentPdf[i];
    sumLumi += lumi;
  }

  // look for 95% CL limit
  double integral = 0;
  for (int i = 0; i < xSecBins; ++i) integral += combinedPdf[i];
  double sumBefore = 0;
  double sumWith = 0;
  double xSec95limit = 0;;
  for (int i = 0; i < xSecBins; ++i) {
    sumWith = sumBefore + combinedPdf[i] / integral;
    double cl = 0.95;
    if (sumWith >= cl) {
      xSec95limit = xSecGrid[i] - (xSecGrid[i]-xSecGrid[i-1])*(sumWith - cl)/(sumWith-sumBefore);
      break;
    }
    sumBefore = sumWith;
  }
  // normalize to effective number of events
  return xSec95limit * sumLumi;
}


  std::vector<double> makeSignalPdf (const std::vector<double>& fSignalScan, 
				     const std::vector<double>& fBackgroundScan,
				     MyLikelihood& fLikelihood,
				     double fRelativeScaleUncertainty) {
    unsigned nSignalBins = fSignalScan.size();
    unsigned nBackgroundBins = fBackgroundScan.size();
    if (nSignalBins < 2) return std::vector<double>(0);
    // Run Bayesian integral explicitly
    // get all probabilities on grid
    std::vector<std::vector<double> > allLogLH (nSignalBins, std::vector<double> (nBackgroundBins, 0.));
    double maxLogLH = 0;
    for (size_t is = 0; is < nSignalBins; ++is) {
      for (size_t ib = 0; ib < nBackgroundBins; ++ib) {
	double loglh = fLikelihood.getLogLikelyhood (fSignalScan[is], fBackgroundScan[ib]);
	allLogLH[is][ib] = loglh;
	if ((is==0&&ib==0) || loglh > maxLogLH)  maxLogLH = loglh;
      }
    }
    // normalize to 1
    for (size_t is = 0; is < nSignalBins; ++is) {
      for (size_t ib = 0; ib < nBackgroundBins; ++ib) {
	allLogLH[is][ib] -= maxLogLH;
      }
    }

    std::vector<double> pdfNoSys (nSignalBins, 0.);
    for (size_t is = 0; is < nSignalBins; ++is) {
      for (size_t ib = 0; ib < nBackgroundBins; ++ib) {
	double lh = exp (allLogLH[is][ib]);
	pdfNoSys [is] += lh;
	//        std::cout << "iteration-> " << signal << '/' << background
	//  		<< " LH: " << lh
	//  		<< "  " << signalPDFv [is]
	//  		<< std::endl;
      }
    }
    
    // smear by scale uncertainty 
    double integral = 0;
    std::vector<double> pdfSys (nSignalBins, 0.);
    
    for (int di = nSignalBins-1; di >= 0; --di) {
      for (int isign = -1; isign <=1; isign+=2) {
	if (di == 0 && isign > 0) continue;
	for (size_t is = 0; is < nSignalBins; ++is) {
	  int is2 = int(is) + isign*di;
	  if (is2 < 0 || is2 >= int(nSignalBins)) continue;
	  double sigma = fSignalScan[is] * fRelativeScaleUncertainty;
	  double sMin = is2 > 0 ? 0.5*(fSignalScan[is2-1]+fSignalScan[is2]) : 0.5*(3*fSignalScan[is2]-fSignalScan[is2+1]);
	  double sMax = is2 < int(nSignalBins)-1 ? 0.5*(fSignalScan[is2]+fSignalScan[is2+1]) : 0.5*(3*fSignalScan[is2]-fSignalScan[is2-1]);
	  double weight = ROOT::Math::normal_cdf (sMax, sigma, fSignalScan[is]) -
	    ROOT::Math::normal_cdf (sMin, sigma, fSignalScan[is]);
	  double contrib = pdfNoSys[is] * weight;
	  //  	std::cout << "contrib:" << signalValue[is2]-signalValue[is] << '/' 
	  //  		  << sigma << '/' << weight
	  //  		  << " integral:" << integral
	  //  		  << std::endl;
	  pdfSys [is2] += contrib;
	  integral += contrib;
	}
      }
    }
    for (size_t is = 0; is < nSignalBins; ++is) pdfSys [is] /= integral;

//     cout << endl << "beam structure: " << fLikelihood.signalPdf ()->GetName() << endl;
//     integral = 0;
//      for (size_t is = 0; is < nSignalBins; ++is) {
//        integral += pdfSys [is];
//        if (integral < 0.995 && !(is%5)) {
// 	 cout << "signal:" << fSignalScan[is] << " pdf:" << pdfSys [is] << " integral:" << integral << endl;
//        }
//      }
    
    return pdfSys;
  }
 
MyLikelihood* makeFillStructure (const string& scheme, double lumi, RooRealVar& bx, RooRealVar& logtau) {
  std::vector<double> beam1;
  std::vector<double> beam2;

  makeBeams (scheme, &beam1, &beam2);

  // look for collision bunches
  std::vector<int> collisionBX;
  for (unsigned i = 0; i < beam1.size(); ++i) {
    if (beam1[i]*beam2[i] > 0) 	collisionBX.push_back (i);
  }
  
  std::cout << scheme <<": Colliding bunches: " << collisionBX.size() << std::endl;

//   for (size_t i = 0; i < collisionBX.size(); ++i) {
//     if (!(i % 20)) cout << endl;
//     cout << collisionBX[i] << ' ';
//   }
//   cout << endl;

  char name[1024];
  char title[1024];
  sprintf (name, "signal%s", scheme.c_str());
  sprintf (title, "Signal PDF %s", scheme.c_str());
  RooHCSPInOrbitPdf* signalPDF = new RooHCSPInOrbitPdf(name, title, bx, logtau);
  fillBunchStructure (*signalPDF, beam1, beam2);
  signalPDF->fillCache();
  sprintf (name, "background%s", scheme.c_str());
  sprintf (title, "Flat Background PDF %s", scheme.c_str());
  RooHCSPBkgInOrbitPdf* backgroundPdf = new RooHCSPBkgInOrbitPdf(name, title, bx, signalPDF);
  return new MyLikelihood (signalPDF, backgroundPdf, &bx, lumi);
}

void plotFill (MyLikelihood& fLH) {
  TCanvas* cdata = new TCanvas("data_pdf",
			       "Stopped Gluino fit",1200,800) ;
  RooPlot* frame = fLH.bxVar().frame(BX_IN_ORBIT);
  fLH.signalPdf ()->plotOn(frame, LineColor (kBlue),LineWidth(2),Normalization(500),Name("signal"));
  frame->Draw();
  
  // data points
  int nData = fLH.data().size();
  const int MAX_DATA = 1024;
  double xData [MAX_DATA];
  double yData [MAX_DATA];
  for (int i = 0; i < nData && i < MAX_DATA; ++i) {
    xData[i] = fLH.data()[i];
    yData[i] = 1;
  }
  
  TGraph* gData = new TGraph (nData, xData, yData);
  gData->SetMarkerSize (2);
  gData->SetMarkerStyle (30);
  gData->SetMarkerColor (kBlack);
  TGraph* gData2 = new TGraph (*gData);
  gData2->SetMarkerSize (2);
  gData2->SetMarkerStyle (29);
  gData2->SetMarkerColor (kWhite);

  gData2->Draw("P");
  gData->Draw("P");
 
  TPaveText* blurb = new TPaveText(2000, 1.4, 3500, 1.49);
  // blurb->AddText("CMS Preliminary 2010");
  // blurb->AddText("#int L dt = 12.9 pb^{-1}");
  blurb->AddText("#sqrt{s} = 7 TeV");
  blurb->SetTextFont(42);
  blurb->SetBorderSize(0);
  blurb->SetFillColor(0);
  blurb->SetShadowColor(0);
  blurb->SetTextAlign(12);
  blurb->SetTextSize(0.035);
  // blurb->Draw();
  
  TLegend *leg = 	new TLegend(2000, 1.3, 3500, 1.49,"","");
  leg->SetTextSize(0.035);
  leg->SetBorderSize(0);
  leg->SetTextFont(42);
  leg->SetFillColor(0);
  leg->AddEntry(gData, "CMS Data (2011)", "p");
  leg->AddEntry(frame->findObject("signal"), 
		"Signal PDF (#tau = 1 #mus)", "l");
  leg->Draw();
  
  frame->GetXaxis()->SetTitle ("BX");
  frame->GetYaxis()->SetTitle ("Events");
  frame->SetTitle ("");
  frame->SetMaximum (1.5);
  frame->SetMinimum (0);

  cdata->Update();
  cdata->Print ("plot.pdf");
}
