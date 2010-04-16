#! /usr/bin/env python

# analyse a dataset (ie. file containing multiple runs)
#

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
from rates import *
from monitorPlots import *



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


if len(args) < 3 :
    print "Wrong number of arguments"
    print "Usage : python analyseDataset.py <input file> <output dir> <run list>"
    sys.exit(1)

filename=args[0]
label=args[1]
#rfilename=args[2]

# get list of runs
runlist=args[2].split(',')
runs=[]
for i in range(0, len(runlist)):
    runs.append(int(runlist[i]))

# make dir to store results if not present
odir = makeOutputDir(label)

# open input file
ifile = TFile(filename)

# set the style
tdrStyle()
gROOT.SetStyle("tdrStyle")
gROOT.ForceStyle()

# get tree & add old tree as friend
tree = ifile.Get("stoppedHSCPTree/StoppedHSCPTree")
oldtree = ifile.Get("globalRunAnalyser/EventTree")
tree.AddFriend(oldtree)

# get run info
#rfile = TFile(rfilename)
#runtree = rfile.Get("StoppedHSCPRunTree")

# output files
filename=odir+"/"+label

# cuts
cutObj=oldcuts
c1 = TCut("")
for run in runs:
    c = TCut("run=="+str(run))
    c1 += c

c2 = TCut(cutObj.jetMu)
c2 += c1
c3 = TCut(cutObj.allCuts())
c3 += c1

# make histograms for dataset
print "Storing histograms in "+filename+".root"
hfile = TFile(filename+".root","recreate")
basicHistos(tree, hfile, "NoCuts",  c1, 1.)
basicHistos(tree, hfile, "JetMuCuts", c2, 1.)
basicHistos(tree, hfile, "AllCuts", c3, 1.)
effHistos(tree, hfile, oldjmcuts, 1.)
hfile.Close()

# make plots
hfile = TFile(filename+".root","read")
canvas = TCanvas("canvas")
canvas.Print(filename+".ps[", "Portrait")
basicPlots(hfile, "NoCuts", 1., filename+".ps")
basicPlots(hfile, "JetMuCuts", 1., filename+".ps")
basicPlots(hfile, "AllCuts", 1., filename+".ps")
effPlots(hfile, filename+".ps")
canvas = TCanvas("canvas")
canvas.Print(filename+".ps]")

# cconvert to PDF and delete original
subprocess.call(["ps2pdf", filename+".ps", filename+".pdf"])
subprocess.call(["rm", filename+".ps"])

# make tar ball
tar = tarfile.open(name = odir+".tgz", mode = 'w:gz')
tar.add(label)
tar.close()

