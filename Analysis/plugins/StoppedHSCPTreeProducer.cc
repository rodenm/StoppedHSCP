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
// $Id: StoppedHSCPTreeProducer.cc,v 1.55 2011/03/08 18:01:19 jbrooke Exp $
//
//


// system include files
#include <memory>

// framework
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"

#include "FWCore/Framework/interface/ESHandle.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "FWCore/MessageLogger/interface/MessageLogger.h"

// L1
#include "CondFormats/L1TObjects/interface/L1GtTriggerMenu.h"
#include "CondFormats/DataRecord/interface/L1GtTriggerMenuRcd.h"
#include "DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerReadoutSetupFwd.h"
#include "DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerReadoutSetup.h"
#include "DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerReadoutRecord.h"

#include "DataFormats/L1Trigger/interface/L1JetParticleFwd.h"
#include "DataFormats/L1Trigger/interface/L1JetParticle.h"

#include "SimDataFormats/GeneratorProducts/interface/HepMCProduct.h"

// HLT
#include "DataFormats/HLTReco/interface/TriggerEvent.h"
#include "DataFormats/HLTReco/interface/TriggerTypeDefs.h"
#include "DataFormats/HLTReco/interface/TriggerObject.h"
#include "DataFormats/Common/interface/TriggerResults.h"
#include "FWCore/Utilities/interface/InputTag.h"

#include "HLTrigger/HLTcore/interface/HLTConfigProvider.h"

// jets
#include "DataFormats/JetReco/interface/CaloJetCollection.h"

// muons
#include "DataFormats/MuonReco/interface/MuonFwd.h"
#include "DataFormats/MuonReco/interface/Muon.h"

// Vertices
#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/VertexReco/interface/VertexFwd.h"

// Beam Halo Summary
#include "DataFormats/METReco/interface/BeamHaloSummary.h"

// HCAL noise
#include "DataFormats/METReco/interface/HcalNoiseHPD.h"
#include "DataFormats/METReco/interface/HcalNoiseRBX.h"
#include "DataFormats/METReco/interface/HcalNoiseSummary.h"

// HCAL Channel Status
#include "CondFormats/HcalObjects/interface/HcalChannelStatus.h"
#include "CondFormats/HcalObjects/interface/HcalChannelQuality.h"
#include "CondFormats/HcalObjects/interface/HcalCondObjectContainer.h"
#include "CondFormats/DataRecord/interface/HcalChannelQualityRcd.h"

#include "CalibCalorimetry/HcalAlgos/interface/HcalDbASCIIIO.h"
#include "CalibFormats/HcalObjects/interface/HcalDbRecord.h"

// towers
#include "DataFormats/CaloTowers/interface/CaloTowerCollection.h"
#include "DataFormats/CaloTowers/interface/CaloTowerDetId.h"

// rechits
#include "Geometry/Records/interface/CaloGeometryRecord.h" 
#include "Geometry/CaloGeometry/interface/CaloGeometry.h" 
#include "DataFormats/GeometryVector/interface/GlobalPoint.h" 
#include "DataFormats/HcalRecHit/interface/HcalRecHitCollections.h"
#include "CalibCalorimetry/HcalAlgos/interface/HcalLogicalMapGenerator.h"
#include "CondFormats/HcalObjects/interface/HcalLogicalMap.h"

// CSC segments
#include "DataFormats/CSCRecHit/interface/CSCSegment.h"
#include "DataFormats/CSCRecHit/interface/CSCSegmentCollection.h"
#include "Geometry/Records/interface/MuonGeometryRecord.h"
#include "Geometry/MuonGeometry/interface/MuonGeometry.h"

// digis
#include "CalibFormats/HcalObjects/interface/HcalCoderDb.h"
#include "CalibFormats/HcalObjects/interface/HcalCalibrations.h"
#include "CalibFormats/HcalObjects/interface/HcalDbService.h"
#include "CalibFormats/HcalObjects/interface/HcalDbRecord.h"

#include "DataFormats/HcalDigi/interface/HBHEDataFrame.h"
#include "DataFormats/HcalDigi/interface/HcalDigiCollections.h"
#include "DataFormats/HcalDetId/interface/HcalDetId.h"
#include "DataFormats/HcalDetId/interface/HcalSubdetector.h"



// ROOT output stuff
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "TH1.h"
#include "TTree.h"
#include "TF1.h"

// Helper classes
#include "StoppedHSCP/Analysis/interface/LhcFills.h"


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
  virtual void beginJob() ;
  virtual void beginRun(const edm::Run&, const edm::EventSetup&) ;
  virtual void analyze(const edm::Event&, const edm::EventSetup&);
  virtual void endJob() ;
  
  void doEventInfo(const edm::Event&);

  /// write MC info
  void doMC(const edm::Event&);

  /// write trigger info
  void doTrigger(const edm::Event&, const edm::EventSetup&);

  // write basic RECO objects
  void doJets(const edm::Event&);
  void doGlobalCalo(const edm::Event&);
  void doMuons(const edm::Event&);
  void doVertices(const edm::Event&);
  void doBeamHalo(const edm::Event&);

  // write variables based on HCAL noise summary
  void doHcalNoise(const edm::Event&);
  void fillNoiseObjectTopDigiSamples(shscp::HPD& hpd, std::vector<double>& outvec);
  void fillNoiseObjectTop5DigiSamples(shscp::HPD& hpd, std::vector<double>& outvec);

  // write HCAL RecHits
  void doHcalRecHits(const edm::Event&);

  // write CSC segments
  void doCscSegments(const edm::Event&, const edm::EventSetup&);

  // write variables based on digis
  void doTimingFromDigis(const edm::Event&, const edm::EventSetup&);

  // method to calculate pulse shape variables from time samples
  void pulseShapeVariables(const std::vector<double>& samples,
			   unsigned& ipeak,
			   double& total,
			   double& r1,
			   double& r2,
			   double& rpeak,
			   double& router);



public:
  
  struct l1jet_gt : public std::binary_function<l1extra::L1JetParticle, l1extra::L1JetParticle, bool> {
    bool operator()(const l1extra::L1JetParticle& x, const l1extra::L1JetParticle& y) {
      return ( x.et() > y.et() ) ;
    }
  };

  struct jete_gt : public std::binary_function<reco::CaloJet, reco::CaloJet, bool> {
    bool operator()(const reco::CaloJet& x, const reco::CaloJet& y) {
      return ( x.energy() > y.energy() ) ;
    }
  };
  
  struct calotower_gt : public std::binary_function<CaloTower, CaloTower, bool> {
    bool operator()(const CaloTower& x, const CaloTower& y) {
      return ( x.hadEnergy() > y.hadEnergy() ) ;
    }
  };

  struct rechit_gt : public std::binary_function<CaloRecHit, CaloRecHit, bool> {
    bool operator()(const CaloRecHit& x, const CaloRecHit& y) {
      return ( x.energy() > y.energy() ) ;
    }
  };
  
  struct digi_gt : public std::binary_function<HBHEDataFrame, HBHEDataFrame, bool> {
    bool operator()(const HBHEDataFrame& x, const HBHEDataFrame& y) {
      float TotalX=0;
      float TotalY=0;
      for(int i=0; i<HBHEDataFrame::MAXSAMPLES; i++)
	{
	  double samplex = x.sample(i).nominal_fC();
	  TotalX += samplex;
	  double sampley = y.sample(i).nominal_fC();
	  TotalY += sampley;
	}
      return ( TotalX > TotalY ) ;
    }
  };
  
  struct digiDetId_eq : public std::binary_function<HBHEDataFrame, DetId, bool> {
    bool operator()(const HBHEDataFrame& digi, const DetId& id) const {
      return ( digi.id() == id ) ;
    }
  };
  
private:
  
  // output file
  edm::Service<TFileService> fs_;
  
  // tree
  TTree * tree_;
  StoppedHSCPEvent* event_;

  // EDM input tags
  std::string l1JetsTag_;
  edm::InputTag l1BitsTag_;
  edm::InputTag hltResultsTag_;
  edm::InputTag hltEventTag_;
  std::string hltPath_;
  edm::InputTag hltL3Tag_;
  edm::InputTag mcTag_;
  edm::InputTag jetTag_;
  edm::InputTag muonTag_;
  edm::InputTag cosmicMuonTag_;
  edm::InputTag verticesTag_;
  edm::InputTag caloTowerTag_;
  edm::InputTag caloRecHitTag_;
  edm::InputTag hcalNoiseTag_;
  edm::InputTag hcalNoiseFilterResultTag_;
  edm::InputTag rbxTag_;
  edm::InputTag hpdTag_;
  edm::InputTag hcalRecHitTag_;
  edm::InputTag hcalDigiTag_;
  edm::InputTag cscSegmentsTag_;

  // HLT config helper
  HLTConfigProvider hltConfig_;
  unsigned hltPathIndex_;

  // geometry
  CaloGeometry* caloGeom_;
  MuonGeometry

  // cuts
  double towerMinEnergy_;
  double towerMaxEta_;
  double jetMinEnergy_;
  double jetMaxEta_;
  double digiMinFc_;
  double rechitMinEnergy_;	

  // output control
  bool doMC_;
  bool doCaloTowers_;
  bool doRecHits_;
  bool writeHistos_;

  // Hcal Logical map (ieta-iphi->hardware) object
  HcalLogicalMap* logicalMap_;  
  
  // bad channel status to mask;
  HcalChannelQuality* chanquality_;
  int badchannelstatus_;
  std::set<HcalDetId> badChannels_;

  // LHC Fill structure (temporary until this is available through CMSSW)
  LhcFills fills_;
  std::vector<unsigned> colls_;

  // debug stuff
  bool l1JetsMissing_;
  bool hltJetsMissing_;
  bool hltMissing_;
  bool mcMissing_;
  bool jetsMissing_;
  bool muonsMissing_;
  bool towersMissing_;
  bool rechitsMissing_;
  bool noiseSumMissing_;
  bool rbxsMissing_;
  bool hpdsMissing_;
  bool digisMissing_;
  bool verticesMissing_;
  bool cscSegsMissing_;

  std::vector<CaloTowerPtr> jetTowers_;
  std::vector<unsigned> towerJets_;

  std::vector<HcalDetId> hcalDetIds_;
  std::vector<unsigned> hcalDetJets_;

  std::vector<HBHERecHit> recHits_;

};



StoppedHSCPTreeProducer::StoppedHSCPTreeProducer(const edm::ParameterSet& iConfig):
  tree_(0),
  event_(0),
  l1JetsTag_(iConfig.getUntrackedParameter<std::string>("l1JetsTag",std::string("l1extraParticles"))),
  l1BitsTag_(iConfig.getUntrackedParameter<edm::InputTag>("l1BitsTag",edm::InputTag("gtDigis"))),
  hltResultsTag_(iConfig.getUntrackedParameter<edm::InputTag>("hltResultsTag",edm::InputTag("TriggerResults","","HLT"))),
  hltEventTag_(iConfig.getUntrackedParameter<edm::InputTag>("hltEventTag",edm::InputTag("hltTriggerSummaryAOD","","HLT"))),
  hltPath_(iConfig.getUntrackedParameter<std::string>("hltPath",std::string("HLT_StoppedHSCP"))),
  hltL3Tag_(iConfig.getUntrackedParameter<edm::InputTag>("hltL3Tag",edm::InputTag("hltStoppedHSCP1CaloJetEnergy","","HLT"))),
  mcTag_(iConfig.getUntrackedParameter<edm::InputTag>("mcTag",edm::InputTag("generator"))),
  jetTag_(iConfig.getUntrackedParameter<edm::InputTag>("jetTag",edm::InputTag("sisCone5CaloJets"))),
  muonTag_(iConfig.getUntrackedParameter<edm::InputTag>("muonTag",edm::InputTag("muons"))),
  cosmicMuonTag_(iConfig.getUntrackedParameter<edm::InputTag>("cosmicMuonTag",edm::InputTag("muonsFromCosmics"))),
  verticesTag_(iConfig.getUntrackedParameter("verticesTag",edm::InputTag("offlinePrimaryVertices"))),
  caloTowerTag_(iConfig.getUntrackedParameter<edm::InputTag>("caloTowerTag",edm::InputTag("towerMaker"))),
  caloRecHitTag_(iConfig.getUntrackedParameter<edm::InputTag>("caloRecHitTag",edm::InputTag("hbhereco"))),
  hcalNoiseTag_(iConfig.getUntrackedParameter<edm::InputTag>("hcalNoiseTag",edm::InputTag("hcalnoise"))),
  hcalNoiseFilterResultTag_(iConfig.getUntrackedParameter<edm::InputTag>("hcalNoiseFilterResultTag",edm::InputTag("HBHENoiseFilterResultProducer"))),
  rbxTag_(iConfig.getUntrackedParameter<edm::InputTag>("rbxTag",edm::InputTag("hcalnoise"))),
  hpdTag_(iConfig.getUntrackedParameter<edm::InputTag>("hpdTag",edm::InputTag("hcalnoise"))),
  hcalRecHitTag_(iConfig.getUntrackedParameter<edm::InputTag>("hcalRecHitTag",edm::InputTag("hbhereco"))),
  hcalDigiTag_(iConfig.getUntrackedParameter<edm::InputTag>("hcalDigiTag",edm::InputTag("hcalDigis"))),
  cscSegmentsTag_(iConfig.getUntrackedParameter<edm::InputTag>("cscSegmentsTag",edm::InputTag("cscSegments"))),
  towerMinEnergy_(iConfig.getUntrackedParameter<double>("towerMinEnergy", 1.)),
  towerMaxEta_(iConfig.getUntrackedParameter<double>("towerMaxEta", 1.3)),
  jetMinEnergy_(iConfig.getUntrackedParameter<double>("jetMinEnergy", 1.)),
  jetMaxEta_(iConfig.getUntrackedParameter<double>("jetMaxEta", 3.)),
  digiMinFc_(iConfig.getUntrackedParameter<double>("digiMinFc", 30)),
  rechitMinEnergy_(iConfig.getUntrackedParameter<double>("rechitMinEnergy", 0.2)),
  doMC_(iConfig.getUntrackedParameter<bool>("doMC",true)),
  doCaloTowers_(iConfig.getUntrackedParameter<bool>("doCaloTowers",true)),
  doRecHits_(iConfig.getUntrackedParameter<bool>("doRecHits",false)),
  writeHistos_(iConfig.getUntrackedParameter<bool>("writeHistos",false)),
  badchannelstatus_(iConfig.getUntrackedParameter<int>("badchannelstatus",0)),
  fills_(),
  colls_(0),
  l1JetsMissing_(false),
  hltJetsMissing_(false),
  hltMissing_(false),
  mcMissing_(false),
  jetsMissing_(false),
  muonsMissing_(false),
  towersMissing_(false),
  rechitsMissing_(false),
  noiseSumMissing_(false),
  rbxsMissing_(false),
  hpdsMissing_(false),
  digisMissing_(false),
  hcalDetIds_(0),
  hcalDetJets_(0)
{

  // set up output
  tree_=fs_->make<TTree>("StoppedHSCPTree", "");
  tree_->Branch("events", "StoppedHSCPEvent", &event_, 64000, 1);
  
  // log
  std::string log="reco ";
  if (doMC_) log += " mc";
  if (doCaloTowers_) log += " calotowers";
  if (doRecHits_) log += " rechits";

  edm::LogInfo("StoppedHSCPTree") << "Going to fill " << log << std::endl;

  HcalLogicalMapGenerator gen;
  logicalMap_=new HcalLogicalMap(gen.createMap());
}


StoppedHSCPTreeProducer::~StoppedHSCPTreeProducer() {

   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called once each job just before starting event loop  ------------
void 
StoppedHSCPTreeProducer::beginJob()
{
}

// -- called once per run
void 
StoppedHSCPTreeProducer::beginRun(edm::Run const & run, edm::EventSetup const& iSetup)
{

  // HLT setup
  bool changed;
  hltConfig_.init(run, iSetup, hltResultsTag_.process(), changed);
  hltPathIndex_ = hltConfig_.triggerIndex(hltPath_);

  // HCAL geometry to calculate eta/phi for CaloRecHits
  edm::ESHandle<CaloGeometry> caloGeomRec;
  iSetup.get<CaloGeometryRecord>().get(caloGeomRec);
  caloGeom_ = caloGeomRec.product();

  // HCAL bad channel removal
  badChannels_.clear();
  edm::ESHandle<HcalChannelQuality> p;
  iSetup.get<HcalChannelQualityRcd>().get(p);
  //std::cout <<"BEGIN RUN STARTED!"<<std::endl;
  chanquality_= new HcalChannelQuality(*p.product());
  std::vector<DetId> mydetids = chanquality_->getAllChannels();
  for (std::vector<DetId>::const_iterator i = mydetids.begin();i!=mydetids.end();++i)
    {
      if (i->det()!=DetId::Hcal) continue; // not an hcal cell
      // Only consider HB/HE for now; revise when necessary
      if (i->subdetId()!=HcalBarrel && i->subdetId()!=HcalEndcap) continue;
      HcalDetId id=HcalDetId(*i);
      int status=(chanquality_->getValues(id))->getValue();
      //std::cout <<"checking "<<id<<"  STATUS = "<<status<<std::endl;
      if ((status&badchannelstatus_)==0) continue;
      //std::cout <<"\tBAD CHANNEL FOUND!"<<id<<"  STATUS = "<<status<<std::endl;
      badChannels_.insert(id);
    }

  // CSC geometry
  edm::ESHandle<CSCGeometry> cscGeomRec;
  iSetup.get<MuonGeometryRecord>().get(cscGeomRec);
  cscGeom_ = cscGeomRec.product();

  // set filling scheme for this run
  colls_ = fills_.getCollisionsFromRun(run.runAuxiliary().run());

}


// ------------ method called once each job just after ending the event loop  ------------
void 
StoppedHSCPTreeProducer::endJob() {
}

// ------------ method called to for each event  ------------
void
StoppedHSCPTreeProducer::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  event_ = new StoppedHSCPEvent();
  
  if (doMC_) doMC(iEvent);

  // event & trigger info
  doEventInfo(iEvent);
  doTrigger(iEvent, iSetup);

  // general RECO info
  doJets(iEvent);
  doGlobalCalo(iEvent);
  doMuons(iEvent);
  doBeamHalo(iEvent);
  doVertices(iEvent);

  // HCAL noise summary info
  doHcalNoise(iEvent);

  // HCAL RecHits & flags
  doHcalRecHits(iEvent);

  // CSC segments
  doCscSegments(iEvent, iSetup);

  // digi based variables
  doTimingFromDigis(iEvent, iSetup);
  
  // fill TTree
  tree_->Fill();
  
  delete event_;

}



void StoppedHSCPTreeProducer::doMC(const edm::Event& iEvent) {

  edm::Handle<edm::HepMCProduct> mcHandle;
  iEvent.getByLabel(mcTag_,mcHandle);
  
  if (mcHandle.isValid()) {
    
    const edm::HepMCProduct *mcProd = mcHandle.product();
    const HepMC::GenEvent *evt = mcProd->GetEvent();
    
    for(HepMC::GenEvent::vertex_const_iterator pitr = evt->vertices_begin();
	pitr!= evt->vertices_end();
	++pitr) {
      
      if((*pitr)->barcode()==-1)  {

	event_->rHadVtxX = (*pitr)->point3d().x();
	event_->rHadVtxY = (*pitr)->point3d().y();
	event_->rHadVtxZ = (*pitr)->point3d().z();
	event_->rHadVtxT = (*pitr)->position().t();
	
	for(HepMC::GenVertex::particles_out_const_iterator part = (*pitr)->particles_out_const_begin();
	    part!=(*pitr)->particles_out_const_end(); 
	    ++part) {

	  if((*part)->pdg_id()>=1000000)
	    {
	      event_->rHadPdgId = (*part)->pdg_id();
	      event_->rHadPx  = (*part)->momentum().x();
	      event_->rHadPy  = (*part)->momentum().y();
	      event_->rHadPz  = (*part)->momentum().z();
	      event_->rHadPt  = (*part)->momentum().perp();
	      event_->rHadE   = (*part)->momentum().e();

	    }
	}
	
      }
    }
    
  }
  else {
    if (!mcMissing_) edm::LogWarning("MissingProduct") << "MC information not found.  Branch will not be filled" << std::endl;
    mcMissing_ = true;
    doMC_ = false;
  }

}




void StoppedHSCPTreeProducer::doEventInfo(const edm::Event& iEvent){ 
  unsigned long orbitsPerLB = 1<<18;
  unsigned long bxPerOrbit = 3564;
  unsigned nsPerBx = 25;
  unsigned bx = iEvent.bunchCrossing();

  event_->id = iEvent.id().event();
  event_->bx = bx;
  event_->orbit = iEvent.orbitNumber();
  event_->lb = iEvent.luminosityBlock();
  event_->run = iEvent.id().run();
  event_->fill = iEvent.eventAuxiliary().storeNumber();
  event_->time = iEvent.time().value();

  // calculate event time from run start + LS, orbit, BX
  ULong64_t nBx = ( ( (iEvent.luminosityBlock() * orbitsPerLB ) + iEvent.orbitNumber() ) * bxPerOrbit ) + iEvent.bunchCrossing() ;
  event_->time2 = iEvent.getRun().beginTime().value() + (nBx * nsPerBx);

  // find last/next collisions
  int bxLast=-1;
  int bxNext=-1;
  if (colls_.size() > 0) {
    // special case if event is before first collision
    if (bx < colls_.at(0)) {
      bxLast = colls_.at(colls_.size() - 1);
      bxNext = colls_.at(colls_.at(0));
    }
    // special case if event is after last collision
    else if (bx > colls_.at(colls_.size() - 1)) {
      bxLast = colls_.at(colls_.size()-1);
      // For MC, colls_ = [1], so  colls_.at(colls_.at(0)) = colls_.at(1), which doesn't exist.
      // Protection added here against that case.
      // JIM -- do you want to use the conditional statement below, or add in a separate "else if" for this circumstance?
      //if (colls_.size()>colls_.at(0))
      bxNext = colls_.at(colls_.at(0));
    }
    // general case
    else {      
      for (unsigned c=0; c<(colls_.size()-1) && colls_.at(c)<bx; ++c) {
	bxLast = colls_.at(c);
	bxNext = colls_.at(c+1);
      }
    }
  }

  // set values in ntuple
  event_->bxAfterCollision = bx - bxLast;
  event_->bxBeforeCollision = bxNext - bx;
  if (event_->bxAfterCollision > event_->bxBeforeCollision) {
    event_->bxWrtCollision = event_->bxBeforeCollision;
  }
  else {
    event_->bxWrtCollision = -1 * event_->bxAfterCollision;
  }
}
  

void StoppedHSCPTreeProducer::doTrigger(const edm::Event& iEvent, const edm::EventSetup& iSetup) {

  // trigger bits
  uint64_t gtAlgoWord0(0), gtAlgoWord1(0), gtTechWord(0);
  bool hltBit(false);

  // get GT data
//   edm::ESHandle<L1GtTriggerMenu> menuRcd;
//   iSetup.get<L1GtTriggerMenuRcd>().get(menuRcd) ;
//   const L1GtTriggerMenu* menu = menuRcd.product();

  edm::Handle<L1GlobalTriggerReadoutRecord> gtReadoutRecord;
  iEvent.getByLabel(l1BitsTag_, gtReadoutRecord);

  // L1 trigger bits
  DecisionWord gtDecisionWord = gtReadoutRecord->decisionWord();
  unsigned i=0;
  for(DecisionWord::const_iterator itr=gtDecisionWord.begin();
      itr != gtDecisionWord.end();
      itr++, i++) {
    if (*itr) {
      if(i<64) { gtAlgoWord0 |= (1LL<<i); }
      else { gtAlgoWord1 |= (1LL<<(i-64)); }
    } 
  }

  TechnicalTriggerWord gtTechDecisionWord = gtReadoutRecord->technicalTriggerWord();    
  i=0;
  for(TechnicalTriggerWord::const_iterator itr=gtDecisionWord.begin();
      itr != gtDecisionWord.end();
      itr++, i++) {
    if (*itr) {
      gtTechWord |= (1LL<<i);
    } 
  }
 

  // HLT config setup
  // moved to beginRun()

  // get HLT results
  edm::Handle<edm::TriggerResults> HLTR;
  iEvent.getByLabel(hltResultsTag_, HLTR);

  if (HLTR.isValid()) {
    // triggerIndex must be less than the size of HLTR or you get a CMSException: _M_range_check
    if (hltPathIndex_ < HLTR->size()) hltBit = HLTR->accept(hltPathIndex_); 
  }

  // store bits
  event_->gtAlgoWord0 = gtAlgoWord0;
  event_->gtAlgoWord1 = gtAlgoWord1;
  event_->gtTechWord = gtTechWord;
  event_->hltBit = hltBit;

  // L1 jets
  edm::Handle<l1extra::L1JetParticleCollection> l1CenJets;
  iEvent.getByLabel(l1JetsTag_, "Central", l1CenJets);  
  edm::Handle<l1extra::L1JetParticleCollection> l1TauJets;
  iEvent.getByLabel(l1JetsTag_, "Tau", l1TauJets);
  
  if (l1CenJets.isValid() && l1TauJets.isValid()) { 

    // merge and sort central and tau jet collections
    std::vector<l1extra::L1JetParticle> l1jets;
    
    l1jets.insert(l1jets.end(), l1CenJets->begin(), l1CenJets->end());
    l1jets.insert(l1jets.end(), l1TauJets->begin(), l1TauJets->end());
    std::sort(l1jets.begin(), l1jets.end(), l1jet_gt());
    
    for (std::vector<l1extra::L1JetParticle>::const_iterator jet=l1jets.begin(); jet!=l1jets.end(); ++jet) {
      shscp::TrigJet j;
      j.type = jet->type();   // 0 = central, 1 = forward, 2 = tau
      j.e = jet->energy();
      j.et = jet->et();
      j.phi = jet->phi();
      j.eta = jet->eta();
      event_->addL1Jet(j);
    }
    
  }
  else {
    if (!l1JetsMissing_) edm::LogWarning("MissingProduct") << "L1 information not found.  Branch will not be filled" << std::endl;
    l1JetsMissing_ = true;
  }

  // get HLT jets
  edm::Handle<trigger::TriggerEvent> trgEvent;
  iEvent.getByLabel(hltEventTag_, trgEvent);

  // for Stopped HSCP L3 filter  
  if (trgEvent.isValid()) {

    const unsigned int filterIndex (trgEvent->filterIndex(hltL3Tag_) );

    //   edm::LogInfo("StoppedHSCP") << "Debugging HLT...  StoppedHSCP index=" << filterIndex 
    //				<< ",  N paths=" << trgEvent->sizeFilters() << std::endl;
    
    if (filterIndex < trgEvent->sizeFilters()) {
            
      const trigger::TriggerObjectCollection& TOC(trgEvent->getObjects());
      const trigger::Keys& keys( trgEvent->filterKeys(filterIndex) );
	
      //      edm::LogInfo("StoppedHSCP") << "Found  " << keys.size() << " HLT jets" << std::endl;

      for ( unsigned hlto = 0; 
	    hlto < keys.size();
	    hlto++ ) {
	trigger::size_type hltf = keys[hlto];
	const trigger::TriggerObject& L3obj(TOC[hltf]);

	//	edm::LogInfo("StoppedHSCP") << "HLT jet e=" << L3obj.energy() << std::endl;
        
	shscp::TrigJet j;
	j.type = 99;
	j.e = L3obj.energy();
	j.et = L3obj.et();
	j.phi = L3obj.phi();
	j.eta = L3obj.eta();
	event_->addHltJet(j);
	
      }
      
    }

  }
  else {
    if (!hltJetsMissing_) edm::LogWarning("MissingProduct") << "TriggerEvent not found.  Branch will not be filled" << std::endl;
    hltJetsMissing_ = true;
  }
							       
}



void StoppedHSCPTreeProducer::doJets(const edm::Event& iEvent) {

   edm::Handle<CaloJetCollection> caloJets;
   iEvent.getByLabel(jetTag_, caloJets);
   
   unsigned njet=0;

   if (caloJets.isValid()) {

     // sort jets by energy
     std::vector<CaloJet> jets;
     jets.insert(jets.end(), caloJets->begin(), caloJets->end());
     std::sort(jets.begin(), jets.end(), jete_gt() );

     for(CaloJetCollection::const_iterator it=jets.begin(); 
	 it!=jets.end();
	 ++it, ++njet) {
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

// 	 std::cout << "Jet " << std::endl;q
// 	 std::cout << "   E=" << it->energy() << " eta=" << it->eta() << " phi=" << it->phi() << std::endl;
	 // get towers

	 if (doCaloTowers_) {

	   for (int i=0; i<it->nConstituents(); ++i) {
	     
	     CaloTowerPtr tower = it->getCaloConstituent(i);
	     
	     if (tower->energy() > towerMinEnergy_ &&
		 fabs(tower->eta()) < towerMaxEta_) {
	       
	       // write tower
	       shscp::Tower tow;
	       tow.e = tower->energy();
	       tow.et = tower->et();
	       tow.eta = tower->eta();
	       tow.phi = tower->phi();
	       tow.ieta = tower->ieta();
	       tow.iphi = tower->iphi();
	       tow.nJet = njet;
	       tow.eHad = tower->hadEnergy();
	       tow.etHad = tower->hadEt();
	       tow.eEm = tower->emEnergy();
	       tow.etEm = tower->emEt();
	       event_->addTower(tow);

	       // 	   std::cout << "  Calo tower" << std::endl;
	       // 	   std::cout << "    eta=" << tower->eta() << " phi=" << tower->phi() << std::endl;
	       // 	   std::cout << "    ECAL E=" << tower->emEnergy() << " HCAL E=" << tower->hadEnergy() << std::endl;
	       // 	   std::cout << "    ECAL time : " << tower->ecalTime() << std::endl;
	       // 	   std::cout << "    HCAL time : " << tower->hcalTime() << std::endl;
	       
	     }
	   }
	 } // if (doCaloTowers_)

       }
     }
   }
   else {
     if (!jetsMissing_) edm::LogWarning("MissingProduct") << "CaloJets not found.  Branch will not be filled" << std::endl;
     jetsMissing_ = true;
   }
   
}



void StoppedHSCPTreeProducer::doMuons(const edm::Event& iEvent) {

  // loop over reco muons
  edm::Handle<reco::MuonCollection> muons;
  iEvent.getByLabel(muonTag_,muons);

  if (muons.isValid()) {
    for(reco::MuonCollection::const_iterator it =muons->begin();
	it!=muons->end();
	it++) {
      shscp::Muon mu;
      mu.pt = it->pt();
      mu.eta = it->eta();
      mu.phi = it->phi();
      mu.hcalEta = 0.;  // TODO extrapolate GlobalMuon track to HCAL surface and store position!
      mu.hcalPhi = 0.;
      mu.type = (0xf & it->type());
       event_->addMuon(mu);
    }
  }
  else {
    if (!muonsMissing_) edm::LogWarning("MissingProduct") << "Muons not found.  Branch will not be filled" << std::endl;
    muonsMissing_ = true;
  }
  
  // loop over cosmic muons
  edm::Handle<reco::MuonCollection> cosmicMuons;
  iEvent.getByLabel(cosmicMuonTag_,cosmicMuons);
 
  if (cosmicMuons.isValid()) {
    for(reco::MuonCollection::const_iterator it =cosmicMuons->begin();
	it!=cosmicMuons->end();
	it++) {
      shscp::Muon mu;
      mu.pt = it->pt();
      mu.eta = it->eta();
      mu.phi = it->phi();
      mu.hcalEta = 0.;  // TODO extrapolate GlobalMuon track to HCAL surface and store position!
      mu.hcalPhi = 0.;
      mu.type = (0xf & it->type())<<8;
       event_->addMuon(mu);
    }
  }
  else {
    if (!muonsMissing_) edm::LogWarning("MissingProduct") << "Cosmic muons not found.  Branch will not be filled" << std::endl;
    muonsMissing_ = true;
  }

} // void StoppedHSCPTreeProducer::doMuons()



void StoppedHSCPTreeProducer::doVertices(const edm::Event& iEvent) {

  edm::Handle<reco::VertexCollection> recoVertices;
  iEvent.getByLabel(verticesTag_, recoVertices);

  event_->nVtx=0;
  if (recoVertices.isValid()) {
    for(reco::VertexCollection::const_iterator it=recoVertices->begin();
	it!=recoVertices->end();
	++it) {
      
      if (!it->isFake()) {
	event_->vtxNDOF.push_back(it->ndof());
	event_->vtxZ.push_back(it->z());
	event_->vtxRho.push_back(it->position().rho());
	event_->nVtx++;
      }
    }
  }
  else {
    if (!verticesMissing_) {
      edm::LogWarning("MissingProduct") << "Vertices not found.  Branch will not be filled" << std::endl;
      verticesMissing_=true;
    }
  }
  
} // void StoppedHSCPTreeProducer::doVertices(const edm::Event& iEvent)



void StoppedHSCPTreeProducer::doBeamHalo(const edm::Event& iEvent)
{
    
  edm::Handle<BeamHaloSummary> TheBeamHaloSummary;
  iEvent.getByLabel("BeamHaloSummary",TheBeamHaloSummary);
  bool beamhalo_csctight=false;
  bool beamhalo_cscloose=false;
  bool beamhalo_hcaltight=false;
  bool beamhalo_hcalloose=false;

  if (TheBeamHaloSummary.isValid())
    {
      const BeamHaloSummary TheSummary = (*TheBeamHaloSummary.product() );
      if (TheSummary.CSCTightHaloId()==true)  beamhalo_csctight = true; 
      if (TheSummary.CSCLooseHaloId()==true)  beamhalo_cscloose = true; 
      if (TheSummary.HcalTightHaloId()==true)  beamhalo_hcaltight = true; 
      if (TheSummary.HcalLooseHaloId()==true)  beamhalo_hcalloose = true; 
    }
  event_->beamHalo_CSCTight=beamhalo_csctight;
  event_->beamHalo_CSCLoose=beamhalo_cscloose;
  event_->beamHalo_HcalTight=beamhalo_hcaltight;
  event_->beamHalo_HcalLoose=beamhalo_hcalloose;

  return;
} // void StoppedHSCPTreeProducer::doBeamHalo(iEvent)



// global calo based quantities
void StoppedHSCPTreeProducer::doGlobalCalo(const edm::Event& iEvent) {

  event_->nTowerSameiPhi=0;

  // get calo towers
  edm::Handle<CaloTowerCollection> caloTowers;
  iEvent.getByLabel(caloTowerTag_,caloTowers);

  if (caloTowers.isValid()) {
    
    std::vector<CaloTower> caloTowersTmp;
    caloTowersTmp.insert(caloTowersTmp.end(), caloTowers->begin(), caloTowers->end());
    sort(caloTowersTmp.begin(), caloTowersTmp.end(), calotower_gt());
    
    int iphiFirst=caloTowersTmp.begin()->iphi();
    bool keepgoing=true;
    for(std::vector<CaloTower>::const_iterator twr = caloTowersTmp.begin();
	twr!=caloTowersTmp.end() && keepgoing;
	++twr) {
      
      if (fabs(twr->eta()) < towerMaxEta_) {	

	// tower same iphi as leading tower
	if (twr->iphi()==iphiFirst) {
	  event_->nTowerSameiPhi++;
	  event_->nTowerLeadingIPhi++;
	  event_->eHadLeadingIPhi += twr->hadEnergy();
	}
	else {
	  keepgoing=false;
	}
      }  
    } 

  }
  else {
    if (!towersMissing_) edm::LogWarning("MissingProduct") << "CaloTowers not found.  Branches will not be filled" << std::endl;
    towersMissing_ = true;
  }
  
} // void StoppedHSCPTreeProducer::doGlobalCalo(const edm::Event& iEvent)



void StoppedHSCPTreeProducer::doHcalNoise(const edm::Event& iEvent) {
  
  // get noise summary
  edm::Handle<HcalNoiseSummary> summary;
  iEvent.getByLabel(hcalNoiseTag_,summary);

  if (summary.isValid()) {
    event_->noiseMinE2Over10TS = summary->minE2Over10TS();
    event_->noiseMaxE2Over10TS = summary->maxE2Over10TS();
    event_->noiseMaxHPDHits = summary->maxHPDHits();
    event_->noiseMaxRBXHits = summary->maxRBXHits();
    event_->noiseMaxHPDNoOtherHits = summary->maxHPDNoOtherHits();
    event_->noiseMaxZeros = summary->maxZeros();
    event_->noiseMin25GeVHitTime = summary->min25GeVHitTime();
    event_->noiseMax25GeVHitTime = summary->max25GeVHitTime();
    event_->noiseMinRBXEMF = summary->minRBXEMF();

    event_->noiseEventEMEnergy = summary->eventEMEnergy();
    event_->noiseEventHadEnergy = summary->eventHadEnergy();
    event_->noiseEventTrackEnergy = summary->eventTrackEnergy();
    event_->noiseNumProblematicRBXs = summary->numProblematicRBXs();
    // The following only work in 3_11_X (?) and above
    //event_->noiseNumIsolatedNoiseChannels = summary->numIsolatedNoiseChannels();
    //event_->noiseIsolatedNoiseSumEt = summary->isolatedNoiseSumEt();
  }
  else {
    if (!noiseSumMissing_) edm::LogWarning("MissingProduct") << "HCALNoiseSummary not found.  Branch will not be filled" << std::endl;
    noiseSumMissing_ = true;
  }

  // get noise filter flag
  edm::Handle<bool> flag;
  iEvent.getByLabel(hcalNoiseFilterResultTag_,flag);

  event_->noiseFilterResult = true;
  if (flag.isValid()) {
    event_->noiseFilterResult = (*flag.product());
  }
  else {
    edm::LogWarning("MissingProduct") << "No HBHE filter flag in Event" << std::endl;
  }


  // get RBX/HPD collection
  edm::Handle<HcalNoiseRBXCollection> rbxs;
  iEvent.getByLabel(rbxTag_,rbxs);
  
  if (rbxs.isValid()) 
    {
      // Store the HPD object with the largest total Charge; used that for forming noise variables
      shscp::HPD maxHPD;
      double maxCharge=0;

      for(HcalNoiseRBXCollection::const_iterator it = rbxs->begin(); 
	  it!=rbxs->end();
	  ++it) {
	
	std::vector<HcalNoiseHPD> hpds = it->HPDs();
	for (std::vector<HcalNoiseHPD>::const_iterator hpd = hpds.begin();
	     hpd!=hpds.end();
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
	  // Compute total charge for the "top5" of this HPD; compare to maxCharge
	  double totalCharge = 0;
	  totalCharge+= h.fc5_0+h.fc5_1+h.fc5_2+h.fc5_3+h.fc5_4;
	  totalCharge+= h.fc5_5+h.fc5_6+h.fc5_7+h.fc5_8+h.fc5_9;
	  if (totalCharge>maxCharge)
	    {
	      maxCharge=totalCharge;
	      //maxHPD=hpd;
	      maxHPD=h;
	    }
	  event_->addHPD(h);
	  
	} // loop on HPDs
      } // loop on RBXs
      // One maximum HPD has been found, compute NoiseSummary-based R values

      // Fill event vector "topHPD5TimeSamples" with "top5" charges from max HPD
      fillNoiseObjectTop5DigiSamples(maxHPD,event_->topHPD5TimeSamples);

      // Compute noise summary versions of R1, R2, etc. variables
      pulseShapeVariables(event_->topHPD5TimeSamples,
			  event_->topHPD5PeakSample,
			  event_->topHPD5Total,
			  event_->topHPD5R1,
			  event_->topHPD5R2,
			  event_->topHPD5RPeak,
			  event_->topHPD5ROuter);
    }
  else {
    if (!hpdsMissing_) edm::LogWarning("MissingProduct") << "HCALNoiseRBXCollection not found.  Branch will not be filled" << std::endl;
    hpdsMissing_ = true;
  }
  
}// doHcalNoise(...)


void StoppedHSCPTreeProducer::fillNoiseObjectTop5DigiSamples(shscp::HPD& hpd, std::vector<double>& outvec)
{
  /* Fill a pulse shape vector with values from the "top5" digis in a single HPD.
     Only positive charge values are allowed; otherwise, the vector entry is 0.
  */
  outvec.clear();
  outvec.push_back(std::max(0.,hpd.fc5_0));
  outvec.push_back(std::max(0.,hpd.fc5_1));
  outvec.push_back(std::max(0.,hpd.fc5_2));
  outvec.push_back(std::max(0.,hpd.fc5_3));
  outvec.push_back(std::max(0.,hpd.fc5_4));
  outvec.push_back(std::max(0.,hpd.fc5_5));
  outvec.push_back(std::max(0.,hpd.fc5_6));
  outvec.push_back(std::max(0.,hpd.fc5_7));
  outvec.push_back(std::max(0.,hpd.fc5_8));
  outvec.push_back(std::max(0.,hpd.fc5_9));
  return;
}



void StoppedHSCPTreeProducer::fillNoiseObjectTopDigiSamples(shscp::HPD& hpd, std::vector<double>& outvec)
{
  /* Fill a pulse shape vector with values from the digi with the largest charge in a single HPD.
     Only positive charge values are allowed; otherwise, the vector entry is 0.
  */
  outvec.clear();
  outvec.push_back(std::max(0.,hpd.fc0));
  outvec.push_back(std::max(0.,hpd.fc1));
  outvec.push_back(std::max(0.,hpd.fc2));
  outvec.push_back(std::max(0.,hpd.fc3));
  outvec.push_back(std::max(0.,hpd.fc4));
  outvec.push_back(std::max(0.,hpd.fc5));
  outvec.push_back(std::max(0.,hpd.fc6));
  outvec.push_back(std::max(0.,hpd.fc7));
  outvec.push_back(std::max(0.,hpd.fc8));
  outvec.push_back(std::max(0.,hpd.fc9));
  return;
}




/// fill rec hit 
void
StoppedHSCPTreeProducer::doHcalRecHits(const edm::Event& iEvent)
{

  recHits_.clear();

  // get the rechits (to select digis ordered by energy)
  edm::Handle<HBHERecHitCollection> recHits;
  iEvent.getByLabel(hcalRecHitTag_, recHits);

  // copy rechits to internal vector
  if(recHits.isValid()) {
    
    // reject bad status rechits from collection
    for (HBHERecHitCollection::const_iterator it=recHits->begin();
	 it!=recHits->end();++it) {
      
      if (std::find(badChannels_.begin(),
		    badChannels_.end(),
		    it->id())!=badChannels_.end()) {
	continue;
      }

      recHits_.push_back(*it);
      
    }
  }
  else {
    if (!rechitsMissing_) edm::LogWarning("MissingProduct") << "CaloRecHits not found.  Branches will not be filled" << std::endl;
    rechitsMissing_ = true;
  }

  // sort by energy
  sort(recHits_.begin(), recHits_.end(), rechit_gt());
  
  // store to ntuple if required
  if (doRecHits_) {
    
    unsigned count=0;

    for (HBHERecHitCollection::const_iterator hit=recHits_.begin();
	 hit!=recHits_.end() && count < 6000;
	 ++hit, ++count) {
      
      GlobalPoint pos = caloGeom_->getPosition((*hit).detid());
      
      shscp::RecHit rh;
      
      rh.e = (*hit).energy();
      
      if (rh.e > rechitMinEnergy_ ) {
	
	rh.time  = (*hit).time();
	rh.flags = (*hit).flags();
	rh.aux   = (*hit).aux();
	rh.eta   = pos.eta();
	rh.phi   = pos.phi();
	rh.ieta  = (*hit).id().ieta();
	rh.iphi  = (*hit).id().iphi();
	rh.depth = (*hit).id().depth();
	rh.RBXindex = logicalMap_->getHcalFrontEndId(hit->detid()).rbxIndex();
	rh.RMindex  = logicalMap_->getHcalFrontEndId(hit->detid()).rm();
	event_->addRecHit(rh);

	count++;

      }
      
    }
    
  }
  
}


void StoppedHSCPTreeProducer::doCscSegments(const edm::Event& iEvent, const edm::EventSetup& iSetup) {

  // get the rechits (to select digis ordered by energy)
  edm::Handle<CSCSegmentCollection> segments;
  iEvent.getByLabel(cscSegmentsTag_, segments);

  // copy rechits to internal vector
  if(segments.isValid()) {

    unsigned i=0;
    for (CSCSegmentCollection::const_iterator seg=segments->begin();
	 seg!=segments->end() && i<1000;
	 ++seg, ++i) {

      // use CSC geometry to get segment position
      //GlobalPoint pos = ????

      shscp::CscSegment s;
      s.detId = seg->cscDetId();
      s.nHits = seg->nRecHits();
//       s.phi = pos.phi();
//       s.z = pos.z();
//       s.r = pos.rho();
    }

  }
  else {
    if (!cscSegsMissing_) edm::LogWarning("MissingProduct") << "CSC Segments not found.  Branches will not be filled" << std::endl;
    cscSegsMissing_ = true;
  }

}



void StoppedHSCPTreeProducer::doTimingFromDigis(const edm::Event& iEvent, const edm::EventSetup& iSetup) {

  // this code taken from John Paul Chou's noise info producer
  // RecoMET/METProducers/src/HcalNoiseInfoProducer.cc

  // get the conditions and channel quality
  edm::ESHandle<HcalDbService> conditions;
  iSetup.get<HcalDbRecord>().get(conditions);
  const HcalQIEShape* shape = conditions->getHcalShape();

  // get the digis themselves
  edm::Handle<HBHEDigiCollection> hcalDigis;
  iEvent.getByLabel(hcalDigiTag_,hcalDigis);

  if (hcalDigis.isValid()) {

    // loop over the digis
    for(HBHEDigiCollection::const_iterator it=hcalDigis->begin(); it!=hcalDigis->end(); ++it) {

      const HBHEDataFrame &digi=(*it);
      HcalDetId cell = digi.id();

      // still need to check on valid digis; don't want to include bad channels in digi check
      if (std::find(badChannels_.begin(),
		    badChannels_.end(),
		    cell)!=badChannels_.end())
	{
	  //std::cout <<"BAD CHANNEL FOUND IN DIGI COLLECTION!";
	  //std::cout <<"\t("<<cell.ieta()<<","<<cell.iphi()<<","<<cell.depth()<<")"<<  std::endl;
	  continue;
	}
      DetId detcell=(DetId)cell;

      // get the calibrations and coder
      const HcalCalibrations& calibrations=conditions->getHcalCalibrations(cell);
      const HcalQIECoder* channelCoder = conditions->getHcalCoder (cell);
      HcalCoderDb coder (*channelCoder, *shape);

      // figure out if this digi corresponds to highest RecHit or top 5 RecHits
      bool isBig=false, isBig5=false;
      unsigned counter=0;

      for(HBHERecHitCollection::const_iterator hit=recHits_.begin();
	  hit!=recHits_.end() && counter < 5;
	  ++hit, ++counter) 
	{
	  if(hit->id() == digi.id()) 
	    {
	      if(counter==0) isBig=true;  // digi is also the highest energy rechit
	      isBig5=true;         // digi is one of 5 highest energy rechits
	      break;
	    }
	}
     
      // correct time slices for pedestal
      CaloSamples tool;
      coder.adc2fC(digi,tool);
      for(int ts=0; ts<tool.size(); ++ts) {
	
	// get the fC's
	double corrfc = tool[ts]-calibrations.pedestal(digi[ts].capid());
	
	// fill the relevant digi arrays
	if(isBig) {
	  event_->leadingDigiTimeSamples.at(ts) += corrfc;
	  event_->leadingDigiIEta = digi.id().ieta();
	  event_->leadingDigiIPhi = digi.id().iphi();
	}
	if(isBig5 && corrfc > 0.) event_->top5DigiTimeSamples.at(ts) += corrfc;
      }

    }

    // find peaks in time samples and totals
    pulseShapeVariables(event_->leadingDigiTimeSamples,
			event_->leadingDigiPeakSample,
			event_->leadingDigiTotal,
			event_->leadingDigiR1,
			event_->leadingDigiR2,
			event_->leadingDigiRPeak,
			event_->leadingDigiROuter);

    pulseShapeVariables(event_->top5DigiTimeSamples,
			event_->top5DigiPeakSample,
			event_->top5DigiTotal,
			event_->top5DigiR1,
			event_->top5DigiR2,
			event_->top5DigiRPeak,
			event_->top5DigiROuter);
    
  }
  else {
    if (!digisMissing_) {
      edm::LogWarning("MissingProduct") << "HBHEDigiCollection not found.  Branch will not be filled" << std::endl;
      digisMissing_ = true;
    }
  }
  
} // void StoppedHSCPTreeProducer::doTimingFromDigis(const edm::Event& iEvent, const edm::EventSetup& iSetup)



void StoppedHSCPTreeProducer::pulseShapeVariables(const std::vector<double>& samples,
						  unsigned& ipeak,
						  double& total,
						  double& r1,
						  double& r2,
						  double& rpeak,
						  double& router) {

  ipeak = 3;
  total = 0.;
  r1 = 0.;
  r2 = 0.;
  rpeak = 0.;
  router = 0.;

  for (int i=0; i<HBHEDataFrame::MAXSAMPLES; ++i) {
    if (samples.at(i) > samples.at(ipeak)) {
      ipeak = i;
    }
      total += samples.at(i);
  }

  if (total==0.) return;
  
  // R1
  if (ipeak < HBHEDataFrame::MAXSAMPLES-1) {
    if (samples.at(ipeak) > 0.) { 
      r1 = samples.at(ipeak+1) / samples.at(ipeak);
    }
    else r1 = 1.;
  }
  
  // R2
  if (ipeak < HBHEDataFrame::MAXSAMPLES-2) {
    if (samples.at(ipeak+1) > 0. &&
	samples.at(ipeak+1) > samples.at(ipeak+2)) {
      r2 = samples.at(ipeak+2) / samples.at(ipeak+1);
    }
    else r2 = 1.;
  }

  // Rpeak - leading digi
  rpeak = samples.at(ipeak) / total;
  
  // Router - leading digi
  double foursample=0.;
  for (int i=-1; i<3; ++i) {
    if (ipeak+i > 0 && ipeak+i<(int)HBHEDataFrame::MAXSAMPLES) { //JIM:  why is this condition "> 0" and not "> = 0"??
      foursample += samples.at(ipeak+i);
    }
  }
  router = 1. - (foursample / total);
  /*
    //  Dump diagnostic information
  std::cout <<"--------------------"<<std::endl;
  std::cout <<"NOISE SUMMARY OUTPUT"<<std::endl;
  for (uint i=0;i<samples.size();++i)
    std::cout <<samples[i]<<"\t";
  std::cout<<std::endl;
  std::cout <<"total = "<<total<<"  foursample = "<<foursample<<std::endl;
  std::cout <<"ipeak = "<<ipeak<<std::endl;
  if (ipeak<(int)HBHEDataFrame::MAXSAMPLES)
    std::cout <<"Peak value = "<<samples.at(ipeak)<<std::endl;
  else
    std::cout <<"Peak value = N/A"<<std::endl;
  std::cout<<std::endl;
  std::cout <<"R1 = "<<r1<<std::endl;
  std::cout <<"R2 = "<<r2<<std::endl;
  std::cout <<"Router = "<<router<<std::endl;
  std::cout <<"Rpeak = "<<rpeak<<std::endl;
  */ 
}





//define this as a plug-in
DEFINE_FWK_MODULE(StoppedHSCPTreeProducer);
