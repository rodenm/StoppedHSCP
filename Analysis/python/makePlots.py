#! /usr/bin/env python

#
# Make all plots from existing histogram files
# (Run makeHistograms to produce them!)
# Jim Brooke
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
filename=args[0]+"/histograms.root"
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


# make plots from a file
def plotsFromHistos(filename):

    print "Making plots for", filename
    
    file = TFile(filename, "read")
    
    # make plot file
    fileroot = filename.split('.')[0]
    canvas = TCanvas("canvas")
    canvas.Print(fileroot+".ps[", "Portrait")

    dir="All/NoCuts";

    # BX plots etc
    histPlot(dir+"/hbx", file, fileroot+".ps", 0., True, "", "BX", "N events")
    histPlot(dir+"/hlb", file, fileroot+".ps", 0., True, "", "LS", "Rate")
#    histPlot(dir+"/hlbdist", file, fileroot+".ps", 0., True, "", "Rate", "N LS")
    
    # L1 trigger
    histPlot(dir+"/hl1bits", file, fileroot+".ps", 1., True, "", "L1 bit", "")
    histPlot(dir+"/hl1et", file, fileroot+".ps", 1., True, "", "E_{L1} (GeV)", "")
    histPlot(dir+"/hl1eta", file, fileroot+".ps", 1., True, "", "#eta", "")
    histPlot(dir+"/hl1phi", file, fileroot+".ps", 1., True, "", "#phi", "")
    
    # HLT
    histPlot(dir+"/hhlte", file, fileroot+".ps", 1., True, "", "E_{HLT} (GeV)", "")
    histPlot(dir+"/hhlteta", file, fileroot+".ps", 1., True, "", "#eta", "")
    histPlot(dir+"/hhltphi", file, fileroot+".ps", 1., True, "", "#phi", "")

    # global variables
    histPlot(dir+"/hntowsameiphi", file, fileroot+".ps", 1., True, "", "N_{towers}", "")

    # jet variables
    histPlot(dir+"/hjete", file, fileroot+".ps", 1., True, "", "E (GeV)", "E")
    histPlot(dir+"/hjeteta", file, fileroot+".ps", 1., True, "", "#eta", "E")
    histPlot(dir+"/hjetphi", file, fileroot+".ps", 1., True, "", "#phi", "E")
    histPlot(dir+"/hjeteem", file, fileroot+".ps", 1., True, "", "E_{ECAL}", "E")
    histPlot(dir+"/hjetehad", file, fileroot+".ps", 1., True, "", "E_{HCAL}", "E")
    histPlot(dir+"/hjetemf", file, fileroot+".ps", 1., True, "", "EM fraction", "E")
    histPlot(dir+"/hjetn60", file, fileroot+".ps", 1., True, "", "n60", "E")
    histPlot(dir+"/hjetn90", file, fileroot+".ps", 1., True, "", "n90", "E")

    # muon variables
    histPlot(dir+"/hnmu", file, fileroot+".ps", 1., True, "", "N_{#mu}", "")

    # pulse shape variables
    histPlot(dir+"/hpksample", file, fileroot+".ps", 1., False, "", "Peak sample", "")
    histPlot(dir+"/hr1", file, fileroot+".ps", 1., False, "", "R1", "")
    histPlot(dir+"/hr2", file, fileroot+".ps", 1., False, "", "R2", "")
    histPlot(dir+"/hrpk", file, fileroot+".ps", 1., False, "", "R_{peak}", "")
    histPlot(dir+"/hrout", file, fileroot+".ps", 1., False, "", "R_{outer}", "")

    # 2D timing plots
    hist2DPlot(dir+"/hr1r2", file, fileroot+".ps", 1., True, "", "R_{1}", "R_{2}", "", "COLZ")
    hist2DPlot(dir+"/hpkout", file, fileroot+".ps", 1., True, "", "R_{peak}", "R_{out}", "", "COLZ")

    # pulse shape variables after jet/mu cuts
    dir = "All/Cuts"
    histPlot(dir+"/hr1_jetmu", file, fileroot+".ps", 1., False, "R_{1} after jet/mu cuts", "R_{1}", "")
    histPlot(dir+"/hr2_jetmu", file, fileroot+".ps", 1., False, "R_{2} after jet/mu cuts", "R_{2}", "")
    histPlot(dir+"/hrpk_jetmu", file, fileroot+".ps", 1., False, "R_{peak} after jet/mu cuts", "R_{peak}", "")
    histPlot(dir+"/hrout_jetmu", file, fileroot+".ps", 1., False, "R_{outer} after jet/mu cuts", "R_{outer}", "")
    hist2DPlot(dir+"/hr1r2_jetmu", file, fileroot+".ps", 1., True, "After jet/mu cuts", "R_{1}", "R_{2}", "", "COLZ")
    hist2DPlot(dir+"/hpkout_jetmu", file, fileroot+".ps", 1., True, "After jet/mu cuts", "R_{peak}", "R_{out}", "", "COLZ")


    # cut plots
    dir = "All/Cuts"
    histPlot(dir+"/hncutcum", file, fileroot+".ps", 1., True, "", "Cut", "N_{events}")
    histPlot(dir+"/hncutind", file, fileroot+".ps", 1., True, "", "Cut", "N_{events}")
    histPlot(dir+"/hnminus1cut", file, fileroot+".ps", 1., True, "", "Cut", "N_{events}")
    histPlot(dir+"/holdcutcum", file, fileroot+".ps", 1., True, "", "Cut", "N_{events}")
    histPlot(dir+"/holdcutind", file, fileroot+".ps", 1., True, "", "Cut", "N_{events}")

    histPlot(dir+"/hjete_nmo", file, fileroot+".ps", 1., False, "", "E (GeV)", "E")
    histPlot(dir+"/hjetn60_nmo", file, fileroot+".ps", 1., False, "", "n60", "E")
    histPlot(dir+"/hjetn90_nmo", file, fileroot+".ps", 1., False, "", "n90", "E")
    histPlot(dir+"/hnmu_nmo", file, fileroot+".ps", 1., False, "", "N_{#mu}", "")
    histPlot(dir+"/hr1_nmo", file, fileroot+".ps", 1., False, "", "R1", "")
    histPlot(dir+"/hr2_nmo", file, fileroot+".ps", 1., False, "", "R2", "")
    histPlot(dir+"/hrpk_nmo", file, fileroot+".ps", 1., False, "", "R_{peak}", "")
    histPlot(dir+"/hrout_nmo", file, fileroot+".ps", 1., False, "", "R_{outer}", "")
    histPlot(dir+"/hjetemf_nmo", file, fileroot+".ps", 1., False, "", "EM fraction", "E")


    canvas = TCanvas("canvas")
    canvas.Print(fileroot+".ps]")

    subprocess.call(["ps2pdf", fileroot+".ps", fileroot+".pdf"])
    subprocess.call(["rm", fileroot+".ps"])


# main program starts here

# set style
tdrStyle()
gROOT.SetStyle("tdrStyle")
gROOT.ForceStyle()


# make plots for all runs
plotsFromHistos(filename)


# loop over runs
if doRuns:

    # strip .root from filename
    fileroot = filename.split('.')[0]
    
    for run in runs:
        plotsFromHistos(fileroot+str(run)+".root")

