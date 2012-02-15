#!/usr/bin/env python


import sys,os,string


def GetRunsFromFills(fillfile):
    filldict={}
    tmp=open(fillfile,'r').readlines()
    for i in tmp:
        x=string.strip(i)
        x=string.split(x)
        try:
            fill=string.atoi(x[0])
        except:
            print "Cannot parse %s as a fill number!  Skipping line '%s'"%(x[0],i)
            continue
        runs=string.split(x[-1],",")
        runlist=[]
        for r in runs:
            runlist.append(string.atoi(r))
        filldict[fill]=runlist
    return filldict



if os.getenv("CMSSW_BASE")=="":
    print "Error!  Could not get CMSSW_BASE directory!"
    sys.exit()

fillfile=os.path.join(os.getenv("CMSSW_BASE"),"src/StoppedHSCP/Ntuples/data/fills.txt")
if not os.path.isfile(fillfile):
    print "ERROR!  Fill file %s does not exist"%fillfile
    sys.exit()

filldict=GetRunsFromFills(fillfile)

if len(sys.argv)<2:
    fills=raw_input("Enter (comma-separated) list of bad fills: ")
else:
    fills=sys.argv[1]
fills=string.split(fills,",")
print "List of bad runs is:\n"
print "(",
count=0
for f in fills:
    fill=string.atoi(f)
    if fill not in filldict.keys():
        print "\\ Warning!  Fill %s not in fills.txt!"%fill
    else:
        for r in filldict[fill]:
            print "(run==%i)"%r,
            if f != fills[-1]:
                print " || ",
            count=count+1
            if (count%4==0):
                print
print ")"
