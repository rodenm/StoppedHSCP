#
#  produce stopped HSCP TTree
#  assumes RAW, HLT, RECO data present
#  Run this on Stopped HSCP MC samples
#

import FWCore.ParameterSet.Config as cms

from StoppedHSCP.Analysis.stoppedHSCPTree_cfg import *

# change Global Tag
process.GlobalTag.globaltag = "STARTUP3X_V8I::All" # MC

# change RawToDigi RAW data label
process.gctDigis.inputLabel = 'rawDataCollector'
process.gtDigis.DaqGtInputTag = 'rawDataCollector'
process.hcalDigis.InputLabel = 'rawDataCollector'

process.path.remove(process.hltHighLevel)

# input files
readFiles.extend( [
    'file:/storage/phjjb/StoppedHSCP_MC_312/stoppedGluino_300_100.1K.root'
    ] )

