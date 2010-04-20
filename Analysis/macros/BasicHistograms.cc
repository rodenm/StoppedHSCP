
// some methods to make basic distributions

#include "StoppedHSCPTree.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TMath.h"
#include <vector>

#include <string>

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
TH1D* hntowsameiphi_;
TH1D* hjete_;
TH1D* hjeteta_;
TH1D* hjetphi_;
TH1D* hjeteem_;
TH1D* hjetehad_;
TH1D* hjetn60_;
TH1D* hjetn90_;
TH1D* hjetn90hits_;
TH1D* hjetfhpd_;
TH1D* hnmu_;
TH1D* hr1_;
TH1D* hr2_;
TH1D* hrpk_;
TH1D* hrout_;
TH2D* hr1r2_;
TH2D* hpkout_;


void bookHistos() {
  
  // time
  hbx_ = new TH1D("hbx", "BX number", 3564, 0., 3564.);
  horb_ = new TH1D("horb", "Orbit number", 100, 0., 10000.);
  hlb_ = new TH1D("hlb", "Lumi block", 2000, 0., 2000.);
  htime_ = new TH1D("htime", "Event time", 100, 0., 1.E8);
  
  // L1
  hl1et_ = new TH1D("hl1et",  "Leading L1 jet E_{t}", 100, 0., 200.);
  hl1eta_ = new TH1D("hl1eta", "Leading L1 jet #eta", 70, -3.5, 3.5);
  hl1phi_ = new TH1D("hl1phi", "Leading L1 jet #phi", 60, -1 * TMath::Pi(),  TMath::Pi());

  // HLT
  hhlte_ = new TH1D("hhlte",  "Leading HLT jet E", 100, 0., 200.);
  hhlteta_ = new TH1D("hhlteta", "Leading HLT jet #eta", 70, -3.5, 3.5);
  hhltphi_ = new TH1D("hhltphi", "Leading HLT jet #phi", 60, -1 * TMath::Pi(),  TMath::Pi());
	
  // global calo
  hntowsameiphi_ = new TH1D("hntowsamephi", "N leading towers at same iphi", 20, -0.5, 19.5);

  // jets
  hjete_ = new TH1D("hjete", "Leading jet energy", 50, 0., 200.);
  hjeteta_ = new TH1D("hjeteta", "Leading jet #eta", 70, -3.5, 3.5);
  hjetphi_ = new TH1D("hjetphi", "Leading jet #phi", 60, -1 * TMath::Pi(),  TMath::Pi());
  hjeteem_ = new TH1D("hjeteem", "Leading jet ECAL energy", 100, 0., 200.);
  hjetehad_ = new TH1D("hjetehad", "Leading jet HCAL energy", 100, 0., 200.);
  hjetn60_ = new TH1D("hjetn60", "Leading jet N60", 50, 0., 50.);
  hjetn90_ = new TH1D("hjetn90", "Leading jet N90", 50, 0., 50.);

  // muons
  hnmu_ = new TH1D("hnmu", "N muons", 4, -0.5, 3.5);

  // pulse shape
  hr1_ = new TH1D("hr1", "R_{1}", 50, 0., 1.);
  hr2_ = new TH1D("hr2", "R_{2}", 50, 0., 1.);
  hrpk_ = new TH1D("hrpk", "R_{peak}", 50, 0., 1.);
  hrout_ = new TH1D("hrout", "R_{outer}", 30, 0., 1.);    
  hr1r2_ = new TH2D("hr1r2", "R_{1} vs R_{2}", 50, 0., 1., 50, 0., 1.);
  hpkout_ = new TH2D("hpkout", "R_{peak} vs R_{outer}", 50, 0., 1., 50, 0., 1.);

}


// fill all histograms
void fillHistos(StoppedHSCPTree& tree) {

  hbx_->Fill(tree.bx);
  horb_->Fill(tree.orbit);
  hlb_->Fill(tree.lb);
  htime_->Fill(tree.time);
  hl1et_->Fill(tree.l1JetE.at(0));
//   hl1eta_->Fill();
//   hl1phi_->Fill();
//   hl1type_->Fill();
//   hhltet_->Fill();
//   hhlteta_->Fill();
//   hhltphi_->Fill();
//   hntowsameiphi_->Fill();
//   hjete_->Fill();
//   hjeteta_->Fill();
//   hjetphi_->Fill();
//   hjeteem_->Fill();
//   hjetehad_->Fill();
//   hjetn60_->Fill();
//   hjetn90_->Fill();
//   hjetn90hits_->Fill();
//   hjetfhpd_->Fill();
//   hnmu_->Fill();
//   hr1_->Fill();
//   hr2_->Fill();
//   hrpk_->Fill();
//   hrout_->Fill();
//   hr1r2_->Fill();
//   hpkout_->Fill();

}

void writeHistos() {

  hbx_->Write();
  horb_->Write();
  hlb_->Write();
  htime_->Write();
  hl1et_->Write();
  hl1eta_->Write();
  hl1phi_->Write();
  hl1type_->Write();
  hhlte_->Write();
  hhlteta_->Write();
  hhltphi_->Write();
  hntowsameiphi_->Write();
  hjete_->Write();
  hjeteta_->Write();
  hjetphi_->Write();
  hjeteem_->Write();
  hjetehad_->Write();
  hjetn60_->Write();
  hjetn90_->Write();
  hjetn90hits_->Write();
  hjetfhpd_->Write();
  hnmu_->Write();
  hr1_->Write();
  hr2_->Write();
  hrpk_->Write();
  hrout_->Write();
  hr1r2_->Write();
  hpkout_->Write();

}



void plotHistos() {




}




void run(std::string filename, std::vector<unsigned> runs) {
  
  // open file and get tree
  TFile file(filename.c_str());
  TTree* tt = (TTree*) file.Get("stoppedHSCPTree/StoppedHSCPTree");

  StoppedHSCPTree tree(tt);

  // set up loop
  if (tree.fChain == 0) return;
  Long64_t nentries = tree.fChain->GetEntriesFast();
  Long64_t nbytes = 0, nb = 0;

  // run loop
  for (Long64_t jentry=0; jentry<nentries;jentry++) {

    // this bit is ridiculous, isn't it
    Long64_t ientry = tree.LoadTree(jentry);
    if (ientry < 0) break;
    nb = tree.fChain->GetEntry(jentry);
    nbytes += nb;

    // check if event is in run list
    if (runs.size()==0 ||
	std::count(runs.begin(), runs.end(), tree.run) > 0) {

      // if so fill histograms
      fillHistos(tree);

    }

  }

  writeHistos();

}


// // plot histograms
// def basicPlots(file, dir, scale, ofile):
    
//     // reminder of method arguments
//     // histPlot(hist, file, norm=False, log=False, title="histogram", xtitle="", ytitle="", opt="HIST")
//     // hist2DPlot(hist, file, norm=False, log=False, title="histogram", xtitle="", ytitle="", ztitle="", opt="")

//     // L1 trigger
//     histPlot(dir+"/hl1et", file, ofile, scale, True, "", "E_{L1} (GeV)", "")
//     histPlot(dir+"/hl1eta", file, ofile, scale, True, "", "//eta", "")
//     histPlot(dir+"/hl1phi", file, ofile, scale, True, "", "//phi", "")
    
//     // HLT
//     histPlot(dir+"/hhlte", file, ofile, scale, True, "", "E_{HLT} (GeV)", "")
//     histPlot(dir+"/hhlteta", file, ofile, scale, True, "", "//eta", "")
//     histPlot(dir+"/hhltphi", file, ofile, scale, True, "", "#phi", "")

//     // misc
//     histPlot(dir+"/hntowsamephi", file, ofile, scale, True, "", "N_{towers}", "")

//     // jet variables
//     histPlot(dir+"/hjete2", file, ofile, scale, True, "", "E (GeV)", "E")
//     histPlot(dir+"/hjeteta", file, ofile, scale, True, "", "#eta", "E")
//     histPlot(dir+"/hjetphi", file, ofile, scale, True, "", "#phi", "E")
//     histPlot(dir+"/hjetem", file, ofile, scale, True, "", "E_{ECAL}", "E")
//     histPlot(dir+"/hjethad", file, ofile, scale, True, "", "E_{HCAL}", "E")
//     histPlot(dir+"/hjetn60", file, ofile, scale, True, "", "n60", "E")
//     histPlot(dir+"/hjetn90", file, ofile, scale, True, "", "n90", "E")

// // muon variables
//     histPlot(dir+"/hnmu", file, ofile, scale, True, "", "N_{#mu}", "")

//     // pulse shape variables
//     histPlot(dir+"/hr1", file, ofile, scale, False, "", "R1", "")
//     histPlot(dir+"/hr2", file, ofile, scale, False, "", "R2", "")
//     histPlot(dir+"/hpk", file, ofile, scale, False, "", "R_{peak}", "")
//     histPlot(dir+"/hout", file, ofile, scale, False, "", "R_{outer}", "")

//     // 2D timing plots
//     hist2DPlot(dir+"/hr1r2", file, ofile, scale, True, "", "R_{2}", "R_{1}", "", "CONT")
//     hist2DPlot(dir+"/hpkout", file, ofile, scale, True, "", "R_{out}", "R_{peak}", "", "CONT")        


// def timePlots(file, ofilename):

//     dir = "NoCuts"

//     histPlot(dir+"/hbx", file, ofilename, 0., True, "", "BX", "N events")
//     histPlot(dir+"/hlb", file, ofilename, 0., True, "", "LS", "N events")
//     histPlot(dir+"/hlbdist", file, ofilename, 0., True, "", "Rate", "N LS")



