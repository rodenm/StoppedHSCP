// -*- C++ -*-
//
// Package:    HLTCaloJetEnergyFilter
// Class:      HLTCaloJetEnergyFilter
// 
/**\class HLTCaloJetEnergyFilter HLTCaloJetEnergyFilter.cc JBrooke/HLTCaloJetEnergyFilter/src/HLTCaloJetEnergyFilter.cc

 Description: <one line class summary>

 Implementation:
     <Notes on implementation>
*/
//
// Original Author:  Jim Brooke
//         Created:  Mon Jan 26 15:41:31 CET 2009
// $Id: HLTCaloJetEnergyFilter.cc,v 1.1 2009/02/04 21:18:41 jbrooke Exp $
//
//


// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDFilter.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "DataFormats/JetReco/interface/CaloJet.h"
#include "DataFormats/JetReco/interface/CaloJetCollection.h"


//
// class declaration
//

class HLTCaloJetEnergyFilter : public edm::EDFilter {
   public:
      explicit HLTCaloJetEnergyFilter(const edm::ParameterSet&);
      ~HLTCaloJetEnergyFilter();

   private:
      virtual void beginJob(const edm::EventSetup&) ;
      virtual bool filter(edm::Event&, const edm::EventSetup&);
      virtual void endJob() ;
      
      // ----------member data ---------------------------
  edm::InputTag inputTag_;
  double minE_;
  double maxEta_;
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
HLTCaloJetEnergyFilter::HLTCaloJetEnergyFilter(const edm::ParameterSet& iConfig) :
  inputTag_ (iConfig.getParameter<edm::InputTag>("inputTag" )),
  minE_     (iConfig.getParameter<double>       ("MinEnergy")),
  maxEta_   (iConfig.getParameter<double>       ("MaxEta"   ))
{
   //now do what ever initialization is needed

}


HLTCaloJetEnergyFilter::~HLTCaloJetEnergyFilter()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called on each new Event  ------------
bool
HLTCaloJetEnergyFilter::filter(edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   using namespace edm;

   bool result = false;

   Handle<reco::CaloJetCollection> jets;
   iEvent.getByLabel(inputTag_,jets);

   reco::CaloJetCollection::const_iterator jet;
   for (jet=jets->begin(); jet!= jets->end(); ++jet) {
     if (jet->energy() > minE_ && fabs(jet->eta())< maxEta_) {
       result = true;
     }
   }

   return result;
}

// ------------ method called once each job just before starting event loop  ------------
void 
HLTCaloJetEnergyFilter::beginJob(const edm::EventSetup&)
{
}

// ------------ method called once each job just after ending the event loop  ------------
void 
HLTCaloJetEnergyFilter::endJob() {
}

//define this as a plug-in
DEFINE_FWK_MODULE(HLTCaloJetEnergyFilter);
