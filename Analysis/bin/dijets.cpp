//
// Program to make some histograms from a StoppedHSCP TTree
// Jim Brooke, April 2010
// 

#include "StoppedHSCPTree.h"
#include "TFile.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TMath.h"
#include "TCanvas.h"
#include "TLorentzVector.h"
#include "TStyle.h"

#include <vector>


int main() {

  gROOT->ProcessLine(".L ~/root/tdrstyle.C");
  gROOT->ProcessLine("setTDRStyle()");

  TH1::SetDefaultSumw2();

  TFile file("ntuples/stoppedHSCP_tree_Coll10_JetsRun2010A_May27th_v1.root");

  StoppedHSCPTree* tree = new StoppedHSCPTree(&file, false);

  TH1D* hmass = new TH1D("hmass", "Dijet inv mass", 50, 0., 500.);
  TH1D* hmass2 = new TH1D("hmass2", "Dijet inv mass", 50, 0., 500.);
  TH1D* hdr = new TH1D("hdr", "delta R", 100, 0., 2*TMath::Pi());

  if (tree->fChain == 0) return 1;

  Long64_t nentries = tree->fChain->GetEntriesFast();
  Long64_t nbytes = 0, nb = 0;

  unsigned nmu=0;
  unsigned njet=0;

  for (Long64_t jentry=0; jentry<nentries; jentry++) {
    
    if (jentry%100000==0) {
      std::cout << "Processing " << jentry << "th event" << std::endl;
    }
    
    // this bit is ridiculous, isn't it
    Long64_t ientry = tree->LoadTree(jentry);
    if (ientry < 0) break;
    nb = tree->fChain->GetEntry(jentry);
    nbytes += nb;
 
    // require bptx coincidence
    if (tree->gtTechWord&1 == 0) continue;

    // n jets
    unsigned nj=0;
    for (unsigned ij=0; ij<tree->jet_N; ++ij) {
      if (tree->jetE[ij]>2.) nj++;
    }
    if (nj != 2) continue;
    
    // check if leading two jets pass cuts
    if (tree->jetEt[0] > 15. && tree->jetEt[1] > 15. &&  // Et
	tree->jetPhi[0] < 1.3 && tree->jetPhi[1] < 1.3 &&  // eta
	(tree->jetEEm[0]/tree->jetE[0]) > 0.01 && (tree->jetEEm[1]/tree->jetE[1]) > 0.01) {  // EMF
      
      TLorentzVector j1, j2, mu, mass;
      j1.SetPtEtaPhiE(tree->jetEt[0], tree->jetEta[0], tree->jetPhi[0], tree->jetE[0]);
      j2.SetPtEtaPhiE(tree->jetEt[1], tree->jetEta[1], tree->jetPhi[1], tree->jetE[1]);
      
      // require back to back jets
      double dphi = fabs(j1.Phi() - j2.Phi());
      if ( fabs(dphi-TMath::Pi()) < 0.25) {
	mass = j1 + j2;
	hmass->Fill(mass.M());      
	njet++;

	if (tree->mu_N > 0) {
	  hmass2->Fill(mass.M());
	  nmu++;
	  double dr=999.;
	  for (unsigned im=0; im<tree->mu_N; ++im) {
	    for (unsigned ij=0; ij<tree->jet_N; ++ij) {
	      double djmeta=fabs(tree->jetEta[ij] - tree->muEta[im]);
	      double djmphi=fabs(tree->jetPhi[ij] - tree->muPhi[im]);
	      if (sqrt((djmeta * djmeta) + (djmphi * djmphi)) < dr) {
		dr = sqrt((djmeta * djmeta) + (djmphi * djmphi));
	      }
	    }
	    hdr->Fill(dr);
	  }
	}
      
      }
    }

  } 
  
  // end of loop, plot histos
  
  std::cout << "N dijet events\t\t" << njet << std::endl;
  std::cout << "N dijet eventsw muon\t" << nmu << std::endl;


  gStyle->SetOptStat(1);

  TCanvas c("canvas");

  c.SetLogy(1);

  hmass->GetYaxis()->SetTitle("events");
  hmass->GetXaxis()->SetTitle("M_{jj} (GeV)");

  hmass2->SetLineColor(2);
  hmass2->SetMarkerColor(2);
  hmass2->SetMarkerStyle(22);

  hmass->Draw("E");
  hmass2->Draw("SAME E");

  c.Print("DijetMass.pdf");
  c.Print("DijetMass.C");

  hmass2->Divide(hmass);

  hmass2->Draw("E");
  c.Update();
  c.Print("MuRatio.pdf");
  c.Print("MuRatio.C");

  c.SetLogy(0);


  hdr->Draw("E");
  c.Update();
  c.Print("DeltaR.pdf");
  c.Print("DeltaR.C");
    
}
