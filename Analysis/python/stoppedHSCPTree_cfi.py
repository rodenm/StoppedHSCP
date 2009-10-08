import FWCore.ParameterSet.Config as cms

stoppedHSCPTree = cms.EDAnalyzer(
    "StoppedHSCPTreeProducer",

    # trigger
    l1JetsTag = cms.untracked.string("l1extraParticles"),
    hltResultsTag = cms.untracked.InputTag("TriggerResults","","SHSCP"),
    hltEventTag = cms.untracked.InputTag("hltTriggerSummaryAOD","","SHSCP"),
    hltL3Tag = cms.untracked.InputTag("hltStoppedHSCP1CaloJetEnergy","","SHSCP"),

    # MC
    mcTag = cms.untracked.InputTag("generator"),
    
    # jets
    jetTag = cms.untracked.InputTag("iterativeCone5CaloJets"),
    jetMinEnergy = cms.untracked.double(1.),
    jetMaxEta = cms.untracked.double(5.),
    
    # muons
    muonTag = cms.untracked.InputTag("muons"),
    
    # calo towers
    caloTowerTag = cms.untracked.InputTag("towerMaker"),
    towerMinEnergy = cms.untracked.double(1.),
    towerMaxEta = cms.untracked.double(3.),
    
    # HCAL digis/noise
    hcalNoiseTag = cms.untracked.InputTag("hcalnoise"),
    rbxTag = cms.untracked.InputTag("hcalnoise"),
    hpdTag = cms.untracked.InputTag("hcalnoise"),
    hcalDigiTag = cms.untracked.InputTag("hcalDigis"),
    digiMinFc = cms.untracked.double(30.),
    
    # content controls
    doMC = cms.untracked.bool(False),
    doReco = cms.untracked.bool(True),
    doDigis = cms.untracked.bool(True),
    writeHistos = cms.untracked.bool(False)
    )
