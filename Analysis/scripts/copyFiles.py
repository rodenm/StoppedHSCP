#! /usr/bin/env python

# copy files from grid location to local disk

import sys
import subprocess

print len(sys.argv)

if len(sys.argv)!=7 :
    print "Wrong number of arguments"
    print "Usage : python copy.py <in dir> <out dir> <base filename> <n files> <n of first file> <stupid CRAB index>"
    sys.exit(1)


idir=sys.argv[1]
odir=sys.argv[2]
basename=sys.argv[3]
nfiles=int(sys.argv[4])
firstfile=int(sys.argv[5])
crabwank=int(sys.argv[6])


print "Copying files from "+idir
print "to "+odir

for i in range(firstfile, firstfile+nfiles):
    command = "lcg-cp "+idir+"/"+basename+"_"+str(i)+"_"+str(crabwank)+".root "
    command += odir+"/"+basename+"_"+str(i)+".root"
    print command
    copy = subprocess.Popen(command,
                            shell=True)
    print copy.communicate()[0]


ls=subprocess.Popen("ls -l "+odir,
                    shell=True)
print ls.communicate()[0]


