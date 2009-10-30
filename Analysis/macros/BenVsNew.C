{

  // make comparison plots

  // custom libs
  gSystem->Load("libStoppedHSCPAnalysis");

  gROOT->ProcessLine(".L macros/Style.C");
  setTDRStyle();
  gROOT->ForceStyle();


  // my ntuples CRAFT 09 31X
//   TChain* chain = new TChain("stoppedHSCPTree/StoppedHSCPTree");
//   chain->Add("/storage/phjjb/StoppedHSCP_CRAFT09_v9/stoppedHSCPTree.root");

//   gROOT->ProcessLine(".L macros/BasicHistos.C+");
//   double time = 2513; // Run 111039

//   BasicHistos(chain, "BasicHistos_CRAFT09_31X.root", time);
//   BasicPlots("BasicHistos_CRAFT09_31X.root", "BasicPlots_CRAFT09_31X.ps");


  // Ben's ntuples CRAFT 09 31X
//   TChain* chain = new TChain("globalRunAnalyser/EventTree");
//   chain->Add("/storage/phjjb/StoppedHSCP_CRAFT09_v8/stoppedHSCPTree.root");

//   gROOT->ProcessLine(".L macros/BasicHistos_Ben.C+");
//   double time = 2513; // Run 11039

//   BasicHistos(chain, "BasicHistos_Ben_CRAFT09_31X.root", time);
//   BasicPlots("BasicHistos_Ben_CRAFT09_31X.root", "BasicPlots_Ben_CRAFT09_31X.ps");


  // Ben's ntuples CRAFT 08 22X
  TChain* chain = new TChain("an_HLT/EventTree");
  chain->Add("/storage/phjjb/StoppedHSCP_CRAFT08_22X_v1/Filter_Data_Histos.root");

  gROOT->ProcessLine(".L macros/BasicHistos_Ben.C+");
  double time = 61753; // Run 11039

  BasicHistos(chain, "BasicHistos_Ben_CRAFT08_22x.root", time);
  BasicPlots("BasicHistos_Ben_CRAFT08_22X.root", "BasicPlots_Ben_CRAFT08_22X.ps");


}
