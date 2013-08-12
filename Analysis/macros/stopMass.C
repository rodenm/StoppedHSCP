/// .L massPlot.C+
// lifetimePlot("limit_summary.txt", "time_profile_summary.txt")

// ***********************************************
// The following parameters (LUMI, MAXLUMI) need to be set by hand:
// LUMI is a double
#define LUMI 877.
// MAXINSTLUMI is a double
// Get MAXINSTLUMI directly from https://cmswbm.web.cern.ch/cmswbm/cmsdb/servlet/FillReport 
// (PeakInstLumi).  
// Units are 10^30 cm^-2 s^-1
#define MAXINSTLUMI 1300.
// ENERGY is a string
#define ENERGY "8"
// ***********************************************


#include <cstdlib>
#include <fstream>
#include <iostream> 
#include <sstream>

#include "TGraph.h"
#include "TGraphErrors.h"
#include "TGraphAsymmErrors.h"
#include "TCanvas.h"
#include "TFile.h"
#include "TH1.h"
#include "TH1F.h"
#include "TLegend.h"
#include "TPaveText.h"
#include "TBox.h"
#include "TLatex.h"

#include "LimitPlots.h"

// .L massPlot.C+
// massPlot("limit_summary.txt", "time_profile_summary.txt");

void stopMass(double lumi=-1., double maxInstLumi=-1.) {
	
  if (lumi<0)
    lumi=877.;
  if (maxInstLumi<0)
    maxInstLumi=1300.;
  LimitPlots plots(lumi);

  plots.calculateCrossSections(7,4,39,9);
  
  	// expected limit (1 and 2 sigma bands)
	TGraph* g_exp = plots.getExpMassLimitStop();
  	TGraphAsymmErrors* g_exp1 = plots.getExpMassLimitStop1Sig();
  	TGraphAsymmErrors* g_exp2 = plots.getExpMassLimitStop2Sig();
  
  	// three points on counting expt curve
  	TGraph* g_gluino = plots.getMassLimitGluino();
  	TGraph* g_stop = plots.getMassLimitStop();
  
  	// one point from lifetime fit
  	TGraph* g_tp = plots.getMassLimitStopTP();
  
  	// theory prediction
  	TGraph* g_thGluino = plots.getGluinoTheory();
  	TGraph* g_thStop = plots.getStopTheory();
  
  	TCanvas* canvas = new TCanvas("canvas");
  
  	//canvas->SetGrid();
  	canvas->SetLogy();
  
  	TH1 * h;
  	h = canvas->DrawFrame(300., .03, 600., 1e2);
  	//h->SetTitle("Beamgap Expt;m_{HSCP} [GeV/c^{2}]; Stopped HSCP Cross Section #times BR [pb]");
  	h->SetTitle("Beamgap Expt;m_{#tilde{t}} [GeV/c^{2}]; #sigma(pp #rightarrow #tilde{t}#tilde{t}) #times BR(#tilde{t} #rightarrow t#tilde{#chi}^{0}) [pb]");
  
  	// not covered region
  	TBox* nc = new TBox(100., .1, 150., 1e2);
  	nc->SetFillStyle(3354);
  	nc->SetFillColor(kRed-4);
  	//nc->Draw();
  
  	// details
  	TPaveText* blurb = new TPaveText(305., 3, 400., 1e2);
  	blurb->AddText("CMS Preliminary 2012");

  	std::stringstream label;
  	label<<"#int L dt = "<<lumi<<" fb^{-1}";
  	blurb->AddText(label.str().c_str());
  	label.str("");
  	double peakInstLumi=maxInstLumi;
  	int exponent=30;
  	while (peakInstLumi>10) {
    	peakInstLumi/=10.;
      	++exponent;
    }
  	label<<"L^{max}_{inst} = "<<peakInstLumi<<" x 10^{"<<exponent<<"} cm^{-2}s^{-1}";
  	blurb->AddText(label.str().c_str());
  	label.str("");
	label << "#sqrt{s} = " << ENERGY << " TeV";
	blurb->AddText(label.str().c_str());

  	//blurb->AddText("m_{#tilde{g}} - m_{#tilde{#chi}^{0}} = 100 GeV/c^{2}");
    blurb->AddText("m_{#tilde{t}} - m_{#tilde{#chi}^{0}} = 180 GeV/c^{2}");	
  	blurb->SetTextFont(42);
  	blurb->SetBorderSize(0);
  	blurb->SetFillColor(0);
  	blurb->SetShadowColor(0);
  	blurb->SetTextAlign(12);
  	blurb->SetTextSize(0.032);

  
  	// legend
  	TBox *legbg = new TBox(410., 3, 590., 1e2);
  	legbg->Draw();
  	TLegend *leg = new TLegend(410., 3, 590., 1e2,"95% C.L. Limits","");
  	leg->SetTextSize(0.028);
  	leg->SetBorderSize(0);
  	leg->SetTextFont(42);
  	leg->SetFillColor(0);
  	leg->AddEntry(g_exp, "Expected: 10 #mus - 1000 s Counting Exp.", "l");
  	leg->AddEntry(g_exp1, "Expected #pm1#sigma: 10 #mus - 1000 s Counting Exp.", "f");
  	leg->AddEntry(g_exp2, "Expected #pm2#sigma: 10 #mus - 1000 s Counting Exp.", "f");
//	  leg->AddEntry(graph3, "Obs.: 10^{6} s Counting Exp.", "l");
  	leg->AddEntry(g_stop, "Obs.: 10 #mus - 1000 s Counting Exp.", "l");
  	//leg->AddEntry(g_gluino, "Obs.: 10 #mus - 1000 s Counting Exp.", "l");
  	leg->AddEntry(g_tp, "Obs.: 10 #mus Timing Profile", "l");
  	//leg->AddEntry(graph_em, "Obs.: 10 #mus - 1000 s Counting Exp. (EM only)", "l");
  	//  leg->AddEntry(graph1, "Obs.: 570 ns Counting Exp.", "l");
  	leg->Draw();
  
  
  
  // 2 sigma expected band
  g_exp2->SetLineColor(0);
  g_exp2->SetLineStyle(0);
  g_exp2->SetLineWidth(0);
  g_exp2->SetFillColor(5);
  g_exp2->SetFillStyle(1001);
  g_exp2->Draw("3");
  
  // 1 sigma expected band
  g_exp1->SetLineColor(0);
  g_exp1->SetLineStyle(0);
  g_exp1->SetLineWidth(0);
  g_exp1->SetFillColor(3);
  g_exp1->SetFillStyle(1001);
  g_exp1->Draw("3");  
  
  // expected line
  g_exp->SetLineStyle(2);
  g_exp->SetLineWidth(1);
  g_exp->Draw("l");
  
 
  // plateau limit - 1 ms
  g_gluino->SetLineColor(1);
  g_gluino->SetLineStyle(1);
  g_gluino->SetLineWidth(2);
  //g_gluino->Draw("l");
  
   // stop curve
  g_stop->SetLineColor(1);
  g_stop->SetLineStyle(1);
  g_stop->SetLineWidth(2);
  g_stop->Draw("l");
 

  // 1 mus lifetime fit limit
  g_tp->SetLineColor(kRed);
  g_tp->SetLineStyle(1);
  g_tp->SetLineWidth(2);
  g_tp->Draw("l");
  
  // theory line
  g_thGluino->SetLineColor(kBlue);
  g_thGluino->SetLineStyle(1);
  g_thGluino->SetLineWidth(2);
  g_thGluino->SetFillStyle(3001);
  g_thGluino->SetFillColor(kBlue-4);
  //g_thGluino->Draw("l3");
  
  g_thStop->SetLineColor(kBlue);
  g_thStop->SetLineStyle(1);
  g_thStop->SetLineWidth(2);
  g_thStop->SetFillStyle(3001);
  g_thStop->SetFillColor(kRed-4);
  g_thStop->Draw("l3");


  // theory line label
  TLatex* th = new TLatex(480., 4., "NLO+NLL #tilde{g}");
  th->SetTextColor(kBlue);
  th->SetTextFont(42);
  th->SetTextSize(0.035);
  //th->Draw();

  TLatex* ths = new TLatex(400., .5, "NLO+NLL #tilde{t}");
  ths->SetTextColor(kBlue);
  ths->SetTextFont(42);
  ths->SetTextSize(0.035);
  ths->Draw();

  // not explored label
  TText* ne = new TText(125., .2, "Not Sensitive");
  ne->SetTextColor(kRed+1);
  ne->SetTextFont(42);
  ne->SetTextAngle(90);
  ne->SetTextSize(0.035);
  //ne->Draw();

  blurb->Draw();

  canvas->RedrawAxis();

  canvas->Print("stopMassLimit.pdf");
  canvas->Print("stopMassLimit.C");

	plots.calculateIntercepts();
  
}

