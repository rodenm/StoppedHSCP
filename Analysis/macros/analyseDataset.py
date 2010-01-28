#! /usr/bin/env python

# analyse a dataset
#  - produce histograms
#  - make plots

import sys
import os
import subprocess
import tarfile

from ROOT import *

from style import *
from makeHistos import *
from makePlots import *
from cuts import *

# arguments : file location and local dir for results
if len(sys.argv)!=4 :
    print "Wrong number of arguments"
    print "Usage : python analyseDataset.py <input file> <output dir> <time>"
    sys.exit(1)

filename=sys.argv[1]
dir=sys.argv[2]
time=int(sys.argv[3])

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
#oldtree = ifile.Get("an_HLT/EventTree")
oldtree = ifile.Get("globalRunAnalyser/EventTree")
tree.AddFriend(oldtree)

# run analysis
cuts = CutsOld()

# make histograms
makeHistos(tree, odir+"/"+dir+"_BasicHistos.root", cuts)

# make plots (with normalisation if chosen)
if (time==0):
    scale=1
else:
    scale=1./time

makePlots(odir+"/"+dir+"_BasicHistos.root", odir+"/"+dir+"_BasicPlots.ps", scale)

# convert to PDF
subprocess.call(["ps2pdf", odir+"/"+dir+"_BasicPlots.ps", odir+"/"+dir+"_BasicPlots.pdf"])


tar = tarfile.open(name = odir+".tgz", mode = 'w:gz')
tar.add(dir)

#for file in os.listdir(odir):
#	t.add(file);
tar.close()


