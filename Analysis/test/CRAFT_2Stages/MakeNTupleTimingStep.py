
import FWCore.ParameterSet.Config as cms

process = cms.Process("FilterData")
process.load("FWCore.MessageLogger.MessageLogger_cfi")

process.load("CondCore.DBCommon.CondDBSetup_cfi")


process.maxEvents = cms.untracked.PSet(  input = cms.untracked.int32(2000) )
process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring(
    '/store/data/Commissioning08/Calo/RAW/v1/000/068/021/9264B7F4-E6A5-DD11-85FD-000423D99B3E.root',
       '/store/data/Commissioning08/Calo/RAW/v1/000/068/021/F61B221F-EBA5-DD11-92AD-00161757BF42.root',
       '/store/data/Commissioning08/Calo/RAW/v1/000/068/021/10B024AA-59A6-DD11-B304-001617C3B6FE.root',
       '/store/data/Commissioning08/Calo/RAW/v1/000/068/021/3C4668DC-58A6-DD11-9469-000423D99A8E.root',
       '/store/data/Commissioning08/Calo/RAW/v1/000/068/021/20EA7B2C-45A6-DD11-A61C-000423D94700.root',
       '/store/data/Commissioning08/Calo/RAW/v1/000/068/021/A2E92744-5AA6-DD11-9CEA-000423D98B28.root',
       '/store/data/Commissioning08/Calo/RAW/v1/000/068/021/848394AC-54A6-DD11-B4F9-001D09F28EC1.root',
       '/store/data/Commissioning08/Calo/RAW/v1/000/068/021/AA128F56-5AA6-DD11-950F-0030487A3C9A.root',
       '/store/data/Commissioning08/Calo/RAW/v1/000/068/021/8E87747A-57A6-DD11-8899-000423D98AF0.root',
       '/store/data/Commissioning08/Calo/RAW/v1/000/068/021/74A8B9F0-26A6-DD11-B5E4-000423D952C0.root',
       '/store/data/Commissioning08/Calo/RAW/v1/000/068/021/BE0D681D-24A6-DD11-9AA1-001617E30D38.root',
       '/store/data/Commissioning08/Calo/RAW/v1/000/068/021/6C08A081-25A6-DD11-A0D4-001617C3B78C.root',
       '/store/data/Commissioning08/Calo/RAW/v1/000/068/021/3E8B583C-26A6-DD11-AD91-000423D94AA8.root',
       '/store/data/Commissioning08/Calo/RAW/v1/000/068/021/5A2B8D2F-1FA6-DD11-BEF8-001D09F27003.root',
       '/store/data/Commissioning08/Calo/RAW/v1/000/068/021/70D140E7-1FA6-DD11-BBCF-000423D6B42C.root',
       '/store/data/Commissioning08/Calo/RAW/v1/000/068/021/32E589AA-2EA6-DD11-ADE6-001617DBD5B2.root',
       '/store/data/Commissioning08/Calo/RAW/v1/000/068/021/F8024C2E-32A6-DD11-901B-001617C3B5E4.root',
       '/store/data/Commissioning08/Calo/RAW/v1/000/068/021/2044807A-2AA6-DD11-99CB-001617C3B70E.root',
       '/store/data/Commissioning08/Calo/RAW/v1/000/068/021/2A764AC3-30A6-DD11-9FBF-001617C3B654.root',
       '/store/data/Commissioning08/Calo/RAW/v1/000/068/021/AAEEC027-2BA6-DD11-854B-001D09F251D1.root',
       '/store/data/Commissioning08/Calo/RAW/v1/000/068/021/6478CD36-F9A5-DD11-AF2D-000423D98B5C.root',
       '/store/data/Commissioning08/Calo/RAW/v1/000/068/021/420F0B1B-FEA5-DD11-987C-000423D95030.root',
       '/store/data/Commissioning08/Calo/RAW/v1/000/068/021/D40320CA-03A6-DD11-AF22-000423D99614.root',
       '/store/data/Commissioning08/Calo/RAW/v1/000/068/021/3EED9AD8-FEA5-DD11-A975-000423D98C20.root',
       '/store/data/Commissioning08/Calo/RAW/v1/000/068/021/C49BC97E-FFA5-DD11-805A-001617E30D38.root',
       '/store/data/Commissioning08/Calo/RAW/v1/000/068/021/32F11468-FDA5-DD11-9394-001617E30D00.root',
       '/store/data/Commissioning08/Calo/RAW/v1/000/068/021/D0E04B66-1CA6-DD11-9128-0030487C6062.root',
       '/store/data/Commissioning08/Calo/RAW/v1/000/068/021/6C47F32E-18A6-DD11-A732-000423D9880C.root',
       '/store/data/Commissioning08/Calo/RAW/v1/000/068/021/7AA8A9F7-1AA6-DD11-AD3D-001617DF785A.root',
       '/store/data/Commissioning08/Calo/RAW/v1/000/068/021/7E8066DE-4AA6-DD11-B5BE-000423D94524.root',
  
   
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

process.an_Timing = cms.EDFilter("GlobalRunAnalyser",
    IncludeJetDetails=cms.untracked.bool(False),
    IncludeDigisOld=cms.untracked.bool(True),
    IncludeCaloTowers=cms.untracked.bool(False),
    IncludeRecHits=cms.untracked.bool(False),                                 
    IncludeMC=cms.untracked.bool(False),
    IncludeJets=cms.untracked.bool(False),
    IncludeMuons=cms.untracked.bool(False)                                   
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

process.extracttiming=cms.EDFilter("TimingExtractFltr",
    InputFile = cms.FileInPath('GluinoFilter/TimingExtractFltr/data/68021Events.txt'))





# Paths
#########


process.allPath = cms.Path(
    process.extracttiming*
    process.RawToDigi_woGCT * 
    process.an_Timing
 )

