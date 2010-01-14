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
        '/store/data/CRAFT09/Calo/RAW-RECO/StoppedHSCP-CRAFT09_R_V4_CosmicsSeq_v1/0044/0A369A8B-0EBF-DE11-B9A9-001A92971BB8.root',
        '/store/data/CRAFT09/Calo/RAW-RECO/StoppedHSCP-CRAFT09_R_V4_CosmicsSeq_v1/0041/F6D84B79-82BD-DE11-9D3C-002618943973.root'
] );


secFiles.extend( [
               ] )
