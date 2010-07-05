import re
import os

# generate input files for many simulation jobs

# read lifetimes from lifetime file
lifetimes = []
file = open('data/lifetimes.txt', 'r')
for line in file:
    lifetimes.append(float(line))


p = re.compile(r'(lifetime\s*)(\S*)')

counter = 1
for lifetime in lifetimes:
    f = open('data/parameters.txt')
    w = open('input_params_tmp.txt', 'w')
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
