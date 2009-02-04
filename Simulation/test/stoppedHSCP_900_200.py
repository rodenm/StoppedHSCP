
from JBrooke.StoppedHSCPSim.StoppedHSCPSimJob import *

process.maxEvents.input = 10000
process.source.PythiaParameters.SLHAParameters = cms.vstring("SLHAFILE = \'JBrooke/StoppedHSCPSim/data/Rhadron_1jet_900_200.dat\'")
process.VtxSmeared.stoppedData = cms.FileInPath('JBrooke/StoppedHSCPSim/data/stopped_rhadrons_gluino900.txt')

