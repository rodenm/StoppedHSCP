#include "StoppedHSCP/Analysis/interface/RunHistograms.h"

#include "StoppedHSCP/Analysis/interface/Constants.h"

#include "TMath.h"

#include <sstream>
#include <iostream>

RunHistograms::RunHistograms(TFile* file, Cuts* cuts, LhcFills* fills) :
  cuts_(cuts),
  fills_(fills),
  base_(),
  runs_(0),
  hbx_(0),
  horb_(0),
  hlb_(0)
{
 
  // create directory structure
  file->mkdir("runs");
  base_ = file->GetDirectory("runs");

  // these histograms will be booked on the fly
  //  book();

}


RunHistograms::~RunHistograms() {

  // print list of runs found
  sort(runs_.begin(), runs_.end());
  std::cout << std::endl;
  std::cout << "Runs : ";
  for (unsigned i=0; i<runs_.size(); ++i) {
    std::cout << runs_.at(i);
    if (i<runs_.size()-1) std::cout << ",";
  }
  std::cout << std::endl;

  // clean up memory
  std::vector<TH1D*>::iterator itr;

  for (itr=hbx_.begin(); itr!=hbx_.end(); ++itr) delete (*itr);
  for (itr=horb_.begin(); itr!=horb_.end(); ++itr) delete (*itr);
  for (itr=hlb_.begin(); itr!=hlb_.end(); ++itr) delete (*itr);
  for (itr=hlivetime_.begin(); itr!=hlivetime_.end(); ++itr) delete (*itr);

  hbx_.clear();
  horb_.clear();
  hlb_.clear();
  hlivetime_.clear();

}


// book these histograms on the fly since we don't know run numbers in advance
void RunHistograms::book(unsigned long run) {

  // check if this run has already been booked and bail if so
  std::vector<unsigned long>::const_iterator itr = find(runs_.begin(), runs_.end(), run);
  if (itr != runs_.end()) return;

  std::cout << "Creating histograms for new run #" << run << std::endl;

  // set up new run directory 
  std::stringstream runstr;
  runstr << run;
  base_->mkdir(runstr.str().c_str());

  // resize vectors if need be, without creating histograms
  if (hbx_.size() < run+1) hbx_.resize(run+1, 0);
  if (horb_.size() < run+1) horb_.resize(run+1, 0);
  if (hlb_.size() < run+1) hlb_.resize(run+1, 0);
  if (hlivetime_.size() < run+1) hlivetime_.resize(run+1, 0);

  // and book histograms
  hbx_.at(run) = new TH1D((std::string("hbx")+runstr.str()).c_str(), "BX number", 3564, 0., 3564.);
  horb_.at(run) = new TH1D((std::string("horb")+runstr.str()).c_str(), "Orbit number", 100, 0., 10000.);
  hlb_.at(run) = new TH1D((std::string("hlb")+runstr.str()).c_str(), "Lumi block", 5000, 0., 5000.);
  
  hlivetime_.at(run) = new TH1D((std::string("hlivetime")+runstr.str()).c_str(), "Livetime per LS", 5000, 0., 5000.);

  // record the fact we booked this run already
  runs_.push_back(run);
  
}


void RunHistograms::fill(StoppedHSCPEvent& event) {

  // get run number
  unsigned long run = event.run;

  // book histos
  book(run);
  
  // fill histos
  if (run < hbx_.size()) 
    hbx_.at(run)->Fill(event.bx);

  if (run < horb_.size()) 
    horb_.at(run)->Fill(event.orbit);

  if (run < hlb_.size()) 
    hlb_.at(run)->Fill(event.lb);
  else 
    std::cout << "size = " << hlb_.size() << " " << run << std::endl;

  if (run < hlivetime_.size())
    hlivetime_.at(run)->SetBinContent(event.lb, fills_->getLiveFractionFromRun(run) * TIME_PER_LS);

}


void RunHistograms::save() {

  // loop over runs
  std::vector<unsigned long>::const_iterator itr;
  for (itr=runs_.begin(); itr!=runs_.end(); ++itr) {

    // cd to directory
    std::stringstream runstr;
    runstr << (*itr);
    base_->cd(runstr.str().c_str());

    // save histograms
    hbx_.at(*itr)->Write("",TObject::kOverwrite);
    horb_.at(*itr)->Write("",TObject::kOverwrite);
    hlb_.at(*itr)->Write("",TObject::kOverwrite);

  }

}


void RunHistograms::summarise() {

  unsigned nruns = runs_.size();

  // book histograms
  TH1D* hnhlt       = new TH1D("hnhlt", "HLT counts", nruns, 0., 0.);
  TH1D* hlivetime   = new TH1D("hlivetime", "Live time", nruns, 0., 0.);
  //  TH1D* hnfin       = new TH1D("hnfin", "Final counts", nruns, 0., 0.);
  //  TH1D* hefftime    = new TH1D("hefftime", "Effective live time", nruns, 0., 0.);
  TH1D* hnlb        = new TH1D("hnlb", "N lumi blocks", nruns, 0., 0.);
  //  TH1D* hnpostjet   = new TH1D("hnpostjet", "N events after jet cuts", nruns, 0., 0.);
  //  TH1D* hnposttim   = new TH1D("hnposttim", "N events after timing cuts", nruns, 0., 0.);
  //  TH1D* hnj50nmo    = new TH1D("hnj50nmo", "Jet50 N-1 counts", nruns, 0., 0.);

  // fill them
  for (std::vector<unsigned long>::const_iterator itr=runs_.begin();
       itr!=runs_.end();
       ++itr) {

    std::stringstream runss;
    runss << (*itr);
    std::string runstr=runss.str();

    // # events passing HLT
    double nhlt = hlb_.at(*itr)->GetEntries();
    if (nhlt>0) hnhlt->Fill(runstr.c_str(), nhlt);
    else hnhlt->Fill(runstr.c_str(), 0);

    // number LS
    unsigned long nlb=0;
    for (int i=0; i<hlb_.at(*itr)->GetNbinsX(); ++i) {
      if (hlb_.at(*itr)->GetBinContent(i) > 0) ++nlb;
    }
    hnlb->Fill(runstr.c_str(), nlb);

    // live time
    hlivetime->Fill(runstr.c_str(), nlb*TIME_PER_LS);
    
  }


  // save them
  base_->cd();

  hnhlt->Write("",TObject::kOverwrite);
  hlivetime->Write("",TObject::kOverwrite);
  hnlb->Write("",TObject::kOverwrite);

}

