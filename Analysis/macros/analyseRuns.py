#! /usr/bin/env python

# make histograms for a list of runs
# make summary plot of various quantities per run

import sys
import os
import getopt
import subprocess
import tarfile

sys.argv.append('-b')

from ROOT import *

from cuts import *
from basicDistributions import *
from efficiency import *
from distsByRun import *

def makeRunHistos(filebase, run, cutObj):
    print "Making histograms for run "+str(run)

    filename=filebase+"-"+str(run)
    hfile = TFile(filename+".root","recreate")

    c1 = TCut("run=="+str(run))

    basicHistos(tree, hfile, "NoCuts",  c1, 1.)
    #effHistos(tree, hfile, oldjmcuts, 1.)

    hfile.Close()


# make plots
def makeRunPlots(filebase, run):

    # open histo file
    filename=filebase+"-"+str(run)
    hfile = TFile(filename+".root","read")

    # make plot file
    canvas = TCanvas("canvas")
    canvas.Print(filename+".ps[", "Portrait")

    timePlots(hfile, filename+".ps")
    basicPlots(hfile, "NoCuts", 1., filename+".ps")
    #effPlots(hfile, filename+".ps")

    canvas = TCanvas("canvas")
    canvas.Print(filename+".ps]")

    subprocess.call(["ps2pdf", filename+".ps", filename+".pdf"])
    subprocess.call(["rm", filename+".ps"])


# arguments : file location and local dir for results
try:
    opts, args = getopt.getopt(sys.argv[1:], "ph")
except getopt.GetoptError:
    print "Usage : python analyseRuns.py [-hp] <input file> <label> <run list>"
    sys.exit(2)

if len(args) < 3 :
    print "Wrong number of arguments"
    print "Usage : python analyseRuns.py [-hp] <input file> <label> <run list>"
    sys.exit(1)

# options
doHistos=True
for opt, arg in opts:
    if opt=='-h':
        usage()
        exit.sys()
    if opt=='-p':
        doHistos=False

# arguments
filename=args[0]
label=args[1]
runlist=args[2].split(',')
runs=[]
for i in range(0, len(runlist)):
    runs.append(int(runlist[i]))

print "Analysing runs : ", runs

# make dir to store results
odir=makeOutputDir(label)

# open input file
ifile = TFile(filename)

# set the style
tdrStyle()
gROOT.SetStyle("tdrStyle")
gROOT.ForceStyle()


# get tree & add old tree as friend
tree = ifile.Get("stoppedHSCPTree/StoppedHSCPTree")
#oldtree = ifile.Get("globalRunAnalyser/EventTree")
#tree.AddFriend(oldtree)

# get run tree
#rfile = TFile(rfilename)
#runtree = rfile.Get("StoppedHSCPRunTree")

# cuts
cutObj = CutCollection(["jetE[0]>30.", \
                            "jetE[0]>50.", \
                            "jetnN60[0]<6", \
                            "jetnN90[0]>3", \
                            "mu_N==0", \
                            "top5DigiR1>0.15", \
                            "top5DigiR2>0.1 && top5DigiR2<0.5", \
                            "top5DigiRPeak>0.4 && top5DigiRPeak<0.7", \
                            "top5DigiROuter<0.10", \
                            "nTowerSameiPhi<5"])


# make run histos
filebase=odir+"/"+label
for run in runs:
    if (doHistos):
        makeRunHistos(filebase, run, cutObj)
    makeRunPlots(filebase, run)

# make "by run" histograms
if (doHistos):
    byRunHistos(tree, cutObj, runs, label)

byRunPlots(filebase)




