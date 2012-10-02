#! /usr/bin/env python

#
# halo ID efficiency from control samples
#

import sys
import optparse
import string
import os

# options
parser = optparse.OptionParser()
parser.add_option("-d", "--dir", action="store")
parser.add_option("-t", "--trigger", action="store_true")
#parser.add_option("-e", "--era", action="store")
#parser.add_option("-t", "--type", action="store", default="")

(opts, args)=parser.parse_args()


dataset=str(opts.dir)


# ROOT meh
sys.argv=[]
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
ofile = dataset+"/"+dataset+"_HaloEff.ps"
opdf = dataset+"/"+dataset+"_HaloEff.pdf"

# prepare canvas for plotting
canvas = TCanvas("c")
#canvas.SetLogy(1)
canvas.Print(ofile+"[", "Portrait")

# open file
ifile = TFile(dataset+"/HaloBackground.root", "read")
#cfile  = TFile(control+"/HaloBackground.root", "read")

# get histogram of time per fill
#hfilltime = ifile1.Get("fills/hfilltime")


# energy
htote = ifile.Get("hControlJetE")
htage = ifile.Get("hControlTaggedJetE")

htage.SetLineColor(2)
htage.SetMarkerColor(2)
htage.SetFillStyle(0)
htote.SetFillStyle(0)

canvas.SetLogy(1)
htote.Draw("")
htage.Draw("SAME")
canvas.Print(ofile)

canvas.SetLogy(0)

# eta
htoteta = ifile.Get("hControlJetEta")
htageta = ifile.Get("hControlTaggedJetEta")

htageta.SetLineColor(2)
htageta.SetMarkerColor(2)
htageta.SetFillStyle(0)

htoteta.Draw("")
htageta.Draw("SAME")
canvas.Print(ofile)

# phi
htotphi = ifile.Get("hControlJetPhi")
htagphi = ifile.Get("hControlTaggedJetPhi")

htagphi.SetLineColor(2)
htagphi.SetMarkerColor(2)
htagphi.SetFillStyle(0)

htotphi.Draw("")
htagphi.Draw("SAME")
canvas.Print(ofile)



# efficiency as fn of energy
effe = TEfficiency(htage, htote)
effe.Draw()
canvas.Print(ofile)


# efficiency as fn of eta
effeta = TEfficiency(htageta, htoteta)
effeta.Draw()
canvas.Print(ofile)


# efficiency as fn of phi
effphi = TEfficiency(htagphi, htotphi)
effphi.Draw()
canvas.Print(ofile)


# plots from control trigger
if (opts.trigger):

    # energy
    htote = ifile.Get("hControlTrigJetE")
    htage = ifile.Get("hControlTrigTaggedJetE")
    
    htage.SetLineColor(2)
    htage.SetMarkerColor(2)
    htage.SetFillStyle(0)
    htote.SetFillStyle(0)
    
    canvas.SetLogy(1)
    htote.Draw("")
    htage.Draw("SAME")
    canvas.Print(ofile)
    
    canvas.SetLogy(0)
    
    # eta
    htoteta = ifile.Get("hControlTrigJetEta")
    htageta = ifile.Get("hControlTrigTaggedJetEta")

    htageta.SetLineColor(2)
    htageta.SetMarkerColor(2)
    htageta.SetFillStyle(0)
    
    htoteta.Draw("")
    htageta.Draw("SAME")
    canvas.Print(ofile)
    
    # phi
    htotphi = ifile.Get("hControlTrigJetPhi")
    htagphi = ifile.Get("hControlTrigTaggedJetPhi")
    
    htagphi.SetLineColor(2)
    htagphi.SetMarkerColor(2)
    htagphi.SetFillStyle(0)
    
    htotphi.Draw("")
    htagphi.Draw("SAME")
    canvas.Print(ofile)

    # efficiency as fn of energy
    effe = TEfficiency(htage, htote)
    effe.Draw()
    canvas.Print(ofile)
    
    # efficiency as fn of eta
    effeta = TEfficiency(htageta, htoteta)
    effeta.Draw()
    canvas.Print(ofile)
    
    
    # efficiency as fn of phi
    effphi = TEfficiency(htagphi, htotphi) 
    effphi.Draw()
    canvas.Print(ofile)
    




# close file
canvas = TCanvas("c")
canvas.Print(ofile+"]")

# convert to PDF
subprocess.call(["ps2pdf", ofile, opdf])
subprocess.call(["rm", ofile])
