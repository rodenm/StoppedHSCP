
# utility methods for making histograms from TTrees

from ROOT import *

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
