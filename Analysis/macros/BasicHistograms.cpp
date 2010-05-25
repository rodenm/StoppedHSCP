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

#include <sys/stat.h>
#include <stdlib.h>


class Analysis {

public:
  Analysis(const char* filename, const char* outdir, unsigned nlimit=999999999, bool dump=false);
  ~Analysis();

  void bookHistos();
  void writeHistos();
  void deleteHistos();
  void getHistos();
  void fillHistos(StoppedHSCPTree& tree);

  TH1D rateDist(TH1D& hist, unsigned nbins);
 
  void newHistos(unsigned run);
  void saveHistos();
  void loopAll();
  void loopByRun();

  void cutAxisLabels(TH1D* h);

private:

  TFile file_;            // input file
  TTree* ttree_;          // input TTree (stupid ROOT)
  StoppedHSCPTree* tree_; // tree (makeClass output)
  std::string outdir_;    // output directory
  TFile* ofile_;          // current output file
  unsigned nlimit_;       // limited number of events per run
  bool dumpEvents_;       // dump events passing all cuts if true
  unsigned nCuts_;     // number of cuts
  unsigned currentRun_;   // current run #
  unsigned nHcalCuts_;     // number of cuts

  // the histograms
  TH1D* hbx_;
  TH1D* horb_;
  TH1D* hlb_;
  TH1D* htime_;
  TH1D* hl1bits_;
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
  TH1D* hpksample_;
  TH1D* hr1_;
  TH1D* hr2_;
  TH1D* hrpk_;
  TH1D* hrout_;
  TH2D* hr1r2_;
  TH2D* hpkout_;
  TH1D* hr1_old_;
  TH1D* hr2_old_;
  TH1D* hrpk_old_;
  TH1D* hrout_old_;
  TH1D* hbxup_;

  TH1D* hncutind_;
  TH1D* hncutcum_;
  TH1D* hnminus1cut_;
  TH1D* holdcutind_;
  TH1D* holdcutcum_;
  TH1D* hhcalcutind_;
  TH1D* hhcalcutcum_;


  // histograms after each cut
  std::vector<TH1D*> hjete_cuts_;
  std::vector<TH2D*> hjetetaphi_cuts_;
  std::vector<TH2D*> hmuetaphi_cuts_;
  std::vector<TH1D*> hbx_cuts_;
  std::vector<TH1D*> hjetemf_cuts_;
  
};



void Analysis::bookHistos() {
  
  // time
  hbx_ = new TH1D("hbx", "BX number", 3564, 0., 3564.);
  horb_ = new TH1D("horb", "Orbit number", 100, 0., 10000.);
  hlb_ = new TH1D("hlb", "Lumi block", 2000, 0., 2000.);
  htime_ = new TH1D("htime", "Event time", 100, 0., 1.E8);
  
  // L1
  hl1bits_ = new TH1D("hl1bits", "L1 trigger bits", 10, 0., 20.);
  hl1et_ = new TH1D("hl1et",  "Leading L1 jet E_{t}", 100, 0., 200.);
  hl1eta_ = new TH1D("hl1eta", "Leading L1 jet #eta", 70, -3.5, 3.5);
  hl1phi_ = new TH1D("hl1phi", "Leading L1 jet #phi", 72, -1 * TMath::Pi(),  TMath::Pi());
  hl1type_ = new TH1D("hl1type",  "Leading L1 jet type", 3, 0., 3.);
  
  // HLT
  hhlte_ = new TH1D("hhlte",  "Leading HLT jet E", 100, 0., 200.);
  hhlteta_ = new TH1D("hhlteta", "Leading HLT jet #eta", 70, -3.5, 3.5);
  hhltphi_ = new TH1D("hhltphi", "Leading HLT jet #phi", 72, -1 * TMath::Pi(),  TMath::Pi());
  
  // calo towers
  hntowsameiphi_ = new TH1D("hntowsameiphi", "N leading towers at same iphi", 20, -0.5, 19.5);
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
  hpksample_ = new TH1D("hpksample", "Peak sample", 10, 0., 10.);
  hr1_ = new TH1D("hr1", "R_{1}", 50, 0., 1.);
  hr2_ = new TH1D("hr2", "R_{2}", 50, 0., 1.);
  hrpk_ = new TH1D("hrpk", "R_{peak}", 50, 0., 1.);
  hrout_ = new TH1D("hrout", "R_{outer}", 30, 0., 1.);    
  hr1r2_ = new TH2D("hr1r2", "R_{1} vs R_{2}", 50, 0., 1., 50, 0., 1.);
  hpkout_ = new TH2D("hpkout", "R_{peak} vs R_{outer}", 50, 0., 1., 50, 0., 1.);
  hr1_old_ = new TH1D("hr1old", "R_{1} old", 50, 0., 1.);
  hr2_old_ = new TH1D("hr2old", "R_{2} old", 50, 0., 1.);
  hrpk_old_ = new TH1D("hrpkold", "R_{peak} old", 50, 0., 1.);
  hrout_old_ = new TH1D("hroutold", "R_{outer} old", 30, 0., 1.);    
  
  // special
  hbxup_ = new TH1D("hbxup", "BX (unpaired bunches)", 3564, 0., 3564.);

  // cut counts
  hncutind_ = new TH1D("hncutind", "Cut counts", 20, 0., 20.);
  cutAxisLabels(hncutind_);
  hncutcum_ = new TH1D("hncutcum", "Cumulative cut counts", 20, 0., 20.);
  cutAxisLabels(hncutcum_);  
  hnminus1cut_ = new TH1D("hnminus1cut", "N-1 cut counts", 20, 0., 20.);
  cutAxisLabels(hnminus1cut_);

  // old cuts
  holdcutind_ = new TH1D("holdcutind", "Old cut counts", 20, 0., 20.);
  cutAxisLabels(holdcutind_);
  holdcutcum_ = new TH1D("holdcutcum", "Old cut cumulative counts", 20, 0., 20.);
  cutAxisLabels(holdcutcum_);

  // HCAL noise cuts
  hhcalcutind_ = new TH1D("hhcalcutind", "HCAL noise cut counts", 20, 0., 20.);
  hhcalcutcum_ = new TH1D("hhcalcutcum", "HCAL noise cut cumulative counts", 20, 0., 20.);
  
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


// write histos
void Analysis::writeHistos() {

  // check if dir exists, create if not
  if (  ofile_->cd("NoCuts") != kTRUE ) {
    ofile_->mkdir("NoCuts");
    ofile_->cd("NoCuts");
  }

  hbx_->Write("",TObject::kOverwrite);
  horb_->Write("",TObject::kOverwrite);
  hlb_->Write("",TObject::kOverwrite);

  rateDist(*hlb_, 100);

  htime_->Write("",TObject::kOverwrite);
  hl1bits_->Write("",TObject::kOverwrite);
  hl1et_->Write("",TObject::kOverwrite);
  hl1eta_->Write("",TObject::kOverwrite);
  hl1phi_->Write("",TObject::kOverwrite);
  hl1type_->Write("",TObject::kOverwrite);
  hhlte_->Write("",TObject::kOverwrite);
  hhlteta_->Write("",TObject::kOverwrite);
  hhltphi_->Write("",TObject::kOverwrite);
  hntowsameiphi_->Write("",TObject::kOverwrite);
  htowietaiphi_->Write("",TObject::kOverwrite);
  hjete_->Write("",TObject::kOverwrite);
  hjeteta_->Write("",TObject::kOverwrite);
  hjetphi_->Write("",TObject::kOverwrite);
  hjetetaphi_->Write("",TObject::kOverwrite);
  hjeteem_->Write("",TObject::kOverwrite);
  hjetehad_->Write("",TObject::kOverwrite);
  hjetemf_->Write("",TObject::kOverwrite);
  hjetn60_->Write("",TObject::kOverwrite);
  hjetn90_->Write("",TObject::kOverwrite);
  hjetn90hits_->Write("",TObject::kOverwrite);
  hjetfhpd_->Write("",TObject::kOverwrite);
  hnmu_->Write("",TObject::kOverwrite);
  hmuetaphi_->Write("",TObject::kOverwrite);
  hpksample_->Write("",TObject::kOverwrite);
  hr1_->Write("",TObject::kOverwrite);
  hr2_->Write("",TObject::kOverwrite);
  hrpk_->Write("",TObject::kOverwrite);
  hrout_->Write("",TObject::kOverwrite);
  hr1r2_->Write("",TObject::kOverwrite);
  hpkout_->Write("",TObject::kOverwrite);
  hr1_old_->Write("",TObject::kOverwrite);
  hr2_old_->Write("",TObject::kOverwrite);
  hrpk_old_->Write("",TObject::kOverwrite);
  hrout_old_->Write("",TObject::kOverwrite);
  hbxup_->Write("",TObject::kOverwrite);

  if ( ofile_->cd("Cuts") != kTRUE ){
    ofile_->mkdir("Cuts");
    ofile_->cd("Cuts");
  }

  hncutind_->Write("",TObject::kOverwrite);
  hncutcum_->Write("",TObject::kOverwrite);
  hnminus1cut_->Write("",TObject::kOverwrite);

  holdcutind_->Write("",TObject::kOverwrite);
  holdcutcum_->Write("",TObject::kOverwrite);

  hhcalcutind_->Write("",TObject::kOverwrite);
  hhcalcutcum_->Write("",TObject::kOverwrite);
  
  for (unsigned i=0; i< nCuts_; ++i) {
    hjete_cuts_.at(i)->Write("",TObject::kOverwrite);
    hjetetaphi_cuts_.at(i)->Write("",TObject::kOverwrite);
    hmuetaphi_cuts_.at(i)->Write("",TObject::kOverwrite);
    hbx_cuts_.at(i)->Write("",TObject::kOverwrite);
    hjetemf_cuts_.at(i)->Write("",TObject::kOverwrite);
  }

}


// get histograms from file
void Analysis::getHistos() {

  hbx_ = (TH1D*) ofile_->Get("NoCuts/hbx");
  horb_ = (TH1D*) ofile_->Get("NoCuts/horb");
  hlb_ = (TH1D*) ofile_->Get("NoCuts/hlb");
  htime_ = (TH1D*) ofile_->Get("NoCuts/htime");
  hl1bits_ = (TH1D*) ofile_->Get("NoCuts/hl1bits");
  hl1et_ = (TH1D*) ofile_->Get("NoCuts/hl1et");
  hl1eta_ = (TH1D*) ofile_->Get("NoCuts/hl1eta");
  hl1phi_ = (TH1D*) ofile_->Get("NoCuts/hl1phi");
  hl1type_ = (TH1D*) ofile_->Get("NoCuts/hl1type");
  hhlte_ = (TH1D*) ofile_->Get("NoCuts/hhlte");
  hhlteta_ = (TH1D*) ofile_->Get("NoCuts/hhlteta");
  hhltphi_ = (TH1D*) ofile_->Get("NoCuts/hhltphi");
  hjete_ = (TH1D*) ofile_->Get("NoCuts/hjete");
  hjeteta_ = (TH1D*) ofile_->Get("NoCuts/hjeteta");
  hjetphi_ = (TH1D*) ofile_->Get("NoCuts/hjetphi");
  hjetetaphi_ = (TH2D*) ofile_->Get("NoCuts/hjetetaphi");
  hjeteem_ = (TH1D*) ofile_->Get("NoCuts/hjeteem");
  hjetehad_ = (TH1D*) ofile_->Get("NoCuts/hjetehad");
  hjetemf_ = (TH1D*) ofile_->Get("NoCuts/hjetemf");
  hjetn60_ = (TH1D*) ofile_->Get("NoCuts/hjetn60");
  hjetn90_ = (TH1D*) ofile_->Get("NoCuts/hjetn90");
  hjetn90hits_ = (TH1D*) ofile_->Get("NoCuts/hjetn90hits");
  hjetfhpd_ = (TH1D*) ofile_->Get("NoCuts/hjetfhpd");
  hnmu_ = (TH1D*) ofile_->Get("NoCuts/hnmu");
  hmuetaphi_ = (TH2D*) ofile_->Get("NoCuts/hmuetaphi");
  hntowsameiphi_ = (TH1D*) ofile_->Get("NoCuts/hntowsameiphi");
  htowietaiphi_ = (TH2D*) ofile_->Get("NoCuts/htowietaiphi");
  hpksample_ = (TH1D*) ofile_->Get("NoCuts/hpksample");
  hr1_ = (TH1D*) ofile_->Get("NoCuts/hr1");
  hr2_ = (TH1D*) ofile_->Get("NoCuts/hr2");
  hrpk_ = (TH1D*) ofile_->Get("NoCuts/hrpk");
  hrout_ = (TH1D*) ofile_->Get("NoCuts/hrout");
  hr1r2_ = (TH2D*) ofile_->Get("NoCuts/hr1r2");
  hpkout_ = (TH2D*) ofile_->Get("NoCuts/hpkout");
  hr1_old_ = (TH1D*) ofile_->Get("NoCuts/hr1old");
  hr2_old_ = (TH1D*) ofile_->Get("NoCuts/hr2old");
  hrpk_old_ = (TH1D*) ofile_->Get("NoCuts/hrpkold");
  hrout_old_ = (TH1D*) ofile_->Get("NoCuts/hroutold");
  hbxup_ = (TH1D*) ofile_->Get("NoCuts/hbxup");
  
  // cuts histos
  hncutind_ = (TH1D*) ofile_->Get("Cuts/hncutind");
  hncutcum_ = (TH1D*) ofile_->Get("Cuts/hncutcum");
  hnminus1cut_ = (TH1D*) ofile_->Get("Cuts/hnminus1cut");

  holdcutind_ = (TH1D*) ofile_->Get("Cuts/holdcutind");
  holdcutcum_ = (TH1D*) ofile_->Get("Cuts/holdcutcum");

  hhcalcutind_ = (TH1D*) ofile_->Get("Cuts/hhcalcutind");
  hhcalcutcum_ = (TH1D*) ofile_->Get("Cuts/hhcalcutcum");

    
  for (unsigned i=0; i< nCuts_; ++i) {
    std::stringstream istr;
    istr << i;
    hjete_cuts_.push_back( (TH1D*) ofile_->Get((std::string("Cuts/hjete")+istr.str()).c_str()));
    hjetetaphi_cuts_.push_back( (TH2D*) ofile_->Get((std::string("Cuts/hjetetaphi")+istr.str()).c_str()) );
    hmuetaphi_cuts_.push_back( (TH2D*) ofile_->Get((std::string("Cuts/hmuetaphi")+istr.str()).c_str()) );
    hbx_cuts_.push_back( (TH1D*) ofile_->Get((std::string("Cuts/hbx")+istr.str()).c_str()) );
    hjetemf_cuts_.push_back( (TH1D*) ofile_->Get((std::string("Cuts/hjetemf")+istr.str()).c_str()) );
  }

}


// save and delete all histogram objects
void Analysis::deleteHistos() {

  if (hbx_ != 0) {
    delete hbx_;
    delete horb_;
    delete hlb_;
    delete htime_;
    delete hl1bits_;
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
    delete hpksample_;
    delete hr1_;
    delete hr2_;
    delete hrpk_;
    delete hrout_;
    delete hr1r2_;
    delete hpkout_;
    delete hr1_old_;
    delete hr2_old_;
    delete hrpk_old_;
    delete hrout_old_;
    delete hbxup_;

    delete hncutind_;
    delete hncutcum_;
    delete hnminus1cut_;
    delete holdcutind_;
    delete holdcutcum_;
    delete hhcalcutind_;
    delete hhcalcutcum_;
    
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
void Analysis::fillHistos(StoppedHSCPTree& tree) {

  hbx_->Fill(tree.bx);
  horb_->Fill(tree.orbit);
  hlb_->Fill(tree.lb);
  htime_->Fill(tree.time);
  hl1bits_->Fill("L1_SingleJet10_NotBptxC", (tree.gtAlgoWord1>>(88-64))&0x1);
  hl1bits_->Fill("L1Tech_BPTX_plus_AND_minus", (tree.gtTechWord)&0x1);
  hl1bits_->Fill("L1_BptxMinus", (tree.gtAlgoWord1>>(81-64))&0x1);
  hl1bits_->Fill("L1_BptxPlus", (tree.gtAlgoWord1>>(80-64))&0x1);
  hl1bits_->Fill("L1_SingleJet10U", (tree.gtAlgoWord0>>16)&0x1);
  hl1bits_->Fill("L1_SingleMuOpen", (tree.gtAlgoWord0>>55)&0x1);
  hl1bits_->Fill("L1Tech_BSC_minBias_thresh1", (tree.gtTechWord>>40)&0x1);
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
  hr1_->Fill(tree.top5DigiPeakSample);
  hr1_->Fill(tree.top5DigiR1);
  hr2_->Fill(tree.top5DigiR2);
  hrpk_->Fill(tree.top5DigiRPeak);
  hrout_->Fill(tree.top5DigiROuter);
  hr1r2_->Fill(tree.top5DigiR1, tree.top5DigiR2);
  hpkout_->Fill(tree.top5DigiRPeak, tree.top5DigiROuter);
  hr1_old_->Fill(tree.TimingRightPeak);
  hr2_old_->Fill(tree.TimingFracRightNextRight);
  hrpk_old_->Fill(tree.TimingFracInLeader);
  hrout_old_->Fill(1.-tree.TimingFracInCentralFour);

  if ( ((tree.gtAlgoWord1>>(80-64))&0x1)>0 || ((tree.gtAlgoWord1>>(81-64))&0x1)>0) {
    hbxup_->Fill(tree.bx);
  }

  // loop over cuts
  bool fail=false;
  for (unsigned c=0; c<nCuts_; c++) {
    if (tree.CutNMinusOne(c)) hnminus1cut_->Fill(c);
    if (tree.CutN(c)) hncutind_->Fill(c);
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

  // old cuts
  fail=false;
  for (unsigned c=0; c<12; c++) {
    if (tree.OldCutN(c)) holdcutind_->Fill(c);
    else fail |= true;
    if (!fail) holdcutcum_->Fill(c);
  }


  // loop over HCAL noise cuts
  bool hcalfail=false;
  for (unsigned c=0; c<nHcalCuts_; c++) {
    if (tree.StdHcalCutN(c)) hhcalcutind_->Fill(c);
    else hcalfail |= true;
    if (!hcalfail) hhcalcutcum_->Fill(c);  
  }

}

// make a histogram of means of bins of existing histogram
TH1D Analysis::rateDist(TH1D& hist, unsigned nbins) {

  std::string name=std::string(hist.GetName())+"dist";
  TH1D h(name.c_str(), "Rate", nbins, hist.GetMinimum()*0.8, hist.GetMaximum()*1.25);

  // fill histogram
  for (int i=0; i<hist.GetNbinsX(); ++i) {
    unsigned r=hist.GetBinContent(i);
    if (r>0.) h.Fill(r);
  }
	
  // do fit
  //  TF1 f("fit", "gaus");
  //  h.Fit("fit", "");    
	
  h.Write();

  return h;

}


void Analysis::newHistos(unsigned run) {

  // histograms filename
  std::string filename=outdir_ + "/histograms";
  if (run > 0) {
    char runstr[10];
    sprintf(runstr, "%d", run);
    filename += runstr;
  }
  filename += ".root";

  std::cout << "Putting histograms in " << filename << std::endl;

  // check if histo file exists and open it if so
  struct stat fileInfo;
  if (stat(filename.c_str(),&fileInfo)==0) {
    ofile_ = new TFile(filename.c_str(), "update");
    getHistos();
  }
  else {
    // if run histo file doesn't exist, create it, and new histograms   
    ofile_ = new TFile(filename.c_str(), "recreate");
    bookHistos();
  }

}


void Analysis::saveHistos() {

  writeHistos();
  deleteHistos();

  ofile_->Close();
  delete ofile_;

}


// loop over all events, filling histograms
void Analysis::loopAll() {

  std::cout << "Making histograms for entire file" << std::endl;

  currentRun_ = 0;

  newHistos(0);

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

    if (dumpEvents_ &&
	(tree_->Cut()>0. ||
	tree_->id == 13200704 ||
	tree_->id == 23338580 ||
	tree_->id == 9871709 ||
	tree_->id == 41317372 ||
	tree_->id == 70303519 ||
	tree_->id == 81147704 ||
	tree_->id == 92716023 ||
	tree_->id == 97106991 ||
	tree_->id == 110183807 ||
	tree_->id == 117516582 ||
	tree_->id == 12685963 ||
	tree_->id == 11537315 ||
	tree_->id == 17661711 ||
	tree_->id == 19381281 ||
	 tree_->id == 36361101 )) {
      tree_->PrintCutValues();
    }
    
  }

  saveHistos();

}


// loop over all events, clear histograms and write file for each run
void Analysis::loopByRun() {

  // set up loop
  if (tree_->fChain == 0) return;
  Long64_t nentries = tree_->fChain->GetEntriesFast();
  Long64_t nbytes = 0, nb = 0;

  unsigned currentRun_=0;
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

    unsigned thisRun = tree_->run;

    // if first event, get new histos
    if (currentRun_==0) {
      std::cout << "First run " << thisRun << std::endl;
      currentRun_ = thisRun;
      newHistos(thisRun);
    }

    // or if the run changed
    if (currentRun_!=0 && thisRun != currentRun_) {

      std::cout << "Found " << nevts << " events in run " << currentRun_ << std::endl;
      std::cout << "New run " << thisRun << std::endl;

      // save histos
      saveHistos();
      
      // and reset histograms etc
      nevts=0;
      currentRun_ = thisRun;
      newHistos(thisRun);

    }

    // otherwise just fill the histograms
    fillHistos(*tree_);
    nevts++;
    
  }

}


void Analysis::cutAxisLabels(TH1D* h) {

  for (unsigned i=0; i<nCuts_; ++i) {
    h->GetXaxis()->SetBinLabel(i+1, tree_->CutName(i));
  }

}


Analysis::Analysis(const char* filename, const char* outdir, unsigned nlimit, bool dump) :
  file_(filename), 
  ttree_(0),
  tree_(0),
  outdir_(outdir),
  ofile_(0),
  nlimit_(nlimit),
  dumpEvents_(dump),
  currentRun_(0)
{

  // open file and get tree
  //  ttree_ = (TTree*) file_.Get("stoppedHSCPTree/StoppedHSCPTree");
  tree_ = new StoppedHSCPTree(&file_);

  nCuts_ = tree_->NCuts();
  nHcalCuts_ = 12;
}


Analysis::~Analysis() {

  if (ttree_ != 0) delete ttree_;
  if (tree_ != 0) delete tree_;
  if (ofile_ != 0) delete ofile_;

  file_.Close();

}

int main(int argc, char* argv[]) {

  if (argc < 3) {
    std::cout << "Insufficient arguments" << std::endl;
    std::cout << "Usage : BasicHistograms <filename> <label>" << std::endl;
    exit(1);
  }

  // options
  unsigned nlimit=999999999;
  bool dump=false;
  bool doByRun=true;
  for (int i=1; i<argc; ++i) {
    // check option flags
    std::string opt = argv[i];
    if (opt=="-d") {
      nlimit=1000;
    }
    if (opt=="-p") {
      dump=true;
    }
    if (opt=="-q") {
      doByRun = false;
    }
  }

  if (nlimit<999999999) std::cout << "Running on " << nlimit << " events per run" << std::endl;

  // arguments
  std::string filename = std::string(argv[argc-2]);
  std::cout << "Going to run on " << filename << std::endl;

  std::string outdir=std::string(argv[argc-1]);
  std::cout << "Putting output in " << outdir << std::endl;

  // clean output directory
  std::string command("mkdir ");
  command += outdir;
  system(command.c_str());
  command = std::string("rm ");
  command += outdir;
  command += std::string("/*");
  system(command.c_str());
  command = std::string("ls ");
  command += outdir;
  system(command.c_str());

  // create analysis
  Analysis analysis(filename.c_str(), outdir.c_str(), nlimit, dump);

  // make histograms for all events
  analysis.loopAll();

  // make histograms for each run
  if (doByRun) {
    analysis.loopByRun();

  }

}
  // make histograms for each run
//   std::string runlist = argv[argc-1];
//   std::vector<std::string> runStrs;
//   boost::split(runStrs, runlist, boost::is_any_of(","));
//   std::vector<unsigned> runs;
//   for (std::vector<std::string>::const_iterator runStr=runStrs.begin();
//        runStr!=runStrs.end();
//        ++runStr) runs.push_back( boost::lexical_cast<unsigned>(runStr->c_str()) );



