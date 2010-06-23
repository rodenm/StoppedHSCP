#include <iostream>

#include "TMath.h"
#include "TFile.h"
#include "TCanvas.h"
//#include "SimpleShortPdf.h"
#include "StoppedHSCP/ToyMC/interface/LifetimePdf.h"
#include "StoppedHSCP/ToyMC/interface/SimpleBGPdf.h"
#include "RooRealVar.h"
#include "RooDataSet.h"
#include "RooPlot.h"
#include "RooGlobalFunc.h"
#include "RooFitResult.h"

using namespace RooFit;

int main(int, char**) {

  TCanvas c;

  TFile file("events.root");
  TTree *events = (TTree*)(file.Get("events"));

  RooRealVar ls("ls", "ls", 0, 15000);
  RooRealVar tau("tau", "tau", 600000);
  // SimpleShortPdf pdf("pdf", "pdf", ls);
  LifetimePdf pdf("pdf", "pdf", ls, tau);
  SimpleBGPdf bg("bg", "bg", ls);

  RooDataSet imported("imported", "imported", events, RooArgList(ls));

  RooPlot *frame = ls.frame();
  imported.plotOn(frame);
  //RooFitResult *result = pdf.fitTo(imported, Save(kTRUE), Minos(kFALSE), Hesse(kFALSE),PrintLevel(0));
  pdf.plotOn(frame);
  //RooFitResult *result_bg = bg.fitTo(imported, Save(kTRUE), Minos(kFALSE), Hesse(kFALSE),PrintLevel(0));
  bg.plotOn(frame, RooFit::LineColor(kRed));
  frame->Draw();

  //  std::cout << "Signal NLL: " << result->minNll() << std::endl;
  //std::cout << "BG     NLL: " << result_bg->minNll() << std::endl;

  c.Print("frame.eps");

  return 0;
}
