
// macro that runs all parts of the analysis

{
  // needed by selection
  gSystem->Load("libStoppedHSCPAnalysis");

  gROOT->ProcessLine(".L macros/Chain.C+");
  gROOT->ProcessLine(".L macros/BasicPlots.C+");
  gROOT->ProcessLine(".L macros/Cuts.C+");
  gROOT->ProcessLine(".L macros/WriteSelection.C+");

  // get the events
  TChain* chain = Chain();

  // make the basic plots
  BasicPlots(chain);

  // pulse shape plots
  //  PulseShapePlots();

  // make the selection efficiency plots
  //  EffPlots();

}
