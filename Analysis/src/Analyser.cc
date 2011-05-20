#include "StoppedHSCP/Analysis/interface/Analyser.h"

#include "StoppedHSCP/Analysis/interface/Constants.h"

#include <iostream>
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>

Analyser::Analyser(std::vector<std::string> ifiles, 
		   std::string outdir, 
		   bool isMC,
		   unsigned cutVersion) :
  isMC_(isMC),
  nEvents_(0),
  iEvent_(0),
  ofile_((outdir+std::string("/histograms.root")).c_str(), "RECREATE"),
  event_(0),
  cuts_(0, isMC, cutVersion, 0),
  histograms_(&ofile_, &cuts_),
  controlHistos_(&ofile_, &cuts_),
  haloHistos_(&ofile_, &cuts_),
  beamGasHistos_(&ofile_, &cuts_),
  collisionsHistos_(&ofile_, &cuts_),
  cosmicsHistos_(&ofile_, &cuts_),
  noiseHistos_(&ofile_, &cuts_),
  signalHistos_(&ofile_, &cuts_),
  runHistos_(&ofile_, &cuts_),
  fillHistos_(&ofile_, &cuts_),
  fills_(),
  watchedEvents_(0),
  eventFile_(),
  pickFile_(),
  dumpFile_(),
  lifetimeFile_()
{

  // input files
  ifiles_.clear();
  for (uint i=0;i<ifiles.size();++i)
    ifiles_.push_back(ifiles[i]);

  // setup log files
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
  std::cout << "Ntuple files       : " <<std::endl;
  for (uint zz=0;zz<ifiles.size();++zz)
    std::cout <<"\t\t"<<ifiles[zz] << std::endl;
  std::cout << "Output file       : " << outdir+std::string("/histograms.root") << std::endl;
//   std::cout << "Run list          : ";
//   for (unsigned i=0; i<runs.size(); ++i) {
//     std::cout << runs.at(i) << ",";
//   }
//   std::cout << std::endl;

  // for backwards compatibility with old versions of the analysis
  fills_.writeBunchMaskFile();

}

Analyser::~Analyser() {

  dumpFile_.close();
  eventFile_.close();

}


void Analyser::setup() {

  // set up the TChain
  chain_=new TChain("stoppedHSCPTree/StoppedHSCPTree");

  for (unsigned i=0;i<ifiles_.size();++i)
    chain_->Add(ifiles_[i].c_str());
  
  chain_->SetBranchAddress("events",&event_);
  Int_t nentries = Int_t(chain_->GetEntries());
  if (nentries>-1) nEvents_=nentries;
  iEvent_ = 0;

  // setup the cuts
  cuts_.setEvent(event_);
  cuts_.setFills(&fills_);

  // setup the watched event list
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
	unsigned long run = (unsigned long) atoi(strs.at(0).c_str());
	//unsigned lb  = (unsigned) atoi(strs.at(1).c_str()); // not currently used
	unsigned long id  = (unsigned long) atoi(strs.at(2).c_str());
	watchedEvents_.push_back(std::pair<unsigned long, unsigned long>(run, id));
      }
    }
  }

  std::cout << "Watching for " << watchedEvents_.size() << " events" << std::endl;
  for (unsigned long i=0; i<watchedEvents_.size(); ++i) {
    std::cout << watchedEvents_.at(i).first << ", " << watchedEvents_.at(i).second << std::endl;
  }
 
}


void Analyser::reset() {
  iEvent_ = 0;
}


void Analyser::nextEvent() {

  if (iEvent_ < nEvents_-1) {
    int nb=0;
    nb=chain_->GetEntry(iEvent_);
    iEvent_++;
    if (nb == 0) {  std::cout << "TChain::GetEntry() failed" << std::endl; }
  }

}


void Analyser::printEvent() {
  chain_->Show();
}


void Analyser::printCutValues(ostream& o) {

  o << "Stopped HSCP Event" << std::endl;
  o << "  run            = " << event_->run << std::endl;
  o << "  lb             = " << event_->lb << std::endl;
  o << "  id             = " << event_->id << std::endl;
  o << "  bx             = " << event_->bx << std::endl;
  o << "  t since coll   = " << event_->bxAfterCollision * 25e-9 << std::endl;
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


void Analyser::loop(ULong64_t maxEvents) {

  reset();
 
  unsigned long currentRun=0;

  // run loop

  if (maxEvents==0) maxEvents=nEvents_;

  nextEvent();

  for (unsigned long i=0; i<maxEvents; ++i, nextEvent()) {

    // occasional print out
    if (i%100000==0) {
      std::cout << "Processing " << i << "th event of " <<maxEvents<< std::endl;
    }
    
    // pass event to histogrammers
    histograms_.fill(*event_);
    runHistos_.fill(*event_);
    fillHistos_.fill(*event_);
    
    haloHistos_.fill(*event_);
    beamGasHistos_.fill(*event_);
    collisionsHistos_.fill(*event_);
    cosmicsHistos_.fill(*event_);
    noiseHistos_.fill(*event_);
    signalHistos_.fill(*event_);
    
    // check if this is an event we're watching for and do something if so
    if (isWatchedEvent()) {
      printCutValues(dumpFile_);
    }

    // check if this event passes all cuts and do something if so
    if (cuts_.cut()) {
      printCutValues(dumpFile_);
      eventFile_ << event_->run << "," << event_->lb << "," << event_->orbit << "," << event_->bx << "," << event_->id << std::endl;
      pickFile_ << event_->run << ":" << event_->lb << ":"  << event_->id << std::endl;
      lifetimeFile_ << ((event_->bxAfterCollision - 1) *  TIME_PER_BX)/TIME_WINDOW << std::endl;
      lifetimeFile_ << (event_->bxAfterCollision *  TIME_PER_BX)/TIME_WINDOW << std::endl;
    }
  } // for (unsigned long i=0;...)

  // save the histograms
  histograms_.save();
  controlHistos_.save();
  runHistos_.save();
  fillHistos_.save();

  histograms_.summarise();
  runHistos_.summarise();
  fillHistos_.summarise();

  haloHistos_.save();
  beamGasHistos_.save();
  collisionsHistos_.save();
  cosmicsHistos_.save();
  noiseHistos_.save();
  signalHistos_.save();

  haloHistos_.summarise();
  beamGasHistos_.summarise();
  collisionsHistos_.summarise();
  cosmicsHistos_.summarise();
  noiseHistos_.summarise();
  signalHistos_.summarise();

}
