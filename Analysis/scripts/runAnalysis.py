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

from optparse import OptionParser


def GenericCommand(cmd):
    print
    print cmd
    os.system(cmd)
    return
    
def RunAnalysis(outdir, indir, version=0,steps=[]):
    if len(steps)==0:
        steps=range(10)

    if 0 in steps:
        # Step 0:  Make Histograms
        cmd="makeHistograms -c %s %s %s/*root > %s"%(version, outdir, indir, os.path.join(outdir,"histogrammer.log"))
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

    if 6 in steps:
        # Step 6:  Make Toy MC jobs
        os.system("chmod a+rw %s"%os.path.join(outdir,"histograms.root"))
        cmd="python %s/src/StoppedHSCP/ToyMC/scripts/makeToyJobs.py %s"%(os.environ["CMSSW_BASE"],outdir)
        GenericCommand(cmd)

    if 7 in steps:
        # Step 7:  run Toy MC jobs
        # Need to access this directly from python file, in order to check that all parallel jobs have completed
        #cmd="python %s/toymc/runAll.py >& %s/toymc/runAll.log &"%(outdir, outdir)
        #cmd="python %s/toymc/runAll.py"%outdir
        #GenericCommand(cmd)
        runAll.Main(workingdir="%s/toymc/"%outdir,
                    myfile="runAll.sh")  # does not yet support log file

    if 8 in steps:
        # Step 8:   make limit plots
        cmd="makeFinalPlots.sh %s"%outdir
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
                      default=None,
                      dest="inputdir",
                      help="Input directory where root tuples exist")
    parser.add_option("-o","--outputdir",
                      default=None,
                      dest="outputdir",
                      help="Output directory")
    parser.add_option("-v","--version",
                      dest="version",
                      default="0",
                      help="Version (default is '0')")
    for i in range(0,10):
        parser.add_option("-%i"%i,"--step%i"%i,
                          dest="step%i"%i,
                          help=labels(i),
                          default=False,
                          action="store_true")

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
            options.inputdir=args[i]
        elif i==2:
            options.version=args[i]
        
    if options.outputdir==None or options.inputdir==None:
        print "No input/output directories found!"
        print "Usage is: 'runAnalysis.py <outputdir> <inputdir> [version]"
        print "( [version] is optional. )"
        parser.print_help()
        print 
        help()
        sys.exit()

    if not os.path.isdir(options.inputdir):
        print "Error!  Input directory '%s' does not exist!"%inputdir
        sys.exit()
    if not os.path.isdir(options.outputdir):
        print "Error!  Output directory '%s' does not exist!"%outputdir
        yesno=raw_input("Create directory (y/n)? ")
        if yesno.upper().startswith("Y"):
            try:
                os.mkdir(options.outputdir)
            except OSError:
                print "Sorry, can't make output directory '%s'"%outputdir
                print "Perhaps you need to create parent directories first?"
                sys.exit()
        else:
            sys.exit()
            
    RunAnalysis(options.outputdir,options.inputdir, options.version,steps)
