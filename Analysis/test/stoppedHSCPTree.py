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
#process.GlobalTag.globaltag = "STARTUP3X_V8I::All" # MC
process.GlobalTag.globaltag = 'GR09_R_35X_V2::All'  # collision 09 35X reprocessing
#process.GlobalTag.globaltag = "GR09_R_V5::All"  # collisions Dec19th rereco
#process.GlobalTag.globaltag = "GR09_P_V1::All"   # CRAFT 09 HLT reskim
#process.GlobalTag.globaltag = "CRAFT09_R2_V2::All"   # CRAFT 09 re-reco
#process.GlobalTag.globaltag = "GR09_31X_V5P::All"  # CRAFT 09 prompt reco
#process.GlobalTag.globaltag = "CRAFT08_R_V1::All"  # CRAFT 08

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(1000) )

# input files
readFiles.extend( [

       '/store/data/BeamCommissioning09/MinimumBias/RAW-RECO/18thFebPreProd_351p1_Skim_StoppedHSCP-v2/0000/F2790389-351E-DF11-B286-00237DA15C66.root'
#       '/store/data/BeamCommissioning09/MinimumBias/RAW-RECO/18thFebPreProd_351p1_Skim_StoppedHSCP-v2/0000/EE0ADD92-381E-DF11-98C1-001E0B5FE438.root',
#       '/store/data/BeamCommissioning09/MinimumBias/RAW-RECO/18thFebPreProd_351p1_Skim_StoppedHSCP-v2/0000/B43234C1-511E-DF11-8B0C-00237DA13FB6.root',
#       '/store/data/BeamCommissioning09/MinimumBias/RAW-RECO/18thFebPreProd_351p1_Skim_StoppedHSCP-v2/0000/A677D2CF-361E-DF11-9841-001F29C4A352.root',
#       '/store/data/BeamCommissioning09/MinimumBias/RAW-RECO/18thFebPreProd_351p1_Skim_StoppedHSCP-v2/0000/9EE5775E-421E-DF11-A3C7-001E0BEACAB8.root',
#       '/store/data/BeamCommissioning09/MinimumBias/RAW-RECO/18thFebPreProd_351p1_Skim_StoppedHSCP-v2/0000/9648CD9E-331E-DF11-9CBE-001CC47A52B6.root',
#       '/store/data/BeamCommissioning09/MinimumBias/RAW-RECO/18thFebPreProd_351p1_Skim_StoppedHSCP-v2/0000/929EB7B1-341E-DF11-AEF6-001E0B472CEE.root',
#       '/store/data/BeamCommissioning09/MinimumBias/RAW-RECO/18thFebPreProd_351p1_Skim_StoppedHSCP-v2/0000/90B20CD0-361E-DF11-8F79-00237DF345D6.root',
#       '/store/data/BeamCommissioning09/MinimumBias/RAW-RECO/18thFebPreProd_351p1_Skim_StoppedHSCP-v2/0000/8C42DAD0-361E-DF11-BBBC-00237DA1A548.root',
#       '/store/data/BeamCommissioning09/MinimumBias/RAW-RECO/18thFebPreProd_351p1_Skim_StoppedHSCP-v2/0000/8C034D82-511E-DF11-A699-00237DA28240.root',
#       '/store/data/BeamCommissioning09/MinimumBias/RAW-RECO/18thFebPreProd_351p1_Skim_StoppedHSCP-v2/0000/421E9E83-511E-DF11-B22D-00237DA1A548.root',
#       '/store/data/BeamCommissioning09/MinimumBias/RAW-RECO/18thFebPreProd_351p1_Skim_StoppedHSCP-v2/0000/4094BC51-3C1E-DF11-96E7-00237DA14FF4.root'

       ] );




