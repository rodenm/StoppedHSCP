#! /usr/bin/env python

#
# Make per-fill plots from histograms.root
#

import sys
import getopt
import string
import os

# help message
def usage():
    print "Usage : fillPlots.py <input file>"    


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

# arguments
dataset=args[0]
        
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
ofile = dataset+"/"+dataset+"_fills.ps"
opdf = dataset+"/"+dataset+"_fills.pdf"

# prepare canvas for plotting
canvas = TCanvas("canvas")
canvas.Print(ofile+"[", "Portrait")

# open file
ifile = TFile(dataset+"/histograms.root", "read")


# make plots
dir = ifile.Get("fills")

htime=ifile.Get("fills/hfilltime")

hnm1_1=ifile.Get("fills/hfillnm1rate_1")
multiPlot([hnm1_1], [""], ofile, 0., 0., "N-1 rate - BPTX veto", "Fill", "Hz", "", 0, 0., 0.)

hnm1_2=ifile.Get("fills/hfillnm1rate_2")
multiPlot([hnm1_2], [""], ofile, 0., 0., "N-1 rate - BX veto", "Fill", "Hz", "", 0, 0., 0.)

hnm1_3=ifile.Get("fills/hfillnm1rate_3")
multiPlot([hnm1_3], [""], ofile, 0., 0., "N-1 rate - Vertex veto", "Fill", "Hz", "", 0, 0., 0.)

hnm1_4=ifile.Get("fills/hfillnm1rate_4")
multiPlot([hnm1_4], [""], ofile, 0., 0., "N-1 rate - halo veto", "Fill", "Hz", "", 0, 0., 0.)

hnm1_5=ifile.Get("fills/hfillnm1rate_5")
multiPlot([hnm1_5], [""], ofile, 0., 0., "N-1 rate - cosmic veto", "Fill", "Hz", "", 0, 0., 0.)

hnm1_6=ifile.Get("fills/hfillnm1rate_6")
multiPlot([hnm1_6], [""], ofile, 0., 0., "N-1 rate - noise veto", "Fill", "Hz", "", 0, 0., 0.)

hnm1_7=ifile.Get("fills/hfillnm1rate_7")
multiPlot([hnm1_7], [""], ofile, 0., 0., "N-1 rate - E30", "Fill", "Hz", "", 0, 0., 0.)

hnm1_8=ifile.Get("fills/hfillnm1rate_8")
multiPlot([hnm1_8], [""], ofile, 0., 0., "N-1 rate - E70", "Fill", "Hz", "", 0, 0., 0.)

hnm1_9=ifile.Get("fills/hfillnm1rate_9")
multiPlot([hnm1_9], [""], ofile, 0., 0., "N-1 rate - n60", "Fill", "Hz", "", 0, 0., 0.)

hnm1_10=ifile.Get("fills/hfillnm1rate_10")
multiPlot([hnm1_10], [""], ofile, 0., 0., "N-1 rate - n90", "Fill", "Hz", "", 0, 0., 0.)

hnm1_11=ifile.Get("fills/hfillnm1rate_11")
multiPlot([hnm1_11], [""], ofile, 0., 0., "N-1 rate - nTowIPhi", "Fill", "Hz", "", 0, 0., 0.)

hnm1_12=ifile.Get("fills/hfillnm1rate_12")
multiPlot([hnm1_12], [""], ofile, 0., 0., "N-1 rate - R1", "Fill", "Hz", "", 0, 0., 0.)

hnm1_13=ifile.Get("fills/hfillnm1rate_13")
multiPlot([hnm1_13], [""], ofile, 0., 0., "N-1 rate - R2", "Fill", "Hz", "", 0, 0., 0.)

hnm1_14=ifile.Get("fills/hfillnm1rate_14")
multiPlot([hnm1_14], [""], ofile, 0., 0., "N-1 rate - Rpeak", "Fill", "Hz", "", 0, 0., 0.)

hnm1_15=ifile.Get("fills/hfillnm1rate_15")
multiPlot([hnm1_15], [""], ofile, 0., 0., "N-1 rate - Router", "Fill", "Hz", "", 0, 0., 0.)



#histPlot("hfillnm1_1", dir, ofile, 1., False, 
#histPlot("hfillnm1_2", dir, ofile, 1., False, "N-1 rate - BX veto", "Fill", "Hz", "E P0")
#histPlot("hfillnm1_3", dir, ofile, 1., False, "N-1 rate - Vertex veto", "Fill", "Hz", "E P0")
#histPlot("hfillnm1_4", dir, ofile, 1., False, "N-1 rate - Halo veto", "Fill", "Hz", "E P0")
#histPlot("hfillnm1_5", dir, ofile, 1., False, "N-1 rate - Cosmic veto", "Fill", "Hz", "E P0")
#histPlot("hfillnm1_6", dir, ofile, 1., False, "N-1 rate - Noise veto", "Fill", "Hz", "E P0")
#histPlot("hfillnm1_7", dir, ofile, 1., False, "N-1 rate - E30", "Fill", "Hz", "E P0")
#histPlot("hfillnm1_8", dir, ofile, 1., False, "N-1 rate - E70", "Fill", "Hz", "E P0")
#histPlot("hfillnm1_9", dir, ofile, 1., False, "N-1 rate - n60", "Fill", "Hz", "E P0")
#histPlot("hfillnm1_10", dir, ofile, 1., False, "N-1 rate - n90", "Fill", "Hz", "E P0")
#histPlot("hfillnm1_11", dir, ofile, 1., False, "N-1 rate - nTowiPhi", "Fill", "Hz", "E P0")
#histPlot("hfillnm1_12", dir, ofile, 1., False, "N-1 rate - R1", "Fill", "Hz", "E P0")
#histPlot("hfillnm1_13", dir, ofile, 1., False, "N-1 rate - R2", "Fill", "Hz", "E P0")
#histPlot("hfillnm1_14", dir, ofile, 1., False, "N-1 rate - Rpeak", "Fill", "Hz", "E P0")
#histPlot("hfillnm1_15", dir, ofile, 1., False, "N-1 rate - Router", "Fill", "Hz", "E P0")

#(hists, labels, ofile, ymin=0., ymax=0., title="histogram", xtitle="", ytitle="", ztitle="", style=0, xmin=0., xmax=0.

# close file
canvas = TCanvas("canvas")
canvas.Print(ofile+"]")

# convert to PDF
subprocess.call(["ps2pdf", ofile, opdf])
subprocess.call(["rm", ofile])

