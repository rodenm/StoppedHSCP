
// macro that runs all parts of the analysis

{
  gSystem->Load("libStoppedHSCPAnalysis");

  gROOT->ProcessLine(".L macros/Chain.C+");
  gROOT->ProcessLine(".L macros/BasicHistos.C+");
  gROOT->ProcessLine(".L macros/EffHistos.C+");

  // make the plots
  gROOT->ProcessLine(".L macros/Style.C");
  setTDRStyle();

  EffPlots();
  //  BasicPlots();

}
