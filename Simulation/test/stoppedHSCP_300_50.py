
from JBrooke.StoppedHSCPSim.stoppedHSCPSim import *

process.maxEvents.input = 10
process.source.PythiaParameters.SLHAParameters = cms.vstring("SLHAFILE = \'JBrooke/StoppedHSCPSim/data/Rhadron_1jet_300_50.dat\'")
process.VtxSmeared.stoppedData = cms.FileInPath('JBrooke/StoppedHSCPSim/data/stopped_rhadrons_gluino300.txt')

