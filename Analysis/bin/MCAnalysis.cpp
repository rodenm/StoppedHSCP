#ifndef MCAnalysis_h
#define MCAnalysis_h

/**
 * Marissa Rodenburg, Dec 2011
 * 
 * Takes text files with lists of events selected by HSCP and stopped HSCP analysis
 * and compares the events.
 * 
 * To run:
 * ---------
 *
   mcAnalysis --mc -o mcAnalysis_test -i /store/user/rodenm/data/mcgluino/stoppedHSCP_tree_Summer11Repro_428p5_V20_HSCP_RECO_Gluino700/Gluino700/ --doOverlap --energy=700 --hscp-eventlist=hscp_ntuples/eventlists_HSCP/HSCPSelected_Gluino700.txt --stopped-eventlist=results/gluino/Gluino700_Neutralino592/pickEvents.txt --flavor=gluino

 *
 *
   mcAnalysis --mc -o mcAnalysis_test -i /store/user/rodenm/data/mcgluino/stoppedHSCP_tree_Summer11Repro_428p5_V20_Gluino700_Neutralino592_v4/Gluino700/ --doEfficiencies

 *
 * Notes:
 * -------------
 * 1. On first iteration, overlap study requires ntuples made from HSCP RECO sets because 
 *    these include all events, stopped, HSCP, or neither. This wouldn't be necessary if 
 *    the stopped ntuples had the MC for all events. However, this makes things tricky 
 *    because then we can't use cuts_ because the ntuples don't have the RECO
 *    information from the stage 2 stopped MC. Instead (for now), the overlap study has 
 *    to use the text file output of the selected events from runAnalysis.py. 
 *
 * 2. Runs, lb, and event numbers overlap between the bx0 and bx1 sets for gluino. These 
 *    need to be analyzed separately, even though one text file describes the HSCP 
 *    selection for both.
 * 
 * 3. Need to avoid making assumptions about the number of stage 1 events that were 
 *    processed for any analysis here due to the fact that some stage 2 jobs segfaulted 
 *    and I just let them die. For instance, the Gluino900 sample has 50,000 events in it, 
 *    but only 49,800 were processed to make stage 2. Similarly for stop and stau. On the 
 *    other hand, HSCP analysis doesn't appear to have lost any jobs (I believe, but I 
 *    have not confirmed).
 *
 * 4. For the efficiency study, the geometric boundaries for the regions Tracker, EE, EB,
 *    HE, HB, ME, and MB are approximate. There is also a region in the outside corner of
 *    HB that seems to be uninstrumented, but I'm not 100% certain. There typically are
 *    stopped particles there and they do occasionally pass selection.
 */

#include "StoppedHSCP/Analysis/interface/BasicAnalyser.h"

#include "TFile.h"
#include "TChain.h"
#include "TH1D.h"
#include "TCanvas.h"
#include "TLorentzVector.h"
#include "TLegend.h"
#include "TStyle.h"

#include <cmath>
#include <sstream>
#include "stdlib.h"

#include <boost/program_options.hpp>

#include <TROOT.h>

using namespace std;
namespace po = boost::program_options;

// The code handling r-hadron pid <-> name is taked from 
// StoppedHSCP/Simulation/plugins/Pythia6HSCPGun.cc
const int specialNumber = 32;
const int specialPid [specialNumber] = {
  1000993,1009213,1009313,1009323,1009113,
  1009223,1009333,1091114,1092114,1092214,
  1092224,1093114,1093214,1093224,1093314,
  1093324,1093334,
  1000612,1000622,1000632,1000642,1000652,
  1006113,1006211,1006213,1006223,1006311,
  1006313,1006321,1006323,1006333,
  1000015
};
const std::string specialName [specialNumber] = {
  "~g_glueball","~g_rho+","~g_K*0","~g_K*+","~g_rho0",
  "~g_omega","~g_phi","~g_Delta-","~g_Delta0","~g_Delta+",
  "~g_Delta++","~g_Sigma*-","~g_Sigma*0","~g_Sigma*+","~g_Xi*-",
  "~g_Xi*0 ","~g_Omega-",
  "~T+","~T0","~T_s+","~T_c0","~T_b+",
  "~T_dd10","~T_ud0+","~T_ud1+","~T_uu1++","~T_sd00",
  "~T_sd10","~T_su0+","~T_su1+","~T_ss10",
  "tau1"
};

const std::string specialAntiName [specialNumber] = {
  "~g_glueball","~g_rho-","~g_K*bar0","~g_K*-","~g_rho0",
  "~g_omega","~g_phi","~g_Deltabar+","~g_Deltabar0","~g_Deltabar-",
  "~g_Deltabar--","~g_Sigma*bar+","~g_Sigma*bar0","~g_Sigma*bar-","~g_Xi*bar+",
  "~g_Xi*bar0","~g_Omegabar+",
  "~Tbar-","~Tbar0","~Tbar_s-","~Tbar_c0","~Tbar_b-",
  "~Tbar_dd10","~Tbar_ud0-","~Tbar_ud1-","~Tbar_uu1--","~Tbar_sd00",
  "~Tbar_sd10","~Tbar_su0-","~Tbar_su1-","~Tbar_ss10",
  "~tau1"
};

int getSpecialId (const TString& fName) {
  for (int i = 0; i < specialNumber; ++i) {
    if (fName == specialName[i]) return specialPid[i];
    if (fName == specialAntiName[i]) return -specialPid[i];
  }
  return 0;
}

struct EventInfo {
  EventInfo(): run(0),lb(0),id(0) {}
  unsigned run;
  unsigned lb;
  unsigned id;
};

// Required to use EventInfo as the key in a map
bool operator<(EventInfo const& e1, EventInfo const& e2) {
  return e1.run < e2.run || (e1.run == e2.run && e1.lb < e2.lb) || 
    (e1.run == e2.run && e1.lb == e2.lb && e1.id < e2.id);
}

class MCAnalysis : public BasicAnalyser {
  
public:
  MCAnalysis(int argc, char* argv[]) :
    BasicAnalyser(argc, argv), doOverlap_(false), doBX1_(false), doEfficiencies_(false){ 
    gROOT->ProcessLine(".X ~/.rootlogon.C");
 
    // Save commandline to write out to dumpFile_ 
    for (int i = 0; i < argc; i++)
      commandLine_ += argv[i];
    commandLine_ += "\n";

   // get options
    po::options_description desc("Custom options");
    po::positional_options_description poptd;
    
    desc.add_options()
      ("doOverlap", "Do the overlap analysis between stopped HSCP and HSCP. Also requires -e and -f options.")
      ("doBX1", "In overlap analysis, look at bx1 events from HSCP analysis.")
      ("doEfficiencies", "Print info needed to calculate efficiencies")
      ("hscp-eventlist,e", po::value<std::string>(), "Text file with list of selected events from HSCP analysis")
      ("stopped-eventlist,f", po::value<std::string>(), "Text file with list of selected events from stopped HSCP analysis")
      ("mass", po::value<std::string>(), "Mass of the gluino/stop/stau")
      ("flavor", po::value<std::string>(), "Flavor of the sparticle (gluino/stop/stau)")
      ("nStage1", po::value<unsigned>(), "Number of stage 1 events (usually 50000)");

    po::variables_map vm;
    po::store(po::command_line_parser(argc, argv).options(desc).allow_unregistered().run(), vm);
    po::notify(vm);

    // get my custom option
    if (vm.count("hscp-eventlist")) {
      eventList_hscp_ = vm["hscp-eventlist"].as<std::string>();
      std::cout << "HSCP event list    : " << eventList_hscp_ << std::endl;
    }
    if (vm.count("stopped-eventlist")) {
      eventList_stopped_ = vm["stopped-eventlist"].as<std::string>();
      std::cout << "Stopped event list : " << eventList_stopped_ << std::endl;
    }

    // TODO: set sparticleM_ & flavor_ by reading the ntuples
    // TODO: for now, need to require these fields are filled before proceeding
    //sparticleM_ = "700";
    //flavor_ = std::string("gluino");
    if (vm.count("mass")) {
      sparticleM_ = vm["mass"].as<std::string>();
      std::cout << "Sparticle mass   : " << sparticleM_ << std::endl;
    
    } else {
      std::cout << "Must provide sparticle mass with --mass" <<std::endl;
      exit(3);
    }

    if (vm.count("flavor")) {
      flavor_ = vm["flavor"].as<std::string>();
      std::cout << "Sparticle flavor   : " << flavor_ << std::endl;
    }
    if (vm.count("doOverlap")) {
      doOverlap_ = true;
    }
    if (vm.count("doBX1")) {
      doBX1_ = true;
    }
    if (vm.count("doEfficiencies")) {
      doEfficiencies_ = true;
    }
    if (vm.count("nStage1")) {
      nStage1_ = vm["nStage1"].as<unsigned>();
    } else {
      std::cout << "Must provide number of stage 1 events with --nStage1" <<std::endl;
      exit(3);
    }

    intersect_count_ = 0;
    
    trigger_ = 0;
    eb_trigger_ = 0;
    hb_trigger_ = 0;

    hb_count_ = 0;
    he_count_ = 0;
    eb_count_ = 0;
    ee_count_ = 0;
    mb_count_ = 0;
    me_count_ = 0;

    reco_tracker_count_ = 0;
    reco_hb_count_ = 0;
    reco_he_count_ = 0;
    reco_eb_count_ = 0;
    reco_ee_count_ = 0;
    reco_mb_count_ = 0;
    reco_me_count_ = 0;
    reco_other_count_ = 0;

    detector_count_ = 0;
    tracker_count_ = 0;
    total_count_ = 0;
    cavern_count_ = 0;
    rbaryon_count_ = 0;
    not_rbaryon_count_ = 0;
    not_rbaryon_inhbeb_count_ = 0;
    glueball_count_ = 0;
    selected_count_ = 0;
    selected_indetector_count_ = 0;

    selected_systhi_ = 0;
    selected_systlo_ = 0;
    jes_hi_ = 1.10;
    jes_lo_ = 0.90;
    jetCut_ = 70.;

  
  // TODO: obviously this is not the best way.But it is ok that the options are xor:
  //       since the different options take different input files, they can't
  //       be run at the same time.
  if (doOverlap_)
    ofilename_ = "MCAnalysis_" +flavor_ + sparticleM_  + "_overlapHists.root"; 
  else if (doEfficiencies_) 
    ofilename_ = "MCAnalysis_" +flavor_ + sparticleM_ + "_efficiencyHists.root"; 
  else
    ofilename_ = "MCAnalysis_" +flavor_ + sparticleM_ + "_hists.root";

  }
     
  
  ~MCAnalysis() { };
  
  // Analysis methods
  virtual void loop();
  
private:
  int overlapStudy();
  void efficiencyStudy();

  // Setup methods
  int readHSCPEvents();
  int readStoppedEvents();
  
  // Helpers
  double beta(double mass, double energy);
  double eta(double x, double y, double z, double time);

  // Control variables
  bool doOverlap_;
  bool doBX1_;
  bool doEfficiencies_;

  // Overlap hists
  TH1D* hbeta_all_;
  TH1D* hbeta_hscp_;
  TH1D* hbeta_stopped_;
  TH1D* hbeta_intersect_;
  TH1D* hbeta_stopped_intersect_;

  // histogram used to calculate daughter particle energy (particularly for tops)
  TH1D* hdaughter_E_;

  int intersect_count_;

  std::string sparticleM_;
  std::string flavor_;
  int nStage1_;

  std::string eventList_hscp_;
  std::string eventList_stopped_;

  std::ifstream hscp_file_;
  std::ifstream stopped_file_;

  int trigger_;
  int hb_trigger_;
  int eb_trigger_;

  int hb_count_;
  int he_count_;
  int eb_count_;
  int ee_count_;
  int mb_count_;
  int me_count_;

  int reco_tracker_count_;
  int reco_hb_count_;
  int reco_he_count_;
  int reco_eb_count_;
  int reco_ee_count_;
  int reco_mb_count_;
  int reco_me_count_;
  int reco_other_count_;

  int detector_count_;
  int tracker_count_;
  int total_count_;
  int cavern_count_;
  int not_rbaryon_count_;
  int not_rbaryon_inhbeb_count_;
  int rbaryon_count_;
  int glueball_count_;
  int selected_count_;
  int selected_indetector_count_;

  // For JES systematic uncertainties
  int selected_systlo_;
  int selected_systhi_;
  double jes_lo_;
  double jes_hi_;
  double jetCut_;

  // TODO: find a way to handle the situation where hscp has more than one gluino listed. 
  // Stupid option: add a second map/make the second arg an array (for both maps)
  map<EventInfo, double> hscp_phimap_;

  // Can't get phi info for stopped events until we reach the event in loop(). This map
  // just stores if the event was selected or not. 
  map<EventInfo, int> stopped_map_;

  // Output file 
  std::ofstream dumpFile_;
  std::ofstream tableFile_;
  std::ofstream eventListFile_;

  std::string commandLine_;
  std::ostringstream neutralinoMass_;
};

#endif

// this is the event loop
void MCAnalysis::loop() {

  // SETUP
  hbeta_all_               = new TH1D("hbeta_all", "", 100, 0., 1.);
  hbeta_hscp_              = new TH1D("hbeta_hscp", "", 100, 0., 1.);
  hbeta_stopped_           = new TH1D("hbeta_stopped", "", 100, 0., 1.);
  hbeta_intersect_         = new TH1D("hbeta_intersect", "", 100, 0., 1.);
  hbeta_stopped_intersect_ = new TH1D("hbeta_stopped_intersect", "", 100, 0., 1.);

  hdaughter_E_             = new TH1D("hdaughter_E", "", 6000, 0., 600.);
  
  // TODO: add general histogramer method
  // dE, radial distribution, distribution of selected events, delta-phi between stopped points

  reset();
  nextEvent();

  neutralinoMass_ << event_->mcNeutralinoMass[0];

  // setup log files
  std::string fd(outdir_);
  std::string td(outdir_);
  std::string ed(outdir_);
  fd+="/MCAnalysis_" +flavor_ + sparticleM_ + "_neutralino" +neutralinoMass_.str() + "_";
  td+="/MCAnalysis_" +flavor_ + sparticleM_ + "_neutralino" +neutralinoMass_.str() + "_";
  ed+="/MCAnalysis_" +flavor_ + sparticleM_ + "_neutralino" +neutralinoMass_.str() + "_";

  if (doOverlap_) 
    fd+="overlap.txt";
  else if (doEfficiencies_) {
    fd+="efficiencies.txt";
    td+="efficiencyTable.txt";
    ed+="eventList.txt";
    tableFile_.open(td.c_str());
    eventListFile_.open(ed.c_str());
  }
  else 
    fd+="other.txt";

  dumpFile_.open(fd.c_str());
  dumpFile_ << "Output from mcAnalysis" << std::endl << std::endl;
  dumpFile_ << "Command line       : " << commandLine_.c_str();

  // print input files
  dumpFile_ << "Ntuple files       : " <<std::endl;
  for (std::vector<std::string>::iterator file=ifiles_.begin(); file!=ifiles_.end(); ++file)
    dumpFile_ << (*file) << std::endl;
  dumpFile_ << "Number of events   : " << maxEvents_ << std::endl;
  dumpFile_ << "Sparticle energy   : " << sparticleM_ << std::endl;
  dumpFile_ << "Sparticle flavor   : " << flavor_ << std::endl;
  dumpFile_ << "Neutralino mass    : " << neutralinoMass_.str() << std::endl << std::endl;

  dumpFile_ << "Output files       : \n\t" << fd.c_str() << "\n\t" << td.c_str() << std::endl;
  

  // Begin analysis of the monte carlo events
  if (doOverlap_) {
    dumpFile_ << "\n*** Begining overlap study...\n" << std::endl;
    dumpFile_ << maxEvents_ << " events in ntuples." << std::endl;
    hscp_file_.open(eventList_hscp_.c_str());
    if (readHSCPEvents() != 0) {
      std::cout << "ERROR --- Could not open hscp_file_: " << eventList_hscp_ << std::endl;
    }
    stopped_file_.open(eventList_stopped_.c_str());
    if (readStoppedEvents() != 0) {
      std::cout << "ERROR --- Could not open stopped_file_: " << eventList_stopped_ << std::endl;
    }
  }
  
  if (doEfficiencies_) 
    dumpFile_ << "\n*** Begining calculate efficiencies..." << std::endl;

  // EVENT LOOP
  for (unsigned long i=0; i<maxEvents_; ++i, nextEvent()) {
    if (i%2000==0 && i > 1)
      std::cout << "Processing " << i << "th event of " <<maxEvents_<< std::endl;

    if (doOverlap_) overlapStudy();
    else if (doEfficiencies_) efficiencyStudy();

  }

  // POST-LOOP OUTPUT
  if (doEfficiencies_) {
    dumpFile_ << "-------------------------------" << std::endl;
    dumpFile_ << "Total count = " << total_count_ << std::endl;
    dumpFile_ << "Total selected = " << selected_count_ << std::endl << std::endl;
    dumpFile_ << "Total trigger = " << trigger_ << std::endl;
    dumpFile_ << "Passed trigger (EB) = " << eb_trigger_ << std::endl;
    dumpFile_ << "Passed trigger (HB) = " << hb_trigger_ << std::endl<<std::endl;

    dumpFile_ << "Tracker count = " << tracker_count_ << std::endl;
    dumpFile_ << "EB count = " << eb_count_ << std::endl;
    dumpFile_ << "EE count = " << ee_count_ << std::endl;
    dumpFile_ << "HB count = " << hb_count_ << std::endl;
    dumpFile_ << "HE count = " << he_count_ << std::endl;
    dumpFile_ << "MB count = " << mb_count_ << std::endl;
    dumpFile_ << "ME count = " << me_count_ << std::endl << std::endl;

    dumpFile_ << "Tracker & selected count = " << reco_tracker_count_ << std::endl;
    dumpFile_ << "EB & selected count = " << reco_eb_count_ << std::endl;
    dumpFile_ << "EE & selected count = " << reco_ee_count_ << std::endl;
    dumpFile_ << "HB & selected count = " << reco_hb_count_ << std::endl;
    dumpFile_ << "HE & selected count = " << reco_he_count_ << std::endl;
    dumpFile_ << "MB & selected count = " << reco_mb_count_ << std::endl;
    dumpFile_ << "ME & selected count = " << reco_me_count_ << std::endl;
    dumpFile_ << "Detector & selected count = " << selected_indetector_count_ << std::endl << std::endl;;

    dumpFile_ << "Other & selected count = " << reco_other_count_ << std::endl << std::endl;
 
    dumpFile_ << "detector_count = " << detector_count_ << std::endl;
    dumpFile_ << "cavern count = " << cavern_count_ << std::endl;
    dumpFile_ << "no r-baryon count = " << not_rbaryon_count_ << std::endl;
    dumpFile_ << "no r-baryon (stopped in EB+HB) count = " << not_rbaryon_inhbeb_count_ << std::endl;
    dumpFile_ << "glueball count = " << glueball_count_ << std::endl << std::endl;
    
    cout.precision(5);
    tableFile_ << flavor_ << " " 
	       << sparticleM_ << "\t" 
	       << fixed << hdaughter_E_->GetMean() << "\t"
	       << fixed << hdaughter_E_->GetMeanError() << "\t"
	       << neutralinoMass_.str() << "\t"
	       << eb_trigger_+hb_trigger_ << "\t"
	       << eb_count_+hb_count_ << "\t" 
	       << reco_eb_count_+reco_hb_count_ << "\t" // stopped count; selected count
	       << fixed << 1.0*(eb_count_+hb_count_)/nStage1_ << "\t"// stopping eff
	       << fixed << 1.0*(reco_eb_count_+reco_hb_count_)/(eb_count_+hb_count_)<< "\t"     // reco eff
	       << fixed << 1.0*(eb_trigger_+hb_trigger_)/(eb_count_+hb_count_)<< "\t" // trigger eff
	       << selected_systlo_<< "\t"
	       << selected_systhi_<< "\t"
	       << fixed << fabs((reco_eb_count_+reco_hb_count_)-selected_systlo_)*1.0/(reco_eb_count_+reco_hb_count_) << "\t"         // low JES uncertainty
	       << fixed << fabs((reco_eb_count_+reco_hb_count_)-selected_systhi_)*1.0/(reco_eb_count_+reco_hb_count_)                 // hi JES uncertainty
	       << std::endl;
  }

  if (doOverlap_) {
    dumpFile_ << "Found " << intersect_count_ << " events present in both analyses." << std::endl;
    hbeta_hscp_->SetLineColor(kGreen);
    hbeta_stopped_->SetLineColor(kBlue);
    hbeta_intersect_->SetLineColor(kRed);
    hbeta_stopped_intersect_->SetLineColor(kMagenta);

    hbeta_hscp_->SetMarkerColor(kGreen);
    hbeta_stopped_->SetMarkerColor(kBlue);
    hbeta_intersect_->SetMarkerColor(kRed);
    hbeta_stopped_intersect_->SetMarkerColor(kMagenta);
    
    //hbeta_all_->SetMarkerStyle(22);
    //hbeta_hscp_->SetMarkerStyle(22);
    //hbeta_stopped_->SetMarkerStyle(22);
    //hbeta_intersect_->SetMarkerStyle(22);
    //hbeta_stopped_intersect_->SetMarkerStyle(22);

    TCanvas c2("c2","");
    c2.SetLogy();
    hbeta_all_->SetMaximum(100000);
    hbeta_all_->GetXaxis()->SetTitle("#beta");
    //hbeta_all_->GetYaxis()->SetTitle("Label of y axis");
    gStyle->SetOptStat(0);
    hbeta_all_->Draw(); // was "hist p"
    hbeta_hscp_->Draw("same");
    hbeta_intersect_->Draw("same");
    hbeta_stopped_intersect_->Draw("same");
    hbeta_stopped_->Draw("same");
    
    // TODO: save this in the output directory, not in this directory
    TLegend *leg = new TLegend(0.5, 0.7, 0.88, 0.88);
    leg->AddEntry(hbeta_all_, "All R-hadrons", "le");
    leg->AddEntry(hbeta_hscp_, "HSCP-selected R-hadrons", "le");
    leg->AddEntry(hbeta_stopped_, "Stopped HSCP-selected R-hadrons", "le");
    leg->AddEntry(hbeta_stopped_intersect_, "R-hadrons from overlap events (stopped #beta)", "le");
    leg->AddEntry(hbeta_intersect_, "R-hadrons from overlap events (HSCP #beta)", "le");
    leg->SetHeader("CMS Simulation");
    leg->SetFillColor(kWhite);
    leg->Draw();
    std::string pdfname = "MCAnalysis_" +flavor_ + sparticleM_ + "_overlaphists.pdf";
    c2.SaveAs(pdfname.c_str());
  }
  
  // AGGREGATE, CLEAN UP & SAVE
  if (doOverlap_) {
    hbeta_all_->Write("",TObject::kOverwrite);
    hbeta_hscp_->Write("",TObject::kOverwrite);
    hbeta_stopped_->Write("",TObject::kOverwrite);
    hbeta_intersect_->Write("",TObject::kOverwrite);
    hbeta_stopped_intersect_->Write("",TObject::kOverwrite);
    
    hscp_file_.close();
    stopped_file_.close();
    tableFile_.close();
    eventListFile_.close();
  }
 }
  
/**
 * overlapStudy()
 *
 * Produces plots comparing stopped and HSCP event selection.
 * 
 * Ignores possibility that more than one particle may have stopped.
 */
int MCAnalysis::overlapStudy() {
  bool isHSCPEvent = false;
  bool isStoppedEvent = false;
  
  for (unsigned iHad = 0; iHad < event_->mcRhadron_N; iHad++) {
    double b = beta(event_->mcRhadronMass[iHad], event_->mcRhadronE[iHad]);
    hbeta_all_->Fill(b);
  }

  EventInfo info;
  info.run = event_->run;
  info.lb = event_->lb;
  info.id = event_->id;
  
  // HSCP EVENTS
  // Find the r-hadron that best matches the HSCP value of phi.
  double hscpBeta = -1.0;
  map<EventInfo, double>::iterator hscp_phi_iter;
  hscp_phi_iter = hscp_phimap_.find(info);
  if (hscp_phi_iter != hscp_phimap_.end()) {
    isHSCPEvent = true;
    unsigned iMatch;
    double hscp_phi = hscp_phimap_[info];
    if (acos(cos(event_->mcRhadronPhi[0] - hscp_phi)) < acos(cos(event_->mcRhadronPhi[1] - hscp_phi))) {
      iMatch = 0;
    } else {
      iMatch = 1;
    }
    hbeta_hscp_->Fill(hscpBeta = beta(event_->mcRhadronMass[iMatch], event_->mcRhadronE[iMatch]));
  }

  // STOPPED EVENTS
  // About 90% of stopped events only have one stopped point, so as a first pass,
  // I'm just treating the first stopped point in the vector as the one that caused
  // the trigger/selection. Since we want to plot beta, we need to associate the 
  // stopped point with the initial R-hadron that resulted in the stopped point.
  // Only the 4-momentum of the mcRhadrons are available, so use eta-phi of the
  // R-hadrons and eta-phi of the stopped point to match them.
  double stoppedBeta = -1.0;
  map<EventInfo, int>::iterator stopped_iter;
  stopped_iter = stopped_map_.find(info);
  if (stopped_iter != stopped_map_.end()) {
    isStoppedEvent = true;
    double stoppedEta = eta(event_->mcStoppedParticleX[0], 
			    event_->mcStoppedParticleY[0], 
			    event_->mcStoppedParticleZ[0],  
			    event_->mcStoppedParticleTime[0]);
    double deltaR0 = sqrt(pow(stoppedEta - event_->mcRhadronEta[0],2) 
			  + pow(event_->mcStoppedParticlePhi[0] - event_->mcRhadronPhi[0], 2));
    double deltaR1 = sqrt(pow(stoppedEta - event_->mcRhadronEta[1], 2) 
			  + pow(event_->mcStoppedParticlePhi[0] - event_->mcRhadronPhi[1], 2));

    unsigned iMatch = deltaR0 < deltaR1 ? 0 : 1;
    hbeta_stopped_->Fill(stoppedBeta = beta(event_->mcRhadronMass[iMatch], event_->mcRhadronE[iMatch]));
  }

  // OVERLAP EVENTS
  // Use the HSCP event's value of beta for the intersection histogram.
  // TODO: can we check if it's actually the same r-hadron that is selected for both 
  // analyses? To do this, we would probably need more info about the HSCP event than just 
  // the phi.
  if (isStoppedEvent && isHSCPEvent) {
    hbeta_intersect_->Fill(hscpBeta);
    hbeta_stopped_intersect_->Fill(stoppedBeta);
    intersect_count_++;
  }
  
  return 0;
}

/**
 * efficiencyStudy()
 *
 * Prints out the counts needed for various efficiency calculations
 */
void MCAnalysis::efficiencyStudy() {
  total_count_++;

  hdaughter_E_->Fill(event_->mcDaughterE[0]);
  
  if (cuts_.cut()) 
    selected_count_++;
  
// count # of DTs outside the innermost DT cylinder
  double outerDT = 0.000001; // avoid divide by zero
  int innerDT = 0;

  double testPhi;
  double maxDeltaPhi = -1.;
  for (unsigned idt = 0; idt<event_->DTSegment_N; idt++){
    if (idt == 0) {
      testPhi = event_->DTSegPhi[0];
      //std::cout << testPhi << "   ";
    } else {
      //std::cout << event_->DTSegPhi[idt] << "   ";
      double deltaphi = acos(cos(event_->DTSegPhi[idt] - testPhi));
      if (deltaphi > maxDeltaPhi) maxDeltaPhi = deltaphi;
    }
    if (event_->DTSegR[idt] > 480) outerDT++;
    else innerDT++;
  }

  unsigned nCloseRPCPairs = 0;
  double frac = 1.0*innerDT/outerDT;
  if ( outerDT < 3 ) {
    for (unsigned irpc = 0; irpc < event_->rpcHit_N; irpc++) {
      if (event_->rpcHitR[irpc] < 670) continue;              
      for (unsigned jrpc = irpc+1; jrpc < event_->rpcHit_N; jrpc++) {
        if (event_->rpcHitR[jrpc] < 670) continue;                   
        double deltaZ = fabs(event_->rpcHitZ[irpc] - event_->rpcHitZ[jrpc]);
        double deltaPhi = acos(cos(event_->rpcHitPhi[irpc] - event_->rpcHitPhi[jrpc]));

	// Require hits to be localized in z or in phi
        if (deltaZ < 40.0 || deltaPhi > TMath::Pi()/2.) { //  || deltaPhi < 0.2
	  nCloseRPCPairs++;
        }
      }
    }
  }
  if (cuts_.cutNMinusOne(5) && !cuts_.cutN(5))
      eventListFile_ << event_->run << "\t" << event_->lb << "\t" << event_->id << "\t"
		     << event_->DTSegment_N << "\t" << event_->rpcHit_N << "\t"
		     << maxDeltaPhi << "\t" << frac << "\t" << nCloseRPCPairs 
		     << std::endl;;
  

  if (cuts_.triggerCut()) trigger_++;
  // Associate leading jet with stopped point
  // If no reconstructed jets, just use first stopped point.
  // TODO: The no-jet solution is kind of a cop-out.

  unsigned iMatch;
  if (event_->jet_N == 0 || event_->mcStoppedParticle_N == 1) {
    iMatch = 0;
  } else {
    double stoppedEta0 = eta(event_->mcStoppedParticleX[0], 
			     event_->mcStoppedParticleY[0], 
			     event_->mcStoppedParticleZ[0],  
			     event_->mcStoppedParticleTime[0]);
    double stoppedEta1 = eta(event_->mcStoppedParticleX[1], 
			     event_->mcStoppedParticleY[1], 
			     event_->mcStoppedParticleZ[1],  
			     event_->mcStoppedParticleTime[1]);
    double deltaR0 = sqrt(pow(event_->jetEta[0] - stoppedEta0, 2) 
			  + pow(event_->jetPhi[0] - event_->mcStoppedParticlePhi[0], 2));

    double deltaR1 = sqrt(pow(event_->jetEta[0] - stoppedEta1, 2) 
			  + pow(event_->jetPhi[0] - event_->mcStoppedParticlePhi[1], 2));

    iMatch = deltaR0 < deltaR1 ? 0 : 1;    
  }

  int pid = getSpecialId(event_->mcStoppedParticleName[iMatch]);
  double r = event_->mcStoppedParticleR[iMatch]/10.0;
  double z = event_->mcStoppedParticleZ[iMatch]/10.0;
  double particle_eta = eta(event_->mcStoppedParticleX[iMatch],event_->mcStoppedParticleY[iMatch],
			    event_->mcStoppedParticleZ[iMatch],event_->mcStoppedParticleTime[iMatch]);
  
  if (abs(pid) % 100000 < 90000 && flavor_ == "gluino") // Not an R-baryon w/ gluino
    not_rbaryon_count_++;

  // Identify which detector region the particles stopped in. For ME and MB, this definition includes
  // the entire muon system, not just the yokes.
  if (r < 131.0 && fabs(particle_eta) <= 2.5 && fabs(z) < 300.0) { // TRACKER
    tracker_count_++;
    if (cuts_.cut()) reco_tracker_count_++;
  } else if (r>=131.0 && r<184.0 && fabs(z)<376.0 && fabs(particle_eta)<1.479) { // EB
    eb_count_++;
    if (cuts_.cut()) {
      reco_eb_count_++;
    }
    if (cuts_.triggerCut()) eb_trigger_++;
    if (abs(pid) % 100000 < 90000 && flavor_ == "gluino") // Not an R-baryon
      not_rbaryon_inhbeb_count_++;
    // calculate change in selection efficiency corresponding to JES uncertainty - EB
    if (cuts_.cutNMinusOne(8) && fabs(event_->jetEta[0])<1.0) {
      //if (event_->jetE[0]> jetCut_) reco_eb_count_++;
      if (event_->jetE[0]*jes_lo_ > jetCut_) selected_systlo_++;
      if (event_->jetE[0]*jes_hi_ > jetCut_) selected_systhi_++;
    }
  } else if (fabs(z)<376.0 && fabs(z) >= 300.0 && fabs(particle_eta)>=1.479 && fabs(particle_eta)<3.0) { // EE
    ee_count_++;
    if (cuts_.cut()) reco_ee_count_++;
  } else if (r>=184.0 && r<295.0 && fabs(particle_eta)<1.3 && fabs(z)<500.0) { // HB
    hb_count_++;
    if (cuts_.cut()) reco_hb_count_++;
    if (cuts_.triggerCut()) hb_trigger_++;
    if (abs(pid) % 100000 < 90000 && flavor_ == "gluino") // Not an R-baryon
      not_rbaryon_inhbeb_count_++;
    // calculate change in selection efficiency corresponding to JES uncertainty - HB
    if (cuts_.cutNMinusOne(8) && fabs(event_->jetEta[0])<1.0) {
      //if (event_->jetE[0] > jetCut_) reco_hb_count_++;
      if (event_->jetE[0]*jes_lo_ > jetCut_) selected_systlo_++;
      if (event_->jetE[0]*jes_hi_ > jetCut_) selected_systhi_++;
    }
  } else if (fabs(z)<560.0 && fabs(z)>=376.0 && fabs(particle_eta)>=1.3 && fabs(particle_eta)<3.0) { // HE
    he_count_++;
    if (cuts_.cut()) reco_he_count_++;
  } else if (r>=295.0 && r<728.5 && fabs(z)<675.0) { // MB
    mb_count_++;
    if (cuts_.cut()) reco_mb_count_++;
  } else if (r>=267.3 && r<728.5 && fabs(z)>=675.0 && fabs(z)<1080.0) { // ME-top
    me_count_++;
    if (cuts_.cut()) reco_me_count_++;
  } else if (r<267.3 && fabs(particle_eta)<3.0 && fabs(z)>=560.0 && fabs(z)<1080.0) { // ME-bottom
    me_count_++;
    if (cuts_.cut()) reco_me_count_++;
  } else if (r<728.5 && fabs(z)<1080.0) { // other regions?
    if (cuts_.cut()) reco_other_count_++;
    //dumpFile_ << r << "\t" << z << "\t" << particle_eta << std::endl;
  }

  if (r >= 728.5 || fabs(z) > 1080)
    cavern_count_++;
  else {
    detector_count_++;
    if (cuts_.cut()) selected_indetector_count_++;
  }

}

/** 
 * readHSCPEvents()
 *
 * Read in the text file listing the events selected by the HSCP analysis
 * and stores it for later lookup
 */
int MCAnalysis::readHSCPEvents() {
  if (!hscp_file_.is_open()) {
    return 1;
  }
  int bx, run, lb, id;
  double phi;
  while (hscp_file_ >> bx >> run >> lb >> id >> phi) {
    EventInfo info;
    info.run = run;
    info.lb = lb;
    info.id = id;
    
    if (doBX1_ && bx == 1) hscp_phimap_[info] = phi;
    if (!doBX1_ && bx == 0) hscp_phimap_[info] = phi;
  }
  std::cout << "Found " << hscp_phimap_.size() << " events in HSCP event file." << std::endl;
  return 0;
}

/** 
 * readStoppedEvents()
 *
 * Read in the text file listing the events selected by the stopped analysis
 * and stores it for later lookup
 */
int MCAnalysis::readStoppedEvents() {
  if (!stopped_file_.is_open()) {
    return 1;
  }
  int run, lb, id;
  while (stopped_file_.good()) {
    std::string line;
    if (!getline(stopped_file_, line)) break;
    std::stringstream line2(line);

    std::string num;
    getline(line2, num, ':');
    run = atoi(num.c_str());
    getline(line2, num, ':');
    lb = atoi(num.c_str());
    getline(line2, num);
    id = atoi(num.c_str());
    
    EventInfo info;
    info.run = run;
    info.lb = lb;
    info.id = id;

    stopped_map_[info] = 1;
  }
  std::cout << "Found " << stopped_map_.size() << " events in stopped event file." << std::endl;
  return 0;
}

/**
 * beta()
 *
 * Calculates beta for given mass, energy value
 */
double MCAnalysis::beta(double mass, double energy) {
  return sqrt(1-(mass*mass/(energy*energy)));
}

/**
 * eta()
 *
 * Calculates eta (pseudorapidity) given the cartesian coordinates
 */
// TODO: there's some weirdness where if pt = 0, PsuedoRapitidy() returns
//       a bad value. I don't know how it's calculating pt considering
//       the input is just the position...sort this out.
double MCAnalysis::eta(double x, double y, double z, double time) {
  TLorentzVector v = TLorentzVector(x, y, z, time);
  return v.PseudoRapidity();
}

/**
 * this is the main program, no need to do anything here
 */
int main(int argc, char* argv[]) {

  // sum of squares error info for histograms
  TH1D::SetDefaultSumw2();

  // create analysis
  MCAnalysis analyser(argc, argv);

  analyser.setup();

  analyser.cuts().print(std::cout);

  analyser.loop();

  return 0;

}
