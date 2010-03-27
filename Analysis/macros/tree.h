//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Fri Mar 26 23:47:49 2010 by ROOT version 5.22/00
// from TTree StoppedHSCPTree/
// found on file: ntuples/stoppedHSCPTree_Coll09_Dec19th_v2.root
//////////////////////////////////////////////////////////

#ifndef tree_h
#define tree_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

#include <iostream>
#include <fstream>


class tree {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

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
   Double_t        vtxX;
   Double_t        vtxY;
   Double_t        vtxZ;
   Double_t        vtxR;
   Double_t        vtxT;
   UInt_t          rHadPdgId;
   Double_t        rHadE;
   Double_t        rHadPx;
   Double_t        rHadPy;
   Double_t        rHadPz;
   Double_t        rHadPt;
   UInt_t          nTowerSameiPhi;
   UInt_t          nL1Jet;
 //shscp::TrigJet  l1Jets[10];
   UInt_t          nHltJet;
 //shscp::TrigJet  hltJets[10];
   UInt_t          nMCDecay;
 //shscp::MCDecay  mcDecays[10];
   UInt_t          nJet;
 //shscp::Jet      jets[20];
   UInt_t          nMuon;
 //shscp::Muon     muons[4];
   UInt_t          nTower;
 //shscp::Tower    towers[100];
   UInt_t          nHpd;
 //shscp::HPD      hpds[10];
   UInt_t          nDigi;
 //shscp::HcalDigi digis[100];

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
   Float_t         TimingTotal;
   Float_t         TimingNoOfChannels;
   Float_t         TimingEnergyBeforePorch;
   Float_t         TimingEnergyBeforePeak;
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
   Float_t         TimingRightNextRight;
   Float_t         TimingPeakNextRight;
   Float_t         TimingFracInCentralFour;
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
   TBranch        *b_events_vtxX;   //!
   TBranch        *b_events_vtxY;   //!
   TBranch        *b_events_vtxZ;   //!
   TBranch        *b_events_vtxR;   //!
   TBranch        *b_events_vtxT;   //!
   TBranch        *b_events_rHadPdgId;   //!
   TBranch        *b_events_rHadE;   //!
   TBranch        *b_events_rHadPx;   //!
   TBranch        *b_events_rHadPy;   //!
   TBranch        *b_events_rHadPz;   //!
   TBranch        *b_events_rHadPt;   //!
   TBranch        *b_events_nTowerSameiPhi;   //!
   TBranch        *b_events_nL1Jet;   //!
   TBranch        *b_events_nHltJet;   //!
   TBranch        *b_events_nMCDecay;   //!
   TBranch        *b_events_nJet;   //!
   TBranch        *b_events_nMuon;   //!
   TBranch        *b_events_nTower;   //!
   TBranch        *b_events_nHpd;   //!
   TBranch        *b_events_nDigi;   //!

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
   TBranch        *b_LeadingJetEta;   //!
   TBranch        *b_LeadingJetEnergy;   //!
   TBranch        *b_LeadingJetEt;   //!
   TBranch        *b_LeadingCenJetEta;   //!
   TBranch        *b_LeadingCenJetEta;   //!
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
   TBranch        *b_TimingRightNextRight;   //!
   TBranch        *b_TimingPeakNextRight;   //!
   TBranch        *b_TimingFracInCentralFour;   //!
   TBranch        *b_TimingTotal;   //!
   TBranch        *b_TimingPeakPosition;   //!
   TBranch        *b_TimingTotalOverTime;   //!
   TBranch        *b_TimingRightNextNextRight;   //!
   TBranch        *b_TimingPeakNextNextRight;   //!
   TBranch        *b_NoOfMuons;   //!
   TBranch        *b_EventID;   //!
   TBranch        *b_RunNumber;   //!
   TBranch        *b_LumiNumber;   //!
   TBranch        *b_TimeStamp;   //!

   ofstream log;

   tree(TTree *tree=0);
   virtual ~tree();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);

};

#endif

#ifdef tree_cxx
tree::tree(char* fname)
{
  if (fname == "") {
    rf = new TFile("stoppedHSCPTree.root");
  } else {
    rf = new TFile(fname);
  }
  TTree* tree = (TTree*)rf->Get("stoppedHSCPTree/StoppedHSCPTree");
  TTree* oldtree = (TTree*)rf->Get("globalRunAnalyser/EventTree");
  tree->AddFriend(oldtree);
  Init(tree);

}

tree::~tree()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t tree::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t tree::LoadTree(Long64_t entry)
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

void tree::Init(TTree *tree)
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
   fChain->SetBranchAddress("vtxX", &vtxX, &b_events_vtxX);
   fChain->SetBranchAddress("vtxY", &vtxY, &b_events_vtxY);
   fChain->SetBranchAddress("vtxZ", &vtxZ, &b_events_vtxZ);
   fChain->SetBranchAddress("vtxR", &vtxR, &b_events_vtxR);
   fChain->SetBranchAddress("vtxT", &vtxT, &b_events_vtxT);
   fChain->SetBranchAddress("rHadPdgId", &rHadPdgId, &b_events_rHadPdgId);
   fChain->SetBranchAddress("rHadE", &rHadE, &b_events_rHadE);
   fChain->SetBranchAddress("rHadPx", &rHadPx, &b_events_rHadPx);
   fChain->SetBranchAddress("rHadPy", &rHadPy, &b_events_rHadPy);
   fChain->SetBranchAddress("rHadPz", &rHadPz, &b_events_rHadPz);
   fChain->SetBranchAddress("rHadPt", &rHadPt, &b_events_rHadPt);
   fChain->SetBranchAddress("nTowerSameiPhi", &nTowerSameiPhi, &b_events_nTowerSameiPhi);
   fChain->SetBranchAddress("nL1Jet", &nL1Jet, &b_events_nL1Jet);
   fChain->SetBranchAddress("nHltJet", &nHltJet, &b_events_nHltJet);
   fChain->SetBranchAddress("nMCDecay", &nMCDecay, &b_events_nMCDecay);
   fChain->SetBranchAddress("nJet", &nJet, &b_events_nJet);
   fChain->SetBranchAddress("nMuon", &nMuon, &b_events_nMuon);
   fChain->SetBranchAddress("nTower", &nTower, &b_events_nTower);
   fChain->SetBranchAddress("nHpd", &nHpd, &b_events_nHpd);
   fChain->SetBranchAddress("nDigi", &nDigi, &b_events_nDigi);

   // old tree
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
   fChain->SetBranchAddress("LeadingJetPhi", &LeadingJetPhi, &b_LeadingJetEta);
   fChain->SetBranchAddress("LeadingJetEnergy", &LeadingJetEnergy, &b_LeadingJetEnergy);
   fChain->SetBranchAddress("LeadingJetEt", &LeadingJetEt, &b_LeadingJetEt);
   fChain->SetBranchAddress("LeadingCenJetEta", &LeadingCenJetEta, &b_LeadingCenJetEta);
   fChain->SetBranchAddress("LeadingCenJetPhi", &LeadingCenJetPhi, &b_LeadingCenJetEta);
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
   fChain->SetBranchAddress("TimingFracRightNextRight", &TimingFracRightNextRight, &b_TimingFracRightNextRight);
   fChain->SetBranchAddress("TimingFracPeakNextRight", &TimingFracPeakNextRight, &b_TimingFracPeakNextRight);
   fChain->SetBranchAddress("TimingFracInCentralFour", &TimingFracInCentralFour, &b_TimingFracInCentralFour);
   fChain->SetBranchAddress("TimingTotal", &TimingTotal, &b_TimingTotal);
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

   Notify();
}

Bool_t tree::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void tree::Show(Long64_t entry)
{

  using namespace std;
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
    cout << "jet e            = " << LeadingCenJetEnergy << endl;
    cout << "jet eta          = " << LeadingCenJetEta << endl;
    cout << "jet phi          = " << LeadingCenJetPhi << endl;
    cout << "jet n60          = " << LeadingCenJetn60 << endl;
    cout << "jet n90          = " << LeadingCenJetn90 << endl;
    cout << "nmu              = " << NoOfMuons << endl;
    cout << "R1               = " << TimingRightPeak << endl;
    cout << "R2               = " << TimingFracRightNextRight << endl;
    cout << "Rpeak            = " << TimingFracInLeader << endl;
    cout << "Rout             = " << (1. - TimingFracInCentralFour) << endl;
}
Int_t tree::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.

  if ((lb==2 && id==628807) ||
      (lb==3 && id==944473) ||
      (lb==4 && id==1239986) ||
      (lb==13 && id==3777393) ||
      (lb==23 && id==7569416) ||
      (lb==33 && id==11445910) ||
      (lb==35 && id==12269330) ||
      (lb==35 && id==12344410) ||
      (lb==37 && id==12901605) ||
      (lb==41 && id==14440923) ||
      (lb==45 && id==15877224) ||
      (lb==45 && id==16175671) ||
      (lb==49 && id==16984520) ||
      (lb==51 && id==17874221) ||
      (lb==52 && id==18238333) ||
      (lb==53 && id==18497167) ||
      (lb==54 && id==19159387) ||
      (lb==59 && id==21088247) ||
      (lb==60 && id==21144963) ||
      (lb==65 && id==23254318) ||
      (lb==68 && id==24450917) &&

      run==124230 )//&&
/*       nTowerSameiPhi<5 &&  */
/*       LeadingCenJetEnergy>30. && */
/*       LeadingCenJetEnergy>50. && */
/*       LeadingCenJetn60<6 && */
/*       LeadingCenJetn90>3 && */
/*       nMuon==0 )//&& */
/*       TimingRightPeak>0.15 && */
/*       TimingFracRightNextRight>0.1 && TimingFracRightNextRight<0.5 && */
/*       TimingFracInLeader>0.4 && TimingFracInLeader<0.7 && */
/*       TimingFracInCentralFour>0.90) */
    { 
   return 1;
  }
  else return -1;
}
#endif // #ifdef tree_cxx

