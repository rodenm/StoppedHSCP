
from math import sqrt
from ROOT import *

# useful methods for getting info from the data and run trees

errTime = 10

def getLivetime(runtree, run):
    time=0
    # loop over runs in run TTree
    nruns=runtree.GetEntriesFast()
    for i in range(0,nruns):
        entry = runtree.LoadTree(i)
        if entry < 0:
            break
        nb = runtree.GetEntry(i)
        if nb <= 0:
            continue
        time+=runtree.livetime
        if (runtree.run==run):
            return runtree.livetime
    return time


# return array of run number/livetime pairs
def getRuns(runtree):
    runs=[]
    # loop over runs in run TTree
    nruns=runtree.GetEntriesFast()
    for i in range(0,nruns):
        entry = runtree.LoadTree(i)
        if entry < 0:
            break
        nb = runtree.GetEntry(i)
        if nb <= 0:
            continue
        runs.append(runtree.run)
    return runs


# get number of events passing a given cut
def nEvents(tree, cuts, run):
    if (run==0):
        return tree.Draw("",cuts)
    else:
        if (cuts==""):
            return tree.Draw("", TCut("run=="+str(run)));
        else:
            c = TCut(cuts)
            c += TCut("run=="+str(run))
            return tree.Draw("", c);


# get rate for given cut and run
def getRate(tree, runtree, cuts, run):
    nevt = nEvents(tree, cuts, run)
    time = getLivetime(runtree, run)
    return float(nevt) / float(time)


def getRateErr(tree, runtree, cuts, run):
    nevt = nEvents(tree, cuts, run)
    time = getLivetime(runtree, run)
    if (nevt!=0 and time!=0):
        return sqrt(1/float(nevt*nevt) + float(errTime*errTime)/float(time*time)) * (float(nevt) / float(time))
    else:
        return 0.
    

def printInfo(tree, runtree, cutobj):

    print "Total events  : ", nEvents(tree, "", 0)
    print "Live time     : ", getLivetime(runtree, 0)
    print "HLT rate      : ", getRate(tree, runtree, "", 0), " +/- ", getRateErr(tree, runtree, "", 0)
    print "jet+mu rate   : ", getRate(tree, runtree, cutobj.jetMu, 0), " +/- ", getRateErr(tree, runtree, cutobj.jetMu, 0)
    print "all cuts rate : ", getRate(tree, runtree, cutobj.allCuts(), 0), " +/- ", getRateErr(tree, runtree, cutobj.allCuts(), 0)
    print
    for run in getRuns(runtree):
        print "Run "+str(run)
        print "Total events  : ", nEvents(tree, "", run)
        print "Live time     : ", getLivetime(runtree, run)
        print "HLT rate      : ", getRate(tree, runtree, "", run), " +/- ", getRateErr(tree, runtree, "", run)
        print "jet+mu rate   : ", getRate(tree, runtree, cutobj.jetMu, run), " +/- ", getRateErr(tree, runtree, cutobj.jetMu, run)
        print "all cuts rate : ", getRate(tree, runtree, cutobj.allCuts(), run), " +/- ", getRateErr(tree, runtree, cutobj.allCuts(), run)
        print


    
