# Marissa Rodenburg, February 2012
#
# Makes a pretty RECO efficiency plot called summer12_compareRECOeff_requireHBEB.pdf
#

import sys, os, time
from array import array
from ROOT import *

# Run in batch mode
ROOT.gROOT.SetBatch()

output = TFile('summer12Reproduction_RECOEff.root', 'RECREATE')

# stop and gluino points
gluinox = array('d',
                [300.0, 400.0, 500.0, 600.0, 700.0, 800.0, 900.0, 1000.0, 1100.0, 1200.0])
gluinoyNum = array('d',
                   [1657.,1594.,1593.,1640.,1710.,1734.,1816.,1922.,2093.,2189.])
gluinoyDen = array('d',
                   [3655., 3454., 3577., 3641., 3608., 3791., 3926., 4204., 4468., 4723.])

gluinoxErr = array('d',[0.,0.,0.,0.,0.,0.,0.,0.,0.,0.])
gluinoyErr = array('d',[0.,0.,0.,0.,0.,0.,0.,0.,0.,0.])
gluinoy = array('d',[0.,0.,0.,0.,0.,0.,0.,0.,0.,0.])

stopx = array('d',
              [300.0, 400.0, 500.0, 600.0, 700.0, 800.0])
stopyNum = array('d',
                 [1030.,979.,935.,941.,796.,793.])
stopyDen = array('d',
                 [3414., 3052., 2754., 2767., 2569., 2563.])

stopy = array('d',[0.,0.,0.,0.,0.,0.])
stopxErr = array('d',[0.,0.,0.,0.,0.,0.])
stopyErr = array('d',[0.,0.,0.,0.,0.,0.])

for i in xrange(0, len(gluinox)):
    gluinoy[i] = gluinoyNum[i]/gluinoyDen[i]
    gluinoyErr[i] = gluinoy[i]*sqrt(1.0/gluinoyNum[i] + 1.0/gluinoyDen[i])

for i in xrange(0, len(stopx)):
    stopy[i] = stopyNum[i]/stopyDen[i]
    stopyErr[i] = stopy[i]*sqrt(1.0/stopyNum[i] + 1.0/stopyDen[i])

# 2012 stop and gluino points
gluinox2012 = array('d',
                    [300.0, 400.0, 500.0, 600.0, 700.0, 800.0, 900.0, 1000.0, 1100.0, 1200.0, 1300., 1400., 1500.])
gluinoyNum2012 = array('d',
                       [1589.,1521.,1468.,1521.,1482.,1510.,1550.,1624.,1691.,1766.,1829.,1996.,2016.])
gluinoyDen2012 = array('d',
                       [4163.,3929.,3940.,3867.,3845.,3930.,3955.,4181.,4400.,4595.,4816.,5132.,5229.,])

gluinoxErr2012 = array('d',[0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.])
gluinoyErr2012 = array('d',[0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.])
gluinoy2012 = array('d',[0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.])

stopx2012 = array('d',
                  [300.0, 400.0, 500.0, 600.0, 700.0, 800.0, 900., 1000.])
stopyNum2012 = array('d',
                     [901.,835.,743.,772.,683.,669.,685.,668.])
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
geff_gluino     = TGraphErrors(len(gluinox), gluinox, gluinoy, gluinoxErr, gluinoyErr)
geff_stop       = TGraphErrors(len(stopx), stopx, stopy, stopxErr, stopyErr)

# TGraphs
geff_gluino2012 = TGraphErrors(len(gluinox2012), gluinox2012, gluinoy2012, gluinoxErr2012, gluinoyErr2012)
geff_stop2012   = TGraphErrors(len(stopx2012), stopx2012, stopy2012, stopxErr2012, stopyErr2012)

geff_gluino.SetTitle(';m [GeV];#varepsilon_{RECO}')
geff_gluino.SetMarkerStyle(8)
geff_gluino.SetMarkerSize(2)
geff_gluino.SetMarkerColor(kRed)
geff_gluino.SetLineColor(kRed)
geff_gluino.SetLineWidth(4)
geff_gluino.SetLineStyle(7)

geff_stop.SetTitle(';m [GeV];#varepsilon_{RECO}')
geff_stop.SetMarkerStyle(8)
geff_stop.SetMarkerSize(2)
geff_stop.SetMarkerColor(kBlue)
geff_stop.SetLineColor(kBlue)
geff_stop.SetLineWidth(4)
geff_stop.SetLineStyle(7)

geff_gluino2012.SetTitle(';m [GeV];#varepsilon_{RECO}')
geff_gluino2012.SetMarkerStyle(8)
geff_gluino2012.SetMarkerSize(2)
geff_gluino2012.SetMarkerColor(kRed)
geff_gluino2012.SetLineColor(kRed)
geff_gluino2012.SetLineWidth(4)

geff_stop2012.SetTitle(';m [GeV];#varepsilon_{RECO}')
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
mg.Add(geff_gluino)
mg.Add(geff_stop)
mg.Add(geff_gluino2012)
mg.Add(geff_stop2012)
mg.SetMaximum(0.8)
mg.SetMinimum(0.0)
mg.SetTitle(';M [GeV/c^{2}];#varepsilon_{detection}')
mg.Draw('aple')

gPad.Modified()
mg.GetXaxis().SetLimits(300,1500)

leg = TLegend(0.50, 0.65 ,0.89, 0.89)
leg.SetTextFont(42)
leg.AddEntry(geff_gluino2012, '2012 gluinos, #tilde{g} #tilde{g}', 'l')
leg.AddEntry(geff_gluino, '2011 gluinos, #tilde{g} #tilde{g}', 'l')
leg.AddEntry(geff_stop2012, '2012 stops, #tilde{t} #tilde{t}', 'l')
leg.AddEntry(geff_stop, '2011 stops, #tilde{t} #tilde{t}', 'l')
leg.SetHeader("CMS Simulation, 2011 #sqrt{s} = 7 TeV, 2012 #sqrt{s} = 8 TeV")
leg.SetFillColor(kWhite)
leg.SetBorderSize(0)
leg.Draw()

output.Write()
geff_gluino.Write()
geff_stop.Write()
geff_gluino2012.Write()
geff_stop2012.Write()
mg.Write()
c1.RedrawAxis()

c1.RedrawAxis()

#time.sleep(10)
c1.Print('summer12_compareRECOeff_requireHBEB.pdf')
