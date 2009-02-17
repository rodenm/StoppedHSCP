
from StoppedHSCP.Simulation.stoppedHSCPSim import *

process.maxEvents.input = 10000
process.source.PythiaParameters.SLHAParameters = cms.vstring("SLHAFILE = \'StoppedHSCP/Simulation/data/Rhadron_1jet_900_200.dat\'")
process.VtxSmeared.stoppedData = cms.FileInPath('StoppedHSCP/Simulation/data/stopped_rhadrons_gluino900.txt')

