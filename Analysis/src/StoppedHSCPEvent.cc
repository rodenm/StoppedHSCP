#include "StoppedHSCP/Analysis/interface/StoppedHSCPEvent.h"

#include <iostream>

using namespace shscp;

StoppedHSCPEvent::StoppedHSCPEvent() :
  id(0),
  bx(0),
  orbit(0),
  lb(0),
  run(0),
  fill(0),
  time(0), // timestamp from EvF
  time2(0),  // calculated from run start + L1 counters for LS, orbit, BX
  time3(0),  // timestamp from LHC info in L1 data
  gtAlgoWord0(0),
  gtAlgoWord1(0),
  gtTechWord(0),
  hltBit(false),
  vtxX(0.),
  vtxY(0.),
  vtxZ(0.),
  vtxR(0.),
  vtxT(0.),
  rHadPdgId(0),
  rHadE(0.),
  rHadPx(0.),
  rHadPy(0.),
  rHadPz(0.),
  rHadPt(0.),
  nTowerSameiPhi(0),
  nL1Jet(0),
//   l1jetType(0),
//   l1jetE(0),
//   l1jetEt(0),
//   l1jetEta(0),
//   l1jetPhi(0),
  nHltJet(0),
  nMCDecay(0),
  nJet(0),
  nMuon(0),
  nTower(0),
  nHpd(0),
  nDigi(0),
  leadingDigiIEta(-999),
  leadingDigiIPhi(-999),
  leadingDigiTimeSamples(10),
  leadingDigiPeakSample(0),
  leadingDigiTotal(-999.),
  leadingDigiR1(-999.),
  leadingDigiR2(-999.),
  leadingDigiRPeak(-999.),
  leadingDigiROuter(-999.),
  top5DigiTimeSamples(10),
  top5DigiPeakSample(0),
  top5DigiTotal(-999.),
  top5DigiR1(-999.),
  top5DigiR2(-999.),
  top5DigiRPeak(-999.),
  top5DigiROuter(-999.) 
{
  
  for (int k=0; k<10; ++k) { 
    leadingDigiTimeSamples.at(k)=0.;
    top5DigiTimeSamples.at(k)=0.; 
  }

}

StoppedHSCPEvent::~StoppedHSCPEvent() { }


void StoppedHSCPEvent::addMCDecay(MCDecay d) { 
  if (nMCDecay < MAX_N_MCDECAYS) {
    mcDecays[nMCDecay] = d;
    ++nMCDecay;
  }
}


void StoppedHSCPEvent::addL1Jet(TrigJet j) {
  if (nL1Jet < MAX_N_TRIGJETS) {
    l1Jets[nL1Jet] = j;
//     l1jetType.push_back(j.type);
//     l1jetE.push_back(j.e);
//     l1jetEt.push_back(j.et);
//     l1jetEta.push_back(j.eta);
//     l1jetPhi.push_back(j.phi);
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

void StoppedHSCPEvent::Dump() {

  using namespace std;

  cout << "New tree info :" << endl;
  cout << "Run          " << run << endl;
  cout << "Event        " << id << endl;
  cout << "LS           " << lb << endl;
  cout << "nTowSameiPhi " << nTowerSameiPhi << endl;
  cout << "Jet energy   " << jets[0].e << endl;
  cout << "Jet eta      " << jets[0].eta << endl;
  cout << "Jet n90      " << jets[0].n90 << endl;
  cout << "Jet n60      " << jets[0].n60 << endl;
  cout << "nMuon        " << nMuon << endl;

}

#if !defined(__CINT__)
  ClassImp(StoppedHSCPEvent)
#endif
