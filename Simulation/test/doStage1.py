import getopt, sys
import StoppedHSCP.Simulation.Helper as hscp
import StoppedHSCP.Simulation.ProductionSetup as setup

doc = """
    doStage1.py

    - Runs stage1 simulation for long living particles, traces stopping points, stores stopping points

    required parameters:
    flavor           :       gluino, stop, stau
    nevents          :       # of events to generate
    mass             :       particle mass

    optional parameters:
    stoppedPoints    :       file to store stopping points
    globalTag        :       global tag to be used
    randomize        :       randomize seeds, set run to given value
    """

flavor = None
nEvents = None
iMass = None
globalTag = 'STARTUP3X_V8M::All'
stopPointsFile = None
randomize = None

for (opt, value) in hscp.parseParams ():
    if opt == "flavor": flavor = value
    if opt == "nevents": nEvents = int (value)
    if opt == "mass": iMass = int (value)
    if opt == "stoppedPoints": stopPointsFile = value
    if opt == "globalTag": globalTag = value
    if opt == "randomize": randomize = int (value)

if not flavor or not nEvents or not iMass:
    print '======> Missing parameters! <======'
    print doc
    sys.exit(1)

# validate parameters
particlesFile = None
processList = None
if flavor == "gluino":
    gluinoMasses = [50, 200, 250, 300, 400, 500, 600, 900, 1200, 2000, 5000]
    if iMass not in gluinoMasses :
        print 'Wrong gluino mass. Only accepted are:', gluinoMasses
        sys.exit(1)
    particlesFile = 'StoppedHSCP/Simulation/data/particles_gluino_%s_GeV.txt' % iMass
    processList = 'SimG4Core/CustomPhysics/data/RhadronProcessList.txt'
elif flavor == "stau":
    stauMasses = [156, 247]
    if iMass not in stauMasses :
        print "Wrong stau mass. Only accepted are:", stauMasses
        sys.exit(1)
elif flavor == "stop":
    stopMasses = [100, 130, 200, 300, 500, 600, 800]
    if iMass not in stopMasses :
        print "Wrong stop mass. Only accepted are:", stopMasses
        sys.exit(1)
    particlesFile = 'SimG4Core/CustomPhysics/data/particles_stop_%s_GeV.txt' % iMass
    processList = 'SimG4Core/CustomPhysics/data/stophadronProcessList.txt'
else:
    print "Wrong flavor %s. Only accepted are gluino, stau, stop." % flavor 
    
if not stopPointsFile:
    stopPointsFile = 'stopped_rhadrons_%s_%s.txt' % (flavor, iMass)

firstRun = 1
if randomize: firstRun = randomize

print '**********************************************'
print 'Generating %s production and passing through the detector' % flavor
print 'Total events:', nEvents
print '%s mass:' % flavor, iMass
print 'Output stopping points file:', stopPointsFile
print 'Combined particles listing file:', particlesFile
print 'randomize job:', randomize
print '**********************************************'

import FWCore.ParameterSet.Config as cms

process = cms.Process('HLT')

# import of standard configurations
process.load('Configuration/StandardSequences/Services_cff')
process.load('FWCore/MessageService/MessageLogger_cfi')
process.MessageLogger.debugModules = ['g4SimHits']
process.MessageLogger.categories.append('CustomPhysics')
process.MessageLogger.cerr.threshold = 'DEBUG'
process.MessageLogger.cerr.DEBUG = cms.untracked.PSet( limit = cms.untracked.int32(0) )
process.MessageLogger.cerr.CustomPhysics = cms.untracked.PSet( limit = cms.untracked.int32(-1) )

process.load('Configuration/StandardSequences/MixingNoPileUp_cff')
process.load('Configuration/StandardSequences/GeometryIdeal_cff')
process.load('Configuration/StandardSequences/MagneticField_38T_cff')
process.load('Configuration/StandardSequences/Generator_cff')
process.load('Configuration/StandardSequences/VtxSmearedFlat_cff')
process.VtxSmeared.MinX = cms.double(0.)
process.VtxSmeared.MaxX = cms.double(0.)
process.VtxSmeared.MinY = cms.double(0.)
process.VtxSmeared.MaxY = cms.double(0.)
process.VtxSmeared.MinZ = cms.double(0.)
process.VtxSmeared.MaxZ = cms.double(0.)
process.VtxSmeared.TimeOffset = cms.double(0.)

process.load('Configuration/StandardSequences/Sim_cff')
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
process.source = cms.Source("EmptySource",
                            firstRun = cms.untracked.uint32(firstRun)
                            )

#smear random numbers if necessary
if randomize: hscp.randomize (process.RandomNumberGeneratorService)


# Other statements
process.GlobalTag.globaltag = globalTag

# Setup Generator
process.generator = setup.setupProduction (process,flavor, iMass, particlesFile) 



# Fine tuning
process.genParticles.abortOnUnknownPDGCode = False
process.g4SimHits.Watchers = cms.VPSet (
  cms.PSet(
    type = cms.string('RHStopTracer'),
    RHStopTracer = cms.PSet(
      stoppedFile = cms.untracked.string(stopPointsFile),
#      verbose = cms.untracked.bool (False),
      verbose = cms.untracked.bool (True),
      traceEnergy = cms.untracked.double (10000.),
      traceParticle = cms.string ("~.*")
    )        
  )
)

process.g4SimHits.HCalSD.UseShowerLibrary = False


process.g4SimHits.Physics.type = cms.string('SimG4Core/Physics/CustomPhysics')
process.g4SimHits.Physics.reggeSuppression = cms.double(0.0)

# Paths to files with particle and physics processes definition
process.g4SimHits.Physics.particlesDef = cms.FileInPath(particlesFile)
process.g4SimHits.Physics.resonanceEnergy = cms.double(200.0)

#        FileInPath particlesDef = "SimG4Core/CustomPhysics/data/isa-slha.out"
process.g4SimHits.Physics.processesDef = cms.FileInPath(processList)
process.g4SimHits.Physics.amplitude = cms.double(100.0)

# R-hadron physics setup
process.g4SimHits.Physics.resonant = cms.bool(False)
process.g4SimHits.Physics.gamma = cms.double(0.1)

process.ProductionFilterSequence = cms.Sequence(process.generator)

# Path and EndPath definitions
process.generation_step = cms.Path(process.pgen)
process.simulation_step = cms.Path(process.psim)
#process.endjob_step = cms.Path(process.endOfProcess)

# Schedule definition
process.schedule = cms.Schedule(process.generation_step,process.simulation_step)
#process.schedule.extend([process.endjob_step,process.out_step])
# special treatment in case of production filter sequence  
for path in process.paths: 
    getattr(process,path)._seq = process.ProductionFilterSequence*getattr(process,path)._seq

