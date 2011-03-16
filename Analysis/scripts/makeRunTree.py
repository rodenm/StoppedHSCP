#!/usr/bin/python

# get RunInfo data for a given range of runs
#
# calculate length of run from RunInfo start/stop/pause/resume times
# output to ROOT tree or text dump

import sys
import getopt
import cx_Oracle
import datetime
from array import array

from ROOT import *    

def usage():
    print "Usage: getRunInfo [-rt] firstRun lastRun"

# program options
doRoot=False
doText=False

# arguments
try:
    opts, args = getopt.getopt(sys.argv[1:], "rth")
except getopt.GetoptError:
    usage()
    sys.exit(2)

for opt, arg in opts:
    if opt=='-h':
        usage()
        exit.sys()
    if opt=='-r':
        doRoot=True
    if opt=='-t':
        doText=True

firstrun = int(args[0])
lastrun = int(args[1])+1

# connect to DB
db = cx_Oracle.connect('cms_trg_r/X3lmdvu4@CMS_OMDS_LB')

if (doRoot):
    
    # open output file
    rfile = TFile("RunTree.root","recreate")
    
    # create TTree
    tree = TTree("runTree/StoppedHSCPRunTree", "Run TTree")

    # nasty arrays to store data so that the TTree can access them
    nmax = 25
    run = array( 'i', [0] )
    livetime = array( 'i', [0] )
    times = array( 'f', nmax*[0] )
    labels = array( 'i', nmax*[0] )

    # run variables & branch
    tree.Branch("run", run, "run/I")
    tree.Branch("livetime", livetime, "length/I")
    tree.Branch("times", times, "times[25]/F")
    tree.Branch("labels", labels, "labels[25]/I")

# loop over runs
for i in range(firstrun, lastrun):

    # get data from DB
    cursor = db.cursor()
    cursor.execute("select * from cms_runinfo.runsession_parameter where cms_runinfo.runsession_parameter.runnumber="+str(i)+" and cms_runinfo.runsession_parameter.name='CMS.LVL0:TRG_STATE'")
    list = cursor.fetchall()

    # tuple of timestamps
    tstamps = []

    # loop over entries for this run
    for item in list:
        if (item[4]=='Starting' or
            item[4]=='Stopping' or
            item[4]=='Resuming' or
            item[4]=='Pausing'):
            time = datetime.datetime(item[5].year, item[5].month,
                                     item[5].day, item[5].hour, item[5].minute, item[5].second,
                                     item[5].fsecond)
            tstamps.append((time, item[4]))

    # sort timestamps (is this necessary?)
    tstamps.sort()

    # loop over timestamps and sum running time
    length = 0
    for j in range(0,len(tstamps)):
        if (tstamps[j][1]=='Pausing'):
            if (not ((tstamps[j-1][1] == 'Starting') or (tstamps[j-1][1] == 'Resuming'))):
                print "Found a pause not preceded by start/resume"
                print tstamps[j][1], tstamps[j-1][1]
                sys.exit(1)
            delta=tstamps[j][0]-tstamps[j-1][0]
            length+=delta.seconds
        if (tstamps[j][1]=='Stopping' and tstamps[j-1][1]=='Resuming'):
            delta=tstamps[j][0]-tstamps[j-1][0]
            length+=delta.seconds


#    naivelength=0
#    if (len(tstamps)>1):
#        naivedelta=tstamps[len(tstamps)-1][0]-tstamps[0][0]
#        naivelength=naivedelta.seconds



    if (doText and (length>0)):
        print run, length
        
    if (doRoot and (length>0)):
        # set variables
        run[0] = i
        livetime[0] = length
        for k in range(0,len(tstamps)):
            delta=tstamps[k][0]-tstamps[0][0]
            times[k]=delta.seconds
            labels[k]={
                'Starting' : 0,
                'Pausing'  : 1,
                'Resuming' : 2,
                'Stopping' : 3}[tstamps[k][1]]
        tree.Fill()


if (doRoot):
    rfile.Write()
    rfile.Close()
