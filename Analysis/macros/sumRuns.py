#!/usr/bin/env python

import sys
import getopt
import string
import os
import subprocess

# help message
def usage():
    print "Usage : sumRuns.py [-h] <dataset> <runs>"    


# the main program
try:
    opts, args = getopt.getopt(sys.argv[1:], "h")
except getopt.GetoptError:
    usage();
    sys.exit(2)

if len(args) < 2 :
    print "Wrong number of arguments"
    usage();
    sys.exit(1)


# arguments
dataset=args[0]
runs=[]
if (len(args)>1):
    runlist=args[1].split(',')
    for i in range(0, len(runlist)):
        runs.append(int(runlist[i]))



# put together list of files to merge
files=""
for run in runs:
    files += dataset+"/histograms"+str(run)+".root "

print "Merging "+files

# do the merge
hadd=subprocess.Popen("hadd -f "+dataset+"/selectedRuns.root "+files, shell=True)
hadd.wait()
