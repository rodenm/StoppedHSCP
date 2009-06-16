import FWCore.ParameterSet.Config as cms

process = cms.Process("Test")

# import of standard configurations
process.load('Configuration/StandardSequences/Services_cff')
process.load('FWCore/MessageService/MessageLogger_cfi')

process.load('Configuration/StandardSequences/FrontierConditions_GlobalTag_cff')
process.GlobalTag.globaltag = "IDEAL_31X::All"

process.options = cms.untracked.PSet(
#    Rethrow = cms.untracked.vstring('ProductNotFound')
)

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(10)
)

process.load('StoppedHSCP/Analysis/stoppedHSCPTree_cfi')

process.path = cms.Path(
    process.stoppedHSCPTree
)

process.TFileService = cms.Service("TFileService",
    fileName = cms.string('stoppedHSCPTree.root')
)

process.source = cms.Source("PoolSource",
    fileNames=cms.untracked.vstring(
        '/store/relval/CMSSW_3_1_0_pre9/RelValQCD_Pt_80_120/GEN-SIM-RECO/STARTUP_31X_v1/0007/F6DE1DAA-ED4E-DE11-8A9B-001D09F25325.root',
        '/store/relval/CMSSW_3_1_0_pre9/RelValQCD_Pt_80_120/GEN-SIM-RECO/STARTUP_31X_v1/0007/F05D9103-524F-DE11-96EB-001D09F2AD4D.root',
        '/store/relval/CMSSW_3_1_0_pre9/RelValQCD_Pt_80_120/GEN-SIM-RECO/STARTUP_31X_v1/0007/F01E8CB2-F14E-DE11-B2EF-001D09F2A465.root',
        '/store/relval/CMSSW_3_1_0_pre9/RelValQCD_Pt_80_120/GEN-SIM-RECO/STARTUP_31X_v1/0007/D2AB5809-F14E-DE11-B36C-001D09F24024.root',
        '/store/relval/CMSSW_3_1_0_pre9/RelValQCD_Pt_80_120/GEN-SIM-RECO/STARTUP_31X_v1/0007/880B0814-EA4E-DE11-8BB4-001D09F276CF.root',
        '/store/relval/CMSSW_3_1_0_pre9/RelValQCD_Pt_80_120/GEN-SIM-RECO/STARTUP_31X_v1/0007/1C221D94-F04E-DE11-A9ED-001D09F23944.root',
        '/store/relval/CMSSW_3_1_0_pre9/RelValQCD_Pt_80_120/GEN-SIM-RECO/STARTUP_31X_v1/0000/F01E9FFE-5F4F-DE11-97D5-003048678FE4.root',
        '/store/relval/CMSSW_3_1_0_pre9/RelValQCD_Pt_80_120/GEN-SIM-RECO/STARTUP_31X_v1/0000/8844A4D8-734E-DE11-9208-001731AF6859.root',
        '/store/relval/CMSSW_3_1_0_pre9/RelValQCD_Pt_80_120/GEN-SIM-RECO/STARTUP_31X_v1/0000/720A062B-794E-DE11-9E6C-003048767ED5.root',
        '/store/relval/CMSSW_3_1_0_pre9/RelValQCD_Pt_80_120/GEN-SIM-RECO/STARTUP_31X_v1/0000/407B954B-764E-DE11-86B9-003048678B44.root',
        '/store/relval/CMSSW_3_1_0_pre9/RelValQCD_Pt_80_120/GEN-SIM-RECO/STARTUP_31X_v1/0000/089C14CE-814E-DE11-91EC-003048678B0E.root'
    )
)
