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


# write histo file
def makeBasicHistos(tree, filebase, cutObj, run):

    if (run!=0):
        filename=filebase+"-"+str(run)
        c1 = TCut("run=="+str(run))
    else:
        filename=filebase
        c1 = TCut("")

    print "Storing histograms in "+filename+".root"
    hfile = TFile(filename+".root","recreate")

    c2 = TCut(cutObj.jetMu)
    c2 += c1
    c3 = TCut(cutObj.allCuts())
    c3 += c1

    rateHistos(tree, hfile, oldcuts, run, 1.)
    basicHistos(tree, hfile, "NoCuts",  c1, 1.)
    basicHistos(tree, hfile, "JetMuCuts", c2, 1.)
    basicHistos(tree, hfile, "AllCuts", c3, 1.)
    effHistos(tree, hfile, oldjmcuts, 1.)

    hfile.Close()


def makeBasicPlots(filebase, run):

    if (run!=0):
        filename=filebase+"-"+str(run)
    else:
        filename=filebase

    hfile = TFile(filename+".root","read")

    # make plot file
    canvas = TCanvas("canvas")
#    ps = TPostScript(filename+".ps", 111)
    canvas.Print(filename+".ps[", "Portrait")

    if (run!=0):
        ratePlots(hfile, filename+".ps")

    basicPlots(hfile, "NoCuts", 1., filename+".ps")
    basicPlots(hfile, "JetMuCuts", 1., filename+".ps")
    basicPlots(hfile, "AllCuts", 1., filename+".ps")
    effPlots(hfile, filename+".ps")

    canvas = TCanvas("canvas")
    canvas.Print(filename+".ps]")

#    ps.Close()
    subprocess.call(["ps2pdf", filename+".ps", filename+".pdf"])
    subprocess.call(["rm", filename+".ps"])



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
label=args[1]
rfilename=args[2]

# make dir to store results if not present
odir = os.getcwd()+"/"+label
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

cutObj=oldcuts

# make histograms for dataset
filebase=odir+"/"+label

makeBasicHistos(tree, filebase, cutObj, 0)
makeBasicPlots(filebase, 0)

#runs=getRuns(runtree)
#runs=[110958, 110972, 110987, 111009, 111039]
runs = [124022, 124023, 124025, 124027, 124115, 124228, 124230]

# make run histos
for run in runs:
    print "Making histograms for run "+str(run)
    makeBasicHistos(tree, filebase, cutObj, run)
    makeBasicPlots(filebase, run)

# make "by run" plots
monitorPlots(tree, runs, label, runtree)

tar = tarfile.open(name = odir+".tgz", mode = 'w:gz')
tar.add(label)

#for file in os.listdir(odir):
#	t.add(file);
tar.close()

