#include "StoppedHSCP/Ntuples/interface/StoppedHSCPEvent.h"

#include "DataFormats/HcalDigi/interface/HBHEDataFrame.h"

#include <iostream>
#include <algorithm>

using namespace shscp;

StoppedHSCPEvent::StoppedHSCPEvent() :
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
  mcSparticle_N(0),
  mcSparticleId(0),
  mcSparticleMass(0),
  mcSparticleCharge(0),
  mcSparticlePx(0),
  mcSparticlePy(0),
  mcSparticlePz(0),
  mcSparticlePt(0),
  mcSparticleE(0),
  mcSparticlePhi(0),
  mcSparticleEta(0),
  mcRhadron_N(0),
  mcRhadronId(0),
  mcRhadronMass(0),
  mcRhadronCharge(0),
  mcRhadronPx(0),
  mcRhadronPy(0),
  mcRhadronPz(0),
  mcRhadronPt(0),
  mcRhadronE(0),
  mcRhadronPhi(0),
  mcRhadronEta(0),
  mcNeutralino_N(0),
  mcNeutralinoId(0),
  mcNeutralinoMass(0),
  mcNeutralinoCharge(0),
  mcNeutralinoPx(0),
  mcNeutralinoPy(0),
  mcNeutralinoPz(0),
  mcNeutralinoPt(0),
  mcNeutralinoE(0),
  mcNeutralinoPhi(0),
  mcNeutralinoEta(0),
  mcDaughter_N(0),
  mcDaughterId(0),
  mcDaughterMass(0),
  mcDaughterCharge(0),
  mcDaughterPx(0),
  mcDaughterPy(0),
  mcDaughterPz(0),
  mcDaughterPt(0),
  mcDaughterE(0),
  mcDaughterPhi(0),
  mcDaughterEta(0),
  mcStoppedParticle_N(0),
  mcStoppedParticleName(0),
  mcStoppedParticleId(0),
  mcStoppedParticleX(0),
  mcStoppedParticleY(0),
  mcStoppedParticleZ(0),
  mcStoppedParticleR(0),
  mcStoppedParticlePhi(0),
  mcStoppedParticleTime(0),
  id(0),
  bx(0),
  orbit(0),
  lb(0),
  run(0),
  fill(0),
  fillFromL1(0),
  time(0), // timestamp from EvF
  time2(0),  // calculated from run start + L1 counters for LS, orbit, BX
  time3(0),  // timestamp from LHC info in L1 data
  bxAfterCollision(0),
  bxBeforeCollision(0),
  bxWrtCollision(-99999),
  bxAfterBunch(0),
  bxBeforeBunch(0),
  bxWrtBunch(-99999),
  beam1Intensity(5),
  beam2Intensity(5),
  lumiByBx(5),
  lsLuminosity(0),
  lsLuminosityErr(0),
  gtAlgoWord0(0),
  gtAlgoWord1(0),
  gtTechWord(0),
  l1JetNoBptx(5),
  l1JetNoBptxNoHalo(5),
  l1Jet32NoBptxNoHalo(5),
  l1Bptx(5),
  l1MuBeamHalo(5),
  hltJetNoBptx(false),
  hltJetNoBptxNoHalo(false),
  hltJetNoBptx3BXNoHalo(false),
  hltJetE50NoBptx3BXNoHalo(false),
  hltJetE70NoBptx3BXNoHalo(false),
  algoTriggerPrescaleIndex(0),
  techTriggerPrescaleIndex(0),
  hltPrescaleIndex(0),
  l1JetNoBptxPrescale(0),
  l1JetNoBptxNoHaloPrescale(0),
  l1Jet32NoBptxNoHaloPrescale(0),
  hltJetNoBptxPrescale(0),
  hltJetNoBptxNoHaloPrescale(0),
  hltJetNoBptx3BXNoHaloPrescale(0),
  hltJetE50NoBptx3BXNoHaloPrescale(0),
  hltJetE70NoBptx3BXNoHaloPrescale(0),
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
  jet_N(0),
  jetE(0),
  jetECorr(0),
  jetEt(0),
  jetEtCorr(0),
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
  jetEtaMean(0),
  jetPhiMean(0),
  jetEtaetaMoment(0),
  jetPhiphiMoment(0),
  jetEtaphiMoment(0),
  studyJet_N(0),
  studyJetE(0),
  studyJetECorr(0),
  studyJetEt(0),
  studyJetEtCorr(0),
  studyJetEta(0),
  studyJetPhi(0),
  studyJetEHad(0),
  studyJetEEm(0),
  studyJetEMaxEcalTow(0),
  studyJetEMaxHcalTow(0),
  studyJetN60(0),
  studyJetN90(0),
  studyJetFHPD(0),
  studyJetN90Hits(0),
  jetAK5_N(0),
  jetAK5E(0),
  jetAK5ECorr(0),
  jetAK5Et(0),
  jetAK5EtCorr(0),
  jetAK5Eta(0),
  jetAK5Phi(0),
  jetAK5EHad(0),
  jetAK5EEm(0),
  jetAK5EMaxEcalTow(0),
  jetAK5EMaxHcalTow(0),
  jetAK5N60(0),
  jetAK5N90(0),
  jetAK5FHPD(0),
  jetAK5N90Hits(0),
  studyJetAK5_N(0),
  studyJetAK5E(0),
  studyJetAK5ECorr(0),
  studyJetAK5Et(0),
  studyJetAK5EtCorr(0),
  studyJetAK5Eta(0),
  studyJetAK5Phi(0),
  studyJetAK5EHad(0),
  studyJetAK5EEm(0),
  studyJetAK5EMaxEcalTow(0),
  studyJetAK5EMaxHcalTow(0),
  studyJetAK5N60(0),
  studyJetAK5N90(0),
  studyJetAK5FHPD(0),
  studyJetAK5N90Hits(0),
  mu_N(0),
  muType(0),
  muPt(0),
  muEta(0),
  muPhi(0),
  muHcalEta(0),
  muHcalPhi(0),
  muNumChambers(0),
  muNumChambersNoRPC(0),
  muNumMatches(0),
  muNumMatchedStations(0),
  muStationMask(0),
  nVtx(0),
  vtx_N(0),
  vtxNDOF(0),
  vtxZ(0),
  vtxRho(0),
  track_N(0),
  trackChi2(0),
  trackNdof(0),
  trackNHits(0),
  trackNLost(0),
  trackP(0),
  trackQuality(0),
  trackHcalEta(0),
  trackHcalPhi(0),
  beamHalo_CSCTight(false),
  beamHalo_CSCLoose(false),
  beamHalo_HcalTight(false),
  beamHalo_HcalLoose(false),
  nTowerSameiPhi(0),
  leadingIPhiFractionValue(0.),
  nTowerLeadingIPhi(0),
  eHadLeadingIPhi(0.),
  hfPlusTotalE(0.),
  hfMinusTotalE(0.),
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
  noiseEventEMEnergy(0.),
  noiseEventHadEnergy(0.),
  noiseEventTrackEnergy(0.),
  noiseNumProblematicRBXs(0.),
  topHPD5TimeSamples(HBHEDataFrame::MAXSAMPLES),
  topHPD5PeakSample(0),
  topHPD5Total(-999.),
  topHPD5R1(-999.),
  topHPD5R2(-999.),
  topHPD5RPeak(-999.),
  topHPD5ROuter(-999.),
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
  hpdFc5_9(0),
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
  studyTower_N(0),
  studyTowerE(0),
  studyTowerEt(0),
  studyTowerEta(0),
  studyTowerPhi(0),
  studyTowerIEta(0),
  studyTowerIPhi(0),
  studyTowerNJet(0),
  studyTowerEHad(0),
  studyTowerEtHad(0),
  studyTowerEEm(0),
  studyTowerEtEm(0),
  recHit_N(0),
  recHitE(0),
  recHitTime(0),
  recHitFlags(0),
  recHitAux(0),
  recHitEta(0.),
  recHitPhi(0.),
  recHitIEta(0),
  recHitIPhi(0),
  recHitDepth(0),
  hfRecHit_N(0),
  hfRecHitE(0),
  hfRecHitTime(0),
  hfRecHitEta(0.),
  hfRecHitPhi(0.),
  hfRecHitIEta(0),
  hfRecHitIPhi(0),
  hfRecHitDepth(0),
  cscSeg_N(0),
  cscSegEndcap(0),
  cscSegRing(0),
  cscSegStation(0),
  cscSegChamber(0),
  cscSegNHits(0),
  cscSegPhi(0),
  cscSegZ(0),
  cscSegR(0),
  cscSegDirPhi(0),
  cscSegDirTheta(0),
  cscSegTime(0),
  cscHit_N (0),
  cscHitZ (0),
  cscHitRho (0),
  cscHitPhi (0),
  DTSegment_N(0),
  DTSegWheel(0),
  DTSegStation(0),
  DTSegSector(0),
  DTSegLocalX(0),
  DTSegLocalY(0),
  DTSegX(0),
  DTSegY(0),
  DTSegR(0),
  DTSegZ(0),
  DTSegRho(0),
  DTSegPhi(0),
  DTSegXDir(0),
  DTSegYDir(0),
  DTSegPhiDir(0),
  DTSegZDir(0),
  //DTSegTime(0),
  rpcHit_N(0),
  rpcHitX(0),
  rpcHitY(0),
  rpcHitR(0),
  rpcHitZ(0),
  rpcHitRho(0),
  rpcHitPhi(0),
  rpcHitRegion(0),
  hePlusEnergy (-999),
  hePlusAntiEnergy (-999),
  hePlusPhi (-999),
  heMinusEnergy (-999),
  heMinusAntiEnergy (-999),
  heMinusPhi (-999),
  heEnergy (-999),
  heAntiEnergy (-999),
  hePhi (-999), 
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
  top5DigiROuter(-999.)
{

  for (int k=0; k<5; ++k) {
    l1JetNoBptx.at(k) = 0;//false;
    l1JetNoBptxNoHalo.at(k) = 0;//false;
    l1Bptx.at(k) = 0;//false;
    l1MuBeamHalo.at(k) = 0;//false;
    beam1Intensity.at(k) = -1.0;
    beam2Intensity.at(k) = -1.0;
    lumiByBx.at(k) = -1.0;
  }
  
  for (int k=0; k<HBHEDataFrame::MAXSAMPLES; ++k) { 
    leadingDigiTimeSamples.at(k)=0.;
    top5DigiTimeSamples.at(k)=0.; 
    topHPD5TimeSamples.at(k)=0.;
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
  if (l1Jet_N < MAX_N_JETS) {
    l1JetType.push_back(j.type);
    l1JetE.push_back(j.e);
    l1JetEt.push_back(j.et);
    l1JetEta.push_back(j.eta);
    l1JetPhi.push_back(j.phi);
    ++l1Jet_N;
  }
}


void StoppedHSCPEvent::addHltJet(TrigJet j) {
 if (hltJet_N < MAX_N_JETS) {
   hltJetType.push_back(j.type);
   hltJetE.push_back(j.e);
   hltJetEt.push_back(j.et);
   hltJetEta.push_back(j.eta);
   hltJetPhi.push_back(j.phi);
   ++hltJet_N;
 }
}


void StoppedHSCPEvent::addJet(Jet j) {
  if (jet_N < MAX_N_JETS) {
    jetE.push_back(j.e);
    jetECorr.push_back(j.e_corr);
    jetEt.push_back(j.et);
    jetEtCorr.push_back(j.et_corr);
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
    jetEtaMean.push_back(j.etaMean);
    jetPhiMean.push_back(j.phiMean);
    jetEtaetaMoment.push_back(j.etaetaMoment);
    jetPhiphiMoment.push_back(j.phiphiMoment);
    jetEtaphiMoment.push_back(j.etaphiMoment);
    ++jet_N;
  }
}

void StoppedHSCPEvent::addStudyJet(Jet j) {
  if (studyJet_N < MAX_N_JETS) {
    studyJetE.push_back(j.e);
    studyJetECorr.push_back(j.e_corr);
    studyJetEt.push_back(j.et);
    studyJetEtCorr.push_back(j.et_corr);
    studyJetEta.push_back(j.eta);
    studyJetPhi.push_back(j.phi);
    studyJetEHad.push_back(j.eHad);
    studyJetEEm.push_back(j.eEm);
    studyJetEMaxEcalTow.push_back(j.eMaxEcalTow);
    studyJetEMaxHcalTow.push_back(j.eMaxHcalTow);
    studyJetN60.push_back(j.n60);
    studyJetN90.push_back(j.n90);
    studyJetFHPD.push_back(j.fHPD);
    studyJetN90Hits.push_back(j.n90Hits);
    ++studyJet_N;
  }
}

void StoppedHSCPEvent::addAK5Jet(Jet j) {
  if (jetAK5_N < MAX_N_JETS) {
    jetAK5E.push_back(j.e);
    jetAK5ECorr.push_back(j.e_corr);
    jetAK5Et.push_back(j.et);
    jetAK5EtCorr.push_back(j.et_corr);
    jetAK5Eta.push_back(j.eta);
    jetAK5Phi.push_back(j.phi);
    jetAK5EHad.push_back(j.eHad);
    jetAK5EEm.push_back(j.eEm);
    jetAK5EMaxEcalTow.push_back(j.eMaxEcalTow);
    jetAK5EMaxHcalTow.push_back(j.eMaxHcalTow);
    jetAK5N60.push_back(j.n60);
    jetAK5N90.push_back(j.n90);
    jetAK5FHPD.push_back(j.fHPD);
    jetAK5N90Hits.push_back(j.n90Hits);
    ++jetAK5_N;
  }
}

void StoppedHSCPEvent::addAK5StudyJet(Jet j) {
  if (studyJetAK5_N < MAX_N_JETS) {
    studyJetAK5E.push_back(j.e);
    studyJetAK5ECorr.push_back(j.e_corr);
    studyJetAK5Et.push_back(j.et);
    studyJetAK5EtCorr.push_back(j.et_corr);
    studyJetAK5Eta.push_back(j.eta);
    studyJetAK5Phi.push_back(j.phi);
    studyJetAK5EHad.push_back(j.eHad);
    studyJetAK5EEm.push_back(j.eEm);
    studyJetAK5EMaxEcalTow.push_back(j.eMaxEcalTow);
    studyJetAK5EMaxHcalTow.push_back(j.eMaxHcalTow);
    studyJetAK5N60.push_back(j.n60);
    studyJetAK5N90.push_back(j.n90);
    studyJetAK5FHPD.push_back(j.fHPD);
    studyJetAK5N90Hits.push_back(j.n90Hits);
    ++studyJetAK5_N;
  }
}


void StoppedHSCPEvent::addMuon(Muon m) { 
  muType.push_back(m.type);
  muPt.push_back(m.pt);
  muEta.push_back(m.eta);
  muPhi.push_back(m.phi);
  muHcalEta.push_back(m.hcalEta);
  muHcalPhi.push_back(m.hcalPhi);
  muNumChambers.push_back(m.numChambers);
  muNumChambersNoRPC.push_back(m.numChambersNoRPC);
  muNumMatches.push_back(m.numMatches);
  muNumMatchedStations.push_back(m.numStations);
  muStationMask.push_back(m.stationMask);
  ++mu_N;
}


void StoppedHSCPEvent::addTower(Tower t) {
  if (tower_N < MAX_N_TOWERS) {
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
}

void StoppedHSCPEvent::removeTowers() {
  // remove towers (used for reduced ntuples,
  // and when doCaloTowers is false
  towerE.clear();
  towerEt.clear();   
  towerEta.clear();  
  towerPhi.clear();  
  towerIEta.clear(); 
  towerIPhi.clear(); 
  towerNJet.clear(); 
  towerEHad.clear(); 
  towerEtHad.clear();
  towerEEm.clear();  
  towerEtEm.clear(); 
  tower_N=0;
} // void StoppedHSCPEvent::removeTowers()


void StoppedHSCPEvent::addStudyTower(Tower t) {
  if (studyTower_N < MAX_N_TOWERS) {
    studyTowerE.push_back(t.e);
    studyTowerEt.push_back(t.et);
    studyTowerEta.push_back(t.eta);
    studyTowerPhi.push_back(t.phi);
    studyTowerIEta.push_back(t.ieta);
    studyTowerIPhi.push_back(t.iphi);
    studyTowerNJet.push_back(t.nJet);
    studyTowerEHad.push_back(t.eHad);
    studyTowerEtHad.push_back(t.etHad);
    studyTowerEEm.push_back(t.eEm);
    studyTowerEtEm.push_back(t.etEm);
    ++studyTower_N;
  }
}

void StoppedHSCPEvent::addRecHit(RecHit r) {
  recHitE.push_back(r.e);
  recHitTime.push_back(r.time);
  recHitFlags.push_back(r.flags);
  recHitAux.push_back(r.aux);
  recHitEta.push_back(r.eta);
  recHitPhi.push_back(r.phi); 
  recHitIEta.push_back(r.ieta);
  recHitIPhi.push_back(r.iphi);
  recHitDepth.push_back(r.depth);
  recHitRBXindex.push_back(r.RBXindex);
  recHitRMindex.push_back(r.RMindex);
  ++recHit_N;
}

void StoppedHSCPEvent::addHFRecHit(RecHit r) {
  hfRecHitE.push_back(r.e);
  hfRecHitTime.push_back(r.time);
  hfRecHitEta.push_back(r.eta);
  hfRecHitPhi.push_back(r.phi); 
  hfRecHitIEta.push_back(r.ieta);
  hfRecHitIPhi.push_back(r.iphi);
  hfRecHitDepth.push_back(r.depth);
  ++hfRecHit_N;
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

void StoppedHSCPEvent::addCscSegment(CscSegment s) {
  cscSegEndcap.push_back(s.endcap);
  cscSegRing.push_back(s.ring);
  cscSegStation.push_back(s.station);
  cscSegChamber.push_back(s.chamber);
  cscSegNHits.push_back(s.nHits);
  cscSegPhi.push_back(s.phi);
  cscSegZ.push_back(s.z);
  cscSegR.push_back(s.r);
  cscSegDirPhi.push_back(s.dirPhi);
  cscSegDirTheta.push_back(s.dirTheta);
  cscSegTime.push_back(s.time);
  ++cscSeg_N;
}

void StoppedHSCPEvent::addCscHit(CscHit h) {
  cscHitZ.push_back(h.z);
  cscHitRho.push_back(h.rho);
  cscHitPhi.push_back(h.phi);
  cscHitTime.push_back(h.time);
  ++cscHit_N;
}

void StoppedHSCPEvent::addDTSegment(DTSegment dt)
{
  DTSegWheel.push_back(dt.wheel);
  DTSegStation.push_back(dt.station);
  DTSegSector.push_back(dt.sector);
  DTSegLocalX.push_back(dt.localX);
  DTSegLocalY.push_back(dt.localY);
  DTSegX.push_back(dt.x);
  DTSegY.push_back(dt.y);
  DTSegR.push_back(dt.r);
  DTSegZ.push_back(dt.z);
  DTSegRho.push_back(dt.rho);
  DTSegPhi.push_back(dt.phi);
  DTSegXDir.push_back(dt.xdir);
  DTSegYDir.push_back(dt.ydir);
  DTSegPhiDir.push_back(dt.phidir);
  DTSegZDir.push_back(dt.zdir);
  //DTSegTime.push_back(dt.time);
  ++DTSegment_N;
}

void StoppedHSCPEvent::addRpcHit(RpcHit h)
{
  rpcHitX.push_back(h.x);
  rpcHitY.push_back(h.y);
  rpcHitR.push_back(h.r);
  rpcHitZ.push_back(h.z);
  rpcHitRho.push_back(h.rho);
  rpcHitPhi.push_back(h.phi);
  rpcHitRegion.push_back(h.region);
  ++rpcHit_N;
}

void StoppedHSCPEvent::addTrack(Track track) {

  trackChi2.push_back(track.chi2);
  trackNdof.push_back(track.ndof);
  trackNHits.push_back(track.nHits);
  trackNLost.push_back(track.nLost);
  trackQuality.push_back(track.quality);
  trackP.push_back(track.p);
  ++track_N;
}

void StoppedHSCPEvent::addHePlus(double energy, double antienergy, double phi) {
  if (hePlusEnergy < energy) {
    hePlusEnergy = energy;
    hePlusAntiEnergy = antienergy;
    hePlusPhi = phi;
  }
}

void StoppedHSCPEvent::addHeMinus(double energy, double antienergy, double phi) {
  if (heMinusEnergy < energy) {
    heMinusEnergy = energy;
    heMinusAntiEnergy = antienergy;
    heMinusPhi = phi;
  }
}

void StoppedHSCPEvent::addHe(double energy, double antienergy, double phi) {
  if (heEnergy < energy) {
    heEnergy = energy;
    heAntiEnergy = antienergy;
    hePhi = phi;
  }
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

// energy fraction at same iphi
double StoppedHSCPEvent::leadingIPhiFraction() const {

    std::vector<double> tmp(75, 0);
    for (unsigned i=0; i<tower_N; ++i) {
      tmp.at(towerIPhi.at(i)) += towerE.at(i);
    }
    std::vector<double>::iterator max=max_element(tmp.begin(), tmp.end());

    double frac=0.;
    if (jet_N>0) frac = (*max)/jetE.at(0);
    return frac;

}


unsigned StoppedHSCPEvent::jetCaloTowers() const {

  std::vector<shscp::Tower> towers;
  for (unsigned i=0; i<tower_N; ++i) {
    if (towerNJet.at(i)==0) {
      Tower t;
      t.iphi=towerIPhi.at(i);
      t.e = towerE.at(i);
      towers.push_back(t);
    }
  }

  std::sort(towers.begin(), towers.end(), shscp::tow_gt());

  unsigned tmp=0;

  if (towers.size() > 0) {
    int iphiFirst=towers.at(0).iphi;
    bool keepgoing=true;
    for (unsigned i=0; i<towers.size() && keepgoing; ++i) {
      if (towers.at(i).iphi==iphiFirst) tmp++;
      else keepgoing=false;
    }
  }

  return tmp;

}


#if !defined(__CINT__)
  ClassImp(StoppedHSCPEvent)
#endif
