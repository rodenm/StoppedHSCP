#
# Custom pieces of Stopped HSCP simulation
#
# J Brooke, 15 Jan 2009

import FWCore.ParameterSet.Config as cms

from SimG4Core.CustomPhysics.CustomPhysics_cfi import *

source = cms.Source("PythiaSource",
    pythiaVerbosity = cms.untracked.bool(False),
    pythiaPylistVerbosity = cms.untracked.int32(0),
    pythiaHepMCVerbosity = cms.untracked.bool(False),
    maxEventsToPrint = cms.untracked.int32(1),
    gluinoHadrons = cms.untracked.bool(True),
    stopHadrons = cms.untracked.bool(False),
    ParticleID = cms.untracked.int32(1092224),
    DoubleParticle = cms.untracked.bool(False),
    Phimin = cms.untracked.double(-3.5),
    Phimax = cms.untracked.double(3.5),
    Etamin = cms.untracked.double(-6),
    Etamax = cms.untracked.double(6),
    Ptmin = cms.untracked.double(0.001),
    Ptmax = cms.untracked.double(0.001),                                                       
    PythiaParameters = cms.PSet(
        pythiaUESettings = cms.vstring('MSTJ(11)=3     ! Choice of the fragmentaemtion function', 
           'MSTJ(22)=2     ! Decay those unstable particles',
           'PARJ(71)=10 .  ! for which ctau  10 mm', 
           'MSTP(2)=1      ! which order running alphaS', 
           'MSTP(33)=0     ! no K factors in hard cross sections', 
           'MSTP(51)=7     ! structure function chosen', 
           'MSTP(81)=1     ! multiple parton interactions 1 is Pythia default', 
           'MSTP(82)=4     ! Defines the multi-parton model', 
           'MSTU(21)=1     ! Check on possible errors during program execution', 
           'PARP(82)=1.9409   ! pt cutoff for multiparton interactions', 
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
           'PARP(93)=15.0  ! '),
       processParameters = cms.vstring('MSEL=39',
           'IMSS(1) = 11',
           'IMSS(21) = 33',
           'IMSS(22) = 33'),        
       parameterSets=cms.vstring('pythiaUESettings','processParameters','SLHAParameters'),
       SLHAParameters = cms.vstring("SLHAFILE = \'StoppedHSCP/Simulation/data/Rhadron_1jet_300_50.dat\'"),
    )
)

VtxSmeared = cms.EDFilter("RHDecay",
    stoppedData = cms.FileInPath('StoppedHSCP/Simulation/data/stopped_rhadrons_gluino300.txt'),
    src = cms.InputTag("source"),
    timeOffsetMin = cms.double(-12.5),
    timeOffsetMax = cms.double(12.5),
    Silent = cms.untracked.bool(False),
    MakeCuts = cms.untracked.bool(True),
    MinRadius = cms.untracked.double(0),                              
    MaxRadius = cms.untracked.double(10000),
    MinZ = cms.untracked.double(-10000),
    MaxZ = cms.untracked.double(10000),
    MinPhi = cms.untracked.double(0),
    MaxPhi = cms.untracked.double(6.28),
    OperationMode = cms.untracked.int32(0),
    RDivs=cms.untracked.int32(200),
    ZDivs=cms.untracked.int32(200)
)
      
pgen = cms.Sequence( VtxSmeared )


# simulation
from Configuration.StandardSequences.Sim_cff import *

g4SimHits.Physics = cms.PSet(
    customPhysicsSetup,
    GFlashEmin = cms.double(1.0),
    G4BremsstrahlungThreshold = cms.double(0.5),
    DefaultCutValue = cms.double(.01),
    CutsPerRegion = cms.bool(True),
    Verbosity = cms.untracked.int32(0),
    GFlashEToKill = cms.double(0.1),
    GFlashEmax = cms.double(1000000.0),
    type = cms.string('SimG4Core/Physics/CustomPhysics'),
    DummyEMPhysics = cms.bool(True)
)

from SimG4Core.Application.hectorParameter_cfi import *

g4SimHits.Generator = cms.PSet(
       HectorEtaCut,
 # string HepMCProductLabel = "VtxSmeared"
       HepMCProductLabel = cms.string('source'),
       ApplyPCuts = cms.bool(False),
       MinPCut = cms.double(0.0001), ## the pt-cut is in GeV (CMS conventions)
       MaxPCut = cms.double(99999.0), ## the ptmax=99.TeV in this case
       ApplyEtaCuts = cms.bool(False),
       MinEtaCut = cms.double(-5.5),
       MaxEtaCut = cms.double(5.5),
       ApplyPhiCuts = cms.bool(False),
       MinPhiCut = cms.double(-3.14159265359), ## in radians
       MaxPhiCut = cms.double(3.14159265359), ## according to CMS conventions
       RDecLenCut = cms.double(0.01), ## the minimum decay length in cm (!) for mother tracking
       Verbosity = cms.untracked.int32(10)
)
