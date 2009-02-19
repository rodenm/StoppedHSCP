nEvents = 2
gluinoMass = 300
neutralinoMass = 100
stoppedPoints = 'stoppoints/stopped_rhadrons_gluino%s.txt' % gluinoMass
decayFile = 'Rhadron_1jet_%s_%s.dat' % (gluinoMass, neutralinoMass)
outputFile = 'decaySimReco_1jet_%s_%s.root' % (gluinoMass, neutralinoMass)


import FWCore.ParameterSet.Config as cms

process = cms.Process('RECO')

# import of standard configurations
process.load('Configuration/StandardSequences/Services_cff')
process.load('FWCore/MessageService/MessageLogger_cfi')
process.load('Configuration/StandardSequences/MixingNoPileUp_cff')
process.load('Configuration/StandardSequences/GeometryPilot2_cff')
process.load('Configuration/StandardSequences/MagneticField_38T_cff')
process.load('Configuration/StandardSequences/Generator_cff')
#process.load('Configuration/StandardSequences/VtxSmearedEarly10TeVCollision_cff')
process.load('Configuration/StandardSequences/Sim_cff')
process.load('Configuration/StandardSequences/Digi_cff')
process.load('Configuration/StandardSequences/Reconstruction_cff')
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
process.source = cms.Source("PythiaSource",
                        ParticleID = cms.untracked.int32(1092224),
                        DoubleParticle = cms.untracked.bool(False),
                        Etamin = cms.untracked.double(0.),
                        Etamax = cms.untracked.double(0.),
                        Phimin = cms.untracked.double(0.),
                        Phimax = cms.untracked.double(0.),
                        Ptmin = cms.untracked.double(0.001),
                        Ptmax = cms.untracked.double(0.001),
                            
    pythiaPylistVerbosity = cms.untracked.int32(2),
    filterEfficiency = cms.untracked.double(1.0),
    pythiaHepMCVerbosity = cms.untracked.bool(False),
    comEnergy = cms.untracked.double(10000.0),
    maxEventsToPrint = cms.untracked.int32(1),
    gluinoHadrons =  cms.untracked.bool(True),            
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

# Get vertex from the file
process.VtxSmeared = cms.EDProducer("RHDecay",
  src = cms.InputTag("source"),
  stoppedData = cms.string(stoppedPoints),
  timeOffsetMin = cms.double (0.),
  timeOffsetMax = cms.double (0.)
)

#Unknown particles is OK
process.genParticles.abortOnUnknownPDGCode = False

#Don't use shower library
process.g4SimHits.HCalSD.UseShowerLibrary = False

# Output definition
process.output = cms.OutputModule("PoolOutputModule",
    outputCommands = process.FEVTEventContent.outputCommands,
    fileName = cms.untracked.string(outputFile),
    dataset = cms.untracked.PSet(
        dataTier = cms.untracked.string('GEN-SIM-DIGI-RECO'),
        filterName = cms.untracked.string('')
    ),
    SelectEvents = cms.untracked.PSet(
        SelectEvents = cms.vstring('generation_step')
    )
)

# Additional output definition

# Other statements
process.GlobalTag.globaltag = 'IDEAL_V11::All'

process.Tracer = cms.Service("Tracer")

# Path and EndPath definitions
process.generation_step = cms.Path(process.pgen)
process.simulation_step = cms.Path(process.psim)
process.digitisation_step = cms.Path(process.pdigi)
process.reconstruction_step = cms.Path(process.reconstruction)

hscp_calo_reconstruction = cms.Sequence (process.calolocalreco*process.caloTowersRec*process.vertexreco*process.recoJets)
process.hscp_calo_step = cms.Path(hscp_calo_reconstruction)
                                      
process.endjob_step = cms.Path(process.endOfProcess)
process.out_step = cms.EndPath(process.output)

# Schedule definition
#process.schedule = cms.Schedule(process.generation_step,process.simulation_step,process.digitisation_step,process.reconstruction_step,process.endjob_step,process.out_step)
process.schedule = cms.Schedule(process.generation_step,process.simulation_step,process.digitisation_step,process.hscp_calo_step,process.endjob_step,process.out_step)
#process.schedule = cms.Schedule(process.generation_step)
