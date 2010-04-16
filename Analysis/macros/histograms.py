
# some functions for making histograms

from ROOT import *
from math import pi

from style import *
from histograms import *
from utils import *


def histogram1D(tree, name, treecommand, cuts, scale, title, nbins, xlo, xhi) :
    h = TH1D(name, title, nbins, xlo, xhi)
    h.Sumw2()
    tree.Draw(treecommand, cuts)
    h.Scale(scale)
    h.Write()
    return h


def histogram2D(tree, name, treecommand, cuts, scale, title, nbins, xlo, xhi, ylo, yhi) :
    h = TH2D(name, title, nbins, xlo, xhi, ylo, yhi)
    h.Sumw2()
    tree.Draw(treecommand, cuts)
    h.Scale(scale)
    h.Write()
    return h


# make a histogram of 'rate distribution' from histogram of eg. rate-per-LS
# and fit a Gaussian to it
def rateDist(rateByTime, nbins):

    name=rateByTime.GetName()+"dist"
    h = TH1D(name, "Rate", nbins, rateByTime.GetMinimum()*0.8, rateByTime.GetMaximum()*1.25)

    for i in range(rateByTime.GetNbinsX()):
        r=rateByTime.GetBinContent(i)
        if (r>0.):
            h.Fill(r)
    
    f = TF1("fit", "gaus")
    h.Fit("fit", "")       

    h.Write()

    return h
