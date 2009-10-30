{

  // custom libs
  gSystem->Load("libStoppedHSCPAnalysis");

  // macros
  gROOT->ProcessLine(".L macros/BasicHistos.C+");
//   gROOT->ProcessLine(".L macros/EffHistos.C+");
//   gROOT->ProcessLine(".L macros/PulseShapeHistos.C+");
//   gROOT->ProcessLine(".L macros/Cuts.C+");
//   gROOT->ProcessLine(".L macros/WriteSelection.C+");
   gROOT->ProcessLine(".L macros/Style.C");

  // set plot style
  setTDRStyle();
  gROOT->ForceStyle();

  // load chain
  TChain* chain = new TChain("globalRunAnalyser/EventTree");
  chain->Add("/storage/phjjb/StoppedHSCP_CRAFT09_v8/stoppedHSCPTree.root");

  TChain* chain = new TChain("stoppedHSCPTree/Events");
  chain->Add("/storage/phjjb/StoppedHSCP_CRAFT09_v8/stoppedHSCPTree.root");


}
