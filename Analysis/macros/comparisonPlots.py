
from ROOT import *

from style import *


# set the style
tdrStyle()
gROOT.SetStyle("tdrStyle")
gROOT.ForceStyle()

# style options for this macro

gStyle.SetHistFillStyle(0)

# open files
file08 = TFile("22X_Ben/BasicHistosOld.root") # histos from Ben's original ntuples
file09 = TFile("v13/BasicHistosOld.root")  # latest CRAFT 09 results


# output file
ps = TPostScript("craft09_vs_craft08.ps")


canvas = TCanvas("canvas")
canvas.SetLogy()

# L1
##   hl1et.SetXTitle("E (GeV)");
##   hl1et.SetYTitle("Hz / 2 GeV");
##   hl1et.Draw("HIST");
##   hl1et08 = (TH1D*)file08.Get("hl1et");
##   hl1et08.SetLineColor(2);
##   hl1et08.Draw("HIST SAME");
##   canvas.Update();

##   hl1eta = (TH1D*)file09.Get("hl1eta");
##   hl1eta.SetXTitle("#eta");
##   hl1eta.SetYTitle("Hz / 0.1");
##   hl1eta.Draw("HIST");
##   hl1eta08 = (TH1D*)file08.Get("hl1eta");
##   hl1eta08.SetLineColor(2);
##   hl1eta08.Draw("HIST SAME");
##   canvas.Update();

##   hl1phi = (TH1D*)file09.Get("hl1phi");
##   hl1phi.SetXTitle("E (GeV)");
##   hl1phi.SetYTitle("Hz / #pi/30");
##   hl1phi.Draw("HIST");
##   hl1phi08 = (TH1D*)file08.Get("hl1phi");
##   hl1phi08.SetLineColor(2);
##   hl1phi08.Draw("HIST SAME");
##   canvas.Update();

# offline jets
hjete08 = file08.Get("hjete2")
hjete08.SetXTitle("E (GeV)")
hjete08.SetYTitle("Hz / 2 GeV")
hjete09 = file09.Get("hjete2")
hjete09.SetXTitle("E (GeV)")
hjete09.SetYTitle("Hz / 2 GeV")
hjete09.SetLineColor(2)
hjete08.Draw("HIST")
hjete09.Draw("HIST SAME")
canvas.Update()

hjeteta = file09.Get("hjeteta");
hjeteta.SetXTitle("#eta");
hjeteta.SetYTitle("Hz / 0.1");
hjeteta.SetLineColor(2);
hjeteta08 = file08.Get("hjeteta");
hjeteta08.SetXTitle("#eta");
hjeteta08.SetYTitle("Hz / 0.1");
hjeteta08.Draw("HIST");
hjeteta.Draw("HIST SAME");
canvas.Update();

hjetphi = file09.Get("hjetphi");
hjetphi.SetXTitle("#phi");
hjetphi.SetYTitle("Hz / #pi/30");
hjetphi.SetLineColor(2);
hjetphi08 = file08.Get("hjetphi");
hjetphi08.SetXTitle("#phi");
hjetphi08.SetYTitle("Hz / #pi/30");
hjetphi08.Draw("HIST");
hjetphi.Draw("HIST SAME");
canvas.Update();

hjetem = file09.Get("hjetem");
hjetem.SetXTitle("E_{ECAL} / GeV");
hjetem.SetYTitle("Hz / 2 GeV");
hjetem.SetLineColor(2);
hjetem08 = file08.Get("hjetem");
hjetem08.SetXTitle("E_{ECAL} / GeV");
hjetem08.SetYTitle("Hz / 2 GeV");
hjetem08.Draw("HIST");
hjetem.Draw("HIST SAME");
canvas.Update();

hjethad = file09.Get("hjethad");
hjethad.SetXTitle("E_{HCAL} / GeV");
hjethad.SetYTitle("Hz / 2 GeV");
hjethad.SetLineColor(2);
hjethad08 = file08.Get("hjethad");
hjethad08.SetXTitle("E_{HCAL} / GeV");
hjethad08.SetYTitle("Hz / 2 GeV");
hjethad08.Draw("HIST");
hjethad.Draw("HIST SAME");
canvas.Update();

hjetn60 = file09.Get("hjetn60");
hjetn60.SetXTitle("n60");
hjetn60.SetYTitle("N");
hjetn60.SetLineColor(2);
hjetn6008 = file08.Get("hjetn60");
hjetn6008.SetXTitle("n60");
hjetn6008.SetYTitle("N");
hjetn6008.Draw("HIST");
hjetn60.Draw("HIST SAME");
canvas.Update();

hjetn90 = file09.Get("hjetn90");
hjetn90.SetXTitle("n90");
hjetn90.SetYTitle("N");
hjetn90.SetLineColor(2);
hjetn9008 = file08.Get("hjetn90");
hjetn9008.SetXTitle("n90");
hjetn9008.SetYTitle("N");
hjetn9008.Draw("HIST");
hjetn90.Draw("HIST SAME");
canvas.Update();

hnmu = file09.Get("hnmu");
hnmu.SetXTitle("N_{#mu}");
hnmu.SetYTitle("Hz");
hnmu.SetLineColor(2);
hnmu08 = file08.Get("hnmu");
hnmu08.SetXTitle("N_{#mu}");
hnmu08.SetYTitle("Hz");
hnmu08.Draw("HIST");
hnmu.Draw("HIST SAME");
canvas.Update();

##   hmupt = file09.Get("hmupt");
##   hmupt.SetXTitle("p_{t}^{#mu}");
##   hmupt.SetYTitle("Hz / 1 GeV");
##   hmupt.Draw("HIST");
##   hmupt08 = file08.Get("hmupt");
##   hmupt08.SetLineColor(2);
##   hmupt08.Draw("HIST SAME");
##   canvas.Update();

##   hntow = file09.Get("hntow");
##   hntow.SetXTitle("N_{towers}");
##   hntow.SetYTitle("Hz");
##   hntow.Draw("HIST");
##   hntow08 = file08.Get("hntow");
##   hntow08.SetLineColor(2);
##   hntow08.Draw("HIST SAME");
##   canvas.Update();

##   htowe = file09.Get("htowe");
##   htowe.SetXTitle("E (GeV)");
##   htowe.SetYTitle("Hz / 2 GeV");
##   htowe.Draw("HIST");
##   htowe08 = file08.Get("htowe");
##   htowe08.SetLineColor(2);
##   htowe08.Draw("HIST SAME");
##   canvas.Update();

##   htowem = file09.Get("htowem");
##   htowem.SetXTitle("E (GeV)");
##   htowem.SetYTitle("Hz / 2 GeV");
##   htowem.Draw("HIST");
##   htowem08 = file08.Get("htowem");
##   htowem08.SetLineColor(2);
##   htowem08.Draw("HIST SAME");
##   canvas.Update();

##   htowhad = file09.Get("htowhad");
##   htowhad.SetXTitle("E (GeV)");
##   htowhad.SetYTitle("Hz / 2 GeV");
##   htowhad.Draw("HIST");
##   htowhad08 = file08.Get("htowhad");
##   htowhad08.SetLineColor(2);
##   htowhad08.Draw("HIST SAME");
##   canvas.Update();

hEffJetE = file09.Get("heffjete");
hEffJetE.Scale(1/hEffJetE.Integral(0,100))
hEffJetE.SetLineColor(2);
hEffJetE.SetXTitle("GeV");
hEffJetE08 = file08.Get("heffjete");
hEffJetE08.SetXTitle("GeV");
hEffJetE08.Scale(1/hEffJetE08.Integral(0,100))
hEffJetE08.Draw("HIST");
hEffJetE.Draw("HIST SAME");
canvas.Update();

##   hEffJetEta08 = file08.Get("heffjeteta");
##   hEffJetEta08.SetLineColor(2);
##   hEffJetEta08.Draw("HIST");
##   hEffJetEta = file09.Get("heffjeteta");
##   hEffJetEta.Draw("SAME HIST");
##   canvas.Update();

hEffJetN60 = file09.Get("heffjetn60");
hEffJetN60.SetLineColor(2);
hEffJetN60.Scale(1/hEffJetN60.Integral())
hEffJetN60.SetXTitle("N");
hEffJetN6008 = file08.Get("heffjetn60");
hEffJetN6008.Scale(1/hEffJetN6008.Integral())
hEffJetN6008.SetXTitle("N");
hEffJetN6008.Draw("HIST");
hEffJetN60.Draw("HIST SAME");
canvas.Update();

hEffJetN90 = file09.Get("heffjetn90");
hEffJetN90.SetLineColor(2);
hEffJetN90.Scale(1/hEffJetN90.Integral())
hEffJetN90.SetXTitle("N");
hEffJetN9008 = file08.Get("heffjetn90");
hEffJetN9008.Scale(1/hEffJetN9008.Integral())
hEffJetN9008.SetXTitle("N");
hEffJetN9008.Draw("HIST");
hEffJetN90.Draw("HIST SAME");
canvas.Update();

hEffMuVeto = file09.Get("heffnmu");
hEffMuVeto.SetLineColor(2);
hEffMuVeto.Scale(1/hEffMuVeto.Integral())
hEffMuVeto.SetXTitle("N");
hEffMuVeto08 = file08.Get("heffnmu");
hEffMuVeto08.Scale(1/hEffMuVeto08.Integral())
hEffMuVeto08.SetXTitle("N");
hEffMuVeto.Draw("HIST");
hEffMuVeto08.Draw("HIST SAME");
canvas.Update();


##   hpeakall = file09.Get("peakfrac");
##   hpeakall.SetXTitle("s_{peak}/s_{total}");
##   hpeakall.SetYTitle("Hz");
##   hpeakall.Draw("HIST");
##   hpeak08all = file08.Get("peakfrac");
##   hpeak08all.SetLineColor(2);
##   hpeak08all.Draw("HIST SAME");
##   canvas.Update();

##   houtall = file09.Get("outfrac");
##   houtall.SetXTitle("s_{outer}/s_{total}");
##   houtall.SetYTitle("Hz");
##   houtall.Draw("HIST");
##   hout08all = file08.Get("outfrac");
##   hout08all.SetLineColor(2);
##   hout08all.Draw("HIST SAME");
##   canvas.Update();

##   hpeak08 = file08.Get("peakfrac");
##   hpeak08.SetXTitle("s_{peak}/s_{total}");
##   hpeak08.SetYTitle("Hz");
##   hpeak08.SetLineColor(2);
##   hpeak08.Draw("HIST");
##   hpeak = file09.Get("peakfrac");
##   hpeak.Draw("HIST SAME");
##   canvas.Update();

##   hout08 = file08.Get("outfrac");
##   hout08.SetXTitle("s_{outer}/s_{total}");
##   hout08.SetYTitle("Hz");
##   hout08.SetLineColor(2);
##   hout08.Draw("HIST");
##   hout = file09.Get("outfrac");
##   hout.Draw("HIST SAME");
##   canvas.Update();


ps.Close()
