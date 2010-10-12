
import sys
import getopt
import string
import os

from constants import *

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

## cutnames=["HLT\t",
##           "BX veto\t",
##           "BPTX veto\t",
##           "Beam halo\t",
##           "Muon veto\t",
##           "HCAL noise\t",
##           "Jet 30 GeV\t",
##           "Jet 50 GeV\t",
##           "Jet n60\t",
##           "Jet n90\t",
##           "Calo tower\t",
##           "R1\t\t",
##           "R2\t\t",
##           "Rpeak\t\t",
##           "Router\t\t"]


ntot=hnmu.GetEntries()
if isMC:
    ntot=hcutcum.GetBinContent(1)

print
print '[TABLE border=1]'

if isMC:
    print "|Cut\t|N\t|cum %\t|N-1 % |-"
else:
    print "|Cut\t|N\t|Rate (Hz) |ind %\t|cum %\t|N-1 % |N-1 (Hz)|-"

for i in range(0,15):
    ncum = hcutcum.GetBinContent(i+1)
    nind = hcutind.GetBinContent(i+1)
    nnmo = hcutnmo.GetBinContent(i+1)
    label = hcutcum.GetXaxis().GetBinLabel(i+1)
    if isMC:
        print '|%s | %i | %.2e | %.2e |' % (label, ncum, 100.*ncum/ntot, 100.*nnmo/ntot)
    else:
        print '|%s | %i | %.2e | %.2e | %.2e | %.2e | %.2e |-' % (label, ncum, ncum/time, 100.*nind/ntot, 100.*ncum/ntot, 100.*nnmo/ntot, nnmo/time)

print '[/TABLE]'
print

# backgrounds
n90rate = hcutnmo.GetBinContent(in90+1)/time
ctrate  = hcutnmo.GetBinContent(iCT+1)/time

# naive method
bg0  = fall
ebg0 = efall

# n90 method
bg1  = fn90*n90rate
ebg1 = efn90*n90rate

# CT method
bg2  = fct*ctrate
ebg2 = efct*ctrate

# combined n90 & CT
bg3  = (bg1 + bg2) / 2
ebg3 = 0.

print "N-1 counts :"
print '  n60    : ' % (hcutnmo.GetBinContent(in90+1))
print '  CT     : ' % (hcutnmo.GetBinContent(iCT+1))
print

print "Expected background rates :"
print '  Simple method : %s +/- %s' % (bg0, ebg0)
print '  N90 method    : %s +/- %s' % (bg1, ebg1)
print '  CT method     : %s +/- %s' % (bg2, ebg2)
print '  N90 & CT      : %s +/- %s' % (bg3, ebg3)
print

print "Expected background counts :"
print '  Simple method : %s +/- %s' % (bg0*time, ebg0*time)
print '  N90 method    : %s +/- %s' % (bg1*time, ebg1*time)
print '  CT method     : %s +/- %s' % (bg2*time, ebg2*time)
print '  N90 & CT      : %s +/- %s' % (bg3*time, ebg3*time)

