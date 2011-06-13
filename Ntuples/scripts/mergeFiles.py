#!/usr/bin/env python

# copy all files from a GRID directory to local disk

import getopt
import sys
import os
import shutil
from subprocess import *


def usage():
    print "mergeFiles.py <dataset>"
    sys.exit()

try:
    opts, args = getopt.getopt(sys.argv[1:], "")
except getopt.GetoptError:
    usage()
    sys.exit(2)

dataset  = args[0]
dir      = "/storage/phjjb/stoppedHSCP/"+dataset
ofile    = dataset+".root"
odir     = "/users/phjjb/stoppedHSCP/ntuples"

print "Merging files in "+dir

# remove old file if it exists
if os.path.isfile(dir+"/"+ofile):
    os.remove(dir+"/"+ofile)


# get file list
ls = Popen("ls "+dir, shell=True, stdout=PIPE)
lsop=ls.communicate()

files=lsop[0].split()

# merge them
command="hadd -f "+dir+"/"+ofile+" "

for file in files:
    command = command+dir+"/"+file+" "

print command

hadd = Popen(command, shell=True)
hadd.wait()

    
# copy output file
shutil.copy(dir+"/"+ofile, odir)
