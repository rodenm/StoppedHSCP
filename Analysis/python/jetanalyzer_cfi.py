import FWCore.ParameterSet.Config as cms

jetanalyzer = cms.EDAnalyzer('JetAnalyzer',
                             jets = cms.InputTag( "iterativeCone5CaloJets" ))
