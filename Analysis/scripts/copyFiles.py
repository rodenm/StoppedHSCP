#!/usr/bin/env python

# copy all files from a GRID directory to local disk

import getopt
import sys
import os
from subprocess import *

from optparse import OptionParser



#def usage():
#    print "copyFiles.py [-c] <dataset>"
#    sys.exit()

try:
    opts, args = getopt.getopt(sys.argv[1:], "c")
except getopt.GetoptError:
    usage()
    sys.exit(2)

def CopyFiles(user="jbrooke",
              gridroot="srm://heplnx204.pp.rl.ac.uk:8443/srm/managerv2?SFN=",
              gridloc="/pnfs/pp.rl.ac.uk/data/cms/store/user",
              dataset="",
              odir="/storage/phjjb/stoppedHSCP/",
              verbose=False,
              overwrite=False):

    # Specify grid location using base gridloc, user and dataset
    # Specify output directory from base and dataset
    gridloc=os.path.join(gridloc,user,dataset)
    odir=os.path.join(odir,dataset)
    if not os.path.exists(odir):  # Create output dir if it doesn't exist
        os.makedirs(odir)

    print "Copying files from :"
    print gridroot
    print gridloc

    # get file list
    ls = Popen("lcg-ls "+gridroot+gridloc, shell=True, stdout=PIPE)
    lsop=ls.communicate()

    files=lsop[0]

    # copy files
    for file in files.splitlines():
        basename=os.path.basename(file)
        #command = "lcg-cp "+gridroot+"/"+file+" "+os.path.join(odir,basename)
        command = "lcg-cp %s/%s %s"%(gridroot,file,os.path.join(odir,basename))
        print "\n%s\n"%command
        
        # Protection against overwriting existing files -- ask if conflicting files should be overwritten
        if overwrite==False:
            print os.path.join(odir,basename), os.path.exists(os.path.join(odir,basename))
            if os.path.exists(os.path.join(odir,basename)):
                print "WARNING!  File '%s' already exists!"%os.path.join(odir,basename)
                cont=raw_input("Overwrite (y/n)? :  ")
                if not (cont.upper()).startswith("Y"):
                    continue
                print "Overwriting '%s'..."%basename
        cp = Popen(command, shell=True)
        cp.wait()

    return


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
        print "ERROR!  No datasets have been specified!"
        sys.exit()
        
    if options.gridloc==None:
        if options.useCAF==True:
            options.gridloc = "/castor.cern.ch/cms/store/caf/user/"
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
        print "Copying files in dataset '%s'"%d
        CopyFiles(user=options.user,
                  gridroot=options.gridroot,
                  gridloc=options.gridloc,
                  dataset=d,
                  odir=options.outputdir,
                  verbose=options.verbose,
                  overwrite=options.overwrite)
