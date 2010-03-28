
# get output from a given job and hadd it
import getopt
import sys
import os
import re
from subprocess import *
import tarfile

def usage():
    print "cafSubmit.py [-ms] <run>"
    sys.exit()

try:
    opts, args = getopt.getopt(sys.argv[1:], "hems")
except getopt.GetoptError:
    usage()
    sys.exit(2)
    
# control variables
workdir=os.environ['CAFDIR']+"/jobs"
ntupdir=os.environ['CAFDIR']+"/ntuples"

# get arugments
for opt, arg in opts:
    if opt=='-h':
        usage()
        exit.sys()
    if opt=='-e':
        label="express"
#        dataset="/ExpressPhysics/Commissioning10-Express-v4/FEVT"
    if opt=='-m':
        label="minbias"
#        dataset="/MinimumBias/Commissioning10-PromptReco-v4/RECO"
    if opt=='-s':
        label="skim"
#        dataset=""

run = args[0]
crabdir=workdir+"/"+label+"-"+run

print "Getting files from "+crabdir

# retrieve data
retrieve = Popen("crab -getoutput -c "+crabdir, shell=True)
retrieve.wait()

# untar if required
files=os.listdir(crabdir+"/res")
for file in files:
    if re.search("tgz", file):
        tarfile.open(file, "r:gz")
        tarfile.extractall(crabdir+"/res")

# hadd all the files together
hadd=Popen("hadd -f "+ntupdir+"/"+label+"-"+run+".root "+crabdir+"/res/stoppedHSCPTree_*.root", shell=True)
hadd.wait()

# add latest ntuple to collection
hadd=Popen("hadd -f "+ntupdir+"/"+label+"-"+run+".root "+crabdir+"/res/stoppedHSCPTree_*.root", shell=True)
hadd.wait()
