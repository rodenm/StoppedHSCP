#
#  produce stopped HSCP TTree
#  assumes RAW, HLT, RECO data present
#  Run this on StoppedHSCP Skim
#
import FWCore.ParameterSet.Config as cms

from StoppedHSCP.Ntuples.stoppedHSCPTree_MC_2012_cfg import *

process.MessageLogger.cerr.INFO.limit = cms.untracked.int32(10)

# change Global Tag
process.GlobalTag.globaltag = 'GR_P_V32::All'

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(10) )

# input files
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring()
process.source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
    '/store/data/Run2012A/SingleMu/RECO/PromptReco-v1/000/190/465/4EF8B039-0181-E111-98CC-003048F024DC.root'
    ] );




