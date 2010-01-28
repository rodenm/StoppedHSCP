
from ROOT import *
from math import pi

from style import *
from histograms import *

# histogram1D(name, treecommand, title, nbins, xlo, xhi)
# full set of histograms to make from new TTree
def makeHistos(tree, filename, cuts) :

    hfile = TFile(filename,"recreate")
    nEvents = tree.GetEntries()

    # event time
    histogram1D(tree, "hbx", "bx>>hbx", "", "BX number (new)", 3564, 0., 3564.)
    histogram1D(tree, "horb", "orbit>>horb", "", "Orbit number (new)", 100, 0., 10000.)    
    histogram1D(tree, "hlb", "lb>>hlb", "", "Lumi block (new)", 100, 0., 1000.)  

    # trigger
    histogram1D(tree, "hl1et", "l1Jets[0].et>>hl1et", "", "Leading L1 jet E_{t} (new)", 100, 0., 200.)  
    histogram1D(tree, "hl1eta", "l1Jets[0].eta>>hl1eta", "", "Leading L1 jet #eta (new)", 70, -3.5, 3.5)  
    histogram1D(tree, "hl1phi", "l1Jets[0].phi>>hl1phi", "", "Leading L1 jet #phi (new)", 60, TMath.Pi()*-1., TMath.Pi())  
    histogram1D(tree, "hhlte", "hltJets[0].e>>hhlte", "", "Leading HLT jet energy (new)", 100, 0., 200.)      
    histogram1D(tree, "hhlteta", "hltJets[0].eta>>hhlteta", "", "Leading HLT jet #eta (new)", 70, -3.5, 3.5)  
    histogram1D(tree, "hhltphi", "hltJets[0].phi>>hhltphi", "", "Leading HLT jet #phi (new)", 60, -1 * pi, pi)

    # global quantities
    histogram1D(tree, "hntowsamephi", "nTowerSameiPhi>>hntowsamephi", "", "N leading towers at same iphi (new)", 20, -0.5, 19.5)

    # jets
    histogram1D(tree, "hjete", "LeadingCenJetEnergy>>hjete", cuts.init, "Leading jet energy", 100, 0., 1000.)
    histogram1D(tree, "hjete2", "LeadingCenJetEnergy>>hjete2", cuts.init, "Leading jet energy (zoom)", 100, 0., 200.)
    histogram1D(tree, "hjeteta", "LeadingCenJetEta>>hjeteta", cuts.init, "Leading jet #eta", 70, -3.5, 3.5)
    histogram1D(tree, "hjetphi", "LeadingCenJetPhi>>hjetphi", cuts.init, "Leading jet #phi", 60, -1 * pi, pi)
    histogram1D(tree, "hjetem", "LeadingCenJetEmInEB>>hjetem", cuts.init, "Leading jet ECAL energy", 100, 0., 200.)
    histogram1D(tree, "hjethad", "LeadingCenJetHadInHB>>hjethad", cuts.init, "Leading jet HCAL energy", 100, 0., 200.)
    histogram1D(tree, "hjetn60", "LeadingCenJetn60>>hjetn60", cuts.init, "Leading jet N60", 50, 0., 50.)
    histogram1D(tree, "hjetn90", "LeadingCenJetn90>>hjetn90", cuts.init, "Leading jet N90", 50, 0., 50.)
    
    # muons
    histogram1D(tree, "hnmu", "NoOfMuons>>hnmu", cuts.init, "N muons", 4, -0.5, 3.5)

    # timing distributions (before any cuts)
    histogram1D(tree, "hr1", "TimingRightPeak>>hr1", cuts.init, "R_{1}", 50, 0., 1.)
    histogram1D(tree, "hr2", "TimingFracRightNextRight>>hr2", cuts.init, "R_{2}", 50, 0., 1.)
    histogram1D(tree, "hpk", "TimingFracInLeader>>hpk", cuts.init, "R_{peak}", 50, 0., 1.)
    histogram1D(tree, "hout", "(1-TimingFracInCentralFour)>>hout", cuts.init, "R_{outer}", 30, 0., 1.)
    
    # 2D timing histograms
    hr1r2 = TH2D("hr1r2", "R_{1} vs R_{2}", 50, 0., 1., 50, 0., 1.)
    tree.Draw("TimingRightPeak:TimingFracRightNextRight>>hr1r2")
    for i in range(1,100):
        hr1r2.SetBinContent(1,i,0.)
        hr1r2.SetBinContent(i,1,0.)
    hr1r2.Write()

    hpkout = TH2D("hpkout", "R_{peak} vs R_{outer}", 50, 0., 1., 50, 0., 1.)
    tree.Draw("TimingFracInLeader:(1-TimingFracInCentralFour)>>hpkout")
    for i in range(1,100):
        hpkout.SetBinContent(1,i,0.)
        hpkout.SetBinContent(i,1,0.)
    hpkout.Write()


    # N-1 efficiencies
    histogram1D(tree, "heffjete", "LeadingCenJetEnergy>>heffjete", cuts.nMinusOneJetE, "Leading jet energy (N-1)", 100, 0., 200.)    
    histogram1D(tree, "heffjetn60", "LeadingCenJetn60>>heffjetn60", cuts.nMinusOneN60, "Leading jet n60 (N-1)", 25, 0., 25.)
    histogram1D(tree, "heffjetn90", "LeadingCenJetn90>>heffjetn90", cuts.nMinusOneN90, "Leading jet n90 (N-1)", 15, 0., 15.)
    histogram1D(tree, "heffnmu", "NoOfMuons>>heffnmu", cuts.nMinusOneNMu, "N muons (N-1)", 6, 0., 6.)
    
    #  plots after jet+mu cuts
    histogram1D(tree, "hjete_jetmu", "LeadingCenJetEnergy>>hjete_jetmu", cuts.jetMu, "Leading jet energy after jet+#mu cuts", 100, 0., 200.)
    histogram1D(tree, "hr1_jetmu", "TimingRightPeak>>hr1_jetmu", cuts.jetMu, "R_{1} after jet+#mu cuts", 50, 0., 1.)  
    histogram1D(tree, "hr2_jetmu", "TimingFracRightNextRight>>hr2_jetmu", cuts.jetMu, "R_{2} after jet+#mu cuts", 50, 0., 1.)
    histogram1D(tree, "hpk_jetmu", "TimingFracInLeader>>hpk_jetmu", cuts.jetMu, "R_{peak} after jet+#mu cuts", 50, 0., 1.)
    histogram1D(tree, "hout_jetmu", "(1-TimingFracInCentralFour)>>hout_jetmu", cuts.jetMu, "R_{outer} after jet+#mu cuts", 30, 0., 1.)

    # 2D timing plots after jet+mu cuts
    hr1r2_jetmu = TH2D("hr1r2_jetmu", "R_{1} vs R_{2} after jet+#mu cuts", 50, 0., 1., 50, 0., 1.)
    tree.Draw("TimingRightPeak:TimingFracRightNextRight>>hr1r2_jetmu", cuts.jetMu )
    for i in range(1,100):
        hr1r2_jetmu.SetBinContent(1,i,0.)
        hr1r2_jetmu.SetBinContent(i,1,0.)
    hr1r2_jetmu.Write()

    hpkout_jetmu = TH2D("hpkout_jetmu", "R_{peak} vs R_{outer} after jet+#mu cuts", 50, 0., 1., 50, 0., 1.)
    tree.Draw("TimingFracInLeader:(1-TimingFracInCentralFour)>>hpkout_jetmu", cuts.jetMu )
    for i in range(1,100):
        hpkout_jetmu.SetBinContent(1,i,0.)
        hpkout_jetmu.SetBinContent(i,1,0.)
    hpkout_jetmu.Write()

    # distributions after all cuts
    histogram1D(tree, "hjete_allcuts", "LeadingCenJetEnergy>>hjete_allcuts", cuts.all, "Leading jet energy after all cuts", 100, 0., 200.)

    histogram1D(tree, "hbx_allcuts", "bx>>hbx", cuts.all, "BX after all cuts", 3564, 0., 3564.)
    histogram1D(tree, "horb_allcuts", "orbit>>horb", cuts.all, "Orbit after all cuts", 100, 0., 10000.)    
    histogram1D(tree, "hlb_allcuts", "lb>>hlb", cuts.all, "Lumi block after all cuts", 100, 0., 1000.)  



    hfile.Close()

    
