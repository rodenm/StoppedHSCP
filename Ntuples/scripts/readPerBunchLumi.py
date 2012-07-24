#! /usr/bin/env python
#
# Marissa Rodenburg July 2012
#
# This is a crude first pass at a script to mine the filling scheme data from the
# output of the central lumiContext.py script.
#
# Unfortunately, it appears that this won't give us the full and complete filling schemes.
# For example, for the scheme 50ns_1374_1368_0_1262_144bpi12inj, some of the uncollided
# bunches at the front of the first beam2 train are always missing (particularly
# bunches 15 and 19) and I cannot figure out why. These values are also uncorrected HF
# values so they aren't perfectly accurate, but the error is supposedly on ~5%.
#
# The input file for this is created by running:
#   lumiContext.py --with-beamintensity beambyls -o stdout -r 199021 > & lumidata.txt
# using a run from the desired fill. The output file of that command (lumidata.txt)
# is the input file for this script.
#
# To run this script:
#   python readPerBunchLumi.py lumidata.txt
#
# There are a few variables below that modify the output and which lumisections are
# examined to get the fill scheme. These should be commandline arguments, but I
# just haven't implemented that yet.

import sys

from ROOT import *
from array import *

# TODO: Make minIntensity and lumisection commandline arguments!
minintensity = 10000000000
lb = 10
nColliding = 112
requireStableBeams = true
skipToChosenLumi = true


gSystem.Load("libStoppedHSCPNtuples")

infileName = sys.argv[1]
infile = open(infileName, 'r')

beam1bunches = ''
beam2bunches = ''
nBeam1 = 0
nBeam2 = 0
nBoth  = 0
for line in infile:
    bunches = ''
    beam1bunches = ''
    beam2bunches = ''
    nBeam1 = 0
    nBeam2 = 0
    nBoth  = 0

    nBunches = 0
    if line.find('[') != 0: continue

    words = line.split('\'')
    beamstate = words[len(words)-8]
    if requireStableBeams and beamstate != 'STABLE BEAMS': continue
    
    lumi = words[len(words)-10]
    if skipToChosenLumi and lumi < str(lb)+':'+str(lb): continue

    print beamstate
    print lumi
    
    intensities = words[len(words)-2]
    intensitiesByBx = intensities.split(' ')

    for bunch in intensitiesByBx:
        temp = bunch.split(',')
        bx = temp[0]
        if bx == '0': continue # Dump. BX=1 is repeated for 0
        
        beam1 = float(temp[1])
        beam2 = float(temp[2])
        #print bx + ' ' + str(beam1) + ' ' + str(beam2)

        if beam1 > minintensity:
            beam1bunches = beam1bunches + bx + ','
            nBeam1 = nBeam1 + 1
        if beam2 > minintensity:
            beam2bunches = beam2bunches + bx + ','
            nBeam2 = nBeam2 + 1
        if beam1 > minintensity and beam2 > minintensity:
            nBoth = nBoth + 1

    print 'nBunches: ' + str(nBeam1) + ' ' + str(nBeam2) + ' ' + str(nBoth)
    if nBoth == nColliding: break

print beam1bunches
print beam2bunches

