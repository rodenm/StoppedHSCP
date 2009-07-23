#include "StoppedHSCP/Analysis/interface/StoppedHSCPEvent.h"

//#include "StoppedHSCP/Analysis/interface/StoppedHSCPJet.h"

using namespace shscp;

StoppedHSCPEvent::StoppedHSCPEvent() :
  nMCDecays(0),
  nJets(0),
  nMuons(0),
  nTowers(0),
  nHpds(0),
  nDigis(0)
{ 
}

StoppedHSCPEvent::~StoppedHSCPEvent() { }

void StoppedHSCPEvent::setEventInfo(unsigned e,
				    unsigned b,
				    unsigned o,
				    unsigned ls,
				    unsigned r,
				    unsigned f,
				    unsigned ts) {
  event.id = e;
  event.bx = b;
  event.orbit = o;
  event.lumisection = ls;
  event.run = r;
  event.fill = f;
  event.timestamp = ts;
}

void StoppedHSCPEvent::setTriggerInfo(double l1JetEt,
				      double l1JetEta,
				      double l1JetPhi,
				      double l1BptxPlus,
				      double l1BptxMinus,
				      double hltJetE,
				      double hltJetEta,
				      double hltJetPhi) {
  trigger.l1JetEt = l1JetEt;
  trigger.l1JetEta = l1JetEta;
  trigger.l1JetPhi = l1JetPhi;
  trigger.l1BptxPlus = l1BptxPlus;
  trigger.l1BptxMinus = l1BptxMinus;
  trigger.hltJetEt = l1BptxMinus;
  trigger.hltJetEta = hltJetEta;
  trigger.hltJetPhi = hltJetPhi;
}


void StoppedHSCPEvent::setMC(MC mcEvt) {
  mc = mcEvt;
}


void StoppedHSCPEvent::addMCDecay(MCDecay d) { 
  if (nMCDecays < MAX_N_MCDECAYS) {
    mcDecays[nMCDecays] = d;
    ++nMCDecays;
  }
}


void StoppedHSCPEvent::addJet(Jet j) {
  if (nJets < MAX_N_JETS) {
    jets[nJets] = j;
    ++nJets;
  }
}


void StoppedHSCPEvent::addMuon(Muon m) { 
  if (nMuons < MAX_N_MUONS) {
    muons[nMuons] = m;
    ++nMuons;
  }
}


void StoppedHSCPEvent::addTower(Tower t) {
  if (nTowers < MAX_N_TOWERS) {
    towers[nTowers] = t;
    ++nTowers;
  }
}


void StoppedHSCPEvent::addHPD(HPD h) {
  if (nHpds < MAX_N_HPDS) {
    hpds[nHpds] = h;
    ++nHpds;
  } 
}


void StoppedHSCPEvent::addDigi(HcalDigi d) {
  if (nDigis < MAX_N_DIGIS) {
    digis[nDigis] = d;
    ++nDigis;
  } 
}

#if !defined(__CINT__)
  ClassImp(StoppedHSCPEvent)
#endif
