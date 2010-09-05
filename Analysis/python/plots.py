
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


