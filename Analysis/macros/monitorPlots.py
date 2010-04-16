
# this macro reads 'per run' histogram files
# and produces history plots of interesting quantities
# plots currently in png format, since this is designed for prompt monitoring

from ROOT import *
from math import *


from style import *
from utils import *
from cuts import *


def histByRun(name, title, nruns):
    h = TH1D(name, title, nruns, 0, 0)
    h.Sumw2()
    return h

def getHistMeanAndErr(file, hname):
    ratedist = file.Get(hname)
    return ratedist.GetMean(), ratedist.GetMeanError()

def getFitMeanAndErr(file, hname):
    ratedist = file.Get(hname)
    fit = ratedist.GetFunction("fit")
    return fit.GetParameter(1), fit.GetParError(1)

def plotMulti(histos, file, log, min=0, max=0):
    canvas=TCanvas()
    if (log):
        canvas.SetLogy(1)
    if (max>0.):
        histos[0].SetMaximum(max)
        histos[0].SetMinimum(min)
    markers = [ 22, 25, 27, 28, 29 ]
    colours = [ 2, 4, 5, 6, 7 ]
    first=True
    for hist, marker, colour in zip(histos, markers, colours):
        hist.SetMarkerStyle(marker)
        hist.SetMarkerColor(colour)
        hist.SetLineColor(colour)
        if (first):
            hist.Draw("P E1")
            first=False
        else:
            hist.Draw("P E1 SAME")
    canvas.Update()
    canvas.Print(file)


# runs argument is list of runs (eg. getRuns(runtree))
def monitorPlots(tree, cutObj, runs, dir):

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

    hratecuts = []
    for c in range(0,10):
        hratecuts.append(histByRun("hratecut"+str(c), "Rate cut "+str(c), nruns))
        

    # fill histograms from "rate per LS" fits
    i=0
    for run in runs:

        file = TFile(dir+"/"+dir+"-"+str(run)+".root")

        # HLT counts
        hlb=file.Get("NoCuts/hlb")
        nhlt=hlb.GetEntries()
        hnhlt.Fill(str(run), nhlt)
        hnhlt.SetBinError(i+1, sqrt(nhlt))
                     
        # HLT rate
        hltrate = getHistMeanAndErr(file, "Rates/hlbdist")        
        hratehlt.Fill(str(run), hltrate[0])
        hratehlt.SetBinError(i+1, hltrate[1])

        hltfitrate = getFitMeanAndErr(file, "Rates/hlbdist")        
        hratehltfit.Fill(str(run), hltfitrate[0])
        hratehltfit.SetBinError(i+1, hltfitrate[1])
        
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
        nevtFinal = nEvents(tree, cutObj.allCuts(), run)
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

        # rate after N cuts
        cut = TCut("")
        
        for c in range(0, 10):
            cut += cutObj[c]
            n=nEvents(tree, cut, run)
            rate=0.
            erate=0.
            if (livetime>0.):
                rate=n/livetime
                erate=sqrt(n)/livetime
            hratecuts[c].Fill(str(run), rate)
            hratecuts[c].SetBinError(i+1, erate)


        i=i+1


    # write ROOT file
    ofile = TFile(dir+"/"+dir+"_Rates.root", "recreate")
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
    for i in range(0,10):
        hratecuts[i].Write()
    ofile.Close()
                      
    # draw plots
    tdrStyle()
    gROOT.SetStyle("tdrStyle")
    gROOT.ForceStyle()
    
    plotMulti([ hratehlt ], dir+"/"+dir+"_hltRate.png", False)
    plotMulti([ hlivetime, hefftime ], dir+"/"+dir+"_time.png", False)
    plotMulti([ hnhlt ], dir+"/"+dir+"_hltCounts.png", False)
    plotMulti([ hnfin ], dir+"/"+dir+"_finalCounts.png", False)
    plotMulti([ hratefin ], dir+"/"+dir+"_finalRate.png", False)
    plotMulti([ hratehlt, hratefin ], dir+"/"+dir+"_rates.png", True, 1.e-5, 10.)

