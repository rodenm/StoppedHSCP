#!/usr/bin/python

version=1.00

''' This script will perform a number of steps to identify new fills/runs:

1)  Get fill/run/scheme cross-correlation info from WBM  (still in development -- will eventually alter fills.txt and fillingSchemes.txt in ../data directory).

2)  Search DBS for runs in specified dataset

3)  Fill schemes, runs for new fills (still in development)

4)  get JSON file from afs and produce final JSON based on runs in range

'''

import sys, os, string
from optparse import OptionParser
import time
import threading


# for json support
try: # FUTURE: Python 2.6, prior to 2.6 requires simplejson
    import json as JSON
except:
    try:
        import simplejson as JSON
    except:
        print "Please use lxplus or set an environment (for example crab) with json lib available"
        sys.exit(1)


class FillInfo:
    ''' Stores information about fills for each line from fills.txt'''
    def __init__(self,line,debug=False):
        self.valid=False
        self.debug=debug
        self.Fill=None
        self.Scheme=None
        self.Runs=[]
        temp=string.split(line)

        # Need to have fill and scheme on line
        if len(temp)<2:
            if (debug):  print "<FillInfo> ERROR:  Not enough arguments in line '%s'"%line
            return

        # Try to read fill number
        try:
            self.Fill=string.atoi(temp[0])
        except:
            if (debug):
                print "<FillInfo> ERROR:  Unable to parse line '%s' to get Fill"%line
            return

        # Try to read fill scheme
        self.Scheme=string.strip(temp[1])

        # Try to read runs
        if (len(temp)>2):
            runs=string.strip(temp[2])
            runs=string.split(runs,",")
            for r in runs:
                try:
                    self.Runs.append(string.atoi(r))
                except:
                    if (debug):  # Need to edit this to check whether run is from stable beams at some point -- otherwise, error is expected.  Until we have auto-access to the run/scheme/fill info, only show this message when debugging
                        print "<FillInfo> ERROR:  Cannot parse run '%s' in line '%s'"%(r,line)

        if len(self.Runs)>0:
            self.valid=True  # all info read from line
        return

# Step 1:  Does not yet exist

# Step 2:
def SearchDBS(dataset="/MinimumBias/Run2011A-HSCPSD-PromptSkim-v6/RECO",
              debug=False):
    ''' Searches DBS for runs in a given dataset.'''
    cmd="dbs --search --query='find run where dataset=%s'"%dataset
    print "Searching DBS, using this command:"
    print cmd
    print
    out=os.popen(cmd).readlines()
    runs=[]
    for i in out:
        try:
            runs.append(string.atoi(string.strip(i)))
        except:
            continue
    runs.sort()
    print "RUNS FOUND = ",runs
    if len(runs)>0:
        print "Run range = %i - %i"%(runs[0],runs[-1])
    return runs

# Step 3:
def ReadFills(fills="%s/src/StoppedHSCP/Ntuples/data/fills.txt"%os.getenv("CMSSW_BASE"),
              runs=[],  # list of runs found in dataset
              debug=False
              ):
    ''' Reads fills.txt, checks run/fill/scheme info.  Still to be updated once WBM access figured out.'''
    if not os.path.isfile(fills):
        print "<ReadFills> ERROR:  No file '%s'"%fills
        return False
    thefile=open(fills,'r').readlines()
    readfills={}
    readfillsbyrun={}
    for f in thefile:
        tmp=FillInfo(f)
        if tmp.valid==True:
            readfills[tmp.Fill]=tmp
            for r in tmp.Runs:
                readfillsbyrun[r]=tmp
    keys=readfillsbyrun.keys()
    keys.sort()
    valid=True
    for r in runs:
        if r not in keys:
            # Need to edit this to check whether run is from stable beams at some point -- otherwise, error is expected.  Until we have auto-access to the run/scheme/fill info, list this as "ERROR" only if debugging turned on (used by MakeJsonFile function below)
            if (debug==True):
                print "<ReadFills> WARNING:  Dataset run '%i' not found in fill file '%s'.  Run may not come from a fill with stable beams?"%(r,fills)
                valid=False
    return valid

# Step 4:
def MakeJsonFile(json=None,
                 runs=[],
                 cernuser=None,
                 scpjson=True,
                 debug=False):
    '''
    Makes a json file from list of runs in step 2, and an input json file.
    Tries to copy the input json from lxplus, unless "scpjson" is set to False,
    in which case the input json is treated as a local file.
    '''
        
    if json==None:
        print "<MakeJsonFile>ERROR!  No json file provided!"
        return False
    if runs==[]:
        print "<MakeJsonFile>WARNING!  No run range specified!  Will look for all runs from 0-999999999]"
        runs=[0,999999999]
    print "Trying to copy file '%s' to local directory"%json

    # scp file from lxplus
    if scpjson==True:
        host=os.getenv("HOST")
        if host.find("lxplus")>-1 and host.find(".cern.ch")>-1:
            cmd="scp %s ."%json
        else:
            if (cernuser==None):
                print "<MakeJsonFile>ERROR!  Must specify CERN user name!"
                return False
            cmd="scp %s@lxplus.cern.ch:%s ."%(cernuser,json)

        print "Copying json file via:"
        print cmd
        print
        mycopy=os.system(cmd)

        if mycopy==0:  # scp returns 0 when successful
            print "Successfully copied file!"
        else:
            print "<MakeJsonFile>ERROR!  Could not scp file '%s'"%json
            return False
        localjson=os.path.basename(json)
    else:
        localjson=json # json file already present; no need to copy
    print
    # Make new json from input
    print "Making new json file for runs %i-%i from original json file %s"%(runs[0],runs[-1],localjson)
    newjson="runs_SE_TEMP.json"
    cmd="jsonrunsel.py %i %i %s %s"%(runs[0],runs[-1],
                                     localjson,
                                     newjson)
    print cmd
    print
    os.system(cmd)

    if not os.path.isfile(newjson):
        print "<MakeJsonFile>ERROR!  No file '%s' has been produced!"%newjson
        return False

    # open new json, and get list of all included runs
    temp=open(newjson,'r')
    tempjson=JSON.load(temp)
    keys=tempjson.keys()
    keys.sort()
    intkeys=[]
    if len(keys)==0:
        print "<MakeJsonFile>ERROR!  No valid runs found in '%s'"%newjson
        return False

    print "\nChecking that all runs in json are also in fills.txt"
    for k in keys:
        intkeys.append(string.atoi(k))
    runsgood=ReadFills(runs=intkeys,debug=True)  # for now, call 'ReadFills' from here to check whether runs in JSON files are also in fills.txt
    if runsgood==False:
        print "<MakeJsonFile>ERROR!  Not all runs in json file '%s' are in fills.txt!"%newjson
        return False
    
    print "Json file contains runs %u-%u"%(string.atoi(keys[0]),
                                           string.atoi(keys[-1])
                                           )
    newfile="runs_SE_%u_%u.json"%(string.atoi(keys[0]),
                                  string.atoi(keys[-1])
                                  )
    print "Moving file '%s' to '%s'"%(newjson,newfile)
    cmd="mv %s %s"%(newjson, newfile)
    os.system(cmd)

    # Copy file to ../data directory.  Change 'cp' to 'mv'?
    if os.getenv("CMSSW_BASE")<>None:
        print "Copying new json file to %s"%os.path.join(os.getenv("CMSSW_BASE"),"src/StoppedHSCP/Ntuples/data",newfile)
        cmd="cp %s %s"%(newfile, 
                        os.path.join(os.getenv("CMSSW_BASE"),"src/StoppedHSCP/Ntuples/data"))
        x=os.system(cmd)
        if x>0:
            print "<MakeJsonFile>ERROR!  Could not copy file '%s'"%newfile
            return False
    else:
        print "Unable to identify CMSSW base directory!"
        print "Leaving new json file '%s' in current directory!"%newfile
    return True
    
#######

if __name__=="__main__":
    parser=OptionParser(usage="hi there!",
                        version="%s"%version)
    parser.add_option("-v","--verbose",
                      dest="debug",
                      action="store_true",
                      default=False,
                      help="Show debugging information")
    parser.add_option("-d","--dataset",
                      dest="dataset",
                      default="",
                      help="Specify dataset.  Default is '/MinimumBias/Run2011A-HSCPSD-PromptSkim-v6/RECO'")
    parser.add_option("-j","--json",
                      dest="json",
                      default=None,
                      help="Specify json file")
    parser.add_option("-l","--localjson",
                      dest="localjson",
                      default=False,
                      action="store_true",
                      help="If specified, input json will be considered a local file, instead of being copied from lxplus.  Default is False.")
    parser.add_option("-u","--username",
                      dest="user",
                      default="temple",
                      help="Specify your CERN user name, so that files can be copied from lxplus.  (Default is 'temple'.")
    opts,args=parser.parse_args()

    if opts.json<>None:
        if opts.json.startswith("https://cms-service-dqm.web.cern.ch/cms-service-dqm/"):

            #http location for Prompt JSONS: 'https://cms-service-dqm.web.cern.ch/cms-service-dqm/CAF/certification/Collisions11/7TeV/Prompt/'
            opts.json=string.replace(opts.json,
                                     "https://cms-service-dqm.web.cern.ch/cms-service-dqm/CAF",
                                     "/afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM")

        if opts.localjson==False and not opts.json.startswith("/"):
            opts.json=os.path.join("/afs/cern.ch/cms/CAF/CMSCOMM/COMM_DQM/certification/Collisions11/7TeV/Prompt",opts.json)

    runs=SearchDBS(debug=opts.debug,
                   dataset=opts.dataset)
    # new 2011B dataset:/MinimumBias/Run2011B-HSCPSD-PromptSkim-v1/RECO
    #sys.exit()
    ReadFills(runs=runs,
              debug=opts.debug)
    #runs=[0,999999999]
    MakeJsonFile(json=opts.json,
                 cernuser=opts.user,
                 scpjson=not opts.localjson,
                 runs=runs)
