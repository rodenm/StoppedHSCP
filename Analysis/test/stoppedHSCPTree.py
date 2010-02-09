#
#  produce stopped HSCP TTree
#  assumes RAW, HLT, RECO data present
#  Run this on StoppedHSCP Skim
#
import FWCore.ParameterSet.Config as cms

from StoppedHSCP.Analysis.stoppedHSCPTree_cfg import *

# change Global Tag
#process.GlobalTag.globaltag = "STARTUP3X_V8I::All" # MC
#process.GlobalTag.globaltag = "GR09_R_V5::All"  # collisions Dec19th rereco
#process.GlobalTag.globaltag = "GR09_P_V1::All"   # CRAFT 09 HLT reskim
process.GlobalTag.globaltag = "CRAFT09_R2_V2::All"   # CRAFT 09 re-reco
#process.GlobalTag.globaltag = "GR09_31X_V5P::All"  # CRAFT 09 prompt reco
#process.GlobalTag.globaltag = "CRAFT08_R_V1::All"  # CRAFT 08

# input files
readFiles.extend( [

    # re-reco
    '/store/user/jbrooke/StoppedHSCP_CRAFT09_rereco_v1_1/StoppedHSCP_ReReco_1.root',
    '/store/user/jbrooke/StoppedHSCP_CRAFT09_rereco_v1_1/StoppedHSCP_ReReco_2.root',
    '/store/user/jbrooke/StoppedHSCP_CRAFT09_rereco_v1_1/StoppedHSCP_ReReco_3.root',
    '/store/user/jbrooke/StoppedHSCP_CRAFT09_rereco_v1_1/StoppedHSCP_ReReco_4.root',
    '/store/user/jbrooke/StoppedHSCP_CRAFT09_rereco_v1_1/StoppedHSCP_ReReco_5.root',
    '/store/user/jbrooke/StoppedHSCP_CRAFT09_rereco_v1_1/StoppedHSCP_ReReco_6.root',
    '/store/user/jbrooke/StoppedHSCP_CRAFT09_rereco_v1_1/StoppedHSCP_ReReco_7.root',
    '/store/user/jbrooke/StoppedHSCP_CRAFT09_rereco_v1_1/StoppedHSCP_ReReco_8.root',
    '/store/user/jbrooke/StoppedHSCP_CRAFT09_rereco_v1_1/StoppedHSCP_ReReco_9.root',
    '/store/user/jbrooke/StoppedHSCP_CRAFT09_rereco_v1_1/StoppedHSCP_ReReco_10.root',
    '/store/user/jbrooke/StoppedHSCP_CRAFT09_rereco_v1_1/StoppedHSCP_ReReco_11.root'

    # HLT reskim
#    '/store/user/jbrooke/Calo/StoppedHSCP_CRAFT09_rerunHLT_v3/a9f20537e9e1239e6910ee9cb81f358d/stoppedHSCP_rerunHLT_1.root'
#    '/store/user/jbrooke/Calo/StoppedHSCP_CRAFT09_rerunHLT_v3/a9f20537e9e1239e6910ee9cb81f358d/stoppedHSCP_rerunHLT_2.root'
#    '/store/user/jbrooke/Calo/StoppedHSCP_CRAFT09_rerunHLT_v3/a9f20537e9e1239e6910ee9cb81f358d/stoppedHSCP_rerunHLT_3.root'
#    '/store/user/jbrooke/Calo/StoppedHSCP_CRAFT09_rerunHLT_v3/a9f20537e9e1239e6910ee9cb81f358d/stoppedHSCP_rerunHLT_4.root'
#    '/store/user/jbrooke/Calo/StoppedHSCP_CRAFT09_rerunHLT_v3/a9f20537e9e1239e6910ee9cb81f358d/stoppedHSCP_rerunHLT_5.root'
#    '/store/user/jbrooke/Calo/StoppedHSCP_CRAFT09_rerunHLT_v3/a9f20537e9e1239e6910ee9cb81f358d/stoppedHSCP_rerunHLT_6.root'
#    '/store/user/jbrooke/Calo/StoppedHSCP_CRAFT09_rerunHLT_v3/a9f20537e9e1239e6910ee9cb81f358d/stoppedHSCP_rerunHLT_7.root'
#    '/store/user/jbrooke/Calo/StoppedHSCP_CRAFT09_rerunHLT_v3/a9f20537e9e1239e6910ee9cb81f358d/stoppedHSCP_rerunHLT_8.root'
#    '/store/user/jbrooke/Calo/StoppedHSCP_CRAFT09_rerunHLT_v3/a9f20537e9e1239e6910ee9cb81f358d/stoppedHSCP_rerunHLT_9.root'
#    '/store/user/jbrooke/Calo/StoppedHSCP_CRAFT09_rerunHLT_v3/a9f20537e9e1239e6910ee9cb81f358d/stoppedHSCP_rerunHLT_10.root'
#    '/store/user/jbrooke/Calo/StoppedHSCP_CRAFT09_rerunHLT_v3/a9f20537e9e1239e6910ee9cb81f358d/stoppedHSCP_rerunHLT_11.root'
    ] )


