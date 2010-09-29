
# make summary histograms

import sys
import getopt
import json
import math

from ROOT import *

from StoppedHSCP.Analysis.runHistos import *
from StoppedHSCP.Analysis.fillHistos import *


TH1.SetDefaultSumw2()

# arguments
try:
    opts, args = getopt.getopt(sys.argv[1:], "")
except getopt.GetoptError:
    sys.exit(2)

if len(args)<2:
    print "Insufficient arguments!"
    sys.exit(1)

jsonfile = args[2]
filllist = args[1]
dataset  = args[0]


# read JSON file to get list of runs/LS
jfile = open(jsonfile, 'r')

lsranges={}
for line in jfile:
    lsranges.update(json.loads(line))

runstrs = lsranges.keys()
runstrs.sort()

## how to get LS ranges if needed
## for runstr in runstrs:
##     last=lsranges[runstr][0]
##     for lsrange in lsranges[runstr]:
##         print runstr, lsrange[0], lsrange[1]
##         if (last[0]>lsrange[0]):
##             print "Found inconsistent LS range!"
##             sys.exit(1)

runs=[]
for runstr in runstrs:
    runs.append(int(runstr))


# convert fill list to ints
fills=[]
fillstrs = filllist.split(',')
for fstr in fillstrs:
    fills.append(int(fstr))

# read fills file
fillinfo=[]
ffile = open("StoppedHSCP/Analysis/data/fills.txt")
ffile.next()

for line in ffile:
    tokens=line.split()
    if (len(tokens)==3):
        rstrs=tokens[2].split(',')
        rs=[]
        for rstr in rstrs:
            rs.append(int(rstr))
        fillinfo.append([ int(tokens[0]), rs])
        



# open histogram file
hfile = TFile(dataset+"/histograms.root", "update")

runHistos(hfile, runs)

fillHistos(hfile, fills, fillinfo)


# close file
hfile.Close()

