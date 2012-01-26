#ifndef BeamGas_h
#define BeamGas_h

#include "StoppedHSCP/Analysis/interface/BasicAnalyser.h"

#include "TFile.h"
#include "TChain.h"
#include "TH1D.h"

#include <boost/program_options.hpp>


using namespace std;
namespace po = boost::program_options;

class BeamGas : public BasicAnalyser {

public:
  BeamGas(int argc, char* argv[]) :
    BasicAnalyser(argc, argv) {
    ofilename_ = std::string("BeamGas.root");  /// SET YOUR OUTPUT FILENAME HERE

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
  
  ~BeamGas() { };
  
  virtual void loop();
  
private:

  // YOUR CODE HERE
  TH1D* nTracks_;
  TH1D* nTracksHQ_;

  TH1D* nTracksNoVtx_;
  TH1D* nTracksHQNoVtx_;

  TH1D* trackPFraction_;

};

#endif


// this is the event loop
void BeamGas::loop() {

  // DO ANY SETUP HERE
  nTracks_ = new TH1D("hNTracks", "N_{trk}", 100, 0., 100.);
  nTracksHQ_ = new TH1D("hNTracksHQ", "N_{trkHQ}", 100, 0., 100.);

  nTracksNoVtx_ = new TH1D("hNTracksNoVtx", "N_{trk}", 100, 0., 100.);
  nTracksHQNoVtx_ = new TH1D("hNTracksHQNoVtx", "N_{trkHQ}", 100, 0., 100.);

  trackPFraction_ = new TH1D("hTrackPFraction", "", 100, 0., 2.);

  reset();
  nextEvent();

  for (unsigned long i=0; i<maxEvents_; ++i, nextEvent()) {

    // occasional print out
    if (i%100000==0) {
      std::cout << "Processing " << i << "th event of " <<maxEvents_<< std::endl;
    }

    // YOUR CODE HERE
    if (event_->jet_N>0 && event_->jetE[0]>50. && event_->jetEta[0]<1.3) {

      // count tracks of different types
      unsigned nTracks(0), nTracksHQ(0);
      for (unsigned j=0; j<event_->track_N; ++j) {
	nTracks++;
      	if (event_->trackQuality[0] == 1) nTracksHQ++;
      }
      
      nTracks_->Fill(nTracks);
      nTracksHQ_->Fill(nTracksHQ);

      if (event_->vtx_N == 0) {
	nTracksNoVtx_->Fill(nTracks);
	nTracksHQNoVtx_->Fill(nTracksHQ);
      }

      // leading jet/track ratio
      if (event_->track_N>0) {
	trackPFraction_->Fill(event_->trackP[0]/event_->jetE[0]);
      }

    }

  }


  // SAVE HISTOGRAMS HERE
  nTracks_->Write("",TObject::kOverwrite);
  nTracksHQ_->Write("",TObject::kOverwrite);
  nTracksNoVtx_->Write("",TObject::kOverwrite);
  nTracksHQNoVtx_->Write("",TObject::kOverwrite);
  trackPFraction_->Write("",TObject::kOverwrite);
  
}



// this is the main program, no need to do anything here
int main(int argc, char* argv[]) {

  // sum of squares error info for histograms
  TH1D::SetDefaultSumw2();

  // create analysis
  BeamGas analyser(argc, argv);

  analyser.setup();

  analyser.cuts().print(std::cout);

  analyser.loop();

  return 0;

}
