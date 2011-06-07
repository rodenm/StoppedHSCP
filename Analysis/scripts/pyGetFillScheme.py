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


def GetFillScheme(scheme,
                  website="http://lpc.web.cern.ch/lpc/documents/FillPatterns",
                  backupwebsite="http://lpc-afs.web.cern.ch/lpc-afs/FILLSCHEMES",
                  verbose=False):

    '''
    Program looks for two sites (webiste and backupwebsite) for information.
    If info cannot be found in either, None value returned.
    If good info is read, ntuple of (beams1, beams2) returned.
    '''

    if os.path.isfile("scheme.tmp"):
        os.remove("scheme.tmp")

    fillingScheme=None  # store beams1, beam2 ntuple

    goodread=True  # Check whether file can be read with valid info
    for site in [website,backupwebsite]:
        if site==None or not site.startswith("http"):
            continue
        os.system("curl %s/%s.txt > scheme.tmp"%(website,scheme))
        # Check to see whether valid output read
        goodread=True
        schemefile=None
        if not os.path.isfile("scheme.tmp"):  # no file produced
            goodread=False
            continue
        # file found, open it and look for "BEAM1", "BEAM2"
        else:
            schemefile=open("scheme.tmp",'r').read()
            if string.find(schemefile,'BEAM1')==-1 or string.find(schemefile,'BEAM2')==-1:
                goodread=False
                continue
        if (goodread==True):  # Stop when first good file found
            break

    if (goodread==False):
        print "ERROR!  Could not read file for scheme %s"%scheme
        return fillingScheme

    myfile=open("scheme.tmp",'r').readlines()

    dobeam1=False
    dobeam2=False
    beam1=[]
    beam2=[]

    for i in myfile:  # loop through file, look for "BEAM1   BEAM2 slots", or vice versa
        if i.startswith("#"):
            temp=string.split(i)
            if (len(temp)>=3):
                # BEAM 1 found
                if temp[1]=="BEAM1" and temp[2]=="BEAM2" and temp[3]=="slots":
                    dobeam1=True
                    dobeam2=False
                # BEAM 2 found
                elif temp[1]=="BEAM2" and temp[2]=="BEAM1" and temp[3]=="slots":
                    dobeam1=False
                    dobeam2=True

        if (i.startswith("#")):
            continue
        # No beam found; continue
        if (dobeam1==False and dobeam2==False):
            continue
        # Beam 1
        elif dobeam1==True:
            temp=string.split(i)
            try:
                slot=string.atoi(temp[0])
                beam1.append(slot)
            except:
                print "Beam1:  Cannot parse line: '%s'"%beam1
        # Beam 2
        elif dobeam2==True:
            temp=string.split(i)
            try:
                slot=string.atoi(temp[0])
                beam2.append(slot)
            except:
                print "Beam2:  Cannot parse line: '%s'"%beam1
        # Assume file ends after beam 2
    if verbose:
        print "Scheme = ",scheme
        print "Beam 1 = ",beam1
        print "Beam 2 = ",beam2
    if len(beam1)==0 or len(beam2)==0:
        print "Error in scheme %s:  valid data can't be read"%scheme
        return fillingScheme
    fillingScheme=(beam1,beam2)
    return fillingScheme



def Main(scheme,fillschemetext=None,overwrite=False,verbose=False):
    ''' Check whether "scheme" exists in input file "fillschemetext".  If so, do not add it to file
    (unless overwrite=True, in which case the new scheme will be added, but old will not (yet) be removed).
    If scheme does not exist, add it to text file using the getFillScheme.sh script.)
    '''
    #  Default location of fillingSchemes file
    if fillschemetext==None:
        fillschemetext=os.path.join(os.environ["CMSSW_BASE"],"src/StoppedHSCP/Analysis/data/fillingSchemes.txt")

    # Check to see whether scheme is already defined in file
    foundscheme=False
    inputlines=None
    if not os.path.isfile(fillschemetext):
        print "Error!  Filling Scheme file '%s' does not exist!"%fillschemetext
    else:
        inputlines=open(fillschemetext,'r').readlines()
        for line in inputlines:
            name=string.strip(line)
            if name==scheme:
                foundscheme=True
                break

    # Eventually, allow for overwriting of new information over old, instead of just adding new info
    if (foundscheme==True and overwrite==False):
        #print "Scheme '%s' already exists in file!  Skipping this scheme..."%scheme
        return True

    print "TRYING TO ADD SCHEME:",scheme

    newscheme=GetFillScheme(scheme,verbose=verbose)  # add ability to change websites
    if newscheme==None:
        print "<pyGetFillScheme::Main> ERROR!  No scheme '%s' could be found!"%scheme
        return False
    
    if inputlines==None:
        inputlines=[]

    # Add extra line if necessary
    if len(inputlines)>0 and len(string.strip(inputlines[-1]))>1:
        inputlines.append("\n")

    inputlines.append("%s\n"%scheme)
    temp=""
    for i in range(len(newscheme[0])):  # BEAM 1
        temp=temp+"%i,"%newscheme[0][i]
    inputlines.append("%s\n"%temp[:-1])  # remove trailing comma
    temp=""
    for i in range(len(newscheme[1])):  # BEAM 1
        temp=temp+"%i,"%newscheme[1][i]
    inputlines.append("%s\n"%temp[:-1])  # remove trailing comma
    inputlines.append("\n")

    outfile=open(fillschemetext,'w')
    for i in inputlines:
        outfile.write(i)
    outfile.close()

    time.sleep(2)  # 2 second delay before next scheme
    return True


############################################################

if __name__=="__main__":
    
    # Read command-line options
    parser = OptionParser()
    parser.add_option("-w","--write",
                      action="store_true",
                      default=False,
                      dest="write",
                      help="write scheme to file, even if it already exists in file.  (Default is False.)")
    parser.add_option("-o","--fillschemetext",
                      dest="fillschemetext",
                      default=os.path.join(os.environ["CMSSW_BASE"],"src/StoppedHSCP/Analysis/data/fillingSchemes.txt"),
                      help="Specify filling schemes file (default is ....data/fillingSchemes.txt)")
    parser.add_option("-i","--inputfile",
                      dest="input",
                      default=None,
                      help="Specify input file (fills.txt) from which the filling schemes should be taken")
    parser.add_option("-v","--verbose",
                      dest="verbose",
                      default=False,
                      action="store_true",
                      help="Turn on verbose debugging")
    parser.add_option("-s","--scheme",
                      dest="schemes",
                      default=[],
                      action="append",
                      help="Specify a single scheme to get")
    
    (options,args)=parser.parse_args()

    # List of all schemes
    schemes=options.schemes

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

    FalseFiles=[]
    # Add all new schems to fillschemetext file
    for scheme in schemes:
        scheme=string.strip(scheme)
        if (scheme in FalseFiles):
            print "Already tried adding scheme '%s' without success -- skipping"%scheme
            continue
        temp=Main(scheme,
                  fillschemetext   = options.fillschemetext,
                  overwrite  = options.write,
                  verbose=options.verbose)
        if temp==False:
            FalseFiles.append(scheme)

    if len(FalseFiles)>0:
        print "The following schemes could not be added:"
        for i in FalseFiles:
            print "\t%s"%i

    # Now get rid of trailing commas
    # Shouldn't be necessary now
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
