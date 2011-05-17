#!/usr/bin/env python

'''
This programs reads the runAll.sh script produced by makeToyJobs, and
runs each "source" line of the script as a parallel thread.
Used by runAnalysis.py to speed up output processing.
'''

import os, sys, string
import threading
import time

# Custom sort based on first number in each line of summary.txt file
def sortsummary(a,b):
    x=string.atof(string.split(a)[0])
    y=string.atof(string.split(b)[0])
    if (x>y):
        return 1
    elif x<y:
        return -1
    else:
        return 0


# Threading module runs each "source" from runAll.sh in parallel
class MyThread(threading.Thread):

    def __init__(self,mystring,sleeptime=2):
        threading.Thread.__init__(self)

        # self.mystring is the command that is run in each thread
        self.mystring=mystring
        self.sleeptime=sleeptime
        self.dir=None  # identify directory where each job output goes

        if len(string.split(mystring))>1:
            self.dir=string.split(mystring)[1]
            self.dir=string.strip(self.dir)
            self.dir=os.path.dirname(self.dir)


    def run(self):
        # Wait a few seconds between submissions
        time.sleep(self.sleeptime)
        print self.mystring
        # Start job
        os.system(self.mystring)
        return


def Main(startingdir=os.getcwd(),
         workingdir=os.getcwd(),
         myfile="runAll.sh"):
    if not os.path.isdir(workingdir):
        print "runAll.py ERROR:  working directory '%s' does not exist"%workingdir
        return False
    os.chdir(workingdir)
    
    # Remove old versions of summary.txt
    if os.path.exists("summary.txt"):
        x=raw_input("'summary.txt' already exists!  Remove it (Y/N)? ")
        if x.upper().startswith("Y"):
            os.system("rm -f summary.txt")
    starttime=time.time()
    # Read from runAll.sh
    myfile="runAll.sh"

    print "file = ",myfile, " exists ? = ",os.path.isfile(myfile)
    if not os.path.isfile(myfile):
        print "Sorry, file '%s' does not exist!"%myfile
        return False
        
    myThreads=[]
    myfile=open(myfile,'r').readlines()
    count=0
    for i in myfile:
        if not i.startswith("source"):  # only process lines starting with 'source'
            continue
        myThreads.append(MyThread(i))
        myThreads[-1].start()  # begin thread
        count+=1
        
    # Now wait for all threads to finish
    alive=0
    while 1:
        alive=0
        mysize=len(myThreads)
        for i in myThreads:
            if i.isAlive():
                alive+=1
        print "%i of %i total jobs are still running "%(alive,mysize)
        sys.stdout.flush()
        time.sleep(30) # Check every 30 seconds to see how many jobs still processing 
        if (alive==0):
            break

    print "ALIVE = ",alive
    outputdir=os.getcwd()
    if len(myThreads)>0:
        outputdir=string.split(myThreads[0].dir,"/job")[0]

    # Error -- summary.txt not produced
    mysummary=os.path.join(outputdir,"summary.txt")
    if not os.path.isfile(mysummary):
        print "Something's wrong!  Unabled to find summary.txt file!"
        return False

    myfile=open(mysummary,'r').readlines()
    myfile.sort(sortsummary)
    out=open(mysummary,'w')
    for i in myfile:
        out.write(i)
    out.close()
                 
    # Now make root output
    outputroot=os.path.join(outputdir,"results.root")  # default output file
    finalcommand = "hadd -f %s "%outputroot  # hadd command + output name

    # Loop over all threads to get input root files
    hcount=0
    for i in myThreads:
        name=os.path.join(i.dir,"outfile.root")
        # Only consider jobs where root file exists and is newer than start time
        if os.path.exists(name) and os.path.getmtime(name)>=starttime:
            finalcommand+="%s "%name
            hcount=hcount+1
    if (hcount<len(myThreads)):
        print "WARNING!  Only %i of %i jobs have recent valid root files!"%(hcount, mysize)
        return False
    
    print "Writing output to '%s'"%outputroot
    # run hadd
    if (hcount>0):
        os.system(finalcommand)

    endtime=time.time()
    print "Toy MC jobs completed"
    print "Total time taken = %i min %.2f sec"%((endtime-starttime)/60, (endtime-starttime)%60)
    os.chdir(startingdir)
    return True

    

if __name__=="__main__":

    startingdir=os.getcwd()
    workingdir=os.getcwd()
    myfile="runAll.sh"
    if len(sys.argv)>1 and os.path.isfile(sys.argv[1]):
        myfile=sys.argv[1]
    x=Main(startingdir,workingdir,myfile)
    if x==True:
        print "Successfully completed 'runAll.py'"
