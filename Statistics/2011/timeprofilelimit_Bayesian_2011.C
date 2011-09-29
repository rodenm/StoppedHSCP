
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
#include "TSystem.h"
#include "TRandom2.h"
#include "TH2D.h"
#include "TPaveText.h"
#include "TLegend.h"
#include <string>
#include <sstream>
#include <fstream>
#include <map>

#include "StoppedHSCP/Analysis/interface/Constants.h"
#include "StoppedHSCP/Analysis/interface/LhcFill.h" 
#include "StoppedHSCP/Analysis/interface/LhcFills.h" 
#include "StoppedHSCP/Statistics/interface/RooHSCPInOrbitPdf.h" 

namespace {
#include "MyLikelyhood.cc"
}

std::vector<double> makeSignalPdf (const std::vector<double>& fSignalScan, 
				   const std::vector<double>& fBackgroundScan,
				   MyLikelihood& fLikelihood,
				   double fRelativeScaleUncertainty);

void plotFill (MyLikelihood& fLH, const string& fName, const string& fDataset, double scale = 1.);

using namespace std;
using namespace RooFit;

double get95BayesianLimit (double fLifetime, bool fPlot = false) {
  string dataset = "1711-1895";
  string eventsFile;
  map <string, double> fillsUsed;
  map <string, double> plotScale;
  fillsUsed["50ns_228b+1small_214_12_180_36bpi8inj"] = 5.022290545;
  fillsUsed["50ns_336b+1small_322_12_288_36bpi11inj"] = 8.040648971;
  fillsUsed["50ns_336b+1small_322_14_288_72bpi7inj"] = 9.626760776;
  fillsUsed["50ns_480b+1small_424_12_468_36bpi15inj"] = 48.660758755;
  fillsUsed["50ns_480b+1small_424_14_468_72bpi11inj"] = 38.176998736;
  fillsUsed["50ns_624b+1small_598_16_576_72bpi11inj_b"] = 17.184344221;
  fillsUsed["50ns_768b+1small_700_16_756_72bpi15inj_b"] = 17.57424307;
  fillsUsed["50ns_768b+1small_700_18_756_108bpi11inj"] = 19.02279022;
  fillsUsed["50ns_912b+1small_874_20_864_108bpi11inj"] = 92.026679661;
  fillsUsed["50ns_912b+1small_874_9_876_108bpi11inj"] = 38.851934101;
  fillsUsed["50ns_1092b+1small_1042_35_1008_108bpi13inj"] = 199.082192572;

  
  if (dataset == "1711-1864") { // 622/pb
    eventsFile = "events_1711_1864.txt";
    fillsUsed["50ns_1092b+1small_1042_35_1008_144bpi13inj"] = 71.226997869;
    fillsUsed["50ns_1104b+1small_1042_35_1008_108bpi_ob"] = 68.448983672;
  }
  else if (dataset == "1711-1895") { // 886/pb
    eventsFile = "events_1711_1895.txt";
    fillsUsed["50ns_1092b+1small_1042_35_1008_144bpi13inj"] = 281.715130005;
    fillsUsed["50ns_1104b+1small_1042_35_1008_108bpi_ob"] = 68.448983672;
    fillsUsed["50ns_1236b+1small_1180_37_1152_144bpi13inj"] = 42.442729595;
  }
  else {
    cout << "Unknown dataset: " << dataset << endl;
    return 0;
  }

  plotScale["50ns_228b+1small_214_12_180_36bpi8inj"] = 214;
  plotScale["50ns_336b+1small_322_12_288_36bpi11inj"] = 322;
  plotScale["50ns_336b+1small_322_14_288_72bpi7inj"] = 336;
  plotScale["50ns_480b+1small_424_12_468_36bpi15inj"] = 350;
  plotScale["50ns_480b+1small_424_14_468_72bpi11inj"] = 350;
  plotScale["50ns_624b+1small_598_16_576_72bpi11inj_b"] = 598;
  plotScale["50ns_768b+1small_700_16_756_72bpi15inj_b"] = 500;
  plotScale["50ns_768b+1small_700_18_756_108bpi11inj"] = 500;
  plotScale["50ns_912b+1small_874_20_864_108bpi11inj"] = 874;
  plotScale["50ns_912b+1small_874_9_876_108bpi11inj"] = 874;
  plotScale["50ns_1092b+1small_1042_35_1008_108bpi13inj"] = 450;
  plotScale["50ns_1092b+1small_1042_35_1008_144bpi13inj"] = 450;
  plotScale["50ns_1104b+1small_1042_35_1008_108bpi_ob"] = 450;
  plotScale["50ns_1236b+1small_1180_37_1152_144bpi13inj"] = 450;


  vector<DataEvent> allEvents = eventsFromLog (eventsFile.c_str());
  RooRealVar bx ("bx", "bx", -0.5, double(BX_IN_ORBIT)-0.5,"bxs");
  RooRealVar logtau ("logtau","log(lifetime)",log (fLifetime) ,log(1.e-10),log (1.e10));
  std::cout << "tau: " << fLifetime << ", logtau: " << logtau.getVal() << std::endl;

  std::vector <MyLikelihood*> fills;
  for (map <string, double>::const_iterator fill = fillsUsed.begin(); fill != fillsUsed.end(); ++fill) {
    const string& fillName = fill->first;
    double lumi = fill->second;
    MyLikelihood* mlh = makeFillStructure (fillName, lumi, allEvents, bx, logtau);
    fills.push_back (mlh);
    if (fPlot && mlh->eventsNumber()) plotFill (*mlh, fillName, dataset, plotScale[fillName]);
  }

// collect statistics
  double allLumi = 0;
  double allLumiEff = 0;
  int totalEvents = 0;
  for (size_t iFill = 0; iFill < fills.size(); ++iFill) {
    MyLikelihood* mylh = fills[iFill];
    allLumi += mylh->getLumi();
    allLumiEff += mylh->getLumi()* mylh->signalPdf()->offLumiFraction ();
    totalEvents += mylh->eventsNumber();
  } 
  int nMax = 1;
  while (ROOT::Math::poisson_cdf (totalEvents, nMax) > 1e-4) nMax *=2;
  
  double maxXsec = nMax / allLumiEff;
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
    while (ROOT::Math::poisson_cdf (nEvents, maxBkg) > 1e-3) maxBkg += 1.;
    // cout << "maxBkg-> " << maxBkg << " events " << nEvents << endl;
    int bkgBins = 500;
    bool flatPrior = false;
    if (flatPrior) {
      for (int i = 0; i < bkgBins; ++i) bkgGrid.push_back ((i+0.5)*maxBkg/bkgBins);
    }
    else { 
      for (int i = 0; i < bkgBins; ++i) bkgGrid.push_back (exp(i)/exp(bkgBins)*maxBkg);
      // for (int i = 0; i < bkgBins; ++i) bkgGrid.push_back (0.001);
    }
//     else { 
//       for (int i = 0; i < bkgBins; ++i) bkgGrid.push_back ((exp(i)/exp(bkgBins))*(exp(i)/exp(bkgBins))*maxBkg);
//       // for (int i = 0; i < bkgBins; ++i) bkgGrid.push_back (0.001);
//     }
    std::vector<double> signalGrid;
    for (int i = 0; i < xSecBins; ++i) signalGrid.push_back (xSecGrid[i]*lumi*timeEfficiency);
    std::vector<double> componentPdf = makeSignalPdf (signalGrid, bkgGrid, *fills[iFill], 0.0806);
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
      if (i < xSecBins/20 || i > xSecBins/2) {
	cout << "WORNING: 95CL precision lost: " << xSecBins/20 << '<' << i << '<' << xSecBins/2 << endl;
      }
      xSec95limit = xSecGrid[i] - (xSecGrid[i]-xSecGrid[i-1])*(sumWith - cl)/(sumWith-sumBefore);
      break;
    }
    sumBefore = sumWith;
  }
  // normalize to effective number of events
  double result = xSec95limit * sumLumi;
  cout << "get95BayesianLimit-> Lifetime: " << fLifetime << " Limit: " << result 
       << ", scaled limit: " << result / allLumi * allLumiEff 
       << ", efficiency scale: " << allLumiEff/allLumi
       << ", xSec*stopping*reco limit: " <<  xSec95limit << " pb"
       << endl; 
  ofstream ("get95BayesianLimit.log", ios_base::app) << fLifetime << ' ' << result 
						     << ' ' << result / allLumi * allLumiEff
						     << ' ' << xSec95limit
						     << endl;
  return result;
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
 

void plotFill (MyLikelihood& fLH, const string& fName, const string& fDataset, double scale) {
  char buffer[1024];
  
  TCanvas* cdata = new TCanvas(fName.c_str(),
			       fName.c_str(),1200,800) ;
  cdata->SetTopMargin (0.1);
  cdata->SetLeftMargin (0.05);
  cdata->SetRightMargin (0.05);

  RooPlot* frame = fLH.bxVar().frame(BX_IN_ORBIT);
  fLH.signalPdf ()->plotOn(frame, LineColor (kBlue),LineWidth(2),Normalization(scale),Name("signal"));
  frame->Draw();
  
  // data points
  int nData = fLH.data().size();
  const int MAX_DATA = 1024;
  double xData [MAX_DATA];
  double yData [MAX_DATA];
  for (int i = 0; i < nData && i < MAX_DATA; ++i) {
    xData[i] = fLH.data()[i];
    yData[i] = 0.05;
  }
  
  TGraph* gData = new TGraph (nData, xData, yData);
  gData->SetMarkerSize (4);
  gData->SetMarkerStyle (30);
  gData->SetMarkerColor (kBlack);
  TGraph* gData2 = new TGraph (*gData);
  gData2->SetMarkerSize (4);
  gData2->SetMarkerStyle (29);
  gData2->SetMarkerColor (kRed);

  gData2->Draw("P");
  gData->Draw("P");
 
  TPaveText* blurb = new TPaveText(0, 1.55, 3500, 1.58);
  
  // blurb->AddText("CMS Preliminary 2010");
  // blurb->AddText("#int L dt = 12.9 pb^{-1}");
  sprintf (buffer, "%s      L_{int} = %3.0f pb^{-1}", fName.c_str(), fLH.getLumi());
  blurb->AddText(buffer);
  blurb->SetTextFont(42);
  blurb->SetBorderSize(0);
  blurb->SetFillColor(0);
  blurb->SetShadowColor(0);
  blurb->SetTextAlign(12);
  blurb->SetTextSize(0.035);
  blurb->Draw();
  
  TPaveText* label2 = new TPaveText(50, 1.3, 2000, 1.45);
  sprintf (buffer, "CMS Preliminary 2011");
  label2->AddText(buffer);
  label2->SetTextFont(42);
  label2->SetBorderSize(0);
  label2->SetFillColor(0);
  label2->SetShadowColor(0);
  label2->SetTextAlign(12);
  label2->SetTextSize(0.035);
  label2->Draw();
  
  TLegend *leg = 	new TLegend(2000, 1.3, 3500, 1.45,"","");
  leg->SetTextSize(0.035);
  leg->SetBorderSize(0);
  leg->SetTextFont(42);
  leg->SetFillColor(0);
  //  sprintf (buffer, "CMS Data, fills %s", fDataset.c_str()); 
  sprintf (buffer, "CMS Data"); 
  leg->AddEntry(gData2, buffer, "p");
  leg->AddEntry(frame->findObject("signal"), 
		"Signal PDF (#tau = 1 #mus)", "l");
  leg->Draw();
  
  frame->GetXaxis()->SetTitle ("BX");
  frame->GetYaxis()->SetTitle ("");
  frame->GetYaxis()->SetLabelSize (0);
  frame->SetTitle ("");
  frame->SetMaximum (1.5);
  frame->SetMinimum (0);

  cdata->Update();
  cdata->Print (string(fName + string(".pdf")).c_str());
  cdata->Print (string(fName + string(".png")).c_str());
}
