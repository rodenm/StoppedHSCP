//
//  Extended version of MakeClass output
//  Jim Brooke 21/4/2010
//
//  Added ctor from filename
//  Added nCut method - return true/false if currently loaded event passes n-th cut
//

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

class StoppedHSCPTree {
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

   StoppedHSCPTree(char* filename);
   StoppedHSCPTree(TTree *tree=0);
   virtual ~StoppedHSCPTree();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
   virtual bool     CutN(unsigned n);
};

StoppedHSCPTree::StoppedHSCPTree(char* filename) {

  // open file and get tree
  TFile file(filename);
  TTree* tree = (TTree*) file.Get("stoppedHSCPTree/StoppedHSCPTree");

  Init(tree);

}

StoppedHSCPTree::StoppedHSCPTree(TTree *tree)
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("ntuples/stoppedHSCP_tree_Comm10_Promptv3_v3.root");
      if (!f) {
         f = new TFile("ntuples/stoppedHSCP_tree_Comm10_Promptv3_v3.root");
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

Int_t StoppedHSCPTree::Cut(Long64_t entry=0)
{
  // This function may be called from Loop.
  // returns  1 if entry is accepted.
  // returns -1 otherwise.
  bool pass=false;

  for (unsigned i=0; i<11; ++i) {
    pass &= CutN(i);
  }
  
  if (pass) return 1;
  else return -1;

}

bool StoppedHSCPTree::CutN(unsigned n)
{
  bool passed=true;
  
  switch (n) {
  case 0:
    return true;
    break;
  case 1:
    return nTowerSameiPhi<5;
    break;
  case 2:
    return jetE[0]>30. && jetEta[0]<1.3;
    break;
  case 3:
    return jetE[0]>50. && jetEta[0]<1.3;
    break;
  case 4:
    return jetN60[0]<6;
    break;
  case 5:
    return jetN90[0]>3;
    break;
  case 6:
    return mu_N==0;
    break;
  case 7:
    return top5DigiR1 > 0.15;
    break;
  case 8:
    return top5DigiR2 > 0.1 && top5DigiR2 < 0.5;
    break;
  case 9:
    return top5DigiRPeak > 0.4 && top5DigiRPeak < 0.7;
    break;
  case 10:
    return top5DigiROuter < 0.1;
    break;
  case 11:
    return jetEEm[0] / jetEHad[0] > 0.05;
  default:
    return false;
    
  }

}

#endif

