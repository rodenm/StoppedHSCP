// -*- C++ -*-
//
// Package:    MuonFilter
// Class:      MuonFilter
// 
/**\class MuonFilter MuonFilter.cc GluinoFilter/MuonFilter/src/MuonFilter.cc

 Description: <one line class summary>

 Implementation:
     <Notes on implementation>
*/
//
// Original Author:  Benjamin Jones
//         Created:  Thu Sep 18 17:50:32 CEST 2008
// $Id$
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

#include "DataFormats/MuonReco/interface/Muon.h"
#include "DataFormats/MuonReco/interface/MuonFwd.h"

#include "PhysicsTools/UtilAlgos/interface/TFileService.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "TTree.h"

//
// class declaration
//

class MuonFilter : public edm::EDFilter {
   public:
      explicit MuonFilter(const edm::ParameterSet&);
      ~MuonFilter();

   private:
      virtual void beginJob(const edm::EventSetup&) ;
      virtual bool filter(edm::Event&, const edm::EventSetup&);
      virtual void endJob() ;
      
      Int_t MuonCount;
      Float_t Energy;
      Float_t MomX;
      Float_t MomY;
      Float_t MomZ; 
      TTree * MuonFilterTree;
      TTree * MuonFilterTreePerMuon;
      bool AllowMuons;
      

      // ----------member data ---------------------------
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
MuonFilter::MuonFilter(const edm::ParameterSet& iConfig):
  AllowMuons(iConfig.getUntrackedParameter("AllowMuons",true))
{
   //now do what ever initialization is needed

  edm::Service<TFileService> fs;
  MuonFilterTree=fs->make<TTree>("MuonFilterTree","MuonFilterTree");
  MuonFilterTreePerMuon=fs->make<TTree>("MuonFilterTreePerMuon","MuonFilterTreePerMuon");

  MuonFilterTreePerMuon->Branch("MuonCount",&MuonCount,"MuonCount/I");
  MuonFilterTreePerMuon->Branch("Energy",&Energy,"Energy/F");
  MuonFilterTreePerMuon->Branch("MomX",&MomX,"MomX/F");
  MuonFilterTreePerMuon->Branch("MomY",&MomY,"MomY/F");
  MuonFilterTreePerMuon->Branch("MomZ",&MomZ,"MomZ/F");
}


MuonFilter::~MuonFilter()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called on each new Event  ------------
bool
MuonFilter::filter(edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  
  bool KeepThisEvent=true;

  using namespace edm;

  Handle<reco::MuonCollection> pMuons;
  iEvent.getByLabel("muons",pMuons);
  
  MuonCount=0;

  for(reco::MuonCollection::const_iterator it = pMuons->begin(); it!=pMuons->end(); it++)
    {
      MomX=it->px();
      MomY=it->py();
      MomZ=it->pz();
      Energy=it->energy();
      MuonFilterTreePerMuon->Fill();
      MuonCount++;
    }
  
  MuonFilterTree->Fill();
  
  if((!AllowMuons)&&(MuonCount>0)) KeepThisEvent=false;    






   return KeepThisEvent;
}

// ------------ method called once each job just before starting event loop  ------------
void 
MuonFilter::beginJob(const edm::EventSetup&)
{
}

// ------------ method called once each job just after ending the event loop  ------------
void 
MuonFilter::endJob() {
}

//define this as a plug-in
DEFINE_FWK_MODULE(MuonFilter);
