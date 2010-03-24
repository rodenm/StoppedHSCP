
import sys

from ROOT import *

from utils import *
from cuts import *


ifile=TFile(sys.argv[1])
run=sys.argv[2]

tree = ifile.Get("stoppedHSCPTree/StoppedHSCPTree")
oldtree = ifile.Get("globalRunAnalyser/EventTree")
tree.AddFriend(oldtree)


cuts = TCut(CutsOld.jetMu)
cuts += TCut("run=="+str(run))


nevt = tree.Draw(">>elist", cuts)
elist=gDirectory.Get("elist")

gROOT.ProcessLine(".L StoppedHSCPTree.C")

myobj=StoppedHSCPTree()
myobj.Init(tree)

print "Found ", nevt, " events"


for i in range(elist.GetN()):
    a = elist.GetEntry(i)
    b = myobj.LoadTree(a)
    myobj.GetEntry(elist.GetEntry(i))
    myobj.Dump()
    
