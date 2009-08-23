// -*- C++ -*-
//
// Package:    StoppedHSCP/Analysis
// Class:      StoppedHSCPTreeProducer
// 
/**\class StoppedHSCPTreeProducer StoppedHSCPTreeProducer.cc StoppedHSCP/Analysis/src/StoppedHSCPTreeProducer.cc

 Description: Produce Stopped HSCP tree

 Implementation:
     
*/
//
// Original Author:  Jim Brooke
//         Created:  
// $Id: StoppedHSCPTreeProducer.cc,v 1.7 2009/07/23 16:33:04 jbrooke Exp $
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
// class declaration
//

using namespace reco;

class StoppedHSCPTreeProducer : public edm::EDAnalyzer {
public:
  explicit StoppedHSCPTreeProducer(const edm::ParameterSet&);
  ~StoppedHSCPTreeProducer();
  
  
private:
  virtual void beginJob(const edm::EventSetup&) ;
  virtual void analyze(const edm::Event&, const edm::EventSetup&);
  virtual void endJob() ;
  
  void doEventInfo(const edm::Event&);
  void doMC(const edm::Event&);
  void doTrigger(const edm::Event&);
  void doJets(const edm::Event&);
  void doMuons(const edm::Event&);
  void doTowersAboveThreshold(const edm::Event&);
  void doTowersInJets(const edm::Event&);
  void doHcalNoise(const edm::Event&);
  void doDigisAboveThreshold(const edm::Event&);
  void doDigisInJets(const edm::Event&);

public:
  
  struct compare_l1j : public std::binary_function<l1extra::L1JetParticle, l1extra::L1JetParticle, bool> {
    bool operator()(const l1extra::L1JetParticle& x, const l1extra::L1JetParticle& y) {
      return ( x.et() > y.et() ) ;
    }
  };

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
      return ( TotalX > TotalY ) ;
    }
  };
  
  
private:
  
  // output file
  edm::Service<TFileService> fs_;
  
  // tree
  TTree * tree_;
 
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
  double towerMinEnergy_;
  double towerMaxEta_;
  double jetMinEnergy_;
  double jetMaxEta_;
  double digiMinFc_;

  // output control
  bool doMC_;
  bool doReco_;
  bool doDigis_;
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

  std::vector<CaloTowerPtr> jetTowers_;
  std::vector<unsigned> towerJets_;

  std::vector<HcalDetId> hcalDetIds_;
  std::vector<unsigned> hcalDetJets_;
};



StoppedHSCPTreeProducer::StoppedHSCPTreeProducer(const edm::ParameterSet& iConfig):
  l1JetsTag_(iConfig.getUntrackedParameter<std::string>("l1JetsTag",std::string("l1extraParticles"))),
  hltTag_(iConfig.getUntrackedParameter<edm::InputTag>("hltTag",edm::InputTag("HLT"))),
  mcTag_(iConfig.getUntrackedParameter<edm::InputTag>("mcTag",edm::InputTag("generator"))),
  jetTag_(iConfig.getUntrackedParameter<edm::InputTag>("jetTag",edm::InputTag("sisCone5CaloJets"))),
  muonTag_(iConfig.getUntrackedParameter<edm::InputTag>("muonTag",edm::InputTag("muons"))),
  caloTowerTag_(iConfig.getUntrackedParameter<edm::InputTag>("caloTowerTag",edm::InputTag("towerMaker"))),
  hcalNoiseTag_(iConfig.getUntrackedParameter<edm::InputTag>("rbxTag",edm::InputTag("hcalnoise"))),
  rbxTag_(iConfig.getUntrackedParameter<edm::InputTag>("rbxTag",edm::InputTag("hcalnoise"))),
  hpdTag_(iConfig.getUntrackedParameter<edm::InputTag>("hpdTag",edm::InputTag("hcalnoise"))),
  hcalDigiTag_(iConfig.getUntrackedParameter<edm::InputTag>("hcalDigiTag",edm::InputTag(""))),
  towerMinEnergy_(iConfig.getUntrackedParameter<double>("towerMinEnergy", 1.)),
  towerMaxEta_(iConfig.getUntrackedParameter<double>("towerMaxEta", 3.)),
  jetMinEnergy_(iConfig.getUntrackedParameter<double>("jetMinEnergy", 1.)),
  jetMaxEta_(iConfig.getUntrackedParameter<double>("jetMaxEta", 3.)),
  digiMinFc_(iConfig.getUntrackedParameter<double>("digiMinFc", 30)),
  doMC_(iConfig.getUntrackedParameter<bool>("doMC",true)),
  doReco_(iConfig.getUntrackedParameter<bool>("doReco",true)),
  doDigis_(iConfig.getUntrackedParameter<bool>("doDigis",false)),
  writeHistos_(iConfig.getUntrackedParameter<bool>("writeHistos",false)),
  l1JetsMissing_(false),
  hltMissing_(false),
  mcMissing_(false),
  jetsMissing_(false),
  muonsMissing_(false),
  towersMissing_(false),
  noiseSumMissing_(false),
  rbxsMissing_(false),
  hpdsMissing_(false),
  event_(0),
  hcalDetIds_(0),
  hcalDetJets_(0)
{

  // set up output
  tree_=fs_->make<TTree>("StoppedHSCPTree", "");
  tree_->Branch("events", "StoppedHSCPEvent", &event_, 64000, 1);
  
  // log
  std::string log;
  if (doMC_) log += " mc";
  if (doReco_) log += " reco";
  if (doDigis_) log += " digis";

  edm::LogInfo("StoppedHSCPTree") << "Going to fill " << log << std::endl;

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

  event_ = new StoppedHSCPEvent();
  
  doEventInfo(iEvent);
  doTrigger(iEvent);
  
  if (doMC_) doMC(iEvent);
  
  if (doReco_) {
    doJets(iEvent);
    doMuons(iEvent);
    doTowersAboveThreshold(iEvent);
    doHcalNoise(iEvent);
  }
  
  if (doDigis_) doDigisAboveThreshold(iEvent);
  
  tree_->Fill();
  
  delete event_;

}

void StoppedHSCPTreeProducer::doEventInfo(const edm::Event& iEvent){ 
  
  event_->setEventInfo(iEvent.id().event(),
		       0,
		       0,
		       iEvent.luminosityBlock(),
		       iEvent.id().run(),
		       0,
		       iEvent.time().value());

}
  

void StoppedHSCPTreeProducer::doTrigger(const edm::Event& iEvent) {

  double l1JetEt(0.), l1JetEta(0.), l1JetPhi(0.);
  double hltJetE(0.), hltJetEta(0.), hltJetPhi(0.);
  unsigned l1BptxPlus(0), l1BptxMinus(0);

  // get L1 jet info
  edm::Handle<l1extra::L1JetParticleCollection> l1CenJets;
  iEvent.getByLabel(l1JetsTag_, "Central", l1CenJets);
  
  edm::Handle<l1extra::L1JetParticleCollection> l1TauJets;
  iEvent.getByLabel(l1JetsTag_, "Tau", l1TauJets);
  
  std::vector<l1extra::L1JetParticle> l1jets;

  if (l1CenJets.isValid() && l1TauJets.isValid()) { 

    // merge & sort collections
    l1jets.insert(l1jets.end(), l1CenJets->begin(), l1CenJets->end());
    l1jets.insert(l1jets.end(), l1CenJets->begin(), l1CenJets->end());
    std::sort(l1jets.begin(), l1jets.end(), StoppedHSCPTreeProducer::compare_l1j());

    if (l1jets.size()!=0) {
      l1JetEt=l1jets.at(0).et();
      l1JetEta=l1jets.at(0).eta();
      l1JetPhi=l1jets.at(0).phi();
    }
    
  }
  else {
    if (!l1JetsMissing_) edm::LogWarning("MissingProduct") << "L1 information not found.  Branch will not be filled" << std::endl;
    l1JetsMissing_ = true;
  }

  // To Do - fill BPTX & HLT info

  event_->setTriggerInfo(l1JetEt,
			 l1JetEta,
			 l1JetPhi,
			 l1BptxPlus,
			 l1BptxMinus,
			 hltJetE,
			 hltJetEta,
			 hltJetPhi);

}


void StoppedHSCPTreeProducer::doMC(const edm::Event& iEvent) {

  edm::Handle<edm::HepMCProduct> mcHandle;
  iEvent.getByLabel(mcTag_,mcHandle);
  
  if (mcHandle.isValid()) {
    
    const edm::HepMCProduct *mcProd = mcHandle.product();
    const HepMC::GenEvent *evt = mcProd->GetEvent();
    
    shscp::MC mcEvt;
    
    for(HepMC::GenEvent::vertex_const_iterator pitr = evt->vertices_begin();
	pitr!= evt->vertices_end();
	++pitr) {
      
      if((*pitr)->barcode()==-1)  {
	
	mcEvt.vtxX = (*pitr)->point3d().x();
	mcEvt.vtxY = (*pitr)->point3d().y();
	mcEvt.vtxZ = (*pitr)->point3d().z();
	mcEvt.vtxT = (*pitr)->position().t();
	
	for(HepMC::GenVertex::particles_out_const_iterator part = (*pitr)->particles_out_const_begin();
	    part!=(*pitr)->particles_out_const_end(); 
	    ++part) {

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
    doMC_ = false;
  }

}


void StoppedHSCPTreeProducer::doJets(const edm::Event& iEvent) {

   edm::Handle<CaloJetCollection> caloJets;
   iEvent.getByLabel(jetTag_, caloJets);
   
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
	 
 	 // get constituents for later use
//  	 jetTowers_.insert(jetTowers_.end(), it->getCaloConstituents().begin(), it->getCaloConstituents().end());
// 	 for (unsigned i=0; i<it->getCaloConstituents().size(); ++i) {
// 	   towerJets_.push_back(event_->nJet());
// 	 }
	 
       }
     }
   }
   else {
     if (!jetsMissing_) edm::LogWarning("MissingProduct") << "CaloJets not found.  Branch will not be filled" << std::endl;
     jetsMissing_ = true;
   }
   
}


void StoppedHSCPTreeProducer::doMuons(const edm::Event& iEvent) {

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

}


void StoppedHSCPTreeProducer::doTowersAboveThreshold(const edm::Event& iEvent) {
   
  edm::Handle<CaloTowerCollection> caloTowers;
  iEvent.getByLabel(caloTowerTag_,caloTowers);
  
  if (caloTowers.isValid()) {
    
    std::vector<CaloTower> towers;
    towers.insert(towers.end(), caloTowers->begin(), caloTowers->end());     
    sort(towers.begin(), towers.end(), compare_ct());
    
    for(std::vector<CaloTower>::const_iterator it = towers.begin(); 
	it!=towers.end() && event_->nTow() < StoppedHSCPEvent::MAX_N_TOWERS;
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
	tow.nJet = 999;
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
  
}


void StoppedHSCPTreeProducer::doTowersInJets(const edm::Event& iEvent) {


}


void StoppedHSCPTreeProducer::doHcalNoise(const edm::Event& iEvent) {
  
  edm::Handle<HcalNoiseRBXCollection> rbxs;
  iEvent.getByLabel(rbxTag_,rbxs);
  
  if (rbxs.isValid()) {
    for(HcalNoiseRBXCollection::const_iterator it = rbxs->begin(); 
	it!=rbxs->end();
	++it) {
      
      std::vector<HcalNoiseHPD> hpds = it->HPDs();
      for (std::vector<HcalNoiseHPD>::const_iterator hpd = hpds.begin();
	   hpd!=hpds.end() && event_->nHpd() < StoppedHSCPEvent::MAX_N_HPDS;
	   ++hpd) {
	
	shscp::HPD h;
	h.id = hpd->idnumber();
	h.totalZeros = hpd->totalZeros();
	h.maxZeros = hpd->maxZeros();
	h.nJet = 999;  // TODO - fill nJet
	h.fc0 = hpd->bigCharge().at(0);
	h.fc1 = hpd->bigCharge().at(1);
	h.fc2 = hpd->bigCharge().at(2);
	h.fc3 = hpd->bigCharge().at(3);
	h.fc4 = hpd->bigCharge().at(4);
	h.fc5 = hpd->bigCharge().at(5);
	h.fc6 = hpd->bigCharge().at(6);
	h.fc7 = hpd->bigCharge().at(7);
	h.fc8 = hpd->bigCharge().at(8);
	h.fc9 = hpd->bigCharge().at(9);
	h.fc5_0 = hpd->big5Charge().at(0);
	h.fc5_1 = hpd->big5Charge().at(1);
	h.fc5_2 = hpd->big5Charge().at(2);
	h.fc5_3 = hpd->big5Charge().at(3);
	h.fc5_4 = hpd->big5Charge().at(4);
	h.fc5_5 = hpd->big5Charge().at(5);
	h.fc5_6 = hpd->big5Charge().at(6);
	h.fc5_7 = hpd->big5Charge().at(7);
	h.fc5_8 = hpd->big5Charge().at(8);
	h.fc5_9 = hpd->big5Charge().at(9);
	event_->addHPD(h);

      }
    }
  }
  else {
    if (!hpdsMissing_) edm::LogWarning("MissingProduct") << "HCALNoiseRBXCollection not found.  Branch will not be filled" << std::endl;
    hpdsMissing_ = true;
  }
  
}


void StoppedHSCPTreeProducer::doDigisAboveThreshold(const edm::Event& iEvent) {

  // TODO - include threshold!

  edm::Handle<HBHEDigiCollection > hcalDigis;
  iEvent.getByLabel(hcalDigiTag_,hcalDigis);
    
  if (hcalDigis.isValid()) {
  
    std::vector<HBHEDataFrame> digis;
    digis.insert(digis.end(), hcalDigis->begin(), hcalDigis->end());
    sort(digis.begin(), digis.end(), compare_df());

    for(HBHEDigiCollection::const_iterator it=digis.begin();
	it!=digis.end() && event_->nDigi() < StoppedHSCPEvent::MAX_N_DIGIS;
	it++) {

      double totFc=0.;
      for(int i=0; i<10; i++) totFc += it->sample(i).nominal_fC();

      if (totFc > digiMinFc_) {

	shscp::HcalDigi d;
	d.id = it->id();
	d.nJet = 999;
	d.fc0 = it->sample(0).nominal_fC();
	d.fc1 = it->sample(1).nominal_fC();
	d.fc2 = it->sample(2).nominal_fC();
	d.fc3 = it->sample(3).nominal_fC();
	d.fc4 = it->sample(4).nominal_fC();
	d.fc5 = it->sample(5).nominal_fC();
	d.fc6 = it->sample(6).nominal_fC();
	d.fc7 = it->sample(7).nominal_fC();
	d.fc8 = it->sample(8).nominal_fC();
	d.fc9 = it->sample(9).nominal_fC();
	event_->addDigi(d);
	
      }
      
    }
  }
  else {
    if (!digisMissing_) edm::LogWarning("MissingProduct") << "HBHEDigiCollection not found.  Branch will not be filled" << std::endl;
    digisMissing_ = true;
  }

}


void StoppedHSCPTreeProducer::doDigisInJets(const edm::Event& iEvent) {


}


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
