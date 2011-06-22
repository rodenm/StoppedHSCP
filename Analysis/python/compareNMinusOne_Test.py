

#cutName = ["trigger", "BPTX veto", "BX veto", "Vertex veto", "Halo veto", "Cosmic Veto", "Noise veto", "E30", "E70", "n60", "n90", "nTowIPhi", "R1", "R2", "R_{peak}", "R_{outer}" ]
cutName = [ "BX", "Vertex", "Halo", "Cosmic", "Wide Noise", "n90", "Timing" ]
nHist = len(cutName)

end=[ "bx", "vtx", "halo", "cos", "noise", "n90", "timing" ]


dontUse = []

# bin boundaries
edges0 = [ 0, 11, 18, 23, 28, 34, 41, 45, 50, 55 ] # this is for Run2010A 1117-1309
edges1 = [ 0, 4, 13, 26 ] # this is for Run2010B 1364-1459
edges2 = [ 0, 9, 14, 26, 44 ] # this is for Run2011A 1711 - 1851

totalPoints=16


import sys
import getopt
import string
import os

# help message
def usage():
    print "Usage : nMinusOnePlots.py <dataset>"    


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
dataset0=args[0]
dataset1=args[1]
#dataset2=args[2]

ndatset = len(args)-1

sys.argv.append('-b')

from ROOT import *
from math import *
from style import *
from plots import *
from constants import *


cols = [1, 2, 4]
markers = [20, 21, 22]

# set style
tdrStyle()
gROOT.SetStyle("tdrStyle")
gROOT.ForceStyle()



def getGraphs(ifile, edges):

    # some variables
    nBins = len(edges)-1

    # create new time histogram
    hTime=ifile.Get("fills/hfilltime")
    hFin=ifile.Get("fills/hfillnfin")
    print "Rebinning time histogram : ", hTime.Integral()
    print "Rebinning fin counts histogram : ", hFin.Integral()

    hNewTime = TH1D('hnewtime', '', nBins, 0., nBins)
    hNewFin = TH1D('hnewnfin', '', nBins, 0., nBins)
    hNewFinRate = TH1D('hnewfinrate', '', nBins, 0., nBins)

    for bin in range(1, nBins+1):
        tsum=0.
        count=0.
        for b in range(edges[bin-1], edges[bin]):
            tsum += hTime.GetBinContent(1+b)
            count += hFin.GetBinContent(1+b)
        hNewTime.SetBinContent(bin, tsum)
        hNewFin.SetBinContent(bin, count)
        hNewFinRate.SetBinContent(bin, count/tsum)
        if (count>0):
            hNewFin.SetBinError(bin, sqrt(count))
            hNewFinRate.SetBinError(bin, sqrt(count)/tsum)
        else:
            hNewFin.SetBinError(bin, 1)
            hNewFinRate.SetBinError(bin, 1/tsum)
        print "Bin="+str(bin)+" time="+str(tsum)+" count="+str(count)

    print "New time hist : ", hNewTime.Integral()
    print "New nfin hist : ", hNewFin.Integral()
    print "New fin rate hist : ", hNewFinRate.Integral()/hNewFinRate.GetNbinsX()


    # new histograms
    countHists=[]
    rateHists=[]

    # loop over histograms
    for h in range(0,nHist):

        # get old histrogram
        hOld = ifile.Get('fills/hfilltest_'+end[h])
        print "Rebinning hfilltest_"+end[h]+". Integral = ", hOld.Integral()

        # create new histograms
        hNew = TH1D('hnm1_'+end[h], cutName[h], nBins, 0., nBins)
        hRate = TH1D('hnm1rate_'+end[h], cutName[h], nBins, 0., nBins)

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
            if (hNewFinRate.GetBinContent(bin+1) <> rateHists[i2].GetBinContent(bin+1)):
                corrGraph.SetPoint(bin, hNewFinRate.GetBinContent(bin+1), rateHists[i2].GetBinContent(bin+1))
                corrGraph.SetPointError(bin, hNewFinRate.GetBinError(bin+1), rateHists[i2].GetBinError(bin+1))


        corrGraph.SetName("corr_fin_"+str(i2))
        corrGraph.SetTitle("N-1 vs N rates");
        corrGraph.GetXaxis().SetTitle("Final rate")
        corrGraph.GetYaxis().SetTitle(cutName[i2])

        corrGraphs.append(corrGraph)

    return [ rateHists, corrGraphs ]


file0 = TFile(dataset0+"/histograms.root")
file1 = TFile(dataset1+"/histograms.root")
#file2 = TFile(dataset2+"/histograms.root")

corrGraphs0 = getGraphs(file0, edges0)
corrGraphs1 = getGraphs(file1, edges1)
#corrGraphs2 = getGraphs(file2, edges2)

# output file
ofile = "compareNMinusOne.ps"
opdf = "compareNMinusOne.pdf"

# prepare canvas for plotting
canvas = TCanvas("canvas")
canvas.Print(ofile+"[", "Portrait")



# do rate vs time plots
for g,h,c in zip(corrGraphs0[0],corrGraphs1[0],range(0,len(corrGraphs0[0]))): #corrGraphs2[0], range(0,len(corrGraphs0[0]))):
    ng = g.GetNbinsX()
    nh = h.GetNbinsX()
#    ni = i.GetNbinsX()
    nNew = ng+nh
#    nNew = ng+nh+ni
    hNew = TH1D("hnew", "N-1 rate : "+cutName[c], nNew, 0., nNew)
    for s in range(0,nNew):
        if (s<ng):
            hNew.SetBinContent(s+1, g.GetBinContent(s+1))
            hNew.SetBinError(s+1, g.GetBinError(s+1))
        if (s>=ng and s<(ng+nh)):
            hNew.SetBinContent(s+1, h.GetBinContent(s-ng+1))
            hNew.SetBinError(s+1, h.GetBinError(s-ng+1))
#        if (s>=(ng+nh) and s<(ng+nh+ni)):
#            hNew.SetBinContent(s+1, i.GetBinContent(s-ng-nh+1))
#            hNew.SetBinError(s+1, i.GetBinError(s-ng-nh+1))

    hNew.Draw("E P0")
    line1=TLine(ng,-1.,ng,+1.)
    line1.SetLineStyle(2)
    line1.Draw()
    line2=TLine(ng+nh,-1.,ng+nh,+1.)
    line2.SetLineStyle(2)
    line2.Draw()
    canvas.Print(ofile)
    canvas.Clear()

# N-1 vs N-1
nGraph=len(corrGraphs0[1])
for g,h,k in zip(corrGraphs0[1],corrGraphs1[1], range(0,nGraph)): #,corrGraphs2[1]):

    title=str(g.GetTitle())
    xtitle=str(g.GetXaxis().GetTitle())
    ytitle=str(g.GetYaxis().GetTitle())
    print title,ytitle,xtitle
    graph=TMultiGraph()

    coll = TObjArray()
    coll.Add(g)
    coll.Add(h)
    combined = TGraphErrors()
    combined.Merge(coll)    

    if (k>=(nGraph-7)):
        fn = TF1("fn"+str(k), "[0]+x*[1]")
        combined.Fit(fn)
        combined.SetMarkerStyle(0)
        combined.SetMarkerColor(0)

    g.SetMarkerStyle(20)
    h.SetMarkerStyle(21)
    h.SetMarkerColor(2)
    #    i.SetMarkerStyle(22)
    #    i.SetMarkerColor(4)

#    if (combined.GetN()>0):
    graph.Add(combined)
    graph.Add(g)
    graph.Add(h)
    #    graph.Add(i)

    graph.SetTitle(title+";"+xtitle+";"+ytitle)
    #    graph.SetColor(0)

    #    if (k>=(nGraph-7)):
    graph.Draw("ap")
    canvas.Print(ofile)
    canvas.Clear()

# close file
canvas = TCanvas("canvas")
canvas.Print(ofile+"]")

# convert to PDF
subprocess.call(["ps2pdf", ofile, opdf])
subprocess.call(["rm", ofile])
