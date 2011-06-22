#!/usr/bin/env python

# copy all files from a GRID directory to local disk

import getopt
import sys
import os
from subprocess import *

from optparse import OptionParser

import threading
import time


###  'copySites' variables is a dictionary storing some common locations of ntuples

global copySites
copySites={}
# Add labels here for any other sites.
# Add ntuple of [gridroot, gridloc]
copySites["RAL"]=["srm://heplnx204.pp.rl.ac.uk:8443/srm/managerv2?SFN=",
                  "/pnfs/pp.rl.ac.uk/data/cms/store/user/"]

copySites["PUR"]=["srm://srm-dcache.rcac.purdue.edu:8443/srm/managerv2?SFN=",
                  "/store/user/"]
copySites["CAF"]=["srm://srm-cms.cern.ch:8443/srm/managerv2?SFN=",
                  "/castor/cern.ch/cms/store/caf/user/"]


class CopyFileThread(threading.Thread):
    ''' Class that will run each copy command independently, rather than sequentially.'''
    
    def __init__(self,command,sleeptime=60):
        threading.Thread.__init__(self)
        self.command=command
        self.sleeptime=sleeptime
        
    def run(self):
        time.sleep(2)  # small break between jobs
        print self.command
        cp = Popen(self.command, shell=True)  # execute command
        # wait to see if copying is complete
        completed=False
        totaltime=0

        # This doesn't seem to work -- sometimes the "poll" command
        # never returns True, even when the file is copied.
        
        #while (completed==False):
        #    completed=cp.poll()
        #    # Check every (sleeptime) seconds to see if file has finished copying
        #    if (totaltime>300):  # print messages after 5 minutes
        #        print "Checking on '%s':  Completed? %s"%(self.command,completed)
        #    time.sleep(self.sleeptime)
        #    totaltime=totaltime+self.sleeptime
        cp.wait()  # is this necessary?
        print "Completed '%s'"%self.command
        return

def CopyFiles(user="jbrooke",
              gridroot="srm://heplnx204.pp.rl.ac.uk:8443/srm/managerv2?SFN=",
              gridloc="/pnfs/pp.rl.ac.uk/data/cms/store/user",
              dataset="",
              odir="/storage/phjjb/stoppedHSCP/",
              verbose=False,
              overwrite=False,
              listfiles=False,
              srmcp=False):

    starttime=time.time()
    # Specify grid location using base gridloc, user and dataset
    # Specify output directory from base and dataset
    gridloc=os.path.join(gridloc,user,dataset)
    odir=os.path.join(odir,dataset)
    if (listfiles==False):
        if not os.path.exists(odir):  # Create output dir if it doesn't exist; not necessary for listfiles option
            os.makedirs(odir)

    if (listfiles==True):
        print "Listing files from :"
    else:
        print "Copying files from :"
    print gridroot+gridloc

    # get file list
    if (srmcp==False):
        ls = Popen("lcg-ls "+gridroot+gridloc, shell=True, stdout=PIPE)
    else:
        ls = Popen("srmls "+gridroot+gridloc,
                   shell=True,
                   stdout=PIPE)
    lsop=ls.communicate()
    files=lsop[0]

    filenames={}
    allfiles=files.splitlines()
    filecount=len(allfiles)
    print "A total of %i files found:"%filecount
    print files
    # Only list files, don't copy them
    if listfiles==True:
        for file in allfiles:
            basename=os.path.basename(file)
            if basename.endswith("stoppedHSCP"):
                dictname=string.split(basename,"_")
                if len(dictname)>2:
                    key="%s_%s_%s"%(dictname[0],dictname[1],dictname[2])
                else:
                    key=dictname
                if key not in filenames:
                    filenames[key]=[]
                filenames[key].append(basename)

        endtime=time.time()
        print "A total of %i files found."%filecount
        print "Total time taken: %i min %.2f sec"%((endtime-starttime)/60, (endtime-starttime)%60)
        for x in filenames.keys():
            if len(filenames[x])>1:
                print "*************************************************"
                print "MAJOR ERROR!  Multiple files with same base name!"
                for i in filenames[x]:
                    print "\t\t",i
        
        return True

    print "A total of %i files will be copied."%filecount
    endtime=time.time()
    print "(Job time so far: %i min %.2f sec)"%((endtime-starttime)/60, (endtime-starttime)%60)
    # copy files
    counter=1

    cmdThreads=[]

    for file in allfiles:
        #if (counter>1):           continue
        basename=os.path.basename(file)
        if basename.endswith("stoppedHSCP"):
            dictname=string.split(basename,"_")
            if len(dictname)>2:
                key="%s_%s_%s"%(dictname[0],dictname[1],dictname[2])
            else:
                key=dictname
            if key not in filenames:
                filenames[key]=[]
            filenames[key].append(basename)
            
        #command = "lcg-cp "+gridroot+"/"+file+" "+os.path.join(odir,basename)
        if (srmcp==False):
            command = "lcg-cp %s/%s %s"%(gridroot,file,os.path.join(odir,basename))
        else:
            if not file.endswith(".root"):  # only copy root files?
                continue
            temp=string.split(file)
            temp=string.strip(temp[-1])
            command = "srmcp -2 \"%s/%s\" %s%s"%(gridroot,temp,"file:///",os.path.join(odir,basename))
        
        print "\n%s\n"%command
        print "Copying %s -- file %i of %i"%(os.path.join(odir,basename),counter,filecount)
        counter=counter+1

        # Protection against overwriting existing files -- ask if conflicting files should be overwritten
        if overwrite==False:
            if os.path.exists(os.path.join(odir,basename)):  
                if __name__<>"__main__":   # run from a separate program -- don't overwrite
                    continue
                else:  # run in stand-alone mode; ask user for input
                    print "WARNING!  File '%s' already exists!"%os.path.join(odir,basename)
                    cont=raw_input("Overwrite (y/n)? :  ")
                    if not (cont.upper()).startswith("Y"):
                        continue
                    print "Overwriting '%s'..."%basename

        cmdThreads.append(CopyFileThread(command))
        cmdThreads[-1].start()

        #cp = Popen(command, shell=True)
        #cp.wait()

    # Wait for all jobs to complete
    alive=99
    while alive>0:
        endtime=time.time()
        alive=0
        mysize=len(cmdThreads)
        for i in cmdThreads:
            if i.isAlive():
                alive=alive+1
                if (endtime-starttime)>300:
                    print "alive:  ",i.command
        print "%i of %i total files are still being copied "%(alive,mysize)
        sys.stdout.flush()
        if (alive==0):
            break
        time.sleep(60)
        
    endtime=time.time()
    print "Total time taken: %i min %.2f sec"%((endtime-starttime)/60, (endtime-starttime)%60)
    for x in filenames.keys():
        if len(filenames[x])>1:
            print "*************************************************"
            print "MAJOR ERROR!  Multiple files with same base name!"
            for i in filenames[x]:
                print "\t\t",i
    return True


def PrintHelp(parser):
    parser.print_help()
    print
    return

if __name__=="__main__":



    parser = OptionParser()
    parser.add_option("-v","--verbose",
                      action="store_true",
                      default=False,
                      dest="verbose",
                      help="turn on verbose debugging")
    parser.add_option("-c","--useCAF",
                      action="store_true",
                      default=False,
                      dest="useCAF",
                      help="run on CAF")
    parser.add_option("-d","--datasets",
                      action="append",
                      default=[],
                      dest="datasets",
                      help="Specify dataset to access (used in defining input directory")
    parser.add_option("-u","--user",
                      dest="user",
                      default="jbrooke",
                      help="Specify user name for input directory")
    parser.add_option("-i","--inputdir",
                      dest="gridloc",
                      default=None,
                      help="Specify input directory (without user/dataset suffixes)")
    parser.add_option("-o","--outputdir",
                      dest="outputdir",
                      default=None,
                      help="Specify output directory")
    parser.add_option("-g","--gridroot",
                      default=None,
                      dest="gridroot",
                      help="Specify grid location")
    parser.add_option("-w","--overwrite",
                      default=False,
                      dest="overwrite",
                      action="store_true",
                      help="Automatically overwrite existing files in the local directory with newly-copied versions")
    parser.add_option("-H","--Help",
                      dest="help",
                      default=False,
                      action="store_true",
                      help="Alternate method of accessing this help message")
    parser.add_option("-l","--listfiles",
                      dest="listfiles",
                      default=False,
                      action="store_true",
                      help="Only list the files in the initial location, rather than copying them")
    parser.add_option("-s","--site",
                      dest="site",
                      default=None,
                      help="Specify site where files located.  Options are: %s "%copySites.keys())
    parser.add_option("-p","--srmcp",
                      dest="srmcp",
                      default=False,
                      action="store_true",
                      help="Use srmcp to copy files.  Default is false (lcg is used by default.)")
    
    (options,args)=parser.parse_args()

    if options.help==True:
        PrintHelp(parser)
        sys.exit()
    
    for i in args:  # Any unclaimed arguments are treated as datasets
        if i not in options.datasets:
            options.datasets.append(i)
        else:
            print "Warning!  Dataset '%s' has already been specified!  No need to enter it again!"%i

    if len(options.datasets)==0:
        print "WARNING!  No datasets have been specified!"
        options.datasets=[""]
        #sys.exit()
        
    if options.site<>None:
        if options.site not in copySites.keys():
            print "ERROR!  User-specified site '%s' is not recognized!"%options.site
            print "Allowed sites are: %s"%copySites.keys()
            print "Proceeding with default gridroot, gridloc values"
        else:
            thisloc=copySites[options.site]
            options.gridroot=thisloc[0]
            options.gridloc=thisloc[1]

    if options.gridloc==None:
        if options.useCAF==True:
            options.gridloc = "/castor/cern.ch/cms/store/caf/user/"
        else:
            options.gridloc = "/pnfs/pp.rl.ac.uk/data/cms/store/user/"

    if options.gridroot==None:
        if options.useCAF==True:
            options.gridroot  = "srm://srm-cms.cern.ch:8443/srm/managerv2?SFN="
        else:
            options.gridroot  = "srm://heplnx204.pp.rl.ac.uk:8443/srm/managerv2?SFN="

    if options.outputdir==None:
        if os.path.isdir("/storage/phjjb/stoppedHSCP/"):
            options.outputdir="/storage/phjjb/stoppedHSCP/"
        else:
            options.outputdir=os.getcwd()
        

    print "Input location:"
    print "\tgridroot = %s \n\tgridloc = %s"%(options.gridroot,options.gridloc)
    print "User = %s"%options.user
    print "Datasets = "
    for d in options.datasets:
        print "\t%s"%d
    print "\n Local Output Directory = %s"%options.outputdir

    if options.verbose:
        answer=raw_input("\nProceed with copy using the above values (y/n)? :  ")
        if not (answer.upper()).startswith("Y"):
            sys.exit()

    for d in options.datasets:
        if (options.listfiles==True):
            print "Listing files in dataset '%s'"%d
        else:
            print "Copying files in dataset '%s'"%d
        CopyFiles(user=options.user,
                  gridroot=options.gridroot,
                  gridloc=options.gridloc,
                  dataset=d,
                  odir=options.outputdir,
                  verbose=options.verbose,
                  overwrite=options.overwrite,
                  listfiles=options.listfiles,
                  srmcp=options.srmcp)
