#!/usr/bin/env python

import sys
import json

if len(sys.argv) < 2:
    print 'Dump json file in 3 column format'
    print 'usage', argv[0], 'jsonFile [outputFile]'
    sys.exit(-1)
    
jsonFile = open (sys.argv[1])
if (len(sys.argv) >= 3):
    outFile = open (sys.argv[2], 'w')
else:
    outFile = sys.stdout

compactList = json.load (jsonFile)
for run in sorted(compactList.keys()):
    for range in compactList[run]:
        outFile.write ('%s %s %s\n' % (run, range[0], range[1]))
