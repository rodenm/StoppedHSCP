# Auto generated configuration file
# using: 
# Revision: 1.149 
# Source: /cvs_server/repositories/CMSSW/CMSSW/Configuration/PyReleaseValidation/python/ConfigBuilder.py,v 
# with command line options: promptCollisionReco -s RAW2DIGI,L1Reco,RECO,DQM,ALCA:SiStripCalZeroBias --datatier RECO --eventcontent RECO --conditions CRAFT09_R_V4::All --scenario pp --no_exec --data --magField AutoFromDBCurrent -n 100
import FWCore.ParameterSet.Config as cms

process = cms.Process('RECO2')

# import of standard configurations
process.load('Configuration/StandardSequences/Services_cff')
process.load('FWCore/MessageService/MessageLogger_cfi')
process.load('Configuration/StandardSequences/GeometryExtended_cff')
process.load('Configuration/StandardSequences/MagneticField_AutoFromDBCurrent_cff')
process.load('Configuration/StandardSequences/RawToDigi_Data_cff')
process.load('Configuration/StandardSequences/L1Reco_cff')
process.load('Configuration/StandardSequences/Reconstruction_cff')
process.load('DQMOffline/Configuration/DQMOffline_cff')
process.load('Configuration/StandardSequences/EndOfProcess_cff')
process.load('Configuration/StandardSequences/FrontierConditions_GlobalTag_cff')
process.load('Configuration/EventContent/EventContent_cff')
process.load('Configuration/StandardSequences/AlCaRecoStreams_cff')
process.load('Configuration/EventContent/AlCaRecoOutput_cff')

process.configurationMetadata = cms.untracked.PSet(
    version = cms.untracked.string('$Revision: 1.5 $'),
    annotation = cms.untracked.string('rereco nevts:100'),
    name = cms.untracked.string('PyReleaseValidation')
)
process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(100)
)
process.options = cms.untracked.PSet(
    Rethrow = cms.untracked.vstring('ProductNotFound'),
    wantSummary = cms.untracked.bool(True) 
)
# Input source
process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring( 
'/store/data/BeamCommissioning09/MinimumBias/RAW/v1/000/124/120/DC0FA50D-6BE8-DE11-8A92-000423D94E70.root'
#'file:/data/withvertex732.root'
#'/store/express/BeamCommissioning09/ExpressPhysics/FEVT/v2/000/123/615/38379AF1-B4E2-DE11-BB10-001617C3B706.root'
#'rfio:/castor.cern.ch/cms/store/data/BeamCommissioning09/castor/MinimumBias/RAW/v1/000/122/314/CC89C4BC-DE11-B365-0030487D0D3A.root'
    )
)

process.source.inputCommands = cms.untracked.vstring("keep *", "drop *_MEtoEDMConverter_*_*", "drop L1GlobalTriggerObjectMapRecord_hltL1GtObjectMap__HLT")

# Output definition
process.FEVT = cms.OutputModule("PoolOutputModule",
    splitLevel = cms.untracked.int32(0),
    outputCommands = process.RECOEventContent.outputCommands,
    fileName = cms.untracked.string('promptReco_RAW2DIGI_L1Reco_RECO_DQM_ALCA.root'),
    dataset = cms.untracked.PSet(
        dataTier = cms.untracked.string('RECO'),
        filterName = cms.untracked.string('')
    )
)

# Additional output definition
## process.ALCARECOStreamTkAlMinBias = cms.OutputModule("PoolOutputModule",
##     SelectEvents = cms.untracked.PSet(
##         SelectEvents = cms.vstring('pathALCARECOTkAlMinBias:RECO')
##     ),
##     outputCommands = process.OutALCARECOTkAlMinBias_noDrop.outputCommands,
##     fileName = cms.untracked.string('TkAlMinBias.root'),
##     dataset = cms.untracked.PSet(
##         filterName = cms.untracked.string('StreamTkAlMinBias'),
##         dataTier = cms.untracked.string('ALCARECO')
##     )
## )
## process.ALCARECOStreamTkAlMuonIsolated = cms.OutputModule("PoolOutputModule",
##     SelectEvents = cms.untracked.PSet(
##         SelectEvents = cms.vstring('pathALCARECOTkAlMuonIsolated:RECO')
##     ),
##     outputCommands = process.OutALCARECOTkAlMuonIsolated_noDrop.outputCommands,
##     fileName = cms.untracked.string('TkAlMuonIsolated.root'),
##     dataset = cms.untracked.PSet(
##         filterName = cms.untracked.string('StreamTkAlMuonIsolated'),
##         dataTier = cms.untracked.string('ALCARECO')
##     )
## )
## process.ALCARECOStreamMuAlOverlaps = cms.OutputModule("PoolOutputModule",
##     SelectEvents = cms.untracked.PSet(
##         SelectEvents = cms.vstring('pathALCARECOMuAlOverlaps:RECO')
##     ),
##     outputCommands = process.OutALCARECOMuAlOverlaps_noDrop.outputCommands,
##     fileName = cms.untracked.string('MuAlOverlaps.root'),
##     dataset = cms.untracked.PSet(
##         filterName = cms.untracked.string('StreamMuAlOverlaps'),
##         dataTier = cms.untracked.string('ALCARECO')
##     )
## )
## process.ALCARECOStreamMuAlCalIsolatedMu = cms.OutputModule("PoolOutputModule",
##     SelectEvents = cms.untracked.PSet(
##         SelectEvents = cms.vstring('pathALCARECOMuAlCalIsolatedMu:RECO')
##     ),
##     outputCommands = process.OutALCARECOMuAlCalIsolatedMu_noDrop.outputCommands,
##     fileName = cms.untracked.string('MuAlCalIsolatedMu.root'),
##     dataset = cms.untracked.PSet(
##         filterName = cms.untracked.string('StreamMuAlCalIsolatedMu'),
##         dataTier = cms.untracked.string('ALCARECO')
##     )
## )
## process.ALCARECOStreamHcalCalIsoTrk = cms.OutputModule("PoolOutputModule",
##     SelectEvents = cms.untracked.PSet(
##         SelectEvents = cms.vstring('pathALCARECOHcalCalIsoTrk:RECO')
##     ),
##     outputCommands = process.OutALCARECOHcalCalIsoTrk_noDrop.outputCommands,
##     fileName = cms.untracked.string('HcalCalIsoTrk.root'),
##     dataset = cms.untracked.PSet(
##         filterName = cms.untracked.string('StreamHcalCalIsoTrk'),
##         dataTier = cms.untracked.string('ALCARECO')
##     )
## )
## process.ALCARECOStreamHcalCalDijets = cms.OutputModule("PoolOutputModule",
##     SelectEvents = cms.untracked.PSet(
##         SelectEvents = cms.vstring('pathALCARECOHcalCalDijets:RECO')
##     ),
##     outputCommands = process.OutALCARECOHcalCalDijets_noDrop.outputCommands,
##     fileName = cms.untracked.string('HcalCalDijets.root'),
##     dataset = cms.untracked.PSet(
##         filterName = cms.untracked.string('StreamHcalCalDijets'),
##         dataTier = cms.untracked.string('ALCARECO')
##     )
## )
## process.ALCARECOStreamSiStripCalZeroBias = cms.OutputModule("PoolOutputModule",
##     SelectEvents = cms.untracked.PSet(
##         SelectEvents = cms.vstring('pathALCARECOSiStripCalZeroBias:RECO')
##     ),
##     outputCommands = process.OutALCARECOSiStripCalZeroBias_noDrop.outputCommands,
##     fileName = cms.untracked.string('SiStripCalZeroBias.root'),
##     dataset = cms.untracked.PSet(
##         filterName = cms.untracked.string('StreamSiStripCalZeroBias'),
##         dataTier = cms.untracked.string('ALCARECO')
##     )
## )

# KH, switching to V2B as in the request 
# Other statements
#process.GlobalTag.globaltag = 'GR09_R_35X_V2::All'
process.GlobalTag.globaltag = 'GR09_R_35_V2B::All'

# KH, adding lazy-download
process.AdaptorConfig = cms.Service("AdaptorConfig",
                                    stats = cms.untracked.bool(True),
                                    enable = cms.untracked.bool(True),
                                    #                                    tempDir = cms.untracked.string(""),
                                    cacheHint = cms.untracked.string("lazy-download"),
                                    readHint = cms.untracked.string("auto-detect"))


#####################################################################################################
####
####  Top level replaces for handling strange scenarios of early collisions
####

## TRACKING:
## Skip events with HV off
process.newSeedFromTriplets.ClusterCheckPSet.MaxNumberOfPixelClusters=2000
process.newSeedFromPairs.ClusterCheckPSet.MaxNumberOfCosmicClusters=10000
process.secTriplets.ClusterCheckPSet.MaxNumberOfPixelClusters=1000
process.fifthSeeds.ClusterCheckPSet.MaxNumberOfCosmicClusters = 5000
process.fourthPLSeeds.ClusterCheckPSet.MaxNumberOfCosmicClusters=10000

###### FIXES TRIPLETS FOR LARGE BS DISPLACEMENT ######

### pixelTracks
#---- replaces ----
process.pixelTracks.RegionFactoryPSet.ComponentName = 'GlobalRegionProducerFromBeamSpot' # was GlobalRegionProducer
#---- new parameters ----
process.pixelTracks.RegionFactoryPSet.RegionPSet.nSigmaZ  = cms.double(4.06) # was originHalfLength = 15.9; translated assuming sigmaZ ~ 3.8
process.pixelTracks.RegionFactoryPSet.RegionPSet.beamSpot = cms.InputTag("offlineBeamSpot")

### 0th step of iterative tracking
#---- replaces ----
process.newSeedFromTriplets.RegionFactoryPSet.ComponentName = 'GlobalRegionProducerFromBeamSpot' # was GlobalRegionProducer
#---- new parameters ----
process.newSeedFromTriplets.RegionFactoryPSet.RegionPSet.nSigmaZ   = cms.double(4.06)  # was originHalfLength = 15.9; translated assuming sigmaZ ~ 3.8
process.newSeedFromTriplets.RegionFactoryPSet.RegionPSet.beamSpot = cms.InputTag("offlineBeamSpot")

### 2nd step of iterative tracking
#---- replaces ----
process.secTriplets.RegionFactoryPSet.ComponentName = 'GlobalRegionProducerFromBeamSpot' # was GlobalRegionProducer
#---- new parameters ----
process.secTriplets.RegionFactoryPSet.RegionPSet.nSigmaZ  = cms.double(4.47)  # was originHalfLength = 17.5; translated assuming sigmaZ ~ 3.8
process.secTriplets.RegionFactoryPSet.RegionPSet.beamSpot = cms.InputTag("offlineBeamSpot")

## Primary Vertex
process.offlinePrimaryVerticesWithBS.PVSelParameters.maxDistanceToBeam = 2
process.offlinePrimaryVerticesWithBS.TkFilterParameters.maxNormalizedChi2 = 20
process.offlinePrimaryVerticesWithBS.TkFilterParameters.minSiliconHits = 6
process.offlinePrimaryVerticesWithBS.TkFilterParameters.maxD0Significance = 100
process.offlinePrimaryVerticesWithBS.TkFilterParameters.minPixelHits = 1
process.offlinePrimaryVerticesWithBS.TkClusParameters.zSeparation = 10
process.offlinePrimaryVertices.PVSelParameters.maxDistanceToBeam = 2
process.offlinePrimaryVertices.TkFilterParameters.maxNormalizedChi2 = 20
process.offlinePrimaryVertices.TkFilterParameters.minSiliconHits = 6
process.offlinePrimaryVertices.TkFilterParameters.maxD0Significance = 100
process.offlinePrimaryVertices.TkFilterParameters.minPixelHits = 1
process.offlinePrimaryVertices.TkClusParameters.zSeparation = 10

## ECAL 
process.ecalRecHit.ChannelStatusToBeExcluded = [ 1, 2, 3, 4, 8, 9, 10, 11, 12, 13, 14, 78, 142 ]

##Preshower
process.ecalPreshowerRecHit.ESBaseline = 0

##only for 34X
process.ecalPreshowerRecHit.ESRecoAlgo = cms.untracked.int32(1)

## HCAL temporary fixes
process.hfreco.firstSample  = 3
process.hfreco.samplesToAdd = 4

process.zdcreco.firstSample = 4
process.zdcreco.samplesToAdd = 3

## EGAMMA

process.gsfElectrons.applyPreselection = cms.bool(False)
process.photons.minSCEtBarrel = 1.
process.photons.minSCEtEndcap =1.
process.photonCore.minSCEt = 1.
process.conversionTrackCandidates.minSCEt =1.
process.conversions.minSCEt =1.
process.trackerOnlyConversions.AllowTrackBC = cms.bool(False)
process.trackerOnlyConversions.AllowRightBC = cms.bool(False)
process.trackerOnlyConversions.MinApproach = cms.double(-.25)
process.trackerOnlyConversions.DeltaCotTheta = cms.double(.07)
process.trackerOnlyConversions.DeltaPhi = cms.double(.2)

###
###  end of top level replacements
###
###############################################################################################

# produce L1 trigger object maps (temporary fix for HLT mistake 
# in event content definition of RAW datatier for stream A)
import L1Trigger.GlobalTrigger.gtDigis_cfi
process.hltL1GtObjectMap = L1Trigger.GlobalTrigger.gtDigis_cfi.gtDigis.clone()
process.hltL1GtObjectMap.GmtInputTag = cms.InputTag( "gtDigis" )
process.hltL1GtObjectMap.GctInputTag = cms.InputTag( "gctDigis" )
process.hltL1GtObjectMap.CastorInputTag = cms.InputTag( "castorL1Digis" )
process.hltL1GtObjectMap.ProduceL1GtDaqRecord = cms.bool( False )
process.hltL1GtObjectMap.ProduceL1GtEvmRecord = cms.bool( False )
process.hltL1GtObjectMap.ProduceL1GtObjectMapRecord = cms.bool( True )
process.hltL1GtObjectMap.WritePsbL1GtDaqRecord = cms.bool( False )
process.hltL1GtObjectMap.ReadTechnicalTriggerRecords = cms.bool( True )
process.hltL1GtObjectMap.EmulateBxInEvent = cms.int32( 1 )
process.hltL1GtObjectMap.AlternativeNrBxBoardDaq = cms.uint32( 0 )
process.hltL1GtObjectMap.AlternativeNrBxBoardEvm = cms.uint32( 0 )
process.hltL1GtObjectMap.BstLengthBytes = cms.int32( -1 )
process.hltL1GtObjectMap.TechnicalTriggersInputTags = cms.VInputTag( 'simBscDigis' )
process.hltL1GtObjectMap.RecordLength = cms.vint32( 3, 0 )



# Path and EndPath definitions
process.raw2digi_step = cms.Path(process.RawToDigi)
process.L1GtObjectMap_step = cms.Path(process.hltL1GtObjectMap)
process.L1Reco_step = cms.Path(process.L1Reco)
process.reconstruction_step = cms.Path(process.reconstruction_withPixellessTk)
process.dqmoffline_step = cms.Path(process.DQMOffline)
process.endjob_step = cms.Path(process.endOfProcess)
process.out_step = cms.EndPath(process.FEVT)

## process.pathALCARECOHcalCalIsoTrk = cms.Path(process.seqALCARECOHcalCalIsoTrk*process.ALCARECOHcalCalIsoTrackDQM)
## process.pathALCARECOTkAlMuonIsolated = cms.Path(process.seqALCARECOTkAlMuonIsolated*process.ALCARECOTkAlMuonIsolatedDQM)
## process.pathALCARECOHcalCalDijets = cms.Path(process.seqALCARECOHcalCalDijets*process.ALCARECOHcalCalDiJetsDQM)
## process.pathALCARECOMuAlCalIsolatedMu = cms.Path(process.seqALCARECOMuAlCalIsolatedMu*process.ALCARECOMuAlCalIsolatedMuDQM*process.ALCARECODTCalibrationDQM)
## process.pathALCARECOSiStripCalZeroBias = cms.Path(process.seqALCARECOSiStripCalZeroBias*process.ALCARECOSiStripCalZeroBiasDQM)
## process.pathALCARECOTkAlMinBias = cms.Path(process.seqALCARECOTkAlMinBias*process.ALCARECOTkAlMinBiasDQM)
## process.pathALCARECOMuAlOverlaps = cms.Path(process.seqALCARECOMuAlOverlaps*process.ALCARECOMuAlOverlapsDQM)

## process.ALCARECOStreamTkAlMinBiasOutPath = cms.EndPath(process.ALCARECOStreamTkAlMinBias)
## process.ALCARECOStreamTkAlMuonIsolatedOutPath = cms.EndPath(process.ALCARECOStreamTkAlMuonIsolated)
## process.ALCARECOStreamMuAlOverlapsOutPath = cms.EndPath(process.ALCARECOStreamMuAlOverlaps)
## process.ALCARECOStreamMuAlCalIsolatedMuOutPath = cms.EndPath(process.ALCARECOStreamMuAlCalIsolatedMu)
## process.ALCARECOStreamHcalCalIsoTrkOutPath = cms.EndPath(process.ALCARECOStreamHcalCalIsoTrk)
## process.ALCARECOStreamHcalCalDijetsOutPath = cms.EndPath(process.ALCARECOStreamHcalCalDijets)
## process.ALCARECOStreamSiStripCalZeroBiasOutPath = cms.EndPath(process.ALCARECOStreamSiStripCalZeroBias)

# Schedule definition
#process.schedule = cms.Schedule(process.raw2digi_step,process.L1GtObjectMap_step,process.L1Reco_step,process.reconstruction_step,process.dqmoffline_step,process.pathALCARECOSiStripCalZeroBias,process.pathALCARECOTkAlMinBias,process.pathALCARECOTkAlMuonIsolated,process.pathALCARECOMuAlCalIsolatedMu,process.pathALCARECOMuAlOverlaps,process.pathALCARECOHcalCalIsoTrk,process.pathALCARECOHcalCalDijets,process.endjob_step,process.out_step,process.ALCARECOStreamTkAlMinBiasOutPath,process.ALCARECOStreamTkAlMuonIsolatedOutPath,process.ALCARECOStreamMuAlOverlapsOutPath,process.ALCARECOStreamMuAlCalIsolatedMuOutPath,process.ALCARECOStreamHcalCalIsoTrkOutPath,process.ALCARECOStreamHcalCalDijetsOutPath,process.ALCARECOStreamSiStripCalZeroBiasOutPath)

###
### J Brooke additions
###

process.source.fileNames = cms.untracked.vstring(
    # test file
    'rfio:/castor/cern.ch/user/j/jbrooke/hscp/test/Calo_CRAFT09-GR09_31X_V5P_StoppedHSCP-332_v4_RAW-RECO_111039_test.root'

    # HLT reskim files on Bristol SE
#    '/store/user/jbrooke/Calo/StoppedHSCP_CRAFT09_rerunHLT_v3/a9f20537e9e1239e6910ee9cb81f358d/stoppedHSCP_rerunHLT_9.root'
)

process.GlobalTag.globaltag = 'CRAFT09_R_V10::All'

process.schedule = cms.Schedule(process.raw2digi_step,process.L1Reco_step,process.reconstruction_step,process.endjob_step,process.out_step)

process.source.inputCommands = cms.untracked.vstring(
    "drop *",
    "keep *_*_*_HLT",
    "drop *_MEtoEDMConverter_*_*",
#    "drop L1GlobalTriggerObjectMapRecord_hltL1GtObjectMap__HLT"
    )


process.FEVT.outputCommands = cms.untracked.vstring(
    process.FEVTEventContent.outputCommands
    )

process.FEVT.fileName = cms.untracked.string('StoppedHSCP_ReReco.root')
