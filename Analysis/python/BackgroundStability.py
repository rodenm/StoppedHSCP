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

#input file
file = TFile(dataset+"/BackgroundStability.root", "read")

#output dir
odir = dataset+"/BackgroundStability/"
d = os.path.dirname(odir)
if not os.path.exists(d):
    os.makedirs(d)

# canvas
c = TCanvas("c","",600,200)

# plot definition
def ratePlot(histname, ofile, xtitle="Fill", ytitle="Hz"):
    hist = file.Get(histname)
    hist.SetMarkerStyle(7)
    hist.SetXTitle(xtitle)
    hist.SetYTitle(ytitle)
#    hist.SetMarkerSize(1)
    hist.Draw()
    c.Print(odir+ofile)

# start plotting
ratePlot("hEventRateByFill", "EventRateByFill.pdf")

ratePlot("hNoiseRateByFill", "NoiseRateByFill.pdf")
ratePlot("hMeanENoiseByFill", "NoiseMeanEByFill.pdf", "Fill", "mean(E_{jet})")
ratePlot("hStdDevENoiseByFill", "NoiseStdDevEByFill.pdf", "Fill", "#sigma(E_{jet})")

ratePlot("hCosmicRateByFill", "CosmicRateByFill.pdf")
ratePlot("hMeanECosmicByFill", "CosmicMeanEByFill.pdf",  "Fill", "mean(E_{jet})")
ratePlot("hStdDevECosmicByFill", "CosmicStdDevEByFill.pdf", "Fill", "#sigma(E_{jet})")

ratePlot("hBeamHaloRateByFill", "BeamHaloRateByFill.pdf")
ratePlot("hMeanEBeamHaloByFill", "BeamHaloMeanEByFill.pdf",  "Fill", "mean(E_{jet})")
ratePlot("hStdDevEBeamHaloByFill", "BeamHaloStdDevEByFill.pdf", "Fill", "#sigma(E_{jet})")

ratePlot("hBeamGasRateByFill", "BeamGasRateByFill.pdf")
ratePlot("hMeanEBeamGasByFill", "BeamGasMeanEByFill.pdf",  "Fill", "mean(E_{jet})")
ratePlot("hStdDevEBeamGasByFill", "BeamGasStdDevEByFill.pdf", "Fill", "#sigma(E_{jet})")

ratePlot("hVertexRateByFill", "VertexRateByFill.pdf")
ratePlot("hMeanEVertexByFill", "VertexMeanEByFill.pdf",  "Fill", "mean(E_{jet})")
ratePlot("hStdDevEVertexByFill", "VertexStdDevEByFill.pdf", "Fill", "#sigma(E_{jet})")

ratePlot("hUnidentifiedRateByFill", "UnidentifiedRateByFill.pdf")
ratePlot("hMeanEUnidentifiedByFill", "UnidentifiedMeanEByFill.pdf",  "Fill", "<E_{jet}>")
ratePlot("hStdDevEUnidentifiedByFill", "UnidentifiedStdDevEByFill.pdf")


ratePlot("hCosmic2RateByFill", "Cosmic2RateByFill.pdf")

ratePlot("hCSCSegRateByFill", "CSCSegRateByFill.pdf")

ratePlot("hMuonNMinusOneRateByFill", "MuonNMinusOneRateByFill.pdf")

ratePlot("hEventRateByRun", "EventRateByRun.pdf", "Run")
ratePlot("hTriggerRateByRun", "TriggerRateByRun.pdf", "Run")




