
# override trigger settings for 2011 triggers

import FWCore.ParameterSet.Config as cms
#Wild cards are okay for these names
HLTPaths = cms.vstring(
    "HLT_JetE30_NoBPTX_v*",
    "HLT_JetE30_NoBPTX_NoHalo_v*",
    "HLT_JetE30_NoBPTX3BX_NoHalo_v*",
    "HLT_JetE50_NoBPTX3BX_NoHalo_v*"
)

# Wild cards are not currently supported for these strings
hltPathJetNoBptx = cms.untracked.string("HLT_JetE30_NoBPTX_v")
hltPathJetNoBptxNoHalo = cms.untracked.string("HLT_JetE30_NoBPTX_NoHalo_v")
hltPathJetNoBptx3BXNoHalo = cms.untracked.string("HLT_JetE30_NoBPTX3BX_NoHalo_v")
hltPathJetE50NoBptx3BXNoHalo = cms.untracked.string("HLT_JetE50_NoBPTX3BX_NoHalo_v")

hltL3Tag = cms.untracked.InputTag("hltStoppedHSCPTight1CaloJetEnergy30","","HLT")
# Use the tag below for fills 1795 and above:
#hltL3Tag = cms.untracked.InputTag("hltStoppedHSCPCaloJetEnergy50","","HLT")
