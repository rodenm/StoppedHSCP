#! /usr/bin/env python

import sys
import os
import getopt
import subprocess

def usage():
    print "Usage : comparisonPlots.py [-h] <background> <mc> <data>"    

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

# raw distributions
multiPlot2(getHistograms("NoCuts/hjete"), ofilename+".ps", True, True, "", "E (GeV)", "", "HIST", True, 1.e-4, 0.2)
multiPlot2(getHistograms("NoCuts/hjeteta"), ofilename+".ps", True, True, "", "#eta", "", "HIST", True, 5.e-3, 0.2)
multiPlot2(getHistograms("NoCuts/hjetphi"), ofilename+".ps", True, True, "", "#phi", "", "HIST", True, 2.e-3, 0.1)
multiPlot2(getHistograms("NoCuts/hjeteem"), ofilename+".ps", True, True, "", "E_{ECAL} (GeV)", "", "HIST", True, 1.e-4, 2.)
multiPlot2(getHistograms("NoCuts/hjetehad"), ofilename+".ps", True, True, "", "E_{HCAL} (GeV)", "", "HIST", True, 1.e-4, 0.5)
multiPlot2(getHistograms("NoCuts/hjetemf"), ofilename+".ps", True, True, "", "jet EMF", "", "HIST", True, 1.e-4, 2.)
multiPlot2(getHistograms("NoCuts/hjetn60"), ofilename+".ps", True, True, "", "n_{60}", "", "HIST", True, 1.e-3, 2.)
multiPlot2(getHistograms("NoCuts/hjetn90"), ofilename+".ps", True, True, "", "n_{90}", "", "HIST", True, 1.e-3, 2.)
multiPlot2(getHistograms("NoCuts/hnmu"), ofilename+".ps", True, True, "", "n_{#mu}", "", "HIST", True, 1.e-3, 2.)
multiPlot2(getHistograms("NoCuts/hntowsameiphi"), ofilename+".ps", True, True, "", "N", "", "HIST", True, 1.e-3, 2.)
multiPlot2(getHistograms("NoCuts/hr1"), ofilename+".ps", True, True, "", "R_1", "", "HIST", True, 1.e-4, 2.)
multiPlot2(getHistograms("NoCuts/hr2"), ofilename+".ps", True, True, "", "R_2", "", "HIST", True, 1.e-4, 2.)
multiPlot2(getHistograms("NoCuts/hrpk"), ofilename+".ps", True, True, "", "R_{peak}", "", "HIST", True, 1.e-4, 2.)
multiPlot2(getHistograms("NoCuts/hrout"), ofilename+".ps", True, True, "", "R_{outer}", "", "HIST", True, 1.e-4, 2.)

# cuts
multiPlot2(getHistograms("Cuts/hncutcum"), ofilename+".ps", True, True, "", "cut", "events", "HIST", True, 1.e-6, 0.5)

multiPlot2(getHistograms("Cuts/hjete_nmo"), ofilename+".ps", True, True, "", "E (GeV)", "", "HIST", True, 1.e-4, 0.5)
multiPlot2(getHistograms("Cuts/hjetn60_nmo"), ofilename+".ps", True, True, "", "n_{60}", "", "HIST", True, 1.e-4, 2.)
multiPlot2(getHistograms("Cuts/hjetn90_nmo"), ofilename+".ps", True, True, "", "n_{90}", "", "HIST", True, 1.e-4, 2.)
multiPlot2(getHistograms("Cuts/hnmu_nmo"), ofilename+".ps", True, True, "", "n_{#mu}", "", "HIST", True, 1.e-4, 2.)
multiPlot2(getHistograms("Cuts/hntowsameiphi_nmo"), ofilename+".ps", True, True, "", "N", "", "HIST", True, 1.e-4, 2.)
multiPlot2(getHistograms("Cuts/hr1_nmo"), ofilename+".ps", True, True, "", "R_1", "", "HIST", True, 1.e-4, 2.)
multiPlot2(getHistograms("Cuts/hr2_nmo"), ofilename+".ps", True, True, "", "R_2", "", "HIST", True, 1.e-4, 2.)
multiPlot2(getHistograms("Cuts/hrpk_nmo"), ofilename+".ps", True, True, "", "R_{peak}", "", "HIST", True, 1.e-4, 2.)
multiPlot2(getHistograms("Cuts/hrout_nmo"), ofilename+".ps", True, True, "", "R_{outer}", "", "HIST", True, 1.e-4, 2.)
multiPlot2(getHistograms("Cuts/hjetemf_nmo"), ofilename+".ps", True, True, "", "jet EMF", "", "HIST", True, 1.e-4, 2.)

canvas = TCanvas("canvas")
canvas.Print(ofilename+".ps]")

# convert to PDF
subprocess.call(["ps2pdf", ofilename+".ps", ofilename+".pdf"])
subprocess.call(["rm", ofilename+".ps"])







