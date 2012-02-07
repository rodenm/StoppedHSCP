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
def ratePlot(histname, ofile, title="", xtitle="Fill", ytitle="Hz"):
    hist = file.Get(histname)
    hist.SetMarkerStyle(7)
    hist.SetTitle(title)
    hist.SetXTitle(xtitle)
    hist.SetYTitle(ytitle)
    hist.GetXaxis().SetLabelSize(0.06)
    hist.GetYaxis().SetLabelSize(0.06)
#    hist.SetMarkerSize(1)
    hist.Draw()
    c.Print(odir+dataset+"_"+ofile)

# start plotting
ratePlot("hEventRateByFill", "EventRateByFill.pdf", "Event rate")

ratePlot("hNoiseRateByFill", "NoiseRateByFill.pdf", "Noise rate")
ratePlot("hMeanENoiseByFill", "NoiseMeanEByFill.pdf", "Noise", "Fill", "mean(E_{jet})")
ratePlot("hStdDevENoiseByFill", "NoiseStdDevEByFill.pdf", "Noise", "Fill", "#sigma(E_{jet})")

ratePlot("hCosmicRateByFill", "CosmicRateByFill.pdf", "#mu rate")
ratePlot("hMeanECosmicByFill", "CosmicMeanEByFill.pdf",  "#mu", "Fill", "mean(E_{jet})")
ratePlot("hStdDevECosmicByFill", "CosmicStdDevEByFill.pdf", "#mu", "Fill", "#sigma(E_{jet})")

ratePlot("hBeamHaloRateByFill", "BeamHaloRateByFill.pdf", "Halo rate")
ratePlot("hMeanEBeamHaloByFill", "BeamHaloMeanEByFill.pdf",  "Halo", "Fill", "mean(E_{jet})")
ratePlot("hStdDevEBeamHaloByFill", "BeamHaloStdDevEByFill.pdf", "Halo", "Fill", "#sigma(E_{jet})")

ratePlot("hBeamGasRateByFill", "BeamGasRateByFill.pdf", "Beam-gas rate")
ratePlot("hMeanEBeamGasByFill", "BeamGasMeanEByFill.pdf", "Beam-gas", "Fill", "mean(E_{jet})")
ratePlot("hStdDevEBeamGasByFill", "BeamGasStdDevEByFill.pdf", "Beam-gas", "Fill", "#sigma(E_{jet})")

ratePlot("hVertexRateByFill", "VertexRateByFill.pdf", "Vertex rate")
ratePlot("hMeanEVertexByFill", "VertexMeanEByFill.pdf",  "Vertex", "Fill", "mean(E_{jet})")
ratePlot("hStdDevEVertexByFill", "VertexStdDevEByFill.pdf", "Vertex", "Fill", "#sigma(E_{jet})")

ratePlot("hUnidentifiedRateByFill", "UnidentifiedRateByFill.pdf", "Unid rate")
ratePlot("hMeanEUnidentifiedByFill", "UnidentifiedMeanEByFill.pdf", "Unid", "Fill", "<E_{jet}>")
ratePlot("hStdDevEUnidentifiedByFill", "UnidentifiedStdDevEByFill.pdf", "Unid", "Fill", "#sigma(E_{jet})")


ratePlot("hCosmic2RateByFill", "Cosmic2RateByFill.pdf", "DT cosmic rate")
ratePlot("hCosmic3RateByFill", "Cosmic3RateByFill.pdf", "RPC cosmic rate")

#ratePlot("hCSCSegRateByFill", "CSCSegRateByFill.pdf")

ratePlot("hNM1CosmicRateByFill", "CosmicNM1RateByFill.pdf", "N-1(cosmic)", "Fill", "Hz")

ratePlot("hEventRateByRun", "EventRateByRun.pdf", "Run")
ratePlot("hTriggerRateByRun", "TriggerRateByRun.pdf", "Run")




