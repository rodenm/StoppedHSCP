#! /usr/bin/env python

#
# Make per-run plots from histograms.root
#

import sys
import getopt
import string
import os

# help message
def usage():
    print "Usage : runPlots.py <input file>"    


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
while dataset.endswith("/"):  #remove any trailing '/'
    dataset=dataset[:-1]
    
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
ofile=os.path.join(dataset,"%s_runs.ps"%dataset)
opdf=os.path.join(dataset,"%s_runs.pdf"%dataset)

# prepare canvas for plotting
canvas = TCanvas("canvas")
canvas.Print(ofile+"[", "Portrait")

# open file
ifile = TFile(dataset+"/histograms.root", "read")


### TO DO ###



# close file
canvas = TCanvas("canvas")
canvas.Print(ofile+"]")

# convert to PDF
subprocess.call(["ps2pdf", ofile, opdf])
subprocess.call(["rm", ofile])

