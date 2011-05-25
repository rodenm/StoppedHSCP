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
    "HLT_JetE30_NoBPTX_*",
    "HLT_JetE30_NoBPTX_NoHalo_*",
    "HLT_JetE30_NoBPTX3BX_NoHalo_*",
    "HLT_JetE50_NoBPTX3BX_NoHalo_*"
)

process.hltStoppedHSCPHpdFilter = cms.EDFilter( "HLTHPDFilter",
    inputTag = cms.InputTag( "hbhereco" ),
    energy = cms.double( -99.0 ),
    hpdSpikeEnergy = cms.double( 10.0 ),
    hpdSpikeIsolationEnergy = cms.double( 1.0 ),
    rbxSpikeEnergy = cms.double( 50.0 ),
    rbxSpikeUnbalance = cms.double( 0.2 )
)

process.load("CommonTools.RecoAlgos.HBHENoiseFilter_cfi")
process.HBHENoiseFilter.minNumIsolatedNoiseChannels = cms.int32(999999)
process.HBHENoiseFilter.minIsolatedNoiseSumE = cms.double(999999.)
process.HBHENoiseFilter.minIsolatedNoiseSumEt = cms.double(999999.)

# add a flag indicating the HBHE noise 
process.load('CommonTools/RecoAlgos/HBHENoiseFilterResultProducer_cfi')

# get RAW data
process.load('Configuration/StandardSequences/RawToDigi_Data_cff')
process.load('Configuration/StandardSequences/L1Extra_cff')

# Ntuple producer
process.load('StoppedHSCP/Analysis/stoppedHSCPTree_cfi')

# path
process.ntuple = cms.Path(

# filter on HLT bit
    process.hltHighLevel

# replicate HLT filter (for early 2011 data)
    +process.hltStoppedHSCPHpdFilter

# filter HCAL noise
    +process.HBHENoiseFilterResultProducer

# get hcal digis
    +process.gctDigis
    +process.gtDigis
    +process.l1extraParticles
    +process.hcalDigis

# generate TTree    
    +process.stoppedHSCPTree
)


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

    ] )


secFiles.extend( [

    ] )
