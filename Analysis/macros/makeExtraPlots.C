
void makeExtraPlots(double lumi=4560., double maxInstLumi=5000.)
{
  std::cout <<" Integrated lumi = "<<lumi<<"  max Inst. Lumi = "<<maxInstLumi<<std::endl;
  gROOT->ProcessLine(".X finalPlotStyle.C+");
  gROOT->ProcessLine(".L ExtraLimitPlots.C+");
  
  /**
  gROOT->ProcessLine(".L modelIndLimit.C+");
  modelIndLimit(lumi,maxInstLumi);
  
  gROOT->ProcessLine(".L gluinoLimit.C+");
  gluinoLimit(lumi,maxInstLumi);
  
  gROOT->ProcessLine(".L stopLimit.C+");
  stopLimit(lumi,maxInstLumi);

  gROOT->ProcessLine(".L gluinoMass.C+");
  gluinoMass(lumi,maxInstLumi);

  gROOT->ProcessLine(".L stopMass.C+");
  stopMass(lumi,maxInstLumi);

  gROOT->ProcessLine(".L massPlot.C+");
  massPlot(lumi,maxInstLumi);
  */

  gROOT->ProcessLine(".L allInOneLifetime.C+");
  allInOneLifetime(lumi,maxInstLumi);

  gROOT->ProcessLine(".L gluinostopMassLifetime.C+");
  gluinostopMassLifetime(lumi,maxInstLumi);

  gROOT->ProcessLine(".L excludedRegion.C+");
  excludedRegion();

  gROOT->ProcessLine(".L excludedRegionStop.C+");
  excludedRegionStop();

}

