
// macro to select events from original file

{
  gSystem->Load("libStoppedHSCPAnalysis");
  gROOT->ProcessLine(".L macros/Chain.C+");
  gROOT->ProcessLine(".L macros/BasicPlots.C+");
  gROOT->ProcessLine(".L macros/Cuts.C+");
  gROOT->ProcessLine(".L macros/WriteSelection.C+");

  TChain* chain = Chain();

  // note the option to set maximum number of events to run over
  WriteSelection(chain, "SelectedEvents.root", 999999999);
}
