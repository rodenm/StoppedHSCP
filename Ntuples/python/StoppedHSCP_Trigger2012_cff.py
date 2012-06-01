
# override trigger settings for 2011 triggers

import FWCore.ParameterSet.Config as cms


# For runs 193834-194825 the NoHalo condition was removed by Juliette due to
# the fact that the L1_SingleMuBeamHalo trigger wasn't present in the v0 L1 trigger menu


#Wild cards are okay for these names
HLTPaths = cms.vstring(
    "HLT_JetE30_NoBPTX_v*",           
    "HLT_JetE30_NoBPTX3BX_*", # HLT_JetE30_NoBPTX3BX_NoHalo_v*
    "HLT_JetE50_NoBPTX3BX_*", # HLT_JetE50_NoBPTX3BX_NoHalo_v*
    "HLT_JetE70_NoBPTX3BX_*"  # HLT_JetE70_NoBPTX3BX_NoHalo_v*
)

# Wild cards are not currently supported for these strings
hltPathJetNoBptx = cms.untracked.string("HLT_JetE30_NoBPTX_v")
hltPathJetNoBptxNoHalo = cms.untracked.string("HLT_JetE30_NoBPTX_")          # HLT_JetE30_NoBPTX_NoHalo_v
hltPathJetNoBptx3BXNoHalo = cms.untracked.string("HLT_JetE30_NoBPTX3BX_")    # HLT_JetE30_NoBPTX3BX_NoHalo_v
hltPathJetE50NoBptx3BXNoHalo = cms.untracked.string("HLT_JetE50_NoBPTX3BX_") # HLT_JetE50_NoBPTX3BX_NoHalo_v
hltPathJetE70NoBptx3BXNoHalo = cms.untracked.string("HLT_JetE70_NoBPTX3BX_") # HLT_JetE70_NoBPTX3BX_NoHalo_v

l1JetNoBptxNoHaloName = cms.untracked.string("L1_SingleJetC20_NotBptxOR")
l1Jet32NoBptxNoHaloName = cms.untracked.string("L1_SingleJetC32_NotBptxOR")

# Use the tag below for fills 1795 and above:
hltL3Tag = cms.untracked.InputTag("hltStoppedHSCPCaloJetEnergy50","","HLT")
#hltL3Tag = cms.untracked.InputTag("hltStoppedHSCP1CaloJetEnergy70","","HLT")
