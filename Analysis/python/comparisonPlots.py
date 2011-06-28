#! /usr/bin/env python

import sys
import os
import getopt
import subprocess

def usage():
    print "Usage : comparisonPlots.py [-h] <bg> <sig> <mc>"    

try:
    opts, args = getopt.getopt(sys.argv[1:], "hn")
except getopt.GetoptError:
    usage();
    sys.exit(2)

if len(args) < 1 :
    print "Wrong number of arguments"
    usage();
    sys.exit(1)

# options
doSig=True;
for opt, arg in opts:
    if opt=='-h':
        usage()
        exit.sys()
    if opt=='-n':
        doSig=False;

# ROOT
sys.argv.append('-b')

from ROOT import *

from style import *
from plots import *

# files
files=[]
for arg in args:
    files.append(TFile(arg))


# set the style
tdrStyle()
gROOT.SetStyle("tdrStyle")
gROOT.ForceStyle()

# output file
ofilename="comparisonPlots"
canvas = TCanvas("canvas")
canvas.Print(ofilename+".ps[")

def getHistograms(histname):
    hists=[]
    for file in files:
        hists.append(file.Get(histname))
    return hists

labels = ["Run2010A", "Signal MC"]

# raw distributions
## multiPlot(getHistograms("NoCuts/hjete"), labels, ofilename+".ps", 0, 0, "", "E (GeV)", "", 0) # "HIST", True, 1.e-4, 0.2)
## multiPlot(getHistograms("NoCuts/hjeteta"), labels, ofilename+".ps", 0, 0, "", "#eta", "", 0) #, "HIST", True, 5.e-3, 0.2)
## multiPlot(getHistograms("NoCuts/hjetphi"), labels, ofilename+".ps", 0, 0, "", "#phi", "", 0) #, "HIST", True, 2.e-3, 0.1)
## multiPlot(getHistograms("NoCuts/hjeteem"), labels, ofilename+".ps", 0, 0, "", "E_{ECAL} (GeV)", "", 0) #, "HIST", True, 1.e-4, 2.)
## multiPlot(getHistograms("NoCuts/hjetehad"), labels, ofilename+".ps", 0, 0, "", "E_{HCAL} (GeV)", "", 0) #, "HIST", True, 1.e-4, 0.5)
## multiPlot(getHistograms("NoCuts/hjetemf"), labels, ofilename+".ps", 0, 0, "", "jet EMF", "", 0) #, "HIST", True, 1.e-4, 2.)
## multiPlot(getHistograms("NoCuts/hjetn60"), labels, ofilename+".ps", 0, 0, "", "n_{60}", "", 0) #, "HIST", True, 1.e-3, 2.)
## multiPlot(getHistograms("NoCuts/hjetn90"), labels, ofilename+".ps", 0, 0, "", "n_{90}", "", 0) #, "HIST", True, 1.e-3, 2.)
## multiPlot(getHistograms("NoCuts/hnmu"), labels, ofilename+".ps", 0, 0, "", "n_{#mu}", "", 0) #, "HIST", True, 1.e-3, 2.)
## multiPlot(getHistograms("NoCuts/hntowsameiphi"), labels, ofilename+".ps", 0, 0, "", "N", "", 0) #, "HIST", True, 1.e-3, 2.)
multiPlot(getHistograms("histograms/NoCuts/hr1"), labels, ofilename+".ps", 0., 0., "", "R_{1}", "", 0) #, "HIST", True, 1.e-4, 2.)
multiPlot(getHistograms("histograms/NoCuts/hr2"), labels, ofilename+".ps", 0., 0., "", "R_{2}", "", 0) #, "HIST", True, 1.e-4, 2.)
multiPlot(getHistograms("histograms/NoCuts/hrpk"), labels, ofilename+".ps", 0., 0., "", "R_{peak}", "", 0) #, "HIST", True, 1.e-4, 2.)
multiPlot(getHistograms("histograms/NoCuts/hrout"), labels, ofilename+".ps", 0., 0., "", "R_{outer}", "", 0) #, "HIST", True, 1.e-4, 2.)

# cuts
multiPlot(getHistograms("histograms/Cuts/hncutcum"), labels, ofilename+".ps", 0., 0., "", "cut", "events", 2, 0., 0.) #, "HIST", True, 1.e-6, 0.5)

#def multiPlot(hists, labels, ofile, ymin=0., ymax=0., title="histogram", xtitle="", ytitle="", ztitle="", style=0, xmin=0., xmax=0.) :

multiPlot(getHistograms("histograms/Cuts/hjete_nmo"), labels, ofilename+".ps", 0., 0., "", "E (GeV)", "", 1, 0., 0.) #, "HIST", True, 1.e-4, 0.5)
multiPlot(getHistograms("histograms/Cuts/hjetn60_nmo"), labels, ofilename+".ps", 0., 0., "", "n_{60}", "", 1, 0., 0.) #, "HIST", True, 1.e-4, 2.)
multiPlot(getHistograms("histograms/Cuts/hjetn90_nmo"), labels, ofilename+".ps", 0., 0., "", "n_{90}", "", 1, 0., 0.) #, "HIST", True, 1.e-4, 2.)
multiPlot(getHistograms("histograms/Cuts/hnmu_nmo"), labels, ofilename+".ps", 0., 0., "", "n_{#mu}", "", 1, 0., 0.) #, "HIST", True, 1.e-4, 2.)
multiPlot(getHistograms("histograms/Cuts/hntowsameiphi_nmo"), labels, ofilename+".ps", 0., 0., "", "N", "", 1, 0., 0.) #, "HIST", True, 1.e-4, 2.)
multiPlot(getHistograms("histograms/Cuts/hiphifrac_nmo"), labels, ofilename+".ps", 0., 0., "", "N", "", 1, 0., 0.) #, "HIST", True, 1.e-4, 2.)
multiPlot(getHistograms("histograms/Cuts/hr1_nmo"), labels, ofilename+".ps", 0., 0., "", "R_{1}", "", 1, 0., 0.) #, "HIST", True, 1.e-4, 2.)
multiPlot(getHistograms("histograms/Cuts/hr2_nmo"), labels, ofilename+".ps", 0., 0., "", "R_{2}", "", 1, 0., 0.) #, "HIST", True, 1.e-4, 2.)
multiPlot(getHistograms("histograms/Cuts/hrpk_nmo"), labels, ofilename+".ps", 0., 0., "", "R_{peak}", "", 1, 0., 0.) #, "HIST", True, 1.e-4, 2.)
multiPlot(getHistograms("histograms/Cuts/hrout_nmo"), labels, ofilename+".ps", 0., 0., "", "R_{outer}", "", 1, 0., 0.) #, "HIST", True, 1.e-4, 2.)
#multiPlot(getHistograms("histograms/Cuts/hjetemf_nmo"), labels, ofilename+".ps", 0., 0., "", "jet EMF", "", 1, 0., 0.) #, "HIST", True, 1.e-4, 2.)

canvas = TCanvas("canvas")
canvas.Print(ofilename+".ps]")

# convert to PDF
subprocess.call(["ps2pdf", ofilename+".ps", ofilename+".pdf"])
subprocess.call(["rm", ofilename+".ps"])







