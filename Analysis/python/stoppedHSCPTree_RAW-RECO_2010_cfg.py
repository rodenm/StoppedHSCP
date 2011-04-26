# run on RAW+RECO

import FWCore.ParameterSet.Config as cms

from StoppedHSCP.Analysis.stoppedHSCPTree_Master_cfg import *

from StoppedHSCP.Analysis.stoppedHSCP_Trigger2010_cff import *

process.hltHighLevel.HLTPaths = HLTPaths
process.stoppedHSCPTree.hltPathJetNoBptx = hltPathJetNoBptx
process.stoppedHSCPTree.hltPathJetNoBptxNoHalo = hltPathJetNoBptxNoHalo
process.stoppedHSCPTree.hltPathJetNoBptx3BXNoHalo = hltPathJetNoBptx3BXNoHalo
process.stoppedHSCPTree.hltL3Tag = hltL3Tag
