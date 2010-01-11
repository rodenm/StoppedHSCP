import FWCore.ParameterSet.Config as cms

globalRunAnalyser = cms.EDAnalyzer(
    "GlobalRunAnalyser",
    IncludeJets=cms.untracked.bool(True),
    IncludeJetDetails=cms.untracked.bool(True),
    IncludeDigis=cms.untracked.bool(True),
    IncludeDigisOld=cms.untracked.bool(True),
    IncludeCaloTowers=cms.untracked.bool(True),
    IncludeMuons=cms.untracked.bool(True),
    IncludeMC=cms.untracked.bool(False),
    DigisTag=cms.untracked.InputTag("hcalDigis"),
    JetTag=cms.untracked.InputTag("iterativeCone5CaloJets"),
    CaloToweTag=cms.untracked.InputTag("towerMaker"),
    MCTag=cms.untracked.InputTag("source"),
    MuonsTag=cms.untracked.InputTag("muons"),
    DigiCount=cms.untracked.int32(5),
    CenJetEta=cms.untracked.double(1.3),
    WriteHistos=cms.untracked.bool(False)
    )
