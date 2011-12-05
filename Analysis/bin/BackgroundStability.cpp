#ifndef BackgroundStability_h
#define BackgroundStability_h

#include "StoppedHSCP/Analysis/interface/BasicAnalyser.h"
#include "StoppedHSCP/Analysis/interface/MultiHistogram1D.h"
#include "StoppedHSCP/Ntuples/interface/Constants.h"

#include "TFile.h"
#include "TChain.h"
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
  std::vector<unsigned long> nBeamHaloByFill_;
  std::vector<unsigned long> nBeamGasByFill_;
  std::vector<unsigned long> nVertexByFill_;

  // energy distributions for different types
  MultiHistogram1D jetENoiseByFill_;
  MultiHistogram1D jetECosmicByFill_;
  MultiHistogram1D jetEBeamHaloByFill_;
  MultiHistogram1D jetEBeamGasByFill_;
  MultiHistogram1D jetEVertexByFill_;

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
  jetEBeamHaloByFill_.setup(ofile_, "hJetEBeamHaloByFill", "Beam Halo", 200, 0., 200.);
  jetEBeamGasByFill_.setup(ofile_, "hJetEBeamGasByFill", "Beam gas", 200, 0., 200.);
  jetEVertexByFill_.setup(ofile_, "hJetEVertexByFill", "Vertex", 200, 0., 200.);

  reset();
  nextEvent();

  for (unsigned long i=0; i<maxEvents_; ++i, nextEvent()) {

    // occasional print out
    if (i%100000==0) {
      std::cout << "Processing " << i << "th event of " <<maxEvents_<< std::endl;
    }

    // YOUR CODE HERE

    // count lumi sections
    std::pair<unsigned long, unsigned long> runLumiPair(event_->run, event_->lb);
    std::vector<std::pair<unsigned long, unsigned long> >::const_iterator itr = 
      find(runLumiPairs_.begin(), runLumiPairs_.end(), runLumiPair);
    if (itr == runLumiPairs_.end()) {
      runLumiPairs_.push_back(runLumiPair);
    }

    // record fills run over
    unsigned fill = event_->fill;
    std::vector<unsigned long>::const_iterator itr2 = find(fillList_.begin(), fillList_.end(), fill);
    if (itr2 == fillList_.end()) {
      fillList_.push_back(fill);
      jetENoiseByFill_.fill(fill, 0., 0.);
      jetECosmicByFill_.fill(fill, 0., 0.);
      jetEBeamHaloByFill_.fill(fill, 0., 0.);
      jetEBeamGasByFill_.fill(fill, 0., 0.);
      jetEVertexByFill_.fill(fill, 0., 0.);
    }
    if (fill > maxFill) maxFill = fill;

    // keep vectors big enough
    if (nTriggerByFill_.size() < fill+1) nTriggerByFill_.resize(fill+1, 0);
    if (nNoiseFlagByFill_.size() < fill+1) nNoiseFlagByFill_.resize(fill+1, 0);
    if (nCosmicByFill_.size() < fill+1) nCosmicByFill_.resize(fill+1, 0);
    if (nBeamHaloByFill_.size() < fill+1) nBeamHaloByFill_.resize(fill+1, 0);
    if (nBeamGasByFill_.size() < fill+1) nBeamGasByFill_.resize(fill+1, 0);
    if (nVertexByFill_.size() < fill+1) nVertexByFill_.resize(fill+1, 0);

    // event quantities
    bool trig       = event_->hltJetE50NoBptx3BXNoHalo;
    double e        = event_->jetE[0];
    double eta      = event_->jetEta[0];
    bool isNoise    = !event_->noiseFilterResult;
    bool isCosmic   = event_->mu_N > 0 && !event_->beamHalo_CSCLoose;
    bool isBeamHalo = event_->beamHalo_CSCLoose;
    bool isBeamGas  = event_->track_N>0 && !event_->beamHalo_CSCLoose;
    bool isVtx      = event_->nVtx>0;

    // only consider events passing main trigger with jet in barrel
    if ( !(trig && e>50. && fabs(eta)<1.3) ) continue;

    nTriggerByFill_.at(fill) += 1;

    if (isNoise) {
      nNoiseFlagByFill_.at(fill) += 1;
      jetENoiseByFill_.fill(fill, event_->jetE[0]);
    }
    if (isCosmic) {
      nCosmicByFill_.at(fill) += 1;
      jetECosmicByFill_.fill(fill, event_->jetE[0]);
    }
    if (isBeamHalo) {
      nBeamHaloByFill_.at(fill) += 1;
      jetEBeamHaloByFill_.fill(fill, event_->jetE[0]);
    }
    if (isBeamGas) {
      nBeamGasByFill_.at(fill) += 1;
      jetEBeamGasByFill_.fill(fill, event_->jetE[0]);
    }
    if (isVtx) {
      nVertexByFill_.at(fill) += 1;
      jetEVertexByFill_.fill(fill, event_->jetE[0]);
    }

    // per fill histograms


    // per Run stuff
    unsigned long run = event_->run;
    std::vector<unsigned long>::const_iterator itr3 = find(runList_.begin(), runList_.end(), run);
    if (itr3 == runList_.end()) runList_.push_back(run);
    if (run > maxRun) maxRun = run;

    // keep vectors big enough
    if (nTriggerByRun_.size() < run+1) nTriggerByRun_.resize(run+1, 0);
    if (nNoiseFlagByRun_.size() < run+1) nNoiseFlagByRun_.resize(run+1, 0);
    if (nCosmicByRun_.size() < run+1) nCosmicByRun_.resize(run+1, 0);
    if (nBeamHaloByRun_.size() < run+1) nBeamHaloByRun_.resize(run+1, 0);
    if (nBeamGasByRun_.size() < run+1) nBeamGasByRun_.resize(run+1, 0);
    if (nVertexByRun_.size() < run+1) nVertexByRun_.resize(run+1, 0);

    nTriggerByRun_.at(run) += 1;
    if (isNoise)    nNoiseFlagByRun_.at(run) += 1;
    if (isCosmic)   nCosmicByRun_.at(run) += 1;
    if (isBeamHalo) nBeamHaloByRun_.at(run) += 1;
    if (isBeamGas)  nBeamGasByRun_.at(run) += 1;
    if (isVtx)      nVertexByRun_.at(run) += 1;

  }

  // summary
  unsigned nFills = fillList_.size();
  unsigned nRuns  = runList_.size();


  // SAVE HISTOGRAMS HERE

  // count lumis for normalisation factor
  std::vector<double> livetimeByFill_(maxFill+1);
  std::vector<double> livetimeByRun_(maxRun+1);

  std::vector<std::pair<unsigned long, unsigned long> >::const_iterator litr;
  for (litr=runLumiPairs_.begin(); litr!=runLumiPairs_.end(); ++litr) {
    unsigned long r = litr->first;
    unsigned long f = lhcFills_.getFillFromRun(r);
    livetimeByFill_.at(f) += TIME_PER_LS;
    livetimeByRun_.at(r) += TIME_PER_LS;
  }

  // fill histograms
  TH1D* hLivetimeByFill = new TH1D("hLivetimeByFill", "", nFills, 0, 0);
  TH1D* hTriggerRateByFill = new TH1D("hTriggerRateByFill", "", nFills, 0, 0);
  TH1D* hNoiseRateByFill = new TH1D("hNoiseRateByFill", "Noise flag", nFills, 0, 0);
  TH1D* hCosmicRateByFill = new TH1D("hCosmicRateByFill", "N_{#mu} > 0", nFills, 0, 0);
  TH1D* hBeamHaloRateByFill = new TH1D("hBeamHaloRateByFill", "Beam halo flag", nFills, 0, 0);
  TH1D* hBeamGasRateByFill = new TH1D("hBeamGasRateByFill", "N_{trk} > 0 and not beam halo flag", nFills, 0, 0);
  TH1D* hVertexRateByFill = new TH1D("hVertexRateByFill", "N_{vtx} > 0", nFills, 0, 0);

  TH1D* hMeanENoiseByFill = new TH1D("hMeanENoiseByFill", "", nFills, 0, 0);
  TH1D* hMeanECosmicByFill = new TH1D("hMeanECosmicByFill", "", nFills, 0, 0);
  TH1D* hMeanEBeamHaloByFill = new TH1D("hMeanEBeamHaloByFill", "", nFills, 0, 0);
  TH1D* hMeanEBeamGasByFill = new TH1D("hMeanEBeamGasByFill", "", nFills, 0, 0);
  TH1D* hMeanEVertexByFill = new TH1D("hMeanEVertexByFill", "", nFills, 0, 0);

  std::sort(fillList_.begin(), fillList_.end());
  std::vector<unsigned long>::const_iterator fitr;
  for (fitr=fillList_.begin(); fitr!=fillList_.end(); ++fitr) {
    unsigned long fill = *fitr;
    std::stringstream sstr;
    sstr << (fill);
    std::string fillstr = sstr.str();

    double livetime = livetimeByFill_.at(fill);

    hLivetimeByFill->Fill(fillstr.c_str(), livetime);

    if (livetime>0.) {

      for (unsigned long i=0; i<nTriggerByFill_.at(fill); ++i) 
	hTriggerRateByFill->Fill(fillstr.c_str(), 1./livetime);

      for (unsigned long i=0; i<nNoiseFlagByFill_.at(fill); ++i) 
	hNoiseRateByFill->Fill(fillstr.c_str(), 1./livetime);
      
      for (unsigned long i=0; i<nCosmicByFill_.at(fill); ++i) 
	hCosmicRateByFill->Fill(fillstr.c_str(), 1./livetime);
      
      for (unsigned long i=0; i<nBeamHaloByFill_.at(fill); ++i) 
	hBeamHaloRateByFill->Fill(fillstr.c_str(), 1./livetime);
      
      for (unsigned long i=0; i<nBeamGasByFill_.at(fill); ++i) 
	hBeamGasRateByFill->Fill(fillstr.c_str(), 1./livetime);

      for (unsigned long i=0; i<nVertexByFill_.at(fill); ++i) 
	hVertexRateByFill->Fill(fillstr.c_str(), 1./livetime);

      hMeanENoiseByFill->Fill(fillstr.c_str(), jetENoiseByFill_.histogram(fill)->GetMean() );
      hMeanECosmicByFill->Fill(fillstr.c_str(), jetECosmicByFill_.histogram(fill)->GetMean() );
      hMeanEBeamHaloByFill->Fill(fillstr.c_str(), jetEBeamHaloByFill_.histogram(fill)->GetMean() );
      hMeanEBeamGasByFill->Fill(fillstr.c_str(), jetEBeamGasByFill_.histogram(fill)->GetMean() );
      hMeanEVertexByFill->Fill(fillstr.c_str(), jetEVertexByFill_.histogram(fill)->GetMean() );

    }

  }

  // run histograms
  TH1D* hLivetimeByRun = new TH1D("hLivetimeByRun", "", nRuns, 0, 0);
  TH1D* hTriggerRateByRun = new TH1D("hTriggerRateByRun", "", nRuns, 0, 0);
  TH1D* hNoiseRateByRun = new TH1D("hNoiseRateByRun", "Noise flag", nRuns, 0, 0);
  TH1D* hCosmicRateByRun = new TH1D("hCosmicRateByRun", "N_{#mu} > 0", nRuns, 0, 0);
  TH1D* hBeamHaloRateByRun = new TH1D("hBeamHaloRateByRun", "Beam halo flag", nRuns, 0, 0);
  TH1D* hBeamGasRateByRun = new TH1D("hBeamGasRateByRun", "N_{trk} > 0 and not beam halo flag", nRuns, 0, 0);
  TH1D* hVertexRateByRun = new TH1D("hVertexRateByRun", "N_{vtx} > 0", nRuns, 0, 0);

  std::sort(runList_.begin(), runList_.end());
  std::vector<unsigned long>::const_iterator ritr;
  for (ritr=runList_.begin(); ritr!=runList_.end(); ++ritr) {
    std::stringstream sstr;
    sstr << (*ritr);
    std::string runstr = sstr.str();

    double livetime = livetimeByRun_.at(*ritr);

    hLivetimeByRun->Fill(runstr.c_str(), livetime);

    if (livetime>0.) {

      for (unsigned long i=0; i<nTriggerByRun_.at(*ritr); ++i) 
	hTriggerRateByRun->Fill(runstr.c_str(), 1./livetime);

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

  hLivetimeByFill->Write("",TObject::kOverwrite);
  hTriggerRateByFill->Write("",TObject::kOverwrite);
  hNoiseRateByFill->Write("",TObject::kOverwrite);
  hCosmicRateByFill->Write("",TObject::kOverwrite);
  hBeamHaloRateByFill->Write("",TObject::kOverwrite);
  hBeamGasRateByFill->Write("",TObject::kOverwrite);
  hVertexRateByFill->Write("",TObject::kOverwrite);

  hMeanENoiseByFill->Write("",TObject::kOverwrite);
  hMeanECosmicByFill->Write("",TObject::kOverwrite);
  hMeanEBeamHaloByFill->Write("",TObject::kOverwrite);
  hMeanEBeamGasByFill->Write("",TObject::kOverwrite);
  hMeanEVertexByFill->Write("",TObject::kOverwrite);

  hLivetimeByRun->Write("",TObject::kOverwrite);
  hTriggerRateByRun->Write("",TObject::kOverwrite);
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
