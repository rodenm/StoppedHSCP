#! /usr/bin/env python

import sys
import os
import subprocess

from ROOT import *

from style import *

from plots import *

# argumentw
# comparisonPlots.py [data] [CRAFT09] [MC]
if len(sys.argv)!=5 :
    print "Wrong number of arguments"
    print "Usage : comparisonPlots.py <data dir> <craft dir> <mc dir> <out file>"
    sys.exit(1)

data=sys.argv[1]
craft=sys.argv[2]
mc=sys.argv[3]
outfile=sys.argv[4]


# set the style
tdrStyle()
gROOT.SetStyle("tdrStyle")
gROOT.ForceStyle()

# style options for this macro
gStyle.SetHistFillStyle(0)

# open files
fdata = TFile(data+"/"+data+"_Histos.root")
fcraft = TFile(craft+"/"+craft+"_Histos.root")
fmc = TFile(mc+"/"+mc+"_Histos.root")


# output file
ps = TPostScript(outfile+".ps")

# make plots
canvas = TCanvas("canvas")
canvas.SetLogy()

# offline jets
compPlot("NoCuts/hjete2", fdata, fcraft, fmc, canvas, True, True, "", "E (GeV)", "")
compPlot("NoCuts/hjeteta", fdata, fcraft, fmc, canvas, True, True, "", "#eta", "")
compPlot("NoCuts/hjetphi", fdata, fcraft, fmc, canvas, True, True, "", "#phi", "")
compPlot("NoCuts/hjetem", fdata, fcraft, fmc, canvas, True, True, "", "E_{ECAL} / GeV", "")
compPlot("NoCuts/hjethad", fdata, fcraft, fmc, canvas, True, True, "", "E_{HCAL} / GeV", "")
compPlot("NoCuts/hjetn60", fdata, fcraft, fmc, canvas, True, True, "", "n60", "")
compPlot("NoCuts/hjetn90", fdata, fcraft, fmc, canvas, True, True, "", "n90", "")
compPlot("NoCuts/hnmu", fdata, fcraft, fmc, canvas, True, True, "", "N_{#mu}", "")

compPlot("NoCuts/hntowsamephi", fdata, fcraft, fmc, canvas, True, True, "", "N_{#mu}", "")

compPlot("EffPlots/heffjete", fdata, fcraft, fmc, canvas, True, True, "", "E (GeV)", "")
compPlot("EffPlots/heffjetn60", fdata, fcraft, fmc, canvas, True, True, "", "n60", "")
compPlot("EffPlots/heffjetn90", fdata, fcraft, fmc, canvas, True, True, "", "n90", "")
compPlot("EffPlots/heffnmu", fdata, fcraft, fmc, canvas, True, False, "", "N_{#mu}", "")


compPlot("NoCuts/hr1", fdata, fcraft, fmc, canvas, True, True, "", "R1", "")
compPlot("NoCuts/hr2", fdata, fcraft, fmc, canvas, True, True, "", "R2", "")
compPlot("NoCuts/hpk", fdata, fcraft, fmc, canvas, True, True, "", "R_{peak}", "")
compPlot("NoCuts/hout", fdata, fcraft, fmc, canvas, True, True, "", "R_{outer}", "")

compPlot("AllCuts/hjete", fdata, fcraft, fmc, canvas, True, True, "", "E (GeV)", "")
compPlot("AllCuts/hjete2", fdata, fcraft, fmc, canvas, True, True, "", "E (GeV)", "")

ps.Close()

# convert to PDF
subprocess.call(["ps2pdf", outfile+".ps", outfile+".pdf"])

exit(1)






