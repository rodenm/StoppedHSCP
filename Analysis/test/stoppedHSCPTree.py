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


# path
process.myPath = cms.Path(

# rerun HLT sequence (quick and dirty)
    process.HLT_StoppedHSCP_8E29_Sequence

# filter on HLT bit (do not re-run HLT in same job!!!)
#    process.hltHighLevel

# recreate info not in RECO
    +process.hcalDigis
    +process.gtDigis
    +process.gctDigis
    +process.l1extraParticles

# generate TTree    
    +process.stoppedHSCPTree
)


process.schedule = cms.Schedule(
    process.myPath
)

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring() 
process.source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)

readFiles.extend( [
    '/store/caf/user/jbrooke/CRAFT09_HLT_v5/hltOutputA_1.root',
    '/store/caf/user/jbrooke/CRAFT09_HLT_v5/hltOutputA_2.root',    
    '/store/caf/user/jbrooke/CRAFT09_HLT_v5/hltOutputA_3.root',    
    '/store/caf/user/jbrooke/CRAFT09_HLT_v5/hltOutputA_4.root',    
    '/store/caf/user/jbrooke/CRAFT09_HLT_v5/hltOutputA_5.root',    
    '/store/caf/user/jbrooke/CRAFT09_HLT_v5/hltOutputA_6.root',    
    '/store/caf/user/jbrooke/CRAFT09_HLT_v5/hltOutputA_7.root',    
    '/store/caf/user/jbrooke/CRAFT09_HLT_v5/hltOutputA_8.root'    
] );


secFiles.extend( [
               ] )
