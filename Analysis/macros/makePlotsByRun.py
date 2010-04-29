
# make plots of various quantities by run

import sys
import getopt
import subprocess
import os

sys.argv.append('-b')

from ROOT import *
from math import *

from utils import *
from style import *
from plots import *


def histByRun(name, title, nruns):
    h = TH1D(name, title, nruns, 0, 0)
    h.Sumw2()
    return h

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
for opt, arg in opts:
    if opt=='-h':
        usage()
        exit.sys()

# arguments
dir=args[0]
runlist=args[1].split(',')
runs=[]
for i in range(0, len(runlist)):
    runs.append(int(runlist[i]))


# make plots of rate by run
nruns=len(runs)

# histos
hratehlt    = histByRun("hratehlt", "HLT rate", nruns)
hratehltfit = histByRun("hratehltfit", "HLT rate (fit)", nruns)
hratemu     = histByRun("hratemu", "Muon rate", nruns)
hratemufit  = histByRun("hratemufit", "Muon rate (fit)", nruns)
hratetim    = histByRun("hratetim", "Rate failing timing cuts", nruns)
hratetimfit = histByRun("hratetimfit", "Rate failing timing cuts (fit)", nruns)
hratefin    = histByRun("hratefin", "Final rate", nruns)
hnhlt       = histByRun("hnhlt", "HLT counts", nruns)
hnfin       = histByRun("hnfin", "Final counts", nruns)
hefftime    = histByRun("hefftime", "EFfective live time", nruns)
hlivetime   = histByRun("hlivetime", "Live time", nruns)
hratejetem  = histByRun("hratejetem", "Rate after jet+mu+jetEM cuts", nruns)

hratecuts = []
for c in range(0,12):
    hratecuts.append(histByRun("hratecut"+str(c), "Rate cut "+str(c), nruns))
    
    
# fill histograms from "rate per LS" fits
i=0
for run in runs:
    
    file = TFile(dir+"/histograms"+str(run)+".root")
    
    # HLT counts
    hlb=file.Get("NoCuts/hlb")
    nhlt=hlb.GetEntries()
    hnhlt.Fill(str(run), nhlt)
    hnhlt.SetBinError(i+1, sqrt(nhlt))
    
    # HLT rate
    hltrate = getHistMeanAndErr(file, "NoCuts/hlbdist")
    ratehlt = hltrate[0]/lumiBlockLength
    eratehlt = hltrate[1]/lumiBlockLength
    hratehlt.Fill(str(run), ratehlt)
    hratehlt.SetBinError(i+1, eratehlt)
    
#    hltfitrate = getFitMeanAndErr(file, "NoCuts/hlbdist")        
#    hratehltfit.Fill(str(run), hltfitrate[0])
#    hratehltfit.SetBinError(i+1, hltfitrate[1])
    
    # effective time (HLT rate / nevents)
    efftime=0.
    if (hltrate[0] > 0.):
        efftime = nhlt / hltrate[0]
    hefftime.Fill(str(run), efftime)
    hefftime.SetBinError(i+1, 10.)

    # live time (N non-zero LS after HLT)
    livetime = getLivetime2(hlb)
    hlivetime.Fill(str(run), livetime)
    hlivetime.SetBinError(i+1, 10.)
    
    # final counts
    hcutcount = file.Get("NoCuts/hncutcum")
    nevtFinal = hcutcount.GetBinContent(11)
    hnfin.Fill(str(run), nevtFinal)
    hnfin.SetBinError(i+1, sqrt(nevtFinal))
    
    # final rate
    finrate=0.
    efinrate=0.
    if (livetime>0.):
        finrate=nevtFinal / livetime
        efinrate=sqrt(nevtFinal)/livetime
    hratefin.Fill(str(run), finrate)
    hratefin.SetBinError(i+1, efinrate)

    # rate after jet + mu + jetEM cuts
    hjetem = file.Get("Cuts/hjetemf6")
    nevtjetem = hjetem.Integral(6, 100)
    if (livetime>0.):
        jetemrate=nevtjetem / livetime
        ejetemrate=sqrt(nevtjetem)/livetime
    hratejetem.Fill(str(run), jetemrate)
    hratejetem.SetBinError(i+1, ejetemrate)
    

    # rate after N cuts
    cut = TCut("")
    
    for c in range(0, 12):
        n=hcutcount.GetBinContent(c+1)
        rate=0.
        erate=0.
        if (livetime>0.):
            rate=n/livetime
            erate=sqrt(n)/livetime
        hratecuts[c].Fill(str(run), rate)
        hratecuts[c].SetBinError(i+1, erate)


    i=i+1


# write ROOT file
ofile = TFile(dir+"/"+dir+"_byRun.root", "recreate")
hratehlt.Write()
hratehltfit.Write()
hnhlt.Write()
hnfin.Write()
hefftime.Write()
hlivetime.Write()
hratefin.Write()
hratemu.Write()
hratemufit.Write()
hratetim.Write()
hratetimfit.Write()
hratejetem.Write()
for i in range(0,12):
    hratecuts[i].Write()
ofile.Close()
    

# draw plots
tdrStyle()
gROOT.SetStyle("tdrStyle")
gROOT.ForceStyle()


file=TFile(dir+"/"+dir+"_byRun.root", "read")

filebase=dir+"/"+dir

multiPlot([ "hratehlt" ],file, filebase+"_hltRate.png", False, False, "HLT rate", "run", "Hz", "E P1")
multiPlot([ "hlivetime", "hefftime" ],file, filebase+"_time.png", False, False, "time", "run", "s", "E P1")
multiPlot([ "hnhlt" ],file, filebase+"_hltCounts.png", False, True, "HLT counts", "run", "events", "E P1")
multiPlot([ "hnfin" ],file, filebase+"_finalCounts.png", False, True, "Final counts", "run", "events", "E P1")
multiPlot([ "hratefin" ],file, filebase+"_finalRate.png", False, False, "Final rate", "run", "Hz", "E P1")
multiPlot([ "hratejetem" ],file, filebase+"_jetEMRate.png", False, False, "Rate after jet EM cut", "run", "Hz", "E P1")
multiPlot([ "hratehlt", "hratefin" ],file, filebase+"_rate.png", False, True, "Rate", "run", "Hz", "E P1")

canvas = TCanvas("canvas")
canvas.Print(filebase+"_rateCuts.ps[", "Portrait")

for i in range(0,12):
    multiPlot([ "hratecut"+str(i) ],file, filebase+"_rateCuts.ps", False, False, "Rate after cuts "+str(i), "run", "Hz", "E P1", True)

canvas = TCanvas("canvas")
canvas.Print(filebase+"_rateCuts.ps]")
subprocess.call(["ps2pdf", filebase+"_rateCuts.ps", filebase+"_rateCuts.pdf"])
subprocess.call(["rm", filebase+"_rateCuts.ps"])


