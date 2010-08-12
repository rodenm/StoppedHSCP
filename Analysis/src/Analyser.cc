#include "StoppedHSCP/Analysis/interface/Analyser.h"

#include <iostream>
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>

Analyser::Analyser(std::string ifile, std::string outdir, std::vector<unsigned> runs, bool isMC) :
  isMC_(isMC),
  file_(ifile.c_str()),
  tree_(0),
  event_(0),
  nEvents_(0),
  iEvent_(0),
  cuts_(0, isMC),
  histogrammer_(outdir+std::string("/histograms.root"), runs, &cuts_),
  watchedEvents_(0),
  eventFile_(),
  dumpFile_()
{
  
  // log files
  std::string fd(outdir);
  fd+="/fullDump.log";
  dumpFile_.open(fd.c_str());
  dumpFile_ << "Cut variables for events passing all cuts" << std::endl << std::endl;
  
  std::string ei(outdir);
  ei+="/eventList.log";
  eventFile_.open(ei.c_str());

  std::cout << "Stopped Gluino Analysis" << std::endl;
  std::cout << "Ntuple file       : " << ifile << std::endl;
  std::cout << "Output directory  : " << outdir << std::endl;
  std::cout << "Run list          : ";
  for (unsigned i=0; i<runs.size(); ++i) {
    std::cout << runs.at(i) << ",";
  }
  std::cout << std::endl;

}

Analyser::~Analyser() {

  histogrammer_.save();

  dumpFile_.close();
  eventFile_.close();

}


void Analyser::setup() {

  // TTree
  tree_ = (TTree*) file_.Get("stoppedHSCPTree/StoppedHSCPTree");
  tree_->SetBranchAddress("events",&event_);

  nEvents_ = tree_->GetEntriesFast();
  iEvent_ = 0;

  std::cout << "Input file contains " << nEvents_ << " events" << std::endl;

  cuts_.setEvent(event_);

}


void Analyser::readWatchedEvents() {

  // open file
  std::string fname("watchedEvents.csv");
  std::ifstream file(fname.c_str(), ifstream::in);

  // read lines until we find the current run
  std::string line;
  if (!file.fail()) {
    while (!file.eof()) {
      getline(file, line);
      std::vector<std::string> strs;
      boost::split(strs, line, boost::is_any_of(",")); 
      if(atoi(strs.at(0).c_str())>0) {
	unsigned run=(unsigned) atoi(strs.at(0).c_str());
	unsigned id=(unsigned) atoi(strs.at(1).c_str());
	watchedEvents_.push_back(std::pair<unsigned, unsigned>(run, id));
      }
    }
  }

  std::cout << "Watching for " << watchedEvents_.size() << " events" << std::endl;
  for (unsigned i=0; i<watchedEvents_.size(); ++i) {
    std::cout << watchedEvents_.at(i).first << ", " << watchedEvents_.at(i).second << std::endl;
  }
 
}


void Analyser::reset() {
  iEvent_ = 0;
}


void Analyser::nextEvent() {

  int nb=0;
  if (iEvent_ < nEvents_-1) {
    nb = tree_->GetEntry(iEvent_);
    iEvent_++;
  }

  if (nb == 0) {  std::cout << "TTree GetEntry() failed" << std::endl; }

}


void Analyser::printEvent() {
  tree_->Show();
}


void Analyser::printCutValues(ostream& o) {

  o << "Stopped HSCP Event" << std::endl;
  o << "  id             = " << event_->id << std::endl;
  o << "  lb             = " << event_->lb << std::endl;
  o << "  run            = " << event_->run << std::endl;
  o << "  nTowerSameiPhi = " << event_->nTowerSameiPhi << std::endl;
  o << "  jetE[0]        = " << event_->jetE[0] << std::endl;
  o << "  jetEta[0]      = " << event_->jetEta[0] << std::endl;
  o << "  jetN60[0]      = " << event_->jetN60[0] << std::endl;
  o << "  jetN90[0]      = " << event_->jetN90[0] << std::endl;
  o << "  mu_N           = " << event_->mu_N << std::endl;
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


bool Analyser::isWatchedEvent() {

  bool result=false;
  for (unsigned i=0; i<watchedEvents_.size(); ++i) {
    if (event_->run == watchedEvents_.at(i).first && 
	event_->id == watchedEvents_.at(i).second) result=true;
  }

  return result;

}


void Analyser::loop() {

  reset();

  // run loop
  for (unsigned long i=0; i<nEvents_; ++i, nextEvent()) {
    
    if (i%100000==0) {
      std::cout << "Processing " << i << "th event" << std::endl;
    }
    
    histogrammer_.fill(*event_);
    
    // print watched events
    if (isWatchedEvent()) {
      printCutValues(dumpFile_);
    }
    
    // print selected events
    if (cuts_.cut()) {
      printCutValues(dumpFile_);
      eventFile_ << event_->run << ", " << event_->lb << ", " << event_->orbit << ", " << event_->bx << ", " << event_->id << std::endl;
    }
    
  }

  histogrammer_.save();

}
