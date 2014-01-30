#ifndef Search_h
#define Search_h

//
// This program runs the search
// It applies all cuts, prints out some cut flow figures, and writes out candidate event #s
//

#include "StoppedHSCP/Analysis/interface/BasicAnalyser.h"
#include "StoppedHSCP/Ntuples/interface/Constants.h"

#include "StoppedHSCP/Analysis/interface/Livetime.h"
#include "StoppedHSCP/Analysis/interface/MultiHistogram1D.h"

#include "TFile.h"
#include "TChain.h"
#include "TH1D.h"
#include "TMath.h"

#include <boost/program_options.hpp>

#include <cmath>


using namespace std;
namespace po = boost::program_options;

class Search : public BasicAnalyser {

public:
  Search(int argc, char* argv[]) :
    BasicAnalyser(argc, argv),
    nSelected_(0) {
    ofilename_ = std::string("Search.root");  /// SET YOUR OUTPUT FILENAME HERE

    // get options
    po::options_description desc("Custom options");
    po::positional_options_description poptd;

    desc.add_options()
      ("special,s", po::value<std::string>(), "Special option");

    po::variables_map vm;
    po::store(po::command_line_parser(argc, argv).options(desc).allow_unregistered().run(), vm);  
    po::notify(vm);
    
    // get my custom option
    if (vm.count("special")) {
      std::string special = vm["special"].as<std::string>();
      std::cout << "Command line argument : " << special << std::endl;
    }

  }
  
  ~Search() { };
  
  void printCutValues(ostream& o);

  void cutAxisLabels(TH1D* h);

  virtual void loop();
  
private:

  // YOUR CODE HERE

  // cut flow
  TH1D* hncutind_;
  TH1D* hncutcum_;
  TH1D* hnminus1cut_;

  // systematics
  TH1D* hncutsystlo_;
  TH1D* hncutsysthi_;
  TH1D* hncutsystg_;
  
  // N-1 distributions
  TH1D* hnmu_nmo_;
  TH1D* hjete_nmo_;
  TH1D* hjetn60_nmo_;
  TH1D* hjetn90_nmo_;
  TH1D* hntowiphi_nmo_;
  TH1D* hiphifrac_nmo_;
  TH1D* hr1_nmo_;
  TH1D* hr2_nmo_;
  TH1D* hrpk_nmo_;
  TH1D* hrout_nmo_;
  TH1D* hjetemf_nmo_;

  // final selection
  unsigned nSelected_;
  TH1D* searchJetE_;
  TH1D* searchJetEta_;
  TH1D* searchJetPhi_;
  TH1D* searchJetN60_;
  TH1D* searchJetN90_;
  TH1D* searchNtow_;
  TH1D* searchIPhiFrac_;
  TH1D* searchNMu_;
  TH1D* searchNCSC_;
  TH1D* searchBHFlag_;
  TH1D* searchNTrack_;
  TH1D* searchNVtx_;

  std::vector<unsigned long> fillList_;
  std::vector<unsigned> nObsByFill_;

};

#endif

void Search::printCutValues(ostream& o) {
  o << "Stopped HSCP Event" << std::endl;
  o << "  run            = " << event_->run << "\t" << std::endl;
  o << "  lb             = " << event_->lb << "\t" << std::endl;
  o << "  id             = " << event_->id << "\t" << std::endl;
  o << "  bx             = " << event_->bx << "\t" << std::endl;
  double lifetime = event_->bxAfterCollision * TIME_PER_BX;
  o << "  t since coll   = " << lifetime << "\t" << std::endl;
  o << "  orbit          = " << event_->orbit << "\t" << std::endl;
  o << " Cut values :" << std::endl;
  o << "  BX wrt bunch   = " << event_->bxWrtBunch << "\t" << cuts_.bxVeto() << std::endl;
  o << "  BX wrt coll    = " << event_->bxWrtCollision << "\t" << cuts_.bxVeto() << std::endl;
  o << "  nVtx           = " << event_->nVtx << "\t" << cuts_.vertexVeto() << std::endl;
  std::string halo("None");
  if (event_->beamHalo_CSCLoose) halo = "CSCLoose";
  if (event_->beamHalo_CSCTight) halo = "CSCTight";
  o << "  beamHalo       = " << halo << "\t" << cuts_.haloVeto() << std::endl;
  o << "  mu_N           = " << event_->mu_N << "\t\t" << cuts_.cosmicVeto3() << std::endl;
  o << "  cscSeg_N       = " << event_->cscSeg_N << "\t\t" << cuts_.haloVeto() << std::endl;
  o << "  DTSegment_N    = " << event_->DTSegment_N << "\t\t" << cuts_.cosmicVeto3() << std::endl;
  o << "  rpcHit_N       = " << event_->rpcHit_N << "\t\t" << cuts_.cosmicVeto3() << std::endl;
  std::string noise = (event_->noiseFilterResult ? "No" : "Yes");
  o << "  HCAL noise     = " << noise << "\t\t" << cuts_.hcalNoiseVeto() << std::endl;
  o << "  nTowerSameiPhi = " << event_->nTowerSameiPhi << "\t\t" << cuts_.towersIPhiCut() << std::endl;
  o << "  jetE[0]        = " << event_->jetE[0] << "\t" << cuts_.jetEnergyCut() << std::endl;
  o << "  jetEta[0]      = " << event_->jetEta[0] << "\t" << cuts_.jetEnergyCut() << std::endl;
  o << "  jetPhi[0]      = " << event_->jetPhi[0] << "\t" << cuts_.hcalNoiseVeto() << std::endl;
  o << "  jetN60[0]      = " << event_->jetN60[0] << "\t\t" << cuts_.jetN60Cut() << std::endl;
  o << "  jetN90[0]      = " << event_->jetN90[0] << "\t\t" << cuts_.jetN90Cut() << std::endl;
  o << "  jetEMF[0]      = " << (event_->jetEEm[0] / event_->jetEHad[0]) << std::endl;
  o << "  topHPD5R1      = " << event_->topHPD5R1 << "\t" << cuts_.hpdR1Cut() << std::endl;
  o << "  topHPDR2       = " << event_->topHPD5R2 << "\t" << cuts_.hpdR2Cut() << std::endl;
  o << "  topHPD5RPeak   = " << event_->topHPD5RPeak << "\t" << cuts_.hpdRPeakCut() << std::endl;
  o << "  topHPD5ROuter  = " << event_->topHPD5ROuter << "\t" << cuts_.hpdROuterCut() << std::endl;
  o << "  top5DigiR1     = " << event_->top5DigiR1 << "\t" << cuts_.digiR1Cut() << std::endl;
  o << "  top5DigiR2     = " << event_->top5DigiR2 << "\t" << cuts_.digiR2Cut() << std::endl;
  o << "  top5DigiRPeak  = " << event_->top5DigiRPeak << "\t" << cuts_.digiRPeakCut() << std::endl;
  o << "  top5DigiROuter = " << event_->top5DigiROuter << "\t" << cuts_.digiROuterCut() << std::endl;
  o << "  time sample    = ";
  for (unsigned i=0; i<10; ++i) o << event_->top5DigiTimeSamples.at(i) << " ";
  o << std::endl;
  o << "  HPDs           = ";
  for (unsigned i=0; i<event_->hpd_N ; i++)
    o << event_->hpdId[i] << "  ";
  o << std::endl;
  o << std::endl;
}




// this is the event loop
void Search::loop() {

  // DO ANY SETUP HERE
  searchJetE_     = new TH1D("hSearchJetE",    "Search - jet E",    200, 0., 200.);
  searchJetEta_   = new TH1D("hSearchJetEta",  "Search - jet #eta", 70, -3.5, 3.5);
  searchJetPhi_   = new TH1D("hSearchJetPhi",  "Search - jet #phi", 72, -1 * TMath::Pi(), TMath::Pi());
  searchJetN60_   = new TH1D("hSearchJetN60",  "Search - jet n60",  25, -0.5, 24.5);
  searchJetN90_   = new TH1D("hSearchJetN90",  "Search - jet n90",  30, -0.5, 29.5);
  searchNtow_     = new TH1D("hSearchNtow",    "Search - N_{tow}",  20, -0.5, 19.5);
  searchIPhiFrac_ = new TH1D("hSearchIPhiFrac","Search - f_{iphi}", 50, 0., 5.);;
  searchNMu_      = new TH1D("hSearchNMu",     "Search - N_{#mu}",  10, -0.5, 9.5);
  searchNCSC_     = new TH1D("hSearchNCSC",    "Search - N_{CSC}",  20, -0.5, 19.5);
  searchBHFlag_   = new TH1D("hSearchBHFlag",  "Search - Beam Halo flag", 2, -0.5, 1.5);
  searchNTrack_   = new TH1D("hSearchNTrack",  "Search - N_{track}",      20, -0.5, 19.5);
  searchNVtx_     = new TH1D("hSearchNVtx",    "Search - N_{vertex}",     10, -0.5, 9.5);

  hncutind_ = new TH1D("hncutind", "Cut counts", 20, 0., 20.);
  cutAxisLabels(hncutind_);
  hncutcum_ = new TH1D("hncutcum", "Cumulative cut counts", 20, 0., 20.);
  cutAxisLabels(hncutcum_);  
  hnminus1cut_ = new TH1D("hnminus1cut", "N-1 cut counts", 20, 0., 20.);
  cutAxisLabels(hnminus1cut_);

  hncutsystlo_ = new TH1D("hncutsystlo", "Cum cut counts (low JES syst)", 20, 0., 20.);
  cutAxisLabels(hncutsystlo_);  
  hncutsysthi_ = new TH1D("hncutsysthi", "Cum cut counts (hi JES syst)", 20, 0., 20.);
  cutAxisLabels(hncutsysthi_);  
  hncutsystg_ = new TH1D("hncutsystg", "Cum cut counts (Gauss JES syst)", 20, 0., 20.);
  cutAxisLabels(hncutsystg_);  

  hnmu_nmo_ = new TH1D("hnmu_nmo", "N muons (N-1)", 4, -0.5, 3.5);;
  hjete_nmo_ = new TH1D("hjete_nmo", "Leading jet energy (N-1)", 50, 0., 200.);
  hjetn60_nmo_ = new TH1D("hjetn60_nmo", "Leading jet N60 (N-1)", 25, 0., 25.);
  hjetn90_nmo_ = new TH1D("hjetn90_nmo", "Leading jet N90 (N-1)", 25, 0., 25.);
  hntowiphi_nmo_ = new TH1D("hntowsameiphi_nmo", "N leading towers at same iphi (N-1)", 20, -0.5, 19.5);
  hiphifrac_nmo_ = new TH1D("hiphifrac_nmo", "iphi E fraction", 50, 0., 1.);
  hr1_nmo_ = new TH1D("hr1_nmo", "R_{1} (N-1)", 50, 0., 1.);
  hr2_nmo_ = new TH1D("hr2_nmo", "R_{2} (N-1)", 50, 0., 1.);
  hrpk_nmo_ = new TH1D("hrpk_nmo", "R_{peak} (N-1)", 50, 0., 1.);
  hrout_nmo_ = new TH1D("hrout_nmo", "R_{outer} (N-1)", 30, 0., 1.);
  hjetemf_nmo_ = new TH1D("hjetemf_nmo", "Leading jet EM fraction (N-1)", 100, 0., 1.);


  // setup log files
  std::string fd(outdir_);
  fd+="/searchDump.txt";
  std::ofstream dumpFile;
  dumpFile.open(fd.c_str());
  dumpFile << "Cut variables for events passing all cuts" << std::endl << std::endl;
  
  std::string ei(outdir_);
  ei+="/searchEvents.txt";
  std::ofstream eventFile;
  eventFile.open(ei.c_str());

  std::string pf(outdir_);
  pf+="/searchPickEvents.txt";
  std::ofstream pickFile;
  pickFile.open(pf.c_str());

  std::string lf(outdir_);
  lf+="/searchLifetimes.txt";
  std::ofstream lifetimeFile;
  lifetimeFile.open(lf.c_str());

  std::string sf(outdir_);
  sf+="/searchSummary.txt";
  std::ofstream summaryFile;
  summaryFile.open(sf.c_str());

  reset();
  nextEvent();

  for (unsigned long i=0; i<maxEvents_; ++i, nextEvent()) {

    // occasional print out
    if (i%100000==0) {
      std::cout << "Processing " << i << "th event of " <<maxEvents_<< std::endl;
    }

    // YOUR CODE HERE
    bool trig       = cuts_.triggerCut();
    if (!trig) continue;

    livetime_.newEvent(event_->fill, event_->run, event_->lb);

    // count fills etc
    unsigned long fill = event_->fill;
    std::vector<unsigned long>::const_iterator itr2 = find(fillList_.begin(), fillList_.end(), fill);
    if (itr2 == fillList_.end()) fillList_.push_back(fill);
    if (nObsByFill_.size() < fill+1) nObsByFill_.resize(fill+1, 0);

    // event quantities
    int bxWrtBunch  = event_->bxWrtBunch;
    double e(0.), eta(0.), phi(0.);
    unsigned n60(0), n90(0);
    if (event_->jet_N>0) {
      double e        = event_->jetE[0];
      double eta      = event_->jetEta[0];
      double phi      = event_->jetPhi[0];
      unsigned n60    = event_->jetN60[0];
      unsigned n90    = event_->jetN90[0];
    }
    unsigned ntow   = event_->nTowerSameiPhi;
    double fiphi    = event_->leadingIPhiFractionValue;
    double r1       = event_->topHPD5R1;
    double r2       = event_->topHPD5R2;
    double rp       = event_->topHPD5RPeak;
    double ro       = event_->topHPD5ROuter;
    bool bh         = event_->beamHalo_CSCLoose;
    unsigned nmu    = event_->mu_N;
    unsigned ncsc   = event_->cscSeg_N;
    unsigned ntrk   = event_->track_N;
    unsigned nvtx   = event_->nVtx;

    // cut flow histograms
    bool fail=false;
    for (unsigned c=0; c<cuts_.nCuts(); c++) {
      
      // N-1
      if (cuts_.cutNMinusOne(c)) {
	hnminus1cut_->Fill(c);
// 	hbx_nm1_.at(c)->Fill(event.bx);
// 	hrelbx_nm1_.at(c)->Fill(event.bxWrtCollision);
// 	if (event.jet_N > 0) {
// 	  hjete_nm1_.at(c)->Fill(event.jetE[0]);
// 	  hjeteta_nm1_.at(c)->Fill(event.jetEta[0]);
// 	  hjetphi_nm1_.at(c)->Fill(event.jetPhi[0]);
// 	  hjetetaphi_nm1_.at(c)->Fill(event.jetEta[0], event.jetPhi[0]);
// 	}
      }
      // passes all cuts so far
      if (cuts_.cutN(c)) {
	hncutind_->Fill(c);
      }
      
      else fail |= true;
      if (!fail) {
	hncutcum_->Fill(c);
	
      }
    }
    
    // N-1 histograms
    if (cuts_.cutNMinusOne(5)) hnmu_nmo_->Fill(nmu);
    if (cuts_.cutNMinusOne(8)) hjete_nmo_->Fill(e);
    if (cuts_.cutNMinusOne(9)) hjetn60_nmo_->Fill(n60);
    if (cuts_.cutNMinusOne(10)) hjetn90_nmo_->Fill(n90);
    if (cuts_.cutNMinusOne(11)) hntowiphi_nmo_->Fill(ntow);
    if (cuts_.cutNMinusOne(12)) hiphifrac_nmo_->Fill(fiphi);
    if (cuts_.cutNMinusOne(13)) hr1_nmo_->Fill(r1);
    if (cuts_.cutNMinusOne(14)) hr2_nmo_->Fill(r2);
    if (cuts_.cutNMinusOne(15)) hrpk_nmo_->Fill(rp);
    if (cuts_.cutNMinusOne(16)) hrout_nmo_->Fill(ro);
    
    // systematics
    fail=false;
    double smear = 0.95;
    for (unsigned c=0; c<cuts_.nCuts(); c++) {
      if (!cuts_.cutNSyst(c, smear)) fail |= true;
      if (!fail) hncutsystlo_->Fill(c);
    }
    
    fail=false;
    smear = 1.05;
    for (unsigned c=0; c<cuts_.nCuts(); c++) {
      if (!cuts_.cutNSyst(c, smear)) fail |= true;
      if (!fail) hncutsysthi_->Fill(c);
    }

    // final selection histograms
    if (cuts_.cut()) {

      // fill histograms
      searchJetE_->Fill(e);
      searchJetEta_->Fill(eta);
      searchJetPhi_->Fill(phi);
      searchJetN60_->Fill(n60);
      searchJetN90_->Fill(n90);
      searchNtow_->Fill(ntow);
      searchIPhiFrac_->Fill(fiphi);
      searchNMu_->Fill(nmu);
      searchNCSC_->Fill(ncsc);
      searchBHFlag_->Fill(bh);
      searchNTrack_->Fill(ntrk);
      searchNVtx_->Fill(nvtx);

      // write to logs
      printCutValues(dumpFile);
      eventFile << event_->run << "," << event_->lb << "," << event_->orbit << "," << event_->bx << "," << event_->id << std::endl;
      pickFile << event_->run << ":" << event_->lb << ":"  << event_->id << std::endl;
      lifetimeFile << ((event_->bxAfterCollision - 1) *  TIME_PER_BX)/TIME_WINDOW << std::endl;
      lifetimeFile << (event_->bxAfterCollision *  TIME_PER_BX)/TIME_WINDOW << std::endl;
      
      ++nSelected_;
      nObsByFill_.at(fill) += 1;

    }

  }


  // SAVE HISTOGRAMS HERE

  // write logs
  std::cout << "Runs analysed : " << std::endl;
  std::vector<unsigned long> runList = livetime_.runList();
  for (unsigned i=0; i!=runList.size(); ++i) {
    std::cout << runList.at(i) << ",";
  }
  std::cout << std::endl;

  std::cout << "Fills analysed : " << std::endl;
  std::vector<unsigned long> fillList = livetime_.fillList();
  for (unsigned i=0; i!=fillList.size(); ++i) {
    std::cout << fillList.at(i) << ",";
  }
  std::cout << std::endl;

  std::cout << "Run\tLivetime " << std::endl;

  for (unsigned i=0; i!=runList.size(); ++i) {
    std::cout << runList.at(i) << "\t" << livetime_.getLivetimeByRun(runList.at(i)) << std::endl;
  }
  std::cout << std::endl;

  double livetime = livetime_.getTotalLivetime();
  std::cout << "Total livetime : " << livetime << std::endl;

  std::cout << "Final rate : " << nSelected_/livetime
	    << " +/- " << sqrt(nSelected_)/livetime
	    << std::endl;

  std::cout << std::endl;

  // write out cutflow
  std::cout << "[TABLE border=1]" << std::endl;
  unsigned ntot = hncutcum_->GetBinContent(1);
  if (isMC_) std::cout << "|Cut\t|N\t|N-1|-" << std::endl;
  else std::cout << "|Cut\t|N\t|Rate (Hz) |N-1 % |N-1 (Hz)|-" << std::endl;
  for (unsigned i=0; i<cuts_.nCuts(); ++i) {
    unsigned ncum = hncutcum_->GetBinContent(i+1);
    unsigned nind = hncutind_->GetBinContent(i+1);
    unsigned nnmo = hnminus1cut_->GetBinContent(i+1);
    std::string label = hncutcum_->GetXaxis()->GetBinLabel(i+1);
    if (isMC_) {
      if (ntot>0) 
	std::cout << "| " << i << " " << label.c_str() << " | " 
		  << ncum << " | " << nnmo<< " |\n";
      else 
	std::cout << "| " << i << " " << label.c_str() << " | " 
		  << ncum << " | N/A | N/A |\n";
    }
    else {
      if (ntot>0) 
	printf("|%i %s | %i | %.2e +/- %.2e | %i | %.2e +/- %.2e |-\n", 
	       i, label.c_str(), ncum, ncum/livetime, sqrt(ncum)/livetime, nnmo, nnmo/livetime, sqrt(nnmo)/livetime);
      else 
	printf("|%i %s | %i | N/A | N/A | N/A |\n", i, label.c_str(), ncum);
    }
  }
  std::cout << "[/TABLE]" << std::endl;

  std::cout << std::endl;

  std::cout << "\n==================== JES uncertainty: LOW ======================" << std::endl;
   ntot = hncutsystlo_->GetBinContent(1);
  std::cout << "|Cut\t|N\t|cum %\t|N-1 |-" << std::endl;
  for (unsigned i=0; i<cuts_.nCuts(); ++i) {
    unsigned ncum = hncutsystlo_->GetBinContent(i+1);
    std::string label = hncutsystlo_->GetXaxis()->GetBinLabel(i+1);
    if (ntot>0) printf( "|%i %s | %i | %.2e |\n",
                       i, label.c_str(), ncum, 100.*ncum/ntot);

  }

  std::cout << "\n==================== JES uncertainty: HIGH ======================" << std::endl;
  ntot = hncutsysthi_->GetBinContent(1);
  std::cout << "|Cut\t|N\t|cum %\t|N-1 |-" << std::endl;
  for (unsigned i=0; i<cuts_.nCuts(); ++i) {
    unsigned ncum = hncutsysthi_->GetBinContent(i+1);
    std::string label = hncutsysthi_->GetXaxis()->GetBinLabel(i+1);
    if (ntot>0) printf("|%i %s | %i | %.2e |\n",
                       i, label.c_str(), ncum, 100.*ncum/ntot);

  }

  // save histograms
  hncutind_->Write("",TObject::kOverwrite);
  hncutcum_->Write("",TObject::kOverwrite);
  hnminus1cut_->Write("",TObject::kOverwrite);
  hncutsystlo_->Write("",TObject::kOverwrite);
  hncutsysthi_->Write("",TObject::kOverwrite);
  hncutsystg_->Write("",TObject::kOverwrite);
  hnmu_nmo_->Write("",TObject::kOverwrite);
  hjete_nmo_->Write("",TObject::kOverwrite);
  hjetn60_nmo_->Write("",TObject::kOverwrite);
  hjetn90_nmo_->Write("",TObject::kOverwrite);
  hntowiphi_nmo_->Write("",TObject::kOverwrite);
  hiphifrac_nmo_->Write("",TObject::kOverwrite);
  hr1_nmo_->Write("",TObject::kOverwrite);
  hr2_nmo_->Write("",TObject::kOverwrite);
  hrpk_nmo_->Write("",TObject::kOverwrite);
  hrout_nmo_->Write("",TObject::kOverwrite);
  hjetemf_nmo_->Write("",TObject::kOverwrite);
  searchJetE_->Write("",TObject::kOverwrite);
  searchJetEta_->Write("",TObject::kOverwrite);
  searchJetPhi_->Write("",TObject::kOverwrite);
  searchJetN60_->Write("",TObject::kOverwrite);
  searchJetN90_->Write("",TObject::kOverwrite);
  searchNtow_->Write("",TObject::kOverwrite);
  searchIPhiFrac_->Write("",TObject::kOverwrite);
  searchNMu_->Write("",TObject::kOverwrite);
  searchNCSC_->Write("",TObject::kOverwrite);
  searchBHFlag_->Write("",TObject::kOverwrite);
  searchNTrack_->Write("",TObject::kOverwrite);
  searchNVtx_->Write("",TObject::kOverwrite);

  // write livetime histograms
  livetime_.writeHistograms(ofile_);

  TH1D* hNObsByFill = new TH1D("hNObsByFill", "N_{obs}", fillList_.size(), 0, 0);

  std::sort(fillList_.begin(), fillList_.end());
  std::vector<unsigned long>::const_iterator fitr;
  for (fitr=fillList_.begin(); fitr!=fillList_.end(); ++fitr) {
    unsigned long fill = *fitr;
    std::stringstream sstr;
    sstr << (fill);
    std::string fillstr = sstr.str();
    
    hNObsByFill->Fill(fillstr.c_str(), 0.);
    for (unsigned i=0; i<nObsByFill_.at(fill); ++i) hNObsByFill->Fill(fillstr.c_str(), 1);
  }

  hNObsByFill->Write("",TObject::kOverwrite);

//   // write out parameters file for next step
//   std::string pf(outdir_);
//   pf+="/parameters.txt";
//   std::ofstream paramFile;
//   paramFile.open(pf.c_str());

//   paramFile << "mass\t\t\t200" << std::endl;
//   paramFile << "crossSection\t\t606" << std::endl;
//   paramFile << "lifetime\t\t1" << std::endl;
//   paramFile << "signalEff\t\t0.033652" << std::endl;
//   paramFile << "signalEff_e\t\t0.0" << std::endl;
//   paramFile << "bgRate\t\t\t";
//   paramFile << str(bgRate_exp)+"" << std::endl;
//   paramFile << "bgRate_e\t\t";
//   paramFile << str(bgRate_exp_err)+"" << std::endl;
//   paramFile << "scaleUncert\t\t";
//   paramFile << str(scaleUncert) +"" << std::endl;
//   paramFile << "optimizeTimeCut\t\t1" << std::endl;
//   paramFile << "histFile\t\t";
//   paramFile << ddir+"/histograms.root" << std::endl;
//   paramFile << "lumiFile\t\t";
//   paramFile << cmsswdir+"/src/StoppedHSCP/Analysis/data/lumi_all.csv" << std::endl;
//   paramFile << "jsonFile\t\t";
//   paramFile << cmsswdir+"/src/StoppedHSCP/Analysis/data/"+dataset+".root" << std::endl;
//   paramFile << "lumiFirstRun\t\t";
//   paramFile << runlist[0]+"" << std::endl;  
//   paramFile << "lumiLastRun\t\t";
//   paramFile << runlist[len(runlist)-1]+"" << std::endl;
//   paramFile << "fills\t\t\t";
//   paramFile << fillsStr+"" << std::endl;
//   paramFile << "eventsFile\t\t";
//   paramFile << ddir+"/eventList.log" << std::endl;
//   paramFile << "nTrialsSignal\t\t100" << std::endl;
//   paramFile << "nTrialsBackground\t100" << std::endl;
//   paramFile << "simulateExpt\t\t0" << std::endl;
//   paramFile << "fillScheme\t\tSingle_2b_1_1_1" << std::endl;
//   paramFile << "beamOnTime\t\t0." << std::endl;
//   paramFile << "beamOffTime\t\t0." << std::endl;
//   paramFile << "instLumi\t\t0." << std::endl;
//   paramFile << "runningTime\t\t0." << std::endl;


  // close files
  eventFile.close();
  pickFile.close();
  dumpFile.close();
  lifetimeFile.close();
  summaryFile.close();
  //  paramFile.close();


}

void Search::cutAxisLabels(TH1D* h) {

  for (unsigned i=0; i<cuts_.nCuts(); ++i) {
    h->GetXaxis()->SetBinLabel(i+1, cuts_.cutName(i).c_str());
  }

}


// this is the main program, no need to do anything here
int main(int argc, char* argv[]) {

  // sum of squares error info for histograms
  TH1D::SetDefaultSumw2();

  // create analysis
  Search analyser(argc, argv);

  analyser.setup();

  analyser.cuts().print(std::cout);

  analyser.loop();

  return 0;

}
