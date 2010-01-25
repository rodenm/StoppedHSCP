#
#  produce stopped HSCP TTree
#  assumes RAW, HLT, RECO data present
#  Run this on StoppedHSCP Skim
#

from test.stoppedHSCPTree import *

# change Global Tag
#process.GlobalTag.globaltag = "STARTUP3X_V8I::All" # MC
process.GlobalTag.globaltag = "GR09_R_V5::All"  # collisions reprocessing
#process.GlobalTag.globaltag = "GR09_31X_V5P::All"  # CRAFT 09
#process.GlobalTag.globaltag = "CRAFT08_R_V1::All"  # CRAFT 08

# input files
readFiles.extend( [
    'file:/storage/phjjb/StoppedHSCP_MC_336/gluino_336_300_100.root'
    ] )

