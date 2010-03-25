

from ROOT import *

from histograms import *
from plots import *


lumiBlockLength = 25. * 1e-9 * pow(2., 18)


def ratePlots(file):

    dir = "Rates"
    canvas = TCanvas("canvas")

    histPlot(dir+"/hlb", file, canvas, 0., True, "", "LS", "Rate")

        


def rateHistos(tree, file, cutObj, run):

    file.mkdir("Rates")
    file.cd("Rates")

    if (run!=0):
        cuts = TCut("")
    else:
        cuts = TCut("run=="+str(run))

#    n=tree.Draw("lb>>hlb", cuts)
#    hlb.Write()
                    
    # event time
    histogram1D(tree, "hbx", "bx>>hbx", cuts, 1., "BX number (new)", 3564, 0., 3564.)
    histogram1D(tree, "horb", "orbit>>horb", cuts, 1., "Orbit number (new)", 100, 0., 10000.)    
    hlb=histogram1D(tree, "hlb", "lb>>hlb", cuts, 1., "Lumi block", 2000, 0., 2000.)  
    histogram1D(tree, "htime", "time>>htime", cuts, 1., "Event time", 100, 0., 1.E8)
    
    rateDist(hlb, 100, 0., 10.)
    
    file.cd()



# make a histogram of 'rate distribution' from histogram of eg. rate-per-LS
def rateDist(rateByTime, nbins, lo, hi):

    rateDist = TH1D(str(rateByTime.GetName())+"dist", "Rate", nbins, lo, hi)

    for i in range(0, rateByTime.GetNbinsX()):
        rateDist.Fill(rateByTime.GetBinContent(i))

    rateDist.Write()

    return rateDist


        
