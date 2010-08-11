#!/usr/bin/env python

# copy all files from a GRID directory to local disk

import getopt
import sys
import os
from subprocess import *


def usage():
    print "copyFiles.py [-c] <dataset>"
    sys.exit()

try:
    opts, args = getopt.getopt(sys.argv[1:], "c")
except getopt.GetoptError:
    usage()
    sys.exit(2)

useCAF=False
for opt, arg in opts:
    if opt=='-c':
        useCAF=True


dataset=args[0]

gridroot  = "srm://heplnx204.pp.rl.ac.uk:8443/srm/managerv2?SFN="
gridloc   = "/pnfs/pp.rl.ac.uk/data/cms/store/user/jbrooke/"+dataset
if (useCAF):
    gridroot  = "srm://srm-cms.cern.ch:8443/srm/managerv2?SFN="
    gridloc   = "/castor/cern.ch/cms/store/caf/user/jbrooke/"+dataset
odir      = "/storage/phjjb/stoppedHSCP/"+dataset

print "Copying files from :"
print gridroot
print gridloc

# get file list
ls = Popen("lcg-ls "+gridroot+gridloc, shell=True, stdout=PIPE)
lsop=ls.communicate()

files=lsop[0]

# make output dir
if not os.path.exists(odir):
    os.makedirs(odir)

# copy files
for file in files.splitlines():
    basename=os.path.basename(file)
    command = "lcg-cp "+gridroot+"/"+file+" "+odir+"/"+basename
    print command
    cp = Popen(command, shell=True)
    cp.wait()





