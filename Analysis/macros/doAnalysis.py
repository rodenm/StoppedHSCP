
# Run analysis macros for a given processing

import sys
import os
import tarfile

from ROOT import *

from style import *
from basicHistos import *
from cuts import *

# arguments : file location and local dir for results
if len(sys.argv)!=4 :
    print "Wrong number of arguments"
    print "Usage : python doAnalysis.py <input file> <output dir> <time>"
    sys.exit(1)

filename=sys.argv[1]
dir=sys.argv[2]
time=int(sys.argv[3])

# make dir to store results if not present
odir = os.getcwd()+"/"+dir
print "Putting results in "+odir
if not os.path.exists(odir):
    os.makedirs(odir)

# open input file
ifile = TFile(filename)

# set the style
tdrStyle()
gROOT.SetStyle("tdrStyle")
gROOT.ForceStyle()


# get tree & add old tree as friend
tree = ifile.Get("stoppedHSCPTree/StoppedHSCPTree")
#oldtree = ifile.Get("an_HLT/EventTree")
oldtree = ifile.Get("globalRunAnalyser/EventTree")
tree.AddFriend(oldtree)

# run analysis
cuts = CutsOld()

basicHistos(tree, odir+"/BasicHistos.root", time, cuts)

basicPlots(odir+"/BasicHistos.root", odir+"/BasicPlots.ps", false)


tar = tarfile.open(name = odir+".tgz", mode = 'w:gz')
tar.add(dir)

#for file in os.listdir(odir):
#	t.add(file);
tar.close()


