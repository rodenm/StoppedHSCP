// -*- C++ -*-
//
// Package:    CaloFilter
// Class:      CaloFilter
// 
/**\class CaloFilter CaloFilter.cc GluinoFilter/CaloFilter/src/CaloFilter.cc

 Description: <one line class summary>

 Implementation:
     <Notes on implementation>
*/
//
// Original Author:  Benjamin Jones
//         Created:  Fri Sep 12 15:55:18 CEST 2008
// $Id: CaloFilter.cc,v 1.1 2009/02/17 11:10:06 bjones Exp $
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

#include "DataFormats/JetReco/interface/CaloJetCollection.h"
#include "DataFormats/CaloTowers/interface/CaloTowerCollection.h"

#include "FWCore/ServiceRegistry/interface/Service.h"
#include "PhysicsTools/UtilAlgos/interface/TFileService.h"
#include "TTree.h"
#include "TH1D.h"


//
// class declaration
//

class CaloFilter : public edm::EDFilter {
   public:
      explicit CaloFilter(const edm::ParameterSet&);
      ~CaloFilter();
       struct compare_ct : public std::binary_function<CaloTower, CaloTower, bool> {
         bool operator()(const CaloTower& x, const CaloTower& y) {
           return ( x.energy() > y.energy() ) ;
         }
       };


   private:
      virtual void beginJob(const edm::EventSetup&) ;
      virtual bool filter(edm::Event&, const edm::EventSetup&);
      virtual void endJob() ;

      int NOver5;
    
      bool DismissByEtaCut;
      bool DismissByEnergyCut;
      bool DismissByEtCut;
      bool DismissByn90Cut;
      bool DismissByn60Cut;
      bool DismissAsEndcapNoise;
      bool DismissByLeaders;
      bool DismissBy5Thresh;
      bool DismissByTopCaloThresh; 
      bool DismissByNoJet;  

      int n60MinThreshold;
      int n90MinThreshold;
      int n60MaxThreshold;
      int n90MaxThreshold;
      double ETMinThreshold;     
      double ETMaxThreshold;
      double EMinThreshold;    
      double EMaxThreshold;
      double CaloTowerEMin;
      bool CaloTowerVeto;
      int CaloTowerCount; 

      double CentralEta;
  
      int LeadersMaxCut;
      int LeadersMinCut;

      double CaloTowerEtaMinThreshold;
      double CaloTowerEtaMaxThreshold;
      double EtaMinThreshold;
      double EtaMaxThreshold;

      bool Verbose;

      TTree * FilterTree;

      Int_t NoLeaders;
      Int_t NoLeaders2;
      Int_t NOverThresh5;
      Int_t NOverThresh10;
      Int_t NOverThresh15;
      Int_t NOverThresh20;
      Int_t NOverThresh25; 
      Int_t NOverThresh30;
      Float_t ELeaders;
      Float_t ELeaders2;

      TH1D * RejectCount;

  edm::InputTag JetTag_;
  edm::InputTag CaloTowerTag_;
 


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
CaloFilter::CaloFilter(const edm::ParameterSet& iConfig):
  n60MinThreshold(iConfig.getUntrackedParameter("n60MinThreshold",0)),
  n90MinThreshold(iConfig.getUntrackedParameter("n90MinThreshold",0)),
  n60MaxThreshold(iConfig.getUntrackedParameter("n60MaxThreshold",100)),
  n90MaxThreshold(iConfig.getUntrackedParameter("n90MaxThreshold",100)),
  ETMinThreshold(iConfig.getUntrackedParameter("ETMinThreshold",0.)),
  ETMaxThreshold(iConfig.getUntrackedParameter("ETMaxThreshold",10000.)),
  EMinThreshold(iConfig.getUntrackedParameter("EMinThreshold",0.)),
  EMaxThreshold(iConfig.getUntrackedParameter("EMaxThreshold",10000.)),
  EtaMinThreshold(iConfig.getUntrackedParameter("EtaMinThreshold",-1.3)),
  EtaMaxThreshold(iConfig.getUntrackedParameter("EtaMaxThreshold",1.3)), 
  CaloTowerCount(iConfig.getUntrackedParameter("CaloTowerCount",8)),
  CaloTowerVeto(iConfig.getUntrackedParameter("CaloTowerVeto",false)),
  NOver5(iConfig.getUntrackedParameter("NOver5",2)),
  CentralEta(iConfig.getUntrackedParameter("CentralEta",1.3)),
  Verbose(iConfig.getUntrackedParameter("Verbose",false)),
  JetTag_(iConfig.getUntrackedParameter("JetTag",edm::InputTag("iterativeCone5CaloJets"))),
  CaloTowerTag_(iConfig.getUntrackedParameter("CaloTowerTag",edm::InputTag("towerMaker")))
 
{
   //now do what ever initialization is needed

  edm::Service<TFileService> fs;
  FilterTree=fs->make<TTree>("FilterTree","FilterTree");
  RejectCount=fs->make<TH1D>("RejectCount","RejectCount",10,0,10);

  

  FilterTree->Branch("NOverThresh5",&NOverThresh5,"NOverThresh5/I");
  FilterTree->Branch("NOverThresh10",&NOverThresh10,"NOverThresh10/I");
  FilterTree->Branch("NOverThresh15",&NOverThresh15,"NOverThresh15/I");
  FilterTree->Branch("NOverThresh20",&NOverThresh20,"NOverThresh20/I");
  FilterTree->Branch("NOverThresh25",&NOverThresh25,"NOverThresh25/I");
  FilterTree->Branch("NOverThresh30",&NOverThresh30,"NOverThresh30/I");
  FilterTree->Branch("DismissByEtaCut",&DismissByEtaCut,"DismissByEtaCut/B");
  FilterTree->Branch("DismissByEnergyCut",&DismissByEnergyCut,"DismissByEnergyCut/B");
  FilterTree->Branch("DismissByEtCut",&DismissByEtCut,"DismissByEtCut/B");
  FilterTree->Branch("DismissByn90Cut",&DismissByn90Cut,"DismissByn90Cut/B");
  FilterTree->Branch("DismissByn60Cut",&DismissByn60Cut,"DismissByn60Cut/B");
  FilterTree->Branch("DismissBy5Thresh",&DismissBy5Thresh,"DismissBy5Thresh/B");
  FilterTree->Branch("DismissByNoJet",&DismissByNoJet,"DismissByNoJet/B");




}


CaloFilter::~CaloFilter()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called on each new Event  ------------
bool
CaloFilter::filter(edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  using namespace reco;
  using namespace edm;
       
  Handle<CaloJetCollection> pCalo5;
  iEvent.getByLabel(JetTag_,pCalo5);

  bool SelectEvent=false;


  DismissByEtaCut=false;
  DismissByEnergyCut=false;
  DismissByEtCut=false;
  DismissByn90Cut=false;
  DismissByn60Cut=false;
  DismissAsEndcapNoise=false;
  DismissByLeaders=false;
  DismissBy5Thresh = false;
  DismissByTopCaloThresh=false; 
  DismissByNoJet=false;  
  bool StillCheckingForLeaders=true;
  bool StillCheckingForLeaders2=true;

  double LeadingCenEnergy=-1;

  SelectEvent=true;

  bool FoundLeader=false;
  CaloJetCollection::const_iterator it;
  for(CaloJetCollection::const_iterator it1 = pCalo5->begin(); it1!=pCalo5->end(); it1++)
    
    {
      if((it1->energy()>LeadingCenEnergy)&&(it1->eta()<CentralEta)&&(it1->eta()>(-CentralEta)))
	{
	  LeadingCenEnergy=it1->energy();
	  FoundLeader=true;
	  it=it1;
	}
    }
  
  if(FoundLeader)
    {
      if( !   ((it->n60()>n60MinThreshold)&&(it->n60()<n60MaxThreshold))  )
	{
	  DismissByn60Cut=true;
	}
      if( !   ((it->n90()>n90MinThreshold)&&(it->n90()<n90MaxThreshold))  )
	{
	  DismissByn90Cut=true;
	}
      if( !   ((it->et()>ETMinThreshold)&&(it->et()<ETMaxThreshold))  )
	{
	  DismissByEtCut=true;
	}
      if( !   ((it->energy()>EMinThreshold)&&(it->energy()<EMaxThreshold))  )
	{		  
	  DismissByEnergyCut=true;
	}
      if( !   ((it->eta()>EtaMinThreshold)&&(it->eta()<EtaMaxThreshold))  )
	{
	  DismissByEtaCut=true;
	}
    }
  
  else
    {
      DismissByNoJet=true;
    }


  Handle<CaloTowerCollection> MyCaloTowers;
  iEvent.getByLabel(CaloTowerTag_,MyCaloTowers);
  
  std::vector<CaloTower> MyCaloVector;
  
  MyCaloVector.insert(MyCaloVector.end(),MyCaloTowers->begin(),MyCaloTowers->end());
  
  sort(MyCaloVector.begin(),MyCaloVector.end(),compare_ct());
  
  int Count=0;
  double FirstiPhi=200;
  double FirstiEta=200;
  
  bool DismissAsHPDNoise;
  if(CaloTowerVeto) DismissAsHPDNoise =true;





  for(std::vector<CaloTower>::const_iterator it = MyCaloVector.begin(); (Count!=CaloTowerCount)&&(it!=MyCaloVector.end()); it++){
    
    if(Verbose)
      {
	std::cout << "Energy, eta, phi of tower " << Count << std::endl;
	std::cout << "Still checking: " << StillCheckingForLeaders << std::endl;
	std::cout << it->energy() << "  " << it->ieta() << "  " <<it->iphi() << std::endl;
      }
    
    if((it->eta()>(-CentralEta))&&(it->eta()<CentralEta))
      {
	if((FirstiEta==200)&&(FirstiPhi==200))
	  {
	    FirstiPhi=it->iphi();
	    FirstiEta=it->ieta();
	    DismissAsEndcapNoise=true;
	  }	  
	if(it->energy()<CaloTowerEMin) DismissByTopCaloThresh=true;
    
	if(it->iphi()!=FirstiPhi)
	  {
	    DismissAsHPDNoise=false;
	    if(Verbose) std::cout<<"Only "<<Count<<" Leaders, no HPD cut" << std::endl;
	  }

	Count++;
      }
  }


  int NThresholdLimit=10;
  
  NOverThresh5=0;
  NOverThresh10=0;
  NOverThresh15=0;
  NOverThresh20=0;
  NOverThresh25=0;
  NOverThresh30=0;

  Count=0;

  for(std::vector<CaloTower>::const_iterator it = MyCaloVector.begin(); (Count!=NThresholdLimit)&&(it!=MyCaloVector.end()); it++){
    {
	if((it->iphi()==FirstiPhi)&&(it->energy() > 5)) NOverThresh5++;
	if((it->iphi()==FirstiPhi)&&(it->energy() > 10)) NOverThresh10++;
	if((it->iphi()==FirstiPhi)&&(it->energy() > 15)) NOverThresh15++;
	if((it->iphi()==FirstiPhi)&&(it->energy() > 20)) NOverThresh20++;
	if((it->iphi()==FirstiPhi)&&(it->energy() > 25)) NOverThresh25++;
	if((it->iphi()==FirstiPhi)&&(it->energy() > 30)) NOverThresh30++;
       
	Count++;
      }
  }


  if(NOverThresh5 > NOver5) DismissBy5Thresh=true;
 
 


  if(   DismissAsHPDNoise      ||  
	DismissBy5Thresh       ||
	DismissByEnergyCut     ||
	DismissByEtCut         ||
	DismissByEtaCut        ||
	DismissByn60Cut        ||
	DismissByn90Cut        ||
	DismissByNoJet)
                SelectEvent=false;      

  if(DismissByEtaCut) RejectCount->Fill("EtaCut",1);
  if(DismissByEnergyCut) RejectCount->Fill("EnergyCut",1);
  if(DismissByEtCut) RejectCount->Fill("ETCut",1);
  if(DismissByn90Cut) RejectCount->Fill("n90Cut",1);
  if(DismissByn60Cut) RejectCount->Fill("n60Cut",1);
  if(DismissBy5Thresh) RejectCount->Fill("5GevThreshCut",1);  
  if(DismissByNoJet) RejectCount->Fill("NoJet",1);
  if(DismissAsHPDNoise) RejectCount->Fill("CaloTowersPerHPD",1);



  FilterTree->Fill();

  






  return SelectEvent;


}

// ------------ method called once each job just before starting event loop  ------------
void 
CaloFilter::beginJob(const edm::EventSetup&)
{
}

// ------------ method called once each job just after ending the event loop  ------------
void 
CaloFilter::endJob() {
}



  
//define this as a plug-in
DEFINE_FWK_MODULE(CaloFilter);
