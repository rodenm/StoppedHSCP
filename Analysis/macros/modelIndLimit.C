// .L lifetimePlot.C+
// lifetimePlot("limit_summary.txt")


// *********************************
// The following parameters (LUMI, MAXLUMI) need to be set by hand:
// LUMI is a double
#define LUMI 417.
// MAXINSTLUMI is a double
// Get MAXINSTLUMI directly from https://cmswbm.web.cern.ch/cmswbm/cmsdb/servlet/FillReport  
// (PeakInstLumi). 
// Units are 10^30 cm^-2 s^-1
#define MAXINSTLUMI 1300
// ENERGY is a string
#define ENERGY "8"
// *********************************

#include <string>
#include <sstream>
#include "TGraph.h"
#include "TGraphAsymmErrors.h"
#include "TCanvas.h"
#include "TFile.h"
#include "TH1.h"
#include "TH1F.h"
#include "TLegend.h"
#include "TLatex.h"
#include "TPaveText.h"

#include "LimitPlots.h"

void modelIndLimit(double lumi=-1.,double maxInstLumi=-1.) 
{
  if (lumi<0)
    lumi=LUMI;
  if (maxInstLumi<0)
    maxInstLumi=MAXINSTLUMI;
  LimitPlots plots(lumi);
	
  plots.calculateCrossSections(7,4,39,9);

  // graphs - observed
  TGraph* g_gluino  = plots.getLimitGluinoBasic();
  TGraph* g_stop    = plots.getLimitStopBasic();
  
  TCanvas *canvas;
  canvas = new TCanvas("basicPlot");

  //canvas->SetGrid();
  canvas->SetLogx();
  canvas->SetLogy();

  TH1* h = canvas->DrawFrame(7.5e-8, 3e-3, 1e6, 10);
  //	h->SetTitle("Beamgap Expt;#tau_{#tilde{g}} [s]; #sigma(pp #rightarrow #tilde{g}#tilde{g}) #times BR(#tilde{g} #rightarrow g#tilde{#chi}^{0}) #times #varepsilon^{#tilde{g}#tilde{g}}_{stop} [pb]");
  h->SetTitle("Beamgap Expt;#tau_{HSCP} [s]; Model Independent Cross-section [pb]");

  TPaveText* blurb = new TPaveText(5e-7, .5, 1e-2, 7);
  blurb->AddText("CMS Preliminary 2012");

  std::stringstream label;
  label<<"#int L dt = "<<lumi<<" fb^{-1}";
  blurb->AddText(label.str().c_str());

  label.str("");
  double peakInstLumi=maxInstLumi;
  int exponent=30;
  while (peakInstLumi>10) {
    peakInstLumi/=10;
    ++exponent;
  }
  label<<"L^{max}_{inst} = "<<peakInstLumi<<" x 10^{"<<exponent<<"} cm^{-2}s^{-1}";
  blurb->AddText(label.str().c_str());

  //	blurb->AddText("LUMI pb^{-1}");
  //	blurb->AddText("L^{max}_{inst} = MAXLUMI 10^{33} cm^{-2}s^{-1}");
	
  label.str("");
  label << "#sqrt{s} = " << ENERGY << " TeV";
  blurb->AddText(label.str().c_str());
  //blurb->AddText("m_{HSCP} - m_{#tilde{#chi}^{0}} = 100 GeV/c^{2}");
  //blurb->AddText("m_{#tilde{g}} = 300 GeV/c^{2}");
  //blurb->AddText("m_{#tilde{#chi}^{0}} = 200 GeV/c^{2}");
  blurb->SetTextFont(42);
  blurb->SetBorderSize(0);
  blurb->SetFillColor(0);
  blurb->SetShadowColor(0);
  blurb->SetTextAlign(12);
  blurb->SetTextSize(0.033);
  blurb->Draw();


  //	TPaveText* cms = new TPaveText(1e-6, 1.5e1, 1e-2, 2e1);
  //	cms->AddText("CMS 2011");
  //	cms->SetTextFont(62);
  //	cms->SetBorderSize(0);
  //	cms->SetFillColor(0);
  //	cms->SetShadowColor(0);
  //	cms->SetTextAlign(12);
  //	cms->SetTextSize(0.040);
  //	cms->Draw();


  TLegend* leg = new TLegend(2e-2, .5, 1e2, 7,"95% C.L. Limits:","");
  leg->SetTextSize(0.030);
  leg->SetBorderSize(0);
  leg->SetTextFont(42);
  leg->SetFillColor(0);
  leg->AddEntry(g_gluino, "Gluino : m_{#tilde{g}}=500 GeV/c^{2}, m_{#tilde{#chi^{0}}}=387 GeV/c^{2}", "l");
  leg->AddEntry(g_stop, "Stop  : m_{#tilde{t}}=300 GeV/c^{2}, m_{#tilde{#chi^{0}}}=109 GeV/c^{2}", "l");
  leg->Draw();

  g_gluino->SetLineColor(2);
  g_gluino->SetLineStyle(1);
  g_gluino->SetLineWidth(2);
  g_gluino->Draw("l");

  g_stop->SetLineColor(4);
  g_stop->SetLineStyle(1);
  g_stop->SetLineWidth(2);
  g_stop->Draw("l");

  canvas->Print("basicLimit.png");
  canvas->Print("basicLimit.pdf");
  canvas->Print("basicLimit.C");

  return;

}
