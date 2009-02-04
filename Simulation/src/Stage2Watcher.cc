#include "Validation/Stage2Watcher/interface/Stage2Watcher.h"

#include "SimG4Core/Notification/interface/BeginOfJob.h"
#include "SimG4Core/Notification/interface/BeginOfRun.h"

#include "FWCore/Framework/interface/EventSetup.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"
#include "Geometry/Records/interface/IdealGeometryRecord.h"

#include "G4Run.hh"
#include "G4PhysicalVolumeStore.hh"
#include "G4PVPlacement.hh"
#include "G4PVParameterised.hh"
#include "G4LogicalVolume.hh"
#include "G4Material.hh"
#include "G4TransportationManager.hh"
#include "G4Step.hh"

#include "FWCore/ServiceRegistry/interface/Service.h"
#include "PhysicsTools/UtilAlgos/interface/TFileService.h"
#include "TTree.h"
#include "TH1D.h"
#include "TH2.h"

#include <set>

Stage2Watcher::Stage2Watcher(const edm::ParameterSet &iConfig):
  TimeHists_(iConfig.getUntrackedParameter("TimeHists",true) )
  {
    std::cout<<"Stage 2 watcher enabled"<<std::endl;
  
  
  
  
  

}
 
Stage2Watcher::~Stage2Watcher() {}
  



void Stage2Watcher::update(const G4Step * iStep) {
  if((iStep->GetPreStepPoint()->GetGlobalTime()/ns) > 0)
    {

      GlobalTimingHisto->Fill(iStep->GetPreStepPoint()->GetGlobalTime()/ns,-iStep->GetDeltaEnergy()/GeV);
      LocalTimingHisto->Fill(iStep->GetPreStepPoint()->GetLocalTime()/ns,-iStep->GetDeltaEnergy()/GeV);
      ProperTimingHisto->Fill(iStep->GetPreStepPoint()->GetProperTime()/ns,-iStep->GetDeltaEnergy()/GeV);
      
      Time=iStep->GetPreStepPoint()->GetGlobalTime()/ns;
      PosX=iStep->GetPreStepPoint()->GetPosition().x()/cm;
      PosY=iStep->GetPreStepPoint()->GetPosition().y()/cm;
      PosZ=iStep->GetPreStepPoint()->GetPosition().z()/cm;
      PosR=iStep->GetPreStepPoint()->GetPosition().r()/cm;
      PosRho=iStep->GetPreStepPoint()->GetPosition().rho()/cm;
      PosPhi=iStep->GetPreStepPoint()->GetPosition().phi();
      EnergyDep=iStep->GetDeltaEnergy()/GeV;
      EventTree->Fill();

      //   std::cout << iStep->GetPreStepPoint()->GetProperTime()/ns << std::endl;
    }
}




void Stage2Watcher::update(const EndOfEvent * endofevent){

}

void Stage2Watcher::update(const BeginOfEvent * beginofevent) {

  int TimeDivs=1000;
  double TimeMax=100;
  double TimeMin=0;
  std::stringstream LocalHistName;
  LocalHistName << "LTimingHisto_"<<(*beginofevent)()->GetEventID();
  std::stringstream GlobalHistName;
  GlobalHistName << "GTimingHisto_"<<(*beginofevent)()->GetEventID();
  std::stringstream ProperHistName;
  ProperHistName << "PTimingHisto_"<<(*beginofevent)()->GetEventID();
  std::stringstream TreeName;
  TreeName<< "Tree_"<<(*beginofevent)()->GetEventID();
  
  
  if(TimeHists_)
    {
      
      GlobalTimingHisto = fs->make<TH1D>(GlobalHistName.str().c_str(),"Sim Timing Profile", TimeDivs,TimeMin,TimeMax);
      LocalTimingHisto = fs->make<TH1D>(LocalHistName.str().c_str(),"Sim Timing Profile", TimeDivs,TimeMin,TimeMax);
      ProperTimingHisto = fs->make<TH1D>(ProperHistName.str().c_str(),"Sim Timing Profile", TimeDivs,TimeMin,TimeMax);
      
      EventTree = fs->make<TTree>(TreeName.str().c_str(),"Tree of steps in event");
      EventTree->Branch("Time",&Time,"Time/F");
      EventTree->Branch("PosX",&PosX,"PosX/F");
      EventTree->Branch("PosY",&PosY,"PosY/F");
      EventTree->Branch("PosZ",&PosZ,"PosZ/F");
      EventTree->Branch("PosR",&PosR,"PosR/F");
      EventTree->Branch("PosRho",&PosRho,"PosRho/F");
      EventTree->Branch("EnergyDep",&EnergyDep,"EnergyDep/F");
      EventTree->Branch("PosPhi",&PosPhi,"PosPhi/F");
      
    }
}


#include "Validation/Stage2Watcher/interface/Stage2Watcher.h"
#include "SimG4Core/Watcher/interface/SimWatcherFactory.h"
#include "FWCore/PluginManager/interface/ModuleDef.h"
   
DEFINE_SEAL_MODULE ();
DEFINE_SIMWATCHER(Stage2Watcher);
