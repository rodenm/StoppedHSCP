
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


hfile=TFile(dataset+"/histograms.root")

# run info
time=0
if (not isMC):
    htime=hfile.Get("ByRun/hlivetime")
    hnlb=hfile.Get("ByRun/hnlb")
    
    print "Run\tLS\tLivetime"
    for i in range(1,htime.GetNbinsX()+1):
        print htime.GetXaxis().GetBinLabel(i)+"\t"+str(hnlb.GetBinContent(i))+"\t"+str(htime.GetBinContent(i))


    # total time
    time=htime.Integral()
    print "Total live time : "+str(time)+" s"


hcutcum=hfile.Get("All/Cuts/hncutcum")
hcutind=hfile.Get("All/Cuts/hncutind")
hcutnmo=hfile.Get("All/Cuts/hnminus1cut")
hnmu=hfile.Get("All/NoCuts/hnmu")

cutnames=["HBHE filter\t",
          "BX veto\t",
          "BPTX veto\t",
          "muon veto\t",
          "jet 30 GeV\t",
          "jet 50 GeV\t",
          "jet n60\t",
          "jet n90\t",
          "Calo tower\t",
          "R1\t\t",
          "R2\t\t",
          "Rpeak\t\t",
          "Router\t\t"]


ntot=hnmu.GetEntries()
if isMC:
    ntot=hcutcum.GetBinContent(1)

print
print '[TABLE border=1]'

if isMC:
    print "|Cut\t|N\t|cum %\t|N-1 % |-"
else:
    print "|Cut\t|N\t|Rate (Hz) |ind %\t|cum %\t|N-1 % |-"

for i in range(0,13):
    ncum = hcutcum.GetBinContent(i+1)
    nind = hcutind.GetBinContent(i+1)
    nnmo = hcutnmo.GetBinContent(i+1)
    if isMC:
        print '|%s | %i | %.2e | %.2e |' % (cutnames[i], ncum, 100.*ncum/ntot, 100.*nnmo/ntot)
    else:
        print '|%s | %i | %.2e | %.2e | %.2e | %.2e |-' % (cutnames[i], ncum, ncum/time, 100.*nind/ntot, 100.*ncum/ntot, 100.*nnmo/ntot)

print '[/TABLE]'
