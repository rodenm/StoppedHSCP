#!/bin/sh

# arguments
dataset=$1
ntupdir=$2
version=$3
control=$4
if [ $# -ne 3 ]
then
    version=0
fi

if [ $# -lt 2 ]
then
    echo "Must provide <outputdir> <inputdir> on command line!"
    exit 2
fi

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
echo "  control : " $control

# make output dir
if [ ! -e $outdir ]
then
    mkdir $outdir
fi

# make histograms
echo
echo "makeHistograms $control -c $version $outdir $ntuples > $outdir/histogrammer.log"
makeHistograms $control -c $version $outdir $ntuples > $outdir/histogrammer.log

# make basic plots
echo
echo "basicPlots.py $outdir > $outdir/plots.log"
python $CMSSW_BASE/src/StoppedHSCP/Analysis/python/basicPlots.py $outdir > $outdir/plots.log

# make per-run plots
echo
echo "runPlots.py $outdir > $outdir/plots.log"
python $CMSSW_BASE/src/StoppedHSCP/Analysis/python/runPlots.py $outdir > $outdir/plots.log

# make per-fill plots
echo
echo "fillPlots.py $outdir > $outdir/plots.log"
python $CMSSW_BASE/src/StoppedHSCP/Analysis/python/fillPlots.py $outdir > $outdir/plots.log

# make more complex plots
### TO DO ###

# print summary
echo
echo "printSummary.py $outdir > $outdir/summary.txt"
python $CMSSW_BASE/src/StoppedHSCP/Analysis/python/printSummary.py $outdir $bgdir > $outdir/summary.txt

# generate Toy MC jobs
echo
echo "makeToyJobs.py $outdir"
makeToyJobs.py $outdir

# run Toy MC jobs
echo
echo "$outdir/runAll.sh >& runAll.log"
#./$outdir/toymc/runAll.sh >& $outdir/toymc/runAll.log &

# make limit plots
echo
echo "makeFinalPlots.sh $outdir"
makeFinalPlots.sh $outdir

# make tarball
echo
echo "tar -zcvf $outdir.tgz $outdir/"
tar -zcvf $outdir.tgz $outdir/
