// .L lifetimePlot.C+
// lifetimePlot("limit_summary.txt")


// *********************************
// The following parameters (LUMI, MAXLUMI) need to be set by hand:
// LUMI is a double
#define LUMI 267.
// MAXINSTLUMI is a double
// Get MAXINSTLUMI directly from https://cmswbm.web.cern.ch/cmswbm/cmsdb/servlet/FillReport  
// (PeakInstLumi). 
// Units are 10^30 cm^-2 s^-1
#define MAXINSTLUMI 1106.
// *********************************

#include <cstdlib>
#include <fstream>
#include <iostream> 
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

TCanvas *makeLifetimePlot(TGraph *g_cl95,
			  TGraph *g_exp_1sig=NULL,
			  TGraph *g_exp_2sig=NULL,
			  TGraph *g_cl95_em=NULL,
			  TGraph *g_cl95_nb=NULL,
			  TGraph *g_cl95_stop=NULL,
			  TGraph *g_cl95_tp=NULL,
			  double lumi_tp=0.);

TCanvas *makeBasicPlot(TGraph *g1,
		       TGraph *g2,
		       double lumi_tp=0);

// filename 1 = counting experiment output
// filename 2 = time profile fit output (if null do not plot curve)
// filename 3 = take limits from Fedors file
void lifetimePlot(char* filename, char* filename2="", char* filename3="") {

  // which mass point ?
  unsigned massIndex = 3;  // point 3 -> m_gluino=400, m_neutralino=300
  unsigned stopIndex = 2;  // point 3 -> m_stop=300

  // some numbers need to be set by hand
  double lumi_tp = LUMI;  // lumi figure to use for time-profile fit

  unsigned nGluino      = 7;
  double m_g[10]        = { 150.,     200.,      300.,      400.,      500.,     600.,    900. };
  double m_chi[10]      = { 50.,      100.,      200.,      300.,      400.,     500.,    800. };
  double stopEff_cm[10] = { 0.219*2., 0.198*2.,  0.205*2.,  0.207*2.,  0.209*2.  };  // cloud model
  double stopEff_em[10] = { 0.062*2., 0.0591*2., 0.0596*2., 0.0601*2., 0.0634*2. };  // EM only
  double stopEff_nb[10] = { 0.120*2., 0.0115*2., 0.0128*2., 0.0141*2., 0.0147*2. };  // neutral baryon
  double recoEff[10]    = { 0.146,    0.157,     0.170,     0.175,     0.175,    0.175,   0.175 };
 
  unsigned nStop          = 7;
  double m_stop[10]       = { 130,   200,   300,   500,   600,   800,   1200 };
  double m_chi_stop[10]   = { 30,    100,   200,   400,   500,   700,   1100 };
  double stopEff_stop[10] = { .2962, .2656, .2438, .2060, .1949, .1835, .1853 };
  double recoEff_stop[10] = { 0.146, 0.157, 0.170, 0.175, 0.175, 0.175, 0.175 };

  // arrays to fill with data
  double lifetime[100];
  double effLumi[100];
  double expBG[100];
  double expBG_e[100];
  unsigned nObs[100];
  double cl95[100];
  double exp[100];          // expected
  double exp_lo1sig[100];   // lower 1 sigma band
  double exp_hi1sig[100];   // upper 1 sigma band
  double exp_lo2sig[100];   // lower 2 sigma band
  double exp_hi2sig[100];   // upper 2 sigma band
 
  // read data from file
  ifstream file;
  file.open(filename);
  std::string line;
  unsigned count =0 ;

  std::cout << "Using mass point " << massIndex << std::endl;
  std::cout << "  effReco    = " << recoEff[massIndex] << std::endl;
  std::cout << "  effStop    = " << stopEff_cm[massIndex] << std::endl;
  std::cout << "  effStop EM = " << stopEff_em[massIndex] << std::endl;
  std::cout << "  effStop NB = " << stopEff_nb[massIndex] << std::endl;
  
  // read my file if only one filename provided
  if (filename3=="") {

    double t(0.), el(0.), es(0.), b(0.), eb(0.), cl(0.);
    double exmean(0.), lo1sig(0.), hi1sig(0.), lo2sig(0.), hi2sig(0.);
    unsigned n(0);
    std::string z;
    
    while (file >> t >> el >> es >> b >> eb >> n >> cl >> exmean >> lo1sig >> hi1sig >> lo2sig >> hi2sig) {
      lifetime[count] = t;
      effLumi[count]  = el;
      expBG[count]    = b;
      expBG_e[count]  = eb;
      nObs[count]     = n;
      cl95[count]     = cl;
      exp[count]        = exmean;
      exp_lo1sig[count] = lo1sig;
      exp_hi1sig[count] = hi1sig;
      exp_lo2sig[count] = lo2sig;
      exp_hi2sig[count] = hi2sig;
      ++count;
    }
  }
  // read Fedor's & mine if two provided
  else {

    double t(0.), el(0.), l(0.), s(0.), b(0.), eb(0.), cl(0.);
    double exmean(0.), lo1sig(0.), hi1sig(0.), lo2sig(0.), hi2sig(0.);
    unsigned n(0);
    std::string z;
    
    while (file >> z >> z >> t >> z >> el >> z >> b >> z >> n >> z >> cl >>
	   z >> exmean >> z >> z >> z >> z >> z >> z >> z >> z >>
	   z >> lo1sig >> hi1sig >> z >> lo2sig >> hi2sig) {
      lifetime[count] = t;
      expBG[count]    = b;
      expBG_e[count]  = eb;
      nObs[count]     = n;
      cl95[count]     = cl;
      exp[count]        = exmean;
      exp_lo1sig[count] = lo1sig;
      exp_hi1sig[count] = hi1sig;
      exp_lo2sig[count] = lo2sig;
      exp_hi2sig[count] = hi2sig;
      ++count;
    }

    // read effective lumi
    ifstream file3;
    file3.open(filename3);
    while (file3 >> t >> l >> s >> b >> eb >> n >> cl) {
      for (unsigned i=0; i<count; ++i) {
	if (lifetime[i] == t) {
	  effLumi[i] = l;
	}
      }
    }
  }

  std::cout << "Read " << count << " lifetime points for counting experiment" << std::endl;

  // print out to check
  for (unsigned c=0; c<count; ++c) {
    std::cout << lifetime[c] << " " << effLumi[c] << " " << cl95[c] << " " << exp[c] << " " << exp_lo1sig[c] << " " << exp_hi1sig[c] << " " << exp_lo2sig[c] << " " << exp_hi2sig[c] << std::endl;
  }


  // lifetime fit
  double lifetime_tp[100];
  double cl95_tp[100];

  // read data from file
  ifstream file2;
  file2.open(filename2);
  unsigned count2=0 ;
  double ltp(0.), cltp(0.);
    while (file2 >> ltp >> cltp) {
      lifetime_tp[count2] = ltp;
      cl95_tp[count2]     = cltp;
      ++count2;
    }

  std::cout << "Read " << count2 << " lifetime points for time profile fit" << std::endl;


  // convert to cross-section limits
  double xs_cl95[100]; // observed limit
  double xs_cl95_em[100];  // EM only
  double xs_cl95_nb[100];  // neutral baryon
  double xs_cl95_stop[100];  // stop

  double xs_exp[100];          // expected limit
  double xs_exp_lo1sig[100];   // lower 1 sigma band
  double xs_exp_hi1sig[100];   // upper 1 sigma band
  double xs_exp_lo2sig[100];   // lower 2 sigma band
  double xs_exp_hi2sig[100];   // upper 2 sigma band

  double xs_tp[100];

  std::cout << std::endl;

  std::cout << "Lifetime,XSlimit,ExpLimit,-1sigma,+1sigma,-2sigma,+2sigma" << std::endl;
  for (unsigned l=0; l<count; ++l) {

    // observed limits
    xs_cl95[l]      = cl95[l] / (effLumi[l] * stopEff_cm[massIndex] * recoEff[massIndex]);
    xs_cl95_em[l]   = cl95[l] / (effLumi[l] * stopEff_em[massIndex] * recoEff[massIndex]);
    xs_cl95_nb[l]   = cl95[l] / (effLumi[l] * stopEff_nb[massIndex] * recoEff[massIndex]);
    xs_cl95_stop[l] = cl95[l] / (effLumi[l] * stopEff_stop[massIndex] * recoEff_stop[massIndex]);

    // expected limit and bands
    xs_exp[l]        = exp[l] / (effLumi[l] * stopEff_cm[massIndex] * recoEff[massIndex]);
    xs_exp_lo1sig[l] = (exp[l]-exp_lo1sig[l]) / (effLumi[l] * stopEff_cm[massIndex] * recoEff[massIndex]);
    xs_exp_hi1sig[l] = (exp_hi1sig[l]-exp[l]) / (effLumi[l] * stopEff_cm[massIndex] * recoEff[massIndex]);
    xs_exp_lo2sig[l] = (exp[l]-exp_lo2sig[l]) / (effLumi[l] * stopEff_cm[massIndex] * recoEff[massIndex]);
    xs_exp_hi2sig[l] = (exp_hi2sig[l]-exp[l]) / (effLumi[l] * stopEff_cm[massIndex] * recoEff[massIndex]);

    std::cout << lifetime[l] << "," << xs_cl95[l] << "," << xs_exp[l] << "," << xs_exp_lo1sig[l] << "," << xs_exp_hi1sig[l] << "," << xs_exp_lo2sig[l] << "," << xs_exp_hi2sig[l] << std::endl;
  }
  std::cout << std::endl;

  std::cout << "Lifetime, time profile limit" << std::endl;
  for (unsigned i=0; i<13; ++i) {
    xs_tp[i] = cl95_tp[i] / (lumi_tp * stopEff_cm[massIndex] * recoEff[massIndex]);
    std::cout << lifetime_tp[i] << "," << xs_tp[i] << std::endl;
  }

  // graphs - observed
  TGraph* g_cl95    = new TGraph(count, lifetime, xs_cl95);
  TGraph* g_cl95_em = new TGraph(count, lifetime, xs_cl95_em);
  TGraph* g_cl95_nb = new TGraph(count, lifetime, xs_cl95_nb);
  TGraph* g_cl95_stop = new TGraph(count, lifetime, xs_cl95_stop);
  TGraph* g_cl95_tp = new TGraph(13, lifetime_tp, xs_tp);

  // graphs - expected
  TGraph* g_exp = new TGraph(count, lifetime, xs_exp);
  TGraph* g_exp_1sig = new TGraphAsymmErrors(count, lifetime, xs_exp, 0, 0, xs_exp_lo1sig, xs_exp_hi1sig);
  TGraph* g_exp_2sig = new TGraphAsymmErrors(count, lifetime, xs_exp, 0, 0, xs_exp_lo2sig, xs_exp_hi2sig);

  TFile outfile("plots2.root", "RECREATE");


  TCanvas *plot = makeLifetimePlot(g_cl95,
				   g_exp_1sig,
				   g_exp_2sig,
				   g_cl95_em,
				   g_cl95_nb,
				   g_cl95_stop,
				   g_cl95_tp,
				   lumi_tp);
  
  plot->Print("lifetimeLimit.png");
  plot->Print("lifetimeLimit.pdf");
  plot->Print("lifetimeLimit.C");
  plot->Write();
    

  // make basic plot
  double xs1[100];
  double xs2[100];
  for (unsigned l=0; l<count; ++l) {
    xs1[l]    = cl95[l] / (effLumi[l] * recoEff[2]);
    xs2[l]    = cl95[l] / (effLumi[l] * recoEff[3]);
  }

  TGraph* g1    = new TGraph(count, lifetime, xs1);
  TGraph* g2    = new TGraph(count, lifetime, xs2);

  TCanvas *plot2 = makeBasicPlot(g1, g2,lumi_tp);

  plot2->Print("basicLimit.png");
  plot2->Print("basicLimit.pdf");
  plot2->Print("basicLimit.C");
  plot2->Write();
  
  return;

}


// TODO - clean up this method!

TCanvas *makeLifetimePlot(TGraph *g_obs,
			  TGraph *g_exp_1sig,
			  TGraph *g_exp_2sig,
			  TGraph *g_obs_em,
			  TGraph *g_obs_nb,
			  TGraph *g_obs_stop,
			  TGraph *g_obs_tp,
			  double lumi_tp) {

  // expected limit
  TGraph* g_exp = 0;
  if (g_exp_1sig) g_exp = new TGraph(g_exp_1sig->GetN(),g_exp_1sig->GetX(),g_exp_1sig->GetY());

  TCanvas *canvas;
  canvas = new TCanvas("lifetimeLimit");

  //canvas->SetGrid();
  canvas->SetLogx();
  canvas->SetLogy();

  TH1 * h;
  TPaveText *blurb;

  h = canvas->DrawFrame(7.5e-8, .1, 1e6, 5e3);
  //  h->SetTitle("Beamgap Expt;#tau_{#tilde{g}} [s]; #sigma(pp #rightarrow #tilde{g}#tilde{g}) [cm^{2}]");
  h->SetTitle("Beamgap Expt;#tau_{#tilde{g}} [s]; #sigma(pp #rightarrow #tilde{g}#tilde{g}) #times BR(#tilde{g} #rightarrow g#tilde{#chi}^{0}) [pb]");

  blurb = new TPaveText(9e-8, 8e1, 2e-3, 4e3);
  blurb->AddText("CMS Preliminary 2011");
  std::stringstream label;
  label<<"#int L dt = "<<lumi_tp<<" pb^{-1}";
  blurb->AddText(label.str().c_str());
  label.str("");
  // Where do we get max inst value from?
  double peakInstLumi=MAXINSTLUMI;
  int exponent=30;
  while (peakInstLumi>10)
    {
      peakInstLumi/=10;
      ++exponent;
    }
  label<<"L^{max}_{inst} = "<<peakInstLumi<<" x 10^{"<<exponent<<"} cm^{-2}s^{-1}";
  //blurb->AddText("L^{max}_{inst} = 5 x 10^{32} cm^{-2}s^{-1}");
  blurb->AddText(label.str().c_str());
  label.str("");
  blurb->AddText("#sqrt{s} = 7 TeV");
  blurb->AddText("m_{#tilde{g}} - m_{#tilde{#chi}^{0}} = 100 GeV/c^{2}");
  //blurb->AddText("m_{#tilde{g}} = 300 GeV/c^{2}");
  //blurb->AddText("m_{#tilde{#chi}^{0}} = 200 GeV/c^{2}");
  blurb->SetTextFont(42);
  blurb->SetBorderSize(0);
  blurb->SetFillColor(0);
  blurb->SetShadowColor(0);
  blurb->SetTextAlign(12);
  blurb->SetTextSize(0.033);
  blurb->Draw();

  TLegend *leg = new TLegend(2e-3, 8e1 /*4e-30*/, 8e4, 4e3,"95% C.L. Limits:","");
  leg->SetTextSize(0.033);
  leg->SetBorderSize(0);
  leg->SetTextFont(42);
  leg->SetFillColor(0);
  leg->AddEntry(g_exp, "Expected: Counting Exp.", "l");
  leg->AddEntry(g_exp_1sig, "Expected #pm1#sigma: Counting Exp.", "f");
  leg->AddEntry(g_exp_2sig, "Expected #pm2#sigma: Counting Exp.", "f");
  leg->AddEntry(g_obs,     "Obs.: Counting Exp.", "l");
  leg->AddEntry(g_obs_stop,"Obs.: Counting Exp. (#tilde{t})", "l");
  leg->AddEntry(g_obs_nb,  "Obs.: Counting Exp. (Neutral R-Baryon)", "l");
  leg->AddEntry(g_obs_em,  "Obs.: Counting Exp. (EM only)", "l");
  leg->AddEntry(g_obs_tp,  "Obs.: Timing Profile", "l");
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
    //    g_exp_1sig->SetLineColor(8);
    g_exp_1sig->SetLineColor(0);
    g_exp_1sig->SetLineStyle(0);
    g_exp_1sig->SetLineWidth(0);
    //    g_exp_1sig->SetFillColor(8);    
    g_exp_1sig->SetFillColor(kGreen);    
    g_exp_1sig->SetFillStyle(1001);
    //    g_exp_1sig->SetFillStyle(3005);
    g_exp_1sig->Draw("3");
    // g_exp_1sig->Draw("lX");
  }

  //lifetime fit
  if (g_obs_tp) {
    g_obs_tp->SetLineColor(kRed);
    g_obs_tp->SetLineStyle(3);    
    g_obs_tp->SetLineWidth(3);
    g_obs_tp->Draw("l3");
  }  

  // epxected limit
  if (g_exp) {
    g_exp->SetLineColor(1);
    g_exp->SetLineStyle(2);
    g_exp->SetLineWidth(1);
    g_exp->Draw("l");
  }

  TLine *l;
  l = new TLine(7.5e-8, 8.98, 1e6, 8.98); //300 GeV
  //l = new TLine(7.5e-8, 57.2, 1e6, 57.2); //300 GeV
  //l = new TLine(7.5e-8, 606, 1e6, 606); //200 GeV
  //  l = new TLine(1e-8, 3.75e-34, 1e7, 3.75e-34);
  l->SetLineColor(kBlue);
  l->SetLineWidth(1);
  l->Draw();

  //uncertainty band
//   TBox *syst = new TBox(1e-8, 515, 1e7, 697);
//   syst->SetFillStyle(3001);
//   syst->SetFillColor(kBlue-4);
//   syst->Draw();

  TLatex *t1;
  //t1 = new TLatex(1.e2, 70., "NLO+NLL");
  t1 = new TLatex(0.1, 10., "NLO+NLL (m_{#tilde{g}} = 400 GeV/c^{2})");
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
  if (g_obs_nb) {
    g_obs_nb->SetLineColor(kGray+1);
    g_obs_nb->SetLineWidth(2);
    g_obs_nb->SetLineStyle(5);
    g_obs_nb->Draw("l");
  }

  // stop
  if (g_obs_stop) {
    g_obs_stop->SetLineColor(kRed+1);
    g_obs_stop->SetLineWidth(2);
    g_obs_stop->SetLineStyle(5);
    g_obs_stop->Draw("l");
  }


  canvas->RedrawAxis();

  return canvas;

}


TCanvas *makeBasicPlot(TGraph *g1,
		       TGraph* g2,
		       double lumi_tp) {

  TCanvas *canvas;
  canvas = new TCanvas("basicPlot");

  //canvas->SetGrid();
  canvas->SetLogx();
  canvas->SetLogy();

  TH1 * h;
  TPaveText *blurb;

  h = canvas->DrawFrame(7.5e-8, .3, 1e6, 3e1);
  //  h->SetTitle("Beamgap Expt;#tau_{#tilde{g}} [s]; #sigma(pp #rightarrow #tilde{g}#tilde{g}) [cm^{2}]");
  h->SetTitle("Beamgap Expt;#tau_{#tilde{g}} [s]; #sigma(pp #rightarrow #tilde{g}#tilde{g}) #times BR(#tilde{g} #rightarrow g#tilde{#chi}^{0}) #times #varepsilon^{#tilde{g}#tilde{g}}_{stop} [pb]");

  blurb = new TPaveText(1e-6, 3e0, 1e-2, 1e1);
  blurb->AddText("CMS Preliminary 2011");
  std::stringstream label;
  label<<"#int L dt = "<<lumi_tp<<" pb^{-1}";
  blurb->AddText(label.str().c_str());
  label.str("");

  // Where do we get max inst value from?
  double peakInstLumi=MAXINSTLUMI;
  int exponent=30;
  while (peakInstLumi>10)
    {
      peakInstLumi/=10.;
      ++exponent;
    }
  label<<"L^{max}_{inst} = "<<peakInstLumi<<" x 10^{"<<exponent<<"} cm^{-2}s^{-1}";
  blurb->AddText(label.str().c_str());
  label.str("");

  blurb->AddText("#sqrt{s} = 7 TeV");
  blurb->SetTextFont(42);
  blurb->SetBorderSize(0);
  blurb->SetFillColor(0);
  blurb->SetShadowColor(0);
  blurb->SetTextAlign(12);
  blurb->SetTextSize(0.030);
  blurb->Draw();

  TPaveText* cms = new TPaveText(1e-6, 1.5e1, 1e-2, 2e1);
  cms->AddText("CMS 2011");
  cms->SetTextFont(62);
  cms->SetBorderSize(0);
  cms->SetFillColor(0);
  cms->SetShadowColor(0);
  cms->SetTextAlign(12);
  cms->SetTextSize(0.040);
  cms->Draw();


  TLegend *leg = new TLegend(1e-1, 3e0 /*4e-30*/, 1e4, 1e1,"95% C.L. Limits:","");
  leg->SetTextSize(0.030);
  leg->SetBorderSize(0);
  leg->SetTextFont(42);
  leg->SetFillColor(0);
  leg->AddEntry(g1, "m_{#tilde{g}} - m_{#tilde{#chi}^0} = 200 GeV/c^{2}", "l");
  leg->AddEntry(g2, "m_{#tilde{g}} - m_{#tilde{#chi}^0} = 100 GeV/c^{2}", "l");
  leg->Draw();

  g1->SetLineColor(2);
  g1->SetLineStyle(1);
  g1->SetLineWidth(2);
  g1->Draw("l");

  g2->SetLineColor(4);
  g2->SetLineStyle(1);
  g2->SetLineWidth(2);
  g2->Draw("l");


  return canvas;

}
