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
process.MessageLogger.cerr.threshold = ''
process.MessageLogger.cerr.FwkReport.reportEvery = 1000


# geometry & magnetic field
process.load('Configuration/StandardSequences/GeometryIdeal_cff')
process.load("Configuration.StandardSequences.MagneticField_38T_cff")
process.load("Configuration.StandardSequences.Reconstruction_cff")

# conditions
process.load('Configuration/StandardSequences/FrontierConditions_GlobalTag_cff')

# HLT bit filter
process.load('HLTrigger.HLTfilters.hltHighLevel_cfi')
process.hltHighLevel.TriggerResultsTag = cms.InputTag("TriggerResults","","HLT")
process.hltHighLevel.HLTPaths = cms.vstring(
    "HLT_JetE30_NoBPTX_v1",
    "HLT_JetE30_NoBPTX_NoHalo_v2",
    "HLT_JetE30_NoBPTX3BX_NoHalo_v2"
)

# add a flag indicating the HBHE noise 
process.load('CommonTools/RecoAlgos/HBHENoiseFilterResultProducer_cfi')

# Ntuple producer
process.load('StoppedHSCP/Analysis/stoppedHSCPTree_cfi')
#process.stoppedHSCPTree.hltPath = cms.untracked.string("HLT_StoppedHSCP*")

# path
process.ntuple = cms.Path(

# filter on HLT bit
    process.hltHighLevel

# filter HCAL noise
    +process.HBHENoiseFilterResultProducer

# generate TTree    
    +process.stoppedHSCPTree
)


#    outputCommands = cms.untracked.vstring('keep *'),
#    fileName = cms.untracked.string('test.root'),
#)
#process.out = cms.EndPath(process.output)


# TTree output file
process.TFileService = cms.Service("TFileService",
    fileName = cms.string('stoppedHSCPTree.root')
)


# input files
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )
readFiles = cms.untracked.vstring()
secFiles = cms.untracked.vstring()
process.source = cms.Source ("PoolSource",fileNames = readFiles, secondaryFileNames = secFiles)


# Global Tag and input files
process.GlobalTag.globaltag = "GR10_P_V10::All"

readFiles.extend( [
#    'file:///tmp/jbrooke/HLT_StoppedHSCP_148829.root'
#    'file:///tmp/jbrooke/test2.root'
#    'file:pickEvents_1375_1400.root',
#    'file:pickEvents_1408_1424.root',
#    'file:///tmp/jbrooke/D4EBF75E-14CB-DF11-9404-003048D15DDA.root'
   ] )


secFiles.extend( [

               ] )
