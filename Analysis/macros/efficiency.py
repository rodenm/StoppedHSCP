
# make efficiency histograms

from ROOT import *

from histograms import *
from plots import *


def effPlots(file) :

    dir = "EffHistos"
    canvas = TCanvas("canvas")
    
    # N-1 efficiencies
    histPlot(dir+"/heffjete", file, canvas, -1., True, "", "E (GeV)", "")
    histPlot(dir+"/heffjetn60", file, canvas, -1., True, "", "n60", "")
    histPlot(dir+"/heffjetn90", file, canvas, -1., True, "", "n90", "")
    histPlot(dir+"/heffnmu", file, canvas, -1., True, "", "N_{#mu}", "")


def effHistos(tree, file, cutObj, scale):

    file.mkdir("EffHistos")
    file.cd("EffHistos")

    # N-1 efficiencies
    histogram1D(tree, "heffjete", "LeadingCenJetEnergy>>heffjete", cutObj.nMinusOneCuts(2), scale, "Leading jet energy (N-1)", 100, 0., 200.)    
    histogram1D(tree, "heffjetn60", "LeadingCenJetn60>>heffjetn60", cutObj.nMinusOneCuts(3), scale, "Leading jet n60 (N-1)", 25, 0., 25.)
    histogram1D(tree, "heffjetn90", "LeadingCenJetn90>>heffjetn90", cutObj.nMinusOneCuts(4), scale, "Leading jet n90 (N-1)", 15, 0., 15.)
    histogram1D(tree, "heffnmu", "NoOfMuons>>heffnmu", cutObj.nMinusOneCuts(5), scale, "N muons (N-1)", 6, 0., 6.)

    file.cd()


def newEffHistos(tree, file, cutObj, scale):

    file.mkdir("NewEffHistos")
    file.cd("NewEffHistos")

    histogram1D(tree, "heffjete", "LeadingCenJetEnergy>>heffjete", cutObj.nMinusOneCuts(2), scale, "Leading jet energy (N-1)", 100, 0., 200.)    
    histogram1D(tree, "heffjetn60", "LeadingCenJetn60>>heffjetn60", cutObj.nMinusOneCuts(3), scale, "Leading jet n60 (N-1)", 25, 0., 25.)
    histogram1D(tree, "heffjetn90", "LeadingCenJetn90>>heffjetn90", cutObj.nMinusOneCuts(4), scale, "Leading jet n90 (N-1)", 15, 0., 15.)
    histogram1D(tree, "heffnmu", "NoOfMuons>>heffnmu", cutObj.nMinusOneCuts(5), scale, "N muons (N-1)", 6, 0., 6.)

    file.cd()   
