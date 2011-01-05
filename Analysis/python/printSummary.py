
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

print "Rate coefficients from control sample"
print "Rate coefficient N90 : ", rateCoeffN90
print "Rate coefficient CT  : ", rateCoeffCT

# backgrounds
n90nmo   = int(hcutnmo.GetBinContent(in90+1))
ctnmo    = int(hcutnmo.GetBinContent(iCT+1))
fincount = hcutcum.GetBinContent(iAllCuts+1)

print "N-1 rates"
print '  n90   : %.2e +/- %.2e (stat)' % (n90nmo/time, sqrt(n90nmo)/time)
print '  CT    : %.2e +/- %.2e (stat)' % (ctnmo/time, sqrt(ctnmo)/time)
print


print "Expected background rates"

### all error variables are relative, not absolute ###

# n90 method
bgRateN90        = rateCoeffN90*n90nmo/time
errStatBGRateN90 = 1/sqrt(n90nmo)
errSystBGRateN90 = sqrt(errSystRateCoeff*errSystRateCoeff +
                        errCtrlN90NM1Rate*errCtrlN90NM1Rate +
                        errCtrlFinRate*errCtrlFinRate)

print '  N90 method    : %.2e +/- %.2e (stat) +/- %.2e (syst)' % (bgRateN90, bgRateN90*errStatBGRateN90, bgRateN90*errSystBGRateN90)


# CT method
bgRateCT         = rateCoeffCT*ctnmo/time
errStatBGRateCT  = 1/sqrt(ctnmo)
errSystBGRateCT  = sqrt(errSystRateCoeff*errSystRateCoeff +
                        errCtrlCTNM1Rate*errCtrlCTNM1Rate +
                        errCtrlFinRate*errCtrlFinRate)

print '  CT method     : %.2e +/- %.2e (stat) +/- %.2e (syst)' % (bgRateCT, bgRateCT*errStatBGRateCT, bgRateCT*errSystBGRateCT)


# combined n90 & CT
bgRateEst        = 0.5 * (bgRateN90 + bgRateCT)
errStatBGRateEst = sqrt(errStatBGRateN90*errStatBGRateN90 +
                        errStatBGRateCT*errStatBGRateCT)
errSystBGRateEst = 0.5 * sqrt(2*errSystRateCoeff*errSystRateCoeff +
                              errCtrlN90NM1Rate*errCtrlN90NM1Rate +
                              errCtrlCTNM1Rate*errCtrlCTNM1Rate +
                              4*errCtrlFinRate*errCtrlFinRate)


print '  Combined      : %.2e +/- %.2e (stat) +/- %.2e (syst)' % (bgRateEst, bgRateEst*errStatBGRateEst, bgRateEst*errSystBGRateEst)
print



