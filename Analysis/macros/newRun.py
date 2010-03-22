#! /usr/bin/env python

#  - produce histograms
#  - make plots

import sys
import os
import getopt
import subprocess
import tarfile
import shutil

from ROOT import *

from style import *
from histograms import *
from plots import *
from cuts import *
from monitorPlots import *


# filenames
treebase="ntuples/minbias-"

# arguments : file location and local dir for results
try:
    opts, args = getopt.getopt(sys.argv[1:], "bh")
except getopt.GetoptError:
    usage()
    sys.exit(2)

for opt, arg in opts:
    if opt=='-h':
        usage()
        exit.sys()

#if len(args) <1 :
#    print "Wrong number of arguments"
#    print "Usage : python analyseRun.py <run>"
#    sys.exit(1)

# get list of runs
if len(args)>0:
    runlist=args[0].split(',')
else:
    runlist=[]
runs=[]
for i in range(0, len(runlist)):
    runs.append(int(runlist[i]))

# get run list
rfile=TFile("ntuples/RunTree.root")    
runtree = rfile.Get("StoppedHSCPRunTree")

mergestring=""

# make histos
for run in runs:
    runstr=str(run)
    
    # get tree
    dfile=TFile(treebase+runstr+".root")
    tree = dfile.Get("stoppedHSCPTree/StoppedHSCPTree")
    
    # make histograms
    hfilebase="plots/"
    runHistos(tree, hfilebase, oldcuts, runtree, run)

    mergestring += treebase+run+".root "


# merge all files again
if len(runs)>0:
    subprocess.call(["hadd", "ntuples/allRuns.root "+mergestring])

dfile=TFile("ntuples/allRuns.root")
tree = dfile.Get("stoppedHSCPTree/StoppedHSCPTree")
oldtree = dfile.Get("globalRunAnalyser/EventTree")
tree.AddFriend(oldtree)

monitorPlots(tree, runtree)


shutil.copy2("plots/hltRate.png", "/afs/cern.ch/user/j/jbrooke/www/stoppedGluinos/hltRate.png")
shutil.copy2("plots/jetmuRate.png", "/afs/cern.ch/user/j/jbrooke/www/stoppedGluinos/jetmuRate.png")
shutil.copy2("plots/finalRate.png", "/afs/cern.ch/user/j/jbrooke/www/stoppedGluinos/finalRate.png")

