
#! /usr/bin/env python

#
# Summary of BX distributions
#

import sys
import optparse
import string
import os

# options
parser = optparse.OptionParser()
parser.add_option("-d", "--dir", action="store")

(opts, args)=parser.parse_args()

dataset=opts.dir

# ROOT stupidity
sys.argv=[]
sys.argv.append('-b')

from ROOT import *
from math import *
from style import *
from plots import *

TH1.SetDefaultSumw2

# set style
tdrStyle()
gROOT.SetStyle("tdrStyle")
gROOT.ForceStyle()

# output file
ofile = dataset+"/"+dataset+"_bxSummary.ps"
opdf = dataset+"/"+dataset+"_bxSummary.pdf"

# prepare canvas for plotting
canvas = TCanvas("c")
canvas.SetLogy(1)
canvas.Print(ofile+"[", "Portrait")

# open file
ifile1 = TFile(dataset+"/histograms.root", "read")
ifile2 = TFile(dataset+"/BXDistributions.root", "read")


# baseline summary plots
collBaseNorm = ifile2.Get("hCollBaseRateNorm")
collMinusOneNorm = ifile2.Get("hCollMinusOneRateNorm")
upBaseNorm = ifile2.Get("hUPBaseRateNorm")
upMinusOneNorm = ifile2.Get("hUPMinusOneRateNorm")
time = ifile1.Get("fills/hfilltime")

# set errors properly
for bin in range(1,time.GetNbinsX()+1):
    collBaseNorm.SetBinError(bin,0)
    collMinusOneNorm.SetBinError(bin,0)
    upBaseNorm.SetBinError(bin,0)
    upMinusOneNorm.SetBinError(bin,0)
    time.SetBinError(bin,0)


# collision base rates
collBaseSumm = ifile2.Get("hCollBaseRate")
collBaseSumm.Divide(collBaseNorm)
collBaseSumm.Divide(time)
collBaseSumm.Draw()
canvas.Print(ofile)

collBaseHalo = ifile2.Get("hCollBaseRateHalo")
collBaseHalo.Divide(collBaseNorm)
collBaseHalo.Divide(time)
collBaseHalo.Draw()
canvas.Print(ofile)

collBaseBG = ifile2.Get("hCollBaseRateBeamgas")
collBaseBG.Divide(collBaseNorm)
collBaseBG.Divide(time)
collBaseBG.Draw()
canvas.Print(ofile)

collBaseCosm = ifile2.Get("hCollBaseRateCosmic")
collBaseCosm.Divide(collBaseNorm)
collBaseCosm.Divide(time)
collBaseCosm.Draw()
canvas.Print(ofile)

collBaseNoise = ifile2.Get("hCollBaseRateNoise")
collBaseNoise.Divide(collBaseNorm)
collBaseNoise.Divide(time)
collBaseNoise.Draw()
canvas.Print(ofile)

collBaseNoID = ifile2.Get("hCollBaseRateNoID")
collBaseNoID.Divide(collBaseNorm)
collBaseNoID.Divide(time)
collBaseNoID.Draw()
canvas.Print(ofile)

# collision BX-1 rates
collMinusOneSumm = ifile2.Get("hCollMinusOneRate")
collMinusOneSumm.Divide(collMinusOneNorm)
collMinusOneSumm.Divide(time)
collMinusOneSumm.Draw()
canvas.Print(ofile)

collMinusOneHalo = ifile2.Get("hCollMinusOneRateHalo")
collMinusOneHalo.Divide(collMinusOneNorm)
collMinusOneHalo.Divide(time)
collMinusOneHalo.Draw()
canvas.Print(ofile)

collMinusOneBG = ifile2.Get("hCollMinusOneRateBeamgas")
collMinusOneBG.Divide(collMinusOneNorm)
collMinusOneBG.Divide(time)
collMinusOneBG.Draw()
canvas.Print(ofile)

collMinusOneCosm = ifile2.Get("hCollMinusOneRateCosmic")
collMinusOneCosm.Divide(collMinusOneNorm)
collMinusOneCosm.Divide(time)
collMinusOneCosm.Draw()
canvas.Print(ofile)

collMinusOneNoise = ifile2.Get("hCollMinusOneRateNoise")
collMinusOneNoise.Divide(collMinusOneNorm)
collMinusOneNoise.Divide(time)
collMinusOneNoise.Draw()
canvas.Print(ofile)

collMinusOneNoID = ifile2.Get("hCollMinusOneRateNoID")
collMinusOneNoID.Divide(collMinusOneNorm)
collMinusOneNoID.Divide(time)
collMinusOneNoID.Draw()
canvas.Print(ofile)

# unpaired bunch base rates
upBaseSumm = ifile2.Get("hUPBaseRate")
upBaseSumm.Divide(upBaseNorm)
upBaseSumm.Divide(time)
upBaseSumm.Draw()
canvas.Print(ofile)

upBaseHalo = ifile2.Get("hUPBaseRateHalo")
upBaseHalo.Divide(upBaseNorm)
upBaseHalo.Divide(time)
upBaseHalo.Draw()
canvas.Print(ofile)

upBaseBG = ifile2.Get("hUPBaseRateBeamgas")
upBaseBG.Divide(upBaseNorm)
upBaseBG.Divide(time)
upBaseBG.Draw()
canvas.Print(ofile)

upBaseCosm = ifile2.Get("hUPBaseRateCosmic")
upBaseCosm.Divide(upBaseNorm)
upBaseCosm.Divide(time)
upBaseCosm.Draw()
canvas.Print(ofile)

upBaseNoise = ifile2.Get("hUPBaseRateNoise")
upBaseNoise.Divide(upBaseNorm)
upBaseNoise.Divide(time)
upBaseNoise.Draw()
canvas.Print(ofile)

upBaseNoID = ifile2.Get("hUPBaseRateNoID")
upBaseNoID.Divide(upBaseNorm)
upBaseNoID.Divide(time)
upBaseNoID.Draw()
canvas.Print(ofile)

# unpaired bunch BX-1 rates
upMinusOneSumm = ifile2.Get("hUPMinusOneRate")
upMinusOneSumm.Divide(upMinusOneNorm)
upMinusOneSumm.Divide(time)
upMinusOneSumm.Draw()
canvas.Print(ofile)

upMinusOneHalo = ifile2.Get("hUPMinusOneRateHalo")
upMinusOneHalo.Divide(upMinusOneNorm)
upMinusOneHalo.Divide(time)
upMinusOneHalo.Draw()
canvas.Print(ofile)

upMinusOneBG = ifile2.Get("hUPMinusOneRateBeamgas")
upMinusOneBG.Divide(upMinusOneNorm)
upMinusOneBG.Divide(time)
upMinusOneBG.Draw()
canvas.Print(ofile)

upMinusOneCosm = ifile2.Get("hUPMinusOneRateCosmic")
upMinusOneCosm.Divide(upMinusOneNorm)
upMinusOneCosm.Divide(time)
upMinusOneCosm.Draw()
canvas.Print(ofile)

upMinusOneNoise = ifile2.Get("hUPMinusOneRateNoise")
upMinusOneNoise.Divide(upMinusOneNorm)
upMinusOneNoise.Divide(time)
upMinusOneNoise.Draw()
canvas.Print(ofile)

upMinusOneNoID = ifile2.Get("hUPMinusOneRateNoID")
upMinusOneNoID.Divide(upMinusOneNorm)
upMinusOneNoID.Divide(time)
upMinusOneNoID.Draw()
canvas.Print(ofile)



def correlationGraph(h1, h2, title, xtitle, ytitle):

    # get number of points
    n = h1.GetNbinsX()

    # create graph
    g = TGraphErrors(n)

    # loop over bins
    for i in range(1,n+1):

        # check we have the same fill in both histograms!
        if (h1.GetXaxis().GetBinLabel(i) != h1.GetXaxis().GetBinLabel(i)):
            print "Mismatching bin labels!", h1.GetXaxis().GetBinLabel(i), h1.GetXaxis().GetBinLabel(i)
        
        g.SetPoint(i-1, h1.GetBinContent(i), h2.GetBinContent(i))
        g.SetPointError(i-1, h1.GetBinError(i), h2.GetBinError(i))

    g.SetTitle(title)
    g.GetXaxis().SetTitle(xtitle)
    g.GetYaxis().SetTitle(ytitle)
    g.SetMarkerStyle(22)
    g.Draw("AP")
    canvas.Print(ofile)


print "Making correlation graphs"

canvas.SetLogy(0)

#sanity checks
correlationGraph(collBaseSumm, upBaseSumm, "All events (sanity check)", "Base_{coll} Rate", "Base_{upb} Rate")
correlationGraph(collMinusOneSumm, upMinusOneSumm, "All events", "BX-1_{coll} Rate", "BX-1_{upb} Rate")


# halo prediction
correlationGraph(collMinusOneHalo, collBaseHalo, "Halo", "BX-1_{coll} Rate", "Base_{coll} Rate")
correlationGraph(upMinusOneHalo,   collBaseHalo, "Halo", "BX-1_{upb} Rate", "Base_{coll} Rate")

# beamgas prediction
correlationGraph(collMinusOneBG, collBaseBG, "Beam-gas", "BX-1_{coll} Rate", "Base_{coll} Rate")
correlationGraph(upMinusOneBG,   collBaseBG, "Beam-gas", "BX-1_{upb} Rate", "Base_{coll} Rate")

# no ID check
correlationGraph(collBaseNoise, collBaseNoID, "Noise vs NoID", "Noise Base_{coll} Rate", "No ID Base_{coll} Rate")

# close file
canvas = TCanvas("c")
canvas.Print(ofile+"]")

# convert to PDF
subprocess.call(["ps2pdf", ofile, opdf])
subprocess.call(["rm", ofile])
