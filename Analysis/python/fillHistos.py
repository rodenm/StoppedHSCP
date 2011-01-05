
# make per-fill histograms

from ROOT import *

from constants import *

def fillHistos(hfile, fills, fillinfo):

    print "Making per-fill plots for : ", fills
    
    hnfin       = hfile.Get("ByRun/hnfin")
    hlivetime   = hfile.Get("ByRun/hlivetime")
    nruns = hnfin.GetXaxis().GetNbins()

    # book histograms
    if not hfile.cd("ByFill"):
        hfile.mkdir("ByFill")
        hfile.cd("ByFill")

    nfills=len(fills)
    hfcount  = TH1D("hfillcount","",nfills, 0., 0.)
    hftime   = TH1D("hfilltime","",nfills, 0., 0.)
    hfrate   = TH1D("hfillrate","",nfills, 0., 0.)

##     for f,i in zip(fills, range(1,nfills+1)):
##         hfcount.GetXaxis().SetBinLabel(i, str(f))
##         hftime.GetXaxis().SetBinLabel(i, str(f))
##         hfrate.GetXaxis().SetBinLabel(i, str(f))

    # fill histos
    for i in range(0,nruns):
        time   = hlivetime.GetBinContent(i+1)
        counts = hnfin.GetBinContent(i+1)
        
        binlabel=hnfin.GetXaxis().GetBinLabel(i+1)
        run=0
        if (binlabel!=''):
            run = int(binlabel)
            print run, time, counts

            for fill in fillinfo:
                if (fill[1].count(run) > 0):
                    hfcount.Fill(str(fill[0]), counts)
                    hftime.Fill(str(fill[0]), time)
                    if (time>0.):
                        hfrate.Fill(str(fill[0]), counts/time)

    # set errors
    for i in range(1,nfills+1):
        c = hfcount.GetBinContent(i)
        if (c>0):
            hfcount.SetBinError(i,sqrt(hfcount.GetBinContent(i)))
        else:
            hfcount.SetBinError(i,1)

    # expected background
    hbgmpv = TH1D("hbgmpv", "Expected BG (MPV);fill;N", nfills, 0., 0.)
    hbgmean = TH1D("hbgmean", "Expected BG (mean);fill;N", nfills, 0., 0.)

    for i in range(1,nfills+1):
        label = hftime.GetXaxis().GetBinLabel(i)
        time  = hftime.GetBinContent(i)

        poisson = TF1("poisson", "TMath::Poisson(x, [0])", 0., 100.)
        poisson.SetParameter(0,time * ctrlFinRate)
        mpv = poisson.GetMaximumX()

        hbgmpv.Fill(label, mpv)
        hbgmpv.SetBinError(i, 0.)
        hbgmean.Fill(label, time*ctrlFinRate)
        hbgmean.SetBinError(i, time*errCtrlFinRate*ctrlFinRate)

    # N-1 estimate
##     hbgj50 = TH1D("hbgj50", "Expected BG (Jet50N-1);fill;N", nfills, 0., 0.)
##     for i in range(1,nfills+1):
##         label = hftime.GetXaxis().GetBinLabel(i)
##         est   = hfj50nmo.GetBinContent(i) * fj50nmo
##         err2   = 0.
##         if (fj50nmo>0.):
##             err2 += pow(ej50nmo/fj50nmo, 2)
##         if (hfj50nmo.GetBinContent(i)>0.):
##             err2 += pow(hfj50nmo.GetBinError(i)/hfj50nmo.GetBinContent(i), 2)
##         err  = sqrt(err2)
        
##         hbgj50.Fill(label, est)
##         hbgj50.SetBinError(i, err)
        

    # save histograms
    hfcount.Write()
    hftime.Write()
    hfrate.Write()
    hbgmpv.Write()
    hbgmean.Write()
