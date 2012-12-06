#ifndef Noise_h
#define Noise_h

#include "StoppedHSCP/Analysis/interface/BasicAnalyser.h"

#include "TFile.h"
#include "TChain.h"
#include "TH1D.h"

#include <boost/program_options.hpp>


using namespace std;
namespace po = boost::program_options;

class Noise : public BasicAnalyser {

public:
  Noise(int argc, char* argv[]) :
    BasicAnalyser(argc, argv) {
    ofilename_ = std::string("Noise.root");  /// SET YOUR OUTPUT FILENAME HERE

    // get options
    po::options_description desc("Custom options");
    po::positional_options_description poptd;

    desc.add_options()
      ("special,s", po::value<std::string>(), "Special option");

    po::variables_map vm;
    po::store(po::command_line_parser(argc, argv).options(desc).allow_unregistered().run(), vm);  
    po::notify(vm);
    
    // get my custom option
    if (vm.count("special")) {
      std::string special = vm["special"].as<std::string>();
      std::cout << "Command line argument : " << special << std::endl;
    }

  }
  
  ~Noise() { };
  
  virtual void loop();
  
private:

  // YOUR CODE HERE
  TH1D* hJetE_;
  TH1D* hJetEdm_;
  TH1D* hJetEstopped_;

};

#endif


// this is the event loop
void Noise::loop() {

  // DO ANY SETUP HERE
  hJetE_ = new TH1D("jetE", "", 1000, 0., 1000.);
  hJetEdm_ = new TH1D("jetEdm", "", 1000, 0., 1000.);
  hJetEstopped_ = new TH1D("jetEstopped", "", 1000, 0., 1000.);

  reset();
  nextEvent();

  for (unsigned long i=0; i<maxEvents_; ++i, nextEvent()) {

    // occasional print out
    if (i%100000==0) {
      std::cout << "Processing " << i << "th event of " <<maxEvents_<< std::endl;
    }

    // calculate livetime
    livetime_.newEvent(event_->fill, event_->run, event_->lb);


    // YOUR CODE HERE
    if (event_->jet_N == 0) continue;
    hJetE_->Fill(event_->jetE[0]);
    if (event_->hltDelayedMuonControl && !event_->hltJetE50NoBptx3BXNoHalo)
      hJetEdm_->Fill(event_->jetE[0]);
    if (event_->hltJetE50NoBptx3BXNoHalo)
      hJetEstopped_->Fill(event_->jetE[0]);
  }


  // SAVE HISTOGRAMS HERE
  hJetE_->Write("",TObject::kOverwrite);
  hJetEdm_->Write("",TObject::kOverwrite);
  hJetEstopped_->Write("",TObject::kOverwrite);

}



// this is the main program, no need to do anything here
int main(int argc, char* argv[]) {

  // sum of squares error info for histograms
  TH1D::SetDefaultSumw2();

  // create analysis
  Noise analyser(argc, argv);

  analyser.setup();

  analyser.cuts().print(std::cout);

  analyser.loop();

  return 0;

}
