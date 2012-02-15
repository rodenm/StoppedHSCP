#include "StoppedHSCP/Analysis/interface/RunHistograms.h"

#include "StoppedHSCP/Ntuples/interface/Constants.h"
#include "StoppedHSCP/Analysis/interface/BadRuns.h"

#include "TMath.h"

#include <sstream>
#include <iostream>

RunHistograms::RunHistograms(TFile* file, Cuts* cuts, LhcFills* fills) :
  cuts_(cuts),
  fills_(fills),
  base_(),
  runs_(0),
  nEvts_(0),
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

  for (itr=hlb_.begin(); itr!=hlb_.end(); ++itr) delete (*itr);

  hlb_.clear();

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
  if (nEvts_.size() < run+1) nEvts_.resize(run+1, 0);

  if (hlb_.size() < run+1) hlb_.resize(run+1, 0);


  // and book histograms
  hlb_.at(run) = new TH1D((std::string("hlb")+runstr.str()).c_str(), "Lumi block", 5000, 0., 5000.);

  // record the fact we booked this run already
  runs_.push_back(run);
  
}


void RunHistograms::fill(StoppedHSCPEvent& event) {

  // get run number
  unsigned long run = event.run;

  // book histos
  book(run);

  // count stuff
  nEvts_.at(run) += 1;
  
  // fill histos
  if (run < hlb_.size()) 
    hlb_.at(run)->Fill(event.lb);
  else 
    std::cout << "size = " << hlb_.size() << " " << run << std::endl;

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
    hlb_.at(*itr)->Write("",TObject::kOverwrite);

  }

}


void RunHistograms::summarise() {

  std::sort(runs_.begin(), runs_.end());

  unsigned nruns = runs_.size();

  // book histograms
  TH1D* hnhlt       = new TH1D("hrunevt", "HLT counts", nruns, 0., 0.);
  TH1D* hlivetime   = new TH1D("hruntime", "Live time", nruns, 0., 0.);
  TH1D* hnlb        = new TH1D("hrunlb", "N lumi blocks", nruns, 0., 0.);

  // fill them
  for (std::vector<unsigned long>::const_iterator itr=runs_.begin();
       itr!=runs_.end();
       ++itr) {
    
    unsigned long run = *itr;
    if (isBadRun(run)) continue; // don't fill info for bad runs

    std::stringstream runss;
    runss << (*itr);
    std::string runstr=runss.str();

    // # events passing HLT
    hnhlt->Fill(runstr.c_str(), nEvts_.at(run));

    // number LS
    unsigned long nlb=0;
    for (int i=0; i<hlb_.at(*itr)->GetNbinsX(); ++i) {
      if (hlb_.at(*itr)->GetBinContent(i+1) > 0) ++nlb;
    }
    hnlb->Fill(runstr.c_str(), nlb);

    // live time
    hlivetime->Fill(runstr.c_str(), nlb*TIME_PER_LS*fills_->getLiveFractionFromRun(*itr));
    
  }


  // save them
  base_->cd();

  hnhlt->Write("",TObject::kOverwrite);
  hlivetime->Write("",TObject::kOverwrite);
  hnlb->Write("",TObject::kOverwrite);

}

