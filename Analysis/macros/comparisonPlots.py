#! /usr/bin/env python

import sys
import os

from ROOT import *

from style import *

from plots import *

# argumentw
# comparisonPlots.py [data] [CRAFT09] [MC]
if len(sys.argv)!=5 :
    print "Wrong number of arguments"
    print "Usage : comparisonPlots.py <data dir> <craft dir> <mc dir> <out file>"
    sys.exit(1)

datadir=sys.argv[1]
craftdir=sys.argv[2]
mcdir=sys.argv[3]
outfile=sys.argv[4]


# set the style
tdrStyle()
gROOT.SetStyle("tdrStyle")
gROOT.ForceStyle()

# style options for this macro

gStyle.SetHistFillStyle(0)

# open files
fdata = TFile(datadir+"/BasicHistos.root")
fcraft = TFile(craftdir+"/BasicHistos.root")
fmc = TFile(mcdir+"/BasicHistos.root")


# output file
ps = TPostScript(outfile)

# make plots
canvas = TCanvas("canvas")
canvas.SetLogy()

# offline jets
compPlot("hjete2", fdata, fcraft, fmc, canvas, True, True, "", "E (GeV)", "")
compPlot("hjeteta", fdata, fcraft, fmc, canvas, True, True, "", "#eta", "")
compPlot("hjetphi", fdata, fcraft, fmc, canvas, True, True, "", "#phi", "")
compPlot("hjetem", fdata, fcraft, fmc, canvas, True, True, "", "E_{ECAL} / GeV", "")
compPlot("hjethad", fdata, fcraft, fmc, canvas, True, True, "", "E_{HCAL} / GeV", "")
compPlot("hjetn60", fdata, fcraft, fmc, canvas, True, True, "", "n60", "")
compPlot("hjetn90", fdata, fcraft, fmc, canvas, True, True, "", "n90", "")
compPlot("hnmu", fdata, fcraft, fmc, canvas, True, True, "", "N_{#mu}", "")

compPlot("heffjete", fdata, fcraft, fmc, canvas, True, True, "", "E (GeV)", "")
compPlot("heffjetn60", fdata, fcraft, fmc, canvas, True, True, "", "n60", "")
compPlot("heffjetn90", fdata, fcraft, fmc, canvas, True, True, "", "n90", "")
compPlot("heffnmu", fdata, fcraft, fmc, canvas, True, True, "", "N_{#mu}", "")


compPlot("hr1", fdata, fcraft, fmc, canvas, True, True, "", "R1", "")
compPlot("hr2", fdata, fcraft, fmc, canvas, True, True, "", "R2", "")
compPlot("hpk", fdata, fcraft, fmc, canvas, True, True, "", "R_{peak}", "")
compPlot("hout", fdata, fcraft, fmc, canvas, True, True, "", "R_{outer}", "")

compPlot("hntowsamephi", fdata, fcraft, fmc, canvas, True, True, "", "N_{#mu}", "")


ps.Close()

exit(1)






