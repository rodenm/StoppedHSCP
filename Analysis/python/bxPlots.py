#! /usr/bin/env python

#
# Make plots of BX distributions, per-fill
#

import sys
import optparse
import string
import os

# options
parser = optparse.OptionParser()
parser.add_option("-d", "--dir", action="store")
parser.add_option("-e", "--era", action="store")
parser.add_option("-t", "--type", action="store", default="")

(opts, args)=parser.parse_args()

type=opts.type
fillset=opts.era
dataset=opts.dir

# ROOT wankiness
sys.argv=[]
sys.argv.append('-b')

from ROOT import *
from math import *
from style import *
from plots import *


# set style
tdrStyle()
gROOT.SetStyle("tdrStyle")
gROOT.ForceStyle()

# output file
ofile = dataset+"/"+dataset+"_"+type+"BX.ps"
opdf = dataset+"/"+dataset+"_"+type+"BX.pdf"

# prepare canvas for plotting
canvas = TCanvas("c")
canvas.SetLogy(1)
canvas.Print(ofile+"[", "Portrait")

# open file
ifile1 = TFile(dataset+"/histograms.root", "read")
ifile2 = TFile(dataset+"/BXDistributions.root", "read")

# get histogram of time per fill
hfilltime = ifile1.Get("fills/hfilltime")


# loop over some fills
def bxPlot(fills, ifile, ofile, wrt):

    hbxvec=[]
    legvec=[]

    for fill in fills:

        fillstr = str(fill)

        if (wrt=="coll"):
            hnorm = ifile.Get("hRelBXNorm/hRelBXNorm"+fillstr)
            hbx   = ifile.Get("hRelBX"+type+"/hRelBX"+type+fillstr)
        else:
            hnorm = ifile.Get("hRelUPBunchBXNorm/hRelUPBunchBXNorm"+fillstr)
            hbx   = ifile.Get("hRelUPBunchBX"+type+"/hRelUPBunchBX"+type+fillstr)

        time=0.
        for i in range(1, hfilltime.GetNbinsX()+1):
            if (hfilltime.GetXaxis().GetBinLabel(i) == fillstr):
                time = hfilltime.GetBinContent(i)
                break

        hbx.Divide(hnorm)
        hbx.Scale(1/time)
        
        hbxvec.append(hbx)
        legvec.append(fillstr)

    if (wrt=="coll"):
        multiPlot(hbxvec, legvec, ofile, 1E-6, 1E0, "BX wrt collision (normalised)", "BX", "Hz", "", 4, -20., 20.)
    else:
        multiPlot(hbxvec, legvec, ofile, 1E-6, 1E0, "BX wrt UPB (normalised)", "BX", "Hz", "", 4, -20., 20.)

if fillset=="2010A":
    fills=[1117,1118,1119,1121,1122,1134,1179,1182]
    bxPlot(fills, ifile2, ofile, "coll")
    fills=[1185,1186,1188,1190,1192,1196,1197,1198]
    bxPlot(fills, ifile2, ofile, "coll")
    fills=[1199,1207,1222,1224,1225,1226,1229,1232]
    bxPlot(fills, ifile2, ofile, "coll")
    fills=[1233,1250,1251,1253,1256,1257,1258,1260]
    bxPlot(fills, ifile2, ofile, "coll")
    fills=[1262,1263,1266,1267,1268,1271,1283,1284]
    bxPlot(fills, ifile2, ofile, "coll")
    fills=[1285,1287,1293,1295,1298,1299,1301,1303]
    bxPlot(fills, ifile2, ofile, "coll")
    fills=[1305,1308,1309]
    bxPlot(fills, ifile2, ofile, "coll")
    fills=[1117,1118,1119,1121,1122,1134,1179,1182]
    bxPlot(fills, ifile2, ofile, "upb")
    fills=[1185,1186,1188,1190,1192,1196,1197,1198]
    bxPlot(fills, ifile2, ofile, "upb")
    fills=[1199,1207,1222,1224,1225,1226,1229,1232]
    bxPlot(fills, ifile2, ofile, "upb")
    fills=[1233,1250,1251,1253,1256,1257,1258,1260]
    bxPlot(fills, ifile2, ofile, "upb")
    fills=[1262,1263,1266,1267,1268,1271,1283,1284]
    bxPlot(fills, ifile2, ofile, "upb")
    fills=[1285,1287,1293,1295,1298,1299,1301,1303]
    bxPlot(fills, ifile2, ofile, "upb")
    fills=[1305,1308,1309]
    bxPlot(fills, ifile2, ofile, "upb")

if fillset=="2010B":
    fills=[1364,1366,1372,1373,1375,1381,1387]
    bxPlot(fills, ifile2, ofile, "coll")
    fills=[1388,1389,1393,1394,1397,1400,1408]
    bxPlot(fills, ifile2, ofile, "coll")
    fills=[1418,1424,1427,1430,1439,1440,1443]
    bxPlot(fills, ifile2, ofile, "coll")
    fills=[1444,1450,1453]
    bxPlot(fills, ifile2, ofile, "coll")
    fills=[1364,1366,1372,1373,1375,1381,1387]
    bxPlot(fills, ifile2, ofile, "upb")
    fills=[1388,1389,1393,1394,1397,1400,1408]
    bxPlot(fills, ifile2, ofile, "upb")
    fills=[1418,1424,1427,1430,1439,1440,1443]
    bxPlot(fills, ifile2, ofile, "upb")
    fills=[1444,1450,1453]
    bxPlot(fills, ifile2, ofile, "upb")

if fillset=="2011A":
    fills=[1711,1712,1713,1716,1721,1722,1727,1728]
    bxPlot(fills, ifile2, ofile, "coll")
    fills=[1729,1730,1731,1732,1733,1735,1736,1737]
    bxPlot(fills, ifile2, ofile, "coll")
    fills=[1739,1743,1745,1749,1795,1796,1798,1799]
    bxPlot(fills, ifile2, ofile, "coll")
    fills=[1800,1801,1802,1803,1804,1805,1806,1809]
    bxPlot(fills, ifile2, ofile, "coll")
    fills=[1812,1813,1815,1816,1822,1823,1835,1836]
    bxPlot(fills, ifile2, ofile, "coll")
    fills=[1841,1844,1845,1846,1848,1851,1852,1854]
    bxPlot(fills, ifile2, ofile, "coll")
    fills=[1855,1856,1859,1862,1863,1864]
    bxPlot(fills, ifile2, ofile, "coll")
    fills=[1711,1712,1713,1716,1721,1722,1727,1728]
    bxPlot(fills, ifile2, ofile, "upb")
    fills=[1729,1730,1731,1732,1733,1735,1736,1737]
    bxPlot(fills, ifile2, ofile, "upb")
    fills=[1739,1743,1745,1749,1795,1796,1798,1799]
    bxPlot(fills, ifile2, ofile, "upb")
    fills=[1800,1801,1802,1803,1804,1805,1806,1809]
    bxPlot(fills, ifile2, ofile, "upb")
    fills=[1812,1813,1815,1816,1822,1823,1835,1836]
    bxPlot(fills, ifile2, ofile, "upb")
    fills=[1841,1844,1845,1846,1848,1851,1852,1854]
    bxPlot(fills, ifile2, ofile, "upb")
    fills=[1855,1856,1859,1862,1863,1864]
    bxPlot(fills, ifile2, ofile, "upb")


# close file
canvas = TCanvas("c")
canvas.Print(ofile+"]")

# convert to PDF
subprocess.call(["ps2pdf", ofile, opdf])
subprocess.call(["rm", ofile])
