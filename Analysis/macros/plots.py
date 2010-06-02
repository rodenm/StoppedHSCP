
# define some plot making functions

import subprocess
from ROOT import *
from style import *
from plots import *
from utils import *

from math import pi


# just plot one quantity
def histPlot(hist, file, ofilename, scale=0, log=False, title="histogram", xtitle="", ytitle="", opt="HIST") :
    
    canvas=TCanvas("canvas")

    h = file.Get(hist)

    if (scale>0.) :
        h.Scale(scale)
    elif (scale<0.):
        h.Scale(1./h.Integral())        

    if (log) :
        canvas.SetLogy(1)
    else :
        canvas.SetLogy(0)

    h.SetLineColor(1)
    h.SetFillColor(2)

    if (not (title == "")) :
        h.SetTitle(title)
    if (not (ytitle == "")) :
        h.SetYTitle(ytitle)
    if (not (xtitle == "")) :
        h.SetXTitle(xtitle)

    h.Draw(opt)

#    canvas.Update()
    canvas.Print(ofilename)



# make a 2D plot
# scale=0. -> do not scale
# scale=-1 -> normalise to unit area
def hist2DPlot(hist, file, ofilename, scale=0., log=False, title="histogram", xtitle="", ytitle="", ztitle="", opt="") :

    canvas=TCanvas("canvas")

    h = file.Get(hist)

    if (scale>0.) :
        h.Scale(scale)
    elif (scale<0.):
        h.Scale(1./h.Integral())        

    if (log) :
        canvas.SetLogz()
    else :
        canvas.SetLogz(0)

    if (not (title == "")) :
        h.SetTitle(title)
    if (not (ytitle == "")) :
        h.SetYTitle(ytitle)
    if (not (xtitle == "")) :
        h.SetXTitle(xtitle)
    if (not (ztitle == "")) :
        h.SetZTitle(ztitle)

    # options
    canvas.SetLogy(0)
    h.SetStats(False)

    h.Draw(opt)

#    canvas.Update()
    canvas.Print(ofilename)


# superimpose multiple histograms
def multiPlot(hists, file, ofilename, norm=False, log=False, ymin=0., ymax=0., title="histogram", xtitle="", ytitle="", opt="HIST", port=False) :

    canvas=TCanvas("canvas")

    # set log scale, or not
    if (log) :
        canvas.SetLogy(1)
    else :
        canvas.SetLogy(0)

    # set y axis maximum
    setMaxMin = false
    if (not norm) :
        for hist in hists:
            h = file.Get(hist)
            if h.GetMaximum() > ymax:
                ymax=1.1*h.GetMaximum()
    else:
        ymax = 1.1

    # set titles

    # set list of colours
    colours = [2, 4, 5, 6, 7, 8, 9, 1]
    markers = [22, 25, 27, 28, 29, 22, 25, 27, 28]

    # iterate over histograms
    first=True
    for hist,col,mark in zip(hists,colours,markers):

        h = file.Get(hist)

        # set colour
        h.SetLineColor(col)
        h.SetMarkerColor(col)
        h.SetMarkerStyle(mark)

        # normalise if required
        if (norm and h.Integral() > 0.):
            h.Scale(1./h.Integral())

        # plot histogram
        if first:
            if (not (title == "")) :
                h.SetTitle(title)
            if (not (ytitle == "")) :
                h.SetYTitle(ytitle)
            if (not (xtitle == "")) :
                h.SetXTitle(xtitle)
            h.SetMaximum(ymax)
            h.Draw(opt)
            first=False
        else:
#            h.SetMaximum(ymax)
#            h.SetMinimum(ymin)
            h.Draw(opt+" SAME")

    canvas.Update()
    if (port):
        canvas.Print(ofilename, "Portrait")
    else:
        canvas.Print(ofilename)


# superimpose 3 plots
def compPlot(hist, fdata, fbg, fmc, ofile, norm=False, log=False, title="histogram", xtitle="", ytitle="", ymin=0., ymax=0.) :

    canvas=TCanvas("canvas")

    hbg=TH1D()
    hmc=TH1D()
    hdata=TH1D()
    
    if (fbg != 0):
        hbg = fbg.Get(hist)
    if (fmc != 0):
        hmc = fmc.Get(hist)
    if (fdata != 0):
        hdata = fdata.Get(hist)

    if (norm):
        if (hdata.Integral() > 0):
            hdata.Scale(1./hdata.Integral())
        if (hmc.Integral() > 0):
            hmc.Scale(1./hmc.Integral())
        if (hbg.Integral() > 0):
            hbg.Scale(1./hbg.Integral())
    
    if (log) :
        canvas.SetLogy(1)
    else :
        canvas.SetLogy(0)

    hbg.SetLineColor(17)
    hbg.SetFillColor(17)
    #hbg.SetMarkerColor(1)
    hmc.SetLineColor(4)
    hmc.SetFillStyle(0)
    hdata.SetLineStyle(0)
    hdata.SetFillStyle(0)
    hdata.SetMarkerColor(2)
    hdata.SetMarkerStyle(22)

    # set y axis maximum
    if (ymax > 0.):
        hbg.SetMaximum(ymax)
    else:
        ymax = hbg.GetMaximum()
        if (hmc.GetMaximum() > ymax) :
            ymax = hmc.GetMaximum()
        if (hdata.GetMaximum() > ymax) :
            ymax = hdata.GetMaximum()
        if (log):
            hbg.SetMaximum(ymax * 2.)
        else:
            hbg.SetMaximum(ymax * 1.2)

    if (ymin > 0.):
        hbg.SetMinimum(ymin)

    if (not (title == "")) :
        hbg.SetTitle(title)
    if (not (ytitle == "")) :
        hbg.SetYTitle(ytitle)
    if (not (xtitle == "")) :
        hbg.SetXTitle(xtitle)

    hbg.Draw("HIST")
    hmc.Draw("HIST SAME")
    hdata.Draw("HIST SAME P")

    canvas.Update()
    canvas.Print(ofile)


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
