# Auto generated configuration file
# using: 
# Revision: 1.71 
# Source: /cvs_server/repositories/CMSSW/CMSSW/Configuration/PyReleaseValidation/python/ConfigBuilder.py,v 
import FWCore.ParameterSet.Config as cms

process = cms.Process('RECO')

# import of standard configurations
process.load('Configuration/StandardSequences/Services_cff')
process.load('FWCore/MessageService/MessageLogger_cfi')
process.load('Configuration/StandardSequences/Generator_cff')
process.load('Configuration/StandardSequences/MixingNoPileUp_cff')
process.load('Configuration/StandardSequences/GeometryPilot2_cff')
process.load('Configuration/StandardSequences/MagneticField_38T_cff')
process.load('Configuration/StandardSequences/Generator_cff')
#process.load('Configuration/StandardSequences/VtxSmearedEarly10TeVCollision_cff')
process.load('Configuration/StandardSequences/Sim_cff')
process.load('SimG4Core/CustomPhysics/CustomPhysics_cfi')
process.load('Configuration/StandardSequences/Digi_cff')
process.load('Configuration/StandardSequences/SimL1Emulator_cff')
process.load('L1TriggerConfig/L1GtConfigProducers/Luminosity/lumi1030.L1Menu2008_2E30_Unprescaled_cff')
process.load('Configuration/StandardSequences/DigiToRaw_cff')
process.load('Configuration/StandardSequences/RawToDigi_cff')
process.load('Configuration/StandardSequences/Reconstruction_cff')
process.load('Configuration/StandardSequences/FrontierConditions_GlobalTag_cff')
#process.load('HLTrigger/Configuration/HLT_2E30_cff')
process.load('Configuration/StandardSequences/L1Extra_cff')
process.load('Configuration/EventContent/EventContent_cff')

process.configurationMetadata = cms.untracked.PSet(
    version = cms.untracked.string('$Revision: 1.1 $'),
    annotation = cms.untracked.string('TTbar.cfi nevts:1'),
    name = cms.untracked.string('PyReleaseValidation')
)

process.options = cms.untracked.PSet(
    Rethrow = cms.untracked.vstring('ProductNotFound')
)
# Input source

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(10000)
)

process.source = cms.Source("PoolSource",
    fileNames=cms.untracked.vstring(
    'rfio:/castor/cern.ch/user/j/jbrooke/hscp/sim_v5/stoppedHSCP_MASSPOINT.root'))
    


      

process.g4SimHits.Physics = cms.PSet(
    process.customPhysicsSetup,
    GFlashEmin = cms.double(1.0),
    G4BremsstrahlungThreshold = cms.double(0.5),
    DefaultCutValue = cms.double(.01),
    CutsPerRegion = cms.bool(True),
    Verbosity = cms.untracked.int32(0),
    GFlashEToKill = cms.double(0.1),
    GFlashEmax = cms.double(1000000.0),
    type = cms.string('SimG4Core/Physics/CustomPhysics'),
    DummyEMPhysics = cms.bool(True)
)



from SimG4Core.Application.hectorParameter_cfi import *
    
process.g4SimHits.Generator = cms.PSet(
       HectorEtaCut,
 # string HepMCProductLabel = "VtxSmeared"
       HepMCProductLabel = cms.string('source'),
       ApplyPCuts = cms.bool(False),
       MinPCut = cms.double(0.0001), ## the pt-cut is in GeV (CMS conventions)
       MaxPCut = cms.double(99999.0), ## the ptmax=99.TeV in this case
       ApplyEtaCuts = cms.bool(False),
       MinEtaCut = cms.double(-5.5),
       MaxEtaCut = cms.double(5.5),
       ApplyPhiCuts = cms.bool(False),
       MinPhiCut = cms.double(-3.14159265359), ## in radians
       MaxPhiCut = cms.double(3.14159265359), ## according to CMS conventions
       RDecLenCut = cms.double(0.01), ## the minimum decay length in cm (!) for mother tracking
       Verbosity = cms.untracked.int32(0)
)




process.hltGtDigis = cms.EDProducer( "L1GlobalTriggerRawToDigi",
    DaqGtInputTag = cms.InputTag( "rawDataCollector" ),
    DaqGtFedId = cms.untracked.int32( 813 ),
    ActiveBoardsMask = cms.uint32( 0x101 ),
    UnpackBxInEvent = cms.int32( 1 )
)
process.hltGctDigis = cms.EDProducer( "GctRawToDigi",
    inputLabel = cms.InputTag( "rawDataCollector" ),
    gctFedId = cms.int32( 745 ),
    hltMode = cms.bool( False ),
    grenCompatibilityMode = cms.bool( False )
)
process.hltL1GtObjectMap = cms.EDProducer( "L1GlobalTrigger",
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

process.hltL1extraParticles = cms.EDProducer( "L1ExtraParticlesProd",
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


process.TFileService = cms.Service("TFileService",
    fileName = cms.string('GenSimReco_MASSPOINT.root')
)




process.l1jetfilter = cms.EDFilter("L1JetFltr",
    EMinCut = cms.untracked.double(0.0),
    EMaxCut = cms.untracked.double(10000.0),
    ETMinCut = cms.untracked.double(15.0),
    ETMaxCut = cms.untracked.double(10000.0),
    EtaMinCut = cms.untracked.double(-5.5),
    EtaMaxCut = cms.untracked.double(5.5),
    BranchTag = cms.untracked.string("hltL1extraParticles"),
)





# Analyzers
#########


process.an_L1 = cms.EDFilter("GlobalRunAnalyser",
    IncludeJetDetails=cms.untracked.bool(True),
    IncludeDigisOld=cms.untracked.bool(True),
    IncludeCaloTowers=cms.untracked.bool(True),
    IncludeRecHits=cms.untracked.bool(False),                                 
    IncludeMC=cms.untracked.bool(True),
    IncludeJets=cms.untracked.bool(True),
    IncludeMuons=cms.untracked.bool(True)                                   
)                                      


process.an_HLT = cms.EDFilter("GlobalRunAnalyser",
    IncludeJetDetails=cms.untracked.bool(True),
    IncludeDigisOld=cms.untracked.bool(True),
    IncludeCaloTowers=cms.untracked.bool(True),
    IncludeRecHits=cms.untracked.bool(False),                                 
    IncludeMC=cms.untracked.bool(True),
    IncludeJets=cms.untracked.bool(True),
    IncludeMuons=cms.untracked.bool(True)                                      
)

process.an_All = cms.EDFilter("GlobalRunAnalyser",
    IncludeJetDetails=cms.untracked.bool(True),
    IncludeDigisOld=cms.untracked.bool(True),
    IncludeCaloTowers=cms.untracked.bool(True),
    IncludeRecHits=cms.untracked.bool(False),                                 
    IncludeMC=cms.untracked.bool(True),
    IncludeJets=cms.untracked.bool(True),
    IncludeMuons=cms.untracked.bool(True)                                      
)




# Filters and cuts
#########


                             

process.topncalocut = cms.EDFilter("CaloFilter",
                               
    n60MinThreshold=cms.untracked.int32(0),
    n90MinThreshold=cms.untracked.int32(0),
    n60MaxThreshold=cms.untracked.int32(100),
    n90MaxThreshold=cms.untracked.int32(100),
    ETMinThreshold=cms.untracked.double(0.),
    ETMaxThreshold=cms.untracked.double(10000.),
    EMinThreshold=cms.untracked.double(0.),
    EMaxThreshold=cms.untracked.double(10000 ),
    EtaMinThreshold=cms.untracked.double(-1.3),
    EtaMaxThreshold=cms.untracked.double(1.3),
    CaloTowerVeto=cms.untracked.bool(True),
    CaloTowerCount=cms.untracked.int32(5),
    CaloTowerEMin=cms.untracked.double(0),
    NOver5=cms.untracked.int32(100),
  
                                   
)

process.n90cut = cms.EDFilter("CaloFilter",
                   
    n60MinThreshold=cms.untracked.int32(0),
    n90MinThreshold=cms.untracked.int32(3),
    n60MaxThreshold=cms.untracked.int32(100),
    n90MaxThreshold=cms.untracked.int32(100),
    ETMinThreshold=cms.untracked.double(0.),
    ETMaxThreshold=cms.untracked.double(10000.),
    EMinThreshold=cms.untracked.double(0.),
    EMaxThreshold=cms.untracked.double(10000 ),
    EtaMinThreshold=cms.untracked.double(-1.3),
    EtaMaxThreshold=cms.untracked.double(1.3),
    CaloTowerVeto=cms.untracked.bool(False),
    CaloTowerCount=cms.untracked.int32(5),
    CaloTowerEMin=cms.untracked.double(0),
    NOver5=cms.untracked.int32(100),
                               
)

process.n60cut = cms.EDFilter("CaloFilter",
                     
    n60MinThreshold=cms.untracked.int32(0),
    n90MinThreshold=cms.untracked.int32(0),
    n60MaxThreshold=cms.untracked.int32(6),
    n90MaxThreshold=cms.untracked.int32(100),
    ETMinThreshold=cms.untracked.double(0.),
    ETMaxThreshold=cms.untracked.double(10000.),
    EMinThreshold=cms.untracked.double(0.),
    EMaxThreshold=cms.untracked.double(10000 ),
    EtaMinThreshold=cms.untracked.double(-1.3),
    EtaMaxThreshold=cms.untracked.double(1.3),
    CaloTowerVeto=cms.untracked.bool(False),
    CaloTowerCount=cms.untracked.int32(5),
    CaloTowerEMin=cms.untracked.double(0),
    NOver5=cms.untracked.int32(100),
                             
)

process.othercalocuts = cms.EDFilter("CaloFilter",
                     
    n60MinThreshold=cms.untracked.int32(0),
    n90MinThreshold=cms.untracked.int32(0),
    n60MaxThreshold=cms.untracked.int32(100),
    n90MaxThreshold=cms.untracked.int32(100),
    ETMinThreshold=cms.untracked.double(0.),
    ETMaxThreshold=cms.untracked.double(10000.),
    EMinThreshold=cms.untracked.double(0.),
    EMaxThreshold=cms.untracked.double(10000 ),
    EtaMinThreshold=cms.untracked.double(-1.3),
    EtaMaxThreshold=cms.untracked.double(1.3),
    CaloTowerVeto=cms.untracked.bool(False),
    CaloTowerCount=cms.untracked.int32(5),
    CaloTowerEMin=cms.untracked.double(15),
    NOver5=cms.untracked.int32(100),
                                      
                                   
)



process.hltenergycut = cms.EDFilter("CaloFilter",
                   
    n60MinThreshold=cms.untracked.int32(0),
    n90MinThreshold=cms.untracked.int32(0),
    n60MaxThreshold=cms.untracked.int32(100),
    n90MaxThreshold=cms.untracked.int32(100),
    ETMinThreshold=cms.untracked.double(0.),
    ETMaxThreshold=cms.untracked.double(10000.),
    EMinThreshold=cms.untracked.double(20.),
    EMaxThreshold=cms.untracked.double(10000 ),
    EtaMinThreshold=cms.untracked.double(-3.3),
    EtaMaxThreshold=cms.untracked.double(3.3),
    CaloTowerVeto=cms.untracked.bool(False),
    CaloTowerCount=cms.untracked.int32(5),
    CaloTowerEMin=cms.untracked.double(0),
    NOver5=cms.untracked.int32(100),
    CentralEta=cms.untracked.double(3.0)                         
                                  
)


process.energycut = cms.EDFilter("CaloFilter",
                   
    n60MinThreshold=cms.untracked.int32(0),
    n90MinThreshold=cms.untracked.int32(0),
    n60MaxThreshold=cms.untracked.int32(100),
    n90MaxThreshold=cms.untracked.int32(100),
    ETMinThreshold=cms.untracked.double(0.),
    ETMaxThreshold=cms.untracked.double(10000.),
    EMinThreshold=cms.untracked.double(50.),
    EMaxThreshold=cms.untracked.double(10000 ),
    EtaMinThreshold=cms.untracked.double(-1.3),
    EtaMaxThreshold=cms.untracked.double(1.3),
    CaloTowerVeto=cms.untracked.bool(False),
    CaloTowerCount=cms.untracked.int32(5),
    CaloTowerEMin=cms.untracked.double(0),
    NOver5=cms.untracked.int32(100),
                                   
)


process.barrelonly = cms.EDFilter("CaloFilter",
                    
    n60MinThreshold=cms.untracked.int32(0),
    n90MinThreshold=cms.untracked.int32(0),
    n60MaxThreshold=cms.untracked.int32(100),
    n90MaxThreshold=cms.untracked.int32(100),
    ETMinThreshold=cms.untracked.double(0.),
    ETMaxThreshold=cms.untracked.double(10000.),
    EMinThreshold=cms.untracked.double(30),
    EMaxThreshold=cms.untracked.double(10000 ),
    EtaMinThreshold=cms.untracked.double(-1.3),
    EtaMaxThreshold=cms.untracked.double(1.3),
    CaloTowerVeto=cms.untracked.bool(False),
    CaloTowerCount=cms.untracked.int32(5),
    CaloTowerEMin=cms.untracked.double(0),
    NOver5=cms.untracked.int32(100),
    CentralEta = cms.untracked.double(3.0)
                               
)              

                             

process.noisefilter = cms.EDFilter("HLTHPDFilter",
    inputTag = cms.InputTag("hbhereco"),
    energy = cms.double(-99.0),
    hpdSpikeEnergy = cms.double(10.0),
    hpdSpikeIsolationEnergy = cms.double(1.0),
    rbxSpikeEnergy = cms.double(50.0),                               
    rbxSpikeUnbalance = cms.double(0.2)
)

process.muoncut=cms.EDFilter("MuonFilter",
    AllowMuons=cms.untracked.bool(False)
)


process.bitfilter=cms.EDFilter("RecoFilter",
     FilterCondition=cms.untracked.string("OneBit"),
     Bit1 = cms.untracked.int32(16)
)



process.load("L1TriggerConfig.L1GtConfigProducers.Luminosity.startup.L1Menu_startup2_v2_Unprescaled_cff")

process.MessageLogger.cerr.FwkReport.reportEvery = 100




# Output definition
process.output = cms.OutputModule("PoolOutputModule",
    outputCommands = process.FEVTDEBUGEventContent.outputCommands,
    fileName = cms.untracked.string('GenSimReco.root'),
    dataset = cms.untracked.PSet(
        dataTier = cms.untracked.string('GEN-SIM-DIGI-RAW-RECO'),
        filterName = cms.untracked.string('')
    ),
    SelectEvents = cms.untracked.PSet(
        SelectEvents = cms.vstring('filter_step')
    )
)

process.simGctDigis.preSamples = cms.uint32(1)
process.simGctDigis.postSamples = cms.uint32(1)
process.simRctDigis.preSamples = cms.uint32(1)
process.simRctDigis.postSamples = cms.uint32(1)
process.l1extraParticles.centralBxOnly = cms.bool(False)
process.l1extraParticles.EmulateBxInEvent = cms.uint32(3)


# Additional output definition

# Other statements
process.GlobalTag.globaltag = 'IDEAL_V9::All'

# Path and EndPath definitions

process.L1simulation_step = cms.Path(process.SimL1Emulator)
process.HLT_step = cms.Path(process.hltGtDigis*process.hltGctDigis*process.hltL1extraParticles)
process.raw2digi_step = cms.Path(process.RawToDigi)
process.reconstruction_step = cms.Path(process.reconstruction)
process.filter_step = cms.Path(process.an_All*
                               process.bitfilter *
                               process.an_L1 *
                               process.noisefilter *
                               process.hltenergycut *
                               process.an_HLT)





# Schedule definition
process.schedule = cms.Schedule(process.HLT_step,process.raw2digi_step,process.reconstruction_step,process.filter_step)

