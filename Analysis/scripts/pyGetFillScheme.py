#!/usr/bin/env python


'''
pyGetFillScheme.py

v1.0

Jeff Temple


pythonized-version of getFillScheme.sh script.  This version allows users simply to provide input file "fills.txt",
and only the filling schemes in that file that have not already been defined (in "fillingSchemes.txt") will be added.
Users can also specify list of schemes on command line, and change input/output from default fills.txt and fillingSchemes.txt files
'''

import sys,os,string
import time

from optparse import OptionParser


def GetFillScheme(scheme,fillschemetext=None,overwrite=False):
    ''' Check whether "scheme" exists in input file "fillschemetext".  If so, do not add it to file
    (unless overwrite=True, in which case the new scheme will be added, but old will not (yet) be removed).
    If scheme does not exist, add it to text file using the getFillScheme.sh script.)
    '''
    #  Default location of fillingSchemes file
    if fillschemetext==None:
        fillschemetext=os.path.join(os.environ["CMSSW_BASE"],"src/StoppedHSCP/Analysis/data/fillingSchemes.txt")

    # Check to see whether scheme is already defined in file
    foundscheme=False
    if not os.path.isfile(fillschemetext):
        print "Error!  Filling Scheme file '%s' does not exist!"%fillschemetext
    else:
        temp=open(fillschemetext,'r').readlines()
        for line in temp:
            name=string.strip(line)
            if name==scheme:
                foundscheme=True
                break

    # Eventually, allow for overwriting of new information over old, instead of just adding new info
    if (foundscheme==True and overwrite==False):
        print "Scheme '%s' already exists in file!  Skipping this scheme..."%scheme
        return

    # Try to run shell script
    shellscript=os.path.join(os.environ["CMSSW_BASE"],"src/StoppedHSCP/Analysis/scripts/getFillScheme.sh")
    if not os.path.isfile(shellscript):
        print "ERROR!  Shell script '%s' does not exist!"%shellscript
        return
    print "Trying to add scheme '%s' to %s"%(scheme,fillschemetext)
    if os.path.isfile(fillschemetext):
        os.system("%s %s %s"%(shellscript,scheme, fillschemetext))
    else:
        print "Warning:  fillscheme file '%s' does not exist!"%fillschemetext
        os.system("%s %s"%(shellscript, scheme))  # will this work?
    time.sleep(2)  # 2 second delay before next scheme
    return


############################################################

if __name__=="__main__":
    
    # Read command-line options
    parser = OptionParser()
    parser.add_option("-w","--write",
                      action="store_true",
                      default=False,
                      dest="write",
                      help="write scheme to file, even if it already exists in file.  (Default is False.)")
    parser.add_option("-f","--fillschemetext",
                      dest="fillschemetext",
                      default=os.path.join(os.environ["CMSSW_BASE"],"src/StoppedHSCP/Analysis/data/fillingSchemes.txt"),
                      help="Specify filling schemes file (default is ....data/fillingSchemes.txt)")
    parser.add_option("-i","--inputfile",
                      dest="input",
                      default=None,
                      help="Specify input file (fills.txt) from which the filling schemes should be taken")
    
    (options,args)=parser.parse_args()

    # List of all schemes
    schemes=[]

    # Schemes on command line
    for i in args:
        schemes.append(i)

    # Check fills.txt file (if provided)
    if options.input<>None:
        if not os.path.isfile(options.input):
            print "Sorry,  fills file '%s' does not exist!"%options.input
        else:
            temp=open(options.input,'r').readlines()
            for i in temp:
                # Try to read input line
                try:
                    line=string.split(i)
                    fill=string.atoi(line[0])
                    scheme=line[1]
                    schemes.append(scheme)
                except:
                    print "Could not parse line '%s'"%line

    # Add all new schems to fillschemetext file
    for scheme in schemes:
        GetFillScheme(scheme,
                      fillschemetext   = options.fillschemetext,
                      overwrite  = options.write)

    # Now get rid of trailing commas
    if os.path.isfile(options.fillschemetext):
        mylines=open(options.fillschemetext,'r').readlines()
        for i in range(0,len(mylines)):
            temp=string.strip(mylines[i])
            if temp.endswith(","):
                mylines[i]="%s\n"%temp[:-1]
        outfile=open(options.fillschemetext,'w')
        for i in mylines:
            outfile.write(i)
        outfile.close()
    else:
        print "Hmm... output file '%s' doesn't exist"%options.fillschemetext
