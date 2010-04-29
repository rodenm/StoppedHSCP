//
// Program to make some histograms from a StoppedHSCP TTree
// Jim Brooke, April 2010
// 

#include "StoppedHSCPTree.h"
#include "TFile.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TMath.h"
#include <vector>

#include <string>
#include <stdlib.h>
#include <iostream>
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>


TH1D* hbx_;
TH1D* horb_;
TH1D* hlb_;
TH1D* htime_;
TH1D* hl1et_;
TH1D* hl1eta_;
TH1D* hl1phi_;
TH1D* hl1type_;
TH1D* hhlte_;
TH1D* hhlteta_;
TH1D* hhltphi_;
TH1D* hjete_;
TH1D* hjeteta_;
TH1D* hjetphi_;
TH2D* hjetetaphi_;
TH1D* hjeteem_;
TH1D* hjetehad_;
TH1D* hjetemf_;
TH1D* hjetn60_;
TH1D* hjetn90_;
TH1D* hjetn90hits_;
TH1D* hjetfhpd_;
TH1D* hnmu_;
TH2D* hmuetaphi_;
TH1D* hntowsameiphi_;
TH2D* htowietaiphi_;
TH1D* hr1_;
TH1D* hr2_;
TH1D* hrpk_;
TH1D* hrout_;
TH2D* hr1r2_;
TH2D* hpkout_;
TH1D* hncutind_;
TH1D* hncutcum_;
TH1D* hnminus1cut_;

// histograms after each cut
std::vector<TH1D*> hjete_cuts_;
std::vector<TH2D*> hjetetaphi_cuts_;
std::vector<TH2D*> hmuetaphi_cuts_;
std::vector<TH1D*> hbx_cuts_;
std::vector<TH1D*> hjetemf_cuts_;


StoppedHSCPTree* tree_;
std::string outdir_;
unsigned nlimit_;
bool dumpEvents_;
unsigned nCuts_=12;

void bookHistos() {
  
  // time
  hbx_ = new TH1D("hbx", "BX number", 3564, 0., 3564.);
  horb_ = new TH1D("horb", "Orbit number", 100, 0., 10000.);
  hlb_ = new TH1D("hlb", "Lumi block", 2000, 0., 2000.);
  htime_ = new TH1D("htime", "Event time", 100, 0., 1.E8);
  
  // L1
  hl1et_ = new TH1D("hl1et",  "Leading L1 jet E_{t}", 100, 0., 200.);
  hl1eta_ = new TH1D("hl1eta", "Leading L1 jet #eta", 70, -3.5, 3.5);
  hl1phi_ = new TH1D("hl1phi", "Leading L1 jet #phi", 72, -1 * TMath::Pi(),  TMath::Pi());
  hl1type_ = new TH1D("hl1type",  "Leading L1 jet type", 3, 0., 3.);

  // HLT
  hhlte_ = new TH1D("hhlte",  "Leading HLT jet E", 100, 0., 200.);
  hhlteta_ = new TH1D("hhlteta", "Leading HLT jet #eta", 70, -3.5, 3.5);
  hhltphi_ = new TH1D("hhltphi", "Leading HLT jet #phi", 72, -1 * TMath::Pi(),  TMath::Pi());
	
  // calo towers
  hntowsameiphi_ = new TH1D("hntowsamephi", "N leading towers at same iphi", 20, -0.5, 19.5);
  htowietaiphi_ = new TH2D("htowietaiphi", "Leading tower position", 100, -50., 50., 75, 0., 75.);

  // jets
  hjete_ = new TH1D("hjete", "Leading jet energy", 50, 0., 200.);
  hjeteta_ = new TH1D("hjeteta", "Leading jet #eta", 70, -3.5, 3.5);
  hjetphi_ = new TH1D("hjetphi", "Leading jet #phi", 60, -1 * TMath::Pi(),  TMath::Pi());
  hjetetaphi_ = new TH2D("hjetetaphi", "Leading jet pos", 70, -3.5, 3.5, 72, -1 * TMath::Pi(),  TMath::Pi());
  hjeteem_ = new TH1D("hjeteem", "Leading jet ECAL energy", 100, 0., 200.);
  hjetehad_ = new TH1D("hjetehad", "Leading jet HCAL energy", 100, 0., 200.);
  hjetemf_ =  new TH1D("hjetemf", "Leading jet EM fraction", 100, 0., 1.);
  hjetn60_ = new TH1D("hjetn60", "Leading jet N60", 50, 0., 50.);
  hjetn90_ = new TH1D("hjetn90", "Leading jet N90", 50, 0., 50.);
  hjetn90hits_ = new TH1D("hjetn90hits", "Leading jet N90 hits", 50, 0., 50.);
  hjetfhpd_ = new TH1D("hjetfhpd", "Leading jet fHPD", 50, 0., 1.);

  // muons
  hnmu_ = new TH1D("hnmu", "N muons", 4, -0.5, 3.5);
  hmuetaphi_ = new TH2D("hmuetaphi", "Muon pos", 70, -3.5, 3.5, 72, -1 * TMath::Pi(),  TMath::Pi());

  // pulse shape
  hr1_ = new TH1D("hr1", "R_{1}", 50, 0., 1.);
  hr2_ = new TH1D("hr2", "R_{2}", 50, 0., 1.);
  hrpk_ = new TH1D("hrpk", "R_{peak}", 50, 0., 1.);
  hrout_ = new TH1D("hrout", "R_{outer}", 30, 0., 1.);    
  hr1r2_ = new TH2D("hr1r2", "R_{1} vs R_{2}", 50, 0., 1., 50, 0., 1.);
  hpkout_ = new TH2D("hpkout", "R_{peak} vs R_{outer}", 50, 0., 1., 50, 0., 1.);

  // cut counts
  hncutind_ = new TH1D("hncutind", "Cut counts", 20, 0., 20.);
  hncutcum_ = new TH1D("hncutcum", "Cumulative cut counts", 20, 0., 20.);
  hnminus1cut_ = new TH1D("hnminus1cut", "N-1 cut counts", 20, 0., 20.);

  // histograms per cut
  for (unsigned i=0; i<nCuts_; ++i) {
    std::stringstream istr;
    istr << i;
    hjete_cuts_.push_back(new TH1D((std::string("hjete")+istr.str()).c_str(), "Leading jet energy", 50, 0., 200.));
    hjetetaphi_cuts_.push_back(new TH2D((std::string("hjetetaphi")+istr.str()).c_str(), "Leading jet pos", 70, -3.5, 3.5, 72, -1 * TMath::Pi(),  TMath::Pi()));
    hmuetaphi_cuts_.push_back(new TH2D((std::string("hmuetaphi")+istr.str()).c_str(), "Muon pos", 70, -3.5, 3.5, 72, -1 * TMath::Pi(),  TMath::Pi()));
    hbx_cuts_.push_back(new TH1D((std::string("hbx")+istr.str()).c_str(), "BX number", 3564, 0., 3564.));
    hjetemf_cuts_.push_back(new TH1D((std::string("hjetemf")+istr.str()).c_str(), "Leading jet EM fraction", 100, 0., 1.));
  }

}


// delete all histogram objects
void deleteHistos() {

  if (hbx_ != 0){
    delete hbx_;
    delete horb_;
    delete hlb_;
    delete htime_;
    delete hl1et_;
    delete hl1eta_;
    delete hl1phi_;
    delete hl1type_;
    delete hhlte_;
    delete hhlteta_;
    delete hhltphi_;
    delete hjete_;
    delete hjeteta_;
    delete hjetphi_;
    delete hjetetaphi_;
    delete hjeteem_;
    delete hjetehad_;
    delete hjetemf_;
    delete hjetn60_;
    delete hjetn90_;
    delete hjetn90hits_;
    delete hjetfhpd_;
    delete hnmu_;
    delete hmuetaphi_;
    delete hntowsameiphi_;
    delete htowietaiphi_;
    delete hr1_;
    delete hr2_;
    delete hrpk_;
    delete hrout_;
    delete hr1r2_;
    delete hpkout_;
    delete hncutind_;
    delete hncutcum_;
    delete hnminus1cut_;

    for (unsigned i=0; i< hjete_cuts_.size(); ++i) {
      delete hjete_cuts_.at(i);
      delete hjetetaphi_cuts_.at(i);
      delete hmuetaphi_cuts_.at(i);
      delete hbx_cuts_.at(i);
      delete hjetemf_cuts_.at(i);
    }
    hjete_cuts_.clear();
    hjetetaphi_cuts_.clear();
    hmuetaphi_cuts_.clear();
    hbx_cuts_.clear();
    hjetemf_cuts_.clear();
  }
  
}


// fill all histograms for current event
void fillHistos(StoppedHSCPTree& tree) {

  hbx_->Fill(tree.bx);
  horb_->Fill(tree.orbit);
  hlb_->Fill(tree.lb);
  htime_->Fill(tree.time);
  if (tree.l1Jet_N > 0) {
    hl1et_->Fill(tree.l1JetE.at(0));
    hl1eta_->Fill(tree.l1JetEta.at(0));
    hl1phi_->Fill(tree.l1JetPhi.at(0));
    hl1type_->Fill(tree.l1JetType.at(0));
  }
  if (tree.hltJet_N > 0) {
    hhlte_->Fill(tree.hltJetE.at(0));
    hhlteta_->Fill(tree.hltJetEta.at(0));
    hhltphi_->Fill(tree.hltJetPhi.at(0));
  }
  if (tree.jet_N > 0) {
    hjete_->Fill(tree.jetE.at(0));
    hjeteta_->Fill(tree.jetEta.at(0));
    hjetphi_->Fill(tree.jetPhi.at(0));
    hjetetaphi_->Fill(tree.jetEta.at(0), tree.jetPhi.at(0));
    hjeteem_->Fill(tree.jetEEm.at(0));
    hjetehad_->Fill(tree.jetEHad.at(0));
    hjetemf_->Fill(tree.jetEEm.at(0)/tree.jetE.at(0));
    hjetn60_->Fill(tree.jetN60.at(0));
    hjetn90_->Fill(tree.jetN90.at(0));
    hjetn90hits_->Fill(0.);
    hjetfhpd_->Fill(0.);
  }
  hnmu_->Fill(tree.mu_N);
  if (tree.mu_N>0) {
    hmuetaphi_->Fill(tree.muEta.at(0), tree.muPhi.at(0));
  }
  hntowsameiphi_->Fill(tree.nTowerSameiPhi);
  if (tree.tower_N>0) {
    htowietaiphi_->Fill(tree.towerIEta.at(0), tree.towerIPhi.at(0));
  }
  hr1_->Fill(tree.top5DigiR1);
  hr2_->Fill(tree.top5DigiR2);
  hrpk_->Fill(tree.top5DigiRPeak);
  hrout_->Fill(tree.top5DigiROuter);
  hr1r2_->Fill(tree.top5DigiR1, tree.top5DigiR2);
  hpkout_->Fill(tree.top5DigiRPeak, tree.top5DigiROuter);

  // loop over cuts
  bool fail=false;
  for (unsigned c=0; c<nCuts_; c++) {
    if (tree.CutN(c)) hncutind_->Fill(c);
    if (tree.CutNMinusOne(c)) hnminus1cut_->Fill(c);
    else fail |= true;
    if (!fail) {
      hncutcum_->Fill(c);
      if (tree.jet_N>0) {
	hjete_cuts_.at(c)->Fill(tree.jetE.at(0));
	hjetetaphi_cuts_.at(c)->Fill(tree.jetEta.at(0), tree.jetPhi.at(0));
	hjetemf_cuts_.at(c)->Fill(tree.jetEEm.at(0)/tree.jetE.at(0));
      }
      if (tree.mu_N>0) {
	hmuetaphi_cuts_.at(c)->Fill(tree.muEta.at(0), tree.muPhi.at(0));
      }
      hbx_cuts_.at(c)->Fill(tree.bx);
    }
  }

}

// make a histogram of means of bins of existing histogram
TH1D rateDist(TH1D& hist, unsigned nbins) {

  std::string name=std::string(hist.GetName())+"dist";
  TH1D h(name.c_str(), "Rate", nbins, hist.GetMinimum()*0.8, hist.GetMaximum()*1.25);

  // fill histogram
  for (unsigned i=0; i<hist.GetNbinsX(); ++i) {
    unsigned r=hist.GetBinContent(i);
    if (r>0.) h.Fill(r);
  }
	
  // do fit
  //  TF1 f("fit", "gaus");
  //  h.Fit("fit", "");    
	
  h.Write();

  return h;

}


// write a file of histograms
void writeHistos(unsigned run) {

  std::string filename=outdir_ + "/histograms";
  if (run>0) {
    char runstr[10];
    sprintf(runstr, "%d", run);
    filename += runstr;
  }
  filename += ".root";

  TFile ofile(filename.c_str(), "recreate");

  ofile.mkdir("NoCuts");
  ofile.cd("NoCuts");

  hbx_->Write();
  horb_->Write();
  hlb_->Write();

  rateDist(*hlb_, 100);

  htime_->Write();
  hl1et_->Write();
  hl1eta_->Write();
  hl1phi_->Write();
  hl1type_->Write();
  hhlte_->Write();
  hhlteta_->Write();
  hhltphi_->Write();
  hntowsameiphi_->Write();
  htowietaiphi_->Write();
  hjete_->Write();
  hjeteta_->Write();
  hjetphi_->Write();
  hjetetaphi_->Write();
  hjeteem_->Write();
  hjetehad_->Write();
  hjetemf_->Write();
  hjetn60_->Write();
  hjetn90_->Write();
  hjetn90hits_->Write();
  hjetfhpd_->Write();
  hnmu_->Write();
  hmuetaphi_->Write();
  hr1_->Write();
  hr2_->Write();
  hrpk_->Write();
  hrout_->Write();
  hr1r2_->Write();
  hpkout_->Write();
  hncutind_->Write();
  hncutcum_->Write();
  hnminus1cut_->Write();

  ofile.mkdir("Cuts");
  ofile.cd("Cuts");

  for (unsigned i=0; i< hjete_cuts_.size(); ++i) {
    hjete_cuts_.at(i)->Write();
    hjetetaphi_cuts_.at(i)->Write();
    hmuetaphi_cuts_.at(i)->Write();
    hbx_cuts_.at(i)->Write();
    hjetemf_cuts_.at(i)->Write();
  }
 
  ofile.Close();

}


// loop over all events, filling histograms
void loopAll() {

  deleteHistos();
  bookHistos();

  // set up loop
  if (tree_->fChain == 0) return;
  Long64_t nentries = tree_->fChain->GetEntriesFast();
  Long64_t nbytes = 0, nb = 0;
  unsigned nevts=0;

  // run loop
  for (Long64_t jentry=0; jentry<nentries && jentry<nlimit_; jentry++) {

    if (jentry%100000==0) {
      std::cout << "Processing " << jentry << "th event" << std::endl;
    }
    
    // this bit is ridiculous, isn't it
    Long64_t ientry = tree_->LoadTree(jentry);
    if (ientry < 0) break;
    nb = tree_->fChain->GetEntry(jentry);
    nbytes += nb;
    
    fillHistos(*tree_);
    nevts++;

    if (tree_->Cut() && dumpEvents_) tree_->Show();
    
  }

  writeHistos(0);

}


// loop over all events, clear histograms and write file for each run
void loopByRun() {

  // set up loop
  if (tree_->fChain == 0) return;
  Long64_t nentries = tree_->fChain->GetEntriesFast();
  Long64_t nbytes = 0, nb = 0;

  unsigned currentRun=0;
  unsigned nevts=0;

  // run loop
  for (Long64_t jentry=0; jentry<nentries && jentry<nlimit_; jentry++) {

    if (jentry%100000==0) {
      std::cout << "Processing " << jentry << "th event" << std::endl;
    }

    // this bit is ridiculous, isn't it
    Long64_t ientry = tree_->LoadTree(jentry);
    if (ientry < 0) break;
    nb = tree_->fChain->GetEntry(jentry);
    nbytes += nb;

    // check if the run changed
    if (tree_->run != currentRun) {

      // write file
      if (currentRun != 0) {
	writeHistos(currentRun);
	std::cout << "Found " << nevts << " events in run " << currentRun << std::endl;
	nevts=0;
      }
      
      // and reset histograms etc
      deleteHistos();
      bookHistos();
      currentRun = tree_->run;

    }
    // otherwise just fill the histograms
    else {
      
      fillHistos(*tree_);
      nevts++;

    }
    
  }

}




int main(int argc, char* argv[]) {

  if (argc < 3) {
    std::cout << "Insufficient arguments" << std::endl;
    std::cout << "Usage : BasicHistograms <filename> <label>" << std::endl;
    exit(1);
  }

  // options
  nlimit_=999999999;
  for (int i=1; i<argc; ++i) {
    // check option flags
    std::string opt = argv[i];
    if (opt=="-d") {
      nlimit_=1000;
    }
  }

  if (nlimit_<999999999) std::cout << "Running on " << nlimit_ << " events per run" << std::endl;

  // filename
  char* filename = argv[argc-2];
  std::cout << "Going to run on " << filename << std::endl;

  // open file and get tree
  TFile file(filename);
  TTree* ttree = (TTree*) file.Get("stoppedHSCPTree/StoppedHSCPTree");
  tree_ = new StoppedHSCPTree(ttree);

  // label/directory
  outdir_ = argv[argc-1];
  std::cout << "Putting results in directory " << outdir_ << std::endl;


  // make histograms for all events
  loopAll();

  // make histograms for each run
  loopByRun();

  // clean up
  file.Close();

}
  // make histograms for each run
//   std::string runlist = argv[argc-1];
//   std::vector<std::string> runStrs;
//   boost::split(runStrs, runlist, boost::is_any_of(","));
//   std::vector<unsigned> runs;
//   for (std::vector<std::string>::const_iterator runStr=runStrs.begin();
//        runStr!=runStrs.end();
//        ++runStr) runs.push_back( boost::lexical_cast<unsigned>(runStr->c_str()) );



