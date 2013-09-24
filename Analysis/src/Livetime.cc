

#include "StoppedHSCP/Analysis/interface/Livetime.h"

#include "StoppedHSCP/Ntuples/interface/Constants.h"
#include "StoppedHSCP/Ntuples/interface/LhcFills.h"

#include "TFile.h"
#include "TH1D.h"

#include <algorithm>
#include <sstream>
#include <iostream>

Livetime::Livetime(LhcFills* lhcFills) :
  lhcFills_(lhcFills),
  runLumiPairs_(0),
  runList_(0),
  fillList_(0)
{

}


Livetime::~Livetime() {

}


void Livetime::newEvent(unsigned long fill, unsigned long run, unsigned long lb) {

  if (fill<1 || fill>9999 || run<1 || run > 999999) {
    //std::cerr << "ERROR : weird fill/run/lumi numbers" << std::endl;
    //std::cout << fill << " : " << run << " : " << lb << std::endl;
    return;
  }

  std::pair<unsigned long, unsigned long> runLumiPair(run, lb);

  std::vector<std::pair<unsigned long, unsigned long> >::const_iterator itr = 
    find(runLumiPairs_.begin(), runLumiPairs_.end(), runLumiPair);

  if (itr == runLumiPairs_.end()) {
    runLumiPairs_.push_back(runLumiPair);
  }

  std::vector<unsigned long>::const_iterator itr2 = find(runList_.begin(), runList_.end(), run);
  if (itr2 == runList_.end()) {
    runList_.push_back(run);
  }


  std::vector<unsigned long>::const_iterator itr3 = find(fillList_.begin(), fillList_.end(), fill);
  if (itr3 == fillList_.end()) {
    fillList_.push_back(fill);
  }
    
}


std::vector<unsigned long> Livetime::fillList()  { 
  sort(fillList_.begin(), fillList_.end());
  return fillList_;
}


std::vector<unsigned long> Livetime::runList()  { 
  sort(runList_.begin(), runList_.end());
  return runList_;
}

std::vector<std::pair<unsigned long, unsigned long> > Livetime::runLumiPairs() {
  return runLumiPairs_;
}


double Livetime::getLivetimeByRun(unsigned long run) {
  
  double result=0.;
  
  std::vector<std::pair<unsigned long, unsigned long> >::const_iterator litr;
  for (litr=runLumiPairs_.begin(); litr!=runLumiPairs_.end(); ++litr) {
    unsigned long r = litr->first;
    unsigned long f = lhcFills_->getFillFromRun(r);
    if (r==run) result += TIME_PER_LS * lhcFills_->getLiveFraction(f);
  }

  return result;

}


double Livetime::getLivetimeByFill(unsigned long fill) {
  
  double result=0.;
  
  std::vector<std::pair<unsigned long, unsigned long> >::const_iterator litr;
  for (litr=runLumiPairs_.begin(); litr!=runLumiPairs_.end(); ++litr) {
    unsigned long r = litr->first;
    unsigned long f = lhcFills_->getFillFromRun(r);
    if (f==fill) result += TIME_PER_LS * lhcFills_->getLiveFraction(f);
  }

  return result;

}


double Livetime::getTotalLivetime() {
  
  double result=0.;
  
  std::vector<std::pair<unsigned long, unsigned long> >::const_iterator litr;
  for (litr=runLumiPairs_.begin(); litr!=runLumiPairs_.end(); ++litr) {
    unsigned long r = litr->first;
    unsigned long f = lhcFills_->getFillFromRun(r);
    result += TIME_PER_LS * lhcFills_->getLiveFraction(f);
  }

  return result;

}


void Livetime::writeHistograms(TFile* ofile) {

  // make output directory
  ofile->mkdir("runs");
  TDirectory* runsDir = ofile->GetDirectory("runs");


  // loop over runs
  std::vector<unsigned long>::const_iterator ritr;
  for (ritr=runList_.begin(); ritr!=runList_.end(); ++ritr) {

    unsigned long run = (*ritr);

    std::stringstream runstr;
    runstr << run;
    std::string hname = std::string("hlb")+runstr.str();

    // make directory & create histogram
    TDirectory* runDir = runsDir->mkdir(runstr.str().c_str());
    TH1D* hlb = new TH1D(hname.c_str(), "Lumi block", 5000, 0., 5000.);

    // loop over lumis and fill histogram
    std::vector<std::pair<unsigned long, unsigned long> >::const_iterator litr;
    for (litr=runLumiPairs_.begin(); litr!=runLumiPairs_.end(); ++litr) {
      if (litr->first == run) hlb->Fill(litr->second);
    }

    // write histogram
    runDir->cd();
    hlb->Write("",TObject::kOverwrite);

  }

}
