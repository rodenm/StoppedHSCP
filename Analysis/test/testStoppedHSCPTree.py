import FWCore.ParameterSet.Config as cms

process = cms.Process("Test")

# import of standard configurations
process.load('Configuration/StandardSequences/Services_cff')
process.load('FWCore/MessageService/MessageLogger_cfi')

process.load('Configuration/StandardSequences/FrontierConditions_GlobalTag_cff')
process.GlobalTag.globaltag = "CRAFT0831X_V1::All"

process.options = cms.untracked.PSet(
    Rethrow = cms.untracked.vstring('ProductNotFound')
)

process.load('L1Trigger/Skimmer/l1Filter_cfi')
process.l1Filter.algorithms = cms.vstring("L1_SingleJet10")

process.load('StoppedHSCP/Analysis/stoppedHSCPTree_cfi')

process.myPath = cms.Path(
    process.l1Filter
    +process.stoppedHSCPTree
)

process.TFileService = cms.Service("TFileService",
    fileName = cms.string('stoppedHSCPTree.root')
)

process.output = cms.OutputModule("PoolOutputModule",
    fileName = cms.untracked.string('testStoppedHSCPTree.root'),
    SelectEvents = cms.untracked.PSet(
    SelectEvents = cms.vstring("myPath")
    )
)
process.endpath = cms.EndPath(
    process.output
)

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(100000) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
process.source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
#readFiles.extend( [
#       '/store/relval/CMSSW_3_1_0/RelValQCD_Pt_80_120/GEN-SIM-RECO/STARTUP31X_V1-v1/0001/A44DEAE2-3166-DE11-96E4-001D09F24EC0.root',
#       '/store/relval/CMSSW_3_1_0/RelValQCD_Pt_80_120/GEN-SIM-RECO/STARTUP31X_V1-v1/0001/8CDE0D6C-DE66-DE11-A614-001D09F254CE.root',
#       '/store/relval/CMSSW_3_1_0/RelValQCD_Pt_80_120/GEN-SIM-RECO/STARTUP31X_V1-v1/0001/5E4083BB-3166-DE11-8863-001617C3B66C.root',
#       '/store/relval/CMSSW_3_1_0/RelValQCD_Pt_80_120/GEN-SIM-RECO/STARTUP31X_V1-v1/0001/5E36F749-3466-DE11-A205-001D09F2AD4D.root',
#       '/store/relval/CMSSW_3_1_0/RelValQCD_Pt_80_120/GEN-SIM-RECO/STARTUP31X_V1-v1/0001/225475D6-3366-DE11-B8D4-001D09F251E0.root',
#       '/store/relval/CMSSW_3_1_0/RelValQCD_Pt_80_120/GEN-SIM-RECO/STARTUP31X_V1-v1/0001/06B8E518-3466-DE11-B56E-0019B9F581C9.root' ] );

#readFiles.extend( [
#       '/store/relval/CMSSW_3_1_0/RelValMinBias/GEN-SIM-RECO/STARTUP31X_V1-v1/0001/6223D589-DE66-DE11-BF72-001D09F27067.root',
#       '/store/relval/CMSSW_3_1_0/RelValMinBias/GEN-SIM-RECO/STARTUP31X_V1-v1/0001/26BEEE9E-6A66-DE11-910B-001D09F2841C.root' ] );

readFiles.extend( [
       '/store/relval/CMSSW_3_1_0/RelValCosmics/RECO/CRAFT0831X_V1-v1/0002/8676AA9A-E066-DE11-81F9-001D09F23C73.root',
       '/store/relval/CMSSW_3_1_0/RelValCosmics/RECO/CRAFT0831X_V1-v1/0002/245612A9-E266-DE11-8754-000423D94C68.root',
       '/store/relval/CMSSW_3_1_0/RelValCosmics/RECO/CRAFT0831X_V1-v1/0002/0056351D-E366-DE11-933F-000423D94E1C.root',
       '/store/relval/CMSSW_3_1_0/RelValCosmics/RECO/CRAFT0831X_V1-v1/0001/FC2906A2-D166-DE11-8369-001D09F2AD4D.root',
       '/store/relval/CMSSW_3_1_0/RelValCosmics/RECO/CRAFT0831X_V1-v1/0001/FA50B373-D866-DE11-872B-001D09F253C0.root',
       '/store/relval/CMSSW_3_1_0/RelValCosmics/RECO/CRAFT0831X_V1-v1/0001/EE979BDD-D766-DE11-9C9A-001D09F25217.root',
       '/store/relval/CMSSW_3_1_0/RelValCosmics/RECO/CRAFT0831X_V1-v1/0001/E8DED3F2-DA66-DE11-81F1-000423D8FA38.root',
       '/store/relval/CMSSW_3_1_0/RelValCosmics/RECO/CRAFT0831X_V1-v1/0001/E6AD8847-DC66-DE11-A258-000423D990CC.root',
       '/store/relval/CMSSW_3_1_0/RelValCosmics/RECO/CRAFT0831X_V1-v1/0001/E673A002-DA66-DE11-A4A4-001617DBD472.root',
       '/store/relval/CMSSW_3_1_0/RelValCosmics/RECO/CRAFT0831X_V1-v1/0001/E28D0501-CF66-DE11-914D-000423D94534.root',
       '/store/relval/CMSSW_3_1_0/RelValCosmics/RECO/CRAFT0831X_V1-v1/0001/D8EEE96E-D566-DE11-A6EF-000423D99CEE.root',
       '/store/relval/CMSSW_3_1_0/RelValCosmics/RECO/CRAFT0831X_V1-v1/0001/D6D6A312-D866-DE11-A94C-001D09F24024.root',
       '/store/relval/CMSSW_3_1_0/RelValCosmics/RECO/CRAFT0831X_V1-v1/0001/D6B0147C-D866-DE11-997C-001D09F24D67.root',
       '/store/relval/CMSSW_3_1_0/RelValCosmics/RECO/CRAFT0831X_V1-v1/0001/D4ED48E2-D066-DE11-BF47-001D09F2432B.root',
       '/store/relval/CMSSW_3_1_0/RelValCosmics/RECO/CRAFT0831X_V1-v1/0001/CAE86B91-D666-DE11-BC5D-000423D33970.root',
       '/store/relval/CMSSW_3_1_0/RelValCosmics/RECO/CRAFT0831X_V1-v1/0001/C825BAF5-D966-DE11-83E9-001D09F23C73.root',
       '/store/relval/CMSSW_3_1_0/RelValCosmics/RECO/CRAFT0831X_V1-v1/0001/BE5041D1-D866-DE11-A46E-001D09F2A465.root',
       '/store/relval/CMSSW_3_1_0/RelValCosmics/RECO/CRAFT0831X_V1-v1/0001/BA4D087A-D466-DE11-9AE3-000423D9890C.root',
       '/store/relval/CMSSW_3_1_0/RelValCosmics/RECO/CRAFT0831X_V1-v1/0001/B8F2CDF0-D666-DE11-A04B-001D09F2915A.root',
       '/store/relval/CMSSW_3_1_0/RelValCosmics/RECO/CRAFT0831X_V1-v1/0001/B63A06E5-D766-DE11-9461-001D09F24D67.root',
       '/store/relval/CMSSW_3_1_0/RelValCosmics/RECO/CRAFT0831X_V1-v1/0001/B0FC0F88-D366-DE11-81EC-000423D6CA02.root',
       '/store/relval/CMSSW_3_1_0/RelValCosmics/RECO/CRAFT0831X_V1-v1/0001/AA3DA208-D666-DE11-AA55-001617C3B654.root',
       '/store/relval/CMSSW_3_1_0/RelValCosmics/RECO/CRAFT0831X_V1-v1/0001/A8BBA7FF-D566-DE11-8104-001D09F2983F.root',
       '/store/relval/CMSSW_3_1_0/RelValCosmics/RECO/CRAFT0831X_V1-v1/0001/A840B668-D966-DE11-AF7E-001D09F23A61.root',
       '/store/relval/CMSSW_3_1_0/RelValCosmics/RECO/CRAFT0831X_V1-v1/0001/A6D1CBEA-DA66-DE11-A9AB-000423D98EA8.root',
       '/store/relval/CMSSW_3_1_0/RelValCosmics/RECO/CRAFT0831X_V1-v1/0001/A6CF1281-D766-DE11-9652-000423D6CA02.root',
       '/store/relval/CMSSW_3_1_0/RelValCosmics/RECO/CRAFT0831X_V1-v1/0001/96586DE4-D766-DE11-A67D-001D09F2AD4D.root',
       '/store/relval/CMSSW_3_1_0/RelValCosmics/RECO/CRAFT0831X_V1-v1/0001/9403AA07-D966-DE11-8D95-001D09F34488.root',
       '/store/relval/CMSSW_3_1_0/RelValCosmics/RECO/CRAFT0831X_V1-v1/0001/92E7DAA7-D566-DE11-97EA-000423D998BA.root',
       '/store/relval/CMSSW_3_1_0/RelValCosmics/RECO/CRAFT0831X_V1-v1/0001/90B6A65F-DA66-DE11-B47B-000423D98EA8.root',
       '/store/relval/CMSSW_3_1_0/RelValCosmics/RECO/CRAFT0831X_V1-v1/0001/8C995ACA-DC66-DE11-B205-000423D98930.root',
       '/store/relval/CMSSW_3_1_0/RelValCosmics/RECO/CRAFT0831X_V1-v1/0001/8AB481EF-D666-DE11-8623-001617C3B6DC.root',
       '/store/relval/CMSSW_3_1_0/RelValCosmics/RECO/CRAFT0831X_V1-v1/0001/8AA80D51-D766-DE11-B072-001D09F24FBA.root',
       '/store/relval/CMSSW_3_1_0/RelValCosmics/RECO/CRAFT0831X_V1-v1/0001/88D1ED8C-DA66-DE11-866C-001D09F25217.root',
       '/store/relval/CMSSW_3_1_0/RelValCosmics/RECO/CRAFT0831X_V1-v1/0001/88BFA47C-D766-DE11-8E0D-001617C3B76E.root',
       '/store/relval/CMSSW_3_1_0/RelValCosmics/RECO/CRAFT0831X_V1-v1/0001/8882FE13-D866-DE11-A824-001D09F25217.root',
       '/store/relval/CMSSW_3_1_0/RelValCosmics/RECO/CRAFT0831X_V1-v1/0001/86323F6A-D966-DE11-8573-001D09F2B30B.root',
       '/store/relval/CMSSW_3_1_0/RelValCosmics/RECO/CRAFT0831X_V1-v1/0001/860B0873-D466-DE11-8E7D-001D09F2983F.root',
       '/store/relval/CMSSW_3_1_0/RelValCosmics/RECO/CRAFT0831X_V1-v1/0001/801AFA1B-D166-DE11-8A9C-001D09F2AD4D.root',
       '/store/relval/CMSSW_3_1_0/RelValCosmics/RECO/CRAFT0831X_V1-v1/0001/7ED03704-D966-DE11-B937-000423D94A04.root',
       '/store/relval/CMSSW_3_1_0/RelValCosmics/RECO/CRAFT0831X_V1-v1/0001/7C216E23-D066-DE11-93B7-000423D99A8E.root',
       '/store/relval/CMSSW_3_1_0/RelValCosmics/RECO/CRAFT0831X_V1-v1/0001/7A4A89F9-D566-DE11-8670-001617C3B66C.root',
       '/store/relval/CMSSW_3_1_0/RelValCosmics/RECO/CRAFT0831X_V1-v1/0001/786E3B0E-D966-DE11-98F2-000423D99614.root',
       '/store/relval/CMSSW_3_1_0/RelValCosmics/RECO/CRAFT0831X_V1-v1/0001/6AB201E1-D766-DE11-86BF-001D09F24024.root',
       '/store/relval/CMSSW_3_1_0/RelValCosmics/RECO/CRAFT0831X_V1-v1/0001/6A64C812-D866-DE11-B0AC-001D09F2AD4D.root',
       '/store/relval/CMSSW_3_1_0/RelValCosmics/RECO/CRAFT0831X_V1-v1/0001/60F42709-D966-DE11-A79B-000423D9A2AE.root',
       '/store/relval/CMSSW_3_1_0/RelValCosmics/RECO/CRAFT0831X_V1-v1/0001/60B62194-D366-DE11-B33D-000423D6B444.root',
       '/store/relval/CMSSW_3_1_0/RelValCosmics/RECO/CRAFT0831X_V1-v1/0001/5CDA3973-D566-DE11-B4B6-000423D94908.root',
       '/store/relval/CMSSW_3_1_0/RelValCosmics/RECO/CRAFT0831X_V1-v1/0001/58450473-D166-DE11-B96C-001D09F24024.root',
       '/store/relval/CMSSW_3_1_0/RelValCosmics/RECO/CRAFT0831X_V1-v1/0001/54B889A7-D566-DE11-889D-000423D987E0.root',
       '/store/relval/CMSSW_3_1_0/RelValCosmics/RECO/CRAFT0831X_V1-v1/0001/50FF4F58-DA66-DE11-94F3-001D09F2A465.root',
       '/store/relval/CMSSW_3_1_0/RelValCosmics/RECO/CRAFT0831X_V1-v1/0001/5046026A-D966-DE11-922B-001D09F27003.root',
       '/store/relval/CMSSW_3_1_0/RelValCosmics/RECO/CRAFT0831X_V1-v1/0001/4A33A6A6-DA66-DE11-8C93-000423D98F98.root',
       '/store/relval/CMSSW_3_1_0/RelValCosmics/RECO/CRAFT0831X_V1-v1/0001/448E5612-D866-DE11-B628-000423D944FC.root',
       '/store/relval/CMSSW_3_1_0/RelValCosmics/RECO/CRAFT0831X_V1-v1/0001/3E4723F4-DA66-DE11-BFCE-001617E30CE8.root',
       '/store/relval/CMSSW_3_1_0/RelValCosmics/RECO/CRAFT0831X_V1-v1/0001/3CDAD665-D966-DE11-B2AD-001D09F24FBA.root',
       '/store/relval/CMSSW_3_1_0/RelValCosmics/RECO/CRAFT0831X_V1-v1/0001/3C7390DD-D766-DE11-B306-001617C3B76E.root',
       '/store/relval/CMSSW_3_1_0/RelValCosmics/RECO/CRAFT0831X_V1-v1/0001/3AFF4A75-D866-DE11-9DE0-001D09F34488.root',
       '/store/relval/CMSSW_3_1_0/RelValCosmics/RECO/CRAFT0831X_V1-v1/0001/36C83956-DA66-DE11-B74E-001D09F23A61.root',
       '/store/relval/CMSSW_3_1_0/RelValCosmics/RECO/CRAFT0831X_V1-v1/0001/3263435B-DA66-DE11-9364-000423D99264.root',
       '/store/relval/CMSSW_3_1_0/RelValCosmics/RECO/CRAFT0831X_V1-v1/0001/32023451-D766-DE11-A6AC-001D09F29321.root',
       '/store/relval/CMSSW_3_1_0/RelValCosmics/RECO/CRAFT0831X_V1-v1/0001/30554FF1-D966-DE11-98BB-001D09F23A61.root',
       '/store/relval/CMSSW_3_1_0/RelValCosmics/RECO/CRAFT0831X_V1-v1/0001/2C80EACA-D966-DE11-8610-000423D9517C.root',
       '/store/relval/CMSSW_3_1_0/RelValCosmics/RECO/CRAFT0831X_V1-v1/0001/2C3CB5DC-D766-DE11-BB9B-001D09F2432B.root',
       '/store/relval/CMSSW_3_1_0/RelValCosmics/RECO/CRAFT0831X_V1-v1/0001/22584277-D566-DE11-880E-000423D9A212.root',
       '/store/relval/CMSSW_3_1_0/RelValCosmics/RECO/CRAFT0831X_V1-v1/0001/204F7CFB-D166-DE11-8D4B-000423D98834.root',
       '/store/relval/CMSSW_3_1_0/RelValCosmics/RECO/CRAFT0831X_V1-v1/0001/1E7D1D55-DD66-DE11-ACFF-001617C3B5E4.root',
       '/store/relval/CMSSW_3_1_0/RelValCosmics/RECO/CRAFT0831X_V1-v1/0001/1CBD7290-D266-DE11-8698-001D09F25217.root',
       '/store/relval/CMSSW_3_1_0/RelValCosmics/RECO/CRAFT0831X_V1-v1/0001/1C521DE2-D766-DE11-BF23-001D09F2516D.root',
       '/store/relval/CMSSW_3_1_0/RelValCosmics/RECO/CRAFT0831X_V1-v1/0001/1401B79E-D566-DE11-807F-000423D99658.root',
       '/store/relval/CMSSW_3_1_0/RelValCosmics/RECO/CRAFT0831X_V1-v1/0001/12C00086-D366-DE11-8F0F-000423D99AA2.root',
       '/store/relval/CMSSW_3_1_0/RelValCosmics/RECO/CRAFT0831X_V1-v1/0001/12240F68-D966-DE11-9F71-001D09F2915A.root',
       '/store/relval/CMSSW_3_1_0/RelValCosmics/RECO/CRAFT0831X_V1-v1/0001/0EA1FFDE-D066-DE11-A716-000423D99A8E.root',
       '/store/relval/CMSSW_3_1_0/RelValCosmics/RECO/CRAFT0831X_V1-v1/0001/0CADA06C-D966-DE11-9705-001D09F24D67.root',
       '/store/relval/CMSSW_3_1_0/RelValCosmics/RECO/CRAFT0831X_V1-v1/0001/0CA02068-D966-DE11-AE2F-001D09F23C73.root',
       '/store/relval/CMSSW_3_1_0/RelValCosmics/RECO/CRAFT0831X_V1-v1/0001/0AAB236B-D966-DE11-BEE4-001D09F24DA8.root',
       '/store/relval/CMSSW_3_1_0/RelValCosmics/RECO/CRAFT0831X_V1-v1/0001/0847F865-D966-DE11-8A0E-001D09F253C0.root',
       '/store/relval/CMSSW_3_1_0/RelValCosmics/RECO/CRAFT0831X_V1-v1/0001/06E28765-D966-DE11-A947-001D09F290BF.root',
       '/store/relval/CMSSW_3_1_0/RelValCosmics/RECO/CRAFT0831X_V1-v1/0001/06867DC6-D966-DE11-864B-000423D99614.root',
       '/store/relval/CMSSW_3_1_0/RelValCosmics/RECO/CRAFT0831X_V1-v1/0001/063595C8-D966-DE11-A6BA-001D09F25217.root',
       '/store/relval/CMSSW_3_1_0/RelValCosmics/RECO/CRAFT0831X_V1-v1/0000/E295822A-A866-DE11-A0D0-001D09F292D1.root',
       '/store/relval/CMSSW_3_1_0/RelValCosmics/RECO/CRAFT0831X_V1-v1/0000/BE755A7E-A766-DE11-8EF9-001D09F26C5C.root',
       '/store/relval/CMSSW_3_1_0/RelValCosmics/RECO/CRAFT0831X_V1-v1/0000/769F580D-A766-DE11-98E6-001D09F24F1F.root',
       '/store/relval/CMSSW_3_1_0/RelValCosmics/RECO/CRAFT0831X_V1-v1/0000/6A1028ED-A666-DE11-A30B-001D09F24EC0.root',
       '/store/relval/CMSSW_3_1_0/RelValCosmics/RECO/CRAFT0831X_V1-v1/0000/3CC8A51C-A766-DE11-9300-001D09F2441B.root',
       '/store/relval/CMSSW_3_1_0/RelValCosmics/RECO/CRAFT0831X_V1-v1/0000/38E76CAD-A766-DE11-82D3-001D09F24024.root',
       '/store/relval/CMSSW_3_1_0/RelValCosmics/RECO/CRAFT0831X_V1-v1/0000/287BF497-A766-DE11-BCCB-0019B9F6C674.root',
       '/store/relval/CMSSW_3_1_0/RelValCosmics/RECO/CRAFT0831X_V1-v1/0000/1C50F3BA-A866-DE11-8BFE-001D09F24DA8.root' ] );

secFiles.extend( [
               ] )
