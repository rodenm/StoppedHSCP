#!/usr/bin/env python

# create CRAB config file for an ntuple job


import sys, os, string
import getopt
import string

# Get pyGetFillScheme from StoppedHSCP/Ntuples
temp=os.path.join(os.environ['CMSSW_BASE'],"src","StoppedHSCP","Ntuples","scripts")
if not os.path.isdir(temp):
    print "ERROR!  Cannot find directory '%s'"%temp
    sys.exit()
sys.path.append(temp)

try:
    import pyGetFillScheme
except:
    print "ERROR:  Unable to import pyGetFillScheme.py"
    print "Have you remembered to check out StoppedHSCP/Ntuples from CVS?"
    sys.exit()

    

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


def WriteCrabFile(scheduler, dataset,storage,
                  runStr,dbsStr,evtStr,
                  useCAFsettings,
                  # The following all change when making reduced ntuples
                  cfgname,
                  jobStr,
                  dirStr,
                  whitelist,
                  output="stoppedHSCPTree.root" 
                  ):
    server_type="#use_server = 1\n"
    if (scheduler=="condor"):  # condor must have use_server=0
        server_type="use_server = 0\n"
    crabstring = "[CRAB]\n\
jobtype = cmssw\n\
scheduler = "+scheduler+"\n"+server_type+"\
[CMSSW]\n\
pset="+jobStr+"\n\
output_file = "+output+"\n\
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
    
    if (useCAFsettings):
        crabstring += "\nqueue = cmscaf1nd"
    else:
        crabstring += "\n#se_black_list = \n\
#se_white_list = \n\
#ce_black_list = \n\
#ce_white_list = heplnx206.pp.rl.ac.uk,heplnx207.pp.rl.ac.uk\n\
        "
        if not whitelist.startswith("#"):
            crabstring=crabstring+"\nce_white_list = %s\n"%whitelist
        
    # create CRAB file
    crab = open(cfgname, 'w')
    print "Writing file '%s'"%cfgname
    crab.write(crabstring)
    crab.close()
    return
###########################################

def WritePyCfgFile(datatype,trigger,gtag,
                   HLTL3Tag,
                   jobStr,makeReduced=False):
    # create CMSSW variables
    cmsswStr="import FWCore.ParameterSet.Config as cms\n\
\n\
from StoppedHSCP.Ntuples.stoppedHSCPTree_"+datatype+"_"+trigger+"_cfg import *\n\
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
    if (makeReduced==True):
        # need to keep calotowers, because they are used to compute iphi fraction
        cmsswStr=cmsswStr+'\nprocess.stoppedHSCPTree.doCaloTowers=False'
        cmsswStr=cmsswStr+'\nprocess.stoppedHSCPTree.doRecHits=False'
        cmsswStr=cmsswStr+'\nprocess.stoppedHSCPTree.doHFRecHits=False'
        cmsswStr=cmsswStr+'\nprocess.stoppedHSCPTree.makeReducedNtuples=True'
        cmsswStr=cmsswStr+'\nprocess.TFileService.fileName="stoppedHSCPTree_reduced.root"\n\n'

    # create CMSSW config
    cmssw =open(jobStr, 'w')
    print "Writing file '%s'"%jobStr
    cmssw.write(cmsswStr)
    cmssw.close()

    return
################################################################

def makeTreeJob(era,
                label,dataset,
                gtag,
                runjsonfile,
                useLocalDBS,
                useJSON,
                trigger,
                datatype,
                HLTL3Tag,
                whitelist='heplnx206.pp.rl.ac.uk,heplnx207.pp.rl.ac.uk',
                scheduler = "glite",
                storage = "T2_UK_SGrid_RALPP",
                useCAFsettings=False
                ):

    # Always check that fills.txt can be properly parsed
    fillfile=os.path.join(os.environ['CMSSW_BASE'],"src","StoppedHSCP","Ntuples","data","fills.txt")
    fillresult=pyGetFillScheme.CheckFillFile(fillfile)
    if fillresult==False:
        print "*********************************************"
        print "****   WARNING!!!!   ************************"
        print "****   Fill file '%s' ***********************"%fillfile
        print "****   appears to have bad syntax! **********"
        print "****   Results may be corrupted!  ***********"
        print "*********************************************"
        return False

    name = era + "_" + label
    cfgname = "crab_tree_"+name+".cfg"
    jobStr = "stoppedHSCP_tree_"+name+".py"
    dirStr = "stoppedHSCP_tree_"+name

    reducedcfgname="crab_tree_%s_reduced.cfg"%name
    reducedjobStr="stoppedHSCP_tree_%s_reduced.py"%name
    reduceddirStr="stoppedHSCP_tree_%s_reduced"%name

    dbsStr = ""
    if (useLocalDBS):
        dbsStr = "dbs_url=http://cmsdbsprod.cern.ch/cms_dbs_ph_analysis_02/servlet/DBSServlet"

    # runjsonfile can specify either json file or run selection
    runStr = ""
    if (runjsonfile!="0" and not useJSON):
        runStr = "runselection="+runs

    evtStr = ""
    if (useJSON):
        evtStr = "lumi_mask="+runjsonfile+"\n\
total_number_of_lumis = 100000\n\
lumis_per_job = 500\n"
    else :
        evtStr = "total_number_of_events=-1\n\
events_per_job=100000\n"

    if (useCAFsettings):
        scheduler = "caf"
        storage = "T2_CH_CAF"

    # necessary if one supplies scheduler, but doesn't supply useCAFsettings:
    if scheduler=="caf":
        useCAFsettings=True
        storage = "T2_CH_CAF"

    WriteCrabFile(scheduler, dataset,storage,
                  runStr,dbsStr,evtStr,
                  useCAFsettings,
                  cfgname,
                  jobStr,
                  dirStr,
                  whitelist,
                  "stoppedHSCPTree.root") 

    WriteCrabFile(scheduler, dataset, storage,
                  runStr,dbsStr,evtStr,
                  useCAFsettings,
                  reducedcfgname,
                  reducedjobStr,
                  reduceddirStr,
                  whitelist,
                  "stoppedHSCPTree_reduced.root") 

    WritePyCfgFile(datatype,trigger,gtag,
                   HLTL3Tag,
                   jobStr,makeReduced=False)
    WritePyCfgFile(datatype,trigger,gtag,
                   HLTL3Tag,
                   reducedjobStr,makeReduced=True)
    return True # True indicates that files written successfully

#####################################################

if __name__=="__main__":

    # Get command line options
    # Move to OptionParser?
    
    try:
        opts, args = getopt.getopt(sys.argv[1:], "hjlcm", ['2010','2011','raw','reco','mc','oldhlttag','newhlttag'])
    except getopt.GetoptError:
        print "Error getting options"
        usage()
        sys.exit(2)

    useLocalDBS = False
    useJSON = False
    useCAFsettings = False
    trigger = '2011'
    datatype = 'RECO'
    HLTL3Tag = "Default"

    for opt, arg in opts:
        if opt=='-l':
            useLocalDBS=True
        if opt=='-j':
            useJSON = True
        if opt=='-c':
            useCAFsettings = True
        if opt=='-h':
            print "Printing Help Message"
            usage()
            sys.exit()
        if opt=='--2010':
            trigger = '2010'
        if opt=='--2011':
            trigger = '2011'
        if opt=='--raw' or opt=='RAW':
            datatype = 'RAWRECO'
        if opt=='--reco' or opt=='--RECO':
            datatype = 'RECO'
        if opt=='--mc' or opt=='MC':
            datatype = 'MC'
        if opt=='-m':
            datatype = 'MC'
        if opt=="--newhlttag":
            HLTL3Tag="hltStoppedHSCPCaloJetEnergy50"
        if opt=="--oldhlttag":
            HLTL3Tag="hltStoppedHSCPTight1CaloJetEnergy30"

    # arguments
    if (len(args)!=5):
        print "Wrong number of arguments!"
        usage()
        sys.exit()

    era = args[0]
    label = args[1]
    dataset = args[2]
    gtag = args[3]
    #runs = args[4]
    jsonfile = args[4]

    # Call the makeTreeJob function
    x=makeTreeJob(era=era,
                  label=label,
                  dataset=dataset,
                  gtag=gtag,
                  runjsonfile=jsonfile,
                  useLocalDBS=useLocalDBS,
                  useJSON=useJSON,
                  trigger=trigger,
                  datatype=datatype,
                  HLTL3Tag=HLTL3Tag,
                  whitelist='heplnx206.pp.rl.ac.uk,heplnx207.pp.rl.ac.uk',  # add whitelist option at some point?
                  scheduler = "glite",
                  storage = "T2_UK_SGrid_RALPP"
                  )
    if x==True:
        print "Successfully created files!"

