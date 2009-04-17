
import FWCore.ParameterSet.Config as cms

process = cms.Process("FilterData")
process.load("FWCore.MessageLogger.MessageLogger_cfi")

process.load("CondCore.DBCommon.CondDBSetup_cfi")


process.maxEvents = cms.untracked.PSet(  input = cms.untracked.int32(2000) )
process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(
    '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0003/D2495FBB-A200-DE11-81F9-001A92971B8E.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0000/16D10875-9C00-DE11-A416-001A92811718.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0010/3A151CF4-7400-DE11-9C0D-003048678F9C.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0009/60749D6E-8A00-DE11-BFBB-001A928116AE.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0004/726409AE-8700-DE11-8D10-001731AF6981.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0004/2ED91B9B-9D00-DE11-806B-003048679006.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0005/26FF0027-4600-DE11-B2E9-003048678A7E.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0004/4EFD98B5-3F00-DE11-9906-001A92810AC0.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0000/1A30AADA-4100-DE11-B1DD-001A92811708.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0005/28B26A20-5100-DE11-9ECD-00304875AA61.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0003/92A60838-E8FF-DD11-88C6-003048679164.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0002/A42EAD04-A000-DE11-8435-003048678FD6.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0005/16D1478E-4400-DE11-962F-001A928116DE.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0000/281B7269-3800-DE11-BE97-001A92811716.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0000/74C2C494-E900-DE11-9431-001731AF685B.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0003/BCC81F88-2500-DE11-B693-001731AF66B5.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0008/A034FFC7-9C00-DE11-BD49-001731AF6AC5.root',
       '/store/data/Commissioning08/Calo/RECO/CRAFT_ALL_V9_225-v3/0000/E8A9DFF9-6300-DE11-B012-00304867920C.root'
       
   
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
process.GlobalTag.globaltag = "CRAFT_ALL_V9::All"
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
    IncludeDigisOld=cms.untracked.bool(False),
    IncludeCaloTowers=cms.untracked.bool(True),
    IncludeRecHits=cms.untracked.bool(False),                                 
    IncludeMC=cms.untracked.bool(False),
    IncludeJets=cms.untracked.bool(True),
    IncludeMuons=cms.untracked.bool(True)                                   
)                                      


process.an_HLT = cms.EDFilter("GlobalRunAnalyser",
    IncludeJetDetails=cms.untracked.bool(True),
    IncludeDigisOld=cms.untracked.bool(False),
    IncludeCaloTowers=cms.untracked.bool(True),
    IncludeRecHits=cms.untracked.bool(False),                                 
    IncludeMC=cms.untracked.bool(False),
    IncludeJets=cms.untracked.bool(True),
    IncludeMuons=cms.untracked.bool(True)                                      
)

process.an_All = cms.EDFilter("GlobalRunAnalyser",
    IncludeJetDetails=cms.untracked.bool(True),
    IncludeDigisOld=cms.untracked.bool(False),
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





# Paths
#########


process.allPath = cms.Path(  process.an_All *
                            process.l1Filter*
                            process.an_L1 *
                            process.noisefilter*
                            process.hltenergycut*
                            process.an_HLT
 )

