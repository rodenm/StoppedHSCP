
from ROOT import *

from style import *
from utils import *
from cuts import *

from math import sqrt


def monitorPlots(tree, runtree):

    # make plots of rate by run
    allruns=getRuns(runtree)
    nruns=len(allruns)
    
    # declare histos
    hltrate=TH1D("hltrate", "HLT rate", nruns, 0, 0)
    hltrate.Sumw2()
    jmrate=TH1D("jmrate", "jet+mu rate", nruns, 0, 0)
    jmrate.Sumw2()
    allrate=TH1D("allrate", "final rate", nruns, 0, 0)
    allrate.Sumw2()

    jmgr = TGraph(nruns)

    # fill histograms
    i=0
    for run in getRuns(runtree):

        nhlt = nEvents(tree, "", run)
        print nhlt, sqrt(nhlt)
        hltrate.Fill(str(run), nhlt)
        hltrate.SetBinError(i+1,sqrt(nhlt))

        njm = nEvents(tree, oldcuts.jetMu, run)
        jmrate.Fill(str(run), njm)
        jmrate.SetBinError(i+1, sqrt(njm))

        nfinal = nEvents(tree, oldcuts.allCuts(), run)
        allrate.Fill(str(run), nfinal)
        allrate.SetBinError(i+1, sqrt(nfinal))
        
        jmgr.SetPoint(i, run, getRate(tree, runtree, oldcuts.jetMu, run))
        i=i+1

    hltrate.Scale(1./getLivetime(runtree, run))
    jmrate.Scale(1./getLivetime(runtree, run))
    allrate.Scale(1./getLivetime(runtree, run))
                      
    # draw plots
    tdrStyle()
    gROOT.SetStyle("tdrStyle")
    gROOT.ForceStyle()
    
    canvas=TCanvas()

    hltrate.SetMarkerStyle(8)
    hltrate.SetMarkerColor(2)
    hltrate.Draw("P E")
    canvas.Update()
    canvas.Print("plots/hltRate.png")

    canvas.Clear()
    jmrate.SetMarkerStyle(8)
    jmrate.SetMarkerColor(2)
    jmrate.Draw("P E")
    canvas.Update()
    canvas.Print("plots/jetmuRate.png")

    canvas.Clear()
    allrate.SetMarkerStyle(8)
    allrate.SetMarkerColor(2)
    allrate.Draw("P E")
    canvas.Update()
    canvas.Print("plots/finalRate.png")


