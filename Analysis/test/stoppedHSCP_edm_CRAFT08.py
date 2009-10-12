import FWCore.ParameterSet.Config as cms

process = cms.Process("SHSCP")

# import of standard configurations
process.load('Configuration/StandardSequences/Services_cff')
process.load('FWCore/MessageService/MessageLogger_cfi')
#process.load('Configuration/StandardSequences/MixingNoPileUp_cff')
process.load('Configuration/StandardSequences/GeometryIdeal_cff')
process.load('Configuration/StandardSequences/RawToDigi_Data_cff')
process.load('Configuration/StandardSequences/ReconstructionCosmics_cff')
process.load('DQMOffline/Configuration/DQMOfflineCosmics_cff')
process.load('Configuration/StandardSequences/EndOfProcess_cff')
process.load('Configuration/StandardSequences/FrontierConditions_GlobalTag_cff')
process.load('Configuration/EventContent/EventContentCosmics_cff')
# Magnetic field: force mag field to be 3.8 tesla
process.load("Configuration.StandardSequences.MagneticField_38T_cff")
# Conditions (Global Tag is used here):
process.GlobalTag.globaltag = "CRAFT0831X_V3::All"

process.maxEvents = cms.untracked.PSet(  input = cms.untracked.int32(-1))

process.load('Configuration/StandardSequences/Services_cff')
process.load('FWCore/MessageService/MessageLogger_cfi')
process.MessageLogger.cerr.INFO.limit = cms.untracked.int32(10)


#Drop old reco
process.source = cms.Source("PoolSource",
#    skipEvents = cms.untracked.uint32(523),
    fileNames = cms.untracked.vstring(
#        '/store/data/Commissioning08/Calo/RAW/v1/000/068/021/002453BF-E9A5-DD11-971F-001617C3B5F4.root'
        '/store/data/Commissioning08/Cosmics/RAW-RECO/CRAFT_ALL_V9_SuperPointing_225-v3/0012/1A8C28D2-0402-DE11-84C0-0018F3D09644.root'
#    '/store/data/Commissioning08/Cosmics/RAW-RECO/CRAFT_ALL_V9_SuperPointing_225-v3/0006/20993712-7C00-DE11-8BAA-003048678B5E.root',
#    '/store/data/Commissioning08/Cosmics/RAW-RECO/CRAFT_ALL_V9_SuperPointing_225-v3/0007/7AC674EA-7F00-DE11-A0AB-0018F3D09706.root',
#    '/store/data/Commissioning08/Cosmics/RAW-RECO/CRAFT_ALL_V9_SuperPointing_225-v3/0008/5EF7C8EC-9B00-DE11-B1C5-00304867920C.root'
    ),
    inputCommands = cms.untracked.vstring('drop *')
)
process.source.inputCommands.extend(process.RAWEventContent.outputCommands)
process.source.inputCommands.append('drop *_*_*_Rec')
process.source.inputCommands.append('keep *_eventAuxiliaryHistoryProducer_*_*')
process.source.dropDescendantsOfDroppedBranches=cms.untracked.bool(False)


# L1 filter
process.load('L1Trigger/Skimmer/l1Filter_cfi')
process.l1Filter.algorithms = cms.vstring("L1_SingleJet10")

# re-run HLT
process.load('StoppedHSCP.Analysis.HLT_StoppedHSCP_cff')

# HLT filter
import HLTrigger.HLTfilters.hltHighLevel_cfi
process.HLTFilter = HLTrigger.HLTfilters.hltHighLevel_cfi.hltHighLevel.clone()
process.HLTFilter.TriggerResultsTag = cms.InputTag("TriggerResults","","SHSCP")
process.HLTFilter.HLTPaths = cms.vstring("HLT_StoppedHSCP_8E29")

# HSCP Tree
process.load('StoppedHSCP/Analysis/stoppedHSCPTree_cfi')
process.stoppedHSCPTree.l1JetsTag = cms.untracked.string("hltL1extraParticles")

process.TFileService = cms.Service("TFileService",
    fileName = cms.string('stoppedHSCPTree.root')
)


# Path and EndPath definitions
process.myPath = cms.Path(
    process.HLTFilter
    +process.RawToDigi
    +process.l1Filter
    +process.reconstructionCosmics
#    +process.stoppedHSCPTree
)

# write EDM file
process.load('StoppedHSCP.Analysis.StoppedHSCP_EventContent_cff')

process.output = cms.OutputModule(
    "PoolOutputModule",
    fileName = cms.untracked.string('stoppedHSCP_edm.root'),
#    SelectEvents = cms.untracked.PSet(
#        SelectEvents = cms.vstring("myPath")
#        ),
    outputCommands = process.SHSCP_EventContent.outputCommands

)
                                  
process.endpath = cms.EndPath(
    process.output
)


# schedule
process.schedule = cms.Schedule(
    process.HLT_StoppedHSCP_8E29,
    process.myPath,
    process.endpath
)
