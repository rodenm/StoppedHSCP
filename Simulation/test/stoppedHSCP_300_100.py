
from StoppedHSCP.Simulation.stoppedHSCPSim import *

process.maxEvents.input = 10000
process.source.PythiaParameters.SLHAParameters = cms.vstring("SLHAFILE = \'StoppedHSCP/Simulation/data/Rhadron_1jet_300_100.dat\'")
process.VtxSmeared.stoppedData = cms.FileInPath('StoppedHSCP/Simulation/data/stopped_rhadrons_gluino300.txt')

