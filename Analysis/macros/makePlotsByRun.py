
# make plots of various quantities by run

import sys
import getopt
import subprocess
import os

def usage():
    print "Usage : python makePlotsByRun.py [-h] <input dir> <run list>"

# arguments : file location and local dir for results
try:
    opts, args = getopt.getopt(sys.argv[1:], "ph")
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
    h = TH2D(name, title, nruns, 0, 0, ny, ymin, ymax)
    h.Sumw2()
    return h

def getLivetime(runtree, run):
    time=0.
    # loop over runs in run TTree
    nruns=runtree.GetEntriesFast()
    for i in range(0,nruns):
        entry = runtree.LoadTree(i)
        if entry < 0:
            break
        nb = runtree.GetEntry(i)
        if nb <= 0:
            continue
        time+=runtree.livetime
        if (runtree.run==run):
            return runtree.livetime
    return time

def getLivetime2(hist, lumiBlockLength) :
    time=0.
    for i in range(0,hist.GetNbinsX()):
        if (hist.GetBinContent(i) > 0.):
            time += lumiBlockLength
    return time

# main program starts here

# make plots of rate by run
nruns=len(runs)

# histos
hnhlt       = histByRun("hnhlt", "HLT counts", nruns)
hnfin       = histByRun("hnfin", "Final counts", nruns)
hefftime    = histByRun("hefftime", "EFfective live time", nruns)
hlivetime   = histByRun("hlivetime", "Live time", nruns)
hnpostjet   = histByRun("hnpostjet", "N events after jet cuts", nruns)
hnposttim   = histByRun("hnposttim", "N events after timing cuts", nruns)

# rate after each cut
hratecuts = []
for c in range(0,13):
    hratecuts.append(histByRun("hratecut"+str(c), "Rate cut "+str(c), nruns))

# 2D vs run plots
hbxrun    = hist2DByRun("hbxrun", "BX vs Run", nruns, "BX", 3564, 0., 3564.)
hetarun    = hist2DByRun("hetarun", "#eta vs Run", nruns, "#eta", 70, -3.0, 3.0)
hphirun    = hist2DByRun("hphirun", "#phi vs Run", nruns, "#phi", 72, -1 * pi, pi)

    
# fill histograms from "rate per LS" fits
i=0
for run in runs:
    
    file = TFile(dir+"/histograms"+str(run)+".root")
    
    # HLT counts
    hlb=file.Get("NoCuts/hlb")
    nhlt=hlb.GetEntries()
    hnhlt.Fill(str(run), nhlt)
    hnhlt.SetBinError(i+1, sqrt(nhlt))

    # effective time (HLT rate / nevents)
#    efftime=0.
#    if (hltrate[0] > 0.):
#        efftime = nhlt / hltrate[0]
#    hefftime.Fill(str(run), efftime)
#    hefftime.SetBinError(i+1, 10.)

    # live time (N non-zero LS after HLT)
    livetime = getLivetime2(hlb)
    hlivetime.Fill(str(run), livetime)
    hlivetime.SetBinError(i+1, 10.)

    hcutcount = file.Get("Cuts/hncutcum")

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
    

    i=i+1


# write ROOT file
ofile = TFile(dir+"/"+dir+"_byRun.root", "recreate")
hnhlt.Write()
hefftime.Write()
hlivetime.Write()
hnfin.Write()
for i in range(0,13):
    hratecuts[i].Write()
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
multiPlot([ "hlivetime" ],file, filebase+"_byRun.ps", False, False, 0., 0., "time", "run", "s", "E P1")
multiPlot([ "hnfin" ],file, filebase+"_byRun.ps", False, True, 0., 0., "Final counts", "run", "events", "E P1")


# rate per cut
ymax = [0.0, 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0. ]
ymin = [0.0, 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0. ]

gStyle.SetOptTitle(0)
for i in range(0,13):
    multiPlot([ "hratecut"+str(i) ],file, filebase+"_byRun.ps", False, False, ymin[i], ymax[i], "Rate after cuts "+str(i), "run", "Hz", "E P1", True)

canvas = TCanvas("canvas")
canvas.Print(filebase+"_byRun.ps]")

# convert to PDF
subprocess.call(["ps2pdf", filebase+"_byRun.ps", filebase+"_byRun.pdf"])
subprocess.call(["rm", filebase+"_byRun.ps"])


