import FWCore.ParameterSet.Config as cms

process = cms.Process("Test")

# import of standard configurations
process.load('Configuration/StandardSequences/Services_cff')
process.load('FWCore/MessageService/MessageLogger_cfi')
process.MessageLogger.cerr.INFO.limit = cms.untracked.int32(10)

process.load('Configuration/StandardSequences/FrontierConditions_GlobalTag_cff')
process.GlobalTag.globaltag = "GR09_31X_V5P::All"

process.options = cms.untracked.PSet(
    Rethrow = cms.untracked.vstring('ProductNotFound')
)

process.load('L1Trigger/Skimmer/l1Filter_cfi')
process.l1Filter.algorithms = cms.vstring("L1_SingleJet10_NotBptxC")

# HCAL Unpacker
process.load('Configuration.StandardSequences.RawToDigi_Data_cff')

# L1 extra (missing from RECO!)
process.load('L1Trigger.Configuration.L1Extra_cff')

# Ntuple producer
process.load('StoppedHSCP/Analysis/stoppedHSCPTree_cfi')

process.TFileService = cms.Service("TFileService",
    fileName = cms.string('stoppedHSCPTree.root')
)

# debugging, utilities
process.load("HLTrigger.HLTcore.hltEventAnalyzerAOD_cfi")


# path
process.myPath = cms.Path(
#    process.hltEventAnalyzerAOD
#    process.l1Filter
    process.hcalDigis
    +process.gtDigis
    +process.gctDigis
    +process.l1extraParticles
    +process.stoppedHSCPTree
)

process.TFileService = cms.Service("TFileService",
    fileName = cms.string('stoppedHSCPTree.root')
)

#process.output = cms.OutputModule("PoolOutputModule",
#    fileName = cms.untracked.string('testStoppedHSCPTree.root'),
#    SelectEvents = cms.untracked.PSet(
#    SelectEvents = cms.vstring("myPath")
#    )
#)
#process.endpath = cms.EndPath(
#    process.output
#)

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(1000) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
process.source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)

readFiles.extend( [
'/store/data/BeamCommissioning09/MinimumBias/RAW/v1/000/124/030/EAAF17C6-6AE7-DE11-8DCB-001617DBCF6A.root'
#        '/store/data/CRAFT09/Calo/RAW-RECO/GR09_31X_V5P_StoppedHSCP-332_v4/0019/F0A84670-6F8D-DE11-ABDE-001731AF6847.root',
#        '/store/data/CRAFT09/Calo/RAW-RECO/GR09_31X_V5P_StoppedHSCP-332_v4/0019/C44B8164-6F8D-DE11-A379-0030486792AC.root',
#        '/store/data/CRAFT09/Calo/RAW-RECO/GR09_31X_V5P_StoppedHSCP-332_v4/0019/C2E5E378-6F8D-DE11-AF21-003048679168.root',
#        '/store/data/CRAFT09/Calo/RAW-RECO/GR09_31X_V5P_StoppedHSCP-332_v4/0019/AAAEAE6B-6F8D-DE11-9ECB-001A92810ADE.root',
#        '/store/data/CRAFT09/Calo/RAW-RECO/GR09_31X_V5P_StoppedHSCP-332_v4/0019/A85D8C68-6F8D-DE11-A7D3-0018F3D09604.root',
#        '/store/data/CRAFT09/Calo/RAW-RECO/GR09_31X_V5P_StoppedHSCP-332_v4/0019/9E769D95-6D8D-DE11-9165-001731AF684D.root',
] );


secFiles.extend( [
               ] )
