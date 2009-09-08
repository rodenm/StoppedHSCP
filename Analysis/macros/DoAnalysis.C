
// macro that runs all parts of the analysis

{
  gSystem->Load("libStoppedHSCPAnalysis");

  gROOT->ProcessLine(".L macros/Chain.C+");
  gROOT->ProcessLine(".L macros/BasicHistos.C+");
  gROOT->ProcessLine(".L macros/EffHistos.C+");

  // get the events
  //  TChain* chain = Chain();

  // make the histograms
  //  BasicHistos(chain);
  //  EffHistos(chain);

  // make the plots
  gROOT->ProcessLine(".L macros/Style.C");
  setTDRStyle();

  BasicPlots();
  EffPlots();

  // write out selected events
  //  gROOT->ProcessLine(".L macros/WriteSelection.C+");
  //  WriteSelection(chain, "SelectedEvents.root", 999999999);

  // make plots of selected events?
  

}
