
// macro that runs all parts of the analysis

{

  // custom libs
  gSystem->Load("libStoppedHSCPAnalysis");

  // macros
  gROOT->ProcessLine(".L macros/PulseShape.C+");
  gROOT->ProcessLine(".L macros/BasicHistos.C+");
  gROOT->ProcessLine(".L macros/EffHistos.C+");
  gROOT->ProcessLine(".L macros/PulseShapeHistos.C+");
  gROOT->ProcessLine(".L macros/Cuts.C+");
  gROOT->ProcessLine(".L macros/WriteSelection.C+");
  gROOT->ProcessLine(".L macros/Style.C");

  // set plot style
  setTDRStyle();
  gROOT->ForceStyle();


  /// *** histograms from all events ***

  TChain* chain = new TChain("stoppedHSCPTree/StoppedHSCPTree");
  chain->Add("/storage/phjjb/StoppedHSCP_CRAFT08_v1/stoppedHSCPTree.root");

  double time = 60032.;

//   BasicHistos(chain, "BasicHistos08.root", time);
//  BasicPlots("BasicHistos08.root", "BasicPlots08.ps");

   EffHistos(chain, "EffHistos08.root", time);
  EffPlots("EffHistos08.root", "EffPlots08.ps");

//   PulseShapeHistos(chain, "PulseShapeHistos08.root", time);
//  PulseShapePlots("PulseShapeHistos08.root", "PulseShapePlots08.ps");


  
  /// *** histograms from events passing jet+mu cuts ***

//   std::cout << "Writing events passing jet and mu cuts" << std::endl;
//   WriteSelection(chain, "SelEvents_JetMuCuts08.root", 0x1f);

//   TChain* chain_b = new TChain("StoppedHSCPTree");
//   chain_b->Add("SelEvents_JetMuCuts08.root");

//   std::cout << "Making basic histos of events passing jet and mu cuts" << std::endl;
//   BasicHistos(chain_b, "BasicHistos_JetMuCuts08.root", time);
//   std::cout << "Making basic plots of events passing jet and mu cuts" << std::endl;
//   BasicPlots("BasicHistos_JetMuCuts08.root", "BasicPlots_JetMuCuts08.ps");
  
//   std::cout << "Making pulse shape histos of events passing jet and mu cuts" << std::endl;
//   PulseShapeHistos(chain_b, "PulseShapeHistos_JetMuCuts08.root", time);
//   std::cout << "Making pulse shape plots of events passing jet and mu cuts" << std::endl;
//   PulseShapePlots("PulseShapeHistos_JetMuCuts08.root", "PulseShapePlots_JetMuCuts08.ps");
  


  /// *** histograms from events passing all cuts ***

//   std::cout << "Writing events passing all cuts" << std::endl;
//   WriteSelection(chain_b, "SelEvents_AllCuts08.root", 0xffff);

//   TChain* chain_c = new TChain("StoppedHSCPTree");
//   chain_c->Add("SelEvents_AllCuts08.root");

//   std::cout << "Making pulse shape histos of events passing all cuts" << std::endl;
//   PulseShapeHistos(chain_c, "PulseShapeHistos_AllCuts08.root", time);
//   std::cout << "Making pulse shape plots of events passing all cuts" << std::endl;
//   PulseShapePlots("PulseShapeHistos_AllCuts08.root", "PulseShapePlots_AllCuts08.ps");
  
}
