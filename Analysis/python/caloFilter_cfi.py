# Ben's filter that mimics HLT

import FWCore.ParameterSet.Config as cms

caloFilter = cms.EDFilter(
    "CaloFilter",               
    n60MinThreshold = cms.untracked.int32(0),
    n90MinThreshold = cms.untracked.int32(0),
    n60MaxThreshold = cms.untracked.int32(100),
    n90MaxThreshold = cms.untracked.int32(100),
    ETMinThreshold  = cms.untracked.double(0.),
    ETMaxThreshold  = cms.untracked.double(10000.),
    EMinThreshold   = cms.untracked.double(20.),
    EMaxThreshold   = cms.untracked.double(10000 ),
    EtaMinThreshold = cms.untracked.double(-3.3),
    EtaMaxThreshold = cms.untracked.double(3.3),
    CaloTowerVeto   = cms.untracked.bool(False),
    CaloTowerCount  = cms.untracked.int32(5),
    CaloTowerEMin   = cms.untracked.double(0),
    NOver5          = cms.untracked.int32(100),
    CentralEta      = cms.untracked.double(3.0)                                                           
)
