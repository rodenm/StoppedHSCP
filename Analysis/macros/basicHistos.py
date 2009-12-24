
from ROOT import *
from style import *

from math import pi

# full set of histograms to make from new TTree
def basicHistos(tree, filename, time, cuts) :

    hfile = TFile(filename,"recreate")
    nEvents = tree.GetEntries()
    scale = 1./time

    # jets
    hjete = TH1D("hjete", "Leading jet energy", 100, 0., 1000.)
    tree.Draw("LeadingCenJetEnergy>>hjete")
    hjete.SetXTitle("E (GeV)")
    hjete.SetYTitle("Hz / 2 GeV")
    hjete.Scale(scale)
    hjete.Write()

    hjete2 = TH1D("hjete2", "Leading jet energy (zoom)", 100, 0., 200.)
    tree.Draw("LeadingCenJetEnergy>>hjete2")
    hjete2.Scale(scale)
    hjete2.Write()
    
    hjeteta = TH1D("hjeteta", "Leading jet #eta", 70, -3.5, 3.5)
    tree.Draw("LeadingCenJetEta>>hjeteta")
    hjeteta.Scale(scale)
    hjeteta.Write()
    
    hjetphi = TH1D("hjetphi", "Leading jet #phi", 60, -1 * pi, pi)
    tree.Draw("LeadingCenJetPhi>>hjetphi")
    hjetphi.Scale(scale)
    hjetphi.Write()
    
    hjetem = TH1D("hjetem", "Leading jet ECAL energy", 100, 0., 200.)
    tree.Draw("LeadingCenJetEmInEB>>hjetem")
    hjetem.Scale(scale)
    hjetem.Write()
    
    hjethad = TH1D("hjethad", "Leading jet HCAL energy", 100, 0., 200.)
    tree.Draw("LeadingCenJetHadInHB>>hjethad")
    hjethad.Scale(scale)
    hjethad.Write()
    
    hjetn60 = TH1D("hjetn60", "Leading jet N60", 50, 0., 50.)
    tree.Draw("LeadingCenJetn60>>hjetn60")
    hjetn60.Scale(scale)
    hjetn60.Write()
    
    hjetn90 = TH1D("hjetn90", "Leading jet N90", 50, 0., 50.)
    tree.Draw("LeadingCenJetn90>>hjetn90")
    hjetn90.Scale(scale)
    hjetn90.Write()
    
    # muons
    hnmu = TH1D("hnmu", "N muons", 4, -0.5, 3.5)
    tree.Draw("NoOfMuons>>hnmu")
    hnmu.Scale(scale)
    hnmu.Write()

    # timing distributions (before any cuts)
    hr1 = TH1D("hr1", "R_{1}", 50, 0., 1.)
    tree.Draw("TimingRightPeak>>hr1")
    hr1.Scale(scale)
    hr1.Write()
    
    hr2 = TH1D("hr2", "R_{2}", 50, 0., 1.)
    tree.Draw("TimingFracRightNextRight>>hr2")
    hr2.Scale(scale)
    hr2.Write()
    
    hpk = TH1D("hpk", "R_{peak}", 50, 0., 1.)
    tree.Draw("TimingFracInLeader>>hpk")
    hpk.Scale(scale)
    hpk.Write()
    
    hout = TH1D("hout", "R_{outer}", 30, 0., 1.)
    tree.Draw("(1-TimingFracInCentralFour)>>hout")
    hout.Scale(scale)
    hout.Write()
    
    hr1r2 = TH2D("hr1r2", "R_{1} vs R_{2}", 50, 0., 1., 50, 0., 1.)
    tree.Draw("TimingRightPeak:TimingFracRightNextRight>>hr1r2")
    for i in range(1,100):
        hr1r2.SetBinContent(1,i,0.)
        hr1r2.SetBinContent(i,1,0.)
    hr1r2.Scale(scale)
    hr1r2.Write()

    hpkout = TH2D("hpkout", "R_{peak} vs R_{outer}", 50, 0., 1., 50, 0., 1.)
    tree.Draw("TimingFracInLeader:(1-TimingFracInCentralFour)>>hpkout")
    for i in range(1,100):
        hpkout.SetBinContent(1,i,0.)
        hpkout.SetBinContent(i,1,0.)
    hpkout.Scale(scale)
    hpkout.Write()


    # N-1 efficiencies
    heffjete = TH1D("heffjete", "Leading jet energy (N-1)", 100, 0., 200.)
    tree.Draw("LeadingCenJetEnergy>>heffjete", cuts.nMinusOneJetE )
    heffjete.Scale(scale)
    heffjete.Write()
    
    heffjetn60 = TH1D("heffjetn60", "Leading jet n60 (N-1)", 25, 0., 25.)
    tree.Draw("LeadingCenJetn60>>heffjetn60", cuts.nMinusOneN60 )
    heffjetn60.Scale(scale)
    heffjetn60.Write()
    
    heffjetn90 = TH1D("heffjetn90", "Leading jet n90 (N-1)", 15, 0., 15.)
    tree.Draw("LeadingCenJetn90>>heffjetn90", cuts.nMinusOneN90 )
    heffjetn90.Scale(scale)
    heffjetn90.Write()
    
    heffnmu = TH1D("heffnmu", "N muons (N-1)", 6, 0., 6.)
    tree.Draw("NoOfMuons>>heffnmu", cuts.nMinusOneNMu )
    heffnmu.Scale(scale)
    heffnmu.Write()
    
    #  plots after jet+mu cuts
    hjete_jetmu = TH1D("hjete_jetmu", "Leading jet energy after jet+#mu cuts", 100, 0., 200.)
    tree.Draw("LeadingCenJetEnergy>>hjete_jetmu", cuts.jetMu )
    hjete_jetmu.Scale(scale)
    hjete_jetmu.Write()
  
    # timing distributions
    hr1_jetmu = TH1D("hr1_jetmu", "R_{1} after jet+#mu cuts", 50, 0., 1.)
    tree.Draw("TimingRightPeak>>hr1_jetmu", cuts.jetMu )
    hr1_jetmu.Scale(scale)
    hr1_jetmu.Write()
    
    hr2_jetmu = TH1D("hr2_jetmu", "R_{2} after jet+#mu cuts", 50, 0., 1.)
    tree.Draw("TimingFracRightNextRight>>hr2_jetmu", cuts.jetMu )
    hr2_jetmu.Scale(scale)
    hr2_jetmu.Write()
    
    hpk_jetmu = TH1D("hpk_jetmu", "R_{peak} after jet+#mu cuts", 50, 0., 1.)
    tree.Draw("TimingFracInLeader>>hpk_jetmu", cuts.jetMu )
    hpk_jetmu.Scale(scale)
    hpk_jetmu.Write()
    
    hout_jetmu = TH1D("hout_jetmu", "R_{outer} after jet+#mu cuts", 30, 0., 1.)
    tree.Draw("(1-TimingFracInCentralFour)>>hout_jetmu", cuts.jetMu )
    hout_jetmu.Scale(scale)
    hout_jetmu.Write()

    hr1r2_jetmu = TH2D("hr1r2_jetmu", "R_{1} vs R_{2} after jet+#mu cuts", 50, 0., 1., 50, 0., 1.)
    tree.Draw("TimingRightPeak:TimingFracRightNextRight>>hr1r2_jetmu", cuts.jetMu )
    for i in range(1,100):
        hr1r2_jetmu.SetBinContent(1,i,0.)
        hr1r2_jetmu.SetBinContent(i,1,0.)
    hr1r2_jetmu.Scale(scale)
    hr1r2_jetmu.Write()

    hpkout_jetmu = TH2D("hpkout_jetmu", "R_{peak} vs R_{outer} after jet+#mu cuts", 50, 0., 1., 50, 0., 1.)
    tree.Draw("TimingFracInLeader:(1-TimingFracInCentralFour)>>hpkout_jetmu", cuts.jetMu )
    for i in range(1,100):
        hpkout_jetmu.SetBinContent(1,i,0.)
        hpkout_jetmu.SetBinContent(i,1,0.)
    hpkout_jetmu.Scale(scale)
    hpkout_jetmu.Write()

    # distributions after all cuts
    hjete_allcuts = TH1D("hjete_allcuts", "Leading jet energy after all cuts", 100, 0., 200.)
    tree.Draw("LeadingCenJetEnergy>>hjete_allcuts", cuts.all )
    hjete_allcuts.Scale(scale)
    hjete_allcuts.Write()


    # new plots

    # event time
    hbx = TH1D("hbx", "BX number (new)", 3564, 0., 3564.)
    tree.Draw("bx>>hbx")
    hbx.Scale(scale)
    hbx.Write()
  
    horb = TH1D("horb", "Orbit number (new)", 100, 0., 10000.)
    tree.Draw("orbit>>horb")
    horb.Scale(scale)
    horb.Write()
    
    hlb = TH1D("hlb", "Lumi block (new)", 100, 0., 1000.)  
    tree.Draw("lb>>hlb")
    hlb.Scale(scale)
    hlb.Write()
    
    # trigger
    hl1et = TH1D("hl1et", "Leading L1 jet E_{t} (new)", 100, 0., 200.)  
    tree.Draw("l1Jets[0].et>>hl1et")
    hl1et.Scale(scale)
    hl1et.Write()
    
    hl1eta = TH1D("hl1eta", "Leading L1 jet #eta (new)", 70, -3.5, 3.5)  
    tree.Draw("l1Jets[0].eta>>hl1eta")
    hl1eta.Scale(scale)
    hl1eta.Write()
    
    hl1phi = TH1D("hl1phi", "Leading L1 jet #phi (new)", 60, TMath.Pi()*-1., TMath.Pi())  
    tree.Draw("l1Jets[0].phi>>hl1phi")
    hl1phi.Scale(scale)
    hl1phi.Write()
    
    hhlte = TH1D("hhlte", "Leading HLT jet energy (new)", 100, 0., 200.)  
    tree.Draw("hltJets[0].e>>hhlte")
    hhlte.Scale(scale)
    hhlte.Write()
    
    hhlteta = TH1D("hhlteta", "Leading HLT jet #eta (new)", 70, -3.5, 3.5)  
    tree.Draw("hltJets[0].eta>>hhlteta")
    hhlteta.Scale(scale)
    hhlteta.Write()
    
    hhltphi = TH1D("hhltphi", "Leading HLT jet #phi (new)", 60, -1 * pi, pi)
    tree.Draw("hltJets[0].phi>>hhltphi")
    hhltphi.Scale(scale)
    hhltphi.Write()

    # global quantities
    hntowsamephi = TH1D("hntowsamephi", "N leading towers at same iphi (new)", 20, -0.5, 19.5)
    tree.Draw("nTowerSameiPhi")
    hntowsamephi.Scale(scale)
    hntowsamephi.Write()
    
    # jets
##     hjete_new = TH1D("hjete_new", "Leading jet energy (new)", 100, 0., 1000.)
##     tree.Draw("jets.e[0]>>hjete_new")
##     hjete_new.Scale(scale)
##     hjete_new.Write()
    
##     hjete2_new = TH1D("hjete2_new", "Leading jet energy (zoom) (new)", 100, 0., 200.)
##     tree.Draw("jets.e[0]>>hjete2_new")
##     hjete2_new.Scale(scale)
##     hjete2_new.Write()
    
##     hjeteta_new = TH1D("hjeteta_new", "Leading jet #eta (new)", 70, -3.5, 3.5)
##     tree.Draw("jets.eta[0]>>hjeteta_new", cuts.init)
##     hjeteta_new.Scale(scale)
##     hjeteta_new.Write()
    
##     hjetphi_new = TH1D("hjetphi_new", "Leading jet #phi (new)", 60, -3.4151, 3.4151)
##     tree.Draw("jets.phi[0]>>hjetphi_new", cuts.init)
##     hjetphi_new.Scale(scale)
##     hjetphi_new.Write()
    
##     hjetem_new = TH1D("hjetem_new", "Leading jet ECAL energy (new)", 100, 0., 200.)
##     tree.Draw("jets.eEm[0]>>hjetem_new")
##     hjetem_new.Scale(scale)
##     hjetem_new.Write()
    
##     hjethad_new = TH1D("hjethad_new", "Leading jet HCAL energy (new)", 100, 0., 200.)
##     tree.Draw("jets.eHad[0]>>hjethad_new")
##     hjethad_new.Scale(scale)
##     hjethad_new.Write()
    
##     hjetn60_new = TH1D("hjetn60_new", "Leading jet N60 (new)", 50, 0., 50.)
##     tree.Draw("jets.n60[0]>>hjetn60_new")
##     hjetn60_new.Scale(scale)
##     hjetn60_new.Write()
    
##     hjetn90_new = TH1D("hjetn90_new", "Leading jet N90 (new)", 50, 0., 50.)
##     tree.Draw("jets.n90[0]>>hjetn90_new")
##     hjetn90_new.Scale(scale)
##     hjetn90_new.Write()
    
##     # muons
##     hnmu_new = TH1D("hnmu_new", "N muons (new)", 4, -0.5, 3.5)
##     tree.Draw("nMuon>>hnmu_new")
##     hnmu_new.Scale(scale)
##     hnmu_new.Write()
    
##     hmupt_new = TH1D("hmupt_new", "Leading muon pt (new)", 100, 0., 100.)
##     tree.Draw("muons.pt[0]>>hmupt_new")
##     hmupt_new.Scale(scale)
##     hmupt_new.Write()
    
##     # towers
##     hntow = TH1D("hntow", "N towers (new)", 100, 0., 100.)
##     tree.Draw("nTower>>hntow")
##     hntow.Scale(scale)
##     hntow.Write()
    
##     htowe = TH1D("htowe", "Leading tower energy (new)", 100, 0., 200.)
##     tree.Draw("towers.e[0]>>htowe")
##     htowe.Scale(scale)
##     htowe.Write()
    
##     htowem = TH1D("htowem", "Leading tower ECAL energy (new)", 100, 0., 200.)
##     tree.Draw("towers.eEm[0]>>htowem")
##     htowem.Scale(scale)
##     htowem.Write()
    
##     htowhad = TH1D("htowhad", "Leading tower HCAL energy (new)", 100, 0., 200.)
##     tree.Draw("towers.eHad[0]>>htowhad")
##     htowhad.Scale(scale)
##     htowhad.Write()
    
##     # N-1 efficiencies
##     # assumes jets are already restricted to |eta| < 1.3 !!!
    
##     heffjete_new = TH1D("heffjete_new", "Leading jet energy (N-1) (new)", 100, 0., 200.)
##     tree.Draw("jets[0].e>>heffjete_new", cuts.nMinusOneJetE )
##     heffjete_new.Scale(scale)
##     heffjete_new.Write()
    
##     heffjetn60_new = TH1D("heffjetn60_new", "Leading jet n60 (N-1) (new)", 25, 0., 25.)
##     tree.Draw("jets[0].n60>>heffjetn60_new", cuts.nMinusOneN60 )
##     heffjetn60_new.Scale(scale)
##     heffjetn60_new.Write()
    
##     heffjetn90_new = TH1D("heffjetn90_new", "Leading jet n90 (N-1) (new)", 15, 0., 15.)
##     tree.Draw("jets[0].n90>>heffjetn90_new", cuts.nMinusOneN90 )
##     heffjetn90_new.Scale(scale)
##     heffjetn90_new.Write()
    
##     heffnmu_new = TH1D("heffnmu_new", "N muons (N-1) (new)", 6, 0., 6.)
##     tree.Draw("nMuon>>heffnmu_new", cuts.nMinusOneNMu )
##     heffnmu_new.Scale(scale)
##     heffnmu_new.Write()

    hfile.Close()

    
def basicPlots(rootfile, psfile, new) :
    
    file = TFile(rootfile, "read")
    ps = TPostScript(psfile)

    canvas = TCanvas("canvas")

    canvas.SetLogy()

    # plot a basic set of histograms for old & new analyses

    # Jets
    hjete = file.Get("hjete2")
    hjete.Draw("HIST")
    canvas.Update()
    
    hjeteta = file.Get("hjeteta")
    hjeteta.SetXTitle("#eta")
    hjeteta.SetYTitle("Hz / 0.1")
    hjeteta.Draw("HIST")
    canvas.Update()
    
    hjetphi = file.Get("hjetphi")
    hjetphi.SetXTitle("#phi")
    hjetphi.SetYTitle("Hz / #pi/30")
    hjetphi.Draw("HIST")
    canvas.Update()
    
    hjetem = file.Get("hjetem")
    hjetem.SetXTitle("E_{ECAL} (GeV)")
    hjetem.SetYTitle("Hz / 2 GeV")
    hjetem.Draw("HIST")
    canvas.Update()
    
    hjethad = file.Get("hjethad")
    hjethad.SetXTitle("E_{HCAL} / GeV")
    hjethad.SetYTitle("Hz / 2 GeV")
    hjethad.Draw("HIST")
    canvas.Update()
    
    hjetn60 = file.Get("hjetn60")
    hjetn60.SetXTitle("n60")
    hjetn60.SetYTitle("Hz / unit")
    hjetn60.Draw("HIST")
    canvas.Update()
    
    hjetn90 = file.Get("hjetn90")
    hjetn90.SetXTitle("n90")
    hjetn90.SetYTitle("Hz / unit")
    hjetn90.Draw("HIST")
    canvas.Update()
    
    hnmu = file.Get("hnmu")
    hnmu.SetXTitle("N_{#mu}")
    hnmu.SetYTitle("Hz")
    hnmu.Draw("HIST")
    canvas.Update()
    
    heffjete = file.Get("heffjete")
    heffjete.SetXTitle("E (GeV)")
    heffjete.SetYTitle("Hz / 2 GeV")
    heffjete.Draw("HIST")
    canvas.Update()

    heffjetn60 = file.Get("heffjetn60")
    heffjetn60.SetXTitle("")
    heffjetn60.SetYTitle("Hz / unit")
    heffjetn60.Draw("HIST")
    canvas.Update()
    
    heffjetn90 = file.Get("heffjetn90")
    heffjetn90.SetXTitle("")
    heffjetn90.SetYTitle("Hz / unit")
    heffjetn90.Draw("HIST")
    canvas.Update()
    
    heffnmu = file.Get("heffnmu")
    heffnmu.SetXTitle("")
    heffnmu.SetYTitle("Hz / unit")
    heffnmu.Draw("HIST")
    canvas.Update()

    canvas.SetLogy(0)

    hr1 = file.Get("hr1")
    hr1.SetXTitle("")
    hr1.SetYTitle("Hz / 2 Gev")
    hr1.Draw("HIST")
    canvas.Update()

    hr2 = file.Get("hr2")
    hr2.SetXTitle("")
    hr2.SetYTitle("Hz / 2 Gev")
    hr2.Draw("HIST")
    canvas.Update()

    hpk = file.Get("hpk")
    hpk.SetXTitle("")
    hpk.SetYTitle("Hz / 2 Gev")
    hpk.Draw("HIST")
    canvas.Update()

    hout = file.Get("hout")
    hout.SetXTitle("")
    hout.SetYTitle("Hz / 2 Gev")
    hout.Draw("HIST")
    canvas.Update()

    canvas.SetLogy(0)
 #   canvas.SetLogz()
    
    hr1r2 = file.Get("hr1r2")
    hr1r2.SetXTitle("R_{2}")
    hr1r2.SetYTitle("R_{1}")
    hr1r2.SetStats(False)
    hr1r2.Draw("CONT")
    canvas.Update()

    hpkout = file.Get("hpkout")
    hpkout.SetXTitle("R_{out}")
    hpkout.SetYTitle("R_{peak}")
    hpkout.SetStats(False)
    hpkout.Draw("CONT")
    canvas.Update()

#    canvas.SetLogy()

    hr1_jetmu= file.Get("hr1_jetmu")
    hr1_jetmu.SetXTitle("")
    hr1_jetmu.SetYTitle("Hz / 2 Gev")
    hr1_jetmu.Draw("HIST")
    canvas.Update()

    hr2_jetmu = file.Get("hr2_jetmu")
    hr2_jetmu.SetXTitle("")
    hr2_jetmu.SetYTitle("Hz / 2 Gev")
    hr2_jetmu.Draw("HIST")
    canvas.Update()

    hpk_jetmu = file.Get("hpk_jetmu")
    hpk_jetmu.SetXTitle("")
    hpk_jetmu.SetYTitle("Hz / 2 Gev")
    hpk_jetmu.Draw("HIST")
    canvas.Update()

    hout_jetmu = file.Get("hout_jetmu")
    hout_jetmu.SetXTitle("")
    hout_jetmu.SetYTitle("Hz / 2 Gev")
    hout_jetmu.Draw("HIST")
    canvas.Update()

#    canvas.SetLogy(0)
    
    hr1r2_jetmu = file.Get("hr1r2_jetmu")
    hr1r2_jetmu.SetXTitle("R_{2}")
    hr1r2_jetmu.SetYTitle("R_{1}")
    hr1r2_jetmu.SetStats(False)
    hr1r2_jetmu.Draw("CONT")
    canvas.Update()

    hpkout_jetmu = file.Get("hpkout_jetmu")
    hpkout_jetmu.SetXTitle("R_{out}")
    hpkout_jetmu.SetYTitle("R_{peak}")
    hpkout_jetmu.SetStats(False)
    hpkout_jetmu.Draw("CONT")
    canvas.Update()

    hjete_allcuts = file.Get("hjete_allcuts")
    hjete_allcuts.SetXTitle("E (GeV)")
    hjete_allcuts.SetYTitle("Hz / 2 GeV")
    hjete_allcuts.Draw("HIST")
    canvas.Update()

    # plot an extended set of histograms if new ntuples are used
    
    hbx = file.Get("hbx")
    hbx.SetTitle("BX number")
    hbx.SetXTitle("N_{BX}")
    hbx.SetYTitle("Hz")
    hbx.Draw("HIST")
    canvas.Update()
    
    horb = file.Get("horb")
    horb.Draw("HIST")
    canvas.Update()
    
    hlb = file.Get("hlb")
    hlb.Draw("HIST")
    canvas.Update()
        
    # L1
    hl1et = file.Get("hl1et")
    hl1et.SetXTitle("E (GeV)")
    hl1et.SetYTitle("Hz / 2 GeV")
    hl1et.Draw("HIST")
    canvas.Update()
    
    hl1eta = file.Get("hl1eta")
    hl1eta.SetXTitle("#eta")
    hl1eta.SetYTitle("Hz / 0.1")
    hl1eta.Draw("HIST")
    canvas.Update()
    
    hl1phi = file.Get("hl1phi")
    hl1phi.SetXTitle("#phi")
    hl1phi.SetYTitle("Hz / #pi/30")
    hl1phi.Draw("HIST")
    canvas.Update()
    
    # HLT
    hhlte = file.Get("hhlte")
    hhlte.SetXTitle("E (GeV)")
    hhlte.SetYTitle("Hz / 2 GeV")
    hhlte.Draw("HIST")
    canvas.Update()
    
    hhlteta = file.Get("hhlteta")
    hhlteta.SetXTitle("#eta")
    hhlteta.SetYTitle("Hz / 0.1")
    hhlteta.Draw("HIST")
    canvas.Update()
    
    hhltphi = file.Get("hhltphi")
    hhltphi.SetXTitle("#phi")
    hhltphi.SetYTitle("Hz / #pi/30")
    hhltphi.Draw("HIST")
    canvas.Update()

    hntowsamephi = file.Get("hntowsamephi")
    hntowsamephi.SetXTitle("N towers")
    hntowsamephi.SetYTitle("Hz / N")
    hntowsamephi.Draw("HIST")
    canvas.Update()
    
##     hmupt = file.Get("hmupt")
##     hmupt.SetXTitle("p_{t}^{#mu}")
##     hmupt.SetYTitle("Hz / 1 GeV")
##     hmupt.Draw("HIST")
##     canvas.Update()
    
##     hntow = file.Get("hntow")
##     hntow.SetXTitle("N_{towers}")
##     hntow.SetYTitle("Hz")
##     hntow.Draw("HIST")
##     canvas.Update()
    
##     htowe = file.Get("htowe")
##     htowe.SetXTitle("E (GeV)")
##     htowe.SetYTitle("Hz / 2 GeV")
##     htowe.Draw("HIST")
##     canvas.Update()
    
##     htowem = file.Get("htowem")
##     htowem.SetXTitle("E (GeV)")
##     htowem.SetYTitle("Hz / 2 GeV")
##     htowem.Draw("HIST")
##     canvas.Update()
    
##     htowhad = file.Get("htowhad")
##     htowhad.SetXTitle("E (GeV)")
##     htowhad.SetYTitle("Hz / 2 GeV")
##     htowhad.Draw("HIST")
##     canvas.Update()
    
    # close file
    ps.Close()
