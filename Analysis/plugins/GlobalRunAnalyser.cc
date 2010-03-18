// -*- C++ -*-
//
// Package:    GlobalRunAnalyser
// Class:      GlobalRunAnalyser
// 
/**\class GlobalRunAnalyser GlobalRunAnalyser.cc GluinoAnalyzers/GlobalRunAnalyser/src/GlobalRunAnalyser.cc

 Description: <one line class summary>

 Implementation:
     <Notes on implementation>
*/
//
// Original Author:  Benjamin JONES
//         Created:  Thu Dec  4 11:44:26 CET 2008
// $Id: GlobalRunAnalyser.cc,v 1.3 2010/02/26 15:56:34 jbrooke Exp $
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

#include "DataFormats/HcalRecHit/interface/HcalRecHitCollections.h"
#include "DataFormats/HcalDetId/interface/HcalDetId.h"

#include "DataFormats/CaloTowers/interface/CaloTowerCollection.h"

#include "DataFormats/JetReco/interface/CaloJetCollection.h"

//#include "SimDataFormats/HepMCProduct/interface/HepMCProduct.h"

#include "DataFormats/HcalDigi/interface/HBHEDataFrame.h"
#include "DataFormats/HcalDigi/interface/HcalDigiCollections.h"

#include "DataFormats/MuonReco/interface/MuonFwd.h"
#include "DataFormats/MuonReco/interface/Muon.h"

#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "TH1.h"
#include "TTree.h"
#include "TF1.h"






//
// class decleration
//

class GlobalRunAnalyser : public edm::EDAnalyzer {
   public:
      explicit GlobalRunAnalyser(const edm::ParameterSet&);
      ~GlobalRunAnalyser();


   private:
      virtual void beginJob() ;
      virtual void analyze(const edm::Event&, const edm::EventSetup&);
      virtual void endJob() ;



  public:

      struct compare_ct : public std::binary_function<CaloTower, CaloTower, bool> {
         bool operator()(const CaloTower& x, const CaloTower& y) {
           return ( x.energy() > y.energy() ) ;
         }
       };

      struct compare_df : public std::binary_function<HBHEDataFrame, HBHEDataFrame, bool> {
	bool operator()(const HBHEDataFrame& x, const HBHEDataFrame& y) {
	  float TotalX=0;
	  float TotalY=0;
	  for(int i=0; i<10; i++)
	    {
	      TotalX += x.sample(i).nominal_fC();
	      TotalY += y.sample(i).nominal_fC();
	    }
	  return (TotalX > TotalY ) ;
         }
      };


  private:


  TTree * EventTree;
 
  Int_t CTMaxiEta_;
  Int_t CTMaxiPhi_;
  Float_t CTMaxEnergy_;
  Float_t CTMaxEt_;
  Float_t CTMaxEta_;
  Float_t CTMaxPhi_;
  Float_t CTMaxZSide_;
  Float_t CTMaxEnergyHad_;
  Float_t CTMaxEnergyEm_;
  Float_t CTMaxEtHad_;
  Float_t CTMaxEtEm_;
  
  Float_t LeadingJetEt_;
  Float_t LeadingJetEta_;
  Float_t LeadingJetPhi_;
  Float_t LeadingJetEnergy_;
  Float_t LeadingJetEmInEB_;
  Float_t LeadingJetHadInHB_;
  Float_t LeadingJetMaxEInEmTowers_;
  Float_t LeadingJetMaxEInHadTowers_;
  Float_t LeadingJetTowerArea_;
  Int_t LeadingJetn60_;
  Int_t LeadingJetn90_;

  Float_t LeadingCenJetEt_;
  Float_t LeadingCenJetEta_;
  Float_t LeadingCenJetPhi_;
  Float_t LeadingCenJetEnergy_;
  Float_t LeadingCenJetEmInEB_;
  Float_t LeadingCenJetHadInHB_;
  Float_t LeadingCenJetMaxEInEmTowers_;
  Float_t LeadingCenJetMaxEInHadTowers_;
  Float_t LeadingCenJetTowerArea_;
  Int_t LeadingCenJetn60_;
  Int_t LeadingCenJetn90_;


  Long64_t EventID_;
  Long64_t LumiNumber_;
  Long64_t RunNumber_;
  Long64_t TimeStamp_;

  Int_t NoOfJets_;
  Int_t NoOfCenJets_;
  
  Int_t NoLeaders_;
  Int_t NoLeaders2_;
  Int_t NOverThresh5_;
  Int_t NOverThresh10_;
  Int_t NOverThresh15_;
  Int_t NOverThresh20_;
  Int_t NOverThresh25_; 
  Int_t NOverThresh30_;


  Int_t NCaloTowersInTopHPD_;

  Float_t TimingFirstBin_;
  Float_t TimingFirst2Bins_;
  Float_t TimingLastBin_;
  Float_t TimingLast2Bins_;
  Float_t TimingLeftPeak_;
  Float_t TimingRightPeak_;
  Float_t TimingFracInLeader_;
  Float_t TimingFracRightNextRight_;
  Float_t TimingFracPeakNextRight_;
  Int_t Timingn60_;
  Int_t Timingn70_;
  Int_t Timingn80_;
  Int_t Timingn90_;
  Float_t TimingBX0_;
  Float_t TimingBX1_;
  Float_t TimingBX2_;
  Float_t TimingBX3_;
  Float_t TimingBX4_;
  Float_t TimingBX5_;
  Float_t TimingBX6_;
  Float_t TimingBX7_;
  Float_t TimingBX8_;
  Float_t TimingBX9_;
  Float_t TimingTotal_;
  Float_t TimingFracInCentralFour_;
  
  Float_t VtxX_;
  Float_t VtxY_;
  Float_t VtxZ_;
  Float_t VtxT_;
  Float_t VtxR_;
  Float_t SusyMomX_;
  Float_t SusyMomY_;
  Float_t SusyMomZ_;
  Float_t SusyMomR_;
  Float_t SusyEnergy_;
  Int_t SusyPDG_;

  Int_t NoOfMuons_;

  bool IncludeCaloTowers_;
  bool IncludeJets_;
  bool IncludeJetDetails_;
  bool IncludeDigis_;
  bool IncludeMC_;
  bool IncludeMuons_;
  bool IncludeDigisOld_;
  bool WriteHistos_;
  bool IncludeHPDVeto_;

  edm::InputTag DigisTag_;
  edm::InputTag RecHitTag_;
  edm::InputTag JetTag_;
  edm::InputTag CaloTowerTag_;
  edm::InputTag MCTag_;
  edm::InputTag MuonTag_;

  float CenJetEta_;
  int DigiCount_;
  

  Int_t PeakPosition_;
  Float_t TotalOverTime_;
  Float_t TimingRightNextNextRight_;
  Float_t TimingPeakNextNextRight_;
  Float_t TimingRightNextRight_;
  Float_t TimingPeakNextRight_;
  Float_t TimingNoOfChannels_;

  Float_t TimingExpSlope_;
  Float_t TimingExpConst_;
  Float_t TimingExpChiSq_;
  Float_t TimingEnergyBeforePorch_;
  Float_t TimingEnergyBeforePeak_;

  edm::Service<TFileService> fs;





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
GlobalRunAnalyser::GlobalRunAnalyser(const edm::ParameterSet& iConfig):
  IncludeJetDetails_(iConfig.getUntrackedParameter("IncludeJetDetails",true)),
  IncludeJets_(iConfig.getUntrackedParameter("IncludeJets",true)),
  IncludeCaloTowers_(iConfig.getUntrackedParameter("IncludeCaloTowers",true)),
  IncludeMC_(iConfig.getUntrackedParameter("IncludeMC",false)),
  IncludeDigis_(iConfig.getUntrackedParameter("IncludeDigis",false)),
  IncludeMuons_(iConfig.getUntrackedParameter("IncludeMuons",false)),
  IncludeDigisOld_(iConfig.getUntrackedParameter("IncludeDigisOld",false)),
  

  DigisTag_(iConfig.getUntrackedParameter("DigisTag",edm::InputTag("hcalDigis"))),
  JetTag_(iConfig.getUntrackedParameter("JetTag",edm::InputTag("iterativeCone5CaloJets"))),
  CaloTowerTag_(iConfig.getUntrackedParameter("CaloToweTag",edm::InputTag("towerMaker"))),
  MCTag_(iConfig.getUntrackedParameter("MCTag",edm::InputTag("source"))),
  MuonTag_(iConfig.getUntrackedParameter("MuonsTag",edm::InputTag("muons"))),
  
  
  DigiCount_(iConfig.getUntrackedParameter("DigiCount",5)),
  CenJetEta_(iConfig.getUntrackedParameter("CenJetEta",1.3)),
  WriteHistos_(iConfig.getUntrackedParameter("WriteHistos",false))
  
{
   //now do what ever initialization is needed



  
  

  EventTree=fs->make<TTree>("EventTree", "Per Event Rec Hit Info");
 
  if(IncludeCaloTowers_)
    {

      EventTree->Branch("CTMaxiEta",&CTMaxiEta_,"CTMaxiEta_/I");
      EventTree->Branch("CTMaxiPhi",&CTMaxiPhi_,"CTMaxiPhi_/I");
      EventTree->Branch("CTMaxEnergy",&CTMaxEnergy_,"CTMaxEnergy_/F");
      EventTree->Branch("CTMaxEt",&CTMaxEt_,"CTMaxEt_/F");
      EventTree->Branch("CTMaxEta",&CTMaxEta_,"CTMaxEta_/F");
      EventTree->Branch("CTMaxPhi",&CTMaxPhi_,"CTMaxPhi_/F");
      EventTree->Branch("CTMaxEnergyHad",&CTMaxEnergyHad_,"CTMaxEnergyHad/F");
      EventTree->Branch("CTMaxEtHad",&CTMaxEtHad_,"CTMaxEtHad/F");
      EventTree->Branch("CTMaxEnergyEm",&CTMaxEnergyEm_,"CTMaxEnergyEm/F");
      EventTree->Branch("CTMaxEtEm",&CTMaxEtEm_,"CTMaxEtEm/F");
      
      EventTree->Branch("CTNoLeaders",&NoLeaders_,"CTNoLeaders/I");
      EventTree->Branch("CTNoLeaders2",&NoLeaders2_,"CTNoLeaders2/I");
      EventTree->Branch("CTNOverThresh5",&NOverThresh5_,"CTNOverThresh5/I");
      EventTree->Branch("CTNOverThresh10",&NOverThresh10_,"CTNOverThresh10/I");
      EventTree->Branch("CTNOverThresh15",&NOverThresh15_,"CTNOverThresh15/I");
      EventTree->Branch("CTNOverThresh20",&NOverThresh20_,"CTNOverThresh20/I");
      EventTree->Branch("CTNOverThresh25",&NOverThresh25_,"CTNOverThresh25/I");
      EventTree->Branch("CTNOverThresh30",&NOverThresh30_,"CTNOverThresh30/I");
    }



  if(IncludeJets_)
    {
      EventTree->Branch("NCaloTowersInTopHPD",&NCaloTowersInTopHPD_,"NCaloTowersInTopHPD/I");
      EventTree->Branch("LeadingJetEta",&LeadingJetEta_,"LeadingJetEta/F");
      EventTree->Branch("LeadingJetPhi",&LeadingJetPhi_,"LeadingJetEta/F");
      EventTree->Branch("LeadingJetEnergy",&LeadingJetEnergy_,"LeadingJetEnergy/F");
      EventTree->Branch("LeadingJetEt",&LeadingJetEt_,"LeadingJetEt/F");    
      EventTree->Branch("LeadingCenJetEta",&LeadingCenJetEta_,"LeadingCenJetEta/F");
      EventTree->Branch("LeadingCenJetPhi",&LeadingCenJetPhi_,"LeadingCenJetEta/F");
      EventTree->Branch("LeadingCenJetEnergy",&LeadingCenJetEnergy_,"LeadingCenJetEnergy/F");
      EventTree->Branch("LeadingCenJetEt",&LeadingCenJetEt_,"LeadingCenJetEt/F");
      EventTree->Branch("NoOfJets",&NoOfJets_,"NoOfJets/I");
      EventTree->Branch("NoOfCenJets",&NoOfCenJets_,"NoOfCenJets/I");
    }

  if(IncludeJetDetails_)
    {
      EventTree->Branch("LeadingJetEmInEB",&LeadingJetEmInEB_,"LeadingJetEmInEB/F");
      EventTree->Branch("LeadingJetHadInHB",&LeadingJetHadInHB_,"LeadingJetHadInHB/F");
      EventTree->Branch("LeadingJetMaxEInEmTowers",&LeadingJetMaxEInEmTowers_,"LeadingJetMaxEInEmTowers/F");
      EventTree->Branch("LeadingJetMaxEInHadTowers",&LeadingJetMaxEInHadTowers_,"LeadingJetMaxEInHadTowers/F");
      EventTree->Branch("LeadingJetTowerArea",&LeadingJetTowerArea_,"LeadingJetTowerArea/F");
      EventTree->Branch("LeadingJetn60",&LeadingJetn60_,"LeadingJetn60/I");
      EventTree->Branch("LeadingJetn90",&LeadingJetn90_,"LeadingJetn90/I");

      EventTree->Branch("LeadingCenJetEmInEB",&LeadingCenJetEmInEB_,"LeadingCenJetEmInEB/F");
      EventTree->Branch("LeadingCenJetHadInHB",&LeadingCenJetHadInHB_,"LeadingCenJetHadInHB/F");
      EventTree->Branch("LeadingCenJetMaxEInEmTowers",&LeadingCenJetMaxEInEmTowers_,"LeadingCenJetMaxEInEmTowers/F");
      EventTree->Branch("LeadingCenJetMaxEInHadTowers",&LeadingCenJetMaxEInHadTowers_,"LeadingCenJetMaxEInHadTowers/F");
      EventTree->Branch("LeadingCenJetTowerArea",&LeadingCenJetTowerArea_,"LeadingCenJetTowerArea/F");
      EventTree->Branch("LeadingCenJetn60",&LeadingCenJetn60_,"LeadingCenJetn60/I");
      EventTree->Branch("LeadingCenJetn90",&LeadingCenJetn90_,"LeadingCenJetn90/I");

      EventTree->Branch("TimingExpConst",&TimingExpConst_,"TimingExpConst/F");
      EventTree->Branch("TimingExpSlope",&TimingExpSlope_,"TimingExpSlope/F");
      EventTree->Branch("TimingExpChiSq",&TimingExpChiSq_,"TimingExpChiSq/F");
    }

  if(IncludeMC_)
    {
      EventTree->Branch("VtxX",&VtxX_,"VtxX/F");
      EventTree->Branch("VtxY",&VtxY_,"VtxY/F");
      EventTree->Branch("VtxZ",&VtxZ_,"VtxZ/F");
      EventTree->Branch("VtxR",&VtxR_,"VtxR/F");
      EventTree->Branch("VtxT",&VtxT_,"VtxT/F");
      
      EventTree->Branch("SusyMomX",&SusyMomX_,"SusyMomX/F");
      EventTree->Branch("SusyMomY",&SusyMomY_,"SusyMomY/F");
      EventTree->Branch("SusyMomZ",&SusyMomZ_,"SusyMomZ/F");
      EventTree->Branch("SusyMomR",&SusyMomR_,"SusyMomR/F");
      
      EventTree->Branch("SusyEnergy",&SusyEnergy_,"SusyEnergy/I");
      
      EventTree->Branch("SusyPDG",&SusyPDG_,"SusyPDG/I");
    }

  if(IncludeDigisOld_)
    {
      EventTree->Branch("TimingFirstBin",&TimingFirstBin_,"TimingFirstBin/F");
      EventTree->Branch("TimingFirst2Bins",&TimingFirst2Bins_,"TimingFirst2Bins/F");
      EventTree->Branch("TimingLastBin",&TimingLastBin_,"TimingLastBin/F");
      EventTree->Branch("TimingLast2Bins",&TimingLast2Bins_,"TimingLast2Bins/F");
      EventTree->Branch("TimingLeftPeak",&TimingLeftPeak_,"TimingFracLeft/F");
      EventTree->Branch("TimingRightPeak",&TimingRightPeak_,"TimingRightPeak/F");
      EventTree->Branch("TimingFracInLeader",&TimingFracInLeader_,"TimingFracInLeader/F");
      EventTree->Branch("Timingn60",&Timingn60_,"Timingn60/I");
      EventTree->Branch("Timingn70",&Timingn70_,"Timingn70/I");
      EventTree->Branch("Timingn80",&Timingn80_,"Timingn80/I");
      EventTree->Branch("Timingn90",&Timingn90_,"Timingn90/I"); 
      EventTree->Branch("TimingBX0",&TimingBX0_,"TimingBX0/F");
      EventTree->Branch("TimingBX1",&TimingBX1_,"TimingBX1/F");
      EventTree->Branch("TimingBX2",&TimingBX2_,"TimingBX2/F");
      EventTree->Branch("TimingBX3",&TimingBX3_,"TimingBX3/F");
      EventTree->Branch("TimingBX4",&TimingBX4_,"TimingBX4/F");
      EventTree->Branch("TimingBX5",&TimingBX5_,"TimingBX5/F");
      EventTree->Branch("TimingBX6",&TimingBX6_,"TimingBX6/F");
      EventTree->Branch("TimingBX7",&TimingBX7_,"TimingBX7/F");
      EventTree->Branch("TimingBX8",&TimingBX8_,"TimingBX8/F");
      EventTree->Branch("TimingBX9",&TimingBX9_,"TimingBX9/F");
      EventTree->Branch("TimingFracRightNextRight",&TimingFracRightNextRight_,"TimingFracRightNextRight/F");
      EventTree->Branch("TimingFracPeakNextRight",&TimingFracPeakNextRight_,"TimingFracPeakNextRight/F");
      EventTree->Branch("TimingFracInCentralFour",&TimingFracInCentralFour_,"TimingFracInCentralFour/F");
      EventTree->Branch("TimingTotal",&TimingTotal_,"TimingTotal/F");
      EventTree->Branch("TimingNoOfChannels",&TimingNoOfChannels_,"TimingNoOfChannels/F");
      EventTree->Branch("TimingEnergyBeforePorch",&TimingEnergyBeforePorch_,"TimingEnergyBeforePorch/F");
      EventTree->Branch("TimingEnergyBeforePeak",&TimingEnergyBeforePeak_,"TimingEnergyBeforePeak/F");
    }

  if(IncludeDigis_)
    {
      EventTree->Branch("TimingFirstBin",&TimingFirstBin_,"TimingFirstBin/F");
      EventTree->Branch("TimingFirst2Bins",&TimingFirst2Bins_,"TimingFirst2Bins/F");
      EventTree->Branch("TimingLastBin",&TimingLastBin_,"TimingLastBin/F");
      EventTree->Branch("TimingLast2Bins",&TimingLast2Bins_,"TimingLast2Bins/F");
      EventTree->Branch("TimingLeftPeak",&TimingLeftPeak_,"TimingFracLeft/F");
      EventTree->Branch("TimingRightPeak",&TimingRightPeak_,"TimingRightPeak/F");
      EventTree->Branch("TimingFracInLeader",&TimingFracInLeader_,"TimingFracInLeader/F");
      EventTree->Branch("Timingn60",&Timingn60_,"Timingn60/I");
      EventTree->Branch("Timingn70",&Timingn70_,"Timingn70/I");
      EventTree->Branch("Timingn80",&Timingn80_,"Timingn80/I");
      EventTree->Branch("Timingn90",&Timingn90_,"Timingn90/I"); 
      EventTree->Branch("TimingBX0",&TimingBX0_,"TimingBX0/F");
      EventTree->Branch("TimingBX1",&TimingBX1_,"TimingBX1/F");
      EventTree->Branch("TimingBX2",&TimingBX2_,"TimingBX2/F");
      EventTree->Branch("TimingBX3",&TimingBX3_,"TimingBX3/F");
      EventTree->Branch("TimingBX4",&TimingBX4_,"TimingBX4/F");
      EventTree->Branch("TimingBX5",&TimingBX5_,"TimingBX5/F");
      EventTree->Branch("TimingBX6",&TimingBX6_,"TimingBX6/F");
      EventTree->Branch("TimingBX7",&TimingBX7_,"TimingBX7/F");
      EventTree->Branch("TimingBX8",&TimingBX8_,"TimingBX8/F");
      EventTree->Branch("TimingBX9",&TimingBX9_,"TimingBX9/F");
      EventTree->Branch("TimingRightNextRight",&TimingRightNextRight_,"TimingRightNextRight/F");
      EventTree->Branch("TimingPeakNextRight",&TimingPeakNextRight_,"TimingPeakNextRight/F");
      EventTree->Branch("TimingFracInCentralFour",&TimingFracInCentralFour_,"TimingFracInCentralFour/F");
      EventTree->Branch("TimingTotal",&TotalOverTime_,"TimingTotal/F");

      EventTree->Branch("TimingPeakPosition", &PeakPosition_,"TimingPeakPosition/I");
      
      EventTree->Branch("TimingTotalOverTime",&TotalOverTime_,"TimingTotalOverTime/F");
      EventTree->Branch("TimingRightNextNextRight",&TimingRightNextNextRight_,"TimingRightNextNextRight/F");
      EventTree->Branch("TimingPeakNextNextRight",&TimingPeakNextNextRight_,"TimingPeakNextNextRight/F");






    }
  
  

  

  if(IncludeMuons_)
    {
      EventTree->Branch("NoOfMuons",&NoOfMuons_,"NoOfMuons/I");
    }

  EventTree->Branch("EventID",&EventID_,"EventID/L");
  EventTree->Branch("RunNumber",&RunNumber_,"RunNumber/L");
  EventTree->Branch("LumiNumber",&LumiNumber_,"LumiNumber/L");
  EventTree->Branch("TimeStamp",&TimeStamp_,"TimeStamp/L");






}


GlobalRunAnalyser::~GlobalRunAnalyser()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called to for each event  ------------
void
GlobalRunAnalyser::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   using namespace edm;


   EventID_=iEvent.id().event();
   RunNumber_=iEvent.id().run();
   LumiNumber_=iEvent.luminosityBlock();
   TimeStamp_=iEvent.time().value();

   // std::cout<<iEvent.time().value()<<std::endl;
   // std::cout<<iEvent.orbitNumber()<<"  " << iEvent.bunchCrossing()<<std::endl ;

   
   if(IncludeJets_)
     {
       
       // Jets
       
       
       using namespace reco;
       
       Handle<CaloJetCollection> pCalo5;
       iEvent.getByLabel(JetTag_,pCalo5);
       
       LeadingJetEnergy_=-10;
       LeadingJetEta_=0;
       LeadingJetEt_=-10;
       LeadingJetEta_=0;
       LeadingJetPhi_=0;
       LeadingJetEmInEB_=0;
       LeadingJetHadInHB_=0;
       LeadingJetMaxEInEmTowers_=0;
       LeadingJetMaxEInHadTowers_=0;
       LeadingJetTowerArea_=0;
       LeadingJetn60_=0;
       LeadingJetn90_=0;

       LeadingCenJetEnergy_=-10;
       LeadingCenJetEta_=0;
       LeadingCenJetEt_=-10;
       LeadingCenJetEta_=0;
       LeadingCenJetPhi_=0;
       LeadingCenJetEmInEB_=0;
       LeadingCenJetHadInHB_=0;
       LeadingCenJetMaxEInEmTowers_=0;
       LeadingCenJetMaxEInHadTowers_=0;
       LeadingCenJetTowerArea_=0;
       LeadingCenJetn60_=0;
       LeadingCenJetn90_=0;

       NoOfJets_=0;
       
       


       for(CaloJetCollection::const_iterator it=pCalo5->begin();it!=pCalo5->end();it++)
	 {
	   if(it->energy()<1000)
	     {
	       NoOfJets_++;
	       if(NoOfJets_==1)
		 {
		   if((it->eta()>(0-CenJetEta_))&&(it->eta()<CenJetEta_))
		     {
		       
		       LeadingCenJetEt_=it->et();
		       LeadingCenJetEta_=it->eta();
		       LeadingCenJetPhi_=it->phi();
		       LeadingCenJetEnergy_=it->energy();
		       LeadingCenJetEmInEB_=it->emEnergyInEB();
		       LeadingCenJetHadInHB_=it->hadEnergyInHB();
		       LeadingCenJetMaxEInEmTowers_=it->maxEInEmTowers();
		       LeadingCenJetMaxEInHadTowers_=it->maxEInHadTowers();
		       LeadingCenJetTowerArea_=it->towersArea();
		       //	   std::cout<< "n60, n90"<<std::endl<<it->n60()<<", "<<it->n90()<<std::endl;
		       LeadingCenJetn60_=it->n60();
		       LeadingCenJetn90_=it->n90();
		     }
		   LeadingJetEt_=it->et();
		   LeadingJetEta_=it->eta();
		   LeadingJetPhi_=it->phi();
		   LeadingJetEnergy_=it->energy();
		   LeadingJetEmInEB_=it->emEnergyInEB();
		   LeadingJetHadInHB_=it->hadEnergyInHB();
		   LeadingJetMaxEInEmTowers_=it->maxEInEmTowers();
		   LeadingJetMaxEInHadTowers_=it->maxEInHadTowers();
		   LeadingJetTowerArea_=it->towersArea();
		   //	   std::cout<< "n60, n90"<<std::endl<<it->n60()<<", "<<it->n90()<<std::endl;
		   LeadingJetn60_=it->n60();
		   LeadingJetn90_=it->n90();
		   
		 }
	       else
		 {
		   if(LeadingJetEnergy_ < it->energy())
		     {
		      
		       LeadingJetEt_=it->et();
		       LeadingJetEta_=it->eta();
		       LeadingJetPhi_=it->phi();
		       LeadingJetEnergy_=it->energy();
		       LeadingJetEmInEB_=it->emEnergyInEB();
		       LeadingJetHadInHB_=it->hadEnergyInHB();
		       LeadingJetMaxEInEmTowers_=it->maxEInEmTowers();
		       LeadingJetMaxEInHadTowers_=it->maxEInHadTowers();
		       LeadingJetTowerArea_=it->towersArea();
		       //   std::cout<< "n60, n90"<<std::endl<<it->n60()<<", "<<it->n90()<<std::endl;
		       LeadingJetn60_=it->n60();
		       LeadingJetn90_=it->n90();
		     }

		   if((it->eta()>(0-CenJetEta_))&&(it->eta()<CenJetEta_)&&(it->energy()>LeadingCenJetEnergy_))
		     {
		       
		       LeadingCenJetEt_=it->et();
		       LeadingCenJetEta_=it->eta();
		       LeadingCenJetPhi_=it->phi();
		       LeadingCenJetEnergy_=it->energy();
		       LeadingCenJetEmInEB_=it->emEnergyInEB();
		       LeadingCenJetHadInHB_=it->hadEnergyInHB();
		       LeadingCenJetMaxEInEmTowers_=it->maxEInEmTowers();
		       LeadingCenJetMaxEInHadTowers_=it->maxEInHadTowers();
		       LeadingCenJetTowerArea_=it->towersArea();
		       //	   std::cout<< "n60, n90"<<std::endl<<it->n60()<<", "<<it->n90()<<std::endl;
		       LeadingCenJetn60_=it->n60();
		       LeadingCenJetn90_=it->n90();
		     }
		   
		 }
	       
	     }
	 }

       Handle<CaloTowerCollection> MyCaloTowers;
       iEvent.getByLabel(CaloTowerTag_,MyCaloTowers);

       std::vector<CaloTower> MyCaloVector;
       
       MyCaloVector.insert(MyCaloVector.end(),MyCaloTowers->begin(),MyCaloTowers->end());
       
       sort(MyCaloVector.begin(),MyCaloVector.end(),compare_ct());

       int FirstEta=200;
       int FirstPhi=200;
       bool KeepChecking=true;

       NCaloTowersInTopHPD_=0;
         
       for(std::vector<CaloTower>::const_iterator it = MyCaloVector.begin(); (it!=MyCaloVector.end())&&(KeepChecking);it++)
	 {
	   if((it->eta()<1.3)&&(it->eta()>-1.3))
	     {
	       if((FirstEta==200)&&(FirstPhi==200))
		 {
		   FirstEta=it->ieta();
		   FirstPhi=it->iphi();
		 }
	       else
		 {
		   if(it->iphi()==FirstPhi)
		     NCaloTowersInTopHPD_++;
		   else
		     KeepChecking=false;
		 }
		      
	     }
	       
	 }




     }







   //
   //
   // Monte Carlo Analysis
   //
   //


   if(IncludeMC_)
     {
       
//        Handle<edm::HepMCProduct> mcHandle;
//        iEvent.getByLabel(MCTag_,mcHandle);
       
//        const edm::HepMCProduct *mcProd = mcHandle.product();
//        const HepMC::GenEvent *evt = mcProd->GetEvent();
       
//        for(HepMC::GenEvent::vertex_const_iterator pitr = evt->vertices_begin(); pitr!= evt->vertices_end(); ++pitr)
// 	 {
	   
// 	   if((*pitr)->barcode()==-1)
// 	     {
	       
// 	       VtxR_ = (*pitr)->point3d().perp();
// 	       VtxX_ = (*pitr)->point3d().x();
// 	       VtxY_ = (*pitr)->point3d().y();
// 	       VtxZ_ = (*pitr)->point3d().z();
	       
// 	       VtxT_ = (*pitr)->position().t();

// 	       for(HepMC::GenVertex::particles_out_const_iterator part = (*pitr)->particles_out_const_begin(); part!=(*pitr)->particles_out_const_end(); ++part)
// 		 {
// 		   //	std::cout << (*part)->pdg_id()<<std::endl;
// 		   if((*part)->pdg_id()>=1000000)
// 		     {
// 		       SusyMomX_=(*part)->momentum().x();
// 		       SusyMomY_=(*part)->momentum().y();
// 		       SusyMomZ_=(*part)->momentum().z();
// 		       SusyMomR_=(*part)->momentum().perp();
// 		       SusyEnergy_=(*part)->momentum().e();
// 		       SusyPDG_=(*part)->pdg_id()-1000000;
// 		     }
// 		 }
// 	     }
// 	 }
     }
   



   //
   //
   //   Timing Information
   //
   //

   /*
   if(IncludeDigisJet_)
     {
       
       using namespace reco;
       
       
       float ThisSpectrum[10];
   

       std::vector<HcalDetId> HBDigisInLeadingCenJet;

       edm::Handle<CaloJetCollection> pCalo;
       iEvent.getByLabel(JetTag_,pCalo);
       
       double LeadingJetEnergy=0;
       double LeadingJetEta=0;
       double LeadingJetPhi=0;

       for(reco::CaloJetCollection::const_iterator itJet = pCalo->begin(); itJet!=pCalo->end(); itJet++)
	 {
	   if(LeadingJetEnergy<itJet->energy())
	     {
	       LeadingJetEnergy=it->energy();
	       LeadingJetEta=it->eta();
	       LeadingJetPhi=it->phi();
	     }
	 }
       

       
       for(int k=0; k<10; k++)
	 {
	   ThisSpectrum[k]=0;
	 }
       
       double ThisEnergy=0;
       int JetDigiCount=0;

       Handle<HBHEDigiCollection > pDigi;
       iEvent.getByLabel(DigisTag_,pDigi);

       std::cout<<"No of digis with energy : " << HBDigisInLeadingCenJet.size()<<std::endl;
       for(HBHEDigiCollection::const_iterator itDigi=pDigi->begin();itDigi!=pDigi->end(); itDigi++)
	 {
	   
	   for(int i=0; i!=HBDigisInLeadingCenJet.size(); i++)
	     {
	       if(itDigi->id()==HBDigisInLeadingCenJet.at(i))
		 {
		   std::cout<<"Found HCal Digi : "<<itDigi->id().ieta() << " " <<itDigi->id().iphi()<<std::endl;
		   for(int j=0; j<10; j++)
		     {
		       ThisEnergy+=itDigi->sample(j).nominal_fC();
		     }
		   //  if(ThisEnergy>10)
		     {
		       for(int j=0; j<10; j++)
			 {
		       	  
			   ThisSpectrum[j]+=itDigi->sample(j).nominal_fC();
			  
		     
			 }
		     }
		   JetDigiCount++;
		 }
	     }


	 }

       std::cout<<"DEBUG Made it here -1"<<std::endl;
 

       TotalOverTime_=ThisEnergy;
       PeakPosition_=0;
       for(int i=0; i<10; i++)
	 {
	   if(ThisSpectrum[i]>ThisSpectrum[PeakPosition_])
	     PeakPosition_=i;
	       
	 }
   


       //Fraction left and right of peak
       
       TimingFracInLeader_=ThisSpectrum[PeakPosition_]/TotalOverTime_;
       
       TimingLeftPeak_=TimingRightPeak_=0;
       TimingRightNextRight_= TimingPeakNextRight_=0;
       TimingRightNextNextRight_=TimingPeakNextNextRight_=0;

       if(ThisSpectrum[PeakPosition_]!=0)
	 {
	   if(PeakPosition_!=0)
	     TimingLeftPeak_=ThisSpectrum[PeakPosition_-1]/ThisSpectrum[PeakPosition_];
	   
	   if(PeakPosition_!=9)
	     TimingRightPeak_=ThisSpectrum[PeakPosition_+1]/ThisSpectrum[PeakPosition_];

	   if((PeakPosition_!=9) && (PeakPosition_!=8) && (PeakPosition_!=7) && (PeakPosition_!=1))
	     TimingFracInCentralFour_=(ThisSpectrum[PeakPosition_]+ThisSpectrum[PeakPosition_-1]+ThisSpectrum[PeakPosition_+1]+ThisSpectrum[PeakPosition_+2])/TotalOverTime_;

	   if((PeakPosition_!=8) && (PeakPosition_!=9))
	     {
	       TimingRightNextRight_=ThisSpectrum[PeakPosition_+2]/ThisSpectrum[PeakPosition_+1];
	       TimingPeakNextRight_=ThisSpectrum[PeakPosition_+2]/ThisSpectrum[PeakPosition_];
	     }
	   
	   if((PeakPosition_!=7)&&(PeakPosition_!=8)&&(PeakPosition_!=9))
	     {
	       TimingRightNextNextRight_=ThisSpectrum[PeakPosition_+3]/ThisSpectrum[PeakPosition_+2];
	       TimingPeakNextNextRight_=ThisSpectrum[PeakPosition_+3]/ThisSpectrum[PeakPosition_];


	     }

	 }
       
       
       //n60, n70, n80, n90
       
       Timingn60_ = Timingn70_ = Timingn80_ = Timingn90_ = 0;
       
       std::vector<double> SortableSpec;
       SortableSpec.resize(10);
       for(int i=0; i<10; i++)
	 {
	   SortableSpec[i]=ThisSpectrum[i];
	 }
       
       std::sort(SortableSpec.begin(), SortableSpec.end());
       
       double TotalSoFar=0;
       int counter=0;
       
       for(int i=9; i>=0; i--)
	 {
	   counter++;
	   
	   TotalSoFar+=SortableSpec[i];
	   if(((TotalSoFar/TotalOverTime_) >= 0.6) && Timingn60_==0) Timingn60_ = counter;
	   if(((TotalSoFar/TotalOverTime_) >= 0.7) && Timingn70_==0) Timingn70_ = counter;
	   if(((TotalSoFar/TotalOverTime_) >= 0.8) && Timingn80_==0) Timingn80_ = counter;
	   if(((TotalSoFar/TotalOverTime_) >= 0.9) && Timingn90_==0) Timingn90_ = counter;
	 }		
       
       TimingBX0_=ThisSpectrum[0];
       TimingBX1_=ThisSpectrum[1];
       TimingBX2_=ThisSpectrum[2];
       TimingBX3_=ThisSpectrum[3];
       TimingBX4_=ThisSpectrum[4];
       TimingBX5_=ThisSpectrum[5];
       TimingBX6_=ThisSpectrum[6];
       TimingBX7_=ThisSpectrum[7];
       TimingBX8_=ThisSpectrum[8];	
       TimingBX9_=ThisSpectrum[9]; 
  
       std::cout<<"DEBUG: Made it here"<<std::endl;
       if(WriteHistos_)
	 {
	   std::stringstream HistName;
	   HistName.str("");
	   HistName<< "TimingPlotAll"<<iEvent.id().event();
	   TH1D* TheHist= fs->make<TH1D>(HistName.str().c_str(),HistName.str().c_str(),10,0,10);
	   for(int j=0; j!=10; j++)
	     {
	       TheHist->Fill(j,ThisSpectrum[j]);
	     }
	 }

     }



   */

   if(IncludeDigis_)
     {
       
       using namespace reco;
       
       
       float ThisSpectrum[10];
   

       std::vector<HcalDetId> HBDigisInLeadingCenJet;

       edm::Handle<CaloJetCollection> pCalo;
       iEvent.getByLabel(JetTag_,pCalo);


       for(reco::CaloJetCollection::const_iterator itJet = pCalo->begin(); itJet!=pCalo->end(); itJet++)
	 {
	   //  std::cout<<"Considering jet with eta "<<itJet->eta()<<std::endl;
	   //	   if(fabs(itJet->eta())<1.3)
	     {
	       //  std::cout<<"Including jet with E = " << itJet->energy() << std::endl;
	       std::vector<CaloTowerPtr> CaloTowers = itJet->getCaloConstituents();
	       for(std::vector<CaloTowerPtr>::const_iterator itCalo = CaloTowers.begin(); itCalo!=CaloTowers.end(); itCalo++)
		 {
		   // std::cout<<"Calo tower had energy " << (*itCalo)->hadEnergy()<<std::endl;
		   const std::vector<DetId>& CaloConst = (*itCalo)->constituents();
		   for(std::vector<DetId>::const_iterator itConst = CaloConst.begin(); itConst!=CaloConst.end(); itConst++)
		     {
		       if(itConst->det()==4)
			 {
			   HcalDetId HBId = HcalDetId(*itConst);
			   HBDigisInLeadingCenJet.push_back(HBId);
			   //	   std::cout<< "Storing : " << HBId.ieta() << "  " << HBId.iphi() << "  " <<HBId.depth()<<std::endl;
			 }
		     }
		 }
	     }
	   
	 }


       for(int k=0; k<10; k++)
	 {
	   ThisSpectrum[k]=0;
	 }
       
       double ThisEnergy=0;
       int JetDigiCount=0;

       Handle<HBHEDigiCollection > pDigi;
       iEvent.getByLabel(DigisTag_,pDigi);

       std::cout<<"No of digis with energy : " << HBDigisInLeadingCenJet.size()<<std::endl;
       for(HBHEDigiCollection::const_iterator itDigi=pDigi->begin();itDigi!=pDigi->end(); itDigi++)
	 {
	   
	   for(int i=0; i!=HBDigisInLeadingCenJet.size(); i++)
	     {
	       if(itDigi->id()==HBDigisInLeadingCenJet.at(i))
		 {
		   std::cout<<"Found HCal Digi : "<<itDigi->id().ieta() << " " <<itDigi->id().iphi()<<std::endl;
		   for(int j=0; j<10; j++)
		     {
		       ThisEnergy+=itDigi->sample(j).nominal_fC();
		     }
		   //  if(ThisEnergy>10)
		     {
		       for(int j=0; j<10; j++)
			 {
		       	  
			   ThisSpectrum[j]+=itDigi->sample(j).nominal_fC();
			  
		     
			 }
		     }
		   JetDigiCount++;
		 }
	     }


	 }

       std::cout<<"DEBUG Made it here -1"<<std::endl;
 

       TotalOverTime_=ThisEnergy;
       PeakPosition_=0;
       for(int i=0; i<10; i++)
	 {
	   if(ThisSpectrum[i]>ThisSpectrum[PeakPosition_])
	     PeakPosition_=i;
	       
	 }
   


       //Fraction left and right of peak
       
       TimingFracInLeader_=ThisSpectrum[PeakPosition_]/TotalOverTime_;
       
       TimingLeftPeak_=TimingRightPeak_=0;
       TimingRightNextRight_= TimingPeakNextRight_=0;
       TimingRightNextNextRight_=TimingPeakNextNextRight_=0;

       if(ThisSpectrum[PeakPosition_]!=0)
	 {
	   if(PeakPosition_!=0)
	     TimingLeftPeak_=ThisSpectrum[PeakPosition_-1]/ThisSpectrum[PeakPosition_];
	   
	   if(PeakPosition_!=9)
	     TimingRightPeak_=ThisSpectrum[PeakPosition_+1]/ThisSpectrum[PeakPosition_];

	   if((PeakPosition_!=9) && (PeakPosition_!=8) && (PeakPosition_!=7) && (PeakPosition_!=1))
	     TimingFracInCentralFour_=(ThisSpectrum[PeakPosition_]+ThisSpectrum[PeakPosition_-1]+ThisSpectrum[PeakPosition_+1]+ThisSpectrum[PeakPosition_+2])/TotalOverTime_;

	   if((PeakPosition_!=8) && (PeakPosition_!=9))
	     {
	       TimingRightNextRight_=ThisSpectrum[PeakPosition_+2]/ThisSpectrum[PeakPosition_+1];
	       TimingPeakNextRight_=ThisSpectrum[PeakPosition_+2]/ThisSpectrum[PeakPosition_];
	     }
	   
	   if((PeakPosition_!=7)&&(PeakPosition_!=8)&&(PeakPosition_!=9))
	     {
	       TimingRightNextNextRight_=ThisSpectrum[PeakPosition_+3]/ThisSpectrum[PeakPosition_+2];
	       TimingPeakNextNextRight_=ThisSpectrum[PeakPosition_+3]/ThisSpectrum[PeakPosition_];


	     }

	 }
       
       
       //n60, n70, n80, n90
       
       Timingn60_ = Timingn70_ = Timingn80_ = Timingn90_ = 0;
       
       std::vector<double> SortableSpec;
       SortableSpec.resize(10);
       for(int i=0; i<10; i++)
	 {
	   SortableSpec[i]=ThisSpectrum[i];
	 }
       
       std::sort(SortableSpec.begin(), SortableSpec.end());
       
       double TotalSoFar=0;
       int counter=0;
       
       for(int i=9; i>=0; i--)
	 {
	   counter++;
	   
	   TotalSoFar+=SortableSpec[i];
	   if(((TotalSoFar/TotalOverTime_) >= 0.6) && Timingn60_==0) Timingn60_ = counter;
	   if(((TotalSoFar/TotalOverTime_) >= 0.7) && Timingn70_==0) Timingn70_ = counter;
	   if(((TotalSoFar/TotalOverTime_) >= 0.8) && Timingn80_==0) Timingn80_ = counter;
	   if(((TotalSoFar/TotalOverTime_) >= 0.9) && Timingn90_==0) Timingn90_ = counter;
	 }		
       
       TimingBX0_=ThisSpectrum[0];
       TimingBX1_=ThisSpectrum[1];
       TimingBX2_=ThisSpectrum[2];
       TimingBX3_=ThisSpectrum[3];
       TimingBX4_=ThisSpectrum[4];
       TimingBX5_=ThisSpectrum[5];
       TimingBX6_=ThisSpectrum[6];
       TimingBX7_=ThisSpectrum[7];
       TimingBX8_=ThisSpectrum[8];	
       TimingBX9_=ThisSpectrum[9]; 
  
       std::cout<<"DEBUG: Made it here"<<std::endl;
       if(WriteHistos_)
	 {
	   std::stringstream HistName;
	   HistName.str("");
	   HistName<< "TimingPlotAll"<<iEvent.id().event();
	   TH1D* TheHist= fs->make<TH1D>(HistName.str().c_str(),HistName.str().c_str(),10,0,10);
	   for(int j=0; j!=10; j++)
	     {
	       TheHist->Fill(j,ThisSpectrum[j]);
	     }
	 }

     }







       
   if(IncludeDigisOld_)
     {
 
       Handle<HBHEDigiCollection > pIn;
       iEvent.getByLabel(DigisTag_,pIn);


       float ThisSpectrum[10];
   

       
       std::vector<HBHEDataFrame> MyDataFrameVector;
       
       MyDataFrameVector.insert(MyDataFrameVector.end(),pIn->begin(),pIn->end());
       sort(MyDataFrameVector.begin(),MyDataFrameVector.end(),compare_df());

       double ThisEnergy=0;
       int topcount=std::max(DigiCount_,(int)MyDataFrameVector.size());
       int count=0;

       for(int k=0; k<10; k++)
	 {
	   ThisSpectrum[k]=0;
	 }
       
       
       int FirstiEta, FirstiPhi;
       bool FirstTower=true;

       for(HBHEDigiCollection::const_iterator it = MyDataFrameVector.begin(); (it!=MyDataFrameVector.end())&&(count!=1); it++)
	 {
	   double FrameEnergy=0;
	   if(FirstTower)
	     {	   
	       FirstiEta=it->id().ieta();
	       FirstiPhi=it->id().iphi();
	       FirstTower=false;
	     }

	   if((abs(it->id().iphi()-FirstiPhi)<2)&&(abs(it->id().ieta())<16))
	     {
	       for(int j=0; j<10; j++)
		 FrameEnergy+=it->sample(j).nominal_fC();
	  
	       if(FrameEnergy>30)
		 {
		   /*
		   if(WriteHistos_)
		     {
		       std::stringstream HistName;
		       HistName.str("");
		       HistName<< "TimingPlotAll"<<iEvent.id().event()<<"_"<<count;
		       TH1D* TheHist= fs->make<TH1D>(HistName.str().c_str(),HistName.str().c_str(),10,0,10);
		       for(int j=0; j!=10; j++)
			 {
			   TheHist->Fill(j,it->sample(j).nominal_fC());
			 }
		     }
		   */
		   count++;
		   ThisEnergy+=FrameEnergy;
		   for(int j=0; j<10; j++)
		     if(it->sample(j).nominal_fC()>5) ThisSpectrum[j]+=(it->sample(j).nominal_fC());


		   
	     
		 }
	     }
	 }
	      
       TimingNoOfChannels_=count;
       TimingFirstBin_=ThisSpectrum[0];
       TimingFirst2Bins_=ThisSpectrum[0]+ThisSpectrum[1];
       TimingLastBin_=ThisSpectrum[9];
       TimingLast2Bins_=ThisSpectrum[8]+ThisSpectrum[9];
       
       int TopPosition=9;
       double TotalOverTime=0;

       
       std::stringstream HistName;
       HistName.str("");
       HistName<< "TimingPlotAll"<<iEvent.id().event();
       TH1D * hist1 = new TH1D(HistName.str().c_str(),HistName.str().c_str(),10,0,10);
       for(int i=9; i>=0; i--)
	 {
	   hist1->Fill(i,ThisSpectrum[i]);
	   TotalOverTime+=ThisSpectrum[i];
	   if(ThisSpectrum[i]>ThisSpectrum[TopPosition])
	     TopPosition=i;
	       
	 }
   
       hist1->Fit("expo","WWQ","",TopPosition,10);
       TF1 * Fit = hist1->GetFunction("expo");
       TimingExpSlope_=Fit->GetParameter("Slope");
       TimingExpConst_=Fit->GetParameter("Constant");
       TimingExpChiSq_=Fit->GetChisquare();
       

       if(WriteHistos_)
	 {
	   TH1D* FileHist= fs->make<TH1D>(*hist1);
	 }

       delete hist1;
       

       TimingEnergyBeforePorch_=0;
       for (int j=0; j!=std::max(TopPosition-1,0); j++)
	 {
	   TimingEnergyBeforePorch_+=ThisSpectrum[j];
	 }
       TimingEnergyBeforePeak_=TimingEnergyBeforePorch_+ThisSpectrum[TopPosition-1];

       //Fraction left and right of peak
       
       TimingFracInLeader_=ThisSpectrum[TopPosition]/TotalOverTime;
       
       TimingLeftPeak_=TimingRightPeak_=0;
       
       if(ThisSpectrum[TopPosition]!=0)
	 {
	   if(TopPosition!=0)
	     TimingLeftPeak_=ThisSpectrum[TopPosition-1]/ThisSpectrum[TopPosition];
	   
	   if(TopPosition!=9)
	     TimingRightPeak_=ThisSpectrum[TopPosition+1]/ThisSpectrum[TopPosition];

	   if((TopPosition!=9) && (TopPosition!=8) && (TopPosition!=7) && (TopPosition!=1))
	     TimingFracInCentralFour_=(ThisSpectrum[TopPosition]+ThisSpectrum[TopPosition-1]+ThisSpectrum[TopPosition+1]+ThisSpectrum[TopPosition+2])/TotalOverTime;

	   if(TopPosition!=8)
	     {
	       TimingFracRightNextRight_=ThisSpectrum[TopPosition+2]/ThisSpectrum[TopPosition+1];
	       TimingFracPeakNextRight_=ThisSpectrum[TopPosition+2]/ThisSpectrum[TopPosition];
	     }
	 }
       
       
       //n60, n70, n80, n90
       
       Timingn60_ = Timingn70_ = Timingn80_ = Timingn90_ = 0;
       
       std::vector<double> SortableSpec;
       SortableSpec.resize(10);
       for(int i=0; i<10; i++)
	 {
	   SortableSpec[i]=ThisSpectrum[i];
	 }
       
       std::sort(SortableSpec.begin(), SortableSpec.end());
       
       double TotalSoFar=0;
       int counter=0;
       
       for(int i=9; i>=0; i--)
	 {
	   counter++;
	   
	   TotalSoFar+=SortableSpec[i];
	   if(((TotalSoFar/TotalOverTime) >= 0.6) && Timingn60_==0) Timingn60_ = counter;
	   if(((TotalSoFar/TotalOverTime) >= 0.7) && Timingn70_==0) Timingn70_ = counter;
	   if(((TotalSoFar/TotalOverTime) >= 0.8) && Timingn80_==0) Timingn80_ = counter;
	   if(((TotalSoFar/TotalOverTime) >= 0.9) && Timingn90_==0) Timingn90_ = counter;
	 }		
       
       TimingBX0_=ThisSpectrum[0];
       TimingBX1_=ThisSpectrum[1];
       TimingBX2_=ThisSpectrum[2];
       TimingBX3_=ThisSpectrum[3];
       TimingBX4_=ThisSpectrum[4];
       TimingBX5_=ThisSpectrum[5];
       TimingBX6_=ThisSpectrum[6];
       TimingBX7_=ThisSpectrum[7];
       TimingBX8_=ThisSpectrum[8];	
       TimingBX9_=ThisSpectrum[9]; 
       TimingTotal_=TotalOverTime;

  
 

       
     }

   
   if(IncludeHPDVeto_)
     {




     }



   //
   //
   //  Calo Tower Information
   //
   //


   if(IncludeCaloTowers_)
     {

       Handle<CaloTowerCollection> MyCaloTowers;
       iEvent.getByLabel(CaloTowerTag_,MyCaloTowers);

       std::vector<CaloTower> MyCaloVector;
       
       MyCaloVector.insert(MyCaloVector.end(),MyCaloTowers->begin(),MyCaloTowers->end());
       
       sort(MyCaloVector.begin(),MyCaloVector.end(),compare_ct());
       
       int Count=0;
       double FirstiPhi=0.;
       double FirstiEta=0.;
       
       bool StillCheckingForLeaders=true;
       bool StillCheckingForLeaders2=true;
       
       NoLeaders_=0;
       NoLeaders2_=0;
       NOverThresh5_=0;
       NOverThresh10_=0;
       NOverThresh15_=0;
       NOverThresh20_=0;
       NOverThresh25_=0;
       NOverThresh30_=0;
       
       for(std::vector<CaloTower>::const_iterator it = MyCaloVector.begin(); it!=MyCaloVector.end();it++)
	 {
	   Count++;
	   if(Count==1)
	     {
	       CTMaxEnergy_=it->hadEnergy();
	       CTMaxEt_=it->hadEt();
	       CTMaxiEta_=it->id().ieta();
	       CTMaxiPhi_=it->id().iphi();
	       CTMaxEta_=it->eta();
	       CTMaxPhi_=it->phi();
	       CTMaxZSide_=it->id().zside();
	       CTMaxEnergyHad_=it->hadEnergy();
	       CTMaxEtHad_=it->hadEt();
	       CTMaxEnergyEm_=it->emEnergy();
	       CTMaxEtEm_=it->emEt();
	       FirstiEta=it->ieta();
	       FirstiPhi=it->iphi();
	       
	     }



	   // 1 tower leaders
    
	   if(StillCheckingForLeaders)
	     {	
	       if(FirstiPhi==1)
		 {
		   if(((it->ieta()==FirstiEta)||(it->ieta()==FirstiEta+1)||(it->ieta()==FirstiEta-1))&&((it->iphi()==1)||(it->iphi()==2)||(it->iphi()==72)))
		     {
		       NoLeaders_++;
		     }
		   else
		     {
		       StillCheckingForLeaders=false;
		     }	    
		 }
	       else if(FirstiPhi==72)
		 {
		   if(((it->ieta()==FirstiEta)||(it->ieta()==FirstiEta+1)||(it->ieta()==FirstiEta-1))&&((it->iphi()==1)||(it->iphi()==71)||(it->iphi()==72)))
		     {
		       NoLeaders_++;
		     }
		   else
		     {	
		       StillCheckingForLeaders=false;
		     }	    
		 }	   		
	       else 
		 {
		   if(((it->ieta()==FirstiEta)||(it->ieta()==FirstiEta+1)||(it->ieta()==FirstiEta-1))&&((it->iphi()==FirstiPhi)||(it->iphi()==FirstiPhi+1)||(it->iphi()==FirstiPhi-1)))
		     {
		       NoLeaders_++;
		     }
		   else
		     {
		       StillCheckingForLeaders=false;
		     }
		 }
	     }
	   
	   


	   // 2 tower leaders
	   
	   
	   if(StillCheckingForLeaders2)
	     {	
	       if(FirstiPhi==1)
		 {
		   if(((it->ieta()==FirstiEta-2)||(it->ieta()==FirstiEta+2)||(it->ieta()==FirstiEta)||(it->ieta()==FirstiEta+1)||(it->ieta()==FirstiEta-1))
		      &&((it->iphi()==71)||(it->iphi()==3)||(it->iphi()==1)||(it->iphi()==2)||(it->iphi()==72)))
		     {
		       NoLeaders2_++;
		     }
		   else
		     {
		       StillCheckingForLeaders2=false;
		     }	    
		 }
	       else if(FirstiPhi==72)
		 {
		   if(((it->ieta()==FirstiEta-2)||(it->ieta()==FirstiEta+2)||(it->ieta()==FirstiEta)||(it->ieta()==FirstiEta+1)||(it->ieta()==FirstiEta-1))
		      &&((it->iphi()==70)||(it->iphi()==2)||(it->iphi()==1)||(it->iphi()==71)||(it->iphi()==72)))
		     {
		       NoLeaders2_++;
		     }
		   else
		     {
		       StillCheckingForLeaders2=false;
		     }	    
		 }	   		
	       else 
		 {
		   if(((it->ieta()==FirstiEta-2)||(it->ieta()==FirstiEta+2)||(it->ieta()==FirstiEta)||(it->ieta()==FirstiEta+1)||(it->ieta()==FirstiEta-1))
		      &&((it->iphi()==FirstiPhi-2)||(it->iphi()==FirstiPhi+2)||(it->iphi()==FirstiPhi)||(it->iphi()==FirstiPhi+1)||(it->iphi()==FirstiPhi-1)))
		     {
		       NoLeaders2_++;
		     }
		   else
		     {
		       StillCheckingForLeaders2=false;
		     }
		 }
	     }
	 
	   
	   // N Threshold method
	    
	   if((it->iphi()==FirstiPhi)&&(it->energy() > 5)) NOverThresh5_++;
	   if((it->iphi()==FirstiPhi)&&(it->energy() > 10)) NOverThresh10_++;
	   if((it->iphi()==FirstiPhi)&&(it->energy() > 15)) NOverThresh15_++;
	   if((it->iphi()==FirstiPhi)&&(it->energy() > 20)) NOverThresh20_++;
	   if((it->iphi()==FirstiPhi)&&(it->energy() > 25)) NOverThresh25_++;
	   if((it->iphi()==FirstiPhi)&&(it->energy() > 30)) NOverThresh30_++;
	   
	   
	   
	   
	 }
       
       
       

     }


   if(IncludeMuons_)
     {
       NoOfMuons_=0;
       Handle<reco::MuonCollection> pMuon;
       iEvent.getByLabel(MuonTag_,pMuon);
       for(reco::MuonCollection::const_iterator it =pMuon->begin(); it!=pMuon->end(); it++)
	 NoOfMuons_++;
     }

   EventTree->Fill();

}


// ------------ method called once each job just before starting event loop  ------------
void 
GlobalRunAnalyser::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
void 
GlobalRunAnalyser::endJob() {
}

//define this as a plug-in
DEFINE_FWK_MODULE(GlobalRunAnalyser);
