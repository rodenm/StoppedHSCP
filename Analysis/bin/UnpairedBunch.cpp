#ifndef UnpairedBunch_h
#define UnpairedBunch_h

#include "StoppedHSCP/Analysis/interface/BasicAnalyser.h"

#include "TMath.h"
#include "TFile.h"
#include "TChain.h"
#include "TH1D.h"

#include <boost/program_options.hpp>


using namespace std;
namespace po = boost::program_options;

class UnpairedBunch : public BasicAnalyser {

public:
  UnpairedBunch(int argc, char* argv[]) :
    BasicAnalyser(argc, argv) {
    ofilename_ = std::string("UnpairedBunch.root");  /// SET YOUR OUTPUT FILENAME HERE

    //    lhcFills_.print(std::cout);

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
  
  ~UnpairedBunch() { };
  
  virtual void loop();
  
private:

  // YOUR CODE HERE
  TH1D* hJetE_;
  TH1D* hJetEta_;
  TH1D* hJetPhi_;
  TH1D* hJetEMF_;

  TH1D* hBX_;

  TH1D* nVtx_;
  TH1D* nTracks_;
  TH1D* nTracksHQ_;
  TH1D* nTracksNoVtx_;
  TH1D* nTracksHQNoVtx_;

};

#endif


// this is the event loop
void UnpairedBunch::loop() {

  // DO ANY SETUP HERE
  std::string pf(outdir_);
  pf+="/unpairedBunchPickEvents.txt";
  std::ofstream pickFile;
  pickFile.open(pf.c_str());


  hJetE_   = new TH1D("hJetE", "Energy", 200, 0., 200.);
  hJetEta_ = new TH1D("hJetEta", "#eta", 72, -1*TMath::Pi(), TMath::Pi());
  hJetPhi_ = new TH1D("hJetPhi", "#phi", 50, -1.5, 1.5);
  hJetEMF_ = new TH1D("hJetEMF", "EMF", 50, 0., 1.);

  hBX_ = new TH1D("hBX", "BX", 3564, 0., 3564.);

  nVtx_ = new TH1D("hNVtx", "N_{vtx}", 10, 0., 10.);
  nTracks_ = new TH1D("hNTracks", "N_{trk}", 100, 0., 100.);
  nTracksHQ_ = new TH1D("hNTracksHQ", "N_{trkHQ}", 100, 0., 100.);
  nTracksNoVtx_ = new TH1D("hNTracksNoVtx", "N_{trk}", 100, 0., 100.);
  nTracksHQNoVtx_ = new TH1D("hNTracksHQNoVtx", "N_{trkHQ}", 100, 0., 100.);

  reset();
  nextEvent();

  for (unsigned long i=0; i<maxEvents_; ++i, nextEvent()) {

    // occasional print out
    if (i%100000==0) {
      std::cout << "Processing " << i << "th event of " <<maxEvents_<< std::endl;
    }

    // YOUR CODE HERE
    unsigned long fill = event_->fill;
    unsigned long run = event_->run;
    unsigned bx = event_->bx;
    int bxWrtBunch = lhcFills_.getBxWrtBunch(fill, bx);
    int bxWrtCollision = lhcFills_.getBxWrtCollision(fill, bx);

    //    std::cout << "Fill " << fill << ", run " << run << ", bx " << bx << ", bxWrtBunch " << lhcFills_.getBxWrtBunch(fill, bx) << ", bxWrtColl " << lhcFills_.getBxWrtCollision(fill, bx) << std::endl;;

    // check this is an unpaired bunch event
    if (bxWrtBunch!=0 || bxWrtCollision==0) continue;

    // check there is a jet in HB with some energy
    if (!(event_->jet_N>0 && event_->jetE[0]>30. && event_->jetEta[0]<1.3)) continue;

    // print out
    pickFile << event_->run << ":" << event_->lb << ":" << event_->id << std::endl;

    //std::cout << "Fill " << fill << ", run " << run << ", bx " << bx << ", bxWrtBunch " << lhcFills_.getBxWrtBunch(fill, bx) << ", bxWrtColl " << lhcFills_.getBxWrtCollision(fill, bx) << std::endl;;
    std::cout << event_->run << ":" << event_->lb << ":" << event_->id << " : BX=" << event_->bx << std::endl;

    double e   = event_->jetE[0];
    double ee  = event_->jetEEm[0];
    double eh  = event_->jetEHad[0];
    double eta = event_->jetEta[0];
    double phi = event_->jetPhi[0];

    hJetE_->Fill(e);
    hJetEta_->Fill(eta);
    hJetPhi_->Fill(phi);
    hJetEMF_->Fill(ee/e);

    hBX_->Fill(event_->bx);

    nVtx_->Fill(event_->vtx_N);

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




  }


  // SAVE HISTOGRAMS HERE
  hJetE_->Write("",TObject::kOverwrite);
  hJetEta_->Write("",TObject::kOverwrite);
  hJetPhi_->Write("",TObject::kOverwrite);

  nVtx_->Write("",TObject::kOverwrite);
  nTracks_->Write("",TObject::kOverwrite);
  nTracksHQ_->Write("",TObject::kOverwrite);
  nTracksNoVtx_->Write("",TObject::kOverwrite);
  nTracksHQNoVtx_->Write("",TObject::kOverwrite);
  
}



// this is the main program, no need to do anything here
int main(int argc, char* argv[]) {

  // sum of squares error info for histograms
  TH1D::SetDefaultSumw2();

  // create analysis
  UnpairedBunch analyser(argc, argv);

  analyser.setup();

  analyser.cuts().print(std::cout);

  analyser.loop();

  return 0;

}
