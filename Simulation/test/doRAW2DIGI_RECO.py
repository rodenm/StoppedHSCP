import sys
import StoppedHSCP.Simulation.Helper as hscp

doc = """
    doRAW2DIGI_RECO.py

    - Runs reconstruction on RAW+HLT file

    required parameters:
    rawFile          :       input RAW file
    recoFile         :       output RECO file

    optional parameters:
    globalTag        :       global tag to be used
    """

rawFile = None
recoFile = None

nEvents = -1
globalTag = 'STARTUP3X_V8M::All'

for (opt, value) in hscp.parseParams ():
    if opt == "rawFile": rawFile = value
    if opt == "recoFile": recoFile = value
    if opt == "globalTag": globalTag = value

if not rawFile or not recoFile:
    print '======> Missing parameters! <======'
    print doc
    sys.exit(1)

print 'input:', rawFile
print 'output:', recoFile
print 'Global Tag:', globalTag

    
import FWCore.ParameterSet.Config as cms

process = cms.Process('RECO')

# import of standard configurations
process.load('Configuration/StandardSequences/Services_cff')
process.load('FWCore/MessageService/MessageLogger_cfi')
process.load('Configuration/StandardSequences/MixingNoPileUp_cff')
process.load('Configuration/StandardSequences/GeometryIdeal_cff')
process.load('Configuration/StandardSequences/MagneticField_38T_cff')
process.load('Configuration/StandardSequences/RawToDigi_cff')
process.load('Configuration/StandardSequences/Reconstruction_cff')
process.load('Configuration/StandardSequences/EndOfProcess_cff')
process.load('Configuration/StandardSequences/FrontierConditions_GlobalTag_cff')
process.load('Configuration/EventContent/EventContent_cff')

process.configurationMetadata = cms.untracked.PSet(
    version = cms.untracked.string('$Revision: 1.1 $'),
    annotation = cms.untracked.string('Configuration/Generator/python/SingleMuPt1000_cfi.py nevts:10'),
    name = cms.untracked.string('PyReleaseValidation')
)
process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(nEvents)
)
process.options = cms.untracked.PSet(
    Rethrow = cms.untracked.vstring('ProductNotFound')
)
# Input source
process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring('file:'+rawFile)
)

# Output definition
process.output = cms.OutputModule("PoolOutputModule",
    splitLevel = cms.untracked.int32(0),
    outputCommands = process.RECOSIMEventContent.outputCommands,
#    outputCommands = process.FEVTEventContent.outputCommands,
    fileName = cms.untracked.string(recoFile),
    dataset = cms.untracked.PSet(
        dataTier = cms.untracked.string('GEN-SIM-RECO'),
        filterName = cms.untracked.string('')
    )
)
process.output.outputCommands.extend(['keep FEDRawDataCollection_*_*_*'])


# Additional output definition

# Other statements
process.GlobalTag.globaltag = globalTag

# Path and EndPath definitions
process.raw2digi_step = cms.Path(process.RawToDigi)
process.reconstruction_step = cms.Path(process.reconstruction)
process.endjob_step = cms.Path(process.endOfProcess)
process.out_step = cms.EndPath(process.output)

# Schedule definition
process.schedule = cms.Schedule(process.raw2digi_step,process.reconstruction_step,process.endjob_step,process.out_step)
