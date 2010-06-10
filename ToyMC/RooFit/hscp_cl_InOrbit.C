
#ifndef __CINT__
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
#include "RooStats/HypoTestResult.h"
#include "TRandom2.h"
#include "TH2D.h"
#include <string>

#include "RooHCSPInOrbitPdf.h"

namespace {
  void setBunchStructure (RooHCSPInOrbitPdf* fSignal, int fBx, double fLumi) {
    fSignal->setInsensitive (fBx-1);
    fSignal->setInstantLumi (fBx, fLumi);
    fSignal->setInsensitive (fBx+1);
  }
}


// use this order for safety on library loading
using namespace RooFit;

double get95CLLimit (RooAbsData* fData, double fLifetime) {
  int FILLSCHEME = 6333;
  RooAbsReal* rooAbsReal = 0;
  RooFitResult* rooFitResult = 0;
  RooDataSet* rooDataSet = 0;
  TRandom2 rndm;
  std::ofstream outstream ("dump.txt");
  RooMsgService::instance().setGlobalKillBelow (RooFit::WARNING);
  double result = 0;
  // random generator
  TRandom2 random;
  // define model here
  RooRealVar bx("bx", "bx", -0.5, double(BX_IN_ORBIT)-0.5,"bxs");
  // lifetime 
  RooRealVar logtau("logtau","log(lifetime)",log (fLifetime) ,log(1.e-10),log (1.e10));
  logtau.setConstant();
  std::cout << "tau: " << fLifetime << ", logtau: " << logtau.getVal() << std::endl;
  // signal
  RooHCSPInOrbitPdf signal("signal", "Signal Model", bx, logtau);

  if (FILLSCHEME==13888) {
    setBunchStructure (&signal, 1, 100);
    setBunchStructure (&signal, 101, 100);
    setBunchStructure (&signal, 201, 100);
    setBunchStructure (&signal, 301, 100);
    setBunchStructure (&signal, 1786, 100);
    setBunchStructure (&signal, 1886, 100);
    setBunchStructure (&signal, 1986, 100);
    setBunchStructure (&signal, 2086, 100);
    // parasitic collisions
    setBunchStructure (&signal, 894, 0);
    setBunchStructure (&signal, 994, 0);
    setBunchStructure (&signal, 1094, 0);
    setBunchStructure (&signal, 1194, 0);
  }
  else if (FILLSCHEME==6333) {
    setBunchStructure (&signal, 1, 100);
    setBunchStructure (&signal, 20, 100);
    setBunchStructure (&signal, 40, 100);
  }

  signal.fillCache();
  double fractionOffLumi = signal.offLumiFraction ();
   std::cout << "Fraction of OFF LUMI registered signal: " << fractionOffLumi << std::endl;

  // background
  RooHCSPBkgInOrbitPdf background ("background", "flat Bkg Model", bx, &signal);
  // fractions
  int totalEntries = 2;
  std::cout << "==> Events in 'data' sample: " << totalEntries << " <==" << std::endl;

  RooRealVar nsignal("nsignal","# of signal events", 1, 0, totalEntries);
  RooRealVar nbkg("nbkg","# of bkg events", totalEntries, 0, 2*totalEntries);
  // full model
//   RooExtendPdf esig ("esig", "esig", signal, nsignal); 
//   RooExtendPdf ebkg ("ebkg", "ebkg", background, nbkg); 
//   RooAddPdf model("model","Lumi + Flat Bkg", RooArgList (esig, ebkg));

  RooArgList models (signal, background);
  RooArgList scales (nsignal,nbkg);
  RooAddPdf model("model","Lumi + Flat Bkg",models, scales) ; 

  // fill data
  RooDataSet* data = new RooDataSet ("data", "data", bx);
  bx = 2224; data->add (bx);
  //  bx = 2085; data->add (bx);

  // null hypothesis on ref data
  nsignal = 0;
  nbkg = totalEntries;
  rooAbsReal = model.createNLL (*data);
  double referenceNullNll = rooAbsReal->evaluate();
  delete rooAbsReal; rooAbsReal = 0;

  // plots
  std::cout << "plots" << std::endl;
  TCanvas* cdata = new TCanvas("plot","Stopped Gluino fit",400,400) ;
  RooPlot* frame = bx.frame();
  data->plotOn(frame, MarkerColor (kBlack));
  signal.plotOn(frame, LineColor (kBlue));
  background.plotOn(frame, LineColor (kRed));
  frame->Draw();
  cdata->Update();

  return 0.;

  // best fit
  rooFitResult = model.fitTo (*data,Strategy(0),Hesse(kFALSE),Save(kTRUE),PrintLevel(-1));
  double referenceBestNll = rooFitResult->minNll();
  double referenceBestSignal = nsignal.evaluate();
  double referenceBestBkg = nbkg.evaluate();
  delete rooFitResult; rooFitResult = 0;
  std::cout << "null NLL/best NLL/best signal/best bkg: " << referenceNullNll << '/' 
	    << referenceBestNll << '/' << referenceBestSignal << '/' << referenceBestBkg << std::endl;

  nsignal.setConstant();
  nbkg.setConstant();

  int nSigEv = 13;
  double sigmin = 1.;
  double sigmax = 4.;
  double dsig = (sigmax - sigmin) / (nSigEv-1) / 2.;
  int nBkgEv = 17;
  double bkgmin = 0;
  double bkgmax = 4;
  double dbkg = (bkgmax - bkgmin) / (nBkgEv-1) / 2.;

  TH2D* hCL = new TH2D ("hCL", "exclusion CL (%)", nBkgEv, bkgmin-dbkg, bkgmax+dbkg, nSigEv, sigmin-dsig, sigmax+dsig);
  hCL->SetMinimum (70);
  hCL->GetXaxis()->SetTitle("N Bkg");
  hCL->GetYaxis()->SetTitle("N Signal");
  double contours [7] = {80, 85, 90, 93, 95, 98, 99};
  hCL->SetContour(7, contours);

  for (int isig = 0; isig < nSigEv; ++isig) {
    double signal = sigmin + 2*dsig*isig;
    for (int ibkg = 0; ibkg < nBkgEv; ++ibkg) {
      double bkg = bkgmin + 2*dbkg*ibkg;
      if (signal+bkg <= 0.) continue;
      // signal hypothesis on ref data
      nsignal = signal;
      nbkg = bkg;
      rooAbsReal = model.createNLL (*data);
      double referenceHypNll = rooAbsReal->evaluate();
      delete rooAbsReal; rooAbsReal = 0;
      
      //     std::cout << "Reference Null/Hyp-> Signal: " << signal*totalEntries 
      // 	      << "  null/hyp: " << referenceNullNll << '/' << referenceHypNll << " diff=" << referenceHypNll - referenceNullNll
      // 	      << std::endl;
      
      int nBetter = 0;
      int nWorse = 0;
      for (int iToy = 0; iToy < 1000; ++iToy) { 
	nsignal = signal;
	nbkg = bkg;
	int toyEntries = rndm.Poisson (signal+bkg);
	
	rooDataSet = model.generate (bx, toyEntries);
	
	// signal hypothesis on toy data 
	nsignal = signal;
	nbkg = bkg;
	rooAbsReal = model.createNLL (*rooDataSet);
	double toyHypNll = rooAbsReal->evaluate();
	delete rooAbsReal; rooAbsReal = 0;
	
	// null hyp on toy data
	nsignal = 0;
	nbkg = totalEntries;
	rooAbsReal = model.createNLL (*rooDataSet);
	double toyNullNll = rooAbsReal->evaluate();
	delete rooAbsReal; rooAbsReal = 0;

	if ((toyHypNll - toyNullNll) < (referenceHypNll - referenceNullNll)) ++nBetter; // toy is better than ref
	else if ((toyHypNll - toyNullNll) > (referenceHypNll - referenceNullNll)) ++nWorse;
	else {
	  if (rndm.Uniform() < 0.5) ++nBetter; 
	  else ++nWorse;
	}
	
	//       if ((toyNullNll - toyHypNll) < (referenceNullNll - referenceHypNll)) {
	//  	std::cout << "toyHyp-> " << signal*totalEntries << '/' << iToy 
	//  		  << " null/hyp " << toyNullNll << '/' << toyHypNll << " diff=" << toyNullNll-toyHypNll 
	//  		  << " nb/nw " << nBetter << '/' << nWorse
	//  		  << std::endl;
	//       }
	
	delete rooDataSet; rooDataSet = 0;
      }
      std::cout << "ToyMC result: Signal=" << signal
		<< " Background=" << bkg 
		<< ", scaled signal=" << signal*fractionOffLumi
		<< ", better/worse:" << nBetter << '/' << nWorse
		<< ", CL=" << double(nBetter) / (nBetter+nWorse) * 100. << '%'
		<< std::endl;
      outstream << "ToyMC result: Signal=" << signal
		<< " Background=" << bkg 
		<< ", scaled signal=" << signal/fractionOffLumi
		<< ", better/worse:" << nBetter << '/' << nWorse
		<< ", CL=" << double(nBetter) / (nBetter+nWorse) * 100. << '%'
		<< std::endl;
      hCL->Fill (bkg, signal, double(nBetter) / (nBetter+nWorse)*100.);
    }
 }
  
  std::cout << "hCL->Draw()" << std::endl;
 return result;
} 

void run95Limit (double lifetime = 1.e-6) {
  //  double lifetime = 1.e-6;
  // double lifetime = 1.e-6;
  get95CLLimit (0, lifetime);
}

