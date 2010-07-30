# generate simulation input files for multiple lifetimes
# based on 

import re
import os
import sys
import getopt

# command line arguments
def usage():
    print "makeToyJobs.py [-h] <dataset>"

try:
    opts, args = getopt.getopt(sys.argv[1:], "h")
except getopt.GetoptError:
    usage()
    sys.exit(2)

for opt, arg in opts:
    if opt=='-h':
        usage()
        sys.exit()

dataset = args[0]
odir = os.environ['PWD']+'/'+dataset+'/toymc'

# create output directory
if not os.path.exists(odir):
    os.makedirs(odir)

# read lifetimes from lifetime file
lifetimes = []
file = open(os.environ['CMSSW_BASE']+'/src/StoppedHSCP/ToyMC/data/lifetimes.txt', 'r')
for line in file:
    lifetimes.append(float(line))
file.close()

# regexps to replace lifetime in standard parameters file
p = re.compile(r'(lifetime\s*)(\S*)')

# generate file for each lifetime
counter = 1
for lifetime in lifetimes:
    f = open(os.environ['CMSSW_BASE']+'/src/StoppedHSCP/ToyMC/data/parameters.txt')
    w = open(odir+'/params'+str(counter)+'.txt', 'w')
    for line in f.readlines():
        m = p.match(line)
        if (not m):
            w.write(line)
        else:
            w.write(m.group(1))
            w.write(str(lifetime))
            w.write('\n')
#    os.system('./frontend < input_params_tmp.txt')
#    os.system('mv outfile.root outfile'+str(counter)+'.root')
    counter+=1
