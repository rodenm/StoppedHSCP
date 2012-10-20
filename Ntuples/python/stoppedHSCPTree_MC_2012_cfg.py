
# remove pieces of master config so it can run on RECO only

import FWCore.ParameterSet.Config as cms

from StoppedHSCP.Ntuples.stoppedHSCPTree_Master_cfg import *

process.stoppedHSCPTree.isMC = cms.untracked.bool(True)

process.gctDigis.inputLabel = 'rawDataCollector'
process.gtDigis.DaqGtInputTag = 'rawDataCollector'
process.hcalDigis.InputLabel = 'rawDataCollector'


process.ntuple.remove(process.hltHighLevel)
process.ntuple.remove(process.gctDigis)
process.ntuple.remove(process.gtDigis)
process.ntuple.remove(process.l1extraParticles)
process.ntuple.remove(process.hcalDigis)
process.ntuple.remove(process.hltStoppedHSCPHpdFilter)

# 2012 trigger config  (although it's irrelevant for MC as BPTX assumed to fire for all MC)

from StoppedHSCP.Ntuples.StoppedHSCP_Trigger2012_cff import *

process.hltHighLevel.HLTPaths = HLTPaths
process.stoppedHSCPTree.hltPathJetNoBptx = hltPathJetNoBptx
process.stoppedHSCPTree.hltPathJetNoBptxNoHalo = hltPathJetNoBptxNoHalo
process.stoppedHSCPTree.hltPathJetNoBptx3BXNoHalo = hltPathJetNoBptx3BXNoHalo
process.stoppedHSCPTree.hltPathJetE50NoBptx3BXNoHalo = hltPathJetE50NoBptx3BXNoHalo
process.stoppedHSCPTree.hltPathJetE70NoBptx3BXNoHalo = hltPathJetE70NoBptx3BXNoHalo

process.stoppedHSCPTree.hltL3Tag = hltL3Tag
process.stoppedHSCPTree.doDigis=False 
