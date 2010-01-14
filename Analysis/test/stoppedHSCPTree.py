#
#  produce stopped HSCP TTree
#  assumes RAW, HLT, RECO data present
#  includes a check that the event passed stopped HSCP HLT
#  (may want to turn this off for MC)
#

import FWCore.ParameterSet.Config as cms

process = cms.Process("SHSCPTree")

# import of standard configurations

process.load('Configuration/StandardSequences/Services_cff')
process.load('FWCore/MessageService/MessageLogger_cfi')
#process.MessageLogger.cerr.INFO.limit = cms.untracked.int32(10)

process.load('Configuration/StandardSequences/GeometryIdeal_cff')
process.load('Configuration/StandardSequences/RawToDigi_Data_cff')
process.load('Configuration/StandardSequences/ReconstructionCosmics_cff')
process.load('DQMOffline/Configuration/DQMOfflineCosmics_cff')
process.load('Configuration/StandardSequences/EndOfProcess_cff')
process.load('Configuration/EventContent/EventContentCosmics_cff')
# Magnetic field: force mag field to be 3.8 tesla
process.load("Configuration.StandardSequences.MagneticField_38T_cff")

process.load('Configuration/StandardSequences/FrontierConditions_GlobalTag_cff')

process.GlobalTag.globaltag = "GR09_R_V5::All"  # collisions reprocessing
#process.GlobalTag.globaltag = "GR09_31X_V5P::All"  # CRAFT 09
#process.GlobalTag.globaltag = "CRAFT08_R_V1::All"  # CRAFT 08

process.options = cms.untracked.PSet(
    Rethrow = cms.untracked.vstring('ProductNotFound')
)

# HLT bit filter
process.load('HLTrigger.HLTfilters.hltHighLevel_cfi')
process.hltHighLevel.TriggerResultsTag = cms.InputTag("TriggerResults","","HLT")
process.hltHighLevel.HLTPaths = cms.vstring("HLT_StoppedHSCP_8E29")

# Ntuple producer
process.load('StoppedHSCP/Analysis/stoppedHSCPTree_cfi')
process.stoppedHSCPTree.doDigis = cms.untracked.bool(False)

# Bens ntuple producer
process.load('StoppedHSCP/Analysis/globalRunAnalyser_cfi')

# Ken's histogrammer
process.load('StoppedHSCP/Analysis/jetanalyzer_cfi')

# histogram output file
process.TFileService = cms.Service("TFileService",
    fileName = cms.string('stoppedHSCPTree.root')
)



# path
process.myPath = cms.Path(

# filter on HLT bit (do not re-run HLT in same job!!!)
    process.hltHighLevel

# Collisions 09 reproduce missing digis etc
    +process.hcalDigis

# CRAFT 09 reproduce missing digis etc
#    +process.hcalDigis
#    +process.gtDigis
#    +process.gctDigis
#    +process.l1extraParticles

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


# input files
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring()
process.source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)

# CRAFT 09 skim
readFiles.extend( [

   ] )


secFiles.extend( [
               ] )
