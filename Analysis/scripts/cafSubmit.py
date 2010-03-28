#!/bin/env python

# script to create & submit CRAB jobs for stopped gluino analysis

import getopt
import sys
import os
from subprocess import *
from optparse import OptionParser

def usage():
    print "cafSubmit.py [-hems] <run>"
    sys.exit()

try:
    opts, args = getopt.getopt(sys.argv[1:], "hems")
except getopt.GetoptError:
    usage()
    sys.exit(2)
    
# control variables
workdir=os.environ['CAFDIR']+"/jobs"
label=""
dataset=""
run=0
job=os.environ['CAFDIR']+"/"+os.environ['CMSVER']+"/src/StoppedHSCP/Analysis/test/stoppedHSCPTree_CAF.py"

# get arugments
for opt, arg in opts:
    if opt=='-h':
        usage()
        exit.sys()
    if opt=='-e':
        label="express"
        dataset="/ExpressPhysics/Commissioning10-Express-v4/FEVT"
    if opt=='-m':
        label="minbias"
        dataset="/MinimumBias/Commissioning10-PromptReco-v4/RECO"
    if opt=='-s':
        label="skim"
        dataset=""

run = args[0]

# CRAB file
crabfile=workdir+"/crab-"+label+"-"+run+".cfg"

print "Running on "+label+", run "+run+", using "+dataset

# create file
crab="""
[CRAB]
jobtype = cmssw
scheduler = caf

[CMSSW]
datasetpath="""+dataset+"""
runselection="""+run+"""
pset="""+job+"""
total_number_of_events=-1 
events_per_job=100000
#number_of_jobs=-1
output_file = stoppedHSCPTree.root
use_parent=1
dbs_url=http://cmsdbsprod.cern.ch/cms_dbs_prod_global/servlet/DBSServlet

[USER]
return_data = 1
copy_data = 0
ui_working_dir = """+workdir+"/"+label+"-"+run+"""
thresholdLevel = 50
eMail = jim.brooke@cern.ch

[GRID]
rb = CERN
proxy_server = myproxy.cern.ch
"""

f = open(crabfile, 'w')
f.write(crab)

print "crab -create -submit -cfg "+crabfile

submit = Popen("crab -create -submit -cfg "+crabfile, shell=True)
#submit.wait()
