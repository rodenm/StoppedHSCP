
// macro that runs all parts of the analysis

{

  gROOT->ProcessLine(".X macros/Setup.C");

  double time = 2513; // Run 111039
  //  double time = 178244;  // Runs 110958,110972,110987,110998,111009,111017,111023,111039,111047,111138

  BasicHistos(chain, "BasicHistos.root", time);
  BasicPlots("BasicHistos.root", "BasicPlots.ps");

//    EffHistos(chain, "EffHistos.root", time);
//    EffPlots("EffHistos.root", "EffPlots.ps");

//    PulseShapeHistos(chain, "PulseShapeHistos.root", time);
//    PulseShapePlots("PulseShapeHistos.root", "PulseShapePlots.ps");


  
  /// *** histograms from events passing jet+mu cuts ***

//   std::cout << "Writing events passing jet and mu cuts" << std::endl;
//   WriteSelection(chain, "SelEvents_JetMuCuts.root", 0x1f);

//   TChain* chain_b = new TChain("StoppedHSCPTree");
//   chain_b->Add("SelEvents_JetMuCuts.root");

//   std::cout << "Making basic histos of events passing jet and mu cuts" << std::endl;
//   BasicHistos(chain_b, "BasicHistos_JetMuCuts.root", time);
//   std::cout << "Making basic plots of events passing jet and mu cuts" << std::endl;
//    BasicPlots("BasicHistos_JetMuCuts.root", "BasicPlots_JetMuCuts.ps");
  
//   std::cout << "Making pulse shape histos of events passing jet and mu cuts" << std::endl;
//   PulseShapeHistos(chain_b, "PulseShapeHistos_JetMuCuts.root", time);
//   std::cout << "Making pulse shape plots of events passing jet and mu cuts" << std::endl;
//    PulseShapePlots("PulseShapeHistos_JetMuCuts.root", "PulseShapePlots_JetMuCuts.ps");
  


  /// *** histograms from events passing all cuts ***

//   std::cout << "Writing events passing all cuts" << std::endl;
//   WriteSelection(chain_b, "SelEvents_AllCuts.root", 0xffff);

//   TChain* chain_c = new TChain("StoppedHSCPTree");
//   chain_c->Add("SelEvents_AllCuts.root");

//   std::cout << "Making pulse shape histos of events passing all cuts" << std::endl;
//   PulseShapeHistos(chain_c, "PulseShapeHistos_AllCuts.root", time);
//   std::cout << "Making pulse shape plots of events passing all cuts" << std::endl;
//   PulseShapePlots("PulseShapeHistos_AllCuts.root", "PulseShapePlots_AllCuts.ps");


}
