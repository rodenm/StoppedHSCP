// .L massPlot.C+
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

// .L massPlot.C+
// massPlot("limit_summary.txt", "time_profile_summary.txt");

void massPlot(char* filename, char* filename2) {
  // .X massPlot.C

  // stuff that has to be set by hand
  // some numbers need to be set buy hand
  double lumi_tp = 38.0;  // lumi figure to use for time-profile fit

  // set which bin to use for intercept calculation (mass limit)
  unsigned theoryBin = 4;
  unsigned dataBin = 3;

  unsigned point1 = 9;
  unsigned point2 = 27;
  unsigned point3 = 43;
  unsigned pointtp = 9;

  unsigned nmasses=5;
  double mass[10] = {
    150.,
    200.,
    300.,
    400.,
    500.,
    600.,
    900.
  };
  
  
  double recoEff[10] = {
    0.146,
    0.157,
    0.170,
    0.175,  
    0.175,   
    0.,
    0.
  };
  
  double stopEff[10] = {
    0.217 * 2.,
    0.198 * 2.,
    0.205 * 2.,
    0.207 * 2.,
    0.209 * 2.,
    0.216 * 2.,
    0.255 * 2.
  };

  double stopEffEm[10] = {
	0.0622 * 2.,
	0.0591 * 2.,
	0.0596 * 2.,
	0.0601 * 2.,
	0.0634 * 2.
  };

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
  
  double excXS_EM[10];

  double excXSL[10];
  
  for (unsigned im=0; im<nmasses; ++im) {
    excXS_exp[im]   = exp[point2] / (effLumi[point2] * stopEff[im] * recoEff[im]);
    excXS_exp1m[im] = (exp[point2]-exp_lo1sig[point2]) / (effLumi[point2] * stopEff[im] * recoEff[im]);
    excXS_exp1p[im] = (exp_hi1sig[point2]-exp[point2]) / (effLumi[point2] * stopEff[im] * recoEff[im]);
    excXS_exp2m[im] = (exp[point2]-exp_lo2sig[point2]) / (effLumi[point2] * stopEff[im] * recoEff[im]);
    excXS_exp2p[im] = (exp_hi2sig[point2]-exp[point2]) / (effLumi[point2] * stopEff[im] * recoEff[im]);
    excXS1[im]= cl95[point1] / (effLumi[point1] * stopEff[im] * recoEff[im]);
    excXS2[im]= cl95[point2] / (effLumi[point2] * stopEff[im] * recoEff[im]);
    excXS3[im]= cl95[point3] / (effLumi[point3] * stopEff[im] * recoEff[im]);
	excXS_EM[im] = cl95[point2] / (effLumi[point2] * stopEffEm[im] * recoEff[im]);
    excXSL[im]= cl95_tp[pointtp] / (lumi_tp * stopEff[im] * recoEff[im]);
  }
  
  
  // theoretical cross-section  (pb)
  unsigned ntheory = 6;
  double theoryUncertainty = 0.0;
  double theoryXS[10] = {
    2.11e4,
    2.82e3,
    6.06e2,
    5.72e1,
    8.98e0,
    1.87e0,
    4.65e-1,
    1.30e-1,
    3.96e-2,
    1.28e-2
  };
  
  double theoryBand[10];
  for (unsigned i=0; i<10; ++i) {
    theoryBand[i] = theoryUncertainty*theoryXS[i];
  }
  
  double theoryMass[10] = { 100., 150., 200., 300., 400., 500., 600., 700., 800., 900. };
  
  
  // plotting below
  
  // expected limit (1 and 2 sigma bands)
  TGraph* graph_exp = new TGraph(nmasses, mass, excXS_exp);
  TGraphAsymmErrors* graph_exp1 = new TGraphAsymmErrors(nmasses, mass, excXS_exp, 0, 0, excXS_exp1m, excXS_exp1p);
  TGraphAsymmErrors* graph_exp2 = new TGraphAsymmErrors(nmasses, mass, excXS_exp, 0, 0, excXS_exp2m, excXS_exp2p);
  
  // three points on counting expt curve
  TGraph* graph1 = new TGraph(nmasses, mass, excXS1);
  TGraph* graph2 = new TGraph(nmasses, mass, excXS2);
  TGraph* graph3 = new TGraph(nmasses, mass, excXS3);
  TGraph* graphEM = new TGraph(nmasses, mass, excXS_EM);
  
  // one point from lifetime fit
  TGraph* graphL = new TGraph(nmasses, mass, excXSL);
  
  // theory prediction
  TGraph* theory = new TGraphErrors(ntheory, theoryMass, theoryXS, 0, theoryBand);
  
  TCanvas* canvas = new TCanvas("canvas");
  
  //canvas->SetGrid();
  canvas->SetLogy();
  
  TH1 * h;
  h = canvas->DrawFrame(100., .5, 500., 5e3);
  h->SetTitle("Beamgap Expt;m_{#tilde{g}} [GeV/c^{2}]; #sigma(pp #rightarrow #tilde{g}#tilde{g}) #times BR(#tilde{g} #rightarrow g#tilde{#chi}^{0}) [pb]");
  
  // not covered region
  TBox* nc = new TBox(100., .5, 150., 5e3);
  nc->SetFillStyle(3354);
  nc->SetFillColor(kRed-4);
  nc->Draw();
  
  // details
  TPaveText* blurb = new TPaveText(101., 1.e2, 220., 4.5e3);
  //blurb->AddText("CMS Preliminary 2010");
  blurb->AddText("#int L dt = 38 pb^{-1}");
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
  TLegend *leg = new TLegend(220., 1.e2, 480., 4e3,"95% C.L. Limits","");
  leg->SetTextSize(0.032);
  leg->SetBorderSize(0);
  leg->SetTextFont(42);
  leg->SetFillColor(0);
  leg->AddEntry(graph_exp, "Expected: 10 #mus - 1000 s Counting Exp.", "l");
  leg->AddEntry(graph_exp1, "Expected #pm1#sigma: 10 #mus - 1000 s Counting Exp.", "f");
  leg->AddEntry(graph_exp2, "Expected #pm2#sigma: 10 #mus - 1000 s Counting Exp.", "f");
//  leg->AddEntry(graph3, "Obs.: 10^{6} s Counting Exp.", "l");
  leg->AddEntry(graphEM, "Obs.: 10 #mus - 1000 s Counting Exp. (EM only)", "l");
  leg->AddEntry(graph2, "Obs.: 10 #mus - 1000 s Counting Exp.", "l");
  //  leg->AddEntry(graph1, "Obs.: 570 ns Counting Exp.", "l");
  leg->AddEntry(graphL, "Obs.: 10 #mus Timing Profile", "l");
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
  
  // EM curve
  graphEM->SetLineColor(kGray+1);
  graphEM->SetLineStyle(5);
graphEM->SetLineWidth(2);
graphEM->Draw("l");

  // 1 mus lifetime fit limit
  graphL->SetLineColor(kRed);
  graphL->SetLineStyle(3);
  graphL->SetLineWidth(3);
  graphL->Draw("l");
  
  // theory line
  theory->SetLineColor(kBlue);
  theory->SetLineStyle(1);
  theory->SetLineWidth(2);
  theory->SetFillStyle(3001);
  theory->SetFillColor(kBlue-4);
  theory->Draw("l3");
  
  // theory line label
  TText* th = new TText(290., 80., "NLO+NLL");
  th->SetTextColor(kBlue);
  th->SetTextFont(42);
  th->SetTextSize(0.035);
  th->Draw();

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
  double mexp = ( log10(excXS_exp[dataBin+1]) - log10(excXS_exp[dataBin]) ) / (mass[dataBin+1]-mass[dataBin]);
  double cexp = log10(excXS_exp[dataBin+1]) - (mexp*mass[dataBin+1]);

  // plateau limit
  double mobs = ( log10(excXS2[dataBin+1]) - log10(excXS2[dataBin]) ) / (mass[dataBin+1]-mass[dataBin]);
  double cobs = log10(excXS2[dataBin+1]) - (mobs*mass[dataBin+1]);

  // EM limit
  double mem = ( log10(excXS_EM[dataBin+1]) - log10(excXS_EM[dataBin]) ) / (mass[dataBin+1]-mass[dataBin]);
  double cem = log10(excXS_EM[dataBin+1]) - (mem*mass[dataBin+1]);

  // time profile limit
  double tpml = (log10(excXSL[dataBin+1])-log10(excXSL[dataBin])) / (mass[dataBin+1]-mass[dataBin]);
  double tpcl = log10(excXSL[dataBin+1]) - (tpml*mass[dataBin+1]);

  double massLimit_exp = (cexp - ct) / (mt - mexp);
  double massLimit_obs = (cobs - ct) / (mt - mobs);
  double massLimit_EM = (cem - ct) / (mt - mem);
  double massLimit_TP = (tpcl - ct) / (mt - tpml);

  cout << "Mass limit - counting expt expected = " << massLimit_exp << endl;
  cout << "Mass limit - counting expt observed = " << massLimit_obs << endl;
  cout << "Mass limit - counting expt obs (EM) = " << massLimit_EM << endl;
  cout << "Mass limit - time profile           = " << massLimit_TP << endl;

  
}

