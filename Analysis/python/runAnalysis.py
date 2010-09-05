#!/usr/bin/env python

import sys
import getopt
from subprocess import *

# run all steps of the analysis

try:
    opts, args = getopt.getopt(sys.argv[1:], "")
except getopt.GetoptError:
    sys.exit(2)

if len(args) < 1 :
    print "Specify dataset and fills to analyse"
    sys.exit(1)

dataset = args[0]
fillstr = args[1]

# convert fill list to runs list
filllist=fillstr.split(',')
print filllist
runs=''
ffile = open("StoppedHSCP/Analysis/data/fills.txt")
ffile.next()
for line in ffile:
    tokens=line.split()
    print tokens
    if (len(tokens)>2):
        if (filllist.count(tokens[0])>0):
            print tokens[0]
            rstrs=tokens[2].split(',')
            for r in rstrs:
                runs+=r+","

print runs


# make histograms
p1 = Popen("makeHistograms ntuples/stoppedHSCP_tree_"+dataset+".root "+dataset+" "+runs, shell=True)
p1.wait()

# make plots
p2 = Popen("python $CMSSW_BASE/src/StoppedHSCP/Analysis/python/makePlots.py "+dataset, shell=True)
p2.wait()
p3 = Popen("python $CMSSW_BASE/src/StoppedHSCP/Analysis/python/summary.py "+dataset, shell=True)
p3.wait()

# print summary
p4 = Popen("python $CMSSW_BASE/src/StoppedHSCP/Analysis/python/printSummary.py "+dataset+" > "+dataset+"/summary.txt", shell=True)
p4.wait()

# make Toy MC jobs
p5 = Popen("makeToyJobs.py "+dataset, shell=True)
p5.wait()
