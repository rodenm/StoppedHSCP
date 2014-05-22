#ifndef CosmicInefficiency_h
#define CosmicInefficiency_h

#include "StoppedHSCP/Analysis/interface/BasicAnalyser.h"

#include "StoppedHSCP/Analysis/interface/Livetime.h"
#include "StoppedHSCP/Ntuples/interface/Constants.h"

#include "TMath.h"
#include "TFile.h"
#include "TChain.h"
#include "TH1D.h"
#include "TH2D.h"

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
  std::ofstream eventsFile_;

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

  TH2D* taggedDTbyRPC_;
  TH2D* untaggedDTbyRPC_;
  TH2D* untaggedDTbyRPC_uncert_;
  TH2D* totalDTbyRPC_;
  TH1D* taggedFrac_;
  TH1D* untaggedFrac_;
  TH1D* totalFrac_;

  TH2D* inefficiencyDTbyRPC_;
  TH2D* inefficiencyDTbyRPC_uncert_;
  TH1D* inefficiencyFrac_;
};

#endif


// this is the event loop
void CosmicInefficiency::loop() {

  // set up events file
  std::string ed(outdir_);
  ed+="/CosmicInefficiency_untaggedEvents.txt";
  eventsFile_.open(ed.c_str());

  // setup log file
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
  rpcDeltaZ_ = new TH1D("rpcDetlaZ", "RPC #Delta(z)", 10, 0, 1000);
  rpcDeltaZ_Min_ = new TH1D("rpcDetlaZ_Min", "Min RPC #Delta(z)", 100, 0, 1000);
  rpcNClosePairs_ = new TH1D("rpcNClosePairs", "N(close RPC pairs)", 25, 0, 25); 

  taggedDTbyRPC_ = new TH2D("taggedDTbyRPC","tagged cosmic;nDT;nRPC", 15, 0, 30, 15, 0, 30);
  untaggedDTbyRPC_ = new TH2D("untaggedDTbyRPC","untagged cosmic;nDT;nRPC", 15, 0, 30, 15, 0, 30);
  untaggedDTbyRPC_uncert_ = new TH2D("untaggedDTbyRPC_uncert","untagged cosmic;nDT;nRPC", 15, 0, 30, 15, 0, 30);
  totalDTbyRPC_ = new TH2D("totalDTbyRPC","total cosmic;nDT;nRPC", 15, 0, 30, 15, 0, 30);

  taggedFrac_ = new TH1D("taggedFrac","tagged cosmic;inner/outer DT hits;", 20, 0, 10);
  untaggedFrac_ = new TH1D("untaggedFrac","untagged cosmic;inner/outer DT hits;", 20, 0, 10);
  totalFrac_ = new TH1D("totalFrac","total cosmic;inner/outer DT hits;", 20, 0, 10);

  inefficiencyDTbyRPC_ = new TH2D("ineffciencyDTbyRPC", "inefficiency", 15, 0, 30, 15, 0, 30);
  inefficiencyDTbyRPC_uncert_ = new TH2D("ineffciencyDTbyRPC_uncert", "inefficiency", 15, 0, 30, 15, 0, 30);
  inefficiencyFrac_ = new TH1D("ineffciencyFrac", "inefficiency", 20, 0, 10);
  
  reset();
  nextEvent();

  
  // inefficiency = b/(a+b)
  unsigned a = 0; // tagged cosmic
  unsigned b = 0; // not tagged cosmic
  unsigned nVetoed = 0;
  unsigned nminusone = 0;
  unsigned selected = 0;

  // EVENT LOOP
  for (unsigned long i=0; i<maxEvents_; ++i, nextEvent()) {
    
    // occasional print out
    if (i%10000==0) {
      std::cout << "Processing " << i << "th event of " <<maxEvents_<< std::endl;
    }

    unsigned nRPC = event_->rpcHit_N;
    unsigned nDT  = event_->DTSegment_N;

    /************* REMOVE THIS LINE IN REAL ANALYSIS ***************/
    //if ((nRPC < 5 || nRPC > 15) || (nDT < 5 || nDT > 17)) continue;
    /************* REMOVE THIS LINE IN REAL ANALYSIS ***************/

    if (cuts_.cutNMinusOne(5)) nminusone++;
    if (cuts_.cut()) selected++;

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
    unsigned outerRPC = 0;
    unsigned innerRPC = 0;
    for (unsigned irpc = 0; irpc < event_->rpcHit_N; irpc++) {

      if (event_->rpcHitPhi[irpc] > 560)
	outerRPC++;
      else
	innerRPC++;

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
	if (event_->rpcHit_N > 2 && event_->DTSegment_N < 3) { // only plot these values if event passes all other cuts but RPC
	  rpcDeltaPhi_->Fill(deltaPhi);
	  rpcDeltaZ_->Fill(deltaZ);
	}
	
	if (deltaPhi > TMath::Pi()/2.) {
	  nCloseRPCPairs++;

	if (deltaZ < minDeltaZ) 
	  minDeltaZ = deltaZ;

	}
      }
    }
    rpcNClosePairs_->Fill(nCloseRPCPairs);
    if (event_->rpcHit_N > 2 && event_->DTSegment_N < 3)
      rpcDeltaZ_Min_->Fill(minDeltaZ);

    // Calculte the fraction of inner and outer DT hits
    float outerDT = 0.0000001;
    float innerDT = 0;
    for (unsigned idt = 0; idt<event_->DTSegment_N; idt++) {
      if (event_->DTSegR[idt] > 560) outerDT++;
      else innerDT++;
    }
    double frac = innerDT/outerDT;

    // Using a "loose" N-1 requirement because of low statistics. 
    // Exclude events with OR of:
    //  1. cscSeg_N > 0
    //  2. jet_N == 0
    //  3. jetEta > 1.0
    // ********************
    // Nevermind, just require a jet
    if (event_->jet_N > 0) {
      if (cuts_.cutN(5)) b++;
      else a++;
    }

    // Binned version of the b/a+b calculation    
    //if (cuts_.triggerCut()) {
    if (event_->jet_N > 0) {
      if (cuts_.cutN(5)) {
	untaggedDTbyRPC_->Fill(event_->DTSegment_N, event_->rpcHit_N);
	untaggedDTbyRPC_uncert_->Fill(event_->DTSegment_N, event_->rpcHit_N);
	untaggedFrac_->Fill(frac);
	eventsFile_ << event_->run << ":" << event_->lb << ":" << event_->id << std::endl;
	
	/**std::cout.precision(4);
	std::cout << event_->run << "\t"
		  << event_->id << "\t"
		  << event_->DTSegment_N << "   "
		  << event_->rpcHit_N << "   "
		  << nCloseRPCPairs << "   "
		  << std::fixed << outerDT << "\t   "
		  << std::fixed << outerRPC << "   "
		  << std::fixed << frac << "   "
	  //<< std::fixed << maxDeltaPhi << "   "
	  //<< std::fixed << maxDeltaJetPhi << "   "
	  //<< std::fixed << maxRPCDeltaPhi << "   "
		  << std::endl;
	std::cout << "\t\t" << std::fixed << event_->jetPhi[0] << "\t\t";
	for (unsigned i = 0; i < event_->DTSegment_N; i++) 
	  std::cout << std::fixed << event_->DTSegPhi[i] << "  ";
	std::cout << "\t\t";
	for (unsigned i = 0; i < event_->rpcHit_N; i++) 
	  std::cout << std::fixed << event_->rpcHitPhi[i] << "  ";
	std::cout << std::endl;
	*/
      } else {
	taggedDTbyRPC_->Fill(event_->DTSegment_N, event_->rpcHit_N);
	taggedFrac_->Fill(frac);
      }
      totalDTbyRPC_->Fill(event_->DTSegment_N, event_->rpcHit_N);
      totalFrac_->Fill(frac);
    }

  } // END EVENT LOOP
  
  // PRINT OUT
  double ineff = 1.0*b/(1.0*(a+b));
  double sigma = sqrt((ineff*(1-ineff))/(a+b));
  //dumpFile_ << std::endl;
  dumpFile_ << "Inefficiency calculation using unbinned values" << std::endl;
  dumpFile_ << "----------------------------------------------" << std::endl;
  dumpFile_ << "Total events:      " << maxEvents_ << std::endl;
  dumpFile_ << "N events vetoed:   " << nVetoed << std::endl;
  dumpFile_ << "N-1 cosmic events: " << nminusone << std::endl;
  dumpFile_ << "Selected events:   " << selected << std::endl;
  dumpFile_ << "----------------------------" << std::endl;
  dumpFile_ << "a: " << a <<std::endl;
  dumpFile_ << "b: " << b <<std::endl;
  dumpFile_ << "----------------------------" << std::endl;
  dumpFile_ << "b/(a+b) = " << ineff << " +/- " << sigma << std::endl;
  dumpFile_ << std::endl;
  dumpFile_ << std::endl;
  
  dumpFile_ << "Inefficiency calculation using integrated binned values" << std::endl;
  dumpFile_ << "----------------------------------------------" << std::endl;
  dumpFile_ << "ineff (DT/RPC) = " << untaggedDTbyRPC_->Integral() << "/" << totalDTbyRPC_->Integral() << std::endl;
  dumpFile_ << "               = " << untaggedDTbyRPC_->Integral()/totalDTbyRPC_->Integral() << std::endl;
  dumpFile_ << "----------------------------" << std::endl;
  dumpFile_ << "ineff (frac)   = " << untaggedFrac_->Integral() << "/" << totalFrac_->Integral() << std::endl;
  dumpFile_ << "               = " << untaggedFrac_->Integral()/totalFrac_->Integral() << std::endl;
  dumpFile_ << std::endl;
  dumpFile_ << std::endl;
  
  for (int i = 0; i<15; i++) {
    for (int j = 0; j<15; j++) {
      if (untaggedDTbyRPC_uncert_->GetBinContent(i,j) == 0)
	untaggedDTbyRPC_uncert_->SetBinContent(i,j,0.01);
    }
  }


  // Now calculate using binned values
  // Binned version of the b/a+b calculation                                                                                                             
  taggedDTbyRPC_->Sumw2();
  taggedFrac_->Sumw2();
  untaggedDTbyRPC_->Sumw2();
  untaggedFrac_->Sumw2();
  totalDTbyRPC_->Sumw2();
  totalFrac_->Sumw2();

  inefficiencyDTbyRPC_->Divide(untaggedDTbyRPC_, totalDTbyRPC_);
  inefficiencyDTbyRPC_uncert_->Divide(untaggedDTbyRPC_uncert_, totalDTbyRPC_);
  inefficiencyFrac_->Divide(untaggedFrac_, totalFrac_);

  double errorDR = 0;
  double integralDR = inefficiencyDTbyRPC_->IntegralAndError(1,inefficiencyDTbyRPC_->GetNbinsX(),
							     1,inefficiencyDTbyRPC_->GetNbinsY(),
							     errorDR);
  double errorUncert = 0;
  double integralUncert = inefficiencyDTbyRPC_uncert_->IntegralAndError(1,inefficiencyDTbyRPC_uncert_->GetNbinsX(),
									1,inefficiencyDTbyRPC_uncert_->GetNbinsY(),
							     errorUncert);
  double errorFrac = 0;
  double integralFrac = inefficiencyFrac_->IntegralAndError(1,inefficiencyFrac_->GetNbinsX(),errorFrac);
  
  dumpFile_ << "Inefficiency calculation binned in nDT and nRPC" << std::endl;
  dumpFile_ << "-----------------------------------------------" << std::endl;
  dumpFile_ << "ineff (binned by DT & RPC) : " << integralDR << " +/- " << errorDR << std::endl;
  dumpFile_ << "ineff (DT & RPC uncert)    : " << integralUncert << " +/- " << errorUncert << std::endl;
  dumpFile_ << "ineff (binned by Frac)     : " << integralFrac << " +/- " << errorFrac << std::endl;
  dumpFile_ << std::endl;
  



  // SAVE HISTOGRAMS HERE
  //ofilename_.Write("",TObject::kOverwrite);
  
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
  
  taggedDTbyRPC_->Write("",TObject::kOverwrite);
  untaggedDTbyRPC_->Write("",TObject::kOverwrite);
  untaggedDTbyRPC_uncert_->Write("",TObject::kOverwrite);
  totalDTbyRPC_->Write("",TObject::kOverwrite);
  inefficiencyDTbyRPC_->Write("",TObject::kOverwrite);
  inefficiencyDTbyRPC_uncert_->Write("",TObject::kOverwrite);

  taggedFrac_->Write("",TObject::kOverwrite);
  untaggedFrac_->Write("",TObject::kOverwrite);
  totalFrac_->Write("",TObject::kOverwrite);  
  inefficiencyFrac_->Write("",TObject::kOverwrite);

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
