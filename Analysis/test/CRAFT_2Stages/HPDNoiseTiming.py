
import FWCore.ParameterSet.Config as cms

process = cms.Process("FilterData")
process.load("FWCore.MessageLogger.MessageLogger_cfi")

process.load("CondCore.DBCommon.CondDBSetup_cfi")


process.maxEvents = cms.untracked.PSet(  input = cms.untracked.int32(1000) )
process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(
    '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0273/C425CF62-95F1-DD11-8D00-0015170AD178.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0273/18387281-B3F1-DD11-AEB1-003048635DDA.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0273/3C9930F4-BBF1-DD11-AF2E-0015170ACBB8.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0273/7662881B-B2F1-DD11-B680-00304863623E.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0272/6E87B00E-6BF1-DD11-88EE-0013D3228131.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0273/A6A45102-B3F1-DD11-8A7E-0015170AC798.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0273/7697E880-ADF1-DD11-B7EC-0015170AE650.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0273/3C0122C7-B7F1-DD11-B8A6-001A64789498.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0272/5C336180-68F1-DD11-B925-00161725E51C.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0273/3E0DD090-A0F1-DD11-B8C6-003048670B66.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0273/AC35D53B-96F1-DD11-8F96-001A64789DD4.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0272/EA6C47BB-6BF1-DD11-9986-0013D3541FDC.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0273/F4C1CD99-98F1-DD11-AC68-00E081791761.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0273/98498488-A9F1-DD11-A8A9-00E08178C053.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0273/50FDEC71-B9F1-DD11-BB1A-00E0817917D9.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0273/58371C48-A4F1-DD11-A822-0015170AE404.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0272/E2B549EC-6AF1-DD11-94CF-00161725E504.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0273/72EA06F3-8CF1-DD11-9060-0015170AE3B8.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0273/2A3B5AF4-98F1-DD11-86DD-00E08179186F.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0273/108D921D-AFF1-DD11-903F-00304863623C.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0273/78502C3F-AAF1-DD11-B0F7-001A64789D14.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0273/803F0DF6-BBF1-DD11-9DA8-00151715C5D4.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0273/FC58AA12-9AF1-DD11-BDEE-0013D32281CF.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0273/540C50DC-97F1-DD11-823E-0013D3228177.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0273/D0BD35CF-91F1-DD11-A5AF-0013D322812F.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0273/1A5BB284-AAF1-DD11-B29F-003048635E2C.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0273/B28CC0C5-A5F1-DD11-B288-0013D32281A5.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0273/1E3D1F5E-A1F1-DD11-B49F-0015170AE344.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0273/C04D425D-A9F1-DD11-AB8A-003048670B66.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0273/A0F7BF1A-B2F1-DD11-80D9-00E0817917B9.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0273/AA0D3FF6-AFF1-DD11-BEA5-001A6478AB7C.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0273/CA55A20B-B1F1-DD11-9603-00E08179183F.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0273/3627A507-BBF1-DD11-BB61-0013D3542064.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0273/1C44CD92-A0F1-DD11-BCB3-00304866C674.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0273/DED1F70A-90F1-DD11-B711-0015170AE418.root',
       '/store/data/Commissioning08/Calo/RAW-RECO/CRAFT_ALL_V4_HCALHighEnergy_HCALHighEnergy_v1/0273/2AABBC01-A5F1-DD11-93EE-0013D3228171.root' 


    
   
    )
)


process.load('Configuration.StandardSequences.L1Emulator_cff')

process.load('FastSimulation.L1CaloTriggerProducer.fastl1calosim_cfi')

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
    IncludeDigis=cms.untracked.bool(True),
    IncludeCaloTowers=cms.untracked.bool(True),
    IncludeRecHits=cms.untracked.bool(False),                                 
    IncludeMC=cms.untracked.bool(False),
    IncludeJets=cms.untracked.bool(True),
    IncludeMuons=cms.untracked.bool(True),
    WriteHistos=cms.untracked.bool(False)
)                                      


process.an_HLT = cms.EDFilter("GlobalRunAnalyser",
    IncludeJetDetails=cms.untracked.bool(True),
    IncludeDigis=cms.untracked.bool(False),
    IncludeDigisOld=cms.untracked.bool(True),
    IncludeCaloTowers=cms.untracked.bool(True),
    IncludeRecHits=cms.untracked.bool(False),                                 
    IncludeMC=cms.untracked.bool(False),
    IncludeJets=cms.untracked.bool(True),
    IncludeMuons=cms.untracked.bool(True),
    WriteHistos=cms.untracked.bool(False)
)

process.an_All = cms.EDFilter("GlobalRunAnalyser",
    IncludeJetDetails=cms.untracked.bool(True),
    IncludeDigis=cms.untracked.bool(True),
    IncludeCaloTowers=cms.untracked.bool(True),
    IncludeRecHits=cms.untracked.bool(False),                                 
    IncludeMC=cms.untracked.bool(False),
    IncludeJets=cms.untracked.bool(True),
    IncludeMuons=cms.untracked.bool(True),
    WriteHistos=cms.untracked.bool(False)
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
    CentralEta=cms.untracked.double(1.3)                         
                                  
)

process.noisefilter = cms.EDFilter("HLTHPDFilter",
    inputTag = cms.InputTag("hbhereco"),
    energy = cms.double(-99.0),
    hpdSpikeEnergy = cms.double(10.0),
    hpdSpikeIsolationEnergy = cms.double(1.0),
    rbxSpikeEnergy = cms.double(50.0),                               
    rbxSpikeUnbalance = cms.double(0.2)
)





# Paths
#########


process.allPath = cms.Path( process.RawToDigi_woGCT*
                            process.l1Filter*
                            process.hltenergycut*
                            process.an_HLT
 )

