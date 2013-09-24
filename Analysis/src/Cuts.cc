#include "StoppedHSCP/Analysis/interface/Cuts.h"

#include "StoppedHSCP/Ntuples/interface/StoppedHSCPEvent.h"
#include "StoppedHSCP/Ntuples/interface/LhcFills.h"
#include "StoppedHSCP/Analysis/interface/BadRuns.h"

#include "TMath.h"

#include <iostream>
#include <fstream>
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>
#include <math.h>

#define CALL_MEMBER_FN(object,ptrToMember)  ((object).*(ptrToMember))


Cuts::Cuts(StoppedHSCPEvent* event,
	   bool isMC,
	   unsigned version,
	   LhcFills* fills) :
  event_(event),
  isMC_(isMC),
  version_(version),
  fills_(fills)
{

  // set up cuts

  // default
  if (version_ == 0) {
    addCut(&Cuts::triggerCut, "trigger");      // 0
    addCut(&Cuts::bptxVeto, "BPTX veto");      // 1
    addCut(&Cuts::bxVeto, "BX veto");          // 2
    addCut(&Cuts::vertexVeto, "Vertex veto");  // 3
    addCut(&Cuts::haloVeto, "Halo veto");      // 4
    addCut(&Cuts::cosmicVeto2, "Cosmic veto");  // 5
    addCut(&Cuts::hcalNoiseVeto, "Noise veto");// 6
    addCut(&Cuts::looseJetCut, "E30");         // 7
    addCut(&Cuts::jetEnergyCut, "E70");        // 8
    addCut(&Cuts::jetN60Cut, "n60");           // 9
    addCut(&Cuts::jetN90Cut, "n90");           // 10
    addCut(&Cuts::towersIPhiCut, "nTowiPhi");  // 11
    addCut(&Cuts::iPhiFractionCut, "iPhiFrac");// 12
    addCut(&Cuts::hpdR1Cut, "R1");             // 13
    addCut(&Cuts::hpdR2Cut, "R2");             // 14
    addCut(&Cuts::hpdRPeakCut, "Rpeak");       // 15
    addCut(&Cuts::hpdROuterCut, "Router");     // 16
  }

  // digi-based timing cuts
  if (version_ == 1) {
    addCut(&Cuts::trigger2010Cut, "trigger");
    addCut(&Cuts::bptxVeto, "BPTX veto");
    addCut(&Cuts::bxVeto, "BX veto");
    addCut(&Cuts::vertexVeto, "Vertex veto");
    addCut(&Cuts::haloVeto, "Halo veto");
    addCut(&Cuts::cosmicVeto3, "Cosmic veto");
    addCut(&Cuts::hcalNoiseVeto, "Noise veto");
    addCut(&Cuts::looseJetCut, "E30");
    addCut(&Cuts::jetEnergyCut, "E70");
    addCut(&Cuts::jetN60Cut, "n60");
    addCut(&Cuts::jetN90Cut, "n90");
    addCut(&Cuts::towersIPhiCut, "nTowiPhi");
    addCut(&Cuts::iPhiFractionCut, "iPhiFrac");
    addCut(&Cuts::digiR1Cut, "R1 digi");
    addCut(&Cuts::digiR2Cut, "R2 digi");
    addCut(&Cuts::digiRPeakCut, "Rpeak digi");
    addCut(&Cuts::digiROuterCut, "Router digi");
  }

  // use corrected jet Et
  if (version_ == 2) {
    addCut(&Cuts::triggerCut, "trigger");      // 0
    addCut(&Cuts::bptxVeto, "BPTX veto");      // 1
    addCut(&Cuts::bxVeto, "BX veto");          // 2
    addCut(&Cuts::vertexVeto, "Vertex veto");  // 3
    addCut(&Cuts::haloVeto, "Halo veto");      // 4
    addCut(&Cuts::cosmicVeto, "Cosmic veto");  // 5
    addCut(&Cuts::hcalNoiseVeto, "Noise veto");// 6
    addCut(&Cuts::looseJetCorrCut, "E30");     // 7
    addCut(&Cuts::jetEnergyCorrCut, "E70");    // 8
    addCut(&Cuts::jetN60Cut, "n60");           // 9
    addCut(&Cuts::jetN90Cut, "n90");           // 10
    addCut(&Cuts::towersIPhiCut, "nTowiPhi");  // 11
    addCut(&Cuts::iPhiFractionCut, "iPhiFrac");// 12
    addCut(&Cuts::hpdR1Cut, "R1");             // 13
    addCut(&Cuts::hpdR2Cut, "R2");             // 14
    addCut(&Cuts::hpdRPeakCut, "Rpeak");       // 15
    addCut(&Cuts::hpdROuterCut, "Router");     // 16
  }

}

Cuts::~Cuts() {

}


  





bool Cuts::triggerCut() const {      // require event passed main trigger

  //  bool trigBX = 

  bool trigger = false;

  // Skip bad fills and runs; uses method from BadRuns.cc
  if (isBadFillOrRun(event_->fill,event_->run)) return false;

  //0) MC should use the main 2012 signal trigger
  if (isMC_)
    trigger = event_->hltJetE50NoBptx3BXNoHalo;

  //1) in Run2010A, require hltJetNoBptx only
  else if (event_->fill<1711)
    trigger = event_->hltJetNoBptx;// && abs(event_->bxWrtBunch) > 1;

  //2) in Run2011A, before tech stop (fills 1711-1749) require hltJetNoBptx3BXNoHalo only
  else if (event_->fill<1750)
    trigger = event_->hltJetNoBptx3BXNoHalo;

  //3) in Run2011A, post tech stop (fills 1795 onwards) require hltJetE50NoBptx3BXNoHalo only
  else if (event_->fill>=1795)
    trigger = event_->hltJetE50NoBptx3BXNoHalo;

  //4) Starting in 2012, higher threshold trigger
  else if (event_->fill>2351)
    trigger = event_->hltJetE50NoBptx3BXNoHalo;

  return trigger;

}

bool Cuts::trigger2010Cut() const {  // require event passed main trigger
  return true;//event_->hltJetNoBptx;
}

bool Cuts::controlTrigger() const {  // event fired control trigger
  return event_->hltJetNoBptx;
}

bool Cuts::bptxVeto() const {        // cut on time wrt BPTX signal
  return true;
}

bool Cuts::bxVeto() const {          // cut on BX wrt expected collisions
  //return isMC_ || !(fills_->getMaskFromRun(event_->run).at(event_->bx));
  //return isMC_ || abs(fills_->getBxWrtBunch(event_->fill, event_->bx)) > 2;

  return isMC_ || (abs(fills_->getBxWrtBunch(event_->fill, event_->bx)) > 1);


}

bool Cuts::vertexVeto() const {      // no vertex
  return (event_->nVtx == 0);
}

bool Cuts::haloVeto() const {        // no halo ID
  //return !(event_->beamHalo_CSCLoose) ;//&& geometryHaloCut();

  return (event_->cscSeg_N == 0);


}

bool Cuts::hfVeto() const {
  return event_->hfPlusTotalE < 50. && event_->hfMinusTotalE < 50.;
}

bool Cuts::trackVeto() const {
  return (event_->track_N == 0);
}

bool Cuts::cosmicVeto() const {      // no cosmic muon
  return (event_->mu_N==0);
  //return true;
  /**
  unsigned nCloseRPCPairs = 0;
  for (unsigned irpc = 0; irpc < event_->rpcHit_N; irpc++) {
    for (unsigned jrpc = irpc+1; jrpc < event_->rpcHit_N; jrpc++) {
      double deltaZ = fabs(event_->rpcHitZ[irpc] - event_->rpcHitZ[jrpc]);
      double deltaPhi = acos(cos(event_->rpcHitPhi[irpc] - event_->rpcHitPhi[jrpc]));
      
      // Require hits to be localized in z or in phi
      if (deltaZ < 40.0 || deltaPhi < 0.2 || deltaPhi > TMath::Pi()/2.) {
	nCloseRPCPairs++;
      }
    }
  }
  return (nCloseRPCPairs < 2);
  */
}

bool Cuts::cosmicVeto2() const {      // Cosmic cut from 2011 analysis
  //return (event_->DTSegment_N < 3);
  
  // TODO: calculate relevant variables first, and then write cuts succinctly 

  // count # of DTs outside the innermost DT cylinder
  double outerDT = 0.000001; // avoid divide by zero
  int innerDT = 0;

  double testPhi;
  double maxDeltaPhi = -1.;
  double maxDeltaJetPhi = -1.;
  for (unsigned idt = 0; idt<event_->DTSegment_N; idt++){
    if (idt == 0) {
      testPhi = event_->DTSegPhi[0];
      //std::cout <<"dts...";
    } else {
      double deltaphi = acos(cos(event_->DTSegPhi[idt] - testPhi));
      if (deltaphi > maxDeltaPhi) maxDeltaPhi = deltaphi;
    }
    if (event_->DTSegR[idt] > 560) outerDT++;
    else innerDT++;
    if (event_->jet_N > 0) {
      double deltajetphi = acos(cos(event_->DTSegPhi[idt] - event_->jetPhi[0]));
      if (deltajetphi > maxDeltaJetPhi) maxDeltaJetPhi = deltajetphi;
    }
  }
  //std::cout << "frac...";

  double frac = innerDT/outerDT;
  //std::cout << "rpcs...";

  double outerRPC = 0.00000001;
  double innerRPC = 0;
  double maxRPCDeltaPhi = -1.;
  double maxRPCDeltaJetPhi = -1.;
  unsigned nCloseRPCPairs = 0;
  for (unsigned irpc = 0; irpc < event_->rpcHit_N; irpc++) {
    if (irpc == 0) {
      testPhi = event_->rpcHitPhi[0];
      //std::cout <<"test rpc...";
    } else {
      double deltaphi = acos(cos(event_->rpcHitPhi[irpc] - testPhi));
      if (deltaphi > maxRPCDeltaPhi) maxRPCDeltaPhi = deltaphi;
      //std::cout << "compare rpcs...";
    }
    if (event_->jet_N > 0) {
      double deltajetphi = acos(cos(event_->rpcHitPhi[irpc] - event_->jetPhi[0]));
      if (deltajetphi > maxRPCDeltaJetPhi) maxRPCDeltaJetPhi = deltajetphi;
    }
    if (event_->rpcHitR[irpc] > 560) outerRPC++;
    else innerRPC++;
  
  
    //std::cout << "logic..." << std::endl;
  
    if (event_->rpcHitR[irpc] < 385) continue;
    for (unsigned jrpc = irpc+1; jrpc < event_->rpcHit_N; jrpc++) {
      if (event_->rpcHitR[jrpc] < 385) continue;
      double deltaZ = fabs(event_->rpcHitZ[irpc] - event_->rpcHitZ[jrpc]);
      double deltaPhi = acos(cos(event_->rpcHitPhi[irpc] - event_->rpcHitPhi[jrpc]));
      
      // Require hits to be localized in z or in phi
      if (deltaPhi > TMath::Pi()/2.) { //  || deltaPhi < 0.2
	nCloseRPCPairs++;
      }
    }
  }
  
  //******************* Cut logic starts here *******************/
  /**
  if (event_->DTSegment_N > 1 || event_->rpcHit_N > 2) { // require min muon activity
    // cosmic if DT hits are separated in phi
    if (maxDeltaPhi > TMath::Pi()/2.|| maxDeltaJetPhi > 1.1)
      return false;

    // Cosmic if more activity in outer barrel than inner barrel
    return (frac < 2);

    // Cosmic if lots of activity in outer barrel
    if ( outerDT > 3) return false; 
  }

  return true;
  */

  /** Energy dependent:
      - delta(jet, DT)
      - delta (DT, DT)

      There is always at least 1 outer DT hit for cosmic MC events
  */
 
 /******************* Option #2 ******************************/
  
  // cosmic if DT hits are separated in phi
  if (maxDeltaPhi > TMath::Pi()/2. || maxDeltaJetPhi > 1.0)
    return false;

  //if (nCloseRPCPairs > 2.)
  //  return false;

  if (maxRPCDeltaPhi > 2.)
    return false;
    
    // Cosmic if more activity in outer barrel than inner barrel
  if (outerDT >= 1 || outerRPC >= 2)// && frac < 4 )
    return false;

  return true;
}


bool Cuts::cosmicVeto3() const {      // no cosmic muon
  if (event_->DTSegment_N < 3) { 
    unsigned nCloseRPCPairs = 0;
    for (unsigned irpc = 0; irpc < event_->rpcHit_N; irpc++) {
      for (unsigned jrpc = irpc+1; jrpc < event_->rpcHit_N; jrpc++) {
	double deltaZ = fabs(event_->rpcHitZ[irpc] - event_->rpcHitZ[jrpc]);
	double deltaPhi = acos(cos(event_->rpcHitPhi[irpc] - event_->rpcHitPhi[jrpc]));
	
	// Require hits to be localized in z or in phi
	if (deltaZ < 40.0 || deltaPhi < 0.2 || deltaPhi > TMath::Pi()/2.) {
	  nCloseRPCPairs++;
	}
      }
    }
    return (nCloseRPCPairs < 2);
  }
  return (false);
}

bool Cuts::hcalNoiseVeto() const {   // std HCAL noise veto
  //std::cout <<"TRIGDEC:"<<event_->run<<":"<<event_->lb<<":"<<event_->id<<":"<<event_->bx<<":"<<event_->noiseFilterResult<<std::endl;
    
  // veto events where the leading jet is contained in HPDs 52-55
  bool pass = true;
  if (event_->hpd_N > 0) {
    for (unsigned i = 0; i<event_->hpd_N; i++) {
      if (event_->hpdId[i]==52 || event_->hpdId[i]==53 || event_->hpdId[i]==54 || event_->hpdId[i]==55) pass = false;
    }
  }

  return (event_->noiseFilterResult && pass);
  
  //return true;
}

bool Cuts::looseJetCut() const {     // low Et threshold
  return event_->jet_N>0 && event_->jetE[0]>30. && fabs(event_->jetEta[0])<1.3;
}

bool Cuts::jetEnergyCut() const {    // require jet above Et threshold
  // raise jet energy cut to 70, since we're using a 50-GeV trigger?
  return event_->jet_N>0 && event_->jetE[0]>70. && fabs(event_->jetEta[0])<1.;
}

bool Cuts::looseJetCorrCut() const {     // low Et threshold
  return event_->jet_N>0 && event_->jetECorr[0]>45. && fabs(event_->jetEta[0])<1.3;
}

bool Cuts::jetEnergyCorrCut() const {    // require jet above Et threshold
  // raise jet energy cut to 70, since we're using a 50-GeV trigger?
  return event_->jet_N>0 && event_->jetECorr[0]>100. && fabs(event_->jetEta[0])<1.;
}

bool Cuts::jetN60Cut() const {       // jet n60
  //return event_->jet_N>0;// && event_->jetN60[0]<6;
  return true;
}

bool Cuts::jetN90Cut() const {       // jet n90
  return event_->jet_N>0 && event_->jetN90[0]>3;
}

bool Cuts::towersIPhiCut() const {   // cut on N leading towers at same iphi
  return event_->nTowerSameiPhi<5;
}

bool Cuts::iPhiFractionCut() const { // Et fraction at leading iphi
  //return event_->leadingIPhiFraction()<0.95;
  return event_->leadingIPhiFractionValue<0.95;
}

bool Cuts::hpdR1Cut() const {        // timing R1 cut from HPD
  return (event_->topHPD5R1 > 0.15) && (event_->topHPD5R1 <= 1.0);
}

bool Cuts::hpdR2Cut() const {        // timing R2 cut from HPD
  return (event_->topHPD5R2 > 0.1) && (event_->topHPD5R2 < 0.8);
}

bool Cuts::hpdRPeakCut() const {     // timing Rp cut from HPD
  return (event_->topHPD5RPeak > 0.3) && (event_->topHPD5RPeak < 0.7) && (event_->topHPD5PeakSample > 0) && (event_->topHPD5PeakSample < 7);
}

bool Cuts::hpdROuterCut() const {    // timing Ro cut from HPD
  return (event_->topHPD5ROuter < 0.3) && (event_->topHPD5ROuter >= 0.0) && (event_->topHPD5PeakSample > 0) && (event_->topHPD5PeakSample < 7);
}

bool Cuts::digiR1Cut() const {       // timing R1 cut from digis
  return (event_->top5DigiR1 > 0.15) && (event_->top5DigiR1 <= 1.0);
}

bool Cuts::digiR2Cut() const {       // timing R2 cut from digis
  return (event_->top5DigiR2 > 0.1) && (event_->top5DigiR2 < 0.5);
}

bool Cuts::digiRPeakCut() const {    // timing Rp cut from digis
  return (event_->top5DigiRPeak > 0.4) && (event_->top5DigiRPeak < 0.7) && (event_->top5DigiPeakSample > 0) && (event_->top5DigiPeakSample < 7);
}

bool Cuts::digiROuterCut() const {   // timing Ro cut from digis
  return (event_->top5DigiROuter < 0.1) && (event_->top5DigiROuter >= 0.0) && (event_->top5DigiPeakSample > 0) && (event_->top5DigiPeakSample < 7);
}

bool Cuts::geometryHaloCut() const {
  if (event_->cscSeg_N == 0) return true;

  for (unsigned int i = 0; i < event_->cscSeg_N; i++) {
    if (event_->cscSegDirTheta[i] < 0.4 || event_->cscSegDirTheta[i] > 2.74){
      Double_t r = event_->cscSegR[i];
      Double_t phi = event_->cscSegPhi[i];

      for (unsigned int j = i; j < event_->cscSeg_N; j++) {
	if (fabs(r - event_->cscSegR[j]) < 20.0 &&
	    fabs(phi - event_->cscSegPhi[j]) < 0.2) 
	  return false;
      }
    }
  }

  return true;
}

// setup method
void Cuts::addCut(Cuts::CutFn fn, std::string name) {
  cuts_.push_back(fn);
  names_.push_back(name);
}


bool Cuts::cutN(unsigned n) const { 
  return CALL_MEMBER_FN(*this, cuts_.at(n))(); 
}

// Returns true if all cuts up to and including n are passed; returns false otherwise
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


// returns combined result of all cuts EXCEPT those specified in 'some' vector
bool Cuts::cutNMinusSome(std::vector<unsigned int> some) const {

  bool pass=true;
  for (unsigned i=0; i<nCuts(); ++i) 
    {
      bool checkthiscut=true;
      for (unsigned int n=0;n<some.size();++n) // loop over cuts to be excluded
	{
	  if (i==some[n]) // current cut should be excluded; set 'checkthiscut' to false
	    {
	      checkthiscut=false;
	      break;
	    }
	}
      // pass = boolean AND of all cuts to be checked
      if (checkthiscut==true) pass = pass && cutN(i);
    }
  return pass;

}


// return result of a particular cut, after smearing for systematics
// TRUE means the event passed the cuts, wasn't vetoed
bool Cuts::cutNSyst(unsigned n, double smear) const 
{

  switch (n) {
  case 7:
    if (event_->jet_N>0  && fabs(event_->jetEta[0])<1.3) {
      double jetE_syst = event_->jetE[0] * smear;
      return jetE_syst>30.;
    }
    else return false;
  case 8:
    if (event_->jet_N>0  && fabs(event_->jetEta[0])<1.0) {
      double jetE_syst = event_->jetE[0] * smear;
      
      //if (cutN(8) != (jetE_syst>70.) && smear > 1.0) {
      //std::cout << names_.at(n).c_str() << "\t"
      //	  << event_->jetE[0] << "\t" 
      //	  << event_->jetEta[0] << "\t"
      //	  << cutN(8) << "\t"
      //	  << smear << "\t"
      //	  << jetE_syst << "\t" 
      //	  << (jetE_syst > 70.) << std::endl;
      //}
      return jetE_syst>70.;
    }
    else return false;
  default:
    return cutN(n);
  }
  
}
 

void Cuts::print(std::ostream& os) const {

  os << "Cuts : version " << version_ << std::endl;
  for (unsigned i=0; i<cuts_.size(); ++i) {
    os << "  " << i << " : " << names_.at(i) << std::endl;
  }

}
