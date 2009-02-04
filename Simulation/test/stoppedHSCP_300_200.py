
from StoppedHSCP.Simulation.stoppedHSCPSim import *

process.maxEvents.input = 1000
process.source.PythiaParameters.SLHAParameters = cms.vstring("SLHAFILE = \'StoppedHSCP/Simulation/data/Rhadron_1jet_300_200.dat\'")
process.VtxSmeared.stoppedData = cms.FileInPath('StoppedHSCP/Simulation/data/stopped_rhadrons_gluino300.txt')

