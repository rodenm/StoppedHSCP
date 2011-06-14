#include "StoppedHSCP/Analysis/interface/FillHistograms.h"

#include "StoppedHSCP/Ntuples/interface/Constants.h"

#include "TMath.h"

#include <sstream>
#include <iostream>

FillHistograms::FillHistograms(TFile* file, Cuts* cuts, LhcFills* fills) :
  cuts_(cuts),
  base_(),
  lhcFills_(fills),
  fills_(0),
  nEvts_(0),
  lb_(0),
  nm1_(),
  nFin_(0),
  hbx_(0),
  hnm1_(0)
{
 
  // create directory structure
  file->mkdir("fills");
  base_ = file->GetDirectory("fills");

  // these histograms will be booked on the fly
  //  book();

}


FillHistograms::~FillHistograms() {

  // print list of fills found
  sort(fills_.begin(), fills_.end());
  std::cout << std::endl;
  std::cout << "Fills : ";
  for (unsigned i=0; i<fills_.size(); ++i) {
    std::cout << fills_.at(i);
    if (i<fills_.size()-1) std::cout << ",";
  }
  std::cout << std::endl;

  // clean up memory
  std::vector<TH1D*>::iterator itr;

  for (itr=hbx_.begin(); itr!=hbx_.end(); ++itr) delete (*itr);
  for (itr=hnm1_.begin(); itr!=hnm1_.end(); ++itr) delete (*itr);

  hbx_.clear();
  hnm1_.clear();

}



void FillHistograms::book(unsigned long fill) {

  // check if this run has already been booked and bail if so
  std::vector<unsigned long>::const_iterator itr = find(fills_.begin(), fills_.end(), fill);
  if (itr != fills_.end()) return;

  std::cout << "Creating histograms for new fill #" << fill << std::endl;

  // set up new run directory 
  std::stringstream fillstr;
  fillstr << fill;
  base_->mkdir(fillstr.str().c_str());

  // resize vectors if need be, without creating histograms
  if (nEvts_.size() < fill+1) nEvts_.resize(fill+1, 0);
  if (nLB_.size() < fill+1) nLB_.resize(fill+1, 0);
  if (nm1_.size() < fill+1) nm1_.resize(fill+1, std::vector<unsigned long>(cuts_->nCuts()));
  if (nFin_.size() < fill+1) nFin_.resize(fill+1, 0);

  if (hbx_.size() < fill+1) hbx_.resize(fill+1, 0);
  if (hnm1_.size() < fill+1) hnm1_.resize(fill+1, 0);

  // and book histograms
  hbx_.at(fill) = new TH1D((std::string("hbx")+fillstr.str()).c_str(), "BX number", 3564, 0., 3564.);
  //hnm1_.at(fill) = new TH1D((std::string("hnm1")+fillstr.str()).c_str(), "N-1 counts", 20, 0., 20.);

  // record the fact we booked this fill already
  fills_.push_back(fill);

}


void FillHistograms::fill(StoppedHSCPEvent& event) {

  // get fill number
  unsigned long fill = event.fill;

  // book histos
  book(fill);
  
  // count stuff
  nEvts_.at(fill) += 1;
  
  std::pair<unsigned long, unsigned long> lb(event.run, event.lb);
  if (find(lb_.begin(), lb_.end(), lb) == lb_.end()) {
    lb_.push_back(lb);
    nLB_.at(fill) += 1;
  }
  
  // N-1 histo
  for (unsigned cut=0; cut<cuts_->nCuts(); ++cut) {
    if (cuts_->cutNMinusOne(cut)) nm1_.at(fill).at(cut) += 1;
  }

  if (cuts_->cut()) nFin_.at(fill) += 1;
  
  // fill histos
  hbx_.at(fill)->Fill(event.bx);

}


void FillHistograms::save() {

  // loop over fills
  std::vector<unsigned long>::const_iterator itr;
  for (itr=fills_.begin(); itr!=fills_.end(); ++itr) {

    // cd to directory
    std::stringstream fillstr;
    fillstr << (*itr);
    base_->cd(fillstr.str().c_str());

    // save histograms
    hbx_.at(*itr)->Write("",TObject::kOverwrite);
    //    hnm1_.at(*itr)->Write("",TObject::kOverwrite);

  }

}


void FillHistograms::summarise() {

  unsigned nFills = fills_.size();

  // book histograms
  TH1D* hnevt       = new TH1D("hfillnevt", "HLT counts", nFills, 0., 0.);
  TH1D* hlivetime   = new TH1D("hfilltime", "Live time", nFills, 0., 0.);
  TH1D* hnfin       = new TH1D("hfillnfin", "Final counts", nFills, 0., 0.);

  // N-1 histos
  std::vector<TH1D*> hnm1counts;
  std::vector<TH1D*> hnm1rates;
  std::string nbasec("hfillnm1count_");
  std::string nbaser("hfillnm1rate_");
  std::string lbase("N-1 rate : ");
  std::stringstream str;
  for (unsigned i=0; i<cuts_->nCuts(); ++i) {
    str << i;
    std::string namec=nbasec+str.str();
    std::string namer=nbaser+str.str();
    std::string label=lbase+str.str();
    hnm1counts.push_back(new TH1D(namec.c_str(), label.c_str(), nFills, 0., 0.));
    hnm1rates.push_back(new TH1D(namer.c_str(), label.c_str(), nFills, 0., 0.));
    str.str("");
  }

  // fill them
  std::vector<unsigned long>::const_iterator itr;
  unsigned bin=1;

  sort(fills_.begin(), fills_.end());

  for (itr=fills_.begin();
       itr!=fills_.end();
       ++itr, ++bin) {

    unsigned long fill = *itr;

    std::stringstream fillss;
    fillss << (*itr);
    std::string fillstr=fillss.str();

    // # events passing HLT
    hnevt->Fill(fillstr.c_str(), nEvts_.at(fill));
    hnevt->SetBinError(bin, sqrt(nEvts_.at(fill)));

    // live time
    double livetime = nLB_.at(fill) * TIME_PER_LS * lhcFills_->getLiveFraction(fill);
    hlivetime->Fill(fillstr.c_str(), livetime);
    
    for (unsigned cut=0; cut<cuts_->nCuts(); ++cut) {
      unsigned long count = nm1_.at(fill).at(cut);
      hnm1counts.at(cut)->Fill(fillstr.c_str(), count);
      if (count > 0) hnm1counts.at(cut)->SetBinError(bin, sqrt(count));
      else hnm1counts.at(cut)->SetBinError(bin, 1.);
      hnm1rates.at(cut)->Fill(fillstr.c_str(), count/livetime);
      if (count > 0) hnm1rates.at(cut)->SetBinError(bin, sqrt(count)/livetime);
      else hnm1rates.at(cut)->SetBinError(bin, 1/livetime);
    }

    // final counts
    hnfin->Fill(fillstr.c_str(), nFin_.at(fill));
    hnfin->SetBinError(bin, sqrt(nFin_.at(fill)));

  }


  // save them
  base_->cd();

  hnevt->Write("",TObject::kOverwrite);
  hlivetime->Write("",TObject::kOverwrite);
  hnfin->Write("",TObject::kOverwrite);

  for (unsigned i=0; i<cuts_->nCuts(); ++i) {
    hnm1counts.at(i)->Write("",TObject::kOverwrite);
    hnm1rates.at(i)->Write("",TObject::kOverwrite);
  }

}
