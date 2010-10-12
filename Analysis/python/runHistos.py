
# make per-run histograms

import math

from ROOT import *

from constant import *

nCuts   = 15
nCutJ50 = 7
nCutCT  = 10

def getNLumiBlocks(hist) :
    n=0
    for i in range(0,hist.GetNbinsX()):
        if (hist.GetBinContent(i) > 0.):
            n=n+1
    return n

def getLivetime2(hist) :
    return getNLumiBlocks(hist) * lumiBlockLength


def runHistos(hfile, runs):

    print "Making per-run plots for : ", runs

    if not hfile.cd("ByRun"):
        hfile.mkdir("ByRun")
        hfile.cd("ByRun")

    # book per-run histograms
    nruns=len(runs)
    hnhlt       = TH1D("hnhlt", "HLT counts", nruns, 0., 0.)
    hnfin       = TH1D("hnfin", "Final counts", nruns, 0., 0.)
    hefftime    = TH1D("hefftime", "Effective live time", nruns, 0., 0.)
    hnlb        = TH1D("hnlb", "N lumi blocks", nruns, 0., 0.)
    hlivetime   = TH1D("hlivetime", "Live time", nruns, 0., 0.)
    hnpostjet   = TH1D("hnpostjet", "N events after jet cuts", nruns, 0., 0.)
    hnposttim   = TH1D("hnposttim", "N events after timing cuts", nruns, 0., 0.)
    hnj50nmo    = TH1D("hnj50nmo", "Jet50 N-1 counts", nruns, 0., 0.)
    
    # rate after each cut
    hratecuts = []
    for c in range(0,nCuts):
        hratecuts.append(TH1D("hratecut"+str(c), "Rate cut "+str(c), nruns, 0., 0.))

    # 2D vs run plots
    hbx      = TH2D("hbx", "BX vs Run;BX;", nruns, 0, nruns, 3564, 0., 3564.)
    heta     = TH2D("heta", "#eta vs Run;#eta;", nruns, 0, nruns, 70, -3.5, 3.5)
    hphi     = TH2D("hphi", "#phi vs Run;#phi;", nruns, 0, nruns, 72, -1. * math.pi, 1. * math.pi)
    
    hbxfin   = TH2D("hbxfin", "BX vs Run;BX;", nruns, 0, nruns, 3564, 0., 3564.)
    hetafin  = TH2D("hetafin", "#eta vs Run;#eta;", nruns, 0, nruns, 70, -3.5, 3.5)
    hphifin  = TH2D("hphifin", "#phi vs Run;#phi;", nruns, 0, nruns, 72, -1. * math.pi, 1. * math.pi)
    
    # fill histograms
    i=0
    for run in runs:
        runstr = str(run)

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
            hlivetime.SetBinError(i+1, lumiBlockLength/2)
            
            hcutcount = hfile.Get(runstr+"/Cuts/hncutcum")
            
            # final counts
            nevtFinal = hcutcount.GetBinContent(nCuts)
            hnfin.Fill(str(run), nevtFinal)
            hnfin.SetBinError(i+1, sqrt(nevtFinal))
            
            # post jet counst
            npostjet = hcutcount.GetBinContent(iCT+1)
            hnpostjet.Fill(str(run), npostjet)
            hnpostjet.SetBinError(i+1, sqrt(npostjet))
            
            # post timing counts
            nposttim = 0#hcutcount.GetBinContent(7)
            hnposttim.Fill(str(run), nposttim)
            hnposttim.SetBinError(i+1, sqrt(nposttim))

            hnminus1cut = hfile.Get(runstr+"/Cuts/hnminus1cut")

            # J50 N-1 counts
            nj50nmo = hnminus1cut.GetBinContent(nCutJ50+1)
            hnj50nmo.Fill(str(run), nj50nmo)
            hnj50nmo.SetBinError(i+1, sqrt(nj50nmo))
            
            # rate after N cuts
            cut = TCut("")
            
            for c in range(0, nCuts):
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

    # save histograms
    hnhlt.Write()
    hnfin.Write()
    hefftime.Write()
    hnlb.Write()
    hlivetime.Write()
    hnpostjet.Write()
    hnposttim.Write()
    hnj50nmo.Write()
    for c in range(0,nCuts):
        hratecuts[c].Write()
    hbx.Write()
    heta.Write()
    hphi.Write()
    hbxfin.Write()
    hetafin.Write()
    hphifin.Write()
    
