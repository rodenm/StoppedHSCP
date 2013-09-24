#ifndef BXDistributions_h
#define BXDistributions_h

#include "StoppedHSCP/Analysis/interface/BasicAnalyser.h"
#include "StoppedHSCP/Analysis/interface/MultiHistogram1D.h"

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
    BasicAnalyser(argc, argv),
    nFills(0)
  {
    ofilename_ = std::string("BXDistributions.root");  /// SET YOUR OUTPUT FILENAME HERE
  }
  
  ~BXDistributions() { 

  };
  
  virtual void loop();
  
private:

  // YOUR CODE HERE
  unsigned nFills;
  std::vector<unsigned long> fillList_;

  MultiHistogram1D hBX_;

  // near a collision
  MultiHistogram1D hRelBXNorm_;
  MultiHistogram1D hRelBX_;
  MultiHistogram1D hRelBXVtx_;
  MultiHistogram1D hRelBXBeamgas_;
  MultiHistogram1D hRelBXHalo_;
  MultiHistogram1D hRelBXCosmic_;
  MultiHistogram1D hRelBXNoise_;
  MultiHistogram1D hRelBXNoID_;
  MultiHistogram1D hRelBXSearch_;

  std::vector<unsigned> collBaseRate_;
  std::vector<unsigned> collBaseRateHalo_;
  std::vector<unsigned> collBaseRateBG_;
  std::vector<unsigned> collBaseRateCosmic_;
  std::vector<unsigned> collBaseRateNoise_;
  std::vector<unsigned> collBaseRateNoID_;
  
  std::vector<unsigned> collMinusOneRate_;
  std::vector<unsigned> collMinusOneRateHalo_;
  std::vector<unsigned> collMinusOneRateBG_;
  std::vector<unsigned> collMinusOneRateCosmic_;
  std::vector<unsigned> collMinusOneRateNoise_;
  std::vector<unsigned> collMinusOneRateNoID_;


  // near an unpaired bunch
  MultiHistogram1D hRelUPBunchBXNorm_;
  MultiHistogram1D hRelUPBunchBX_;
  MultiHistogram1D hRelUPBunchBXVtx_;
  MultiHistogram1D hRelUPBunchBXBeamgas_;
  MultiHistogram1D hRelUPBunchBXHalo_;
  MultiHistogram1D hRelUPBunchBXCosmic_;
  MultiHistogram1D hRelUPBunchBXNoise_;
  MultiHistogram1D hRelUPBunchBXNoID_;
  MultiHistogram1D hRelUPBunchBXSearch_;

  std::vector<unsigned> upBaseRate_;
  std::vector<unsigned> upBaseRateHalo_;
  std::vector<unsigned> upBaseRateBG_;
  std::vector<unsigned> upBaseRateCosmic_;
  std::vector<unsigned> upBaseRateNoise_;
  std::vector<unsigned> upBaseRateNoID_;
  
  std::vector<unsigned> upMinusOneRate_;
  std::vector<unsigned> upMinusOneRateHalo_;
  std::vector<unsigned> upMinusOneRateBG_;
  std::vector<unsigned> upMinusOneRateCosmic_;
  std::vector<unsigned> upMinusOneRateNoise_;
  std::vector<unsigned> upMinusOneRateNoID_;



};

#endif


// this is the event loop
void BXDistributions::loop() {

  hBX_.setup(ofile_, "hBX", "BX distribution:BX:N_{evt}", 3564, 0., 3564.);

  hRelBXNorm_.setup(ofile_, "hRelBXNorm", "Relative BX normalisation", 2000, -1000., 1000.);
  hRelBX_.setup(ofile_, "hRelBX", "Relative BX", 2000, -1000., 1000.);
  hRelBXVtx_.setup(ofile_, "hRelBXVtx", "Relative BX (Vtx)", 2000, -1000., 1000.);
  hRelBXBeamgas_.setup(ofile_, "hRelBXBeamgas", "Relative BX (Beamgas)", 2000, -1000., 1000.);
  hRelBXHalo_.setup(ofile_, "hRelBXHalo", "Relative BX (Halo)", 2000, -1000., 1000.);
  hRelBXCosmic_.setup(ofile_, "hRelBXCosmic", "Relative BX (Cosmic)", 2000, -1000., 1000.);
  hRelBXNoise_.setup(ofile_, "hRelBXNoise", "Relative BX (Noise)", 2000, -1000., 1000.);
  hRelBXNoID_.setup(ofile_, "hRelBXNoID", "Relative BX (No ID)", 2000, -1000., 1000.);
  hRelBXSearch_.setup(ofile_, "hRelBXSearch", "Relative BX (Search)", 2000, -1000., 1000.);

  hRelUPBunchBXNorm_.setup(ofile_, "hRelUPBunchBXNorm", "Relative BX normalisation", 2000, -1000., 1000.);
  hRelUPBunchBX_.setup(ofile_, "hRelUPBunchBX", "Relative BX", 2000, -1000., 1000.);
  hRelUPBunchBXVtx_.setup(ofile_, "hRelUPBunchBXVtx", "Relative BX (Vtx)", 2000, -1000., 1000.);
  hRelUPBunchBXBeamgas_.setup(ofile_, "hRelUPBunchBXBeamgas", "Relative BX (Beamgas)", 2000, -1000., 1000.);
  hRelUPBunchBXHalo_.setup(ofile_, "hRelUPBunchBXHalo", "Relative BX (Halo)", 2000, -1000., 1000.);
  hRelUPBunchBXCosmic_.setup(ofile_, "hRelUPBunchBXCosmic", "Relative BX (Cosmic)", 2000, -1000., 1000.);
  hRelUPBunchBXNoise_.setup(ofile_, "hRelUPBunchBXNoise", "Relative BX (Noise)", 2000, -1000., 1000.);
  hRelUPBunchBXNoID_.setup(ofile_, "hRelUPBunchBXNoID", "Relative BX (No ID)", 2000, -1000., 1000.);
  hRelUPBunchBXSearch_.setup(ofile_, "hRelUPBunchBXSearch", "Relative BX (Search)", 2000, -1000., 1000.);

  reset();
 
  nextEvent();

  for (ULong64_t i=0; i<maxEvents_; ++i, nextEvent()) {

    // occasional print out
    if (i%100000==0) {
      std::cout << "Processing " << i << "th event of " <<maxEvents_<< std::endl;
    }

    // YOUR CODE HERE
    

    // check for new fill and only fill normalisation histograms once
    unsigned long fill=event_->fill;
    std::vector<unsigned long>::const_iterator itr = find(fillList_.begin(), fillList_.end(), fill);

    if (itr == fillList_.end()) {
      
      for (unsigned i=0; i<3564; ++i) {

	int bxWrtBunch = lhcFills_.getBxWrtBunch(fill, i);
	int bxWrtColl  = lhcFills_.getBxWrtCollision(fill, i);

	if ( abs(abs(bxWrtBunch) - abs(bxWrtColl)) < 2) hRelBXNorm_.fill( fill, bxWrtBunch );
	else if (abs(bxWrtBunch) < (abs(bxWrtColl)-1)) hRelUPBunchBXNorm_.fill( fill, bxWrtBunch );
	else std::cerr << "Found a BX where bxWrtBunch=" << bxWrtBunch << " and bxWrtCollision=" << bxWrtColl << std::endl;

      }

      std::cout << fill << ":   " << lhcFills_.getLiveFraction(fill) << std::endl;

      fillList_.push_back(fill);
      nFills++;

      // relative to a collision
      hRelBXVtx_.fill(fill, 0., 0.);
      hRelBXBeamgas_.fill(fill, 0., 0.);
      hRelBXHalo_.fill(fill, 0., 0.);
      hRelBXCosmic_.fill(fill, 0., 0.);
      hRelBXNoise_.fill(fill, 0., 0.);
      hRelBXNoID_.fill(fill, 0., 0.);
      hRelBXSearch_.fill(fill, 0., 0.);

      if (collBaseRate_.size() < fill+1) collBaseRate_.resize(fill+1, 0);
      if (collBaseRateBG_.size() < fill+1) collBaseRateBG_.resize(fill+1, 0);
      if (collBaseRateHalo_.size() < fill+1) collBaseRateHalo_.resize(fill+1, 0);
      if (collBaseRateCosmic_.size() < fill+1) collBaseRateCosmic_.resize(fill+1, 0);
      if (collBaseRateNoise_.size() < fill+1) collBaseRateNoise_.resize(fill+1, 0);
      if (collBaseRateNoID_.size() < fill+1) collBaseRateNoID_.resize(fill+1, 0);

      if (collMinusOneRate_.size() < fill+1) collMinusOneRate_.resize(fill+1, 0);
      if (collMinusOneRateBG_.size() < fill+1) collMinusOneRateBG_.resize(fill+1, 0);
      if (collMinusOneRateHalo_.size() < fill+1) collMinusOneRateHalo_.resize(fill+1, 0);
      if (collMinusOneRateCosmic_.size() < fill+1) collMinusOneRateCosmic_.resize(fill+1, 0);
      if (collMinusOneRateNoise_.size() < fill+1) collMinusOneRateNoise_.resize(fill+1, 0);
      if (collMinusOneRateNoID_.size() < fill+1) collMinusOneRateNoID_.resize(fill+1, 0);

      // relative to unpaired bunch
      hRelUPBunchBXVtx_.fill(fill, 0., 0.);
      hRelUPBunchBXBeamgas_.fill(fill, 0., 0.);
      hRelUPBunchBXHalo_.fill(fill, 0., 0.);
      hRelUPBunchBXCosmic_.fill(fill, 0., 0.);
      hRelUPBunchBXNoise_.fill(fill, 0., 0.);
      hRelUPBunchBXNoID_.fill(fill, 0., 0.);
      hRelUPBunchBXSearch_.fill(fill, 0., 0.);

      if (upBaseRate_.size() < fill+1) upBaseRate_.resize(fill+1, 0);
      if (upBaseRateBG_.size() < fill+1) upBaseRateBG_.resize(fill+1, 0);
      if (upBaseRateHalo_.size() < fill+1) upBaseRateHalo_.resize(fill+1, 0);
      if (upBaseRateCosmic_.size() < fill+1) upBaseRateCosmic_.resize(fill+1, 0);
      if (upBaseRateNoise_.size() < fill+1) upBaseRateNoise_.resize(fill+1, 0);
      if (upBaseRateNoID_.size() < fill+1) upBaseRateNoID_.resize(fill+1, 0);

      if (upMinusOneRate_.size() < fill+1) upMinusOneRate_.resize(fill+1, 0);
      if (upMinusOneRateBG_.size() < fill+1) upMinusOneRateBG_.resize(fill+1, 0);
      if (upMinusOneRateHalo_.size() < fill+1) upMinusOneRateHalo_.resize(fill+1, 0);
      if (upMinusOneRateCosmic_.size() < fill+1) upMinusOneRateCosmic_.resize(fill+1, 0);
      if (upMinusOneRateNoise_.size() < fill+1) upMinusOneRateNoise_.resize(fill+1, 0);
      if (upMinusOneRateNoID_.size() < fill+1) upMinusOneRateNoID_.resize(fill+1, 0);

    }

     
    // fill histograms
    bool hasJet = (event_->jet_N>0 && event_->jetE[0]>30. && event_->jetEta[0]<1.3);

    // event classes (very loose right now!)
    bool isColl     = event_->vtx_N>0;
    bool isBeamGas  = event_->track_N>1 && !isColl;
    bool isHalo     = event_->cscSeg_N>0 && !isBeamGas && !isColl;
    bool isCosmic   = event_->mu_N>0 && !isHalo && !isBeamGas && !isColl;
    bool isNoise    = !event_->noiseFilterResult;
    bool isNoID     = (!isNoise && !isCosmic && !isHalo && !isBeamGas && !isColl);

    int bx = event_->bx;
    int bxWrtBunch = event_->bxWrtBunch;
    int bxWrtColl  = event_->bxWrtCollision;

    if (hasJet) {

      // fill histograms
      hBX_.fill(fill, bx);


      // near a collision
      // (difference in absolute values less than 1 to account for BX ~equidistant between UPB and Coll)
      if ( abs(abs(bxWrtBunch) - abs(bxWrtColl)) < 2) {

	hRelBX_.fill(fill, bxWrtBunch);
	if (isColl)    hRelBXVtx_.fill(fill, bxWrtBunch);
	if (isBeamGas) hRelBXBeamgas_.fill(fill, bxWrtBunch);
	if (isHalo)    hRelBXHalo_.fill(fill, bxWrtBunch);
	if (isCosmic)  hRelBXCosmic_.fill(fill, bxWrtBunch);
	if (isNoise)   hRelBXNoise_.fill(fill, bxWrtBunch);
	if (isNoID)    hRelBXNoID_.fill(fill, bxWrtBunch);
	if (cuts_.cut())    hRelBXSearch_.fill(fill, bxWrtBunch);

	// record base rate
	if (abs(bxWrtBunch) > 5) {
	  collBaseRate_.at(fill)+=1;
	  if (isBeamGas) collBaseRateBG_.at(fill)+=1;
	  if (isHalo)    collBaseRateHalo_.at(fill)+=1;
	  if (isCosmic)  collBaseRateCosmic_.at(fill)+=1;
	  if (isNoise)   collBaseRateNoise_.at(fill)+=1;
	  if (isNoID)    collBaseRateNoID_.at(fill)+=1;	
	}
	
	// record near rate
	if (bxWrtBunch == -1) {
	  collMinusOneRate_.at(fill)+=1;
	  if (isBeamGas) collMinusOneRateBG_.at(fill)+=1;
	  if (isHalo)    collMinusOneRateHalo_.at(fill)+=1;
	  if (isCosmic)  collMinusOneRateCosmic_.at(fill)+=1;
	  if (isNoise)   collMinusOneRateNoise_.at(fill)+=1;
	  if (isNoID)    collMinusOneRateNoID_.at(fill)+=1;
	}
	
      }
      else if (abs(bxWrtBunch) < (abs(bxWrtColl)-1) ) {  // closer to a unpaired bunch than a collision

	hRelUPBunchBX_.fill(fill, bxWrtBunch);
	if (isColl)    hRelUPBunchBXVtx_.fill(fill,  bxWrtBunch);
	if (isBeamGas) hRelUPBunchBXBeamgas_.fill(fill,  bxWrtBunch);
	if (isHalo)    hRelUPBunchBXHalo_.fill(fill,  bxWrtBunch);
	if (isCosmic)  hRelUPBunchBXCosmic_.fill(fill,  bxWrtBunch);
	if (isNoise)   hRelUPBunchBXNoise_.fill(fill,  bxWrtBunch);
	if (isNoID)    hRelUPBunchBXNoID_.fill(fill,  bxWrtBunch);
	if (cuts_.cut())    hRelUPBunchBXSearch_.fill(fill,  bxWrtBunch);

	// record base rate
	if (abs(bxWrtBunch) > 5) {
	  upBaseRate_.at(fill)+=1;
	  if (isBeamGas) upBaseRateBG_.at(fill)+=1;
	  if (isHalo)    upBaseRateHalo_.at(fill)+=1;
	  if (isCosmic)  upBaseRateCosmic_.at(fill)+=1;
	  if (isNoise)   upBaseRateNoise_.at(fill)+=1;
	  if (isNoID)    upBaseRateNoID_.at(fill)+=1;	
	}
	
	// record near rate
	if (bxWrtBunch == -1) {
	  upMinusOneRate_.at(fill)+=1;
	  if (isBeamGas) upMinusOneRateBG_.at(fill)+=1;
	  if (isHalo)    upMinusOneRateHalo_.at(fill)+=1;
	  if (isCosmic)  upMinusOneRateCosmic_.at(fill)+=1;
	  if (isNoise)   upMinusOneRateNoise_.at(fill)+=1;
	  if (isNoID)    upMinusOneRateNoID_.at(fill)+=1;
	}


      }
      else {  // closer to a collision than a bunch - cannot occur!
	std::cerr << "Found an event with bxWrtBunch=" << bxWrtBunch << " and bxWrtCollision=" << bxWrtColl << std::endl;
      }


    } 

  }

  /// save histograms
  hBX_.save();
  hRelBXNorm_.save();
  hRelBX_.save();
  hRelBXVtx_.save();
  hRelBXBeamgas_.save();
  hRelBXHalo_.save();
  hRelBXCosmic_.save();
  hRelBXNoise_.save();
  hRelBXNoID_.save();
  hRelBXSearch_.save();

  hRelUPBunchBXNorm_.save();
  hRelUPBunchBX_.save();
  hRelUPBunchBXVtx_.save();
  hRelUPBunchBXBeamgas_.save();
  hRelUPBunchBXHalo_.save();
  hRelUPBunchBXCosmic_.save();
  hRelUPBunchBXNoise_.save();
  hRelUPBunchBXNoID_.save();
  hRelUPBunchBXSearch_.save();

  ofile_->cd();
 
  // "base" rate 
  TH1D* hCollBaseRateNorm = new TH1D("hCollBaseRateNorm", "Base rate normalisation", nFills, 0., 0.);
  TH1D* hCollBaseRate = new TH1D("hCollBaseRate", "Base rate - all", nFills, 0., 0.);
  TH1D* hCollBaseRateHalo = new TH1D("hCollBaseRateHalo", "Base rate - halo", nFills, 0., 0.);
  TH1D* hCollBaseRateBG = new TH1D("hCollBaseRateBeamgas", "Base rate - beam gas", nFills, 0., 0.);
  TH1D* hCollBaseRateCosmic = new TH1D("hCollBaseRateCosmic", "Base rate - cosmic", nFills, 0., 0.);
  TH1D* hCollBaseRateNoise = new TH1D("hCollBaseRateNoise", "Base rate - noise", nFills, 0., 0.);
  TH1D* hCollBaseRateNoID = new TH1D("hCollBaseRateNoID", "Base rate - no ID", nFills, 0., 0.);

  sort(fillList_.begin(), fillList_.end());

  for (std::vector<unsigned long>::const_iterator i=fillList_.begin(); i!=fillList_.end(); ++i) {

    unsigned long fill = (*i);
    std::stringstream ss;
    ss << fill;
    std::string fillstr = ss.str();

    hCollBaseRateNorm->Fill(fillstr.c_str(), 0.);
    hCollBaseRate->Fill(fillstr.c_str(), 0.);
    hCollBaseRateHalo->Fill(fillstr.c_str(), 0.);
    hCollBaseRateBG->Fill(fillstr.c_str(), 0.);
    hCollBaseRateCosmic->Fill(fillstr.c_str(), 0.);
    hCollBaseRateNoise->Fill(fillstr.c_str(), 0.);
    hCollBaseRateNoID->Fill(fillstr.c_str(), 0.);

    for (unsigned count=0; count<collBaseRate_.at(fill); count++) hCollBaseRate->Fill(fillstr.c_str(), 1.);
    for (unsigned count=0; count<collBaseRateHalo_.at(fill); count++) hCollBaseRateHalo->Fill(fillstr.c_str(), 1.);
    for (unsigned count=0; count<collBaseRateBG_.at(fill); count++) hCollBaseRateBG->Fill(fillstr.c_str(), 1.);
    for (unsigned count=0; count<collBaseRateCosmic_.at(fill); count++) hCollBaseRateCosmic->Fill(fillstr.c_str(), 1.);
    for (unsigned count=0; count<collBaseRateNoise_.at(fill); count++) hCollBaseRateNoise->Fill(fillstr.c_str(), 1.);
    for (unsigned count=0; count<collBaseRateNoID_.at(fill); count++) hCollBaseRateNoID->Fill(fillstr.c_str(), 1.);

    // normalisation histogram - integrate normalisation
    for (int bx=-1000; bx<1000; ++bx) {

      unsigned norm=hRelBXNorm_.histogram(fill)->GetBinContent(bx+1001);

      if (abs(bx)>=5) {
	hCollBaseRateNorm->Fill(fillstr.c_str(), norm);
      }
      //      else std::cout << "Normalisation for BX=" << bx << " in fill " << fill << " is " << norm << std::endl;
      
    }
  }

  // "minus one" rate 
  hCollBaseRateNorm->Write("",TObject::kOverwrite);
  hCollBaseRate->Write("",TObject::kOverwrite);
  hCollBaseRateHalo->Write("",TObject::kOverwrite);
  hCollBaseRateBG->Write("",TObject::kOverwrite);
  hCollBaseRateCosmic->Write("",TObject::kOverwrite);
  hCollBaseRateNoise->Write("",TObject::kOverwrite);
  hCollBaseRateNoID->Write("",TObject::kOverwrite);

  TH1D* hCollMinusOneRateNorm = new TH1D("hCollMinusOneRateNorm", "Coll-1 rate normalisation", nFills, 0., 0.);
  TH1D* hCollMinusOneRate = new TH1D("hCollMinusOneRate", "Coll-1 rate - all", nFills, 0., 0.);
  TH1D* hCollMinusOneRateHalo = new TH1D("hCollMinusOneRateHalo", "Coll-1 rate - halo", nFills, 0., 0.);
  TH1D* hCollMinusOneRateBG = new TH1D("hCollMinusOneRateBeamgas", "Coll-1 rate - beam gas", nFills, 0., 0.);
  TH1D* hCollMinusOneRateCosmic = new TH1D("hCollMinusOneRateCosmic", "Coll-1 rate - cosmic", nFills, 0., 0.);
  TH1D* hCollMinusOneRateNoise = new TH1D("hCollMinusOneRateNoise", "Coll-1 rate - noise", nFills, 0., 0.);
  TH1D* hCollMinusOneRateNoID = new TH1D("hCollMinusOneRateNoID", "Coll-1 rate - no ID", nFills, 0., 0.);

  sort(fillList_.begin(), fillList_.end());

  for (std::vector<unsigned long>::const_iterator i=fillList_.begin(); i!=fillList_.end(); ++i) {

    unsigned long fill = (*i);
    std::stringstream ss;
    ss << fill;
    std::string fillstr = ss.str();

    hCollMinusOneRateNorm->Fill(fillstr.c_str(), 0.);
    hCollMinusOneRate->Fill(fillstr.c_str(), 0.);
    hCollMinusOneRateHalo->Fill(fillstr.c_str(), 0.);
    hCollMinusOneRateBG->Fill(fillstr.c_str(), 0.);
    hCollMinusOneRateCosmic->Fill(fillstr.c_str(), 0.);
    hCollMinusOneRateNoise->Fill(fillstr.c_str(), 0.);
    hCollMinusOneRateNoID->Fill(fillstr.c_str(), 0.);

    for (unsigned count=0; count<collMinusOneRate_.at(fill); count++) hCollMinusOneRate->Fill(fillstr.c_str(), 1.);
    for (unsigned count=0; count<collMinusOneRateHalo_.at(fill); count++) hCollMinusOneRateHalo->Fill(fillstr.c_str(), 1.);
    for (unsigned count=0; count<collMinusOneRateBG_.at(fill); count++) hCollMinusOneRateBG->Fill(fillstr.c_str(), 1.);
    for (unsigned count=0; count<collMinusOneRateCosmic_.at(fill); count++) hCollMinusOneRateCosmic->Fill(fillstr.c_str(), 1.);
    for (unsigned count=0; count<collMinusOneRateNoise_.at(fill); count++) hCollMinusOneRateNoise->Fill(fillstr.c_str(), 1.);
    for (unsigned count=0; count<collMinusOneRateNoID_.at(fill); count++) hCollMinusOneRateNoID->Fill(fillstr.c_str(), 1.);

    // normalisation histogram - integrate normalisation
    for (int bx=-1000; bx<1000; ++bx) {

      unsigned norm=hRelBXNorm_.histogram(fill)->GetBinContent(bx+1001);

      if (bx == -1) {
	hCollMinusOneRateNorm->Fill(fillstr.c_str(), norm);
      }
      //      else std::cout << "Normalisation for BX=" << bx << " in fill " << fill << " is " << norm << std::endl;
      
    }
  }


  hCollMinusOneRateNorm->Write("",TObject::kOverwrite);
  hCollMinusOneRate->Write("",TObject::kOverwrite);
  hCollMinusOneRateHalo->Write("",TObject::kOverwrite);
  hCollMinusOneRateBG->Write("",TObject::kOverwrite);
  hCollMinusOneRateCosmic->Write("",TObject::kOverwrite);
  hCollMinusOneRateNoise->Write("",TObject::kOverwrite);
  hCollMinusOneRateNoID->Write("",TObject::kOverwrite);


  // near unpaired bunch

  // "base" rate 
  TH1D* hUPBaseRateNorm = new TH1D("hUPBaseRateNorm", "Base rate normalisation", nFills, 0., 0.);
  TH1D* hUPBaseRate = new TH1D("hUPBaseRate", "Base rate - all", nFills, 0., 0.);
  TH1D* hUPBaseRateHalo = new TH1D("hUPBaseRateHalo", "Base rate - halo", nFills, 0., 0.);
  TH1D* hUPBaseRateBG = new TH1D("hUPBaseRateBeamgas", "Base rate - beam gas", nFills, 0., 0.);
  TH1D* hUPBaseRateCosmic = new TH1D("hUPBaseRateCosmic", "Base rate - cosmic", nFills, 0., 0.);
  TH1D* hUPBaseRateNoise = new TH1D("hUPBaseRateNoise", "Base rate - noise", nFills, 0., 0.);
  TH1D* hUPBaseRateNoID = new TH1D("hUPBaseRateNoID", "Base rate - no ID", nFills, 0., 0.);

  sort(fillList_.begin(), fillList_.end());

  for (std::vector<unsigned long>::const_iterator i=fillList_.begin(); i!=fillList_.end(); ++i) {

    unsigned long fill = (*i);
    std::stringstream ss;
    ss << fill;
    std::string fillstr = ss.str();

    hUPBaseRateNorm->Fill(fillstr.c_str(), 0.);
    hUPBaseRate->Fill(fillstr.c_str(), 0.);
    hUPBaseRateHalo->Fill(fillstr.c_str(), 0.);
    hUPBaseRateBG->Fill(fillstr.c_str(), 0.);
    hUPBaseRateCosmic->Fill(fillstr.c_str(), 0.);
    hUPBaseRateNoise->Fill(fillstr.c_str(), 0.);
    hUPBaseRateNoID->Fill(fillstr.c_str(), 0.);

    for (unsigned count=0; count<upBaseRate_.at(fill); count++) hUPBaseRate->Fill(fillstr.c_str(), 1.);
    for (unsigned count=0; count<upBaseRateHalo_.at(fill); count++) hUPBaseRateHalo->Fill(fillstr.c_str(), 1.);
    for (unsigned count=0; count<upBaseRateBG_.at(fill); count++) hUPBaseRateBG->Fill(fillstr.c_str(), 1.);
    for (unsigned count=0; count<upBaseRateCosmic_.at(fill); count++) hUPBaseRateCosmic->Fill(fillstr.c_str(), 1.);
    for (unsigned count=0; count<upBaseRateNoise_.at(fill); count++) hUPBaseRateNoise->Fill(fillstr.c_str(), 1.);
    for (unsigned count=0; count<upBaseRateNoID_.at(fill); count++) hUPBaseRateNoID->Fill(fillstr.c_str(), 1.);

    // normalisation histogram - integrate normalisation
    for (int bx=-1000; bx<1000; ++bx) {

      unsigned norm=hRelUPBunchBXNorm_.histogram(fill)->GetBinContent(bx+1001);

      if (abs(bx)>=5) {
	hUPBaseRateNorm->Fill(fillstr.c_str(), norm);
      }
      //      else std::cout << "Normalisation for BX=" << bx << " in fill " << fill << " is " << norm << std::endl;
      
    }
  }

  // "minus one" rate 
  hUPBaseRateNorm->Write("",TObject::kOverwrite);
  hUPBaseRate->Write("",TObject::kOverwrite);
  hUPBaseRateHalo->Write("",TObject::kOverwrite);
  hUPBaseRateBG->Write("",TObject::kOverwrite);
  hUPBaseRateCosmic->Write("",TObject::kOverwrite);
  hUPBaseRateNoise->Write("",TObject::kOverwrite);
  hUPBaseRateNoID->Write("",TObject::kOverwrite);

  TH1D* hUPMinusOneRateNorm = new TH1D("hUPMinusOneRateNorm", "Up-1 rate normalisation", nFills, 0., 0.);
  TH1D* hUPMinusOneRate = new TH1D("hUPMinusOneRate", "Up-1 rate - all", nFills, 0., 0.);
  TH1D* hUPMinusOneRateHalo = new TH1D("hUPMinusOneRateHalo", "Up-1 rate - halo", nFills, 0., 0.);
  TH1D* hUPMinusOneRateBG = new TH1D("hUPMinusOneRateBeamgas", "Up-1 rate - beam gas", nFills, 0., 0.);
  TH1D* hUPMinusOneRateCosmic = new TH1D("hUPMinusOneRateCosmic", "Up-1 rate - cosmic", nFills, 0., 0.);
  TH1D* hUPMinusOneRateNoise = new TH1D("hUPMinusOneRateNoise", "Up-1 rate - noise", nFills, 0., 0.);
  TH1D* hUPMinusOneRateNoID = new TH1D("hUPMinusOneRateNoID", "Up-1 rate - no ID", nFills, 0., 0.);

  sort(fillList_.begin(), fillList_.end());

  for (std::vector<unsigned long>::const_iterator i=fillList_.begin(); i!=fillList_.end(); ++i) {

    unsigned long fill = (*i);
    std::stringstream ss;
    ss << fill;
    std::string fillstr = ss.str();

    hUPMinusOneRateNorm->Fill(fillstr.c_str(), 0.);
    hUPMinusOneRate->Fill(fillstr.c_str(), 0.);
    hUPMinusOneRateHalo->Fill(fillstr.c_str(), 0.);
    hUPMinusOneRateBG->Fill(fillstr.c_str(), 0.);
    hUPMinusOneRateCosmic->Fill(fillstr.c_str(), 0.);
    hUPMinusOneRateNoise->Fill(fillstr.c_str(), 0.);
    hUPMinusOneRateNoID->Fill(fillstr.c_str(), 0.);

    for (unsigned count=0; count<upMinusOneRate_.at(fill); count++) hUPMinusOneRate->Fill(fillstr.c_str(), 1.);
    for (unsigned count=0; count<upMinusOneRateHalo_.at(fill); count++) hUPMinusOneRateHalo->Fill(fillstr.c_str(), 1.);
    for (unsigned count=0; count<upMinusOneRateBG_.at(fill); count++) hUPMinusOneRateBG->Fill(fillstr.c_str(), 1.);
    for (unsigned count=0; count<upMinusOneRateCosmic_.at(fill); count++) hUPMinusOneRateCosmic->Fill(fillstr.c_str(), 1.);
    for (unsigned count=0; count<upMinusOneRateNoise_.at(fill); count++) hUPMinusOneRateNoise->Fill(fillstr.c_str(), 1.);
    for (unsigned count=0; count<upMinusOneRateNoID_.at(fill); count++) hUPMinusOneRateNoID->Fill(fillstr.c_str(), 1.);

    // normalisation histogram - integrate normalisation
    for (int bx=-1000; bx<1000; ++bx) {

      unsigned norm=hRelUPBunchBXNorm_.histogram(fill)->GetBinContent(bx+1001);

      if (bx == -1) {
	hUPMinusOneRateNorm->Fill(fillstr.c_str(), norm);
      }
      //      else std::cout << "Normalisation for BX=" << bx << " in fill " << fill << " is " << norm << std::endl;
      
    }
  }


  hUPMinusOneRateNorm->Write("",TObject::kOverwrite);
  hUPMinusOneRate->Write("",TObject::kOverwrite);
  hUPMinusOneRateHalo->Write("",TObject::kOverwrite);
  hUPMinusOneRateBG->Write("",TObject::kOverwrite);
  hUPMinusOneRateCosmic->Write("",TObject::kOverwrite);
  hUPMinusOneRateNoise->Write("",TObject::kOverwrite);
  hUPMinusOneRateNoID->Write("",TObject::kOverwrite);

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
