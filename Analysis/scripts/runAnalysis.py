#!/usr/bin/env python

import sys, string, os
# Get runAll.py script from its location in StoppedHSCP/ToyMC
sys.path.append(os.path.join(os.environ['CMSSW_BASE'],"src","StoppedHSCP","ToyMC","scripts"))
try:
    import runAll
except:
    print "ERROR:  Unable to import runAll.py"
    print "Have you remembered to check out StoppedHSCP/ToyMC from CVS?"
    sys.exit()


# Add path with BuildToyMCSummary
# Get BuildToyMCSummary code
sys.path.append(os.path.join(os.environ['CMSSW_BASE'],"src","StoppedHSCP","Analysis","scripts"))
try:
    import BuildToyMCSummary
except:
    print "ERROR:  Unable to import buildToyMCSummary.py"
    sys.exit()


sys.path.append(os.path.join(os.environ['CMSSW_BASE'],"src","StoppedHSCP","Analysis","python"))
#try:
#    import printSummary
#except SyntaxError:
#    print "ERROR:  Unable to import printSummary.py"
#    sys.exit()

from optparse import OptionParser, OptionGroup


def GenericCommand(cmd):
    print
    print cmd
    os.system(cmd)
    return
    
def RunAnalysis(outdir, indirs, steps=[],makeHistsOptions={},
                oldSim=False,
                lumi=-1,
                maxInstLumi=-1):
    if len(steps)==0:
        steps=range(10)

    # TO DO:  Edit python methods to return True/False, depending on output results, and call the methods directly via import, rather than executing os.system calls

    if 0 in steps:
        # Step 0:  Make Histograms
        cmd="makeHistograms"
        keys=makeHistsOptions.keys()
        keys.sort()
        for k in keys:# add individual options
            cmd = cmd +" %s %s"%(k,makeHistsOptions[k])
        cmd =cmd +" %s"%outdir
        for dir in indirs:
            cmd=cmd+ " %s/*root"%dir
        cmd=cmd+" > %s"%os.path.join(outdir,"histogrammer.log")
        GenericCommand(cmd)
        
    if 1 in steps:
        # Step 1:  make basic plots
        cmd="python %s/src/StoppedHSCP/Analysis/python/basicPlots.py %s > %s"%(os.environ["CMSSW_BASE"],outdir, os.path.join(outdir,"plots.log"))
        GenericCommand(cmd)

    if 2 in steps:
        # Step 2:  make per-run plots
        cmd="python %s/src/StoppedHSCP/Analysis/python/runPlots.py %s > %s"%(os.environ["CMSSW_BASE"],outdir, os.path.join(outdir,"plots.log"))
        GenericCommand(cmd)

    if 3 in steps:
        # Step 3:  make per-fill plots
        cmd="python %s/src/StoppedHSCP/Analysis/python/fillPlots.py %s > %s"%(os.environ["CMSSW_BASE"],outdir, os.path.join(outdir,"plots.log"))
        #GenericCommand(cmd)
    
    if 4 in steps:
        # Step 4:  make more complex plots
        ### TO DO ###
        pass
    
    if 5 in steps:
        # Step 5:  print summary -- what is $bgdir supposed to be?
        cmd="python %s/src/StoppedHSCP/Analysis/python/printSummary.py %s > %s"%(os.environ["CMSSW_BASE"],outdir, os.path.join(outdir,"summary.txt"))
        GenericCommand(cmd)
        summary=os.path.join(outdir,"summary.txt")
        if not os.path.isfile(summary):
            print "File '%s' from printSummary.py not produced!  DISCONTINUING ANY REMAINING STEPS!"%summary
            return
        out=open(summary).read()
        if out.find("<printSummary.py> ERROR FOUND!")>-1:
            print "ERROR IN printSummary.py! \nDISCONTINUING ANY REMAINING STEPS! \nCheck output in %s"%summary
            return 
        

    if 6 in steps:
        # Step 6:  Make Toy MC jobs
        os.system("chmod a+rw %s"%os.path.join(outdir,"histograms.root"))
        cmd="python %s/src/StoppedHSCP/ToyMC/scripts/makeToyJobs.py  "%(os.environ["CMSSW_BASE"])
        args="%s"%(outdir)
        if (oldSim==True):  # add -o option before args
            args="-o %s"%args
        cmd="%s %s"%(cmd,args)
        GenericCommand(cmd)

    if 7 in steps:
        # Step 7:  run Toy MC jobs
        # Need to access this directly from python file, in order to check that all parallel jobs have completed
        #cmd="python %s/toymc/runAll.py >& %s/toymc/runAll.log &"%(outdir, outdir)
        #cmd="python %s/toymc/runAll.py"%outdir
        #GenericCommand(cmd)

        runAll.Main(workingdir="%s/toymc/"%outdir,
                    myfile="runAll.sh")  # does not yet support log file
        # Once job is written, overwrite summary file
        BuildToyMCSummary.Main(outdir,
                               outputfile="summary.txt")

    if 8 in steps:
        # Step 8:   make limit plots
        cmd="makeFinalPlots.sh %s %f %f"%(outdir,lumi,maxInstLumi)
        GenericCommand(cmd)

    if 9 in steps:
        # Step 9:  make tarball
        cmd="tar -zcvf %s.tgz %s"%(outdir,outdir)
        GenericCommand(cmd)
    
    return

def labels(step):
    if (step==0):
        return "Step 0:  Make Histograms"
    if (step==1):
        return "Step 1:  Make Basic Plots"
    if (step==2):  return "Step 2:  Make Per-Run Plots"
    if (step==3):  return "Step 3:  Make Per-Fill Plots"
    if (step==4):  return "Step 4:  Make Complex Plots (not yet enabled)"
    if (step==5):  return "Step 5:  Print Summary"
    if (step==6):  return "Step 6:  Make Toy MC Jobs"
    if (step==7):  return "Step 7:  Run Toy MC Jobs"
    if (step==8):  return "Step 8:  Make Final Limit Plots"
    if (step==9):  return "Step 9:  Create Tarball"
    else:
        return "Step %s not defined"%step
    return

def help():
    for i in range(0,10):
        print labels(i)
    return

if __name__=="__main__":
    parser=OptionParser()
    parser.add_option("-i","--inputdir",
                      default=[],
                      action="append",
                      dest="inputdir",
                      help="Input directory where root tuples exist")
    parser.add_option("-o","--outputdir",
                      default=None,
                      dest="outputdir",
                      help="Output directory")
    for i in range(0,10):
        parser.add_option("-%i"%i,"--step%i"%i,
                          dest="step%i"%i,
                          help=labels(i),
                          default=False,
                          action="store_true")
    #makeHistograms options
    makeHistGroup = OptionGroup(parser,
                                "Options for 'makeHistograms'",
                                "Optional arguments below are used in Step 0 (makeHistograms)."
                                )
    makeHistGroup.add_option("-b","--doControl",
                             dest="doControl",
                             action="store_true",
                             default=False,
                             help="Run on control triggers only.")
    makeHistGroup.add_option("-s","--doSearch",
                             dest="doSearch",
                             action="store_true",
                             default=False,
                             help="Run on search triggers only.")
    makeHistGroup.add_option("-n","--num",
                             dest="num",
                             type="int",
                             default=-1,
                             help="Specify number of events.")
    makeHistGroup.add_option("-m","--isMC",
                             dest="isMC",
                             action="store_true",
                             default=False,
                             help="Use MC settings, rather than default data setttings.")
    makeHistGroup.add_option("-c","--cuts",
                             dest="version",
                             default=0,
                             type="int",
                             help="Specify cut version.  Default is 0")
    parser.add_option_group(makeHistGroup)
    makeFinalGroup = OptionGroup(parser,
                                 "Options for 'makeFinalPlots'",
                                "Optional arguments below are used in Step 8 (makeFinalPlots)."
                                 )
    makeFinalGroup.add_option("--oldSim",
                              dest="oldSim",
                              action="store_true",
                              default=False,
                              help="If specified, use old simulate method, instead of new default 'simulateMulti'.")
    makeFinalGroup.add_option("-l","--lumi",
                              dest="lumi",
                              type="float",
                              default=-1.,
                              help="Specify integrated luminosity.  Default is -1.")
    makeFinalGroup.add_option("-x","--maxInstLumi",
                              dest="maxInstLumi",
                              type="float",
                              default=-1.,
                              help="Specify maximum integrated luminosity.  Default is -1.")
    parser.add_option_group(makeFinalGroup)

    options,args=parser.parse_args()
    steps=[]
    for i in range(0,10):
        exec("x=options.step%i"%i)
        if x==True:
            steps.append(i)

    # Old-style input <outputdir> <inputdir> <versions>
    for i in range(len(args)):
        if i==0:
            options.outputdir=args[i]
        elif i==1:
            options.inputdir.append(args[i])
        elif i==2:
            options.version=string.atoi(args[i])

    # Output directory always necessary
    if options.outputdir==None:
        print "No output directory found!"
        print "Usage is: 'runAnalysis.py <outputdir> [inputdir] [version] [analysis steps]"
        parser.print_help()
        print 
        help()
        sys.exit()


    #Get special options for makeHistograms
    makehistopt={}
    makehistopt["-c"]=options.version
    if options.doControl==True:
        makehistopt["--doControl"]=""
    if options.doSearch==True:
        makehistopt["--doSearch"]=""
    if options.num>-1:
        makehistopt["--num"]=options.num
    if options.isMC==True:
        makehistopt["--isMC"]=""

    if 0 in steps:  # first step (making a histogram) requires files from an input directory

        if len(options.inputdir)==0:
            print "Error!  Input directory has not been specified!"
            parser.print_help()
            print
            help()
            sys.exit()
        for dir in options.inputdir:
            if not os.path.isdir(dir):
                print "Error!  Input directory '%s' does not exist!"%dir
                options.inputdir.remove(dir)
        if len(options.inputdir)==0:
            print "No valid input directories remain"
            sys.exit()
            
    if not os.path.isdir(options.outputdir):
        #print "Error!  Output directory '%s' does not exist!"%options.outputdir
        #yesno=raw_input("Create directory (y/n)? ")
        #if yesno.upper().startswith("Y"):
        try:
            os.mkdir(options.outputdir)
        except OSError:
            print "Sorry, can't make output directory '%s'"%options.outputdir
            print "Perhaps you need to create parent directories first?"
            sys.exit()
        else:
            sys.exit()
            
    RunAnalysis(options.outputdir,
                options.inputdir,
                steps,
                makeHistsOptions=makehistopt,
                oldSim=options.oldSim,
                lumi=options.lumi,
                maxInstLumi=options.maxInstLumi
                )
