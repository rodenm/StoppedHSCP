// -*- C++ -*-
//
// Package:    TriggerValidator
// Class:      TriggerValidator
// 
/**\class TriggerValidator TriggerValidator.cc StoppedHSCP/TriggerValidator/src/TriggerValidator.cc

 Description: Validate StoppedHSCP trigger and make plots

 Implementation:
     <Notes on implementation>
*/
//
// Original Author:  Jim Brooke
//         Created:  Fri Oct  9 14:28:32 CEST 2009
// $Id: TriggerValidator.cc,v 1.2 2010/03/18 13:06:10 jbrooke Exp $
//
//


// system include files
#include <memory>
#include <iostream>

// ROOT
#include "TH1D.h"

// framework
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "FWCore/Framework/interface/ESHandle.h"

#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"

// L1
#include "CondFormats/L1TObjects/interface/L1GtTriggerMenu.h"
#include "CondFormats/DataRecord/interface/L1GtTriggerMenuRcd.h"
#include "DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerReadoutSetupFwd.h"
#include "DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerReadoutSetup.h"
#include "DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerReadoutRecord.h"

#include "DataFormats/L1Trigger/interface/L1JetParticleFwd.h"
#include "DataFormats/L1Trigger/interface/L1JetParticle.h"

#include "SimDataFormats/GeneratorProducts/interface/HepMCProduct.h"

// HLT
#include "DataFormats/HLTReco/interface/TriggerEvent.h"
#include "DataFormats/HLTReco/interface/TriggerTypeDefs.h"
#include "DataFormats/HLTReco/interface/TriggerObject.h"
#include "DataFormats/Common/interface/TriggerResults.h"
#include "FWCore/Utilities/interface/InputTag.h"

#include "DataFormats/JetReco/interface/CaloJetCollection.h"

#include "HLTrigger/HLTcore/interface/HLTConfigProvider.h"


//
// class decleration
//

class TriggerValidator : public edm::EDAnalyzer {
public:
  explicit TriggerValidator(const edm::ParameterSet&);
  ~TriggerValidator();
  
  
private:
  virtual void beginJob() ;
  virtual void beginRun(const edm::Run&, const edm::EventSetup&) ;
  virtual void analyze(const edm::Event&, const edm::EventSetup&);
  virtual void endJob() ;
  
  // HLT config helper
  HLTConfigProvider hltOnConfig_;
  unsigned hltOnPathIndex_;
  HLTConfigProvider hltOffConfig_;
  unsigned hltOffPathIndex_;

  edm::InputTag l1BitsTag_;
  edm::InputTag hltTag_;
  edm::InputTag offlineHltTag_;
  edm::InputTag offlineHltEventTag_;
  edm::InputTag hltL3Tag_;
  edm::InputTag hltJetTag_;

  // results
  edm::Service<TFileService> fs_;

  unsigned nEvents_;
  unsigned nHLTOnPass_;
  unsigned nHLTOffPass_;
  unsigned nHLTOnPassOffFail_;
  unsigned nHLTOnFailOffPass_;
  
  TH1D *hltPassJetE_, *hltPassJetEta_, *hltPassJetPhi_;
  TH1D *hltFailJetE_, *hltFailJetEta_, *hltFailJetPhi_;
  TH1D *hltOnPOffFJetE_, *hltOnPOffFJetEta_, *hltOnPOffFJetPhi_;
  TH1D *hltOnFOffPJetE_, *hltOnFOffPJetEta_, *hltOnFOffPJetPhi_;

};

//
// constants, enums and typedefs
//

//
// static data member definitions
//

//
// constructors and destructor
//
TriggerValidator::TriggerValidator(const edm::ParameterSet& iConfig) :
  l1BitsTag_(iConfig.getUntrackedParameter<edm::InputTag>("l1BitsTag",edm::InputTag("gtDigis"))),
  hltTag_(iConfig.getUntrackedParameter<edm::InputTag>("hltTag",edm::InputTag("TriggerResults","","HLT"))),
  offlineHltTag_(iConfig.getUntrackedParameter<edm::InputTag>("offlineHltTag",edm::InputTag("TriggerResults","","HLT2"))),
  offlineHltEventTag_(iConfig.getUntrackedParameter<edm::InputTag>("offlineHltEventTag",edm::InputTag("hltTriggerSummaryAOD","","HLT2"))),
  hltL3Tag_(iConfig.getUntrackedParameter<edm::InputTag>("hltL3Tag",edm::InputTag("hltStoppedHSCP1CaloJetEnergy","","HLT2"))),
  hltJetTag_(iConfig.getUntrackedParameter<edm::InputTag>("hltJetTag",edm::InputTag("hltStoppedHSCPIterativeCone5CaloJets","","HLT2"))),
  nEvents_(0),
  nHLTOnPass_(0),
  nHLTOffPass_(0),
  nHLTOnPassOffFail_(0),
  nHLTOnFailOffPass_(0)
{
   //now do what ever initialization is needed

}


TriggerValidator::~TriggerValidator()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called to for each event  ------------
void
TriggerValidator::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   using namespace edm;

   // trigger bits
   bool l1SingleJet10_NotBptxC=false;
   bool hlt_StoppedHSCP_8E29=false;
   bool hlt_StoppedHSCP_8E29_offline=false;

   // L1 results
   edm::ESHandle<L1GtTriggerMenu> menuRcd;
   iSetup.get<L1GtTriggerMenuRcd>().get(menuRcd) ;
   const L1GtTriggerMenu* menu = menuRcd.product();
   
   edm::Handle< L1GlobalTriggerReadoutRecord > gtReadoutRecord;
   iEvent.getByLabel(l1BitsTag_, gtReadoutRecord);
   
   const  DecisionWord& gtDecisionWordBeforeMask = gtReadoutRecord->decisionWord();
   l1SingleJet10_NotBptxC = menu->gtAlgorithmResult( "L1_SingleJet10_NotBptxC", gtDecisionWordBeforeMask);
   
   // HLT results
   edm::Handle<edm::TriggerResults> HLTR;
   iEvent.getByLabel(hltTag_, HLTR);

   if (HLTR.isValid()) {
     // triggerIndex must be less than the size of HLTR or you get a CMSException: _M_range_check
     if (hltOnPathIndex_ < HLTR->size()) hlt_StoppedHSCP_8E29 = HLTR->accept(hltOnPathIndex_); 
   }
   else {
     edm::LogWarning("TrigVal") << "Online HLT results not found" << std::endl;
   }

   
   // get offline HLT result
   edm::Handle<edm::TriggerResults> HLTR_offline;
   iEvent.getByLabel(offlineHltTag_, HLTR_offline);

   if (HLTR_offline.isValid()) {
     // triggerIndex must be less than the size of HLTR or you get a CMSException: _M_range_check
     if (hltOffPathIndex_ < HLTR_offline->size()) hlt_StoppedHSCP_8E29_offline = HLTR_offline->accept(hltOffPathIndex_); 
   }
   else {
     edm::LogWarning("TrigVal") << "Offline HLT results not found" << std::endl;
   }

   // get HLT jets
//    edm::Handle<trigger::TriggerEvent> trgEvent;
//    iEvent.getByLabel(offlineHltEventTag_, trgEvent);
   
//    // for Stopped HSCP L3 filter  
//    unsigned filterIndex=0;     
//    trigger::TriggerObjectCollection hltObjects;
//    trigger::Keys hltKeys;

//    if (trgEvent.isValid()) {
//      filterIndex = trgEvent->filterIndex(hltL3Tag_);
//      if (filterIndex < trgEvent->sizeFilters()) {       
//        hltObjects = trgEvent->getObjects();
//        hltKeys = trgEvent->filterKeys(filterIndex);
//      }
//    }

   // get HLT jet collection
   edm::Handle<reco::CaloJetCollection> hltJets;
   iEvent.getByLabel(hltJetTag_, hltJets);
   
   // count HLT outcome errors
   if (hlt_StoppedHSCP_8E29) nHLTOnPass_++;
   if (hlt_StoppedHSCP_8E29_offline) nHLTOffPass_++;
   if (hlt_StoppedHSCP_8E29 && !hlt_StoppedHSCP_8E29_offline) nHLTOnPassOffFail_++;
   if (hlt_StoppedHSCP_8E29_offline && !hlt_StoppedHSCP_8E29) nHLTOnFailOffPass_++;

   // fill histos
   if (hltJets.isValid()) {
     if (hlt_StoppedHSCP_8E29_offline) {   
       for (reco::CaloJetCollection::const_iterator j = hltJets->begin(); 
	    j != hltJets->end();
	    ++j) {
	 hltPassJetE_->Fill(j->energy());
	 hltPassJetEta_->Fill(j->eta());
	 hltPassJetPhi_->Fill(j->phi());
       }
     }
     else {
       for (reco::CaloJetCollection::const_iterator j = hltJets->begin(); 
	    j != hltJets->end();
	    ++j) {
	 hltFailJetE_->Fill(j->energy());
	 hltFailJetEta_->Fill(j->eta());
	 hltFailJetPhi_->Fill(j->phi());
       }
     }
     
     
     if (hlt_StoppedHSCP_8E29 && !hlt_StoppedHSCP_8E29_offline) {
       for (reco::CaloJetCollection::const_iterator j = hltJets->begin(); 
	    j != hltJets->end();
	    ++j) {
	 hltOnPOffFJetE_->Fill(j->energy());
	 hltOnPOffFJetEta_->Fill(j->eta());
	 hltOnPOffFJetPhi_->Fill(j->phi());
       }
     }
     if (hlt_StoppedHSCP_8E29_offline && !hlt_StoppedHSCP_8E29) {
       for (reco::CaloJetCollection::const_iterator j = hltJets->begin(); 
	    j != hltJets->end();
	    ++j) {
	 hltOnFOffPJetE_->Fill(j->energy());
	 hltOnFOffPJetEta_->Fill(j->eta());
	 hltOnFOffPJetPhi_->Fill(j->phi());
       }
     }
   }
   
   nEvents_++;

}


//
void
TriggerValidator::beginRun(edm::Run const &iRun, edm::EventSetup const& iSetup)
{

  hltOnConfig_.init(hltTag_.process());
  hltOnPathIndex_ = hltOnConfig_.triggerIndex("HLT_StoppedHSCP_8E29");
  hltOffConfig_.init(offlineHltTag_.process());
  hltOffPathIndex_ = hltOffConfig_.triggerIndex("HLT_StoppedHSCP_8E29");

}

// ------------ method called once each job just before starting event loop  ------------
void 
TriggerValidator::beginJob()
{

  hltPassJetE_ = fs_->make<TH1D>("hltpasse", "HLT jet energy", 100, 0., 200.);
  hltPassJetEta_ = fs_->make<TH1D>("hltpasseta", "HLT jet #eta", 70, -3.5, 3.5);
  hltPassJetPhi_ = fs_->make<TH1D>("hltpassphi", "HLT jet #phi", 60, -3.4151, 3.4151);
  hltFailJetE_ = fs_->make<TH1D>("hltfaile", "HLT jet energy", 100, 0., 200.);
  hltFailJetEta_ = fs_->make<TH1D>("hltfaileta", "HLT jet #eta", 70, -3.5, 3.5);
  hltFailJetPhi_ = fs_->make<TH1D>("hltfailphi", "HLT jet #phi", 60, -3.4151, 3.4151);
  hltOnFOffPJetE_ = fs_->make<TH1D>("hltonfoffpe", "HLT jet energy", 100, 0., 200.);
  hltOnFOffPJetEta_ = fs_->make<TH1D>("hltonfoffpeta", "HLT jet #eta", 70, -3.5, 3.5);
  hltOnFOffPJetPhi_ = fs_->make<TH1D>("hltonfoffpphi", "HLT jet #phi", 60, -3.4151, 3.4151);
  hltOnPOffFJetE_ = fs_->make<TH1D>("hltonpofffe", "HLT jet energy", 100, 0., 200.);
  hltOnPOffFJetEta_ = fs_->make<TH1D>("hltonpofffeta", "HLT jet #eta", 70, -3.5, 3.5);
  hltOnPOffFJetPhi_ = fs_->make<TH1D>("hltonpofffphi", "HLT jet #phi", 60, -3.4151, 3.4151);

}

// ------------ method called once each job just after ending the event loop  ------------
void 
TriggerValidator::endJob() {

  edm::LogWarning("TrigVal") << nHLTOnPass_ << " online HLT passes in " << nEvents_ << " events" << std::endl;
  edm::LogWarning("TrigVal") << nHLTOffPass_ << " offline HLT passes in " << nEvents_ << " events" << std::endl;
  edm::LogWarning("TrigVal") << nHLTOnPassOffFail_ << " HLT passed online but failed offline" << std::endl;
  edm::LogWarning("TrigVal") << nHLTOnFailOffPass_ << " HLT failed online but passed offline" << std::endl;


}

//define this as a plug-in
DEFINE_FWK_MODULE(TriggerValidator);
