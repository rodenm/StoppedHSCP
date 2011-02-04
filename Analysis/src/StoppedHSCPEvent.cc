#include "StoppedHSCP/Analysis/interface/StoppedHSCPEvent.h"
#include "DataFormats/HcalDigi/interface/HBHEDataFrame.h"

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
  bxAfterCollision(0),
  bxBeforeCollision(0),
  bxWrtCollision(-99999),
  gtAlgoWord0(0),
  gtAlgoWord1(0),
  gtTechWord(0),
  hltBit(false),
  l1Jet_N(0),
  l1JetType(0),
  l1JetE(0),
  l1JetEt(0),
  l1JetEta(0),
  l1JetPhi(0),
  hltJet_N(0),
  hltJetType(0),
  hltJetE(0),
  hltJetEt(0),
  hltJetEta(0),
  hltJetPhi(0),
  rHadPdgId(0),
  rHadVtxX(0.),
  rHadVtxY(0.),
  rHadVtxZ(0.),
  rHadVtxR(0.),
  rHadVtxT(0.),
  rHadE(0.),
  rHadPx(0.),
  rHadPy(0.),
  rHadPz(0.),
  rHadPt(0.),
  mc_N(0),
  mcPDGid(0),
  mcVtxX(0),
  mcVtxY(0),
  mcVtxZ(0),
  mcVtxR(0),
  mcVtxT(0),
  mcE(0),
  mcPx(0),
  mcPy(0),
  mcPz(0),
  mcPt(0),
  nTowerSameiPhi(0),
  nTowerLeadingIPhi(0),
  eHadLeadingIPhi(0.),
  leadingDigiIEta(-999),
  leadingDigiIPhi(-999),
  leadingDigiTimeSamples(HBHEDataFrame::MAXSAMPLES),
  leadingDigiPeakSample(0),
  leadingDigiTotal(-999.),
  leadingDigiR1(-999.),
  leadingDigiR2(-999.),
  leadingDigiRPeak(-999.),
  leadingDigiROuter(-999.),
  top5DigiTimeSamples(HBHEDataFrame::MAXSAMPLES),
  top5DigiPeakSample(0),
  top5DigiTotal(-999.),
  top5DigiR1(-999.),
  top5DigiR2(-999.),
  top5DigiRPeak(-999.),
  top5DigiROuter(-999.),
  jet_N(0),
  jetE(0),
  jetEt(0),
  jetEta(0),
  jetPhi(0),
  jetEHad(0),
  jetEEm(0),
  jetEMaxEcalTow(0),
  jetEMaxHcalTow(0),
  jetN60(0),
  jetN90(0),
  jetFHPD(0),
  jetN90Hits(0),
  mu_N(0),
  muType(0),
  muPt(0),
  muEta(0),
  muPhi(0),
  muHcalEta(0),
  muHcalPhi(0),
  tower_N(0),
  towerE(0),
  towerEt(0),
  towerEta(0),
  towerPhi(0),
  towerIEta(0),
  towerIPhi(0),
  towerNJet(0),
  towerEHad(0),
  towerEtHad(0),
  towerEEm(0),
  towerEtEm(0),
  rechite(0),
  rechittime(0),
  rechitflags(0),
  rechitaux(0),
  rechitieta(0),
  rechitiphi(0),
  rechitdepth(0),
  noiseMinE2Over10TS(0.),
  noiseMaxE2Over10TS(0.),
  noiseMaxHPDHits(0),
  noiseMaxRBXHits(0),
  noiseMaxHPDNoOtherHits(0),
  noiseMaxZeros(0),
  noiseMin25GeVHitTime(0.),
  noiseMax25GeVHitTime(0.),
  noiseMinRBXEMF(0.),
  noiseFilterResult(0),
  beamHalo_CSCTight(false),
  beamHalo_CSCLoose(false),
  beamHalo_HcalTight(false),
  beamHalo_HcalLoose(false),
  nVtx(0),
  vtxNDOF(0),
  vtxZ(0.),
  vtxRho(0.),
  hpd_N(0),
  hpdId(0),
  hpdEta(0),
  hpdPhi(0),
  hpdTotalZeros(0),
  hpdMaxZeros(0),
  hpdNJet(0),
  hpdFc0(0), 
  hpdFc1(0), 
  hpdFc2(0), 
  hpdFc3(0), 
  hpdFc4(0), 
  hpdFc5(0), 
  hpdFc6(0), 
  hpdFc7(0), 
  hpdFc8(0), 
  hpdFc9(0),
  hpdFc5_0(0), 
  hpdFc5_1(0), 
  hpdFc5_2(0), 
  hpdFc5_3(0), 
  hpdFc5_4(0), 
  hpdFc5_5(0), 
  hpdFc5_6(0), 
  hpdFc5_7(0), 
  hpdFc5_8(0), 
  hpdFc5_9(0)
{
  
  for (int k=0; k<10; ++k) { 
    leadingDigiTimeSamples.at(k)=0.;
    top5DigiTimeSamples.at(k)=0.; 
  }

}

StoppedHSCPEvent::~StoppedHSCPEvent() { }


void StoppedHSCPEvent::addMCDecay(MCDecay d) { 
  mcPDGid.push_back(d.pdgId);
  mcVtxX.push_back(d.vtxX);
  mcVtxY.push_back(d.vtxY);
  mcVtxZ.push_back(d.vtxZ);
  mcVtxR.push_back(d.vtxR);
  mcVtxT.push_back(d.vtxT);
  mcE.push_back(d.e);
  mcPx.push_back(d.px);
  mcPy.push_back(d.py);
  mcPz.push_back(d.px);
  mcPt.push_back(d.pt);
  ++mc_N;
}


void StoppedHSCPEvent::addL1Jet(TrigJet j) {
  l1JetType.push_back(j.type);
  l1JetE.push_back(j.e);
  l1JetEt.push_back(j.et);
  l1JetEta.push_back(j.eta);
  l1JetPhi.push_back(j.phi);
  ++l1Jet_N;
}


void StoppedHSCPEvent::addHltJet(TrigJet j) {
  hltJetType.push_back(j.type);
  hltJetE.push_back(j.e);
  hltJetEt.push_back(j.et);
  hltJetEta.push_back(j.eta);
  hltJetPhi.push_back(j.phi);
  ++hltJet_N;
}


void StoppedHSCPEvent::addJet(Jet j) {
  jetE.push_back(j.e);
  jetEt.push_back(j.et);
  jetEta.push_back(j.eta);
  jetPhi.push_back(j.phi);
  jetEHad.push_back(j.eHad);
  jetEEm.push_back(j.eEm);
  jetEMaxEcalTow.push_back(j.eMaxEcalTow);
  jetEMaxHcalTow.push_back(j.eMaxHcalTow);
  jetN60.push_back(j.n60);
  jetN90.push_back(j.n90);
  jetFHPD.push_back(j.fHPD);
  jetN90Hits.push_back(j.n90Hits);
  ++jet_N;
}


void StoppedHSCPEvent::addMuon(Muon m) { 
  muType.push_back(m.type);
  muPt.push_back(m.pt);
  muEta.push_back(m.eta);
  muPhi.push_back(m.phi);
  muHcalEta.push_back(m.hcalEta);
  muHcalPhi.push_back(m.hcalPhi);
  ++mu_N;
}


void StoppedHSCPEvent::addTower(Tower t) {
  towerE.push_back(t.e);
  towerEt.push_back(t.et);
  towerEta.push_back(t.eta);
  towerPhi.push_back(t.phi);
  towerIEta.push_back(t.ieta);
  towerIPhi.push_back(t.iphi);
  towerNJet.push_back(t.nJet);
  towerEHad.push_back(t.eHad);
  towerEtHad.push_back(t.etHad);
  towerEEm.push_back(t.eEm);
  towerEtEm.push_back(t.etEm);
  ++tower_N;
}

void StoppedHSCPEvent::addRecHit(RecHit r) {
  rechite.push_back(r.e);
  rechittime.push_back(r.time);
  rechitflags.push_back(r.flags);
  rechitaux.push_back(r.aux);
  rechitieta.push_back(r.ieta);
  rechitiphi.push_back(r.iphi);
  rechitdepth.push_back(r.depth);
  ++rechit_N;
}

void StoppedHSCPEvent::addHPD(HPD h) {
  hpdId.push_back(h.id);
  hpdEta.push_back(h.eta);
  hpdPhi.push_back(h.phi);
  hpdTotalZeros.push_back(h.totalZeros);
  hpdMaxZeros.push_back(h.maxZeros);
  hpdNJet.push_back(h.nJet);
  hpdFc0.push_back(h.fc0);
  hpdFc1.push_back(h.fc1);
  hpdFc2.push_back(h.fc2);
  hpdFc3.push_back(h.fc3);
  hpdFc4.push_back(h.fc4);
  hpdFc5.push_back(h.fc5);
  hpdFc6.push_back(h.fc6);
  hpdFc7.push_back(h.fc7);
  hpdFc8.push_back(h.fc8);
  hpdFc9.push_back(h.fc9);
  hpdFc5_0.push_back(h.fc5_0);
  hpdFc5_1.push_back(h.fc5_1);
  hpdFc5_2.push_back(h.fc5_2);
  hpdFc5_3.push_back(h.fc5_3);
  hpdFc5_4.push_back(h.fc5_4);
  hpdFc5_5.push_back(h.fc5_5);
  hpdFc5_6.push_back(h.fc5_6);
  hpdFc5_7.push_back(h.fc5_7);
  hpdFc5_8.push_back(h.fc5_8);
  hpdFc5_9.push_back(h.fc5_9);
  ++hpd_N;
}


void StoppedHSCPEvent::Dump() {

  using namespace std;

  cout << "New tree info :" << endl;
  cout << "Run          " << run << endl;
  cout << "Event        " << id << endl;
  cout << "LS           " << lb << endl;
  cout << "nTowSameiPhi " << nTowerSameiPhi << endl;
  cout << "nMuon        " << mu_N << endl;
  cout << "BeamHalo     " << beamHalo_CSCLoose << " " << beamHalo_CSCTight << std::endl;

}

#if !defined(__CINT__)
  ClassImp(StoppedHSCPEvent)
#endif
