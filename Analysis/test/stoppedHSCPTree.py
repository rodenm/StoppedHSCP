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

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )

# input files
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring()
process.source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
        '/store/data/Run2011A/MinimumBias/AOD/PromptReco-v1/000/160/853/E87F802E-4F53-E011-BE87-001617C3B6DE.root',
        '/store/data/Run2011A/MinimumBias/AOD/PromptReco-v1/000/160/853/74AC62A9-4D53-E011-8CE4-0030487C635A.root',
        '/store/data/Run2011A/MinimumBias/AOD/PromptReco-v1/000/160/853/309B4830-4F53-E011-B5F7-001D09F2441B.root',
        '/store/data/Run2011A/MinimumBias/AOD/PromptReco-v1/000/160/853/20250333-4F53-E011-860B-0019B9F70607.root',
        '/store/data/Run2011A/MinimumBias/AOD/PromptReco-v1/000/160/853/0609E301-5453-E011-B5E7-0030487CD906.root'
        #'/store/data/Run2011A/MinimumBias/AOD/PromptReco-v1/000/160/497/D404CDF5-5E50-E011-AA95-003048F024FA.root'
    ] );




