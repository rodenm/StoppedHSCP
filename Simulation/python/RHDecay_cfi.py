import FWCore.ParameterSet.Config as cms

VtxSmeared = cms.EDFilter("RHDecay",
                          src = cms.InputTag("generator"),
                          stoppedData = cms.FileInPath ("stoppedPoints.txt"),
                          timeOffsetMin = cms.double (-5.), # offset by 7.5 ns to adjast trigger time "0" with senter of 25ns interval
                          timeOffsetMax = cms.double (20.), # --"--
                          verbose = cms.untracked.bool (False)
                          )