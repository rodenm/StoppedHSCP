#!/usr/bin/env python

import sys
import optparse
import string
import os
import re

from constants import *

# ROOT
from ROOT import *


# help message
def usage():
    print "Usage : printSummary.py [-h] <input dataset>"

# Wrap printSummary in a function, so that
# a 'True' or 'False' can be returned, depending on
# success of function

def printSummary():

    # options
    parser = optparse.OptionParser()
    parser.add_option("-f", "--file", action="store",
                      dest="inputFile",
                      default="histograms.root")
    parser.add_option("-m", "--mc", action="store",
                      dest="isMC",
                      default=False)
    
    (opts, args)=parser.parse_args()

    theFile = opts.inputFile
    dataset = args[0]

    
    try:

        # arguments
        ddir = os.environ['PWD']+'/'+dataset

        # cmssw
        cmsswdir = os.environ['CMSSW_BASE']

        # print out
        print "Summary for dataset : ", dataset
        print

        hfile=TFile(dataset+"/"+theFile)

        # run info
        time=0
        if (not opts.isMC):
            # Previously-used method for accessing time, # of lb -- doesn't work on reduced ntuples
            ##htime=hfile.Get("runs/hruntime")
            ##hnlb=hfile.Get("runs/hrunlb")

            # Instead, use these histograms, which are filled correctly even for reduced ntuples
            htime=hfile.Get("runsReduced/hruntime_REDUCED")
            hnlb=hfile.Get("runsReduced/hrunlb_REDUCED")
            

            print "Run\t# LS\tTime(s)\tLive frac"
            runlivetime={}
            for i in range(1,htime.GetNbinsX()+1):
                runlivetime[htime.GetXaxis().GetBinLabel(i)] = (hnlb.GetBinContent(i),htime.GetBinContent(i))
                #print htime.GetXaxis().GetBinLabel(i)+"\t"+str(hnlb.GetBinContent(i))+"\t"+str(htime.GetBinContent(i))
            runlivekeys=runlivetime.keys()
            runlivekeys.sort()
            for key in runlivekeys:
                nLS = runlivetime[key][0]
                time = runlivetime[key][1]
                frac = time/(nLS*TIME_PER_LS)
                print "%s\t%i\t%d\t%f"%(key,nLS,time,frac)


            # total time
            time=htime.Integral()
            print "Total live time (s) : %i"%(time)


        hcutcum=hfile.Get("histograms/Cuts/hncutcum")
        hcutind=hfile.Get("histograms/Cuts/hncutind")
        hcutnmo=hfile.Get("histograms/Cuts/hnminus1cut")
        hnmu=hfile.Get("histograms/NoCuts/hnmu")

        ntot=hnmu.GetEntries()
        if opts.isMC:
            ntot=hcutcum.GetBinContent(1)

        # if (ntot==0):  print "ERROR!  Total number of entries = 0!"  # EXIT?

        # ELOG table
        print
        print '[TABLE border=1]'

        if opts.isMC:
            print "|Cut\t|N\t|cum %\t|N-1 % |-"
        else:
            print "|Cut\t|N\t|Rate (Hz) |N-1 % |N-1 (Hz)|-"

        for i in range(0,nCuts):
            ncum = hcutcum.GetBinContent(i+1)
            nind = hcutind.GetBinContent(i+1)
            nnmo = hcutnmo.GetBinContent(i+1)
            label = hcutcum.GetXaxis().GetBinLabel(i+1)
            if opts.isMC:
                if (ntot<>0):
                    print '|%i %s | %i | %.2e | %.2e |' % (i, label, ncum, 100.*ncum/ntot, 100.*nnmo/ntot)
                else:
                    print '|%i %s | %i | N/A | N/A |' % (i, label, ncum)
            else:
                if (ntot<>0):
                    print '|%i %s | %i | %.2e +/- %.2e | %i | %.2e +/- %.2e |-' % (i, label, ncum, ncum/time, sqrt(ncum)/time, nnmo, nnmo/time, sqrt(nnmo)/time)
                else:
                    print '|%i %s | %i | N/A | N/A | N/A |' % (i, label, ncum)

        print '[/TABLE]'
        print


        print 'Combined cuts N-1'
        print
        print '[TABLE border=1]'

        if opts.isMC:
            print "|Cut\t|N-1 % |-"
        else:
            print "|Cut\t|N-1 (Hz)|-"

        hnm1Test = hfile.Get("histograms/Cuts/hNM1Test")

        for i in range(0,7):
            nnmo = hnm1Test.GetBinContent(i+1)
            label = hnm1Test.GetXaxis().GetBinLabel(i+1)
            if opts.isMC:
                if (ntot<>0):
                    print '|%i %s | %i | %.2e |' % (i, label, nnmo, 100.*nnmo/ntot)
                else:
                    print '|%i %s | N/A |' % (i, label)
            else:
                if (ntot<>0):
                    print '|%i %s | %i | %.2e +/- %.2e |-' % (i, label, nnmo, nnmo/time, sqrt(nnmo)/time)
                else:
                    print '|%i %s | N/A |' % (i, label, ncum)

        print '[/TABLE]'
        print



        # backgrounds
        N_n90   = int(hcutnmo.GetBinContent(in90+1))
        N_ct    = int(hcutnmo.GetBinContent(iCT+1))
        N       = hcutcum.GetBinContent(iAllCuts+1)

        #print "N-1 rates"
        #print '  n90   : %.2e +/- %.2e (stat)' % (n90nmo/time, sqrt(n90nmo)/time)
        #print '  CT    : %.2e +/- %.2e (stat)' % (ctnmo/time, sqrt(ctnmo)/time)
        #print

        # selected counts
        print "Selected counts from this sample"
        ## print "  N90(N-1)  : ", N_n90
        ## print "  CT(N-1)   : ", N_ct
        print "  Final     : ", int(N)
        print

        # Rate coefficients
        if (N_n90>0):
            Rn90 = N/N_n90
        else:
            Rn90=-1 # nonsense rate when N_n90=0

        if (N_ct>0):
            Rct  = N/N_ct
        else:
            Rct = -1 # nonsense rate when N_ct=0
        
        ## print "Rate coefficients from this sample"
        ## print "  N90 : ", Rn90
        ## print "  CT  : ", Rct
        ## print

        # Rate coefficients from control
        Rn90_ctrl = float(N_ctrl)/N_n90_ctrl
        Rct_ctrl  = float(N_ctrl)/N_ct_ctrl
        ## print "Rate coefficients from control sample"
        ## print "  N90 : ", Rn90_ctrl
        ## print "  CT  : ", Rct_ctrl
        ## print

        # calculate expected final counts
        # using n90 only
        Nexp_n90       = Rn90_ctrl * N_n90
        if (N_n90 > 0):
            Nexp_n90_stat = 1/sqrt(N_n90)
        else:
            Nexp_n90_stat = 99999999
        Nexp_n90_syst = sqrt( pow(N_n90_ctrl_stat, 2) +
                              pow(N_ctrl_stat, 2) )

        # using CT only
        Nexp_ct       = Rct_ctrl * N_ct
        if (N_ct > 0):
            Nexp_ct_stat = 1/sqrt(N_ct)
        else:
            Nexp_ct_stat = 99999999
        Nexp_ct_syst = sqrt( pow(N_ct_ctrl_stat, 2) +
                             pow(N_ctrl_stat, 2) )


        # combined
        Nexp       = 0.5 * ((Rn90_ctrl * N_n90) + (Rct_ctrl * N_ct))
        Nexp_stat  = sqrt( pow(N_n90_ctrl_stat, 2) +
                           pow(N_ct_ctrl_stat, 2) )


        Nexp_syst = 0.5 * sqrt( 2*pow(errSystRateCoeff, 2) +
                                      pow(N_n90_ctrl_stat, 2) +
                                      pow(N_ct_ctrl_stat, 2) +
                                      4*pow(N_ctrl_stat, 2) )

        Nexp_err  = sqrt(pow(Nexp_stat, 2) +
                         pow(Nexp_syst, 2) )

        print 'Expected BG counts : %.2e +/- %.2e (stat) +/- %.2e (syst)' % (Nexp, Nexp*Nexp_stat, Nexp*Nexp_syst)
        print 'Expected N90-only BG counts : %.2e +/- %.2e (stat) +/- %.2e (syst)' % (Nexp_n90, Nexp_n90*Nexp_n90_stat, Nexp_n90*Nexp_n90_syst)
        print 'Expected CT-only BG counts : %.2e +/- %.2e (stat) +/- %.2e (syst)' % (Nexp_ct, Nexp_ct*Nexp_ct_stat, Nexp_ct*Nexp_ct_syst)
        print 'Expected 2010B rate counts : %.2e +/- %.2e (stat)' % (R_ctrl*time, R_ctrl_stat*time)
        print

        print "Background rates"
        if (N_n90>0):
            print '  N90 method    : %.2e +/- %.2e (stat) +/- %.2e (syst)' % (Nexp_n90/time, Nexp*Nexp_n90_stat/time, Nexp*Nexp_n90_syst/time) 
        else:
            print '  N90 method    : n90nmo = 0! '
        if (N_ct>0):
            print '  CT method     : %.2e +/- %.2e (stat) +/- %.2e (syst)' % (Nexp_ct/time, Nexp*Nexp_ct_stat/time, Nexp*Nexp_ct_syst/time) 
        else:
            print '  CT method     :  ctnmo = 0!'
        print '  Combined      : %.2e +/- %.2e (stat) +/- %.2e (syst)' % (Nexp/time, Nexp*Nexp_stat/time, Nexp*Nexp_syst/time) 

        # background from control sample final rate
        print  '  Final rate method: %.2e +/- %.2e (stat)' % (R_ctrl, R_ctrl_stat)
        print

        # expected rate & total error
        n90Rate_exp     = Nexp_n90/time
        n90Rate_exp_err = (Nexp_n90/time)*sqrt( pow(Nexp_n90_stat, 2) + pow(Nexp_n90_syst, 2) )

        comb_exp        = Nexp/time
        comb_exp_err    = (Nexp/time)*sqrt( pow(Nexp_stat, 2) +
                                            pow(Nexp_syst, 2) )

        bgRate_exp     = R_ctrl
        bgRate_exp_err = R_ctrl_stat

        print "Expected rate for simulation :  %.3e +/- %.3e" % (bgRate_exp, bgRate_exp_err)
        print



        # get lists of runs, fills
        logfile = open(dataset+"/histogrammer.log", 'r')
        line1 = re.compile(r'(Runs :\s*)(\S*)')
        line2 = re.compile(r'(Fills :\s*)(\S*)')
        runsStr = ""
        fillsStr = ""
        for line in logfile.readlines():
            l1 = line1.match(line)
            if (l1):
                runsStr = l1.group(2)
            l2 = line2.match(line)
            if (l2):
                fillsStr = l2.group(2)

        runlist = runsStr.split(',')

        # write TeX file
        texfile = open(dataset+"/table.tex", "w")
        if opts.isMC:
            texfile.write( "& Cut & cum \% & N-1 \% & \\\ \hline \n" )
        else:
            texfile.write( "& Cut & Rate (Hz) & N-1 rate (Hz) & \\\ \hline \n" )

        for i in range(0,nCuts):
            ncum = hcutcum.GetBinContent(i+1)
            nind = hcutind.GetBinContent(i+1)
            nnmo = hcutnmo.GetBinContent(i+1)
            label = hcutcum.GetXaxis().GetBinLabel(i+1)
            if opts.isMC:
                if (ntot<>0):
                    texfile.write( '& %s & %.2e & %.2e & \\\ \n' % (label, 100.*ncum/ntot, 100.*nnmo/ntot) )
                else:
                    texfile.write('& %s & N/A | N/A | \\\ \n' % (label) )
            else:
                if (ntot<>0):
                    texfile.write( '& %s & %.2e \pm %.2e & %.2e \pm %.2e & \\\ \n' % (label, ncum/time, sqrt(ncum)/time, nnmo/time, sqrt(nnmo)/time) )
                else:
                    texfile.write( '& %s & N/A & N/A & \\\ \n' % (label) )
        texfile.close()


        # now write Toy MC file
        ofile = open(dataset+"/parameters.txt", 'w')
        ofile.write("mass\t\t\t200\n")
        ofile.write("crossSection\t\t606\n")
        ofile.write("lifetime\t\t1\n")
        ofile.write("signalEff\t\t0.033652\n")
        ofile.write("signalEff_e\t\t0.0\n")
        ofile.write("bgRate\t\t\t")
        ofile.write(str(bgRate_exp)+"\n")
        ofile.write("bgRate_e\t\t")
        ofile.write(str(bgRate_exp_err)+"\n")
        ofile.write("scaleUncert\t\t")
        ofile.write(str(scaleUncert) +"\n")
        ofile.write("optimizeTimeCut\t\t1\n")
        ofile.write("histFile\t\t")
        ofile.write(ddir+"/histograms.root\n")
        ofile.write("lumiFile\t\t")
        ofile.write(cmsswdir+"/src/StoppedHSCP/Analysis/data/lumi_all.csv\n")
        ofile.write("jsonFile\t\t")
        ofile.write(cmsswdir+"/src/StoppedHSCP/Analysis/data/"+dataset+".root\n")
        ofile.write("lumiFirstRun\t\t")
        ofile.write(runlist[0]+"\n")  
        ofile.write("lumiLastRun\t\t")
        ofile.write(runlist[len(runlist)-1]+"\n")
        ofile.write("fills\t\t\t")
        ofile.write(fillsStr+"\n")
        ofile.write("eventsFile\t\t")
        ofile.write(ddir+"/eventList.log\n")
        ofile.write("nTrialsSignal\t\t100\n")
        ofile.write("nTrialsBackground\t100\n")
        ofile.write("simulateExpt\t\t0\n")
        ofile.write("fillScheme\t\tSingle_2b_1_1_1\n")
        ofile.write("beamOnTime\t\t0.\n")
        ofile.write("beamOffTime\t\t0.\n")
        ofile.write("instLumi\t\t0.\n")
        ofile.write("runningTime\t\t0.\n")
        ofile.close()
        return True

    except: # generic exception
        return False


#####################################

if __name__=="__main__":
    printSummary()
