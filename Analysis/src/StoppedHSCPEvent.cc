#include "StoppedHSCP/Analysis/interface/StoppedHSCPEvent.h"

//#include "StoppedHSCP/Analysis/interface/StoppedHSCPJet.h"

using namespace shscp;

StoppedHSCPEvent::StoppedHSCPEvent() :
  nL1Jet(0),
  nHltJet(0),
  nMCDecay(0),
  nJet(0),
  nMuon(0),
  nTower(0),
  nHpd(0),
  nDigi(0)
{ 
}

StoppedHSCPEvent::~StoppedHSCPEvent() { }

void StoppedHSCPEvent::setEventInfo(unsigned evt,
				    unsigned bx,
				    unsigned orbit,
				    unsigned ls,
				    unsigned run,
				    unsigned fill,
				    unsigned ts0,
				    unsigned ts1) {
  event.id = evt;
  event.bx = bx;
  event.orbit = orbit;
  event.lumisection = ls;
  event.run = run;
  event.fill = fill;
  event.time0 = ts0;
  event.time0 = ts1;
}

void StoppedHSCPEvent::setTriggerInfo(unsigned gtTrigWord0,
				      unsigned gtTrigWord1,
				      unsigned l1BptxPlus,
				      unsigned l1BptxMinus,
				      unsigned hltBit) {
  trigger.gtTrigWord0 = gtTrigWord0;
  trigger.gtTrigWord1 = gtTrigWord1;
  trigger.l1BptxPlus = l1BptxPlus;
  trigger.l1BptxMinus = l1BptxMinus;
  trigger.hltBit = hltBit;
}


void StoppedHSCPEvent::setMC(MC mcEvt) {
  mc = mcEvt;
}


void StoppedHSCPEvent::addMCDecay(MCDecay d) { 
  if (nMCDecay < MAX_N_MCDECAYS) {
    mcDecays[nMCDecay] = d;
    ++nMCDecay;
  }
}


void StoppedHSCPEvent::addL1Jet(TrigJet j) {
  if (nL1Jet < MAX_N_TRIGJETS) {
    l1Jets[nL1Jet] = j;
    ++nL1Jet;
  }
}


void StoppedHSCPEvent::addHltJet(TrigJet j) {
  if (nHltJet < MAX_N_TRIGJETS) {
    hltJets[nHltJet] = j;
    ++nHltJet;
  }
}


void StoppedHSCPEvent::addJet(Jet j) {
  if (nJet < MAX_N_JETS) {
    jets[nJet] = j;
    ++nJet;
  }
}


void StoppedHSCPEvent::addMuon(Muon m) { 
  if (nMuon < MAX_N_MUONS) {
    muons[nMuon] = m;
    ++nMuon;
  }
}


void StoppedHSCPEvent::addTower(Tower t) {
  if (nTower < MAX_N_TOWERS) {
    towers[nTower] = t;
    ++nTower;
  }
}


void StoppedHSCPEvent::addHPD(HPD h) {
  if (nHpd < MAX_N_HPDS) {
    hpds[nHpd] = h;
    ++nHpd;
  } 
}


void StoppedHSCPEvent::addDigi(HcalDigi d) {
  if (nDigi < MAX_N_DIGIS) {
    digis[nDigi] = d;
    ++nDigi;
  } 
}

shscp::TrigJet StoppedHSCPEvent::getL1Jet(unsigned i) {
 if (i < nL1Jet) return l1Jets[i]; 
 else return shscp::TrigJet();
}

shscp::TrigJet StoppedHSCPEvent::getHltJet(unsigned i) {
 if (i < nHltJet) return hltJets[i]; 
 else return shscp::TrigJet();
}

shscp::MCDecay StoppedHSCPEvent::getMCDecay(unsigned i) {
 if (i < nMCDecay) return mcDecays[i]; 
 else return shscp::MCDecay();
}

shscp::Jet StoppedHSCPEvent::getJet(unsigned i) { 
  if (i < nJet) return jets[i];
  else return shscp::Jet();
}

shscp::Muon StoppedHSCPEvent::getMuon(unsigned i) { 
  if (i < nMuon) return muons[i]; 
  else return shscp::Muon();
}

shscp::Tower StoppedHSCPEvent::getTower(unsigned i) {
  if (i < nTower) return towers[i]; 
  else return shscp::Tower();
}


shscp::HPD StoppedHSCPEvent::getHPD(unsigned i) { 
  if (i < nHpd) return hpds[i]; 
  else return shscp::HPD();
}

shscp::HcalDigi StoppedHSCPEvent::getDigi(unsigned i) { 
  if (i < nDigi) return digis[i]; 
  else return shscp::HcalDigi();
}


#if !defined(__CINT__)
  ClassImp(StoppedHSCPEvent)
#endif
