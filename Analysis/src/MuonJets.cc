// -*- C++ -*-
//
// Package:    MuonJets
// Class:      MuonJets
// 
/**\class MuonJets MuonJets.cc GluinoAnalyzers/MuonJets/src/MuonJets.cc

 Description: <one line class summary>

 Implementation:
     <Notes on implementation>
*/
//
// Original Author:  Benjamin Jones
//         Created:  Fri Dec 12 12:07:32 CET 2008
// $Id$
//
//


// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/Framework/interface/ESHandle.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "DataFormats/RPCRecHit/interface/RPCRecHit.h"
#include "DataFormats/RPCRecHit/interface/RPCRecHitCollection.h"

#include "DataFormats/MuonDetId/interface/RPCDetId.h"
#include "Geometry/RPCGeometry/interface/RPCGeometry.h"
#include "Geometry/RPCGeometry/interface/RPCGeomServ.h"
#include "DataFormats/DetId/interface/DetId.h"
#include "Geometry/Records/interface/MuonGeometryRecord.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "PhysicsTools/UtilAlgos/interface/TFileService.h"
#include "CLHEP/Vector/ThreeVector.h"
#include "TTree.h"


//
// class decleration
//

class MuonJets : public edm::EDAnalyzer {
   public:
      explicit MuonJets(const edm::ParameterSet&);
      ~MuonJets();


   private:
      virtual void beginJob(const edm::EventSetup&) ;
      virtual void analyze(const edm::Event&, const edm::EventSetup&);
      virtual void endJob() ;
      std::string RPCDataLabel;
      Int_t NoOfHits;
      Int_t NoOfHitsIn1m;
      Int_t NoOfHitsIn2m;
      Int_t NoOfHitsIn3m;
      Int_t NoOfHitsIn4m;
      Float_t Radius90;
      Float_t Radius80;
      Float_t Radius70;
      Float_t Radius60;
      Float_t Radius50;

      TTree * EventTree;

      bool ProduceHistos;

      struct compare_vecmag : public std::binary_function<Hep3Vector, Hep3Vector, bool> {
         bool operator()(const Hep3Vector& x, const Hep3Vector& y) {
           return ( x.mag() < y.mag() ) ;
         }
       };


      
   

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
MuonJets::MuonJets(const edm::ParameterSet& iConfig): 
  RPCDataLabel(iConfig.getUntrackedParameter("rpcRecHitLabel",std::string("rpcRecHits"))),
  ProduceHistos(iConfig.getUntrackedParameter("ProduceHistos",false))
{
  edm::Service<TFileService> fs;
  EventTree =fs->make<TTree>("EventTree","EventTree");
  
  EventTree->Branch("NoOfHits",&NoOfHits,"NoOfHits/I");
  EventTree->Branch("NoOfHitsIn1m",&NoOfHitsIn1m,"NoOfHitsIn1m/I");
  EventTree->Branch("NoOfHitsIn2m",&NoOfHitsIn2m,"NoOfHitsIn2m/I");
  EventTree->Branch("NoOfHitsIn3m",&NoOfHitsIn3m,"NoOfHitsIn3m/I");
  EventTree->Branch("NoOfHitsIn4m",&NoOfHitsIn4m,"NoOfHitsIn4m/I");  
  EventTree->Branch("Radius50",&Radius50,"Radius50/F");  
  EventTree->Branch("Radius60",&Radius60,"Radius60/F"); 
  EventTree->Branch("Radius70",&Radius70,"Radius70/F"); 
  EventTree->Branch("Radius80",&Radius80,"Radius80/F"); 
  EventTree->Branch("Radius90",&Radius90,"Radius90/F"); 

}


MuonJets::~MuonJets()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called to for each event  ------------
void
MuonJets::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   using namespace edm;

   edm::ESHandle<RPCGeometry> rpcGeo;
   iSetup.get<MuonGeometryRecord>().get(rpcGeo);
   
   edm::Handle<RPCRecHitCollection> rpcHits;
   iEvent.getByLabel(RPCDataLabel,rpcHits);

   std::vector<Hep3Vector> RecHitPositions;
   Hep3Vector MeanPosition;
   std::cout<<"check1"<<std::endl;

   std::cout<<"Next event...."<<std::endl;
  

   for(RPCRecHitCollection::const_iterator itRH = rpcHits->begin(); itRH != rpcHits->end(); itRH++)
     {
       
	
       const RPCChamber * ch = rpcGeo->chamber(itRH->rpcId());
       const RPCRoll * ro = rpcGeo->roll(itRH->rpcId());


	   
       if(ch->id() == itRH->rpcId())
	 {
	   std::cout<<"Found Match ";
	   GlobalPoint GlobPos = ch->toGlobal(itRH->localPosition());
	   std::cout<<GlobPos.x()<<"  " << GlobPos.y() << "  " << GlobPos.z() << "  " <<  std::endl;
	   Hep3Vector ThisPosition(GlobPos.x(),GlobPos.y(),GlobPos.z());
	   RecHitPositions.push_back(ThisPosition);
	   MeanPosition+=ThisPosition;
	 }
	  
       if(ro->id() == itRH->rpcId())
	 {
	   std::cout<<"Found Match ";
	   GlobalPoint GlobPos = ch->toGlobal(itRH->localPosition());
	   std::cout<<GlobPos.x()<<"  " << GlobPos.y() << "  " << GlobPos.z() << "  " <<  std::endl;
	   Hep3Vector ThisPosition(GlobPos.x(),GlobPos.y(),GlobPos.z());
	   RecHitPositions.push_back(ThisPosition);
	   MeanPosition+=ThisPosition;
	 }
       
       
	

     }




   MeanPosition = 1./RecHitPositions.size() * MeanPosition;



   std::vector<Hep3Vector> SepFromMean;
   for(std::vector<Hep3Vector>::const_iterator itPos = RecHitPositions.begin(); itPos!=RecHitPositions.end(); itPos++)
     {
       SepFromMean.push_back((*itPos)-MeanPosition);
     }
   std::cout<<"check3"<<std::endl;

   sort(SepFromMean.begin(), SepFromMean.end(), compare_vecmag());
   
   NoOfHitsIn1m=-1;
   NoOfHitsIn2m=-1;
   NoOfHitsIn3m=-1;
   NoOfHitsIn4m=-1;
   Radius50=-1;
   Radius60=-1;
   Radius70=-1;
   Radius80=-1;
   Radius90=-1;

   NoOfHits=SepFromMean.size();
   for(int i=0; i!=SepFromMean.size(); i++)
     {
       std::cout<<"Sep: " << SepFromMean.at(i).mag()<<std::endl;
       if((NoOfHitsIn1m==-1)&&(SepFromMean.at(i).mag()>100)) NoOfHitsIn1m=i;
       if((NoOfHitsIn2m==-1)&&(SepFromMean.at(i).mag()>200)) NoOfHitsIn2m=i;
       if((NoOfHitsIn3m==-1)&&(SepFromMean.at(i).mag()>300)) NoOfHitsIn3m=i;
       if((NoOfHitsIn4m==-1)&&(SepFromMean.at(i).mag()>400)) NoOfHitsIn4m=i;     
       if((Radius50==-1)&&((i+1)==ceil(0.5 * SepFromMean.size()))) Radius50=SepFromMean.at(i).mag();
       if((Radius60==-1)&&((i+1)==ceil(0.6 * SepFromMean.size()))) Radius60=SepFromMean.at(i).mag();
       if((Radius70==-1)&&((i+1)==ceil(0.7 * SepFromMean.size()))) Radius70=SepFromMean.at(i).mag();
       if((Radius80==-1)&&((i+1)==ceil(0.8 * SepFromMean.size()))) Radius80=SepFromMean.at(i).mag();
       if((Radius90==-1)&&((i+1)==ceil(0.9 * SepFromMean.size()))) Radius90=SepFromMean.at(i).mag();	  
     }

   if(NoOfHitsIn1m==-1) NoOfHitsIn1m=SepFromMean.size();
   if(NoOfHitsIn2m==-1) NoOfHitsIn2m=SepFromMean.size();
   if(NoOfHitsIn3m==-1) NoOfHitsIn3m=SepFromMean.size();
   if(NoOfHitsIn4m==-1) NoOfHitsIn4m=SepFromMean.size();
   std::cout<<"check4"<<std::endl;

   EventTree->Fill();
 
}


// ------------ method called once each job just before starting event loop  ------------
void 
MuonJets::beginJob(const edm::EventSetup&)
{
}

// ------------ method called once each job just after ending the event loop  ------------
void 
MuonJets::endJob() {
}

//define this as a plug-in
DEFINE_FWK_MODULE(MuonJets);
