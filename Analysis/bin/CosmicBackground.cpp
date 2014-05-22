#ifndef CosmicBackground_h
#define CosmicBackground_h

#include "StoppedHSCP/Analysis/interface/BasicAnalyser.h"

#include "TFile.h"
#include "TChain.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TRandom2.h"

#include <boost/program_options.hpp>


using namespace std;
namespace po = boost::program_options;

class CosmicBackground : public BasicAnalyser {

public:
  CosmicBackground(int argc, char* argv[]) :
    BasicAnalyser(argc, argv) {
    ofilename_ = std::string("CosmicBackground.root");  /// SET YOUR OUTPUT FILENAME HERE

     // get options
    po::options_description desc("Custom options");
    po::positional_options_description poptd;

    desc.add_options()
      ("ineffPlots",po::value<std::string>(),"ROOT file produced by cosmicInefficiency");

    po::variables_map vm;
    po::store(po::command_line_parser(argc, argv).options(desc).allow_unregistered().run(), vm);  
    po::notify(vm);
    
    // get my custom option
    if (vm.count("ineffPlots")) {
      std::string inFileName = vm["ineffPlots"].as<std::string>();
      inFile_ = new TFile(inFileName.c_str(),"READ");
      std::cout << "Inefficiency Plots : " << inFileName << std::endl;
    } else {
      std::cout << "--ineffPlots is a required argument" << std::endl;
      exit(3);
    }
  }
  
  ~CosmicBackground() { };
  
  virtual void loop();
  
private:

  // YOUR CODE HERE
  TFile* inFile_;

  TH2D* hNMinusOne_DTRPC_;
  TH2D* hNMinusOne_smeared_;

  TH2D* hBackground_DTRPC_;
  TH2D* hBackground_smeared_;
  TH2D* hBackground_uncert_;

};

#endif


// this is the event loop
void CosmicBackground::loop() {

  // DO ANY SETUP HERE
  hNMinusOne_DTRPC_ = new TH2D("NMinusOne_DTRPC", ";nDT;nRPC", 15, 0., 30., 15., 0, 30.);
  hNMinusOne_smeared_ = new TH2D("NMinusOne_smeared",";nDT;nRPC", 15, 0., 30., 15., 0, 30.);

  hBackground_DTRPC_ = new TH2D("Background_DTRPC", ";nDT;nRPC", 15, 0., 30., 15., 0, 30.);
  hBackground_smeared_ = new TH2D("Background_smeared",";nDT;nRPC", 15, 0., 30., 15., 0, 30.);
  hBackground_uncert_ = new TH2D("Background_uncert",";nDT;nRPC", 15, 0., 30., 15., 0, 30.);


  TH2D* hIneff_DTRPC = (TH2D*)inFile_->Get("ineffciencyDTbyRPC"); 
  TH2D* hIneff_smeared = (TH2D*)inFile_->Get("ineffciencyDTbyRPC"); 
  TH2D* hIneff_uncert = (TH2D*)inFile_->Get("ineffciencyDTbyRPC_uncert"); 
  hIneff_DTRPC->GetEntries();
  hIneff_smeared->GetEntries();
  double q = hIneff_uncert->GetEntries();
  std::cout << q << std::endl;
  reset();
  nextEvent();

  for (unsigned long i=0; i<maxEvents_; ++i, nextEvent()) {

    // occasional print out
    if (i%100000==0) {
      std::cout << "Processing " << i << "th event of " <<maxEvents_<< std::endl;
    }
    //if (i==300000) break;


    // Calculte the smearedtion of inner and outer DT hits
    float outerDT = 0.0000001;
    float innerDT = 0;
    for (unsigned idt = 0; idt<event_->DTSegment_N; idt++) {
      if (event_->DTSegR[idt] > 560) outerDT++;
      else innerDT++;
    }
    double frac = innerDT/outerDT;

    if (cuts_.cutNMinusOne(5) && !cuts_.cutN(5) && frac < 2. && event_->DTSegment_N > 0) {
      if (event_->DTSegment_N < 2 && event_->rpcHit_N < 3){
	//std::cout << "what?: " << event_->DTSegment_N << " " << event_->rpcHit_N
	//	  <<std::endl;
      }
      double dtN = event_->DTSegment_N;
      double rpcN = event_->rpcHit_N;
      hNMinusOne_DTRPC_->Fill(dtN, rpcN);
      hNMinusOne_smeared_->Fill(dtN, rpcN);
    }
  }

  // Produce a version of the N-1 histogram with empty bins being interpolated from the 4 surrounding bins
  // Hot spots:
  // y = ny, x = nx
  // y = 0,  x = nx ----------> Don't start at y=0
  // y = ny, x = 0
  // x = 0,  y = ny
  
  int nx = hNMinusOne_smeared_->GetNbinsX();
  int ny = hNMinusOne_smeared_->GetNbinsY();
  //for (int y = 0; y < ny+1; y++) {
  //for (int x = 0; x < nx+1; x++) {
  for (int x = nx; x >= 0; x--) {
    for (int y = 0; y <= ny; y++) {
      if (hNMinusOne_smeared_->GetBinContent(x,y) == 0.) {
	//double value = hNMinusOne_smeared_->Interpolate(x,y); // Interpolate works super weird
	double z = 0.;
	if (x == 0){
	  z = hNMinusOne_smeared_->GetBinContent(x+1,y)/2.;
	} else if (x == nx) {
	  z = hNMinusOne_smeared_->GetBinContent(x-1,y)/2.;
	} else {
	  z = (hNMinusOne_smeared_->GetBinContent(x-1,y) + hNMinusOne_smeared_->GetBinContent(x+1,y))/2.;
	}
	hNMinusOne_smeared_->SetBinContent(x,y,z);
      }
    }
  }
  

  // Smooth() works in a much more reasonable manner than Interpolate()
  // hNMinusOne_smeared_->Smooth(1,"k3a");

  hBackground_DTRPC_->Multiply(hIneff_DTRPC, hNMinusOne_DTRPC_);
  hBackground_smeared_->Multiply(hIneff_smeared, hNMinusOne_smeared_);
  hBackground_uncert_->Multiply(hIneff_uncert, hNMinusOne_smeared_);

  double errorDT = 0;
  double ineffDT = hBackground_DTRPC_->IntegralAndError(1,hBackground_DTRPC_->GetNbinsX(),
							1,hBackground_DTRPC_->GetNbinsY(),
							errorDT);
  double errorSmeared = 0;
  double ineffSmeared = hBackground_smeared_->IntegralAndError(1,hBackground_smeared_->GetNbinsX(),
							       1,hBackground_smeared_->GetNbinsY(),
							       errorSmeared);
  double errorUncert = 0;
  double ineffUncert = hBackground_uncert_->IntegralAndError(1,hBackground_uncert_->GetNbinsX(),
							     1,hBackground_uncert_->GetNbinsY(),
							     errorUncert);

  std::cout << "N-1 entries: " << hNMinusOne_DTRPC_->GetEntries() << std::endl; 
  std::cout << "DT by RPC background: " 
	    << ineffDT << " +/- " << errorDT
	    << std::endl;
  std::cout << "Smeared background: " 
	    << ineffSmeared << " +/-" << errorSmeared
	    << std::endl;
  std::cout << "Uncertainty background: " 
	    << ineffUncert << " +/-" << errorUncert
	    << std::endl;

  // SAVE HISTOGRAMS HERE
  hNMinusOne_DTRPC_->Write("",TObject::kOverwrite);
  hBackground_DTRPC_->Write("",TObject::kOverwrite);
  
  hBackground_smeared_->Write("",TObject::kOverwrite);
  hNMinusOne_smeared_->Write("",TObject::kOverwrite);

  hBackground_uncert_->Write("",TObject::kOverwrite);

}



// this is the main program, no need to do anything here
int main(int argc, char* argv[]) {

  // sum of squares error info for histograms
  TH1D::SetDefaultSumw2();

  // create analysis
  CosmicBackground analyser(argc, argv);

  analyser.setup();

  analyser.cuts().print(std::cout);

  analyser.loop();

  return 0;

}
