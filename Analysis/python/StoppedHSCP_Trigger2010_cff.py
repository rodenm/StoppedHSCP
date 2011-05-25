
# override trigger settings for 2010 trigger

import FWCore.ParameterSet.Config as cms

HLTPaths = cms.vstring("HLT_StoppedHSCP*")

hltPathJetNoBptx = cms.untracked.string("HLT_StoppedHSCP")
hltPathJetNoBptxNoHalo = cms.untracked.string("")
hltPathJetNoBptx3BXNoHalo = cms.untracked.string("")
hltL3Tag = cms.untracked.InputTag("hltStoppedHSCP1CaloJetEnergy30","","HLT")

