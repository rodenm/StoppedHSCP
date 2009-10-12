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

# raw to digi
process.load('Configuration.StandardSequences.RawToDigi_Data_cff')

#trigger validator
process.load('StoppedHSCP.Analysis.triggerValidator_cfi')

# path
process.myPath = cms.Path(
    process.gtDigis
    +process.triggerValidator
)

process.TFileService = cms.Service("TFileService",
    fileName = cms.string('trigHistos.root')
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

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
process.source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)

readFiles.extend( [
		   '/store/caf/user/jbrooke/CRAFT09_HLT_v2/stoppedHSCP_HLT_1.root',
		   '/store/caf/user/jbrooke/CRAFT09_HLT_v2/stoppedHSCP_HLT_2.root',
		   '/store/caf/user/jbrooke/CRAFT09_HLT_v2/stoppedHSCP_HLT_3.root',
		   '/store/caf/user/jbrooke/CRAFT09_HLT_v2/stoppedHSCP_HLT_4.root',
		   '/store/caf/user/jbrooke/CRAFT09_HLT_v2/stoppedHSCP_HLT_5.root',
		   '/store/caf/user/jbrooke/CRAFT09_HLT_v2/stoppedHSCP_HLT_6.root',
		   '/store/caf/user/jbrooke/CRAFT09_HLT_v2/stoppedHSCP_HLT_7.root',
		   '/store/caf/user/jbrooke/CRAFT09_HLT_v2/stoppedHSCP_HLT_8.root',
] )


secFiles.extend( [
               ] )
