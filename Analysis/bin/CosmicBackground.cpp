#ifndef CosmicBackground_h
#define CosmicBackground_h

#include "StoppedHSCP/Analysis/interface/BasicAnalyser.h"

#include "TFile.h"
#include "TChain.h"
#include "TH1D.h"
#include "TH2D.h"

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
  TH1D* hNMinusOne_frac_;

  TH2D* hBackground_DTRPC_;
  TH1D* hBackground_frac_;

};

#endif


// this is the event loop
void CosmicBackground::loop() {

  // DO ANY SETUP HERE
  hNMinusOne_DTRPC_ = new TH2D("NMinusOne_DTRPC", ";nDT;nRPC", 15, 0., 30., 15., 0, 30.);
  hNMinusOne_frac_ = new TH1D("NMinusOne_frac",";frac;",20, 0, 10);

  hBackground_DTRPC_ = new TH2D("Background_DTRPC", ";nDT;nRPC", 15, 0., 30., 15., 0, 30.);
  hBackground_frac_ = new TH1D("Background_frac",";frac;",20, 0, 10);


  TH2D* hIneff_DTRPC = (TH2D*)inFile_->Get("ineffciencyDTbyRPC"); 
  TH1D* hIneff_frac = (TH1D*)inFile_->Get("ineffciencyFrac"); 
  hIneff_DTRPC->GetEntries();
  hIneff_frac->GetEntries();

  reset();
  nextEvent();

  for (unsigned long i=0; i<maxEvents_; ++i, nextEvent()) {

    // occasional print out
    if (i%100000==0) {
      std::cout << "Processing " << i << "th event of " <<maxEvents_<< std::endl;
    }

    // Calculte the fraction of inner and outer DT hits
    float outerDT = 0.0000001;
    float innerDT = 0;
    for (unsigned idt = 0; idt<event_->DTSegment_N; idt++) {
      if (event_->DTSegR[idt] > 560) outerDT++;
      else innerDT++;
    }
    double frac = innerDT/outerDT;

    // YOUR CODE HERE
    if (cuts_.cutNMinusOne(5) && !cuts_.cutN(5) && frac < 2. && event_->DTSegment_N > 0) {
      if (event_->DTSegment_N < 2 && event_->rpcHit_N < 3){
	std::cout << "what?: " << event_->DTSegment_N << " " << event_->rpcHit_N
		  <<std::endl;
      }
      hNMinusOne_DTRPC_->Fill(event_->DTSegment_N,event_->rpcHit_N);
      hNMinusOne_frac_->Fill(frac);
    }

  }


  hBackground_DTRPC_->Multiply(hIneff_DTRPC, hNMinusOne_DTRPC_);
  hBackground_frac_->Multiply(hIneff_frac, hNMinusOne_frac_);

  std::cout << hBackground_DTRPC_->GetNbinsX() << "  "<< hBackground_DTRPC_->GetNbinsY() <<std::endl;
  std::cout << hBackground_frac_->GetNbinsX() << std::endl;
  double errorDT = 0;
  double ineffDT = hBackground_DTRPC_->IntegralAndError(1,hBackground_DTRPC_->GetNbinsX(),
							1,hBackground_DTRPC_->GetNbinsY(),
							errorDT);
  double errorFrac = 0;
  double ineffFrac = hBackground_frac_->IntegralAndError(1,hBackground_frac_->GetNbinsX(),errorFrac);

  std::cout << "N-1 entries: " << hNMinusOne_DTRPC_->GetEntries() << std::endl; 
  std::cout << "DT by RPC background: " 
	    << ineffDT << " +/- " << errorDT
	    << std::endl;
  std::cout << "Frac background: " 
	    << ineffFrac << " +/-" << errorFrac
	    << std::endl;

  // SAVE HISTOGRAMS HERE
  hNMinusOne_DTRPC_->Write("",TObject::kOverwrite);
  hBackground_DTRPC_->Write("",TObject::kOverwrite);
  
  hBackground_frac_->Write("",TObject::kOverwrite);
  hNMinusOne_frac_->Write("",TObject::kOverwrite);

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
