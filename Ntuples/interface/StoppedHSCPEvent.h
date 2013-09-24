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
// $Id: StoppedHSCPEvent.h,v 1.29 2013/09/19 20:07:58 rodenm Exp $
//
//

#include "TObject.h"
#include "TString.h"
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
	    r1(0.),r2(0.),rp(0.),ro(0.),r1_top5(0.),r2_top5(0.),rp_top5(0.),ro_top5(0.),etaMean(0.),phiMean(0.),
	    etaetaMoment(0.),phiphiMoment(0.),etaphiMoment(0.) { }
    double e;
    double e_corr;
    double et;
    double et_corr;
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
    double etaMean;
    double phiMean;
    double etaetaMoment;
    double phiphiMoment;
    double etaphiMoment;

  };
  
  struct Muon {
    Muon() : pt(0.),eta(0.),phi(0.),hcalEta(0.),hcalPhi(0.),numChambers(0),
	     numChambersNoRPC(0),numMatches(0),numStations(0),stationMask(0) { }
    unsigned type;        // type of muon (standalone/global/cosmic/regular)
    double pt;
    double eta;
    double phi;
    double hcalEta;     // track intersection with HCAL front-face (?)
    double hcalPhi;
    int numChambers;
    int numChambersNoRPC;
    int numMatches;
    int numStations;
    unsigned stationMask;
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
    CscSegment() : endcap(0), ring(0), station(0), chamber(0), nHits(0), phi(0.), z(0.), r(0.), dirPhi(0.), dirTheta(0.), time(0) { }
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
    double time;
  };


  struct CscHit {
    CscHit() : z(0), rho(0), phi(0) {}
    double z;
    double rho;
    double phi;
    double time;
  }; 

  struct DTSegment{
    DTSegment(): wheel(0),station(0),sector(0),
		 localX(0.),localY(0.),
		 x(0), y(0), r(0),
		 z(0.),rho(0.),phi(0.),
		 xdir(0),ydir(0),phidir(0),zdir(0){}
    int wheel;
    int station;
    int sector;
    double localX; 
    double localY;
    double x;
    double y;
    double r;
    double z;
    double rho;
    double phi;
    double xdir;
    double ydir;
    double phidir;
    double zdir;
  }; // DTSegment
  
  
  struct RpcHit {
    RpcHit(): x(0), y(0), r(0), z(0), rho(0), phi(0), region(0){}
    double x;
    double y;
    double r;
    double z;
    double rho; 
    double phi;
    int region;
  };

  
  struct Track {
    Track() : chi2(0.), ndof(0.), nHits(0), nLost(0), quality(0), p(0.), hcalEta(0.), hcalPhi(0.) {}
    double chi2;
    double ndof;
    int nHits;
    int nLost;
    int quality;
    double p;
    double hcalEta;
    double hcalPhi;
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
  void removeTowers();
  void addStudyTower(shscp::Tower t);
  void addRecHit(shscp::RecHit r);
  void addHFRecHit(shscp::RecHit r);
  void addCscSegment(shscp::CscSegment s);
  void addCscHit(shscp::CscHit h);
  void addDTSegment(shscp::DTSegment dt);
  void addRpcHit(shscp::RpcHit h);
  void addHePlus(double energy, double antienergy, double phi);
  void addTrack(shscp::Track track);
  void addHeMinus(double energy, double antienergy, double phi);
  void addHe(double energy, double antienergy, double phi); 
  
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

  // MC result of hard scatter (gluino, stop, stau)
  unsigned mcSparticle_N;
  std::vector<UInt_t> mcSparticleId;
  std::vector<Double_t> mcSparticleMass;
  std::vector<Double_t> mcSparticleCharge;
  std::vector<Double_t> mcSparticlePx;
  std::vector<Double_t> mcSparticlePy;
  std::vector<Double_t> mcSparticlePz;
  std::vector<Double_t> mcSparticlePt;
  std::vector<Double_t> mcSparticleE;
  std::vector<Double_t> mcSparticlePhi;
  std::vector<Double_t> mcSparticleEta;

  // MC initial r-hadron (for gluino & stop)
  unsigned mcRhadron_N;
  std::vector<UInt_t> mcRhadronId;
  std::vector<Double_t> mcRhadronMass;
  std::vector<Double_t> mcRhadronCharge; // Not currently filled
  std::vector<Double_t> mcRhadronPx;
  std::vector<Double_t> mcRhadronPy;
  std::vector<Double_t> mcRhadronPz;
  std::vector<Double_t> mcRhadronPt;
  std::vector<Double_t> mcRhadronE;
  std::vector<Double_t> mcRhadronPhi;
  std::vector<Double_t> mcRhadronEta;

  // MC neutralino
  unsigned mcNeutralino_N;
  std::vector<UInt_t> mcNeutralinoId;
  std::vector<Double_t> mcNeutralinoMass;
  std::vector<Double_t> mcNeutralinoCharge; // Not currently filled
  std::vector<Double_t> mcNeutralinoPx;
  std::vector<Double_t> mcNeutralinoPy;
  std::vector<Double_t> mcNeutralinoPz;
  std::vector<Double_t> mcNeutralinoPt;
  std::vector<Double_t> mcNeutralinoE;
  std::vector<Double_t> mcNeutralinoPhi;
  std::vector<Double_t> mcNeutralinoEta;

  // MC neutralino
  unsigned mcDaughter_N;
  std::vector<UInt_t> mcDaughterId;
  std::vector<Double_t> mcDaughterMass;
  std::vector<Double_t> mcDaughterCharge; // Not currently filled
  std::vector<Double_t> mcDaughterPx;
  std::vector<Double_t> mcDaughterPy;
  std::vector<Double_t> mcDaughterPz;
  std::vector<Double_t> mcDaughterPt;
  std::vector<Double_t> mcDaughterE;
  std::vector<Double_t> mcDaughterPhi;
  std::vector<Double_t> mcDaughterEta;

  // MC stopped points
  unsigned mcStoppedParticle_N;
  std::vector<TString> mcStoppedParticleName;
  std::vector<UInt_t> mcStoppedParticleId;    // Not currently filled
  std::vector<Double_t> mcStoppedParticleX;
  std::vector<Double_t> mcStoppedParticleY;
  std::vector<Double_t> mcStoppedParticleZ;
  std::vector<Double_t> mcStoppedParticleR;
  std::vector<Double_t> mcStoppedParticlePhi;
  std::vector<Double_t> mcStoppedParticleTime;

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

  // lumi details (for this bx +/- 2)
  // All are set to -1 if LumiDetails collection is unavailable
  std::vector<Double_t> beam1Intensity; // in #protons
  std::vector<Double_t> beam2Intensity; // in #protons
  std::vector<Double_t> lumiByBx;       // in ub^-1 s^-1

  // Given in Hz/ub
  Double_t lsLuminosity;
  Double_t lsLuminosityErr;

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
  bool hltJetE70NoBptx3BXNoHalo;

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
  Int_t hltJetE70NoBptx3BXNoHaloPrescale;

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
  std::vector<Double_t> jetECorr;
  std::vector<Double_t> jetEt;
  std::vector<Double_t> jetEtCorr;
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
  std::vector<Double_t> jetEtaMean;
  std::vector<Double_t> jetPhiMean;
  std::vector<Double_t> jetEtaetaMoment;
  std::vector<Double_t> jetPhiphiMoment;
  std::vector<Double_t> jetEtaphiMoment;

  // reco jets used for studies only
  unsigned studyJet_N;
  std::vector<Double_t> studyJetE;
  std::vector<Double_t> studyJetECorr;
  std::vector<Double_t> studyJetEt;
  std::vector<Double_t> studyJetEtCorr;
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
  std::vector<Double_t> jetAK5ECorr;
  std::vector<Double_t> jetAK5Et;
  std::vector<Double_t> jetAK5EtCorr;
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
  std::vector<Double_t> studyJetAK5ECorr;
  std::vector<Double_t> studyJetAK5Et;
  std::vector<Double_t> studyJetAK5EtCorr;
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
  std::vector<Int_t> muNumChambers; // number of chambers
  std::vector<Int_t> muNumChambersNoRPC; // number of chambers not including RPC matches
  std::vector<Int_t> muNumMatches; // get number of chambers with matched segments
  std::vector<Int_t> muNumMatchedStations; // get number of stations with matched segments
  // get bit map of stations with matched segments
  // bits 0-1-2-3 = DT stations 1-2-3-4
  // bits 4-5-6-7 = CSC stations 1-2-3-4
  std::vector<UInt_t> muStationMask;
  
/** MLR - notes on new muon variables
  /// number of chambers (MuonChamberMatches include RPC rolls)
  int numberOfChambers() const { return muMatches_.size(); }

  /// number of chambers not including RPC matches (MuonChamberMatches include RPC rolls)
  int numberOfChambersNoRPC() const;

  /// get number of chambers with matched segments
  int numberOfMatches( ArbitrationType type = SegmentAndTrackArbitration ) const;

  /// get number of stations with matched segments
  /// just adds the bits returned by stationMask
  int numberOfMatchedStations( ArbitrationType type = SegmentAndTrackArbitration ) const;

  /// get bit map of stations with matched segments
  /// bits 0-1-2-3 = DT stations 1-2-3-4
  /// bits 4-5-6-7 = CSC stations 1-2-3-4
  unsigned int stationMask( ArbitrationType type = SegmentAndTrackArbitration ) const;
  */

  // vertices
  unsigned nVtx;
  unsigned vtx_N;
  std::vector<UInt_t> vtxNDOF;
  std::vector<Double_t> vtxZ;
  std::vector<Double_t> vtxRho;

  // tracks
  unsigned track_N;
  std::vector<double> trackChi2;
  std::vector<double> trackNdof;
  std::vector<int> trackNHits;
  std::vector<int> trackNLost;
  std::vector<double> trackP;
  std::vector<int> trackQuality;
  std::vector<double> trackHcalEta;
  std::vector<double> trackHcalPhi;
 

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
  std::vector<Double_t> cscSegTime;

  // CSC hits
  unsigned cscHit_N;
  std::vector<Double_t> cscHitZ;
  std::vector<Double_t> cscHitRho;
  std::vector<Double_t> cscHitPhi;
  std::vector<Double_t> cscHitTime; 

  // DT segments
  unsigned DTSegment_N;
  std::vector<Int_t> DTSegWheel;
  std::vector<Int_t> DTSegStation;
  std::vector<Int_t> DTSegSector;
  std::vector<Double_t> DTSegLocalX;
  std::vector<Double_t> DTSegLocalY;
  std::vector<Double_t> DTSegX;
  std::vector<Double_t> DTSegY;
  std::vector<Double_t> DTSegR;
  std::vector<Double_t> DTSegZ;
  std::vector<Double_t> DTSegRho;
  std::vector<Double_t> DTSegPhi;
  std::vector<Double_t> DTSegXDir;
  std::vector<Double_t> DTSegYDir;
  std::vector<Double_t> DTSegPhiDir;
  std::vector<Double_t> DTSegZDir;


  // RPC hits
  unsigned rpcHit_N;
  std::vector<Double_t> rpcHitX;
  std::vector<Double_t> rpcHitY;
  std::vector<Double_t> rpcHitR;
  std::vector<Double_t> rpcHitZ;
  std::vector<Double_t> rpcHitRho;
  std::vector<Double_t> rpcHitPhi;
  std::vector<Int_t>    rpcHitRegion;

  // HE energy -- Fedor's HE variables
  Double_t hePlusEnergy;
  Double_t hePlusAntiEnergy;
  Double_t hePlusPhi;
  Double_t heMinusEnergy;
  Double_t heMinusAntiEnergy;
  Double_t heMinusPhi;
  Double_t heEnergy;
  Double_t heAntiEnergy;
  Double_t hePhi; 

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

  ClassDef(StoppedHSCPEvent,29); // version 27: includes new jet variables

};

#endif
