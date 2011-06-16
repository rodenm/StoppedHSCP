//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Thu Jun 16 18:10:14 2011 by ROOT version 5.27/06b
// from TTree StoppedHSCPTree/
// found on file: /storage/phjjb/stoppedHSCP/stoppedHSCP_tree_Run2010A_Apr21_423p5_v1_1117_1309/stoppedHSCPTree_1_1_6k8.root
//////////////////////////////////////////////////////////

#ifndef StoppedHSCPTree_h
#define StoppedHSCPTree_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

#include <algorithm>

class StoppedHSCPTree {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   // Declaration of leaf types
 //StoppedHSCPEvent *events;
   UInt_t          rHadPdgId;
   Double_t        rHadVtxX;
   Double_t        rHadVtxY;
   Double_t        rHadVtxZ;
   Double_t        rHadVtxR;
   Double_t        rHadVtxT;
   Double_t        rHadE;
   Double_t        rHadPx;
   Double_t        rHadPy;
   Double_t        rHadPz;
   Double_t        rHadPt;
   UInt_t          mc_N;
   vector<UInt_t>  mcPDGid;
   vector<Double_t> mcVtxX;
   vector<Double_t> mcVtxY;
   vector<Double_t> mcVtxZ;
   vector<Double_t> mcVtxR;
   vector<Double_t> mcVtxT;
   vector<Double_t> mcE;
   vector<Double_t> mcPx;
   vector<Double_t> mcPy;
   vector<Double_t> mcPz;
   vector<Double_t> mcPt;
   ULong_t         id;
   ULong_t         bx;
   ULong_t         orbit;
   ULong_t         lb;
   ULong_t         run;
   ULong_t         fill;
   ULong_t         fillFromL1;
   ULong64_t       time;
   ULong64_t       time2;
   ULong64_t       time3;
   Long_t          bxAfterCollision;
   Long_t          bxBeforeCollision;
   Long_t          bxWrtCollision;
   Long_t          bxAfterBunch;
   Long_t          bxBeforeBunch;
   Long_t          bxWrtBunch;
   ULong64_t       gtAlgoWord0;
   ULong64_t       gtAlgoWord1;
   ULong64_t       gtTechWord;
   vector<UInt_t>  l1JetNoBptx;
   vector<UInt_t>  l1JetNoBptxNoHalo;
   vector<UInt_t>  l1Bptx;
   vector<UInt_t>  l1MuBeamHalo;
   Bool_t          hltJetNoBptx;
   Bool_t          hltJetNoBptxNoHalo;
   Bool_t          hltJetNoBptx3BXNoHalo;
   Bool_t          hltJetE50NoBptx3BXNoHalo;
   UInt_t          l1Jet_N;
   vector<UInt_t>  l1JetType;
   vector<Double_t> l1JetE;
   vector<Double_t> l1JetEt;
   vector<Double_t> l1JetEta;
   vector<Double_t> l1JetPhi;
   UInt_t          hltJet_N;
   vector<UInt_t>  hltJetType;
   vector<Double_t> hltJetE;
   vector<Double_t> hltJetEt;
   vector<Double_t> hltJetEta;
   vector<Double_t> hltJetPhi;
   UInt_t          jet_N;
   vector<Double_t> jetE;
   vector<Double_t> jetEt;
   vector<Double_t> jetEta;
   vector<Double_t> jetPhi;
   vector<Double_t> jetEHad;
   vector<Double_t> jetEEm;
   vector<Double_t> jetEMaxEcalTow;
   vector<Double_t> jetEMaxHcalTow;
   vector<UInt_t>  jetN60;
   vector<UInt_t>  jetN90;
   vector<Double_t> jetFHPD;
   vector<UInt_t>  jetN90Hits;
   UInt_t          jetAK5_N;
   vector<Double_t> jetAK5E;
   vector<Double_t> jetAK5Et;
   vector<Double_t> jetAK5Eta;
   vector<Double_t> jetAK5Phi;
   vector<Double_t> jetAK5EHad;
   vector<Double_t> jetAK5EEm;
   vector<Double_t> jetAK5EMaxEcalTow;
   vector<Double_t> jetAK5EMaxHcalTow;
   vector<UInt_t>  jetAK5N60;
   vector<UInt_t>  jetAK5N90;
   vector<Double_t> jetAK5FHPD;
   vector<UInt_t>  jetAK5N90Hits;
   UInt_t          mu_N;
   vector<UInt_t>  muType;
   vector<Double_t> muPt;
   vector<Double_t> muEta;
   vector<Double_t> muPhi;
   vector<Double_t> muHcalEta;
   vector<Double_t> muHcalPhi;
   UInt_t          nVtx;
   UInt_t          vtx_N;
   vector<UInt_t>  vtxNDOF;
   vector<Double_t> vtxZ;
   vector<Double_t> vtxRho;
   UInt_t          track_N;
   Bool_t          beamHalo_CSCTight;
   Bool_t          beamHalo_CSCLoose;
   Bool_t          beamHalo_HcalTight;
   Bool_t          beamHalo_HcalLoose;
   UInt_t          nTowerSameiPhi;
   UInt_t          nTowerLeadingIPhi;
   Double_t        eHadLeadingIPhi;
   Double_t        hfPlusTotalE;
   Double_t        hfMinusTotalE;
   Double_t        noiseMinE2Over10TS;
   Double_t        noiseMaxE2Over10TS;
   Int_t           noiseMaxHPDHits;
   Int_t           noiseMaxRBXHits;
   Int_t           noiseMaxHPDNoOtherHits;
   Int_t           noiseMaxZeros;
   Double_t        noiseMin25GeVHitTime;
   Double_t        noiseMax25GeVHitTime;
   Double_t        noiseMinRBXEMF;
   Bool_t          noiseFilterResult;
   Float_t         noiseEventEMEnergy;
   Float_t         noiseEventHadEnergy;
   Float_t         noiseEventTrackEnergy;
   Int_t           noiseNumProblematicRBXs;
   vector<double>  topHPD5TimeSamples;
   UInt_t          topHPD5PeakSample;
   Double_t        topHPD5Total;
   Double_t        topHPD5R1;
   Double_t        topHPD5R2;
   Double_t        topHPD5RPeak;
   Double_t        topHPD5ROuter;
   UInt_t          hpd_N;
   vector<UInt_t>  hpdId;
   vector<Double_t> hpdEta;
   vector<Double_t> hpdPhi;
   vector<UInt_t>  hpdTotalZeros;
   vector<UInt_t>  hpdMaxZeros;
   vector<UInt_t>  hpdNJet;
   vector<Double_t> hpdFc0;
   vector<Double_t> hpdFc1;
   vector<Double_t> hpdFc2;
   vector<Double_t> hpdFc3;
   vector<Double_t> hpdFc4;
   vector<Double_t> hpdFc5;
   vector<Double_t> hpdFc6;
   vector<Double_t> hpdFc7;
   vector<Double_t> hpdFc8;
   vector<Double_t> hpdFc9;
   vector<Double_t> hpdFc5_0;
   vector<Double_t> hpdFc5_1;
   vector<Double_t> hpdFc5_2;
   vector<Double_t> hpdFc5_3;
   vector<Double_t> hpdFc5_4;
   vector<Double_t> hpdFc5_5;
   vector<Double_t> hpdFc5_6;
   vector<Double_t> hpdFc5_7;
   vector<Double_t> hpdFc5_8;
   vector<Double_t> hpdFc5_9;
   UInt_t          tower_N;
   vector<Double_t> towerE;
   vector<Double_t> towerEt;
   vector<Double_t> towerEta;
   vector<Double_t> towerPhi;
   vector<Int_t>   towerIEta;
   vector<Int_t>   towerIPhi;
   vector<UInt_t>  towerNJet;
   vector<Double_t> towerEHad;
   vector<Double_t> towerEtHad;
   vector<Double_t> towerEEm;
   vector<Double_t> towerEtEm;
   UInt_t          recHit_N;
   vector<Double_t> recHitE;
   vector<Double_t> recHitTime;
   vector<UInt_t>  recHitFlags;
   vector<UInt_t>  recHitAux;
   vector<Double_t> recHitEta;
   vector<Double_t> recHitPhi;
   vector<Int_t>   recHitIEta;
   vector<Int_t>   recHitIPhi;
   vector<Int_t>   recHitDepth;
   vector<Int_t>   recHitRBXindex;
   vector<Int_t>   recHitRMindex;
   UInt_t          hfRecHit_N;
   vector<Double_t> hfRecHitE;
   vector<Double_t> hfRecHitTime;
   vector<Double_t> hfRecHitEta;
   vector<Double_t> hfRecHitPhi;
   vector<Int_t>   hfRecHitIEta;
   vector<Int_t>   hfRecHitIPhi;
   vector<Int_t>   hfRecHitDepth;
   UInt_t          cscSeg_N;
   vector<Int_t>   cscSegEndcap;
   vector<Int_t>   cscSegRing;
   vector<Int_t>   cscSegStation;
   vector<Int_t>   cscSegChamber;
   vector<UInt_t>  cscSegNHits;
   vector<Double_t> cscSegPhi;
   vector<Double_t> cscSegZ;
   vector<Double_t> cscSegR;
   vector<Double_t> cscSegDirPhi;
   vector<Double_t> cscSegDirTheta;
   Int_t           leadingDigiIEta;
   Int_t           leadingDigiIPhi;
   vector<double>  leadingDigiTimeSamples;
   UInt_t          leadingDigiPeakSample;
   Double_t        leadingDigiTotal;
   Double_t        leadingDigiR1;
   Double_t        leadingDigiR2;
   Double_t        leadingDigiRPeak;
   Double_t        leadingDigiROuter;
   vector<double>  top5DigiTimeSamples;
   UInt_t          top5DigiPeakSample;
   Double_t        top5DigiTotal;
   Double_t        top5DigiR1;
   Double_t        top5DigiR2;
   Double_t        top5DigiRPeak;
   Double_t        top5DigiROuter;

   // List of branches
   TBranch        *b_events_rHadPdgId;   //!
   TBranch        *b_events_rHadVtxX;   //!
   TBranch        *b_events_rHadVtxY;   //!
   TBranch        *b_events_rHadVtxZ;   //!
   TBranch        *b_events_rHadVtxR;   //!
   TBranch        *b_events_rHadVtxT;   //!
   TBranch        *b_events_rHadE;   //!
   TBranch        *b_events_rHadPx;   //!
   TBranch        *b_events_rHadPy;   //!
   TBranch        *b_events_rHadPz;   //!
   TBranch        *b_events_rHadPt;   //!
   TBranch        *b_events_mc_N;   //!
   TBranch        *b_events_mcPDGid;   //!
   TBranch        *b_events_mcVtxX;   //!
   TBranch        *b_events_mcVtxY;   //!
   TBranch        *b_events_mcVtxZ;   //!
   TBranch        *b_events_mcVtxR;   //!
   TBranch        *b_events_mcVtxT;   //!
   TBranch        *b_events_mcE;   //!
   TBranch        *b_events_mcPx;   //!
   TBranch        *b_events_mcPy;   //!
   TBranch        *b_events_mcPz;   //!
   TBranch        *b_events_mcPt;   //!
   TBranch        *b_events_id;   //!
   TBranch        *b_events_bx;   //!
   TBranch        *b_events_orbit;   //!
   TBranch        *b_events_lb;   //!
   TBranch        *b_events_run;   //!
   TBranch        *b_events_fill;   //!
   TBranch        *b_events_fillFromL1;   //!
   TBranch        *b_events_time;   //!
   TBranch        *b_events_time2;   //!
   TBranch        *b_events_time3;   //!
   TBranch        *b_events_bxAfterCollision;   //!
   TBranch        *b_events_bxBeforeCollision;   //!
   TBranch        *b_events_bxWrtCollision;   //!
   TBranch        *b_events_bxAfterBunch;   //!
   TBranch        *b_events_bxBeforeBunch;   //!
   TBranch        *b_events_bxWrtBunch;   //!
   TBranch        *b_events_gtAlgoWord0;   //!
   TBranch        *b_events_gtAlgoWord1;   //!
   TBranch        *b_events_gtTechWord;   //!
   TBranch        *b_events_l1JetNoBptx;   //!
   TBranch        *b_events_l1JetNoBptxNoHalo;   //!
   TBranch        *b_events_l1Bptx;   //!
   TBranch        *b_events_l1MuBeamHalo;   //!
   TBranch        *b_events_hltJetNoBptx;   //!
   TBranch        *b_events_hltJetNoBptxNoHalo;   //!
   TBranch        *b_events_hltJetNoBptx3BXNoHalo;   //!
   TBranch        *b_events_hltJetE50NoBptx3BXNoHalo;   //!
   TBranch        *b_events_l1Jet_N;   //!
   TBranch        *b_events_l1JetType;   //!
   TBranch        *b_events_l1JetE;   //!
   TBranch        *b_events_l1JetEt;   //!
   TBranch        *b_events_l1JetEta;   //!
   TBranch        *b_events_l1JetPhi;   //!
   TBranch        *b_events_hltJet_N;   //!
   TBranch        *b_events_hltJetType;   //!
   TBranch        *b_events_hltJetE;   //!
   TBranch        *b_events_hltJetEt;   //!
   TBranch        *b_events_hltJetEta;   //!
   TBranch        *b_events_hltJetPhi;   //!
   TBranch        *b_events_jet_N;   //!
   TBranch        *b_events_jetE;   //!
   TBranch        *b_events_jetEt;   //!
   TBranch        *b_events_jetEta;   //!
   TBranch        *b_events_jetPhi;   //!
   TBranch        *b_events_jetEHad;   //!
   TBranch        *b_events_jetEEm;   //!
   TBranch        *b_events_jetEMaxEcalTow;   //!
   TBranch        *b_events_jetEMaxHcalTow;   //!
   TBranch        *b_events_jetN60;   //!
   TBranch        *b_events_jetN90;   //!
   TBranch        *b_events_jetFHPD;   //!
   TBranch        *b_events_jetN90Hits;   //!
   TBranch        *b_events_jetAK5_N;   //!
   TBranch        *b_events_jetAK5E;   //!
   TBranch        *b_events_jetAK5Et;   //!
   TBranch        *b_events_jetAK5Eta;   //!
   TBranch        *b_events_jetAK5Phi;   //!
   TBranch        *b_events_jetAK5EHad;   //!
   TBranch        *b_events_jetAK5EEm;   //!
   TBranch        *b_events_jetAK5EMaxEcalTow;   //!
   TBranch        *b_events_jetAK5EMaxHcalTow;   //!
   TBranch        *b_events_jetAK5N60;   //!
   TBranch        *b_events_jetAK5N90;   //!
   TBranch        *b_events_jetAK5FHPD;   //!
   TBranch        *b_events_jetAK5N90Hits;   //!
   TBranch        *b_events_mu_N;   //!
   TBranch        *b_events_muType;   //!
   TBranch        *b_events_muPt;   //!
   TBranch        *b_events_muEta;   //!
   TBranch        *b_events_muPhi;   //!
   TBranch        *b_events_muHcalEta;   //!
   TBranch        *b_events_muHcalPhi;   //!
   TBranch        *b_events_nVtx;   //!
   TBranch        *b_events_vtx_N;   //!
   TBranch        *b_events_vtxNDOF;   //!
   TBranch        *b_events_vtxZ;   //!
   TBranch        *b_events_vtxRho;   //!
   TBranch        *b_events_track_N;   //!
   TBranch        *b_events_beamHalo_CSCTight;   //!
   TBranch        *b_events_beamHalo_CSCLoose;   //!
   TBranch        *b_events_beamHalo_HcalTight;   //!
   TBranch        *b_events_beamHalo_HcalLoose;   //!
   TBranch        *b_events_nTowerSameiPhi;   //!
   TBranch        *b_events_nTowerLeadingIPhi;   //!
   TBranch        *b_events_eHadLeadingIPhi;   //!
   TBranch        *b_events_hfPlusTotalE;   //!
   TBranch        *b_events_hfMinusTotalE;   //!
   TBranch        *b_events_noiseMinE2Over10TS;   //!
   TBranch        *b_events_noiseMaxE2Over10TS;   //!
   TBranch        *b_events_noiseMaxHPDHits;   //!
   TBranch        *b_events_noiseMaxRBXHits;   //!
   TBranch        *b_events_noiseMaxHPDNoOtherHits;   //!
   TBranch        *b_events_noiseMaxZeros;   //!
   TBranch        *b_events_noiseMin25GeVHitTime;   //!
   TBranch        *b_events_noiseMax25GeVHitTime;   //!
   TBranch        *b_events_noiseMinRBXEMF;   //!
   TBranch        *b_events_noiseFilterResult;   //!
   TBranch        *b_events_noiseEventEMEnergy;   //!
   TBranch        *b_events_noiseEventHadEnergy;   //!
   TBranch        *b_events_noiseEventTrackEnergy;   //!
   TBranch        *b_events_noiseNumProblematicRBXs;   //!
   TBranch        *b_events_topHPD5TimeSamples;   //!
   TBranch        *b_events_topHPD5PeakSample;   //!
   TBranch        *b_events_topHPD5Total;   //!
   TBranch        *b_events_topHPD5R1;   //!
   TBranch        *b_events_topHPD5R2;   //!
   TBranch        *b_events_topHPD5RPeak;   //!
   TBranch        *b_events_topHPD5ROuter;   //!
   TBranch        *b_events_hpd_N;   //!
   TBranch        *b_events_hpdId;   //!
   TBranch        *b_events_hpdEta;   //!
   TBranch        *b_events_hpdPhi;   //!
   TBranch        *b_events_hpdTotalZeros;   //!
   TBranch        *b_events_hpdMaxZeros;   //!
   TBranch        *b_events_hpdNJet;   //!
   TBranch        *b_events_hpdFc0;   //!
   TBranch        *b_events_hpdFc1;   //!
   TBranch        *b_events_hpdFc2;   //!
   TBranch        *b_events_hpdFc3;   //!
   TBranch        *b_events_hpdFc4;   //!
   TBranch        *b_events_hpdFc5;   //!
   TBranch        *b_events_hpdFc6;   //!
   TBranch        *b_events_hpdFc7;   //!
   TBranch        *b_events_hpdFc8;   //!
   TBranch        *b_events_hpdFc9;   //!
   TBranch        *b_events_hpdFc5_0;   //!
   TBranch        *b_events_hpdFc5_1;   //!
   TBranch        *b_events_hpdFc5_2;   //!
   TBranch        *b_events_hpdFc5_3;   //!
   TBranch        *b_events_hpdFc5_4;   //!
   TBranch        *b_events_hpdFc5_5;   //!
   TBranch        *b_events_hpdFc5_6;   //!
   TBranch        *b_events_hpdFc5_7;   //!
   TBranch        *b_events_hpdFc5_8;   //!
   TBranch        *b_events_hpdFc5_9;   //!
   TBranch        *b_events_tower_N;   //!
   TBranch        *b_events_towerE;   //!
   TBranch        *b_events_towerEt;   //!
   TBranch        *b_events_towerEta;   //!
   TBranch        *b_events_towerPhi;   //!
   TBranch        *b_events_towerIEta;   //!
   TBranch        *b_events_towerIPhi;   //!
   TBranch        *b_events_towerNJet;   //!
   TBranch        *b_events_towerEHad;   //!
   TBranch        *b_events_towerEtHad;   //!
   TBranch        *b_events_towerEEm;   //!
   TBranch        *b_events_towerEtEm;   //!
   TBranch        *b_events_recHit_N;   //!
   TBranch        *b_events_recHitE;   //!
   TBranch        *b_events_recHitTime;   //!
   TBranch        *b_events_recHitFlags;   //!
   TBranch        *b_events_recHitAux;   //!
   TBranch        *b_events_recHitEta;   //!
   TBranch        *b_events_recHitPhi;   //!
   TBranch        *b_events_recHitIEta;   //!
   TBranch        *b_events_recHitIPhi;   //!
   TBranch        *b_events_recHitDepth;   //!
   TBranch        *b_events_recHitRBXindex;   //!
   TBranch        *b_events_recHitRMindex;   //!
   TBranch        *b_events_hfRecHit_N;   //!
   TBranch        *b_events_hfRecHitE;   //!
   TBranch        *b_events_hfRecHitTime;   //!
   TBranch        *b_events_hfRecHitEta;   //!
   TBranch        *b_events_hfRecHitPhi;   //!
   TBranch        *b_events_hfRecHitIEta;   //!
   TBranch        *b_events_hfRecHitIPhi;   //!
   TBranch        *b_events_hfRecHitDepth;   //!
   TBranch        *b_events_cscSeg_N;   //!
   TBranch        *b_events_cscSegEndcap;   //!
   TBranch        *b_events_cscSegRing;   //!
   TBranch        *b_events_cscSegStation;   //!
   TBranch        *b_events_cscSegChamber;   //!
   TBranch        *b_events_cscSegNHits;   //!
   TBranch        *b_events_cscSegPhi;   //!
   TBranch        *b_events_cscSegZ;   //!
   TBranch        *b_events_cscSegR;   //!
   TBranch        *b_events_cscSegDirPhi;   //!
   TBranch        *b_events_cscSegDirTheta;   //!
   TBranch        *b_events_leadingDigiIEta;   //!
   TBranch        *b_events_leadingDigiIPhi;   //!
   TBranch        *b_events_leadingDigiTimeSamples;   //!
   TBranch        *b_events_leadingDigiPeakSample;   //!
   TBranch        *b_events_leadingDigiTotal;   //!
   TBranch        *b_events_leadingDigiR1;   //!
   TBranch        *b_events_leadingDigiR2;   //!
   TBranch        *b_events_leadingDigiRPeak;   //!
   TBranch        *b_events_leadingDigiROuter;   //!
   TBranch        *b_events_top5DigiTimeSamples;   //!
   TBranch        *b_events_top5DigiPeakSample;   //!
   TBranch        *b_events_top5DigiTotal;   //!
   TBranch        *b_events_top5DigiR1;   //!
   TBranch        *b_events_top5DigiR2;   //!
   TBranch        *b_events_top5DigiRPeak;   //!
   TBranch        *b_events_top5DigiROuter;   //!

   StoppedHSCPTree(TTree *tree=0);
   virtual ~StoppedHSCPTree();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);

   bool triggerCut() const;
   bool bptxVeto() const;
   bool bxVeto() const;
   bool vertexVeto() const;
   bool haloVeto() const;
   bool cosmicVeto() const;
   bool hfVeto() const;
   bool trackVeto() const;
   bool hcalNoiseVeto() const;
   bool looseJetCut() const;
   bool jetEnergyCut() const;
   bool jetN60Cut() const;
   bool jetN90Cut() const;
   bool towersIPhiCut() const;
   bool iPhiFractionCut() const;
   bool hpdR1Cut() const;
   bool hpdR2Cut() const;
   bool hpdRPeakCut() const;
   bool hpdROuterCut() const;

   double leadingIPhiFraction() const;

};

#endif

#ifdef StoppedHSCPTree_cxx
StoppedHSCPTree::StoppedHSCPTree(TTree *tree)
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("/storage/phjjb/stoppedHSCP/stoppedHSCP_tree_Run2010A_Apr21_423p5_v1_1117_1309/stoppedHSCPTree_1_1_6k8.root");
      if (!f) {
         f = new TFile("/storage/phjjb/stoppedHSCP/stoppedHSCP_tree_Run2010A_Apr21_423p5_v1_1117_1309/stoppedHSCPTree_1_1_6k8.root");
      }
      tree = (TTree*)gDirectory->Get("StoppedHSCPTree");

   }
   Init(tree);
}

StoppedHSCPTree::~StoppedHSCPTree()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t StoppedHSCPTree::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t StoppedHSCPTree::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (!fChain->InheritsFrom(TChain::Class()))  return centry;
   TChain *chain = (TChain*)fChain;
   if (chain->GetTreeNumber() != fCurrent) {
      fCurrent = chain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void StoppedHSCPTree::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("rHadPdgId", &rHadPdgId, &b_events_rHadPdgId);
   fChain->SetBranchAddress("rHadVtxX", &rHadVtxX, &b_events_rHadVtxX);
   fChain->SetBranchAddress("rHadVtxY", &rHadVtxY, &b_events_rHadVtxY);
   fChain->SetBranchAddress("rHadVtxZ", &rHadVtxZ, &b_events_rHadVtxZ);
   fChain->SetBranchAddress("rHadVtxR", &rHadVtxR, &b_events_rHadVtxR);
   fChain->SetBranchAddress("rHadVtxT", &rHadVtxT, &b_events_rHadVtxT);
   fChain->SetBranchAddress("rHadE", &rHadE, &b_events_rHadE);
   fChain->SetBranchAddress("rHadPx", &rHadPx, &b_events_rHadPx);
   fChain->SetBranchAddress("rHadPy", &rHadPy, &b_events_rHadPy);
   fChain->SetBranchAddress("rHadPz", &rHadPz, &b_events_rHadPz);
   fChain->SetBranchAddress("rHadPt", &rHadPt, &b_events_rHadPt);
   fChain->SetBranchAddress("mc_N", &mc_N, &b_events_mc_N);
   fChain->SetBranchAddress("mcPDGid", &mcPDGid, &b_events_mcPDGid);
   fChain->SetBranchAddress("mcVtxX", &mcVtxX, &b_events_mcVtxX);
   fChain->SetBranchAddress("mcVtxY", &mcVtxY, &b_events_mcVtxY);
   fChain->SetBranchAddress("mcVtxZ", &mcVtxZ, &b_events_mcVtxZ);
   fChain->SetBranchAddress("mcVtxR", &mcVtxR, &b_events_mcVtxR);
   fChain->SetBranchAddress("mcVtxT", &mcVtxT, &b_events_mcVtxT);
   fChain->SetBranchAddress("mcE", &mcE, &b_events_mcE);
   fChain->SetBranchAddress("mcPx", &mcPx, &b_events_mcPx);
   fChain->SetBranchAddress("mcPy", &mcPy, &b_events_mcPy);
   fChain->SetBranchAddress("mcPz", &mcPz, &b_events_mcPz);
   fChain->SetBranchAddress("mcPt", &mcPt, &b_events_mcPt);
   fChain->SetBranchAddress("id", &id, &b_events_id);
   fChain->SetBranchAddress("bx", &bx, &b_events_bx);
   fChain->SetBranchAddress("orbit", &orbit, &b_events_orbit);
   fChain->SetBranchAddress("lb", &lb, &b_events_lb);
   fChain->SetBranchAddress("run", &run, &b_events_run);
   fChain->SetBranchAddress("fill", &fill, &b_events_fill);
   fChain->SetBranchAddress("fillFromL1", &fillFromL1, &b_events_fillFromL1);
   fChain->SetBranchAddress("time", &time, &b_events_time);
   fChain->SetBranchAddress("time2", &time2, &b_events_time2);
   fChain->SetBranchAddress("time3", &time3, &b_events_time3);
   fChain->SetBranchAddress("bxAfterCollision", &bxAfterCollision, &b_events_bxAfterCollision);
   fChain->SetBranchAddress("bxBeforeCollision", &bxBeforeCollision, &b_events_bxBeforeCollision);
   fChain->SetBranchAddress("bxWrtCollision", &bxWrtCollision, &b_events_bxWrtCollision);
   fChain->SetBranchAddress("bxAfterBunch", &bxAfterBunch, &b_events_bxAfterBunch);
   fChain->SetBranchAddress("bxBeforeBunch", &bxBeforeBunch, &b_events_bxBeforeBunch);
   fChain->SetBranchAddress("bxWrtBunch", &bxWrtBunch, &b_events_bxWrtBunch);
   fChain->SetBranchAddress("gtAlgoWord0", &gtAlgoWord0, &b_events_gtAlgoWord0);
   fChain->SetBranchAddress("gtAlgoWord1", &gtAlgoWord1, &b_events_gtAlgoWord1);
   fChain->SetBranchAddress("gtTechWord", &gtTechWord, &b_events_gtTechWord);
   fChain->SetBranchAddress("l1JetNoBptx", &l1JetNoBptx, &b_events_l1JetNoBptx);
   fChain->SetBranchAddress("l1JetNoBptxNoHalo", &l1JetNoBptxNoHalo, &b_events_l1JetNoBptxNoHalo);
   fChain->SetBranchAddress("l1Bptx", &l1Bptx, &b_events_l1Bptx);
   fChain->SetBranchAddress("l1MuBeamHalo", &l1MuBeamHalo, &b_events_l1MuBeamHalo);
   fChain->SetBranchAddress("hltJetNoBptx", &hltJetNoBptx, &b_events_hltJetNoBptx);
   fChain->SetBranchAddress("hltJetNoBptxNoHalo", &hltJetNoBptxNoHalo, &b_events_hltJetNoBptxNoHalo);
   fChain->SetBranchAddress("hltJetNoBptx3BXNoHalo", &hltJetNoBptx3BXNoHalo, &b_events_hltJetNoBptx3BXNoHalo);
   fChain->SetBranchAddress("hltJetE50NoBptx3BXNoHalo", &hltJetE50NoBptx3BXNoHalo, &b_events_hltJetE50NoBptx3BXNoHalo);
   fChain->SetBranchAddress("l1Jet_N", &l1Jet_N, &b_events_l1Jet_N);
   fChain->SetBranchAddress("l1JetType", &l1JetType, &b_events_l1JetType);
   fChain->SetBranchAddress("l1JetE", &l1JetE, &b_events_l1JetE);
   fChain->SetBranchAddress("l1JetEt", &l1JetEt, &b_events_l1JetEt);
   fChain->SetBranchAddress("l1JetEta", &l1JetEta, &b_events_l1JetEta);
   fChain->SetBranchAddress("l1JetPhi", &l1JetPhi, &b_events_l1JetPhi);
   fChain->SetBranchAddress("hltJet_N", &hltJet_N, &b_events_hltJet_N);
   fChain->SetBranchAddress("hltJetType", &hltJetType, &b_events_hltJetType);
   fChain->SetBranchAddress("hltJetE", &hltJetE, &b_events_hltJetE);
   fChain->SetBranchAddress("hltJetEt", &hltJetEt, &b_events_hltJetEt);
   fChain->SetBranchAddress("hltJetEta", &hltJetEta, &b_events_hltJetEta);
   fChain->SetBranchAddress("hltJetPhi", &hltJetPhi, &b_events_hltJetPhi);
   fChain->SetBranchAddress("jet_N", &jet_N, &b_events_jet_N);
   fChain->SetBranchAddress("jetE", &jetE, &b_events_jetE);
   fChain->SetBranchAddress("jetEt", &jetEt, &b_events_jetEt);
   fChain->SetBranchAddress("jetEta", &jetEta, &b_events_jetEta);
   fChain->SetBranchAddress("jetPhi", &jetPhi, &b_events_jetPhi);
   fChain->SetBranchAddress("jetEHad", &jetEHad, &b_events_jetEHad);
   fChain->SetBranchAddress("jetEEm", &jetEEm, &b_events_jetEEm);
   fChain->SetBranchAddress("jetEMaxEcalTow", &jetEMaxEcalTow, &b_events_jetEMaxEcalTow);
   fChain->SetBranchAddress("jetEMaxHcalTow", &jetEMaxHcalTow, &b_events_jetEMaxHcalTow);
   fChain->SetBranchAddress("jetN60", &jetN60, &b_events_jetN60);
   fChain->SetBranchAddress("jetN90", &jetN90, &b_events_jetN90);
   fChain->SetBranchAddress("jetFHPD", &jetFHPD, &b_events_jetFHPD);
   fChain->SetBranchAddress("jetN90Hits", &jetN90Hits, &b_events_jetN90Hits);
   fChain->SetBranchAddress("jetAK5_N", &jetAK5_N, &b_events_jetAK5_N);
   fChain->SetBranchAddress("jetAK5E", &jetAK5E, &b_events_jetAK5E);
   fChain->SetBranchAddress("jetAK5Et", &jetAK5Et, &b_events_jetAK5Et);
   fChain->SetBranchAddress("jetAK5Eta", &jetAK5Eta, &b_events_jetAK5Eta);
   fChain->SetBranchAddress("jetAK5Phi", &jetAK5Phi, &b_events_jetAK5Phi);
   fChain->SetBranchAddress("jetAK5EHad", &jetAK5EHad, &b_events_jetAK5EHad);
   fChain->SetBranchAddress("jetAK5EEm", &jetAK5EEm, &b_events_jetAK5EEm);
   fChain->SetBranchAddress("jetAK5EMaxEcalTow", &jetAK5EMaxEcalTow, &b_events_jetAK5EMaxEcalTow);
   fChain->SetBranchAddress("jetAK5EMaxHcalTow", &jetAK5EMaxHcalTow, &b_events_jetAK5EMaxHcalTow);
   fChain->SetBranchAddress("jetAK5N60", &jetAK5N60, &b_events_jetAK5N60);
   fChain->SetBranchAddress("jetAK5N90", &jetAK5N90, &b_events_jetAK5N90);
   fChain->SetBranchAddress("jetAK5FHPD", &jetAK5FHPD, &b_events_jetAK5FHPD);
   fChain->SetBranchAddress("jetAK5N90Hits", &jetAK5N90Hits, &b_events_jetAK5N90Hits);
   fChain->SetBranchAddress("mu_N", &mu_N, &b_events_mu_N);
   fChain->SetBranchAddress("muType", &muType, &b_events_muType);
   fChain->SetBranchAddress("muPt", &muPt, &b_events_muPt);
   fChain->SetBranchAddress("muEta", &muEta, &b_events_muEta);
   fChain->SetBranchAddress("muPhi", &muPhi, &b_events_muPhi);
   fChain->SetBranchAddress("muHcalEta", &muHcalEta, &b_events_muHcalEta);
   fChain->SetBranchAddress("muHcalPhi", &muHcalPhi, &b_events_muHcalPhi);
   fChain->SetBranchAddress("nVtx", &nVtx, &b_events_nVtx);
   fChain->SetBranchAddress("vtx_N", &vtx_N, &b_events_vtx_N);
   fChain->SetBranchAddress("vtxNDOF", &vtxNDOF, &b_events_vtxNDOF);
   fChain->SetBranchAddress("vtxZ", &vtxZ, &b_events_vtxZ);
   fChain->SetBranchAddress("vtxRho", &vtxRho, &b_events_vtxRho);
   fChain->SetBranchAddress("track_N", &track_N, &b_events_track_N);
   fChain->SetBranchAddress("beamHalo_CSCTight", &beamHalo_CSCTight, &b_events_beamHalo_CSCTight);
   fChain->SetBranchAddress("beamHalo_CSCLoose", &beamHalo_CSCLoose, &b_events_beamHalo_CSCLoose);
   fChain->SetBranchAddress("beamHalo_HcalTight", &beamHalo_HcalTight, &b_events_beamHalo_HcalTight);
   fChain->SetBranchAddress("beamHalo_HcalLoose", &beamHalo_HcalLoose, &b_events_beamHalo_HcalLoose);
   fChain->SetBranchAddress("nTowerSameiPhi", &nTowerSameiPhi, &b_events_nTowerSameiPhi);
   fChain->SetBranchAddress("nTowerLeadingIPhi", &nTowerLeadingIPhi, &b_events_nTowerLeadingIPhi);
   fChain->SetBranchAddress("eHadLeadingIPhi", &eHadLeadingIPhi, &b_events_eHadLeadingIPhi);
   fChain->SetBranchAddress("hfPlusTotalE", &hfPlusTotalE, &b_events_hfPlusTotalE);
   fChain->SetBranchAddress("hfMinusTotalE", &hfMinusTotalE, &b_events_hfMinusTotalE);
   fChain->SetBranchAddress("noiseMinE2Over10TS", &noiseMinE2Over10TS, &b_events_noiseMinE2Over10TS);
   fChain->SetBranchAddress("noiseMaxE2Over10TS", &noiseMaxE2Over10TS, &b_events_noiseMaxE2Over10TS);
   fChain->SetBranchAddress("noiseMaxHPDHits", &noiseMaxHPDHits, &b_events_noiseMaxHPDHits);
   fChain->SetBranchAddress("noiseMaxRBXHits", &noiseMaxRBXHits, &b_events_noiseMaxRBXHits);
   fChain->SetBranchAddress("noiseMaxHPDNoOtherHits", &noiseMaxHPDNoOtherHits, &b_events_noiseMaxHPDNoOtherHits);
   fChain->SetBranchAddress("noiseMaxZeros", &noiseMaxZeros, &b_events_noiseMaxZeros);
   fChain->SetBranchAddress("noiseMin25GeVHitTime", &noiseMin25GeVHitTime, &b_events_noiseMin25GeVHitTime);
   fChain->SetBranchAddress("noiseMax25GeVHitTime", &noiseMax25GeVHitTime, &b_events_noiseMax25GeVHitTime);
   fChain->SetBranchAddress("noiseMinRBXEMF", &noiseMinRBXEMF, &b_events_noiseMinRBXEMF);
   fChain->SetBranchAddress("noiseFilterResult", &noiseFilterResult, &b_events_noiseFilterResult);
   fChain->SetBranchAddress("noiseEventEMEnergy", &noiseEventEMEnergy, &b_events_noiseEventEMEnergy);
   fChain->SetBranchAddress("noiseEventHadEnergy", &noiseEventHadEnergy, &b_events_noiseEventHadEnergy);
   fChain->SetBranchAddress("noiseEventTrackEnergy", &noiseEventTrackEnergy, &b_events_noiseEventTrackEnergy);
   fChain->SetBranchAddress("noiseNumProblematicRBXs", &noiseNumProblematicRBXs, &b_events_noiseNumProblematicRBXs);
   fChain->SetBranchAddress("topHPD5TimeSamples", &topHPD5TimeSamples, &b_events_topHPD5TimeSamples);
   fChain->SetBranchAddress("topHPD5PeakSample", &topHPD5PeakSample, &b_events_topHPD5PeakSample);
   fChain->SetBranchAddress("topHPD5Total", &topHPD5Total, &b_events_topHPD5Total);
   fChain->SetBranchAddress("topHPD5R1", &topHPD5R1, &b_events_topHPD5R1);
   fChain->SetBranchAddress("topHPD5R2", &topHPD5R2, &b_events_topHPD5R2);
   fChain->SetBranchAddress("topHPD5RPeak", &topHPD5RPeak, &b_events_topHPD5RPeak);
   fChain->SetBranchAddress("topHPD5ROuter", &topHPD5ROuter, &b_events_topHPD5ROuter);
   fChain->SetBranchAddress("hpd_N", &hpd_N, &b_events_hpd_N);
   fChain->SetBranchAddress("hpdId", &hpdId, &b_events_hpdId);
   fChain->SetBranchAddress("hpdEta", &hpdEta, &b_events_hpdEta);
   fChain->SetBranchAddress("hpdPhi", &hpdPhi, &b_events_hpdPhi);
   fChain->SetBranchAddress("hpdTotalZeros", &hpdTotalZeros, &b_events_hpdTotalZeros);
   fChain->SetBranchAddress("hpdMaxZeros", &hpdMaxZeros, &b_events_hpdMaxZeros);
   fChain->SetBranchAddress("hpdNJet", &hpdNJet, &b_events_hpdNJet);
   fChain->SetBranchAddress("hpdFc0", &hpdFc0, &b_events_hpdFc0);
   fChain->SetBranchAddress("hpdFc1", &hpdFc1, &b_events_hpdFc1);
   fChain->SetBranchAddress("hpdFc2", &hpdFc2, &b_events_hpdFc2);
   fChain->SetBranchAddress("hpdFc3", &hpdFc3, &b_events_hpdFc3);
   fChain->SetBranchAddress("hpdFc4", &hpdFc4, &b_events_hpdFc4);
   fChain->SetBranchAddress("hpdFc5", &hpdFc5, &b_events_hpdFc5);
   fChain->SetBranchAddress("hpdFc6", &hpdFc6, &b_events_hpdFc6);
   fChain->SetBranchAddress("hpdFc7", &hpdFc7, &b_events_hpdFc7);
   fChain->SetBranchAddress("hpdFc8", &hpdFc8, &b_events_hpdFc8);
   fChain->SetBranchAddress("hpdFc9", &hpdFc9, &b_events_hpdFc9);
   fChain->SetBranchAddress("hpdFc5_0", &hpdFc5_0, &b_events_hpdFc5_0);
   fChain->SetBranchAddress("hpdFc5_1", &hpdFc5_1, &b_events_hpdFc5_1);
   fChain->SetBranchAddress("hpdFc5_2", &hpdFc5_2, &b_events_hpdFc5_2);
   fChain->SetBranchAddress("hpdFc5_3", &hpdFc5_3, &b_events_hpdFc5_3);
   fChain->SetBranchAddress("hpdFc5_4", &hpdFc5_4, &b_events_hpdFc5_4);
   fChain->SetBranchAddress("hpdFc5_5", &hpdFc5_5, &b_events_hpdFc5_5);
   fChain->SetBranchAddress("hpdFc5_6", &hpdFc5_6, &b_events_hpdFc5_6);
   fChain->SetBranchAddress("hpdFc5_7", &hpdFc5_7, &b_events_hpdFc5_7);
   fChain->SetBranchAddress("hpdFc5_8", &hpdFc5_8, &b_events_hpdFc5_8);
   fChain->SetBranchAddress("hpdFc5_9", &hpdFc5_9, &b_events_hpdFc5_9);
   fChain->SetBranchAddress("tower_N", &tower_N, &b_events_tower_N);
   fChain->SetBranchAddress("towerE", &towerE, &b_events_towerE);
   fChain->SetBranchAddress("towerEt", &towerEt, &b_events_towerEt);
   fChain->SetBranchAddress("towerEta", &towerEta, &b_events_towerEta);
   fChain->SetBranchAddress("towerPhi", &towerPhi, &b_events_towerPhi);
   fChain->SetBranchAddress("towerIEta", &towerIEta, &b_events_towerIEta);
   fChain->SetBranchAddress("towerIPhi", &towerIPhi, &b_events_towerIPhi);
   fChain->SetBranchAddress("towerNJet", &towerNJet, &b_events_towerNJet);
   fChain->SetBranchAddress("towerEHad", &towerEHad, &b_events_towerEHad);
   fChain->SetBranchAddress("towerEtHad", &towerEtHad, &b_events_towerEtHad);
   fChain->SetBranchAddress("towerEEm", &towerEEm, &b_events_towerEEm);
   fChain->SetBranchAddress("towerEtEm", &towerEtEm, &b_events_towerEtEm);
   fChain->SetBranchAddress("recHit_N", &recHit_N, &b_events_recHit_N);
   fChain->SetBranchAddress("recHitE", &recHitE, &b_events_recHitE);
   fChain->SetBranchAddress("recHitTime", &recHitTime, &b_events_recHitTime);
   fChain->SetBranchAddress("recHitFlags", &recHitFlags, &b_events_recHitFlags);
   fChain->SetBranchAddress("recHitAux", &recHitAux, &b_events_recHitAux);
   fChain->SetBranchAddress("recHitEta", &recHitEta, &b_events_recHitEta);
   fChain->SetBranchAddress("recHitPhi", &recHitPhi, &b_events_recHitPhi);
   fChain->SetBranchAddress("recHitIEta", &recHitIEta, &b_events_recHitIEta);
   fChain->SetBranchAddress("recHitIPhi", &recHitIPhi, &b_events_recHitIPhi);
   fChain->SetBranchAddress("recHitDepth", &recHitDepth, &b_events_recHitDepth);
   fChain->SetBranchAddress("recHitRBXindex", &recHitRBXindex, &b_events_recHitRBXindex);
   fChain->SetBranchAddress("recHitRMindex", &recHitRMindex, &b_events_recHitRMindex);
   fChain->SetBranchAddress("hfRecHit_N", &hfRecHit_N, &b_events_hfRecHit_N);
   fChain->SetBranchAddress("hfRecHitE", &hfRecHitE, &b_events_hfRecHitE);
   fChain->SetBranchAddress("hfRecHitTime", &hfRecHitTime, &b_events_hfRecHitTime);
   fChain->SetBranchAddress("hfRecHitEta", &hfRecHitEta, &b_events_hfRecHitEta);
   fChain->SetBranchAddress("hfRecHitPhi", &hfRecHitPhi, &b_events_hfRecHitPhi);
   fChain->SetBranchAddress("hfRecHitIEta", &hfRecHitIEta, &b_events_hfRecHitIEta);
   fChain->SetBranchAddress("hfRecHitIPhi", &hfRecHitIPhi, &b_events_hfRecHitIPhi);
   fChain->SetBranchAddress("hfRecHitDepth", &hfRecHitDepth, &b_events_hfRecHitDepth);
   fChain->SetBranchAddress("cscSeg_N", &cscSeg_N, &b_events_cscSeg_N);
   fChain->SetBranchAddress("cscSegEndcap", &cscSegEndcap, &b_events_cscSegEndcap);
   fChain->SetBranchAddress("cscSegRing", &cscSegRing, &b_events_cscSegRing);
   fChain->SetBranchAddress("cscSegStation", &cscSegStation, &b_events_cscSegStation);
   fChain->SetBranchAddress("cscSegChamber", &cscSegChamber, &b_events_cscSegChamber);
   fChain->SetBranchAddress("cscSegNHits", &cscSegNHits, &b_events_cscSegNHits);
   fChain->SetBranchAddress("cscSegPhi", &cscSegPhi, &b_events_cscSegPhi);
   fChain->SetBranchAddress("cscSegZ", &cscSegZ, &b_events_cscSegZ);
   fChain->SetBranchAddress("cscSegR", &cscSegR, &b_events_cscSegR);
   fChain->SetBranchAddress("cscSegDirPhi", &cscSegDirPhi, &b_events_cscSegDirPhi);
   fChain->SetBranchAddress("cscSegDirTheta", &cscSegDirTheta, &b_events_cscSegDirTheta);
   fChain->SetBranchAddress("leadingDigiIEta", &leadingDigiIEta, &b_events_leadingDigiIEta);
   fChain->SetBranchAddress("leadingDigiIPhi", &leadingDigiIPhi, &b_events_leadingDigiIPhi);
   fChain->SetBranchAddress("leadingDigiTimeSamples", &leadingDigiTimeSamples, &b_events_leadingDigiTimeSamples);
   fChain->SetBranchAddress("leadingDigiPeakSample", &leadingDigiPeakSample, &b_events_leadingDigiPeakSample);
   fChain->SetBranchAddress("leadingDigiTotal", &leadingDigiTotal, &b_events_leadingDigiTotal);
   fChain->SetBranchAddress("leadingDigiR1", &leadingDigiR1, &b_events_leadingDigiR1);
   fChain->SetBranchAddress("leadingDigiR2", &leadingDigiR2, &b_events_leadingDigiR2);
   fChain->SetBranchAddress("leadingDigiRPeak", &leadingDigiRPeak, &b_events_leadingDigiRPeak);
   fChain->SetBranchAddress("leadingDigiROuter", &leadingDigiROuter, &b_events_leadingDigiROuter);
   fChain->SetBranchAddress("top5DigiTimeSamples", &top5DigiTimeSamples, &b_events_top5DigiTimeSamples);
   fChain->SetBranchAddress("top5DigiPeakSample", &top5DigiPeakSample, &b_events_top5DigiPeakSample);
   fChain->SetBranchAddress("top5DigiTotal", &top5DigiTotal, &b_events_top5DigiTotal);
   fChain->SetBranchAddress("top5DigiR1", &top5DigiR1, &b_events_top5DigiR1);
   fChain->SetBranchAddress("top5DigiR2", &top5DigiR2, &b_events_top5DigiR2);
   fChain->SetBranchAddress("top5DigiRPeak", &top5DigiRPeak, &b_events_top5DigiRPeak);
   fChain->SetBranchAddress("top5DigiROuter", &top5DigiROuter, &b_events_top5DigiROuter);
   Notify();
}

Bool_t StoppedHSCPTree::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void StoppedHSCPTree::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t StoppedHSCPTree::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
  return triggerCut() &&
    bptxVeto() &&
    bxVeto() &&
    vertexVeto() &&
    haloVeto() &&
    cosmicVeto() &&
    hcalNoiseVeto() &&
    looseJetCut() &&
    jetEnergyCut() &&
    jetN60Cut() &&
    jetN90Cut() &&
    towersIPhiCut() &&
    hpdR1Cut() &&
    hpdR2Cut() &&
    hpdRPeakCut() &&
    hpdROuterCut();

}

bool StoppedHSCPTree::triggerCut() const {      // require event passed main trigger

  //  bool trigBX = !(fills_->getMaskFromRun(event_->run).at(event_->bx));

  bool trigger = false;
  //1) in Run2010A, require hltJetNoBptx only
  if (fill<1711)
    trigger = hltJetNoBptx;
  //2) in Run2011A, before tech stop (fills 1711-1749) require hltJetNoBptx3BXNoHalo only
  else if (fill<1750)
    trigger = hltJetNoBptx3BXNoHalo;
  //3) in Run2011A, post tech stop (fills 1795 onwards) require hltJetE50NoBptx3BXNoHalo only
  else if (fill>=1795)
    trigger = hltJetE50NoBptx3BXNoHalo;

  return trigger;

}

bool StoppedHSCPTree::bptxVeto() const {        // cut on time wrt BPTX signal
  return true;
}

bool StoppedHSCPTree::bxVeto() const {          // cut on BX wrt expected collisions
  return abs(bxWrtBunch) > 2;
}

bool StoppedHSCPTree::vertexVeto() const {      // no vertex
  return (nVtx == 0);
}

bool StoppedHSCPTree::haloVeto() const {        // no halo ID
  return !(beamHalo_CSCLoose) ;//&& geometryHaloCut();
}

bool StoppedHSCPTree::hfVeto() const {
  return hfPlusTotalE < 50. && hfMinusTotalE < 50.;
}

bool StoppedHSCPTree::trackVeto() const {
  return (track_N == 0);
}

bool StoppedHSCPTree::cosmicVeto() const {      // no cosmic muon
  return mu_N==0;
}

bool StoppedHSCPTree::hcalNoiseVeto() const {   // std HCAL noise veto
  //std::cout <<"TRIGDEC:"<<run<<":"<<lb<<":"<<id<<":"<<bx<<":"<<noiseFilterResult<<std::endl;
  return noiseFilterResult;
}

bool StoppedHSCPTree::looseJetCut() const {     // low Et threshold
  return jet_N>0 && jetE[0]>30. && fabs(jetEta[0])<1.3;
}

bool StoppedHSCPTree::jetEnergyCut() const {    // require jet above Et threshold
  // raise jet energy cut to 70, since we're using a 50-GeV trigger?
  return jet_N>0 && jetE[0]>70. && fabs(jetEta[0])<1.3;
}

bool StoppedHSCPTree::jetN60Cut() const {       // jet n60
  return jet_N>0 && jetN60[0]<6;
}

bool StoppedHSCPTree::jetN90Cut() const {       // jet n90
  return jet_N>0 && jetN90[0]>3;
}

bool StoppedHSCPTree::towersIPhiCut() const {   // cut on N leading towers at same iphi
  return nTowerSameiPhi<5 && leadingIPhiFraction()<0.95;
}

bool StoppedHSCPTree::iPhiFractionCut() const { // Et fraction at leading iphi
  return leadingIPhiFraction()<0.95;
}

bool StoppedHSCPTree::hpdR1Cut() const {        // timing R1 cut from HPD
  return (topHPD5R1 > 0.15) && (topHPD5R1 <= 1.0);
}

bool StoppedHSCPTree::hpdR2Cut() const {        // timing R2 cut from HPD
  return (topHPD5R2 > 0.1) && (topHPD5R2 < 0.8);
}

bool StoppedHSCPTree::hpdRPeakCut() const {     // timing Rp cut from HPD
  return (topHPD5RPeak > 0.3) && (topHPD5RPeak < 0.7) && (topHPD5PeakSample > 0) && (topHPD5PeakSample < 7);
}

bool StoppedHSCPTree::hpdROuterCut() const {    // timing Ro cut from HPD
  return (topHPD5ROuter < 0.3) && (topHPD5ROuter >= 0.0) && (topHPD5PeakSample > 0) && (topHPD5PeakSample < 7);
}

double StoppedHSCPTree::leadingIPhiFraction() const {

    std::vector<double> tmp(75, 0);
    for (unsigned i=0; i<tower_N; ++i) {
      tmp.at(towerIPhi.at(i)) += towerE.at(i);
    }
    std::vector<double>::iterator max=max_element(tmp.begin(), tmp.end());

    double frac=0.;
    if (jet_N>0) frac = (*max)/jetE.at(0);
    return frac;

}


#endif // #ifdef StoppedHSCPTree_cxx
