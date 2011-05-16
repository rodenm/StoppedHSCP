
# make final plots

dataset=$1

pwd=$PWD

cd $1

rm makeFinalPlots.C

echo { >> makeFinalPlots.C
echo "gROOT->ProcessLine(\".X $CMSSW_BASE/src/StoppedHSCP/Analysis/macros/finalPlotStyle.C+\");" >> makeFinalPlots.C
echo "gROOT->ProcessLine(\".L $CMSSW_BASE/src/StoppedHSCP/Analysis/macros/lifetimePlot.C+\");" >> makeFinalPlots.C
echo 'lifetimePlot("toymc/summary.txt", "time_profile.txt");' >>  makeFinalPlots.C
echo "gROOT->ProcessLine(\".L $CMSSW_BASE/src/StoppedHSCP/Analysis/macros/massPlot.C+\");" >> makeFinalPlots.C
echo 'massPlot("toymc/summary.txt", "time_profile.txt");' >>  makeFinalPlots.C
echo }  >>  makeFinalPlots.C

root -q -b makeFinalPlots.C >& finalPlots.txt

cd ..
