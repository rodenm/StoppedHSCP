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
process.hltHighLevel.HLTPaths = cms.vstring("HLT_StoppedHSCP_8E29")

# things missing from RECO
process.load('Configuration/StandardSequences/RawToDigi_Data_cff')
process.load('L1Trigger.Configuration.L1Extra_cff')

# Ntuple producer
process.load('StoppedHSCP/Analysis/stoppedHSCPTree_cfi')


# Ben's ntuple producer
process.load('StoppedHSCP/Analysis/globalRunAnalyser_cfi')

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
#    +process.HBHENoiseFilter

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
process.GlobalTag.globaltag = "GR_R_36X_V12::All"

readFiles.extend( [
        '/store/data/Run2010A/MinimumBias/RAW-RECO/Skim_StoppedHSCP-May27thSkim_v3/0034/F41E77E7-2E6F-DF11-9C8E-00E08178C0FF.root',
        '/store/data/Run2010A/MinimumBias/RAW-RECO/Skim_StoppedHSCP-May27thSkim_v3/0034/EE5BCC14-2F6F-DF11-BE6B-00E0817917B9.root',
        '/store/data/Run2010A/MinimumBias/RAW-RECO/Skim_StoppedHSCP-May27thSkim_v3/0034/EC2F02EA-2E6F-DF11-9D68-003048635E2C.root',
        '/store/data/Run2010A/MinimumBias/RAW-RECO/Skim_StoppedHSCP-May27thSkim_v3/0034/EA4D19F3-2E6F-DF11-87E4-00E081791749.root'
    
#        '/store/data/Commissioning10/MinimumBias/RAW-RECO/Skim_StoppedHSCP-May27thSkim_v5/0022/FECEB1C8-B472-DF11-A462-002618943856.root',
#        '/store/data/Commissioning10/MinimumBias/RAW-RECO/Skim_StoppedHSCP-May27thSkim_v5/0022/FEC9C45A-B572-DF11-B77D-001A92971B8A.root',
#        '/store/data/Commissioning10/MinimumBias/RAW-RECO/Skim_StoppedHSCP-May27thSkim_v5/0022/FCFDBAD3-B472-DF11-9FAC-001BFCDBD154.root',
#        '/store/data/Commissioning10/MinimumBias/RAW-RECO/Skim_StoppedHSCP-May27thSkim_v5/0022/FCFB546D-B572-DF11-BE61-0018F3D09616.root',
#        '/store/data/Commissioning10/MinimumBias/RAW-RECO/Skim_StoppedHSCP-May27thSkim_v5/0022/FCA62A47-B572-DF11-A273-0018F3D095F2.root'
   ] )


secFiles.extend( [

               ] )
