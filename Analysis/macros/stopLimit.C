// .L lifetimePlot.C+
// lifetimePlot("limit_summary.txt")


// *********************************
// The following parameters (LUMI, MAXLUMI) need to be set by hand:
// LUMI is a double
#define LUMI 877.
// MAXINSTLUMI is a double
// Get MAXINSTLUMI directly from https://cmswbm.web.cern.ch/cmswbm/cmsdb/servlet/FillReport  
// (PeakInstLumi). 
// Units are 10^30 cm^-2 s^-1
#define MAXINSTLUMI 1300
// ENERGY is a string
#define ENERGY "8"
// *********************************

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

void stopLimit(double lumi=-1., double maxInstLumi=-1.) {


  if (lumi<0)
    lumi=LUMI;
  if (maxInstLumi<0)
    maxInstLumi=MAXINSTLUMI;
  LimitPlots plots(lumi);
  

  plots.calculateCrossSections(7,4,39,9);
	
  	// graphs - observed
  	TGraph* g_obs     = plots.getLimitStop();
	TGraph* g_obs_em  = plots.getLimitStopEM();
//  	TGraph* g_obs_nb = plots.getLimitGluinoNB();
  	TGraph* g_obs_tp  = plots.getLimitStopTP();
  	TGraph* g_exp      = plots.getExpLimitStop();
  	TGraphAsymmErrors* g_exp_1sig = plots.getExpLimitStop1Sig();
  	TGraphAsymmErrors* g_exp_2sig = plots.getExpLimitStop2Sig();
  
	TCanvas *canvas;
	canvas = new TCanvas("lifetimeLimit_stop");
	
	canvas->SetLogx();
	canvas->SetLogy();

	TH1 * h;
	TPaveText *blurb;

	h = canvas->DrawFrame(7.5e-8, .05, 1e6, 3e2);
	// h->SetTitle("Beamgap Expt;#tau_{#tilde{g}} [s]; #sigma(pp #rightarrow #tilde{g}#tilde{g}) [cm^{2}]");
	h->SetTitle("Beamgap Expt;#tau_{#tilde{t}} [s]; #sigma(pp #rightarrow #tilde{t}#tilde{t}) #times BR(#tilde{t} #rightarrow t#tilde{#chi}^{0}) [pb]");

	blurb = new TPaveText(2e-7, 4, 4e-3, 2e2);
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
	label.str("");
	label << "#sqrt{s} = " << ENERGY << " TeV";
	blurb->AddText(label.str().c_str());

	blurb->AddText("m_{#tilde{t}} - m_{#tilde{#chi}^{0}} = 180 GeV/c^{2}");
	//blurb->AddText("m_{#tilde{g}} = 300 GeV/c^{2}");
	//blurb->AddText("m_{#tilde{#chi}^{0}} = 200 GeV/c^{2}");
	blurb->SetTextFont(42);
	blurb->SetBorderSize(0);
	blurb->SetFillColor(0);
	blurb->SetShadowColor(0);
	blurb->SetTextAlign(12);
	blurb->SetTextSize(0.033);
	blurb->Draw();

	TLegend *leg = new TLegend(2e-2, 4, 1e1, 2e2,"95% C.L. Limits:","");
	leg->SetTextSize(0.033);
	leg->SetBorderSize(0);
	leg->SetTextFont(42);
	leg->SetFillColor(0);
	leg->AddEntry(g_exp, "Expected: Counting Exp.", "l");
	leg->AddEntry(g_exp_1sig, "Expected #pm1#sigma: Counting Exp.", "f");
	leg->AddEntry(g_exp_2sig, "Expected #pm2#sigma: Counting Exp.", "f");
	leg->AddEntry(g_obs, "Observed: Counting Exp.", "l");
	//leg->AddEntry(g_obs_stop,"Obs.: Counting Exp. (#tilde{t})", "l");
	//leg->AddEntry(g_obs_nb, "Obs.: Counting Exp. (Neutral R-Baryon)", "l");
	//leg->AddEntry(g_obs_em, "Observed: Counting Exp. (EM only)", "l");
	leg->AddEntry(g_obs_tp, "Observed: Timing Profile", "l");
	leg->Draw();

	// 2 sigma band
	if (g_exp_2sig) {
		g_exp_2sig->SetLineColor(0);
		g_exp_2sig->SetLineStyle(0);
		g_exp_2sig->SetLineWidth(0);
		g_exp_2sig->SetFillColor(kYellow);
		g_exp_2sig->SetFillStyle(1001);
		g_exp_2sig->Draw("3");
	}

	// 1 sigma band
	if (g_exp_1sig) {
		// g_exp_1sig->SetLineColor(8);
		g_exp_1sig->SetLineColor(0);
		g_exp_1sig->SetLineStyle(0);
		g_exp_1sig->SetLineWidth(0);
		// g_exp_1sig->SetFillColor(8);
		g_exp_1sig->SetFillColor(kGreen);
		g_exp_1sig->SetFillStyle(1001);
		// g_exp_1sig->SetFillStyle(3005);
		g_exp_1sig->Draw("3");
		// g_exp_1sig->Draw("lX");
	}

	//lifetime fit
	if (g_obs_tp) {
		g_obs_tp->SetLineColor(kRed);
		g_obs_tp->SetLineStyle(1);
		g_obs_tp->SetLineWidth(2);
		g_obs_tp->Draw("l3");
	}

	// epxected limit
	if (g_exp) {
		g_exp->SetLineColor(1);
		g_exp->SetLineStyle(2);
		g_exp->SetLineWidth(2);
		g_exp->Draw("l3");
	}

	TLine *l;
	l = new TLine(7.5e-8, 2.0, 1e6, 2.0); // Stop 300 GeV
	l->SetLineColor(kBlue);
	l->SetLineWidth(2);
	l->Draw();

	//uncertainty band
	// TBox *syst = new TBox(1e-8, 515, 1e7, 697);
	// syst->SetFillStyle(3001);
	// syst->SetFillColor(kBlue-4);
	// syst->Draw();

	TLatex *t1;
	//t1 = new TLatex(1.e2, 70., "NLO+NLL");
	t1 = new TLatex(0.05, 2.8, "NLO+NLL (m_{#tilde{t}} = 300 GeV/c^{2})");
	t1->SetTextColor(kBlue);
	t1->SetTextFont(42);
	t1->SetTextSize(0.035);
	t1->Draw();

	// observed limit
	if (g_obs) {
		g_obs->SetLineColor(1);
		g_obs->SetLineStyle(1);
		g_obs->SetLineWidth(2);
		g_obs->Draw("l");
	}

	// EM model
	if (g_obs_em) {
		g_obs_em->SetLineColor(kGray+2);
		g_obs_em->SetLineWidth(2);
		g_obs_em->SetLineStyle(5);
		g_obs_em->Draw("l");
	}

	// NB model
//	if (g_obs_nb) {
//		g_obs_nb->SetLineColor(kGray+1);
//		g_obs_nb->SetLineWidth(2);
//		g_obs_nb->SetLineStyle(5);
		//g_obs_nb->Draw("l");
//	}

	canvas->RedrawAxis();

	canvas->Print("lifetimeLimit_stop.png");
	canvas->Print("lifetimeLimit_stop.pdf");
	canvas->Print("lifetimeLimit_stop.C");

}
