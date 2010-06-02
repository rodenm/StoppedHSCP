#
#  produce stopped HSCP TTree
#  assumes RAW, HLT, RECO data present
#  Run this on Stopped HSCP MC samples
#

import FWCore.ParameterSet.Config as cms

from StoppedHSCP.Analysis.stoppedHSCPTree_cfg import *

process.MessageLogger.cerr.threshold = ''
process.MessageLogger.cerr.FwkReport.reportEvery = 1000

# change Global Tag
process.GlobalTag.globaltag = "START3X_V27::All" # MC

# change RawToDigi RAW data label
process.gctDigis.inputLabel = 'rawDataCollector'
process.gtDigis.DaqGtInputTag = 'rawDataCollector'
process.hcalDigis.InputLabel = 'rawDataCollector'

process.myPath.remove(process.hltHighLevel)

# input files
readFiles.extend( [
    'file:/data/sdd1/phjjb/stoppedHSCP/stoppedHSCP_tree_MC_test/Stopped_HSCP_stage2_gluino300_100_RECO.root'
#    'file:/gpfs_phys/storm/cms/user/fedor/hscp/336/7TeV/gluino1jet/gluino_1jet_336_150_100_2.root'
    ] )

process.TFileService.fileName = cms.string('stoppedHSCPTree_gluino_1jet_336_150_100_2.root')
