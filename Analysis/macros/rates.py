

from ROOT import *

from histograms import *
from plots import *


lumiBlockLength = 25. * 1e-9 * 3564 * pow(2., 20)


def ratePlots(file, ofilename):

    dir = "Rates"

    histPlot(dir+"/hbx", file, ofilename, 0., True, "", "BX", "N events")
    histPlot(dir+"/hlb", file, ofilename, 0., True, "", "LS", "Rate")
    histPlot(dir+"/hlbdist", file, ofilename, 0., True, "", "Rate", "N LS")

    histPlot(dir+"/hlbmu", file, ofilename, 0., True, "", "LS", "Rate")
    histPlot(dir+"/hlbmudist", file, ofilename, 0., True, "", "Rate", "N LS")

    histPlot(dir+"/hlbtim", file, ofilename, 0., True, "", "LS", "Rate")
    histPlot(dir+"/hlbtimdist", file, ofilename,  0., True, "", "Rate", "N LS")
    histPlot(dir+"/hlbtimdist", file, ofilename, 0., True, "", "Rate", "N LS")


def rateHistos(tree, file, cutObj, run, scale):

    file.mkdir("Rates")
    file.cd("Rates")

    if (run!=0):
        c1 = TCut("run=="+str(run))
    else:
        c1 = TCut("")

    # some standard histograms
    histogram1D(tree, "hbx", "bx>>hbx", c1, 1., "BX number (new)", 3564, 0., 3564.)
    histogram1D(tree, "horb", "orbit>>horb", c1, 1., "Orbit number (new)", 100, 0., 10000.)
    histogram1D(tree, "htime", "time2>>htime", c1, 1., "Event time", 100, 0., 1.E8)

    # HLT rate per LS
    hlb=histogram1D(tree, "hlb", "lb>>hlb", c1, 1./lumiBlockLength, "Lumi block", 2000, 0., 2000.)  
    rateDist(hlb, 100)

    # muon rate per LS
    c2 = TCut("nMuon>0")
    c2 += c1
    hlbmu=histogram1D(tree, "hlbmu", "lb>>hlbmu", c2, 1./lumiBlockLength, "Lumi block", 2000, 0., 2000.)  
    rateDist(hlbmu, 100)

    # bad timing rate per LS
    c3 = TCut("TimingRightPeak<0.15 || TimingFracRightNextRight<0.1 || TimingFracRightNextRight>0.5 || TimingFracInLeader<0.4 || TimingFracInLeader>0.7 || TimingFracInCentralFour<0.90")
    c3 += c1
    hlbtim=histogram1D(tree, "hlbtim", "lb>>hlbtim", c3, 1./lumiBlockLength, "Lumi block", 2000, 0., 2000.)  
    rateDist(hlbtim, 100)

    file.cd()



# make a histogram of 'rate distribution' from histogram of eg. rate-per-LS
def rateDist(rateByTime, nbins):

    name=rateByTime.GetName()+"dist"
    h = TH1D(name, "Rate", nbins, rateByTime.GetMinimum()*0.8, rateByTime.GetMaximum()*1.25)

    for i in range(rateByTime.GetNbinsX()):
        r=rateByTime.GetBinContent(i)
        if (r>0.):
            h.Fill(r)
    
    f = TF1(name+"fit", "gaus")
    h.Fit(name+"fit", "")       

    h.Write()

    return h


        
