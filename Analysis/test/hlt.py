# Auto generated configuration file
# using: 
# Revision: 1.99.2.3 
# Source: /cvs_server/repositories/CMSSW/CMSSW/Configuration/PyReleaseValidation/python/ConfigBuilder.py,v 
# with command line options: myreco -s RAW2DIGI,RECO -n 1 --conditions FrontierConditions_GlobalTag,CRAFT::All --no_exec --data --eventcontent=FEVTDEBUG
import FWCore.ParameterSet.Config as cms

process = cms.Process('HLT2')

# import of standard configurations
process.load('Configuration/StandardSequences/Services_cff')
process.load('FWCore/MessageService/MessageLogger_cfi')
process.load('Configuration/StandardSequences/MixingNoPileUp_cff')
process.load('Configuration/StandardSequences/GeometryPilot2_cff')
process.load('Configuration/StandardSequences/MagneticField_38T_cff')
process.load('Configuration/StandardSequences/EndOfProcess_cff')
process.load('Configuration/StandardSequences/Reconstruction_cff')
process.load('Configuration/StandardSequences/FrontierConditions_GlobalTag_cff')
process.load('Configuration/EventContent/EventContent_cff')

process.configurationMetadata = cms.untracked.PSet(
    version = cms.untracked.string('$Revision: 1.1 $'),
    annotation = cms.untracked.string('myreco nevts:1'),
    name = cms.untracked.string('PyReleaseValidation')
)
process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(-1)
)
process.options = cms.untracked.PSet(
    Rethrow = cms.untracked.vstring('ProductNotFound')
)

# Output definition
process.output = cms.OutputModule("PoolOutputModule",
#    EventContent.FEVT
    outputCommands = cms.untracked.vstring("keep *_hltL1extraParticles_*_*",
                                           "keep *_iterativeCone5CaloJets_*_*",
                                           "keep HLTPerformanceInfo_*_*_*"),            
    fileName = cms.untracked.string('hlt.root'),
    dataset = cms.untracked.PSet(
        dataTier = cms.untracked.string(''),
        filterName = cms.untracked.string('')
    )
)


# Other statements
process.GlobalTag.globaltag = 'CRAFT_V4P::All'

#
# HSCP L1 seed
process.load("L1TriggerConfig.L1GtConfigProducers.L1GtConfig_cff")
process.load("L1TriggerConfig.L1GtConfigProducers.Luminosity.startup.L1Menu_startup2_v2_Unprescaled_cff")

# Stopped HSCP HLT
process.load('StoppedHSCP/Analysis/StoppedHSCP_HLT_cff')
process.hcalDigis.InputLabel = 'source'

# timing modules
process.PathTimerService = cms.Service( "PathTimerService" )
process.timer = cms.EDProducer( "PathTimerInserter" )

process.end = cms.EndPath(process.timer + process.output)

# Schedule definition
process.schedule = cms.Schedule(process.hscpPath,process.end)

# Input source
process.source = cms.Source("PoolSource",
   fileNames = cms.untracked.vstring(
    'file:skim_L1SingleJet10.root'
    )
)

