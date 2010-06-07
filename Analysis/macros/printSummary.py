
import sys
import getopt
import string
import os

# help message
def usage():
    print "Usage : printSummary.py [-h] <input dataset>"


# the main program
try:
    opts, args = getopt.getopt(sys.argv[1:], "hm")
except getopt.GetoptError:
    usage();
    sys.exit(2)

if len(args) < 1 :
    print "Wrong number of arguments"
    usage();
    sys.exit(1)

# options
isMC=False
for opt, arg in opts:
    if opt=='-h':
        usage()
        exit.sys()
    if opt=='-m':
        isMC=True;

# arguments
dataset=args[0]

# ROOT
from ROOT import *

# get histogram
if isMC:
    hfile=TFile(dataset+"/histograms.root")
else:
    hfile=TFile(dataset+"/selectedRuns.root")
hcuts=hfile.Get("Cuts/hncutcum")
hnmu=hfile.Get("NoCuts/hnmu")

cutnames=["HLT\t\t",
          "BX veto\t\t",
          "BPTX veto\t",
          "muon veto\t",
          "jet 30 GeV\t",
          "jet 50 GeV\t",
          "jet n60\t\t",
          "jet n90\t\t",
          "Calo tower\t",
          "R1\t\t",
          "R2\t\t",
          "Rpeak\t\t",
          "Router\t\t"]

ntot=hnmu.GetEntries()

print "Cut\t\tN_evt\t\t%"
for i in range(0,13):
    nevt = hcuts.GetBinContent(i+1)
    print cutnames[i]+str(nevt)+"\t\t"+str(100.*nevt/ntot)

print

# total time
rfile=TFile(dataset+"/"+dataset+"_byRun.root")
htime=rfile.Get("hlivetime")
time=htime.Integral()
print "Total live time : "+str(time)+" s"

print
