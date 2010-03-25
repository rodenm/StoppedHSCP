
# methods to make basic distributions

from ROOT import *

from histograms import *
from plots import *


# plot histograms
def basicPlots(file, dir, scale):

    canvas = TCanvas("canvas")
    
    # reminder of method arguments
    # histPlot(hist, file, canvas, norm=False, log=False, title="histogram", xtitle="", ytitle="", opt="HIST")
    # hist2DPlot(hist, file, canvas, norm=False, log=False, title="histogram", xtitle="", ytitle="", ztitle="", opt="")

    # L1 trigger
    histPlot(dir+"/hl1et", file, canvas, scale, True, "", "E_{L1} (GeV)", "")
    histPlot(dir+"/hl1eta", file, canvas, scale, True, "", "#eta", "")
    histPlot(dir+"/hl1phi", file, canvas, scale, True, "", "#phi", "")
    
    # HLT
    histPlot(dir+"/hhlte", file, canvas, scale, True, "", "E_{HLT} (GeV)", "")
    histPlot(dir+"/hhlteta", file, canvas, scale, True, "", "#eta", "")
    histPlot(dir+"/hhltphi", file, canvas, scale, True, "", "#phi", "")

    # misc
    histPlot(dir+"/hntowsamephi", file, canvas, scale, True, "", "N_{towers}", "")

    # jet variables
    histPlot(dir+"/hjete2", file, canvas, scale, True, "", "E (GeV)", "E")
    histPlot(dir+"/hjeteta", file, canvas, scale, True, "", "#eta", "E")
    histPlot(dir+"/hjetphi", file, canvas, scale, True, "", "#phi", "E")
    histPlot(dir+"/hjetem", file, canvas, scale, True, "", "E_{ECAL}", "E")
    histPlot(dir+"/hjethad", file, canvas, scale, True, "", "E_{HCAL}", "E")
    histPlot(dir+"/hjetn60", file, canvas, scale, True, "", "n60", "E")
    histPlot(dir+"/hjetn90", file, canvas, scale, True, "", "n90", "E")

    # muon variables
    histPlot(dir+"/hnmu", file, canvas, scale, True, "", "N_{#mu}", "")


    # pulse shape variables
    histPlot(dir+"/hr1", file, canvas, scale, False, "", "R1", "")
    histPlot(dir+"/hr2", file, canvas, scale, False, "", "R2", "")
    histPlot(dir+"/hpk", file, canvas, scale, False, "", "R_{peak}", "")
    histPlot(dir+"/hout", file, canvas, scale, False, "", "R_{outer}", "")

    # 2D timing plots
    hist2DPlot(dir+"/hr1r2", file, canvas, scale, True, "", "R_{2}", "R_{1}", "", "CONT")
    hist2DPlot(dir+"/hpkout", file, canvas, scale, True, "", "R_{out}", "R_{peak}", "", "CONT")



# plot some basic distributions
def basicHistos(tree, file, dir, cuts, scale) :

    if (dir!=""):
        file.mkdir(dir)
        file.cd(dir)

    # trigger
    histogram1D(tree, "hl1et", "l1Jets[0].et>>hl1et", cuts, scale, "Leading L1 jet E_{t} (new)", 100, 0., 200.)  
    histogram1D(tree, "hl1eta", "l1Jets[0].eta>>hl1eta", cuts, scale, "Leading L1 jet #eta (new)", 70, -3.5, 3.5)  
    histogram1D(tree, "hl1phi", "l1Jets[0].phi>>hl1phi", cuts, scale, "Leading L1 jet #phi (new)", 60, TMath.Pi()*-1., TMath.Pi())  
    histogram1D(tree, "hhlte", "hltJets[0].e>>hhlte", cuts, scale, "Leading HLT jet energy (new)", 100, 0., 200.)      
    histogram1D(tree, "hhlteta", "hltJets[0].eta>>hhlteta", cuts, scale, "Leading HLT jet #eta (new)", 70, -3.5, 3.5)  
    histogram1D(tree, "hhltphi", "hltJets[0].phi>>hhltphi", cuts, scale, "Leading HLT jet #phi (new)", 60, -1 * pi, pi)

    # global quantities
    histogram1D(tree, "hntowsamephi", "nTowerSameiPhi>>hntowsamephi", cuts, scale, "N leading towers at same iphi (new)", 20, -0.5, 19.5)

    # jets
    histogram1D(tree, "hjete", "LeadingCenJetEnergy>>hjete", cuts, scale, "Leading jet energy", 50, 0., 500.)
    histogram1D(tree, "hjete2", "LeadingCenJetEnergy>>hjete2", cuts, scale, "Leading jet energy (zoom)", 50, 0., 200.)
    histogram1D(tree, "hjeteta", "LeadingCenJetEta>>hjeteta", cuts, scale, "Leading jet #eta", 70, -3.5, 3.5)
    histogram1D(tree, "hjetphi", "LeadingCenJetPhi>>hjetphi", cuts, scale, "Leading jet #phi", 60, -1 * pi, pi)
    histogram1D(tree, "hjetem", "LeadingCenJetEmInEB>>hjetem", cuts, scale, "Leading jet ECAL energy", 100, 0., 200.)
    histogram1D(tree, "hjethad", "LeadingCenJetHadInHB>>hjethad", cuts, scale, "Leading jet HCAL energy", 100, 0., 200.)
    histogram1D(tree, "hjetn60", "LeadingCenJetn60>>hjetn60", cuts, scale, "Leading jet N60", 50, 0., 50.)
    histogram1D(tree, "hjetn90", "LeadingCenJetn90>>hjetn90", cuts, scale, "Leading jet N90", 50, 0., 50.)

    
    # muons
    histogram1D(tree, "hnmu", "NoOfMuons>>hnmu", cuts, scale, "N muons", 4, -0.5, 3.5)

    # timing distributions (before any cuts)
    histogram1D(tree, "hr1", "TimingRightPeak>>hr1", cuts, scale, "R_{1}", 50, 0., 1.)
    histogram1D(tree, "hr2", "TimingFracRightNextRight>>hr2", cuts, scale, "R_{2}", 50, 0., 1.)
    histogram1D(tree, "hpk", "TimingFracInLeader>>hpk", cuts, scale, "R_{peak}", 50, 0., 1.)
    histogram1D(tree, "hout", "(1-TimingFracInCentralFour)>>hout", cuts, scale, "R_{outer}", 30, 0., 1.)
    
    # 2D timing histograms
    hr1r2 = TH2D("hr1r2", "R_{1} vs R_{2}", 50, 0., 1., 50, 0., 1.)
    tree.Draw("TimingRightPeak:TimingFracRightNextRight>>hr1r2", cuts)
    for i in range(1,100):
        hr1r2.SetBinContent(1,i,0.)
        hr1r2.SetBinContent(i,1,0.)
    hr1r2.Scale(scale)
    hr1r2.Write()
    
    hpkout = TH2D("hpkout", "R_{peak} vs R_{outer}", 50, 0., 1., 50, 0., 1.)
    tree.Draw("TimingFracInLeader:(1-TimingFracInCentralFour)>>hpkout", cuts)
    for i in range(1,100):
        hpkout.SetBinContent(1,i,0.)
        hpkout.SetBinContent(i,1,0.)
    hpkout.Scale(scale)
    hpkout.Write()

    file.cd()



