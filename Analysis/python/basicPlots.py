#! /usr/bin/env python

#
# Make plots from histograms.root
#

import sys
import getopt
import string
import os

# help message
def usage():
    print "Usage : makePlots.py [-hr] <input file> [runs]"    


# the main program
try:
    opts, args = getopt.getopt(sys.argv[1:], "hrb")
except getopt.GetoptError:
    usage();
    sys.exit(2)

if len(args) < 1 :
    print "Wrong number of arguments"
    usage();
    sys.exit(1)

# options
doRuns=False;
for opt, arg in opts:
    if opt=='-h':
        usage()
        exit.sys()
    if opt=='-r':
        doRuns=True;

# arguments
dataset=args[0]
while dataset.endswith("/"):  #remove any trailing '/'
    dataset=dataset[:-1]
runs=[]
if (len(args)>1):
    runlist=args[1].split(',')
    for i in range(0, len(runlist)):
        runs.append(int(runlist[i]))
        
sys.argv.append('-b')

from ROOT import *
from math import *
from style import *
from plots import *


# set style
tdrStyle()
gROOT.SetStyle("tdrStyle")
gROOT.ForceStyle()

# output file
ofile=os.path.join(dataset,"%s_basic.ps"%dataset)
opdf=os.path.join(dataset,"%s_basic.pdf"%dataset)

# prepare canvas for plotting
canvas = TCanvas("canvas")
canvas.Print(ofile+"[", "Portrait")

# open file
ifile = TFile(dataset+"/histograms.root", "read")
dir = ifile.Get("histograms/NoCuts")

# BX
histPlot("hbx", dir, ofile, 1., True, "", "BX", "")
histPlot("hrelbx", dir, ofile, 1., True, "", "BPTX", "")

# L1 trigger
histPlot("hl1bits", dir, ofile, 1., True, "", "L1 bit", "")
histPlot("hl1et", dir, ofile, 1., True, "", "E_{L1} (GeV)", "")
histPlot("hl1eta", dir, ofile, 1., True, "", "#eta", "")
histPlot("hl1phi", dir, ofile, 1., True, "", "#phi", "")

# HLT
histPlot("hhlte", dir, ofile, 1., True, "", "E_{HLT} (GeV)", "")
histPlot("hhlteta", dir, ofile, 1., True, "", "#eta", "")
histPlot("hhltphi", dir, ofile, 1., True, "", "#phi", "")

# global variables
histPlot("hntowsameiphi", dir, ofile, 1., True, "", "N_{towers}", "")

# jet variables
histPlot("hjete", dir, ofile, 1., True, "", "E (GeV)", "E")
histPlot("hjeteta", dir, ofile, 1., True, "", "#eta", "E")
histPlot("hjetphi", dir, ofile, 1., True, "", "#phi", "E")
histPlot("hjeteem", dir, ofile, 1., True, "", "E_{ECAL}", "E")
histPlot("hjetehad", dir, ofile, 1., True, "", "E_{HCAL}", "E")
histPlot("hjetemf", dir, ofile, 1., True, "", "EM fraction", "E")
histPlot("hjetn60", dir, ofile, 1., True, "", "n60", "E")
histPlot("hjetn90", dir, ofile, 1., True, "", "n90", "E")

# muon variables
histPlot("hnmu", dir, ofile, 1., True, "", "N_{#mu}", "")

# pulse shape variables
histPlot("hpksample", dir, ofile, 1., False, "", "Peak sample", "")
histPlot("hr1", dir, ofile, 1., False, "", "R1", "")
histPlot("hr2", dir, ofile, 1., False, "", "R2", "")
histPlot("hrpk", dir, ofile, 1., False, "", "R_{peak}", "")
histPlot("hrout", dir, ofile, 1., False, "", "R_{outer}", "")

# 2D timing plots
hist2DPlot("hr1r2", dir, ofile, 1., True, "", "R_{1}", "R_{2}", "", "COLZ")
hist2DPlot("hpkout", dir, ofile, 1., True, "", "R_{peak}", "R_{out}", "", "COLZ")

# cut plots
dir = ifile.Get("histograms/Cuts")
histPlot("hncutcum", dir, ofile, 1., True, "", "Cut", "N_{events}")
histPlot("hncutind", dir, ofile, 1., True, "", "Cut", "N_{events}")
histPlot("hnminus1cut", dir, ofile, 1., True, "", "Cut", "N_{events}")
histPlot("holdcutcum", dir, ofile, 1., True, "", "Cut", "N_{events}")
histPlot("holdcutind", dir, ofile, 1., True, "", "Cut", "N_{events}")

histPlot("hjete_nmo", dir, ofile, 1., False, "", "E (GeV)", "E")
histPlot("hjetn60_nmo", dir, ofile, 1., False, "", "n60", "E")
histPlot("hjetn90_nmo", dir, ofile, 1., False, "", "n90", "E")
histPlot("hnmu_nmo", dir, ofile, 1., False, "", "N_{#mu}", "")
histPlot("hr1_nmo", dir, ofile, 1., False, "", "R1", "")
histPlot("hr2_nmo", dir, ofile, 1., False, "", "R2", "")
histPlot("hrpk_nmo", dir, ofile, 1., False, "", "R_{peak}", "")
histPlot("hrout_nmo", dir, ofile, 1., False, "", "R_{outer}", "")

# final distributions
#multiPlot([ ifile.Get("histograms/NoCuts/hcoll"), ifile.Get("histograms/Cuts/hbx12")], ["collisions","events"], ofile, 0., 0., "Events after all cuts", "BX", "N", "", 2)
histPlot("hjete12", dir, ofile, 1., False, "Jet energy (after all cuts)", "E (GeV)", "E")
hist2DPlot("hjetetaphi12", dir, ofile, 1., False, "Jet pos (after all cuts)", "#eta", "#phi", "", "COLZ")

# close file
canvas = TCanvas("canvas")
canvas.Print(ofile+"]")

# convert to PDF
subprocess.call(["ps2pdf", ofile, opdf])
subprocess.call(["rm", ofile])

