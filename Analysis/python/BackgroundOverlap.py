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
file1 = TFile(dataset+"/Backgrounds_v1.root", "read")
file2 = TFile(dataset+"/Backgrounds.root", "read")

#output dir
odir = dataset+"/BackgroundOverlaps/"
d = os.path.dirname(odir)
if not os.path.exists(d):
    os.makedirs(d)

# canvas
c = TCanvas()

# plot definition
def plot(name, ofile, xtitle="Fill", ytitle="Hz"):

    h1 = file1.Get("h"+name)
    h2 = file2.Get("h"+name)

    h1.SetTitle(name)
    h1.SetXTitle(xtitle)
    h1.SetYTitle(ytitle)    
    h1.SetLineColor(2)
    h1.SetFillStyle(0)
    h1.Draw("HIST")

    h2.SetLineColor(2)
    h2.SetLineStyle(2)
    h2.SetFillStyle(0)
    h2.Draw("SAME HIST")

    leg=TLegend(0.5, 0.8, 0.6, 0.9)
    leg.SetFillColor(0)
    leg.AddEntry(h1, "Inclusive", "L")
    leg.AddEntry(h2, "Exclusive", "L")
    leg.Draw()

    c.Print(odir+ofile)

# start plotting
for bg in ["Noise", "Cosmic", "BeamHalo", "BeamGas", "Vertex", "Unid"]:
    for dist in ["JetE", "JetEta", "JetPhi", "JetN60", "JetN90", "Ntow", "IPhiFrac", "NMu", "NCSC", "NTrack", "NVtx", "BHFlag"]:
        plot(bg+dist, bg+dist+".pdf", dist, "Hz")
