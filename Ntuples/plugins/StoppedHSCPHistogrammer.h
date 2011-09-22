#ifndef StoppedHSCPHistogrammer_h
#define StoppedHSCPHistogrammer_h

// system include files
#include <memory>

// framework
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"

#include "FWCore/Framework/interface/ESHandle.h"

#include "FWCore/Framework/interface/Run.h"
#include "FWCore/Framework/interface/LuminosityBlock.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "FWCore/MessageLogger/interface/MessageLogger.h"

#include "DataFormats/Common/interface/ConditionsInEdm.h"

// ROOT output stuff
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "TH1.h"

// Helper classes
#include "StoppedHSCP/Ntuples/interface/LhcFills.h"


class StoppedHSCPHistogrammer : public edm::EDAnalyzer {

 public:

  explicit StoppedHSCPHistogrammer(const edm::ParameterSet& iPSet);
  ~StoppedHSCPHistogrammer();

  virtual void beginJob() ;
  virtual void beginRun(const edm::Run&, const edm::EventSetup&) ;
  virtual void beginLuminosityBlock(const edm::LuminosityBlock&, const edm::EventSetup&) ;
  virtual void analyze(const edm::Event&, const edm::EventSetup&);
  virtual void endJob() ;  

  // methods for booking histograms
  void bookPerRunHistograms(unsigned long run);
  void bookPerFillHistograms(unsigned long fill);

 private:

  // output file
  edm::Service<TFileService> fs_;

  LhcFills fills_;

  // per-run histograms
  std::vector<unsigned long> runList_;
  std::vector<TH1D*> runLSHistos_;
  std::vector<TH1D*> runEventLSHistos_;


  // per-fill histograms
  std::vector<unsigned long> fillList_;
  std::vector<TH1D*> bxNormHistos_;

};

#endif
