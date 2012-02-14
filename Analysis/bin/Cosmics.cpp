#ifndef Cosmics_h
#define Cosmics_h

#include "StoppedHSCP/Analysis/interface/BasicAnalyser.h"

#include "StoppedHSCP/Analysis/interface/Livetime.h"
#include "StoppedHSCP/Ntuples/interface/Constants.h"

#include "TMath.h"
#include "TFile.h"
#include "TChain.h"
#include "TH1D.h"

#include <cmath>
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

  // histograms
  TH1D* tracksInCosmics_;

  TH1D* etaMuon_;
  TH1D* phiMuon_;
  TH1D* etaDT_;
  TH1D* phiDT_;
  TH1D* etaRPC_;
  TH1D* phiRPC_;
  TH1D* etaNM1_;
  TH1D* phiNM1_;

};

#endif


// this is the event loop
void Cosmics::loop() {

  // DO ANY SETUP HERE
  int nMinusOneCount(0), nMinus1AbortGap(0);
  int nMuon(0), nRPC(0), nDT(0);

  tracksInCosmics_ = new TH1D("hTracksInCosmics", "", 10, 0., 10.);

  etaMuon_ = new TH1D("hEtaMuon", "N_{#mu} > 0", 50, -1.5, 1.5);
  phiMuon_ = new TH1D("hPhiMuon", "N_{#mu} > 0", 72,  -1 * TMath::Pi(), TMath::Pi());
  etaDT_ = new TH1D("hEtaDT", "N_{#DT} > 2", 50, -1.5, 1.5);
  phiDT_ = new TH1D("hPhiDT", "N_{#DT} > 2", 72,  -1 * TMath::Pi(), TMath::Pi());
  etaRPC_ = new TH1D("hEtaRPC", "N_{#RPC} > 2", 50, -1.5, 1.5);
  phiRPC_ = new TH1D("hPhiRPC", "N_{#RPC} > 2", 72,  -1 * TMath::Pi(), TMath::Pi());
  etaNM1_ = new TH1D("hEtaCosmicNM1", "N-1(cosmic)", 50, -1.5, 1.5);
  phiNM1_ = new TH1D("hPhiCosmicNM1", "N-1(cosmic)", 72,  -1 * TMath::Pi(), TMath::Pi());


  reset();
  nextEvent();

  for (unsigned long i=0; i<maxEvents_; ++i, nextEvent()) {

    // occasional print out
    if (i%100000==0) {
      std::cout << "Processing " << i << "th event of " <<maxEvents_<< std::endl;
    }

    // YOUR CODE HERE
    livetime_.newEvent(event_->fill, event_->run, event_->lb);

    if (event_->jet_N==0) continue;

    double e   = event_->jetE[0];
    double eta = event_->jetEta[0];
    double phi = event_->jetPhi[0];
    
    // n-1 information
    if (cuts_.cutNMinusOne(5)) {
      
      nMinusOneCount++;

      tracksInCosmics_->Fill(event_->track_N);

      etaNM1_->Fill(eta);
      phiNM1_->Fill(phi);

      if (event_->bx > 3485) nMinus1AbortGap++;

    }

    // positively identified cosmics
    if (e>50. && eta<1.3 &&
	event_->bxWrtBunch>2 && event_->cscSeg_N==0 && 
	event_->vtx_N==0 && event_->track_N==0) {

      if (event_->mu_N > 0) {
	nMuon++;
	etaMuon_->Fill(eta);
	phiMuon_->Fill(phi);
      }

      if (event_->DTSegment_N > 2) {
	nDT++;
	etaDT_->Fill(eta);
	phiDT_->Fill(phi);
      }

      if (event_->rpcHit_N > 2) {
	nRPC++; 
	etaRPC_->Fill(eta);
	phiRPC_->Fill(phi);
      }
    }

  }

  // print out
  double livetime = livetime_.getTotalLivetime();
  double gapTime = livetime_.runLumiPairs().size() * TIME_PER_LS * (3529-3485)/3564;

  std::cout << std::endl;
  std::cout << "Livetime           : " << livetime << std::endl;
  std::cout << "N-1 cosmic count   : " << nMinusOneCount << std::endl;
  std::cout << "N-1 cosmic rate    : " << nMinusOneCount/livetime << " +/- " << sqrt(nMinusOneCount)/livetime << std::endl;

  std::cout << std::endl;
  std::cout << "Cosmic (mu) count  : " << nMuon << std::endl;
  std::cout << "Cosmic (mu) rate   : " << nMuon/livetime << " +/- " << sqrt(nMuon)/livetime << std::endl;

  std::cout << std::endl;
  std::cout << "Cosmic (DT) count  : " << nDT << std::endl;
  std::cout << "Cosmic (DT) rate   : " << nDT/livetime << " +/- " << sqrt(nDT)/livetime << std::endl;

  std::cout << std::endl;
  std::cout << "Cosmic (RPC) count : " << nRPC << std::endl;
  std::cout << "Cosmic (RPC) rate  : " << nRPC/livetime << " +/- " << sqrt(nRPC)/livetime << std::endl;

  std::cout << std::endl;
  std::cout << "N-1 abort gap count   : " << nMinus1AbortGap << std::endl;
  std::cout << "N-1 abort gap rate    : " << nMinus1AbortGap/gapTime << " +/- " << sqrt(nMinus1AbortGap)/gapTime << std::endl;


  // SAVE HISTOGRAMS HERE
  tracksInCosmics_->Write("",TObject::kOverwrite);
  
  etaMuon_->Write("",TObject::kOverwrite);
  phiMuon_->Write("",TObject::kOverwrite);
  etaDT_->Write("",TObject::kOverwrite);
  phiDT_->Write("",TObject::kOverwrite);
  etaRPC_->Write("",TObject::kOverwrite);
  phiRPC_->Write("",TObject::kOverwrite);
  etaNM1_->Write("",TObject::kOverwrite);
  phiNM1_->Write("",TObject::kOverwrite);

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
