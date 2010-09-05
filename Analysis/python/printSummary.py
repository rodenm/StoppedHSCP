
import sys
import getopt
import string
import os

# help message
def usage():
    print "Usage : printSummary.py [-h] <input dataset>"


# get arguments
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

# run file
if (not isMC):
    rfile=TFile(dataset+"/"+dataset+"_byRun.root")
    htime=rfile.Get("hlivetime")
    hnlb=rfile.Get("hnlb")
    
    print "Run\tLS\tLivetime"
    for i in range(1,htime.GetNbinsX()+1):
        print htime.GetXaxis().GetBinLabel(i)+"\t"+str(hnlb.GetBinContent(i))+"\t"+str(htime.GetBinContent(i))


    # total time
    time=htime.Integral()
    print "Total live time : "+str(time)+" s"


# get histogram
hfile=TFile(dataset+"/histograms.root")

hcutcum=hfile.Get("All/Cuts/hncutcum")
hcutind=hfile.Get("All/Cuts/hncutind")
hcutnmo=hfile.Get("All/Cuts/hnminus1cut")
hnmu=hfile.Get("All/NoCuts/hnmu")

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
if isMC:
    ntot=hcutcum.GetBinContent(1)

if isMC:
    print "Cut\t\tN_evt\t\tcum %\t\tN-1 %"
else:
    print "Cut\t\tN_evt\t\tind %\t\tcum %\t\tN-1 %"

for i in range(0,13):
    ncum = hcutcum.GetBinContent(i+1)
    nind = hcutind.GetBinContent(i+1)
    nnmo = hcutnmo.GetBinContent(i+1)
    if isMC:
        print cutnames[i]+str(ncum)+"\t\t"+str(100.*ncum/ntot)+"\t\t"+str(100.*nnmo/ntot)
    else:
        print cutnames[i]+str(ncum)+"\t\t"+str(100.*nind/ntot)+"\t\t"+str(100.*ncum/ntot)+"\t\t"+str(100.*nnmo/ntot)

print
