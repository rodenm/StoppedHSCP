#ifndef BackgroundStability_h
#define BackgroundStability_h

#include "StoppedHSCP/Analysis/interface/BasicAnalyser.h"
#include "StoppedHSCP/Analysis/interface/MultiHistogram1D.h"
#include "StoppedHSCP/Ntuples/interface/Constants.h"

#include "TFile.h"
#include "TChain.h"
#include "TF1.h"
#include "TH1D.h"

#include <cmath>
#include <vector>
#include <utility>
#include <algorithm>
#include <iostream>
#include <sstream>

using namespace std;

class BackgroundStability : public BasicAnalyser {

public:
  BackgroundStability(int argc, char* argv[]) :
    BasicAnalyser(argc, argv) {
    ofilename_ = std::string("BackgroundStability.root");  /// SET YOUR OUTPUT FILENAME HERE
  }
  
  ~BackgroundStability() { };
  
  virtual void loop();
  
private:

  // YOUR CODE HERE

  // counts for livetime calculation
  std::vector<std::pair<unsigned long, unsigned long> > runLumiPairs_;
  std::vector<unsigned long> fillList_;
  std::vector<unsigned long> runList_;

  // counts of different event types
  std::vector<unsigned long> nTriggerByFill_;
  std::vector<unsigned long> nNoiseFlagByFill_;
  std::vector<unsigned long> nCosmicByFill_;
  std::vector<unsigned long> nCosmic2ByFill_;
  std::vector<unsigned long> nCosmic3ByFill_;
  std::vector<unsigned long> nm1CosmicByFill_;
  std::vector<unsigned long> nBeamHaloByFill_;
  std::vector<unsigned long> nBeamGasByFill_;
  std::vector<unsigned long> nVertexByFill_;
  std::vector<unsigned long> nUnidentifiedByFill_;

//   std::vector<unsigned long> nCSCSegByFill_;
//   std::vector<unsigned long> nMuonNMinusOneByFill_;

  // energy distributions for different types
  MultiHistogram1D jetENoiseByFill_;
  MultiHistogram1D jetECosmicByFill_;
  MultiHistogram1D jetECosmic2ByFill_;
  MultiHistogram1D jetEBeamHaloByFill_;
  MultiHistogram1D jetEBeamGasByFill_;
  MultiHistogram1D jetEVertexByFill_;
  MultiHistogram1D jetEUnidentifiedByFill_;

  MultiHistogram1D jetN60NoiseByFill_;
  MultiHistogram1D jetN60CosmicByFill_;
  MultiHistogram1D jetN60Cosmic2ByFill_;
  MultiHistogram1D jetN60BeamHaloByFill_;
  MultiHistogram1D jetN60BeamGasByFill_;
  MultiHistogram1D jetN60VertexByFill_;
  MultiHistogram1D jetN60UnidentifiedByFill_;

  MultiHistogram1D jetN90NoiseByFill_;
  MultiHistogram1D jetN90CosmicByFill_;
  MultiHistogram1D jetN90Cosmic2ByFill_;
  MultiHistogram1D jetN90BeamHaloByFill_;
  MultiHistogram1D jetN90BeamGasByFill_;
  MultiHistogram1D jetN90VertexByFill_;
  MultiHistogram1D jetN90UnidentifiedByFill_;

  MultiHistogram1D jetNTowNoiseByFill_;
  MultiHistogram1D jetNTowCosmicByFill_;
  MultiHistogram1D jetNTowCosmic2ByFill_;
  MultiHistogram1D jetNTowBeamHaloByFill_;
  MultiHistogram1D jetNTowBeamGasByFill_;
  MultiHistogram1D jetNTowVertexByFill_;
  MultiHistogram1D jetNTowUnidentifiedByFill_;


  // rates by run
  std::vector<unsigned long> nTriggerByRun_;
  std::vector<unsigned long> nNoiseFlagByRun_;
  std::vector<unsigned long> nCosmicByRun_;
  std::vector<unsigned long> nBeamHaloByRun_;
  std::vector<unsigned long> nBeamGasByRun_;
  std::vector<unsigned long> nVertexByRun_;


};

#endif


// this is the event loop
void BackgroundStability::loop() {

  // DO ANY SETUP HERE
  unsigned maxFill=0;
  unsigned long maxRun=0;

  jetENoiseByFill_.setup(ofile_, "hJetENoiseByFill", "Noise", 200, 0., 200.);
  jetECosmicByFill_.setup(ofile_, "hJetECosmicByFill", "Cosmic", 200, 0., 200.);
  jetECosmic2ByFill_.setup(ofile_, "hJetECosmic2ByFill", "Cosmic2", 200, 0., 200.);
  jetEBeamHaloByFill_.setup(ofile_, "hJetEBeamHaloByFill", "Beam Halo", 200, 0., 200.);
  jetEBeamGasByFill_.setup(ofile_, "hJetEBeamGasByFill", "Beam gas", 200, 0., 200.);
  jetEVertexByFill_.setup(ofile_, "hJetEVertexByFill", "Vertex", 200, 0., 200.);
  jetEUnidentifiedByFill_.setup(ofile_, "hJetEUnidentifiedByFill", "No ID", 200, 0., 200.);

  jetN60NoiseByFill_.setup(ofile_, "hJetN60NoiseByFill", "Noise N60", 25, -0.5, 24.5);
  jetN60CosmicByFill_.setup(ofile_, "hJetN60CosmicByFill", "Cosmic N60", 25, -0.5, 24.5);
  jetN60Cosmic2ByFill_.setup(ofile_, "hJetN60Cosmic2ByFill", "Cosmic2 N60", 25, -0.5, 24.5);
  jetN60BeamHaloByFill_.setup(ofile_, "hJetN60BeamHaloByFill", "Beam Halo N60", 25, -0.5, 24.5);
  jetN60BeamGasByFill_.setup(ofile_, "hJetN60BeamGasByFill", "Beam gas N60", 25, -0.5, 24.5);
  jetN60VertexByFill_.setup(ofile_, "hJetN60VertexByFill", "Vertex N60", 25, -0.5, 24.5);
  jetN60UnidentifiedByFill_.setup(ofile_, "hJetN60UnidentifiedByFill", "No ID N60", 25, 0., 24.5);

  jetN90NoiseByFill_.setup(ofile_, "hJetN90NoiseByFill", "Noise N90", 50, -0.5, 49.5);
  jetN90CosmicByFill_.setup(ofile_, "hJetN90CosmicByFill", "Cosmic N90", 50, -0.5, 49.5);
  jetN90Cosmic2ByFill_.setup(ofile_, "hJetN90Cosmic2ByFill", "Cosmic2 N90", 50, -0.5, 49.5);
  jetN90BeamHaloByFill_.setup(ofile_, "hJetN90BeamHaloByFill", "Beam Halo N90", 50, -0.5, 49.5);
  jetN90BeamGasByFill_.setup(ofile_, "hJetN90BeamGasByFill", "Beam gas N90", 50, -0.5, 49.5);
  jetN90VertexByFill_.setup(ofile_, "hJetN90VertexByFill", "Vertex N90", 50, -0.5, 49.5);
  jetN90UnidentifiedByFill_.setup(ofile_, "hJetN90UnidentifiedByFill", "No ID N90", 50, -0.5, 49.5);

  jetNTowNoiseByFill_.setup(ofile_, "hJetNTowNoiseByFill", "Noise NTow", 20, -0.5, 19.5);
  jetNTowCosmicByFill_.setup(ofile_, "hJetNTowCosmicByFill", "Cosmic NTow", 20, -0.5, 19.5);
  jetNTowCosmic2ByFill_.setup(ofile_, "hJetNTowCosmic2ByFill", "Cosmic2 NTow", 20, -0.5, 19.5);
  jetNTowBeamHaloByFill_.setup(ofile_, "hJetNTowBeamHaloByFill", "Beam Halo NTow", 20, -0.5, 19.5);
  jetNTowBeamGasByFill_.setup(ofile_, "hJetNTowBeamGasByFill", "Beam gas NTow", 20, -0.5, 19.5);
  jetNTowVertexByFill_.setup(ofile_, "hJetNTowVertexByFill", "Vertex NTow", 20, -0.5, 19.5);
  jetNTowUnidentifiedByFill_.setup(ofile_, "hJetNTowUnidentifiedByFill", "NO ID NTow", 20, -0.5, 19.5);

  reset();
  nextEvent();

  for (unsigned long i=0; i<maxEvents_; ++i, nextEvent()) {

    // occasional print out
    if (i%100000==0) {
      std::cout << "Processing " << i << "th event of " <<maxEvents_<< std::endl;
    }

    // YOUR CODE HERE
    // record fills run over
    unsigned fill = event_->fill;

    // count lumi sections
    std::pair<unsigned long, unsigned long> runLumiPair(event_->run, event_->lb);
    std::vector<std::pair<unsigned long, unsigned long> >::const_iterator itr = 
      find(runLumiPairs_.begin(), runLumiPairs_.end(), runLumiPair);
    if (itr == runLumiPairs_.end()) {
      runLumiPairs_.push_back(runLumiPair);
    }

    std::vector<unsigned long>::const_iterator itr2 = find(fillList_.begin(), fillList_.end(), fill);
    if (itr2 == fillList_.end()) {
      fillList_.push_back(fill);
      jetENoiseByFill_.fill(fill, 0., 0.);
      jetECosmicByFill_.fill(fill, 0., 0.);
      jetECosmic2ByFill_.fill(fill, 0., 0.);
      jetEBeamHaloByFill_.fill(fill, 0., 0.);
      jetEBeamGasByFill_.fill(fill, 0., 0.);
      jetEVertexByFill_.fill(fill, 0., 0.);
      jetEUnidentifiedByFill_.fill(fill, 0., 0.);
      jetN60NoiseByFill_.fill(fill, 0., 0.);
      jetN60CosmicByFill_.fill(fill, 0., 0.);
      jetN60Cosmic2ByFill_.fill(fill, 0., 0.);
      jetN60BeamHaloByFill_.fill(fill, 0., 0.);
      jetN60BeamGasByFill_.fill(fill, 0., 0.);
      jetN60VertexByFill_.fill(fill, 0., 0.);
      jetN60UnidentifiedByFill_.fill(fill, 0., 0.);
      jetN90NoiseByFill_.fill(fill, 0., 0.);
      jetN90CosmicByFill_.fill(fill, 0., 0.);
      jetN90Cosmic2ByFill_.fill(fill, 0., 0.);
      jetN90BeamHaloByFill_.fill(fill, 0., 0.);
      jetN90BeamGasByFill_.fill(fill, 0., 0.);
      jetN90VertexByFill_.fill(fill, 0., 0.);
      jetN90UnidentifiedByFill_.fill(fill, 0., 0.);
      jetNTowNoiseByFill_.fill(fill, 0., 0.);
      jetNTowCosmicByFill_.fill(fill, 0., 0.);
      jetNTowCosmic2ByFill_.fill(fill, 0., 0.);
      jetNTowBeamHaloByFill_.fill(fill, 0., 0.);
      jetNTowBeamGasByFill_.fill(fill, 0., 0.);
      jetNTowVertexByFill_.fill(fill, 0., 0.);
      jetNTowUnidentifiedByFill_.fill(fill, 0., 0.);
    }
    if (fill > maxFill) maxFill = fill;

    // record runs
    unsigned long run = event_->run;
    std::vector<unsigned long>::const_iterator itr3 = find(runList_.begin(), runList_.end(), run);
    if (itr3 == runList_.end()) runList_.push_back(run);

    if (run > maxRun) maxRun = run;

    // keep vectors big enough
    if (nTriggerByFill_.size() < fill+1) nTriggerByFill_.resize(fill+1, 0);
    if (nNoiseFlagByFill_.size() < fill+1) nNoiseFlagByFill_.resize(fill+1, 0);
    if (nCosmicByFill_.size() < fill+1) nCosmicByFill_.resize(fill+1, 0);
    if (nCosmic2ByFill_.size() < fill+1) nCosmic2ByFill_.resize(fill+1, 0);
    if (nCosmic3ByFill_.size() < fill+1) nCosmic3ByFill_.resize(fill+1, 0);
    if (nm1CosmicByFill_.size() < fill+1) nm1CosmicByFill_.resize(fill+1, 0);
    if (nBeamHaloByFill_.size() < fill+1) nBeamHaloByFill_.resize(fill+1, 0);
    if (nBeamGasByFill_.size() < fill+1) nBeamGasByFill_.resize(fill+1, 0);
    if (nVertexByFill_.size() < fill+1) nVertexByFill_.resize(fill+1, 0);
    if (nUnidentifiedByFill_.size() < fill+1) nUnidentifiedByFill_.resize(fill+1, 0);

    if (nTriggerByRun_.size() < run+1) nTriggerByRun_.resize(run+1, 0);
    if (nNoiseFlagByRun_.size() < run+1) nNoiseFlagByRun_.resize(run+1, 0);
    if (nCosmicByRun_.size() < run+1) nCosmicByRun_.resize(run+1, 0);
    if (nBeamHaloByRun_.size() < run+1) nBeamHaloByRun_.resize(run+1, 0);
    if (nBeamGasByRun_.size() < run+1) nBeamGasByRun_.resize(run+1, 0);
    if (nVertexByRun_.size() < run+1) nVertexByRun_.resize(run+1, 0);

    if (event_->jet_N == 0) continue;

    // event quantities
    bool trig       = cuts_.triggerCut();
    int bxWrtBunch  = event_->bxWrtBunch;
    double e        = event_->jetE[0];
    double eta      = event_->jetEta[0];
    double phi      = event_->jetPhi[0];
    unsigned n60    = event_->jetN60[0];
    unsigned n90    = event_->jetN90[0];
    unsigned ntow   = event_->nTowerSameiPhi;
    double fiphi    = event_->leadingIPhiFractionValue;
    bool bh         = event_->beamHalo_CSCLoose;
    unsigned nmu    = event_->mu_N;
    unsigned ndt    = event_->DTSegment_N;
    unsigned nrpc   = event_->rpcHit_N;
    unsigned ncsc   = event_->cscSeg_N;
    unsigned ntrk   = event_->track_N;
    unsigned nvtx   = event_->nVtx;

    // event classes (very loose right now!)
    bool isNoise    = !event_->noiseFilterResult;
    bool isCosmic   = nmu > 0;
    bool isCosmic2  = ndt > 0;
    bool isCosmic3  = !cuts_.cosmicVeto3();
    bool isBeamHalo = ncsc > 0;
    bool isBeamHalo2 = bh;
    bool isBeamGas  = ntrk > 1;
    bool isVtx      = nvtx > 0;
    bool isUnid     = (!isNoise && !isCosmic && !isBeamHalo && !isBeamGas && !isVtx);

    bool isRBXNoise = false;
    if (event_->hpd_N > 0) {
      for (unsigned i = 0; i<event_->hpd_N; i++) {
	if (event_->hpdId[i]==52 || event_->hpdId[i]==53 || event_->hpdId[i]==54 || event_->hpdId[i]==55) 
	  isRBXNoise = true;
      }
    }

    try {
      // counts triggers for x-check with WBM
      if (trig) nTriggerByRun_.at(run) += 1;
      
      // MIN REQUIREMENTS
      // only consider events passing main trigger with jet in barrel
      if ( !(trig && abs(bxWrtBunch)>1 && e>50. && fabs(eta)<1.3) ) continue;
      
      // by fill
      nTriggerByFill_.at(fill) += 1;
      
      // NOISE PLOTS
      if (trig && e>70. && !isCosmic3 && !isBeamHalo && !isVtx && !isRBXNoise) {
	nNoiseFlagByFill_.at(fill) += 1;
	jetENoiseByFill_.fill(fill, e);
	jetN60NoiseByFill_.fill(fill, n60);
	jetN90NoiseByFill_.fill(fill, n90);
	jetNTowNoiseByFill_.fill(fill, ntow);
      }

      // COSMIC PLOTS
      if (isCosmic2 ){//&& !isBeamHalo && !isBeamGas && !isVtx) {
	nCosmicByFill_.at(fill) += 1;
	jetECosmicByFill_.fill(fill, e);
	jetN60CosmicByFill_.fill(fill, n60);
	jetN90CosmicByFill_.fill(fill, n90);
	jetNTowCosmicByFill_.fill(fill, ntow);
      }
      if (isCosmic && !isBeamHalo && !isBeamGas && !isVtx &!isNoise) {
	nCosmic2ByFill_.at(fill) += 1;
      }
      if (isCosmic3 && !isBeamHalo && !isBeamGas && !isVtx) {
	nCosmic3ByFill_.at(fill) += 1;
      }

      // BEAMHALO PLOTS
      if (isBeamHalo && !isBeamGas && !isVtx) {
	nBeamHaloByFill_.at(fill) += 1;
	jetEBeamHaloByFill_.fill(fill, e);
	jetN60BeamHaloByFill_.fill(fill, n60);
	jetN90BeamHaloByFill_.fill(fill, n90);
	jetNTowBeamHaloByFill_.fill(fill, ntow);
      }
      if (isBeamGas && !isVtx) {
	nBeamGasByFill_.at(fill) += 1;
	jetEBeamGasByFill_.fill(fill, e);
	jetN60BeamGasByFill_.fill(fill, n60);
	jetN90BeamGasByFill_.fill(fill, n90);
	jetNTowBeamGasByFill_.fill(fill, ntow);
      }

      // VTX PLOTS
      if (isVtx) {
	nVertexByFill_.at(fill) += 1;
	jetEVertexByFill_.fill(fill, e);
	jetN60VertexByFill_.fill(fill, n60);
	jetN90VertexByFill_.fill(fill, n90);
	jetNTowVertexByFill_.fill(fill, ntow);
      }

      // UNIDENTIFIED PLOTS
      if (!isNoise && !isCosmic && !isBeamHalo && !isBeamGas && !isVtx) {
	nUnidentifiedByFill_.at(fill) += 1;
	jetEUnidentifiedByFill_.fill(fill, e);
	jetN60UnidentifiedByFill_.fill(fill, n60);
	jetN90UnidentifiedByFill_.fill(fill, n90);
	jetNTowUnidentifiedByFill_.fill(fill, ntow);
      }
      
      // if (ncsc>0) nCSCSegByFill_.at(fill) += 1;      
      
      // n-1
      if (cuts_.cutNMinusOne(5)) nm1CosmicByFill_.at(fill) += 1;
      
      // by run
      if (isNoise && !isCosmic && !isBeamHalo && !isBeamGas && !isVtx) nNoiseFlagByRun_.at(run) += 1;
      // MLR - changing for Camilo
      if (isCosmic && !isBeamHalo && !isBeamGas && !isVtx) nCosmicByRun_.at(run) += 1;
      //if (isCosmic2 && !isBeamHalo && !isBeamGas && !isVtx) nCosmicByRun_.at(run) += 1;
      if (isBeamHalo && !isBeamGas && !isVtx) nBeamHaloByRun_.at(run) += 1;
      if (isBeamGas && !isVtx) nBeamGasByRun_.at(run) += 1;
      if (isVtx) nVertexByRun_.at(run) += 1;
      
    }
    catch(std::exception e) {
      std::cerr << "Exception caught in fill " << fill << ", run " << run << std::endl;
      std::cerr << e.what() << std::endl;
    }
      
  }

  // summary
  unsigned nFills = fillList_.size();
  unsigned nRuns  = runList_.size();


  // SAVE HISTOGRAMS HERE

  // count lumis for normalisation factor
  std::vector<double> livetimeByFill(maxFill+1, 0.);
  std::vector<double> livetimeByRun(maxRun+1, 0.);
  std::vector<int> nLumisByRun(maxRun+1, 0);

  std::vector<std::pair<unsigned long, unsigned long> >::const_iterator litr;
  for (litr=runLumiPairs_.begin(); litr!=runLumiPairs_.end(); ++litr) {
    unsigned long r = litr->first;
    unsigned long f = lhcFills_.getFillFromRun(r);
    livetimeByFill.at(f) += TIME_PER_LS * lhcFills_.getLiveFraction(f);
    livetimeByRun.at(r) += TIME_PER_LS * lhcFills_.getLiveFraction(f);
    nLumisByRun.at(r) += 1;
  }

  // fill histograms
  TH1D* hLivetimeByFill = new TH1D("hLivetimeByFill", "", nFills, 0, 0);
  TH1D* hEventRateByFill = new TH1D("hEventRateByFill", "", nFills, 0, 0);
  TH1D* hNoiseRateByFill = new TH1D("hNoiseRateByFill", "Noise rate", nFills, 0, 0);
  TH1D* hCosmicRateByFill = new TH1D("hCosmicRateByFill", "N_{#mu} > 0", nFills, 0, 0);
  TH1D* hCosmic2RateByFill = new TH1D("hCosmic2RateByFill", "N_{#mu} > 0  (v2)", nFills, 0, 0);
  TH1D* hCosmic3RateByFill = new TH1D("hCosmic3RateByFill", "N_{#mu} > 0  (v2)", nFills, 0, 0);
  TH1D* hNM1CosmicRateByFill = new TH1D("hNM1CosmicRateByFill", "N_{vtx} > 0", nFills, 0, 0);
  TH1D* hBeamHaloRateByFill = new TH1D("hBeamHaloRateByFill", "Beam halo flag", nFills, 0, 0);
  TH1D* hBeamGasRateByFill = new TH1D("hBeamGasRateByFill", "N_{trk} > 0 and not beam halo flag", nFills, 0, 0);
  TH1D* hVertexRateByFill = new TH1D("hVertexRateByFill", "N_{vtx} > 0", nFills, 0, 0);
  TH1D* hUnidentifiedRateByFill = new TH1D("hUnidentifiedRateByFill", "N_{vtx} > 0", nFills, 0, 0);

  TH1D* hMeanENoiseByFill = new TH1D("hMeanENoiseByFill", "Noise flag", nFills, 0, 0);
  TH1D* hMeanECosmicByFill = new TH1D("hMeanECosmicByFill", "N_{#mu} > 0", nFills, 0, 0);
  TH1D* hMeanECosmic2ByFill = new TH1D("hMeanECosmic2ByFill", "N_{#mu} > 0 (v2)", nFills, 0, 0);
  TH1D* hMeanEBeamHaloByFill = new TH1D("hMeanEBeamHaloByFill", "Beam halo flag", nFills, 0, 0);
  TH1D* hMeanEBeamGasByFill = new TH1D("hMeanEBeamGasByFill", "N_{trk} > 0 and not beam halo flag", nFills, 0, 0);
  TH1D* hMeanEVertexByFill = new TH1D("hMeanEVertexByFill", "N_{vtx} > 0", nFills, 0, 0);
  TH1D* hMeanEUnidentifiedByFill = new TH1D("hMeanEUnidentifiedByFill", "No ID", nFills, 0, 0);

  TH1D* hStdDevENoiseByFill = new TH1D("hStdDevENoiseByFill", "Noise flag", nFills, 0, 0);
  TH1D* hStdDevECosmicByFill = new TH1D("hStdDevECosmicByFill", "N_{#mu} > 0", nFills, 0, 0);
  TH1D* hStdDevECosmic2ByFill = new TH1D("hStdDevECosmic2ByFill", "N_{#mu} > 0 (v2)", nFills, 0, 0);
  TH1D* hStdDevEBeamHaloByFill = new TH1D("hStdDevEBeamHaloByFill", "Beam halo flag", nFills, 0, 0);
  TH1D* hStdDevEBeamGasByFill = new TH1D("hStdDevEBeamGasByFill", "N_{trk} > 0 and not beam halo flag", nFills, 0, 0);
  TH1D* hStdDevEVertexByFill = new TH1D("hStdDevEVertexByFill", "N_{vtx} > 0", nFills, 0, 0);
  TH1D* hStdDevEUnidentifiedByFill = new TH1D("hStdDevEUnidentifiedByFill", "No ID", nFills, 0, 0);

  TH1D* hMeanN60NoiseByFill = new TH1D("hMeanN60NoiseByFill", "Noise flag", nFills, 0, 0);
  TH1D* hMeanN60CosmicByFill = new TH1D("hMeanN60CosmicByFill", "N_{#mu} > 0", nFills, 0, 0);
  TH1D* hMeanN60Cosmic2ByFill = new TH1D("hMeanN60Cosmic2ByFill", "N_{#mu} > 0 (v2)", nFills, 0, 0);
  TH1D* hMeanN60BeamHaloByFill = new TH1D("hMeanN60BeamHaloByFill", "Beam halo flag", nFills, 0, 0);
  TH1D* hMeanN60BeamGasByFill = new TH1D("hMeanN60BeamGasByFill", "N_{trk} > 0 and not beam halo flag", nFills, 0, 0);
  TH1D* hMeanN60VertexByFill = new TH1D("hMeanN60VertexByFill", "N_{vtx} > 0", nFills, 0, 0);
  TH1D* hMeanN60UnidentifiedByFill = new TH1D("hMeanN60UnidentifiedByFill", "No ID", nFills, 0, 0);

  TH1D* hMeanN90NoiseByFill = new TH1D("hMeanN90NoiseByFill", "Noise flag", nFills, 0, 0);
  TH1D* hMeanN90CosmicByFill = new TH1D("hMeanN90CosmicByFill", "N_{#mu} > 0", nFills, 0, 0);
  TH1D* hMeanN90Cosmic2ByFill = new TH1D("hMeanN90Cosmic2ByFill", "N_{#mu} > 0 (v2)", nFills, 0, 0);
  TH1D* hMeanN90BeamHaloByFill = new TH1D("hMeanN90BeamHaloByFill", "Beam halo flag", nFills, 0, 0);
  TH1D* hMeanN90BeamGasByFill = new TH1D("hMeanN90BeamGasByFill", "N_{trk} > 0 and not beam halo flag", nFills, 0, 0);
  TH1D* hMeanN90VertexByFill = new TH1D("hMeanN90VertexByFill", "N_{vtx} > 0", nFills, 0, 0);
  TH1D* hMeanN90UnidentifiedByFill = new TH1D("hMeanN90UnidentifiedByFill", "No ID", nFills, 0, 0);

  TH1D* hMeanNTowNoiseByFill = new TH1D("hMeanNTowNoiseByFill", "Noise flag", nFills, 0, 0);
  TH1D* hMeanNTowCosmicByFill = new TH1D("hMeanNTowCosmicByFill", "N_{#mu} > 0", nFills, 0, 0);
  TH1D* hMeanNTowCosmic2ByFill = new TH1D("hMeanNTowCosmic2ByFill", "N_{#mu} > 0 (v2)", nFills, 0, 0);
  TH1D* hMeanNTowBeamHaloByFill = new TH1D("hMeanNTowBeamHaloByFill", "Beam halo flag", nFills, 0, 0);
  TH1D* hMeanNTowBeamGasByFill = new TH1D("hMeanNTowBeamGasByFill", "N_{trk} > 0 and not beam halo flag", nFills, 0, 0);
  TH1D* hMeanNTowVertexByFill = new TH1D("hMeanNTowVertexByFill", "N_{vtx} > 0", nFills, 0, 0);
  TH1D* hMeanNTowUnidentifiedByFill = new TH1D("hMeanNTowUnidentifiedByFill", "No ID", nFills, 0, 0);


  std::sort(fillList_.begin(), fillList_.end());
  std::vector<unsigned long>::const_iterator fitr;
  for (fitr=fillList_.begin(); fitr!=fillList_.end(); ++fitr) {
    unsigned long fill = *fitr;
    std::stringstream sstr;
    sstr << (fill);
    std::string fillstr = sstr.str();

    double livetime = livetimeByFill.at(fill);

    hLivetimeByFill->Fill(fillstr.c_str(), livetime);

    hEventRateByFill->Fill(fillstr.c_str(), 0.);
    //hNoiseRateByFill->Fill(fillstr.c_str(), 0.);
    hCosmicRateByFill->Fill(fillstr.c_str(), 0.);
    hCosmic2RateByFill->Fill(fillstr.c_str(), 0.);
    hCosmic3RateByFill->Fill(fillstr.c_str(), 0.);
    hNM1CosmicRateByFill->Fill(fillstr.c_str(), 0.);
    hBeamHaloRateByFill->Fill(fillstr.c_str(), 0.);
    hBeamGasRateByFill->Fill(fillstr.c_str(), 0.);
    hVertexRateByFill->Fill(fillstr.c_str(), 0.);

    //    if (livetime>0.) {
    if (livetime>2000) { //fills 2649, 2651

      // Hopefully this means only long fills will be added to the x-axis
      hNoiseRateByFill->Fill(fillstr.c_str(), 0.);

      for (unsigned long i=0; i<nTriggerByFill_.at(fill); ++i) 
	hEventRateByFill->Fill(fillstr.c_str(), 1./livetime);

      for (unsigned long i=0; i<nNoiseFlagByFill_.at(fill); ++i) 
	hNoiseRateByFill->Fill(fillstr.c_str(), 1./livetime);
      
      for (unsigned long i=0; i<nCosmicByFill_.at(fill); ++i) 
	hCosmicRateByFill->Fill(fillstr.c_str(), 1./livetime);

      for (unsigned long i=0; i<nCosmic2ByFill_.at(fill); ++i) 
	hCosmic2RateByFill->Fill(fillstr.c_str(), 1./livetime);

      for (unsigned long i=0; i<nCosmic3ByFill_.at(fill); ++i) 
	hCosmic3RateByFill->Fill(fillstr.c_str(), 1./livetime);

      for (unsigned long i=0; i<nm1CosmicByFill_.at(fill); ++i) 
	hNM1CosmicRateByFill->Fill(fillstr.c_str(), 1./livetime);
      
      for (unsigned long i=0; i<nBeamHaloByFill_.at(fill); ++i) 
	hBeamHaloRateByFill->Fill(fillstr.c_str(), 1./livetime);
      
      for (unsigned long i=0; i<nBeamGasByFill_.at(fill); ++i) 
	hBeamGasRateByFill->Fill(fillstr.c_str(), 1./livetime);

      for (unsigned long i=0; i<nVertexByFill_.at(fill); ++i) 
	hVertexRateByFill->Fill(fillstr.c_str(), 1./livetime);

      for (unsigned long i=0; i<nUnidentifiedByFill_.at(fill); ++i) 
	hUnidentifiedRateByFill->Fill(fillstr.c_str(), 1./livetime);

      // energy distribution characterisation
      TF1* fexp = new TF1("fexp", "[0]+[1]*exp([2]/x)", 50., 150.);
      jetENoiseByFill_.hist(fill)->Fit(fexp, "R");

      TF1* fexp2 = new TF1("fexp2", "[0]+[1]*exp([2]/x)", 50., 150.);
      jetECosmicByFill_.hist(fill)->Fit(fexp2, "R");

      TF1* fexp3 = new TF1("fexp3", "[0]+[1]*exp([2]/x)", 50., 150.);
      jetEBeamHaloByFill_.hist(fill)->Fit(fexp3, "R");

      TF1* fexp4 = new TF1("fexp4", "[0]+[1]*exp([2]/x)", 50., 150.);
      jetEUnidentifiedByFill_.hist(fill)->Fit(fexp4, "R");

      // jet energy means
      hMeanENoiseByFill->Fill(fillstr.c_str(), jetENoiseByFill_.histogram(fill)->GetMean() );
      hMeanENoiseByFill->SetBinError( hMeanENoiseByFill->GetXaxis()->FindBin(fillstr.c_str()), jetENoiseByFill_.histogram(fill)->GetMeanError() );

      hMeanECosmicByFill->Fill(fillstr.c_str(), jetECosmicByFill_.histogram(fill)->GetMean() );
      hMeanECosmicByFill->SetBinError( hMeanECosmicByFill->GetXaxis()->FindBin(fillstr.c_str()), jetECosmicByFill_.histogram(fill)->GetMeanError() );

      hMeanECosmic2ByFill->Fill(fillstr.c_str(), jetECosmic2ByFill_.histogram(fill)->GetMean() );
      hMeanECosmic2ByFill->SetBinError( hMeanECosmic2ByFill->GetXaxis()->FindBin(fillstr.c_str()), jetECosmic2ByFill_.histogram(fill)->GetMeanError() );

      hMeanEBeamHaloByFill->Fill(fillstr.c_str(), jetEBeamHaloByFill_.histogram(fill)->GetMean() );
      hMeanEBeamHaloByFill->SetBinError( hMeanEBeamHaloByFill->GetXaxis()->FindBin(fillstr.c_str()), jetEBeamHaloByFill_.histogram(fill)->GetMeanError() );

      hMeanEBeamGasByFill->Fill(fillstr.c_str(), jetEBeamGasByFill_.histogram(fill)->GetMean() );      hMeanEBeamGasByFill->SetBinError( hMeanEBeamGasByFill->GetXaxis()->FindBin(fillstr.c_str()), jetEBeamGasByFill_.histogram(fill)->GetMeanError() );

      hMeanEVertexByFill->Fill(fillstr.c_str(), jetEVertexByFill_.histogram(fill)->GetMean() );
      hMeanEVertexByFill->SetBinError( hMeanEVertexByFill->GetXaxis()->FindBin(fillstr.c_str()), jetEVertexByFill_.histogram(fill)->GetMeanError() );

      hMeanEUnidentifiedByFill->Fill(fillstr.c_str(), jetEUnidentifiedByFill_.histogram(fill)->GetMean() );
      hMeanEUnidentifiedByFill->SetBinError( hMeanEUnidentifiedByFill->GetXaxis()->FindBin(fillstr.c_str()), jetEUnidentifiedByFill_.histogram(fill)->GetMeanError() );

      // SD histograms
      hStdDevENoiseByFill->Fill(fillstr.c_str(), jetENoiseByFill_.histogram(fill)->GetRMS() );
      hStdDevENoiseByFill->SetBinError( hStdDevENoiseByFill->GetXaxis()->FindBin(fillstr.c_str()), jetENoiseByFill_.histogram(fill)->GetRMSError() );

      hStdDevECosmicByFill->Fill(fillstr.c_str(), jetECosmicByFill_.histogram(fill)->GetRMS() );
      hStdDevECosmicByFill->SetBinError( hStdDevECosmicByFill->GetXaxis()->FindBin(fillstr.c_str()), jetECosmicByFill_.histogram(fill)->GetRMSError() );

      hStdDevECosmic2ByFill->Fill(fillstr.c_str(), jetECosmic2ByFill_.histogram(fill)->GetRMS() );
      hStdDevECosmic2ByFill->SetBinError( hStdDevECosmic2ByFill->GetXaxis()->FindBin(fillstr.c_str()), jetECosmic2ByFill_.histogram(fill)->GetRMSError() );

      hStdDevEBeamHaloByFill->Fill(fillstr.c_str(), jetEBeamHaloByFill_.histogram(fill)->GetRMS() );
      hStdDevEBeamHaloByFill->SetBinError( hStdDevEBeamHaloByFill->GetXaxis()->FindBin(fillstr.c_str()), jetEBeamHaloByFill_.histogram(fill)->GetRMSError() );

      hStdDevEBeamGasByFill->Fill(fillstr.c_str(), jetEBeamGasByFill_.histogram(fill)->GetRMS() );
      hStdDevEBeamGasByFill->SetBinError( hStdDevEBeamGasByFill->GetXaxis()->FindBin(fillstr.c_str()), jetEBeamGasByFill_.histogram(fill)->GetRMSError() );

      hStdDevEVertexByFill->Fill(fillstr.c_str(), jetEVertexByFill_.histogram(fill)->GetRMS() );
      hStdDevEVertexByFill->SetBinError( hStdDevEVertexByFill->GetXaxis()->FindBin(fillstr.c_str()), jetEVertexByFill_.histogram(fill)->GetRMSError() );

      hStdDevEUnidentifiedByFill->Fill(fillstr.c_str(), jetEUnidentifiedByFill_.histogram(fill)->GetRMS() );
      hStdDevEUnidentifiedByFill->SetBinError( hStdDevEUnidentifiedByFill->GetXaxis()->FindBin(fillstr.c_str()), jetEVertexByFill_.histogram(fill)->GetRMSError() );

      // fit parameters ?

      // N60 mean
      hMeanN60NoiseByFill->Fill(fillstr.c_str(), jetN60NoiseByFill_.histogram(fill)->GetMean() );
      hMeanN60NoiseByFill->SetBinError( hMeanN60NoiseByFill->GetXaxis()->FindBin(fillstr.c_str()), jetN60NoiseByFill_.histogram(fill)->GetMeanError() );

      hMeanN60CosmicByFill->Fill(fillstr.c_str(), jetN60CosmicByFill_.histogram(fill)->GetMean() );
      hMeanN60CosmicByFill->SetBinError( hMeanN60CosmicByFill->GetXaxis()->FindBin(fillstr.c_str()), jetN60CosmicByFill_.histogram(fill)->GetMeanError() );

      hMeanN60Cosmic2ByFill->Fill(fillstr.c_str(), jetN60Cosmic2ByFill_.histogram(fill)->GetMean() );
      hMeanN60Cosmic2ByFill->SetBinError( hMeanN60Cosmic2ByFill->GetXaxis()->FindBin(fillstr.c_str()), jetN60Cosmic2ByFill_.histogram(fill)->GetMeanError() );

      hMeanN60BeamHaloByFill->Fill(fillstr.c_str(), jetN60BeamHaloByFill_.histogram(fill)->GetMean() );
      hMeanN60BeamHaloByFill->SetBinError( hMeanN60BeamHaloByFill->GetXaxis()->FindBin(fillstr.c_str()), jetN60BeamHaloByFill_.histogram(fill)->GetMeanError() );

      hMeanN60BeamGasByFill->Fill(fillstr.c_str(), jetN60BeamGasByFill_.histogram(fill)->GetMean() );      hMeanN60BeamGasByFill->SetBinError( hMeanN60BeamGasByFill->GetXaxis()->FindBin(fillstr.c_str()), jetN60BeamGasByFill_.histogram(fill)->GetMeanError() );

      hMeanN60VertexByFill->Fill(fillstr.c_str(), jetN60VertexByFill_.histogram(fill)->GetMean() );
      hMeanN60VertexByFill->SetBinError( hMeanN60VertexByFill->GetXaxis()->FindBin(fillstr.c_str()), jetN60VertexByFill_.histogram(fill)->GetMeanError() );

      hMeanN60UnidentifiedByFill->Fill(fillstr.c_str(), jetN60UnidentifiedByFill_.histogram(fill)->GetMean() );
      hMeanN60UnidentifiedByFill->SetBinError( hMeanN60UnidentifiedByFill->GetXaxis()->FindBin(fillstr.c_str()), jetN60UnidentifiedByFill_.histogram(fill)->GetMeanError() );

      // N90 mean
      hMeanN90NoiseByFill->Fill(fillstr.c_str(), jetN90NoiseByFill_.histogram(fill)->GetMean() );
      hMeanN90NoiseByFill->SetBinError( hMeanN90NoiseByFill->GetXaxis()->FindBin(fillstr.c_str()), jetN90NoiseByFill_.histogram(fill)->GetMeanError() );

      hMeanN90CosmicByFill->Fill(fillstr.c_str(), jetN90CosmicByFill_.histogram(fill)->GetMean() );
      hMeanN90CosmicByFill->SetBinError( hMeanN90CosmicByFill->GetXaxis()->FindBin(fillstr.c_str()), jetN90CosmicByFill_.histogram(fill)->GetMeanError() );

      hMeanN90Cosmic2ByFill->Fill(fillstr.c_str(), jetN90Cosmic2ByFill_.histogram(fill)->GetMean() );
      hMeanN90Cosmic2ByFill->SetBinError( hMeanN90Cosmic2ByFill->GetXaxis()->FindBin(fillstr.c_str()), jetN90Cosmic2ByFill_.histogram(fill)->GetMeanError() );

      hMeanN90BeamHaloByFill->Fill(fillstr.c_str(), jetN90BeamHaloByFill_.histogram(fill)->GetMean() );
      hMeanN90BeamHaloByFill->SetBinError( hMeanN90BeamHaloByFill->GetXaxis()->FindBin(fillstr.c_str()), jetN90BeamHaloByFill_.histogram(fill)->GetMeanError() );

      hMeanN90BeamGasByFill->Fill(fillstr.c_str(), jetN90BeamGasByFill_.histogram(fill)->GetMean() );      hMeanN90BeamGasByFill->SetBinError( hMeanN90BeamGasByFill->GetXaxis()->FindBin(fillstr.c_str()), jetN90BeamGasByFill_.histogram(fill)->GetMeanError() );

      hMeanN90VertexByFill->Fill(fillstr.c_str(), jetN90VertexByFill_.histogram(fill)->GetMean() );
      hMeanN90VertexByFill->SetBinError( hMeanN90VertexByFill->GetXaxis()->FindBin(fillstr.c_str()), jetN90VertexByFill_.histogram(fill)->GetMeanError() );

      hMeanN90UnidentifiedByFill->Fill(fillstr.c_str(), jetN90UnidentifiedByFill_.histogram(fill)->GetMean() );
      hMeanN90UnidentifiedByFill->SetBinError( hMeanN90UnidentifiedByFill->GetXaxis()->FindBin(fillstr.c_str()), jetN90UnidentifiedByFill_.histogram(fill)->GetMeanError() );

      // NTow mean
      hMeanNTowNoiseByFill->Fill(fillstr.c_str(), jetNTowNoiseByFill_.histogram(fill)->GetMean() );
      hMeanNTowNoiseByFill->SetBinError( hMeanNTowNoiseByFill->GetXaxis()->FindBin(fillstr.c_str()), jetNTowNoiseByFill_.histogram(fill)->GetMeanError() );

      hMeanNTowCosmicByFill->Fill(fillstr.c_str(), jetNTowCosmicByFill_.histogram(fill)->GetMean() );
      hMeanNTowCosmicByFill->SetBinError( hMeanNTowCosmicByFill->GetXaxis()->FindBin(fillstr.c_str()), jetNTowCosmicByFill_.histogram(fill)->GetMeanError() );

      hMeanNTowCosmic2ByFill->Fill(fillstr.c_str(), jetNTowCosmic2ByFill_.histogram(fill)->GetMean() );
      hMeanNTowCosmic2ByFill->SetBinError( hMeanNTowCosmic2ByFill->GetXaxis()->FindBin(fillstr.c_str()), jetNTowCosmic2ByFill_.histogram(fill)->GetMeanError() );

      hMeanNTowBeamHaloByFill->Fill(fillstr.c_str(), jetNTowBeamHaloByFill_.histogram(fill)->GetMean() );
      hMeanNTowBeamHaloByFill->SetBinError( hMeanNTowBeamHaloByFill->GetXaxis()->FindBin(fillstr.c_str()), jetNTowBeamHaloByFill_.histogram(fill)->GetMeanError() );

      hMeanNTowBeamGasByFill->Fill(fillstr.c_str(), jetNTowBeamGasByFill_.histogram(fill)->GetMean() );      hMeanNTowBeamGasByFill->SetBinError( hMeanNTowBeamGasByFill->GetXaxis()->FindBin(fillstr.c_str()), jetNTowBeamGasByFill_.histogram(fill)->GetMeanError() );

      hMeanNTowVertexByFill->Fill(fillstr.c_str(), jetNTowVertexByFill_.histogram(fill)->GetMean() );
      hMeanNTowVertexByFill->SetBinError( hMeanNTowVertexByFill->GetXaxis()->FindBin(fillstr.c_str()), jetNTowVertexByFill_.histogram(fill)->GetMeanError() );

      hMeanNTowUnidentifiedByFill->Fill(fillstr.c_str(), jetNTowUnidentifiedByFill_.histogram(fill)->GetMean() );
      hMeanNTowUnidentifiedByFill->SetBinError( hMeanNTowUnidentifiedByFill->GetXaxis()->FindBin(fillstr.c_str()), jetNTowUnidentifiedByFill_.histogram(fill)->GetMeanError() );


    }

  }

  std::cout << "Total livetime in fills : " << hLivetimeByFill->Integral() << std::endl;
  std::cout << std::endl;

  // run histograms
  TH1D* hLivetimeByRun = new TH1D("hLivetimeByRun", "", nRuns, 0, 0);
  TH1D* hTriggerRateByRun = new TH1D("hTriggerRateByRun", "", nRuns, 0, 0);
  TH1D* hEventRateByRun = new TH1D("hEventRateByRun", "", nRuns, 0, 0);
  TH1D* hNoiseRateByRun = new TH1D("hNoiseRateByRun", "Noise flag", nRuns, 0, 0);
  TH1D* hCosmicRateByRun = new TH1D("hCosmicRateByRun", "N_{#mu} > 0", nRuns, 0, 0);
  TH1D* hBeamHaloRateByRun = new TH1D("hBeamHaloRateByRun", "Beam halo flag", nRuns, 0, 0);
  TH1D* hBeamGasRateByRun = new TH1D("hBeamGasRateByRun", "N_{trk} > 0 and not beam halo flag", nRuns, 0, 0);
  TH1D* hVertexRateByRun = new TH1D("hVertexRateByRun", "N_{vtx} > 0", nRuns, 0, 0);

  std::cout << "All triggers : " << std::endl;
  std::cout << "Run \t LS \t Livetime \t Nevents \t Rate" << std::endl;

  std::sort(runList_.begin(), runList_.end());
  std::vector<unsigned long>::const_iterator ritr;
  for (ritr=runList_.begin(); ritr!=runList_.end(); ++ritr) {
    unsigned long run = *ritr;
    std::stringstream sstr;
    sstr << run;
    std::string runstr = sstr.str();

    double livetime = livetimeByRun.at(run);
    int nLumis = nLumisByRun.at(run);
    int nTriggers = nTriggerByRun_.at(run);

    std::cout << runstr << "\t"
	      << nLumis << "\t"
	      << livetime << "\t"
	      << nTriggers << "\t"
	      << nTriggers/(nLumis*TIME_PER_LS) << std::endl;


    hLivetimeByRun->Fill(runstr.c_str(), livetime);

    hEventRateByRun->Fill(runstr.c_str(), 0.);
    hTriggerRateByRun->Fill(runstr.c_str(), 0.);
    hNoiseRateByRun->Fill(runstr.c_str(), 0.);
    hCosmicRateByRun->Fill(runstr.c_str(), 0.);
    hBeamHaloRateByRun->Fill(runstr.c_str(), 0.);
    hBeamGasRateByRun->Fill(runstr.c_str(), 0.);
    hVertexRateByRun->Fill(runstr.c_str(), 0.);

    if (nLumis>0) {
      for (unsigned long i=0; i<nTriggerByRun_.at(*ritr); ++i) 
	hTriggerRateByRun->Fill(runstr.c_str(), 1./(nLumis*TIME_PER_LS));
    }      

    if (livetime>0.) {

      for (unsigned long i=0; i<nTriggerByRun_.at(*ritr); ++i) 
	hEventRateByRun->Fill(runstr.c_str(), 1./livetime);

      for (unsigned long i=0; i<nNoiseFlagByRun_.at(*ritr); ++i) 
	hNoiseRateByRun->Fill(runstr.c_str(), 1./livetime);
      
      for (unsigned long i=0; i<nCosmicByRun_.at(*ritr); ++i) 
	hCosmicRateByRun->Fill(runstr.c_str(), 1./livetime);
      
      for (unsigned long i=0; i<nBeamHaloByRun_.at(*ritr); ++i) 
	hBeamHaloRateByRun->Fill(runstr.c_str(), 1./livetime);
      
      for (unsigned long i=0; i<nBeamGasByRun_.at(*ritr); ++i) 
	hBeamGasRateByRun->Fill(runstr.c_str(), 1./livetime);

      for (unsigned long i=0; i<nVertexByRun_.at(*ritr); ++i) 
	hVertexRateByRun->Fill(runstr.c_str(), 1./livetime);

    }

  }

  std::cout << "Total livetime in runs : " << hLivetimeByRun->Integral() << std::endl;

  ofile_->cd();

  hLivetimeByFill->Write("",TObject::kOverwrite);
  hEventRateByFill->Write("",TObject::kOverwrite);
  hNoiseRateByFill->Write("",TObject::kOverwrite);
  hCosmicRateByFill->Write("",TObject::kOverwrite);
  hCosmic2RateByFill->Write("",TObject::kOverwrite);
  hCosmic3RateByFill->Write("",TObject::kOverwrite);
  hNM1CosmicRateByFill->Write("",TObject::kOverwrite);
  hBeamHaloRateByFill->Write("",TObject::kOverwrite);
  hBeamGasRateByFill->Write("",TObject::kOverwrite);
  hVertexRateByFill->Write("",TObject::kOverwrite);
  hUnidentifiedRateByFill->Write("",TObject::kOverwrite);

  hMeanENoiseByFill->Write("",TObject::kOverwrite);
  hMeanECosmicByFill->Write("",TObject::kOverwrite);
  hMeanEBeamHaloByFill->Write("",TObject::kOverwrite);
  hMeanEBeamGasByFill->Write("",TObject::kOverwrite);
  hMeanEVertexByFill->Write("",TObject::kOverwrite);
  hMeanEUnidentifiedByFill->Write("",TObject::kOverwrite);

  hStdDevENoiseByFill->Write("",TObject::kOverwrite);
  hStdDevECosmicByFill->Write("",TObject::kOverwrite);
  hStdDevEBeamHaloByFill->Write("",TObject::kOverwrite);
  hStdDevEBeamGasByFill->Write("",TObject::kOverwrite);
  hStdDevEVertexByFill->Write("",TObject::kOverwrite);
  hStdDevEUnidentifiedByFill->Write("",TObject::kOverwrite);

  hLivetimeByRun->Write("",TObject::kOverwrite);
  hTriggerRateByRun->Write("",TObject::kOverwrite);
  hEventRateByRun->Write("",TObject::kOverwrite);
  hNoiseRateByRun->Write("",TObject::kOverwrite);
  hCosmicRateByRun->Write("",TObject::kOverwrite);
  hBeamHaloRateByRun->Write("",TObject::kOverwrite);
  hBeamGasRateByRun->Write("",TObject::kOverwrite);
  hVertexRateByRun->Write("",TObject::kOverwrite);

  jetENoiseByFill_.save();
  jetECosmicByFill_.save();
  jetEBeamHaloByFill_.save();
  jetEBeamGasByFill_.save();
  jetEVertexByFill_.save();
  jetEUnidentifiedByFill_.save();

  jetN60NoiseByFill_.save();
  jetN60CosmicByFill_.save();
  jetN60BeamHaloByFill_.save();
  jetN60BeamGasByFill_.save();
  jetN60VertexByFill_.save();
  jetN60UnidentifiedByFill_.save();

  jetN90NoiseByFill_.save();
  jetN90CosmicByFill_.save();
  jetN90BeamHaloByFill_.save();
  jetN90BeamGasByFill_.save();
  jetN90VertexByFill_.save();
  jetN90UnidentifiedByFill_.save();

  jetNTowNoiseByFill_.save();
  jetNTowCosmicByFill_.save();
  jetNTowBeamHaloByFill_.save();
  jetNTowBeamGasByFill_.save();
  jetNTowVertexByFill_.save();
  jetNTowUnidentifiedByFill_.save();

}



// this is the main program, no need to do anything here
int main(int argc, char* argv[]) {

  // sum of squares error info for histograms
  TH1D::SetDefaultSumw2();

  // create analysis
  BackgroundStability analyser(argc, argv);

  analyser.setup();

  analyser.cuts().print(std::cout);

  analyser.loop();

  return 0;

}
