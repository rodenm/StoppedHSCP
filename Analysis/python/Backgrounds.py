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
file = TFile(dataset+"/Backgrounds.root", "read")

#output dir
odir = dataset+"/Backgrounds/"
d = os.path.dirname(odir)
if not os.path.exists(d):
    os.makedirs(d)

# canvas
c = TCanvas()

# plot definition
def plot(name, ofile, xtitle="Fill", ytitle="Hz"):

    h1 = file.Get("hNoise"+name)
    h2 = file.Get("hCosmic"+name)
    if (h2.Integral()>0) :
        h2.Scale(h1.Integral()/h2.Integral())
    h3 = file.Get("hBeamHalo"+name)
    if (h3.Integral()>0) :
        h3.Scale(h1.Integral()/h3.Integral())
    h4 = file.Get("hBeamGas"+name)
    if (h4.Integral()>0) :
        h4.Scale(h1.Integral()/h4.Integral())
    h5 = file.Get("hVertex"+name)
    if (h5.Integral()>0) :
        h5.Scale(h1.Integral()/h5.Integral())
    h6 = file.Get("hUnid"+name)
    if (h6.Integral()>0) :
        h6.Scale(h1.Integral()/h6.Integral())

    ymax = max(h1.GetMaximum(), h2.GetMaximum(), h3.GetMaximum(), h4.GetMaximum(), h5.GetMaximum(), h6.GetMaximum())

    h1.SetMaximum(1.1*ymax)
    h1.SetTitle(name)
    h1.SetXTitle(xtitle)
    h1.SetYTitle(ytitle)    
    h1.SetLineColor(1)
    h1.SetFillStyle(0)
    h1.Draw("HIST")

    h2.SetLineColor(2)
    h2.SetFillStyle(0)
    h2.Draw("SAME HIST")

    h3.SetLineColor(4)
    h3.SetFillStyle(0)
    h3.Draw("SAME HIST")

    h4.SetLineColor(4)
    h4.SetLineStyle(2)
    h4.SetFillStyle(0)
    h4.Draw("SAME HIST")

    h5.SetLineColor(2)
    h5.SetLineStyle(2)
    h5.SetFillStyle(0)
#    h5.Draw("SAME HIST")

    h6.SetLineColor(6)
    h6.SetFillStyle(0)
    h6.Draw("SAME HIST")

    leg = TLegend(0.6, 0.77, 0.8, 0.93)
    leg.SetFillColor(0)
    leg.AddEntry(h1, "Noise", "L")
    leg.AddEntry(h2, "Cosmic", "L")
    leg.AddEntry(h3, "Beam Halo", "L")
    leg.AddEntry(h4, "Beam Gas", "L")
    leg.AddEntry(h5, "Vertex", "L")
    leg.AddEntry(h6, "No ID", "L")
    leg.Draw()
    
    c.Print(odir+ofile)

# start plotting
plot("JetE",     "JetE.pdf",    "E [GeV]", "")
plot("JetEta",   "JetEta.pdf",  "#eta", "")
plot("JetPhi",   "JetPhi.pdf",  "#phi", "")
plot("JetN60",   "JetN60.pdf",  "n60", "")
plot("JetN90",   "JetN90.pdf",  "n90", "")
plot("Ntow",     "NTowers.pdf", "N_{towers}", "")
plot("IPhiFrac", "IPhiFrac.pdf","f_{iphi}", "")
#plot("NMu",      "NMu.pdf",     "N_{#mu}", "")
plot("NCSC",     "NCSC.pdf",    "N_{CSC}", "")
plot("NTrack",   "NTrack.pdf",  "N_{track}", "")
plot("NVtx",     "NVtx.pdf",    "N_{vtx}", "")
plot("BHFlag",   "BHFlag.pdf",  "Beam Halo", "")




