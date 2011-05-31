/// .L massPlot.C+
// lifetimePlot("limit_summary.txt", "time_profile_summary.txt")

#include <cstdlib>
#include <fstream>
#include <iostream> 

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

// .L massPlot.C+
// massPlot("limit_summary.txt", "time_profile_summary.txt");

void massPlot(char* filename, char* filename2) {
  // .X massPlot.C

  // stuff that has to be set by hand
  // some numbers need to be set buy hand
  double lumi_tp = 132.0;  // lumi figure to use for time-profile fit

  // set which bin to use for intercept calculation (mass limit)
  unsigned theoryBin = 5;
  unsigned dataBin = 4;

  unsigned point1 = 9;    // short lifetime
  unsigned point2 = 39;   // plateau
  unsigned point3 = 43;   // long lifetime
  unsigned pointtp = 9;   // time profile

  unsigned nGluino=7;

  double m_g[10]        = { 150.,     200.,      300.,      400.,      500.,     600.,    900. };
  double m_chi[10]      = { 50.,      100.,      200.,      300.,      400.,     500.,    800. };
  double stopEff_cm[10] = { 0.219*2., 0.198*2.,  0.205*2.,  0.207*2.,  0.209*2., 0.216*2, 0.255*2 };  // cloud model
  double stopEff_em[10] = { 0.062*2., 0.0591*2., 0.0596*2., 0.0601*2., 0.0634*2. };  // EM only
  double stopEff_nb[10] = { 0.120*2., 0.0115*2., 0.0128*2., 0.0141*2., 0.0147*2. };  // neutral baryon
  double recoEff[10]    = { 0.146,    0.157,     0.170,     0.175,     0.175,    0.175,   0.175 };
 
  unsigned nStop          = 7;
  double m_stop[10]       = { 130,   200,   300,   500,   600,   800,   1200 };
  double m_chi_stop[10]   = { 30,    100,   200,   400,   500,   700,   1100 };
  double stopEff_stop[10] = { .2962, .2656, .2438, .2060, .1949, .1835, .1853 };
  double recoEff_stop[10] = { 0.146, 0.157, 0.170, 0.175, 0.175, 0.175, 0.175 };

  unsigned nTheory = 10;
  double theoryUncertainty = 0.0;
  double theoryMass[10] = { 100.,   150.,   200.,   300.,   400.,   500.,   600.,    700.,    800.,    900. };
  double theoryXS[10]   = { 2.11e4, 2.82e3, 6.06e2, 5.72e1, 8.98e0, 1.87e0, 4.65e-1, 1.30e-1, 3.96e-2, 1.28e-2 };
  
  unsigned nTheory_stop = 4;
  double theoryMass_stop[10] = { 100., 400.,    600.,    1000. };
  double theoryXS_stop[10]   = { 423., 2.18E-1, 1.30E-2, 1.31E-4 };


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

  // read file
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

  std::cout << "Read " << count << " lifetime points for counting experiment" << std::endl;
  std::cout << "  going to use lifetimes " << lifetime[point1] << ", " << lifetime[point2] << ", " << lifetime[point3] << std::endl;

//   // print out to check
//   for (unsigned c=0; c<count; ++c) {
//     std::cout << lifetime[c] << " " << effLumi[c] << " " << cl95[c] << " " << exp[c] << " " << exp_lo1sig[c] << " " << exp_hi1sig[c] << " " << exp_lo2sig[c] << " " << exp_hi2sig[c] << std::endl;
//   }

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
  std::cout << "  going to use lifetimes " << lifetime_tp[pointtp] << std::endl;
  
  double excXS_exp[10];
  double excXS_exp1m[10];
  double excXS_exp1p[10];
  double excXS_exp2m[10];
  double excXS_exp2p[10];
  
  double excXS1[10];
  double excXS2[10];
  double excXS3[10];
  
  double excXS_em[10];
  double excXS_tp[10];
  double excXS_stop[10];
  
  for (unsigned im=0; im<nGluino; ++im) {
    excXS_exp[im]   = exp[point2] / (effLumi[point2] * stopEff_cm[im] * recoEff[im]);
    excXS_exp1m[im] = (exp[point2]-exp_lo1sig[point2]) / (effLumi[point2] * stopEff_cm[im] * recoEff[im]);
    excXS_exp1p[im] = (exp_hi1sig[point2]-exp[point2]) / (effLumi[point2] * stopEff_cm[im] * recoEff[im]);
    excXS_exp2m[im] = (exp[point2]-exp_lo2sig[point2]) / (effLumi[point2] * stopEff_cm[im] * recoEff[im]);
    excXS_exp2p[im] = (exp_hi2sig[point2]-exp[point2]) / (effLumi[point2] * stopEff_cm[im] * recoEff[im]);
    excXS1[im]= cl95[point1] / (effLumi[point1] * stopEff_cm[im] * recoEff[im]);
    excXS2[im]= cl95[point2] / (effLumi[point2] * stopEff_cm[im] * recoEff[im]);
    excXS3[im]= cl95[point3] / (effLumi[point3] * stopEff_cm[im] * recoEff[im]);
    excXS_em[im] = cl95[point2] / (effLumi[point2] * stopEff_em[im] * recoEff[im]);
    excXS_tp[im]= cl95_tp[pointtp] / (lumi_tp * stopEff_cm[im] * recoEff[im]);
  }

  for (unsigned im=0; im<nStop; ++im) {
    excXS_stop[im] = cl95[point2] / (effLumi[point2] * stopEff_stop[im] * recoEff_stop[im]);
  }
  
  // theoretical cross-section  (pb)
  double theoryBand[10];
  for (unsigned i=0; i<nTheory; ++i) {
    theoryBand[i] = theoryUncertainty*theoryXS[i];
  }
  
  double theoryBand_stop[10];
  for (unsigned i=0; i<nTheory_stop; ++i) {
    theoryBand_stop[i] = theoryUncertainty*theoryXS_stop[i];
  }  
  
  // plotting below
  
  // expected limit (1 and 2 sigma bands)
  TGraph* graph_exp = new TGraph(nGluino, m_g, excXS_exp);
  TGraphAsymmErrors* graph_exp1 = new TGraphAsymmErrors(nGluino, m_g, excXS_exp, 0, 0, excXS_exp1m, excXS_exp1p);
  TGraphAsymmErrors* graph_exp2 = new TGraphAsymmErrors(nGluino, m_g, excXS_exp, 0, 0, excXS_exp2m, excXS_exp2p);
  
  // three points on counting expt curve
  TGraph* graph1 = new TGraph(nGluino, m_g, excXS1);
  TGraph* graph2 = new TGraph(nGluino, m_g, excXS2);
  TGraph* graph3 = new TGraph(nGluino, m_g, excXS3);
  TGraph* graph_em = new TGraph(nGluino, m_g, excXS_em);
  TGraph* graph_stop = new TGraph(nStop, m_stop, excXS_stop);
  
  // one point from lifetime fit
  TGraph* graph_tp = new TGraph(nGluino, m_g, excXS_tp);
  
  // theory prediction
  TGraph* theory = new TGraphErrors(nTheory, theoryMass, theoryXS, 0, theoryBand);
  TGraph* theory_stop = new TGraphErrors(nTheory_stop, theoryMass_stop, theoryXS_stop, 0, theoryBand_stop);
  
  TCanvas* canvas = new TCanvas("canvas");
  
  //canvas->SetGrid();
  canvas->SetLogy();
  
  TH1 * h;
  h = canvas->DrawFrame(100., .1, 900., 5e2);
  h->SetTitle("Beamgap Expt;m_{#tilde{g}} [GeV/c^{2}]; #sigma(pp #rightarrow #tilde{g}#tilde{g}) #times BR(#tilde{g} #rightarrow g#tilde{#chi}^{0}) [pb]");
  
  // not covered region
  TBox* nc = new TBox(100., .1, 150., 5e2);
  nc->SetFillStyle(3354);
  nc->SetFillColor(kRed-4);
  nc->Draw();
  
  // details
  TPaveText* blurb = new TPaveText(110., 1.e1, 350., 4.5e2);
  //blurb->AddText("CMS Preliminary 2010");
  blurb->AddText("#int L dt = 132 pb^{-1}");
  blurb->AddText("L^{max}_{inst} = 5 x 10^{32} cm^{-2}s^{-1}");
  blurb->AddText("#sqrt{s} = 7 TeV");
  blurb->AddText("m_{#tilde{g}} - m_{#tilde{#chi}^{0}} = 100 GeV/c^{2}");
  blurb->SetTextFont(42);
  blurb->SetBorderSize(0);
  blurb->SetFillColor(0);
  blurb->SetShadowColor(0);
  blurb->SetTextAlign(12);
  blurb->SetTextSize(0.034);

  
  // legend
  TBox *legbg = new TBox(350., 1.e1, 850., 4e2);
  legbg->Draw();
  TLegend *leg = new TLegend(350., 1.e1, 850., 4e2,"95% C.L. Limits","");
  leg->SetTextSize(0.032);
  leg->SetBorderSize(0);
  leg->SetTextFont(42);
  leg->SetFillColor(0);
  leg->AddEntry(graph_exp, "Expected: 10 #mus - 1000 s Counting Exp.", "l");
  leg->AddEntry(graph_exp1, "Expected #pm1#sigma: 10 #mus - 1000 s Counting Exp.", "f");
  leg->AddEntry(graph_exp2, "Expected #pm2#sigma: 10 #mus - 1000 s Counting Exp.", "f");
//  leg->AddEntry(graph3, "Obs.: 10^{6} s Counting Exp.", "l");
  leg->AddEntry(graph2, "Obs.: 10 #mus - 1000 s Counting Exp.", "l");
  leg->AddEntry(graph_stop, "Obs.: 10 #mus - 1000 s Counting Exp. (#tilde{t})", "l");
  leg->AddEntry(graph_em, "Obs.: 10 #mus - 1000 s Counting Exp. (EM only)", "l");
  //  leg->AddEntry(graph1, "Obs.: 570 ns Counting Exp.", "l");
  leg->AddEntry(graph_tp, "Obs.: 10 #mus Timing Profile", "l");
  leg->Draw();
  
  
  
  // 2 sigma expected band
  graph_exp2->SetLineColor(0);
  graph_exp2->SetLineStyle(0);
  graph_exp2->SetLineWidth(0);
  graph_exp2->SetFillColor(5);
  graph_exp2->SetFillStyle(1001);
  graph_exp2->Draw("3");
  
  // 1 sigma expected band
  graph_exp1->SetLineColor(0);
  graph_exp1->SetLineStyle(0);
  graph_exp1->SetLineWidth(0);
  graph_exp1->SetFillColor(3);
  graph_exp1->SetFillStyle(1001);
  graph_exp1->Draw("3");  
  
  // expected line
  graph_exp->SetLineStyle(2);
  graph_exp->SetLineWidth(1);
  graph_exp->Draw("l");
  
  // best limit - 580 ns
  graph1->SetLineColor(kGray+2);
  graph1->SetLineStyle(5);
  graph1->SetLineWidth(2);
  //  graph1->Draw("l");
  
  // plateau limit - 1 ms
  graph2->SetLineColor(1);
  graph2->SetLineStyle(1);
  graph2->SetLineWidth(2);
  graph2->Draw("l");
  
  // 11 day limit
//  graph3->SetLineColor(kGray+1);
//  graph3->SetLineStyle(5);
//  graph3->SetLineWidth(2);
//  graph3->Draw("l");

   // stop curve
  graph_stop->SetLineColor(kRed+1);
  graph_stop->SetLineStyle(5);
  graph_stop->SetLineWidth(2);
  graph_stop->Draw("l");
 
  // EM curve
  graph_em->SetLineColor(kGray+1);
  graph_em->SetLineStyle(5);
  graph_em->SetLineWidth(2);
  //  graphEM->Draw("l");

  // 1 mus lifetime fit limit
  graph_tp->SetLineColor(kRed);
  graph_tp->SetLineStyle(3);
  graph_tp->SetLineWidth(3);
  graph_tp->Draw("l");
  
  // theory line
  theory->SetLineColor(kBlue);
  theory->SetLineStyle(1);
  theory->SetLineWidth(2);
  theory->SetFillStyle(3001);
  theory->SetFillColor(kBlue-4);
  theory->Draw("l3");
  
  theory_stop->SetLineColor(kRed);
  theory_stop->SetLineStyle(1);
  theory_stop->SetLineWidth(2);
  theory_stop->SetFillStyle(3001);
  theory_stop->SetFillColor(kRed-4);
  theory_stop->Draw("l3");


  // theory line label
  TLatex* th = new TLatex(520., 0.2, "NLO+NLL #tilde{g}");
  th->SetTextColor(kBlue);
  th->SetTextFont(42);
  th->SetTextSize(0.035);
  th->Draw();

  TLatex* ths = new TLatex(270., 0.2, "NLO+NLL #tilde{t}");
  ths->SetTextColor(kRed);
  ths->SetTextFont(42);
  ths->SetTextSize(0.035);
  ths->Draw();

  // not explored label
  TText* ne = new TText(115., 11., "Not Sensitive");
  ne->SetTextColor(kRed+1);
  ne->SetTextFont(42);
  ne->SetTextAngle(66);
  ne->SetTextSize(0.035);
  ne->Draw();

  blurb->Draw();

  canvas->RedrawAxis();

  canvas->Print("massLimit.pdf");
  canvas->Print("massLimit.C");

  // calculate intercept
  double mt = ( log10(theoryXS[theoryBin+1]-theoryBand[theoryBin+1]) - log10(theoryXS[theoryBin]-theoryBand[theoryBin]) ) / (theoryMass[theoryBin+1]-theoryMass[theoryBin]);
  double ct = log10(theoryXS[theoryBin+1]-theoryBand[theoryBin+1]) - (mt*theoryMass[theoryBin+1]);

  // expected limit
  double mexp = ( log10(excXS_exp[dataBin+1]) - log10(excXS_exp[dataBin]) ) / (m_g[dataBin+1]-m_g[dataBin]);
  double cexp = log10(excXS_exp[dataBin+1]) - (mexp*m_g[dataBin+1]);

  // plateau limit
  double mobs = ( log10(excXS2[dataBin+1]) - log10(excXS2[dataBin]) ) / (m_g[dataBin+1]-m_g[dataBin]);
  double cobs = log10(excXS2[dataBin+1]) - (mobs*m_g[dataBin+1]);

  // EM limit
  double mem = ( log10(excXS_em[dataBin+1]) - log10(excXS_em[dataBin]) ) / (m_g[dataBin+1]-m_g[dataBin]);
  double cem = log10(excXS_em[dataBin+1]) - (mem*m_g[dataBin+1]);

  // time profile limit
  double tpml = (log10(excXS_tp[dataBin+1])-log10(excXS_tp[dataBin])) / (m_g[dataBin+1]-m_g[dataBin]);
  double tpcl = log10(excXS_tp[dataBin+1]) - (tpml*m_g[dataBin+1]);

  double massLimit_exp = (cexp - ct) / (mt - mexp);
  double massLimit_obs = (cobs - ct) / (mt - mobs);
  double massLimit_EM = (cem - ct) / (mt - mem);
  double massLimit_TP = (tpcl - ct) / (mt - tpml);

  cout << "Mass limit - counting expt expected = " << massLimit_exp << endl;
  cout << "Mass limit - counting expt observed = " << massLimit_obs << endl;
  cout << "Mass limit - counting expt obs (EM) = " << massLimit_EM << endl;
  cout << "Mass limit - time profile           = " << massLimit_TP << endl;

  
}

