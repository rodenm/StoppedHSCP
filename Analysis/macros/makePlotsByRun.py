
# make plots of various quantities by run

import sys
import getopt
import subprocess
import os

def usage():
    print "Usage : python makePlotsByRun.py [-h] <input dir> <run list>"

# arguments : file location and local dir for results
try:
    opts, args = getopt.getopt(sys.argv[1:], "ch")
except getopt.GetoptError:
    usage()
    sys.exit(2)

if len(args) < 2 :
    print "Wrong number of arguments"
    usage()
    sys.exit(1)

# options
lumiBlockLength = 25.e-9 * 3564. * pow(2., 18)

for opt, arg in opts:
    if opt=='-h':
        usage()
        exit.sys()
    if opt=='-c':
        lumiBlockLength = 25.e-9 * 3564. * pow(2., 20)


# arguments
dir=args[0]
runlist=args[1].split(',')
runs=[]
for i in range(0, len(runlist)):
    runs.append(int(runlist[i]))

# ROOT
sys.argv.append('-b')

from ROOT import *
from math import *

from style import *
from plots import *

def histByRun(name, title, nruns):
    h = TH1D(name, title, nruns, 0, 0)
    h.Sumw2()
    return h

def hist2DByRun(name, title, nruns, ylabel, ny, ymin, ymax):
    h = TH2D(name, title, nruns, 0, nruns, ny, ymin, ymax)
    h.Sumw2()
    return h

def getNLumiBlocks(hist) :
    n=0
    for i in range(0,hist.GetNbinsX()):
        if (hist.GetBinContent(i) > 0.):
            n=n+1
    return n

def getLivetime2(hist) :
    return getNLumiBlocks(hist) * lumiBlockLength

# main program starts here

# open ROOT file
file = TFile(dir+"/histograms.root")

# create histograms
nruns=len(runs)
hnhlt       = histByRun("hnhlt", "HLT counts", nruns)
hnfin       = histByRun("hnfin", "Final counts", nruns)
hefftime    = histByRun("hefftime", "Effective live time", nruns)
hnlb        = histByRun("hnlb", "N lumi blocks", nruns)
hlivetime   = histByRun("hlivetime", "Live time", nruns)
hnpostjet   = histByRun("hnpostjet", "N events after jet cuts", nruns)
hnposttim   = histByRun("hnposttim", "N events after timing cuts", nruns)

# rate after each cut
hratecuts = []
for c in range(0,13):
    hratecuts.append(histByRun("hratecut"+str(c), "Rate cut "+str(c), nruns))

# 2D vs run plots
hbx      = hist2DByRun("hbx", "BX vs Run", nruns, "BX", 3564, 0., 3564.)
heta     = hist2DByRun("heta", "#eta vs Run", nruns, "#eta", 70, -3.5, 3.5)
hphi     = hist2DByRun("hphi", "#phi vs Run", nruns, "#phi", 72, -1. * pi, 1. * pi)

hbxfin   = hist2DByRun("hbxfin", "BX vs Run", nruns, "BX", 3564, 0., 3564.)
hetafin  = hist2DByRun("hetafin", "#eta vs Run", nruns, "#eta", 70, -3.5, 3.5)
hphifin  = hist2DByRun("hphifin", "#phi vs Run", nruns, "#phi", 72, -1. * pi, 1. * pi)

    
# fill histograms from "rate per LS" fits
i=0
for run in runs:

    print run
    runstr=str(run)
    
    # HLT counts
    hlb=file.Get(runstr+"/NoCuts/hlb")
    nhlt=hlb.GetEntries()
    hnhlt.Fill(str(run), nhlt)
    hnhlt.SetBinError(i+1, sqrt(nhlt))

    # effective time (HLT rate / nevents)
    #    efftime=0.
    #    if (hltrate[0] > 0.):
    #        efftime = nhlt / hltrate[0]
    #    hefftime.Fill(str(run), efftime)
    #    hefftime.SetBinError(i+1, 10.)
    
    nlb = getNLumiBlocks(hlb)
    hnlb.Fill(str(run), nlb)

    # live time (N non-zero LS after HLT)
    livetime = getLivetime2(hlb)
    hlivetime.Fill(str(run), livetime)
    hlivetime.SetBinError(i+1, 10.)

    hcutcount = file.Get(runstr+"/Cuts/hncutcum")

    # final counts
    nevtFinal = hcutcount.GetBinContent(12)
    hnfin.Fill(str(run), nevtFinal)
    hnfin.SetBinError(i+1, sqrt(nevtFinal))

    # post jet counst
    npostjet = hcutcount.GetBinContent(7)
    hnpostjet.Fill(str(run), npostjet)
    hnpostjet.SetBinError(i+1, sqrt(npostjet))

    # post timing counts
    nposttim = hcutcount.GetBinContent(7)
    hnposttim.Fill(str(run), nposttim)
    hnposttim.SetBinError(i+1, sqrt(nposttim))
    
    # rate after N cuts
    cut = TCut("")
    
    for c in range(0, 13):
        n=hcutcount.GetBinContent(c+1)
        rate=0.
        erate=0.
        if (livetime>0.):
            rate=n/livetime
            erate=sqrt(n)/livetime
        hratecuts[c].Fill(str(run), rate)
        hratecuts[c].SetBinError(i+1, erate)

    # BX vs run
    hbx0=file.Get(runstr+"/Cuts/hbx0")
    for j in range(0,3564):
        hbx.Fill(str(run), j, hbx0.GetBinContent(j+1))

    # eta/phi vs run
    hetaphi0=file.Get(runstr+"/Cuts/hjetetaphi0")
    heta0=hetaphi0.ProjectionX()
    for j in range(1,heta0.GetNbinsX()):
        heta.Fill(str(run), heta0.GetBinCenter(j), heta0.GetBinContent(j))

    hphi0=hetaphi0.ProjectionY()
    for j in range(0,hphi0.GetNbinsX()):
        hphi.Fill(str(run), hphi0.GetBinCenter(j), hphi0.GetBinContent(j))

    # BX vs run (after all cuts)
    hbx11=file.Get(runstr+"/Cuts/hbx11")
    for j in range(0,3564):
        hbxfin.Fill(str(run), j, hbx11.GetBinContent(j+1))

    # eta/phi vs run (after all cuts)
    hetaphi11=file.Get(runstr+"/Cuts/hjetetaphi11")
    heta11=hetaphi11.ProjectionX()
    for j in range(1,heta11.GetNbinsX()):
        hetafin.Fill(str(run), heta11.GetBinCenter(j), heta11.GetBinContent(j))

    hphi11=hetaphi11.ProjectionY()
    for j in range(0,hphi11.GetNbinsX()):
        hphifin.Fill(str(run), hphi11.GetBinCenter(j), hphi11.GetBinContent(j))

    
    i=i+1


# write ROOT file
ofile = TFile(dir+"/"+dir+"_byRun.root", "recreate")
hnhlt.Write()
hefftime.Write()
hlivetime.Write()
hnlb.Write()
hnfin.Write()
for i in range(0,13):
    hratecuts[i].Write()
hbx.Write()
hbxfin.Write()
heta.Write()
hetafin.Write()
hphi.Write()
hphifin.Write()
ofile.Close()
    

# draw plots
tdrStyle()
gROOT.SetStyle("tdrStyle")
gROOT.ForceStyle()


file=TFile(dir+"/"+dir+"_byRun.root", "read")

filebase=dir+"/"+dir

# PS file
canvas = TCanvas("canvas")
canvas.Print(filebase+"_byRun.ps[", "Portrait")

# n counts, livetime etc.
multiPlot([ "hnhlt" ],file, filebase+"_byRun.ps", False, True, 0., 0., "HLT counts", "run", "events", "E P1")
multiPlot([ "hnlb" ],file, filebase+"_byRun.ps", False, False, 0., 0., "N LS", "run", "s", "E P1")
multiPlot([ "hlivetime" ],file, filebase+"_byRun.ps", False, False, 0., 0., "time", "run", "s", "E P1")
multiPlot([ "hnfin" ],file, filebase+"_byRun.ps", False, True, 0., 0., "Final counts", "run", "events", "E P1")


# rate per cut
ymax = [0.0, 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0. ]
ymin = [0.0, 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0. ]

gStyle.SetOptTitle(0)
for i in range(0,13):
    multiPlot([ "hratecut"+str(i) ],file, filebase+"_byRun.ps", False, False, ymin[i], ymax[i], "Rate after cuts "+str(i), "run", "Hz", "E P1", True)

hist2DPlot("hbx", file,  filebase+"_byRun.ps", 0., False, "HLT", "Run", "BX", "events", "COLZ")
hist2DPlot("heta", file,  filebase+"_byRun.ps", 0., False, "HLT", "Run", "jet #eta", "events", "COLZ")
hist2DPlot("hphi", file,  filebase+"_byRun.ps", 0., False, "HLT", "Run", "jet #phi", "events", "COLZ")

hist2DPlot("hbxfin", file,  filebase+"_byRun.ps", 0., False, "After all cuts", "Run", "BX", "events", "COLZ")
hist2DPlot("hetafin", file,  filebase+"_byRun.ps", 0., False, "After all cuts", "Run", "jet #eta", "events", "COLZ")
hist2DPlot("hphifin", file,  filebase+"_byRun.ps", 0., False, "After all cuts", "Run", "jet #phi", "events", "COLZ")

canvas = TCanvas("canvas")
canvas.Print(filebase+"_byRun.ps]")

# convert to PDF
subprocess.call(["ps2pdf", filebase+"_byRun.ps", filebase+"_byRun.pdf"])
subprocess.call(["rm", filebase+"_byRun.ps"])


