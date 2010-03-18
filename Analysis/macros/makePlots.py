
# method to make all plots for a given dataset

import subprocess
from ROOT import *
from style import *
from plots import *
from utils import *

from math import pi

# plot all quantities
def makePlots(rootfile, outfile, runtree) :

    file = TFile(rootfile, "read")
    canvas = TCanvas("canvas")

    # plots for all runs
    ps = TPostScript(outfile+".ps")
    basicPlots(file, "NoCuts", canvas)
    basicPlots(file, "JetMuCuts", canvas)
    basicPlots(file, "AllCuts", canvas)
    effPlots(file, "EffPlots", canvas)
    ps.Close()

    # convert to PDF
    subprocess.call(["ps2pdf", outfile+".ps", outfile+".pdf"])

    runs=getRuns(runtree)
    for run in runs:
        runstr=str(run)
        rps = TPostScript(outfile+"_"+runstr+".ps")
        basicPlots(file, "Runs/"+runstr+"/NoCuts", canvas)
        basicPlots(file, "Runs/"+runstr+"/JetMuCuts", canvas)
        basicPlots(file, "Runs/"+runstr+"/AllCuts", canvas)
        rps.Close()

        subprocess.call(["ps2pdf", outfile+"_"+runstr+".ps", outfile+"_"+runstr+".pdf"])



def basicPlots(file, dir, canvas):

    # reminder of method arguments
    # histPlot(hist, file, canvas, norm=False, log=False, title="histogram", xtitle="", ytitle="", opt="HIST")
    # hist2DPlot(hist, file, canvas, norm=False, log=False, title="histogram", xtitle="", ytitle="", ztitle="", opt="")

    # event time
    histPlot(dir+"/hbx", file, canvas, False, True, "", "BX", "")
    histPlot(dir+"/horb", file, canvas, False, True, "", "orbit", "")
    histPlot(dir+"/hlb", file, canvas, False, True, "", "Lumi Block", "")
    histPlot(dir+"/htime", file, canvas, False, True, "", "Event time", "")

    # L1 trigger
    histPlot(dir+"/hl1et", file, canvas, False, True, "", "E_{L1} (GeV)", "")
    histPlot(dir+"/hl1eta", file, canvas, False, True, "", "#eta", "")
    histPlot(dir+"/hl1phi", file, canvas, False, True, "", "#phi", "")
    
    # HLT
    histPlot(dir+"/hhlte", file, canvas, False, True, "", "E_{HLT} (GeV)", "")
    histPlot(dir+"/hhlteta", file, canvas, False, True, "", "#eta", "")
    histPlot(dir+"/hhltphi", file, canvas, False, True, "", "#phi", "")

    # misc
    histPlot(dir+"/hntowsamephi", file, canvas, False, True, "", "N_{towers}", "")

    # jet variables
    histPlot(dir+"/hjete2", file, canvas, False, True, "", "E (GeV)", "E")
    histPlot(dir+"/hjeteta", file, canvas, False, True, "", "#eta", "E")
    histPlot(dir+"/hjetphi", file, canvas, False, True, "", "#phi", "E")
    histPlot(dir+"/hjetem", file, canvas, False, True, "", "E_{ECAL}", "E")
    histPlot(dir+"/hjethad", file, canvas, False, True, "", "E_{HCAL}", "E")
    histPlot(dir+"/hjetn60", file, canvas, False, True, "", "n60", "E")
    histPlot(dir+"/hjetn90", file, canvas, False, True, "", "n90", "E")

    # muon variables
    histPlot(dir+"/hnmu", file, canvas, False, True, "", "N_{#mu}", "")


    # pulse shape variables
    histPlot(dir+"/hr1", file, canvas, False, False, "", "R1", "")
    histPlot(dir+"/hr2", file, canvas, False, False, "", "R2", "")
    histPlot(dir+"/hpk", file, canvas, False, False, "", "R_{peak}", "")
    histPlot(dir+"/hout", file, canvas, False, False, "", "R_{outer}", "")

    # 2D timing plots
    hist2DPlot(dir+"/hr1r2", file, canvas, False, True, "", "R_{2}", "R_{1}", "", "CONT")
    hist2DPlot(dir+"/hpkout", file, canvas, False, True, "", "R_{out}", "R_{peak}", "", "CONT")

    # plots after jet + mu cuts
#    histPlot(dir+"/hr1_jetMuCuts", file, canvas, False, False, "", "R1", "")
#    histPlot(dir+"/hr2_jetMuCuts", file, canvas, False, False, "", "R2", "")
#    histPlot(dir+"/hpk_jetMuCuts", file, canvas, False, False, "", "R_{peak}", "")
#    histPlot(dir+"/hout_jetMuCuts", file, canvas, False, False, "", "R_{outer}", "")

    # 2D timing plots
#    hist2DPlot(dir+"/hr1r2_jetMuCuts", file, canvas, False, False, "", "R_{2}", "R_{1}", "", "CONT")
#    hist2DPlot(dir+"/hpkout_jetMuCuts", file, canvas, False, False, "", "R_{out}", "R_{peak}", "", "CONT")

    # plots after all cuts
#    histPlot(dir+"/hjete_allCuts", file, canvas, False, True, "", "E (GeV)", "")
#    histPlot(dir+"/hbx_allCuts", file, canvas, False, True, "", "BX", "")
#    histPlot(dir+"/horb_allCuts", file, canvas, False, True, "", "orbit", "")
#    histPlot(dir+"/hlb_allCuts", file, canvas, False, True, "", "Lumi block", "")




def effPlots(file, dir, canvas) :
    
    # N-1 efficiencies
    histPlot(dir+"/heffjete", file, canvas, True, True, "", "E (GeV)", "")
    histPlot(dir+"/heffjetn60", file, canvas, True, True, "", "n60", "")
    histPlot(dir+"/heffjetn90", file, canvas, True, True, "", "n90", "")
    histPlot(dir+"/heffnmu", file, canvas, True, True, "", "N_{#mu}", "")

