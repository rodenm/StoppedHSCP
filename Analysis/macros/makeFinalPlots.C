
void makeFinalPlots(double lumi=-1, double maxInstLumi=-1)
{
  std::cout <<" Integrated lumi = "<<lumi<<"  max Inst. Lumi = "<<maxInstLumi<<std::endl;
  gROOT->ProcessLine(".X finalPlotStyle.C+");
  gROOT->ProcessLine(".L LimitPlots.C+");
  
  gROOT->ProcessLine(".L modelIndLimit.C+");
  modelIndLimit(lumi,maxInstLumi);
  
  gROOT->ProcessLine(".L gluinoLimit.C+");
  gluinoLimit(lumi,maxInstLumi);
  
  gROOT->ProcessLine(".L stopLimit.C+");
  stopLimit(lumi,maxInstLumi);
  
  gROOT->ProcessLine(".L massPlot.C+");
  massPlot(lumi,maxInstLumi);
}

