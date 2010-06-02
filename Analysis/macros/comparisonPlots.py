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

# arguments
bg='Coll10_Promptv9_v7'
mc='May6th_gluino_1jet_336_300_100_2'
data=''

bg=args[0]
if (len(args)>1):
    mc=args[1]
if (len(args)>2):
    data=args[2]

sys.argv.append('-b')

from ROOT import *

from style import *
from plots import *

# set the style
tdrStyle()
gROOT.SetStyle("tdrStyle")
gROOT.ForceStyle()

# style options for this macro
#gStyle.SetHistFillStyle(0)

# open files
fdata=0
if (data != ''):
    fdata = TFile(data+"/histograms.root")
fbg=0
if (bg != ''):
    fbg   = TFile(bg+"/histograms.root")
fmc=0
if (mc != ''):
    fmc = TFile(mc+"/histograms.root")

# output file
ofilename="comparison_"+bg+"_"+mc+"_"+data
canvas = TCanvas("canvas")
canvas.Print(ofilename+".ps[")

# offline jets
compPlot("NoCuts/hjete", fdata, fbg, fmc, ofilename+".ps", True, True, "", "E (GeV)", "")
compPlot("NoCuts/hjeteta", fdata, fbg, fmc, ofilename+".ps", True, True, "", "#eta", "")
compPlot("NoCuts/hjetphi", fdata, fbg, fmc, ofilename+".ps", True, True, "", "#phi", "")
compPlot("NoCuts/hjeteem", fdata, fbg, fmc, ofilename+".ps", True, True, "", "E_{ECAL} / GeV", "")
compPlot("NoCuts/hjetehad", fdata, fbg, fmc, ofilename+".ps", True, True, "", "E_{HCAL} / GeV", "")
compPlot("NoCuts/hjetn60", fdata, fbg, fmc, ofilename+".ps", True, True, "", "n60", "")
compPlot("NoCuts/hjetn90", fdata, fbg, fmc, ofilename+".ps", True, True, "", "n90", "")
compPlot("NoCuts/hnmu", fdata, fbg, fmc, ofilename+".ps", True, True, "", "N_{#mu}", "")
compPlot("NoCuts/hntowsameiphi", fdata, fbg, fmc, ofilename+".ps", True, True, "", "N_{#mu}", "")
compPlot("NoCuts/hr1", fdata, fbg, fmc, ofilename+".ps", True, True, "", "R1", "")
compPlot("NoCuts/hr2", fdata, fbg, fmc, ofilename+".ps", True, True, "", "R2", "")
compPlot("NoCuts/hrpk", fdata, fbg, fmc, ofilename+".ps", True, True, "", "R_{peak}", "")
compPlot("NoCuts/hrout", fdata, fbg, fmc, ofilename+".ps", True, True, "", "R_{outer}", "")
compPlot("NoCuts/hjetemf", fdata, fbg, fmc, ofilename+".ps", True, True, "", "EM fraction", "")

compPlot("Cuts/hncutcum", fdata, fbg, fmc, ofilename+".ps", True, True, "", "Cut", "Counts")

compPlot("Cuts/hjete_nmo", fdata, fbg, fmc, ofilename+".ps", True, True, "", "E (GeV)", "")
compPlot("Cuts/hjetn60_nmo", fdata, fbg, fmc, ofilename+".ps", True, True, "", "n60", "")
compPlot("Cuts/hjetn90_nmo", fdata, fbg, fmc, ofilename+".ps", True, True, "", "n90", "")
compPlot("Cuts/hnmu_nmo", fdata, fbg, fmc, ofilename+".ps", True, True, "", "N_{#mu}", "")
compPlot("Cuts/hntowsameiphi_nmo", fdata, fbg, fmc, ofilename+".ps", True, True, "", "N_{#mu}", "")
compPlot("Cuts/hr1_nmo", fdata, fbg, fmc, ofilename+".ps", True, True, "", "R1", "")
compPlot("Cuts/hr2_nmo", fdata, fbg, fmc, ofilename+".ps", True, True, "", "R2", "")
compPlot("Cuts/hrpk_nmo", fdata, fbg, fmc, ofilename+".ps", True, True, "", "R_{peak}", "")
compPlot("Cuts/hrout_nmo", fdata, fbg, fmc, ofilename+".ps", True, True, "", "R_{outer}", "")
compPlot("Cuts/hjetemf_nmo", fdata, fbg, fmc, ofilename+".ps", True, True, "", "E (GeV)", "", 1.E-4)

canvas = TCanvas("canvas")
canvas.Print(ofilename+".ps]")

# convert to PDF
subprocess.call(["ps2pdf", ofilename+".ps", ofilename+".pdf"])
subprocess.call(["rm", ofilename+".ps"])







