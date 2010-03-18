
# define some plot making functions

from ROOT import *


# just plot one quantity
def histPlot(hist, file, canvas, norm=False, log=False, title="histogram", xtitle="", ytitle="", opt="HIST") :
    h = file.Get(hist)

    if (norm) :
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

    canvas.Update()



# make a 2D plot
def hist2DPlot(hist, file, canvas, norm=False, log=False, title="histogram", xtitle="", ytitle="", ztitle="", opt="") :
    h = file.Get(hist)

    if (norm) :
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

    canvas.Update()


# superimpose multiple histograms
def multiPlot(hists, canvas, norm=False, log=False, title="histogram", xtitle="", ytitle="", opt="HIST") :

    # set log scale, or not
    if (log) :
        canvas.SetLogy(1)
    else :
        canvas.SetLogy(0)

    # set y axis maximum
    ymax = 1.1
    if (not norm) :
        for hist in hists:
            if hist.GetMaximum() > ymax:
                ymax=1.1*hist.GetMaximum()
    hists[0].SetMaximum(ymax)

    # set titles
    if (not (title == "")) :
        hists[0].SetTitle(title)
    if (not (ytitle == "")) :
        hists[0].SetYTitle(ytitle)
    if (not (xtitle == "")) :
        hists[0].SetXTitle(xtitle)

    # set list of colours
    colours = [0,1,2,4,5,6,7,8,9]

    # iterate over histograms
    first=True
    for hist,col in zip(hists,colours):

        # set colour
        hist.SetLineColor(col)
        hist.SetMarkerColor(col)

        # normalise if required
        if (norm and hist.Integral() > 0.):
            hist.Scale(1./hist.Integral())

        # plot histogram
        if first:
            hist.Draw(opt)
            first=False
        else:
            hist.Draw(opt+" SAME")

    canvas.Update()


# superimpose 3 plots
def compPlot(hist, fdata, fcraft, fmc, canvas, norm=False, log=False, title="histogram", xtitle="", ytitle="") :
    hdata = fdata.Get(hist)
    hcraft = fcraft.Get(hist)
    hmc = fmc.Get(hist)

    if (norm and (hdata.Integral() > 0) and (hcraft.Integral() > 0) and (hmc.Integral() > 0) ) :
        hdata.Scale(1./hdata.Integral())
        hcraft.Scale(1./hcraft.Integral())
        hmc.Scale(1./hmc.Integral())

    if (log) :
        canvas.SetLogy(1)
    else :
        canvas.SetLogy(0)

    hdata.SetLineColor(1)
    hcraft.SetLineColor(2)
    hmc.SetLineColor(4)

    # set y axis maximum
    ymax = 1.1
    if (not norm) :
        ymax = hdata.GetMaximum()
        if (hcraft.GetMaximum() > ymax) :
            ymax = hcraft.GetMaximum()
        if (hmc.GetMaximum() > ymax) :
            ymax = hmc.GetMaximum()
    hdata.SetMaximum(ymax)

    if (not (title == "")) :
        hdata.SetTitle(title)
    if (not (ytitle == "")) :
        hdata.SetYTitle(ytitle)
    if (not (xtitle == "")) :
        hdata.SetXTitle(xtitle)

    hdata.Draw("HIST")
    hdata.SetMarkerColor(1)
    hcraft.Draw("HIST SAME")
    hcraft.SetMarkerColor(2)
    hmc.Draw("HIST SAME")

    canvas.Update()
