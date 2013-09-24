# Marissa Rodenburg, February 2012
#
# Makes a pretty stopping efficiency plot called summer11Reproduction_stoppingEff_requireHBEB.pdf
#

import sys, os, time
from array import array
from ROOT import *

# Run in batch mode
ROOT.gROOT.SetBatch()

output = TFile('summer12_stoppingEff.root', 'RECREATE')

# 2012 stop and gluino points
gluinox2012 = array('d',
                [300.0, 400.0, 500.0, 600.0, 700.0, 800.0, 900.0, 1000.0, 1100.0, 1200.0, 1300., 1400., 1500.])
gluinoyNum2012 = array('d',
                [2860.,2739.,2709.,2676.,2642.,2703.,2755.,2899.,3046.,3152.,3305.,3526.,3564.])
gluinoyDen2012 = array('d',
                [4163.,3929.,3940.,3867.,3845.,3930.,3955.,4181.,4400.,4595.,4816.,5132.,5229.,])
gluinoxErr2012 = array('d',[0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.])
gluinoyErr2012 = array('d',[0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.])
gluinoy2012 = array('d',[0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.])

stopx2012 = array('d',
                  [300.0, 400.0, 500.0, 600.0, 700.0, 800.0, 900., 1000.])
stopyNum2012 = array('d',
                     [2119.,1895.,1742.,1730.,1617.,1526.,1536.,1447.])
stopyDen2012 = array('d',
                     [3213.,2861.,2687.,2518.,2449.,2259.,2242.,2189.,])

stopy2012 = array('d',[0.,0.,0.,0.,0.,0.,0.,0.])
stopxErr2012 = array('d',[0.,0.,0.,0.,0.,0.,0.,0.])
stopyErr2012 = array('d',[0.,0.,0.,0.,0.,0.,0.,0.])

for i in xrange(0, len(gluinox2012)):
    gluinoy2012[i] = gluinoyNum2012[i]/gluinoyDen2012[i]
    gluinoyErr2012[i] = gluinoy2012[i]*sqrt(1.0/gluinoyNum2012[i] + 1.0/gluinoyDen2012[i])

for i in xrange(0, len(stopx2012)):
    stopy2012[i] = stopyNum2012[i]/stopyDen2012[i]
    stopyErr2012[i] = stopy2012[i]*sqrt(1.0/stopyNum2012[i] + 1.0/stopyDen2012[i])

# TGraphs
geff_gluino2012 = TGraphErrors(len(gluinox2012), gluinox2012, gluinoy2012, gluinoxErr2012, gluinoyErr2012)
geff_stop2012   = TGraphErrors(len(stopx2012), stopx2012, stopy2012, stopxErr2012, stopyErr2012)

geff_gluino2012.SetTitle(';M [GeV/c^{2}];#varepsilon_{trigger}')
geff_gluino2012.SetMarkerStyle(8)
geff_gluino2012.SetMarkerSize(2)
geff_gluino2012.SetMarkerColor(kRed)
geff_gluino2012.SetLineColor(kRed)
geff_gluino2012.SetLineWidth(4)

geff_stop2012.SetTitle(';m [GeV];#varepsilon_{trigger}')
geff_stop2012.SetMarkerStyle(8)
geff_stop2012.SetMarkerSize(2)
geff_stop2012.SetMarkerColor(kBlue)
geff_stop2012.SetLineColor(kBlue)
geff_stop2012.SetLineWidth(4)
#geff_stop2012.SetLineStyle(7)

c1 = TCanvas('c1', '', 1400,1000)
c1.SetGrid()

#blank.Draw()
#geff_gluino.Draw('ALPE1 same')
#geff_stop.Draw('ALPE1 same')

mg = TMultiGraph()
mg.Add(geff_gluino2012)
mg.Add(geff_stop2012)
mg.SetMaximum(1.0)
mg.SetMinimum(0.0)
mg.SetTitle(';M [GeV/c^{2}];#varepsilon_{trigger}')
mg.Draw('aple')

gPad.Modified()
mg.GetXaxis().SetLimits(300,1500)

leg = TLegend(0.50, 0.25 ,0.89, 0.49)
leg.SetTextFont(42)
leg.AddEntry(geff_gluino2012, '2012 gluinos, #tilde{g} #tilde{g}, E_{gluon} = 100 GeV', 'l')
leg.AddEntry(geff_stop2012, '2012 stops, #tilde{t} #tilde{t}, E_{top} = 180 GeV', 'l')
leg.SetHeader("CMS Simulation, #sqrt{s} = 8 TeV")
leg.SetFillColor(kWhite)
leg.SetBorderSize(0)
leg.Draw()

output.Write()
geff_gluino2012.Write()
geff_stop2012.Write()
mg.Write()
c1.RedrawAxis()

c1.RedrawAxis()

#time.sleep(10)
c1.Print('summer12_triggerEff_requireHBEB.pdf')
