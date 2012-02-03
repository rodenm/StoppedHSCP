import FWCore.ParameterSet.Config as cms

stoppedHSCPTree = cms.EDAnalyzer(
    "StoppedHSCPTreeProducer",

    # trigger
    l1BitsTag = cms.untracked.InputTag("gtDigis"),
    l1JetsTag = cms.untracked.string("l1extraParticles"),
    l1JetNoBptxName = cms.untracked.string("L1_SingleJet20_NotBptxOR"),  
    l1JetNoBptxNoHaloName = cms.untracked.string("L1_SingleJet20_NotBptxOR_NotMuBeamHalo"),  
    l1BptxName = cms.untracked.string("L1Tech_BPTX_plus_AND_minus"),
    l1MuBeamHaloName = cms.untracked.string("L1_SingleMuBeamHalo"),
    hltResultsTag = cms.untracked.InputTag("TriggerResults","","HLT"),
    hltEventTag = cms.untracked.InputTag("hltTriggerSummaryAOD","","HLT"),
    # Remove '*' from name, so that ntuple Producer can search for strings properly in C++
    hltPathJetNoBptx = cms.untracked.string("HLT_JetE30_NoBPTX_v"),
    hltPathJetNoBptxNoHalo = cms.untracked.string("HLT_JetE30_NoBPTX_NoHalo_v"),
    hltPathJetNoBptx3BXNoHalo = cms.untracked.string("HLT_JetE30_NoBPTX3BX_NoHalo_v"),
    hltPathJetE50NoBptx3BXNoHalo = cms.untracked.string("HLT_JetE50_NoBPTX3BX_NoHalo_v"),
    hltL3Tag = cms.untracked.InputTag("hltStoppedHSCPTight1CaloJetEnergy30","","HLT"),

    # MC
    mcTag = cms.untracked.InputTag("generator"),
    
    # jets
    jetCorrectorServiceName = cms.untracked.string("ak5CaloJetsL1L2L3Residual"),
    jetTag = cms.untracked.InputTag("iterativeCone5CaloJets"),
    jetAK5Tag = cms.untracked.InputTag("ak5CaloJets"),
    jetMinEnergy = cms.untracked.double(1.),
    jetMaxEta = cms.untracked.double(1.3),

    # objects for study
    studyJetMinEta = cms.untracked.double(1.3),
    studyJetMaxEta = cms.untracked.double(3.0),
    studyTowerMinEta = cms.untracked.double(1.3),
    studyTowerMaxEta = cms.untracked.double(3.0),
    
    
    # muons
    muonTag = cms.untracked.InputTag("muons"),
    cosmicMuonTag = cms.untracked.InputTag("muonsFromCosmics"),
    
    # calo towers
    caloTowerTag = cms.untracked.InputTag("towerMaker"),
    towerMinEnergy = cms.untracked.double(1.),
    towerMaxEta = cms.untracked.double(1.3),
    
    # calo rechits
    caloRecHitTag = cms.untracked.InputTag("hbhereco"),
    rechitMinEnergy = cms.untracked.double(0.2),

    # HCAL digis/noise
    hcalNoiseTag = cms.untracked.InputTag("hcalnoise"),
    hcalNoiseFilterResultTag = cms.untracked.InputTag("HBHENoiseFilterResultProducer:HBHENoiseFilterResult"),
    rbxTag = cms.untracked.InputTag("hcalnoise"),
    hpdTag = cms.untracked.InputTag("hcalnoise"),
    hcalDigiTag = cms.untracked.InputTag("hcalDigis"),
    cscSegmentsTag = cms.untracked.InputTag("cscSegments"),
    cscRecHitsTag = cms.untracked.InputTag("csc2DRecHits"),

    DTRecHitsTag=cms.untracked.InputTag("dt1DRecHits"),
    DT4DSegmentsTag=cms.untracked.InputTag("dt4DSegments"),

    digiMinFc = cms.untracked.double(30.),
    
    # content controls
    isMC = cms.untracked.bool(False),
    doCaloTowers = cms.untracked.bool(True),
    doRecHits = cms.untracked.bool(False),
    doHFRecHits = cms.untracked.bool(False),
    doCsc = cms.untracked.bool(True),
    doCscRecHits = cms.untracked.bool(False),
    doDT    = cms.untracked.bool(True),  # muon Drift Tubes
    doRpcRecHits = cms.untracked.bool(True),
    doDigis = cms.untracked.bool(True),
    writeHistos = cms.untracked.bool(False),

    # bit 0:  off;
    #bit 1:  exclude rechit;
    #bit 5:  dead;
    #bit 6:  hot;
    #bit 18:  exclude from calotower
    badchannelstatus=cms.untracked.int32(1<<0 | 1<<1 | 1<<5 | 1<<6 | 1<<18),
    makeReducedNtuples=cms.untracked.bool(False)
    )
