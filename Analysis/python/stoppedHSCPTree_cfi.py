import FWCore.ParameterSet.Config as cms

stoppedHSCPTree = cms.EDAnalyzer("StoppedHSCPTreeProducer",
  l1JetTag = cms.untracked.InputTag("l1extra::central"),
  hltTag = cms.untracked.InputTag("HLT"),
  mcTag = cms.untracked.InputTag("generator"),
  jetTag = cms.untracked.InputTag("sisCone5CaloJets"),
  muonTag = cms.untracked.InputTag("muons"),
  caloTowerTag = cms.untracked.InputTag("towerMaker"),
  hcalNoiseTag = cms.untracked.InputTag("hcalnoise"),
  rbxTag = cms.untracked.InputTag("hcalnoise"),
  hpdTag = cms.untracked.InputTag("hcalnoise"),
#  hcalDigiTag = cms.untracked.InputTag("hcalDigis"),
  hcalDigiTag = cms.untracked.InputTag(""),
  writeHistos = cms.untracked.bool(False)
)
