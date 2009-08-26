
// macro that runs all parts of the analysis

{

  gROOT->ProcessLine(".L macros/Chain.C+");
  gROOT->ProcessLine(".L macros/BasicPlots.C+");

  // get the events
  TChain* chain = Chain();

  // make the basic plots
  BasicPlots(chain);

  // pulse shape plots
  //  PulseShapePlots();

  // make the selection efficiency plots
  //  EffPlots();

}
