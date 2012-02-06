#ifndef Cosmics_h
#define Cosmics_h

#include "StoppedHSCP/Analysis/interface/BasicAnalyser.h"

#include "TFile.h"
#include "TChain.h"
#include "TH1D.h"

#include <boost/program_options.hpp>


using namespace std;
namespace po = boost::program_options;

class Cosmics : public BasicAnalyser {

public:
  Cosmics(int argc, char* argv[]) :
    BasicAnalyser(argc, argv) {
    ofilename_ = std::string("Cosmics.root");  /// SET YOUR OUTPUT FILENAME HERE

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
  
  ~Cosmics() { };
  
  virtual void loop();
  
private:

  // YOUR CODE HERE
  TH1D* tracksInCosmics_;

};

#endif


// this is the event loop
void Cosmics::loop() {

  // DO ANY SETUP HERE
  tracksInCosmics_ = new TH1D("hTracksInCosmics", "", 10, 0., 10.);

  reset();
  nextEvent();

  for (unsigned long i=0; i<maxEvents_; ++i, nextEvent()) {

    // occasional print out
    if (i%100000==0) {
      std::cout << "Processing " << i << "th event of " <<maxEvents_<< std::endl;
    }

    // YOUR CODE HERE
    if (event_->jet_N>0 && event_->jetE[0]>50. && event_->jetEta[0]<1.3) {

      if (cuts_.cutNMinusOne(5)) {
	tracksInCosmics_->Fill(event_->track_N);
      }

    }

  }


  // SAVE HISTOGRAMS HERE
  tracksInCosmics_->Write("",TObject::kOverwrite);
  
}



// this is the main program, no need to do anything here
int main(int argc, char* argv[]) {

  // sum of squares error info for histograms
  TH1D::SetDefaultSumw2();

  // create analysis
  Cosmics analyser(argc, argv);

  analyser.setup();

  analyser.cuts().print(std::cout);

  analyser.loop();

  return 0;

}
