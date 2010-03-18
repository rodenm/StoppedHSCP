#
#  produce stopped HSCP TTree
#  assumes RAW, HLT, RECO data present
#  Run this on StoppedHSCP Skim
#
import FWCore.ParameterSet.Config as cms

from StoppedHSCP.Analysis.stoppedHSCPTree_cfg import *

process.MessageLogger.cerr.threshold = ''
process.MessageLogger.cerr.FwkReport.reportEvery = 1000

# change Global Tag
process.GlobalTag.globaltag = 'GR10_P_V3::All'  # 2010 prompt reco

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(1000) )

# input files
readFiles.extend( [
       '/store/data/BeamCommissioning09/MinimumBias/RAW-RECO/18thFebPreProd_351p1_Skim_StoppedHSCP-v2/0000/F2790389-351E-DF11-B286-00237DA15C66.root'
       ] );




