#
#  produce stopped HSCP TTree
#  assumes RAW, HLT, RECO data present
#  Run this on StoppedHSCP Skim
#
#  includes a check that the event passed stopped HSCP HLT
#  (may want to turn this off for MC)
#

import FWCore.ParameterSet.Config as cms

process = cms.Process("SHSCPTree")

process.load('Configuration/StandardSequences/Services_cff')
process.load('FWCore/MessageService/MessageLogger_cfi')
#process.MessageLogger.cerr.INFO.limit = cms.untracked.int32(10)


# geometry & magnetic field
process.load('Configuration/StandardSequences/GeometryIdeal_cff')
process.load("Configuration.StandardSequences.MagneticField_38T_cff")
process.load("Configuration.StandardSequences.Reconstruction_cff")

# conditions
process.load('Configuration/StandardSequences/FrontierConditions_GlobalTag_cff')

# HLT bit filter
process.load('HLTrigger.HLTfilters.hltHighLevel_cfi')
process.hltHighLevel.TriggerResultsTag = cms.InputTag("TriggerResults","","HLT")
process.hltHighLevel.HLTPaths = cms.vstring("HLT_StoppedHSCP")

# things missing from RECO
process.load('Configuration/StandardSequences/RawToDigi_Data_cff')
process.load('L1Trigger.Configuration.L1Extra_cff')

# Ntuple producer
process.load('StoppedHSCP/Analysis/stoppedHSCPTree_cfi')

# Ken's histogrammer
process.load('StoppedHSCP/Analysis/jetanalyzer_cfi')

# HCAL noise filter
process.load('CommonTools/RecoAlgos/HBHENoiseFilter_cfi')

# path
process.ntuple = cms.Path(

# filter on HLT bit
    process.hltHighLevel

# CRAFT 09 reproduce missing digis etc
    +process.hcalDigis
    +process.gtDigis
    +process.gctDigis
    +process.l1extraParticles
    
# filter HCAL noise
    +process.HBHENoiseFilter

# generate TTree    
    +process.stoppedHSCPTree
)

# histogram output file
process.TFileService = cms.Service("TFileService",
    fileName = cms.string('stoppedHSCPTree.root')
)


# input files
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(100) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring()
process.source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)


# Global Tag and input files
process.GlobalTag.globaltag = "GR10_P_V6::All"

readFiles.extend( [

   ] )


secFiles.extend( [

               ] )
