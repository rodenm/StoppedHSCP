
# make final plots

dataset=$1

pwd=$PWD

cd $dataset

rm makeFinalPlots.C

echo { >> makeFinalPlots.C

echo "gROOT->ProcessLine(\".X $CMSSW_BASE/src/StoppedHSCP/Analysis/macros/finalPlotStyle.C+\");" >> makeFinalPlots.C

echo "gROOT->ProcessLine(\".X $CMSSW_BASE/src/StoppedHSCP/Analysis/macros/LimitPlots.C+\");" >> makeFinalPlots.C

# model independent result
echo "gROOT->ProcessLine(\".L $CMSSW_BASE/src/StoppedHSCP/Analysis/macros/modIndLimit.C+\");" >> makeFinalPlots.C
echo 'modIndLimit("toymc/summary.txt", "time_profile.txt");' >>  makeFinalPlots.C

# gluino limit
echo "gROOT->ProcessLine(\".L $CMSSW_BASE/src/StoppedHSCP/Analysis/macros/gluinoLimit.C+\");" >> makeFinalPlots.C
echo 'gluinoLimit("toymc/summary.txt", "time_profile.txt");' >>  makeFinalPlots.C

# stop limit
echo "gROOT->ProcessLine(\".L $CMSSW_BASE/src/StoppedHSCP/Analysis/macros/stopLimit.C+\");" >> makeFinalPlots.C
echo 'stopLimit("toymc/summary.txt", "time_profile.txt");' >>  makeFinalPlots.C

# mass limits
echo "gROOT->ProcessLine(\".L $CMSSW_BASE/src/StoppedHSCP/Analysis/macros/massPlot.C+\");" >> makeFinalPlots.C
echo 'massPlot("toymc/summary.txt", "time_profile.txt");' >>  makeFinalPlots.C
echo }  >>  makeFinalPlots.C

root -q -b makeFinalPlots.C >& finalPlots.txt

cd ..
