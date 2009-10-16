import sys

hadronId = 1092224

if len(sys.argv) < 6:
    print '======> Missing parameters! <======'
    print '======> Use:', sys.argv[0], sys.argv[1], '<# events> <gluino mass> <neutralino mass> <output file> [stop points] [R-hadron decay description]'
    sys.exit(-1)
nEvents = int (sys.argv[2])
iGluinoMass = int (sys.argv[3])
gluinoMass = float (iGluinoMass)
iNeutralinoMass = int (sys.argv[4])
neutralinoMass = float (iNeutralinoMass)
outputFile = sys.argv[5]
stopPointsFile = 'StoppedHSCP/Simulation/data/stopped_rhadrons_gluino%s.txt' % iGluinoMass
decayFile = 'StoppedHSCP/Simulation/data/Rhadron_1jet_%s_%s.dat' % (iGluinoMass, iNeutralinoMass)
if len(sys.argv) >= 7: stopPointsFile = sys.argv[6]
if len(sys.argv) >= 8: decayFile = sys.argv[7]

print '**********************************************'
print 'Generating stopped R-hadrons decays'
print 'R-hadron:', hadronId
print 'Total events:', nEvents
print 'Output file:', outputFile 
print 'Gluino mass:', gluinoMass
print 'Neutralinoino mass:', neutralinoMass
print 'Stopped points:', stopPointsFile
print 'Decay description file:', decayFile
print '**********************************************'


# Auto generated configuration file
# using: 
# Revision: 1.123 
# Source: /cvs_server/repositories/CMSSW/CMSSW/Configuration/PyReleaseValidation/python/ConfigBuilder.py,v 
# with command line options: Configuration/Generator/python/SingleMuPt1000_cfi.py -s GEN,SIM,DIGI,L1,DIGI2RAW,HLT --conditions FrontierConditions_GlobalTag,MC_31X_V5::All --datatier GEN-SIM-RAW --eventcontent RAWSIM -n 10 --no_exec
import FWCore.ParameterSet.Config as cms

process = cms.Process('HLT')

# import of standard configurations
process.load('Configuration/StandardSequences/Services_cff')
process.load('FWCore/MessageService/MessageLogger_cfi')
process.load('Configuration/StandardSequences/MixingNoPileUp_cff')
process.load('Configuration/StandardSequences/GeometryIdeal_cff')
process.load('Configuration/StandardSequences/MagneticField_38T_cff')
process.load('Configuration/StandardSequences/Generator_cff')
#process.load('Configuration/StandardSequences/VtxSmearedFlat_cff')
process.load('Configuration/StandardSequences/Sim_cff')
process.load('Configuration/StandardSequences/Digi_cff')
process.load('Configuration/StandardSequences/SimL1Emulator_cff')
process.load('Configuration/StandardSequences/DigiToRaw_cff')
process.load('HLTrigger/Configuration/HLT_1E31_cff')
process.load('Configuration/StandardSequences/EndOfProcess_cff')
process.load('Configuration/StandardSequences/FrontierConditions_GlobalTag_cff')
process.load('Configuration/EventContent/EventContent_cff')

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(nEvents)
)
process.options = cms.untracked.PSet(
    Rethrow = cms.untracked.vstring('ProductNotFound')
)
# Input source
process.source = cms.Source("EmptySource")

# Output definition
process.output = cms.OutputModule("PoolOutputModule",
    splitLevel = cms.untracked.int32(0),
    outputCommands = process.RAWSIMEventContent.outputCommands,
    fileName = cms.untracked.string(outputFile),
    dataset = cms.untracked.PSet(
        dataTier = cms.untracked.string('GEN-SIM-RAW'),
        filterName = cms.untracked.string('')
    ),
    SelectEvents = cms.untracked.PSet(
        SelectEvents = cms.vstring('generation_step')
    )
)

# Additional output definition

# Other statements
process.GlobalTag.globaltag = 'MC_31X_V5::All'


process.generator = cms.EDProducer("Pythia6PtGun",
                                   pythiaPylistVerbosity = cms.untracked.int32(2),
                                   pythiaHepMCVerbosity = cms.untracked.bool(False),
                                   maxEventsToPrint = cms.untracked.int32(1),
                                   
                                   PGunParameters = cms.PSet(
    ParticleID = cms.vint32(hadronId),
    AddAntiParticle = cms.bool(False),
    MinPhi = cms.double(-3.14159265359),
    MaxPhi = cms.double(3.14159265359),
    MinPt = cms.double(0.001),
    MaxPt = cms.double(0.001),
    MinEta = cms.double(-10),
    MaxEta = cms.double(10)
    ),
                            
                                   PythiaParameters = cms.PSet(
    pythiaUESettings = cms.vstring('MSTJ(11)=3     ! Choice of the fragmentation function', 
                                   'MSTJ(22)=2     ! Decay those unstable particles', 
                                   'PARJ(71)=10 .  ! for which ctau  10 mm', 
                                   'MSTP(2)=1      ! which order running alphaS', 
                                   'MSTP(33)=0     ! no K factors in hard cross sections', 
                                   'MSTP(51)=10042 ! structure function chosen (external PDF CTEQ6L1)', 
                                   'MSTP(52)=2     ! work with LHAPDF', 
                                   'MSTP(81)=1     ! multiple parton interactions 1 is Pythia default', 
                                   'MSTP(82)=4     ! Defines the multi-parton model', 
                                   'MSTU(21)=1     ! Check on possible errors during program execution', 
                                   'PARP(82)=1.8387   ! pt cutoff for multiparton interactions', 
                                   'PARP(89)=1960. ! sqrts for which PARP82 is set', 
                                   'PARP(83)=0.5   ! Multiple interactions: matter distrbn parameter', 
                                   'PARP(84)=0.4   ! Multiple interactions: matter distribution parameter', 
                                   'PARP(90)=0.16  ! Multiple interactions: rescaling power', 
                                   'PARP(67)=2.5    ! amount of initial-state radiation', 
                                   'PARP(85)=1.0  ! gluon prod. mechanism in MI', 
                                   'PARP(86)=1.0  ! gluon prod. mechanism in MI', 
                                   'PARP(62)=1.25   ! ', 
                                   'PARP(64)=0.2    ! ', 
                                   'MSTP(91)=1      !', 
                                   'PARP(91)=2.1   ! kt distribution', 
                                   'PARP(93)=15.0  ! '),
    processParameters = cms.vstring(
    'IMSS(1)=11          ! User defined processes',
    'IMSS(21) = 33       ! LUN number for SLHA File (must be 33) ',
    'IMSS(22) = 33       ! Read-in SLHA decay table '
    ),
    SLHAParameters = cms.vstring('SLHAFILE=%s' % decayFile),
    parameterSets = cms.vstring(
    'pythiaUESettings',
    'processParameters',
    'SLHAParameters')
    )
                                   )

process.load('StoppedHSCP/Simulation/RHDecay_cfi')
process.VtxSmeared.stoppedData = stopPointsFile
process.VtxSmeared.verbose = True

#Unknown particles is OK
process.genParticles.abortOnUnknownPDGCode = False

#Don't use shower library
process.g4SimHits.HCalSD.UseShowerLibrary = False

process.ProductionFilterSequence = cms.Sequence(process.generator)

# Path and EndPath definitions
process.generation_step = cms.Path(process.pgen)
process.simulation_step = cms.Path(process.psim)
process.digitisation_step = cms.Path(process.pdigi)
process.L1simulation_step = cms.Path(process.SimL1Emulator)
process.digi2raw_step = cms.Path(process.DigiToRaw)
process.endjob_step = cms.Path(process.endOfProcess)
process.out_step = cms.EndPath(process.output)

# Schedule definition
process.schedule = cms.Schedule(process.generation_step,process.simulation_step,process.digitisation_step,process.L1simulation_step,process.digi2raw_step)
process.schedule.extend(process.HLTSchedule)
process.schedule.extend([process.endjob_step,process.out_step])
# special treatment in case of production filter sequence  
for path in process.paths: 
    getattr(process,path)._seq = process.ProductionFilterSequence*getattr(process,path)._seq
