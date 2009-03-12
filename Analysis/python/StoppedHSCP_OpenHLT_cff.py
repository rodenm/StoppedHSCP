
import FWCore.ParameterSet.Config as cms

# HSCP HLT path
# this version has no filters for optimisation purposes etc

# begin sequence
#hltGetRaw = cms.EDAnalyzer( "HLTGetRaw",
#    RawDataCollection = cms.InputTag( "source" )
#)
#hltTriggerType = cms.EDFilter( "TriggerTypeFilter",
#    InputLabel = cms.string( "source" ),
#    TriggerFedId = cms.int32( 812 ),
#    SelectedTriggerType = cms.int32( 1 )
#)
hltGtDigis = cms.EDProducer( "L1GlobalTriggerRawToDigi",
    DaqGtInputTag = cms.InputTag( "source" ),
    DaqGtFedId = cms.untracked.int32( 813 ),
    ActiveBoardsMask = cms.uint32( 0x101 ),
    UnpackBxInEvent = cms.int32( 1 )
)
hltGctDigis = cms.EDProducer( "GctRawToDigi",
    inputLabel = cms.InputTag( "source" ),
    gctFedId = cms.int32( 745 ),
    hltMode = cms.bool( False ),
    grenCompatibilityMode = cms.bool( False )
)
hltL1GtObjectMap = cms.EDProducer( "L1GlobalTrigger",
    GmtInputTag = cms.InputTag( "hltGtDigis" ),
    GctInputTag = cms.InputTag( "hltGctDigis" ),
    CastorInputTag = cms.InputTag( "castorL1Digis" ),
    TechnicalTriggersInputTag = cms.InputTag( "techTrigDigis" ),
    ProduceL1GtDaqRecord = cms.bool( False ),
    ProduceL1GtEvmRecord = cms.bool( False ),
    ProduceL1GtObjectMapRecord = cms.bool( True ),
    WritePsbL1GtDaqRecord = cms.bool( False ),
    ReadTechnicalTriggerRecords = cms.bool( True ),
    EmulateBxInEvent = cms.int32( 1 ),
    BstLengthBytes = cms.int32( -1 )
)
hltL1extraParticles = cms.EDProducer( "L1ExtraParticlesProd",
    produceMuonParticles = cms.bool( True ),
    muonSource = cms.InputTag( "hltGtDigis" ),
    produceCaloParticles = cms.bool( True ),
    isolatedEmSource = cms.InputTag( 'hltGctDigis','isoEm' ),
    nonIsolatedEmSource = cms.InputTag( 'hltGctDigis','nonIsoEm' ),
    centralJetSource = cms.InputTag( 'hltGctDigis','cenJets' ),
    forwardJetSource = cms.InputTag( 'hltGctDigis','forJets' ),
    tauJetSource = cms.InputTag( 'hltGctDigis','tauJets' ),
    etTotalSource = cms.InputTag( "hltGctDigis" ),
    etHadSource = cms.InputTag( "hltGctDigis" ),
    etMissSource = cms.InputTag( "hltGctDigis" ),
    centralBxOnly = cms.bool( True )
)
hltOfflineBeamSpot = cms.EDProducer( "BeamSpotProducer" )
#hltGetRaw = cms.EDAnalyzer( "HLTGetRaw",
#    RawDataCollection = cms.InputTag( "source" )
#)

HLTBeginSequence = cms.Sequence( hltGtDigis + hltGctDigis + hltL1GtObjectMap + hltL1extraParticles + hltOfflineBeamSpot )

hltL1SeedHscp = cms.EDFilter( "HLTLevel1GTSeed",
    L1TechTriggerSeeding = cms.bool( False ),
    L1SeedsLogicalExpression = cms.string( "L1_SingleJet10_00001" ),
    L1GtReadoutRecordTag = cms.InputTag( "hltGtDigis" ),
    L1GtObjectMapTag = cms.InputTag( "hltL1GtObjectMap" ),
    L1CollectionsTag = cms.InputTag( "hltL1extraParticles" ),
    L1MuonCollectionTag = cms.InputTag( "hltL1extraParticles" )
)

# HCAL unpacker
from EventFilter.HcalRawToDigi.HcalRawToDigi_cfi import hcalDigis
hltHcalDigis = hcalDigis.clone()

# HCAL local reco
from RecoLocalCalo.HcalRecProducers.HcalSimpleReconstructor_hbhe_cfi import hbhereco
hltHbHeReco = hbhereco.clone()
hltHbHeReco.digiLabel = cms.InputTag("hltHcalDigis")

# HPD noise filter
hltHpdFilter = cms.EDFilter("HLTHPDFilter",
   inputTag = cms.InputTag("hltHbHeReco"),
   energy = cms.double(-99.0),
   hpdSpikeEnergy = cms.double(10.0),
   hpdSpikeIsolationEnergy = cms.double(1.0),
   rbxSpikeEnergy = cms.double(50.0),
   rbxSpikeUnbalance = cms.double(0.2)
)

# calo towers
from RecoJets.JetProducers.CaloTowerSchemeB_cfi import towerMaker
hltTowerMaker = towerMaker.clone()
hltTowerMaker.hbheInput = cms.InputTag("hltHbHeReco")
hltTowerMaker.AllowMissingInputs = cms.untracked.bool(True)
hltTowerMaker.EBWeight = cms.double(0.0)  # ???
hltTowerMaker.EEWeight = cms.double(0.0)  # ???

# jet reco
from RecoJets.JetProducers.iterativeCone5CaloJets_cff import iterativeCone5CaloJets
hltIterativeCone5CaloJets = iterativeCone5CaloJets.clone()
hltIterativeCone5CaloJets.src = cms.InputTag("hltTowerMaker")

# jet filter
hltHscpJet20 = cms.EDFilter( "HLTCaloJetEnergyFilter",
    inputTag = cms.InputTag( "hltIterativeCone5CaloJets" ),
#    saveTag = cms.untracked.bool( True ),
    MinEnergy = cms.double( 20.0 ),
    MaxEta = cms.double( 3.0 )
)


# HSCP path
hscpPath = cms.Path(
    HLTBeginSequence*
#    hltL1SeedHscp*
    hltHcalDigis*
    hltHbHeReco*
#    hltHpdFilter*
    hltTowerMaker*
    hltIterativeCone5CaloJets
#    hltHscpJet20
)
