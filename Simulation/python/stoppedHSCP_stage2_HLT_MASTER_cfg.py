# Modify these variables to switch masses, input stopped points files, and flavor of RHadron
STOPPED_POINTS_FILE='stoppedPoint_gluino500.txt'
SPARTICLE_MASS=500
NEUTRALINO_MASS=100
FLAVOR = 'gluino'
IS_GLUINO = True
IS_STOP = False
OUTPUTFILE='Stopped_HSCP_stage2_sim_' + FLAVOR + str(SPARTICLE_MASS)+'_'+str(NEUTRALINO_MASS)+'.root'

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

# Input source
process.source = cms.Source("EmptySource")
process.options = cms.untracked.PSet()

# Output definition
process.RAWSIMoutput = cms.OutputModule("PoolOutputModule",
    splitLevel = cms.untracked.int32(0),
    eventAutoFlushCompressedSize = cms.untracked.int32(5242880),
    outputCommands = process.RAWSIMEventContent.outputCommands,
    fileName = cms.untracked.string(OUTPUTFILE),
    dataset = cms.untracked.PSet(
        filterName = cms.untracked.string(''),
        dataTier = cms.untracked.string('')
    ),
    SelectEvents = cms.untracked.PSet(
        SelectEvents = cms.vstring('generation_step')
    )
)

# Additional output definition

# Other statements
process.GlobalTag.globaltag = 'MC_42_V12::All'

process.generator = cms.EDProducer("Pythia6HSCPGun",
    PGunParameters = cms.PSet(
        MinPhi = cms.double(-3.14159265359),
        ParticleID = cms.vint32(11),
        stoppedData = cms.string(STOPPED_POINTS_FILE),
        neutralinoMass = cms.double(NEUTRALINO_MASS),
        MinEta = cms.double(-10),
        sparticleMass = cms.double(SPARTICLE_MASS),
        MaxEta = cms.double(10),
        MaxPhi = cms.double(3.14159265359),
        diJetGluino = cms.bool(False),
	decayTable = cms.string('src/stage2ParticlesTable.txt')
    ),
    pythiaPylistVerbosity = cms.untracked.int32(2),
    gluinoHadrons = cms.bool(IS_GLUINO),
    stopHadrons = cms.bool(IS_STOP),
    pythiaHepMCVerbosity = cms.untracked.bool(False),
    maxEventsToPrint = cms.untracked.int32(1),
    PythiaParameters = cms.PSet(
        processParameters = cms.vstring('IMSS(1)=11          ! User defined processes', 
            'IMSS(21) = 33       ! LUN number for SLHA File (must be 33) ', 
            'IMSS(22) = 33       ! Read-in SLHA decay table '),
        parameterSets = cms.vstring('processParameters', 
            'SLHAParameters'),
        SLHAParameters = cms.vstring('SLHAFILE=stage2ParticlesTable.txt')
    )
)


process.genParticles = cms.EDProducer("GenParticleProducer",
    saveBarCodes = cms.untracked.bool(True),
    src = cms.InputTag("generator"),
    abortOnUnknownPDGCode = cms.untracked.bool(False)
)


process.ProductionFilterSequence = cms.Sequence(process.generator)

# FR Extra stuff
process.load('StoppedHSCP/Simulation/RHDecay_cfi')
process.VtxSmeared.stoppedData = STOPPED_POINTS_FILE
process.VtxSmeared.verbose = True

#Unknown particles is OK
process.genParticles.abortOnUnknownPDGCode = False

#Don't use shower library
process.g4SimHits.HCalSD.UseShowerLibrary = False
# FR END Extra stuff

# Path and EndPath definitions
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
process.schedule = cms.Schedule(process.generation_step,process.genfiltersummary_step,process.simulation_step,process.digitisation_step,process.L1simulation_step,process.digi2raw_step)
process.schedule.extend(process.HLTSchedule)
process.schedule.extend([process.raw2digi_step,process.L1Reco_step,process.endjob_step,process.RAWSIMoutput_step])
# filter all path with the production filter sequence
for path in process.paths:
	getattr(process,path)._seq = process.ProductionFilterSequence * getattr(process,path)._seq 

