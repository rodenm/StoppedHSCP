import sys
import optparse
import string
import os

# options
parser = optparse.OptionParser()
parser.add_option("-d", "--dir", action="store")

(opts, args)=parser.parse_args()

dataset=opts.dir

# ROOT
sys.argv=[]
sys.argv.append('-b')

from ROOT import *
from math import *
from style import *
from plots import *


# set style
tdrStyle()
gROOT.SetStyle("tdrStyle")
gROOT.ForceStyle()
gStyle.SetOptStat(0)
ROOT.gROOT.SetBatch()        # don't pop up canvases

#input file
file = TFile(dataset+"/BackgroundStability.root", "read")

#output dir
odir = dataset+"/BackgroundStability/"
d = os.path.dirname(odir)
if not os.path.exists(d):
    os.makedirs(d)

# canvas
c = TCanvas("c","",600,200)

# Calculate the mean y-value for bins 1 through maxbin
def getYMean(hist,maxbin):
    sum = 0.0
    den = maxbin
    for iBin in xrange(1,maxbin):
        #if hist.GetBinContent(iBin) > 2.5*(hist.GetBinContent(int(maxbin/2))+hist.GetBinContent(maxbin-5))/2:
        #    den = den -1
        #else:
            sum = sum + hist.GetBinContent(iBin)
    return sum/den

# plot definition
def ratePlot(histname, ofile, title="", xtitle="Fill", ytitle="Hz"):
    hist = file.Get(histname)
    hist.SetMarkerStyle(7)
    hist.SetMarkerColor(kBlue+2)
    hist.SetTitle(title)
    hist.SetXTitle(xtitle)
    hist.SetYTitle(ytitle)
    hist.SetMinimum(0)
    if ofile=="BeamHaloRateByFill.pdf":
        hist.SetMaximum(2)
    if ofile=="NoiseRateByFill.pdf":
        hist.SetMaximum(.6)
    if ofile=="CosmicNM1RateByFill.pdf":
        hist.SetMaximum(0.01)
    if ofile=="CosmicRateByFill.pdf":
        hist.SetMaximum(2.0)
    hist.GetXaxis().SetLabelSize(0.06)
    hist.GetYaxis().SetLabelSize(0.06)
#    hist.SetMarkerSize(1)
    hist.Draw()
    line = TLine(0,getYMean(hist,hist.GetNbinsX()),hist.GetNbinsX(),getYMean(hist,hist.GetNbinsX()))
    line.SetLineColor(kBlue)
    line.Draw()

    end2012a = hist.GetXaxis().FindBin("2596")
    line2 = TLine(0,getYMean(hist,end2012a),end2012a,getYMean(hist,end2012a))
    line2.SetLineColor(kBlue-3)
    line2.Draw()
    print str(histname) + " mean = " + str(getYMean(hist,hist.GetNbinsX()))
    c.Print(odir+dataset+"_"+ofile)

# start plotting
ratePlot("hEventRateByFill", "EventRateByFill.pdf", "HLT_JetE50_NoBPTX3BX_NoHalo", "", "Hz")

ratePlot("hNoiseRateByFill", "NoiseRateByFill.pdf", "isNoise && !isCosmic && !isBeamHalo && !isBeamGas && !isVtx")
ratePlot("hMeanENoiseByFill", "NoiseMeanEByFill.pdf", "isNoise && !isCosmic && !isBeamHalo && !isBeamGas && !isVtx", "Fill", "mean(E_{jet})")
ratePlot("hStdDevENoiseByFill", "NoiseStdDevEByFill.pdf", "isNoise && !isCosmic && !isBeamHalo && !isBeamGas && !isVtx", "Fill", "#sigma(E_{jet})")

ratePlot("hCosmicRateByFill", "CosmicRateByFill.pdf", "isCosmic3 rate")
ratePlot("hMeanECosmicByFill", "CosmicMeanEByFill.pdf",  "#mu", "Fill", "mean(E_{jet})")
ratePlot("hStdDevECosmicByFill", "CosmicStdDevEByFill.pdf", "#mu", "Fill", "#sigma(E_{jet})")

ratePlot("hBeamHaloRateByFill", "BeamHaloRateByFill.pdf", "isBeamHalo && !isBeamGas && !isVtx")
ratePlot("hMeanEBeamHaloByFill", "BeamHaloMeanEByFill.pdf",  "Halo", "Fill", "mean(E_{jet})")
ratePlot("hStdDevEBeamHaloByFill", "BeamHaloStdDevEByFill.pdf", "Halo", "Fill", "#sigma(E_{jet})")

ratePlot("hBeamGasRateByFill", "BeamGasRateByFill.pdf", "isBeamGas && !isVtx")
ratePlot("hMeanEBeamGasByFill", "BeamGasMeanEByFill.pdf", "Beam-gas", "Fill", "mean(E_{jet})")
ratePlot("hStdDevEBeamGasByFill", "BeamGasStdDevEByFill.pdf", "Beam-gas", "Fill", "#sigma(E_{jet})")

ratePlot("hVertexRateByFill", "VertexRateByFill.pdf", "isVtx rate")
ratePlot("hMeanEVertexByFill", "VertexMeanEByFill.pdf",  "Vertex", "Fill", "mean(E_{jet})")
ratePlot("hStdDevEVertexByFill", "VertexStdDevEByFill.pdf", "Vertex", "Fill", "#sigma(E_{jet})")

ratePlot("hUnidentifiedRateByFill", "UnidentifiedRateByFill.pdf", "Unid rate")
ratePlot("hMeanEUnidentifiedByFill", "UnidentifiedMeanEByFill.pdf", "Unid", "Fill", "<E_{jet}>")
ratePlot("hStdDevEUnidentifiedByFill", "UnidentifiedStdDevEByFill.pdf", "Unid", "Fill", "#sigma(E_{jet})")


ratePlot("hCosmic2RateByFill", "Cosmic2RateByFill.pdf", "isCosmic2")
ratePlot("hCosmic3RateByFill", "Cosmic3RateByFill.pdf", "isCosmic3 && !isBeamHalo && !isBeamGas && !isVtx")

#ratePlot("hCSCSegRateByFill", "CSCSegRateByFill.pdf")

ratePlot("hNM1CosmicRateByFill", "CosmicNM1RateByFill.pdf", "N-1(cosmic)", "Fill", "Hz")

ratePlot("hEventRateByRun", "EventRateByRun.pdf", "Run")
ratePlot("hTriggerRateByRun", "TriggerRateByRun.pdf", "Run")




