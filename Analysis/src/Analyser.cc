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
  fills_(),
  watchedEvents_(0),
  eventFile_(),
  pickFile_(),
  dumpFile_(),
  lifetimeFile_()
{
  // log files
  std::string fd(outdir);
  fd+="/fullDump.log";
  dumpFile_.open(fd.c_str());
  dumpFile_ << "Cut variables for events passing all cuts" << std::endl << std::endl;
  
  std::string ei(outdir);
  ei+="/eventList.log";
  eventFile_.open(ei.c_str());

  std::string pf(outdir);
  pf+="/pickEvents.txt";
  pickFile_.open(pf.c_str());

  std::string lf(outdir);
  lf+="/lifetimes.txt";
  lifetimeFile_.open(lf.c_str());

  std::cout << "Stopped Gluino Histogrammer" << std::endl;
  std::cout << "Ntuple file       : " << ifile << std::endl;
  std::cout << "Output file       : " << outdir+std::string("/histograms.root") << std::endl;
  std::cout << "Run list          : ";
  for (unsigned i=0; i<runs.size(); ++i) {
    std::cout << runs.at(i) << ",";
  }
  std::cout << std::endl;

  // for backwards compatibility with old versions of the analysis
  fills_.writeBunchMaskFile();

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

  readWatchedEvents();

}


void Analyser::readWatchedEvents() {

  // open file
  std::string fname("watchedEvents.txt");
  std::ifstream file(fname.c_str(), ifstream::in);

  // read lines until we find the current run
  std::string line;
  if (!file.fail()) {
    while (!file.eof()) {
      getline(file, line);
      std::vector<std::string> strs(0);
      boost::split(strs, line, boost::is_any_of(std::string(":"))); 
      if(atoi(strs.at(0).c_str())>0) {
	unsigned run = (unsigned) atoi(strs.at(0).c_str());
	//unsigned lb  = (unsigned) atoi(strs.at(1).c_str()); // not currently used
	unsigned id  = (unsigned) atoi(strs.at(2).c_str());
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

  if (iEvent_ < nEvents_-1) {
    int nb=0;
    nb = tree_->GetEntry(iEvent_);
    iEvent_++;
    if (nb == 0) {  std::cout << "TTree GetEntry() failed" << std::endl; }
  }

}


void Analyser::printEvent() {
  tree_->Show();
}


void Analyser::printCutValues(ostream& o) {

  o << "Stopped HSCP Event" << std::endl;
  o << "  run            = " << event_->run << std::endl;
  o << "  lb             = " << event_->lb << std::endl;
  o << "  id             = " << event_->id << std::endl;
  o << "  bx             = " << event_->bx << std::endl;
  o << "  t since coll   = " << eventLifetime(event_->run, event_->bx) << std::endl;
  o << "  orbit          = " << event_->orbit << std::endl;
  o << "  BX veto        = " << cuts_.cutN(1) << std::endl;
  o << "  BPTX veto      = " << cuts_.cutN(2) << std::endl;
  o << "  nVtx           = " << event_->nVtx << std::endl;
  std::string halo("None");
  if (event_->beamHalo_CSCLoose) halo = "CSCLoose";
  if (event_->beamHalo_CSCTight) halo = "CSCTight";
  o << "  beamHalo       = " << halo << std::endl;
  o << "  mu_N           = " << event_->mu_N << std::endl;
  o << "  HCAL noise     = " << (event_->noiseFilterResult ? "No" : "Yes") << std::endl;
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


bool Analyser::isWatchedEvent() {

  bool result=false;
  for (unsigned i=0; i<watchedEvents_.size(); ++i) {
    if (event_->run == watchedEvents_.at(i).first && 
	event_->id == watchedEvents_.at(i).second) result=true;
  }

  return result;

}


void Analyser::loop(Long64_t maxEvents) {

  reset();
 
  unsigned currentRun=0;

  // run loop

  if (maxEvents<=0) maxEvents=nEvents_;

  for (unsigned long i=0; i<maxEvents; ++i, nextEvent()) {
    
    if (i%100000==0) {
      std::cout << "Processing " << i << "th event" << std::endl;
    }
    
    // check to see if the run number changed
    // update fill structure if so
    if (event_->run != currentRun) {

      std::cout << "New run : " << event_->run << std::endl;
      cuts_.setMaskedBXs(fills_.getMaskFromRun(event_->run));
      currentRun = event_->run;

      // write new histograms
      histogrammer_.fillCollisionsHistos(currentRun, &fills_);
    }

    // fill histograms
    histogrammer_.fill(*event_);
    // print watched events
    if (isWatchedEvent()) {
      printCutValues(dumpFile_);
    }
    
    // print selected events
    if (cuts_.cut()) {
      printCutValues(dumpFile_);
      eventFile_ << event_->run << "," << event_->lb << "," << event_->orbit << "," << event_->bx << "," << event_->id << std::endl;
      pickFile_ << event_->run << ":" << event_->lb << ":"  << event_->id << std::endl;
      lifetimeFile_ << eventLifetime(event_->run, event_->bx-1)/1.256 << std::endl;
      lifetimeFile_ << eventLifetime(event_->run, event_->bx)/1.256 << std::endl;
    }

  }

  histogrammer_.save();

}


double Analyser::eventLifetime(unsigned run, unsigned bx) {
  std::vector<unsigned> colls=fills_.getCollisionsFromRun(run);
  std::vector<unsigned>::const_iterator lastColl;

  // this could fail if there is ever no collision at BX=1
  lastColl = lower_bound(colls.begin(), colls.end(), bx);
  if (lastColl==colls.begin()) lastColl=colls.end();
  int collBx = *(--lastColl);

  double t = (bx - collBx) * LhcFills::TIME_PER_BX;
  //  std::cout << "Delta-BX : " << bx << " " << collBx << " " << t << std::endl; 
  return t;

}
