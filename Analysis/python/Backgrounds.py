import sys
import optparse
import string
import os

# options
parser = optparse.OptionParser()
parser.add_option("-d", "--dir", action="store")
parser.add_option("-l", "--label", action="store")

(opts, args)=parser.parse_args()

dataset=opts.dir
label=opts.label

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
c.SetLogy()

# plot definition
def plot(name, ofile, xtitle="Fill", ytitle="Hz", xmin=0., xmax=0., doAll=False):

    h1 = file.Get("hNoise"+name)
    h2 = file.Get("hCosmic"+name)
    h3 = file.Get("hBeamHalo"+name)
    h4 = file.Get("hBeamGas"+name)
    h5 = file.Get("hVertex"+name)
    h6 = file.Get("hUnid"+name)

    norescale=["BX", "BXUP"]
    if not name in norescale:
        if (h2.Integral()>0) :
            h2.Scale(h1.Integral()/h2.Integral())
        if (h3.Integral()>0) :
            h3.Scale(h1.Integral()/h3.Integral())
        if (h4.Integral()>0) :
            h4.Scale(h1.Integral()/h4.Integral())
        if (h5.Integral()>0) :
            h5.Scale(h1.Integral()/h5.Integral())
        if (h6.Integral()>0) :
            h6.Scale(h1.Integral()/h6.Integral())

    norebin=["BX", "BXUP", "JetPhi", "Ntow", "NMu", "NCSC", "NTrack", "Nvtx", "BHFlag"]
    if (not name in norebin):
        h4.Rebin(5)
        h4.Scale(1./5.)
        h5.Rebin(5)
        h5.Scale(1./5.)

    ymax = max(h1.GetMaximum(), h2.GetMaximum(), h3.GetMaximum(), h4.GetMaximum(), h5.GetMaximum(), h6.GetMaximum())

    if (ymax != h1.GetMaximum()):
        h1.SetMaximum(1.1*ymax)

    if (xmax!=0.):
        h1.GetXaxis().SetRangeUser(xmin, xmax)
    
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

    if (doAll):
        h4.SetMarkerColor(2)
        h4.SetMarkerStyle(22)
        h4.Draw("SAME PE")
    
        h5.SetMarkerColor(4)
        h5.SetMarkerStyle(24)
        h5.Draw("SAME PE")

    h6.SetLineColor(6)
    h6.SetFillStyle(0)
    h6.Draw("SAME HIST")

    leg = TLegend(0.6, 0.77, 0.8, 0.93)
    leg.SetFillColor(0)
    leg.AddEntry(h1, "Noise", "L")
    leg.AddEntry(h2, "Cosmic", "L")
    leg.AddEntry(h3, "Beam Halo", "L")
    leg.AddEntry(h4, "Beam Gas", "P")
    leg.AddEntry(h5, "Vertex", "P")
    leg.AddEntry(h6, "No ID", "L")
    leg.Draw()

    lab = TText(0.6, 0.7, label)
    lab.SetNDC()
    lab.Draw()
    
    c.Print(odir+ofile)

# start plotting
plot("JetE",     "JetE.pdf",    "E [GeV]", "")
plot("JetEta",   "JetEta.pdf",  "#eta", "")
plot("JetPhi",   "JetPhi.pdf",  "#phi", "")
plot("JetN60",   "JetN60.pdf",  "n60", "")
plot("JetN90",   "JetN90.pdf",  "n90", "")
plot("Ntow",     "NTowers.pdf", "N_{towers}", "")
plot("IPhiFrac", "IPhiFrac.pdf","f_{iphi}", "")
plot("NMu",      "NMu.pdf",     "N_{#mu}", "")
plot("NCSC",     "NCSC.pdf",    "N_{CSC}", "")
plot("NTrack",   "NTrack.pdf",  "N_{track}", "")
plot("NVtx",     "NVtx.pdf",    "N_{vtx}", "")
plot("BHFlag",   "BHFlag.pdf",  "Beam Halo", "")
plot("BX",       "BX.pdf",      "BX_{rel}", "", -20., 20.)
plot("BXUP",     "BXUP.pdf",    "BX_{wrt UP}", "", -20., 20.)
plot("R1",       "R1.pdf",      "R_{1}", "")
plot("R2",       "R2.pdf",      "R_{2}", "")
plot("RP",       "RPeak.pdf",   "R_{peak}", "")
plot("RO",       "ROuter.pdf",  "R_{outer}", "")

plot("JetE",     "JetEAll.pdf",    "E [GeV]", "", 0., 0., True)
plot("JetEta",   "JetEtaAll.pdf",  "#eta", "", 0., 0., True)
plot("JetPhi",   "JetPhiAll.pdf",  "#phi", "", 0., 0., True)
plot("JetN60",   "JetN60All.pdf",  "n60", "", 0., 0., True)
plot("JetN90",   "JetN90All.pdf",  "n90", "", 0., 0., True)
plot("Ntow",     "NTowersAll.pdf", "N_{towers}", "", 0., 0., True)
plot("IPhiFrac", "IPhiFracAll.pdf","f_{iphi}", "", 0., 0., True)
plot("NMu",      "NMuAll.pdf",     "N_{#mu}", "", 0., 0., True)
plot("NCSC",     "NCSCAll.pdf",    "N_{CSC}", "", 0., 0., True)
plot("NTrack",   "NTrackAll.pdf",  "N_{track}", "", 0., 0., True)
plot("NVtx",     "NVtxAll.pdf",    "N_{vtx}", "", 0., 0., True)
plot("BHFlag",   "BHFlagAll.pdf",  "Beam Halo", "", 0., 0., True)
plot("BX",       "BXAll.pdf",      "BX_{rel}", "", -20., 20., True)
plot("BXUP",     "BXUPAll.pdf",    "BX_{wrt UP}", "", -20., 20., True)
plot("R1",       "R1All.pdf",      "R_{1}", "", 0., 0., True)
plot("R2",       "R2All.pdf",      "R_{2}", "", 0., 0., True)
plot("RP",       "RPeakAll.pdf",   "R_{peak}", "", 0., 0., True)
plot("RO",       "ROuterAll.pdf",  "R_{outer}", "", 0., 0., True)


c.SetLogy(0)
c.SetLogz()
hoverlap = file.Get("hOverlap")
scale = hoverlap.GetBinContent(1,1)
hoverlap.Scale(100./scale)
hoverlap.SetTitle(hoverlap.GetTitle()+" "+label)
hoverlap.Draw("COLZ TEXT")
c.Print(odir+"Overlap.pdf")

