
// macro that runs all parts of the analysis

{

  // custom libs
  gSystem->Load("libStoppedHSCPAnalysis");

  // macros
  gROOT->ProcessLine(".L macros/BasicHistos.C+");
  gROOT->ProcessLine(".L macros/EffHistos.C+");
  gROOT->ProcessLine(".L macros/Cuts.C+");
  gROOT->ProcessLine(".L macros/WriteSelection.C+");
  gROOT->ProcessLine(".L macros/Style.C");

  // set plot style
  setTDRStyle();
  gROOT->ForceStyle();

  // get the events
  TChain* chain = new TChain("stoppedHSCPTree/StoppedHSCPTree");
  chain->Add("CRAFT09_v3a_1.root");
  chain->Add("CRAFT09_v3a_2.root");

  // make histograms
  BasicHistos(chain, "BasicHistos.root");
  EffHistos(chain, "EffHistos.root");

  // make the plots
  BasicPlots("BasicHistos.root", "BasicPlots.pdf");
  EffPlots("EffHistos.root", "EffPlots.pdf");

  // write out selected events
  WriteSelection(chain, "SelEvents_JetMuCuts.root", 0x1f);
  WriteSelection(chain, "SelEvents_AllCuts.root", 0xffff);


  // cross checks
  
  // test cuts
  gROOT->ProcessLine(".x macros/TestCuts.C");

  // make plots of selected events
  TChain* chain_b = new TChain("StoppedHSCPTree");
  chain_b->Add("SelEvents_JetMuCuts.root");

  BasicHistos(chain_b, "BasicHistos_JetMuCuts.root");
  BasicPlots("BasicHistos_JetMuCuts.root", "BasicPlots_JetMuCuts.pdf");
  
}
