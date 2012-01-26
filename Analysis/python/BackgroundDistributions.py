import sys
import optparse
import string
import os

# options
parser = optparse.OptionParser()
parser.add_option("-1", "--dir1", action="store")
parser.add_option("-2", "--dir2", action="store")
parser.add_option("-3", "--dir3", action="store")
parser.add_option("-4", "--dir4", action="store")

(opts, args)=parser.parse_args()

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
file1 = TFile(opts.dir1+"/Backgrounds.root", "read")
file2 = TFile(opts.dir2+"/Backgrounds.root", "read")
file3 = TFile(opts.dir3+"/Backgrounds.root", "read")
file4 = TFile(opts.dir4+"/Backgrounds.root", "read")

#output dir
#odir = "Backgrounds/"
#d = os.path.dirname(odir)
#if not os.path.exists(d):
#    os.makedirs(d)

# canvas
c = TCanvas()
c.SetLogy()

# plot definition
def plot(name, bg, ofile, xtitle="Fill", ytitle="Hz", norm=False, rebin=0, xmin=0., xmax=0., ymax=0.):

    h1 = file1.Get("h"+bg+name)
    h2 = file2.Get("h"+bg+name)
    h3 = file3.Get("h"+bg+name)
    h4 = file4.Get("h"+bg+name)

    if rebin>0:
        h1.Rebin(rebin)
        h2.Rebin(rebin)
        h3.Rebin(rebin)
        h4.Rebin(rebin)

    if norm:
        if (h2.Integral()>0) :
            h2.Scale(h1.Integral()/h2.Integral())
        if (h3.Integral()>0) :
            h3.Scale(h1.Integral()/h3.Integral())
        if (h4.Integral()>0) :
            h4.Scale(h1.Integral()/h4.Integral())

    if (ymax != 0.):
        h1.SetMaximum(ymax)

    if (xmax!=0.):
        h1.GetXaxis().SetRangeUser(xmin, xmax)
    
    h1.SetTitle(bg+" "+name)
    h1.SetXTitle(xtitle)
    h1.SetYTitle(ytitle)    
    h1.SetLineColor(2)
    h1.SetLineStyle(2)
    h1.SetFillStyle(0)
    h1.Draw("HIST")

    h2.SetLineColor(2)
    h2.SetLineStyle(1)
    h2.SetFillStyle(0)
    h2.Draw("SAME HIST")

    h3.SetLineColor(4)
    h3.SetLineStyle(2)
    h3.SetFillStyle(0)
    h3.Draw("SAME HIST")

    h4.SetLineColor(4)
    h4.SetLineStyle(1)
    h4.SetFillStyle(0)
    h4.Draw("SAME HIST")
    
    leg = TLegend(0.6, 0.77, 0.8, 0.93)
    leg.SetFillColor(0)
    leg.AddEntry(h1, "2010A", "L")
    leg.AddEntry(h2, "2010B", "L")
    leg.AddEntry(h3, "2011A", "L")
    leg.AddEntry(h4, "2011B", "L")
    leg.Draw()
    
    c.Print(ofile)

# start plotting
plot("JetE",     "Noise", "Noise/JetE.pdf",    "E [GeV]",    "", True)
plot("JetEta",   "Noise", "Noise/JetEta.pdf",  "#eta",       "", True)
plot("JetPhi",   "Noise", "Noise/JetPhi.pdf",  "#phi",       "", True)
plot("JetN60",   "Noise", "Noise/JetN60.pdf",  "n60",        "", True)
plot("JetN90",   "Noise", "Noise/JetN90.pdf",  "n90",        "", True)
plot("Ntow",     "Noise", "Noise/NTowers.pdf", "N_{towers}", "", True)
plot("IPhiFrac", "Noise", "Noise/IPhiFrac.pdf","f_{iphi}",   "", True)
plot("BX",       "Noise", "Noise/BX.pdf",      "BX_{rel}",   "", True, 0, -20., 20.)
plot("BXUP",     "Noise", "Noise/BXUP.pdf",    "BX_{wrt UP}","", True, 0, -20., 20.)
plot("R1",       "Noise", "Noise/R1.pdf",      "R_{1}",      "", True)
plot("R2",       "Noise", "Noise/R2.pdf",      "R_{2}",      "", True)
plot("RP",       "Noise", "Noise/RPeak.pdf",   "R_{peak}",   "", True)
plot("RO",       "Noise", "Noise/ROuter.pdf",  "R_{outer}",  "", True)
#plot("NMu",      "Noise", "Noise/NMu.pdf",     "N_{#mu}",    "", True)
#plot("NCSC",     "Noise", "Noise/NCSC.pdf",    "N_{CSC}",    "", True)
#plot("NTrack",   "Noise", "Noise/NTrack.pdf",  "N_{track}",  "", True)
#plot("NVtx",     "Noise", "Noise/NVtx.pdf",    "N_{vtx}",    "", True)
#plot("BHFlag",   "Noise", "Noise/BHFlag.pdf",  "Beam Halo",  "", True)

plot("JetE",     "Cosmic", "Cosmic/JetE.pdf",    "E [GeV]",    "", True)
plot("JetEta",   "Cosmic", "Cosmic/JetEta.pdf",  "#eta",       "", True)
plot("JetPhi",   "Cosmic", "Cosmic/JetPhi.pdf",  "#phi",       "", True)
plot("JetN60",   "Cosmic", "Cosmic/JetN60.pdf",  "n60",        "", True)
plot("JetN90",   "Cosmic", "Cosmic/JetN90.pdf",  "n90",        "", True)
plot("Ntow",     "Cosmic", "Cosmic/NTowers.pdf", "N_{towers}", "", True)
plot("IPhiFrac", "Cosmic", "Cosmic/IPhiFrac.pdf","f_{iphi}",   "", True)
plot("BX",       "Cosmic", "Cosmic/BX.pdf",      "BX_{rel}",   "", True, 0, -20., 20.)
plot("BXUP",     "Cosmic", "Cosmic/BXUP.pdf",    "BX_{wrt UP}","", True, 0, -20., 20.)
plot("R1",       "Cosmic", "Cosmic/R1.pdf",      "R_{1}",      "", True)
plot("R2",       "Cosmic", "Cosmic/R2.pdf",      "R_{2}",      "", True)
plot("RP",       "Cosmic", "Cosmic/RPeak.pdf",   "R_{peak}",   "", True)
plot("RO",       "Cosmic", "Cosmic/ROuter.pdf",  "R_{outer}",  "", True)
#plot("NMu",      "Cosmic", "Cosmic/NMu.pdf",     "N_{#mu}",    "", True)
#plot("NCSC",     "Cosmic", "Cosmic/NCSC.pdf",    "N_{CSC}",    "", True)
#plot("NTrack",   "Cosmic", "Cosmic/NTrack.pdf",  "N_{track}",  "", True)
#plot("NVtx",     "Cosmic", "Cosmic/NVtx.pdf",    "N_{vtx}",    "", True)
#plot("BHFlag",   "Cosmic", "Cosmic/BHFlag.pdf",  "Beam Halo",  "", True)

plot("JetE",     "BeamHalo", "BeamHalo/JetE.pdf",    "E [GeV]",    "", True)
plot("JetEta",   "BeamHalo", "BeamHalo/JetEta.pdf",  "#eta",       "", True)
plot("JetPhi",   "BeamHalo", "BeamHalo/JetPhi.pdf",  "#phi",       "", True)
plot("JetN60",   "BeamHalo", "BeamHalo/JetN60.pdf",  "n60",        "", True)
plot("JetN90",   "BeamHalo", "BeamHalo/JetN90.pdf",  "n90",        "", True)
plot("Ntow",     "BeamHalo", "BeamHalo/NTowers.pdf", "N_{towers}", "", True)
plot("IPhiFrac", "BeamHalo", "BeamHalo/IPhiFrac.pdf","f_{iphi}",   "", True)
plot("BX",       "BeamHalo", "BeamHalo/BX.pdf",      "BX_{rel}",   "", True, 0, -20., 20.)
plot("BXUP",     "BeamHalo", "BeamHalo/BXUP.pdf",    "BX_{wrt UP}","", True, 0, -20., 20.)
plot("R1",       "BeamHalo", "BeamHalo/R1.pdf",      "R_{1}",      "", True)
plot("R2",       "BeamHalo", "BeamHalo/R2.pdf",      "R_{2}",      "", True)
plot("RP",       "BeamHalo", "BeamHalo/RPeak.pdf",   "R_{peak}",   "", True)
plot("RO",       "BeamHalo", "BeamHalo/ROuter.pdf",  "R_{outer}",  "", True)
#plot("NMu",      "BeamHalo", "BeamHalo/NMu.pdf",     "N_{#mu}",    "", True)
#plot("NCSC",     "BeamHalo", "BeamHalo/NCSC.pdf",    "N_{CSC}",    "", True)
#plot("NTrack",   "BeamHalo", "BeamHalo/NTrack.pdf",  "N_{track}",  "", True)
#plot("NVtx",     "BeamHalo", "BeamHalo/NVtx.pdf",    "N_{vtx}",    "", True)
#plot("BHFlag",   "BeamHalo", "BeamHalo/BHFlag.pdf",  "Beam Halo",  "", True)

plot("JetE",     "BeamGas", "BeamGas/JetE.pdf",    "E [GeV]",    "", True)
plot("JetEta",   "BeamGas", "BeamGas/JetEta.pdf",  "#eta",       "", True)
plot("JetPhi",   "BeamGas", "BeamGas/JetPhi.pdf",  "#phi",       "", True)
plot("JetN60",   "BeamGas", "BeamGas/JetN60.pdf",  "n60",        "", True)
plot("JetN90",   "BeamGas", "BeamGas/JetN90.pdf",  "n90",        "", True)
plot("Ntow",     "BeamGas", "BeamGas/NTowers.pdf", "N_{towers}", "", True)
plot("IPhiFrac", "BeamGas", "BeamGas/IPhiFrac.pdf","f_{iphi}",   "", True)
plot("BX",       "BeamGas", "BeamGas/BX.pdf",      "BX_{rel}",   "", True, 0, -20., 20.)
plot("BXUP",     "BeamGas", "BeamGas/BXUP.pdf",    "BX_{wrt UP}","", True, 0, -20., 20.)
plot("R1",       "BeamGas", "BeamGas/R1.pdf",      "R_{1}",      "", True)
plot("R2",       "BeamGas", "BeamGas/R2.pdf",      "R_{2}",      "", True)
plot("RP",       "BeamGas", "BeamGas/RPeak.pdf",   "R_{peak}",   "", True)
plot("RO",       "BeamGas", "BeamGas/ROuter.pdf",  "R_{outer}",  "", True)
#plot("NMu",      "BeamGas", "BeamGas/NMu.pdf",     "N_{#mu}",    "", True)
#plot("NCSC",     "BeamGas", "BeamGas/NCSC.pdf",    "N_{CSC}",    "", True)
#plot("NTrack",   "BeamGas", "BeamGas/NTrack.pdf",  "N_{track}",  "", True)
#plot("NVtx",     "BeamGas", "BeamGas/NVtx.pdf",    "N_{vtx}",    "", True)
#plot("BHFlag",   "BeamGas", "BeamGas/BHFlag.pdf",  "Beam Halo",  "", True)

plot("JetE",     "Vertex", "Vertex/JetE.pdf",    "E [GeV]",    "", True)
plot("JetEta",   "Vertex", "Vertex/JetEta.pdf",  "#eta",       "", True)
plot("JetPhi",   "Vertex", "Vertex/JetPhi.pdf",  "#phi",       "", True)
plot("JetN60",   "Vertex", "Vertex/JetN60.pdf",  "n60",        "", True)
plot("JetN90",   "Vertex", "Vertex/JetN90.pdf",  "n90",        "", True)
plot("Ntow",     "Vertex", "Vertex/NTowers.pdf", "N_{towers}", "", True)
plot("IPhiFrac", "Vertex", "Vertex/IPhiFrac.pdf","f_{iphi}",   "", True)
plot("BX",       "Vertex", "Vertex/BX.pdf",      "BX_{rel}",   "", True, 0, -20., 20.)
plot("BXUP",     "Vertex", "Vertex/BXUP.pdf",    "BX_{wrt UP}","", True, 0, -20., 20.)
plot("R1",       "Vertex", "Vertex/R1.pdf",      "R_{1}",      "", True)
plot("R2",       "Vertex", "Vertex/R2.pdf",      "R_{2}",      "", True)
plot("RP",       "Vertex", "Vertex/RPeak.pdf",   "R_{peak}",   "", True)
plot("RO",       "Vertex", "Vertex/ROuter.pdf",  "R_{outer}",  "", True)
#plot("NMu",      "Vertex", "Vertex/NMu.pdf",     "N_{#mu}",    "", True)
#plot("NCSC",     "Vertex", "Vertex/NCSC.pdf",    "N_{CSC}",    "", True)
#plot("NTrack",   "Vertex", "Vertex/NTrack.pdf",  "N_{track}",  "", True)
#plot("NVtx",     "Vertex", "Vertex/NVtx.pdf",    "N_{vtx}",    "", True)
#plot("BHFlag",   "Vertex", "Vertex/BHFlag.pdf",  "Beam Halo",  "", True)

plot("JetE",     "Unid", "Unid/JetE.pdf",    "E [GeV]",    "", True)
plot("JetEta",   "Unid", "Unid/JetEta.pdf",  "#eta",       "", True)
plot("JetPhi",   "Unid", "Unid/JetPhi.pdf",  "#phi",       "", True)
plot("JetN60",   "Unid", "Unid/JetN60.pdf",  "n60",        "", True)
plot("JetN90",   "Unid", "Unid/JetN90.pdf",  "n90",        "", True)
plot("Ntow",     "Unid", "Unid/NTowers.pdf", "N_{towers}", "", True)
plot("IPhiFrac", "Unid", "Unid/IPhiFrac.pdf","f_{iphi}",   "", True)
plot("BX",       "Unid", "Unid/BX.pdf",      "BX_{rel}",   "", True, 0, -20., 20.)
plot("BXUP",     "Unid", "Unid/BXUP.pdf",    "BX_{wrt UP}","", True, 0, -20., 20.)
plot("R1",       "Unid", "Unid/R1.pdf",      "R_{1}",      "", True)
plot("R2",       "Unid", "Unid/R2.pdf",      "R_{2}",      "", True)
plot("RP",       "Unid", "Unid/RPeak.pdf",   "R_{peak}",   "", True)
plot("RO",       "Unid", "Unid/ROuter.pdf",  "R_{outer}",  "", True)
#plot("NMu",      "Unid", "Unid/NMu.pdf",     "N_{#mu}",    "", True)
#plot("NCSC",     "Unid", "Unid/NCSC.pdf",    "N_{CSC}",    "", True)
#plot("NTrack",   "Unid", "Unid/NTrack.pdf",  "N_{track}",  "", True)
#plot("NVtx",     "Unid", "Unid/NVtx.pdf",    "N_{vtx}",    "", True)
#plot("BHFlag",   "Unid", "Unid/BHFlag.pdf",  "Beam Halo",  "", True)
