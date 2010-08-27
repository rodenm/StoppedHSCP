#!/bin/sh

# run all steps of the analysis

dataset=$1
runs=$2

# make histograms
makeHistograms ntuples/stoppedHSCP_tree_$dataset.root $dataset $runs

# make plots
python $CMSSW_BASE/src/StoppedHSCP/Analysis/macros/makePlots.py $dataset
python $CMSSW_BASE/src/StoppedHSCP/Analysis/macros/makePlotsByRun.py $dataset $runs

# print summary
python $CMSSW_BASE/src/StoppedHSCP/Analysis/macros/printSummary.py $dataset

# make Toy MC jobs
makeToyJobs.py $dataset