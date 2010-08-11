//
//  Extended version of MakeClass output
//  Jim Brooke 21/4/2010
//
// Mods :
//  ctor from filename
//  CutN()           - returns true/false if currently loaded event passes n-th cut
//  CutNMinusOne()   - returns true/false if currently loaded event passes all other cuts
//  CutName()        - return name of cut
//  OldCutN()        - return true/false for cuts based on old variables for comparison
//  StdHcalCutN()    - as CutN(), but apply standard HCAL cuts
//  PrintCutValues() - dump cut variables for current event
//  InDisallowedBX() - return true if event is in disallowed BX vector (loaded in ctor)


//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Mon Apr 19 14:26:43 2010 by ROOT version 5.22/00
// from TTree StoppedHSCPTree/
// found on file: ntuples/stoppedHSCP_tree_Comm10_Promptv3_v3.root
//////////////////////////////////////////////////////////

#ifndef StoppedHSCPTree_h
#define StoppedHSCPTree_h

#include <TROOT.h>
#include <TChain.h>
#include <TTree.h>
#include <TFile.h>

#include <vector>
#include <iostream>


class StoppedHSCPTree {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   bool            oldTreePresent;

   // Declaration of leaf types
 //StoppedHSCPEvent *events;
   UInt_t          id;
   UInt_t          bx;
   UInt_t          orbit;
   UInt_t          lb;
   UInt_t          run;
   UInt_t          fill;
   ULong64_t       time;
   ULong64_t       time2;
   ULong64_t       time3;
   ULong64_t       gtAlgoWord0;
   ULong64_t       gtAlgoWord1;
   ULong64_t       gtTechWord;
   Bool_t          hltBit;
   UInt_t          l1Jet_N;
   std::vector<UInt_t>  l1JetType;
   std::vector<Double_t> l1JetE;
   std::vector<Double_t> l1JetEt;
   std::vector<Double_t> l1JetEta;
   std::vector<Double_t> l1JetPhi;
   UInt_t          hltJet_N;
   std::vector<UInt_t>  hltJetType;
   std::vector<Double_t> hltJetE;
   std::vector<Double_t> hltJetEt;
   std::vector<Double_t> hltJetEta;
   std::vector<Double_t> hltJetPhi;
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
   std::vector<UInt_t>  mcPDGid;
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
   UInt_t          nTowerSameiPhi;
   UInt_t          leadingDigiIEta;
   UInt_t          leadingDigiIPhi;
   std::vector<double>  leadingDigiTimeSamples;
   UInt_t          leadingDigiPeakSample;
   Double_t        leadingDigiTotal;
   Double_t        leadingDigiR1;
   Double_t        leadingDigiR2;
   Double_t        leadingDigiRPeak;
   Double_t        leadingDigiROuter;
   std::vector<double>  top5DigiTimeSamples;
   UInt_t          top5DigiPeakSample;
   Double_t        top5DigiTotal;
   Double_t        top5DigiR1;
   Double_t        top5DigiR2;
   Double_t        top5DigiRPeak;
   Double_t        top5DigiROuter;
   UInt_t          jet_N;
   std::vector<Double_t> jetE;
   std::vector<Double_t> jetEt;
   std::vector<Double_t> jetEta;
   std::vector<Double_t> jetPhi;
   std::vector<Double_t> jetEHad;
   std::vector<Double_t> jetEEm;
   std::vector<Double_t> jetEMaxEcalTow;
   std::vector<Double_t> jetEMaxHcalTow;
   std::vector<UInt_t>  jetN60;
   std::vector<UInt_t>  jetN90;
   std::vector<Double_t> jetFHPD;
   std::vector<UInt_t>  jetN90Hits;
   UInt_t          mu_N;
   std::vector<UInt_t>  muType;
   std::vector<Double_t> muPt;
   std::vector<Double_t> muEta;
   std::vector<Double_t> muPhi;
   std::vector<Double_t> muHcalEta;
   std::vector<Double_t> muHcalPhi;
   UInt_t          tower_N;
   std::vector<Double_t> towerE;
   std::vector<Double_t> towerEt;
   std::vector<Double_t> towerEta;
   std::vector<Double_t> towerPhi;
   std::vector<UInt_t>  towerIEta;
   std::vector<UInt_t>  towerIPhi;
   std::vector<UInt_t>  towerNJet;
   std::vector<Double_t> towerEHad;
   std::vector<Double_t> towerEtHad;
   std::vector<Double_t> towerEEm;
   std::vector<Double_t> towerEtEm;
   UInt_t          hpd_N;
   std::vector<UInt_t>  hpdId;
   std::vector<Double_t> hpdEta;
   std::vector<Double_t> hpdPhi;
   std::vector<UInt_t>  hpdTotalZeros;
   std::vector<UInt_t>  hpdMaxZeros;
   std::vector<UInt_t>  hpdNJet;
   std::vector<Double_t> hpdFc0;
   std::vector<Double_t> hpdFc1;
   std::vector<Double_t> hpdFc2;
   std::vector<Double_t> hpdFc3;
   std::vector<Double_t> hpdFc4;
   std::vector<Double_t> hpdFc5;
   std::vector<Double_t> hpdFc6;
   std::vector<Double_t> hpdFc7;
   std::vector<Double_t> hpdFc8;
   std::vector<Double_t> hpdFc9;
   std::vector<Double_t> hpdFc5_0;
   std::vector<Double_t> hpdFc5_1;
   std::vector<Double_t> hpdFc5_2;
   std::vector<Double_t> hpdFc5_3;
   std::vector<Double_t> hpdFc5_4;
   std::vector<Double_t> hpdFc5_5;
   std::vector<Double_t> hpdFc5_6;
   std::vector<Double_t> hpdFc5_7;
   std::vector<Double_t> hpdFc5_8;
   std::vector<Double_t> hpdFc5_9;
   double noiseMinE2Over10TS;
   double noiseMaxE2Over10TS;
   int noiseMaxHPDHits;
   int noiseMaxRBXHits;
   int noiseMaxHPDNoOtherHits;
   int noiseMaxZeros;
   double noiseMin25GeVHitTime;
   double noiseMax25GeVHitTime;
   double noiseMinRBXEMF;

   // old tree
   Int_t           CTMaxiEta;
   Int_t           CTMaxiPhi;
   Float_t         CTMaxEnergy;
   Float_t         CTMaxEt;
   Float_t         CTMaxEta;
   Float_t         CTMaxPhi;
   Float_t         CTMaxEnergyHad;
   Float_t         CTMaxEtHad;
   Float_t         CTMaxEnergyEm;
   Float_t         CTMaxEtEm;
   Int_t           CTNoLeaders;
   Int_t           CTNoLeaders2;
   Int_t           CTNOverThresh5;
   Int_t           CTNOverThresh10;
   Int_t           CTNOverThresh15;
   Int_t           CTNOverThresh20;
   Int_t           CTNOverThresh25;
   Int_t           CTNOverThresh30;
   Int_t           NCaloTowersInTopHPD;
   Float_t         LeadingJetEta;
   Float_t         LeadingJetPhi;
   Float_t         LeadingJetEnergy;
   Float_t         LeadingJetEt;
   Float_t         LeadingCenJetEta;
   Float_t         LeadingCenJetPhi;
   Float_t         LeadingCenJetEnergy;
   Float_t         LeadingCenJetEt;
   Int_t           NoOfJets;
   Int_t           NoOfCenJets;
   Float_t         LeadingJetEmInEB;
   Float_t         LeadingJetHadInHB;
   Float_t         LeadingJetMaxEInEmTowers;
   Float_t         LeadingJetMaxEInHadTowers;
   Float_t         LeadingJetTowerArea;
   Int_t           LeadingJetn60;
   Int_t           LeadingJetn90;
   Float_t         LeadingCenJetEmInEB;
   Float_t         LeadingCenJetHadInHB;
   Float_t         LeadingCenJetMaxEInEmTowers;
   Float_t         LeadingCenJetMaxEInHadTowers;
   Float_t         LeadingCenJetTowerArea;
   Int_t           LeadingCenJetn60;
   Int_t           LeadingCenJetn90;
   Float_t         TimingExpConst;
   Float_t         TimingExpSlope;
   Float_t         TimingExpChiSq;
   Float_t         TimingFirstBin;
   Float_t         TimingFirst2Bins;
   Float_t         TimingLastBin;
   Float_t         TimingLast2Bins;
   Float_t         TimingLeftPeak;
   Float_t         TimingRightPeak;
   Float_t         TimingFracInLeader;
   Int_t           Timingn60;
   Int_t           Timingn70;
   Int_t           Timingn80;
   Int_t           Timingn90;
   Float_t         TimingBX0;
   Float_t         TimingBX1;
   Float_t         TimingBX2;
   Float_t         TimingBX3;
   Float_t         TimingBX4;
   Float_t         TimingBX5;
   Float_t         TimingBX6;
   Float_t         TimingBX7;
   Float_t         TimingBX8;
   Float_t         TimingBX9;
   Float_t         TimingFracRightNextRight;
   Float_t         TimingFracPeakNextRight;
   Float_t         TimingFracInCentralFour;
   Float_t         TimingNoOfChannels;
   Float_t         TimingEnergyBeforePorch;
   Float_t         TimingEnergyBeforePeak;
   Float_t         TimingRightNextRight;
   Float_t         TimingPeakNextRight;
   Float_t         TimingTotal;
   Int_t           TimingPeakPosition;
   Float_t         TimingTotalOverTime;
   Float_t         TimingRightNextNextRight;
   Float_t         TimingPeakNextNextRight;
   Int_t           NoOfMuons;
   Long64_t        EventID;
   Long64_t        RunNumber;
   Long64_t        LumiNumber;
   Long64_t        TimeStamp;


   // List of branches
   TBranch        *b_events_id;   //!
   TBranch        *b_events_bx;   //!
   TBranch        *b_events_orbit;   //!
   TBranch        *b_events_lb;   //!
   TBranch        *b_events_run;   //!
   TBranch        *b_events_fill;   //!
   TBranch        *b_events_time;   //!
   TBranch        *b_events_time2;   //!
   TBranch        *b_events_time3;   //!
   TBranch        *b_events_gtAlgoWord0;   //!
   TBranch        *b_events_gtAlgoWord1;   //!
   TBranch        *b_events_gtTechWord;   //!
   TBranch        *b_events_hltBit;   //!
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
   TBranch        *b_events_nTowerSameiPhi;   //!
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
   TBranch        *b_events_mu_N;   //!
   TBranch        *b_events_muType;   //!
   TBranch        *b_events_muPt;   //!
   TBranch        *b_events_muEta;   //!
   TBranch        *b_events_muPhi;   //!
   TBranch        *b_events_muHcalEta;   //!
   TBranch        *b_events_muHcalPhi;   //!
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
   TBranch        *b_events_noiseMinE2Over10TS;   //!
   TBranch        *b_events_noiseMaxE2Over10TS;   //!
   TBranch        *b_events_noiseMaxHPDHits;   //!
   TBranch        *b_events_noiseMaxRBXHits;   //!
   TBranch        *b_events_noiseMaxHPDNoOtherHits;   //!
   TBranch        *b_events_noiseMaxZeros;   //!
   TBranch        *b_events_noiseMin25GeVHitTime;   //!
   TBranch        *b_events_noiseMax25GeVHitTime;   //!
   TBranch        *b_events_noiseMinRBXEMF;   //!

   // old tree
   TBranch        *b_CTMaxiEta_;   //!
   TBranch        *b_CTMaxiPhi_;   //!
   TBranch        *b_CTMaxEnergy_;   //!
   TBranch        *b_CTMaxEt_;   //!
   TBranch        *b_CTMaxEta_;   //!
   TBranch        *b_CTMaxPhi_;   //!
   TBranch        *b_CTMaxEnergyHad;   //!
   TBranch        *b_CTMaxEtHad;   //!
   TBranch        *b_CTMaxEnergyEm;   //!
   TBranch        *b_CTMaxEtEm;   //!
   TBranch        *b_CTNoLeaders;   //!
   TBranch        *b_CTNoLeaders2;   //!
   TBranch        *b_CTNOverThresh5;   //!
   TBranch        *b_CTNOverThresh10;   //!
   TBranch        *b_CTNOverThresh15;   //!
   TBranch        *b_CTNOverThresh20;   //!
   TBranch        *b_CTNOverThresh25;   //!
   TBranch        *b_CTNOverThresh30;   //!
   TBranch        *b_NCaloTowersInTopHPD;   //!
   TBranch        *b_LeadingJetEta;   //!
   TBranch        *b_LeadingJetPhi;   //!
   TBranch        *b_LeadingJetEnergy;   //!
   TBranch        *b_LeadingJetEt;   //!
   TBranch        *b_LeadingCenJetEta;   //!
   TBranch        *b_LeadingCenJetPhi;   //!
   TBranch        *b_LeadingCenJetEnergy;   //!
   TBranch        *b_LeadingCenJetEt;   //!
   TBranch        *b_NoOfJets;   //!
   TBranch        *b_NoOfCenJets;   //!
   TBranch        *b_LeadingJetEmInEB;   //!
   TBranch        *b_LeadingJetHadInHB;   //!
   TBranch        *b_LeadingJetMaxEInEmTowers;   //!
   TBranch        *b_LeadingJetMaxEInHadTowers;   //!
   TBranch        *b_LeadingJetTowerArea;   //!
   TBranch        *b_LeadingJetn60;   //!
   TBranch        *b_LeadingJetn90;   //!
   TBranch        *b_LeadingCenJetEmInEB;   //!
   TBranch        *b_LeadingCenJetHadInHB;   //!
   TBranch        *b_LeadingCenJetMaxEInEmTowers;   //!
   TBranch        *b_LeadingCenJetMaxEInHadTowers;   //!
   TBranch        *b_LeadingCenJetTowerArea;   //!
   TBranch        *b_LeadingCenJetn60;   //!
   TBranch        *b_LeadingCenJetn90;   //!
   TBranch        *b_TimingExpConst;   //!
   TBranch        *b_TimingExpSlope;   //!
   TBranch        *b_TimingExpChiSq;   //!
   TBranch        *b_TimingFirstBin;   //!
   TBranch        *b_TimingFirst2Bins;   //!
   TBranch        *b_TimingLastBin;   //!
   TBranch        *b_TimingLast2Bins;   //!
   TBranch        *b_TimingFracLeft;   //!
   TBranch        *b_TimingRightPeak;   //!
   TBranch        *b_TimingFracInLeader;   //!
   TBranch        *b_Timingn60;   //!
   TBranch        *b_Timingn70;   //!
   TBranch        *b_Timingn80;   //!
   TBranch        *b_Timingn90;   //!
   TBranch        *b_TimingBX0;   //!
   TBranch        *b_TimingBX1;   //!
   TBranch        *b_TimingBX2;   //!
   TBranch        *b_TimingBX3;   //!
   TBranch        *b_TimingBX4;   //!
   TBranch        *b_TimingBX5;   //!
   TBranch        *b_TimingBX6;   //!
   TBranch        *b_TimingBX7;   //!
   TBranch        *b_TimingBX8;   //!
   TBranch        *b_TimingBX9;   //!
   TBranch        *b_TimingFracRightNextRight;   //!
   TBranch        *b_TimingFracPeakNextRight;   //!
   TBranch        *b_TimingFracInCentralFour;   //!
   TBranch        *b_TimingTotal;   //!
   TBranch        *b_TimingNoOfChannels;   //!
   TBranch        *b_TimingEnergyBeforePorch;   //!
   TBranch        *b_TimingEnergyBeforePeak;   //!
   TBranch        *b_TimingRightNextRight;   //!
   TBranch        *b_TimingPeakNextRight;   //!
   TBranch        *b_TimingPeakPosition;   //!
   TBranch        *b_TimingTotalOverTime;   //!
   TBranch        *b_TimingRightNextNextRight;   //!
   TBranch        *b_TimingPeakNextNextRight;   //!
   TBranch        *b_NoOfMuons;   //!
   TBranch        *b_EventID;   //!
   TBranch        *b_RunNumber;   //!
   TBranch        *b_LumiNumber;   //!
   TBranch        *b_TimeStamp;   //!

   bool           isMC_;
   std::vector<unsigned> disallowedBXs_;

   StoppedHSCPTree(TFile* file, bool isMC);
   StoppedHSCPTree(TTree *tree, bool isMC);
   virtual ~StoppedHSCPTree();
   virtual bool     Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
   virtual unsigned NCuts();
   virtual bool     CutN(unsigned n);
   virtual bool     CutNSyst(unsigned n, double smear);
   virtual bool     AllCutN(unsigned n);
   virtual const char*    CutName(unsigned n);
   virtual bool     CutNMinusOne(unsigned n);
   virtual bool     OldCutN(unsigned n);
   virtual bool     StdHcalCutN(unsigned n);
   virtual void     PrintCutValues(ostream& o);
   virtual void     SetDisallowedBXs(std::vector<unsigned> bxs);
   virtual bool     InDisallowedBX();
};

StoppedHSCPTree::StoppedHSCPTree(TFile* file, bool isMC) :
  oldTreePresent(false),
  isMC_(isMC),
  disallowedBXs_(0)
{

  // open file and get tree
  //  TFile file(filename);
  TTree* tree = (TTree*) file->Get("stoppedHSCPTree/StoppedHSCPTree");
  TTree* oldtree = (TTree*) file->Get("globalRunAnalyser/EventTree");
  if (oldtree!=0) {
    tree->AddFriend(oldtree);
    oldTreePresent = true;
    std::cout << "Adding old TTree as friend" << std::endl;
  }
  Init(tree);

  if (isMC_) std::cout << "StoppedHSCPTree is for MC" << std::endl;

}

StoppedHSCPTree::StoppedHSCPTree(TTree *tree, bool isMC) :
  isMC_(isMC),
  disallowedBXs_(0)
{
   Init(tree);
}

StoppedHSCPTree::~StoppedHSCPTree()
{
  //   if (!fChain) return;
  //   delete fChain->GetCurrentFile();
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

   fChain->SetBranchAddress("id", &id, &b_events_id);
   fChain->SetBranchAddress("bx", &bx, &b_events_bx);
   fChain->SetBranchAddress("orbit", &orbit, &b_events_orbit);
   fChain->SetBranchAddress("lb", &lb, &b_events_lb);
   fChain->SetBranchAddress("run", &run, &b_events_run);
   fChain->SetBranchAddress("fill", &fill, &b_events_fill);
   fChain->SetBranchAddress("time", &time, &b_events_time);
   fChain->SetBranchAddress("time2", &time2, &b_events_time2);
   fChain->SetBranchAddress("time3", &time3, &b_events_time3);
   fChain->SetBranchAddress("gtAlgoWord0", &gtAlgoWord0, &b_events_gtAlgoWord0);
   fChain->SetBranchAddress("gtAlgoWord1", &gtAlgoWord1, &b_events_gtAlgoWord1);
   fChain->SetBranchAddress("gtTechWord", &gtTechWord, &b_events_gtTechWord);
   fChain->SetBranchAddress("hltBit", &hltBit, &b_events_hltBit);
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
   fChain->SetBranchAddress("nTowerSameiPhi", &nTowerSameiPhi, &b_events_nTowerSameiPhi);
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
   fChain->SetBranchAddress("mu_N", &mu_N, &b_events_mu_N);
   fChain->SetBranchAddress("muType", &muType, &b_events_muType);
   fChain->SetBranchAddress("muPt", &muPt, &b_events_muPt);
   fChain->SetBranchAddress("muEta", &muEta, &b_events_muEta);
   fChain->SetBranchAddress("muPhi", &muPhi, &b_events_muPhi);
   fChain->SetBranchAddress("muHcalEta", &muHcalEta, &b_events_muHcalEta);
   fChain->SetBranchAddress("muHcalPhi", &muHcalPhi, &b_events_muHcalPhi);
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
   fChain->SetBranchAddress("noiseMinE2Over10TS", &noiseMinE2Over10TS, &b_events_noiseMinE2Over10TS);
   fChain->SetBranchAddress("noiseMaxE2Over10TS", &noiseMaxE2Over10TS, &b_events_noiseMaxE2Over10TS);
   fChain->SetBranchAddress("noiseMaxHPDHits", &noiseMaxHPDHits, &b_events_noiseMaxHPDHits);
   fChain->SetBranchAddress("noiseMaxRBXHits", &noiseMaxRBXHits, &b_events_noiseMaxRBXHits);
   fChain->SetBranchAddress("noiseMaxHPDNoOtherHits", &noiseMaxHPDNoOtherHits, &b_events_noiseMaxHPDNoOtherHits);
   fChain->SetBranchAddress("noiseMaxZeros", &noiseMaxZeros, &b_events_noiseMaxZeros);
   fChain->SetBranchAddress("noiseMin25GeVHitTime", &noiseMin25GeVHitTime, &b_events_noiseMin25GeVHitTime);
   fChain->SetBranchAddress("noiseMax25GeVHitTime", &noiseMax25GeVHitTime, &b_events_noiseMax25GeVHitTime);
   fChain->SetBranchAddress("noiseMinRBXEMF", &noiseMinRBXEMF, &b_events_noiseMinRBXEMF);

   if (oldTreePresent!=0) {
     fChain->SetBranchAddress("CTMaxiEta", &CTMaxiEta, &b_CTMaxiEta_);
     fChain->SetBranchAddress("CTMaxiPhi", &CTMaxiPhi, &b_CTMaxiPhi_);
     fChain->SetBranchAddress("CTMaxEnergy", &CTMaxEnergy, &b_CTMaxEnergy_);
     fChain->SetBranchAddress("CTMaxEt", &CTMaxEt, &b_CTMaxEt_);
     fChain->SetBranchAddress("CTMaxEta", &CTMaxEta, &b_CTMaxEta_);
     fChain->SetBranchAddress("CTMaxPhi", &CTMaxPhi, &b_CTMaxPhi_);
     fChain->SetBranchAddress("CTMaxEnergyHad", &CTMaxEnergyHad, &b_CTMaxEnergyHad);
     fChain->SetBranchAddress("CTMaxEtHad", &CTMaxEtHad, &b_CTMaxEtHad);
     fChain->SetBranchAddress("CTMaxEnergyEm", &CTMaxEnergyEm, &b_CTMaxEnergyEm);
     fChain->SetBranchAddress("CTMaxEtEm", &CTMaxEtEm, &b_CTMaxEtEm);
     fChain->SetBranchAddress("CTNoLeaders", &CTNoLeaders, &b_CTNoLeaders);
     fChain->SetBranchAddress("CTNoLeaders2", &CTNoLeaders2, &b_CTNoLeaders2);
     fChain->SetBranchAddress("CTNOverThresh5", &CTNOverThresh5, &b_CTNOverThresh5);
     fChain->SetBranchAddress("CTNOverThresh10", &CTNOverThresh10, &b_CTNOverThresh10);
     fChain->SetBranchAddress("CTNOverThresh15", &CTNOverThresh15, &b_CTNOverThresh15);
     fChain->SetBranchAddress("CTNOverThresh20", &CTNOverThresh20, &b_CTNOverThresh20);
     fChain->SetBranchAddress("CTNOverThresh25", &CTNOverThresh25, &b_CTNOverThresh25);
     fChain->SetBranchAddress("CTNOverThresh30", &CTNOverThresh30, &b_CTNOverThresh30);
     fChain->SetBranchAddress("NCaloTowersInTopHPD", &NCaloTowersInTopHPD, &b_NCaloTowersInTopHPD);
     fChain->SetBranchAddress("LeadingJetEta", &LeadingJetEta, &b_LeadingJetEta);
     fChain->SetBranchAddress("LeadingJetPhi", &LeadingJetPhi, &b_LeadingJetPhi);
     fChain->SetBranchAddress("LeadingJetEnergy", &LeadingJetEnergy, &b_LeadingJetEnergy);
     fChain->SetBranchAddress("LeadingJetEt", &LeadingJetEt, &b_LeadingJetEt);
     fChain->SetBranchAddress("LeadingCenJetEta", &LeadingCenJetEta, &b_LeadingCenJetEta);
     fChain->SetBranchAddress("LeadingCenJetPhi", &LeadingCenJetPhi, &b_LeadingCenJetPhi);
     fChain->SetBranchAddress("LeadingCenJetEnergy", &LeadingCenJetEnergy, &b_LeadingCenJetEnergy);
     fChain->SetBranchAddress("LeadingCenJetEt", &LeadingCenJetEt, &b_LeadingCenJetEt);
     fChain->SetBranchAddress("NoOfJets", &NoOfJets, &b_NoOfJets);
     fChain->SetBranchAddress("NoOfCenJets", &NoOfCenJets, &b_NoOfCenJets);
     fChain->SetBranchAddress("LeadingJetEmInEB", &LeadingJetEmInEB, &b_LeadingJetEmInEB);
     fChain->SetBranchAddress("LeadingJetHadInHB", &LeadingJetHadInHB, &b_LeadingJetHadInHB);
     fChain->SetBranchAddress("LeadingJetMaxEInEmTowers", &LeadingJetMaxEInEmTowers, &b_LeadingJetMaxEInEmTowers);
     fChain->SetBranchAddress("LeadingJetMaxEInHadTowers", &LeadingJetMaxEInHadTowers, &b_LeadingJetMaxEInHadTowers);
     fChain->SetBranchAddress("LeadingJetTowerArea", &LeadingJetTowerArea, &b_LeadingJetTowerArea);
     fChain->SetBranchAddress("LeadingJetn60", &LeadingJetn60, &b_LeadingJetn60);
     fChain->SetBranchAddress("LeadingJetn90", &LeadingJetn90, &b_LeadingJetn90);
     fChain->SetBranchAddress("LeadingCenJetEmInEB", &LeadingCenJetEmInEB, &b_LeadingCenJetEmInEB);
     fChain->SetBranchAddress("LeadingCenJetHadInHB", &LeadingCenJetHadInHB, &b_LeadingCenJetHadInHB);
     fChain->SetBranchAddress("LeadingCenJetMaxEInEmTowers", &LeadingCenJetMaxEInEmTowers, &b_LeadingCenJetMaxEInEmTowers);
     fChain->SetBranchAddress("LeadingCenJetMaxEInHadTowers", &LeadingCenJetMaxEInHadTowers, &b_LeadingCenJetMaxEInHadTowers);
     fChain->SetBranchAddress("LeadingCenJetTowerArea", &LeadingCenJetTowerArea, &b_LeadingCenJetTowerArea);
     fChain->SetBranchAddress("LeadingCenJetn60", &LeadingCenJetn60, &b_LeadingCenJetn60);
     fChain->SetBranchAddress("LeadingCenJetn90", &LeadingCenJetn90, &b_LeadingCenJetn90);
     fChain->SetBranchAddress("TimingExpConst", &TimingExpConst, &b_TimingExpConst);
     fChain->SetBranchAddress("TimingExpSlope", &TimingExpSlope, &b_TimingExpSlope);
     fChain->SetBranchAddress("TimingExpChiSq", &TimingExpChiSq, &b_TimingExpChiSq);
     fChain->SetBranchAddress("TimingFracRightNextRight", &TimingFracRightNextRight, &b_TimingFracRightNextRight);
     fChain->SetBranchAddress("TimingFracPeakNextRight", &TimingFracPeakNextRight, &b_TimingFracPeakNextRight);
     fChain->SetBranchAddress("TimingNoOfChannels", &TimingNoOfChannels, &b_TimingNoOfChannels);
     fChain->SetBranchAddress("TimingEnergyBeforePorch", &TimingEnergyBeforePorch, &b_TimingEnergyBeforePorch);
     fChain->SetBranchAddress("TimingEnergyBeforePeak", &TimingEnergyBeforePeak, &b_TimingEnergyBeforePeak);
     fChain->SetBranchAddress("TimingFirstBin", &TimingFirstBin, &b_TimingFirstBin);
     fChain->SetBranchAddress("TimingFirst2Bins", &TimingFirst2Bins, &b_TimingFirst2Bins);
     fChain->SetBranchAddress("TimingLastBin", &TimingLastBin, &b_TimingLastBin);
     fChain->SetBranchAddress("TimingLast2Bins", &TimingLast2Bins, &b_TimingLast2Bins);
     fChain->SetBranchAddress("TimingLeftPeak", &TimingLeftPeak, &b_TimingFracLeft);
     fChain->SetBranchAddress("TimingRightPeak", &TimingRightPeak, &b_TimingRightPeak);
     fChain->SetBranchAddress("TimingFracInLeader", &TimingFracInLeader, &b_TimingFracInLeader);
     fChain->SetBranchAddress("Timingn60", &Timingn60, &b_Timingn60);
     fChain->SetBranchAddress("Timingn70", &Timingn70, &b_Timingn70);
     fChain->SetBranchAddress("Timingn80", &Timingn80, &b_Timingn80);
     fChain->SetBranchAddress("Timingn90", &Timingn90, &b_Timingn90);
     fChain->SetBranchAddress("TimingBX0", &TimingBX0, &b_TimingBX0);
     fChain->SetBranchAddress("TimingBX1", &TimingBX1, &b_TimingBX1);
     fChain->SetBranchAddress("TimingBX2", &TimingBX2, &b_TimingBX2);
     fChain->SetBranchAddress("TimingBX3", &TimingBX3, &b_TimingBX3);
     fChain->SetBranchAddress("TimingBX4", &TimingBX4, &b_TimingBX4);
     fChain->SetBranchAddress("TimingBX5", &TimingBX5, &b_TimingBX5);
     fChain->SetBranchAddress("TimingBX6", &TimingBX6, &b_TimingBX6);
     fChain->SetBranchAddress("TimingBX7", &TimingBX7, &b_TimingBX7);
     fChain->SetBranchAddress("TimingBX8", &TimingBX8, &b_TimingBX8);
     fChain->SetBranchAddress("TimingBX9", &TimingBX9, &b_TimingBX9);
     fChain->SetBranchAddress("TimingRightNextRight", &TimingRightNextRight, &b_TimingRightNextRight);
     fChain->SetBranchAddress("TimingPeakNextRight", &TimingPeakNextRight, &b_TimingPeakNextRight);
     fChain->SetBranchAddress("TimingFracInCentralFour", &TimingFracInCentralFour, &b_TimingFracInCentralFour);
     fChain->SetBranchAddress("TimingTotal", &TimingTotal, &b_TimingTotal);
     fChain->SetBranchAddress("TimingPeakPosition", &TimingPeakPosition, &b_TimingPeakPosition);
     fChain->SetBranchAddress("TimingTotalOverTime", &TimingTotalOverTime, &b_TimingTotalOverTime);
     fChain->SetBranchAddress("TimingRightNextNextRight", &TimingRightNextNextRight, &b_TimingRightNextNextRight);
     fChain->SetBranchAddress("TimingPeakNextNextRight", &TimingPeakNextNextRight, &b_TimingPeakNextNextRight);
     fChain->SetBranchAddress("NoOfMuons", &NoOfMuons, &b_NoOfMuons);
     fChain->SetBranchAddress("EventID", &EventID, &b_EventID);
     fChain->SetBranchAddress("RunNumber", &RunNumber, &b_RunNumber);
     fChain->SetBranchAddress("LumiNumber", &LumiNumber, &b_LumiNumber);
     fChain->SetBranchAddress("TimeStamp", &TimeStamp, &b_TimeStamp);
   }

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

// return result of all cuts
bool StoppedHSCPTree::Cut(Long64_t entry=0)
{
  bool pass=true;
  for (unsigned i=0; i<NCuts(); ++i) {
    pass &= CutN(i);
  }
  return pass;
}

unsigned StoppedHSCPTree::NCuts() {
  return 13;
}


// return result of a particular cut
bool StoppedHSCPTree::CutN(unsigned n)
{
  
  switch (n) {
  case 0:
    return !isMC_ || ((((gtAlgoWord0>>16)&1) == 1) && (hltJet_N>0) && (hltJetE[0]> 20.) && (hltJetEta[0]<1.3));
  case 1:
    return isMC_ || ! InDisallowedBX();
  case 2:
    return isMC_ || ((gtAlgoWord1>>(81-64)&1) == 0 && (gtAlgoWord1>>(80-64)&1) == 0);
  case 3:
    return mu_N==0;
  case 4:
    return jet_N>0 && jetE[0]>30. && jetEta[0]<1.3;
  case 5:
    return jet_N>0 && jetE[0]>50. && jetEta[0]<1.3;
  case 6:
    return jet_N>0 && jetN60[0]<6;
  case 7:
    return jet_N>0 && jetN90[0]>3;
  case 8:
    return nTowerSameiPhi<5;
  case 9:
    return (top5DigiR1 > 0.15) && (top5DigiR1 <= 1.0);
  case 10:
    return (top5DigiR2 > 0.1) && (top5DigiR2 < 0.5);
  case 11:
    return (top5DigiRPeak > 0.4) && (top5DigiRPeak < 0.7) && (top5DigiPeakSample > 0) && (top5DigiPeakSample < 7);
  case 12:
    return (top5DigiROuter < 0.1) && (top5DigiROuter >= 0.0) && (top5DigiPeakSample > 0) && (top5DigiPeakSample < 7);
  case 13:
    return jet_N>0 && (jetEEm[0] / jetE[0]) > 0.05;
  default:
    return true;
    
  }

}

// return result of a particular cut, after smearing for systematics
bool StoppedHSCPTree::CutNSyst(unsigned n, double smear)
{

  switch (n) {
  case 4:
    if (jet_N>0  && jetEta[0]<1.3) {
      double jetE_syst = jetE[0] * smear;
      return jetE_syst>30.;
    }
    else return false;
  case 5:
    if (jet_N>0  && jetEta[0]<1.3) {
      double jetE_syst = jetE[0] * smear;
      return jetE_syst>50.;
    }
    else return false;
  default:
    return CutN(n);
  }
  
}


bool StoppedHSCPTree::AllCutN(unsigned n)
{
  bool pass=true;
  for (unsigned i=0; i<n; ++i) {
    pass &= CutN(i);
  }
  return pass;
}


const char* StoppedHSCPTree::CutName(unsigned n) {
  
  switch (n) {
  case 0:
    return "HLT";
  case 1:
    return "BX cut";
  case 2:
    return "BPTX cut";
  case 3:
    return "mu veto";
  case 4:
    return "jet30";
  case 5:
    return "jet50";
  case 6:
    return "n60";
  case 7:
    return "n90";
  case 8:
    return "Calo towers";
  case 9:
    return "R1";
  case 10:
    return "R2";
  case 11:
    return "Rpeak";
  case 12:
    return "Router";
  case 13:
    return "jet EMF";
  default:
    return "unknown";
  }

}


// return result of all cuts APART FROM the one specified
bool StoppedHSCPTree::CutNMinusOne(unsigned n) {

  bool pass=true;
  for (unsigned i=0; i<NCuts(); ++i) {
    if (i!=n) pass = pass && CutN(i);
  }
  return pass;

}


// return result of a particular cut
bool StoppedHSCPTree::OldCutN(unsigned n)
{

  switch (n) {
  case 0:
    return true;
    break;
  case 1:
    return (gtAlgoWord1>>(81-64)&1) == 0 && (gtAlgoWord1>>(80-64)&1) == 0;
  case 2:
    return nTowerSameiPhi<5;
  case 3:
    return LeadingCenJetEnergy>30. && LeadingCenJetEta<1.3;
  case 4:
    return LeadingCenJetEnergy>50. && LeadingCenJetEta<1.3;
  case 5:
    return LeadingCenJetn60<6;
  case 6:
    return LeadingCenJetn90>3;
  case 7:
    return NoOfMuons==0;
  case 8:
    return TimingRightPeak > 0.15;
  case 9:
    return TimingFracRightNextRight > 0.1 && TimingFracRightNextRight < 0.5;
  case 10:
    return TimingFracInLeader > 0.4 && TimingFracInLeader < 0.7;
  case 11:
    return (1-TimingFracInCentralFour) < 0.1;
  default:
    return true;
  }

}

// return result of a particular cut
bool StoppedHSCPTree::StdHcalCutN(unsigned n)
{
  
  switch (n) {
  case 0:
    return true;
    break;
  case 1:
    return jet_N>0 && jetE[0]>50. && jetEta[0]<1.3;
    break;
  case 2:
    return mu_N==0;
    break;
  case 3:
    return !(noiseMinE2Over10TS < 0.70);
    break;
  case 4:
    return !(noiseMaxE2Over10TS > 0.96);
    break;
  case 5:
    return !(noiseMaxHPDHits >= 17);
    break;
  case 6:
    return !(noiseMaxRBXHits >= 999);
    break;
  case 7:
    return !(noiseMaxHPDNoOtherHits >= 10);
    break;
  case 8:
    return !(noiseMaxZeros >= 10);
    break;
  case 9:
    return !(noiseMin25GeVHitTime < -9999.0);
    break;
  case 10:
    return !(noiseMax25GeVHitTime > 9999.0);
    break;
  case 11:
    return !(noiseMinRBXEMF < 0.01);
    break;
  default:
    return false;
    break; 
  }

}
  

void StoppedHSCPTree::PrintCutValues(ostream& o) {

  o << "Stopped HSCP Event" << std::endl;
  o << "  id             = " << id << std::endl;
  o << "  lb             = " << lb << std::endl;
  o << "  run            = " << run << std::endl;
  o << "  nTowerSameiPhi = " << nTowerSameiPhi << std::endl;
  o << "  jetE[0]        = " << jetE[0] << std::endl;
  o << "  jetEta[0]      = " << jetEta[0] << std::endl;
  o << "  jetN60[0]      = " << jetN60[0] << std::endl;
  o << "  jetN90[0]      = " << jetN90[0] << std::endl;
  o << "  mu_N           = " << mu_N << std::endl;
  o << "  top5DigiR1     = " << top5DigiR1 << std::endl;
  o << "  top5DigiR2     = " << top5DigiR2 << std::endl;
  o << "  top5DigiRPeak  = " << top5DigiRPeak << std::endl;
  o << "  top5DigiROuter = " << top5DigiROuter << std::endl;
  o << "  jetEMF[0]      = " << (jetEEm[0] / jetEHad[0]) << std::endl;
  o << "  time sample    = ";
  for (unsigned i=0; i<10; ++i) o << top5DigiTimeSamples.at(i) << " ";
  o << std::endl;
  o << std::endl;
}

  
bool StoppedHSCPTree::InDisallowedBX() {

  bool passed=false;
  for (unsigned i=0; i<disallowedBXs_.size(); ++i) {
    passed |= (bx==disallowedBXs_.at(i));
  }
  return passed;
}

void StoppedHSCPTree::SetDisallowedBXs(std::vector<unsigned> bxs) {
  disallowedBXs_ = bxs;
}

#endif

