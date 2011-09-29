#!/usr/bin/env python
#
# quick-and-dirty script to extract and cross check LUMI distribution over different
# filling schemes basing on given JSON file
# Author: fedor.ratnikov@cern.ch - May 19, 2011
#

import sys, os, tempfile
from subprocess import Popen, PIPE
import json

def getLumi (jsonDict):
    jsonFile = tempfile.mktemp();
    lumiout = open(jsonFile, 'w')
    json.dump(jsonDict, lumiout, sort_keys=True)
    lumiout.close()

    command = 'lumiCalc.py -c frontier://LumiCalc/CMS_LUMI_PROD -i ' + jsonFile + ' --nowarning overview'
#    print 'Executing:', command, '...'
    foundTotal = 0
    for line in Popen(command, shell=True, stdout=PIPE, close_fds=True).stdout.readlines():
        if foundTotal > 0: foundTotal += 1
        if foundTotal == 4:
            lumi = line.split('|')[4]
            return float (lumi)*1.e-6
        if line.find ('Total') >= 0 : foundTotal = 1
    return 0

def main():

    if len(sys.argv) < 2:
        print 'split lumi over different filling schemes'
        print 'usage', sys.argv[0], 'jsonFile'
        sys.exit(-1)
        
        # get run->fill mapping
    allFills = {}
    cmssw = os.getenv ('CMSSW_BASE')
    if not cmssw:
        print 'CMSSW is not set'
        sys.exit (0)
    # unconditionally skip first line
    fillLines = (file (cmssw+'/src/StoppedHSCP/Ntuples/data/fills.txt')).readlines ()[1:] 
    for line in fillLines:
        if line[0] == '#': continue
        try:
            (fillNo, fillName, fillRuns) = str.split (line)
            runs = str.split (fillRuns, ',')
        except:
            print "Exception in processing line", line, " Skip line"
            continue
        if fillName not in allFills.keys(): allFills[fillName] = []
        allFills[fillName].extend (runs)

    allJsons = {}
    compactList = json.load (open (sys.argv[1]))
    for fill in allFills.keys():
        fillRuns = allFills[fill]
        for run in compactList.keys():
            if run in fillRuns:
                if fill not in allJsons.keys(): allJsons[fill] = {}
                if run not in allJsons[fill].keys(): allJsons[fill][run] = []
                allJsons[fill][run].extend (compactList[run])

    allLumi = 0
    for fill in sorted(allJsons.keys()):
        thisLumi = getLumi (allJsons[fill])
        allLumi += thisLumi
        print fill, thisLumi, '/pb'

    originalLumi = getLumi (compactList)

    print 'cross check... Original:', originalLumi, 'comulative: ', allLumi, 'Difference:', (originalLumi-allLumi)/(originalLumi+allLumi)*50, '%'
                

if __name__ == '__main__':
    main()
