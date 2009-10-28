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
process.GlobalTag.globaltag = "GR09_31X_V5P::All"

process.options = cms.untracked.PSet(
    Rethrow = cms.untracked.vstring('ProductNotFound')
)

# L1 bit filter
process.load('L1Trigger/Skimmer/l1Filter_cfi')
process.l1Filter.algorithms = cms.vstring("L1_SingleJet10")

# re-run HLT (will have subtly different EventSetup config from real HLT!!!)
process.load('StoppedHSCP.Analysis.HLT_StoppedHSCP_cff')


# HLT bit filter
process.load('HLTrigger.HLTfilters.hltHighLevel_cfi')
process.hltHighLevel.TriggerResultsTag = cms.InputTag("TriggerResults","","HLT2")
process.hltHighLevel.HLTPaths = cms.vstring("HLT_StoppedHSCP_8E29")


# things missing from RECO
process.load('Configuration.StandardSequences.RawToDigi_Data_cff')
process.load('L1Trigger.Configuration.L1Extra_cff')

# Ntuple producer
process.load('StoppedHSCP/Analysis/stoppedHSCPTree_cfi')

process.TFileService = cms.Service("TFileService",
    fileName = cms.string('stoppedHSCPTree.root')
)

# Bens ntuple producer
process.load('StoppedHSCP/Analysis/globalRunAnalyser_cfi')

# Ken's histogrammer
process.load('StoppedHSCP/Analysis/jetanalyzer_cfi')

# path
process.myPath = cms.Path(

# filter on HLT bit (do not re-run HLT in same job!!!)
#    process.hltHighLevel

# rerun HLT sequence (quick and dirty)
    process.HLT_StoppedHSCP_8E29_Sequence

# CRAFT 08 re-reco
    +process.RawToDigi
    +process.l1Filter
    +process.reconstructionCosmics

# CRAFT 09 reproduce missing RECO info
#    +process.hcalDigis
#    +process.gtDigis
#    +process.gctDigis
    +process.l1extraParticles

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

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(100) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
process.source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)

# CRAFT 09 skim
#readFiles.extend( [
#    '/store/data/CRAFT09/Calo/RAW-RECO/GR09_31X_V5P_StoppedHSCP-332_v4/0022/FC9ECC6F-2299-DE11-BA40-0018F3D09636.root',
#    '/store/data/CRAFT09/Calo/RAW-RECO/GR09_31X_V5P_StoppedHSCP-332_v4/0022/FC6A5AAA-CA98-DE11-A0F2-001A92810AE0.root',
#    '/store/data/CRAFT09/Calo/RAW-RECO/GR09_31X_V5P_StoppedHSCP-332_v4/0022/FC351559-2299-DE11-B23A-001A92810AE4.root',
#    '/store/data/CRAFT09/Calo/RAW-RECO/GR09_31X_V5P_StoppedHSCP-332_v4/0022/F0B42B50-1F99-DE11-B7E4-001A92810A94.root',
#    '/store/data/CRAFT09/Calo/RAW-RECO/GR09_31X_V5P_StoppedHSCP-332_v4/0022/EAABE6E3-3999-DE11-858E-003048679076.root'
#    ] )

# CRAFT 08 test RAW data
readFiles.extend( [
        '/store/data/Commissioning08/Cosmics/RAW-RECO/CRAFT_ALL_V9_SuperPointing_225-v3/0012/1A8C28D2-0402-DE11-84C0-0018F3D09644.root'
    ] )


secFiles.extend( [
               ] )
