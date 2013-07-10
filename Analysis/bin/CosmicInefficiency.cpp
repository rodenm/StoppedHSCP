#ifndef CosmicInefficiency_h
#define CosmicInefficiency_h

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

class CosmicInefficiency : public BasicAnalyser {

public:
  CosmicInefficiency(int argc, char* argv[]) :
    BasicAnalyser(argc, argv) {
    ofilename_ = std::string("CosmicInefficiency.root");  /// SET YOUR OUTPUT FILENAME HERE

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
  
  ~CosmicInefficiency() { };
  
  virtual void loop();
  
private:

  // YOUR CODE HERE
  std::ofstream dumpFile_;

  // histograms
  TH1D* nJet_;
  TH1D* jetEta_;
  TH1D* nMuon_;
  TH1D* nCSCSegments_;
  TH1D* nDTSegments_;
  TH1D* nRPCHits_;
  TH1D* rpcDeltaPhi_;
  TH1D* rpcDeltaZ_;
  TH1D* rpcDeltaZ_Min_;
  TH1D* rpcNClosePairs_;
};

#endif


// this is the event loop
void CosmicInefficiency::loop() {

  // setup log files                                                                                 
  std::string fd(outdir_);
  fd+="/CosmicInefficiency.txt";
  dumpFile_.open(fd.c_str());
  dumpFile_ << "\nOutput from cosmicInefficiency (based on cosmic MC!)" << std::endl << std::endl;
  
  dumpFile_ << "Ntuple files:" <<std::endl;
  for (std::vector<std::string>::iterator file=ifiles_.begin(); file!=ifiles_.end(); ++file)
    dumpFile_ << "   " << (*file) << std::endl;
  dumpFile_ << std::endl;

  // DO ANY SETUP HERE
  nJet_ = new TH1D("nJet", "jet/event", 15, 0, 15); 
  jetEta_ = new TH1D("jetEta", "#eta_{jet}", 20, -2, 2); 
  nMuon_ = new TH1D("nMuon", "muons/event", 10, 0, 10);
  nCSCSegments_ = new TH1D("nCSCSegments", "CSCSegments/event", 25, 0, 25);
  nDTSegments_ = new TH1D("nDTSegments", "DTSegments/event", 25, 0, 25);
  nRPCHits_ = new TH1D("nRPCHits", "RPCHits/event", 20, 0, 20);
  rpcDeltaPhi_ = new TH1D("rpcDeltaPhi", "RPC #delta(#phi)", 32, 0, 3.2);
  rpcDeltaZ_ = new TH1D("rpcDetlaZ", "RPC #Delta(z)", 100, 0, 1000);
  rpcDeltaZ_Min_ = new TH1D("rpcDetlaZ_Min", "Min RPC #Delta(z)", 100, 0, 1000);
  rpcNClosePairs_ = new TH1D("rpcNClosePairs", "N(close RPC pairs)", 25, 0, 25); 
  
  reset();
  nextEvent();

  
  // inefficiency = b/(a+b)
  unsigned a = 0; // tagged cosmic
  unsigned b = 0; // not tagged cosmic
  unsigned nVetoed = 0;

  // EVENT LOOP
  for (unsigned long i=0; i<maxEvents_; ++i, nextEvent()) {
    
    // occasional print out
    if (i%10000==0) {
      std::cout << "Processing " << i << "th event of " <<maxEvents_<< std::endl;
    }

    if (event_->cscSeg_N > 0 || event_->jet_N == 0 || event_->jetEta[0] > 1.0) {
      nVetoed++;
      continue;
    }

    // Fill some histograms
    nJet_->Fill(event_->jet_N);
    jetEta_->Fill(event_->jetEta[0]);
    nMuon_->Fill(event_->mu_N);
    nCSCSegments_->Fill(event_->cscSeg_N);
    nDTSegments_->Fill(event_->DTSegment_N);
    nRPCHits_->Fill(event_->rpcHit_N);

    unsigned nCloseRPCPairs = 0;
    double minDeltaZ = 2000.;
    for (unsigned irpc = 0; irpc < event_->rpcHit_N; irpc++) {
      for (unsigned jrpc = irpc+1; jrpc < event_->rpcHit_N; jrpc++) {
	double deltaZ = fabs(event_->rpcHitZ[irpc] - event_->rpcHitZ[jrpc]);
	double deltaPhi = acos(cos(event_->rpcHitPhi[irpc] - event_->rpcHitPhi[jrpc]));
	
	// Require barrel hits to be localized in z, endcap hits to be localzied in phi
	/**
	   if (deltaZ < 40.0 && event_->rpcHitRegion[irpc] == 0 && event_->rpcHitRegion[jrpc] == 0) {
	   nCloseRPCPairs++;
	   }
	   if (deltaPhi < 0.4 && abs(event_->rpcHitRegion[irpc]) == 1 && abs(event_->rpcHitRegion[jrpc]) == 1) {
	   nCloseRPCPairs++;
	   }
	   
	*/
	rpcDeltaPhi_->Fill(deltaPhi);
	rpcDeltaZ_->Fill(deltaZ);
	
	if (deltaZ < 40.0 || deltaPhi < 0.2) {
	  nCloseRPCPairs++;

	if (deltaZ < minDeltaZ) 
	  minDeltaZ = deltaZ;

	}
      }
    }
    rpcNClosePairs_->Fill(nCloseRPCPairs);
    rpcDeltaZ_Min_->Fill(minDeltaZ);

    // Using a "lose" N-1 requirement because of low statistics. 
    // Exclude events with OR of:
    //  1. cscSeg_N > 0
    //  2. jet_N == 0
    //  3. jetEta > 1.0
    
    if (cuts_.cutN(5)) b++;
    else a++;
  }
  
  // PRINT OUT
  double ineff = 1.0*b/(1.0*(a+b));
  double sigma = sqrt((ineff*(1-ineff))/(a+b));
  //dumpFile_ << std::endl;
  dumpFile_ << "Total events: " << maxEvents_ << std::endl;
  dumpFile_ << "N events vetoed: " << nVetoed << std::endl;
  dumpFile_ << "----------------------------" << std::endl;
  dumpFile_ << "a: " << a <<std::endl;
  dumpFile_ << "b: " << b <<std::endl;
  dumpFile_ << "----------------------------" << std::endl;
  dumpFile_ << "b/(a+b)" << ineff << " +/- " << sigma << std::endl;
  dumpFile_ << std::endl;
  
  // SAVE HISTOGRAMS HERE
  nJet_->Write("",TObject::kOverwrite);
  jetEta_->Write("",TObject::kOverwrite);
  nMuon_->Write("",TObject::kOverwrite);
  nCSCSegments_->Write("",TObject::kOverwrite);
  nDTSegments_->Write("",TObject::kOverwrite);
  nRPCHits_->Write("",TObject::kOverwrite);
  rpcDeltaPhi_->Write("",TObject::kOverwrite);
  rpcDeltaZ_->Write("",TObject::kOverwrite);
  rpcDeltaZ_Min_->Write("",TObject::kOverwrite);
  rpcNClosePairs_->Write("",TObject::kOverwrite);
  
}



// this is the main program, no need to do anything here
int main(int argc, char* argv[]) {
  
  // sum of squares error info for histograms
  TH1D::SetDefaultSumw2();
  
  // create analysis
  CosmicInefficiency analyser(argc, argv);
  
  analyser.setup();

  analyser.cuts().print(std::cout);

  std::cout << std::endl;
  std::cout << std::endl;
  std::cout << "------------------------------------------------------------------------------"
	    << std::endl;
  std::cout << "WARNING: input ntuples are required to be generated from cosmic MC, not data."
	    << std::endl;
  std::cout << "------------------------------------------------------------------------------"
	    << std::endl;
  std::cout << std::endl;

  analyser.loop();

  return 0;

}
