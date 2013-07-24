#!/bin/env python

# generate simulation scripts for multiple lifetimes

import re
import os
import stat
import sys
import getopt

# command line arguments
def usage():
    print "makeToyJobs.py [-h] [-o] [-j n processes] <dataset>"
    print "If -o option specified, old 'simulate' command used."
    print "Otherwise, new 'simulateMulti' command is used."

try:
    opts, args = getopt.getopt(sys.argv[1:], "hjo")
except getopt.GetoptError:
    usage()
    sys.exit(2)

njobs=1
useOld=False

for opt, arg in opts:
    if opt=='-h':
        usage()
        sys.exit()
    if opt=='-j':
        njobs=arg
    if opt=="-o":
        useOld=True

if len(args)<1:
    usage()
    sys.exit(2)
    
dataset = args[0]
ddir = os.environ['PWD']+'/'+dataset
odir = ddir+'/toymc'

paramfile = ddir+'/parameters.txt'
if len(args)>1:
    paramfile = args[1]

# create output directory
if not os.path.exists(odir):
    os.makedirs(odir)

# read lifetimes from standard lifetime file
lifetimes = []
file = open(os.environ['CMSSW_BASE']+'/src/StoppedHSCP/ToyMC/data/lifetimes.txt', 'r')
for line in file:
    lifetimes.append(float(line))
file.close()

try:
    file = open(ddir+'/lifetimes.txt')
except IOError:
    file = open(ddir+"searchLifetimes.txt")
else:
    file = open(ddir+"searchLifetimes.txt")
    
for line in file:
    if (float(line)>7.5e-8):
        lifetimes.append(float(line))
file.close()

lifetimes.sort()


# regexps to replace lines in standard parameters file
line1 = re.compile(r'(lifetime\s*)(\S*)')

# write master script
master = open(odir+'/runAll.sh', 'w')

# generate file for each job
count = 1
outfiles=''
for lifetime in lifetimes:

    # open std parameters file
    f = open(paramfile)

    # create output dir
    jobdir=odir+'/job'+str(count)
    if not os.path.exists(jobdir):
        os.makedirs(jobdir)

    # write params file
    w = open(jobdir+'/params'+str(count)+'.txt', 'w')
    for line in f.readlines():
        m = line1.match(line)
        if (not m):
            w.write(line)
        else:
            w.write(m.group(1))
            w.write(str(lifetime))
            w.write('\n')
    w.close()

    # write job script
    script = open(jobdir+'/job'+str(count)+'.sh', 'w')
    script.write('cd '+jobdir+'\n')
    # Use simulateMulti by default; simulate if old style specified
    basecommand="simulateMulti"
    if useOld==True:
        basecommand="simulate"
    script.write('%s params'%basecommand+str(count)+'.txt >& job.log\n')
    script.write('cd '+os.environ['PWD']+'\n')
    script.close()

    # write master script
    master.write('source '+jobdir+'/job'+str(count)+'.sh\n')

    outfiles+=' '+jobdir+'/outfile.root'
    
    count+=1

# combine output of all jobs
master.write('hadd -f '+odir+'/results.root '+outfiles+'\n')

master.write('if [ -e '+ddir+'/toymc.txt ]; then')
master.write('    rm '+ddir+'/toymc.txt')
master.write('fi')

count=1
for lifetime in lifetimes:
    master.write('cat '+odir+'/job'+str(count)+'/summary.txt >> '+ddir+'/toymc.txt\n')
    count = count+1


os.chmod(odir+'/runAll.sh', 0755)

master.close()

