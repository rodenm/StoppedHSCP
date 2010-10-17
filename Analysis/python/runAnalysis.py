#!/usr/bin/env python

import os
import sys
import shutil
import getopt
import tarfile

from subprocess import *

# run all steps of the analysis

try:
    opts, args = getopt.getopt(sys.argv[1:], "m")
except getopt.GetoptError:
    sys.exit(2)

if len(args) < 1 :
    print "Specify dataset and fills to analyse"
    sys.exit(1)

mc=False
for opt,arg in opts:
    if opt=='-m':
        mc=True

dataset = args[0]
fillstr = ''
json    = ''
if not mc:
    fillstr = args[1]
    json    = args[2]

# convert fill list to runs list
runs=''
if mc:
    runs='0'
else :
    filllist=fillstr.split(',')
    ffile = open("StoppedHSCP/Analysis/data/fills.txt")
    ffile.next()
    for line in ffile:
        tokens=line.split()
        if (len(tokens)>2):
            if (filllist.count(tokens[0])>0):
                rstrs=tokens[2].split(',')
                for r in rstrs:
                    runs+=r+","

print "Stopped Gluino Analysis"
if mc :
    print "Going to run for MC"
else:
    print "Going to run on :"
    print "Fills :", fillstr
    print "Runs  :", runs
    print

# create directory if it doesn't exist
if os.path.exists(dataset):
    print
    shutil.rmtree(dataset)
    os.makedirs(dataset)
else:
    os.makedirs(dataset)
    
# create summary files
if not mc:
    fillfile = open(dataset+"/fills.txt", "w")
    fillfile.write(fillstr)
    fillfile.close()

    runfile = open(dataset+"/runs.txt", "w")
    runfile.write(runs)
    runfile.close()
    
    cp = Popen("cp "+json+" "+dataset+"/json.txt", shell=True)
    cp.wait()

# MC flag
mcFlag=''
if mc:
    mcFlag='-m'

# make histograms
print
print "makeHistograms "+mcFlag+" ntuples/stoppedHSCP_tree_"+dataset+".root "+dataset+" "+runs+" > "+dataset+"/log.txt"
p1 = Popen("makeHistograms "+mcFlag+" ntuples/stoppedHSCP_tree_"+dataset+".root "+dataset+" "+runs+" > "+dataset+"/histogrammer.log", shell=True)
p1.wait()

# make summary histograms for data
if not mc:
    print
    print "python $CMSSW_BASE/src/StoppedHSCP/Analysis/python/summaryHistos.py "+dataset+" "+fillstr+" "+json+" >> "+dataset+"/log.txt"
    p3 = Popen("python $CMSSW_BASE/src/StoppedHSCP/Analysis/python/summaryHistos.py "+dataset+" "+fillstr+" "+json+" >> "+dataset+"/log.txt", shell=True)
    p3.wait()

# make plots
print
print "python $CMSSW_BASE/src/StoppedHSCP/Analysis/python/makePlots.py "+dataset+" >> "+dataset+"/log.txt"
p2 = Popen("python $CMSSW_BASE/src/StoppedHSCP/Analysis/python/makePlots.py "+dataset+" >> "+dataset+"/log.txt", shell=True)
p2.wait()

# print summary
print
print "python $CMSSW_BASE/src/StoppedHSCP/Analysis/python/printSummary.py "+mcFlag+" "+dataset+" > "+dataset+"/summary.txt"
p4 = Popen("python $CMSSW_BASE/src/StoppedHSCP/Analysis/python/printSummary.py "+mcFlag+" "+dataset+" > "+dataset+"/summary.txt", shell=True)
p4.wait()

# make Toy MC jobs
print
print "makeToyJobs.py "+dataset
if not mc:
    p5 = Popen("makeToyJobs.py "+dataset, shell=True)
    p5.wait()

# run Toy MC
print
print "source "+dataset+"/toymc/runAll.sh"
p6 = Popen("source "+dataset+"/toymc/runAll.sh", shell=True)
p6.wait()


# list files
print
ls = Popen("ls -l "+dataset, shell=True)
ls.wait()

# make tarball
print
print "tar -zcvf "+dataset+".tgz "+dataset+"/" 
tar = tarfile.open(name = dataset+".tgz", mode = 'w:gz')
tar.add(dataset)
tar.close()


