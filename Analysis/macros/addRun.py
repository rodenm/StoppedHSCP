#! /usr/bin/env python

#  - produce histograms
#  - make plots

import sys
import os
import getopt
import subprocess
import tarfile

from ROOT import *

from style import *
from histograms import *
from plots import *
from cuts import *
from analyseRun import *

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

if len(args) <1 :
    print "Wrong number of arguments"
    print "Usage : python analyseRun.py <run>"
    sys.exit(1)

# get list of runs
runlist=args[0].split(',')
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
subprocess.call(["hadd", "ntuples/allRuns.root "+mergestring])

dfile=TFile("ntuples/allRuns.root")
tree = dfile.Get("stoppedHSCPTree/StoppedHSCPTree")

# make plots of rate by run
allruns=getRuns(runtree)
nruns=len(allruns)

hltrate=TGraph(nruns)
jetmurate=TGraph(nruns)
allcutsrate=TGraph(nruns)

p=0
for r in getRuns(runtree):
    hltrate.SetPoint(p, r, getRate(tree, runtree, "", r))
    jetmurate.SetPoint(p, r, getRate(tree, runtree, oldcuts.jetMu, r))
    allcutsrate.SetPoint(p, r, getRate(tree, runtree, oldcuts.allCuts(), r))


hltrate.Draw()




