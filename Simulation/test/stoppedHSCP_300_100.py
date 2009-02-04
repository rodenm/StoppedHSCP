
from JBrooke.StoppedHSCPSim.stoppedHSCPSim import *

process.maxEvents.input = 1000
process.source.PythiaParameters.SLHAParameters = cms.vstring("SLHAFILE = \'JBrooke/StoppedHSCPSim/data/Rhadron_1jet_300_100.dat\'")
process.VtxSmeared.stoppedData = cms.FileInPath('JBrooke/StoppedHSCPSim/data/stopped_rhadrons_gluino300.txt')

