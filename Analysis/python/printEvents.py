
import sys

from ROOT import *

from utils import *
from cuts import *

# print event info
def Dump(evt):
    print "New tree info :"
    print "Run          ", evt.run
    print "Event        ", evt.id
    print "LS           ", evt.lb
    print "nTowSameiPhi ", evt.nTowerSameiPhi
#    print "Jet energy   ", evt.jets.e[0]
#    print "Jet eta      ", evt.jets[0].eta
#    print "Jet n90      ", evt.jets[0].n90
#    print "Jet n60      ", evt.jets[0].n60
    print "nMuon        ", evt.nMuon


# files
ifile=TFile(sys.argv[1])
run=sys.argv[2]

    

# trees
tree = ifile.Get("stoppedHSCPTree/StoppedHSCPTree")
otree = ifile.Get("globalRunAnalyser/EventTree")
#tree.AddFriend(otree)

# selection
c = CutsOld()

cuts = TCut(c.all)
cuts += TCut("run=="+str(run))
if (len(sys.argv)>3):
    cuts += TCut("lb=="+str(sys.argv[3]))
    cuts += TCut("id=="+str(sys.argv[4]))


# list
nevt = tree.Draw(">>elist", cuts)
elist=gDirectory.Get("elist")


# load libs
gROOT.ProcessLine(".L $CMSSW_BASE/lib/slc5_ia32_gcc434/libStoppedHSCPAnalysis.so")
gROOT.ProcessLine(".L EventTree.C")

# set up objects
newEvt=StoppedHSCPEvent()
oldTree=EventTree()
oldTree.Init(otree)

branch = tree.GetBranch("events")
#branch.SetAddress(AddressOf(newEvt))

for i in range(elist.GetN()):
    
    a = elist.GetEntry(i)
    
#    tree.GetEntry(i)
    tree.GetEntry(elist.GetEntry(i))
    print newEvt.id
    
    # old tree info
#    oldTree.GetEntry(a)
#    oldTree.Dump()
    
    
