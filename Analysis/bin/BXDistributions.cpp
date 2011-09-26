#ifndef BXDistributions_h
#define BXDistributions_h

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

class BXDistributions : public BasicAnalyser {

public:
  BXDistributions(int argc, char* argv[]) :
    BasicAnalyser(argc, argv)
  {
    ofilename_ = std::string("BXDistributions.root");  /// SET YOUR OUTPUT FILENAME HERE
  }
  
  ~BXDistributions() { 

    std::vector<TH1D*>::iterator itr;
    for (itr=hnormrelbx_.begin(); itr!=hnormrelbx_.end(); ++itr) delete (*itr);
    for (itr=hrelbx_.begin(); itr!=hrelbx_.end(); ++itr) delete (*itr);
    for (itr=hrelbxvtx_.begin(); itr!=hrelbxvtx_.end(); ++itr) delete (*itr);
    for (itr=hrelbxhalo_.begin(); itr!=hrelbxhalo_.end(); ++itr) delete (*itr);
    for (itr=hrelbxbg_.begin(); itr!=hrelbxbg_.end(); ++itr) delete (*itr);
    for (itr=hrelbxcos_.begin(); itr!=hrelbxcos_.end(); ++itr) delete (*itr);
    for (itr=hrelbxnoise_.begin(); itr!=hrelbxnoise_.end(); ++itr) delete (*itr);
    for (itr=hrelbxnoid_.begin(); itr!=hrelbxnoid_.end(); ++itr) delete (*itr);
    
    hnormrelbx_.clear();
    hrelbx_.clear();
    hrelbxvtx_.clear();
    hrelbxhalo_.clear();
    hrelbxbg_.clear();
    hrelbxcos_.clear();
    hrelbxnoise_.clear();
    hrelbxnoid_.clear();
    
  };
  
  virtual void loop();
  
private:

  // YOUR CODE HERE
  std::vector<unsigned long> fillList_;

  std::vector<TH1D*> hnormrelbx_;
  std::vector<TH1D*> hrelbx_;
  std::vector<TH1D*> hrelbxvtx_;
  std::vector<TH1D*> hrelbxhalo_;
  std::vector<TH1D*> hrelbxbg_;
  std::vector<TH1D*> hrelbxcos_;
  std::vector<TH1D*> hrelbxnoise_;
  std::vector<TH1D*> hrelbxnoid_;

};

#endif


// this is the event loop
void BXDistributions::loop() {

  reset();
 
  nextEvent();

  for (ULong64_t i=0; i<maxEvents_; ++i, nextEvent()) {

    // occasional print out
    if (i%100000==0) {
      std::cout << "Processing " << i << "th event of " <<maxEvents_<< std::endl;
    }

    // YOUR CODE HERE
     
    // create histograms for each new fill
    unsigned long fill = event_->fill;
    std::vector<unsigned long>::const_iterator itr = find(fillList_.begin(), fillList_.end(), fill);

    if (itr == fillList_.end()) {
    
      std::cout << "Creating histograms for new fill #" << fill << std::endl;
      
      // set up new directory 
      std::stringstream fillstr;
      fillstr << fill;
      ofile_->mkdir(fillstr.str().c_str());
      
      // make space for new histograms if needed
      if (hnormrelbx_.size() < fill+1) hnormrelbx_.resize(fill+1, 0);
      if (hrelbx_.size() < fill+1) hrelbx_.resize(fill+1, 0);
      if (hrelbxvtx_.size() < fill+1) hrelbxvtx_.resize(fill+1, 0);
      if (hrelbxhalo_.size() < fill+1) hrelbxhalo_.resize(fill+1, 0);
      if (hrelbxbg_.size() < fill+1) hrelbxbg_.resize(fill+1, 0);
      if (hrelbxcos_.size() < fill+1) hrelbxcos_.resize(fill+1, 0);
      if (hrelbxnoise_.size() < fill+1) hrelbxnoise_.resize(fill+1, 0);
      if (hrelbxnoid_.size() < fill+1) hrelbxnoid_.resize(fill+1, 0);
      
      // and book histograms
      hnormrelbx_.at(fill) = new TH1D((std::string("hnormrelbx")+fillstr.str()).c_str(), "BX wrt bunch", 2000, -1000., 1000.);
      hrelbx_.at(fill) = new TH1D((std::string("hrelbx")+fillstr.str()).c_str(), "BX wrt bunch", 2000, -1000., 1000.);
      hrelbxhalo_.at(fill) = new TH1D((std::string("hrelbxhalo")+fillstr.str()).c_str(), "RelBX - halo", 2000, -1000., 1000.);
      hrelbxvtx_.at(fill) = new TH1D((std::string("hrelbxvtx")+fillstr.str()).c_str(), "Rel BX - collisions", 2000, -1000., 1000.);
      hrelbxbg_.at(fill) = new TH1D((std::string("hrelbxbg")+fillstr.str()).c_str(), "Rel BX - beam-gas", 2000, -1000., 1000.);
      hrelbxcos_.at(fill) = new TH1D((std::string("hrelbxcos")+fillstr.str()).c_str(), "Rel BX - cosmics", 2000, -1000., 1000.);
      hrelbxnoise_.at(fill) = new TH1D((std::string("hrelbxnoise")+fillstr.str()).c_str(), "Rel BX - noise", 2000, -1000., 1000.);
      hrelbxnoid_.at(fill) = new TH1D((std::string("hrelbxnoid")+fillstr.str()).c_str(), "Rel BX - no ID", 2000, -1000., 1000.);
      
      // fill normalisation histogram
      for (unsigned i=0; i<3564; ++i) {
	hnormrelbx_.at(fill)->Fill( lhcFills_.getBxWrtBunch(fill, i) );
      }
      
      // record the fact we booked this fill already
      fillList_.push_back(fill);

    }

    // fill histograms
    if (event_->jet_N>0 && event_->jetE[0]>30. && event_->jetEta[0]<1.3) {
      hrelbx_.at(fill)->Fill(event_->bxWrtBunch);
      if (event_->vtx_N>0) hrelbxvtx_.at(fill)->Fill(event_->bxWrtBunch);
      if (event_->vtx_N==0 && event_->track_N>1) hrelbxbg_.at(fill)->Fill(event_->bxWrtBunch);
      if (event_->vtx_N==0 && event_->track_N<2 && event_->beamHalo_CSCLoose) hrelbxhalo_.at(fill)->Fill(event_->bxWrtBunch);
      if (event_->vtx_N==0 && event_->track_N<2 && !event_->beamHalo_CSCLoose && event_->mu_N>0) hrelbxcos_.at(fill)->Fill(event_->bxWrtBunch);
      if (event_->vtx_N==0 && event_->track_N<2 && !event_->beamHalo_CSCLoose && event_->mu_N==0 && !event_->noiseFilterResult) hrelbxnoise_.at(fill)->Fill(event_->bxWrtBunch);
      
      if (event_->vtx_N==0 && event_->track_N<2 && !event_->beamHalo_CSCLoose && event_->mu_N==0 && event_->noiseFilterResult) hrelbxnoid_.at(fill)->Fill(event_->bxWrtBunch);
    } 

  }

  /// save histograms
  std::vector<unsigned long>::const_iterator itr;
  for (itr=fillList_.begin(); itr!=fillList_.end(); ++itr) {

    // cd to directory
    std::stringstream fillstr;
    fillstr << (*itr);
    ofile_->cd(fillstr.str().c_str());

    hnormrelbx_.at(*itr)->Write("",TObject::kOverwrite);
    hrelbx_.at(*itr)->Write("",TObject::kOverwrite);
    hrelbxvtx_.at(*itr)->Write("",TObject::kOverwrite);
    hrelbxhalo_.at(*itr)->Write("",TObject::kOverwrite);
    hrelbxbg_.at(*itr)->Write("",TObject::kOverwrite);
    hrelbxcos_.at(*itr)->Write("",TObject::kOverwrite);
    hrelbxnoise_.at(*itr)->Write("",TObject::kOverwrite);
    hrelbxnoid_.at(*itr)->Write("",TObject::kOverwrite);

  }

}


// this handles program control, no need to do anything here
int main(int argc, char* argv[]) {

  // sum of squares error info for histograms
  TH1D::SetDefaultSumw2();

  // create analysis
  BXDistributions analyser(argc, argv);

  analyser.setup();

  analyser.cuts().print(std::cout);

  analyser.loop();

  return 0;

}
