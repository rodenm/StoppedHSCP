
{

  // make comparison plots

  // custom libs
  gSystem->Load("libStoppedHSCPAnalysis");

  gROOT->ProcessLine(".L macros/Style.C");
  setTDRStyle();
  gROOT->ForceStyle();


  // CRAFT 09 31X real HLT


  //  double time =1;
  //  double time = 2513; // Run 111039
    double time = 120493; // CRAFT 09

  // my ntuples
//   TChain* chain = new TChain("stoppedHSCPTree/StoppedHSCPTree");
//   chain->Add("/storage/phjjb/StoppedHSCP_CRAFT09_v9/stoppedHSCPTree.root");

//   gROOT->ProcessLine(".L macros/BasicHistos.C+");

//   BasicHistos(chain, "v9/BasicHistos_CRAFT09_31X.root", time);
//   BasicPlots("v9/BasicHistos_CRAFT09_31X.root", "v9/BasicPlots_CRAFT09_31X.ps");


  // Ben's ntuples
//   TChain* chain = new TChain("globalRunAnalyser/EventTree");
//   chain->Add("/storage/phjjb/StoppedHSCP_CRAFT09_v9/stoppedHSCPTree.root");

//   gROOT->ProcessLine(".L macros/BasicHistos_Ben.C+");

//   BasicHistos(chain, "v9/BasicHistos_Ben_CRAFT09_31X.root", time);
//   BasicPlots("v9/BasicHistos_Ben_CRAFT09_31X.root", "v9/BasicPlots_Ben_CRAFT09_31X.ps");


  // CRAFT 09 31X Ben's HLT

  // my ntuples
//   TChain* chain = new TChain("stoppedHSCPTree/StoppedHSCPTree");
//   chain->Add("/storage/phjjb/StoppedHSCP_CRAFT09_v9/stoppedHSCPTree.root");

//   gROOT->ProcessLine(".L macros/BasicHistos.C+");



//   BasicHistos(chain, "v10/BasicHistos_CRAFT09_31X.root", time);
//   BasicPlots("v10/BasicHistos_CRAFT09_31X.root", "v10/BasicPlots_CRAFT09_31X.ps");


  // Ben's ntuples
//   TChain* chain = new TChain("globalRunAnalyser/EventTree");
//   chain->Add("/storage/phjjb/StoppedHSCP_CRAFT09_v10/stoppedHSCPTree.root");

//   gROOT->ProcessLine(".L macros/BasicHistos_Ben.C+");

//   BasicHistos(chain, "v10/BasicHistos_Ben_CRAFT09_31X_fakeHLT.root", time);
//   BasicPlots("v10/BasicHistos_Ben_CRAFT09_31X_fakeHLT.root", "v10/BasicPlots_Ben_CRAFT09_31X_fakeHLT.ps");

  // CRAFT 09 31X Real HLT + Fake HLT, Ben's ntuples
    TChain* chain = new TChain("globalRunAnalyser/EventTree");
    chain->Add("/storage/phjjb/StoppedHSCP_CRAFT09_v13/stoppedHSCPTree.root");
    
    gROOT->ProcessLine(".L macros/BasicHistos_Ben.C+");
    BasicHistos(chain, "v13/BasicHistos_Ben_CRAFT09_31X.root", time);
    BasicPlots("v13/BasicHistos_Ben_CRAFT09_31X.root", "v13/BasicPlots_Ben_CRAFT09_31X.ps");
    
  //

  /// CRAFT 08 31X real HLT

  //  double time = 61753; // Run 68021
//   //double time = 414; // Run 68021 / 149
//    double time = 38958; // Run 68021 * (94 / 149)

  // my ntuples
//    TChain* chain = new TChain("stoppedHSCPTree/StoppedHSCPTree");
//    chain->Add("/storage/phjjb/StoppedHSCP_CRAFT08_v9/stoppedHSCPTree.root");
   
//    gROOT->ProcessLine(".L macros/BasicHistos.C+");
//    double time = 2513; // Run 111039
   
//    BasicHistos(chain, "v9/BasicHistos_CRAFT08_31X.root", time);
//    BasicPlots("v9/BasicHistos_CRAFT08_31X.root", "v9/BasicPlots_CRAFT08_31X.ps");

  // Ben's ntuples 
//   TChain* chain = new TChain("globalRunAnalyser/EventTree");
//   chain->Add("/storage/phjjb/StoppedHSCP_CRAFT08_v9/stoppedHSCPTree.root");

//   gROOT->ProcessLine(".L macros/BasicHistos_Ben.C+");

//   BasicHistos(chain, "v9/BasicHistos_Ben_CRAFT08_31X.root", time);
//   BasicPlots("v9/BasicHistos_Ben_CRAFT08_31X.root", "v9/BasicPlots_Ben_CRAFT08_31X.ps");


   // CRAFT 08 22X

  //   double time = 61753; // Run 68021
   //   double time = 61339; // Run 68021 * 148/149

   // Ben's ntuples
   //   TChain* chain = new TChain("an_HLT/EventTree");/   chain->Add("/storage/phjjb/StoppedHSCP_CRAFT08_22X_v1/Filter_Data_Histos.root");

   //   gROOT->ProcessLine(".L macros/BasicHistos_Ben.C+");

   //   BasicHistos(chain, "22X_v1/BasicHistos_Ben_CRAFT08_22x.root", time);
   //   BasicPlots("22X_v1/BasicHistos_Ben_CRAFT08_22X.root", "22X_v1/BasicPlots_Ben_CRAFT08_22X.ps");


   // CRAFT 08 22X real HLT

   //   TChain* chain = new TChain("globalRunAnalyser/EventTree");
   //   chain->Add("/storage/phjjb/StoppedHSCP_CRAFT08_22X_v3/stoppedHSCPTree.root");
   //   gROOT->ProcessLine(".L macros/BasicHistos_Ben.C+");

   //   BasicHistos(chain, "22X_v3/BasicHistos_Ben_CRAFT08_22X_realHLT.root", time);
   //   BasicPlots("22X_v3/BasicHistos_Ben_CRAFT08_22X_realHLT.root", "22X_v3/BasicPlots_Ben_CRAFT08_22X_realHLT.ps");

   // CRAFT 08 22X - Ben's ntuples from cms-bris-pc02

//    double time = 61753; // Run 11039
//    TChain* chain = new TChain("an_HLT/EventTree");
//    chain->Add("/storage/phjjb/StoppedHSCP_CRAFT08_22X_Ben/Filter_Data_Histos.root");

//    gROOT->ProcessLine(".L macros/BasicHistos_Ben.C+");
//    BasicHistos(chain, "22X_Ben/BasicHistos_Ben_CRAFT08_22x_Ben.root", time);
//    BasicPlots("22X_Ben/BasicHistos_Ben_CRAFT08_22x_Ben.root", "22X_Ben/BasicPlots_Ben_CRAFT08_22X_Ben.ps");


}
