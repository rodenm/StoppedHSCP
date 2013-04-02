#include "StoppedHSCP/Analysis/interface/BasicAnalyser.h"

#include "StoppedHSCP/Ntuples/interface/Constants.h"

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sys/stat.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <boost/program_options.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/filesystem.hpp>

namespace po = boost::program_options;



BasicAnalyser::BasicAnalyser(int argc, char* argv[]) :
  isMC_(false),
  ifiles_(0),
  nEvents_(0),
  maxEvents_(0),
  iEvent_(0),
  outdir_(""),
  ofilename_(""),
  ofile_(0),
  event_(0),
  cuts_(0, false, 0, 0),
  lhcFills_(),
  livetime_(&lhcFills_)
{

  // get options
  po::options_description desc("Allowed options");
  //  po::positional_options_description poptd;

  desc.add_options()
    ("help,h", "Display this message")
    ("outdir,o", po::value<std::string>(), "Output directory")
    ("indir,i", po::value<std::string>(), "Input directory")
    ("cuts,c", po::value<unsigned>()->default_value(0), "Cuts version")
    ("num,n", po::value<unsigned long long>()->default_value(0), "Number of events to process")
    ("mc,m", "Run on MC");

  po::variables_map vm;
  po::store(po::command_line_parser(argc, argv).options(desc).allow_unregistered().run(), vm);  
  po::notify(vm);

  // help
  if (vm.count("help")) {
    std::cout << desc << std::endl;
    std::exit(1);
  }
  
  // set output directory & create it if it doesn't exist already
  if (vm.count("outdir")) {
    outdir_ = vm["outdir"].as<std::string>();

    boost::filesystem::path opath(outdir_);
    if (!exists(opath)) {
      std::cout << "Creating output directory : " << outdir_ << std::endl;
      boost::filesystem::create_directory(opath);
    }
  }
  
  // set input directory
  std::string indir("");
  if (vm.count("indir"))
    indir=vm["indir"].as<std::string>();

  // set number of events
  if (vm.count("num") && vm["num"].as<unsigned long long>()>0)
    maxEvents_=ULong64_t(vm["num"].as<unsigned long long>());

  // set cut version
  cuts_ = Cuts(0, false, vm["cuts"].as<unsigned>(), &lhcFills_);

  /// set if is this MC
  if (vm.count("mc")) {
    isMC_=true;
    cuts_.setMC(true);
  }
  
  // get list of input files
  DIR *dp;
  struct dirent *dirp;
  if((dp  = opendir(indir.c_str())) == NULL) {
    std::cout << "Error(" << errno << ") opening " << indir << std::endl;
    std::exit(errno);
  }
  
  while ((dirp = readdir(dp)) != NULL) {
    std::string filename(dirp->d_name);
    if (filename.find(std::string(".root")) != std::string::npos) {
      ifiles_.push_back(indir+std::string("/")+filename);
    }
  }
  closedir(dp);

  // print some info & catch some error conditions
  std::cout << "Stopped Gluino Analysis" << std::endl;

  // no input files
  if (ifiles_.size()==0) {
    std::cout <<"BasicAnalyser Error : no input files specified!"<<std::endl;
    std::exit(-1);
  }

  // output directory
  if (outdir_ == std::string("")) {
    std::cout <<"BasicAnalyser Error : no output directory specified!"<<std::endl;
    std::exit(-1);
  }

  // print input files
  std::cout << "Ntuple files       : " <<std::endl;
  for (std::vector<std::string>::iterator file=ifiles_.begin(); file!=ifiles_.end(); ++file) 
    std::cout << (*file) << std::endl;

}

BasicAnalyser::~BasicAnalyser() {

  ofile_->Close();
  delete ofile_;

  std::cout << "End of analysis" << std::endl;

}


void BasicAnalyser::setup() {

  // set up the TChain
  chain_=new TChain("stoppedHSCPTree/StoppedHSCPTree");
  for (unsigned i=0;i<ifiles_.size();++i)
    chain_->Add(ifiles_[i].c_str());
  
  // setup event pointer
  chain_->SetBranchAddress("events",&event_);

  // set number of entries
  Int_t nentries = Int_t(chain_->GetEntries());
  if (nentries>-1) nEvents_=nentries;
  iEvent_ = 0;

  // if no maximum has been set, set it equal to number of events
  if (maxEvents_==0) maxEvents_=nEvents_;

  // setup the cuts
  cuts_.setEvent(event_);

  // set up the output file
  ofile_ = new TFile((outdir_+std::string("/")+ofilename_).c_str(), "RECREATE");
  std::cout << "Output file        : " << ofile_->GetName() << std::endl;

  if (ofile_->IsZombie()) {
    std::exit(2);
  }

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
  o << "  BX wrt bunch   = " << event_->bxWrtBunch << "\t" << cuts_.bxVeto() << std::endl;
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
  o << "  jetPhi[0]      = " << event_->jetPhi[0] << "\t" << cuts_.hcalNoiseVeto() << std::endl;
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
  o << "  HPDs           = ";
  for (unsigned i=0; i<event_->hpd_N ; i++)
    o << event_->hpdId[i] << "  ";
  o << std::endl;
  o << std::endl;
}


void BasicAnalyser::loop() {

  reset();
  nextEvent();

  for (unsigned long i=0; i<maxEvents_; ++i, nextEvent()) {

    // occasional print out
    if (i%100000==0) {
      std::cout << "Processing " << i << "th event of " <<maxEvents_<< std::endl;
    }

    // YOUR CODE HERE

  }

}
