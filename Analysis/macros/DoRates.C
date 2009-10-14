
// #include "TPDF.h"
// #include "TChain.h"
// #include "TFile.h"
// #include "TCanvas.h"

// #include <iostream>

{

  gROOT->ProcessLine(".X macros/Setup.C");
  gROOT->ProcessLine(".L macros/RateHistos.C+");

  // Create output file
  TFile *file = new TFile("rateHistos.root","recreate");

  // setup for errors
  TH1::SetDefaultSumw2();

  std::cout << "Making histograms" << std::endl;
  
  RateHistos(chain, 110958, 60);
  RateHistos(chain, 110972, 60);
  RateHistos(chain, 110987, 60);
  RateHistos(chain, 111009, 60);
  RateHistos(chain, 111017, 60);
  RateHistos(chain, 111023, 60);
  RateHistos(chain, 111039, 60);
  RateHistos(chain, 111047, 60);
  RateHistos(chain, 111138, 60);

  std::cout << "Making plots" << std::endl;

  TPostScript* ps = new TPostScript("RatePlots.ps");
  TCanvas* canvas = new TCanvas("canvas");

  RatePlot(file, canvas, 110958);
  RatePlot(file, canvas, 110972);
  RatePlot(file, canvas, 110987);
  RatePlot(file, canvas, 111009);
  RatePlot(file, canvas, 111017);
  RatePlot(file, canvas, 111023);
  RatePlot(file, canvas, 111039);
  RatePlot(file, canvas, 111047);
  RatePlot(file, canvas, 111138);

  ps->Close();

  delete file;


}
