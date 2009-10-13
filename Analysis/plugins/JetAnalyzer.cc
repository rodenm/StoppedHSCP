// -*- C++ -*-
//
// Package:    JetAnalyzer
// Class:      JetAnalyzer
// 
/**\class JetAnalyzer JetAnalyzer.cc UserCode/JetAnalyzer/src/JetAnalyzer.cc

 Description: <one line class summary>

 Implementation:
     <Notes on implementation>
*/
//
// Original Author:  "Kenneth Rossato"
//         Created:  Fri Oct  2 12:11:33 CDT 2009
// $Id: JetAnalyzer.cc,v 1.1 2009/10/13 20:15:38 jbrooke Exp $
//
//


// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "DataFormats/JetReco/interface/CaloJetCollection.h"

#include "FWCore/ServiceRegistry/interface/Service.h"
#include "PhysicsTools/UtilAlgos/interface/TFileService.h"

#include "TH1D.h"
#include "TH2D.h"

//
// class decleration
//

class JetAnalyzer : public edm::EDAnalyzer {
   public:
      explicit JetAnalyzer(const edm::ParameterSet&);
      ~JetAnalyzer();


   private:
      virtual void beginJob() ;
      virtual void analyze(const edm::Event&, const edm::EventSetup&);
      virtual void endJob() ;

      // ----------member data ---------------------------
  edm::Service<TFileService> fs;
  edm::InputTag jets;
  TH1D *e, *e2, *eta, *phi, *n60, *n90, *ls;
  TH2D *eEta;
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
JetAnalyzer::JetAnalyzer(const edm::ParameterSet& iConfig)
  : jets (iConfig.getParameter<edm::InputTag>("jets"))
{
   //now do what ever initialization is needed

}


JetAnalyzer::~JetAnalyzer()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called to for each event  ------------
void
JetAnalyzer::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   using namespace edm;

   ls->Fill(iEvent.luminosityBlock());

   Handle<reco::CaloJetCollection> pIn;
   iEvent.getByLabel(jets,pIn);

   reco::CaloJetCollection::const_iterator leading, current;
   double highestE = 0;
   double highestEt = 0;
   for (leading = current = pIn->begin(); current != pIn->end(); current++) {
     if (current->et() > highestEt &&
	 current->energy() > 1 &&
	 fabs(current->eta() < 3)
	 ) {
       highestE = current->energy();
       highestEt = current->et();
       leading = current;
     }
   }
   if (highestE == 0) {
     e->Fill(0.);
     e2->Fill(0.);
     eta->Fill(0.);
     phi->Fill(0.);
     n60->Fill(0.);
     n90->Fill(0.);
     eEta->Fill(0.,0.);
     return;
   }

   e->Fill(leading->energy());
   e2->Fill(leading->energy());
   eta->Fill(leading->eta());
   phi->Fill(leading->phi());
   n60->Fill(leading->n60());
   n90->Fill(leading->n90());
   eEta->Fill(leading->energy(), leading->eta());
   
#ifdef THIS_IS_AN_EVENTSETUP_EXAMPLE
   ESHandle<SetupData> pSetup;
   iSetup.get<SetupRecord>().get(pSetup);
#endif



   

}


// ------------ method called once each job just before starting event loop  ------------
void 
JetAnalyzer::beginJob()
{
  e = fs->make<TH1D>("e", "Leading Jet Energy", 100, 0, 1000);
  e2 = fs->make<TH1D>("e2", "Leading Jet Energy", 100, 0, 200);
  eta = fs->make<TH1D>("eta", "Leading Jet Eta", 70, -3.5, 3.5);
  phi = fs->make<TH1D>("phi", "Leading Jet Phi", 60, -3.4151, 3.4151);
  n60 = fs->make<TH1D>("n60", "Leading Jet n60", 50, 0, 50);
  n90 = fs->make<TH1D>("n90", "Leading Jet n90", 50, 0, 50);

  ls = fs->make<TH1D>("ls", "Lumi Section", 200, 0, 200);

  eEta = fs->make<TH2D>("eEta", "Leading Jet E v. Eta",
			100, 0, 1000,
			70, -3.5, 3.5);
}

// ------------ method called once each job just after ending the event loop  ------------
void 
JetAnalyzer::endJob() {
}

//define this as a plug-in
DEFINE_FWK_MODULE(JetAnalyzer);
