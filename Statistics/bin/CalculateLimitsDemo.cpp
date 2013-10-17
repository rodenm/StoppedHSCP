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

#include <math.h>
#include "Math/ProbFuncMathCore.h"
#include "Math/PdfFuncMathCore.h"
#include "Math/QuantFuncMathCore.h"
#include "Math/SpecFuncMathCore.h"

#include "StoppedHSCP/ToyMC/interface/Simulator.h"
#include "StoppedHSCP/ToyMC/interface/Experiment.h"
#include "StoppedHSCP/Statistics/interface/CLsCountingExperiment.h"
#include "StoppedHSCP/Statistics/interface/CL95CMSCountingExperiment.h"


using namespace std;
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
  TH1D* myHistogram_;

};

#endif


// this is the event loop
void CalculateLimitsDemo::run() {

  // DO ANY SETUP HERE
  myHistogram_ = new TH1D("test", "", 10, 0., 10.);

  // YOUR CODE HERE
  myHistogram_->Fill(1);

    
  std::cout << "Hello world!" << std::endl;

  // SAVE HISTOGRAMS HERE
  ofile_->cd();
  myHistogram_->Write("",TObject::kOverwrite);

}



// this is the main program, no need to do anything here
int main(int argc, char* argv[]) {

  // sum of squares error info for histograms
  TH1D::SetDefaultSumw2();

  // create analysis
  //CalculateLimitsDemo analyser(argc, argv);
  //analyser.run();

  std::cout << "\n" << std::endl;

  //CLsCountingExperiment (double fBackground, double fBackgroundSigma, double fScale, double fScaleSigma)
  double expBackground    = 39.;    // bkgd estimate from python script
  double expBackground_e  = 7.8;
  double scaleUncert      = 0.14;
  int nObserved = 10;
  CLsCountingExperiment ce (expBackground, expBackground_e, 1, scaleUncert);

  double limit68cl = ce.cl95limit(nObserved,true);

  std::cout << "nlimit68cl" << std::endl;
  std::cout << limit68cl << std::endl;
  return 0;

}
