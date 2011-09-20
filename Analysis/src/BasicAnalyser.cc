#include "StoppedHSCP/Analysis/interface/BasicAnalyser.h"

#include "StoppedHSCP/Ntuples/interface/Constants.h"

#include <iostream>
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>

BasicAnalyser::BasicAnalyser(std::vector<std::string> ifiles, 
		   std::string ofile, 
		   bool isMC) :
  isMC_(isMC),
  ifiles_(ifiles),
  nEvents_(0),
  iEvent_(0),
  ofile_(ofile.c_str(), "RECREATE"),
  event_(0),
  cuts_(0, isMC, 0, 0)
{

  std::cout << "Stopped Gluino Analysis" << std::endl;

  // no input files
  if (ifiles.size()==0) {
    std::cout <<"BasicAnalyser Error : no input files specified!"<<std::endl;
    std::exit(-1);
  }

  // no output files
  if (ofile =="") {
    std::cout <<"BasicAnalyser Error : no output directory specified!"<<std::endl;
    std::exit(-1);
  }

  // print input files
  std::cout << "Ntuple files       : " <<std::endl;
  for (std::vector<std::string>::iterator file=ifiles_.begin(); file!=ifiles_.end(); ++file) 
    std::cout << (*file) << std::endl;

  // print output file
  std::cout << "Output file       : " << ofile << std::endl;

}

BasicAnalyser::~BasicAnalyser() {

}


void BasicAnalyser::setup() {

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

}


void BasicAnalyser::reset() {
  iEvent_ = 0;
}


void BasicAnalyser::nextEvent() {

  if (iEvent_ < nEvents_-1) {
    int nb=0;
    nb=chain_->GetEntry(iEvent_);
    iEvent_++;
    if (nb == 0) {  std::cout << "TChain::GetEntry() failed" << std::endl; }
  }

}


void BasicAnalyser::printEvent() {
  chain_->Show();
}


void BasicAnalyser::printCutValues(ostream& o) {

  o << "Stopped HSCP Event" << std::endl;
  o << "  run            = " << event_->run << "\t" << std::endl;
  o << "  lb             = " << event_->lb << "\t" << std::endl;
  o << "  id             = " << event_->id << "\t" << std::endl;
  o << "  bx             = " << event_->bx << "\t" << std::endl;
  double lifetime = event_->bxAfterCollision * TIME_PER_BX;
  o << "  t since coll   = " << lifetime << "\t" << std::endl;
  o << "  orbit          = " << event_->orbit << "\t" << std::endl;
  o << " Cut values :" << std::endl;
  o << "  BX wrt coll    = " << event_->bxWrtCollision << "\t" << cuts_.bxVeto() << std::endl;
  o << "  nVtx           = " << event_->nVtx << "\t" << cuts_.vertexVeto() << std::endl;
  std::string halo("None");
  if (event_->beamHalo_CSCLoose) halo = "CSCLoose";
  if (event_->beamHalo_CSCTight) halo = "CSCTight";
  o << "  beamHalo       = " << halo << "\t" << cuts_.haloVeto() << std::endl;
  o << "  mu_N           = " << event_->mu_N << "\t\t" << cuts_.cosmicVeto() << std::endl;
  std::string noise = (event_->noiseFilterResult ? "No" : "Yes");
  o << "  HCAL noise     = " << noise << "\t\t" << cuts_.hcalNoiseVeto() << std::endl;
  o << "  nTowerSameiPhi = " << event_->nTowerSameiPhi << "\t\t" << cuts_.towersIPhiCut() << std::endl;
  o << "  jetE[0]        = " << event_->jetE[0] << "\t" << cuts_.jetEnergyCut() << std::endl;
  o << "  jetEta[0]      = " << event_->jetEta[0] << "\t" << cuts_.jetEnergyCut() << std::endl;
  o << "  jetN60[0]      = " << event_->jetN60[0] << "\t\t" << cuts_.jetN60Cut() << std::endl;
  o << "  jetN90[0]      = " << event_->jetN90[0] << "\t\t" << cuts_.jetN90Cut() << std::endl;
  o << "  jetEMF[0]      = " << (event_->jetEEm[0] / event_->jetEHad[0]) << std::endl;
  o << "  topHPD5R1      = " << event_->topHPD5R1 << "\t" << cuts_.hpdR1Cut() << std::endl;
  o << "  topHPDR2       = " << event_->topHPD5R2 << "\t" << cuts_.hpdR2Cut() << std::endl;
  o << "  topHPD5RPeak   = " << event_->topHPD5RPeak << "\t" << cuts_.hpdRPeakCut() << std::endl;
  o << "  topHPD5ROuter  = " << event_->topHPD5ROuter << "\t" << cuts_.hpdROuterCut() << std::endl;
  o << "  top5DigiR1     = " << event_->top5DigiR1 << "\t" << cuts_.digiR1Cut() << std::endl;
  o << "  top5DigiR2     = " << event_->top5DigiR2 << "\t" << cuts_.digiR2Cut() << std::endl;
  o << "  top5DigiRPeak  = " << event_->top5DigiRPeak << "\t" << cuts_.digiRPeakCut() << std::endl;
  o << "  top5DigiROuter = " << event_->top5DigiROuter << "\t" << cuts_.digiROuterCut() << std::endl;
  o << "  time sample    = ";
  for (unsigned i=0; i<10; ++i) o << event_->top5DigiTimeSamples.at(i) << " ";
  o << std::endl;
  o << std::endl;
}


void BasicAnalyser::loop(ULong64_t maxEvents) {

  reset();
 
  if (maxEvents==0) maxEvents=nEvents_;

  nextEvent();

  for (unsigned long i=0; i<maxEvents; ++i, nextEvent()) {

    // occasional print out
    if (i%100000==0) {
      std::cout << "Processing " << i << "th event of " <<maxEvents<< std::endl;
    }

    // YOUR CODE HERE

  }

}
