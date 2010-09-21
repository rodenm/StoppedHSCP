import FWCore.ParameterSet.Config as cms

stoppedHSCPTree = cms.EDAnalyzer(
    "StoppedHSCPTreeProducer",

    # trigger
    l1JetsTag = cms.untracked.string("l1extraParticles"),
    hltResultsTag = cms.untracked.InputTag("TriggerResults","","HLT"),
    hltEventTag = cms.untracked.InputTag("hltTriggerSummaryAOD","","HLT"),
    hltPath = cms.untracked.string("HLT_StoppedHSCP"),
    hltL3Tag = cms.untracked.InputTag("hltStoppedHSCP1CaloJetEnergy","","HLT"),

    # MC
    mcTag = cms.untracked.InputTag("generator"),
    
    # jets
    jetTag = cms.untracked.InputTag("iterativeCone5CaloJets"),
    jetMinEnergy = cms.untracked.double(1.),
    jetMaxEta = cms.untracked.double(1.3),
    
    # muons
    muonTag = cms.untracked.InputTag("muons"),
    cosmicMuonTag = cms.untracked.InputTag("muonsFromCosmics"),
    
    # calo towers
    caloTowerTag = cms.untracked.InputTag("towerMaker"),
    towerMinEnergy = cms.untracked.double(1.),
    towerMaxEta = cms.untracked.double(1.3),
    
    # HCAL digis/noise
    hcalNoiseTag = cms.untracked.InputTag("hcalnoise"),
    hcalNoiseFilterResultTag = cms.untracked.InputTag("HBHENoiseFilterResultProducer:HBHENoiseFilterResult"),
    rbxTag = cms.untracked.InputTag("hcalnoise"),
    hpdTag = cms.untracked.InputTag("hcalnoise"),
    hcalDigiTag = cms.untracked.InputTag("hcalDigis"),
    digiMinFc = cms.untracked.double(30.),
    
    # content controls
    doMC = cms.untracked.bool(True),
    doReco = cms.untracked.bool(True),
    doDigis = cms.untracked.bool(True),
    writeHistos = cms.untracked.bool(False),

    # bit 0:  off;
    #bit 1:  exclude rechit;
    #bit 5:  dead;
    #bit 6:  hot;
    #bit 18:  exclude from calotower
    badchannelstatus=cms.untracked.int32(1<<0 | 1<<1 | 1<<5 | 1<<6 | 1<<18) 
    )
