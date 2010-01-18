
# method to make all plots for a given dataset

from ROOT import *
from style import *
from plots import *

from math import pi

# plot all quantities
def makePlots(rootfile, psfile) :
    
    file = TFile(rootfile, "read")
    ps = TPostScript(psfile)

    canvas = TCanvas("canvas")

    # jet variables
    histPlot("hjete2", file, canvas, False, True, "", "E (GeV)", "")
    histPlot("hjeteta", file, canvas, False, True, "", "#eta", "")
    histPlot("hjetphi", file, canvas, False, True, "", "#phi", "")
    histPlot("hjetem", file, canvas, False, True, "", "E_{ECAL}", "")
    histPlot("hjethad", file, canvas, False, True, "", "E_{HCAL}", "")
    histPlot("hjetn60", file, canvas, False, True, "", "n60", "")
    histPlot("hjetn90", file, canvas, False, True, "", "n90", "")

    # muon variables
    histPlot("hnmu", file, canvas, False, True, "", "N_{#mu}", "")

    # N-1 efficiencies
    histPlot("heffjete", file, canvas, False, True, "", "E (GeV)", "")
    histPlot("heffjetn60", file, canvas, False, True, "", "n60", "")
    histPlot("heffjetn90", file, canvas, False, True, "", "n90", "")
    histPlot("heffnmu", file, canvas, False, True, "", "N_{#mu}", "")

    # pulse shape variables
    histPlot("hr1", file, canvas, False, False, "", "R1", "")
    histPlot("hr2", file, canvas, False, False, "", "R2", "")
    histPlot("hpk", file, canvas, False, False, "", "R_{peak}", "")
    histPlot("hout", file, canvas, False, False, "", "R_{outer}", "")


    # 2D timing plots
    canvas.SetLogy(0)
    
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

    # plots after jet + mu cuts
    histPlot("hr1_jetmu", file, canvas, False, False, "", "R1", "")
    histPlot("hr2_jetmu", file, canvas, False, False, "", "R2", "")
    histPlot("hpk_jetmu", file, canvas, False, False, "", "R_{peak}", "")
    histPlot("hout_jetmu", file, canvas, False, False, "", "R_{outer}", "")

    # 2D timing plots
    canvas.SetLogy(0)
    
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

    # plots after all cuts
    histPlot("hjete_allcuts", file, canvas, False, True, "", "E (GeV)", "")

    # event time
    histPlot("hbx", file, canvas, False, True, "", "BX", "")
    histPlot("horb", file, canvas, False, True, "", "orbit", "")
    histPlot("hlb", file, canvas, False, True, "", "Lumi Block", "")

    # L1 trigger
    histPlot("hl1et", file, canvas, False, True, "", "E_{L1} (GeV)", "")
    histPlot("hl1eta", file, canvas, False, True, "", "#eta", "")
    histPlot("hl1phi", file, canvas, False, True, "", "#phi", "")
    
    # HLT
    histPlot("hhlte", file, canvas, False, True, "", "E_{HLT} (GeV)", "")
    histPlot("hhlteta", file, canvas, False, True, "", "#eta", "")
    histPlot("hhltphi", file, canvas, False, True, "", "#phi", "")

    # misc
    histPlot("hntowsamephi", file, canvas, False, True, "", "N_{towers}", "")


    # close file
    ps.Close()
