import FWCore.ParameterSet.Config as cms

triggerValidator = cms.EDAnalyzer(
    "TriggerValidator",
    l1JetsTag = cms.untracked.string("l1extraParticles"),
    l1BitsTag = cms.untracked.InputTag("gtDigis"),
    hltTag = cms.untracked.InputTag("TriggerResults","","HLT"),
    offlineHltTag = cms.untracked.InputTag("TriggerResults","","HLT2"),
    hltJetTag = cms.untracked.InputTag("hltStoppedHSCPIterativeCone5CaloJets"),
)
