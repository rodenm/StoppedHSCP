#! /usr/bin/env python

#
# Make plots of halo BG
#

import sys
import optparse
import string
import os

# options
parser = optparse.OptionParser()
parser.add_option("-d", "--dir", action="store")
parser.add_option("-c", "--control", action="store")
parser.add_option("-m", "--method", action="store", default="12")
#parser.add_option("-e", "--era", action="store")
#parser.add_option("-t", "--type", action="store", default="")

(opts, args)=parser.parse_args()

#type=opts.type
#fillset=opts.era
dataset=str(opts.dir)
control=str(opts.control)

# ROOT meh
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

# output file
ofile = dataset+"/"+dataset+"_Halo.ps"
opdf = dataset+"/"+dataset+"_Halo.pdf"

# prepare canvas for plotting
canvas = TCanvas("c")
canvas.SetLogy(1)
canvas.Print(ofile+"[", "Portrait")

# open file
ifile1 = TFile(dataset+"/histograms.root", "read")
ifile2 = TFile(dataset+"/HaloBackground.root", "read")
cfile  = TFile(control+"/HaloBackground.root", "read")

# get histogram of time per fill
hfilltime = ifile1.Get("fills/hfilltime")

hExpByFill = TH1D("hExpByFill", "Halo estimate", 30, 0., 0.)
hObsByFill = TH1D("hObsByFill", "Halo observed", 30, 0., 0.)


#
def doBG(fill):

    hsig = ifile2.Get("ByFillSignalTaggedJetE/ByFillSignalTaggedJetE"+str(fill))
    hexp = ifile2.Get("ByFillExpJetE/ByFillExpJetE"+str(fill))
    hnorm = ifile2.Get("ByFillNormTaggedJetE/ByFillNormTaggedJetE"+str(fill))

    # estimate background
    exp = hexp.Integral(19, 52)
    obs = hsig.Integral(19, 52)

    hExpByFill.Fill(str(fill), exp)
    hObsByFill.Fill(str(fill), obs)

    print "Fill", fill
    print "Expected total       : ", exp
    print "Observed total       : ", obs
    print "Unobserved fraction  : ", 1-(obs/exp)
    print


    # make plot
    canvas.SetLogy()

    hexp.SetLineColor(4)
    hexp.SetMarkerColor(4)
    hsig.SetLineColor(1)
    hsig.SetMarkerColor(1)
    hnorm.SetMarkerColor(2)
    hnorm.SetLineColor(2)
    
    hexp.SetAxisRange(0., 200.)
    hnorm.SetAxisRange(52., 67.)

    hexp.Draw()
    hsig.Draw("SAME")
    hnorm.Draw("SAME")

    leg = TLegend(0.65, 0.65, 0.95, 0.75)
    leg.SetFillColor(0)
    leg.SetBorderSize(1)
    leg.AddEntry(hexp, "Exp", "L")
    leg.AddEntry(hsig, "Sig", "L")
    leg.Draw()

    text = TPaveText(0.2, 0.2, 0.35, 0.3, "NDC")
    text.SetFillColor(0)
    text.SetBorderSize(1)
    text.AddText("Exp="+str(exp))
    text.AddText("Obs="+str(obs))
    text.Draw()

    canvas.Print(ofile)


if ("1" in opts.method):

    print "Method 1"

    # loop over fills
    for i in range(1, hfilltime.GetXaxis().GetNbins()):
        
        fill = int(hfilltime.GetXaxis().GetBinLabel(i))
        
        doBG(fill)


    expTot = hExpByFill.Integral()
    sigTot = hObsByFill.Integral()
    
    print "Total"
    print "Expected total       : ", expTot
    print "Observed total       : ", sigTot
    print "Unobserved fraction  : ", 1-(sigTot/expTot)
    print
    
    canvas.SetLogy(0)
    
    hExpByFill.SetLineColor(1)
    hExpByFill.SetMarkerColor(1)
    hExpByFill.SetFillStyle(0)
    hObsByFill.SetLineColor(2)
    hObsByFill.SetMarkerColor(2)
    hObsByFill.SetFillStyle(0)
    
    hExpByFill.Draw("PE0")
    hObsByFill.Draw("SAME PE0")
    
    leg = TLegend(0.65, 0.65, 0.95, 0.75)
    leg.SetFillColor(0)
    leg.SetBorderSize(1)
    leg.AddEntry(hExpByFill, "Exp", "L")
    leg.AddEntry(hObsByFill, "Obs", "L")
    leg.Draw()

    text = TPaveText(0.2, 0.2, 0.35, 0.3, "NDC")
    text.SetFillColor(0)
    text.SetBorderSize(1)
    text.AddText("Exp="+str(expTot))
    text.AddText("Obs="+str(sigTot))
    text.Draw()
    
    canvas.Print(ofile, "Portrait")


# method 2
# get control histogram from (eg.) Run2010B and normalise using low energy region

hcontrol = cfile.Get("hControlJetE")

hExpByFill2 = TH1D("hExpByFill2", "Halo estimate", 30, 0., 0.)
hObsByFill2 = TH1D("hObsByFill2", "Halo observed", 30, 0., 0.)


def doBG2(fill):

    hsig = ifile2.Get("ByFillSignalTaggedJetE/ByFillSignalTaggedJetE"+str(fill))
    hnorm = ifile2.Get("ByFillNormTaggedJetE/ByFillNormTaggedJetE"+str(fill))

    hexp = hcontrol.Clone("hcontrol"+str(fill))

    hexp.Scale(hnorm.Integral(14,18)/hexp.Integral(14,18))

    # estimate background
    exp = hexp.Integral(19, 52)
    obs = hsig.Integral(19, 52)

    hExpByFill2.Fill(str(fill), exp)
    hObsByFill2.Fill(str(fill), obs)

    print "Fill", fill
    print "Expected total       : ", exp
    print "Observed total       : ", obs
    print "Unobserved fraction  : ", 1-(obs/exp)
    print

    # make plot
    canvas.SetLogy()

    hexp.SetLineColor(4)
    hexp.SetMarkerColor(4)
    hsig.SetLineColor(1)
    hsig.SetMarkerColor(1)
    hnorm.SetMarkerColor(2)
    hnorm.SetLineColor(2)
    
    hexp.SetAxisRange(0., 200.)
    hnorm.SetAxisRange(52., 67.)

    hexp.Draw()
    hsig.Draw("SAME")
    hnorm.Draw("SAME")

    leg = TLegend(0.65, 0.65, 0.95, 0.75)
    leg.SetFillColor(0)
    leg.SetBorderSize(1)
    leg.AddEntry(hexp, "Exp", "L")
    leg.AddEntry(hsig, "Obs", "L")
    leg.Draw()

    text = TPaveText(0.2, 0.2, 0.35, 0.3, "NDC")
    text.SetFillColor(0)
    text.SetBorderSize(1)
    text.AddText("Exp="+str(exp))
    text.AddText("Obs="+str(obs))
    text.Draw()
    
    canvas.Print(ofile)
    
if ("2" in opts.method):

    print "Method 2"

    # loop over fills
    for i in range(1, hfilltime.GetXaxis().GetNbins()):
        
        fill = int(hfilltime.GetXaxis().GetBinLabel(i))
        
        doBG2(fill)


    expTot = hExpByFill2.Integral()
    sigTot = hObsByFill2.Integral()
    
    print "Expected total       : ", expTot
    print "Observed total       : ", sigTot
    print "Unobserved fraction  : ", 1-(sigTot/expTot)
    print
    
    canvas.SetLogy(0)
    
    hExpByFill2.SetLineColor(1)
    hExpByFill2.SetMarkerColor(1)
    hExpByFill2.SetFillStyle(0)
    hObsByFill2.SetLineColor(2)
    hObsByFill2.SetMarkerColor(2)
    hObsByFill2.SetFillStyle(0)
    
    hExpByFill2.Draw("PE0")
    hObsByFill2.Draw("SAME PE0")
    
    leg = TLegend(0.65, 0.65, 0.95, 0.75)
    leg.SetFillColor(0)
    leg.SetBorderSize(1)
    leg.AddEntry(hExpByFill2, "Exp", "L")
    leg.AddEntry(hObsByFill2, "Sig", "L")
    leg.Draw()

    text = TPaveText(0.2, 0.2, 0.35, 0.3, "NDC")
    text.SetFillColor(0)
    text.SetBorderSize(1)
    text.AddText("Exp="+str(expTot))
    text.AddText("Obs="+str(sigTot))
    text.Draw()

    canvas.Print(ofile, "Portrait")


# method 3

if ("3" in opts.method):

    hobs = ifile2.Get("hSignalTaggedJetE")
    hobseta = ifile2.Get("hSignalTaggedJetEta")
    hobsphi = ifile2.Get("hSignalTaggedJetPhi")

    hcon = cfile.Get("hControlJetE")
    hconeta = cfile.Get("hControlJetEta")
    hconphi = cfile.Get("hControlJetPhi")

    hnorm = ifile2.Get("hNormTaggedJetE")

    norm = hnorm.Integral(14,18)/hcon.Integral(14,18)

    hcon.Scale(norm)
    hconeta.Scale(norm)
    hconphi.Scale(norm)
    
    # estimate background
    exp = hcon.Integral(19, 52)
    obs = hobs.Integral(19, 52)

    print "Method 3"
    print "Expected total       : ", exp
    print "Observed total       : ", obs
    print "Unobserved fraction  : ", 1-(obs/exp)
    print

    # make jet E plot
    canvas.SetLogy()

    hcon.SetLineColor(4)
    hcon.SetMarkerColor(4)
    hobs.SetLineColor(1)
    hobs.SetMarkerColor(1)
    hnorm.SetMarkerColor(2)
    hnorm.SetLineColor(2)
    
    hcon.SetAxisRange(0., 200.)
    hnorm.SetAxisRange(52., 67.)

    hcon.Draw()
    hobs.Draw("SAME")
    hnorm.Draw("SAME")

    leg = TLegend(0.65, 0.65, 0.95, 0.75)
    leg.SetFillColor(0)
    leg.SetBorderSize(1)
    leg.AddEntry(hcon, "Exp", "L")
    leg.AddEntry(hobs, "Obs", "L")
    leg.Draw()

    text = TPaveText(0.2, 0.2, 0.35, 0.3, "NDC")
    text.SetFillColor(0)
    text.SetBorderSize(1)
    text.AddText("Exp="+str(exp))
    text.AddText("Obs="+str(obs))
    text.Draw()
    
    canvas.Print(ofile)

    # make jet eta plot
    canvas.SetLogy()

    hconeta.SetLineColor(4)
    hconeta.SetMarkerColor(4)
    hobseta.SetLineColor(1)
    hobseta.SetMarkerColor(1)

    hconeta.Draw()
    hobseta.Draw("SAME")

    leg = TLegend(0.65, 0.65, 0.95, 0.75)
    leg.SetFillColor(0)
    leg.SetBorderSize(1)
    leg.AddEntry(hconeta, "Exp", "L")
    leg.AddEntry(hobseta, "Obs", "L")
    leg.Draw()

    canvas.Print(ofile)

    # make jet phi plot
    canvas.SetLogy()

    hconphi.SetLineColor(4)
    hconphi.SetMarkerColor(4)
    hobsphi.SetLineColor(1)
    hobsphi.SetMarkerColor(1)

    hconphi.Draw()
    hobsphi.Draw("SAME")

    leg = TLegend(0.65, 0.65, 0.95, 0.75)
    leg.SetFillColor(0)
    leg.SetBorderSize(1)
    leg.AddEntry(hconphi, "Exp", "L")
    leg.AddEntry(hobsphi, "Obs", "L")
    leg.Draw()

    canvas.Print(ofile)




# close file
canvas = TCanvas("c")
canvas.Print(ofile+"]")

# convert to PDF
subprocess.call(["ps2pdf", ofile, opdf])
subprocess.call(["rm", ofile])
