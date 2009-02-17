
import FWCore.ParameterSet.Config as cms

rHadronFilter = cms.EDFilter("RHadronFilter",
                             JetThreshold = cms.untracked.double(20),
                             CentralJets  = cms.untracked.InputTag("hltL1extraParticles","Central"),
                             TauJets  = cms.untracked.InputTag("hltL1extraParticles","Tau")
                             )
