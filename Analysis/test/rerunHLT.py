import FWCore.ParameterSet.Config as cms

process = cms.Process("HLT2")

# import of standard configurations
process.load('Configuration/StandardSequences/Services_cff')
process.load('FWCore/MessageService/MessageLogger_cfi')
#process.load('Configuration/StandardSequences/MixingNoPileUp_cff')
process.load('Configuration/StandardSequences/GeometryIdeal_cff')

process.load('Configuration/StandardSequences/EndOfProcess_cff')
process.load('Configuration/StandardSequences/FrontierConditions_GlobalTag_cff')
process.load('Configuration/EventContent/EventContentCosmics_cff')
# Magnetic field: force mag field to be 3.8 tesla
process.load("Configuration.StandardSequences.MagneticField_38T_cff")
# Conditions (Global Tag is used here):
process.GlobalTag.globaltag = "GR09_P_V1::All"

process.load('Configuration/StandardSequences/Services_cff')
process.load('FWCore/MessageService/MessageLogger_cfi')
#process.MessageLogger.cerr.INFO.limit = cms.untracked.int32(10)
process.MessageLogger.cerr.threshold = ''
process.MessageLogger.cerr.FwkReport.reportEvery = 1000

# re-run HLT
process.load('HLTrigger.Configuration.HLT_8E29_cff')

# adjust for data instead of MC
process.hltGctDigis.inputLabel = cms.InputTag( "source" )
process.hltGtDigis.DaqGtInputTag = cms.InputTag( "source" )
process.hltHcalDigis.InputLabel = cms.InputTag( "source" )

#fix bugs in config
process.hltStoppedHSCPTowerMakerForAll.hoInput = cms.InputTag( '' )
process.hltStoppedHSCPTowerMakerForAll.hfInput = cms.InputTag( '' )
process.hltStoppedHSCPTowerMakerForAll.ecalInputs = cms.VInputTag( '', '' )


process.output = cms.OutputModule(
    "PoolOutputModule",
    fileName = cms.untracked.string('stoppedHSCP_rerunHLT.root'),
    SelectEvents = cms.untracked.PSet(
        SelectEvents = cms.vstring("HLT_StoppedHSCP_8E29")
        ),
    outputCommands = cms.untracked.vstring("keep *")

)
                                  
process.endpath = cms.EndPath(
    process.output
)

# schedule
process.schedule = cms.Schedule(
    process.HLT_StoppedHSCP_8E29
)
process.schedule.append(process.endpath)


process.maxEvents = cms.untracked.PSet(  input = cms.untracked.int32(100))

#Drop old reco
process.source = cms.Source("PoolSource",
#    skipEvents = cms.untracked.uint32(523),
    fileNames = cms.untracked.vstring(
     'rfio:/castor/cern.ch/user/j/jbrooke/hscp/test/Calo_CRAFT09-GR09_31X_V5P_StoppedHSCP-332_v4_RAW-RECO_111039_test.root'
    )
)
