#!/bin/sh

# arguments
dataset=$1

# variables
ntuple=ntuples/stoppedHSCP_tree_$dataset.root
outdir=$dataset

# 
echo "Going to run Stopped Gluino analysis"
echo "  ntuple : " $ntuple
echo "  output : " $outdir

# make output dir
mkdir $outdir

# make histograms
makeHistograms $ntuple $outdir

# make plots
makePlots.py $outdir

# print summary
printSummary.py $outdir

