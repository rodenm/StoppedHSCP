
# this macro reads 'per run' histogram files
# and produces history plots of interesting quantities
# plots currently in png format, since this is designed for prompt monitoring

from ROOT import *

from style import *
from utils import *
from cuts import *

from math import *

def getHistMeanAndErr(file, hname):
    ratedist = file.Get(hname)
    return ratedist.GetMean(), ratedist.GetRMS()

def getFitMeanAndErr(file, hname):
    ratedist = file.Get(hname)
    fit = ratedist.GetFunction("fit")
    return fit.GetParameter(1), fit.GetParameter(2)

# runs argument is list of runs (eg. getRuns(runtree))
def monitorPlots(tree, runs, dir, runtree):

    # make plots of rate by run
#    allruns=getRuns(runtree)
    nruns=len(runs)
    
    # declare histos
    hltrate=TH1D("hltrate", "HLT rate", nruns, 0, 0)
    hltrate.Sumw2()
    hltfitrate=TH1D("hltfitrate", "HLT rate", nruns, 0, 0)
    hltfitrate.Sumw2()

    murate=TH1D("murate", "Muon rate", nruns, 0, 0)
    murate.Sumw2()
    mufitrate=TH1D("mufitrate", "Muon rate", nruns, 0, 0)
    mufitrate.Sumw2()

    timrate=TH1D("timrate", "Rate failing timing cuts", nruns, 0, 0)
    timrate.Sumw2()
    timfitrate=TH1D("timfitrate", "Rate failing timing cuts", nruns, 0, 0)
    timfitrate.Sumw2()

     # fill histograms from "rate per LS" fits
    i=0
    for run in runs:

        file = TFile(dir+"/"+dir+"-"+str(run)+".root")

        # HLT rate
        rate = getHistMeanAndErr(file, "Rates/hlbdist")        
        hltrate.Fill(str(run), rate[0])
        hltrate.SetBinError(i+1, rate[1])

        fitrate = getFitMeanAndErr(file, "Rates/hlbdist")        
        hltfitrate.Fill(str(run), fitrate[0])
        hltfitrate.SetBinError(i+1, fitrate[1])
        
        # muon rate
        rate2 = getHistMeanAndErr(file, "Rates/hlbmudist")        
        murate.Fill(str(run), rate2[0])
        murate.SetBinError(i+1, rate2[1])

        fitrate2 = getFitMeanAndErr(file, "Rates/hlbmudist")        
        mufitrate.Fill(str(run), fitrate2[0])
        mufitrate.SetBinError(i+1, fitrate2[1])

        # timing cut failure rate
        rate3 = getHistMeanAndErr(file, "Rates/hlbtimdist")        
        timrate.Fill(str(run), rate3[0])
        timrate.SetBinError(i+1, rate3[1])

        fitrate3 = getFitMeanAndErr(file, "Rates/hlbtimdist")        
        timfitrate.Fill(str(run), fitrate3[0])
        timfitrate.SetBinError(i+1, fitrate3[1])

        i=i+1

#    hltrate.Scale(1./getLivetime(runtree, run))
#    jmrate.Scale(1./getLivetime(runtree, run))
#    allrate.Scale(1./getLivetime(runtree, run))
                      
    # draw plots
    tdrStyle()
    gROOT.SetStyle("tdrStyle")
    gROOT.ForceStyle()
    
    canvas=TCanvas()

    hltrate.SetMarkerStyle(22)
    hltrate.SetMarkerColor(2)
    hltrate.SetLineColor(2)
    hltrate.Draw("P E1")
    hltfitrate.SetMarkerStyle(25)
    hltfitrate.SetMarkerColor(4)
    hltfitrate.SetLineColor(4)
    hltfitrate.Draw("P E1 SAME")
    canvas.Update()
    canvas.Print(dir+"/"+dir+"hltRate.png")

    murate.SetMarkerStyle(22)
    murate.SetMarkerColor(2)
    murate.SetLineColor(2)
    murate.Draw("P E1")
    mufitrate.SetMarkerStyle(25)
    mufitrate.SetMarkerColor(4)
    mufitrate.SetLineColor(4)
    mufitrate.Draw("P E1 SAME")
    canvas.Update()
    canvas.Print(dir+"/"+dir+"muRate.png")

    timrate.SetMarkerStyle(22)
    timrate.SetMarkerColor(2)
    timrate.SetLineColor(2)
    timrate.Draw("P E1")
    timfitrate.SetMarkerStyle(25)
    timfitrate.SetMarkerColor(4)
    timfitrate.SetLineColor(4)
    timfitrate.Draw("P E1 SAME")
    canvas.Update()
    canvas.Print(dir+"/"+dir+"timRate.png")

#    finrate.SetMarkerStyle(22)
#    finrate.SetMarkerColor(2)
#    finrate.SetLineColor(2)
#    finrate.Draw("P E1")
#    finfitrate.SetMarkerStyle(25)
#    finfitrate.SetMarkerColor(4)
#    finfitrate.SetLineColor(4)
#    finfitrate.Draw("P E1 SAME")
#    canvas.Update()
#    canvas.Print(dir+"/finRate.png")


#    canvas.Update()
#    canvas.Print(dir+"/hltFitRate.png")


#    canvas.Clear()
#    jmrate.SetMarkerStyle(8)
#    jmrate.SetMarkerColor(2)
#    jmrate.Draw("P E")
#    canvas.Update()
#    canvas.Print(dir+"jetmuRate.png")

#    canvas.Clear()
#    allrate.SetMarkerStyle(8)
#    allrate.SetMarkerColor(2)
#    allrate.Draw("P E")
#    canvas.Update()
#    canvas.Print(dir+"finalRate.png")


