
// macro to select events from original file

{
  gSystem->Load("libStoppedHSCPAnalysis");
  gROOT->ProcessLine(".L macros/Chain.C+");
  gROOT->ProcessLine(".L macros/Cuts.C+");
  gROOT->ProcessLine(".L macros/WriteSelection.C+");

  TChain* chain = Chain();
  WriteSelection(chain, "SelectedEvents.root", 100000);
}
