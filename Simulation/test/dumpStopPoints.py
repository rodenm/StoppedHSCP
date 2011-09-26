import FWCore.ParameterSet.Config as cms

process = cms.Process('SCAN')
process.load('FWCore/MessageService/MessageLogger_cfi')
process.MessageLogger.cerr.threshold = ''
process.MessageLogger.cerr.FwkReport.reportEvery = 1000

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(-1)
)

process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(
    'file:/scratch/hh/current/cms/user/ratnikov/hscp/test/HSCPstop_M_130_7TeV_pythia6_cff_py_RAW2DIGI_RECO_9_1_5hC.root')
)

process.rhStopDump = cms.EDAnalyzer (
    "RHStopDump",
    stoppedFile = cms.string("src/stoppedPoint.txt")
    )

process.rhStopDumpstep = cms.Path (process.rhStopDump)
process.shadule = cms.Schedule(process.rhStopDumpstep)
