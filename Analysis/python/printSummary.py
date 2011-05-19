
import sys
import getopt
import string
import os
import re

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
ddir = os.environ['PWD']+'/'+dataset

# cmssw
cmsswdir = os.environ['CMSSW_BASE']

# ROOT
from ROOT import *


hfile=TFile(dataset+"/histograms.root")

# run info
time=0
if (not isMC):
    htime=hfile.Get("runs/hlivetime")
    hnlb=hfile.Get("runs/hnlb")
    
    print "Run\tLS\tLivetime"
    for i in range(1,htime.GetNbinsX()+1):
        print htime.GetXaxis().GetBinLabel(i)+"\t"+str(hnlb.GetBinContent(i))+"\t"+str(htime.GetBinContent(i))


    # total time
    time=htime.Integral()
    print "Total live time : "+str(time)+" s"


hcutcum=hfile.Get("histograms/Cuts/hncutcum")
hcutind=hfile.Get("histograms/Cuts/hncutind")
hcutnmo=hfile.Get("histograms/Cuts/hnminus1cut")
hnmu=hfile.Get("histograms/NoCuts/hnmu")

ntot=hnmu.GetEntries()
if isMC:
    ntot=hcutcum.GetBinContent(1)

# if (ntot==0):  print "ERROR!  Total number of entries = 0!"  # EXIT?

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
        if (ntot<>0):
            print '|%i %s | %i | %.2e | %.2e |' % (i, label, ncum, 100.*ncum/ntot, 100.*nnmo/ntot)
        else:
            print '|%i %s | %i | N/A | N/A |' % (i, label, ncum)
    else:
        if (ntot<>0):
            print '|%i %s | %i | %.2e | %.2e | %.2e | %.2e | %.2e |-' % (i, label, ncum, ncum/time, 100.*nind/ntot, 100.*ncum/ntot, 100.*nnmo/ntot, nnmo/time)
        else:
            print '|%i %s | %i | N/A | N/A |' % (i, label, ncum)
            
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


# expected counts
print 'Expected BG counts : %.2e +/- %.2e (stat) +/- %.2e (syst)' % (bgRateEst*time, bgRateEst*errStatBGRateEst*time, bgRateEst*errSystBGRateEst*time)
print


# get lists of runs, fills
logfile = open(dataset+"/histogrammer.log", 'r')
line1 = re.compile(r'(Runs :\s*)(\S*)')
line2 = re.compile(r'(Fills :\s*)(\S*)')
runsStr = ""
fillsStr = ""
for line in logfile.readlines():
    l1 = line1.match(line)
    if (l1):
        runsStr = l1.group(2)
    l2 = line2.match(line)
    if (l2):
        fillsStr = l2.group(2)

runlist = runsStr.split(',')


# now write Toy MC file
bgRateTotErr = sqrt(pow(bgRateEst*errStatBGRateEst, 2) + pow(bgRateEst*errSystBGRateEst, 2))

ofile = open(dataset+"/parameters.txt", 'w')
ofile.write("mass\t\t\t200\n")
ofile.write("crossSection\t\t606\n")
ofile.write("lifetime\t\t1\n")
ofile.write("signalEff\t\t0.033652\n")
ofile.write("signalEff_e\t\t0.0\n")
ofile.write("bgRate\t\t\t")
ofile.write(str(bgRateEst)+"\n")
ofile.write("bgRate_e\t\t")
ofile.write(str(bgRateTotErr)+"\n")
ofile.write("scaleUncert\t\t0.13\n")
ofile.write("optimizeTimeCut\t\t1\n")
ofile.write("histFile\t\t")
ofile.write(ddir+"/histograms.root\n")
ofile.write("lumiFile\t\t")
ofile.write(cmsswdir+"/src/StoppedHSCP/Analysis/data/lumi_all.csv\n")
ofile.write("jsonFile\t\t")
ofile.write(cmsswdir+"/src/StoppedHSCP/Analysis/data/"+dataset+".root\n")
ofile.write("lumiFirstRun\t\t")
ofile.write(runlist[0]+"\n")  
ofile.write("lumiLastRun\t\t")
ofile.write(runlist[len(runlist)-1]+"\n")
ofile.write("fills\t\t\t")
ofile.write(fillsStr+"\n")
ofile.write("eventsFile\t\t")
ofile.write(ddir+"/eventList.log\n")
ofile.write("nTrialsSignal\t\t100\n")
ofile.write("nTrialsBackground\t100\n")
ofile.write("simulateExpt\t\t0\n")
ofile.write("fillScheme\t\tSingle_2b_1_1_1\n")
ofile.write("beamOnTime\t\t0.\n")
ofile.write("beamOffTime\t\t0.\n")
ofile.write("instLumi\t\t0.\n")
ofile.write("runningTime\t\t0.\n")
ofile.close()

