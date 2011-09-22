
# remove pieces of master config so it can run on RECO only

import FWCore.ParameterSet.Config as cms

from StoppedHSCP.Ntuples.stoppedHSCPTree_Master_cfg import *

process.ntuple.remove(process.gctDigis)
process.ntuple.remove(process.gtDigis)
process.ntuple.remove(process.l1extraParticles)
process.ntuple.remove(process.hcalDigis)

# 2011 trigger config

from StoppedHSCP.Ntuples.StoppedHSCP_Trigger2011_cff import *

process.hltHighLevel.HLTPaths = HLTPaths
process.stoppedHSCPTree.hltPathJetNoBptx = hltPathJetNoBptx
process.stoppedHSCPTree.hltPathJetNoBptxNoHalo = hltPathJetNoBptxNoHalo
process.stoppedHSCPTree.hltPathJetNoBptx3BXNoHalo = hltPathJetNoBptx3BXNoHalo
process.stoppedHSCPTree.hltL3Tag = hltL3Tag
process.stoppedHSCPTree.doDigis=False 
