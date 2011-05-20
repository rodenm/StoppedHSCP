#include "StoppedHSCP/Analysis/interface/BasicAnalyser.h"

#include <iostream>
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>

BasicAnalyser::BasicAnalyser(const std::string& ifile, const bool isMC) :
  isMC_(isMC),
  file_(ifile.c_str(), "READ"),
  tree_(0),
  event_(0),
  nEvents_(0),
  iEvent_(0),
  cuts_(0, isMC, 0, 0),
  fills_()
{
  
}

BasicAnalyser::~BasicAnalyser() {

}


void BasicAnalyser::setup() {

  // TTree
  tree_ = (TTree*) file_.Get("stoppedHSCPTree/StoppedHSCPTree");
  tree_->SetBranchAddress("events",&event_);

  nEvents_ = tree_->GetEntriesFast();
  iEvent_ = 0;

  std::cout << "Input file contains " << nEvents_ << " events" << std::endl;

  cuts_.setEvent(event_);
  cuts_.setFills(&fills_);
  //  cuts_.setMaskedBXs(fills_.getMaskFromRun(event_->run));

}


void BasicAnalyser::reset() {
  iEvent_ = 0;
}


void BasicAnalyser::nextEvent() {

  //. make note of current run
  unsigned currRun = event_->run;

  if (iEvent_ < nEvents_-1) {
    int nb=0;
    nb = tree_->GetEntry(iEvent_);
    iEvent_++;
    if (nb == 0) {  std::cout << "TTree GetEntry() failed" << std::endl; }
  }

  // update stuff if run changed
//   if (event_->run != currRun) {
//     std::cout << "New run : " << event_->run << std::endl;
//     cuts_.setMaskedBXs(fills_.getMaskFromRun(event_->run));
//   }

}


void BasicAnalyser::printEvent() {
  tree_->Show();
}


void BasicAnalyser::printCutValues(ostream& o) {

  o << "Stopped HSCP Event" << std::endl;
  o << "  run            = " << event_->run << std::endl;
  o << "  lb             = " << event_->lb << std::endl;
  o << "  id             = " << event_->id << std::endl;
  o << "  bx             = " << event_->bx << std::endl;
  o << "  orbit          = " << event_->orbit << std::endl;
  o << "  mu_N           = " << event_->mu_N << std::endl;
  std::string halo("None");
  if (event_->beamHalo_CSCLoose) halo = "CSCLoose";
  if (event_->beamHalo_CSCTight) halo = "CSCTight";
  o << "  beamHalo       = " << halo << std::endl;
  o << "  HCAL noise     = " << event_->noiseFilterResult << std::endl;
  o << "  nTowerSameiPhi = " << event_->nTowerSameiPhi << std::endl;
  o << "  jetE[0]        = " << event_->jetE[0] << std::endl;
  o << "  jetEta[0]      = " << event_->jetEta[0] << std::endl;
  o << "  jetN60[0]      = " << event_->jetN60[0] << std::endl;
  o << "  jetN90[0]      = " << event_->jetN90[0] << std::endl;
  o << "  top5DigiR1     = " << event_->top5DigiR1 << std::endl;
  o << "  top5DigiR2     = " << event_->top5DigiR2 << std::endl;
  o << "  top5DigiRPeak  = " << event_->top5DigiRPeak << std::endl;
  o << "  top5DigiROuter = " << event_->top5DigiROuter << std::endl;
  o << "  jetEMF[0]      = " << (event_->jetEEm[0] / event_->jetEHad[0]) << std::endl;
  o << "  time sample    = ";
  for (unsigned i=0; i<10; ++i) o << event_->top5DigiTimeSamples.at(i) << " ";
  o << std::endl;
  o << std::endl;
}


