#! /usr/bin/env python

# create CRAB config file for an ntuple job


import sys
import getopt

def usage():
    print "makeRecoJob.py [-h] <era> <label> <dataset> <global tag> <runs>"
    print

try:
    opts, args = getopt.getopt(sys.argv[1:], "h")
except getopt.GetoptError:
    usage()
    sys.exit(2)

for opt, arg in opts:
    if opt=='-h':
        usage()
        sys.exit()

# arguments
if (len(args)!=5):
    usage()
    sys.exit()

era = args[0]
label = args[1]
dataset = args[2]
gtag = args[3]
runs = 0

# create CRAB variables
name = era + "_" + label
cfgname = "crab_rereco_"+name+".cfg"
jobStr = "stoppedHSCP_rereco_"+name+".py"
dirStr = "stoppedHSCP_rereco_"+name
evtPerJob = "10000"

dbsStr = ""
if (era=="CRAFT09"):
    dbsStr = "dbs_url=http://cmsdbsprod.cern.ch/cms_dbs_ph_analysis_02/servlet/DBSServlet"

runStr = ""
if (runs!="0"):
    runStr = "runselection="+runs

string = "[CRAB]\n\
jobtype = cmssw\n\
scheduler = glitecoll\n\
[CMSSW]\n\
datasetpath="+dataset+"\n\
"+runStr+"\n\
"+dbsStr+"\n\
pset="+jobStr+"\n\
total_number_of_events=-1\n\
events_per_job="+evtPerJob+"\n\
output_file = stoppedHSCP_rereco.root\n\
[USER]\n\
return_data = 0\n\
copy_data = 1\n\
storage_element = T2_UK_SGrid_RALPP\n\
user_remote_dir = "+dirStr+"\n\
ui_working_dir  = "+dirStr+"\n\
publish_data=1\n\
publish_data_name = StoppedHSCP_"+name+"\n\
dbs_url_for_publication = http://cmsdbsprod.cern.ch/cms_dbs_ph_analysis_02/servlet/DBSServlet

[GRID]\n\
rb = CERN\n\
proxy_server = myproxy.cern.ch\n\
#se_black_list = \n\
#se_white_list = \n\
#ce_black_list = \n\
ce_white_list = heplnx206.pp.rl.ac.uk,heplnx207.pp.rl.ac.uk\n\
#ce_white_list = lcgce03.phy.bris.ac.uk, lcgce02.phy.bris.ac.uk, lcgce01.phy.bris.ac.uk\n"

# create CRAB file
crab = open(cfgname, 'w')
crab.write(string)
crab.close()

# create CMSSW variables
cmsswStr = "\n\
import FWCore.ParameterSet.Config as cms\n\
from StoppedHSCP.Analysis.rereco_"+label+" import *\n\

process.load('StoppedHSCP.Analysis.rereco_"+label+"')\n\
\n\
process.source.fileNames = cms.untracked.vstring(\n\
    # test file\n\
    'rfio:/castor/cern.ch/user/j/jbrooke/hscp/test/Calo_CRAFT09-GR09_31X_V5P_StoppedHSCP-332_v4_RAW-RECO_111039_test.root'\n\
    # HLT reskim files on Bristol SE\n\
#    '/store/user/jbrooke/Calo/StoppedHSCP_CRAFT09_rerunHLT_v3/a9f20537e9e1239e6910ee9cb81f358d/stoppedHSCP_rerunHLT_9.root'\n\
)\n\
\n\
process.GlobalTag.globaltag = '"+gtag+"'\n\
\n\
process.schedule = cms.Schedule(process.raw2digi_step,process.L1Reco_step,process.reconstruction_step,process.endjob_step,process.out_step)\n\
\n\
process.source.inputCommands = cms.untracked.vstring(\n\
    'drop *',\n\
    'keep *_*_*_HLT',\n\
    'drop *_MEtoEDMConverter_*_*')\n\
\n\
process.output.outputCommands = cms.untracked.vstring(\n\
    process.FEVTEventContent.outputCommands\n\
)\n\
\n\
process.output.fileName = cms.untracked.string('stoppedHSCP_rereco.root')\n\
"

# create CMSSW config
cmssw = open(jobStr, 'w')
cmssw.write(cmsswStr)
cmssw.close()
