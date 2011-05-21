#!/usr/bin/env python

'''
RemoveBadRuns.py
by Jeff Temple
v1.0
20 May 2011

This program will take an input json file, and an optional bad json file (defaults to badPrescael_163581_163869.json), and produces a new json file with the bad runs/lumi sections removed.

Options are:
-i <json file>  :  Specify input file to be cleaned
-o <output file>  :  Specify output file name (default is cleanedOutput.json)
-s [run]   : Specify starting run (default is -1; all runs used)
-e [run]   : Specify ending run (default is -1; all runs used)

-b <json file>:  Specify json file containing bad jsons.  With this option, only the LS specified in the file will be excluded from the cleaned output
-B <json file>:  Specify json file containing bad runs.  With this option, all runs in the json keys will be excluded, regardless of whether the LS in the bad file match those in the original file.

To do:  Allow users to specify runs (or range of runs) to be removed directly, rather than through json.
'''

import string,os,sys
from optparse import OptionParser

#for json support
try: # FUTURE: Python 2.6, prior to 2.6 requires simplejson
    import json
except:
    try:
        import simplejson as json
    except:
        print "Please use lxplus or set an environment (for example crab) with json lib available"
        sys.exit(1)



def RemoveLS(goodLS,badLS,debug=False):
    allgoodLS=[]
    allbadLS=[]
    for i in goodLS:
        if len(i)==2:
            for ls in range(i[0],i[1]+1):
                if ls not in allgoodLS:
                    allgoodLS.append(ls)
        else:
            if i[0] not in allgoodLS:
                allgoodLS.append(i[0])

    for i in badLS:
        if len(i)==2:
            for ls in range(i[0],i[1]+1):
                if ls not in allbadLS:
                    allbadLS.append(ls)
        else:
            if i[0] not in allbadLS:
                allbadLS.append(i[0])
    for i in allbadLS:
        if i in allgoodLS:
            allgoodLS.remove(i)
    allgoodLS.sort()
    finalgoodLS=[]

    currentBlock=[]
    if len(allgoodLS)==0:
        return None
    if (len(allgoodLS)==1):
        finalgoodLS.append([allgoodLS[0],allgoodLS[0]])
    else:
        for i in range(0,len(allgoodLS)):
            currentBlock.append(allgoodLS[i])
            # Call whenever there's a jump in LS, and also at end of LS list
            if (i==len(allgoodLS)-1 or allgoodLS[i]-allgoodLS[i-1]>1):
                firstLS=currentBlock[0]
                endLS=currentBlock[-1]
                finalgoodLS.append([firstLS,endLS])
                currentBlock=[]
    return finalgoodLS


def CleanJson(inputlist,  # json dict of good runs
              badlist,  # json dict of bad lumi sections
              badruns=None, # json dict of bad runs
              excludedRuns=None,  # user-specified dict of bad runs
              outputname="cleanedOutput.json",
              startrun=-1,
              endrun=-1):

    inputdict={}
    baddict={}
    cleandict={}
    # Read all keys from input jsons
    for i in inputlist:
        temp=open(i,'r')
        tempdict=json.load(temp)
        for key in tempdict.keys():
            if key in inputdict.keys():
                print "ERROR!  KEY '%s' is already in list of input runs!"%key
                print "Existing JSON for this key: %s"%inputdict[key]
                print "JSON for this key from file '%s': %s"%(i,tempdict[key])
                print "Skipping JSON from file '%s' for this run"%i
            else:
                inputdict[key]=tempdict[key]
    # Now read all keys from badlist
    for i in badlist:
        temp=open(i,'r')
        tempdict=json.load(temp)
        for key in tempdict.keys():
            if key in baddict.keys():
                print "ERROR!  KEY '%s' is already in list of bad jsons!"%key
                print "Existing bad JSON for this key: %s"%baddict[key]
                print "bad JSON for this key from file '%s': %s"%(i,tempdict[key])
                print "Skipping bad JSON from file '%s' for this run"%i
            else:
                baddict[key]=tempdict[key]
    #print "Good list length = %i  bad list length = %i"%(len(inputdict.keys()),len(baddict.keys()))
    # Now read all runs from bad run list
    badrundict={}
    if badruns<>None:
        print badruns
        for i in badruns:
            temp=open(i,'r')
            tempdict=json.load(temp)
            for key in tempdict.keys():
                if key in badrundict.keys():
                    print "ERROR!  KEY '%s' is already in list of bad runs!"%key
                    print "Existing bad RUN for this key: %s"%baddict[key]
                    print "bad RUN for this key from file '%s': %s"%(i,tempdict[key])
                    print "Skipping bad RUN from file '%s' for this run"%i
                else:
                    badrundict[key]=tempdict[key]
    for i in excludedRuns.keys():
        if i not in badrundict.keys():
            badrundict[i]=excludedRuns[i]
    # Remove badruns from goodruns
    inputkeys=inputdict.keys()
    inputkeys.sort()
    badrunkeys=badrundict.keys()
    for i in inputkeys:
        
        thisrun=string.atoi(i)
        print "Checking Run %s"%i
        if i in badrunkeys:  # i is in list of bad runs -- ignore the run completely
            print "BAD RUN '%i' found -- Skipping"%thisrun
            continue

        if (startrun>-1 and thisrun<startrun):
            print "Run '%i' is outside specified range [%i-%i]"%(thisrun,startrun,endrun)
            continue
        if (endrun>-1 and thisrun>endrun):
            print "Run '%i' is outside specified range [%i-%i]"%(thisrun,startrun,endrun)
            continue
        if i not in baddict.keys():
            finalLS=inputdict[i]
        else:
            print "FOUND BAD RUN",i
            finalLS=RemoveLS(inputdict[i],baddict[i])
            if finalLS==None or len(finalLS)==0:  # no good LS left in this run; skip it
                continue
        if i in cleandict.keys():
            cleandict[i].append(finalLS)
        else:
            cleandict[i]=finalLS

    keys=cleandict.keys()
    keys.sort()
    print "\n\n"

    out=open(outputname,'w')
    json.dump(cleandict,out,sort_keys=True)
    out.close()
    
    #outtext="{"
    #for i in keys:
    #     print "Run %s,  good LS:  %s"%(i, cleandict[i])
    #     outtext+='"%s":%s, '%(i,cleandict[i])
    #while outtext.endswith(", "):
    #    outtext=outtext[:-2]
    #outtext+="}"
    #out.write(outtext)
    #out.close()
    return cleandict


def CompareOutput(inputlist,outputfile):
    for i in inputlist:
        if not os.path.isfile(i):
            print "Error!  Input json '%s' does not exist"%i
            print "Skipping file"
    if not os.path.isfile(outputfile):
        print "Error!  Output json '%s' does not exist"%outputfile
        return

    # Read list of input files
    myin={}
    for i in inputlist:
        tempin=open(i,'r')
        tempin=json.load(tempin)
        for x in tempin.keys():
            if x not in myin.keys():
                myin[x]=tempin[x]
            else:
                print "<CompareOutput> Error!  Run '%s' already defined in previous input json.  Skipping..."%x

    # Read single output file
    print "out = ",outputfile
    myout=open(outputfile,'r')
    myout=json.load(myout)

    runs=myin.keys()
    runs.sort()
    print
    print "The following runs were removed in the output file '%s':"%outputfile
    for i in runs:
        if i not in myout.keys():
            print "Run %s"%i
    print
    print "The following LS were modified in the output file '%s':"%outputfile
    for i in runs:
        if i in myout.keys() and myin[i]<>myout[i]:
            print "Run %s:\tInput LS: %s\tOutput LS: %s"%(i,myin[i],myout[i])
    return


#####################
if __name__=="__main__":
    
    parser=OptionParser()
    parser.add_option("-i",action="append",
                      default=[],
                      dest="inputjson",
                      help="Specify input json(s)")
    parser.add_option("-b",action="append",
                      default=[],
                      dest="badjson",
                      help="Specify bad json(s)")
    parser.add_option("-B",action="append",
                      default=[],
                      dest="BADRUNS",
                      help="Specify json with BAD RUNS (all runs in file will be considered bad, regardless of specified LS in list)")
    parser.add_option("-o",
                      dest="outputjson",
                      default="cleanedOutput.json",
                      help="Specify output file")
    
    parser.add_option("-s",
                      dest="startrun",
                      type="int",
                      default=-1,
                      help="Specify starting run")
    parser.add_option("-e",
                      dest="endrun",
                      type="int",
                      default=-1,
                      help="Specify ending run")
    parser.add_option("-d","--diff",
                      dest="diff",
                      action="store_true",
                      default=False,
                      help="If specified, only computes difference between initial and final json file.")

    (options,args)=parser.parse_args()

    excludeRuns={} # list of runs to be excluded
    # Assume all arguments are input files
    for i in args:
        if os.path.isfile(i):
            options.inputjson.append(i)
    for i in options.inputjson:
        if not os.path.isfile(i):
            print "ERROR!  Input Json file '%s' does not exist"%i
            options.inputjson.remove(i)

    if len(options.inputjson)==0:
        print "ERROR!  No valid input Json files given on command line!"
        sys.exit()
    
    for i in options.badjson:
        if not os.path.isfile(i):
            options.badjson.remove(i)
            try:
                temp=string.split(i,"-")
                if len(temp)==1:
                    temp=string.atoi(string.strip(temp))
                    excludeRuns["%s"%temp]="Exclude run %i"%temp
                elif len(temp)==2:
                    startrun=string.atoi(string.strip(temp[0]))
                    endrun=string.atoi(string.strip(temp[1]))
                    for z in range(startrun,endrun+1):
                        excludeRuns["%s"%temp]="Exclude run %i"%temp
            except:
                print "ERROR!  Bad Json file '%s' does not exist!"%i

    

    if len(options.badjson)==0 and len(excludeRuns.keys())==0:
        print "No bad Json files specified."
        #if os.path.isfile("badPrescale_163581_163869.json"):
        #    options.badjson.append("badPrescale_163581_163869.json")
        #    print "Using default file 'badPrescale_163581_163869.json'"
        #else:
        print "Will remove no bad json files"
            
    if len(options.BADRUNS)==0:
        print "NO LIST OF BAD RUNS specified."
        if os.path.isfile("badPrescale_163581_163869.json"):
            options.BADRUNS.append("badPrescale_163581_163869.json")
            print "Using default file 'badPrescale_163581_163869.json'"
        else:
            print "Will remove no BAD RUNS"
        print

    else:
        for i in (options.BADRUNS):
            if not os.path.isfile(i):
                options.BADRUNS.remove(i)
                try:
                    temp=string.split(i,"-")
                    if len(temp)==1:
                        temp=string.atoi(string.strip(temp[0]))
                        excludeRuns["%s"%temp]="Exclude run %i"%temp
                    elif len(temp)==2:
                        startrun=string.atoi(string.strip(temp[0]))
                        endrun=string.atoi(string.strip(temp[1]))
                        
                        for z in range(startrun,endrun+1):
                            excludeRuns["%s"%z]="Exclude run %i"%z
                except:
                    print "ERROR!  BAD RUNS file '%s' does not exist!"%i

    if (options.diff==False):
        CleanJson(options.inputjson,
                  options.badjson,
                  options.BADRUNS,
                  excludeRuns,
                  options.outputjson,
                  options.startrun,
                  options.endrun)        

    CompareOutput(options.inputjson,
                  options.outputjson)
