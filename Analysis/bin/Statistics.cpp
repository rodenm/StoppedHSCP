
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
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>

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


std::vector<unsigned> getCollisionBXs(std::string filename, unsigned run) {

  std::vector<unsigned> bxs;
  std::ifstream bxfile(filename.c_str());

  while (!bxfile.eof()) {
    std::string line;
    getline(bxfile, line);
    std::vector<std::string> strs;
    boost::split(strs, line, boost::is_any_of(","));

    unsigned r=atoi(strs.at(0).c_str());
    if (r==run) {
      for (unsigned i=1; i<strs.size(); ++i) {
	bxs.push_back(atoi(strs.at(i).c_str()));
      }
    }
  }

  return bxs;
}


std::vector<unsigned> getMaskedBXs(std::string filename, unsigned run) {

  std::vector<unsigned> bxs;
  std::ifstream file(filename.c_str());

  while (!file.eof()) {
    std::string line;
    getline(file, line);
    std::vector<std::string> strs;
    boost::split(strs, line, boost::is_any_of(","));

    unsigned r=atoi(strs.at(0).c_str());
    if (r==run) {
      for (unsigned i=1; i<strs.size(); ++i) {
	bxs.push_back(atoi(strs.at(i).c_str()));
      }
    }
  }

  return bxs;

}



std::vector<unsigned> getEventBXs(std::string filename, unsigned run) {

  std::vector<unsigned> bxs;
  std::ifstream file(filename.c_str());

  while (!file.eof()) {
    std::string line;
    getline(file, line);
    std::vector<std::string> strs;
    boost::split(strs, line, boost::is_any_of(","));

    if ((int)run==atoi(strs.at(0).c_str())) {
      unsigned bx = atoi(strs.at(3).c_str());
      bxs.push_back(bx);
      //      std::cout << "Event in run " << run << " at BX " << bx << std::endl;
    }
  }

  return bxs;

}


int main(int argc, char* argv[]) {

  // other params
  int nToys=500;


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

  // filenames
  std::string evFile(dataset);
  evFile+=std::string("/eventInfo.log");

  std::string collFile("collisions.csv");
  std::string maskFile("bx_mask.csv");

  // get background numbers
  // TODO - open BG files and get these numbers
  int bgCounts = 20;
  double bgLivetime = 174687.0;
  double bgRate = ((double) bgCounts) / bgLivetime;
  double bgRateStatErr = sqrt( (double) bgCounts) / bgLivetime;


  // time bins in units of BX
  unsigned b[]={10, 100, 1000};
  std::vector<unsigned> bins(b, b+3);

  // runs
  unsigned r[]={136035,136066,136080,136082,136087,136088,136097,136098,136100,136119};
  std::vector<unsigned> runs(r, r+10);

  double lt[]={6002.,25739.,1681.,11608.,5862.,5605.,1705.,256.,2195.,840.};
  std::vector<double> runLivetime(lt, lt+10);

  // results
  std::vector<double> livetimePerBin;
  std::vector<double> bgExpPerBin;
  std::vector<double> bgStatErrPerBin;
  std::vector<unsigned> nObsPerBin;

  // loop over time bins
  for (unsigned ib=0; ib<bins.size(); ++ib) {
    unsigned binsize=bins.at(ib);

    std::cout << "Bin size " << binsize << std::endl;

    unsigned nObservedTotal=0;
    double livetimeTotal=0.;

    // loop over runs (different BX structure for each run)
    for (unsigned ir=0; ir<runs.size(); ++ir) {
      unsigned run=runs.at(ir);
      unsigned runLength=runLivetime.at(ir);

      std::cout << "Run " << run << " length " << runLength << " ";

      // read collisions file
      std::vector<unsigned> collisions=getCollisionBXs(collFile, run);            

      // read masks from file
      std::vector<unsigned> masks=getMaskedBXs(maskFile, run);            

      // read events file
      std::string evFile(dataset);
      evFile+=std::string("/eventInfo.log");
      std::vector<unsigned> events=getEventBXs(evFile, run);      


      // sum length of windows within orbit
      unsigned liveBXsInOrbit=0;
      for (unsigned ic=0; ic<collisions.size(); ++ic) {
	  unsigned collBx = collisions.at(ic);
	  unsigned windowEnd=collBx+binsize;
	  if (ic<collisions.size()-1) {
	    if (windowEnd > collisions.at(ic+1)) windowEnd = collisions.at(ic+1)-1;
	  }
	  else {
	    if (windowEnd > 3564) windowEnd = 3564;
	  }
	  //	  std::cout << "Coll bx=" << collBx << " end=" << windowEnd << std::endl;
	  liveBXsInOrbit += (windowEnd-(collBx+1));
      }

      std::cout << "Live BXs " << liveBXsInOrbit << std::endl;
      livetimeTotal += (double)liveBXsInOrbit * runLength / 3564.;


      // n observed
      unsigned nObs=0;
      for (unsigned ie=0; ie<events.size(); ++ie) {
	for (unsigned ic=0; ic<collisions.size(); ++ic) {
	  unsigned evBx = events.at(ie);
	  unsigned collBx = collisions.at(ic);
	  unsigned windowEnd=collBx+binsize;

	  if (ic<collisions.size()-1) {
	    if (windowEnd > collisions.at(ic+1)) windowEnd = collisions.at(ic+1);
	  }
	  else {
	    if (windowEnd > 3564) windowEnd = 3564;
	  }

	  // is event in window?
	  if (evBx > collBx+1 && evBx < windowEnd) {
	    nObs++;
	  }

	}
      }

      std::cout << "N obs " << nObs << std::endl;
      nObservedTotal += nObs;

    } 

    std::cout << std::endl;

    livetimePerBin.push_back( livetimeTotal );
    bgExpPerBin.push_back( livetimeTotal * bgRate );
    bgStatErrPerBin.push_back( livetimeTotal * bgRateStatErr );
    nObsPerBin.push_back( nObservedTotal );

  }

  // calculate 95CL limits
  std::vector<double> upperLimit95CLPerBin;
  for (unsigned ib=0; ib<bins.size(); ++ib) {
    unsigned nobs=nObsPerBin.at(ib);
    double bg=bgExpPerBin.at(ib);
    double bgErr=bgStatErrPerBin.at(ib);
    double cl=0.;
    if (nobs>0) {
      cl = countingExperiment95CLUpperLimit(nobs, bg, bgErr, nToys);
    }
    upperLimit95CLPerBin.push_back(cl);
  }

  // do it without time windows the old way (!)
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

  // expected background
  double bgExp = (bgRate * livetime);
  double bgStatErr = bgRateStatErr * livetime;

  // 95% CL
  double cl95 = 0.;
  cl95 = countingExperiment95CLUpperLimit (nObserved, bgExp, bgStatErr, nToys);



  // dump results

  std::cout << std::endl;
  std::cout << "Using background measurement" << std::endl;
  std::cout << "Livetime         : " << bgLivetime << std::endl;
  std::cout << "Counts           : " << bgCounts << std::endl;
  std::cout << "Rate             : " << bgRate << " +/- " << bgRateStatErr << std::endl;
  std::cout << std::endl;

  std::cout << "No time window" << std::endl;
  std::cout << "Live time         : " << livetime << std::endl;
  std::cout << "N exp BG          : " << bgExp << std::endl;
  std::cout << "Err exp BG        : " << bgStatErr << std::endl;
  std::cout << "N observed        : " << nObserved << std::endl;
  std::cout << "95 CL upper limit : " << cl95 << std::endl;

  // time bin results
  std::cout << std::endl;
  for (unsigned ib=0; ib<bins.size(); ++ib) {
    std::cout << "Time window size : " << bins.at(ib) * 0.025 << " mu s " << std::endl;
    std::cout << "Live time        : " << livetimePerBin.at(ib) << std::endl;
    std::cout << "N exp BG         : " << bgExpPerBin.at(ib) << std::endl;
    std::cout << "Err exp BG       : " << bgStatErrPerBin.at(ib) << std::endl;
    std::cout << "N obs            : " << nObsPerBin.at(ib) << std::endl;
    std::cout << "95CL upper limit : " << upperLimit95CLPerBin.at(ib) << std::endl;
  }
  std::cout << std::endl;




  // 


  return 0;

}
