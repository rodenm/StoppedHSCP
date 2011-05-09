#!/bin/env python

# generate simulation scripts for multiple lifetimes

import re
import os
import stat
import sys
import getopt

# command line arguments
def usage():
    print "makeToyJobs.py [-h] <dataset> <parameter file>"

try:
    opts, args = getopt.getopt(sys.argv[1:], "h")
except getopt.GetoptError:
    usage()
    sys.exit(2)

for opt, arg in opts:
    if opt=='-h':
        usage()
        sys.exit()

if len(args)<1:
    usage()
    sys.exit()
    
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
file = open(ddir+'/lifetimes.txt')
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
    script.write('simulate params'+str(count)+'.txt >& job.log\n')
    script.write('cd '+os.environ['PWD']+'\n')
    script.close()

    # write master script
    master.write('source '+jobdir+'/job'+str(count)+'.sh\n')

    outfiles+=' '+jobdir+'/outfile.root'
    
    count+=1

# combine output of all jobs
master.write('hadd -f '+odir+'/results.root '+outfiles+'\n')

os.chmod(odir+'/runAll.sh', 0755)

master.close()

