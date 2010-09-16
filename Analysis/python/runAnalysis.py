#!/usr/bin/env python

import os
import sys
import shutil
import getopt
import tarfile

from subprocess import *

# run all steps of the analysis

try:
    opts, args = getopt.getopt(sys.argv[1:], "")
except getopt.GetoptError:
    sys.exit(2)

if len(args) < 1 :
    print "Specify dataset and fills to analyse"
    sys.exit(1)

dataset = args[0]
fillstr = args[1]
json    = args[2]

# convert fill list to runs list
filllist=fillstr.split(',')
runs=''
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
print "Going to run on :"
print "Fills :", fillstr
print "Runs  :", runs
print

if os.path.exists(dataset):
    print
#    shutil.rmtree(dataset)
#    os.makedirs(dataset)

else:
    os.makedirs(dataset)

# create summary files
fillfile = open(dataset+"/fills.txt", "w")
fillfile.write(fillstr)
fillfile.close()

runfile = open(dataset+"/runs.txt", "w")
runfile.write(runs)
runfile.close()

cp = Popen("cp "+json+" "+dataset+"/json.txt", shell=True)
cp.wait()


# create directory if it doesn't exist
if not os.path.exists(dataset):
    os.makedirs(dataset)

# make histograms
print
print "makeHistograms ntuples/stoppedHSCP_tree_"+dataset+".root "+dataset+" "+runs+" > "+dataset+"/histogrammer.log"
p1 = Popen("makeHistograms ntuples/stoppedHSCP_tree_"+dataset+".root "+dataset+" "+runs+" > "+dataset+"/histogrammer.log", shell=True)
p1.wait()

# make summary histograms
print
print "python $CMSSW_BASE/src/StoppedHSCP/Analysis/python/summaryHistos.py "+dataset+" "+fillstr+" "+json
p3 = Popen("python $CMSSW_BASE/src/StoppedHSCP/Analysis/python/summaryHistos.py "+dataset+" "+fillstr+" "+json, shell=True)
p3.wait()

# make plots
print
print "python $CMSSW_BASE/src/StoppedHSCP/Analysis/python/makePlots.py "+dataset
p2 = Popen("python $CMSSW_BASE/src/StoppedHSCP/Analysis/python/makePlots.py "+dataset, shell=True)
p2.wait()

# print summary
print
print "python $CMSSW_BASE/src/StoppedHSCP/Analysis/python/printSummary.py "+dataset+" > "+dataset+"/summary.txt"
p4 = Popen("python $CMSSW_BASE/src/StoppedHSCP/Analysis/python/printSummary.py "+dataset+" > "+dataset+"/summary.txt", shell=True)
p4.wait()

# make Toy MC jobs
p5 = Popen("makeToyJobs.py "+dataset, shell=True)
p5.wait()

ls = Popen("ls -l "+dataset, shell=True)
ls.wait()
print

tar = tarfile.open(name = dataset+".tgz", mode = 'w:gz')
tar.add(dataset)
tar.close()


