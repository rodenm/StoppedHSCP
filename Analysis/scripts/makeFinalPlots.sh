
# make final plots

dataset=$1
# lumi and maxInstLumi are optional arguments.
lumi=$2
maxInstLumi=$3

# Set defaults in case lumi, maxLumi not provided
if [ $# -lt 2 ]
then
    lumi=4560.  # Units of pb^-1
fi

if [ $# -lt 3 ]
then 
    maxInstLumi=5000.  # Units of 10^30 cm^-2 s^-1
fi

pwd=$PWD

cp $CMSSW_BASE/src/StoppedHSCP/Analysis/macros/makeFinalPlots.C $dataset/.
cp $CMSSW_BASE/src/StoppedHSCP/Analysis/macros/makeExtraPlots.C $dataset/.
cp $CMSSW_BASE/src/StoppedHSCP/Analysis/macros/finalPlotStyle.C $dataset/.

cp $CMSSW_BASE/src/StoppedHSCP/Analysis/macros/LimitPlots.h $dataset/.
cp $CMSSW_BASE/src/StoppedHSCP/Analysis/macros/LimitPlots.C $dataset/.
cp $CMSSW_BASE/src/StoppedHSCP/Analysis/macros/ExtraLimitPlots.h $dataset/.
cp $CMSSW_BASE/src/StoppedHSCP/Analysis/macros/ExtraLimitPlots.C $dataset/.

cp $CMSSW_BASE/src/StoppedHSCP/Analysis/macros/modelIndLimit.C $dataset/.
cp $CMSSW_BASE/src/StoppedHSCP/Analysis/macros/gluinoLimit.C $dataset/.
cp $CMSSW_BASE/src/StoppedHSCP/Analysis/macros/stopLimit.C $dataset/.
cp $CMSSW_BASE/src/StoppedHSCP/Analysis/macros/massPlot.C $dataset/.
cp $CMSSW_BASE/src/StoppedHSCP/Analysis/macros/gluinoMass.C $dataset/.
cp $CMSSW_BASE/src/StoppedHSCP/Analysis/macros/stopMass.C   $dataset/.
cp $CMSSW_BASE/src/StoppedHSCP/Analysis/data/mcGluino.txt $dataset/.
cp $CMSSW_BASE/src/StoppedHSCP/Analysis/data/mcStop.txt $dataset/.
cp $CMSSW_BASE/src/StoppedHSCP/Analysis/data/mcStau.txt $dataset/.

cp $CMSSW_BASE/src/StoppedHSCP/Analysis/macros/allInOneLifetime.C $dataset/.
cp $CMSSW_BASE/src/StoppedHSCP/Analysis/macros/gluinostopMassLifetime.C $dataset/.
cp $CMSSW_BASE/src/StoppedHSCP/Analysis/macros/excludedRegion.C $dataset/.
cp $CMSSW_BASE/src/StoppedHSCP/Analysis/macros/excludedRegionStop.C $dataset/.

cp $dataset/toymc/summary.txt $dataset/toymc.txt

cd $dataset

# Replace MAXINSTLUMI in various files
sed s/=MAXINSTLUMI/=$maxInstLumi/ <stopLimit.C > stopLimitTEMP.C
sed s/=MAXINSTLUMI/=$maxInstLumi/ <gluinoLimit.C > gluinoLimitTEMP.C
sed s/=MAXINSTLUMI/=$maxInstLumi/ <modelIndLimit.C > modelIndLimitTEMP.C
sed s/=MAXINSTLUMI/=$maxInstLumi/ <massPlot.C > massPlotTEMP.C
sed s/=MAXINSTLUMI/=$maxInstLumi/ <gluinoMass.C > gluinoMassTEMP.C
sed s/=MAXINSTLUMI/=$maxInstLumi/ <stopMass.C > stopMassTEMP.C
sed s/=MAXINSTLUMI/=$maxInstLumi/ <allInOneLifetime.C > allInOneLifetimeTEMP.C
sed s/=MAXINSTLUMI/=$maxInstLumi/ <gluinostopMassLifetime.C > gluinostopMassLifetimeTEMP.C
sed s/=MAXINSTLUMI/=$maxInstLumi/ <excludedRegion.C > excludedRegionTEMP.C
sed s/=MAXINSTLUMI/=$maxInstLumi/ <excludedRegionStop.C > excludedRegionStopTEMP.C

mv stopLimitTEMP.C stopLimit.C
mv gluinoLimitTEMP.C gluinoLimit.C
mv modelIndLimitTEMP.C modelIndLimit.C
mv massPlotTEMP.C massPlot.C
mv gluinoMassTEMP.C gluinoMass.C
mv stopMassTEMP.C stopMass.C
mv allInOneLifetimeTEMP.C allInOneLifetime.C
mv gluinostopMassLifetimeTEMP.C gluinostopMassLifetime.C
mv excludedRegionTEMP.C excludedRegion.C
mv excludedRegionStopTEMP.C excludedRegionStop.C


# Replace LUMI in various files
sed s/=LUMI/=$lumi/ <stopLimit.C > stopLimitTEMP.C
sed s/=LUMI/=$lumi/ <gluinoLimit.C > gluinoLimitTEMP.C
sed s/=LUMI/=$lumi/ <modelIndLimit.C > modelIndLimitTEMP.C
sed s/=LUMI/=$lumi/ <massPlot.C > massPlotTEMP.C
sed s/=LUMI/=$lumi/ <gluinoMass.C > gluinoMassTEMP.C
sed s/=LUMI/=$lumi/ <stopMass.C > stopMassTEMP.C
sed s/=LUMI/=$lumi/ <allInOneLifetime.C > allInOneLifetimeTEMP.C
sed s/=LUMI/=$lumi/ <gluinostopMassLifetime.C > gluinostopMassLifetimeTEMP.C
sed s/=LUMI/=$lumi/ <excludedRegion.C > excludedRegionTEMP.C
sed s/=LUMI/=$lumi/ <excludedRegionStop.C > excludedRegionStopTEMP.C

mv stopLimitTEMP.C stopLimit.C
mv gluinoLimitTEMP.C gluinoLimit.C
mv modelIndLimitTEMP.C modelIndLimit.C
mv massPlotTEMP.C massPlot.C
mv gluinoMassTEMP.C gluinoMass.C
mv stopMassTEMP.C stopMass.C
mv allInOneLifetimeTEMP.C allInOneLifetime.C
mv gluinostopMassLifetimeTEMP.C gluinostopMassLifetime.C
mv excludedRegionTEMP.C excludedRegion.C
mv excludedRegionStopTEMP.C excludedRegionStop.C

echo "lumi = "$lumi
echo "maxInstLumi = "$maxInstLumi
textcommand=makeFinalPlots.C"("$lumi,$maxInstLumi")"
root -b -q -l $textcommand >& finalPlots.txt

textcommand=makeExtraPlots.C"("$lumi,$maxInstLumi")"
root -b -q -l $textcommand >& extraPlots.txt


cd ..
