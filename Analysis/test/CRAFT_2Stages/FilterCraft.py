
import FWCore.ParameterSet.Config as cms

process = cms.Process("FilterData")
process.load("FWCore.MessageLogger.MessageLogger_cfi")

process.load("CondCore.DBCommon.CondDBSetup_cfi")


# these not actually used
#process.load('Configuration.StandardSequences.L1Emulator_cff')
#process.load('FastSimulation.L1CaloTriggerProducer.fastl1calosim_cfi')

process.load('L1Trigger.Skimmer.l1Filter_cfi')


# output module
#
process.load("Configuration.EventContent.EventContentCosmics_cff")

process.FEVT = cms.OutputModule("PoolOutputModule",
    process.FEVTEventContent,
    dataset = cms.untracked.PSet(dataTier = cms.untracked.string('RECO')),
    fileName = cms.untracked.string('Filter_Data_Output.root'),
    SelectEvents = cms.untracked.PSet(
       SelectEvents = cms.vstring("allPath")
       )
)

process.FEVT.outputCommands.append('keep CaloTowersSorted_calotoweroptmaker_*_*')
process.FEVT.outputCommands.append('keep CSCDetIdCSCALCTDigiMuonDigiCollection_muonCSCDigis_MuonCSCALCTDigi_*')
process.FEVT.outputCommands.append('keep CSCDetIdCSCCLCTDigiMuonDigiCollection_muonCSCDigis_MuonCSCCLCTDigi_*')
process.FEVT.outputCommands.append('keep CSCDetIdCSCComparatorDigiMuonDigiCollection_muonCSCDigis_MuonCSCComparatorDigi_*')
process.FEVT.outputCommands.append('keep CSCDetIdCSCCorrelatedLCTDigiMuonDigiCollection_csctfDigis_*_*')
process.FEVT.outputCommands.append('keep CSCDetIdCSCCorrelatedLCTDigiMuonDigiCollection_muonCSCDigis_MuonCSCCorrelatedLCTDigi_*')
process.FEVT.outputCommands.append('keep CSCDetIdCSCRPCDigiMuonDigiCollection_muonCSCDigis_MuonCSCRPCDigi_*')
process.FEVT.outputCommands.append('keep CSCDetIdCSCStripDigiMuonDigiCollection_muonCSCDigis_MuonCSCStripDigi_*')
process.FEVT.outputCommands.append('keep CSCDetIdCSCWireDigiMuonDigiCollection_muonCSCDigis_MuonCSCWireDigi_*')
process.FEVT.outputCommands.append('keep cscL1TrackCSCDetIdCSCCorrelatedLCTDigiMuonDigiCollectionstdpairs_csctfDigis_*_*')
process.FEVT.outputCommands.append('keep DTChamberIdDTLocalTriggerMuonDigiCollection_muonDTDigis_*_*')
process.FEVT.outputCommands.append('keep DTLayerIdDTDigiMuonDigiCollection_muonDTDigis_*_*')
process.FEVT.outputCommands.append('keep intL1CSCSPStatusDigisstdpair_csctfDigis_*_*')
process.FEVT.outputCommands.append('keep L1MuDTChambPhContainer_dttfDigis_*_*')
process.FEVT.outputCommands.append('keep L1MuDTChambThContainer_dttfDigis_*_*')
process.FEVT.outputCommands.append('keep L1MuDTTrackContainer_dttfDigis_DATA_*')
process.FEVT.outputCommands.append('keep HBHEDataFramesSorted_*_*_*')
process.FEVT.outputCommands.append('keep PixelDigiedmDetSetVector_siPixelDigis_*_*')
process.FEVT.outputCommands.append('keep recoCandidatesOwned_caloTowersOpt_*_*')
process.FEVT.outputCommands.append('keep RPCDetIdRPCDigiMuonDigiCollection_muonRPCDigis_*_*')



# Conditions (Global Tag is used here):
process.load("Configuration.StandardSequences.FrontierConditions_GlobalTag_cff")
process.GlobalTag.connect = "frontier://PromptProd/CMS_COND_21X_GLOBALTAG"
process.GlobalTag.globaltag = "CRAFT_ALL_V4::All"
process.prefer("GlobalTag")

# Magnetic fiuld: force mag field to be 0 tesla
process.load("Configuration.StandardSequences.MagneticField_38T_cff")

#Geometry
process.load("Configuration.StandardSequences.Geometry_cff")

# Real data raw to digi
process.load("Configuration.StandardSequences.RawToDigi_Data_cff")

# reconstruction sequence for Cosmics
process.load("Configuration.StandardSequences.ReconstructionCosmics_cff")

# offline DQM
process.load("DQMOffline.Configuration.DQMOfflineCosmics_cff")
process.load("DQMServices.Components.MEtoEDMConverter_cff")

#L1 trigger validation
#process.load("L1Trigger.HardwareValidation.L1HardwareValidation_cff")
process.load("L1Trigger.Configuration.L1Config_cff")
process.load("L1TriggerConfig.CSCTFConfigProducers.CSCTFConfigProducer_cfi")
process.load("L1TriggerConfig.CSCTFConfigProducers.L1MuCSCTFConfigurationRcdSrc_cfi")


process.TFileService = cms.Service("TFileService",
    fileName = cms.string('Filter_Data_Histos.root')
)





# Analyzers
#########

process.an_L1 = cms.EDFilter("GlobalRunAnalyser",
    IncludeJetDetails=cms.untracked.bool(True),
    IncludeDigisOld=cms.untracked.bool(True),
    IncludeCaloTowers=cms.untracked.bool(True),
    IncludeRecHits=cms.untracked.bool(False),                                 
    IncludeMC=cms.untracked.bool(False),
    IncludeJets=cms.untracked.bool(True),
    IncludeMuons=cms.untracked.bool(True)                                   
)                                      


process.an_HLT = cms.EDFilter("GlobalRunAnalyser",
    IncludeJetDetails=cms.untracked.bool(True),
    IncludeDigisOld=cms.untracked.bool(True),
    IncludeCaloTowers=cms.untracked.bool(True),
    IncludeRecHits=cms.untracked.bool(False),                                 
    IncludeMC=cms.untracked.bool(False),
    IncludeJets=cms.untracked.bool(True),
    IncludeMuons=cms.untracked.bool(True)                                      
)

process.an_All = cms.EDFilter("GlobalRunAnalyser",
    IncludeJetDetails=cms.untracked.bool(True),
    IncludeDigisOld=cms.untracked.bool(True),
    IncludeCaloTowers=cms.untracked.bool(True),
    IncludeRecHits=cms.untracked.bool(False),                                 
    IncludeMC=cms.untracked.bool(False),
    IncludeJets=cms.untracked.bool(True),
    IncludeMuons=cms.untracked.bool(True)                                      
)









# Trigger tools
#########


process.bitfilter = cms.EDFilter("RecoFilter",
    FilterCondition = cms.untracked.string('OneBit'),
    Bit1 = cms.untracked.int32(16)
)


process.l1jetfilter = cms.EDFilter("L1JetFltr",
    EMinCut = cms.untracked.double(0.0),
    EMaxCut = cms.untracked.double(10000.0),
    ETMinCut = cms.untracked.double(10.0),
    ETMaxCut = cms.untracked.double(10000.0),
    BranchTag = cms.untracked.string("hltL1extraParticles"),
    EtaMinCut = cms.untracked.double(-3.0),
    EtaMaxCut = cms.untracked.double(3.0)
)

process.load("L1TriggerConfig.L1GtConfigProducers.Luminosity.startup.L1Menu_startup2_v2_Unprescaled_cff")

process.l1Filter.algorithms = cms.vstring("L1_SingleJet10_00001")

process.MessageLogger.cerr.FwkReport.reportEvery = 100





# Filters and cuts
#########


                  

process.hltenergycut = cms.EDFilter("CaloFilter",
                   
    n60MinThreshold=cms.untracked.int32(0),
    n90MinThreshold=cms.untracked.int32(0),
    n60MaxThreshold=cms.untracked.int32(100),
    n90MaxThreshold=cms.untracked.int32(100),
    ETMinThreshold=cms.untracked.double(0.),
    ETMaxThreshold=cms.untracked.double(10000.),
    EMinThreshold=cms.untracked.double(20.),
    EMaxThreshold=cms.untracked.double(10000 ),
    EtaMinThreshold=cms.untracked.double(-3.3),
    EtaMaxThreshold=cms.untracked.double(3.3),
    CaloTowerVeto=cms.untracked.bool(False),
    CaloTowerCount=cms.untracked.int32(5),
    CaloTowerEMin=cms.untracked.double(0),
    NOver5=cms.untracked.int32(100),
    CentralEta=cms.untracked.double(3.0)                                                           
)

process.noisefilter = cms.EDFilter("HLTHPDFilter",
    inputTag = cms.InputTag("hbhereco"),
    energy = cms.double(-99.0),
    hpdSpikeEnergy = cms.double(10.0),
    hpdSpikeIsolationEnergy = cms.double(1.0),
    rbxSpikeEnergy = cms.double(50.0),                               
    rbxSpikeUnbalance = cms.double(0.2)
)


process.load('StoppedHSCP.Analysis.jetanalyzer_cfi')


# Paths
#########


process.allPath = cms.Path( #process.RawToDigi_woGCT*
                            #process.an_All *
                            process.l1Filter*
                            process.an_L1 *
                            process.noisefilter*
                            process.hltenergycut*
                            process.an_HLT
#                            process.jetanalyzer
 )




maxEvents = cms.untracked.PSet( input = cms.untracked.int32(1000) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
process.source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)
readFiles.extend( [
        '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0010/F60F7412-7A00-DE11-8430-00304867BFB2.root',
        '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0010/EE9E0D5D-A500-DE11-B93D-0018F3D096A4.root',
        '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0010/EA5E009F-4100-DE11-BB6F-00173199E924.root',
        '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0010/E4B0E934-E0FF-DD11-858C-001A92971BDA.root',
        '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0010/DED0C412-3A00-DE11-A1F3-001A92810AF4.root',
        '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0010/D04EADDE-DEFF-DD11-BB3C-0018F3D096E6.root',
        '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0010/CEE15A92-4100-DE11-BECF-001A9281170E.root',
        '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0010/CE5FF9FE-3000-DE11-B6F0-0018F3D09708.root',
        '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0010/CACFD660-9E00-DE11-B566-0018F3D09624.root',
        '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0010/C48CE2E5-4200-DE11-97F5-001A92811702.root',
        '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0010/C09092AA-3700-DE11-87AC-001731AF66FB.root',
        '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0010/B8D24FF4-8200-DE11-AF9C-0018F3D09636.root',
        '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0010/B273AAA1-B200-DE11-B143-001A92810AA2.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0010/B0D9AE5A-A500-DE11-8626-00304867926C.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0010/B095CE73-CE00-DE11-B6B8-003048754CE5.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0010/B0446461-7400-DE11-8B29-001A92810AEE.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0010/ACA57E4F-4600-DE11-A40A-00304867902C.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0010/A664CE8D-8600-DE11-9CA5-003048678B74.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0010/A445B2F9-E9FF-DD11-9183-0018F3D096CE.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0010/A0C1BCEC-E2FF-DD11-B039-001A92971AA4.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0010/9CE7B5A7-6A01-DE11-A355-00304875AAE3.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0010/9A5D1D54-1600-DE11-A986-0018F3D09614.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0010/986947E7-E0FF-DD11-9BC3-0018F3D095FA.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0010/9815FE33-9F00-DE11-8F93-0018F3D09704.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0010/9454BE9F-6500-DE11-B1A1-003048678BAA.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0010/92D98ED3-9C00-DE11-A880-001731AF6943.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0010/8A2CCB3A-8100-DE11-A548-00304875AAD7.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0010/824D0D77-1C00-DE11-A918-0018F3D0960C.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0010/8041E3DE-A000-DE11-96AB-00304867C29C.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0010/62248696-8600-DE11-9FF7-00304867900C.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0010/48E6E9D9-A500-DE11-BDE4-0030486791DC.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0010/446475C9-9C00-DE11-BABC-00304867D836.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0010/3A151CF4-7400-DE11-9C0D-003048678F9C.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0010/3641DB0B-8500-DE11-BC9C-001A92971B0E.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0010/2ECFBEE5-5F00-DE11-856A-00304867BFB0.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0010/281AD67D-DFFF-DD11-92EA-001A9281173E.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0010/247AD66B-9E00-DE11-899F-001A92810AE0.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0010/22A347B0-7B00-DE11-AF2E-00304867902E.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0010/16F6FC74-9C00-DE11-AB29-001A92810AC4.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0010/166A4C68-EBFF-DD11-96DE-001A92971ADC.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0010/12ADF3D6-7C00-DE11-9DDD-00304875AAE7.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0010/08DD06E8-A000-DE11-BF11-003048678BAC.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0010/02E8D702-6F00-DE11-9A57-003048678FFE.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0009/F2C8FBA8-5B00-DE11-8EB5-003048D15D04.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0009/EE7868E4-7000-DE11-8199-003048678B72.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0009/E8E6CE0A-4500-DE11-8EFA-00304876A15D.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0009/E48ECDEC-4200-DE11-88F9-001A92810AF2.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0009/E22FD067-9E00-DE11-AD0C-0018F3D096DC.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0009/E0AD374E-3900-DE11-A455-001A92971ACC.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0009/DCC3FA72-6700-DE11-9BC4-001A92971AA4.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0009/D8EBDCA6-4600-DE11-9F6F-003048678B08.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0009/D6E3D6A4-3F00-DE11-A780-003048678A6C.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0009/D63141CC-6400-DE11-BA8E-0018F3D096DC.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0009/CE4CD72C-4700-DE11-8D89-0018F3D09678.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0009/CA09C157-6000-DE11-A8FA-001731AF68AD.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0009/C8724EC5-6200-DE11-8555-001A92810AA2.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0009/C6B7C94B-4600-DE11-9BEB-003048678B70.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0009/C67F3BFB-E9FF-DD11-972E-0030486792B8.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0009/C2E257C0-3F00-DE11-A728-00304875AAEB.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0009/B69F394D-4300-DE11-B96A-001731AF6981.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0009/B48E8A36-E0FF-DD11-B60B-0018F3D096AA.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0009/B26CC7BD-3F00-DE11-A280-0017313F02F2.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0009/AEF5132A-0200-DE11-B10B-0018F3D095F8.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0009/AEF33A37-4300-DE11-A9F2-001A9281170C.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0009/AC7ACF55-6500-DE11-9DB2-003048678A6C.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0009/AA60AEC7-E5FF-DD11-A1DA-001A928116C0.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0009/A2333F7C-4300-DE11-A1E4-001A92811700.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0009/A22DBFF4-A500-DE11-AC0D-0017312B5E1D.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0009/A0174C75-4C00-DE11-A222-0018F3D0960C.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0009/9614C79B-3A00-DE11-9516-003048678B1A.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0009/8ED024A1-7300-DE11-824E-001A928116C4.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0009/8C4C54D6-3F00-DE11-AD8B-001A92971ADC.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0009/8A03A8BE-3F00-DE11-AD15-001A92810AAE.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0009/86544B80-0100-DE11-9228-003048678B74.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0009/80A0E371-7700-DE11-9A55-003048769E5D.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0009/8008A3A1-4300-DE11-96BD-003048678F26.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0009/7C6C9BE8-4400-DE11-A210-003048678AF4.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0009/7A02E7F4-3A00-DE11-A382-0018F3D09680.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0009/783D1D0F-A200-DE11-9B08-0030486792B6.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0009/78053768-9E00-DE11-899E-001A92810AE0.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0009/76AC2917-B200-DE11-8ABB-003048678B8E.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0009/76842336-E0FF-DD11-82CC-0018F3D0967E.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0009/705AED9E-4600-DE11-8481-003048678FF8.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0009/6C4014FD-6100-DE11-8342-001A92810AEA.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0009/68AD9938-E8FF-DD11-A9BA-003048678FB2.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0009/66256E64-9E00-DE11-9DEC-001A92971B62.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0009/66056C39-7800-DE11-BE69-00304867C16A.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0009/60749D6E-8A00-DE11-BFBB-001A928116AE.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0009/5C3BB720-3D00-DE11-9920-001A928116DA.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0009/5A9BC23D-0200-DE11-8CE5-001731AF6A49.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0009/5808FCF6-4400-DE11-8D29-00304867BEC0.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0009/56E60475-6E00-DE11-84E5-0017312B5DC9.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0009/56E5070B-1D00-DE11-B1A9-0018F3D096A0.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0009/56C8E05D-7700-DE11-9C4A-003048678A76.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0009/54CBF4A4-4300-DE11-982F-003048678E94.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0009/5417B65F-3500-DE11-8B0E-00304875AAF5.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0009/5228130C-6300-DE11-862F-001A928116D6.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0009/4E577E66-EBFF-DD11-80BE-003048678F62.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0009/4E25B2EF-DDFF-DD11-BE10-0018F3D09660.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0009/48623DF5-EDFF-DD11-B0E8-001A928116CC.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0009/40DDADBF-4400-DE11-BDB9-00304867BFC6.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0009/40C18C6B-9E00-DE11-B3BD-0018F3D0969C.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0009/3C779169-9E00-DE11-86F0-0018F3D095FE.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0009/385BE119-A000-DE11-80CA-00304876A061.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0009/343EF3FE-E8FF-DD11-8B5A-001731AF68C1.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0009/340458D8-8900-DE11-B912-001731AF67E1.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0009/3276B813-3D00-DE11-B8DE-0018F3D0961A.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0009/304212ED-4400-DE11-B362-003048678C62.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0009/302DE6A6-3A00-DE11-83D0-0017313F01E4.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0009/2EB58FE8-4100-DE11-9310-001A92810A9E.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0009/2C52CCF3-4500-DE11-8A41-003048678B44.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0009/2AE27DFB-3000-DE11-B858-0018F3D09612.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0009/24C74AF1-2F00-DE11-A396-0018F3D096C6.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0009/20E83C0A-E5FF-DD11-84E5-0018F3D09702.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0009/1EFC2096-DBFF-DD11-9C5F-001731AF65EF.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0009/1EEF8990-7F00-DE11-B173-003048D3FC94.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0009/1AB4BAA7-3A00-DE11-9795-001A92810AA0.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0009/1A1C5452-3900-DE11-A3AB-0018F3D09690.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0009/128259D6-0B00-DE11-947A-003048678AC0.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0009/120904BA-6E00-DE11-A571-003048754D05.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0009/100E7694-5600-DE11-8DC6-001731AF685D.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0009/0CE48764-D900-DE11-B73D-001731AF664F.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0009/08D5C336-2F00-DE11-B2A2-001731A283E1.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0009/02CB41CC-3F00-DE11-B0C9-0018F3D096CE.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0009/02987915-4700-DE11-A38D-003048678AC8.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0008/FA660421-8A00-DE11-A989-0018F3D09664.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0008/F41A2D4A-1C00-DE11-8C5E-001A92810AA0.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0008/EEC7D24A-6F00-DE11-9AA0-00304875AAF7.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0008/EE2CBE72-9C00-DE11-9DB2-003048678FC6.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0008/DA80A3F5-3A00-DE11-80C2-00304875AC63.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0008/CECC1631-AB00-DE11-94EE-001BFCDBD190.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0008/CA8184C9-3F00-DE11-B95D-0018F3D096C0.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0008/C82BAE48-4400-DE11-8689-00304867C0F6.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0008/B6FE97C7-9C00-DE11-B884-001731AF66A5.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0008/AAD7485F-A000-DE11-A056-001731A28799.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0008/A4AD57E5-4500-DE11-B37A-003048678AF4.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0008/A0F4E417-BB00-DE11-8C04-001A92971BC8.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0008/A034FFC7-9C00-DE11-BD49-001731AF6AC5.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0008/964F3D47-6F00-DE11-B5F1-0018F3D096D2.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0008/88E3A867-9E00-DE11-B387-001A92810AE0.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0008/786D05D9-0B00-DE11-9B78-0018F3D09624.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0008/7483FFAB-3100-DE11-B517-0018F3D09706.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0008/6ACBB315-8500-DE11-9C55-0018F3D09708.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0008/6860DB73-3500-DE11-B6C7-0018F3D096E6.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0008/62AF17E4-4400-DE11-A96B-00304867C1B0.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0008/5E4C67C9-E5FF-DD11-80AB-003048754C69.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0008/58E3DF8F-5600-DE11-B2DA-0018F3D0965A.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0008/58A5F215-3300-DE11-8C38-0018F3D096BC.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0008/56C18C60-5C00-DE11-8B6F-003048678B0C.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0008/4C17A4A1-3000-DE11-9B4B-0018F3D09678.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0008/4A9DE3A4-8700-DE11-BA83-003048679166.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0008/44F7077F-EE00-DE11-9A26-0018F3D096E4.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0008/426B65D9-6A00-DE11-951E-003048678B14.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0008/40AD9ECD-8900-DE11-BC7D-003048678B20.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0008/3EB4B632-6200-DE11-A4E8-001A928116F0.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0008/301F1A5C-3700-DE11-BB47-00304875A339.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0008/2C88B63B-6500-DE11-A697-0030486790FE.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0008/2810EB65-E7FF-DD11-B6AB-003048678FE0.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0008/26BD31A0-5600-DE11-92F9-003048678B8E.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0008/26367AA5-3000-DE11-AAF9-0018F3D09688.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0008/0EBE5D3A-1B00-DE11-8263-001731AF66F3.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0008/0C341638-DDFF-DD11-8635-001731AF66B7.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0008/00CD8BA6-5C00-DE11-990E-001A92810AC8.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0007/FCE0D32C-AB00-DE11-9B5F-00304867C136.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0007/FC3DD8F8-E2FF-DD11-9B53-001A92971AAA.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0007/FAE8F548-3000-DE11-B064-00304867918A.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0007/EC270207-AD00-DE11-8E4E-001BFCDBD184.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0007/E84B0823-DAFF-DD11-9BF0-00304875ABEF.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0007/E41725B7-A100-DE11-99DC-001A92971B0E.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0007/E4155352-8A00-DE11-9C78-003048678F84.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0007/DCC5705F-7B00-DE11-94AB-001A928116CC.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0007/DAA91983-EBFF-DD11-B890-003048678BE6.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0007/DA386AEC-DEFF-DD11-BDB1-0018F3D095F0.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0007/D8E6D063-5900-DE11-9CE6-003048679244.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0007/D8D6187D-9E00-DE11-A365-001731A283DF.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0007/D8629F89-7F00-DE11-8F70-003048678E8A.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0007/D69FBC8F-A300-DE11-ADFC-001731AF6B75.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0007/CC7C35FD-7100-DE11-AD21-003048678F8E.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0007/C897FE59-DBFF-DD11-8090-001731AF6867.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0007/C82E1412-8000-DE11-B67B-001A9281172A.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0007/C4CDEBBB-3B00-DE11-930E-001BFCDBD130.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0007/C4C711BD-6000-DE11-AC7A-0018F3D09642.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0007/C09860B5-E3FF-DD11-AE71-001BFCDBD1BE.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0007/C070B9CA-9C00-DE11-B5B6-001731AF66A5.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0007/BE18E130-DDFF-DD11-8296-001731AF6B75.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0007/B88C1842-3000-DE11-B24E-003048679228.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0007/B4DEF9D1-4300-DE11-95F1-00304867901A.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0007/A8AAB332-5F00-DE11-91DD-0030486792DE.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0007/A030FF54-4600-DE11-8701-003048678C26.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0007/9CC0A589-8900-DE11-AB65-0030486792BA.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0007/94E7B7DA-6B00-DE11-BDC4-003048679214.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0007/9455184E-6600-DE11-A77C-0017319EB92B.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0007/92F86F12-8B00-DE11-B256-003048678E8A.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0007/92EBCD24-2D00-DE11-8BBD-003048678AC0.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0007/90B9014F-3000-DE11-81EC-0018F3D0962C.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0007/907CACB5-E3FF-DD11-8A25-0018F3D0962A.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0007/8C9A2301-DFFF-DD11-A288-001A92810ACA.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0007/84AA3B26-4400-DE11-B8E5-003048678FF2.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0007/845B39F9-3000-DE11-8CCC-001A92971B62.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0007/825667F1-2F00-DE11-9E8A-001A92971B9A.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0007/7CD6C62B-7100-DE11-9EB9-00304876A153.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0007/7C9620AF-8800-DE11-BA54-0018F3D096A2.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0007/78D60B38-E8FF-DD11-BF07-003048678F62.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0007/78B01D90-6200-DE11-9E70-001A9281172A.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0007/74E5A08A-7700-DE11-B426-001A92810AA0.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0007/707D1038-5800-DE11-B35F-003048678BAA.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0007/6893A0DE-E6FF-DD11-BEAA-001731A2832D.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0007/680FFC8C-8300-DE11-8E5D-001BFCDBD182.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0007/6092717C-DBFF-DD11-BB08-001731AF6653.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0007/6018FB25-6800-DE11-9DA3-001A92810ABA.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0007/5AC07606-AB00-DE11-AA4C-001A92810AA6.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0007/58CDB785-6200-DE11-AE01-001A928116BE.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0007/56B28D39-4600-DE11-84A2-003048678B44.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0007/5663282E-AB00-DE11-B32A-003048678F8A.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0007/560C7D5D-6500-DE11-BBB5-001731AF6787.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0007/4AA26D78-5C00-DE11-BFF5-003048678B38.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0007/4A555F2B-DDFF-DD11-B6D4-001731AF66F3.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0007/48936E18-DCFF-DD11-86E5-0018F3D095F0.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0007/485653A9-7F00-DE11-9C38-001A92971B8E.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0007/44015000-8500-DE11-B18B-0018F3D096BA.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0007/426468BF-A100-DE11-992E-00304875AAE1.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0007/3EA4D3F9-E8FF-DD11-8FB5-0030486790B8.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0007/3C353BC7-E3FF-DD11-BE17-003048756525.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0007/30070E18-DCFF-DD11-9EA5-001A92810ACA.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0007/2CFD980E-E6FF-DD11-9044-0030487566E9.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0007/2AC85FA0-6400-DE11-A945-001A92971AD0.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0007/28D7B8B3-AE00-DE11-AC59-0018F3D09608.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0007/28B25B80-8700-DE11-908D-0018F3D0963C.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0007/26E04573-9C00-DE11-B7AF-003048678FFE.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0007/24FE5038-EDFF-DD11-83F1-0018F3D09614.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0007/1CB4C918-DCFF-DD11-8D90-0018F3D095F2.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0007/1C707CFE-5E00-DE11-9A0B-001A92971B3C.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0007/1AA17087-5D00-DE11-87EC-003048678F02.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0007/166CC0D2-6400-DE11-B3AF-001731AF6651.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0007/0CB823AA-9C00-DE11-BA36-0030486792AC.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0007/0C06210F-7900-DE11-8ED6-001731AF6780.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0007/0A92DD0F-A000-DE11-AC99-00304875AA61.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0007/0A09E0EC-6200-DE11-86A7-003048678B74.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0007/06D66C6A-9E00-DE11-83CB-0018F3D096BA.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0005/FE24A702-AD00-DE11-80A4-0018F3D0970A.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0005/EE1373DD-E6FF-DD11-BE90-00304875A9CF.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0005/ECD911B4-4300-DE11-946D-00304867900C.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0005/E6BC46AC-4300-DE11-9A2C-003048679006.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0005/E6662E0A-4000-DE11-966C-001A92810A98.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0005/DAB0A89D-DBFF-DD11-944F-003048769CCF.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0005/D25D03E6-DEFF-DD11-954F-0018F3D096F8.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0005/CCCD1DA6-6700-DE11-85F8-0018F3D09636.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0005/C8FB37F1-4100-DE11-8E64-001A9281172E.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0005/C80CC923-1D00-DE11-8898-001A92971B28.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0005/C49C6D1D-DAFF-DD11-9456-003048769D4B.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0005/C2676938-1D00-DE11-9154-001731AF6A77.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0005/C0A40863-8100-DE11-A544-003048754C53.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0005/C0180ED0-E6FF-DD11-8AB2-003048678FD6.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0005/C0041B0B-E5FF-DD11-A457-0018F3D0969A.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0005/BAD069FC-3800-DE11-B8A3-001A92971ACE.root' ] );
readFiles.extend( [

       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0005/B2ECE00B-E5FF-DD11-AC21-0018F3D0968C.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0005/B2C7B15F-9E00-DE11-81A4-0018F3D095FA.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0005/B288267F-7B00-DE11-807F-0030486790B8.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0005/AE73F0A5-CB00-DE11-A254-00304867C1BC.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0005/AC95CA14-4000-DE11-B321-001A928116C4.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0005/A86A30ED-3F00-DE11-A2DB-00304867929E.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0005/A43F419E-B600-DE11-B9B4-003048767FAB.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0005/A00F4546-4400-DE11-B5C7-001A92971AD8.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0005/9A59B276-DBFF-DD11-A633-003048767DCD.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0005/98BF981F-8300-DE11-8A9C-001A92971B8E.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0005/98887761-1700-DE11-86D5-0018F3D09600.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0005/96CFC6D8-0600-DE11-8073-0018F3D0967E.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0005/901C4634-6700-DE11-BDD9-0018F3D096BE.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0005/8A12A9CA-4100-DE11-BC89-001A9281170A.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0005/881317EE-A600-DE11-BC49-003048678B30.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0005/840B24D9-3300-DE11-A225-001A92971B8E.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0005/7ED2DD17-DAFF-DD11-848E-00304875628B.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0005/7AF962B5-4300-DE11-AE05-00304867BEE4.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0005/6AA9B645-0600-DE11-873B-003048678ED4.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0005/68214443-AF00-DE11-96E4-0018F3D095F8.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0005/62271117-A000-DE11-9FE4-001BFCDBD15E.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0005/60315214-A000-DE11-81D8-0018F3D09706.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0005/5E7F8629-EDFF-DD11-9653-003048678FA0.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0005/5AE1CF2F-4400-DE11-9A56-001A92971B8C.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0005/4E8AC373-9C00-DE11-B150-003048679046.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0005/4A9A4EC8-4200-DE11-9EC0-0030486792B4.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0005/42C32062-6F00-DE11-98D3-00304875AB57.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0005/3E61531F-4000-DE11-A53E-001BFCDBD190.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0005/3E5612F8-3A00-DE11-A261-001731AF6A7B.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0005/3A7CC2A4-B600-DE11-A403-001731AF685F.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0005/2E7F7ED9-DEFF-DD11-A9A5-001A92810AE4.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0005/28B26A20-5100-DE11-9ECD-00304875AA61.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0005/26FF0027-4600-DE11-B2E9-003048678A7E.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0005/26216794-1E00-DE11-8EA0-003048678A6C.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0005/200742A0-3400-DE11-BF8C-001A92971B72.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0005/1AE51E40-B200-DE11-B73A-001A92811710.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0005/1837336E-6B00-DE11-867F-0030487624FB.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0005/1828AADA-6400-DE11-8E96-001A92810AA0.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0005/16D1478E-4400-DE11-962F-001A928116DE.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0005/120A1C14-4C00-DE11-9B5C-003048678AC0.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0005/10DFC1C7-9C00-DE11-9CD0-001731AF678D.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0005/08C01830-4600-DE11-AE7A-003048678B26.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0005/064526C8-8100-DE11-A597-003048678BEA.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0005/060F5B5F-AF00-DE11-BE01-001731AF67E3.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0005/041B5D22-4000-DE11-9A21-001A928116CE.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0005/003670F6-6900-DE11-8FDF-001A92811718.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0004/FE629FCB-6200-DE11-92BE-00304875A9FD.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0004/F8ACAAD3-3D00-DE11-84D5-003048678F92.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0004/F6BB15D4-9C00-DE11-9E78-001731AF66A5.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0004/F690EF17-4100-DE11-81CA-001731AF677D.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0004/F47B9749-6000-DE11-9A7F-0030486791BA.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0004/F2551A0F-6D00-DE11-9183-001A9281174A.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0004/E82A236C-3200-DE11-8C9F-0018F3D095EE.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0004/E078BBA8-4400-DE11-8A56-00304867905A.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0004/DCE50C6D-4300-DE11-AFB5-001A928116B2.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0004/DA760003-3A00-DE11-85DA-003048679180.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0004/DA4DA8A8-6F00-DE11-B376-001A92810AE0.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0004/D6F37290-8400-DE11-AFF9-003048678F8E.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0004/D67D1E78-1C00-DE11-A86F-001A92810AC0.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0004/D47F59A7-7A00-DE11-B4FB-003048678FA6.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0004/D21B912B-8900-DE11-8952-001A92971B48.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0004/D0FDC04B-7C00-DE11-A208-003048679162.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0004/D04F9114-A000-DE11-9EE2-001BFCDBD184.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0004/CCAF07D5-6700-DE11-BA1F-003048D15E24.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0004/C8E96DE7-4500-DE11-A2AC-003048678C26.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0004/C8E21775-9C00-DE11-AEC2-001A92971BBA.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0004/C6F4ABDC-3600-DE11-805E-003048754CE5.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0004/C6D49897-6300-DE11-990A-0018F3D0962C.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0004/BE7C9D0C-8600-DE11-9527-003048678D78.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0004/BCD324A9-EAFF-DD11-A657-003048678C9A.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0004/BC283099-3F00-DE11-9F75-00304867C136.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0004/BC25100A-4700-DE11-8AB6-003048678B26.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0004/B830AD05-A200-DE11-A58F-00304876A13B.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0004/B6C836F7-9F00-DE11-80B6-0030486790B8.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0004/B2D7C3A9-3700-DE11-841C-0017312A250B.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0004/ACB89BEF-6B00-DE11-805C-001731AF68BF.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0004/AAE87636-E0FF-DD11-8AFB-0018F3D095FE.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0004/A8109E66-4E00-DE11-B25E-003048678B14.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0004/A28FCDDE-DDFF-DD11-8558-0018F3D095EE.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0004/9CF60028-DDFF-DD11-A15D-0018F3D096E4.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0004/9CEB3D05-6900-DE11-AA2C-0030486792DE.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0004/9A17BF3D-5D00-DE11-8C9A-00304867BEDE.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0004/9843DE21-3F00-DE11-9B65-003048678B7E.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0004/94707CB1-7900-DE11-B540-001731AF66C2.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0004/9213A343-3E00-DE11-88A5-001A928116FC.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0004/906CC2F7-E1FF-DD11-80CE-003048767C73.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0004/9045ECEF-4500-DE11-9BB5-003048679000.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0004/8CEBDA0B-3A00-DE11-8E32-001A9281173C.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0004/8AE82954-2000-DE11-AA8C-001A92971AD0.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0004/8ADF779A-3F00-DE11-BC5B-003048678F74.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0004/8691B9DE-6500-DE11-B0A3-001A92810AB8.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0004/84CA4A00-4500-DE11-9612-003048678D9A.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0004/8490698B-5C00-DE11-AD22-001A92971B62.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0004/800EC214-8300-DE11-87D1-001A928116F0.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0004/7A398D59-4400-DE11-94CF-003048678E6E.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0004/78FA215E-A500-DE11-B71B-003048755187.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0004/726409AE-8700-DE11-8D10-001731AF6981.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0004/7236B8B6-3F00-DE11-B354-001BFCDBD1B6.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0004/6E6B92F1-5800-DE11-8F38-003048678B38.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0004/6461793C-4500-DE11-B7DB-003048678FFE.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0004/6259B45A-A500-DE11-84B8-003048678B1C.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0004/6081AC45-7400-DE11-B130-001731AF692F.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0004/5C8AC514-4100-DE11-8CB8-001A928116C4.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0004/5C628A50-9F00-DE11-BE82-003048679168.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0004/5AC5E25B-4400-DE11-98A0-00304866C398.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0004/5AA51530-5800-DE11-B791-0018F3D09630.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0004/5A6F36E9-4500-DE11-B4E1-003048678A6A.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0004/582CFA4F-6000-DE11-9CF7-003048678F74.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0004/56E783C8-8100-DE11-ACB0-00304867918A.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0004/5684B7CF-8B00-DE11-8A77-0018F3D095EC.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0004/50E5EEBB-4400-DE11-8478-003048678FDE.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0004/509B1F1E-3300-DE11-8710-0030487566E9.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0004/4EFD98B5-3F00-DE11-9906-001A92810AC0.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0004/4CDB736E-8400-DE11-B67C-0018F3D09686.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0004/46D72A14-8C00-DE11-9C1E-001731AF67C5.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0004/468F7C56-D600-DE11-B69F-0018F3D096F8.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0004/44BE3B10-E6FF-DD11-ACE9-001731AF66FD.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0004/445EDBDB-5C00-DE11-8E6C-001A928116CC.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0004/429CA79B-3500-DE11-8998-001731A28319.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0004/40A1F178-9C00-DE11-BD25-001A92971B06.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0004/406C09AD-1700-DE11-9102-001731A28319.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0004/3ABC06A2-3000-DE11-AA5B-0018F3D09670.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0004/3A7F1B5D-E4FF-DD11-A604-001A92810AA8.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0004/3A5B1455-7600-DE11-855A-003048769E6F.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0004/3668EB18-4100-DE11-BFEC-001A928116E8.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0004/365500EA-4500-DE11-8D51-00304867C16A.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0004/36124B79-B800-DE11-A3F0-0017319EB921.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0004/342E17FC-6300-DE11-A82A-003048678F1C.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0004/32E231FC-AF00-DE11-BACA-001A92810ACE.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0004/3287F28B-6500-DE11-9B58-001BFCDBD184.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0004/30BEB435-EDFF-DD11-BCBE-003048D15DB6.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0004/2ED91B9B-9D00-DE11-806B-003048679006.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0004/2AC68731-3F00-DE11-B34D-001A92810AEA.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0004/289E6297-4600-DE11-904C-003048678BE8.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0004/1CBD16D9-5600-DE11-A6B0-0018F3D09692.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0004/1C56BD72-AF00-DE11-B7C0-001731AF67ED.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0004/0C962006-6100-DE11-B2AA-003048678FF4.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0004/0A298366-3500-DE11-BA1C-0017312B5567.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0004/065F3F51-3E00-DE11-9683-00304875A9EB.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0004/04E68BB4-3100-DE11-AF54-0018F3D0962E.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0004/048C827F-6000-DE11-B953-0030486790B0.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0003/F8327BA1-4100-DE11-A5F6-001A92810ACE.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0003/ECDC1E39-4F00-DE11-AD14-001A92810AD0.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0003/EA2918C1-4100-DE11-B98C-003048678FE4.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0003/E6774466-6C00-DE11-8B43-003048678FF8.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0003/E4A3735F-8300-DE11-8882-001A92811734.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0003/E42F581B-DAFF-DD11-9ED1-003048769DC3.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0003/E2AE1305-4400-DE11-B89E-003048678B38.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0003/E20315F5-E9FF-DD11-93C4-0018F3D09644.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0003/E0294697-A100-DE11-85CD-003048678F9C.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0003/DA4BF064-4500-DE11-9CE2-003048678ED2.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0003/DA2BB572-9C00-DE11-91AA-003048678FDE.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0003/D667F915-4100-DE11-B332-003048678FEA.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0003/D614480F-7900-DE11-9F02-003048678B8E.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0003/D4E66D3B-3900-DE11-AB0D-003048679180.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0003/D2495FBB-A200-DE11-81F9-001A92971B8E.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0003/D06E25B5-6500-DE11-9345-001A92810AB8.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0003/CE4E4140-4F00-DE11-9FF6-00304875668B.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0003/CCAF7C9F-1E00-DE11-BB3D-0017319EB90D.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0003/CC7832A3-8700-DE11-8D82-001BFCDBD1BE.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0003/C8B43F22-4100-DE11-A8DA-003048679048.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0003/C4DEDBF6-4000-DE11-B8FF-0018F3D09634.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0003/BEAA4693-3700-DE11-9D5C-0030486791F2.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0003/BCC81F88-2500-DE11-B693-001731AF66B5.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0003/BC466F31-E1FF-DD11-80FB-0018F3D0967E.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0003/B8E80F3A-E0FF-DD11-BC24-001A92971AD0.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0003/B22A5F77-3500-DE11-B0EB-001A92810AD2.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0003/B20599D1-B100-DE11-B6DF-001A928116C4.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0003/AE6CCCEB-6000-DE11-AA85-003048D3FC94.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0003/AC9C5BBE-3500-DE11-8EA4-001A92971BBE.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0003/A0C7A53B-9F00-DE11-AF7F-001A928116C0.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0003/9CD6A485-4100-DE11-AACD-001BFCDBD1BE.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0003/989C6730-E0FF-DD11-B7B5-0018F3D0969C.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0003/946361F6-7F00-DE11-9E2C-001731AF6B83.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0003/92A60838-E8FF-DD11-88C6-003048679164.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0003/90C97794-6900-DE11-BADC-003048D42DC8.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0003/8E8F145A-9D00-DE11-A48B-003048678E2A.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0003/8AE7FC30-E0FF-DD11-A08B-0018F3D0969C.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0003/846A7AA0-B600-DE11-BBDB-003048767E59.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0003/8418B9BD-8400-DE11-8EA5-001731A2897B.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0003/840BAAE7-E0FF-DD11-B90C-001A92971B90.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0003/8407D36D-DBFF-DD11-A318-0018F3D096C6.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0003/7E7C1FFE-4300-DE11-B101-003048679244.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0003/7AF5CCF9-6B00-DE11-AC83-001731AF6A49.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0003/76575D27-DDFF-DD11-91BC-0018F3D09688.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0003/76428F00-AA00-DE11-997A-0018F3D095F0.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0003/74A7DE5F-DFFF-DD11-9570-001A92971AD0.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0003/74141FBA-4F00-DE11-8597-00304876A13B.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0003/668E7FF0-3D00-DE11-B604-00304875A7B3.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0003/607763FC-E8FF-DD11-B6DD-001A92811716.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0003/606D613D-9F00-DE11-8A7F-0018F3D095F0.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0003/5A9B2EBB-3B00-DE11-A3B4-0017312A247F.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0003/54C97412-3A00-DE11-AC0D-0018F3D0968C.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0003/52E0588D-DE00-DE11-90E3-001731AF684D.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0003/50E8DA9F-DBFF-DD11-A950-001731AF6943.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0003/50E5CBDC-4100-DE11-A439-003048678F8E.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0003/4E2C0665-B700-DE11-9C04-003048678FEA.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0003/4E02C6A5-3B00-DE11-AFA5-00304867906C.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0003/48BACF47-3300-DE11-BE24-001731230E47.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0003/4893DC40-7200-DE11-A48F-0018F3D0968C.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0003/42C2FA40-E0FF-DD11-B630-001A92971AA8.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0003/428BC371-8B00-DE11-945D-00304867BEC0.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0003/4247D594-4F00-DE11-B9B3-003048679228.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0003/405818FE-4300-DE11-8C54-003048678BAC.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0003/3C383730-7100-DE11-9DCE-0017312B56F7.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0003/3A31DD8D-8500-DE11-AED2-00304867901A.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0003/32AD0762-6D00-DE11-9ADE-001A9281172E.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0003/32A58CDD-6000-DE11-AD49-00304876A061.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0003/2C24F1D7-3300-DE11-850C-001A92971B08.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0003/286D61D4-E6FF-DD11-95FE-001731AF6879.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0003/2827EAB2-B000-DE11-87F2-001A92971B7C.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0003/2678D4AB-6A00-DE11-A917-0030486792B8.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0003/24DE276D-4200-DE11-9BBD-0017312310E7.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0003/20B1C2C9-8500-DE11-BE43-003048D42DC8.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0003/1EC5F84E-E1FF-DD11-8674-0018F3D0967A.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0003/18E7435C-7B00-DE11-892B-0018F3D09704.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0003/185F53DC-ECFF-DD11-8AF7-0018F3D0968A.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0003/14C3E771-6700-DE11-A29C-001A92810AE6.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0003/10244E66-ECFF-DD11-94B1-003048679048.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0003/0C79DB72-9C00-DE11-AB50-00304867900C.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0003/0461B9AD-6C00-DE11-B22E-0018F3D095FE.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0003/026F0F68-3700-DE11-A26E-001BFCDBD184.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0003/008A574F-AD00-DE11-870E-00304875A9E7.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0002/F0B72F13-3F00-DE11-AA7D-003048678F74.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0002/E427A0E7-7200-DE11-BED2-001A92971B28.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0002/DC689710-3D00-DE11-9FF1-003048678B74.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0002/D6DC4D15-A000-DE11-A4C7-001A92811748.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0002/CA8F9321-0700-DE11-B2E2-003048767EBB.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0002/C8588915-5100-DE11-8E11-001A92810AE0.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0002/C853367D-3200-DE11-8B6A-0018F3D096F8.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0002/C485B0F1-6500-DE11-BC49-003048678A6A.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0002/C0900161-9E00-DE11-B6A0-001A92810AA8.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0002/BA799FF9-5C00-DE11-A46A-003048679274.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0002/BA26E043-4300-DE11-8F33-001A92971B96.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0002/B6905618-4200-DE11-9F13-001A92810AEC.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0002/B43E208B-8B00-DE11-B353-001BFCDBD154.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0002/B24800AF-5C00-DE11-8D44-0018F3D0962C.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0002/B06A6F1C-3300-DE11-85A9-00304875AA17.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0002/AC6A3E1D-7600-DE11-8B57-0018F3D09660.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0002/AC68182C-9E00-DE11-B1D9-003048678A72.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0002/AC25CE23-0200-DE11-B760-00304867D838.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0002/AA6BA9A3-8500-DE11-8524-001A928116E8.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0002/A42EAD04-A000-DE11-8435-003048678FD6.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0002/9C73B373-4300-DE11-8E19-0018F3D096C8.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0002/905052F0-4700-DE11-8A70-003048678B88.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0002/7E7B5328-5F00-DE11-BA87-001731AF67BF.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0002/72E70F5C-E600-DE11-905A-00304875A9E7.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0002/6C387218-8C00-DE11-9467-003048767DD5.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0002/5E25654E-4300-DE11-8993-001A928116B2.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0002/5A4DF460-4100-DE11-A41B-0018F3D096AE.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0002/4CBFEB19-A000-DE11-823A-00304875AAEF.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0002/4A15D1CE-5700-DE11-84E7-00304867918A.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0002/468DDD55-4100-DE11-ACE4-001A928116FE.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0002/460D4301-EDFF-DD11-A817-003048679048.root' ] );
readFiles.extend( [

       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0002/44C44ADB-A500-DE11-A7D5-003048678B8E.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0002/3C6691C0-4400-DE11-883A-00304867900C.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0002/343CD852-4300-DE11-9DB1-001A92971B8C.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0002/2A3E314D-4300-DE11-951F-001A92971B8C.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0002/24032F45-4300-DE11-8138-0018F3D09634.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0002/2249E931-9E00-DE11-8FBC-003048678AC8.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0002/0EA442E0-3600-DE11-8993-00304875ABF1.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0002/0E560C39-EAFF-DD11-BB4D-001731AF6717.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0002/0A5C829F-1000-DE11-8FBF-0017312B5BAD.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0002/04808F21-6D00-DE11-A46D-00304875A59D.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0002/002A888E-9D00-DE11-84D2-003048678C3A.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0001/EE4DBCF5-E1FF-DD11-9B98-001A92971BD6.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0001/EC278F60-9E00-DE11-A6F9-0018F3D09682.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0001/EA3C6C79-DCFF-DD11-A861-001731AF6AE7.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0001/E23C7801-5500-DE11-A32B-001BFCDBD176.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0001/E076F476-DBFF-DD11-A87C-003048769E65.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0001/CE2A1CF7-E1FF-DD11-ABE3-0018F3D09708.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0001/C8048026-DAFF-DD11-81CC-001731AF6BD3.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0001/C6F4FE47-AF00-DE11-BD5A-00304867C1BA.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0001/C4615CBF-A100-DE11-995B-00304875AA15.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0001/C07F6637-4200-DE11-A488-0018F3D096A0.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0001/B825B7D0-E2FF-DD11-BCA4-00304875ABE5.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0001/B2065866-B200-DE11-B39D-001A928116D8.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0001/A8FA5137-E0FF-DD11-BF5F-0018F3D096EE.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0001/A68E77C9-8B00-DE11-95E3-00304867903E.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0001/A626E5C8-8B00-DE11-BC36-003048678B00.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0001/9A239C6B-8200-DE11-ABCF-001731AF6867.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0001/98BAC5C5-0500-DE11-A0D2-001A92971BA0.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0001/86557722-4100-DE11-954B-00304867BEDE.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0001/8095EAEC-6900-DE11-9B07-003048767E49.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0001/78D8861E-8900-DE11-8B6B-0018F3D096EE.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0001/6E20D44D-7E00-DE11-8EDD-003048678A78.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0001/6A74FA84-6200-DE11-BCFA-001A92811746.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0001/6288AD40-E8FF-DD11-BD9C-001731AF66B5.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0001/6264B0E4-0F00-DE11-8BBA-00304867C136.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0001/606ADAAC-E2FF-DD11-997E-001A92971B38.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0001/56D6A191-6A00-DE11-9C1F-003048679214.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0001/568033C7-E5FF-DD11-BD7E-001BFCDBD154.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0001/54DD2B3F-E8FF-DD11-827E-0017312B58FF.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0001/4860592A-7B00-DE11-BF33-001731AF6B79.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0001/466C4FF6-E1FF-DD11-A802-001BFCDBD11E.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0001/42CC7D38-E8FF-DD11-BE96-003048678B8E.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0001/407A543B-E0FF-DD11-8C6F-001A92971BA0.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0001/22E22FBC-9D00-DE11-89A3-003048D15D04.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0001/22BAA3C6-A100-DE11-BFD6-001731230FC9.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0001/1ED271E0-4100-DE11-9BCF-001A928116F2.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0001/16676540-8400-DE11-A3F2-001A92971B0E.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0001/0A0A8D14-4200-DE11-9F30-001A928116BA.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0001/04DEAB2B-8900-DE11-93EB-0018F3D095EC.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0001/005AC222-5E00-DE11-9AA7-001731AF68CB.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0000/FA369CBD-7100-DE11-9230-0030486790FE.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0000/F6A2401B-4400-DE11-BFDE-003048D15E02.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0000/F4017394-6300-DE11-BC02-003048758A07.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0000/F07E9AF6-A600-DE11-BEC9-00304875ABF7.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0000/EEC91647-7300-DE11-916B-00304867BFA8.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0000/ECF34E1B-4400-DE11-9ABD-003048D15E02.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0000/E8D7391E-E5FF-DD11-9929-0018F3D096AE.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0000/E8C38ED4-3300-DE11-A522-0018F3C3E3A6.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0000/E8BF430D-6800-DE11-A2DB-0018F3D09680.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0000/E8A9DFF9-6300-DE11-B012-00304867920C.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0000/DE9BBC57-3C00-DE11-8B29-001BFCDBD1BA.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0000/DC58C3F3-A600-DE11-9BA0-001A92971AD0.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0000/D274F0F6-A000-DE11-88DC-001731AF6981.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0000/CEAE9F51-AC00-DE11-9151-003048678ED4.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0000/CC24D447-7700-DE11-B261-001A92971B06.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0000/C4CFF9FF-AA00-DE11-BBC7-0018F3D0968A.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0000/C006E2BB-A100-DE11-BEA3-003048679296.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0000/B6EEBEF2-4100-DE11-BE06-001A92810ABA.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0000/AC68CF18-3200-DE11-B1A4-001A92971B80.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0000/A8610BE1-A100-DE11-BBD1-00304875A8E5.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0000/A225385C-A500-DE11-8D60-001A92971ADC.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0000/9AE78300-A600-DE11-986B-003048679180.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0000/98626437-8400-DE11-AFD5-0030486790FE.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0000/942C101A-4400-DE11-8B27-003048679070.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0000/90557438-E8FF-DD11-9863-0030486792B4.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0000/904C9A48-4200-DE11-8224-001A92971B74.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0000/8E45E5BA-E3FF-DD11-8338-001A92971AD0.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0000/8A73C7B3-6F00-DE11-B118-001A92811722.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0000/883BB136-0B00-DE11-B7C1-0018F3D096E4.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0000/86413561-3500-DE11-B6A8-001A92810AEA.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0000/8461B711-4400-DE11-AC9C-003048D15D22.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0000/80AF0713-E5FF-DD11-9BB0-001A92971B16.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0000/7E695C0A-DCFF-DD11-8D53-003048679168.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0000/7C85EABC-3500-DE11-B19E-0017312B577F.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0000/7C7C0A27-4600-DE11-81D6-003048678B26.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0000/74C2C494-E900-DE11-9431-001731AF685B.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0000/66850168-4300-DE11-9CEB-0018F3D09692.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0000/6661E317-4400-DE11-9F92-00304867BFC6.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0000/62CC9491-5C00-DE11-9B8F-001BFCDBD154.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0000/60F6299A-E2FF-DD11-9D9D-0018F3D0962C.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0000/600395FE-AF00-DE11-A5C3-0018F3D096DE.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0000/5CA13FC3-8800-DE11-B13D-001731A288A1.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0000/5A5FC676-9C00-DE11-98DC-003048754C6D.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0000/5A5611FA-6300-DE11-B615-001A92971BBA.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0000/5889C5B0-5900-DE11-B98F-0018F3D0960A.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0000/56B92F16-4300-DE11-A096-0018F3D096DE.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0000/4EEE49C3-5D00-DE11-95C3-003048678E2A.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0000/42ABD772-9C00-DE11-A730-00304867902E.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0000/4037B794-6100-DE11-8028-003048678FF4.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0000/3ADCC197-6900-DE11-BE06-003048678ADA.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0000/348876C3-6000-DE11-A66E-00304867C0C4.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0000/3424697B-0100-DE11-828C-0018F3D09702.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0000/32F4AAF5-2100-DE11-B4F0-003048D42D92.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0000/30DAA68E-EAFF-DD11-AD53-00304867C136.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0000/2EAB1517-8300-DE11-A511-001A92810A96.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0000/2E86EEF9-A000-DE11-A5A2-001731AF6873.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0000/288DE184-8600-DE11-9DE6-003048678F0C.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0000/281B7269-3800-DE11-BE97-001A92811716.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0000/22E8C312-E5FF-DD11-85F1-0018F3D09626.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0000/22B58E39-3F00-DE11-9757-001A928116C4.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0000/2204042D-4600-DE11-AC70-003048678B0E.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0000/20302C74-1600-DE11-B3AC-001731AF698D.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0000/1CC5CD7D-B100-DE11-A325-001A928116EC.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0000/1CA92B66-ECFF-DD11-84C5-003048678F8E.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0000/1A30AADA-4100-DE11-B1DD-001A92811708.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0000/1A182EC8-9C00-DE11-B5DB-001731AF66F1.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0000/16D10875-9C00-DE11-A416-001A92811718.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0000/10CB500F-E5FF-DD11-899A-001A92810AA4.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0000/0A9884D9-DEFF-DD11-A106-0018F3D09624.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0000/06B91E73-9C00-DE11-AE57-003048678FC6.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0000/06596A17-E5FF-DD11-B918-001A92971BD8.root' ] );


secFiles.extend( [

] );



