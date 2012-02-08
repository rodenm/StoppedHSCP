# Modify these variables to switch masses, input stopped points files, and flavor of RHadron
SPARTICLE_MASS=100
NEUTRALINO_MASS=75
OUTPUTFILE='stage2_GEN-HLT_stau' + str(SPARTICLE_MASS)+'_'+str(NEUTRALINO_MASS)+'.root'

import FWCore.ParameterSet.Config as cms

process = cms.Process('HLT')

# import of standard configurations
process.load('Configuration.StandardSequences.Services_cff')
process.load('SimGeneral.HepPDTESSource.pythiapdt_cfi')
process.load('FWCore.MessageService.MessageLogger_cfi')
process.load('Configuration.EventContent.EventContent_cff')
process.load('SimGeneral.MixingModule.mixNoPU_cfi')
process.load('Configuration.StandardSequences.GeometryDB_cff')
process.load('Configuration.StandardSequences.MagneticField_38T_cff')
process.load('Configuration.StandardSequences.Generator_cff')
process.load('GeneratorInterface.Core.genFilterSummary_cff')
process.load('Configuration.StandardSequences.SimIdeal_cff')
process.load('Configuration.StandardSequences.Digi_cff')
process.load('Configuration.StandardSequences.SimL1Emulator_cff')
process.load('Configuration.StandardSequences.DigiToRaw_cff')
process.load('HLTrigger.Configuration.HLT_GRun_cff')
process.load('Configuration.StandardSequences.RawToDigi_cff')
process.load('Configuration.StandardSequences.L1Reco_cff')
process.load('Configuration.StandardSequences.EndOfProcess_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(20)
)

process.options = cms.untracked.PSet(
	    SkipEvent = cms.untracked.vstring( 'g4SimHits','G4HadronicProcess' )
)

# Input source
process.source = cms.Source ("PoolSource",
			     fileNames=cms.untracked.vstring(
	'file:/home/rodenm/CMSSW_4_2_3_patch3/src/HSCPgluino_M-300_7TeV-pythia6_Summer11-START311_V2-v1_GEN-SIM_88B05CB6-3290-E011-93B2-00266CF2EB18.root',
	)
)

# Output definition
process.RAWSIMoutput = cms.OutputModule("PoolOutputModule",
#    outputCommands = cms.untracked.vstring('drop *_*_*_SIM',
#					   'keep *_*_Stopped*_SIM',
#					   'keep *_generator_*_SIM',
#					   'keep *_*_*_HLT'),
    splitLevel = cms.untracked.int32(0),
    eventAutoFlushCompressedSize = cms.untracked.int32(5242880),
    outputCommands = process.RAWSIMEventContent.outputCommands,
    fileName = cms.untracked.string(OUTPUTFILE),
    dataset = cms.untracked.PSet(
        filterName = cms.untracked.string(''),
        dataTier = cms.untracked.string('')
    ),
    SelectEvents = cms.untracked.PSet(
        SelectEvents = cms.vstring('filter_step')
    )
)

process.RAWSIMoutput.outputCommands.append('drop *_*_*_SIM')
process.RAWSIMoutput.outputCommands.append('keep *_*_Stopped*_SIM')
process.RAWSIMoutput.outputCommands.append('keep *_generator_*_SIM')

process.eventFilter = cms.EDFilter("MCStoppedEventFilter",
#				   StoppedParticlesXLabel = cms.InputTag("StoppedParticlesX")
)

# Additional output definition

# Other statements
process.GlobalTag.globaltag = 'MC_42_V12::All'

# Set parameters for the sparticle generation
process.load('StoppedHSCP/Simulation/stauHSCPGun_cfi')
process.generator.readFromFile = cms.untracked.bool(False)
process.generator.PGunParameters = cms.PSet(
	MinPhi = cms.double(-3.14159265359),
	ParticleID = cms.vint32(11),
	neutralinoMass = cms.double(NEUTRALINO_MASS),
	MinEta = cms.double(-10),
	sparticleMass = cms.double(SPARTICLE_MASS),
	MaxEta = cms.double(10),
	MaxPhi = cms.double(3.14159265359),
	diJetGluino = cms.bool(False),
	decayTable = cms.string('src/stage2ParticlesTable.txt')
	)

process.genParticles = cms.EDProducer("GenParticleProducer",
    saveBarCodes = cms.untracked.bool(True),
    src = cms.InputTag("generator"),
    abortOnUnknownPDGCode = cms.untracked.bool(False),
)

process.ProductionFilterSequence = cms.Sequence(process.generator)

# FR Extra stuff
process.load('StoppedHSCP/Simulation/StoppedParticleEvtVtxGenerator_cfi')
process.VtxSmeared.verbose = True

#Unknown particles is OK
process.genParticles.abortOnUnknownPDGCode = False

#Don't use shower library
process.g4SimHits.HCalSD.UseShowerLibrary = False
# FR END Extra stuff

# Path and EndPath definitions
process.filter_step = cms.Path(process.eventFilter)
process.generation_step = cms.Path(process.pgen)
process.simulation_step = cms.Path(process.psim)
process.digitisation_step = cms.Path(process.pdigi)
process.L1simulation_step = cms.Path(process.SimL1Emulator)
process.digi2raw_step = cms.Path(process.DigiToRaw)
process.raw2digi_step = cms.Path(process.RawToDigi)
process.L1Reco_step = cms.Path(process.L1Reco)
process.genfiltersummary_step = cms.EndPath(process.genFilterSummary)
process.endjob_step = cms.EndPath(process.endOfProcess)
process.RAWSIMoutput_step = cms.EndPath(process.RAWSIMoutput)

# Schedule definition
process.schedule = cms.Schedule(process.filter_step,process.generation_step,process.genfiltersummary_step,process.simulation_step,process.digitisation_step,process.L1simulation_step,process.digi2raw_step)
process.schedule.extend(process.HLTSchedule)
process.schedule.extend([process.raw2digi_step,process.L1Reco_step,process.endjob_step,process.RAWSIMoutput_step])
# filter all path with the production filter sequence
for path in process.paths:
	getattr(process,path)._seq = process.ProductionFilterSequence * getattr(process,path)._seq 

