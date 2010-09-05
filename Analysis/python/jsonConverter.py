
import sys
import json

filename=sys.argv[1]
file = open(filename, 'r')

ranges={}
for line in file:
    ranges.update(json.loads(line))

runs = ranges.keys()
runs.sort()
for run in runs:
    last=ranges[run][0]
    for range in ranges[run]:
        print run, range[0], range[1]
        if (last[0]>range[0]):
            print "Argh!"
        
