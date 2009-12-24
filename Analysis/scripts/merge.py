#! /usr/bin/env python

# merge root files on castor

import sys
import subprocess

dir=sys.argv[1]
basename=sys.argv[2]
nfiles=int(sys.argv[3])
firstfile=int(sys.argv[4])

if len(sys.argv)!=5 :
    print "Usage : python merge.py <dir> <base filename> <n files to merge> <n of first file>"
    exit(1)

print "Merging files from "+dir
print "to "+dir+"/"+basename+".root"

command = "hadd "+basename+".root "

for i in range(firstfile, firstfile+nfiles):
    command += dir+"/"+basename+"_"+str(i)+".root "

# call hadd
print command
hadd=subprocess.Popen(command,
                      shell=True
                      )

print hadd.communicate()[0]
