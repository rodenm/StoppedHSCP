#ifndef CalculateLimitsDemo_h
#define CalculateLimitsDemo_h

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sys/stat.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <boost/program_options.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/filesystem.hpp>

#include "TFile.h"
#include "TChain.h"
#include "TH1D.h"
#include "TRandom2.h"
#include "TCanvas.h"

#include <math.h>
#include "Math/ProbFuncMathCore.h"
#include "Math/PdfFuncMathCore.h"
#include "Math/QuantFuncMathCore.h"
#include "Math/SpecFuncMathCore.h"

using namespace std;

namespace {
  
   // Cousins-Highland approach
  double upperLimitCountingCL (double signal, int nObserved, double bkgMean, double bkgSigma, double scaleSigma) {

    TH1D hCLb = TH1D("hCLb", ";nEvents", 20, 0., 1.);
    TH1D hCLsb = TH1D("hCLsb", ";nEvents", 20, 0., 1.);

    TRandom2 rndm;
    int nToys = 1000;
    double CLb = 0;
    double CLsb = 0;
    for (int iToy = 0; iToy < nToys; ++iToy) {
      double bkg = rndm.Gaus (bkgMean, bkgSigma);
      while (bkg < 0) bkg = rndm.Gaus (bkgMean, bkgSigma);
      double scale = rndm.Gaus (1., scaleSigma);
      while (scale <= 0) scale = rndm.Gaus (1., scaleSigma);
      double tCLb = ROOT::Math::poisson_cdf (nObserved, bkg); 
      double tCLsb = ROOT::Math::poisson_cdf (nObserved, bkg + signal * scale);

      hCLb.Fill(tCLb);
      hCLsb.Fill(tCLsb);
      
      CLb  += tCLb;
      CLsb += tCLsb;
    }

    TCanvas c1("c1");
    hCLb.Draw();
    hCLb.SetStats(0);
    hCLsb.SetLineColor(kRed);
    hCLsb.Draw("same");
    c1.SaveAs("68clLimit.pdf");
    
    //std::cout  << "\n\nlimit = " << 1-CLsb/CLb << "\n" << std::endl;

    return 1-CLsb/CLb;
  }
}

namespace po = boost::program_options;

class CalculateLimitsDemo {

public:
  CalculateLimitsDemo(int argc, char* argv[]) {
    ofilename_ = std::string("CalculateLimitsDemo.root");  /// SET YOUR OUTPUT FILENAME HERE

    // get options
    po::options_description desc("Allowed options");
    
    desc.add_options()
      ("help,h", "Display this message")
      ("outdir,o", po::value<std::string>(), "Output directory")
      ("num,n", po::value<unsigned long long>()->default_value(0), "Number of events to process");
  
    po::variables_map vm;
    po::store(po::command_line_parser(argc, argv).options(desc).allow_unregistered().run(), vm);  
    po::notify(vm);
  
    // help
    if (vm.count("help")) {
      std::cout << desc << std::endl;
      std::exit(1);
    }
  
    // set output directory & create it if it doesn't exist already
    if (vm.count("outdir")) {
      outdir_ = vm["outdir"].as<std::string>();

      boost::filesystem::path opath(outdir_);
      if (!exists(opath)) {
	std::cout << "Creating output directory : " << outdir_ << std::endl;
	boost::filesystem::create_directory(opath);
      }
    }
  
    // print some info & catch some error conditions
    std::cout << "Caclulate Limits Demo" << std::endl;

    // output directory
    if (outdir_ == std::string("")) {
      std::cout <<"LimitsDemo Error : no output directory specified!"<<std::endl;
      std::exit(-1);
    }

    // set up the output file
    ofile_ = new TFile((outdir_+std::string("/")+ofilename_).c_str(), "RECREATE");
    std::cout << "Output file        : " << ofile_->GetName() << std::endl;
    
    if (ofile_->IsZombie()) {
      std::exit(2);
    }

  }
  
  ~CalculateLimitsDemo() { 

    ofile_->Close();
    delete ofile_;

  };
  
  virtual void run();

  // input file
  std::string paramfile_;

  
private:

  // output file
  std::string outdir_;
  std::string ofilename_;
  TFile* ofile_;


  // YOUR CODE HERE
  TH1D* hbkg_;
  TH1D* hsig_;
  TH1D* hnoise_;

};

#endif


// this is the event loop
void CalculateLimitsDemo::run() {

  // DO ANY SETUP HERE
  hbkg_ = new TH1D("bkg", ";nEvents", 20, -10., 10.);
  hsig_ = new TH1D("sig", ";nEvents", 20, -10., 10.);
  hnoise_ = new TH1D("noise", ";nEvents", 20, -10., 10.);


  // SET PARAMETERS
  double targetCL = 0.68;  
  double expBackground   = 4.83;    // cosmic background estimate from CosmicBackground.txt: 4.83356 +/-3.58263
  double expBackground_e = 3.58;
  double scaleUncert     = 0.155;
  int nObserved = 2;

  // CALCULATE CENTRAL VALUE
  double sMin = 0;
  double sMax = nObserved > 0 ? 2.5*nObserved : 2.5;
  while (1) {
    double cls = upperLimitCountingCL(sMax, nObserved, expBackground, expBackground_e, scaleUncert);   
    if (cls > targetCL) break;
    sMax *=2;
  }
  
  // CALCULATE LIMIT
  double sThis = 0;
  while (1) {
    sThis = 0.5*(sMin+sMax);
    double cls = upperLimitCountingCL(sThis, nObserved, expBackground, expBackground_e, scaleUncert);
    //std::cout << "upperLimitCountingCLS95-> min/max/sThis: " << sMin << '/' << sMax << '/' << sThis 
    //  	      << " CLS:" << cls << std::endl; 
    if ((fabs(cls - targetCL) < 1e-5) || (0.5*(sMax-sMin)/(sMax+sMin) < 1e-4)) break;
    if (cls > targetCL) sMax = sThis;
    else sMin = sThis;
  }

  std::cout << "68% limit value: " << sThis << std::endl;

  // Make plots
  TRandom2 rndm;
  for (int iToy = 0; iToy < 10000; ++iToy) {
    double bkg = rndm.PoissonD(rndm.Gaus(expBackground, expBackground_e));
    double sig = rndm.PoissonD(nObserved);
    double noise = sig - bkg;

    hbkg_->Fill(bkg);
    hsig_->Fill(sig);
    hnoise_->Fill(noise);
  }

  TCanvas c1("c1");
  hsig_->Draw();
  hbkg_->SetStats(0);
  hbkg_->SetLineColor(kRed);
  hbkg_->Draw("same");
  hnoise_->SetLineColor(kBlack);
  hnoise_->Draw("same");
  c1.SaveAs("cosmicNoiseDist.pdf");

  // SAVE HISTOGRAMS HERE
  ofile_->cd();
  hbkg_->Write("",TObject::kOverwrite);
  hsig_->Write("",TObject::kOverwrite);
  hnoise_->Write("",TObject::kOverwrite);

}



// this is the main program, no need to do anything here
int main(int argc, char* argv[]) {

  std::cout << "\n" << std::endl;

  CalculateLimitsDemo limits(argc, argv);
  limits.run();
  
  return 0;

}
