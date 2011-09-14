#ifndef StoppedHSCPHistogrammer_h
#define StoppedHSCPHistogrammer_h

// system include files
#include <memory>

// framework
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"

#include "FWCore/Framework/interface/ESHandle.h"

#include "FWCore/Framework/interface/Run.h"
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

  StoppedHSCPHistogrammer();
  ~StoppedHSCPHistogrammer();

  virtual void beginJob() ;
  virtual void beginRun(const edm::Run&, const edm::EventSetup&) ;
  virtual void analyze(const edm::Event&, const edm::EventSetup&);
  virtual void endJob() ;  

  // fill histograms for BX normalisation
  void makeBXNormHistogram(unsigned long fill);

 private:

  // output file
  edm::Service<TFileService> fs_;

  LhcFills fills_;

  std::vector<unsigned long> fillList_;
  std::vector<TH1D*> bxNormHistos_;

};

#endif
