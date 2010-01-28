#
#  produce stopped HSCP TTree
#  assumes RAW, HLT, RECO data present
#  Run this on StoppedHSCP Skim
#
import FWCore.ParameterSet.Config as cms

from StoppedHSCP.Analysis.stoppedHSCPTree_cfg import *

# change Global Tag
#process.GlobalTag.globaltag = "STARTUP3X_V8I::All" # MC
process.GlobalTag.globaltag = "GR09_R_V5::All"  # collisions reprocessing
#process.GlobalTag.globaltag = "GR09_31X_V5P::All"  # CRAFT 09
#process.GlobalTag.globaltag = "CRAFT08_R_V1::All"  # CRAFT 08

# input files
readFiles.extend( [
    'rfio:/castor/cern.ch/user/j/jbrooke/hscp/test/Calo_CRAFT09-GR09_31X_V5P_StoppedHSCP-332_v4_RAW-RECO_111039_test.root'
    ] )


