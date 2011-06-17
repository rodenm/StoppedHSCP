#!/usr/bin/env python


'''
pyGetFillScheme.py

v1.0

Jeff Temple


pythonized-version of getFillScheme.sh script.  This version allows users simply to provide input file "fills.txt",
and only the filling schemes in that file that have not already been defined (in "fillingSchemes.txt") will be added.
Users can also specify list of schemes on command line, and change input/output from default fills.txt and fillingSchemes.txt files

If website for a given fill scheme does not exist, it may be that the name in fills.txt is incorrect.  Check against scheme names in /afs/cern.ch/user/l/lpc/2011/stablebeams2011, which should be correct.
'''

import sys,os,string
import time

from optparse import OptionParser

def ParseAndCleanFillFile(fillfile):
    '''
    This gets all filling schemes from a "fills.txt"-style file.
    It also "cleans" the fills.txt file, so that commas are added instead of spaces for any runs in the runlist for each fill.
    '''

    SchemesVsFills={}
    schemes=[]  # Store all schemes in the file
    if not os.path.isfile(fillfile):
        print "<pyGetFillScheme::ParseAndCleanFillFile::ERROR>  Input file '%s' does not exist"%fillfile
        return (schemes,SchemesVsFills)
    thefile=open(fillfile,'r').readlines()  # open file
    for i in range(len(thefile)):
        try:
            line=string.split(thefile[i])
            fill=string.atoi(line[0])
            scheme=line[1]  # identify scheme
            if scheme not in SchemesVsFills:
                SchemesVsFills[scheme]=[]
            SchemesVsFills[scheme].append(fill)
            if scheme not in schemes:  # add to list
                schemes.append(scheme)
            runs=line[2:]  # list of all runs
            
            # Change space-separated runs to comma-separated runs
            runtext=""
            for run in runs:
                runtext=runtext+"%s,"%run
            while runtext.endswith(","): # remove trailing comma
                runtext=runtext[:-1]
            newline=string.split(thefile[i],runs[0])[0]
            newline=newline+"%s"%runtext
            # now parse original line, and keep trailing \n, \t, space
            # No reason to keep them, except that 'diff' becomes simpler
            endline=""
            for char in range(len(thefile[i])-1,-1,-1):
                if thefile[i][char] not in ["\t","\n"," "]:
                    break

                endline=thefile[i][char]+endline
            if not endline.endswith("\n"):
                endline=endline+"\n"
            newline=newline+endline

            
            # replace original line with edited version
            thefile[i]=newline
        except ValueError: # can't read fill number
            print "Could not parse line '%s'"%line

    # Write fixed version of file
    fixedfile=open(fillfile,'w')
    for i in thefile:
        fixedfile.write(i)
    fixedfile.close()
    # Return schemes found
    return (schemes,  SchemesVsFills)



def GetFillScheme(scheme,
                  websites=["http://lpc.web.cern.ch/lpc/documents/FillPatterns",
                            "http://lpc-afs.web.cern.ch/lpc-afs/FILLSCHEMES"],
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
    for site in websites:
        if site==None or not site.startswith("http"):
            continue
        os.system("curl %s/%s.txt > scheme.tmp"%(site,scheme))
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
    '''
    Check whether "scheme" exists in input file "fillschemetext".
    If so, do not add it to file
    (unless overwrite=True, in which case the new scheme will be added,
    but old will not (yet) be removed).
    If scheme does not exist in file, add it to text file using
    the GetFillScheme method.)
    '''
    #  Default location of fillingSchemes file
    if fillschemetext==None:
        fillschemetext=os.path.join(os.environ["CMSSW_BASE"],
                                    "src/StoppedHSCP/Ntuples/data/fillingSchemes.txt")

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
    parser.add_option("-s","--scheme",
                      dest="schemes",
                      default=[],
                      action="append",
                      help="Specify a single scheme to get.  Multiple schemes can be added at once.")
    parser.add_option("-i","--inputfile",
                      dest="input",
                      default=None,
                      help="Specify input file from which the filling schemes should be taken.  Default is no file, but fills.txt will usually be the desired choice.")
    parser.add_option("-o","--fillschemetext",
                      dest="fillschemetext",
                      default=os.path.join(os.environ["CMSSW_BASE"],
                                           "src/StoppedHSCP/Ntuples/data/fillingSchemes.txt"),
                      help="Specify filling schemes file (default is ../StoppedHSCP/Ntuples/data/fillingSchemes.txt)")
    parser.add_option("-w","--website",
                      action="append",
                      default=["http://lpc.web.cern.ch/lpc/documents/FillPatterns",
                               "http://lpc-afs.web.cern.ch/lpc-afs/FILLSCHEMES"],
                      help="Specify websites to search for fill scheme info.  Defaults are: http://lpc.web.cern.ch/lpc/documents/FillPattern  and http://lpc-afs.web.cern.ch/lpc-afs/FILLSCHEMES")
    parser.add_option("-c","--clean",
                      action="store_true",
                      default=False,
                      dest="clean",
                      help="Only clean the input txt file (adding commas where necessary, etc.)  Don't run the actual scheme-getting code.  Default is False.")
    parser.add_option("-r","--rewrite",
                      action="store_true",
                      default=False,
                      dest="write",
                      help="write scheme to file, even if it already exists in file. Previous scheme will not be removed.  (Default is False.)")
    parser.add_option("-v","--verbose",
                      dest="verbose",
                      default=False,
                      action="store_true",
                      help="Turn on verbose debugging")
    
    (options,args)=parser.parse_args()

    # List of all schemes specified with "-s"
    schemes=options.schemes

    # Schemes on command line
    for i in args:
        schemes.append(i)

    # Check fills.txt file (if provided)
    SchemesVsFills={}
    if options.input<>None:
        if not os.path.isfile(options.input):
            print "Sorry,  fills file '%s' does not exist!"%options.input
        else:
            newschemes=ParseAndCleanFillFile(options.input)
            if options.clean==True:
                print "Input file %s has been cleaned"%options.input
                sys.exit()
            SchemesVsFills=newschemes[1]
            for n in newschemes[0]:
                schemes.append(n)

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
        print "\nThe following schemes could not be added:"
        print "\t%s\t\t%s"%("Scheme","Fills")
        print "\t------\t\t------"
        for i in FalseFiles:
            if i in SchemesVsFills.keys():
                print "\t%s\t\t%s"%(i,SchemesVsFills[i])
            else:
                print "\t%s\t\tUnknown Fills"%(i)
        print
        
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
        print "Completed writing of schemes to '%s'"%options.fillschemetext
    else:
        print "Hmm... output file '%s' doesn't exist"%options.fillschemetext
