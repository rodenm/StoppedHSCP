#!/bin/sh

# arguments
dataset=$1

# variables
ntuple=ntuples/stoppedHSCP_tree_$dataset.root
outdir=$dataset
bgdir=0

# print out
echo "Going to run Stopped Gluino analysis"
echo "  ntuple : " $ntuple
echo "  output : " $outdir

# make output dir
mkdir $outdir

# make histograms
echo
echo "makeHistograms $ntuple $outdir > $outdir/histogrammer.log"
makeHistograms $ntuple $outdir > $outdir/histogrammer.log

# make basic plots
echo
echo "basicPlots.py $outdir > $outdir/plots.log"
python $CMSSW_BASE/src/StoppedHSCP/Analysis/python/basicPlots.py $outdir > $outdir/plots.log

# make per-run plots
echo
echo "runPlots.py $outdir > $outdir/plots.log"
python $CMSSW_BASE/src/StoppedHSCP/Analysis/python/runPlots.py $outdir > $outdir/plots.log

# make per-run plots
echo
echo "fillPlots.py $outdir > $outdir/plots.log"
python $CMSSW_BASE/src/StoppedHSCP/Analysis/python/fillPlots.py $outdir > $outdir/plots.log

# make more complex plots
### TO DO ###

# print summary
echo
echo "printSummary.py $outdir > $outdir/summary.txt"
python $CMSSW_BASE/src/StoppedHSCP/Analysis/python/printSummary.py $outdir $bgdir > $outdir/summary.txt

# make tarball
echo
echo "tar -zcvf $outdir.tgz $outdir/"
tar -zcvf $outdir.tgz $outdir/
