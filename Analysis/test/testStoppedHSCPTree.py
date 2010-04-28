import FWCore.ParameterSet.Config as cms

process = cms.Process("Test")

# import of standard configurations
process.load('Configuration/StandardSequences/Services_cff')
process.load('FWCore/MessageService/MessageLogger_cfi')
process.MessageLogger.cerr.INFO.limit = cms.untracked.int32(10)

process.load('Configuration/StandardSequences/FrontierConditions_GlobalTag_cff')
process.GlobalTag.globaltag = "GR10_P_V4::All"

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
process.load('StoppedHSCP/Analysis/stoppedHSCPRunTree_cfi')

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
    +process.scalersRawToDigi
    +process.stoppedHSCPTree
    +process.stoppedHSCPRunTree
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
        '/store/data/Commissioning10/MinimumBias/RAW-RECO/v8/000/132/918/FED85076-BA43-DF11-9ED1-00E08178C025.root',
        '/store/data/Commissioning10/MinimumBias/RAW-RECO/v8/000/132/918/64DC6C15-B443-DF11-8C1A-0025B3E05CAA.root',
        '/store/data/Commissioning10/MinimumBias/RAW-RECO/v8/000/132/918/0A189C19-B843-DF11-9F3D-00E08178C025.root',
        '/store/data/Commissioning10/MinimumBias/RAW-RECO/v8/000/132/918/08408058-B543-DF11-B5E0-003048D46034.root'
] );


secFiles.extend( [
               ] )
