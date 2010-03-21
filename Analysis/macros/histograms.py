
# some functions for making histograms

from ROOT import *
from math import pi

from style import *
from histograms import *
from utils import *

# make all histograms for a dataset
def datasetHistos(tree, filebase, cutObj, runtree) :

    hfile = TFile(filebase+".root","recreate")
    nEvents = tree.GetEntries()

    totaltime=getLivetime(runtree, 0)

    basicHistos(tree, hfile, "NoCuts", "", 1./totaltime)
    basicHistos(tree, hfile, "JetMuCuts", cutObj.jetMu, 1./totaltime)
    basicHistos(tree, hfile, "AllCuts", cutObj.allCuts(), 1./totaltime)
    effHistos(tree, hfile, "EffPlots", cutObj)

    hfile.Close()


# make all histograms for a run
def runHistos(tree, filebase, cutObj, runtree, run):

    runstr=str(run)
    hfile = TFile(filebase+"_"+runstr+".root","recreate")

    livetime=getLivetime(runtree, run)

    basicHistos(tree, file, "NoCuts",  "run=="+runstr, 1./livetime)
    basicHistos(tree, file, "JetMuCuts", cutObj.jetMu and TCut("run=="+runstr), 1./livetime)
    basicHistos(tree, file, "AllCuts", cutObj.allCuts() and TCut("run=="+runstr), 1./livetime)

    hfile.Close()
    

# histogram1D(name, treecommand, title, nbins, xlo, xhi)
# full set of histograms to make from new TTree
def basicHistos(tree, file, dir, cuts, scale) :

    if (dir!=""):
        file.mkdir(dir)
        file.cd(dir)

    # event time
    histogram1D(tree, "hbx", "bx>>hbx", cuts, scale, "BX number (new)", 3564, 0., 3564.)
    histogram1D(tree, "horb", "orbit>>horb", cuts, scale, "Orbit number (new)", 100, 0., 10000.)    
    histogram1D(tree, "hlb", "lb>>hlb", cuts, scale, "Lumi block (new)", 100, 0., 1000.)  
    histogram1D(tree, "htime", "time>>htime", cuts, scale, "Event time", 100, 0., 1.E8)

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



def effHistos(tree, file, dir, cutObj):

    if (dir!=""):
        file.mkdir(dir)
        file.cd(dir)

    # N-1 efficiencies
    histogram1D(tree, "heffjete", "LeadingCenJetEnergy>>heffjete", cutObj.nMinusOneCuts(2), 1., "Leading jet energy (N-1)", 100, 0., 200.)    
    histogram1D(tree, "heffjetn60", "LeadingCenJetn60>>heffjetn60", cutObj.nMinusOneCuts(3), 1., "Leading jet n60 (N-1)", 25, 0., 25.)
    histogram1D(tree, "heffjetn90", "LeadingCenJetn90>>heffjetn90", cutObj.nMinusOneCuts(4), 1., "Leading jet n90 (N-1)", 15, 0., 15.)
    histogram1D(tree, "heffnmu", "NoOfMuons>>heffnmu", cutObj.nMinusOneCuts(5), 1., "N muons (N-1)", 6, 0., 6.)

    file.cd()


def newEffHistos(tree, file, dir, cutObj):

    if (dir!=""):
        file.mkdir(dir)
        file.cd(dir)

    histogram1D(tree, "heffjete", "LeadingCenJetEnergy>>heffjete", cutObj.nMinusOneCuts(2), 1., "Leading jet energy (N-1)", 100, 0., 200.)    
    histogram1D(tree, "heffjetn60", "LeadingCenJetn60>>heffjetn60", cutObj.nMinusOneCuts(3), 1., "Leading jet n60 (N-1)", 25, 0., 25.)
    histogram1D(tree, "heffjetn90", "LeadingCenJetn90>>heffjetn90", cutObj.nMinusOneCuts(4), 1., "Leading jet n90 (N-1)", 15, 0., 15.)
    histogram1D(tree, "heffnmu", "NoOfMuons>>heffnmu", cutObj.nMinusOneCuts(5), 1., "N muons (N-1)", 6, 0., 6.)

    file.cd()   


def histogram1D(tree, name, treecommand, cuts, scale, title, nbins, xlo, xhi) :
    h = TH1D(name, title, nbins, xlo, xhi)
    h.Sumw2()
    tree.Draw(treecommand, cuts)
    h.Scale(scale)
    h.Write()
    return h


def histogram2D(tree, name, treecommand, cuts, scale, title, nbins, xlo, xhi, ylo, yhi) :
    h = TH2D(name, title, nbins, xlo, xhi, ylo, yhi)
    h.Sumw2()
    tree.Draw(treecommand, cuts)
    h.Scale(scale)
    h.Write()
    return h
