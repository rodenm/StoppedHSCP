
# make plots of various quantities by run

import sys
import getopt
import subprocess
import os
import array

filebase='May6th_'
samples=['gluino_1jet_336_150_50_2', \
         'gluino_1jet_336_150_100_2',   \
         'gluino_1jet_336_200_100_2',  \
         'gluino_1jet_336_200_150_2',  \
         'gluino_1jet_336_300_100_2',  \
         'gluino_1jet_336_300_200_2',  \
         'gluino_1jet_336_400_100_2',  \
         'gluino_1jet_336_400_200_2', \
         'gluino_1jet_336_400_300_2',  \
         'gluino_1jet_336_500_100_2',  \
         'gluino_1jet_336_500_200_2',  \
         'gluino_1jet_336_500_400_2',  \
         'gluino_1jet_336_600_300_2',  \
         'gluino_1jet_336_600_500_2',  \
         'gluino_1jet_336_900_800_2']

nevents = 10000.

mgluino=[150.,
         150.,
         200.,
         200.,
         300.,
         300.,
         400.,
         400.,
         400.,
         500.,
         500.,
         500.,
         600.,
         600.,
         900.]

mneutralino=[50.,
             100.,
             100.,
             150.,
             100.,
             200.,
             100.,
             200.,
             300.,
             100.,
             200.,
             400.,
             300.,
             500.,
             800.]


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

# main program starts here
nsamples=len(samples)

# histos

# rate after each cut
hcutcounts = []
for c in range(0,13):
    hcutcounts.append(histByRun("hcutcount"+str(c), "Rate cut "+str(c), nsamples))

# eff as fn of visible energy
m=array("d",[])
merr=array("d",[])
efin=array("d", [])
errfin=array("d", [])
eecal=array("d", [])
errecal=array("d", [])



# fill histograms from "rate per LS" fits
scale=100./nevents
i=0
for (sample,mg,mn) in zip(samples,mgluino,mneutralino):

    print sample, mg, mn
    
    file = TFile(filebase+sample+"/histograms.root")
    hcutcum = file.Get("Cuts/hncutcum")

    # rate after N cuts
    cut = TCut("")
    
    for c in range(0, 13):
        n=hcutcum.GetBinContent(c+1)
        hcutcounts[c].Fill(sample, n)
        hcutcounts[c].SetBinError(i+1, sqrt(n))

    m.append(mg-mn)
    merr.append(0.)

    nfin=hcutcum.GetBinContent(12)
    efin.append(nfin*scale)
    errfin.append(sqrt(nfin)*scale)

    ne=hcutcum.GetBinContent(13)
    eecal.append(ne*scale)
    errecal.append(sqrt(ne)*scale)

    i=i+1


efffin = TGraphErrors(len(m), m, efin, merr, errfin)
effecal = TGraphErrors(len(m), m, eecal, merr, errecal)

# draw plots
tdrStyle()
gROOT.SetStyle("tdrStyle")
gROOT.ForceStyle()


canvas=TCanvas("canvas")
efffin.SetTitle("Efficiency (%)")
efffin.SetMarkerStyle(22)
efffin.SetMarkerColor(2)
efffin.GetXaxis().SetTitle("GeV")
efffin.Draw("APE")
canvas.Update()
canvas.Print("test1.pdf")

canvas=TCanvas("canvas")
effecal.SetTitle("Efficiency (%) inc ECAL")
effecal.SetMarkerStyle(22)
effecal.SetMarkerColor(2)
effecal.GetXaxis().SetTitle("GeV")
effecal.Draw("APE")
canvas.Update()
canvas.Print("test2.pdf")





# write ROOT file
ofile = TFile("MCHistosBySample.root", "recreate")
for i in range(0,13):
    hcutcounts[i].Write()
ofile.Close()

file=TFile("MCHistosBySample.root", "read")

# PS file
canvas = TCanvas("canvas")
canvas.Print("MCHistosBySample.ps[", "Portrait")

# rate per cut
ymax = [0.0, 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0. ]
ymin = [0.0, 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0. ]

gStyle.SetOptTitle(0)
for i in range(0,13):
    multiPlot([ "hcutcount"+str(i) ],file, "MCHistosBySample.ps", False, False, ymin[i], ymax[i], "Rate after cuts "+str(i), "run", "Hz", "E P1", True)

canvas = TCanvas("canvas")
canvas.Print("MCHistosBySample.ps]")

# convert to PDF
subprocess.call(["ps2pdf", "MCHistosBySample.ps", "MCHistosBySample.pdf"])
subprocess.call(["rm", "MCHistosBySample.ps"])

