
from JBrooke.StoppedHSCPSim.stoppedHSCPSim import *

process.maxEvents.input = 10000
process.source.PythiaParameters.SLHAParameters = cms.vstring("SLHAFILE = \'JBrooke/StoppedHSCPSim/data/Rhadron_1jet_500_100.dat\'")
process.VtxSmeared.stoppedData = cms.FileInPath('JBrooke/StoppedHSCPSim/data/stopped_rhadrons_gluino500.txt')

