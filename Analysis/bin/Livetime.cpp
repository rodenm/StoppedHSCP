#ifndef Livetime_h
#define Livetime_h

#include "StoppedHSCP/Analysis/interface/BasicAnalyser.h"

#include "TFile.h"
#include "TChain.h"
#include "TH1D.h"

#include <string>
#include <vector>
#include <fstream>
#include <sys/stat.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <boost/program_options.hpp>

namespace po = boost::program_options;

using namespace std;

class Livetime : public BasicAnalyser {

public:
  Livetime(int argc, char* argv[]) :
    BasicAnalyser (argc, argv),
    ofilename_("Livetime.root")
  { }
  
  ~Livetime() { 

  };
  
  virtual void loop(ULong64_t maxEvents);
  
private:

  // YOUR CODE HERE
  //  std::vector<unsigned long> runList_;
  std::vector<unsigned long> fillList_;

  std::vector<unsigned long> nEvts_;
  std::vector<unsigned long> nLB_;
  std::vector<unsigned long> nFin_;

};

#endif


// this is the event loop
void Livetime::loop(ULong64_t maxEvents) {

  if (maxEvents!=0) {
    std::cout << "Going to run over " << maxEvents << " events" << std::endl;
  }
  else {
    std::cout << "Going to run over all events" << std::endl;
  }

  reset();
 
  if (maxEvents==0) maxEvents=nEvents();

  nextEvent();

  // set up directories before the loop
  //  ofile_->mkdir("runs");
  //  ofile_->mkdir("fills");

  for (ULong64_t i=0; i<maxEvents; ++i, nextEvent()) {

    // occasional print out
    if (i%100000==0) {
      std::cout << "Processing " << i << "th event of " <<maxEvents<< std::endl;
    }

    // YOUR CODE HERE
     
    // create histograms for each new run
//     unsigned long run = event_->run;
//     std::vector<unsigned long>::const_iterator itr1 = find(runList_.begin(), runList_.end(), run);
//     if (itr1 == runList_.end()) {
//       std::cout << "Creating histograms for new run #" << fill << std::endl;
//       std::stringstream runstr;
//       runstr << run;

//     }

    // create histograms for each new fill
    unsigned long fill = event_->fill;
    std::vector<unsigned long>::const_iterator itr2 = find(fillList_.begin(), fillList_.end(), fill);
    if (itr == fillList_.end()) {    
      std::cout << "Creating histograms for new fill #" << fill << std::endl;
      std::stringstream fillstr;
      fillstr << fill;

      if (nEvts_.size() < fill+1) nEvts_.resize(fill+1, 0);
      if (nLB_.size() < fill+1) nLB_.resize(fill+1, 0);
      if (nFin_.size() < fill+1) nFin_.resize(fill+1, 0);

    }

    // count stuff
    nEvts_.at(fill) += 1;
    
    std::pair<unsigned long, unsigned long> lb(event.run, event.lb);
    if (find(lb_.begin(), lb_.end(), lb) == lb_.end()) {
      lb_.push_back(lb);
      nLB_.at(fill) += 1;
    }
    
    if (cuts_->cut()) nFin_.at(fill) += 1;

  }


  // book summary histograms
  unsigned nFills = fillList_.size();
  TH1D* hnevt       = new TH1D("hfillnevt", "HLT counts", nFills, 0., 0.);
  TH1D* hlivetime   = new TH1D("hfilltime", "Live time", nFills, 0., 0.);
  TH1D* hnfin       = new TH1D("hfillnfin", "Final counts", nFills, 0., 0.);

  sort(fillList_.begin(), fillList_.end());

  // fill summary histograms
  std::vector<unsigned long>::const_iterator itr;
  unsigned bin=1;
  for (itr=fillList_.begin();
       itr!=fillList_.end();
       ++itr, ++bin) {

    unsigned long fill = *itr;

    std::stringstream fillss;
    fillss << (*itr);
    std::string fillstr=fillss.str();

    // counts passing HLT
    hnevt->Fill(fillstr.c_str(), nEvts_.at(fill));
    hnevt->SetBinError(bin, sqrt(nEvts_.at(fill)));

    // live time
    double livetime = nLB_.at(fill) * TIME_PER_LS * lhcFills_->getLiveFraction(fill);
    hlivetime->Fill(fillstr.c_str(), livetime);
    

    std::cout << fill << ":   " << lhcFills_->getLiveFraction(fill) << std::endl;

    // final counts
    unsigned long nfin = nFin_.at(fill);
    hnfin->Fill(fillstr.c_str(), nfin);
    if (nfin>0) hnfin->SetBinError(bin, sqrt(nfin));
    else hnfin->SetBinError(bin, 1.);

  }




  // save summary histograms
  base_->cd();

  hnevt->Write("",TObject::kOverwrite);
  hlivetime->Write("",TObject::kOverwrite);
  hnfin->Write("",TObject::kOverwrite);

}


// this handles program control, no need to do anything here
int main(int argc, char* argv[]) {


  // SET YOUR OUTPUT FILENAME HERE
  std::string ofile("Livetime.root");

  // now run the program


  // sum of squares error info for histograms
  TH1D::SetDefaultSumw2();

  // create analysis
  Livetime analyser(filenames, outdir+std::string("/")+ofile, isMC);

  analyser.setup();

  analyser.cuts().print(std::cout);

  // make histograms for all events
  analyser.loop(nEvents);

  return 0;

}
