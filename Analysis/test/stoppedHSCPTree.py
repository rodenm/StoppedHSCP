#
#  produce stopped HSCP TTree
#  assumes RAW, HLT, RECO data present
#  Run this on StoppedHSCP Skim
#

import FWCore.ParameterSet.Config as cms

process = cms.Process("SHSCPTree")

# import of standard configurations

process.load('Configuration/StandardSequences/Services_cff')
process.load('FWCore/MessageService/MessageLogger_cfi')
process.MessageLogger.cerr.INFO.limit = cms.untracked.int32(10)

process.load('Configuration/StandardSequences/GeometryIdeal_cff')
process.load('Configuration/StandardSequences/RawToDigi_Data_cff')
process.load('Configuration/StandardSequences/ReconstructionCosmics_cff')
process.load('DQMOffline/Configuration/DQMOfflineCosmics_cff')
process.load('Configuration/StandardSequences/EndOfProcess_cff')
process.load('Configuration/EventContent/EventContentCosmics_cff')
# Magnetic field: force mag field to be 3.8 tesla
process.load("Configuration.StandardSequences.MagneticField_38T_cff")

process.load('Configuration/StandardSequences/FrontierConditions_GlobalTag_cff')


process.GlobalTag.globaltag = "GR09_31X_V5P::All"  # CRAFT 09
#process.GlobalTag.globaltag = "CRAFT08_R_V1::All"  # CRAFT 08

process.options = cms.untracked.PSet(
    Rethrow = cms.untracked.vstring('ProductNotFound')
)

# L1 bit filter
process.load('L1Trigger/Skimmer/l1Filter_cfi')
# CRAFT 08 bit
#process.l1Filter.algorithms = cms.vstring("L1_SingleJet10")
# CRAFT 09 bit
process.l1Filter.algorithms = cms.vstring("L1_SingleJet10_NotBptxC")
process.l1Filter.inputTag = cms.InputTag("gtDigis")

# re-run HLT (will have subtly different EventSetup config from real HLT!!!)
process.load('StoppedHSCP.Analysis.HLT_StoppedHSCP_cff')

# L1 tech bit filter
from HLTrigger.HLTfilters.hltLevel1GTSeed_cfi import hltLevel1GTSeed
process.ttFilter = hltLevel1GTSeed.clone()
process.ttFilter.L1TechTriggerSeeding = cms.bool(True)
process.ttFilter.L1SeedsLogicalExpression = cms.string('3 AND NOT 4')

process.load('L1TriggerConfig.L1GtConfigProducers.L1GtTriggerMaskTechTrigConfig_cff')



# HLT bit filter
process.load('HLTrigger.HLTfilters.hltHighLevel_cfi')
process.hltHighLevel.TriggerResultsTag = cms.InputTag("TriggerResults","","HLT2")
process.hltHighLevel.HLTPaths = cms.vstring("HLT_StoppedHSCP_8E29")

# Ben's fake HLT filter
process.load('StoppedHSCP.Analysis.caloFilter_cfi')

# things missing from RECO
process.load('Configuration.StandardSequences.RawToDigi_Data_cff')
process.load('L1Trigger.Configuration.L1Extra_cff')

# Ntuple producer
process.load('StoppedHSCP/Analysis/stoppedHSCPTree_cfi')
process.stoppedHSCPTree.doDigis = cms.untracked.bool(False)

process.TFileService = cms.Service("TFileService",
    fileName = cms.string('stoppedHSCPTree.root')
)

# Bens ntuple producer
process.load('StoppedHSCP/Analysis/globalRunAnalyser_cfi')

# Ken's histogrammer
process.load('StoppedHSCP/Analysis/jetanalyzer_cfi')

# path
process.myPath = cms.Path(

# filter on L1 bit
#    process.l1Filter

# filter on L1 tech bit
    process.ttFilter

# filter on HLT bit (do not re-run HLT in same job!!!)
#    process.hltHighLevel

# rerun HLT sequence (quick and dirty, not the full one)
#    process.HLT_StoppedHSCP_8E29_Sequence

# re-reco
#    +process.RawToDigi
#    +process.reconstructionCosmics

# CRAFT 09 reproduce missing RECO info
    +process.hcalDigis
    +process.gtDigis
    +process.gctDigis
    +process.l1extraParticles

# fake HLT selection
    +process.caloFilter

# Ken's histograms
    +process.jetanalyzer

# generate TTree    
    +process.stoppedHSCPTree

# generate Ben's tree
    +process.globalRunAnalyser
)


process.schedule = cms.Schedule(
    process.myPath
)

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
process.source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)

# CRAFT 09 skim
readFiles.extend( [

# beam halo skim
    'file:/afs/cern.ch/cms/CAF/CMSCOMM/COMM_CSC/data/2009/FirstBeam/selectedEvents_121964_beamhalo.root'

    
#   '/store/data/CRAFT09/Calo/RAW-RECO/GR09_31X_V5P_StoppedHSCP-332_v4/0022/FC9ECC6F-2299-DE11-BA40-0018F3D09636.root',
#   '/store/data/CRAFT09/Calo/RAW-RECO/GR09_31X_V5P_StoppedHSCP-332_v4/0022/FC6A5AAA-CA98-DE11-A0F2-001A92810AE0.root',
#   '/store/data/CRAFT09/Calo/RAW-RECO/GR09_31X_V5P_StoppedHSCP-332_v4/0022/FC351559-2299-DE11-B23A-001A92810AE4.root',
#   '/store/data/CRAFT09/Calo/RAW-RECO/GR09_31X_V5P_StoppedHSCP-332_v4/0022/F0B42B50-1F99-DE11-B7E4-001A92810A94.root',
#   '/store/data/CRAFT09/Calo/RAW-RECO/GR09_31X_V5P_StoppedHSCP-332_v4/0022/EAABE6E3-3999-DE11-858E-003048679076.root'
   ] )

# CRAFT 09 Calo PD
## readFiles.extend( [
##        '/store/data/CRAFT09/Calo/RECO/v1/000/111/039/F6DD2D0D-578C-DE11-B40A-001D09F25109.root',
##        '/store/data/CRAFT09/Calo/RECO/v1/000/111/039/F26AF5C0-578C-DE11-82FF-001D09F23C73.root',
##        '/store/data/CRAFT09/Calo/RECO/v1/000/111/039/F07B6B77-538C-DE11-98FA-001617C3B778.root',
##        '/store/data/CRAFT09/Calo/RECO/v1/000/111/039/F05C4FBD-578C-DE11-8114-0019B9F7310E.root',
##        '/store/data/CRAFT09/Calo/RECO/v1/000/111/039/E86BE539-528C-DE11-99BA-001D09F28F1B.root',
##        '/store/data/CRAFT09/Calo/RECO/v1/000/111/039/E2414B50-568C-DE11-8C68-001D09F23E53.root',
##        '/store/data/CRAFT09/Calo/RECO/v1/000/111/039/E04AB303-578C-DE11-B349-003048D37538.root',
##        '/store/data/CRAFT09/Calo/RECO/v1/000/111/039/D69E3B0E-578C-DE11-AB10-003048D2C0F0.root',
##        '/store/data/CRAFT09/Calo/RECO/v1/000/111/039/D66DF737-528C-DE11-8DC5-003048D37456.root',
##        '/store/data/CRAFT09/Calo/RECO/v1/000/111/039/CAA978C7-528C-DE11-9861-001D09F295FB.root',
##        '/store/data/CRAFT09/Calo/RECO/v1/000/111/039/C4EB718F-648C-DE11-8EC9-001D09F2960F.root',
##        '/store/data/CRAFT09/Calo/RECO/v1/000/111/039/C0555F03-578C-DE11-A5A4-003048D2BE12.root',
##        '/store/data/CRAFT09/Calo/RECO/v1/000/111/039/9A5D550D-578C-DE11-9E70-003048D2C0F4.root',
##        '/store/data/CRAFT09/Calo/RECO/v1/000/111/039/92CD0F04-578C-DE11-8C9E-0030486733D8.root',
##        '/store/data/CRAFT09/Calo/RECO/v1/000/111/039/7ECE0404-578C-DE11-AF0F-0030486780B8.root',
##        '/store/data/CRAFT09/Calo/RECO/v1/000/111/039/7C1092C2-528C-DE11-AF45-003048D2BE06.root',
##        '/store/data/CRAFT09/Calo/RECO/v1/000/111/039/7A1C07E2-548C-DE11-88AB-001617E30D40.root',
##        '/store/data/CRAFT09/Calo/RECO/v1/000/111/039/707D6304-578C-DE11-BA85-003048D3750A.root',
##        '/store/data/CRAFT09/Calo/RECO/v1/000/111/039/6EBDD003-578C-DE11-8D4F-003048D2BED6.root',
##        '/store/data/CRAFT09/Calo/RECO/v1/000/111/039/5A1FF5BD-578C-DE11-BD3C-001D09F27003.root',
##        '/store/data/CRAFT09/Calo/RECO/v1/000/111/039/4E77F30A-578C-DE11-B36C-001D09F2910A.root',
##        '/store/data/CRAFT09/Calo/RECO/v1/000/111/039/324AC451-568C-DE11-80AB-001D09F23A02.root',
##        '/store/data/CRAFT09/Calo/RECO/v1/000/111/039/1CDAB003-578C-DE11-BB94-003048D2BE06.root',
##        '/store/data/CRAFT09/Calo/RECO/v1/000/111/039/0818E60D-578C-DE11-8464-001D09F23D04.root',
##        '/store/data/CRAFT09/Calo/RECO/v1/000/111/039/0461CE03-578C-DE11-9ADF-003048D2C020.root',
##        '/store/data/CRAFT09/Calo/RECO/v1/000/111/039/021B1B76-538C-DE11-9868-000423D6B444.root' ] );


# CRAFT 08 test RAW data
#readFiles.extend( [
#        '/store/data/Commissioning08/Cosmics/RAW-RECO/CRAFT_ALL_V9_SuperPointing_225-v3/0012/1A8C28D2-0402-DE11-84C0-0018F3D09644.root'
#    ] )


secFiles.extend( [
               ] )
