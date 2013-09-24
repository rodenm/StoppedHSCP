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
// $Id: StoppedHSCPTreeProducer.cc,v 1.47 2013/09/19 20:07:58 rodenm Exp $
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

#include "DataFormats/Common/interface/ConditionsInEdm.h"
#include "DataFormats/Luminosity/interface/LumiDetails.h"
#include "DataFormats/Luminosity/interface/LumiSummary.h"

// L1
#include "CondFormats/L1TObjects/interface/L1GtTriggerMenu.h"
#include "CondFormats/DataRecord/interface/L1GtTriggerMenuRcd.h"
#include "DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerReadoutSetupFwd.h"
#include "DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerReadoutSetup.h"
#include "DataFormats/L1GlobalTrigger/interface/L1GlobalTriggerReadoutRecord.h"
#include "DataFormats/L1Trigger/interface/L1JetParticleFwd.h"
#include "DataFormats/L1Trigger/interface/L1JetParticle.h"

#include "SimDataFormats/GeneratorProducts/interface/HepMCProduct.h"
#include "L1Trigger/GlobalTriggerAnalyzer/interface/L1GtUtils.h"

// HLT
#include "DataFormats/HLTReco/interface/TriggerEvent.h"
#include "DataFormats/HLTReco/interface/TriggerTypeDefs.h"
#include "DataFormats/HLTReco/interface/TriggerObject.h"
#include "DataFormats/Common/interface/TriggerResults.h"
#include "FWCore/Utilities/interface/InputTag.h"

#include "HLTrigger/HLTcore/interface/HLTConfigProvider.h"

// jets
#include "DataFormats/JetReco/interface/CaloJetCollection.h"

#include "JetMETCorrections/Objects/interface/JetCorrector.h"

// muons
#include "DataFormats/MuonReco/interface/MuonFwd.h"
#include "DataFormats/MuonReco/interface/Muon.h"



// Vertices
#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/VertexReco/interface/VertexFwd.h"

// tracks
#include "DataFormats/TrackReco/interface/TrackFwd.h"
#include "DataFormats/TrackReco/interface/Track.h"

#include "TrackingTools/TransientTrack/interface/TransientTrackBuilder.h"
#include "TrackingTools/TransientTrack/interface/TransientTrack.h"
#include "TrackingTools/Records/interface/TransientTrackRecord.h"
#include "TrackingTools/MaterialEffects/interface/PropagatorWithMaterial.h"
#include "MagneticField/Records/interface/IdealMagneticFieldRecord.h"
#include "DataFormats/GeometrySurface/interface/BoundCylinder.h"
#include "DataFormats/GeometrySurface/interface/SimpleCylinderBounds.h"

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
#include "Geometry/CSCGeometry/interface/CSCGeometry.h"
#include "Geometry/CSCGeometry/interface/CSCChamber.h"
#include "Geometry/CSCGeometry/interface/CSCLayer.h"
#include "Geometry/CSCGeometry/interface/CSCLayerGeometry.h"

// DT segments
#include "DataFormats/DTRecHit/interface/DTRecHit1D.h"
#include "DataFormats/DTRecHit/interface/DTRecSegment4D.h"
#include "DataFormats/DTRecHit/interface/DTRecSegment2D.h"
#include "DataFormats/DTRecHit/interface/DTRecHitCollection.h"
#include "DataFormats/DTRecHit/interface/DTRecSegment2DCollection.h"
#include "DataFormats/DTRecHit/interface/DTRecSegment4DCollection.h"
#include "Geometry/DTGeometry/interface/DTChamber.h"
#include "Geometry/DTGeometry/interface/DTLayer.h"
#include "Geometry/DTGeometry/interface/DTGeometry.h"
#include "DataFormats/MuonDetId/interface/DTLayerId.h"
#include "DataFormats/MuonDetId/interface/DTWireId.h"

// RPC hits
#include "DataFormats/RPCRecHit/interface/RPCRecHit.h"
#include "DataFormats/RPCRecHit/interface/RPCRecHitCollection.h"
#include "Geometry/RPCGeometry/interface/RPCGeometry.h"
#include "Geometry/RPCGeometry/interface/RPCChamber.h"

// digis
#include "CalibFormats/HcalObjects/interface/HcalCoderDb.h"
#include "CalibFormats/HcalObjects/interface/HcalCalibrations.h"
#include "CalibFormats/HcalObjects/interface/HcalDbService.h"
#include "CalibFormats/HcalObjects/interface/HcalDbRecord.h"

#include "DataFormats/HcalDigi/interface/HBHEDataFrame.h"
#include "DataFormats/HcalDigi/interface/HcalDigiCollections.h"
#include "DataFormats/HcalDetId/interface/HcalDetId.h"
#include "DataFormats/HcalDetId/interface/HcalSubdetector.h"

// MC
#include "SimGeneral/HepPDTRecord/interface/ParticleDataTable.h"

// ROOT output stuff
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "TH1.h"
#include "TTree.h"
#include "TF1.h"

// Helper classes
#include "StoppedHSCP/Ntuples/interface/LhcFills.h"


// TTree definition
#include "StoppedHSCP/Ntuples/interface/StoppedHSCPEvent.h"


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
  void doJets(const edm::Event&, const edm::EventSetup&);
  void doGlobalCalo(const edm::Event&);
  void doMuons(const edm::Event&);
  void doMuonDTs(const edm::Event&, const edm::EventSetup&);
  void doMuonRPCs(const edm::Event&, const edm::EventSetup&);
  void doVertices(const edm::Event&);
  void doTracks(const edm::Event&, const edm::EventSetup&);
  void doBeamHalo(const edm::Event&);

  // write variables based on HCAL noise summary
  void doHcalNoise(const edm::Event&);
  void fillNoiseObjectTopDigiSamples(shscp::HPD& hpd, std::vector<double>& outvec);
  void fillNoiseObjectTop5DigiSamples(shscp::HPD& hpd, std::vector<double>& outvec);

  // write HCAL RecHits
  void doHcalRecHits(const edm::Event&);
  void doHFRecHits(const edm::Event&);

  // write CSC segments
  void doCscSegments(const edm::Event&, const edm::EventSetup&);
  void doCscHits(const edm::Event&, const edm::EventSetup&);
  void doSlices (const edm::Event& iEvent, const edm::EventSetup& iSetup); 

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

  // job control
  bool isMC_;
  bool doAK5_;
  bool doCaloTowers_;
  bool doRecHits_;
  bool doHFRecHits_;
  bool doCscSegments_;
  bool doCscRecHits_;
  bool doDT_; // muon drift tubes
  bool doRpcRecHits_;

  bool doDigis_;
  bool doHltBit1_;
  bool doHltBit2_;
  bool doHltBit3_;
  bool doHltBit4_;
  bool doHltBit5_;
  bool writeHistos_;
  


  // EDM input tags
  edm::InputTag condInEdmTag_;
  std::string l1JetsTag_;
  edm::InputTag l1BitsTag_;
  std::string l1JetNoBptxName_;
  std::string l1JetNoBptxNoHaloName_;
  std::string l1Jet32NoBptxNoHaloName_;
  std::string l1BptxName_;
  std::string l1MuBeamHaloName_;
  edm::InputTag hltResultsTag_;
  edm::InputTag hltEventTag_;
  std::string hltPathJetNoBptx_;
  std::string hltPathJetNoBptxNoHalo_;
  std::string hltPathJetNoBptx3BXNoHalo_;
  std::string hltPathJetE50NoBptx3BXNoHalo_;
  std::string hltPathJetE70NoBptx3BXNoHalo_;
  edm::InputTag hltL3Tag_;
  edm::InputTag mcTag_;
  std::string mcProducer_;
  edm::InputTag hepProducer_;
  edm::InputTag hepDecayProducer_;
  std::string jetCorrectorServiceName_;
  edm::InputTag jetTag_;
  edm::InputTag jetAK5Tag_;
  edm::InputTag muonTag_;
  edm::InputTag cosmicMuonTag_;
  edm::InputTag verticesTag_;
  edm::InputTag tracksTag_;
  edm::InputTag caloTowerTag_;
  edm::InputTag caloRecHitTag_;
  edm::InputTag hcalNoiseTag_;
  edm::InputTag hcalNoiseFilterResultTag_;
  edm::InputTag rbxTag_;
  edm::InputTag hpdTag_;
  edm::InputTag hcalRecHitTag_;
  edm::InputTag hfRecHitTag_;
  edm::InputTag hcalDigiTag_;
  edm::InputTag cscSegmentsTag_;
  edm::InputTag cscRecHitsTag_;
  edm::InputTag DTRecHitsTag_;
  edm::InputTag DT4DSegmentsTag_;
  edm::InputTag rpcRecHitsTag_;

  // HLT config helper
  HLTConfigProvider hltConfig_;
  unsigned hltPathIndexJetNoBptx_;
  unsigned hltPathIndexJetNoBptxNoHalo_;
  unsigned hltPathIndexJetNoBptx3BXNoHalo_;
  unsigned hltPathIndexJetE50NoBptx3BXNoHalo_;
  unsigned hltPathIndexJetE70NoBptx3BXNoHalo_;

  // geometry
  const CaloGeometry* caloGeom_;

  // HepPDT table
  edm::ESHandle<HepPDT::ParticleDataTable> fPDGTable;

  // cuts
  double towerMinEnergy_;
  double towerMaxEta_;
  double jetMinEnergy_;
  double jetMaxEta_;
  double digiMinFc_;
  double rechitMinEnergy_;	

  // extra "study" jet tower info
  // (These objects are saved for study purposes, but are not used in the analysis)
  double studyJetMinEta_;
  double studyJetMaxEta_;
  double studyTowerMinEta_;
  double studyTowerMaxEta_;

  // Hcal Logical map (ieta-iphi->hardware) object
  HcalLogicalMap* logicalMap_;  
  
  // bad channel status to mask;
  HcalChannelQuality* chanquality_;
  int badchannelstatus_;
  std::set<HcalDetId> badChannels_;

  // boolean for making reduced ntuples
  bool makeReducedNtuples_;

  // LHC Fill structure (temporary until this is available through CMSSW)
  LhcFills fills_;
  unsigned currentFill_;
  unsigned currentFillL1_;
  std::vector<unsigned long> currentColls_;
  std::vector<unsigned long> currentBunches_;

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
  bool tracksMissing_;
  bool cscSegsMissing_;

  std::vector<CaloTowerPtr> jetTowers_;
  std::vector<unsigned> towerJets_;

  std::vector<HcalDetId> hcalDetIds_;
  std::vector<unsigned> hcalDetJets_;

  std::vector<HBHERecHit> recHits_;

  const TransientTrackBuilder    *theTTBuilder_;
  edm::ESHandle<MagneticField>   theMF_;
  TrajectoryStateOnSurface       stateAtHCAL_; 
  mutable PropagatorWithMaterial *forwardPropagator_ ;
  PropagationDirection           dir_;
  BoundCylinder                  *theHCALbarrel_;

};




StoppedHSCPTreeProducer::StoppedHSCPTreeProducer(const edm::ParameterSet& iConfig):
  tree_(0),
  event_(0),
  isMC_(iConfig.getUntrackedParameter<bool>("isMC",false)),
  doAK5_(iConfig.getUntrackedParameter<bool>("doAK5",false)),
  doCaloTowers_(iConfig.getUntrackedParameter<bool>("doCaloTowers",true)),
  doRecHits_(iConfig.getUntrackedParameter<bool>("doRecHits",false)),
  doHFRecHits_(iConfig.getUntrackedParameter<bool>("doHFRecHits",false)),
  doCscSegments_(iConfig.getUntrackedParameter<bool>("doCsc",false)),
  doCscRecHits_(iConfig.getUntrackedParameter<bool>("doCscRecHits",false)),
  doDT_(iConfig.getUntrackedParameter<bool>("doDT",false)),
  doRpcRecHits_(iConfig.getUntrackedParameter<bool>("doRpcRecHits",false)),
  doDigis_(iConfig.getUntrackedParameter<bool>("doDigis",false)),
  doHltBit1_(true),
  doHltBit2_(true),
  doHltBit3_(true),
  doHltBit4_(true),
  doHltBit5_(true),
  writeHistos_(iConfig.getUntrackedParameter<bool>("writeHistos",false)),
  condInEdmTag_(iConfig.getUntrackedParameter<edm::InputTag>("conditionsInEdm",std::string("CondInEdmInputTag"))),
  l1JetsTag_(iConfig.getUntrackedParameter<std::string>("l1JetsTag",std::string("l1extraParticles"))),
  l1BitsTag_(iConfig.getUntrackedParameter<edm::InputTag>("l1BitsTag",edm::InputTag("gtDigis"))),
  l1JetNoBptxName_(iConfig.getUntrackedParameter<std::string>("l1JetNoBptxName",std::string("L1_SingleJet20_NotBptxOR"))),  
  l1JetNoBptxNoHaloName_(iConfig.getUntrackedParameter<std::string>("l1JetNoBptxNoHaloName",std::string("L1_SingleJet20_NotBptxOR_NotMuBeamHalo"))),
  l1Jet32NoBptxNoHaloName_(iConfig.getUntrackedParameter<std::string>("l1Jet32NoBptxNoHaloName",std::string("L1_SingleJet32_NotBptxOR_NotMuBeamHalo"))),
  
  //  l1BptxPlusName_(iConfig.getUntrackedParameter<std::string>("l1BptxPlusName",std::string(""))),  
  //  l1BptxMinusName_(iConfig.getUntrackedParameter<std::string>("l1BptxMinusName",std::string(""))),  
  l1BptxName_(iConfig.getUntrackedParameter<std::string>("l1BptxName",std::string("L1Tech_BPTX_plus_AND_minus"))),  
  l1MuBeamHaloName_(iConfig.getUntrackedParameter<std::string>("l1MuBeamHaloName",std::string("L1_SingleMuBeamHalo"))),  
  hltResultsTag_(iConfig.getUntrackedParameter<edm::InputTag>("hltResultsTag",edm::InputTag("TriggerResults","","HLT"))),
  hltEventTag_(iConfig.getUntrackedParameter<edm::InputTag>("hltEventTag",edm::InputTag("hltTriggerSummaryAOD","","HLT"))),
  hltPathJetNoBptx_(iConfig.getUntrackedParameter<std::string>("hltPathJetNoBptx",std::string("HLT_JetE30_NoBPTX_v1"))),
  hltPathJetNoBptxNoHalo_(iConfig.getUntrackedParameter<std::string>("hltPathJetNoBptxNoHalo",std::string("HLT_JetE30_NoBPTX_NoHalo_v1"))),
  hltPathJetNoBptx3BXNoHalo_(iConfig.getUntrackedParameter<std::string>("hltPathJetNoBptx3BXNoHalo",std::string("HLT_JetE30_NoBPTX3BX_"))),
  hltPathJetE50NoBptx3BXNoHalo_(iConfig.getUntrackedParameter<std::string>("hltPathJetE50NoBptx3BXNoHalo",std::string("HLT_JetE50_NoBPTX3BX_"))),
  hltPathJetE70NoBptx3BXNoHalo_(iConfig.getUntrackedParameter<std::string>("hltPathJetE70NoBptx3BXNoHalo",std::string("HLT_JetE70_NoBPTX3BX_"))),
  hltL3Tag_(iConfig.getUntrackedParameter<edm::InputTag>("hltL3Tag",edm::InputTag("hltStoppedHSCP1CaloJetEnergy","","HLT"))),
  mcTag_(iConfig.getUntrackedParameter<edm::InputTag>("mcTag",edm::InputTag("generator"))),
  mcProducer_ (iConfig.getUntrackedParameter<std::string>("producer", "g4SimHits")),
  hepProducer_ (iConfig.getUntrackedParameter<edm::InputTag>("hepMCProducerTag", edm::InputTag("generator", "", "SIM"))),
  hepDecayProducer_ (iConfig.getUntrackedParameter<edm::InputTag>("hepMCDecayProducerTag", edm::InputTag("generator", "", "HLT"))),
  jetCorrectorServiceName_(iConfig.getUntrackedParameter<std::string>("jetCorrectorServiceName","ic5CaloL1L2L3Residual")),
  jetTag_(iConfig.getUntrackedParameter<edm::InputTag>("jetTag",edm::InputTag("iterativeCone5CaloJets"))),
  jetAK5Tag_(iConfig.getUntrackedParameter<edm::InputTag>("jetAK5Tag",edm::InputTag("ak5CaloJets"))),
  muonTag_(iConfig.getUntrackedParameter<edm::InputTag>("muonTag",edm::InputTag("muons"))),
  cosmicMuonTag_(iConfig.getUntrackedParameter<edm::InputTag>("cosmicMuonTag",edm::InputTag("muonsFromCosmics"))),
  verticesTag_(iConfig.getUntrackedParameter<edm::InputTag>("verticesTag", edm::InputTag("offlinePrimaryVertices"))),
  tracksTag_(iConfig.getUntrackedParameter<edm::InputTag>("tracksTag", edm::InputTag("generalTracks"))),
  caloTowerTag_(iConfig.getUntrackedParameter<edm::InputTag>("caloTowerTag",edm::InputTag("towerMaker"))),
  caloRecHitTag_(iConfig.getUntrackedParameter<edm::InputTag>("caloRecHitTag",edm::InputTag("hbhereco"))),
  hcalNoiseTag_(iConfig.getUntrackedParameter<edm::InputTag>("hcalNoiseTag",edm::InputTag("hcalnoise"))),
  hcalNoiseFilterResultTag_(iConfig.getUntrackedParameter<edm::InputTag>("hcalNoiseFilterResultTag",edm::InputTag("HBHENoiseFilterResultProducer"))),
  rbxTag_(iConfig.getUntrackedParameter<edm::InputTag>("rbxTag",edm::InputTag("hcalnoise"))),
  hpdTag_(iConfig.getUntrackedParameter<edm::InputTag>("hpdTag",edm::InputTag("hcalnoise"))),
  hcalRecHitTag_(iConfig.getUntrackedParameter<edm::InputTag>("hcalRecHitTag",edm::InputTag("hbhereco"))),
  hfRecHitTag_(iConfig.getUntrackedParameter<edm::InputTag>("hfRecHitTag",edm::InputTag("hfreco"))),
  hcalDigiTag_(iConfig.getUntrackedParameter<edm::InputTag>("hcalDigiTag",edm::InputTag("hcalDigis"))),
  cscSegmentsTag_(iConfig.getUntrackedParameter<edm::InputTag>("cscSegmentsTag",edm::InputTag("cscSegments"))),
  cscRecHitsTag_(iConfig.getUntrackedParameter<edm::InputTag>("cscRecHitsTag",edm::InputTag("csc2DRecHits"))), 
  DTRecHitsTag_(iConfig.getUntrackedParameter<edm::InputTag>("DTRecHitsTag",edm::InputTag("dt1DRecHits"))),
  DT4DSegmentsTag_(iConfig.getUntrackedParameter<edm::InputTag>("DT4DSegmentsTag",edm::InputTag("dt4DSegments"))),
  rpcRecHitsTag_(iConfig.getUntrackedParameter<edm::InputTag>("rpcRecHitsTag",edm::InputTag("rpcRecHits"))),

  towerMinEnergy_(iConfig.getUntrackedParameter<double>("towerMinEnergy", 1.)),
  towerMaxEta_(iConfig.getUntrackedParameter<double>("towerMaxEta", 1.3)),
  jetMinEnergy_(iConfig.getUntrackedParameter<double>("jetMinEnergy", 1.)),
  jetMaxEta_(iConfig.getUntrackedParameter<double>("jetMaxEta", 3.)),
  digiMinFc_(iConfig.getUntrackedParameter<double>("digiMinFc", 30)),
  rechitMinEnergy_(iConfig.getUntrackedParameter<double>("rechitMinEnergy", 0.2)),
  studyJetMinEta_(iConfig.getUntrackedParameter<double>("studyJetMinEta",1.3)),
  studyJetMaxEta_(iConfig.getUntrackedParameter<double>("studyJetMaxEta",3.0)),
  studyTowerMinEta_(iConfig.getUntrackedParameter<double>("studyTowerMinEta",1.3)),
  studyTowerMaxEta_(iConfig.getUntrackedParameter<double>("studyTowerMaxEta",3.0)),
  badchannelstatus_(iConfig.getUntrackedParameter<int>("badchannelstatus",0)),
  makeReducedNtuples_(iConfig.getUntrackedParameter<bool>("makeReducedNtuples",false)),
  currentFill_(0),
  currentFillL1_(0),
  currentColls_(0),
  currentBunches_(0),
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
  if (isMC_) log += " mc";
  if (doCaloTowers_) log += " calotowers";
  if (doRecHits_) log += " rechits";

  edm::LogInfo("StoppedHSCPTree") << "Going to fill " << log << std::endl;

  HcalLogicalMapGenerator gen;
  logicalMap_=new HcalLogicalMap(gen.createMap());

  const float epsilon = 0.001;
  Surface::RotationType rot; // unit rotation matrix

  // values taken from CMS NOTE 2005/016
  const float barrelRadius = 287.65;
  const float barrelHalfLength = 433.20;

  theHCALbarrel_ = new BoundCylinder( Surface::PositionType(0,0,0), rot, SimpleCylinderBounds( -epsilon, barrelRadius+epsilon, -barrelHalfLength, barrelHalfLength));

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
  
  std::cout << " l1JetsTag_; " << l1JetsTag_ << std::endl;
  std::cout << " l1BitsTag_; " <<l1BitsTag_ << std::endl;
  std::cout << " l1JetNoBptxName_; " <<  l1JetNoBptxName_ << std::endl;
  std::cout << " l1JetNoBptxNoHaloName_; " << l1JetNoBptxNoHaloName_ << std::endl;
  std::cout << " l1Jet32NoBptxNoHaloName_; " <<  l1Jet32NoBptxNoHaloName_ << std::endl;
  std::cout << " l1BptxName_; " <<  l1BptxName_ << std::endl;
  std::cout << " l1MuBeamHaloName_; " <<  l1MuBeamHaloName_ << std::endl;
  std::cout << " hltResultsTag_; " << hltResultsTag_ << std::endl;
  std::cout << " hltEventTag_; " << hltEventTag_ << std::endl;
  std::cout << " hltPathJetNoBptx_; " << hltPathJetNoBptx_ << std::endl;
  std::cout << " hltPathJetNoBptxNoHalo_; " << hltPathJetNoBptxNoHalo_ << std::endl;
  std::cout << " hltPathJetNoBptx3BXNoHalo_; " << hltPathJetNoBptx3BXNoHalo_ << std::endl;
  std::cout << " hltPathJetE50NoBptx3BXNoHalo_; " << hltPathJetE50NoBptx3BXNoHalo_ << std::endl;
  std::cout << " hltPathJetE70NoBptx3BXNoHalo_; " << hltPathJetE70NoBptx3BXNoHalo_ << std::endl;
  std::cout << " hltL3Tag_; " << hltL3Tag_ << std::endl << std::endl;
  
}

// -- called once per run
void 
StoppedHSCPTreeProducer::beginRun(edm::Run const & iRun, edm::EventSetup const& iSetup)
{
  // Get PDT Table if MC
  if (isMC_)
    iSetup.getData(fPDGTable);

  // HLT setup
  bool changed;
  hltConfig_.init(iRun, iSetup, hltResultsTag_.process(), changed);

  // HLT Path -- No BPTX
  try{
    hltPathIndexJetNoBptx_=(hltConfig_.triggerNames()).size();  // default setting -- trigger not found
    for (uint i=0;i<(hltConfig_.triggerNames()).size();++i) // loop over trigger names
      {
	std::string trigName=hltConfig_.triggerName(i);
	// Search for first occurrence of trigger name -- store vector of all triggers found at some point?
	if (hltPathJetNoBptx_.size()>0 &&
	    trigName.find(hltPathJetNoBptx_)!= std::string::npos)
	  {
	    hltPathIndexJetNoBptx_ = hltConfig_.triggerIndex(trigName); // could just set to i, but let's be careful...
	  }
      }
    if (hltPathIndexJetNoBptx_==(hltConfig_.triggerNames()).size())
      {
	edm::LogWarning("StoppedHSCPTree") << "HLTJetNoBPTX:  Could not find an HLT path matching "<<hltPathJetNoBptx_<<".  Branch will not be filled."<<std::endl;
	doHltBit1_=false;
      }
    else
      edm::LogInfo("StoppedHSCPTree") << hltPathJetNoBptx_ << " index is " << hltPathIndexJetNoBptx_ << std::endl;
  } // end of try loop
  catch (cms::Exception e) {
    edm::LogWarning("StoppedHSCPTree") << "HLTJetNoBPTX:  Could not find an HLT path matching " << hltPathJetNoBptx_ << ".  Branch will not be filled" << std::endl;
    doHltBit1_ = false;
  }
  // HLT Path -- No BPTX, No Halo
  try {
    hltPathIndexJetNoBptxNoHalo_=(hltConfig_.triggerNames()).size();  // default value
    for (uint i=0;i<(hltConfig_.triggerNames()).size();++i)
      {
	std::string trigName=hltConfig_.triggerName(i);
	// Search triggers for NoBpxtNoHalo name
	if (hltPathJetNoBptxNoHalo_.size()>0 &&
	    trigName.find(hltPathJetNoBptxNoHalo_)!= std::string::npos)
	  {
	    hltPathIndexJetNoBptxNoHalo_ = hltConfig_.triggerIndex(trigName); // could just set to i, but let's be careful...
	  }
      }
    if (hltPathIndexJetNoBptxNoHalo_==(hltConfig_.triggerNames()).size())
      {
	edm::LogWarning("StoppedHSCPTree") << "HLTJetNoBPTXNoHalo:  Could not find an HLT path matching "<<hltPathJetNoBptxNoHalo_<<".  Branch will not be filled."<<std::endl;
	doHltBit2_=false;
      }
    else
      edm::LogInfo("StoppedHSCPTree") << hltPathJetNoBptxNoHalo_ << " index is " << hltPathIndexJetNoBptxNoHalo_ << std::endl;
  }
  catch (cms::Exception e) {
    edm::LogWarning("StoppedHSCPTree") << "HLTJetNoBPTXNoHalo:  Could not find an HLT path matching " << hltPathJetNoBptxNoHalo_ << ".  Branch will not be filled" << std::endl;
    doHltBit2_ = false;
  }
  // HLT Path -- No BPTX, No Halo, 3BX
  try {
    hltPathIndexJetNoBptx3BXNoHalo_=(hltConfig_.triggerNames()).size();  // default value
    for (uint i=0;i<(hltConfig_.triggerNames()).size();++i)
      {
	std::string trigName=hltConfig_.triggerName(i);
	// Search for first occurrence of trigger name
	if (hltPathJetNoBptx3BXNoHalo_.size()>0 &&
	    trigName.find(hltPathJetNoBptx3BXNoHalo_)!= std::string::npos)
	  {
	    hltPathIndexJetNoBptx3BXNoHalo_ = hltConfig_.triggerIndex(trigName); // could just set to i, but let's be careful...
	  }
      }
    edm::LogInfo("StoppedHSCPTree") << hltPathJetNoBptx3BXNoHalo_ << " index is " << hltPathIndexJetNoBptx3BXNoHalo_ << std::endl;
    if (hltPathIndexJetNoBptx3BXNoHalo_==(hltConfig_.triggerNames()).size())
      {
	edm::LogWarning("StoppedHSCPTree") << "HLTJetNoBPTX3BXNoHalo:  Could not find an HLT path matching "<<hltPathJetNoBptx3BXNoHalo_<<".  Branch will not be filled."<<std::endl;
	doHltBit3_=false;
      }
    else
      edm::LogInfo("StoppedHSCPTree") << hltPathJetNoBptx3BXNoHalo_ << " index is " << hltPathIndexJetNoBptx3BXNoHalo_ << std::endl;
  }
  catch (cms::Exception e) {
    edm::LogWarning("StoppedHSCPTree") << "HLTJetNoBPTX3BXNoHalo:  Could not find an HLT path matching " << hltPathJetNoBptx3BXNoHalo_ << ".  Branch will not be filled" << std::endl;
    doHltBit3_ = false;
  }
  // HLT Path -- JetE50 No BPTX, No Halo, 3BX
  try {
    hltPathIndexJetE50NoBptx3BXNoHalo_=(hltConfig_.triggerNames()).size();  // default value
    for (uint i=0;i<(hltConfig_.triggerNames()).size();++i)
      {
	std::string trigName=hltConfig_.triggerName(i);
	// Search for first occurrence of trigger name
	if (hltPathJetE50NoBptx3BXNoHalo_.size()>0 &&
	    trigName.find(hltPathJetE50NoBptx3BXNoHalo_)!= std::string::npos)
	  {
	    hltPathIndexJetE50NoBptx3BXNoHalo_ = hltConfig_.triggerIndex(trigName); // could just set to i, but let's be careful...
	  }
      }
    edm::LogInfo("StoppedHSCPTree") << hltPathJetE50NoBptx3BXNoHalo_ << " index is " << hltPathIndexJetE50NoBptx3BXNoHalo_ << std::endl;
    if (hltPathIndexJetE50NoBptx3BXNoHalo_==(hltConfig_.triggerNames()).size())
      {
	edm::LogWarning("StoppedHSCPTree") << "HLTJetE50NoBPTX3BXNoHalo:  Could not find an HLT path matching "<<hltPathJetE50NoBptx3BXNoHalo_<<".  Branch will not be filled."<<std::endl;
	doHltBit4_=false;
      }
    else
      edm::LogInfo("StoppedHSCPTree") << hltPathJetE50NoBptx3BXNoHalo_ << " index is " << hltPathIndexJetE50NoBptx3BXNoHalo_ << std::endl;
  }
  catch (cms::Exception e) {
    edm::LogWarning("StoppedHSCPTree") << "HLTJetE50NoBPTX3BXNoHalo:  Could not find an HLT path matching " << hltPathJetE50NoBptx3BXNoHalo_ << ".  Branch will not be filled" << std::endl;
    doHltBit4_ = false;
  }
  // HLT Path -- JetE70 No BPTX, No Halo, 3BX (new for 2012)
  try {
    hltPathIndexJetE70NoBptx3BXNoHalo_=(hltConfig_.triggerNames()).size();  // default value
    for (uint i=0;i<(hltConfig_.triggerNames()).size();++i)
      {
	std::string trigName=hltConfig_.triggerName(i);
	// Search for first occurrence of trigger name
	if (hltPathJetE70NoBptx3BXNoHalo_.size()>0 &&
	    trigName.find(hltPathJetE70NoBptx3BXNoHalo_)!= std::string::npos)
	  {
	    hltPathIndexJetE70NoBptx3BXNoHalo_ = hltConfig_.triggerIndex(trigName); // could just set to i, but let's be careful...
	  }
      }
    edm::LogInfo("StoppedHSCPTree") << hltPathJetE70NoBptx3BXNoHalo_ << " index is " << hltPathIndexJetE70NoBptx3BXNoHalo_ << std::endl;
    if (hltPathIndexJetE70NoBptx3BXNoHalo_==(hltConfig_.triggerNames()).size())
      {
	edm::LogWarning("StoppedHSCPTree") << "HLTJetE70NoBPTX3BXNoHalo:  Could not find an HLT path matching "<<hltPathJetE70NoBptx3BXNoHalo_<<".  Branch will not be filled."<<std::endl;
	doHltBit5_=false;
      }
    else
      edm::LogInfo("StoppedHSCPTree") << hltPathJetE70NoBptx3BXNoHalo_ << " index is " << hltPathIndexJetE70NoBptx3BXNoHalo_ << std::endl;
  }
  catch (cms::Exception e) {
    edm::LogWarning("StoppedHSCPTree") << "HLTJetE70NoBPTX3BXNoHalo:  Could not find an HLT path matching " << hltPathJetE70NoBptx3BXNoHalo_ << ".  Branch will not be filled" << std::endl;
    doHltBit5_ = false;
  }


  // end of HLT checks

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

  // get ConditionsInRun block
  edm::Handle<edm::ConditionsInRunBlock> condInRunBlock;
  iRun.getByLabel(condInEdmTag_, condInRunBlock);

  if (condInRunBlock.isValid()) {
    currentFillL1_ = condInRunBlock->lhcFillNumber;
  }

  // set filling scheme for this run
  currentColls_ = fills_.getCollisionsFromRun(iRun.runAuxiliary().run());
  currentBunches_ = fills_.getBunchesFromRun(iRun.runAuxiliary().run());
  currentFill_  = fills_.getFillFromRun(iRun.runAuxiliary().run());

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
 
  if (isMC_) doMC(iEvent);
 
  // event & trigger info
  doEventInfo(iEvent);
  doTrigger(iEvent, iSetup);

  // general RECO info
  doJets(iEvent, iSetup);
  doGlobalCalo(iEvent); // uses ntuple calotower info for leadingIphiFractionValue
  doMuons(iEvent);


  doBeamHalo(iEvent);
  doVertices(iEvent);
  doTracks(iEvent, iSetup);

  // HCAL noise summary info
  doHcalNoise(iEvent);

  // HCAL RecHits & flags
  doHcalRecHits(iEvent);
  doHFRecHits(iEvent);

  // CSC segments
  doCscSegments(iEvent, iSetup);
  doCscHits(iEvent, iSetup); 
  doSlices(iEvent, iSetup);  // HE info

  // DT Segments
  doMuonDTs(iEvent,iSetup);

  // RPCs
  doMuonRPCs(iEvent,iSetup);

  // digi based variables
  if (doDigis_) {
    doTimingFromDigis(iEvent, iSetup);
  }
 
  // if making reduced ntuples, return without writing event
  // unless basic selection criteria met
  if (makeReducedNtuples_==true)
    {
      // reject cosmics
      if (event_->mu_N>0)
	return;

      // loose jet cuts
      if ( event_->jet_N==0) 
	return;
      bool passloosejetcut=false;
      for (uint z=0;z<event_->jet_N;++z)
	{
	  if (event_->jetE[z]>=50 && fabs(event_->jetEta[z])<1.3)
	    {
	      passloosejetcut=true;
	      break;
	    }
	}
      if (passloosejetcut==false)
	return;
    } // if (makeReducedNtuples_==true)

  // remove calotowers
  if (!doCaloTowers_)
    event_->removeTowers(); // caloTowers don't need to be saved, unless specified in cfg

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
  }

  // Now fill variables based on the StoppedParticles vectors made by RHStopTracer module
  edm::Handle<std::vector<std::string> > names;
  iEvent.getByLabel (mcProducer_, "StoppedParticlesName", names);
  edm::Handle<std::vector<float> > xs;
  iEvent.getByLabel (mcProducer_, "StoppedParticlesX", xs);
  edm::Handle<std::vector<float> > ys;
  iEvent.getByLabel (mcProducer_, "StoppedParticlesY", ys);
  edm::Handle<std::vector<float> > zs;
  iEvent.getByLabel (mcProducer_, "StoppedParticlesZ", zs);
  edm::Handle<std::vector<float> > times;
  iEvent.getByLabel (mcProducer_, "StoppedParticlesTime", times);
  if (!names.isValid() || !xs.isValid() || !ys.isValid() || !zs.isValid() || !times.isValid()){
    edm::LogWarning ("MissingProduct") << "StoppedParticles* vectors not available. Branch "
				       << "will not be filled." << std::endl;
  } else if (names->size() != xs->size() || xs->size() != ys->size() || ys->size() != zs->size()) {
    edm::LogWarning ("StoppedHSCPTreeProducer") << "mismatch array sizes name/x/y/z:"
						<< names->size() << '/' << xs->size() << '/' 
						<< ys->size() << '/' << zs->size() << std::endl;
  } else {
    if (names->size() > 0) {
      for (size_t i = 0; i < names->size(); ++i) {
	float phi = ((*ys)[i]==0 && (*xs)[i]==0) ? 0 : atan2((*ys)[i],(*xs)[i]);
	
	// TODO: find a way to get the pdgid, mass, and charge of the stopped particle 
	// (the name is not in the ParticleDataTable)
	Double_t mass = -1.0;
	Double_t charge = 99.0;
	Int_t pdgid = 0;
	const HepPDT::ParticleData* PData = fPDGTable->particle(names->at(i));
	if (PData == 0) {
	  LogDebug ("StoppedHSCPTreeProducer") << "could not get particle data from the"
					       << " table for " << names->at(i)
					       << std::endl;
	} else {
	  mass = PData->mass();
	  charge = PData->charge();
	  pdgid = PData->ID().pid();
	}
	event_->mcStoppedParticleName.push_back(names->at(i));
	event_->mcStoppedParticleId.push_back(pdgid);
	event_->mcStoppedParticleX.push_back(xs->at(i));
	event_->mcStoppedParticleY.push_back(ys->at(i));
	event_->mcStoppedParticleZ.push_back(zs->at(i));
	event_->mcStoppedParticleR.push_back(sqrt(xs->at(i)*xs->at(i) + ys->at(i)*ys->at(i)));
	event_->mcStoppedParticlePhi.push_back(phi);
	event_->mcStoppedParticleTime.push_back(times->at(i));
	event_->mcStoppedParticle_N++;
      }
    }
  }

  // Search the stage 1 HepMC records for the initial SUSY particle (gluino, stop, stau...)
  // and for the initial R-hadrons
  edm::Handle<edm::HepMCProduct> hepMCproduct;
  iEvent.getByLabel(hepProducer_, hepMCproduct);
  if (!hepMCproduct.isValid()) {
    edm::LogWarning ("MissingProduct") << "Stage 1 HepMCproduct not found. Branch "
				     << "will not be filled." << std::endl;
  } else {
    const HepMC::GenEvent* mc = hepMCproduct->GetEvent();
    if( mc == 0 ) {
      throw edm::Exception( edm::errors::InvalidReference ) << "HepMC has null pointer "
							    << "to GenEvent" << std::endl;
    }
    // Uncomment this to print the full HepMC record for each event (for debugging or whatever)
    //mc->print( std::cout );
    
    // Iterate over the HepMC particles, look for the sparticles that produce r-hadrons,
    for ( HepMC::GenEvent::particle_const_iterator piter  = mc->particles_begin();
	  piter != mc->particles_end(); 
	  ++piter ) {
      HepMC::GenParticle* p = *piter;
      int partId = fabs(p->pdg_id());
      
      // Search for the original sparticle (gluino, stop - left and right handed, stau)
      // -- Assumes the first two sparticles found are the correct ones to save.
      if ((partId == 1000021 || partId == 1000006 || partId == 2000006 || partId == 1000015 
	   || partId == 2000015) && event_->mcSparticle_N < 2) {
	math::XYZTLorentzVector momentum1(p->momentum().px(),
					  p->momentum().py(),
					  p->momentum().pz(),
					  p->momentum().e());
	Double_t phi = momentum1.phi();
	Double_t pt = momentum1.pt();
	Double_t e = momentum1.e();
	Double_t eta = momentum1.eta();
	Double_t mass = p->momentum().m();
	Double_t charge = 999.0;
	const HepPDT::ParticleData* PData = fPDGTable->particle(HepPDT::ParticleID(p->pdg_id()));
	if(PData==0) {
	  LogDebug ("StoppedHSCPTreeProducer") << "Error getting HepPDT data table for "
					       << p->pdg_id() << ". Unable to fill charge "
					       << "of sparticle." << std::endl;
	} else {
	  charge = PData->charge();
	}
	event_->mcSparticleId.push_back(p->pdg_id());
	event_->mcSparticleMass.push_back(mass);
	event_->mcSparticleCharge.push_back(charge);
	event_->mcSparticlePx.push_back(momentum1.x());
	event_->mcSparticlePy.push_back(momentum1.y());
	event_->mcSparticlePz.push_back(momentum1.z());
	event_->mcSparticlePt.push_back(pt);
	event_->mcSparticleE.push_back(e);
	event_->mcSparticleEta.push_back(eta);
	event_->mcSparticlePhi.push_back(phi);
	event_->mcSparticle_N++;
      }
    
      // I'm making the (possibly invalid) assumption here that R-hadrons all have numbers 
      // between the SUSY particles and 2,000,000. 
      // -- Assumes the first two r-hadrons we come across are the ones we want.
      // -- This branch may not be filled for stau MC.
      else if (partId > 1000100 && partId < 2000000 && event_->mcRhadron_N < 2) {
	math::XYZTLorentzVector momentum1(p->momentum().px(),
					  p->momentum().py(),
					  p->momentum().pz(),
					  p->momentum().e());
	Double_t phi = momentum1.phi();
	Double_t pt = momentum1.pt();
	Double_t e = momentum1.e();
	Double_t eta = momentum1.eta();
	Double_t mass = p->momentum().m();
	Double_t charge = 999.0;
	const HepPDT::ParticleData* PData = fPDGTable->particle(HepPDT::ParticleID(p->pdg_id()));
	if(PData==0) {
	  LogDebug ("StoppedHSCPTreeProducer") << "Error getting HepPDT data table for "
					       << p->pdg_id() << ". Unable to fill charge "
					       << "of rhadron." << std::endl;
	} else {
	  charge = PData->charge();
	}
	event_->mcRhadronId.push_back(p->pdg_id());
	event_->mcRhadronMass.push_back(mass);
	event_->mcRhadronCharge.push_back(charge);
	event_->mcRhadronPx.push_back(momentum1.x());
	event_->mcRhadronPy.push_back(momentum1.y());
	event_->mcRhadronPz.push_back(momentum1.z());
	event_->mcRhadronPt.push_back(pt);
	event_->mcRhadronE.push_back(e);
	event_->mcRhadronEta.push_back(eta);
	event_->mcRhadronPhi.push_back(phi);
	event_->mcRhadron_N++; 
      }
    }  
  }
  // Search the stage 1 HepMC records for the initial SUSY particle (gluino, stop, stau...)
  // and for the initial R-hadrons
  edm::Handle<edm::HepMCProduct> hepMCDecayproduct;
  iEvent.getByLabel(hepDecayProducer_, hepMCDecayproduct);
  if (!hepMCDecayproduct.isValid()) {
    edm::LogWarning ("MissingProduct") << "Stage 1 HepMC decay product not found. Branch "
				     << "will not be filled." << std::endl;
  } else {
    const HepMC::GenEvent* mc = hepMCDecayproduct->GetEvent();
    if( mc == 0 ) {
      throw edm::Exception( edm::errors::InvalidReference ) << "HepMC has null pointer "
							    << "to GenEvent" << std::endl;
    }
    // Uncomment this to print the full HepMC record for each event (for debugging or whatever)
    //mc->print( std::cout );
    
    // Iterate over the HepMC particles, look for the sparticles that produce r-hadrons,
    for ( HepMC::GenEvent::particle_const_iterator piter  = mc->particles_begin();
	  piter != mc->particles_end(); 
	  ++piter ) {
      HepMC::GenParticle* p = *piter;
      int partId = fabs(p->pdg_id());
      
      // Save information about the daughter decay particles
      int targetId = 0;
      if (event_->mcSparticle_N == 0) {
	LogDebug ("StoppedHSCPTreeProducer") << "mcSparticle branch not filled. Cannot fill "
					     << "mcDaughter branch."
					     << std::endl;
	continue;
      } else {
	targetId = event_->mcSparticleId[0]%100;
      }

      if ((partId == targetId) && event_->mcDaughter_N < 1) {
	math::XYZTLorentzVector momentum1(p->momentum().px(),
					  p->momentum().py(),
					  p->momentum().pz(),
					  p->momentum().e());
	Double_t phi = momentum1.phi();
	Double_t pt = momentum1.pt();
	Double_t e = momentum1.e();
	Double_t eta = momentum1.eta();
	Double_t mass = p->momentum().m();
	Double_t charge = 999.0;
	const HepPDT::ParticleData* PData = fPDGTable->particle(HepPDT::ParticleID(p->pdg_id()));
	if(PData==0) {
	  LogDebug ("StoppedHSCPTreeProducer") << "Error getting HepPDT data table for "
					       << p->pdg_id() << ". Unable to fill charge "
					       << "of particle." << std::endl;
	} else {
	  charge = PData->charge();
	}
	event_->mcDaughterId.push_back(p->pdg_id());
	event_->mcDaughterMass.push_back(mass);
	event_->mcDaughterCharge.push_back(charge);
	event_->mcDaughterPx.push_back(momentum1.x());
	event_->mcDaughterPy.push_back(momentum1.y());
	event_->mcDaughterPz.push_back(momentum1.z());
	event_->mcDaughterPt.push_back(pt);
	event_->mcDaughterE.push_back(e);
	event_->mcDaughterEta.push_back(eta);
	event_->mcDaughterPhi.push_back(phi);
	event_->mcDaughter_N++;
      }
      // Store info about the first two neutralinos seen
      // -- Assumes the first neutralino we come across is the ones we want.
      else if (partId == 1000022 && event_->mcNeutralino_N < 1) {
	math::XYZTLorentzVector momentum1(p->momentum().px(),
					  p->momentum().py(),
					  p->momentum().pz(),
					  p->momentum().e());
	Double_t phi = momentum1.phi();
	Double_t pt = momentum1.pt();
	Double_t e = momentum1.e();
	Double_t eta = momentum1.eta();
	Double_t mass = p->momentum().m();
	Double_t charge = 999.0;
	const HepPDT::ParticleData* PData = fPDGTable->particle(HepPDT::ParticleID(p->pdg_id()));
	if(PData==0) {
	  LogDebug ("StoppedHSCPTreeProducer") << "Error getting HepPDT data table for "
					       << p->pdg_id() << ". Unable to fill charge "
					       << "of neutralino." << std::endl;
	} else {
	  charge = PData->charge();
	}
	event_->mcNeutralinoId.push_back(p->pdg_id());
	event_->mcNeutralinoMass.push_back(mass);
	event_->mcNeutralinoCharge.push_back(charge);
	event_->mcNeutralinoPx.push_back(momentum1.x());
	event_->mcNeutralinoPy.push_back(momentum1.y());
	event_->mcNeutralinoPz.push_back(momentum1.z());
	event_->mcNeutralinoPt.push_back(pt);
	event_->mcNeutralinoE.push_back(e);
	event_->mcNeutralinoEta.push_back(eta);
	event_->mcNeutralinoPhi.push_back(phi);
	event_->mcNeutralino_N++; 
      }
    }  
  }
}

void StoppedHSCPTreeProducer::doEventInfo(const edm::Event& iEvent) {

  unsigned long orbitsPerLB = 1<<18;
  unsigned long bxPerOrbit  = 3564;
  unsigned long nsPerBx     = 25;

  unsigned long id          = iEvent.id().event();
  unsigned long bx          = iEvent.bunchCrossing();
  unsigned long orbit       = iEvent.orbitNumber();
  unsigned long lb          = iEvent.luminosityBlock();
  unsigned long run         = iEvent.id().run();
  unsigned long fill        = fills_.getFillFromRun(run);

  double time               = iEvent.time().unixTime(); // .value() which is in units of I have no fucking clue.
  std::cout << "Time: " << time <<std::endl;

  // calculate event time from run start + LS, orbit, BX
  ULong64_t bxSinceRunStart = (((lb * orbitsPerLB) + orbit) * bxPerOrbit) + bx;
  

  // find last/next collisions
  int bxAfter = 9999;
  int bxBefore = -9999;
  
  if (! isMC_) {
    int bxLast=-1;
    int bxNext=-1;
    if (currentColls_.size() > 0) {
      // special case if event is before first collision
      if (bx <= currentColls_.at(0)) {
	bxLast   = currentColls_.at(currentColls_.size() - 1);
	bxNext   = currentColls_.at(0);
	bxAfter  = (bx + bxPerOrbit) - bxLast;
	bxBefore = bx - bxNext;
	
	//std::cout << bx << " : " << bxLast << " : " << bxNext << " : " << bxAfter << " : " << bxBefore << std::endl;

      }
      // special case if event is after last collision
      else if (bx > currentColls_.at(currentColls_.size() - 1)) {
	bxLast   = currentColls_.at(currentColls_.size()-1);
	bxNext   = currentColls_.at(0);
	bxAfter  = bx - bxLast;
	bxBefore = (bx - bxPerOrbit) - bxNext;

	//std::cout << bx << " : " << bxLast << " : " << bxNext << " : " << bxAfter << " : " << bxBefore << std::endl;
      }
      // general case
      else {      
	for (unsigned c=0; c<(currentColls_.size()-1) && currentColls_.at(c)<bx; ++c) {
	  bxLast = currentColls_.at(c);
	  bxNext = currentColls_.at(c+1);
	  bxAfter = bx - bxLast;
	  bxBefore = bx - bxNext;
	}
	//std::cout << bx << " : " << bxLast << " : " << bxNext << " : " << bxAfter << " : " << bxBefore << std::endl;
      }
    }
    
  }

  // compute relative BX
  int bxWrt    = ( abs(bxAfter) <= abs(bxBefore) ? bxAfter : bxBefore );
  
  // find last/next bunch
  int bxAfterBunch = 9999;
  int bxBeforeBunch = -9999;
  
  if (! isMC_) {
    int bxLast=-1;
    int bxNext=-1;
    if (currentBunches_.size() > 0) {
      // special case if event is before first collision
      if (bx <= currentBunches_.at(0)) {
	bxLast   = currentBunches_.at(currentBunches_.size() - 1);
	bxNext   = currentBunches_.at(0);
	bxAfterBunch  = (bx + bxPerOrbit) - bxLast;
	bxBeforeBunch = bx - bxNext;
	
	//std::cout << bx << " : " << bxLast << " : " << bxNext << " : " << bxAfter << " : " << bxBefore << std::endl;

      }
      // special case if event is after last collision
      else if (bx > currentBunches_.at(currentBunches_.size() - 1)) {
	bxLast   = currentBunches_.at(currentBunches_.size()-1);
	bxNext   = currentBunches_.at(0);
	bxAfterBunch  = bx - bxLast;
	bxBeforeBunch = (bx - bxPerOrbit) - bxNext;

	//	std::cout << bx << " : " << bxLast << " : " << bxNext << " : " << bxAfter << " : " << bxBefore << std::endl;
      }
      // general case
      else {      
	for (unsigned c=0; c<(currentBunches_.size()-1) && currentBunches_.at(c)<bx; ++c) {
	  bxLast = currentBunches_.at(c);
	  bxNext = currentBunches_.at(c+1);
	  bxAfterBunch = bx - bxLast;
	  bxBeforeBunch = bx - bxNext;
	}
      }
    }
    
  }

  // compute relative BX
  int bxWrtBunch    = ( abs(bxAfterBunch) <= abs(bxBeforeBunch) ? bxAfterBunch : bxBeforeBunch );
  /**
  std::cout << "bxAfterCollision = " << bxAfter
  	    <<"\nbxBeforeCollision = "<< bxBefore
  	    <<"\nbxWrtCollision = "<< bxWrt
  	    <<"\nbxAfterBunch = "<< bxAfterBunch
  	    <<"\nbxBeforeBunch = "<< bxBeforeBunch
  	    <<"\nbxWrtBunch = "<< bxWrtBunch
  	    << std::endl;
  */

  // set variables in ntuple
  event_->id = id;
  event_->bx = bx;
  event_->orbit = orbit;
  event_->lb = lb;
  event_->run = run;
  event_->fill = fill;
  event_->fillFromL1 = currentFillL1_;
  event_->time = time;
  event_->time2 = iEvent.getRun().beginTime().value() + (bxSinceRunStart * nsPerBx);  // value() in nanoseconds!?!
  event_->bxAfterCollision = bxAfter;
  event_->bxBeforeCollision = bxBefore;
  event_->bxWrtCollision = bxWrt;
  event_->bxAfterBunch = bxAfterBunch;
  event_->bxBeforeBunch = bxBeforeBunch;
  event_->bxWrtBunch = bxWrtBunch;


  // Get luminosity and intensity info from LumiDetails. 
  // NOTE: luminosity values are calibrated but uncorrected
  // see also: https://twiki.cern.ch/twiki/bin/view/CMS/LumiCalc#LumiDetails
  edm::Handle<LumiDetails> lumiDetails;
  iEvent.getLuminosityBlock().getByLabel("lumiProducer",lumiDetails); 

  edm::Handle<LumiSummary> lumiSummary;
  iEvent.getLuminosityBlock().getByLabel("lumiSummary",lumiSummary); 
  
  if (!lumiDetails.isValid()) {
    edm::LogWarning("MissingProduct") << "Could not retreive LumiDetails collection for " 
				    << event_->run << ":" << event_->lb << ":" << event_->id
				    <<std::endl;
    return; 
  } else if (!lumiDetails->isValid()) {
    edm::LogWarning("doEventInfo()") << "LumiDetails collection invalid (empty) for "
						   << event_->run << ":" << event_->lb << ":" 
						   << event_->id << std::endl;
    return;
  }


  if (!lumiDetails.isValid()) {
    edm::LogError("MissingProduct") << "Could not retreive LumiDetails collection for " 
				    << event_->run << ":" << event_->lb << ":" << event_->id
				    <<std::endl;
    return; 
  } else if (!lumiDetails->isValid()) {
    edm::LogWarning("doEventInfo()") << "LumiDetails collection invalid (empty) for "
						   << event_->run << ":" << event_->lb << ":" 
						   << event_->id << std::endl;
    return;
  }

  if (!lumiSummary.isValid()) {
    edm::LogError("MissingProduct") << "Could not retreive LumiSummary collection for " 
				    << event_->run << ":" << event_->lb << ":" << event_->id
				    <<std::endl;
    return; 
  } else if (!lumiSummary->isValid()) {
    edm::LogWarning("doEventInfo()") << "LumiSummary collection invalid (empty) for "
						   << event_->run << ":" << event_->lb << ":" 
						   << event_->id << std::endl;
    return;
  }

  // debugging
  //std::cout << "Lumi version: " << lumiDetails->lumiVersion() << std::endl;
  bool debug = false;
  if (bx < 4 || bx > 3560) {
    std::cout << "\nEvent " << event_->run << ":" << event_->lb << ":" << event_->id
	      << "\nbx = " << bx 
	      << "\n==================================" << std::endl;
    debug = true;
  }

  for (int i = -2; i < 3; i++) {
    int iBx = bx + i;
    if ( iBx < 0 ) iBx += bxPerOrbit;
    if ( iBx > (int)bxPerOrbit-1) iBx -= bxPerOrbit;
    if (debug) std::cout << iBx << "\t";
    
    Double_t lumiByBx = lumiDetails->lumiValue(LumiDetails::kOCC1,iBx)*6.37;
    Double_t beam1Intensity = lumiDetails->lumiBeam1Intensity(iBx);
    Double_t beam2Intensity = lumiDetails->lumiBeam2Intensity(iBx);
    //std::cout << "...Retreived details" << std::endl;

    event_->beam1Intensity.at(i+2) = beam1Intensity;
    event_->beam2Intensity.at(i+2) = beam2Intensity;
    event_->lumiByBx.at(i+2) = lumiByBx;
    //std::cout << "...Saved details" << std::endl;    
  } 

  // Get average instantaneous luminosity delivered for this LS
  event_->lsLuminosity = lumiSummary->avgInsDelLumi();
  event_->lsLuminosityErr = lumiSummary->avgInsDelLumiErr();

  if (debug) {
    std::cout<<std::endl;
    std::cout<<"  x\tbeam1I\tbeam2I\tlumiByBx(ub^-1 s^-1)\n" 
	     <<" ------------------------------------------------------------------- "
	     << std::endl;
    for (int x=0; x<5; x++) {
      std::cout << "  " << x 
		<< "\t" << event_->beam1Intensity.at(x)
		<< "\t" << event_->beam2Intensity.at(x)
		<< "\t" << event_->lumiByBx.at(x)
		<< std::endl;
    }
  }
}
  

void StoppedHSCPTreeProducer::doTrigger(const edm::Event& iEvent, const edm::EventSetup& iSetup) {

  // get GT data
  edm::ESHandle<L1GtTriggerMenu> menuRcd;
  iSetup.get<L1GtTriggerMenuRcd>().get(menuRcd) ;
  const L1GtTriggerMenu* menu = menuRcd.product();
  
  edm::Handle<L1GlobalTriggerReadoutRecord> gtReadoutRecord;
  iEvent.getByLabel(l1BitsTag_, gtReadoutRecord);

  // L1 trigger bits (for triggered BX)
  uint64_t gtAlgoWord0(0), gtAlgoWord1(0), gtTechWord(0);

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

  // Get prescale information
  L1GtUtils* l1gtutils = new L1GtUtils();
  l1gtutils->retrieveL1EventSetup(iSetup);
  l1gtutils->getL1GtRunCache(iEvent, iSetup, true, false); // TODO: if this works, move to beginRun?

  int errorAlgo=0;
  int errorTech=0;

  //Are Algo and Trigger prescale indices supposed to be the same?  Save them separately, for now
  event_->algoTriggerPrescaleIndex =l1gtutils->prescaleFactorSetIndex(iEvent,L1GtUtils::AlgorithmTrigger,errorAlgo);
  event_->techTriggerPrescaleIndex =l1gtutils->prescaleFactorSetIndex(iEvent,L1GtUtils::TechnicalTrigger,errorTech);
  if (errorAlgo!=0) {
    event_->algoTriggerPrescaleIndex=-999;
    edm::LogError ("StoppedHSCPTreeProducer") << "Error retreiving algo trigger prescale index: " 
					 << errorAlgo << std::endl;
  }
  if (errorTech!=0) {
    event_->techTriggerPrescaleIndex=-999;
    edm::LogError ("StoppedHSCPTreeProducer") << "Error retreiving tech trigger prescale index: " 
					 << errorTech << std::endl;
  }

  event_->gtAlgoWord0 = gtAlgoWord0;
  event_->gtAlgoWord1 = gtAlgoWord1;
  event_->gtTechWord = gtTechWord;
  
  // Get prescales for individual L1 triggers
  
  int errorCode=0;

  // L1GtUtils::prescaleFactor() - line 1300
  // L1GtUtils::l1Results()      - line 1146 - sets tags m_provL1GtRecordInputTag and calls...
  // L1GtUtils::l1Results()      - line 679 
  event_->l1JetNoBptxPrescale = l1gtutils->prescaleFactor(iEvent,
							  l1JetNoBptxName_,
							  errorCode);
  if (errorCode!=0) {
    event_->l1JetNoBptxPrescale=-999;
    edm::LogWarning ("StoppedHSCPTreeProducer") << "Error retreiving l1JetNoBptxPrescale factor: " 
					 << errorCode << std::endl;
  }
  
  event_->l1JetNoBptxNoHaloPrescale = l1gtutils->prescaleFactor(iEvent,
								l1JetNoBptxNoHaloName_,
								errorCode);
  if (errorCode!=0) {
    event_->l1JetNoBptxNoHaloPrescale=-999;
    edm::LogWarning ("StoppedHSCPTreeProducer") << "Error retreiving l1JetNoBptxNoHaloPrescale factor: " 
					 << errorCode << std::endl;
  }

  event_->l1Jet32NoBptxNoHaloPrescale = l1gtutils->prescaleFactor(iEvent,
								  l1Jet32NoBptxNoHaloName_,
								  errorCode);
  if (errorCode!=0) {
    event_->l1Jet32NoBptxNoHaloPrescale=-999;
    edm::LogWarning ("StoppedHSCPTreeProducer") << "Error retreiving l1Jet32NoBptxNoHaloPrescale factor: " 
					 << errorCode << std::endl;
  }

  // L1 trigger bits for -2..+2 BX
  int start = -2;
  int end = 3;
  if (isMC_) {  // don't loop over multiple BX for MC
    start=0;
    end=1;
  }
  for (int bx=start; bx<end; ++bx) {

    const DecisionWord decisionWord = gtReadoutRecord->decisionWord(bx);
    const TechnicalTriggerWord technicalWord = gtReadoutRecord->technicalTriggerWord(bx);

    bool l1JetNoBptx       = menu->gtAlgorithmResult(l1JetNoBptxName_,       decisionWord);
    bool l1JetNoBptxNoHalo = menu->gtAlgorithmResult(l1JetNoBptxNoHaloName_, decisionWord);
    bool l1Jet32NoBptxNoHalo = menu->gtAlgorithmResult(l1Jet32NoBptxNoHaloName_, decisionWord);
    bool l1Bptx            = technicalWord.at(1);
    bool l1MuBeamHalo      = menu->gtAlgorithmResult(l1MuBeamHaloName_,      decisionWord);

    event_->l1JetNoBptx.at(bx+2)       = (l1JetNoBptx ? 1 : 0);
    event_->l1JetNoBptxNoHalo.at(bx+2) = (l1JetNoBptxNoHalo ? 1 : 0);
    event_->l1Jet32NoBptxNoHalo.at(bx+2) = (l1Jet32NoBptxNoHalo ? 1 : 0);

    //     event_->l1BptxPlus.at(bx+2)        = l1BptxPlus;
    //     event_->l1BptxMinus.at(bx+2)       = l1BptxMinus;
    event_->l1Bptx.at(bx+2)            = (l1Bptx ? 1 : 0);
    event_->l1MuBeamHalo.at(bx+2)      = (l1MuBeamHalo ? 1 : 0);
    
  }
  
  // HLT config setup
  // moved to beginRun()
  bool hltBitJetNoBptx(false), 
    hltBitJetNoBptxNoHalo(false), 
    hltBitJetNoBptx3BXNoHalo(false), 
    hltBitJetE50NoBptx3BXNoHalo(false), 
    hltBitJetE70NoBptx3BXNoHalo(false);

  // get HLT results
  edm::Handle<edm::TriggerResults> HLTR;
  iEvent.getByLabel(hltResultsTag_, HLTR);

  if (HLTR.isValid()) {
    // triggerIndex must be less than the size of HLTR or you get a CMSException: _M_range_check
    if (doHltBit1_ && hltPathIndexJetNoBptx_ < HLTR->size()) hltBitJetNoBptx = HLTR->accept(hltPathIndexJetNoBptx_);
    if (doHltBit2_ && hltPathIndexJetNoBptxNoHalo_ < HLTR->size()) hltBitJetNoBptxNoHalo = HLTR->accept(hltPathIndexJetNoBptxNoHalo_); 
    if (doHltBit3_ && hltPathIndexJetNoBptx3BXNoHalo_ < HLTR->size()) hltBitJetNoBptx3BXNoHalo = HLTR->accept(hltPathIndexJetNoBptx3BXNoHalo_); 
    if (doHltBit4_ && hltPathIndexJetE50NoBptx3BXNoHalo_ < HLTR->size()) hltBitJetE50NoBptx3BXNoHalo = HLTR->accept(hltPathIndexJetE50NoBptx3BXNoHalo_); 
    if (doHltBit5_ && hltPathIndexJetE70NoBptx3BXNoHalo_ < HLTR->size()) hltBitJetE70NoBptx3BXNoHalo = HLTR->accept(hltPathIndexJetE70NoBptx3BXNoHalo_); 
  }
  else {
    if (doHltBit1_) edm::LogWarning("MissingProduct") << "HLT information not found for HltBit1.  Branch will not be filled" << std::endl;
    if (doHltBit2_) edm::LogWarning("MissingProduct") << "HLT information not found for HltBit2.  Branch will not be filled" << std::endl;
    if (doHltBit3_) edm::LogWarning("MissingProduct") << "HLT information not found for HltBit3.  Branch will not be filled" << std::endl;
    if (doHltBit4_) edm::LogWarning("MissingProduct") << "HLT information not found for HltBit4.  Branch will not be filled" << std::endl;
    if (doHltBit5_) edm::LogWarning("MissingProduct") << "HLT information not found for HltBit5.  Branch will not be filled" << std::endl;
    doHltBit1_ = false;
    doHltBit2_ = false;
    doHltBit3_ = false;
    doHltBit4_ = false;
    doHltBit5_ = false;
  }

  // store bits
  event_->hltJetNoBptx = hltBitJetNoBptx;
  event_->hltJetNoBptxNoHalo = hltBitJetNoBptxNoHalo;
  event_->hltJetNoBptx3BXNoHalo = hltBitJetNoBptx3BXNoHalo;
  event_->hltJetE50NoBptx3BXNoHalo = hltBitJetE50NoBptx3BXNoHalo;
  event_->hltJetE70NoBptx3BXNoHalo = hltBitJetE70NoBptx3BXNoHalo;
  
  // Store HLT prescale info
  event_->hltPrescaleIndex=hltConfig_.prescaleSet(iEvent, iSetup);
  event_->hltJetNoBptxPrescale=hltConfig_.prescaleValue(iEvent, iSetup, hltPathJetNoBptx_);
  event_->hltJetNoBptxNoHaloPrescale=hltConfig_.prescaleValue(iEvent, iSetup, hltPathJetNoBptxNoHalo_);
  event_->hltJetNoBptx3BXNoHaloPrescale=hltConfig_.prescaleValue(iEvent, iSetup, hltPathJetNoBptx3BXNoHalo_);
  event_->hltJetE50NoBptx3BXNoHaloPrescale=hltConfig_.prescaleValue(iEvent, iSetup, hltPathJetE50NoBptx3BXNoHalo_);
  event_->hltJetE70NoBptx3BXNoHaloPrescale=hltConfig_.prescaleValue(iEvent, iSetup, hltPathJetE70NoBptx3BXNoHalo_);
  

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

  //std::cout <<"hltEventTag = "<<hltEventTag_<<std::endl;
  iEvent.getByLabel(hltEventTag_, trgEvent);

  // for Stopped HSCP L3 filter  
  if (trgEvent.isValid()) {

    const unsigned int filterIndex (trgEvent->filterIndex(hltL3Tag_) );

    //   edm::LogInfo("StoppedHSCP") << "Debugging HLT...  StoppedHSCP index=" << filterIndex 
    //				     << ",  N paths=" << trgEvent->sizeFilters() << std::endl;
    
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
    //else {
    //  edm::LogError("StoppedHSCPTreeProducer") << "Bad hltL3Tag. L3 filter index could not be found: "
    //					       << hltL3Tag_ << std::endl;
    //}

  }
  else {
    if (!hltJetsMissing_) edm::LogWarning("MissingProduct") << "TriggerEvent not found.  Branch will not be filled" << std::endl;
    hltJetsMissing_ = true;
  }
							       
}



void StoppedHSCPTreeProducer::doJets(const edm::Event& iEvent, const edm::EventSetup& iSetup) {

  const JetCorrector* jetCorrector = JetCorrector::getJetCorrector(jetCorrectorServiceName_,iSetup);

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
       if (it->energy() > jetMinEnergy_) {

	 edm::RefToBase<reco::Jet> jetRef(edm::Ref<reco::CaloJetCollection>(caloJets,njet));  
	 double scale = jetCorrector->correction(*it,jetRef,iEvent,iSetup);

	 // store jet in TTree
	 shscp::Jet jet;
	 jet.e = it->energy();
	 jet.e_corr = it->energy()*scale;
	 jet.et = it->et();
	 jet.et_corr = it->et()*scale;
	 jet.eta = it->eta();
	 jet.phi = it->phi();
	 jet.eEm = it->emEnergyInEB();
	 jet.eHad = it->hadEnergyInHB();
	 jet.eMaxEcalTow = it->maxEInEmTowers();
	 jet.eMaxHcalTow = it->maxEInHadTowers();
	 jet.n60 = it->n60();
	 jet.n90 = it->n90();
	 jet.etaMean = it->etaPhiStatistics().etaMean;
	 jet.phiMean = it->etaPhiStatistics().phiMean;
	 jet.etaetaMoment = it->etaPhiStatistics().etaEtaMoment;
	 jet.phiphiMoment = it->etaPhiStatistics().phiPhiMoment;
	 jet.etaphiMoment = it->etaPhiStatistics().etaPhiMoment;

	 // Add to default jet collection and/or to studyJet collection
	 if ((fabs(it->eta()) < jetMaxEta_))
	   event_->addJet(jet);
	 if (fabs(it->eta())>=studyJetMinEta_ && 
	     fabs(it->eta())<studyJetMaxEta_)
	   event_->addStudyJet(jet);
	   // 	 std::cout << "Jet " << std::endl;
// 	 std::cout << "   E=" << it->energy() << " eta=" << it->eta() << " phi=" << it->phi() << std::endl;
	 // get towers
	 
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

	     // Always add tower, if within appropriate eta bounds
	     // (if doCaloTowers_==false, tower will be removed
	     //  via removeTowers after leadingIPhiFractionValue computed)
	     if (fabs(tower->eta()) < towerMaxEta_) 
	       event_->addTower(tow);

	     // only add "studyTower" if doCaloTowers_==true
	     if (doCaloTowers_ && 
		 fabs(tower->eta())>=studyTowerMinEta_ && 
		 fabs(it->eta())<studyTowerMaxEta_)
	       event_->addStudyTower(tow);
	     // 	   std::cout << "  Calo tower" << std::endl;
	     // 	   std::cout << "    eta=" << tower->eta() << " phi=" << tower->phi() << std::endl;
	     // 	   std::cout << "    ECAL E=" << tower->emEnergy() << " HCAL E=" << tower->hadEnergy() << std::endl;
	     // 	   std::cout << "    ECAL time : " << tower->ecalTime() << std::endl;
	     // 	   std::cout << "    HCAL time : " << tower->hcalTime() << std::endl;
	     
	   }
	 } // loop over nconstituents
       } // if (it->energy>jetMinEnergy_)
     } // loop over jets
   } // if (caloJets.isValid())
   else {
     if (!jetsMissing_) edm::LogWarning("MissingProduct") << "CaloJets not found.  Branch will not be filled" << std::endl;
     jetsMissing_ = true;
   }
 
   edm::Handle<CaloJetCollection> ak5Jets;
   iEvent.getByLabel(jetAK5Tag_, ak5Jets);
   
   if (ak5Jets.isValid()) {

     // sort jets by energy
     std::vector<CaloJet> jets;
     jets.insert(jets.end(), ak5Jets->begin(), ak5Jets->end());
     std::sort(jets.begin(), jets.end(), jete_gt() );

     for(CaloJetCollection::const_iterator it=jets.begin(); 
	 it!=jets.end();
	 ++it) {

       //       edm::RefToBase<reco::Jet> jetRef(edm::Ref<reco::CaloJetCollection>(ak5Jets,njet));  
       //       double scale = caloJetCorrector->correction(*it,jetRef,iEvent,iSetup);
       
       if (it->energy() > jetMinEnergy_) { 
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

	 if (fabs(it->eta()) < jetMaxEta_)
	   event_->addAK5Jet(jet);
	 if (fabs(it->eta())>=studyJetMinEta_ && 
	     fabs(it->eta())<studyJetMaxEta_)
	   event_->addAK5StudyJet(jet);
       }
     }
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
      mu.type = (0xff & it->type());

      mu.numChambers = it->numberOfChambers();
      mu.numChambersNoRPC = it->numberOfChambersNoRPC();
      mu.numMatches = it->numberOfMatches();
      mu.numStations = it->numberOfMatchedStations();
      mu.stationMask = it->stationMask();

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
      mu.type = (0xff & it->type())<<8;

      mu.numChambers = it->numberOfChambers();
      mu.numChambersNoRPC = it->numberOfChambersNoRPC();
      mu.numMatches = it->numberOfMatches();
      mu.numStations = it->numberOfMatchedStations();
      mu.stationMask = it->stationMask();

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
	event_->vtx_N++;
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



void StoppedHSCPTreeProducer::doTracks(const edm::Event& iEvent, const edm::EventSetup& iSetup) {

  edm::Handle<reco::TrackCollection> recoTracks;
  iEvent.getByLabel(tracksTag_, recoTracks);
 
  edm::ESHandle<TransientTrackBuilder> builder;
  iSetup.get<TransientTrackRecord>().get("TransientTrackBuilder",builder);
  theTTBuilder_ = builder.product();
  iSetup.get<IdealMagneticFieldRecord>().get(theMF_); 
  

  TrackCollection::const_iterator trk;
  for (trk=recoTracks->begin(); trk!=recoTracks->end(); ++trk) {
    shscp::Track track;
    track.chi2  = trk->chi2();
    track.ndof  = trk->ndof();
    track.nHits = trk->numberOfValidHits();
    track.nLost = trk->numberOfLostHits();
    track.p     = trk->p();

    reco::TrackBase::TrackQuality q = reco::TrackBase::qualityByName("highPurity");
    track.quality = (trk->quality(q) ? 1 : 0);

//     bool muontrackavailable = false;
//     edm::Ref<TrackCollection> muontrack = (&*it)->globalTrack();
//     if (muontrack.isNonnull()) { 
//       muontrackavailable = true; 
//     } 
//     else {
//       muontrack = (&*it)->innerTrack();
//       if (muontrack.isNonnull()) { 
// 	muontrackavailable = true; 
//       } 
//       else {
// 	muontrack = (&*it)->outerTrack();
// 	if (muontrack.isNonnull()) { 
// 	  muontrackavailable = true; 
// 	}
//       }
//     }
    
//     if (muontrackavailable) {

    // This doesn't work -- causes occasional crashes.  Jeff, Jan 27.
    /*
    TransientTrack theTransientTrack = theTTBuilder_->build(&*trk);
    const TrajectoryStateOnSurface myTSOS = theTransientTrack.innermostMeasurementState();
    if ( myTSOS.isValid() ) { 
      stateAtHCAL_= forwardPropagator_->propagate( myTSOS, *theHCALbarrel_ );
      if (stateAtHCAL_.isValid()) {
	track.hcalEta = stateAtHCAL_.globalDirection().eta();
	track.hcalPhi = stateAtHCAL_.globalDirection().phi();
      } 
    } 
    */
    event_->addTrack(track);
  }

}


void StoppedHSCPTreeProducer::doMuonDTs(const edm::Event& iEvent,const edm::EventSetup& iSetup ) 
{
  if (doDT_==false) return;
  
  edm::ESHandle<DTGeometry> dtGeom;
  iSetup.get<MuonGeometryRecord>().get(dtGeom);

  edm::Handle<DTRecSegment4DCollection> all4DSegments;
  iEvent.getByLabel(DT4DSegmentsTag_, all4DSegments);
  edm::Handle<DTRecHitCollection> dtRecHits;
  iEvent.getByLabel(DTRecHitsTag_,dtRecHits);

  int nsegments=0; // count total number of segments

  // loop over each DT chamber
  DTRecSegment4DCollection::id_iterator chamberId;
  for (chamberId = all4DSegments->id_begin();
       chamberId != all4DSegments->id_end();
       ++chamberId)
    {
      const DTChamber* chamber = dtGeom->chamber(*chamberId); 

      DTRecSegment4DCollection::range  range = all4DSegments->get(*chamberId);
      int nchamberseg=0;

      // loop over all segments in chamber
      for (DTRecSegment4DCollection::const_iterator segment4D = range.first;
	   segment4D!=range.second;
	   ++segment4D)
	{
	  // skip invalid values

	  if((*chamberId).station() != 4 && 
	     (*segment4D).dimension() != 4) continue;
	  if((*chamberId).station() == 4 && 
	     (*segment4D).dimension() != 2) continue;

	  ++nchamberseg;

	  const GeomDet* gdet=dtGeom->idToDet(segment4D->geographicalId());
	  const BoundPlane& DTSurface = gdet->surface();
	  LocalPoint segmentLocal = (*segment4D).localPosition();
	  GlobalPoint segmentGlobal = DTSurface.toGlobal(segmentLocal);

	  LocalVector segmentLocalDir   = (*segment4D).localDirection();
	  GlobalVector segmentGlobalDir = DTSurface.toGlobal(segmentLocalDir);

	  // TODO: add DTSegment direction variables.


	  shscp::DTSegment dt;
	  dt.wheel=(chamber->id()).wheel();
	  dt.station=(chamber->id()).station();
	  dt.sector=(chamber->id()).sector();
	  dt.localX=segmentLocal.x();
	  dt.localY=segmentLocal.y();
	  dt.x=segmentGlobal.x();
	  dt.y=segmentGlobal.y();
	  dt.r=sqrt(segmentGlobal.x()*segmentGlobal.x() + segmentGlobal.y()*segmentGlobal.y());
	  dt.z=segmentGlobal.z();
	  dt.rho=segmentGlobal.perp();
	  dt.phi=segmentGlobal.phi();
	  dt.xdir=segmentGlobalDir.x();
	  dt.ydir=segmentGlobalDir.y();
	  dt.phidir=segmentGlobalDir.phi();
	  dt.zdir=segmentGlobalDir.z();
	  event_->addDTSegment(dt);
	}
      nsegments+=nchamberseg;
    }

} // void StoppedHSCPTreeProducer::doMuonDTs


void StoppedHSCPTreeProducer::doMuonRPCs(const edm::Event& iEvent,const edm::EventSetup& iSetup )
{
  if (!doRpcRecHits_) return;
  //Jeff
  edm::Handle<RPCRecHitCollection> hits;
  iEvent.getByLabel(rpcRecHitsTag_, hits);
  edm::ESHandle<RPCGeometry> rpcGeom;
  iSetup.get<MuonGeometryRecord>().get(rpcGeom);
  
  //int nRecHits = hits->size();
  int iHit = 0;
  RPCRecHitCollection::const_iterator rpcIter;
  for (rpcIter = hits->begin(); rpcIter != hits->end(); ++rpcIter) {
    ++iHit;
    const RPCDetId detId = static_cast<const RPCDetId>(rpcIter->rpcId());
    const RPCRoll* roll = dynamic_cast<const RPCRoll*>(rpcGeom->roll(detId));
    const GlobalPoint rhitglobal = roll->toGlobal(rpcIter->localPosition());

    shscp::RpcHit h;
    h.x = rhitglobal.x();
    h.y = rhitglobal.y();
    h.r = sqrt(rhitglobal.x()*rhitglobal.x() + rhitglobal.y()*rhitglobal.y());
    h.z = rhitglobal.z();
    h.rho = rhitglobal.perp();
    h.phi = rhitglobal.phi();
    h.region = detId.region();
    event_->addRpcHit (h);
  } // loop on rpc hits

} // void StoppedHSCPTreeProducer::doMuonRPCs

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
  event_->leadingIPhiFractionValue=0;

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
    } // loop on caloTowers
    event_->leadingIPhiFractionValue=event_->leadingIPhiFraction();
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


/// fill HF rec hit 
void
StoppedHSCPTreeProducer::doHFRecHits(const edm::Event& iEvent)
{

  // get the rechits (to select digis ordered by energy)
  edm::Handle<HFRecHitCollection> recHits;
  iEvent.getByLabel(hfRecHitTag_, recHits);

  // copy rechits to internal vector
  if(recHits.isValid()) {

    unsigned count=0;
    
    for (HFRecHitCollection::const_iterator it=recHits->begin();
	 it!=recHits->end() && count<1000;
	 ++it) {

      // reject bad status rechits from collection      
//       if (std::find(badChannels_.begin(),
// 		    badChannels_.end(),
// 		    it->id())!=badChannels_.end()) {
// 	continue;
//       }

      GlobalPoint pos = caloGeom_->getPosition(it->detid());
      
      // store E sums for HF+ and HF-
      if (pos.eta()> 0. && it->energy() > rechitMinEnergy_ ) {
	event_->hfPlusTotalE += it->energy();
      }
      if (pos.eta()<0. && it->energy() > rechitMinEnergy_ ) {
	event_->hfMinusTotalE += it->energy();
      }

      if (doHFRecHits_ && it->energy() > rechitMinEnergy_ ) {

	shscp::RecHit rh;
	
	rh.e = it->energy();
	rh.time  = it->time();
	rh.eta   = pos.eta();
	rh.phi   = pos.phi();
	rh.ieta  = it->id().ieta();
	rh.iphi  = it->id().iphi();
	rh.depth = it->id().depth();
	event_->addHFRecHit(rh);

	count++;

      }      
    }

  }
  else {
    if (!rechitsMissing_) edm::LogWarning("MissingProduct") << "CaloRecHits not found.  Branches will not be filled" << std::endl;
    rechitsMissing_ = true;
  }

}


void StoppedHSCPTreeProducer::doCscSegments(const edm::Event& iEvent, const edm::EventSetup& iSetup) {

  // get the segments
  edm::Handle<CSCSegmentCollection> segments;
  iEvent.getByLabel(cscSegmentsTag_, segments);

  // Get the geometry :
  edm::ESHandle<CSCGeometry> cscGeom;
  iSetup.get<MuonGeometryRecord>().get(cscGeom);

  if (doCscSegments_) {

    // write segment info to ntuple
    if(segments.isValid()) {
      
      unsigned i=0;
      for (CSCSegmentCollection::const_iterator seg=segments->begin();
	   seg!=segments->end() && i<1000;
	   ++seg, ++i) {
	
	/// code taken from RecoLocalMuon/CSCValidation/src/CSCValidation.cc
	CSCDetId id  = (CSCDetId)seg->cscDetId();
	LocalPoint localPos = seg->localPosition();
	LocalVector segDir = seg->localDirection();
	GlobalPoint globalPos = cscGeom->chamber(id)->toGlobal(localPos);
	GlobalVector globalVec = cscGeom->chamber(id)->toGlobal(segDir);
	//float chisq    = seg->chi2();
	//int nDOF       = 2*nhits-4;
	//double chisqProb = ChiSquaredProbability( (double)chisq, nDOF );
	//float segX     = localPos.x();
	//float segY     = localPos.y();
	//double theta   = segDir.theta();
	
	shscp::CscSegment s;
	s.endcap = id.endcap();
	s.ring = id.ring();
	s.station = id.station();
	s.chamber = id.chamber();
	s.nHits = seg->nRecHits();
	s.phi = globalPos.phi();
	s.z = globalPos.z();
	s.r = sqrt((globalPos.x()*globalPos.x()) + (globalPos.y()*globalPos.y()));
	s.dirTheta = globalVec.theta();
	s.dirPhi = globalVec.phi();
	s.time   = seg->time();
	
	event_->addCscSegment(s);
      }
      
    }
    else {
      if (!cscSegsMissing_) edm::LogWarning("MissingProduct") << "CSC Segments not found.  Branches will not be filled" << std::endl;
      cscSegsMissing_ = true;
    }
  }

} // doCscSegments

void StoppedHSCPTreeProducer::doCscHits(const edm::Event& iEvent, const edm::EventSetup& iSetup) {
  if (!doCscRecHits_) return;
  
  edm::Handle<CSCRecHit2DCollection> hits;
  iEvent.getByLabel(cscRecHitsTag_, hits);
  edm::ESHandle<CSCGeometry> cscGeom;
  iSetup.get<MuonGeometryRecord>().get(cscGeom);
  
  //int nRecHits = hits->size();
  int iHit = 0;
  CSCRecHit2DCollection::const_iterator dRHIter;
  for (dRHIter = hits->begin(); dRHIter != hits->end(); dRHIter++) {
    iHit++;
    CSCDetId idrec = (CSCDetId)(*dRHIter).cscDetId();
    // Following variables aren't yet used:
    //int kEndcap  = idrec.endcap();
    //int kRing    = idrec.ring();
    //int kStation = idrec.station();
    //int kChamber = idrec.chamber();
    //int kLayer   = idrec.layer();
    const CSCLayer* csclayer = cscGeom->layer( idrec );
    LocalPoint rhitlocal = (*dRHIter).localPosition();
    GlobalPoint rhitglobal= csclayer->toGlobal(rhitlocal);
    shscp::CscHit h;
    h.z = rhitglobal.z();
    h.rho = rhitglobal.perp();
    h.phi = rhitglobal.phi();
    h.time = dRHIter->tpeak();
    event_->addCscHit (h);
  }
} //doCscHits

void StoppedHSCPTreeProducer::doSlices (const edm::Event& iEvent, const edm::EventSetup& iSetup) {
  edm::Handle<CaloTowerCollection> towers;
  iEvent.getByLabel(caloTowerTag_, towers);
  for (int iPhi = 0; iPhi < 36; ++ iPhi) {
    int iAntiPhi = iPhi - 18;
    if (iAntiPhi < 0) iAntiPhi += 36;
    double phi = iPhi < 18 ? 3.1415/18.*(iPhi + 0.5) : 3.1415/18.*(iPhi -36 + 0.5);
    double energyPlus = 0;
    double antienergyPlus = 0;
    double energyMinus = 0;
    double antienergyMinus = 0;
    double energy = 0;
    double antienergy = 0;
    for (size_t itower = 0; itower < towers->size(); ++itower) {
      const CaloTower& tower = (*towers)[itower];
      CaloTowerDetId id = tower.id();
      if (id.ietaAbs() >= 17 && id.ietaAbs() <= 24) { // HE in front of HB
	if (id.iphi() > iPhi*2 && id.iphi() <= (iPhi+1)*2) {
	  if (id.zside() > 0) energyPlus += tower.hadEnergy();
	  else energyMinus += tower.hadEnergy();
	  energy += tower.hadEnergy();
	}
	else if (id.iphi() > iAntiPhi*2 && id.iphi() <= (iAntiPhi+1)*2) {
	  if (id.zside() > 0) antienergyPlus += tower.hadEnergy();
	  else antienergyMinus += tower.hadEnergy();
	  antienergy += tower.hadEnergy();
	}
      }
    }
    event_->addHePlus (energyPlus,  antienergyPlus, phi);
    event_->addHeMinus (energyMinus,  antienergyMinus, phi);
    event_->addHe (energy,  antienergy, phi);
  }
} // doSlices
  
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
