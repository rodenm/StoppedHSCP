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
// $Id: StoppedHSCPTreeProducer.cc,v 1.4 2009/07/08 10:09:48 jbrooke Exp $
//
//


// system include files
#include <memory>

// framework
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "FWCore/MessageLogger/interface/MessageLogger.h"

// data formats
#include "DataFormats/L1Trigger/interface/L1JetParticleFwd.h"
#include "DataFormats/L1Trigger/interface/L1JetParticle.h"

#include "SimDataFormats/GeneratorProducts/interface/HepMCProduct.h"

#include "DataFormats/JetReco/interface/CaloJetCollection.h"

#include "DataFormats/MuonReco/interface/MuonFwd.h"
#include "DataFormats/MuonReco/interface/Muon.h"

#include "DataFormats/CaloTowers/interface/CaloTowerCollection.h"

#include "DataFormats/METReco/interface/HcalNoiseHPD.h"
#include "DataFormats/METReco/interface/HcalNoiseRBX.h"
#include "DataFormats/METReco/interface/HcalNoiseSummary.h"

//#include "DataFormats/HcalRecHit/interface/HcalRecHitCollections.h"
//#include "DataFormats/HcalDetId/interface/HcalDetId.h"

#include "DataFormats/HcalDigi/interface/HBHEDataFrame.h"
#include "DataFormats/HcalDigi/interface/HcalDigiCollections.h"

// ROOT output stuff
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "PhysicsTools/UtilAlgos/interface/TFileService.h"
#include "TH1.h"
#include "TTree.h"
#include "TF1.h"

// TTree definition
#include "StoppedHSCP/Analysis/interface/StoppedHSCPEvent.h"


//
// class decleration
//

class StoppedHSCPTreeProducer : public edm::EDAnalyzer {
   public:
      explicit StoppedHSCPTreeProducer(const edm::ParameterSet&);
      ~StoppedHSCPTreeProducer();


   private:
      virtual void beginJob(const edm::EventSetup&) ;
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

  // output file
  edm::Service<TFileService> fs;

  // tree
  TTree * tree;
 
  // EDM input tags
  std::string l1JetsTag_;
  edm::InputTag hltTag_;
  edm::InputTag mcTag_;
  edm::InputTag jetTag_;
  edm::InputTag muonTag_;
  edm::InputTag caloTowerTag_;
  edm::InputTag hcalNoiseTag_;
  edm::InputTag rbxTag_;
  edm::InputTag hpdTag_;
  edm::InputTag hcalDigiTag_;

  // cuts
  double  towerMinEnergy_;
  double  towerMaxEta_;
  double  jetMinEnergy_;
  double  jetMaxEta_;

  // output control
  bool writeHistos_;

  // debug stuff
  bool l1JetsMissing_;
  bool hltMissing_;
  bool mcMissing_;
  bool jetsMissing_;
  bool muonsMissing_;
  bool towersMissing_;
  bool noiseSumMissing_;
  bool rbxsMissing_;
  bool hpdsMissing_;
  bool digisMissing_;

  // the current event
  StoppedHSCPEvent* event_;

};



StoppedHSCPTreeProducer::StoppedHSCPTreeProducer(const edm::ParameterSet& iConfig):
//   IncludeJetDetails_(iConfig.getUntrackedParameter("IncludeJetDetails",true)),
//   IncludeJets_(iConfig.getUntrackedParameter("IncludeJets",true)),
//   IncludeCaloTowers_(iConfig.getUntrackedParameter("IncludeCaloTowers",true)),
//   IncludeMC_(iConfig.getUntrackedParameter("IncludeMC",false)),
//   IncludeDigis_(iConfig.getUntrackedParameter("IncludeDigis",false)),
//   IncludeMuons_(iConfig.getUntrackedParameter("IncludeMuons",false)),
//   IncludeDigisOld_(iConfig.getUntrackedParameter("IncludeDigisOld",false)),
  l1JetsTag_(iConfig.getUntrackedParameter("l1JetsTag",std::string("l1extra"))),
  hltTag_(iConfig.getUntrackedParameter("hltTag",edm::InputTag("HLT"))),
  mcTag_(iConfig.getUntrackedParameter("mcTag",edm::InputTag("generator"))),
  jetTag_(iConfig.getUntrackedParameter("jetTag",edm::InputTag("sisCone5CaloJets"))),
  muonTag_(iConfig.getUntrackedParameter("muonTag",edm::InputTag("muons"))),
  caloTowerTag_(iConfig.getUntrackedParameter("caloTowerTag",edm::InputTag("towerMaker"))),
  hcalNoiseTag_(iConfig.getUntrackedParameter("rbxTag",edm::InputTag("hcalnoise"))),
  rbxTag_(iConfig.getUntrackedParameter("rbxTag",edm::InputTag("hcalnoise"))),
  hpdTag_(iConfig.getUntrackedParameter("hpdTag",edm::InputTag("hcalnoise"))),
  hcalDigiTag_(iConfig.getUntrackedParameter("hcalDigiTag",edm::InputTag(""))),
  towerMinEnergy_(iConfig.getUntrackedParameter("towerMinEnergy", 1.)),
  towerMaxEta_(iConfig.getUntrackedParameter("towerMaxEta", 3.)),
  jetMinEnergy_(iConfig.getUntrackedParameter("jetMinEnergy", 1.)),
  jetMaxEta_(iConfig.getUntrackedParameter("jetMaxEta", 3.)),
  writeHistos_(iConfig.getUntrackedParameter("writeHistos",false)),
  l1JetsMissing_(false),
  hltMissing_(false),
  mcMissing_(false),
  jetsMissing_(false),
  muonsMissing_(false),
  towersMissing_(false),
  noiseSumMissing_(false),
  rbxsMissing_(false),
  hpdsMissing_(false),
  event_(0)
{

  // set up output
  tree=fs->make<TTree>("StoppedHSCPTree", "");
  tree->Branch("events", "StoppedHSCPEvent", &event_, 64000, 1);
  
}


StoppedHSCPTreeProducer::~StoppedHSCPTreeProducer()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called to for each event  ------------
void
StoppedHSCPTreeProducer::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   using namespace reco;

   // event headers
   event_ = new StoppedHSCPEvent();
   event_->setEventInfo(iEvent.id().event(),
			0,
			0,
			iEvent.luminosityBlock(),
			iEvent.id().run(),
			0,
			iEvent.time().value());


   // trigger info
   edm::Handle<l1extra::L1JetParticleCollection> l1Jets;
   iEvent.getByLabel(l1JetsTag_,l1Jets);

   if (l1Jets.isValid()) {
 
   }
   else {
   }

   // MC
   edm::Handle<edm::HepMCProduct> mcHandle;
   iEvent.getByLabel(mcTag_,mcHandle);

   if (mcHandle.isValid()) {
     
     const edm::HepMCProduct *mcProd = mcHandle.product();
     const HepMC::GenEvent *evt = mcProd->GetEvent();
     
     shscp::MC mcEvt;
     
     for(HepMC::GenEvent::vertex_const_iterator pitr = evt->vertices_begin(); pitr!= evt->vertices_end(); ++pitr) {
       
       if((*pitr)->barcode()==-1)  {
	 
	 mcEvt.vtxX = (*pitr)->point3d().x();
	 mcEvt.vtxY = (*pitr)->point3d().y();
	 mcEvt.vtxZ = (*pitr)->point3d().z();
	 mcEvt.vtxT = (*pitr)->position().t();
	 
	 for(HepMC::GenVertex::particles_out_const_iterator part = (*pitr)->particles_out_const_begin(); part!=(*pitr)->particles_out_const_end(); ++part) {
	   //	std::cout << (*part)->pdg_id()<<std::endl;
	   if((*part)->pdg_id()>=1000000)
	     {
	       mcEvt.rHadPdgId = (*part)->pdg_id();
	       mcEvt.rHadPx  = (*part)->momentum().x();
	       mcEvt.rHadPy  = (*part)->momentum().y();
	       mcEvt.rHadPz  = (*part)->momentum().z();
	       mcEvt.rHadPt  = (*part)->momentum().perp();
	       mcEvt.rHadE   = (*part)->momentum().e();
	     }
	 }
       }
     }
     
     event_->setMC(mcEvt);
     
   }
   else {
     if (!mcMissing_) edm::LogWarning("MissingProduct") << "MC information not found.  Branch will not be filled" << std::endl;
     mcMissing_ = true;
   }

   // Jets
   edm::Handle<CaloJetCollection> caloJets;
   iEvent.getByLabel(jetTag_, caloJets);

   std::vector<std::vector<HcalDetId> > hcalDetIdsInJets;
       
   if (caloJets.isValid()) {
     for(CaloJetCollection::const_iterator it=caloJets->begin(); 
	 it!=caloJets->end() && event_->nJet() < StoppedHSCPEvent::MAX_N_JETS;
	 ++it) {
       if (it->energy() > jetMinEnergy_ &&
	   fabs(it->eta()) < jetMaxEta_) {

	 // store jet in TTree
	 shscp::Jet jet;
	 jet.et = it->et();
	 jet.eta = it->eta();
	 jet.phi = it->phi();
	 jet.e = it->energy();
	 jet.eEm = it->emEnergyInEB();
	 jet.eHad = it->hadEnergyInHB();
	 jet.eMaxEcalTow = it->maxEInEmTowers();
	 jet.eMaxHcalTow = it->maxEInHadTowers();
	 jet.n60 = it->n60();
	 jet.n90 = it->n90();
	 event_->addJet(jet);

	 hcalDetIdsInJets.push_back(std::vector<HcalDetId>(0));

	 // get constituents for later use
	 std::vector<CaloTowerPtr> CaloTowers = it->getCaloConstituents();
	 for(std::vector<CaloTowerPtr>::const_iterator itCalo = CaloTowers.begin(); itCalo!=CaloTowers.end(); itCalo++) {
	   const std::vector<DetId>& CaloConst = (*itCalo)->constituents();
	   for(std::vector<DetId>::const_iterator itConst = CaloConst.begin(); itConst!=CaloConst.end(); itConst++) {
	     if(itConst->det()==4) {
	       HcalDetId id = HcalDetId(*itConst);
	       (hcalDetIdsInJets.end()--)->push_back(id);
	     }
	   }
	 }
       }       
     }  
   }
   else {
     if (!jetsMissing_) edm::LogWarning("MissingProduct") << "CaloJets not found.  Branch will not be filled" << std::endl;
     jetsMissing_ = true;
   }

   // Muons
   edm::Handle<reco::MuonCollection> muons;
   iEvent.getByLabel(muonTag_,muons);

   if (muons.isValid()) {
     for(reco::MuonCollection::const_iterator it =muons->begin();
	 it!=muons->end() && event_->nMuon() < StoppedHSCPEvent::MAX_N_MUONS;
	 it++) {
       shscp::Muon mu;
       mu.pt = it->pt();
       mu.eta = it->eta();
       mu.phi = it->phi();
       mu.hcalEta = 0.;  // TODO extrapolate GlobalMuon track to HCAL surface and store position!
       mu.hcalPhi = 0.;
       event_->addMuon(mu);
     }
   }
   else {
     if (!muonsMissing_) edm::LogWarning("MissingProduct") << "Muons not found.  Branch will not be filled" << std::endl;
     muonsMissing_ = true;
   }

   // towers
   edm::Handle<CaloTowerCollection> caloTowers;
   iEvent.getByLabel(caloTowerTag_,caloTowers);
   std::vector<CaloTower> caloTowVec;
      
   if (caloTowers.isValid()) {

     sort(caloTowVec.begin(), caloTowVec.end(), compare_ct());
     
     for(std::vector<CaloTower>::const_iterator it = caloTowVec.begin(); 
	 it!=caloTowVec.end() && event_->nTow() < StoppedHSCPEvent::MAX_N_TOWERS;
	 ++it) {
       if (it->energy() > towerMinEnergy_ &&
	   fabs(it->eta()) < towerMaxEta_) {
	 shscp::Tower tow;
	 tow.e = it->energy();
	 tow.et = it->et();
	 tow.eta = it->eta();
	 tow.phi = it->phi();
	 tow.ieta = it->ieta();
	 tow.iphi = it->iphi();
	 tow.eHad = it->hadEnergy();
	 tow.etHad = it->hadEt();
	 tow.eEm = it->emEnergy();
	 tow.etEm = it->emEt();
	 event_->addTower(tow);
       }
     }
   }
   else {
     if (!towersMissing_) edm::LogWarning("MissingProduct") << "CaloTowers not found.  Branch will not be filled" << std::endl;
     towersMissing_ = true;
   }

   // RBXs
   edm::Handle<HcalNoiseRBXCollection> rbxs;
   iEvent.getByLabel(rbxTag_,rbxs);

   if (rbxs.isValid()) {
     for(HcalNoiseRBXCollection::const_iterator it = rbxs->begin(); 
	 it!=rbxs->end() && event_->nRbx() < StoppedHSCPEvent::MAX_N_RBXS;
	 ++it) {
       shscp::RBX rbx;
       rbx.id = it->idnumber();
       rbx.totalZeros = it->totalZeros();
       rbx.maxZeros = it->maxZeros();
       event_->addRBX(rbx);
     }
   }
   else {
     if (!rbxsMissing_) edm::LogWarning("MissingProduct") << "RBXs not found.  Branch will not be filled" << std::endl;
     rbxsMissing_ = true;
   }

   // HPDs
   edm::Handle<HcalNoiseHPDCollection> hpds;
   iEvent.getByLabel(hpdTag_,hpds);
   if (hpds.isValid()) {
     
   }
   else {
     if (!hpdsMissing_) edm::LogWarning("MissingProduct") << "HPDs not found.  Branch will not be filled" << std::endl;
     hpdsMissing_ = true;
   }


   // digis
   if (""!=hcalDigiTag_.label()) {

     edm::Handle<HBHEDigiCollection > digis;
     iEvent.getByLabel(hcalDigiTag_,digis);

     std::vector<std::vector<HcalDetId> >::const_iterator j;
     std::vector<HcalDetId>::const_iterator det;

     for (j=hcalDetIdsInJets.begin(); j!=hcalDetIdsInJets.end(); ++j) {
       for (det=j->begin(); det!=j->end(); ++det) {

	 for(HBHEDigiCollection::const_iterator it=digis->begin();it!=digis->end(); it++) {
	   
// 	   for(int i=0; i!=HBDigisInLeadingCenJet.size(); i++)
// 	     {
// 	       if(itDigi->id()==HBDigisInLeadingCenJet.at(i))
// 		 {
// 		   std::cout<<"Found HCal Digi : "<<itDigi->id().ieta() << " " <<itDigi->id().iphi()<<std::endl;
// 		   for(int j=0; j<10; j++)
// 		     {
// 		       ThisEnergy+=itDigi->sample(j).nominal_fC();
// 		     }
// 		   //  if(ThisEnergy>10)
// 		     {
// 		       for(int j=0; j<10; j++)
// 			 {
		       	  
// 			   ThisSpectrum[j]+=itDigi->sample(j).nominal_fC();
			  
		     
// 			 }
// 		     }
// 		   JetDigiCount++;
// 		 }
// 	     }


 	 }

       }
     }

   }



//        std::cout<<"No of digis with energy : " << HBDigisInLeadingCenJet.size()<<std::endl;
//        for(HBHEDigiCollection::const_iterator itDigi=pDigi->begin();itDigi!=pDigi->end(); itDigi++)
// 	 {
	   
// 	   for(int i=0; i!=HBDigisInLeadingCenJet.size(); i++)
// 	     {
// 	       if(itDigi->id()==HBDigisInLeadingCenJet.at(i))
// 		 {
// 		   std::cout<<"Found HCal Digi : "<<itDigi->id().ieta() << " " <<itDigi->id().iphi()<<std::endl;
// 		   for(int j=0; j<10; j++)
// 		     {
// 		       ThisEnergy+=itDigi->sample(j).nominal_fC();
// 		     }
// 		   //  if(ThisEnergy>10)
// 		     {
// 		       for(int j=0; j<10; j++)
// 			 {
		       	  
// 			   ThisSpectrum[j]+=itDigi->sample(j).nominal_fC();
			  
		     
// 			 }
// 		     }
// 		   JetDigiCount++;
// 		 }
// 	     }


// 	 }

//        std::cout<<"DEBUG Made it here -1"<<std::endl;
 

//        TotalOverTime_=ThisEnergy;
//        PeakPosition_=0;
//        for(int i=0; i<10; i++)
// 	 {
// 	   if(ThisSpectrum[i]>ThisSpectrum[PeakPosition_])
// 	     PeakPosition_=i;
	       
// 	 }
   


//        //Fraction left and right of peak
       
//        TimingFracInLeader_=ThisSpectrum[PeakPosition_]/TotalOverTime_;
       
//        TimingLeftPeak_=TimingRightPeak_=0;
//        TimingRightNextRight_= TimingPeakNextRight_=0;
//        TimingRightNextNextRight_=TimingPeakNextNextRight_=0;

//        if(ThisSpectrum[PeakPosition_]!=0)
// 	 {
// 	   if(PeakPosition_!=0)
// 	     TimingLeftPeak_=ThisSpectrum[PeakPosition_-1]/ThisSpectrum[PeakPosition_];
	   
// 	   if(PeakPosition_!=9)
// 	     TimingRightPeak_=ThisSpectrum[PeakPosition_+1]/ThisSpectrum[PeakPosition_];

// 	   if((PeakPosition_!=9) && (PeakPosition_!=8) && (PeakPosition_!=7) && (PeakPosition_!=1))
// 	     TimingFracInCentralFour_=(ThisSpectrum[PeakPosition_]+ThisSpectrum[PeakPosition_-1]+ThisSpectrum[PeakPosition_+1]+ThisSpectrum[PeakPosition_+2])/TotalOverTime_;

// 	   if((PeakPosition_!=8) && (PeakPosition_!=9))
// 	     {
// 	       TimingRightNextRight_=ThisSpectrum[PeakPosition_+2]/ThisSpectrum[PeakPosition_+1];
// 	       TimingPeakNextRight_=ThisSpectrum[PeakPosition_+2]/ThisSpectrum[PeakPosition_];
// 	     }
	   
// 	   if((PeakPosition_!=7)&&(PeakPosition_!=8)&&(PeakPosition_!=9))
// 	     {
// 	       TimingRightNextNextRight_=ThisSpectrum[PeakPosition_+3]/ThisSpectrum[PeakPosition_+2];
// 	       TimingPeakNextNextRight_=ThisSpectrum[PeakPosition_+3]/ThisSpectrum[PeakPosition_];


// 	     }

// 	 }
       
       
//        //n60, n70, n80, n90
       
//        Timingn60_ = Timingn70_ = Timingn80_ = Timingn90_ = 0;
       
//        std::vector<double> SortableSpec;
//        SortableSpec.resize(10);
//        for(int i=0; i<10; i++)
// 	 {
// 	   SortableSpec[i]=ThisSpectrum[i];
// 	 }
       
//        std::sort(SortableSpec.begin(), SortableSpec.end());
       
//        double TotalSoFar=0;
//        int counter=0;
       
//        for(int i=9; i>=0; i--)
// 	 {
// 	   counter++;
	   
// 	   TotalSoFar+=SortableSpec[i];
// 	   if(((TotalSoFar/TotalOverTime_) >= 0.6) && Timingn60_==0) Timingn60_ = counter;
// 	   if(((TotalSoFar/TotalOverTime_) >= 0.7) && Timingn70_==0) Timingn70_ = counter;
// 	   if(((TotalSoFar/TotalOverTime_) >= 0.8) && Timingn80_==0) Timingn80_ = counter;
// 	   if(((TotalSoFar/TotalOverTime_) >= 0.9) && Timingn90_==0) Timingn90_ = counter;
// 	 }		
       
//        TimingBX0_=ThisSpectrum[0];
//        TimingBX1_=ThisSpectrum[1];
//        TimingBX2_=ThisSpectrum[2];
//        TimingBX3_=ThisSpectrum[3];
//        TimingBX4_=ThisSpectrum[4];
//        TimingBX5_=ThisSpectrum[5];
//        TimingBX6_=ThisSpectrum[6];
//        TimingBX7_=ThisSpectrum[7];
//        TimingBX8_=ThisSpectrum[8];	
//        TimingBX9_=ThisSpectrum[9]; 
  
//        std::cout<<"DEBUG: Made it here"<<std::endl;
//        if(WriteHistos_)
// 	 {
// 	   std::stringstream HistName;
// 	   HistName.str("");
// 	   HistName<< "TimingPlotAll"<<iEvent.id().event();
// 	   TH1D* TheHist= fs->make<TH1D>(HistName.str().c_str(),HistName.str().c_str(),10,0,10);
// 	   for(int j=0; j!=10; j++)
// 	     {
// 	       TheHist->Fill(j,ThisSpectrum[j]);
// 	     }
// 	 }

//      }







       


//    //
//    //
//    //  Calo Tower Information
//    //
//    //


//    if(IncludeCaloTowers_)
//      {

//        Handle<CaloTowerCollection> MyCaloTowers;
//        iEvent.getByLabel(CaloTowerTag_,MyCaloTowers);

//        std::vector<CaloTower> MyCaloVector;
       
//        MyCaloVector.insert(MyCaloVector.end(),MyCaloTowers->begin(),MyCaloTowers->end());
       
//        sort(MyCaloVector.begin(),MyCaloVector.end(),compare_ct());
       
//        int Count=0;
//        double FirstiPhi=0.;
//        double FirstiEta=0.;
       
//        bool StillCheckingForLeaders=true;
//        bool StillCheckingForLeaders2=true;
       
//        NoLeaders_=0;
//        NoLeaders2_=0;
//        NOverThresh5_=0;
//        NOverThresh10_=0;
//        NOverThresh15_=0;
//        NOverThresh20_=0;
//        NOverThresh25_=0;
//        NOverThresh30_=0;
       
//        for(std::vector<CaloTower>::const_iterator it = MyCaloVector.begin(); it!=MyCaloVector.end();it++)
// 	 {
// 	   Count++;
// 	   if(Count==1)
// 	     {
// 	       CTMaxEnergy_=it->hadEnergy();
// 	       CTMaxEt_=it->hadEt();
// 	       CTMaxiEta_=it->id().ieta();
// 	       CTMaxiPhi_=it->id().iphi();
// 	       CTMaxEta_=it->eta();
// 	       CTMaxPhi_=it->phi();
// 	       CTMaxZSide_=it->id().zside();
// 	       CTMaxEnergyHad_=it->hadEnergy();
// 	       CTMaxEtHad_=it->hadEt();
// 	       CTMaxEnergyEm_=it->emEnergy();
// 	       CTMaxEtEm_=it->emEt();
// 	       FirstiEta=it->ieta();
// 	       FirstiPhi=it->iphi();
	       
// 	     }



// 	   // 1 tower leaders
    
// 	   if(StillCheckingForLeaders)
// 	     {	
// 	       if(FirstiPhi==1)
// 		 {
// 		   if(((it->ieta()==FirstiEta)||(it->ieta()==FirstiEta+1)||(it->ieta()==FirstiEta-1))&&((it->iphi()==1)||(it->iphi()==2)||(it->iphi()==72)))
// 		     {
// 		       NoLeaders_++;
// 		     }
// 		   else
// 		     {
// 		       StillCheckingForLeaders=false;
// 		     }	    
// 		 }
// 	       else if(FirstiPhi==72)
// 		 {
// 		   if(((it->ieta()==FirstiEta)||(it->ieta()==FirstiEta+1)||(it->ieta()==FirstiEta-1))&&((it->iphi()==1)||(it->iphi()==71)||(it->iphi()==72)))
// 		     {
// 		       NoLeaders_++;
// 		     }
// 		   else
// 		     {	
// 		       StillCheckingForLeaders=false;
// 		     }	    
// 		 }	   		
// 	       else 
// 		 {
// 		   if(((it->ieta()==FirstiEta)||(it->ieta()==FirstiEta+1)||(it->ieta()==FirstiEta-1))&&((it->iphi()==FirstiPhi)||(it->iphi()==FirstiPhi+1)||(it->iphi()==FirstiPhi-1)))
// 		     {
// 		       NoLeaders_++;
// 		     }
// 		   else
// 		     {
// 		       StillCheckingForLeaders=false;
// 		     }
// 		 }
// 	     }
	   
	   


// 	   // 2 tower leaders
	   
	   
// 	   if(StillCheckingForLeaders2)
// 	     {	
// 	       if(FirstiPhi==1)
// 		 {
// 		   if(((it->ieta()==FirstiEta-2)||(it->ieta()==FirstiEta+2)||(it->ieta()==FirstiEta)||(it->ieta()==FirstiEta+1)||(it->ieta()==FirstiEta-1))
// 		      &&((it->iphi()==71)||(it->iphi()==3)||(it->iphi()==1)||(it->iphi()==2)||(it->iphi()==72)))
// 		     {
// 		       NoLeaders2_++;
// 		     }
// 		   else
// 		     {
// 		       StillCheckingForLeaders2=false;
// 		     }	    
// 		 }
// 	       else if(FirstiPhi==72)
// 		 {
// 		   if(((it->ieta()==FirstiEta-2)||(it->ieta()==FirstiEta+2)||(it->ieta()==FirstiEta)||(it->ieta()==FirstiEta+1)||(it->ieta()==FirstiEta-1))
// 		      &&((it->iphi()==70)||(it->iphi()==2)||(it->iphi()==1)||(it->iphi()==71)||(it->iphi()==72)))
// 		     {
// 		       NoLeaders2_++;
// 		     }
// 		   else
// 		     {
// 		       StillCheckingForLeaders2=false;
// 		     }	    
// 		 }	   		
// 	       else 
// 		 {
// 		   if(((it->ieta()==FirstiEta-2)||(it->ieta()==FirstiEta+2)||(it->ieta()==FirstiEta)||(it->ieta()==FirstiEta+1)||(it->ieta()==FirstiEta-1))
// 		      &&((it->iphi()==FirstiPhi-2)||(it->iphi()==FirstiPhi+2)||(it->iphi()==FirstiPhi)||(it->iphi()==FirstiPhi+1)||(it->iphi()==FirstiPhi-1)))
// 		     {
// 		       NoLeaders2_++;
// 		     }
// 		   else
// 		     {
// 		       StillCheckingForLeaders2=false;
// 		     }
// 		 }
// 	     }
	 
	   
// 	   // N Threshold method
	    
// 	   if((it->iphi()==FirstiPhi)&&(it->energy() > 5)) NOverThresh5_++;
// 	   if((it->iphi()==FirstiPhi)&&(it->energy() > 10)) NOverThresh10_++;
// 	   if((it->iphi()==FirstiPhi)&&(it->energy() > 15)) NOverThresh15_++;
// 	   if((it->iphi()==FirstiPhi)&&(it->energy() > 20)) NOverThresh20_++;
// 	   if((it->iphi()==FirstiPhi)&&(it->energy() > 25)) NOverThresh25_++;
// 	   if((it->iphi()==FirstiPhi)&&(it->energy() > 30)) NOverThresh30_++;
	   
	   
	   
	   
// 	 }
       
       
       

//      }

   tree->Fill();

   delete event_;

}


// ------------ method called once each job just before starting event loop  ------------
void 
StoppedHSCPTreeProducer::beginJob(const edm::EventSetup&)
{
}

// ------------ method called once each job just after ending the event loop  ------------
void 
StoppedHSCPTreeProducer::endJob() {
}

//define this as a plug-in
DEFINE_FWK_MODULE(StoppedHSCPTreeProducer);
