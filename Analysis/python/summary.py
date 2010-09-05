
# make summary histograms and write text file
import sys
import getopt
import json
import math

from ROOT import *

TH1.SetDefaultSumw2()

# arguments
try:
    opts, args = getopt.getopt(sys.argv[1:], "")
except getopt.GetoptError:
    sys.exit(2)

if len(args)<2:
    sys.exit(1)

jsonfile=args[1]
dataset=args[0]


# read JSON file to get list of runs/LS
jfile = open(jsonfile, 'r')

lsranges={}
for line in jfile:
    lsranges.update(json.loads(line))

runstrs = lsranges.keys()
runstrs.sort()
for runstr in runstrs:
    last=lsranges[runstr][0]
    for lsrange in lsranges[runstr]:
        print runstr, lsrange[0], lsrange[1]
        if (last[0]>lsrange[0]):
            print "Found inconsistent LS range!"
            sys.exit(1)


# read fills file
fills=[]
ffile = open("StoppedHSCP/Analysis/data/fills.txt")
ffile.next()
for line in ffile:
    tokens=line.split()
    if (len(tokens)==3):
        rstrs=tokens[2].split(',')
        rs=[]
        for rstr in rstrs:
            rs.append(int(rstr))
        fills.append([ int(tokens[0]), rs, 0. ])


#print fills

# open histogram file
hfile = TFile(dataset+"/histograms.root", "update")


# book per-run histograms
nruns=len(runstrs)
hnhlt       = TH1D("hnhlt", "HLT counts", nruns, 0., 0.)
hnfin       = TH1D("hnfin", "Final counts", nruns, 0., 0.)
hefftime    = TH1D("hefftime", "Effective live time", nruns, 0., 0.)
hnlb        = TH1D("hnlb", "N lumi blocks", nruns, 0., 0.)
hlivetime   = TH1D("hlivetime", "Live time", nruns, 0., 0.)
hnpostjet   = TH1D("hnpostjet", "N events after jet cuts", nruns, 0., 0.)
hnposttim   = TH1D("hnposttim", "N events after timing cuts", nruns, 0., 0.)

# rate after each cut
hratecuts = []
for c in range(0,13):
    hratecuts.append(TH1D("hratecut"+str(c), "Rate cut "+str(c), nruns, 0., 0.))

# 2D vs run plots
hbx      = TH2D("hbx", "BX vs Run;BX;", nruns, 0, nruns, 3564, 0., 3564.)
heta     = TH2D("heta", "#eta vs Run;#eta;", nruns, 0, nruns, 70, -3.5, 3.5)
hphi     = TH2D("hphi", "#phi vs Run;#phi;", nruns, 0, nruns, 72, -1. * math.pi, 1. * math.pi)

hbxfin   = TH2D("hbxfin", "BX vs Run;BX;", nruns, 0, nruns, 3564, 0., 3564.)
hetafin  = TH2D("hetafin", "#eta vs Run;#eta;", nruns, 0, nruns, 70, -3.5, 3.5)
hphifin  = TH2D("hphifin", "#phi vs Run;#phi;", nruns, 0, nruns, 72, -1. * math.pi, 1. * math.pi)

# helper functions
lumiBlockLength = 25.e-9 * 3564. * pow(2., 18)

def getNLumiBlocks(hist) :
    n=0
    for i in range(0,hist.GetNbinsX()):
        if (hist.GetBinContent(i) > 0.):
            n=n+1
    return n

def getLivetime2(hist) :
    return getNLumiBlocks(hist) * lumiBlockLength


# fill histograms
i=0
for runstr in runstrs:
    run = int(runstr)

    # HLT counts
    hlb=hfile.Get(runstr+"/NoCuts/hlb")

    if (hlb is not None):
    
        nhlt=hlb.GetEntries()
        hnhlt.Fill(str(run), nhlt)
        hnhlt.SetBinError(i+1, sqrt(nhlt))
        
        nlb = getNLumiBlocks(hlb)
        hnlb.Fill(str(run), nlb)
        
        # live time (N non-zero LS after HLT)
        livetime = getLivetime2(hlb)
        hlivetime.Fill(str(run), livetime)
        hlivetime.SetBinError(i+1, 10.)
        
        hcutcount = hfile.Get(runstr+"/Cuts/hncutcum")
        
        # final counts
        nevtFinal = hcutcount.GetBinContent(13)
        hnfin.Fill(str(run), nevtFinal)
        hnfin.SetBinError(i+1, sqrt(nevtFinal))
        
        # post jet counst
        npostjet = hcutcount.GetBinContent(7)
        hnpostjet.Fill(str(run), npostjet)
        hnpostjet.SetBinError(i+1, sqrt(npostjet))
        
        # post timing counts
        nposttim = hcutcount.GetBinContent(7)
        hnposttim.Fill(str(run), nposttim)
        hnposttim.SetBinError(i+1, sqrt(nposttim))
        
        # rate after N cuts
        cut = TCut("")
        
        for c in range(0, 13):
            n=hcutcount.GetBinContent(c+1)
            rate=0.
            erate=0.
            if (livetime>0.):
                rate=n/livetime
                erate=sqrt(n)/livetime
            hratecuts[c].Fill(str(run), rate)
            hratecuts[c].SetBinError(i+1, erate)

        # BX vs run
        hbx0=hfile.Get(runstr+"/Cuts/hbx0")
        for j in range(0,3564):
            hbx.Fill(str(run), j, hbx0.GetBinContent(j+1))

        # eta/phi vs run
        hetaphi0=hfile.Get(runstr+"/Cuts/hjetetaphi0")
        heta0=hetaphi0.ProjectionX()
        for j in range(1,heta0.GetNbinsX()):
            heta.Fill(str(run), heta0.GetBinCenter(j), heta0.GetBinContent(j))
            
        hphi0=hetaphi0.ProjectionY()
        for j in range(0,hphi0.GetNbinsX()):
            hphi.Fill(str(run), hphi0.GetBinCenter(j), hphi0.GetBinContent(j))

        # BX vs run (after all cuts)
        hbx11=hfile.Get(runstr+"/Cuts/hbx11")
        for j in range(0,3564):
            hbxfin.Fill(str(run), j, hbx11.GetBinContent(j+1))

        # eta/phi vs run (after all cuts)
        hetaphi11=hfile.Get(runstr+"/Cuts/hjetetaphi11")
        heta11=hetaphi11.ProjectionX()
        for j in range(1,heta11.GetNbinsX()):
            hetafin.Fill(str(run), heta11.GetBinCenter(j), heta11.GetBinContent(j))

        hphi11=hetaphi11.ProjectionY()
        for j in range(0,hphi11.GetNbinsX()):
            hphifin.Fill(str(run), hphi11.GetBinCenter(j), hphi11.GetBinContent(j))

        i=i+1


# book per-fill histograms
nfills = len(fills)
hfcount=TH1D("hcount","",nfills, 0., 0.)
hftime=TH1D("htime","",nfills, 0., 0.)
hfrate=TH1D("hrate","",nfills, 0., 0.)

hcounts = hfile.Get("hnfin")
hlivetime   = hfile.Get("hlivetime")

# fill per-fill histos
for i in range(0,hnfin.GetXaxis().GetNbins()):
    time   = hlivetime.GetBinContent(i+1)
    counts = hnfin.GetBinContent(i+1)

    binlabel=hnfin.GetXaxis().GetBinLabel(i+1)
    run=0
    if (binlabel!=''):
        run = int(binlabel)
        print run, time, counts

        for fill in fills:
            if (fill.count(run) > 0):
                hfcount.Fill(str(fill[0]), counts)
                hftime.Fill(str(fill[0]), time)


# save histograms
hfile.mkdir("ByRun")
hfile.cd("ByRun")

hnhlt.Write()
hnfin.Write()
hefftime.Write()
hnlb.Write()
hlivetime.Write()
hnpostjet.Write()
hnposttim.Write()
for c in range(0,13):
    hratecuts[c].Write()
hbx.Write()
heta.Write()
hphi.Write()
hbxfin.Write()
hetafin.Write()
hphifin.Write()

hfile.mkdir("ByFill")
hfile.cd("ByFill")

hfcount.Write()
hftime.Write()
hfrate.Write()


hfile.Close()




# print summary
