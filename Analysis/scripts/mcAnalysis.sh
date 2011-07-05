#!/bin/sh

# arguments
dataset=$1
ntupdir=$2

if [ $# -lt 2 ]
then
    echo "Must provide <outputdir> <inputdir> on command line!"
    exit 2
fi

version=0
echo "Using cuts version $version"


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
echo "  cuts    : " $version
#echo "  control : " $control

# make output dir
if [ ! -e $outdir ]
then
    mkdir $outdir
fi

# make histograms
echo
echo "makeHistograms $control -c $version $outdir $ntuples > $outdir/histogrammer.log"
makeHistograms -m -c $version $outdir $ntuples > $outdir/histogrammer.log

# make basic plots
echo
echo "basicPlots.py $outdir > $outdir/plots.log"
python $CMSSW_BASE/src/StoppedHSCP/Analysis/python/basicPlots.py $outdir > $outdir/plots.log

# print summary
echo
echo "printSummary.py $outdir > $outdir/summary.txt"
python $CMSSW_BASE/src/StoppedHSCP/Analysis/python/printSummary.py $outdir $bgdir > $outdir/summary.txt

# make tarball
echo
echo "tar -zcvf $outdir.tgz $outdir/"
tar -zcvf $outdir.tgz $outdir/
