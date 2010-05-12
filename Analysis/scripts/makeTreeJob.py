#!/ /usr/bin/env python

# create CRAB config file for an ntuple job


import sys
import getopt

def usage():
    print "makeTreeJob.py [-h] [-l] <era> <label> <dataset> <global tag> <runs>"
    print " Options   :"
    print "   -h      : print this message"
    print "   -l      : use local DBS"
    print "   -j      : use JSON file of good LS"
    print

try:
    opts, args = getopt.getopt(sys.argv[1:], "hl")
except getopt.GetoptError:
    usage()
    sys.exit(2)

useLocalDBS = False;
useJSON = False;

for opt, arg in opts:
    if opt=='-l':
        useLocalDBS=True
    if opt=='-j':
        useJSON = True;
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
runs = args[4]
    

# create CRAB variables
name = era + "_" + label
cfgname = "crab_tree_"+name+".cfg"
jobStr = "stoppedHSCP_tree_"+name+".py"
dirStr = "stoppedHSCP_tree_"+name

dbsStr = ""
if (useLocalDBS):
    dbsStr = "dbs_url=http://cmsdbsprod.cern.ch/cms_dbs_ph_analysis_02/servlet/DBSServlet"

runStr = ""
if (runs!="0"):
    runStr = "runselection="+runs

evtStr = ""
if (useJSON):
    evtStr = "lumi_mask=jsonls.txt\n\
    total_number_of_lumis = 100000\n\
    lumis_per_job = 500\n"
else :
    evtStr = "total_number_of_events=-1\n\
    events_per_job=100000\n"

string = "[CRAB]\n\
jobtype = cmssw\n\
scheduler = glite\n\
use_server = 1\n\
[CMSSW]\n\
pset="+jobStr+"\n\
output_file = stoppedHSCPTree.root\n\
datasetpath="+dataset+"\n\
"+runStr+"\n\
"+dbsStr+"\n\
"+evtStr+"\n\
[USER]\n\
return_data = 0\n\
copy_data = 1\n\
storage_element = T2_UK_SGrid_RALPP\n\
user_remote_dir = "+dirStr+"\n\
ui_working_dir  = "+dirStr+"\n\
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
cmsswStr="import FWCore.ParameterSet.Config as cms\n\
\n\
from StoppedHSCP.Analysis.stoppedHSCPTree_cfg import *\n\
\n\
process.MessageLogger.cerr.threshold = ''\n\
process.MessageLogger.cerr.FwkReport.reportEvery = 1000\n\
process.GlobalTag.globaltag = '"+gtag+"'\n\
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(1000) )\n\
readFiles.extend( [\n\
] )\n\
"

# create CMSSW config
cmssw =open(jobStr, 'w')
cmssw.write(cmsswStr)
cmssw.close()
