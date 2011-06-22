#! /usr/bin/env python

# bin boundaries
edges = [ 0, 11, 18, 23, 28, 34, 41, 45, 50, 55 ]
nHist = 16

cutName = ["trigger", "BPTX veto", "BX veto", "Vertex veto", "Halo veto", "Cosmic Veto", "Noise veto", "E30", "E70", "n60", "n90", "nTowIPhi", "R1", "R2", "R_{peak}", "R_{outer}" ]

dontUse = [0,1,2,7]

# start from fills histograms
# plot N-1 rates with coarser binning
# plot correlations


import sys
import getopt
import string
import os

# help message
def usage():
    print "Usage : background.py <input file>"    


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

import array
from ROOT import *
from math import *
from style import *
from plots import *


# set style
tdrStyle()
gROOT.SetStyle("tdrStyle")
gROOT.ForceStyle()

# input file
ifilename = dataset+"/histograms.root"
ifile = TFile(ifilename)

# some variables
nBins = len(edges)-1

# create new time histogram
hTime=ifile.Get("fills/hfilltime")
print "Rebinning time histogram : ", hTime.Integral()
hNewTime = TH1D('hnewtime', '', nBins, 0., nBins)
for bin in range(1, nBins+1):
    sum=0.
    for b in range(edges[bin-1], edges[bin]):
        sum += hTime.GetBinContent(1+b)
    hNewTime.SetBinContent(bin, sum)
    print "Bin "+str(bin)+" time : ",sum

print "New time hist : ", hNewTime.Integral()

# new final counts histogram
hFinRate=ifile.Get("fills/hfillnfin")
print "Rebinning fin counts histogram : ", hFinRate.Integral()
hNewFinRate = TH1D('hnewfin', '', nBins, 0., nBins)
for bin in range(1, nBins+1):
    time = hNewTime.GetBinContent(bin)
    count=0.
    for b in range(edges[bin-1], edges[bin]):
        count += hFinRate.GetBinContent(1+b)
    hNewFinRate.SetBinContent(bin, count/time)
    if (count>0):
        hNewFinRate.SetBinError(bin, sqrt(count)/time)
    else:
        hNewFinRate.SetBinError(bin, 1/time)

print "New fin counts hist : ", hNewFinRate.Integral()


# new histograms
countHists=[]
rateHists=[]

# loop over histograms
for h in range(0,nHist):

    # get old histrogram
    hOld = ifile.Get('fills/hfillnm1count_'+str(h))
    print "Rebinning hfillnm1count_"+str(h)+". Integral = ", hOld.Integral()

    # create new histograms
    hNew = TH1D('hnm1_'+str(h), cutName[h], nBins, 0., nBins)
    hRate = TH1D('hnm1rate_'+str(h), cutName[h], nBins, 0., nBins)

    # rebin it
    for bin in range(1, nBins+1):
        count=0

        time = hNewTime.GetBinContent(bin)

        for b in range(edges[bin-1], edges[bin]):
            count += hOld.GetBinContent(1+b)

        hNew.SetBinContent(bin, count)
        hRate.SetBinContent(bin, count/time)

        if (count>0):
            hNew.SetBinError(bin, sqrt(count))
            hRate.SetBinError(bin, sqrt(count)/time)
        else:
            hNew.SetBinError(bin, 1)
            hRate.SetBinError(bin, 1./time)

    print "New histogram hnm1_"+str(h)+".      Integral = ", hNew.Integral()

    countHists.append(hNew)
    rateHists.append(hRate)
        

# make correlation histograms
corrGraphs=[]

for i1 in range(0, nHist):

    for i2 in range(i1+1, nHist):

        if (i1 in dontUse) or (i2 in dontUse):
            continue

        corrGraph=TGraphErrors(nBins)

        for bin in range(0,nBins):
            corrGraph.SetPoint(bin, rateHists[i1].GetBinContent(bin+1), rateHists[i2].GetBinContent(bin+1))
            corrGraph.SetPointError(bin, rateHists[i1].GetBinError(bin+1), rateHists[i2].GetBinError(bin+1))

        corrGraph.SetName("corr_"+str(i1)+"_"+str(i2))
        corrGraph.SetTitle(cutName[i2]+" vs "+cutName[i1]+" N-1")
        corrGraph.GetXaxis().SetTitle(cutName[i1])
        corrGraph.GetYaxis().SetTitle(cutName[i2])

        corrGraphs.append(corrGraph)

# correlations with final rate
for i2 in range(0, nHist):

    if i2 in dontUse:
        continue

    corrGraph=TGraphErrors(nBins)

    for bin in range(0,nBins):
        corrGraph.SetPoint(bin, hNewFinRate.GetBinContent(bin+1), rateHists[i2].GetBinContent(bin+1))
        corrGraph.SetPointError(bin, hNewFinRate.GetBinError(bin+1), rateHists[i2].GetBinError(bin+1))

    corrGraph.SetName("corr_fin_"+str(i2))
    corrGraph.SetTitle("N-1 vs N rates");
    corrGraph.GetXaxis().SetTitle("Final rate")
    corrGraph.GetYaxis().SetTitle(cutName[i2])

    corrGraphs.append(corrGraph)


# make plots

# output file
ofile = dataset+"/background.ps"
opdf = dataset+"/background.pdf"

# prepare canvas for plotting
canvas = TCanvas("canvas")
canvas.Print(ofile+"[", "Portrait")

for h in range (0,nHist):
    if h in dontUse:
        continue
    rateHists[h].Draw("E P0")
    canvas.Print(ofile)
    canvas.Clear()

for g in corrGraphs:
    g.Draw("AP")
    canvas.Print(ofile)
    canvas.Clear()

# close file
canvas = TCanvas("canvas")
canvas.Print(ofile+"]")

# convert to PDF
subprocess.call(["ps2pdf", ofile, opdf])
subprocess.call(["rm", ofile])


#ifile.Close()

# output file
ofile = TFile("background.root", "recreate")

hNewTime.Write()
hNewFinRate.Write()

#for h in countHists:
#    h.Write()

for h in rateHists:
    h.Write()

for g in corrGraphs:
    g.Write()

ofile.Close()
