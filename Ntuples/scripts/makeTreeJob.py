#!/usr/bin/env python

# create CRAB config file for an ntuple job


import sys, os, string
import getopt
import string
from optparse import OptionParser




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

import SetDatasetInfo


def OptParserUsage():
    ''' Usage function as returned by OptionParser. '''
    mytext= "[makeTreeJob.py usage]: \n\tmakeTreeJob.py  <era> <label> <dataset> <global tag> <runlist|JSON file>\n"
    mytext=mytext+"\t\t* 'era' specifies dataset, CMSSW version, and Ntuple tag \n\t\t\t(e.g., 'Run2011B_423p5_V180400')\n"
    mytext=mytext+"\t\t* 'label' specifies the fill range and version for these ntuples \n\t\t\t(e.g., '2006_2040_v1')\n"
    mytext=mytext+"\t\t* 'dataset' specifies full dataset name \n\t\t\t(e.g., '/MinimumBias/Run2011B-HSCPSD-PromptSkim-v1/RECO')\n"
    mytext=mytext+"\t\t* 'global tag' takes the form 'GR_P_V22::All'\n"
    mytext=mytext+"\t\t* 'runlist/JSON file' specifies the runlist or json file for the data.\n"
    mytext=mytext+"\n\nOptional parameters listed below:"
    return mytext

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
    ''' Write crab .cfg file for ntuple generation.'''
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
        if whitelist <>None and not whitelist.startswith("#"):
            crabstring=crabstring+"\nce_white_list = %s\n"%whitelist
        else:
            crabstring=crabstring+"\n"
    # create CRAB file
    crab = open(cfgname, 'w')
    print "Writing file '%s'"%cfgname
    crab.write(crabstring)
    crab.close()
    return
###########################################

def WritePyCfgFile(datatype,
                   trigger,gtag,
                   HLTL3Tag,
                   jobStr,
                   makeReduced=False,
                   datasetInfo=None,
                   l1JetNoBptxName=None,
                   l1JetNoBptxNoHaloName=None
                   ):
    ''' Write python .py file that crab.cfg file uses for running the ntuple job.'''
    
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
    if datasetInfo<>None:
        keys=datasetInfo.InputInfo.keys()
        keys.sort()
        for k in keys:
            if datasetInfo.InputInfo[k]==None:
                continue
            if k=="hltL3Tag":
                cmsswStr=cmsswStr+'\nprocess.stoppedHSCPTree.%s = cms.untracked.InputTag("%s","","HLT")'%(k,datasetInfo.InputInfo[k])
            else:
                cmsswStr=cmsswStr+"\nprocess.stoppedHSCPTree.%s = cms.untracked.string('%s')"%(k,datasetInfo.InputInfo[k])
    cmsswStr=cmsswStr+"\n"
    if (HLTL3Tag<>"Default"):
        cmsswStr=cmsswStr+'\nprocess.stoppedHSCPTree.hltL3Tag = cms.untracked.InputTag("%s","","HLT")\n\n'%HLTL3Tag

    if (l1JetNoBptxName<>None):
        cmsswStr=cmsswStr+"\nprocess.stoppedHSCPTree.l1JetNoBptxName = cms.untracked.string('%s')\n"%l1JetNoBptxName
    if (l1JetNoBptxNoHaloName<>None):
        cmsswStr=cmsswStr+"\nprocess.stoppedHSCPTree.l1JetNoBptxNoHaloName = cms.untracked.string('%s')\n"%l1JetNoBptxNoHaloName

    if (makeReduced==True):
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
                HLTL3Tag="Default", # won't change from default tag
                whitelist=None,
                scheduler = "glite",
                storage = "T2_UK_SGrid_RALPP",
                useCAFsettings=False,
                datasetInfo=None,
                l1JetNoBptxName=None,
                l1JetNoBptxNoHaloName=None
                ):
    ''' Make the .py and .cfg files necessary for generating ntuple trees.'''

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

    # Set up names of tree .cfg and .py file
    name = era + "_" + label
    cfgname = "crab_tree_"+name+".cfg"
    jobStr = "stoppedHSCP_tree_"+name+".py"
    dirStr = "stoppedHSCP_tree_"+name

    # Set up names of reduced ntuples files
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

    # Specify number of lumis or number of events
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

    # write main crab and python cfg files
    print
    WriteCrabFile(scheduler, dataset,storage,
                  runStr,dbsStr,evtStr,
                  useCAFsettings,
                  cfgname,
                  jobStr,
                  dirStr,
                  whitelist,
                  "stoppedHSCPTree.root") 
    WritePyCfgFile(datatype,trigger,gtag,
                   HLTL3Tag,
                   jobStr,
                   makeReduced=False,
                   datasetInfo=datasetInfo,
                   l1JetNoBptxName=l1JetNoBptxName,
                   l1JetNoBptxNoHaloName=l1JetNoBptxNoHaloName
                   )

    print
    # Write reduced cfg files
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
                   reducedjobStr,
                   makeReduced=True,
                   datasetInfo=datasetInfo,
                   l1JetNoBptxName=l1JetNoBptxName,
                   l1JetNoBptxNoHaloName=l1JetNoBptxNoHaloName
                   )
                   
    print
    return True # True indicates that files written successfully

#####################################################

if __name__=="__main__":

    # Parser command line options
    # (Use OptionParser for more control, and to allow for whitelist specification)
    parser=OptionParser(usage=OptParserUsage())
    parser.add_option("-l","--l",
                      action="store_true",
                      dest="useLocalDBS",
                      default=False,
                      help="Use local DBS (http://cmsdbsprod.cern.ch/cms_dbs_ph_analysis_02/servlet/DBSServlet)")
    parser.add_option("-j","--json",
                      dest="useJSON",
                      action="store_true",
                      default=False,
                      help="use JSON file to run on good LS")
    parser.add_option("-c","--CAF",
                      dest="useCAFsettings",
                      action="store_true",
                      default=False,
                      help="use CAF")
    parser.add_option("--2010",
                      dest="trigger2010",
                      action="store_true",
                      default=False,
                      help="use 2010 trigger config")
    parser.add_option("--2011",
                      dest="trigger2011",
                      action="store_true",
                      default=False,
                      help="use 2011 trigger config (default)")
    parser.add_option("--raw","--RAW",
                      dest="rawdata",
                      action="store_true",
                      default=False,
                      help="use RAW+RECO config")
    parser.add_option("--reco","--RECO",
                      dest="recodata",
                      action="store_true",
                      default=False,
                      help="use RECO config (default)")
    parser.add_option("--mc","--MC",
                      dest="mcdata",
                      action="store_true",
                      default=False,
                      help="use MC config")
    parser.add_option("--newhlttag",
                      dest="newhlttag",
                      action="store_true",
                      default=False,
                      help="use HLTL3Tag hltStoppedHSCPCaloJetEnergy50")
    parser.add_option("--oldhlttag",
                      dest="oldhlttag",
                      default=False,
                      action="store_true",
                      help="use HLTL3Tag hltStoppedHSCPTight1CaloJetEnergy30")
    parser.add_option("--defaultwhitelist",
                      dest="defaultwhitelist",
                      action="store_true",
                      default=False,
                      help="Use default white list values (heplnx206.pp.rl.ac.uk,heplnx207.pp.rl.ac.uk)")
    parser.add_option("-w","--whitelist",
                      dest="whitelist",
                      default=None,
                      help="Specify whitelist site(s)")
    parser.add_option("--l1JetNoBptxName",
                      dest="l1JetNoBptxName",
                      default=None,
                      help="Specify l1JetNoBptxName that is different from default in cfi.py file")
    parser.add_option("--l1JetNoBptxNoHaloName",
                      dest="l1JetNoBptxNoHaloName",
                      default=None,
                      help="Specify l1JetNoBptxNoHaloName that is different from default in cfi.py file")
    

    (opts,args)=parser.parse_args()

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

    knownDatasets = SetDatasetInfo.GetDatasets()
    if dataset not in knownDatasets:
        print "WARNING!  Dataset %s is not in list of known datasets!"
        print "You may want to update SetDatasetInfo.py!"
        print
        thisdataset=None
    else:
        thisdataset=knownDatasets[dataset]

    trigger=None
    if thisdataset.trigger<>None:
        trigger=thisdataset.trigger
        
    useLocalDBS = opts.useLocalDBS
    useJSON = opts.useJSON
    useCAFsettings = opts.useCAFsettings
    if opts.trigger2010==True and opts.trigger2011==False:
        if (trigger<>None and trigger <>"2010"):
            print "**********"
            print "Warning!  Overwriting default trigger value of '%s'"%trigger
            print "**********"
        trigger='2010'
    elif opts.trigger2010==False and opts.trigger2011==True:
        if (trigger<>None and trigger<>"2011"):
            print "**********"
            print "Warning!  Overwriting default trigger value of '%s'"%trigger
            print "**********"
        trigger = '2011'
    elif opts.trigger2010==False and opts.trigger2011==False:
        if trigger==None:
            print "ERROR!  No trigger type (--2010 or --2011) has been specified!"
            sys.exit()
    elif opts.trigger2010==True and opts.trigger2011==True:
        print "ERROR!  Trigger type can not be both --2010 and --2011!"
        sys.exit()

    if opts.rawdata==False and opts.mcdata==False and opts.recodata==False:
        if thisdataset<>None and thisdataset.datatype in ["RAW","RECO","MC"]:
            datatype=thisdataset.datatype
        else:
            print "**********"
            print "ERROR!  No data type specified on command line!"
            print "Must specify --raw, --reco, or --mc,"
            print "or have dataset's data type defined in SetDatasetInfo.py"
            sys.exit()

    if opts.rawdata==True:
        if opts.recodata==False and opts.mcdata==False:
            datatype = 'RAW'
        else:
            print "ERROR!  Cannot specify more than one data type (--raw, --reco, --mc)"
            sys.exit()
    elif opts.recodata==True:
        if opts.rawdata==False and opts.mcdata==False:
            datatype = 'RECO'
        else:
            print "ERROR!  Cannot specify more than one data type (--raw, --reco, --mc)"
            sys.exit()
    elif opts.mcdata==True:
        if opts.rawdata==False and opts.recodata==False:
            datatype = 'MC'
        else:
            print "ERROR!  Cannot specify more than one data type (--raw, --reco, --mc)"
            sys.exit()

    if thisdataset<>None and thisdataset.datatype<>datatype:
        print "****************"
        print "Warning!  Specified data type of '%s' doesn't agree with data type '%s' defined in SetDatasetInfo.py for this dataset!"%(datatype,thisdataset.datatype)
        print "****************"
        
    HLTL3Tag = "Default"
    # Get HLT tag from dataset definition, if available
    if thisdataset<>None and thisdataset.InputTag["hltL3Tag"]<>None:
        HLTL3Tag=thisdataset.InputTag["hltL3Tag"]

    # use of new, old hlt options will overwrite default HLTL3Tag!
    if opts.newhlttag==True and opts.oldhlttag==False:
        HLTL3Tag="hltStoppedHSCPCaloJetEnergy50"
    elif opts.newhlttag==False and opts.oldhlttag==True:
        HLTL3Tag="hltStoppedHSCPTight1CaloJetEnergy30"
    elif opts.newhlttag==True and opts.oldhlttag==True:
        print "ERROR!  Cannot specify both --oldhlttag and --newhlttag"
        sys.exit()

    whitelist=None
    if opts.defaultwhitelist==True:
        if opts.whitelist==None:
            whitelist="heplnx206.pp.rl.ac.uk,heplnx207.pp.rl.ac.uk"
        else:
            print "ERROR!  Cannot specify both --defaultwhitelist and your own whitelist (-w)!"
            sys.exit()
    elif opts.whitelist<>None:
        whitelist=opts.whitelist


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
                  whitelist=whitelist,  # add whitelist option at some point?
                  scheduler = "glite",
                  storage = "T2_UK_SGrid_RALPP",
                  datasetInfo=thisdataset,
                  l1JetNoBptxName=opts.l1JetNoBptxName,
                  l1JetNoBptxNoHaloName=opts.l1JetNoBptxNoHaloName
                  )
    if x==True:
        print "Successfully created files!"

