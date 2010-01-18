
# utility methods for making histograms from TTrees

def histogram1D(name, treecommand, title, nbins, xlo, xhi) :
    h = TH1D(name, title, nbins, xlo, xhi)
    tree.Draw(treecommand)
    h.Write()

