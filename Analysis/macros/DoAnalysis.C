
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
  chain->Add("/storage/phjjb/StoppedHSCP_CRAFT09_v4/stoppedHSCPTree.root");

  // make histograms
  std::cout << "Making basic histos" << std::endl;
  BasicHistos(chain, "BasicHistos.root");
  std::cout << "Making efficiency histos" << std::endl;
  EffHistos(chain, "EffHistos.root");

  // make the plots
  std::cout << "Making basic plots" << std::endl;
  BasicPlots("BasicHistos.root", "BasicPlots.pdf");
  std::cout << "Making efficiency plots" << std::endl;
  EffPlots("EffHistos.root", "EffPlots.pdf");

  // write out selected events
  std::cout << "Writing events passing jet and mu cuts" << std::endl;
  WriteSelection(chain, "SelEvents_JetMuCuts.root", 0x1f);
  std::cout << "Writing events passing all cuts" << std::endl;
  WriteSelection(chain, "SelEvents_AllCuts.root", 0xffff);


  // cross checks
  
  // test cuts
  std::cout << "Making test plots" << std::endl;
  gROOT->ProcessLine(".x macros/TestCuts.C");

  // make plots of selected events
  TChain* chain_b = new TChain("StoppedHSCPTree");
  chain_b->Add("SelEvents_JetMuCuts.root");

  std::cout << "Making basic histos of events passing jet and mu cuts" << std::endl;
  BasicHistos(chain_b, "BasicHistos_JetMuCuts.root");
  std::cout << "Making basic plots of events passing jet and mu cuts" << std::endl;
  BasicPlots("BasicHistos_JetMuCuts.root", "BasicPlots_JetMuCuts.pdf");
  
}
