#include "StoppedHSCP/Analysis/interface/Cuts.h"

#include "StoppedHSCP/Analysis/interface/StoppedHSCPEvent.h"


#include <iostream>
#include <fstream>
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>


Cuts::Cuts(StoppedHSCPEvent* event, bool isMC) :
  event_(event),
  isMC_(isMC),
  bxMask_(3564, false)
{

}

Cuts::~Cuts() {

}


void Cuts::readMaskedBXs(std::string filename, unsigned run) {

  bxMask_.clear();

  // open file
  std::ifstream bxfile(filename.c_str(), ifstream::in);

  // read lines until we find the current run
  std::string line;
  if (!bxfile.fail()) {
    while (!bxfile.eof()) {
      getline(bxfile, line);
      std::vector<std::string> strs;
      boost::split(strs, line, boost::is_any_of(","));
      
      if (run==(unsigned)atoi(strs.at(0).c_str())) {
	
	// read BXs to mask from the rest of the line
	std::cout << "Ignoring BX : ";
	for (unsigned i=1; i<strs.size(); ++i) {
	  int bx = atoi(strs.at(i).c_str());
	  if (bx>=0 && bx<3546) bxMask_.at(bx) = true;
	  std::cout << strs.at(i) << " ";
	}
	std::cout << std::endl;
      }
    }
  }

}


void Cuts::setMaskedBXs(std::vector<bool> bxMask) {
  bxMask_ = bxMask;
}


bool Cuts::inMaskedBX() const {
  return bxMask_.at(event_->bx); 
}


unsigned Cuts::nCuts() const {
  return 16;
}


// return result of a particular cut
bool Cuts::cutN(unsigned n) const 
{
  
  switch (n) {
  case 0:  // trigger
    return !isMC_ || ((((event_->gtAlgoWord0>>16)&1) == 1) && (event_->hltJet_N>0) && (event_->hltJetE[0]> 20.) && (event_->hltJetEta[0]<1.3));
  case 1:  // BX mask
    return isMC_ || ! bxMask_.at(event_->bx);
  case 2:  // BPTX
    return isMC_ || ((event_->gtAlgoWord1>>(81-64)&1) == 0 && (event_->gtAlgoWord1>>(80-64)&1) == 0);
  case 3:  // vertex veto
    return (event_->nVtx == 0);
  case 4:  // beam halo
    return !(event_->beamHalo_CSCLoose);
  case 5:  // cosmic veto
    return event_->mu_N==0;
  case 6:  // std HCAL cuts
    return event_->noiseFilterResult;
  case 7:  // jet 30 
    return event_->jet_N>0 && event_->jetE[0]>30. && event_->jetEta[0]<1.3;
  case 8:  // jet 50
    return event_->jet_N>0 && event_->jetE[0]>50. && event_->jetEta[0]<1.3;
  case 9:  // jet n60
    return event_->jet_N>0 && event_->jetN60[0]<6;
  case 10:  // jet n90
    return event_->jet_N>0 && event_->jetN90[0]>3;
  case 11:  // calo towers
    //    return event_->nTowerSameiPhi<5;
    return event_->nTowerSameiPhi<5 && leadingIPhiFraction()<0.95;
    //return jetCaloTowers()<5;
    //return event_->nTowerSameiPhi<5 && jetCaloTowers()<5;
  case 12: // R1
    return (event_->top5DigiR1 > 0.15) && (event_->top5DigiR1 <= 1.0);
  case 13: // R2
    return (event_->top5DigiR2 > 0.1) && (event_->top5DigiR2 < 0.5);
  case 14: // Rpeak
    return (event_->top5DigiRPeak > 0.4) && (event_->top5DigiRPeak < 0.7) && (event_->top5DigiPeakSample > 0) && (event_->top5DigiPeakSample < 7);
  case 15: // Router
    return (event_->top5DigiROuter < 0.1) && (event_->top5DigiROuter >= 0.0) && (event_->top5DigiPeakSample > 0) && (event_->top5DigiPeakSample < 7);
    //  case 13:
    //    return event_->jet_N>0 && (event_->jetEEm[0] / event_->jetE[0]) > 0.05;
    //  case 16:
    //    return leadingIPhiFraction()<0.95;
    //    return jetCaloTowers()<5;
  default:
    return true;
    
  }

}


const std::string Cuts::cutName(unsigned n) const {
  
  switch (n) {
  case 0:
    return "HLT";
  case 1:
    return "BX cut";
  case 2:
    return "BPTX cut";
  case 3:
    return "Vertex veto";
  case 4:
    return "Beam halo veto";
  case 5:
    return "mu veto";
  case 6:
    return "Noise filter";
  case 7:
    return "Jet30";
  case 8:
    return "Jet50";
  case 9:
    return "n60";
  case 10:
    return "n90";
  case 11:
    return "Calo towers";
  case 12:
    return "R1";
  case 13:
    return "R2";
  case 14:
    return "Rpeak";
  case 15:
    return "Router";
  case 16:
    return "iphi fraction";
//   case 15:
//     return "jet EMF";
  default:
    return "unknown";
  }

}


bool Cuts::allCutN(unsigned n) const 
{
  bool pass=true;
  for (unsigned i=0; i<n+1; ++i) {
    pass &= cutN(i);
  }
  return pass;
}


// return result of all cuts
bool Cuts::cut() const 
{
  bool pass=true;
  for (unsigned i=0; i<nCuts(); ++i) {
    pass &= cutN(i);
  }
  return pass;
}


// return result of all cuts APART FROM the one specified
bool Cuts::cutNMinusOne(unsigned n) const {

  bool pass=true;
  for (unsigned i=0; i<nCuts(); ++i) {
    if (i!=n) pass = pass && cutN(i);
  }
  return pass;

}


// return result of a particular cut, after smearing for systematics
bool Cuts::cutNSyst(unsigned n, double smear) const 
{

  switch (n) {
  case 4:
    if (event_->jet_N>0  && event_->jetEta[0]<1.3) {
      double jetE_syst = event_->jetE[0] * smear;
      return jetE_syst>30.;
    }
    else return false;
  case 5:
    if (event_->jet_N>0  && event_->jetEta[0]<1.3) {
      double jetE_syst = event_->jetE[0] * smear;
      return jetE_syst>50.;
    }
    else return false;
  default:
    return cutN(n);
  }
  
}


// n HCAL std noise cuts
unsigned Cuts::nHcalCuts() const {
  return 12;
}


// return result of a particular cut 
bool Cuts::stdHcalCutN(unsigned n) const 
{
  
  switch (n) {
  case 0:
    return true;
    break;
  case 1:
    return event_->jet_N>0 && event_->jetE[0]>50. && event_->jetEta[0]<1.3;
    break;
  case 2:
    return event_->mu_N==0;
    break;
  case 3:
    return !(event_->noiseMinE2Over10TS < 0.70);
    break;
  case 4:
    return !(event_->noiseMaxE2Over10TS > 0.96);
    break;
  case 5:
    return !(event_->noiseMaxHPDHits >= 17);
    break;
  case 6:
    return !(event_->noiseMaxRBXHits >= 999);
    break;
  case 7:
    return !(event_->noiseMaxHPDNoOtherHits >= 10);
    break;
  case 8:
    return !(event_->noiseMaxZeros >= 10);
    break;
  case 9:
    return !(event_->noiseMin25GeVHitTime < -9999.0);
    break;
  case 10:
    return !(event_->noiseMax25GeVHitTime > 9999.0);
    break;
  case 11:
    return !(event_->noiseMinRBXEMF < 0.01);
    break;
  default:
    return false;
    break; 
  }

}


// energy fraction at same iphi
double Cuts::leadingIPhiFraction() const {

    std::vector<double> tmp(75, 0);
    for (unsigned i=0; i<event_->tower_N; ++i) {
      tmp.at(event_->towerIPhi.at(i)) += event_->towerE.at(i);
    }
    std::vector<double>::iterator max=max_element(tmp.begin(), tmp.end());

    double frac=0.;
    if (event_->jet_N>0) frac = (*max)/event_->jetE.at(0);
    return frac;

}


unsigned Cuts::jetCaloTowers() const {

  std::vector<Tower> towers;
  for (unsigned i=0; i<event_->tower_N; ++i) {
    if (event_->towerNJet.at(i)==0) {
      Tower t;
      t.iphi=event_->towerIPhi.at(i);
      t.e = event_->towerE.at(i);
      towers.push_back(t);
    }
  }

  sort(towers.begin(), towers.end(), tow_gt());

  unsigned tmp=0;

  if (towers.size() > 0) {
    unsigned iphiFirst=towers.at(0).iphi;
    bool keepgoing=true;
    for (unsigned i=0; i<towers.size() && keepgoing; ++i) {
      if (towers.at(i).iphi==iphiFirst) tmp++;
      else keepgoing=false;
    }
  }

  return tmp;

}
