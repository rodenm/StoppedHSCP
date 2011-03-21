#
#  produce stopped HSCP TTree
#  assumes RAW, HLT, RECO data present
#  Run this on StoppedHSCP Skim
#
import FWCore.ParameterSet.Config as cms

from StoppedHSCP.Analysis.stoppedHSCPTree_RECO_cfg import *

#process.MessageLogger.cerr.threshold = ''
#process.MessageLogger.cerr.FwkReport.reportEvery = 1000

process.stoppedHSCPTree.isMC = cms.untracked.bool(False)

# change Global Tag
process.GlobalTag.globaltag = 'GR10_P_V12::All'

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(10000) )

# input files
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring()
process.source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
    '/store/data/Run2011A/MinimumBias/AOD/PromptReco-v1/000/160/497/D404CDF5-5E50-E011-AA95-003048F024FA.root'
    ] );




