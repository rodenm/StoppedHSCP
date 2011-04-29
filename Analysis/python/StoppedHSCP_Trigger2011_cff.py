
# override trigger settings for 2011 triggers

import FWCore.ParameterSet.Config as cms

HLTPaths = cms.vstring(
    "HLT_JetE30_NoBPTX_v*",
    "HLT_JetE30_NoBPTX_NoHalo_v*",
    "HLT_JetE30_NoBPTX3BX_NoHalo_v*"
)

hltPathJetNoBptx = cms.untracked.string("HLT_JetE30_NoBPTX_v2")
hltPathJetNoBptxNoHalo = cms.untracked.string("HLT_JetE30_NoBPTX_NoHalo_v4")
hltPathJetNoBptx3BXNoHalo = cms.untracked.string("HLT_JetE30_NoBPTX3BX_NoHalo_v4")
hltL3Tag = cms.untracked.InputTag("hltStoppedHSCPTight1CaloJetEnergy30","","HLT")
