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

if len(args) < 3 :
    print "Wrong number of arguments"
    usage();
    sys.exit(1)

# arguments
dataset=args[0]
firstFill = int(args[1])
lastFill  = int(args[2])
        
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
ofile = dataset+"/"+dataset+"_"+str(firstFill)+"_"+str(lastFill)+".ps"
opdf = dataset+"/"+dataset+"_"+str(firstFill)+"_"+str(lastFill)+".pdf"

# prepare canvas for plotting
canvas = TCanvas("canvas")
canvas.Print(ofile+"[", "Portrait")

# open file
ifile = TFile(dataset+"/histograms.root", "read")


# make plots
hbx    = TH1D("hbx", "BX", 3564, 0., 3564.)
hbunch = TH1D("hbunch", "BX", 3564, 0., 3564.)

for fill in range(firstFill, lastFill+1):

    hbxfill = ifile.Get("fills/"+str(fill)+"/hbxB"+str(fill))
    hbunchfill = ifile.Get("fills/"+str(fill)+"/hbunches"+str(fill))

    if (hbxfill):
        hbx.Add(hbxfill)
        hbx.Draw()

    if (hbunchfill):
        hbunch.Add(hbunchfill)
        hbunch.Draw()


multiPlot([hbunch, hbx], ["bunches","events"], ofile, 0., 0., "BX distribution", "BX", "N_{event}", "", 1, 0., 0.)



# close file
canvas = TCanvas("canvas")
canvas.Print(ofile+"]")

# convert to PDF
subprocess.call(["ps2pdf", ofile, opdf])
subprocess.call(["rm", ofile])

