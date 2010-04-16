
# methods to make basic distributions

from ROOT import *

from histograms import *
from plots import *


# plot histograms
def basicPlots(file, dir, scale, ofile):
    
    # reminder of method arguments
    # histPlot(hist, file, norm=False, log=False, title="histogram", xtitle="", ytitle="", opt="HIST")
    # hist2DPlot(hist, file, norm=False, log=False, title="histogram", xtitle="", ytitle="", ztitle="", opt="")

    # L1 trigger
    histPlot(dir+"/hl1et", file, ofile, scale, True, "", "E_{L1} (GeV)", "")
    histPlot(dir+"/hl1eta", file, ofile, scale, True, "", "#eta", "")
    histPlot(dir+"/hl1phi", file, ofile, scale, True, "", "#phi", "")
    
    # HLT
    histPlot(dir+"/hhlte", file, ofile, scale, True, "", "E_{HLT} (GeV)", "")
    histPlot(dir+"/hhlteta", file, ofile, scale, True, "", "#eta", "")
    histPlot(dir+"/hhltphi", file, ofile, scale, True, "", "#phi", "")

    # misc
    histPlot(dir+"/hntowsamephi", file, ofile, scale, True, "", "N_{towers}", "")

    # jet variables
    histPlot(dir+"/hjete2", file, ofile, scale, True, "", "E (GeV)", "E")
    histPlot(dir+"/hjeteta", file, ofile, scale, True, "", "#eta", "E")
    histPlot(dir+"/hjetphi", file, ofile, scale, True, "", "#phi", "E")
    histPlot(dir+"/hjetem", file, ofile, scale, True, "", "E_{ECAL}", "E")
    histPlot(dir+"/hjethad", file, ofile, scale, True, "", "E_{HCAL}", "E")
    histPlot(dir+"/hjetn60", file, ofile, scale, True, "", "n60", "E")
    histPlot(dir+"/hjetn90", file, ofile, scale, True, "", "n90", "E")

    # muon variables
    histPlot(dir+"/hnmu", file, ofile, scale, True, "", "N_{#mu}", "")

    # pulse shape variables
    histPlot(dir+"/hr1", file, ofile, scale, False, "", "R1", "")
    histPlot(dir+"/hr2", file, ofile, scale, False, "", "R2", "")
    histPlot(dir+"/hpk", file, ofile, scale, False, "", "R_{peak}", "")
    histPlot(dir+"/hout", file, ofile, scale, False, "", "R_{outer}", "")

    # 2D timing plots
    hist2DPlot(dir+"/hr1r2", file, ofile, scale, True, "", "R_{2}", "R_{1}", "", "CONT")
    hist2DPlot(dir+"/hpkout", file, ofile, scale, True, "", "R_{out}", "R_{peak}", "", "CONT")


def timePlots(file, ofilename):

    dir = "NoCuts"

    histPlot(dir+"/hbx", file, ofilename, 0., True, "", "BX", "N events")
    histPlot(dir+"/hlb", file, ofilename, 0., True, "", "LS", "Rate")
    histPlot(dir+"/hlbdist", file, ofilename, 0., True, "", "Rate", "N LS")



# plot some basic distributions
def basicHistos(tree, file, dir, cuts, scale) :

    if (dir!=""):
        file.mkdir(dir)
        file.cd(dir)

    histogram1D(tree, "hbx", "bx>>hbx", cuts, scale, "BX number (new)", 3564, 0., 3564.)
    histogram1D(tree, "horb", "orbit>>horb", cuts, scale, "Orbit number (new)", 100, 0., 10000.)    
    hlb=histogram1D(tree, "hlb", "lb>>hlb", cuts, scale, "Lumi block", 2000, 0., 2000.)  
    histogram1D(tree, "htime", "time>>htime", cuts, scale, "Event time", 100, 0., 1.E8)

    # HLT rate per LS
    hlb.Scale(1./lumiBlockLength)  
    rateDist(hlb, 100)

    # trigger
    histogram1D(tree, "hl1et", "l1JetEt[0]>>hl1et", cuts, scale, "Leading L1 jet E_{t} (new)", 100, 0., 200.)  
    histogram1D(tree, "hl1eta", "l1JetEta[0]>>hl1eta", cuts, scale, "Leading L1 jet #eta (new)", 70, -3.5, 3.5)  
    histogram1D(tree, "hl1phi", "l1JetPhi[0]>>hl1phi", cuts, scale, "Leading L1 jet #phi (new)", 60, TMath.Pi()*-1., TMath.Pi())  
    histogram1D(tree, "hhlte", "hltJetE[0]>>hhlte", cuts, scale, "Leading HLT jet energy (new)", 100, 0., 200.)      
    histogram1D(tree, "hhlteta", "hltJetEta[0]>>hhlteta", cuts, scale, "Leading HLT jet #eta (new)", 70, -3.5, 3.5)  
    histogram1D(tree, "hhltphi", "hltJetPhi[0]>>hhltphi", cuts, scale, "Leading HLT jet #phi (new)", 60, -1 * pi, pi)

    # global quantities
    histogram1D(tree, "hntowsamephi", "nTowerSameiPhi>>hntowsamephi", cuts, scale, "N leading towers at same iphi (new)", 20, -0.5, 19.5)

    # jets
    histogram1D(tree, "hjete", "jetE[0]>>hjete", cuts, scale, "Leading jet energy", 50, 0., 500.)
    histogram1D(tree, "hjete2", "jetE[0]>>hjete2", cuts, scale, "Leading jet energy (zoom)", 50, 0., 200.)
    histogram1D(tree, "hjeteta", "jetEta[0]>>hjeteta", cuts, scale, "Leading jet #eta", 70, -3.5, 3.5)
    histogram1D(tree, "hjetphi", "jetPhi[0]>>hjetphi", cuts, scale, "Leading jet #phi", 60, -1 * pi, pi)
    histogram1D(tree, "hjetem", "jetEEm[0]>>hjetem", cuts, scale, "Leading jet ECAL energy", 100, 0., 200.)
    histogram1D(tree, "hjethad", "jetEHad[0]>>hjethad", cuts, scale, "Leading jet HCAL energy", 100, 0., 200.)
    histogram1D(tree, "hjetn60", "jetN60[0]>>hjetn60", cuts, scale, "Leading jet N60", 50, 0., 50.)
    histogram1D(tree, "hjetn90", "jetN90[0]>>hjetn90", cuts, scale, "Leading jet N90", 50, 0., 50.)

    
    # muons
    histogram1D(tree, "hnmu", "mu_N>>hnmu", cuts, scale, "N muons", 4, -0.5, 3.5)

    # timing distributions (before any cuts)
    histogram1D(tree, "hr1", "top5DigiR1>>hr1", cuts, scale, "R_{1}", 50, 0., 1.)
    histogram1D(tree, "hr2", "top5DigiR2>>hr2", cuts, scale, "R_{2}", 50, 0., 1.)
    histogram1D(tree, "hpk", "top5DigiRPeak>>hpk", cuts, scale, "R_{peak}", 50, 0., 1.)
    histogram1D(tree, "hout", "top5DigiROuter>>hout", cuts, scale, "R_{outer}", 30, 0., 1.)
    
    # 2D timing histograms
    hr1r2 = TH2D("hr1r2", "R_{1} vs R_{2}", 50, 0., 1., 50, 0., 1.)
    tree.Draw("top5DigiR1:top5DigiR2>>hr1r2", cuts)
    for i in range(1,100):
        hr1r2.SetBinContent(1,i,0.)
        hr1r2.SetBinContent(i,1,0.)
    hr1r2.Scale(scale)
    hr1r2.Write()
    
    hpkout = TH2D("hpkout", "R_{peak} vs R_{outer}", 50, 0., 1., 50, 0., 1.)
    tree.Draw("top5DigiRPeak:top5DigiROuter>>hpkout", cuts)
    for i in range(1,100):
        hpkout.SetBinContent(1,i,0.)
        hpkout.SetBinContent(i,1,0.)
    hpkout.Scale(scale)
    hpkout.Write()

    file.cd()



