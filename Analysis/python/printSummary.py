
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

for i in range(0,nCuts):
    ncum = hcutcum.GetBinContent(i+1)
    nind = hcutind.GetBinContent(i+1)
    nnmo = hcutnmo.GetBinContent(i+1)
    label = hcutcum.GetXaxis().GetBinLabel(i+1)
    if isMC:
        print '|%i %s | %i | %.2e | %.2e |' % (i, label, ncum, 100.*ncum/ntot, 100.*nnmo/ntot)
    else:
        print '|%i %s | %i | %.2e | %.2e | %.2e | %.2e | %.2e |-' % (i, label, ncum, ncum/time, 100.*nind/ntot, 100.*ncum/ntot, 100.*nnmo/ntot, nnmo/time)

print '[/TABLE]'
print

# backgrounds
n90nmo   = int(hcutnmo.GetBinContent(in90+1))
ctnmo    = int(hcutnmo.GetBinContent(iCT+1))
fincount = hcutcum.GetBinContent(iAllCuts+1)

# n90 method
bg1  = fn90*n90nmo/time
ebg1 = sqrt(pow(efn90/fn90, 2) + 1/n90nmo)/time

# CT method
bg2  = fct*ctnmo/time
ebg2 = sqrt(pow(efct/fct, 2) + 1/ctnmo)/time

# combined n90 & CT
bg3  = (bg1 + bg2) / 2

# double bkgRateEstimationBothError = 0.5*sqrt (dN90dNtowersBkgStatError*dN90dNtowersBkgStatError +
#					       rateN90m1e*rateN90m1e + 
#					       dN90dNtowersBkgStatError*dN90dNtowersBkgStatError +
#					       rateNtowersm1e*rateNtowersm1e +
#					       4*rateFinale*rateFinale
ebg3 = 0.

print "N-1 rates"
print '  n90   : %.2e ' % (n90nmo/time)
print '  CT    : %.2e ' % (ctnmo/time)
print

print "N-1 rate coefficients"
print '  n90   : %.3e ' % (fincount/n90nmo)
print '  ct    : %.3e ' % (fincount/ctnmo)
print

print "Expected background rates"
print '  Simple method : %.2e +/- %.2e' % (bg, ebg)
print '  N90 method    : %.2e +/- %.2e' % (bg1, ebg1)
print '  CT method     : %.2e +/- %.2e' % (bg2, ebg2)
print '  N90 & CT      : %.2e +/- %.2e' % (bg3, ebg3)
print

print "Expected background counts"
print '  Simple method : %.2e +/- %.2e' % (bg*time, ebg*time)
print '  N90 method    : %.2e +/- %.2e' % (bg1*time, ebg1*time)
print '  CT method     : %.2e +/- %.2e' % (bg2*time, ebg2*time)
print '  N90 & CT      : %.2e +/- %.2e' % (bg3*time, ebg3*time)
print

print "Final count : %i" % (fincount)
print

print "Final rate : %.2e +/- %.2e" % (fincount/time, sqrt(fincount)/time)
print


