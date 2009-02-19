import FWCore.ParameterSet.Config as cms

gluinoMass = 1200.
particlesGluinoFile = 'particles_gluino_1200_GeV.txt'
stopPointsFile = 'stopped_rhadrons_gluino1200.txt'
nEvents = 10000

process = cms.Process('GEN')

# import of standard configurations
process.load('Configuration/StandardSequences/Services_cff')
process.load('FWCore/MessageService/MessageLogger_cfi')
process.load('Configuration/StandardSequences/Generator_cff')
process.load('Configuration/StandardSequences/MixingNoPileUp_cff')
process.load('Configuration/StandardSequences/GeometryPilot2_cff')
process.load('Configuration/StandardSequences/MagneticField_cff')
process.load('Configuration/StandardSequences/Generator_cff')
process.load('Configuration/StandardSequences/VtxSmearedEarly10TeVCollision_cff')
process.load('Configuration/StandardSequences/VtxSmearedGauss_cff')
process.load('Configuration/StandardSequences/Sim_cff')
process.load('SimG4Core/CustomPhysics/CustomPhysics_cfi')
process.load('Configuration/StandardSequences/FrontierConditions_GlobalTag_cff')
process.load('Configuration/EventContent/EventContent_cff')

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(nEvents)
)
process.options = cms.untracked.PSet(
    Rethrow = cms.untracked.vstring('ProductNotFound')
)


#process.MessageLogger = cms.Service("MessageLogger",
#     cout = cms.untracked.PSet(
#         default = cms.untracked.PSet(
#             limit = cms.untracked.int32(0)
#         ),
#         G4cout = cms.untracked.PSet(
#             limit = cms.untracked.int32(-1)
#         ),
#         G4cerr = cms.untracked.PSet(
#             limit = cms.untracked.int32(-1)
#         ),
#         CustomPhysics = cms.untracked.PSet(
#             limit = cms.untracked.int32(-1)
#         )
#     ),
#     categories = cms.untracked.vstring('G4cout', 
#         'G4cerr', 'CustomPhysics'),
#     destinations = cms.untracked.vstring('cout')
#)

# Input source
process.source = cms.Source("PythiaSource",
                            pythiaPylistVerbosity = cms.untracked.int32(2),
                            filterEfficiency = cms.untracked.double(0.701),
                            pythiaHepMCVerbosity = cms.untracked.bool(True),
                            comEnergy = cms.untracked.double(10000.0),
                            crossSection = cms.untracked.double(1232),
                            maxEventsToPrint = cms.untracked.int32(2),
                            gluinoHadrons =  cms.untracked.bool(True),  

                            PythiaParameters = cms.PSet(
    pythiaUESettings = cms.vstring(
    'MSTJ(11)=3     ! Choice of the fragmentation function', 
    'MSTJ(22)=2     ! Decay those unstable particles', 
    'PARJ(71)=10 .  ! for which ctau  10 mm', 
    'MSTP(2)=1      ! which order running alphaS', 
    'MSTP(33)=0     ! no K factors in hard cross sections', 
    'MSTP(51)=10042     ! CTEQ6L1 structure function chosen', 
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
    'MSTP(91)=1     !', 
    'PARP(91)=2.1   ! kt distribution', 
    'PARP(93)=15.0  ! '
    ),
    processParameters = cms.vstring(
    'MSEL=0          ! User defined processes',
    #        'MSTP(51)=7      ! CTEQ5L structure function',
    'IMSS(1)=1       !  brute force',
    'MSUB(243)=1     !  subprocess',
    'MSUB(244)=1     !  subprocess',
    
#    'IMSS(1)=12       !  SUGRA',
#    'RMSS(1)=150  ! m_1/2 (~M_~g/2.7)',
#    'RMSS(5)=10   ! tg_beta',
#    'RMSS(8)=1000 ! m_0',
#    'RMSS(16)=0   ! A_0',
    
    'IMSS(3)=1',
    'RMSS(1)=%f !should be gluino mass/2' % (gluinoMass/2.),
    'RMSS(2)=%f !should be gluino mass/2' % (gluinoMass/2.),
    'RMSS(3)=%f !should be gluino mass' % gluinoMass,
    'RMSS(10)=%f !RMSS(10)=2.2*mass gluino' % (gluinoMass*2.2),
    'RMSS(11)=%f !RMSS(10)=2.1*mass gluino' % (gluinoMass*2.1),
    'RMSS(12)=%f !should be gluino mass X2' % (gluinoMass*2.),
##    'RMSS(4)=10000.',
    
    'MDCY(309,1)=0                   ! set gluino stable',
    'IMSS(5)=1',
#    'IMSS(21)=33  !read SLHAFILE from LUN33',
#    'IMSS(23)=32  !write SLHA data',
    'MSTJ(14)=-1',
    'MSTP(111)=0 ! no hadronization'
    ),
    parameterSets = cms.vstring(
    'pythiaUESettings', 
    'processParameters',
    'SLHAParameters'
    ),
    SLHAParameters = cms.vstring('SLHAFILE = %s' % particlesGluinoFile)
    
    )
                            )

# Output definition
process.output = cms.OutputModule("PoolOutputModule",
    outputCommands = process.RAWSIMEventContent.outputCommands,
    fileName = cms.untracked.string('rHadron_GEN_SIM_test_evt1.root'),
    dataset = cms.untracked.PSet(
        dataTier = cms.untracked.string('GEN'),
        filterName = cms.untracked.string('')
    ),
    SelectEvents = cms.untracked.PSet(
        SelectEvents = cms.vstring('generation_step')
    )
)

# Fine tuning
process.genParticles.abortOnUnknownPDGCode = False
process.g4SimHits.Watchers = cms.VPSet (
  cms.PSet(
    type = cms.string('RHStopTracer'),
    RHStopTracer = cms.PSet(
      stoppedFile = cms.untracked.string(stopPointsFile),
      verbose = cms.untracked.bool (False),
      traceEnergy = cms.untracked.double (10000.)
    )        
  )
)

process.g4SimHits.HCalSD.UseShowerLibrary = False


process.g4SimHits.Physics.type = cms.string('SimG4Core/Physics/CustomPhysics')
process.g4SimHits.Physics.reggeSuppression = cms.double(0.0)

# Paths to files with particle and physics processes definition
process.g4SimHits.Physics.particlesDef = cms.FileInPath(particlesGluinoFile)
process.g4SimHits.Physics.resonanceEnergy = cms.double(200.0)

#        FileInPath particlesDef = "SimG4Core/CustomPhysics/data/isa-slha.out"
process.g4SimHits.Physics.processesDef = cms.FileInPath('SimG4Core/CustomPhysics/data/RhadronProcessList.txt')
process.g4SimHits.Physics.amplitude = cms.double(100.0)

# R-hadron physics setup
process.g4SimHits.Physics.resonant = cms.bool(False)
process.g4SimHits.Physics.gamma = cms.double(0.1)

# Other statements
process.GlobalTag.globaltag = 'STARTUP_V5::All'

# Path and EndPath definitions
process.generation_step = cms.Path(process.pgen)
process.simulation_step = cms.Path(process.psim)
process.out_step = cms.EndPath(process.output)

# Schedule definition
#process.schedule = cms.Schedule(process.generation_step,process.simulation_step,process.out_step)
process.schedule = cms.Schedule(process.generation_step,process.simulation_step)

