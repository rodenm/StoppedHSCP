#!/usr/bin/env python

'''
Script to read fills.txt file and json file to make sure that all runs in json file are also in fills.txt.
'''

import os,sys,string

# for json support
try: # FUTURE: Python 2.6, prior to 2.6 requires simplejson
    import json
except:
    try:
        import simplejson as json
    except:
        print "Please use lxplus or set an environment (for example crab) with json lib available"
        sys.exit(1)

from optparse import OptionParser

####################################################

def ReadFillsFile(fillsfile):
    runs=[]
    rundict={}  # use at some point?
    temp=open(fillsfile,'r').readlines()
    for line in temp:
        if line.startswith("Fill"):
            continue
        try:
            l=string.strip(line)
            l=string.split(l)
            fill=string.atoi(l[0])
            scheme=l[1]
            tempruns=string.split(l[2],",")
            theseruns=[]
            for t in tempruns:
                r=string.atoi(t)
                theseruns.append(r)
                runs.append(r)
            rundict[fill]=theseruns
        except:
            print "Cannot parse line '%s'"%line
    #print "RUNS = ",runs
    return runs

##########################################################

def ReadJsonFile(infile):
    print "infile=",infile
    jsonfile=file(infile,'r')
    jsondict=json.load(jsonfile)
    return jsondict

###########################################################

def CompareRuns(jsondict,fillslist):
    jsonkeys=jsondict.keys()
    jsonkeys.sort()
    bad=0
    for run in jsonkeys:
        if string.atoi(run) not in fillslist:
            print "ERROR!  Run %s not in fills.txt!"%run
            bad=bad+1
    if bad ==0:
        print "All json runs present in fills.txt!"
    else:
        print "\n*****************************************************"
        print "<checkFillsFileForRuns.py::CompareRuns>   WARNING!!!!"
        print "A total of %i runs were not found in fills.txt!"
        print "*****************************************************\n"
    return bad

############################################################

def MainCheckFills(jsonfile,fillsfile):
    jsondict=ReadJsonFile(jsonfile)
    fillslist=ReadFillsFile(fillsfile)
    print "Comparing runs in \njson file '%s'\nto runs in \nfills file '%s'"%(jsonfile,fillsfile)
    CompareRuns(jsondict,fillslist)
    return

############################################################

if __name__=="__main__":

    parser=OptionParser()
    parser.add_option("-j","--json",
                      dest="jsonfile",
                      default=None,
                      help="Specify json file")
    parser.add_option("-f","--fillfile",
                      dest="fillfile",
                      default=None,
                      help="Specify fill file (such as fills.txt)")
    (opts,args)=parser.parse_args()
    arg_index=0
    jsonfile=opts.jsonfile
    if jsonfile==None:
        if len(args)>0:
            jsonfile=args[arg_index]
            arg_index=arg_index+1
        else:
            print "Error!  No input json file provided!"
            sys.exit()
    if not os.path.isfile(jsonfile):
        print 'Error!  Specified json file "%s" does not exist!'%jsonfile
        sys.exit()
        
    fillfile=opts.fillfile
    if fillfile==None:
        if len(args)>arg_index:
            fillfile=args[arg_index]
            arg_index=arg_index+1
        else:
            basedir=os.getenv("CMSSW_BASE")
            if basedir==None:
                print "Error!  No fill file specified and no CMSSW base area detected!"
                sys.exit()

            basedir="%s/src/StoppedHSCP/Ntuples/data"%basedir
            fillfile=os.path.join(basedir,"fills.txt")
            print "No fill file specified -- using default (%s)"%fillfile
    if not os.path.isfile(fillfile):
        print "Error!  Specified fill file '%s' does not exist!"%fillfile
        sys.exit()

    MainCheckFills(jsonfile,fillfile)
    
