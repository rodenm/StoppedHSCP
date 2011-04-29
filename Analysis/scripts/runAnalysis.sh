#!/bin/sh

# arguments
dataset=$1
ntupdir=$2

# variables
ntuples=''
outdir=$dataset

# get file list
for file in `ls $ntupdir`; do
    ntuples="$ntuples $ntupdir$file"
done

# print out
echo "Going to run Stopped Gluino analysis"
echo "  output  : " $outdir
echo "  ntuples : " $ntupdir

# make output dir
if [ ! -e $outdir ]
then
    mkdir $outdir
fi

# make histograms
echo
echo "makeHistograms $outdir $ntuples > $outdir/histogrammer.log"
makeHistograms $outdir $ntuples > $outdir/histogrammer.log

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
