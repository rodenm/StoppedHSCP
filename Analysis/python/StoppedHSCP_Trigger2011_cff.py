
# override trigger settings for 2011 triggers

import FWCore.ParameterSet.Config as cms

HLTPaths = cms.vstring(
    "HLT_JetE30_NoBPTX_*",
    "HLT_JetE30_NoBPTX_NoHalo_*",
    "HLT_JetE30_NoBPTX3BX_NoHalo_*"
)

hltPathJetNoBptx = cms.untracked.string("HLT_JetE30_NoBPTX_*")
hltPathJetNoBptxNoHalo = cms.untracked.string("HLT_JetE30_NoBPTX_NoHalo_*")
hltPathJetNoBptx3BXNoHalo = cms.untracked.string("HLT_JetE30_NoBPTX3BX_NoHalo_*")
hltL3Tag = cms.untracked.InputTag("hltStoppedHSCP1CaloJetEnergy30","","HLT")
