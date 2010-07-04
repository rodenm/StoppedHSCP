import re
import os

lifetimes = (
    5e-8,
    1e-7,
    2e-7,
    1.e-6,
    1e-5,
    1.e-3,
    1,
    5e2,
    2e3,
    3600.,
    6e3,
    1e4,
    2e4,
    3e4,
    5e4,
    1e5,
    3e5,
    1e6,
    1e7
    )

p = re.compile(r'(lifetime\s*)(\S*)')

counter = 1
for lifetime in lifetimes:
    f = open('input_params.txt')
    w = open('input_params_tmp.txt', 'w')
    for line in f.readlines():
        m = p.match(line)
        if (not m):
            w.write(line)
        else:
            w.write(m.group(1))
            w.write(str(lifetime))
            w.write('\n')
    os.system('./frontend < input_params_tmp.txt')
    os.system('mv outfile.root outfile'+str(counter)+'.root')
    counter+=1
