
# define some plot making functions

import subprocess
from ROOT import *
from style import *
from plots import *
from utils import *

from math import pi

# plot histograms from a ROOT file
def makePlots(filebase, doEff) :

    file = TFile(filebase+".root", "read")
    ps = TPostScript(filebase+".ps")
    canvas = TCanvas("canvas")

    basicPlots(file, "NoCuts", canvas)
    basicPlots(file, "JetMuCuts", canvas)
    basicPlots(file, "AllCuts", canvas)
    if doEff:
        effPlots(file, "EffPlots", canvas)

    ps.Close()
    subprocess.call(["ps2pdf", filebase+".ps", filebase+".pdf"])
    

def basicPlots(file, dir, canvas):

    # reminder of method arguments
    # histPlot(hist, file, canvas, norm=False, log=False, title="histogram", xtitle="", ytitle="", opt="HIST")
    # hist2DPlot(hist, file, canvas, norm=False, log=False, title="histogram", xtitle="", ytitle="", ztitle="", opt="")

    # event time
    histPlot(dir+"/hbx", file, canvas, False, True, "", "BX", "")
    histPlot(dir+"/horb", file, canvas, False, True, "", "orbit", "")
    histPlot(dir+"/hlb", file, canvas, False, True, "", "Lumi Block", "")
    histPlot(dir+"/htime", file, canvas, False, True, "", "Event time", "")

    # L1 trigger
    histPlot(dir+"/hl1et", file, canvas, False, True, "", "E_{L1} (GeV)", "")
    histPlot(dir+"/hl1eta", file, canvas, False, True, "", "#eta", "")
    histPlot(dir+"/hl1phi", file, canvas, False, True, "", "#phi", "")
    
    # HLT
    histPlot(dir+"/hhlte", file, canvas, False, True, "", "E_{HLT} (GeV)", "")
    histPlot(dir+"/hhlteta", file, canvas, False, True, "", "#eta", "")
    histPlot(dir+"/hhltphi", file, canvas, False, True, "", "#phi", "")

    # misc
    histPlot(dir+"/hntowsamephi", file, canvas, False, True, "", "N_{towers}", "")

    # jet variables
    histPlot(dir+"/hjete2", file, canvas, False, True, "", "E (GeV)", "E")
    histPlot(dir+"/hjeteta", file, canvas, False, True, "", "#eta", "E")
    histPlot(dir+"/hjetphi", file, canvas, False, True, "", "#phi", "E")
    histPlot(dir+"/hjetem", file, canvas, False, True, "", "E_{ECAL}", "E")
    histPlot(dir+"/hjethad", file, canvas, False, True, "", "E_{HCAL}", "E")
    histPlot(dir+"/hjetn60", file, canvas, False, True, "", "n60", "E")
    histPlot(dir+"/hjetn90", file, canvas, False, True, "", "n90", "E")

    # muon variables
    histPlot(dir+"/hnmu", file, canvas, False, True, "", "N_{#mu}", "")


    # pulse shape variables
    histPlot(dir+"/hr1", file, canvas, False, False, "", "R1", "")
    histPlot(dir+"/hr2", file, canvas, False, False, "", "R2", "")
    histPlot(dir+"/hpk", file, canvas, False, False, "", "R_{peak}", "")
    histPlot(dir+"/hout", file, canvas, False, False, "", "R_{outer}", "")

    # 2D timing plots
    hist2DPlot(dir+"/hr1r2", file, canvas, False, True, "", "R_{2}", "R_{1}", "", "CONT")
    hist2DPlot(dir+"/hpkout", file, canvas, False, True, "", "R_{out}", "R_{peak}", "", "CONT")

    # plots after jet + mu cuts
#    histPlot(dir+"/hr1_jetMuCuts", file, canvas, False, False, "", "R1", "")
#    histPlot(dir+"/hr2_jetMuCuts", file, canvas, False, False, "", "R2", "")
#    histPlot(dir+"/hpk_jetMuCuts", file, canvas, False, False, "", "R_{peak}", "")
#    histPlot(dir+"/hout_jetMuCuts", file, canvas, False, False, "", "R_{outer}", "")

    # 2D timing plots
#    hist2DPlot(dir+"/hr1r2_jetMuCuts", file, canvas, False, False, "", "R_{2}", "R_{1}", "", "CONT")
#    hist2DPlot(dir+"/hpkout_jetMuCuts", file, canvas, False, False, "", "R_{out}", "R_{peak}", "", "CONT")

    # plots after all cuts
#    histPlot(dir+"/hjete_allCuts", file, canvas, False, True, "", "E (GeV)", "")
#    histPlot(dir+"/hbx_allCuts", file, canvas, False, True, "", "BX", "")
#    histPlot(dir+"/horb_allCuts", file, canvas, False, True, "", "orbit", "")
#    histPlot(dir+"/hlb_allCuts", file, canvas, False, True, "", "Lumi block", "")




def effPlots(file, dir, canvas) :
    
    # N-1 efficiencies
    histPlot(dir+"/heffjete", file, canvas, True, True, "", "E (GeV)", "")
    histPlot(dir+"/heffjetn60", file, canvas, True, True, "", "n60", "")
    histPlot(dir+"/heffjetn90", file, canvas, True, True, "", "n90", "")
    histPlot(dir+"/heffnmu", file, canvas, True, True, "", "N_{#mu}", "")


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
