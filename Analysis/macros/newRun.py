#! /usr/bin/env python

# CAF monitoring job
# for each run in argument list :
#  - make histograms
#  - merge tree with all runs processed so far


import sys
import os
import getopt
import subprocess
import tarfile
import shutil

sys.argv.append('-b')

from ROOT import *

from cuts import *
from rates import *
from basicDistributions import *
from efficiency import *
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

# get list of new runs
if len(args)>0:
    runlist=args[0].split(',')
else:
    runlist=[]
runs=[]
for i in range(0, len(runlist)):
    runs.append(int(runlist[i]))


# cuts
cutObj = oldcuts

# style
tdrStyle()
gROOT.SetStyle("tdrStyle")
gROOT.ForceStyle()

# make histos
mergestring=""
for run in runs:
    
    # prepare string for merge
    mergestring += treebase+str(run)+".root "

    # get tree
    dfile=TFile(treebase+str(run)+".root")
    tree = dfile.Get("stoppedHSCPTree/StoppedHSCPTree")
    oldtree = dfile.Get("globalRunAnalyser/EventTree")
    tree.AddFriend(oldtree)
    
    # make histograms
    filebase="plots/histos-"+str(run)
    hfile=TFile(filebase+".root", "recreate")

    rateHistos(tree, hfile, cutObj, run)
    basicHistos(tree, hfile, "NoCuts",  "", 1.)
    basicHistos(tree, hfile, "JetMuCuts", cutObj.jetMu, 1.)
    basicHistos(tree, hfile, "AllCuts", cutObj.allCuts(), 1.)
    effHistos(tree, hfile, cutObj, 1.)

    
    # make plots
    ps = TPostScript(filebase+".ps")

    ratePlots(hfile)

    ps.Close()

    subprocess.call(["ps2pdf", filebase+".ps", filebase+".pdf"])
    subprocess.call(["rm", filebase+".ps"])

    


# merge all files again
#if len(runs)>0:
#    subprocess.call(["hadd", "ntuples/allRuns.root "+mergestring])




# do analysis of all runs


# get run list
#rfile=TFile("ntuples/RunTree.root")    
#runtree = rfile.Get("StoppedHSCPRunTree")


#dfile=TFile("ntuples/allRuns.root")
#tree = dfile.Get("stoppedHSCPTree/StoppedHSCPTree")
#oldtree = dfile.Get("globalRunAnalyser/EventTree")
#tree.AddFriend(oldtree)

#monitorPlots(tree, runtree)


#shutil.copy2("plots/hltRate.png", "/afs/cern.ch/user/j/jbrooke/www/stoppedGluinos/hltRate.png")
#shutil.copy2("plots/jetmuRate.png", "/afs/cern.ch/user/j/jbrooke/www/stoppedGluinos/jetmuRate.png")
#shutil.copy2("plots/finalRate.png", "/afs/cern.ch/user/j/jbrooke/www/stoppedGluinos/finalRate.png")

