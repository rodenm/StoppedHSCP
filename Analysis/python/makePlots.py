#! /usr/bin/env python

#
# Make plots from histograms.root
#

import sys
import getopt
import string
import os

# help message
def usage():
    print "Usage : makePlots.py [-hr] <input file> [runs]"    


# the main program
try:
    opts, args = getopt.getopt(sys.argv[1:], "hrb")
except getopt.GetoptError:
    usage();
    sys.exit(2)

if len(args) < 1 :
    print "Wrong number of arguments"
    usage();
    sys.exit(1)

# options
doRuns=False;
for opt, arg in opts:
    if opt=='-h':
        usage()
        exit.sys()
    if opt=='-r':
        doRuns=True;

# arguments
dataset=args[0]
runs=[]
if (len(args)>1):
    runlist=args[1].split(',')
    for i in range(0, len(runlist)):
        runs.append(int(runlist[i]))
        
sys.argv.append('-b')


from ROOT import *
from math import *
from style import *
from plots import *


# plot basic distributions
def distributions(file, basedir, ofile):
    
    canvas = TCanvas("canvas")
    canvas.Print(ofile+".ps[", "Portrait")

    dir=basedir+"/NoCuts";

    # BX plots etc
    histPlot(dir+"/hbx", file, ofile+".ps", 0., True, "", "BX", "N events")
    histPlot(dir+"/hlb", file, ofile+".ps", 0., True, "", "LS", "Rate")
#    histPlot(dir+"/hlbdist", file, ofile+".ps", 0., True, "", "Rate", "N LS")
    
    # L1 trigger
    histPlot(dir+"/hl1bits", file, ofile+".ps", 1., True, "", "L1 bit", "")
    histPlot(dir+"/hl1et", file, ofile+".ps", 1., True, "", "E_{L1} (GeV)", "")
    histPlot(dir+"/hl1eta", file, ofile+".ps", 1., True, "", "#eta", "")
    histPlot(dir+"/hl1phi", file, ofile+".ps", 1., True, "", "#phi", "")
    
    # HLT
    histPlot(dir+"/hhlte", file, ofile+".ps", 1., True, "", "E_{HLT} (GeV)", "")
    histPlot(dir+"/hhlteta", file, ofile+".ps", 1., True, "", "#eta", "")
    histPlot(dir+"/hhltphi", file, ofile+".ps", 1., True, "", "#phi", "")

    # global variables
    histPlot(dir+"/hntowsameiphi", file, ofile+".ps", 1., True, "", "N_{towers}", "")

    # jet variables
    histPlot(dir+"/hjete", file, ofile+".ps", 1., True, "", "E (GeV)", "E")
    histPlot(dir+"/hjeteta", file, ofile+".ps", 1., True, "", "#eta", "E")
    histPlot(dir+"/hjetphi", file, ofile+".ps", 1., True, "", "#phi", "E")
    histPlot(dir+"/hjeteem", file, ofile+".ps", 1., True, "", "E_{ECAL}", "E")
    histPlot(dir+"/hjetehad", file, ofile+".ps", 1., True, "", "E_{HCAL}", "E")
    histPlot(dir+"/hjetemf", file, ofile+".ps", 1., True, "", "EM fraction", "E")
    histPlot(dir+"/hjetn60", file, ofile+".ps", 1., True, "", "n60", "E")
    histPlot(dir+"/hjetn90", file, ofile+".ps", 1., True, "", "n90", "E")

    # muon variables
    histPlot(dir+"/hnmu", file, ofile+".ps", 1., True, "", "N_{#mu}", "")

    # pulse shape variables
    histPlot(dir+"/hpksample", file, ofile+".ps", 1., False, "", "Peak sample", "")
    histPlot(dir+"/hr1", file, ofile+".ps", 1., False, "", "R1", "")
    histPlot(dir+"/hr2", file, ofile+".ps", 1., False, "", "R2", "")
    histPlot(dir+"/hrpk", file, ofile+".ps", 1., False, "", "R_{peak}", "")
    histPlot(dir+"/hrout", file, ofile+".ps", 1., False, "", "R_{outer}", "")

    # 2D timing plots
    hist2DPlot(dir+"/hr1r2", file, ofile+".ps", 1., True, "", "R_{1}", "R_{2}", "", "COLZ")
    hist2DPlot(dir+"/hpkout", file, ofile+".ps", 1., True, "", "R_{peak}", "R_{out}", "", "COLZ")

    # cut plots
    dir = "All/Cuts"
    histPlot(dir+"/hncutcum", file, ofile+".ps", 1., True, "", "Cut", "N_{events}")
    histPlot(dir+"/hncutind", file, ofile+".ps", 1., True, "", "Cut", "N_{events}")
    histPlot(dir+"/hnminus1cut", file, ofile+".ps", 1., True, "", "Cut", "N_{events}")
    histPlot(dir+"/holdcutcum", file, ofile+".ps", 1., True, "", "Cut", "N_{events}")
    histPlot(dir+"/holdcutind", file, ofile+".ps", 1., True, "", "Cut", "N_{events}")

    histPlot(dir+"/hjete_nmo", file, ofile+".ps", 1., False, "", "E (GeV)", "E")
    histPlot(dir+"/hjetn60_nmo", file, ofile+".ps", 1., False, "", "n60", "E")
    histPlot(dir+"/hjetn90_nmo", file, ofile+".ps", 1., False, "", "n90", "E")
    histPlot(dir+"/hnmu_nmo", file, ofile+".ps", 1., False, "", "N_{#mu}", "")
    histPlot(dir+"/hr1_nmo", file, ofile+".ps", 1., False, "", "R1", "")
    histPlot(dir+"/hr2_nmo", file, ofile+".ps", 1., False, "", "R2", "")
    histPlot(dir+"/hrpk_nmo", file, ofile+".ps", 1., False, "", "R_{peak}", "")
    histPlot(dir+"/hrout_nmo", file, ofile+".ps", 1., False, "", "R_{outer}", "")
    histPlot(dir+"/hjetemf_nmo", file, ofile+".ps", 1., False, "", "EM fraction", "E")

    canvas = TCanvas("canvas")
    canvas.Print(ofile+".ps]")

    subprocess.call(["ps2pdf", ofile+".ps", ofile+".pdf"])
    subprocess.call(["rm", ofile+".ps"])


def runPlots(file, ofile):

    canvas = TCanvas("canvas")
    canvas.Print(ofile+".ps[", "Portrait")

    # n counts, livetime etc.
    multiPlot([ file.Get("ByRun/hnhlt") ], [""], ofile+".ps", 0., 0., "HLT counts", "run", "events", 0)
    multiPlot([ file.Get("ByRun/hnlb") ], [""], ofile+".ps", 0., 0., "N LS", "run", "s", 0)
    multiPlot([ file.Get("ByRun/hlivetime") ], [""], ofile+".ps", 0., 0., "time", "run", "s", 0)
    multiPlot([ file.Get("ByRun/hnfin") ], [""], ofile+".ps", 0., 0., "Final counts", "run", "events", 0)
    

    # rate per cut
    ymax = [0.0, 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0. ]
    ymin = [0.0, 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0. ]
    
    for i in range(0,13):
        multiPlot([ file.Get("ByRun/hratecut"+str(i)) ], [], ofile+".ps", ymin[i], ymax[i], "Rate after cuts "+str(i), "run", "Hz", 0)
        
        hist2DPlot("ByRun/hbx", file,  ofile+".ps", 0., False, "HLT", "Run", "BX", "events", "COLZ")
        hist2DPlot("ByRun/heta", file,  ofile+".ps", 0., False, "HLT", "Run", "jet #eta", "events", "COLZ")
        hist2DPlot("ByRun/hphi", file,  ofile+".ps", 0., False, "HLT", "Run", "jet #phi", "events", "COLZ")
        
        hist2DPlot("ByRun/hbxfin", file,  ofile+".ps", 0., False, "After all cuts", "Run", "BX", "events", "COLZ")
        hist2DPlot("ByRun/hetafin", file,  ofile+".ps", 0., False, "After all cuts", "Run", "jet #eta", "events", "COLZ")
        hist2DPlot("ByRun/hphifin", file,  ofile+".ps", 0., False, "After all cuts", "Run", "jet #phi", "events", "COLZ")
        
    canvas = TCanvas("canvas")
    canvas.Print(ofile+".ps]")
    
    # convert to PDF
    subprocess.call(["ps2pdf", ofile+".ps", ofile+".pdf"])
    subprocess.call(["rm", ofile+".ps"])
    

# plots of quantities vs fill
def fillPlots(file, ofile):

    canvas = TCanvas("canvas")
    canvas.Print(ofile+".ps[", "Portrait")

    multiPlot([ file.Get("ByFill/hfillcount"), file.Get("ByFill/hbgmean") ], ["Data","Expected"], ofile+".ps", 0., 0., "", "Fill", "N_{events}", 0)   

    canvas = TCanvas("canvas")
    canvas.Print(ofile+".ps]")

    subprocess.call(["ps2pdf", ofile+".ps", ofile+".pdf"])
    subprocess.call(["rm", ofile+".ps"])


# compare important quantities with BG
def compPlots(file, bgfile, ofile, dataset, control):

    canvas = TCanvas("canvas")
    canvas.Print(ofile+".ps[", "Portrait")

    multiPlot([bgfile.Get("All/NoCuts/hjete"), file.Get("All/NoCuts/hjete") ], [control, dataset], ofile+".ps", 0., 0., "Jet Energy", "GeV", "events", 1)   
    multiPlot([bgfile.Get("All/NoCuts/hjeteta"), file.Get("All/NoCuts/hjeteta") ], [control, dataset], ofile+".ps", 0., 0., "Jet #eta", "#eta", "events", 1)   
    multiPlot([bgfile.Get("All/NoCuts/hjetphi"), file.Get("All/NoCuts/hjetphi") ], [control, dataset], ofile+".ps", 0., 0., "Jet #phi", "#phi", "events", 1)   
    multiPlot([bgfile.Get("All/NoCuts/hjeteem"), file.Get("All/NoCuts/hjeteem") ], [control, dataset], ofile+".ps", 0., 0., "Jet EM Energy", "GeV", "events", 1)   
    multiPlot([bgfile.Get("All/NoCuts/hjetehad"), file.Get("All/NoCuts/hjetehad") ], [control, dataset], ofile+".ps", 0., 0., "Jet Had Energy", "GeV", "events", 1)   
    multiPlot([bgfile.Get("All/NoCuts/hjetemf"), file.Get("All/NoCuts/hjetemf") ], [control, dataset], ofile+".ps", 0., 0., "Jet Em fraction", "emf", "events", 1)   
    multiPlot([bgfile.Get("All/NoCuts/hjetn60"), file.Get("All/NoCuts/hjetn90") ], [control, dataset], ofile+".ps", 0., 0., "Jet N60", "n60", "events", 1)   
    multiPlot([bgfile.Get("All/NoCuts/hnmu"), file.Get("All/NoCuts/hnmu") ], [control, dataset], ofile+".ps", 0., 0., "Jet N90", "n90", "events", 1)   
    multiPlot([bgfile.Get("All/NoCuts/hpksample"), file.Get("All/NoCuts/hpksample") ], [control, dataset], ofile+".ps", 0., 0., "Peak sample", "BX", "events", 1)   
    multiPlot([bgfile.Get("All/NoCuts/hr1"), file.Get("All/NoCuts/hr1") ], [control, dataset], ofile+".ps", 0., 0., "R_{1} after jet/mu cuts", "R_{1}", "events", 1)   
    multiPlot([bgfile.Get("All/NoCuts/hr2"), file.Get("All/NoCuts/hr2") ], [control, dataset], ofile+".ps", 0., 0., "R_{2} after jet/mu cuts", "R_{2}", "events", 1)   
    multiPlot([bgfile.Get("All/NoCuts/hrpk"), file.Get("All/NoCuts/hrpk") ], [control, dataset], ofile+".ps", 0., 0., "R_{peak} after jet/mu cuts", "R_{peak}", "events", 1)   
    multiPlot([bgfile.Get("All/NoCuts/hrout"), file.Get("All/NoCuts/hrout") ], [control, dataset], ofile+".ps", 0., 0., "R_{outer} after jet/mu cuts", "R_{outer}", "events", 1)   

    multiPlot([bgfile.Get("All/Cuts/hjete_nmo"), file.Get("All/Cuts/hjete_nmo") ], [control, dataset], ofile+".ps", 0., 0., "Jet E (N-1)", "GeV", "events", 1)   
    multiPlot([bgfile.Get("All/Cuts/hjetn60_nmo"), file.Get("All/Cuts/hjetn60_nmo") ], [control, dataset], ofile+".ps", 0., 0., "Jet n60 (N-1)", "n60", "events", 1)   
    multiPlot([bgfile.Get("All/Cuts/hjetn90_nmo"), file.Get("All/Cuts/hjetn90_nmo") ], [control, dataset], ofile+".ps", 0., 0., "Jet n90 (N-1)", "n90", "events", 1)   
    multiPlot([bgfile.Get("All/Cuts/hnmu_nmo"), file.Get("All/Cuts/hnmu_nmo") ], [control, dataset], ofile+".ps", 0., 0., "N muons (N-1)", "N_{#mu}", "events", 1)   
    multiPlot([bgfile.Get("All/Cuts/hr1_nmo"), file.Get("All/Cuts/hr1_nmo") ], [control, dataset], ofile+".ps", 0., 0., "R_{1} (N-1)", "R_{1}", "events", 1)   
    multiPlot([bgfile.Get("All/Cuts/hr2_nmo"), file.Get("All/Cuts/hr2_nmo") ], [control, dataset], ofile+".ps", 0., 0., "R_{2} (N-1)", "R_{2}", "events", 1)   
    multiPlot([bgfile.Get("All/Cuts/hrpk_nmo"), file.Get("All/Cuts/hrpk_nmo") ], [control, dataset], ofile+".ps", 0., 0., "R_{peak} (N-1)", "R_{peak}", "events", 1)   
    multiPlot([bgfile.Get("All/Cuts/hrout_nmo"), file.Get("All/Cuts/hrout_nmo") ], [control, dataset], ofile+".ps", 0., 0., "R_{outer} (N-1)", "R_{outer}", "events", 1)   

    canvas = TCanvas("canvas")
    canvas.Print(ofile+".ps]")

    subprocess.call(["ps2pdf", ofile+".ps", ofile+".pdf"])
    subprocess.call(["rm", ofile+".ps"])

    

# main program starts here

# set style
tdrStyle()
gROOT.SetStyle("tdrStyle")
gROOT.ForceStyle()

# open file
file = TFile(dataset+"/histograms.root", "read")
bgfile = TFile("Comm10_Jun14th_371_v1/histograms.root", "read")

# distributions
distributions(file, "All", dataset+"/"+dataset)

# per run plots
runPlots(file, dataset+"/"+dataset+"_ByRun")

# per fill plots
fillPlots(file, dataset+"/"+dataset+"_ByFill")

compPlots(file, bgfile, dataset+"/"+dataset+"_Comp", dataset, "Comm10_Jun14th_371_v1")

# loop over runs
if doRuns:
    for run in runs:
        distributions(file, str(run), dataset+"/histograms"+str(run))

