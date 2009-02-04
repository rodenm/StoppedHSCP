# skim events that pass L1_SingleJet10_00001


import FWCore.ParameterSet.Config as cms

process = cms.Process('SKIM')

# import of standard configurations
process.load('Configuration/StandardSequences/Services_cff')
process.load('FWCore/MessageService/MessageLogger_cfi')
process.load('Configuration/StandardSequences/MixingNoPileUp_cff')
process.load('Configuration/StandardSequences/GeometryPilot2_cff')
process.load('Configuration/StandardSequences/MagneticField_38T_cff')
process.load('Configuration/StandardSequences/RawToDigi_Data_cff')
process.load('Configuration/StandardSequences/Reconstruction_cff')
process.load('Configuration/StandardSequences/EndOfProcess_cff')
process.load('Configuration/StandardSequences/FrontierConditions_GlobalTag_cff')
process.load('Configuration/EventContent/EventContent_cff')

process.configurationMetadata = cms.untracked.PSet(
    version = cms.untracked.string('$Revision: 1.1 $'),
    annotation = cms.untracked.string('myreco nevts:1'),
    name = cms.untracked.string('PyReleaseValidation')
)
process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(2000)
)
process.options = cms.untracked.PSet(
    Rethrow = cms.untracked.vstring('ProductNotFound')
)

# Output definition
process.output = cms.OutputModule("PoolOutputModule",
    outputCommands = cms.untracked.vstring("keep *"),
    fileName = cms.untracked.string("skim_L1SingleJet10.root"),
    SelectEvents = cms.untracked.PSet(
        SelectEvents = cms.vstring('p')
    ),
    dataset = cms.untracked.PSet(
        dataTier = cms.untracked.string('RAW'),
        filterName = cms.untracked.string('L1_SingleJet10')
    )
)

# filter
process.GlobalTag.globaltag = 'CRAFT_V4P::All'
process.load("L1TriggerConfig.L1GtConfigProducers.L1GtConfig_cff")
process.load("L1TriggerConfig.L1GtConfigProducers.Luminosity.startup.L1Menu_startup2_v2_Unprescaled_cff")

process.hltTriggerType = cms.EDFilter( "TriggerTypeFilter",
    InputLabel = cms.string( "source" ),
    TriggerFedId = cms.int32( 812 ),
    SelectedTriggerType = cms.int32( 1 )
)
process.hltGtDigis = cms.EDProducer( "L1GlobalTriggerRawToDigi",
    DaqGtInputTag = cms.InputTag( "source" ),
    DaqGtFedId = cms.untracked.int32( 813 ),
    ActiveBoardsMask = cms.uint32( 0x101 ),
    UnpackBxInEvent = cms.int32( 1 )
)
process.load("L1Trigger.Skimmer.l1Filter_cfi")
process.l1Filter.inputTag = cms.InputTag("hltGtDigis")
process.l1Filter.algorithms = cms.vstring('L1_SingleJet10_00001')

# path 
process.p = cms.Path ( process.hltTriggerType * process.hltGtDigis * process.l1Filter )
process.e = cms.EndPath ( process.output )

# Input source
process.source = cms.Source("PoolSource",
   fileNames = cms.untracked.vstring(
       '/store/data/Commissioning08/Calo/RAW/v1/000/068/021/6478CD36-F9A5-DD11-AF2D-000423D98B5C.root',
       '/store/data/Commissioning08/Calo/RAW/v1/000/068/021/420F0B1B-FEA5-DD11-987C-000423D95030.root',
       '/store/data/Commissioning08/Calo/RAW/v1/000/068/021/D40320CA-03A6-DD11-AF22-000423D99614.root',
       '/store/data/Commissioning08/Calo/RAW/v1/000/068/021/3EED9AD8-FEA5-DD11-A975-000423D98C20.root',
       '/store/data/Commissioning08/Calo/RAW/v1/000/068/021/C49BC97E-FFA5-DD11-805A-001617E30D38.root',
       '/store/data/Commissioning08/Calo/RAW/v1/000/068/021/32F11468-FDA5-DD11-9394-001617E30D00.root',
       '/store/data/Commissioning08/Calo/RAW/v1/000/068/021/9264B7F4-E6A5-DD11-85FD-000423D99B3E.root',
       '/store/data/Commissioning08/Calo/RAW/v1/000/068/021/F61B221F-EBA5-DD11-92AD-00161757BF42.root',
       '/store/data/Commissioning08/Calo/RAW/v1/000/068/021/2AA99CA0-E7A5-DD11-90A7-0030487D1BCC.root',
       '/store/data/Commissioning08/Calo/RAW/v1/000/068/021/8CBE8340-0CA6-DD11-B2FD-000423D9A2AE.root'
   )
)
