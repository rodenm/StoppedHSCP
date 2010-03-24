#! /usr/bin/env python

# analyse a dataset
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
    print "Usage : python analyseDataset.py <input file> <output dir> <run file>"
    sys.exit(1)

filename=args[0]
dir=args[1]
rfilename=args[2]

# make dir to store results if not present
odir = os.getcwd()+"/"+dir
print "Putting results in "+odir
if not os.path.exists(odir):
    os.makedirs(odir)

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

# get run list
rfile = TFile(rfilename)
runtree = rfile.Get("StoppedHSCPRunTree")

# print info
printInfo(tree, runtree, oldcuts)

# make histograms for dataset
datasetHistos(tree, odir+"/"+dir, oldcuts, runtree)
makePlots(odir+"/"+dir, true)

# make run histos
for run in getRuns(runtree):
    print "Making histograms for run "+str(run)
    runHistos(tree, odir+"/"+dir, oldcuts, runtree, run)
    makePlots(odir+"/"+dir+"-"+str(run), false)


# clean up
#subprocess.call(["rm", odir+"/"+"*.ps"])

tar = tarfile.open(name = odir+".tgz", mode = 'w:gz')
tar.add(dir)

#for file in os.listdir(odir):
#	t.add(file);
tar.close()

