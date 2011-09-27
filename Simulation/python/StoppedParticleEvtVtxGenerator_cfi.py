import FWCore.ParameterSet.Config as cms

VtxSmeared = cms.EDProducer("StoppedParticleEvtVtxGenerator",
                            src = cms.InputTag("generator"),
                            readFromFile = cms.untracked.bool(False),
                            stoppedData = cms.string (""),
                            timeOffsetMin = cms.double (-5.), # offset by 7.5 ns to adjast trigger time "0" with senter of 25ns interval
                            timeOffsetMax = cms.double (20.), # --"--
                            verbose = cms.untracked.bool (False)
)
