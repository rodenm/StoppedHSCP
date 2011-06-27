{

gROOT->ProcessLine(".X finalPlotStyle.C+");
gROOT->ProcessLine(".L LimitPlots.C+");

gROOT->ProcessLine(".L modelIndLimit.C+");
modelIndLimit();

gROOT->ProcessLine(".L gluinoLimit.C+");
gluinoLimit();

gROOT->ProcessLine(".L stopLimit.C+");
stopLimit();

gROOT->ProcessLine(".L massPlot.C+");
massPlot();

}
