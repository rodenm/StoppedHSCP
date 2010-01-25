#
#  produce stopped HSCP TTree
#  assumes RAW, HLT, RECO data present
#  Run this on StoppedHSCP Skim
#

from test.stoppedHSCPTree import *

# change Global Tag
process.GlobalTag.globaltag = "STARTUP3X_V8I::All" # MC

# things missing from RECO
process.load('Configuration/StandardSequences/RawToDigi_cff')

# input files
readFiles.extend( [
    'file:/storage/phjjb/StoppedHSCP_MC_336/gluino_336_300_100.root'
    ] )

