#!/usr/bin/env python

'''BuildToyMCSummary.py

by Jeff Temple
v1.0
06 June 2011

This program takes the indivudal "summary.txt" outputs from each job directory, and merges them together into a single file in the toymc subdirectory.  The single file is then used for further analysis.

The separate files are used because appending to a single file via the simulate.cpp script in ToyMC resulted in some odd behaviors.  (Perhaps these were due to multiple jobs trying to write to the file at once?)

This code removes any summary file in toymc and replaces it with the combination of the outputs in toymc/jobXX.  The combination is sorted in order of increasing lifetime prior to the file being written.

Options are:
  -d  <directory>   # specify directory where toymc subdirectory exists
  -f  <name>        # output file name (default is summary.txt)
'''

import os, sys, string
from optparse import OptionParser

def ReadSummaryFiles(summarylist):
    '''
    Try to read the lifetime from first line of each file in summarylist.
    Then create a dictionary with lifetime as key and first line as value
    This sorted dictionary will be outputted to the final summary file
    '''
    summary_out={}
    for i in summarylist:
        firstline=open(i,'r').readlines()
        if len(firstline)==0:
            print "Unable to read file '%s'"%i
            continue
        firstline=firstline[0]  # read first line only  -- any need to worry about multiple lines?
        temp=string.split(firstline)  
        try:  # Get lifetime
            lifetime=string.atof(temp[0])
            # What to do if multiple lifetime values found?  Should all give the same result, right?
            if lifetime in summary_out.keys():
                print "<BuildToyMCSummary.py::ReadSummaryFiles::WARNING>"
                print "\t Lifetime '%s' was previously listed in summary as '%s'"%(lifetime,summary_out[lifetime])
                print "\t Replacing with '%s'"%firstline
            summary_out[lifetime]=firstline  # assign dictionary key
        except:
            print "<BuildToyMCSummary.py::ReadSummaryFiles::Error>  Could not parse line '%s' in file '%s'"%(temp,i)
            print temp
            continue
    return summary_out  # return dictionary



def GetSummaryFiles(newbasedir):
    summaryfiles=[]
    for i in os.listdir(newbasedir):
        temp=os.path.join(newbasedir,i)
        if not os.path.isdir(temp):
            continue
        if not i.startswith("job"):  # only look at subdirectories named "job.."
            continue
        summaryfile=os.path.join(temp,"summary.txt")  # input files are all named 'summary.txt'
        if os.path.isfile(summaryfile):
            summaryfiles.append(summaryfile)  # add file to list of summaries
    summaryoutput=ReadSummaryFiles(summaryfiles)  # concatenate all summary results
    return summaryoutput



def CreateOutputSummary(summaryoutput, outname):

    # Dump concatenated list to final output file
    keys=summaryoutput.keys()
    keys.sort()
    if os.path.isfile(outname):
        os.remove(outname)
    outfile=open(outname,'w')
    for k in keys:
        outfile.write(summaryoutput[k])
    outfile.close()
    if os.path.isfile(outname):
        print "<BuildToyMCSummary.py::GetSummaryFiles>  Successfully produced summary file '%s'"%outname
        return True
    else:
        print "<BuildToyMCSummary.py::GetSummaryFiles::ERROR>  Could not produce summary file '%s'!"%outname
        return False

def Main(basedir,outputfile="summary.txt"):
    # Check to see that base directory exists
    if not os.path.isdir(basedir):
        print "<BuildToyMCSummary.py::GetSummaryFiles::Error>  Specified directory '%s' does not exist"%basedir
        return
    # Check that toymc subdirectory exists
    newbasedir=os.path.join(basedir,'toymc')
    if not os.path.isdir(newbasedir):
        print "<BuildToyMCSummar.py::GetSummaryFiles::Error>  Specified directory '%s' does not exist"
        return
    # Get list of individual summary files
    summaryoutput=GetSummaryFiles(newbasedir)
    # Make final output summary
    outname=os.path.join(newbasedir,outputfile)
    result=CreateOutputSummary(summaryoutput,outname=outname)
    return result

#############################################
if __name__=="__main__":

    parser=OptionParser()
    parser.add_option("-d","--dir",
                      dest="dir",
                      default=[],
                      action="append",
                      help="Specify directory where 'toymc' subdirectory resides.  Multiple directories may be specified (with a -d option in front of each), or just by listing directories as arguments on command line.")
    parser.add_option("-f","--filename",
                      dest="filename",
                      default="summary.txt",
                      help="Specify name of output summary file in toymc. Default is 'summary.txt'.")
    (options,args)=parser.parse_args()

    # Loop over argument directories
    for i in args:
        if not os.path.isdir(i):
            print "Sorry, directory '%s' does not exist!"%i
        else:
            Main(i,options.filename)

    # Loop over options-specified directories
    for i in options.dir:
        if not os.path.isdir(i):
            print "Sorry, directory '%s' does not exist!"%i
        else:
            Main(i,options.filename)
