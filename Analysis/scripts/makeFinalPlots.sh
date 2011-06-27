
# make final plots

dataset=$1
# lumi and maxInstLumi are optional arguments.
# if not provided, the "LUMI" and "MAXLUMI" values provided in each script are used.
lumi=$2
maxInstLumi=$3

if [ $# -lt 2 ]
then
    lumi=-1.
fi

if [ $# -lt 3 ]
then 
    maxInstLumi=-1.
fi

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

echo "lumi = "$lumi
echo "maxInstLumi = "$maxInstLumi
textcommand=makeFinalPlots.C"("$lumi,$maxInstLumi")"
root -b -q -l $textcommand >& finalPlots.txt


cd ..
