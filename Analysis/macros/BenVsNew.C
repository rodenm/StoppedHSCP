{

  // make comparison plots

  // custom libs
  gSystem->Load("libStoppedHSCPAnalysis");

  gROOT->ProcessLine(".L macros/Style.C");
  setTDRStyle();
  gROOT->ForceStyle();


  // CRAFT 09 31X

//   double time = 2513; // Run 111039

  // my ntuples
//   TChain* chain = new TChain("stoppedHSCPTree/StoppedHSCPTree");
//   chain->Add("/storage/phjjb/StoppedHSCP_CRAFT09_v9/stoppedHSCPTree.root");

//   gROOT->ProcessLine(".L macros/BasicHistos.C+");

//   BasicHistos(chain, "BasicHistos_CRAFT09_31X.root", time);
//   BasicPlots("BasicHistos_CRAFT09_31X.root", "BasicPlots_CRAFT09_31X.ps");


  // Ben's ntuples
//   TChain* chain = new TChain("globalRunAnalyser/EventTree");
//   chain->Add("/storage/phjjb/StoppedHSCP_CRAFT09_v9/stoppedHSCPTree.root");

//   gROOT->ProcessLine(".L macros/BasicHistos_Ben.C+");

//   BasicHistos(chain, "BasicHistos_Ben_CRAFT09_31X.root", time);
//   BasicPlots("BasicHistos_Ben_CRAFT09_31X.root", "BasicPlots_Ben_CRAFT09_31X.ps");


  /// CRAFT 08 31X

//   //  double time = 61753; // Run 68021
//   //double time = 414; // Run 68021 / 149
//    double time = 38958; // Run 68021 * (94 / 149)

  // my ntuples
//    TChain* chain = new TChain("stoppedHSCPTree/StoppedHSCPTree");
//    chain->Add("/storage/phjjb/StoppedHSCP_CRAFT08_v9/stoppedHSCPTree.root");
   
//    gROOT->ProcessLine(".L macros/BasicHistos.C+");
//    double time = 2513; // Run 111039
   
//    BasicHistos(chain, "BasicHistos_CRAFT08_31X.root", time);
//    BasicPlots("BasicHistos_CRAFT08_31X.root", "BasicPlots_CRAFT08_31X.ps");

  // Ben's ntuples 
//   TChain* chain = new TChain("globalRunAnalyser/EventTree");
//   chain->Add("/storage/phjjb/StoppedHSCP_CRAFT08_v9/stoppedHSCPTree.root");

//   gROOT->ProcessLine(".L macros/BasicHistos_Ben.C+");

//   BasicHistos(chain, "BasicHistos_Ben_CRAFT08_31X.root", time);
//   BasicPlots("BasicHistos_Ben_CRAFT08_31X.root", "BasicPlots_Ben_CRAFT08_31X.ps");


   // CRAFT 08 22X

//   double time = 61753; // Run 11039

   // Ben's ntuples
//   TChain* chain = new TChain("an_HLT/EventTree");
//   chain->Add("/storage/phjjb/StoppedHSCP_CRAFT08_22X_v1/Filter_Data_Histos.root");

//   gROOT->ProcessLine(".L macros/BasicHistos_Ben.C+");

//   BasicHistos(chain, "BasicHistos_Ben_CRAFT08_22x.root", time);
//   BasicPlots("BasicHistos_Ben_CRAFT08_22X.root", "BasicPlots_Ben_CRAFT08_22X.ps");


   // CRAFT 08 22X - Ben's ntuples from cms-bris-pc02

   double time = 61753; // Run 11039
   TChain* chain = new TChain("an_HLT/EventTree");
   chain->Add("/storage/phjjb/StoppedHSCP_CRAFT08_22X_Ben/Filter_Data_Histos.root");

   gROOT->ProcessLine(".L macros/BasicHistos_Ben.C+");
   BasicHistos(chain, "BasicHistos_Ben_CRAFT08_22x_Ben.root", time);
   BasicPlots("BasicHistos_Ben_CRAFT08_22x_Ben.root", "BasicPlots_Ben_CRAFT08_22X_Ben.ps");


}
