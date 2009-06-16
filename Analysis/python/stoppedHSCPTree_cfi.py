import FWCore.ParameterSet.Config as cms

stoppedHSCPTree = cms.EDAnalyzer("StoppedHSCPTreeProducer",
  jetTag = cms.untracked.InputTag("iterativeCone5CaloJets"),
  caloTowerTag = cms.untracked.InputTag("towerMaker"),
  mcTag = cms.untracked.InputTag("source"),
  muonTag = cms.untracked.InputTag("muons"),
  writeHistos = cms.untracked.bool(False)
)
