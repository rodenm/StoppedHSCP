
# make final plots

dataset=$1

pwd=$PWD

cp $CMSSW_BASE/src/StoppedHSCP/Analysis/macros/makeFinalPlots.C $dataset/.
cp $CMSSW_BASE/src/StoppedHSCP/Analysis/macros/finalPlotStyle.C $dataset/.
cp $CMSSW_BASE/src/StoppedHSCP/Analysis/macros/LimitPlots.h $dataset/.
cp $CMSSW_BASE/src/StoppedHSCP/Analysis/macros/LimitPlots.C $dataset/.
cp $CMSSW_BASE/src/StoppedHSCP/Analysis/macros/modelIndLimit.C $dataset/.
cp $CMSSW_BASE/src/StoppedHSCP/Analysis/macros/gluinoLimit.C $dataset/.
cp $CMSSW_BASE/src/StoppedHSCP/Analysis/macros/stopLimit.C $dataset/.
cp $CMSSW_BASE/src/StoppedHSCP/Analysis/macros/massPlot.C $dataset/.
cp $CMSSW_BASE/src/StoppedHSCP/Analysis/data/mcGluino.txt $dataset/.
cp $CMSSW_BASE/src/StoppedHSCP/Analysis/data/mcStop.txt $dataset/.

cp $dataset/toymc/summary.txt $dataset/toymc.txt

cd $dataset

root -q -b makeFinalPlots.C >& finalPlots.txt

cd ..
