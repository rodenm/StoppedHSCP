#!/usr/bin/env python

# create CRAB config file for an ntuple job


import sys
import getopt

def usage():
    print "makeTreeJob.py [-hjlc] [--raw|--reco|--mc] [--2010|--2011] [--newhlttag] [--oldhlttag] <era> <label> <dataset> <global tag> <runlist|JSON file>"
    print " Options   :"
    print "   -h      : prints this message"
    print "   -l      : use local DBS (http://cmsdbsprod.cern.ch/cms_dbs_ph_analysis_02/servlet/DBSServlet)"
    print "   -j      : use JSON file to run on good LS"
    print "   -c      : use CAF"
    print "   --2010  : use 2010 trigger config"
    print "   --2011  : use 2011 trigger config (default)"
    print "   --raw   : use RAW+RECO config"
    print "   --reco  : use RECO config (default)"
    print "   --mc    : use MC config"
    print "   --newhlttag  :  use HLTL3Tag hltStoppedHSCPCaloJetEnergy50 "
    print "   --oldhlttag : use HLTL3Tag hltStoppedHSCPTight1CaloJetEnergy30"
    print

try:
    opts, args = getopt.getopt(sys.argv[1:], "hjlcm", ['2010','2011','raw','reco','mc','oldhlttag','newhlttag'])
except getopt.GetoptError:
    usage()
    sys.exit(2)

useLocalDBS = False
useJSON = False
useCAF = False
trigger = '2011'
datatype = 'RECO'
HLTL3Tag = "Default"

for opt, arg in opts:
    if opt=='-l':
        useLocalDBS=True
    if opt=='-j':
        useJSON = True
    if opt=='-c':
        useCAF = True
    if opt=='-h':
        usage()
        sys.exit()
    if opt=='--2010':
        trigger = '2010'
    if opt=='--2011':
        trigger = '2011'
    if opt=='--raw':
        datatype = 'RAWRECO'
    if opt=='--reco':
        datatype = 'RECO'
    if opt=='--mc':
        datatype = 'MC'
    if opt=='-m':
        datatype = 'MC'
    if opt=="--newhlttag":
        HLTL3Tag="hltStoppedHSCPCaloJetEnergy50"
    if opt=="--oldhlttag":
        HLTL3Tag="hltStoppedHSCPTight1CaloJetEnergy30"
        
# arguments
if (len(args)!=5):
    usage()
    sys.exit()
    
era = args[0]
label = args[1]
dataset = args[2]
gtag = args[3]
runs = args[4]
jsonfile = args[4]


# create CRAB variables
name = era + "_" + label
cfgname = "crab_tree_"+name+".cfg"
jobStr = "stoppedHSCP_tree_"+name+".py"
dirStr = "stoppedHSCP_tree_"+name

dbsStr = ""
if (useLocalDBS):
    dbsStr = "dbs_url=http://cmsdbsprod.cern.ch/cms_dbs_ph_analysis_02/servlet/DBSServlet"

runStr = ""
if (runs!="0" and not useJSON):
    runStr = "runselection="+runs

evtStr = ""
if (useJSON):
    evtStr = "lumi_mask="+jsonfile+"\n\
total_number_of_lumis = 100000\n\
lumis_per_job = 500\n"
else :
    evtStr = "total_number_of_events=-1\n\
events_per_job=100000\n"

scheduler = "glite"
storage = "T2_UK_SGrid_RALPP"
if (useCAF):
    scheduler = "caf"
    storage = "T2_CH_CAF"

#storage = "T3_US_UMD"
#user_remote_dir = HSCP_postrun_files



string = "[CRAB]\n\
jobtype = cmssw\n\
scheduler = "+scheduler+"\n\
#use_server = 1\n\
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
storage_element = "+storage+"\n\
user_remote_dir = "+dirStr+"\n\
ui_working_dir  = "+dirStr+"\n\
[GRID]\n\
rb = CERN\n\
proxy_server = myproxy.cern.ch"

if (useCAF):
    string += "queue = cmscaf1nd"
else:
    string += "\n#se_black_list = \n\
#se_white_list = \n\
#ce_black_list = \n\
ce_white_list = heplnx206.pp.rl.ac.uk,heplnx207.pp.rl.ac.uk\n\
#ce_white_list = ceprod02.hep.ph.ic.ac.uk\n\
#ce_white_list = lcgce03.phy.bris.ac.uk, lcgce02.phy.bris.ac.uk, lcgce01.phy.bris.ac.uk\n"

# create CRAB file
crab = open(cfgname, 'w')
crab.write(string)
crab.close()

# create CMSSW variables
cmsswStr="import FWCore.ParameterSet.Config as cms\n\
\n\
from StoppedHSCP.Analysis.stoppedHSCPTree_"+datatype+"_"+trigger+"_cfg import *\n\
\n\
process.MessageLogger.cerr.threshold = ''\n\
process.MessageLogger.cerr.FwkReport.reportEvery = 1000\n\
process.GlobalTag.globaltag = '"+gtag+"'\n\
process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(1000) )\n\
readFiles.extend( [\n\
] )\n\
"
if (HLTL3Tag<>"Default"):
    cmsswStr=cmsswStr+'\nprocess.stoppedHSCPTree.hltL3Tag= cms.untracked.InputTag("%s","","HLT")\n\n'%HLTL3Tag

# create CMSSW config
cmssw =open(jobStr, 'w')
cmssw.write(cmsswStr)
cmssw.close()
