
# define some plot making functions

import subprocess
from ROOT import *
from style import *
from plots import *
from utils import *

from math import pi


# just plot one quantity
def histPlot(hist, file, ofilename, scale=0, log=False, title="histogram", xtitle="", ytitle="", opt="") :
    
    canvas=TCanvas("canvas")

    h = file.Get(hist)
    if h==None:  # Could not identify histogram
        print "Could not get histogram '%s'"%hist
        return
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
    if h==None:  # Could not identify histogram
        print "Could not get histogram '%s'"%hist
        return
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


class PlotStyle:

    # construct object with default style
    def __init__(self, style):
        self.norm    = False
        self.log     = False
        self.leg     = False
        self.opt     = " "
        self.port    = False
        self.colours = [1, 2, 3, 4]
        self.markers = [21, 22, 23, 24]
        self.fills   = [0, 0, 0, 0]
        self.lstyles = [0, 0, 0, 0]
        
        # style dictionary
        styles={0:self.style1,
                1:self.style1,
                2:self.style2,
                3:self.style3,
                4:self.style4}
        
        styles[style]()

    # just markers
    def style0(self):
        self.opt     = "E P0"

    # background vs data comparison
    def style1(self):  
        self.norm    = True
        self.leg     = True
        self.colours = [17, 2, 4]
        self.markers = [0, 0, 0]
        self.fills   = [17, 0, 0]
        self.lstyles = [0, 1, 1]
        self.opt     = "HIST"

    # simple different color histograms
    def style2(self):
        self.leg     = True
        self.colours = [1, 2, 4, 6]
        self.markers = [0, 0, 0, 0]
        self.opt     = "HIST"

    # 2D colour map
    def style3(self):
        self.opt     = "COLZ"

    # different color histograms, log scale
    def style4(self):
        self.leg     = True
        self.log     = True
        self.colours = [1, 2, 4, 6, 1, 2, 4, 6]
        self.markers = [0, 0, 0, 0, 0, 0, 0, 0]
        self.fills   = [0, 0, 0, 0, 0, 0, 0, 0]
        self.lstyles = [1, 1, 1, 1, 2, 2, 2, 2]
        self.opt     = "HIST"


# superimpose multiple histograms
def multiPlot(hists,
              labels,
              ofile,
              ymin=0.,
              ymax=0.,
              title="histogram",
              xtitle="",
              ytitle="",
              ztitle="",
              style=0,
              xmin=0.,
              xmax=0.) :


    # print xtitle, title
    s = PlotStyle(style)

    # fudge to normalize the cum cuts plot - MLR
    #if xtitle=="cut":# or xtitle=="n_{60}" or xtitle=="n_{90}":
    #    s.norm=true
    
    canvas=TCanvas("canvas")

    # set log scale, or not
    if (s.log) :
        canvas.SetLogy(1)
        if (ymax==0.):
            ymax=1.
        if (ymin==0.):
            ymin=0.1
    else :
        canvas.SetLogy(0)

    # get y axis maximum
    if (ymax==0.):
        for h in hists:
            if s.norm and h.Integral()>0.:
                max = 1.1*h.GetMaximum()/h.Integral()
            elif s.log: # need to set max for logy plots
                max = 5*(h.GetMaximum()+h.GetBinError(h.GetMaximumBin()))
            else:
                max = 1.1*(h.GetMaximum()+h.GetBinError(h.GetMaximumBin()))
            if max > ymax:
                ymax = max

    # set x range
    if (not xmax==0.or not xmin==0.):
        for h in hists:
            h.SetAxisRange(xmin, xmax)

    # legend
    legend=TLegend(0.65, 0.65, 0.95, 0.75)
    legend.SetFillColor(0)
    legend.SetBorderSize(1)

    opt = s.opt

    # iterate over histograms
    first=True
    for h,col,lstyle,mark,fill,label in zip(hists,s.colours,s.lstyles,s.markers,s.fills,labels):

        # set colour
        h.SetLineColor(col)
        h.SetLineStyle(lstyle)
        if (fill!=0):
            h.SetFillColor(fill)
        else:
            h.SetFillStyle(0)
        if (mark!=0):
            h.SetMarkerStyle(mark)
            h.SetMarkerColor(col)
            opt+="PE"

        # normalise if required
        if (s.norm and h.Integral() > 0.):
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
            h.SetMinimum(ymin)
            h.Draw(opt)
            first=False
        else:
            h.Draw(opt+" SAME")

        if (fill!=0):
            legend.AddEntry(h, label, "f")
        else:
            if (mark!=0):
                legend.AddEntry(h, label, "m")
            else:
                legend.AddEntry(h, label, "l")

    if s.leg :
        legend.Draw()

    canvas.Update()
    
    if (s.port):
        canvas.Print(ofile, "Portrait")
    else:
        canvas.Print(ofile)


