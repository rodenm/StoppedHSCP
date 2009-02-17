// -*- C++ -*-
//
// Package:    MuonCrossing
// Class:      MuonCrossing
// 
/**\class MuonCrossing MuonCrossing.cc GluinoProducers/MuonCrossing/src/MuonCrossing.cc

 Description: <one line class summary>

 Implementation:
     <Notes on implementation>
*/
//
// Original Author:  Benjamin Jones
//         Created:  Wed Dec  3 16:34:36 CET 2008
// $Id$
//
//


// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDProducer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "DataFormats/TrackReco/interface/TrackFwd.h"
#include "DataFormats/TrackReco/interface/Track.h"
#include "TrackingTools/PatternTools/interface/Trajectory.h"
#include "DataFormats/MuonReco/interface/Muon.h"
#include "DataFormats/MuonReco/interface/MuonFwd.h"
#include "TrackingTools/TrajectoryState/interface/FreeTrajectoryState.h"
#include "TrackingTools/TrackAssociator/interface/TAMuonChamberMatch.h"
#include "DataFormats/HcalRecHit/interface/HcalRecHitCollections.h"
#include "Geometry/CaloGeometry/interface/CaloGeometry.h"
#include "TrackingTools/TrackAssociator/interface/TrackDetectorAssociator.h"
#include "TrackPropagation/SteppingHelixPropagator/interface/SteppingHelixPropagator.h"

#include "MagneticField/Engine/interface/MagneticField.h"
#include "MagneticField/Records/interface/IdealMagneticFieldRecord.h"
#include "DataFormats/HcalDigi/interface/HBHEDataFrame.h"
#include "DataFormats/HcalDigi/interface/HcalDigiCollections.h"
#include "Geometry/HcalTowerAlgo/interface/HcalHardcodeGeometryLoader.h"
#include "Geometry/CaloGeometry/interface/CaloCellGeometry.h"
#include "Geometry/HcalTowerAlgo/interface/HcalGeometry.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "PhysicsTools/UtilAlgos/interface/TFileService.h"


#include "TTree.h"



//
// class decleration
//

class MuonCrossing : public edm::EDProducer {
   public:
      explicit MuonCrossing(const edm::ParameterSet&);
      ~MuonCrossing();
      edm::Service<TFileService> fs;
      TTree * EventTree;



   private:
      virtual void beginJob(const edm::EventSetup&) ;
      virtual void produce(edm::Event&, const edm::EventSetup&);
      virtual void endJob() ;
      std::string MuonCollection_;
      bool Verbose_;
      mutable TrackDetectorAssociator* TrackAssociator_;
      TrackAssociatorParameters parameters_;
      int MuonCount_;
      bool SplitDigis_;
      bool SplitRecHits_;
      std::string DigisTag_;
      std::string RecHitsTag_;
      bool Analyse_;
      double CrossingRadius_;

      struct compare_hbhe : public std::binary_function<HBHERecHit, HBHERecHit, bool> {
         bool operator()(const HBHERecHit& x, const HBHERecHit& y) {
           return ( x.energy() > y.energy() ) ;
         }
       };

  CaloSubdetectorGeometry * barrelgeometry;

  Float_t IntersectX;
  Float_t IntersectY;
  Float_t IntersectZ;
  Float_t IntersectR;
  Float_t IntersectEta;
  Float_t IntersectPhi;

  Float_t MomentumX;
  Float_t MomentumY;
  Float_t MomentumZ;
  Float_t MomentumMag;
  
  Int_t MaxRecHitiEta;
  Int_t MaxRecHitiPhi;
  Float_t MaxRecHitEta;
  Float_t MaxRecHitPhi;
  Float_t MaxRecHitEnergy;

  Float_t RecHitNearestTrajectoryAngle;
  Float_t RecHitNearestTrajectoryDistance;
  Float_t RecHitNearestTrajectorySeparationAngle;

  Int_t NoRecHitsOver5;
  Int_t NoRecHitsOver10;

  Float_t ClosestRadius;
  
  Float_t DoubleMuonEnergyChange;
  Float_t DoubleMuonDeflectionAngle;
  Float_t MuonMomentum2;

  Int_t NoDetIdsCrossed;
  Float_t EnergyInCrossedRecHits;
  Float_t EnergyInTop5RecHits;
  Float_t NoOfTop5RecHitsMissed;
  Float_t RadiusCrossingPhiPlane;
  Float_t ThetaSepInPhiPlane;
  
  Bool_t DoubleMuon;

  SteppingHelixPropagator* prop;

  bool VerboseChecks_;
  bool VerboseKeeps_;



      
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
MuonCrossing::MuonCrossing(const edm::ParameterSet& iConfig):
  MuonCollection_(iConfig.getUntrackedParameter("MuonCollection",std::string("STAMuons"))),
  Verbose_(iConfig.getUntrackedParameter("Verbose",true)),
  SplitDigis_(iConfig.getUntrackedParameter("SplitDigis",true)),
  SplitRecHits_(iConfig.getUntrackedParameter("SplitRecHits",true)),
  DigisTag_(iConfig.getUntrackedParameter("DigisTag",std::string("hcalDigis"))),
  RecHitsTag_(iConfig.getUntrackedParameter("RecHitsTag",std::string("hbhereco"))),
  Analyse_(iConfig.getUntrackedParameter("Analyse",true)),
  CrossingRadius_(iConfig.getUntrackedParameter("Radius",300)),
  VerboseChecks_(iConfig.getUntrackedParameter("VerboseChecks",true)),
  VerboseKeeps_(iConfig.getUntrackedParameter("VerboseKeeps",false))

{

  edm::ParameterSet parameters = iConfig.getParameter<edm::ParameterSet>("TrackAssociatorParameters");
  parameters_.loadParameters( parameters );
  TrackAssociator_=new TrackDetectorAssociator();
  //TrackAssociator_->useDefaultPropagator();
  
  MuonCount_=0;

  if(SplitDigis_)
    {
      produces<HBHEDigiCollection>("MuonCrossingDigiYes");
      produces<HBHEDigiCollection>("MuonCrossingDigiNo");
    }

  if(SplitRecHits_)
    {     
      produces<HBHERecHitCollection>("MuonCrossingRecHitYes");
      produces<HBHERecHitCollection>("MuonCrossingRecHitNo");
    }
  
  if(Analyse_)
    {
      EventTree = fs->make<TTree>("EventTree","EventTree");
      
      EventTree->Branch("IntersectX",&IntersectX,"IntersectX/F");
      EventTree->Branch("IntersectY",&IntersectY,"IntersectY/F");
      EventTree->Branch("IntersectZ",&IntersectZ,"IntersectZ/F");
      EventTree->Branch("IntersectEta",&IntersectEta,"IntersectEta/F");
      EventTree->Branch("IntersectPhi",&IntersectPhi,"IntersectPhi/F");
      EventTree->Branch("IntersectR",&IntersectR,"IntersectR/F");
      
      EventTree->Branch("MomentumX",&MomentumX,"MomentumX/F");
      EventTree->Branch("MomentumY",&MomentumY,"MomentumY/F");
      EventTree->Branch("MomentumZ",&MomentumZ,"MomentumZ/F");
      EventTree->Branch("MomentumMag",&MomentumMag,"MomentumMag/F");
      
      EventTree->Branch("MaxRecHitEnergy",&MaxRecHitEnergy,"MaxRecHitEnergy/F");
      EventTree->Branch("MaxRecHitEta",&MaxRecHitEta,"MaxRecHitEta/F");
      EventTree->Branch("MaxRecHitPhi",&MaxRecHitPhi,"MaxRecHitPhi/F");
      EventTree->Branch("MaxRecHitiEta",&MaxRecHitiEta,"MaxRecHitiEta/I");
      EventTree->Branch("MaxRecHitiPhi",&MaxRecHitiPhi,"MaxRecHitiPhi/I");
      
      EventTree->Branch("NoRecHitsOver5",&NoRecHitsOver5,"NoRecHitsOver5/I");
      EventTree->Branch("NoRecHitsOver10",&NoRecHitsOver10,"NoRecHitsOver10/I");
      
      EventTree->Branch("RecHitNearestTrajectoryAngle",&RecHitNearestTrajectoryAngle,"RecHitNearestTrajectoryAngle/F");
      EventTree->Branch("RecHitNearestTrajectoryDistance",&RecHitNearestTrajectoryDistance,"RecHitNearestTrajectoryDistance/F");
      EventTree->Branch("RecHitNearestTrajectorySeparationAngle",&RecHitNearestTrajectorySeparationAngle,"RecHitNearestTrajectorySeparationAngle/F");  
      
      EventTree->Branch("ClosestRadius",&ClosestRadius,"ClosestRadius/F");
      
      EventTree->Branch("DoubleMuonEnergyChange",&DoubleMuonEnergyChange,"DoubleMuonEnergyChange/F");
      EventTree->Branch("DoubleMuonDeflectionAngle",&DoubleMuonDeflectionAngle,"DoubleMuonDeflectionAngle");
      EventTree->Branch("MuonMomentum2",&MuonMomentum2,"MuonMomentum2/F");
      
      EventTree->Branch("NoDetIdsCrossed",&NoDetIdsCrossed,"NoDetIdsCrossed/I");
      EventTree->Branch("EnergyInTop5RecHits",&EnergyInTop5RecHits,"EnergyInTop5RecHits/F");
      EventTree->Branch("NoOfTop5RecHitsMissed",&NoOfTop5RecHitsMissed,"NoOfTop5RecHitsMissed/I");

      EventTree->Branch("DoubleMuon",&DoubleMuon,"DoubleMuon/B");
      EventTree->Branch("RadiusCrossingPhiPlane",&RadiusCrossingPhiPlane,"RadiusCrossingPhiPlane/F");
      EventTree->Branch("ThetaSepInPhiPlane",&ThetaSepInPhiPlane,"ThetaSepInPhiPlane/F");

    }

  HcalTopology hcaltopology;
  HcalHardcodeGeometryLoader loader(hcaltopology);
  barrelgeometry = loader.load();
  
  

   
}


MuonCrossing::~MuonCrossing()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called to produce the data  ------------
void
MuonCrossing::produce(edm::Event& iEvent, const edm::EventSetup& iSetup)
{

  if(VerboseChecks_) std::cout<<"Check0.5"<<std::endl;
  
  using namespace edm;
  
  Handle<reco::MuonCollection> pMuons;
  iEvent.getByLabel(MuonCollection_,pMuons);
  
  Handle<HBHEDigiCollection> pDigis;
   Handle<HBHERecHitCollection> pRecHits;
   
   std::auto_ptr<HBHEDigiCollection> YesCrossDigi(new HBHEDigiCollection);
   std::auto_ptr<HBHEDigiCollection> NoCrossDigi(new HBHEDigiCollection);
   std::auto_ptr<HBHERecHitCollection> YesCrossRecHit(new HBHERecHitCollection);
   std::auto_ptr<HBHERecHitCollection> NoCrossRecHit(new HBHERecHitCollection);

   edm::ESHandle<MagneticField> bField;
   iSetup.get<IdealMagneticFieldRecord>().get(bField);  
   prop  = new SteppingHelixPropagator(&*bField,anyDirection);
   TrackAssociator_->setPropagator(prop);
   //  prop->setMaterialMode(false);
   //   prop->applyRadX0Correction(true);
   prop->setDebug(true); // tmp
   
   double Radius=CrossingRadius_;
   

   if(SplitDigis_)
     iEvent.getByLabel(DigisTag_,pDigis);
    

   if(SplitRecHits_)  
     iEvent.getByLabel(RecHitsTag_,pRecHits);
    
   bool SomeYes=false;

   std::vector<HcalDetId> HcalIdsAll;
   

   Hep3Vector MaxRecHitPos;
   std::vector<Hep3Vector> MuonFromMaxRHDistances;
   std::vector<Hep3Vector> MuonIntersectMoms;
   std::vector<Hep3Vector> MuonIntersectPoss;
   
   bool Top5Map[100][100];
   

   //   TrackAssociator_->setPropagator(prop);
   




   if(VerboseChecks_) std::cout<<"check1"<<std::endl;





   // For muon - hcal rec hit analysis - find maximum rec hit position


   if(Analyse_)
     {
       NoRecHitsOver5=0;
       NoRecHitsOver10=0;
       for(int i =0; i!=100; i++)
	 for(int j=0; j!=100; j++)
	   Top5Map[i][j]=false;

	     

       GlobalPoint GlobMaxRecHitPoint;
       int rechitcount=0;
       EnergyInTop5RecHits=0;


       std::vector<HBHERecHit> RecHitVector;
		     
       RecHitVector.insert(RecHitVector.begin(),pRecHits->begin(),pRecHits->end());
       
       sort(RecHitVector.begin(),RecHitVector.end(),compare_hbhe());
       

       for(std::vector<HBHERecHit>::const_iterator itRH = RecHitVector.begin(); itRH!=RecHitVector.end(); itRH++)
	 {
	   if(rechitcount==0)
	     {
	       MaxRecHitEnergy=itRH->energy();
	       MaxRecHitiEta=itRH->id().ieta();
	       MaxRecHitiPhi=itRH->id().iphi();
	       GlobMaxRecHitPoint = barrelgeometry->getGeometry(itRH->detid())->getPosition();
	       MaxRecHitPos.set(GlobMaxRecHitPoint.x(),GlobMaxRecHitPoint.y(),GlobMaxRecHitPoint.z());
	       MaxRecHitEta=MaxRecHitPos.eta();
	       MaxRecHitPhi=MaxRecHitPos.phi();
	      
	       
	     }

	   if(itRH->energy()>5) NoRecHitsOver5++;
	   if(itRH->energy()>10) NoRecHitsOver10++;

	   if(rechitcount<5) 
	     {
	       Top5Map[itRH->id().ieta()+50][itRH->id().iphi()+1]=true;
	       EnergyInTop5RecHits+=itRH->energy();
	     }
	   rechitcount++;

	 }
       
     }       
       





   if(VerboseChecks_) std::cout<<"check2"<<std::endl;






   //Loop through muons and find crossed hits and distances from max

   
   for(reco::MuonCollection::const_iterator itMuon = pMuons->begin(); itMuon!=pMuons->end(); itMuon++)
     {
 

       if(Verbose_) std::cout << "Good      : " << itMuon->isGood()<<std::endl;
       if(Verbose_) std::cout << "Muon      : " << itMuon->isMuon()<<std::endl;
       if(Verbose_) std::cout << "Available : " << itMuon->outerTrack().isAvailable()<<std::endl;
       MuonCount_++;
       if(Verbose_) std::cout<<"Muon No " << MuonCount_ << std::endl;
  

       if(itMuon->outerTrack().isAvailable()) 
	   {
	     if(Verbose_) std::cout<<"Using outer track"<<std::endl;
	     const reco::Track * TheTrack = itMuon->outerTrack().get();

	     const FreeTrajectoryState fts = TrackAssociator_->getFreeTrajectoryState(iSetup,*TheTrack);
	     

	     
	     TrackDetMatchInfo info = TrackAssociator_->associate(iEvent,iSetup,fts,parameters_);

	     if(info.isGoodHcal!=0)
	       {

		 std::vector<const HBHERecHit*> HBHEHits = info.hcalRecHits;
		 std::vector<const HORecHit*> HOHits= info.hoRecHits;
		 
		 for(std::vector<const HBHERecHit*>::const_iterator it=HBHEHits.begin(); it!=HBHEHits.end(); it++)
		   {
		     if(VerboseKeeps_)   std::cout<<"HBHERecHit   : "<<(*it)->id().ieta()<<"  " <<(*it)->id().iphi() <<"  " <<(*it)->energy()<<std::endl;
		     HcalDetId HcalCell((*it)->id());
		     HcalIdsAll.push_back(HcalCell);
		     SomeYes=true;
		   }
		 
		 for(std::vector<const HORecHit*>::const_iterator it=HOHits.begin(); it!=HOHits.end(); it++)
		   {
		     if(VerboseKeeps_)    std::cout<<"HORecHit   : "<<(*it)->id().ieta()<<"  " <<(*it)->id().iphi() <<"  " <<(*it)->energy()<<std::endl;
		   }


	       }
		 

	     
	     if(Analyse_ )
	       {
		 
		 const Cylinder * cylinder = new Cylinder(Surface::PositionType(0,0,0),
							  Surface::RotationType(), 
							  CrossingRadius_ );
		 
		 float phi = MaxRecHitPos.phi();
		 

		 std::cout <<"Plane rotation : " <<  phi<<std::endl;

		 Surface::RotationType xyrotation(float(cos(phi)),  float(sin(phi)), float(0),
						  float(0),  float(0), float(1),
						  float(sin(phi)) ,        float(-cos(phi)),        float(0));
		 
		 const Plane * plane = new Plane(Surface::PositionType(0,0,0),
						 xyrotation);
				  
		 
		 if(Verbose_) std::cout<<"Propagating...   "<<std::endl;
	       	 TrajectoryStateOnSurface sosc = prop->propagate(fts, *cylinder);
		 // TrajectoryStateOnSurface sosp = prop->propagate(fts, *plane);
		 
		 if(sosc.isValid())
		   {
		     GlobalPoint GlobPos = sosc.globalPosition();
		     GlobalVector GlobMom = sosc.globalMomentum();
		     
		     Hep3Vector IntersectPos(GlobPos.x(), GlobPos.y(), GlobPos.z());
		     Hep3Vector IntersectMom(GlobMom.x(), GlobMom.y(), GlobMom.z());
		     
		     MuonIntersectPoss.push_back(IntersectPos);
		     MuonIntersectMoms.push_back(IntersectMom);

		     if(Verbose_) std::cout<<"Found Intersect "<<IntersectPos.phi()<<std::endl;
		     
		     MuonFromMaxRHDistances.push_back(IntersectPos-MaxRecHitPos);

		   }
		 
		 
	       }
	     
	   }
       
       
       else if(Verbose_) std::cout<<"No track available - skipping muon "<<std::cout;
       
     }   
   



   if(VerboseChecks_) std::cout<<"check3"<<std::endl;




   //  Fill array of detector ID's crossed into eta phi map
   

   bool KeepMap[100][100];
   for(int i=0; i!=100; i++)
     for(int j=0; j!=100; j++)
       KeepMap[i][j]=false;

   for(std::vector<HcalDetId>::const_iterator ithcal = HcalIdsAll.begin(); ithcal!=HcalIdsAll.end(); ithcal++)
     {
       if(VerboseKeeps_)   std::cout <<"Keeping Hcal Det " << ithcal->ieta()<<"  "<<ithcal->iphi()<<std::endl;
       KeepMap[ithcal->ieta()+50][ithcal->iphi()+1]=true;
     }
   
   
   if(Analyse_)
     {
       NoOfTop5RecHitsMissed=0;
       for(int i=0; i!=100; i++)
	 for(int j=0; j!=100; j++)
	   if((Top5Map[i][j]==true) && (KeepMap[i][j]==false)) NoOfTop5RecHitsMissed++;
     }



   if(VerboseKeeps_) std::cout<<"check4"<<std::endl;








   //Analyser - Get data from nearest trajectory to max rec hit

   double NearestSep=10000;
   int Nearesti=0;
   int NextNearesti=0;
  

   if(Analyse_ && SomeYes && MuonFromMaxRHDistances.size()>0)
     {
       for(int i=0; i!= MuonFromMaxRHDistances.size(); i++)
	 {
	   if(MuonFromMaxRHDistances.at(i).mag()<MuonFromMaxRHDistances.at(Nearesti).mag()) Nearesti=i;
	   if(VerboseChecks_) std::cout<<"Distance between RH and Muon: "<< std::endl <<
	     MaxRecHitPos.perp() << " " <<MaxRecHitPos.phi()<<"  " <<MaxRecHitPos.eta()<<"   -   " << MuonIntersectPoss.at(i).perp()<<" " << MuonIntersectPoss.at(i).phi()<<" " << MuonIntersectPoss.at(i).eta() << "  =   " << MuonFromMaxRHDistances.at(i).mag()<<std::endl;





	     }


       Hep3Vector TempMaxRH, TempMaxRHSep;
       TempMaxRH.setRhoPhiZ(MuonIntersectPoss.at(Nearesti).rho(),MaxRecHitPos.phi(),MaxRecHitPos.z());
       TempMaxRHSep = TempMaxRH - MuonIntersectPoss.at(Nearesti);
       RecHitNearestTrajectoryDistance = TempMaxRHSep.mag();
       RecHitNearestTrajectorySeparationAngle = TempMaxRHSep.theta(MuonIntersectMoms.at(Nearesti));
       RecHitNearestTrajectoryAngle = MuonIntersectMoms.at(Nearesti).theta(MuonIntersectPoss.at(Nearesti));
       
       IntersectX = MuonIntersectPoss.at(Nearesti).x();
       IntersectY = MuonIntersectPoss.at(Nearesti).y();
       IntersectZ = MuonIntersectPoss.at(Nearesti).z();
       IntersectEta= MuonIntersectPoss.at(Nearesti).eta();
       IntersectPhi= MuonIntersectPoss.at(Nearesti).phi();
       IntersectR = MuonIntersectPoss.at(Nearesti).perp();
       
       MomentumX = MuonIntersectMoms.at(Nearesti).x();
       MomentumY = MuonIntersectMoms.at(Nearesti).y();
       MomentumZ = MuonIntersectMoms.at(Nearesti).z();
       MomentumMag = MuonIntersectMoms.at(Nearesti).mag();


       ThetaSepInPhiPlane = MuonIntersectPoss.at(Nearesti).theta()-MaxRecHitPos.theta();


       ClosestRadius = MuonIntersectPoss.at(Nearesti).dot((MuonIntersectMoms.at(Nearesti).unit()).cross(MaxRecHitPos.unit()));

       DoubleMuonEnergyChange=0;
       DoubleMuonDeflectionAngle=0;
       DoubleMuon=false;

       NoDetIdsCrossed = HcalIdsAll.size();

       if(MuonFromMaxRHDistances.size()>1)
	 {
	   DoubleMuon=true;
	   for(int i=0; i!=MuonFromMaxRHDistances.size(); i++)
	     {
	       if((MuonFromMaxRHDistances.at(i).mag()<NearestSep) && (i!=Nearesti))
		 {
		   NextNearesti=i;
		   NearestSep = MuonFromMaxRHDistances.at(i).mag();
		 }
	     }
	   DoubleMuonDeflectionAngle = MuonIntersectMoms.at(Nearesti).theta(MuonIntersectMoms.at(NextNearesti));
	   DoubleMuonEnergyChange = MuonIntersectMoms.at(Nearesti).mag()-MuonIntersectMoms.at(NextNearesti).mag();
	   MuonMomentum2 = MuonIntersectMoms.at(NextNearesti).mag();

	  

	 }
       EventTree->Fill();

     }
   


   std::cout<<"check5"<<std::endl;
      




   // Fill collections

   

   if(SplitRecHits_)
     {
       for(HBHERecHitCollection::const_iterator itRecHits = pRecHits->begin(); itRecHits!=pRecHits->end(); itRecHits++)
	 {
	   if(KeepMap[itRecHits->id().ieta()+50][itRecHits->id().iphi()+1]==true)
	     {

	       YesCrossRecHit->push_back(*itRecHits);
	    
	     }
	   else
	     {
	     
	       NoCrossRecHit->push_back(*itRecHits);
	     }
	 }
       if(SomeYes) iEvent.put(YesCrossRecHit,"MuonCrossingRecHitYes");
       iEvent.put(NoCrossRecHit,"MuonCrossingRecHitNo");


     }
   
     if(SplitDigis_)
     {
       for(HBHEDigiCollection::const_iterator itDigis = pDigis->begin(); itDigis!=pDigis->end(); itDigis++)
	 {
	   HBHEDataFrame MyFrame = (*itDigis);
	   if(KeepMap[itDigis->id().ieta()+50][itDigis->id().iphi()+1]==true)
	     {
	       YesCrossDigi->push_back(MyFrame);
	     }
	   else
	     {
	       NoCrossDigi->push_back(MyFrame);
	     }
	 }
       if(SomeYes) iEvent.put(YesCrossDigi,"MuonCrossingDigiYes");
       iEvent.put(NoCrossDigi, "MuonCrossingDigiNo");

     }
     
     std::cout<<"check6"<<std::endl;

     delete prop;
}

// ------------ method called once each job just before starting event loop  ------------
void 
MuonCrossing::beginJob(const edm::EventSetup&)
{
}

// ------------ method called once each job just after ending the event loop  ------------
void 
MuonCrossing::endJob() {
}

//define this as a plug-in
DEFINE_FWK_MODULE(MuonCrossing);
