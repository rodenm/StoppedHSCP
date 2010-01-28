
# method to make all plots for a given dataset

from ROOT import *
from style import *
from plots import *

from math import pi

# plot all quantities
def makePlots(rootfile, psfile, scale) :
    
    file = TFile(rootfile, "read")
    ps = TPostScript(psfile)

    canvas = TCanvas("canvas")

    # reminder of method arguments
    # histPlot(hist, file, canvas, norm=False, log=False, title="histogram", xtitle="", ytitle="", opt="HIST")
    # hist2DPlot(hist, file, canvas, norm=False, log=False, title="histogram", xtitle="", ytitle="", ztitle="", opt="")

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

    # jet variables
    histPlot("hjete2", file, canvas, False, True, "", "E (GeV)", "")
    histPlot("hjeteta", file, canvas, False, True, "", "#eta", "")
    histPlot("hjetphi", file, canvas, False, True, "", "#phi", "")
    histPlot("hjetem", file, canvas, False, True, "", "E_{ECAL}", "")
    histPlot("hjethad", file, canvas, False, True, "", "E_{HCAL}", "")
    histPlot("hjetn60", file, canvas, False, True, "", "n60", "")
    histPlot("hjetn90", file, canvas, False, True, "", "n90", "")

    # muon variables
    histPlot("hnmu", file, canvas, False, False, "", "N_{#mu}", "")

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
    hist2DPlot("hr1r2", file, canvas, False, True, "", "R_{2}", "R_{1}", "", "CONT")
    hist2DPlot("hpkout", file, canvas, False, True, "", "R_{out}", "R_{peak}", "", "CONT")

    # plots after jet + mu cuts
    histPlot("hr1_jetmu", file, canvas, False, False, "", "R1", "")
    histPlot("hr2_jetmu", file, canvas, False, False, "", "R2", "")
    histPlot("hpk_jetmu", file, canvas, False, False, "", "R_{peak}", "")
    histPlot("hout_jetmu", file, canvas, False, False, "", "R_{outer}", "")

    # 2D timing plots
    hist2DPlot("hr1r2_jetmu", file, canvas, False, False, "", "R_{2}", "R_{1}", "", "CONT")
    hist2DPlot("hpkout_jetmu", file, canvas, False, False, "", "R_{out}", "R_{peak}", "", "CONT")

    # plots after all cuts
    histPlot("hjete_allcuts", file, canvas, False, True, "", "E (GeV)", "")
    histPlot("hbx_allcuts", file, canvas, False, True, "", "BX", "")
    histPlot("horb_allcuts", file, canvas, False, True, "", "orbit", "")
    histPlot("hlb_allcuts", file, canvas, False, True, "", "Lumi block", "")




    # close file
    ps.Close()
