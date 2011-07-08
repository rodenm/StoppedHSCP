#ifndef StoppedHSCPEvent_h
#define StoppedHSCPEvent_h

// -*- C++ -*-
//
// Package:    StoppedHSCP/Analysis
// Class:      StoppedHSCPEvent
// 
/**\class StoppedHSCPEvent StoppedHSCPEvent.h StoppedHSCP/Analysis/interface/StoppedHSCPEvent.h

 Description: Defines the Stopped HSCP TTree

 Implementation:

*/
//
// Original Author:  Jim Brooke
// $Id: StoppedHSCPEvent.h,v 1.2 2011/06/29 23:32:49 temple Exp $
//
//

#include "TObject.h"

#include <vector>
#include <functional>

//#include "boost/cstdint.hpp"

namespace shscp {

  // structs are not part of persistency layer
  // just maintained for interface with other code
    
  struct MCDecay {
  MCDecay() : pdgId(0),vtxX(0.),vtxY(0.),vtxZ(0.),vtxT(0.),e(0.),px(0.),py(0.),pz(0.),pt(0.) { }
    unsigned pdgId;
    double vtxX;
    double vtxY;
    double vtxZ;
    double vtxR;
    double vtxT;
    double e;
    double px;
    double py;
    double pz;
    double pt;
  };
  
  struct TrigJet {
    TrigJet() : type(0), e(0.), et(0.), eta(0.), phi(0.) { }
    unsigned type;   // 0 - L1 jet, 1 - L1 tau, 2, HLT jet
    double e;
    double et;
    double eta;
    double phi;
  };

  struct Jet {
    Jet() : e(0.),et(0.),eta(0.),phi(0.),eHad(0.),eEm(0.),eMaxEcalTow(0.),eMaxHcalTow(0.),n60(0),n90(0),n90Hits(0),fHPD(0.),
	    r1(0.),r2(0.),rp(0.),ro(0.),r1_top5(0.),r2_top5(0.),rp_top5(0.),ro_top5(0.) { }
    double e;
    double et;
    double eta;
    double phi;
    double eHad;
    double eEm;
    double eMaxEcalTow;
    double eMaxHcalTow;
    unsigned n60;
    unsigned n90;
    unsigned n90Hits;
    double fHPD;
    double r1;
    double r2;
    double rp;
    double ro;
    double r1_top5;
    double r2_top5;
    double rp_top5;
    double ro_top5;
  };
  
  struct Muon {
  Muon() : pt(0.),eta(0.),phi(0.),hcalEta(0.),hcalPhi(0.) { }
    unsigned type;        // type of muon (standalone/global/cosmic/regular)
    double pt;
    double eta;
    double phi;
    double hcalEta;     // track intersection with HCAL front-face (?)
    double hcalPhi;
  };  

  struct HPD {
  HPD() : id(0),eta(0),phi(0),totalZeros(0),maxZeros(0),nJet(0),
      fc0(0.), fc1(0.), fc2(0.), fc3(0.), fc4(0.), fc5(0.), fc6(0.), fc7(0.), fc8(0.), fc9(0.),
      fc5_0(0.), fc5_1(0.), fc5_2(0.), fc5_3(0.), fc5_4(0.), fc5_5(0.), fc5_6(0.), fc5_7(0.), fc5_8(0.), fc5_9(0.) { }
    unsigned id;
    double eta;
    double phi;
    unsigned totalZeros;
    unsigned maxZeros;
    unsigned nJet;
    double fc0, fc1, fc2, fc3, fc4, fc5, fc6, fc7, fc8, fc9;  // ROOT screws up an array :-(
    double fc5_0, fc5_1, fc5_2, fc5_3, fc5_4, fc5_5, fc5_6, fc5_7, fc5_8, fc5_9;
  };

  struct Tower {
    Tower() : e(0.),et(0.),eta(0.),phi(0.),ieta(0),iphi(0),nJet(0),eHad(0.),etHad(0.),eEm(0.),etEm(0.) { }
    double e;
    double et;
    double eta;
    double phi;
    int ieta;
    int iphi;
    unsigned nJet;
    double eHad;
    double etHad;
    double eEm;
    double etEm;
  };
  
  struct RecHit {
    RecHit() : e(0.),time(0.), flags(0), aux(0), eta(0.),phi(0.),ieta(0),iphi(0),depth(0), RBXindex(0), RMindex(0) { }
    double e;
    double time;
    unsigned flags;
    unsigned aux;
    double eta;
    double phi;
    int ieta;
    int iphi;
    int depth;
    int RBXindex;
    int RMindex;
  };

  struct CscSegment {
    CscSegment() : endcap(0), ring(0), station(0), chamber(0), nHits(0), phi(0.), z(0.), r(0.), dirPhi(0.), dirTheta(0.) { }
    int endcap;
    int ring;
    int station;
    int chamber;
    int nHits;
    double phi;
    double z;
    double r;
    double dirPhi;
    double dirTheta;
  };

  // functor for ordering towers
  struct tow_gt : public std::binary_function<shscp::Tower, shscp::Tower, bool> {
    bool operator()(const shscp::Tower& x, const shscp::Tower& y) {
      return x.e > y.e;
    }
  };

}

class StoppedHSCPEvent : public TObject {
 public:
  
  enum { MAX_N_JETS=20 };
  enum { MAX_N_TOWERS=100 };
  enum { MAX_N_HPDS=10 };
  //  enum { MAX_N_DIGIS=100 };

 public:

  StoppedHSCPEvent();
  ~StoppedHSCPEvent();

  void addMCDecay(shscp::MCDecay d);
  void addL1Jet(shscp::TrigJet j);
  void addHltJet(shscp::TrigJet j);
  void addJet(shscp::Jet j);
  void addStudyJet(shscp::Jet j);
  void addAK5Jet(shscp::Jet j);
  void addAK5StudyJet(shscp::Jet j);
  void addMuon(shscp::Muon m);
  void addHPD(shscp::HPD h);
  void addTower(shscp::Tower t);
  void addStudyTower(shscp::Tower t);
  void addRecHit(shscp::RecHit r);
  void addHFRecHit(shscp::RecHit r);
  void addCscSegment(shscp::CscSegment s);

  // utils
  void Dump();
  
  // jet leading iphi fraction
  double leadingIPhiFraction() const;
  
  // 
  unsigned jetCaloTowers() const;
    
  
 public:  // data
  
  //MC
  unsigned rHadPdgId;
  double rHadVtxX;
  double rHadVtxY;
  double rHadVtxZ;
  double rHadVtxR;
  double rHadVtxT;
  double rHadE;
  double rHadPx;
  double rHadPy;
  double rHadPz;
  double rHadPt;

  // MC decay products
  unsigned mc_N;
  std::vector<UInt_t> mcPDGid;
  std::vector<Double_t> mcVtxX;
  std::vector<Double_t> mcVtxY;
  std::vector<Double_t> mcVtxZ;
  std::vector<Double_t> mcVtxR;
  std::vector<Double_t> mcVtxT;
  std::vector<Double_t> mcE;
  std::vector<Double_t> mcPx;
  std::vector<Double_t> mcPy;
  std::vector<Double_t> mcPz;
  std::vector<Double_t> mcPt;

  // event
  ULong_t id;
  ULong_t bx;
  ULong_t orbit;
  ULong_t lb;
  ULong_t run;
  ULong_t fill;
  ULong_t fillFromL1;
  ULong64_t time;   // timestamp from EvF
  ULong64_t time2;  // calculated from run start + L1 counters for LS, orbit, BX
  ULong64_t time3;  // timestamp from LHC info in L1 data
  Long_t bxAfterCollision;
  Long_t bxBeforeCollision;
  Long_t bxWrtCollision;
  Long_t bxAfterBunch;
  Long_t bxBeforeBunch;
  Long_t bxWrtBunch;

  // trigger
  ULong64_t gtAlgoWord0;
  ULong64_t gtAlgoWord1;
  ULong64_t gtTechWord;
  std::vector<UInt_t> l1JetNoBptx;
  std::vector<UInt_t> l1JetNoBptxNoHalo;
  std::vector<UInt_t> l1Jet32NoBptxNoHalo;

  std::vector<UInt_t> l1Bptx;
  std::vector<UInt_t> l1MuBeamHalo;

  bool hltJetNoBptx;
  bool hltJetNoBptxNoHalo;
  bool hltJetNoBptx3BXNoHalo;
  bool hltJetE50NoBptx3BXNoHalo;

  // Add prescales
  Int_t algoTriggerPrescaleIndex;
  Int_t techTriggerPrescaleIndex;
  Int_t hltPrescaleIndex;

  Int_t l1JetNoBptxPrescale;
  Int_t l1JetNoBptxNoHaloPrescale;
  Int_t l1Jet32NoBptxNoHaloPrescale;

  Int_t hltJetNoBptxPrescale;
  Int_t hltJetNoBptxNoHaloPrescale;
  Int_t hltJetNoBptx3BXNoHaloPrescale;
  Int_t hltJetE50NoBptx3BXNoHaloPrescale;

  // trigger jets
  unsigned l1Jet_N;
  std::vector<UInt_t> l1JetType;
  std::vector<Double_t> l1JetE;
  std::vector<Double_t> l1JetEt;
  std::vector<Double_t> l1JetEta;
  std::vector<Double_t> l1JetPhi;

  unsigned hltJet_N;
  std::vector<UInt_t> hltJetType;
  std::vector<Double_t> hltJetE;
  std::vector<Double_t> hltJetEt;
  std::vector<Double_t> hltJetEta;
  std::vector<Double_t> hltJetPhi;

  // reco jets
  unsigned jet_N;
  std::vector<Double_t> jetE;
  std::vector<Double_t> jetEt;
  std::vector<Double_t> jetEta;
  std::vector<Double_t> jetPhi;
  std::vector<Double_t> jetEHad;
  std::vector<Double_t> jetEEm;
  std::vector<Double_t> jetEMaxEcalTow;
  std::vector<Double_t> jetEMaxHcalTow;
  std::vector<UInt_t> jetN60;
  std::vector<UInt_t> jetN90;
  std::vector<Double_t> jetFHPD;
  std::vector<UInt_t> jetN90Hits;

  // reco jets used for studies only
  unsigned studyJet_N;
  std::vector<Double_t> studyJetE;
  std::vector<Double_t> studyJetEt;
  std::vector<Double_t> studyJetEta;
  std::vector<Double_t> studyJetPhi;
  std::vector<Double_t> studyJetEHad;
  std::vector<Double_t> studyJetEEm;
  std::vector<Double_t> studyJetEMaxEcalTow;
  std::vector<Double_t> studyJetEMaxHcalTow;
  std::vector<UInt_t> studyJetN60;
  std::vector<UInt_t> studyJetN90;
  std::vector<Double_t> studyJetFHPD;
  std::vector<UInt_t> studyJetN90Hits;


  // AK5 jets
  unsigned jetAK5_N;
  std::vector<Double_t> jetAK5E;
  std::vector<Double_t> jetAK5Et;
  std::vector<Double_t> jetAK5Eta;
  std::vector<Double_t> jetAK5Phi;
  std::vector<Double_t> jetAK5EHad;
  std::vector<Double_t> jetAK5EEm;
  std::vector<Double_t> jetAK5EMaxEcalTow;
  std::vector<Double_t> jetAK5EMaxHcalTow;
  std::vector<UInt_t> jetAK5N60;
  std::vector<UInt_t> jetAK5N90;
  std::vector<Double_t> jetAK5FHPD;
  std::vector<UInt_t> jetAK5N90Hits;

 // AK5 jets used for studies only
  unsigned studyJetAK5_N;
  std::vector<Double_t> studyJetAK5E;
  std::vector<Double_t> studyJetAK5Et;
  std::vector<Double_t> studyJetAK5Eta;
  std::vector<Double_t> studyJetAK5Phi;
  std::vector<Double_t> studyJetAK5EHad;
  std::vector<Double_t> studyJetAK5EEm;
  std::vector<Double_t> studyJetAK5EMaxEcalTow;
  std::vector<Double_t> studyJetAK5EMaxHcalTow;
  std::vector<UInt_t> studyJetAK5N60;
  std::vector<UInt_t> studyJetAK5N90;
  std::vector<Double_t> studyJetAK5FHPD;
  std::vector<UInt_t> studyJetAK5N90Hits;


  // reco muons
  unsigned mu_N;
  std::vector<UInt_t> muType;        // type of muon (standalone/global/cosmic/regular)
  std::vector<Double_t> muPt;
  std::vector<Double_t> muEta;
  std::vector<Double_t> muPhi;
  std::vector<Double_t> muHcalEta;     // track intersection with HCAL front-face (?)
  std::vector<Double_t> muHcalPhi;

  // vertices
  unsigned nVtx;
  unsigned vtx_N;
  std::vector<UInt_t> vtxNDOF;
  std::vector<Double_t> vtxZ;
  std::vector<Double_t> vtxRho;

  // tracks
  unsigned track_N;

  // Beam Halo data
  bool beamHalo_CSCTight;
  bool beamHalo_CSCLoose;
  bool beamHalo_HcalTight;
  bool beamHalo_HcalLoose;

  // global calo quantities
  unsigned nTowerSameiPhi;
  double leadingIPhiFractionValue;
  unsigned nTowerLeadingIPhi;
  double eHadLeadingIPhi;
  double hfPlusTotalE;
  double hfMinusTotalE;

  // noise summary data
  double noiseMinE2Over10TS;
  double noiseMaxE2Over10TS;
  int noiseMaxHPDHits;
  int noiseMaxRBXHits;
  int noiseMaxHPDNoOtherHits;
  int noiseMaxZeros;
  double noiseMin25GeVHitTime;
  double noiseMax25GeVHitTime;
  double noiseMinRBXEMF;
  bool noiseFilterResult;
  
  float noiseEventEMEnergy;
  float noiseEventHadEnergy;
  float noiseEventTrackEnergy;
  int noiseNumProblematicRBXs;

  // NoiseSummary pulse shape variables
  std::vector<double> topHPD5TimeSamples;
  unsigned topHPD5PeakSample;
  double   topHPD5Total;
  double   topHPD5R1;
  double   topHPD5R2;
  double   topHPD5RPeak;
  double   topHPD5ROuter;

  // HPDs identified by noise summary algos
  unsigned hpd_N;
  std::vector<UInt_t> hpdId;
  std::vector<Double_t> hpdEta;
  std::vector<Double_t> hpdPhi;
  std::vector<UInt_t> hpdTotalZeros;
  std::vector<UInt_t> hpdMaxZeros;
  std::vector<UInt_t> hpdNJet;
  std::vector<Double_t> hpdFc0, hpdFc1, hpdFc2, hpdFc3, hpdFc4, hpdFc5, hpdFc6, hpdFc7, hpdFc8, hpdFc9;
  std::vector<Double_t> hpdFc5_0, hpdFc5_1, hpdFc5_2, hpdFc5_3, hpdFc5_4, hpdFc5_5, hpdFc5_6, hpdFc5_7, hpdFc5_8, hpdFc5_9;

  // calo towers
  unsigned tower_N;
  std::vector<Double_t> towerE;
  std::vector<Double_t> towerEt;
  std::vector<Double_t> towerEta;
  std::vector<Double_t> towerPhi;
  std::vector<Int_t> towerIEta;
  std::vector<Int_t> towerIPhi;
  std::vector<UInt_t> towerNJet;
  std::vector<Double_t> towerEHad;
  std::vector<Double_t> towerEtHad;
  std::vector<Double_t> towerEEm;
  std::vector<Double_t> towerEtEm;

  // calo towers used only for study purposes
  unsigned studyTower_N;
  std::vector<Double_t> studyTowerE;
  std::vector<Double_t> studyTowerEt;
  std::vector<Double_t> studyTowerEta;
  std::vector<Double_t> studyTowerPhi;
  std::vector<Int_t> studyTowerIEta;
  std::vector<Int_t> studyTowerIPhi;
  std::vector<UInt_t> studyTowerNJet;
  std::vector<Double_t> studyTowerEHad;
  std::vector<Double_t> studyTowerEtHad;
  std::vector<Double_t> studyTowerEEm;
  std::vector<Double_t> studyTowerEtEm;

  // calo rechits
  unsigned recHit_N;
  std::vector<Double_t> recHitE;
  std::vector<Double_t> recHitTime;
  std::vector<UInt_t> recHitFlags;
  std::vector<UInt_t> recHitAux;
  std::vector<Double_t> recHitEta;
  std::vector<Double_t> recHitPhi;
  std::vector<Int_t> recHitIEta;
  std::vector<Int_t> recHitIPhi;
  std::vector<Int_t> recHitDepth;
  std::vector<Int_t> recHitRBXindex;
  std::vector<Int_t> recHitRMindex;

  // HF Rec Hits
  unsigned hfRecHit_N;
  std::vector<Double_t> hfRecHitE;
  std::vector<Double_t> hfRecHitTime;
  std::vector<Double_t> hfRecHitEta;
  std::vector<Double_t> hfRecHitPhi;
  std::vector<Int_t> hfRecHitIEta;
  std::vector<Int_t> hfRecHitIPhi;
  std::vector<Int_t> hfRecHitDepth;

  // CSC segments
  unsigned cscSeg_N;
  std::vector<Int_t> cscSegEndcap;
  std::vector<Int_t> cscSegRing;
  std::vector<Int_t> cscSegStation;
  std::vector<Int_t> cscSegChamber;
  std::vector<UInt_t> cscSegNHits;
  std::vector<Double_t> cscSegPhi;
  std::vector<Double_t> cscSegZ;
  std::vector<Double_t> cscSegR;
  std::vector<Double_t> cscSegDirPhi;
  std::vector<Double_t> cscSegDirTheta;

  // digi pulse shape variables
  int leadingDigiIEta;
  int leadingDigiIPhi;
  std::vector<double> leadingDigiTimeSamples;
  unsigned leadingDigiPeakSample;
  double leadingDigiTotal;
  double leadingDigiR1;
  double leadingDigiR2;
  double leadingDigiRPeak;
  double leadingDigiROuter;
  std::vector<double> top5DigiTimeSamples;
  unsigned top5DigiPeakSample;
  double top5DigiTotal;
  double top5DigiR1;
  double top5DigiR2;
  double top5DigiRPeak;
  double top5DigiROuter;


  ClassDef(StoppedHSCPEvent,17); // version 17:  includes leadingIPhiFractionValue

};

#endif
