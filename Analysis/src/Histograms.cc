
#include "StoppedHSCP/Analysis/interface/Histograms.h"

#include "TMath.h"

#include <sstream>
#include <iostream>

Histograms::Histograms(TFile* file, Cuts* cuts) :
  cuts_(cuts),
  base_()
{
 
  // create directory structure
  file->mkdir("histograms");
  base_ = file->GetDirectory("histograms");
  base_->mkdir("NoCuts");  
  base_->mkdir("Cuts");

  book();

}

Histograms::~Histograms() {

}



void Histograms::book() {

  base_->cd("NoCuts");

  // time
  hbx_ = new TH1D("hbx", "BX number", 3564, 0., 3564.);
  horb_ = new TH1D("horb", "Orbit number", 100, 0., 10000.);
  htime_ = new TH1D("htime", "Event time", 100, 0., 1.E8);
  hrelbx_ = new TH1D("hrelbx", "BX wrt coll", 200, -200.5, +199.5);
 
  // L1
  hl1bits_ = new TH1D("hl1bits", "L1 trigger bits", 10, 0., 20.);
  hl1et_ = new TH1D("hl1et",  "Leading L1 jet E_{t}", 100, 0., 200.);
  hl1eta_ = new TH1D("hl1eta", "Leading L1 jet #eta", 70, -3.5, 3.5);
  hl1phi_ = new TH1D("hl1phi", "Leading L1 jet #phi", 72, -1 * TMath::Pi(),  TMath::Pi());
  hl1type_ = new TH1D("hl1type",  "Leading L1 jet type", 3, 0., 3.);

  hbptx_ = new TH1D("hbptx", "BPTX BX", 5, -2.5, 2.5);
  
  // HLT
  hhltbits_ = new TH1D("hhltbits", "HLT bits", 5, 0., 5.);
  hhlte_ = new TH1D("hhlte",  "Leading HLT jet E", 100, 0., 200.);
  hhlteta_ = new TH1D("hhlteta", "Leading HLT jet #eta", 70, -3.5, 3.5);
  hhltphi_ = new TH1D("hhltphi", "Leading HLT jet #phi", 72, -1 * TMath::Pi(),  TMath::Pi());
  
  // calo towers
  hntowsameiphi_ = new TH1D("hntowsameiphi", "N leading towers at same iphi", 20, -0.5, 19.5);
  htowietaiphi_ = new TH2D("htowietaiphi", "Leading tower position", 100, -50., 50., 75, 0., 75.);
  
  // jets
  hjete_ = new TH1D("hjete", "Leading jet energy", 50, 0., 200.);
  hjeteta_ = new TH1D("hjeteta", "Leading jet #eta", 70, -3.5, 3.5);
  hjetphi_ = new TH1D("hjetphi", "Leading jet #phi", 72, -1 * TMath::Pi(),  TMath::Pi());
  hjetetaphi_ = new TH2D("hjetetaphi", "Leading jet pos", 70, -3.5, 3.5, 72, -1 * TMath::Pi(),  TMath::Pi());
  hjeteem_ = new TH1D("hjeteem", "Leading jet ECAL energy", 100, 0., 200.);
  hjetehad_ = new TH1D("hjetehad", "Leading jet HCAL energy", 100, 0., 200.);
  hjetemf_ =  new TH1D("hjetemf", "Leading jet EM fraction", 100, 0., 1.);
  hjetn60_ = new TH1D("hjetn60", "Leading jet N60", 25, 0., 25.);
  hjetn90_ = new TH1D("hjetn90", "Leading jet N90", 25, 0., 25.);
  hjetn90hits_ = new TH1D("hjetn90hits", "Leading jet N90 hits", 50, 0., 50.);
  hjetfhpd_ = new TH1D("hjetfhpd", "Leading jet fHPD", 50, 0., 1.);
  
  // towers in jets
  htowiphifrac_ = new TH1D("htowiphifrac", "iphi E fraction", 50, 0., 1.);

  // muons
  hnmu_ = new TH1D("hnmu", "N muons", 4, -0.5, 3.5);
  hmuetaphi_ = new TH2D("hmuetaphi", "Muon pos", 70, -3.5, 3.5, 72, -1 * TMath::Pi(),  TMath::Pi());
  
  // beam halo
  hhalo_ = new TH1D("hhalo", "Halo ID", 4, 0., 0.);

  // pulse shape
  hpksample_ = new TH1D("hpksample", "Peak sample (after jet/#mu cuts)", 10, 0., 10.);
  hr1_ = new TH1D("hr1", "R_{1} (after jet/#mu cuts)", 50, 0., 1.);
  hr2_ = new TH1D("hr2", "R_{2} (after jet/#mu cuts)", 50, 0., 1.);
  hrpk_ = new TH1D("hrpk", "R_{peak} (after jet/#mu cuts)", 50, 0., 1.);
  hrout_ = new TH1D("hrout", "R_{outer} (after jet/#mu cuts)", 30, 0., 1.);    
  hr1r2_ = new TH2D("hr1r2", "R_{1} vs R_{2} (after jet/#mu cuts)", 50, 0., 1., 50, 0., 1.);
  hpkout_ = new TH2D("hpkout", "R_{peak} vs R_{outer} (after jet/#mu cuts)", 50, 0., 1., 50, 0., 1.);

  base_->cd("Cuts");

  // special
  hbxup_ = new TH1D("hbxup", "BX (unpaired bunches)", 3564, 0., 3564.);

  // cut counts
  hncutind_ = new TH1D("hncutind", "Cut counts", 20, 0., 20.);
  cutAxisLabels(hncutind_);
  hncutcum_ = new TH1D("hncutcum", "Cumulative cut counts", 20, 0., 20.);
  cutAxisLabels(hncutcum_);  
  hnminus1cut_ = new TH1D("hnminus1cut", "N-1 cut counts", 20, 0., 20.);
  cutAxisLabels(hnminus1cut_);

  // JES systematic
  hncutsystlo_ = new TH1D("hncutsystlo", "Cum cut counts (low JES syst)", 20, 0., 20.);
  cutAxisLabels(hncutsystlo_);  
  hncutsysthi_ = new TH1D("hncutsysthi", "Cum cut counts (hi JES syst)", 20, 0., 20.);
  cutAxisLabels(hncutsysthi_);  
  hncutsystg_ = new TH1D("hncutsystg", "Cum cut counts (Gauss JES syst)", 20, 0., 20.);
  cutAxisLabels(hncutsystg_);  

  // old cuts
  holdcutind_ = new TH1D("holdcutind", "Old cut counts", 20, 0., 20.);
  cutAxisLabels(holdcutind_);
  holdcutcum_ = new TH1D("holdcutcum", "Old cut cumulative counts", 20, 0., 20.);
  cutAxisLabels(holdcutcum_);

  // HCAL noise cuts
  hhcalcutind_ = new TH1D("hhcalcutind", "HCAL noise cut counts", 20, 0., 20.);
  hhcalcutcum_ = new TH1D("hhcalcutcum", "HCAL noise cut cumulative counts", 20, 0., 20.);
  
  // N-1 histograms
  hnmu_nmo_ = new TH1D("hnmu_nmo", "N muons (N-1)", 4, -0.5, 3.5);;
  hjete_nmo_ = new TH1D("hjete_nmo", "Leading jet energy (N-1)", 50, 0., 200.);
  hjetn60_nmo_ = new TH1D("hjetn60_nmo", "Leading jet N60 (N-1)", 25, 0., 25.);
  hjetn90_nmo_ = new TH1D("hjetn90_nmo", "Leading jet N90 (N-1)", 25, 0., 25.);
  hntowiphi_nmo_ = new TH1D("hntowsameiphi_nmo", "N leading towers at same iphi (N-1)", 20, -0.5, 19.5);
  hr1_nmo_ = new TH1D("hr1_nmo", "R_{1} (N-1)", 50, 0., 1.);
  hr2_nmo_ = new TH1D("hr2_nmo", "R_{2} (N-1)", 50, 0., 1.);
  hrpk_nmo_ = new TH1D("hrpk_nmo", "R_{peak} (N-1)", 50, 0., 1.);
  hrout_nmo_ = new TH1D("hrout_nmo", "R_{outer} (N-1)", 30, 0., 1.);
  hjetemf_nmo_ = new TH1D("hjetemf_nmo", "Leading jet EM fraction (N-1)", 100, 0., 1.);
  

  // histograms per cut
  for (unsigned i=0; i<cuts_->nCuts(); ++i) {
    std::stringstream istr;
    istr << i;
    std::string cstr=cuts_->cutName(i);
    hjete_cuts_.push_back(new TH1D((std::string("hjete")+istr.str()).c_str(), (std::string("Jet E after ")+cstr).c_str(), 50, 0., 200.));
    hjetn60_cuts_.push_back(new TH1D((std::string("hjetn60")+istr.str()).c_str(), (std::string("Jet n60 after ")+cstr).c_str(), 25, 0., 25.));
    hjetn90_cuts_.push_back(new TH1D((std::string("hjetn90")+istr.str()).c_str(), (std::string("Jet n90 after ")+cstr).c_str(), 25, 0., 25.));
    hnmu_cuts_.push_back(new TH1D((std::string("hjetnmu")+istr.str()).c_str(), (std::string("N mu after ")+cstr).c_str(), 4, -0.5, 3.5));
    hr1_cuts_.push_back(new TH1D((std::string("hr1")+istr.str()).c_str(), (std::string("R1 after ")+cstr).c_str(), 50, 0., 1.));
    hr2_cuts_.push_back(new TH1D((std::string("hr2")+istr.str()).c_str(), (std::string("R2 after ")+cstr).c_str(), 50, 0., 1.));
    hrpk_cuts_.push_back(new TH1D((std::string("hrpk")+istr.str()).c_str(), (std::string("R_{peak} after ")+cstr).c_str(), 50, 0., 1.));
    hrout_cuts_.push_back(new TH1D((std::string("hrout")+istr.str()).c_str(), (std::string("R_{outer} after ")+cstr).c_str(), 50, 0., 1.));
    hjetetaphi_cuts_.push_back(new TH2D((std::string("hjetetaphi")+istr.str()).c_str(), (std::string("Jet pos after ")+cstr).c_str(), 70, -3.5, 3.5, 72, -1 * TMath::Pi(),  TMath::Pi()));
    hmuetaphi_cuts_.push_back(new TH2D((std::string("hmuetaphi")+istr.str()).c_str(), (std::string("#mu pos after ")+cstr).c_str(), 70, -3.5, 3.5, 72, -1 * TMath::Pi(),  TMath::Pi()));
    hbx_cuts_.push_back(new TH1D((std::string("hbx")+istr.str()).c_str(), (std::string("BX after ")+cstr).c_str(), 3564, 0., 3564.));
    hjetemf_cuts_.push_back(new TH1D((std::string("hjetemf")+istr.str()).c_str(), (std::string("Jet EMF after ")+cstr).c_str(), 100, 0., 1.));
    //    hlifetime_cuts.push_back(new TH1D((std:;string("hlifetime")+istr.str()).c_str(), (std::string("Lifetime after ")+cstr).c_str(), 100, 0., 1.e-3);
  }

}


void Histograms::fill(StoppedHSCPEvent& event) {

  hbx_->Fill(event.bx);
  horb_->Fill(event.orbit);
  htime_->Fill(event.time);

  hrelbx_->Fill(event.bxWrtCollision);

  hl1bits_->Fill("L1_SingleJet10_NotBptxC", (event.gtAlgoWord1>>(88-64))&0x1);
  hl1bits_->Fill("L1Tech_BPTX_plus_AND_minus", (event.gtTechWord)&0x1);
  hl1bits_->Fill("L1_BptxMinus", (event.gtAlgoWord1>>(81-64))&0x1);
  hl1bits_->Fill("L1_BptxPlus", (event.gtAlgoWord1>>(80-64))&0x1);
  hl1bits_->Fill("L1_SingleJet10U", (event.gtAlgoWord0>>16)&0x1);
  hl1bits_->Fill("L1_SingleMuOpen", (event.gtAlgoWord0>>55)&0x1);
  hl1bits_->Fill("L1Tech_BSC_minBias_thresh1", (event.gtTechWord>>40)&0x1);

  hhltbits_->Fill("HLT_JetE_NoBptx", event.hltJetNoBptx);
  hhltbits_->Fill("HLT_JetE_NoBptx_NoHalo", event.hltJetNoBptxNoHalo);
  hhltbits_->Fill("HLT_JetE_NoBptx3BX_NoHalo", event.hltJetNoBptx3BXNoHalo);


  for (unsigned bx=0; bx<5; ++bx) {
    if (event.l1JetNoBptx.at(bx)>0) hbptx_->Fill(bx-2);
  }

  if ( ((event.gtAlgoWord1>>(80-64))&0x1)>0 || ((event.gtAlgoWord1>>(81-64))&0x1)>0) {
    hbxup_->Fill(event.bx);
  }

  std::string halo("None");
  if (event.beamHalo_CSCLoose) halo = "CSCLoose";
  if (event.beamHalo_CSCTight) halo = "CSCTight";
  hhalo_->Fill(halo.c_str(), 1.);

  // fill remaining histograms for events passing BX veto etc.
  if (cuts_->allCutN(5)) {

    if (event.l1Jet_N > 0) {
      hl1et_->Fill(event.l1JetE.at(0));
      hl1eta_->Fill(event.l1JetEta.at(0));
      hl1phi_->Fill(event.l1JetPhi.at(0));
      hl1type_->Fill(event.l1JetType.at(0));
    }
    if (event.hltJet_N > 0) {
      hhlte_->Fill(event.hltJetE.at(0));
      hhlteta_->Fill(event.hltJetEta.at(0));
      hhltphi_->Fill(event.hltJetPhi.at(0));
    }
    if (event.jet_N > 0) {
      hjete_->Fill(event.jetE.at(0));
      hjeteta_->Fill(event.jetEta.at(0));
      hjetphi_->Fill(event.jetPhi.at(0));
      hjetetaphi_->Fill(event.jetEta.at(0), event.jetPhi.at(0));
      hjeteem_->Fill(event.jetEEm.at(0));
      hjetehad_->Fill(event.jetEHad.at(0));
      hjetemf_->Fill(event.jetEEm.at(0)/event.jetE.at(0));
      hjetn60_->Fill(event.jetN60.at(0));
      hjetn90_->Fill(event.jetN90.at(0));
      hjetn90hits_->Fill(0.);
      hjetfhpd_->Fill(0.);
    }
    hnmu_->Fill(event.mu_N);
    if (event.mu_N>0) {
      hmuetaphi_->Fill(event.muEta.at(0), event.muPhi.at(0));
    }
    hntowsameiphi_->Fill(event.nTowerSameiPhi);
    if (event.tower_N>0) {
      htowietaiphi_->Fill(event.towerIEta.at(0), event.towerIPhi.at(0));
    }

  }

  // plots after jet and mu cuts
  if (cuts_->allCutN(11)) {
    hpksample_->Fill(event.top5DigiPeakSample);
    hr1_->Fill(event.top5DigiR1);
    hr2_->Fill(event.top5DigiR2);
    hrpk_->Fill(event.top5DigiRPeak);
    hrout_->Fill(event.top5DigiROuter);
    hr1r2_->Fill(event.top5DigiR1, event.top5DigiR2);
    hpkout_->Fill(event.top5DigiRPeak, event.top5DigiROuter);

    // energy fraction at same iphi
    std::vector<double> tmp(75, 0);
    for (unsigned i=0; i<event.tower_N; ++i) {
      tmp.at(event.towerIPhi.at(i)) += event.towerE.at(i);
    }
    std::vector<double>::iterator max=max_element(tmp.begin(), tmp.end());

    if (event.jet_N>0) {
      htowiphifrac_->Fill((*max)/event.jetE.at(0));
    }
    
  }

  // loop over cuts
  bool fail=false;
  for (unsigned c=0; c<cuts_->nCuts(); c++) {
    if (cuts_->cutNMinusOne(c)) hnminus1cut_->Fill(c);
    if (cuts_->cutN(c)) hncutind_->Fill(c);
    else fail |= true;
    if (!fail) {
      hncutcum_->Fill(c);
      if (event.jet_N>0) {
	hjete_cuts_.at(c)->Fill(event.jetE.at(0));
	hjetn60_cuts_.at(c)->Fill(event.jetN60.at(0));
	hjetn90_cuts_.at(c)->Fill(event.jetN90.at(0));
	hnmu_cuts_.at(c)->Fill(event.mu_N);
	hr1_cuts_.at(c)->Fill(event.top5DigiR1);
	hr2_cuts_.at(c)->Fill(event.top5DigiR2);
	hrpk_cuts_.at(c)->Fill(event.top5DigiRPeak);
	hrout_cuts_.at(c)->Fill(event.top5DigiROuter);
	hjetetaphi_cuts_.at(c)->Fill(event.jetEta.at(0), event.jetPhi.at(0));
	hjetemf_cuts_.at(c)->Fill(event.jetEEm.at(0)/event.jetE.at(0));
      }
      if (event.mu_N>0) {
	hmuetaphi_cuts_.at(c)->Fill(event.muEta.at(0), event.muPhi.at(0));
      }
      hbx_cuts_.at(c)->Fill(event.bx);
    }
  }

  // systematics
  fail=false;
  double smear = 0.9;
  for (unsigned c=0; c<cuts_->nCuts(); c++) {
    if (!cuts_->cutNSyst(c, smear)) fail |= true;
    if (!fail) hncutsystlo_->Fill(c);
  }

  fail=false;
  smear = 1.1;
  for (unsigned c=0; c<cuts_->nCuts(); c++) {
    if (!cuts_->cutNSyst(c, smear)) fail |= true;
    if (!fail) hncutsysthi_->Fill(c);
  }

//   fail=false;
//   smear = random_->Gaus(1, 0.1);
//   for (unsigned c=0; c<cuts_->nCuts(); c++) {
//     if (!cuts_->cutNSyst(c, smear)) fail |= true;
//     if (!fail) hncutsystg_->Fill(c);
//   }

  // old cuts
//   fail=false;
//   for (unsigned c=0; c<12; c++) {
//     if (event.oldCutN(c)) holdcutind_->Fill(c);
//     else fail |= true;
//     if (!fail) holdcutcum_->Fill(c);
//   }


  // loop over HCAL noise cuts
//   bool hcalfail=false;
//   for (unsigned c=0; c<cuts_->nHcalCuts(); c++) {
//     if (cuts_->stdHcalCutN(c)) hhcalcutind_->Fill(c);
//     else hcalfail |= true;
//     if (!hcalfail) hhcalcutcum_->Fill(c);  
//   }

  if (cuts_->cutNMinusOne(10)) hntowiphi_nmo_->Fill(event.nTowerSameiPhi);
  if (cuts_->cutNMinusOne(5)) hnmu_nmo_->Fill(event.mu_N);
  if (cuts_->cutNMinusOne(12)) hr1_nmo_->Fill(event.top5DigiR1);
  if (cuts_->cutNMinusOne(13)) hr2_nmo_->Fill(event.top5DigiR2);
  if (cuts_->cutNMinusOne(14)) hrpk_nmo_->Fill(event.top5DigiRPeak);
  if (cuts_->cutNMinusOne(15)) hrout_nmo_->Fill(event.top5DigiROuter);
  if (event.jet_N > 0) {
    if (cuts_->cutNMinusOne(8)) hjete_nmo_->Fill(event.jetE.at(0));
    if (cuts_->cutNMinusOne(9)) hjetn60_nmo_->Fill(event.jetN60.at(0));
    if (cuts_->cutNMinusOne(10)) hjetn90_nmo_->Fill(event.jetN90.at(0));
    if (cuts_->cut()) hjetemf_nmo_->Fill(event.jetEEm.at(0)/event.jetE.at(0));
  }

}


void Histograms::save() {

  base_->cd("NoCuts");

  hbx_->Write("",TObject::kOverwrite);
  horb_->Write("",TObject::kOverwrite);
  htime_->Write("",TObject::kOverwrite);
  hrelbx_->Write("",TObject::kOverwrite);
  hl1bits_->Write("",TObject::kOverwrite);
  hbxup_->Write("",TObject::kOverwrite);

  hl1et_->Write("",TObject::kOverwrite);
  hl1eta_->Write("",TObject::kOverwrite);
  hl1phi_->Write("",TObject::kOverwrite);
  hl1type_->Write("",TObject::kOverwrite);
  hbptx_->Write("",TObject::kOverwrite);

  hhltbits_->Write("",TObject::kOverwrite);
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
  htowiphifrac_->Write("",TObject::kOverwrite);

  hnmu_->Write("",TObject::kOverwrite);
  hmuetaphi_->Write("",TObject::kOverwrite);

  hpksample_->Write("",TObject::kOverwrite);
  hr1_->Write("",TObject::kOverwrite);
  hr2_->Write("",TObject::kOverwrite);
  hrpk_->Write("",TObject::kOverwrite);
  hrout_->Write("",TObject::kOverwrite);
  hr1r2_->Write("",TObject::kOverwrite);
  hpkout_->Write("",TObject::kOverwrite);

  base_->cd("Cuts");

  hncutind_->Write("",TObject::kOverwrite);
  hncutcum_->Write("",TObject::kOverwrite);
  hnminus1cut_->Write("",TObject::kOverwrite);

  hncutsystlo_->Write("",TObject::kOverwrite);
  hncutsysthi_->Write("",TObject::kOverwrite);
  hncutsystg_->Write("",TObject::kOverwrite);

  holdcutind_->Write("",TObject::kOverwrite);
  holdcutcum_->Write("",TObject::kOverwrite);

  hhcalcutind_->Write("",TObject::kOverwrite);
  hhcalcutcum_->Write("",TObject::kOverwrite);

  hnmu_nmo_->Write("",TObject::kOverwrite);
  hjete_nmo_->Write("",TObject::kOverwrite);
  hjetn60_nmo_->Write("",TObject::kOverwrite);
  hjetn90_nmo_->Write("",TObject::kOverwrite);
  hntowiphi_nmo_->Write("",TObject::kOverwrite);
  hr1_nmo_->Write("",TObject::kOverwrite);
  hr2_nmo_->Write("",TObject::kOverwrite);
  hrpk_nmo_->Write("",TObject::kOverwrite);
  hrout_nmo_->Write("",TObject::kOverwrite);
  hjetemf_nmo_->Write("",TObject::kOverwrite);
  
  for (unsigned i=0; i< cuts_->nCuts(); ++i) {
    hjete_cuts_.at(i)->Write("",TObject::kOverwrite);
    hjetn60_cuts_.at(i)->Write("",TObject::kOverwrite);
    hjetn90_cuts_.at(i)->Write("",TObject::kOverwrite);
    hnmu_cuts_.at(i)->Write("",TObject::kOverwrite);
    hr1_cuts_.at(i)->Write("",TObject::kOverwrite);
    hr2_cuts_.at(i)->Write("",TObject::kOverwrite);
    hrpk_cuts_.at(i)->Write("",TObject::kOverwrite);
    hrout_cuts_.at(i)->Write("",TObject::kOverwrite);
    hjetetaphi_cuts_.at(i)->Write("",TObject::kOverwrite);
    hmuetaphi_cuts_.at(i)->Write("",TObject::kOverwrite);
    hbx_cuts_.at(i)->Write("",TObject::kOverwrite);
    hjetemf_cuts_.at(i)->Write("",TObject::kOverwrite);
  }

}


void Histograms::summarise() {


}


void Histograms::cutAxisLabels(TH1D* h) {

  for (unsigned i=0; i<cuts_->nCuts(); ++i) {
    h->GetXaxis()->SetBinLabel(i+1, cuts_->cutName(i).c_str());
  }

}


// make a histogram of means of bins of existing histogram
// TH1D Histograms::rateDist(TH1D& hist, unsigned nbins) {

//   std::string name=std::string(hist.GetName())+"dist";
//   TH1D h(name.c_str(), "Rate", nbins, hist.GetMinimum()*0.8, hist.GetMaximum()*1.25);

//   // fill histogram
//   for (int i=0; i<hist.GetNbinsX(); ++i) {
//     unsigned r=hist.GetBinContent(i);
//     if (r>0.) h.Fill(r);
//   }
  
//   // do fit
//   //  TF1 f("fit", "gaus");
//   //  h.Fit("fit", "");    
	
//   h.Write();

//   return h;

// }
