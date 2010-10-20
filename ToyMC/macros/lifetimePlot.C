
// .L lifetimePlot.C+
// lifetimePlot("limit_summary.txt")

#include <cstdlib>
#include <string.h>
#include <fstream>
#include <iostream> 

#include "TGraph.h"
#include "TGraphAsymmErrors.h"
#include "TCanvas.h"
#include "TFile.h"
#include "TH1.h"
#include "TH1F.h"
#include "TLegend.h"
#include "TPaveText.h"


TCanvas *makeLifetimePlot(TGraph *g_cl95,
			  TGraph *g_exp_1sig=NULL,
			  TGraph *g_exp_2sig=NULL,
			  TGraph *g_cl95_em=NULL,
			  TGraph *g_cl95_nb=NULL,
			  TGraph *g_cl95_tp=NULL);

// filename 1 = counting experiment output
// filename 2 = time profile fit output (if null do not plot curve)
// filename 3 = take limits from Fedors file
void lifetimePlot(char* filename, char* filename2="", char* filename3="") {

  // which mass point ?
  unsigned massIndex = 0;

  // some numbers need to be set buy hand
  double lumi_tp = 3.8;  // lumi figure to use for time-profile fit
  double m_g[10]        = { 200., 300., 400., 500. };
  double m_chi[10]      = { 100., 200., 300., 400. };
  double stopEff_cm[10] = { 0.3749, 0., 0., 0. };  // cloud model
  double stopEff_em[10] = { 0.118, 0., 0., 0. };  // EM only
  double stopEff_nb[10] = { 0.022, 0., 0., 0. };  // neutral baryon
  double recoEff[10] = { 0.194, 0., 0., 0. };
  
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

  // read my file if only one filename provided
  if (strcmp(filename3,"")==0) {

    double t(0.), el(0.), es(0.), b(0.), eb(0.), cl(0.);
    double exmean(0.), lo1sig(0.), hi1sig(0.), lo2sig(0.), hi2sig(0.);
    unsigned n(0);
    std::string z;
    
    while (file >> t >> el >> es >> b >> eb >> n >> cl >> exmean >> lo1sig >> hi1sig >> lo2sig >> hi2sig) {
      std::cout << t << std::endl;
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
  bool doTP=true;
  ifstream file2;
  unsigned count2=0 ;
  double ltp(0.), cltp(0.);

  if (strcmp(filename2,"")!=0) {
    file2.open(filename2);
    
    while (file2 >> ltp >> cltp) {
      lifetime_tp[count2] = ltp;
      cl95_tp[count2]     = cltp;
      ++count2;
    }
  }
  else {
    doTP = false;
  }
  
  std::cout << "Read " << count2 << " lifetime points for time profile fit" << std::endl;


  // convert to cross-section limits
  double xs_cl95[100]; // observed limit
  double xs_cl95_em[100];  // EM only
  double xs_cl95_nb[100];  // neutral baryon

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
    xs_cl95[l]    = cl95[l] / (effLumi[l] * stopEff_cm[massIndex] * recoEff[massIndex]);
    xs_cl95_em[l] = cl95[l] / (effLumi[l] * stopEff_em[massIndex] * recoEff[massIndex]);
    xs_cl95_nb[l] = cl95[l] / (effLumi[l] * stopEff_nb[massIndex] * recoEff[massIndex]);

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
  TGraph* g_cl95_tp = 0;
  if (doTP) g_cl95_tp = new TGraph(13, lifetime_tp, xs_tp);

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
				   g_cl95_tp);
  
  plot->Print("lifetimeLimit.png");
  plot->Print("lifetimeLimit.pdf");
  plot->Print("lifetimeLimit.C");
  plot->Write();
    

  
  return;

}


// TODO - clean up this method!

TCanvas *makeLifetimePlot(TGraph *g_obs,
			  TGraph *g_exp_1sig,
			  TGraph *g_exp_2sig,
			  TGraph *g_obs_em,
			  TGraph *g_obs_nb,
			  TGraph *g_obs_tp) {

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

  h = canvas->DrawFrame(7.5e-8, 3., 1e7, 5e5);
  //  h->SetTitle("Beamgap Expt;#tau_{#tilde{g}} [s]; #sigma(pp #rightarrow #tilde{g}#tilde{g}) [cm^{2}]");
  h->SetTitle("Beamgap Expt;#tau_{#tilde{g}} [s]; #sigma(pp #rightarrow #tilde{g}#tilde{g}) #times BR(#tilde{g} #rightarrow g#tilde{#chi}^{0}) [pb]");

  blurb = new TPaveText(8e-8, 2e3, 2e-3, 3e5);
  blurb->AddText("CMS Preliminary 2010");
  blurb->AddText("#int L dt = 12.9 pb^{-1}");
  blurb->AddText("L^{max}_{inst} = 1 x 10^{32}");
  blurb->AddText("#sqrt{s} = 7 TeV");
  blurb->AddText("m_{#tilde{g}} = 200 GeV");
  blurb->AddText("M_{#tilde{#chi}^{0}} = 100 GeV");
  blurb->SetTextFont(42);
  blurb->SetBorderSize(0);
  blurb->SetFillColor(0);
  blurb->SetShadowColor(0);
  blurb->SetTextAlign(12);
  blurb->SetTextSize(0.030);
  blurb->Draw();

  TLegend *leg = new TLegend(2e-3, 2e3 /*4e-30*/, 8e4, 3e5,"95% C.L. Limits:","");
  leg->SetTextSize(0.030);
  leg->SetBorderSize(0);
  leg->SetTextFont(42);
  leg->SetFillColor(0);
  leg->AddEntry(g_exp, "Expected: Counting Exp.", "l");
  leg->AddEntry(g_exp_1sig, "Expected #pm1#sigma: Counting Exp.", "f");
  leg->AddEntry(g_exp_2sig, "Expected #pm2#sigma: Counting Exp.", "f");
  leg->AddEntry(g_obs, "Obs.: Counting Exp.", "l");
  leg->AddEntry(g_obs_nb, "Obs.: Counting Exp. - Neutral R-Baryon", "l");
  leg->AddEntry(g_obs_em, "Obs.: Counting Exp. - EM Interactions", "l");
  leg->AddEntry(g_obs_tp, "Obs.: Timing Profile", "l");
  leg->Draw();

  // D0 covered region  
  TLine *nc = new TLine(30.e-6,8.5e-2,1.08e6,8.5e-2);
  TLine *nc1 = new TLine(30.e-6,8.5e-2,30.e-6,1.5e-1);
  TLine *nc2 = new TLine(1.08e6,8.5e-2,1.08e6,1.5e-1);
  //TBox *nc = new TBox(30e-6, 8e-2, 1.08e6, 1e6);
  //nc->SetFillStyle(3003);
  //nc->SetFillColor(kRed-4);
  nc->SetLineColor(kRed-4);
  nc->SetLineWidth(2);
  nc1->SetLineColor(kRed-4);
  nc1->SetLineWidth(2);
  nc2->SetLineColor(kRed-4);
  nc2->SetLineWidth(2);
//   nc->Draw();
//   nc1->Draw();
//   nc2->Draw();

  // D0 label 
  TText d0(1e-3, 1.1e-1, "D0 exclusion region: Phys. Rev. Lett. 99, 131801 (2007)");
  d0.SetTextColor(kRed+1);
  d0.SetTextFont(42);
  d0.SetTextSize(0.025);
  d0.Draw();


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
  l = new TLine(7.5e-8, 606, 1e7, 606);
  //  l = new TLine(1e-8, 3.75e-34, 1e7, 3.75e-34);
  l->SetLineColor(kBlue);
  l->SetLineWidth(1);
  l->Draw();

  //uncertainty band
//   TBox *syst = new TBox(1e-8, 515, 1e7, 697);
//   syst->SetFillStyle(3001);
//   syst->SetFillColor(kBlue-4);
//   syst->Draw();

  TText *t1;
  t1 = new TText(1.e2, 650., "NLO+NLL");
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

  return canvas;

}
