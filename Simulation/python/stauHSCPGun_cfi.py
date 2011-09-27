
import FWCore.ParameterSet.Config as cms

rHadronGenerator = cms.EDProducer("Pythia6HSCPGun",
    readFromFile = cms.bool(False),
    stoppedData = cms.string(''),
    PGunParameters = cms.PSet(
        MinPhi = cms.double(-3.14159265359),
        ParticleID = cms.vint32(11),
        neutralinoMass = cms.double(500.0),
        MinEta = cms.double(-10),
        sparticleMass = cms.double(200.0),
        MaxEta = cms.double(10),
        MaxPhi = cms.double(3.14159265359),
        diJetGluino = cms.bool(False),
	decayTable = cms.string('src/stage2ParticlesTable.txt')
    ),
    pythiaPylistVerbosity = cms.untracked.int32(2),
    gluinoHadrons = cms.bool(False),
    stopHadrons = cms.bool(True),
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

