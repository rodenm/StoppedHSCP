import FWCore.ParameterSet.Config as cms

SHSCP_EventContent = cms.PSet(
    outputCommands = cms.untracked.vstring(
    'keep *_source_*_*',
    'keep *_TriggerResults_*_*',
    'keep *_hltTriggerSummaryAOD_*_*',
    'keep *_l1extraParticles_*_*',
    'keep *_hltL1GtObjectMap_*_*',
    'keep L1GlobalTriggerReadoutRecord_gtDigis_*_*',
    'keep *_hcalDigis_*_*',
    'keep *_towerMaker_*_*',
    'keep *_hcalnoise_*_*',
    'keep *_iterativeCone5CaloJets_*_*',
    'keep *_sisCone5CaloJets_*_*',
    'keep *_muons_*_*',
    'keep *_lhcSTAMuonsBarrelOnly_*_*',
    'keep *_lhcSTAMuonsEndCapsOnly_*_*',
    'keep *_hltHcalDigis_*_*',
    'keep *_hltHbhereco_*_*',
    'keep *_hltStoppedHSCPHpdFilter_*_*',
    'keep *_hltStoppedHSCPTowerMakerForAll_*_*',
    'keep *_hltStoppedHSCPIterativeCone5CaloJets_*_*', 
    'keep *_hltStoppedHSCP1CaloJetEnergy_*_*'
    )
)
