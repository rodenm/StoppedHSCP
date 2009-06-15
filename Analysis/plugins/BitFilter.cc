// -*- C++ -*-
//
// Package:    BitFilter
// Class:      BitFilter
// 
/**\class BitFilter BitFilter.cc L1BitFilter/BitFilter/src/BitFilter.cc

 Description: <one line class summary>

 Implementation:
     <Notes on implementation>
*/
//
// Original Author:  Benjamin Jones
//         Created:  Fri Dec 12 10:15:22 CET 2008
// $Id: BitFilter.cc,v 1.1 2009/04/17 14:32:38 bjones Exp $
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
#include "DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerReadoutSetupFwd.h"
#include "DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerReadoutSetup.h"
#include "DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerReadoutRecord.h"
#include "DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerObjectMapRecord.h"
#include "DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerObjectMap.h"
#include "L1Trigger/GlobalTrigger/interface/L1GlobalTrigger.h"
#include "DataFormats/L1GlobalMuonTrigger/interface/L1MuGMTReadoutCollection.h"
#include "L1Trigger/GlobalTrigger/interface/L1GlobalTriggerPSB.h"
#include "L1Trigger/GlobalTrigger/interface/L1GlobalTriggerGTL.h"
#include "L1Trigger/GlobalTrigger/interface/L1GlobalTriggerFDL.h"

#include "DataFormats/HcalRecHit/interface/HcalRecHitCollections.h"
#include "DataFormats/HcalDetId/interface/HcalDetId.h"

#include "FWCore/ServiceRegistry/interface/Service.h"
#include "PhysicsTools/UtilAlgos/interface/TFileService.h"
#include "TH1.h"
#include "TH2.h"	 	
#include "TTree.h"

//
// class declaration
//

class BitFilter : public edm::EDFilter {
   public:
      explicit BitFilter(const edm::ParameterSet&);
      ~BitFilter();

   private:
      virtual void beginJob(const edm::EventSetup&) ;
      virtual bool filter(edm::Event&, const edm::EventSetup&);
      virtual void endJob() ;
      std::string SettingString_;

      TH1D * TriggerFired_;
      TH1D * LargestTrigger_;
      TH1D * EventCount_;
      TH1D * TriggerCount_;
      TH1D * SelectCount_;

      TTree * TrigTree_;

      Int_t EventID_;
  

  
      int Bit1_;
      int Bit2_;
      int Bit3_;
  
      bool MakePlots_;
      bool TriggerArray[128];

      
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
BitFilter::BitFilter(const edm::ParameterSet& iConfig):
  SettingString_(iConfig.getUntrackedParameter("FilterCondition",std::string("NoCondition"))),
  Bit1_(iConfig.getUntrackedParameter("Bit1",-1)),
  Bit2_(iConfig.getUntrackedParameter("Bit2",-1)),
  Bit3_(iConfig.getUntrackedParameter("Bit3",-1)),
  MakePlots_(iConfig.getUntrackedParameter("MakePlots",true))
{
   //now do what ever initialization is needed
  
  if(MakePlots_)
    { 
      edm::Service<TFileService>fs;
      
      TriggerFired_=fs->make<TH1D>("TriggerFired","No of Trigger Fired",128,-0.5,127.5);  
      EventCount_=fs->make<TH1D>("EventCount","Counter of initial events in dataset",1,0.5,1.5);
      SelectCount_=fs->make<TH1D>("SelectCount","Counter of events which pass filter",1,0.5,1.5);
      TrigTree_=fs->make<TTree>("EventID","EventID");
      TriggerCount_=fs->make<TH1D>("TriggerCount","Counter of events which pass some trigger",1,0.5,1.5);
      
      TrigTree_->Branch("EventID",&EventID_,"EventID/I");
      TrigTree_->Branch("Triggers",TriggerArray,"Triggers[128]/B");
    }

}


BitFilter::~BitFilter()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called on each new Event  ------------
bool
BitFilter::filter(edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  using namespace edm;
  Handle<L1GlobalTriggerReadoutRecord> readoutRcd;
  iEvent.getByLabel("gtDigis", readoutRcd);
  bool SelectThisEvent=0;

  bool decision = readoutRcd->decision();
  if(decision) TriggerCount_->Fill(1);

  DecisionWord dcWord = readoutRcd->decisionWord();
      
   
  
       
  for(int j=0; j!=128; j++)
    {
      if (dcWord[j]>0)
	{ 
	  TriggerArray[j]=true;
	  if(MakePlots_) TriggerFired_->Fill(j);
	}
      else
	{
	  TriggerArray[j]=false;
	}
    }
  

   if(SettingString_=="NoCondition")
     {
       SelectThisEvent=1;
       std::cout << "Warning : No BitFilter condition set"<<std::endl;
     }
   else
     {
       
       
       if(SettingString_=="OneBit")
	 {
	   if(dcWord[Bit1_]>0)
	     {
	       SelectThisEvent=1;
	     }
	 }
       if(SettingString_=="TwoBits")
	 {
	   if((dcWord[Bit1_]>0)||(dcWord[Bit2_]>0))
	     {
	       SelectThisEvent=1;
	     }
	 }
       if(SettingString_=="ThreeBits")
	 {
	   if((dcWord[Bit1_]>0)||(dcWord[Bit2_]>0)||(dcWord[Bit3_]>0))
	     {
	       SelectThisEvent=1;
	     }
	 }
       
       
       
     }
   if(SelectThisEvent&&MakePlots_) 
     {
       SelectCount_->Fill(1);
     }     	
   
     
  if(MakePlots_)
    {
      EventID_=iEvent.id().event();
      EventCount_->Fill(1);
      TrigTree_->Fill();
    }

   return SelectThisEvent;

}

// ------------ method called once each job just before starting event loop  ------------
void 
BitFilter::beginJob(const edm::EventSetup&)
{
}

// ------------ method called once each job just after ending the event loop  ------------
void 
BitFilter::endJob() {
}

//define this as a plug-in
DEFINE_FWK_MODULE(BitFilter);
