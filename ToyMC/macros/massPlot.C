{

  // plot expected limit for 1e-3s counting expt; plateau
  double exp_effLumi= 1.06116;
  double exp_mean   = 8.274;  // mean
  double exp_1qtm   = 4.826;  // 68% quantile
  double exp_1qtp   = 10.996;
  double exp_2qtm   = 3.586;
  double exp_2qtp   = 15.983;
  
  // best observed limit - 5.8e-7 s
  double effLumi_1 = 0.844145;
  double cl95_1    = 3.879;
  
  // plateau observed limit - 1e-3 s
  double effLumi_2 = 1.06116;
  double cl95_2    = 6.05011;
  
  // long lifetime observed limit - 1e6 s
  double effLumi_3 =  0.0916525;
  double cl95_3    = 6.05011;
  
  // 1e6 s from lifetime fit
  double Lrec   = 1.3;    // integrated lumi for lifetime fit
  double cl95_L = 6.48722;
  
  
  // reco efficiency by mass
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
    0.160,
    0.172,
    0.187,
    0.187,  
    0.181,   
    0.184,
    0.184
  };
  
  double stopEff[10] = {
    0.217 * 2.,
    0.188 * 2.,
    0.205 * 2.,
    0.207 * 2.,
    0.209 * 2.,
    0.216 * 2.,
    0.255 * 2.
  };
  
  double excXS_exp[10];
  double excXS_exp1m[10];
  double excXS_exp1p[10];
  double excXS_exp2m[10];
  double excXS_exp2p[10];
  
  double excXS1[10];
  double excXS2[10];
  double excXS3[10];
  
  double excXSL[10];
  
  for (unsigned im=0; im<nmasses; ++im) {
    excXS_exp[im]   = exp_mean / (exp_effLumi * stopEff[im] * recoEff[im]);
    excXS_exp1m[im] = (exp_mean-exp_1qtm) / (exp_effLumi * stopEff[im] * recoEff[im]);
    excXS_exp1p[im] = (exp_1qtp-exp_mean) / (exp_effLumi * stopEff[im] * recoEff[im]);
    excXS_exp2m[im] = (exp_mean-exp_2qtm) / (exp_effLumi * stopEff[im] * recoEff[im]);
    excXS_exp2p[im] = (exp_2qtp-exp_mean) / (exp_effLumi * stopEff[im] * recoEff[im]);
    excXS1[im]= cl95_1 / (effLumi_1 * stopEff[im] * recoEff[im]);
    excXS2[im]= cl95_2 / (effLumi_2 * stopEff[im] * recoEff[im]);
    excXS3[im]= cl95_3 / (effLumi_3 * stopEff[im] * recoEff[im]);
    excXSL[im]= cl95_L / (Lrec * stopEff[im] * recoEff[im]);
  }
  
  
  // theoretical cross-section  (pb)
  unsigned ntheory = 5;
  double theoryUncertainty = 0.15;
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
  
  // one point from lifetime fit
  TGraph* graphL = new TGraph(nmasses, mass, excXSL);
  
  // theory prediction
  TGraph* theory = new TGraphErrors(ntheory, theoryMass, theoryXS, 0, theoryBand);
  
  TCanvas* canvas = new TCanvas("canvas");
  
  //canvas->SetGrid();
  canvas->SetLogy();
  
  TH1 * h;
  TPaveText *blurb;
  h = canvas->DrawFrame(100., 10, 500., 1e5);
  h->SetTitle("Beamgap Expt;m_{#tilde{g}} [GeV]; #sigma(pp #rightarrow #tilde{g}#tilde{g}) #times BR(#tilde{g} #rightarrow g#tilde{#chi}^{0}) [pb]");
  
  // not covered region
  TBox nc(100., 10, 150., 1e5);
  nc->SetFillStyle(3354);
  nc->SetFillColor(kRed-4);
  nc->Draw();
  
  // details
  TPaveText* blurb = new TPaveText(110., 1.e3, 250., 8.e4);
  blurb->AddText("CMS Preliminary 2010");
  blurb->AddText("#int L dt = 1.3 pb^{-1}");
  blurb->AddText("#sqrt{s} = 7 TeV");
  //  blurb->AddText("Fills 1121,1122");
  //  blurb->AddText("t_{data} = 60 days");
  //  blurb->AddText("m_{#tilde{g}} = 200 GeV");
  blurb->AddText("m_{#tilde{g}} - M_{#tilde{#chi}^{0}} = 100 GeV");
  //blurb->AddText("Beam: 8hr on / 16hr off");
  blurb->SetTextFont(42);
  blurb->SetBorderSize(0);
  blurb->SetFillColor(0);
  blurb->SetShadowColor(0);
  blurb->SetTextAlign(12);
  blurb->SetTextSize(0.030);

  
  // legend
  TLegend *leg = new TLegend(260., 1.e3, 480., 8.e4,"95% C.L. Limits","");
  leg->SetTextSize(0.035);
  leg->SetBorderSize(0);
  leg->SetTextFont(42);
  leg->SetFillColor(0);
  //leg->AddEntry(graph_exp, "95% C.L. Limits", "");
  leg->AddEntry(graph_exp, "Expected: 100 #mus - 1 hr Counting Exp.", "l");
  leg->AddEntry(graph_exp1, "Expected #pm1#sigma: 100 #mus - 1 hr Counting Exp.", "f");
  leg->AddEntry(graph_exp2, "Expected #pm2#sigma: 100 #mus - 1 hr Counting Exp.", "f");
  leg->AddEntry(graph3, "Obs.: 10^{6} s Counting Exp.", "l");
  leg->AddEntry(graph2, "Obs.: 100 #mus - 1 hr Counting Exp.", "l");
  leg->AddEntry(graph1, "Obs.: 580 ns Counting Exp.", "l");
  leg->AddEntry(graphL, "Obs.: 100 ns Timing Profile", "l");
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
  //graph_exp1->Draw("lX");
  
  
  // expected line
  graph_exp->SetLineStyle(2);
  graph_exp->SetLineWidth(1);
  graph_exp->Draw("l");
  
  // best limit - 580 ns
  graph1->SetLineColor(kGray+2);
  graph1->SetLineStyle(5);
  graph1->SetLineWidth(2);
  graph1->Draw("l");
  
  // plateau limit - 1 ms
  graph2->SetLineColor(1);
  graph2->SetLineStyle(1);
  graph2->SetLineWidth(2);
  graph2->Draw("l");
  
  // 11 day limit
  graph3->SetLineColor(kGray+1);
  graph3->SetLineStyle(5);
  graph3->SetLineWidth(2);
  graph3->Draw("l");
  
  // 1 mus lifetime fit limit
  //   graphL->SetLineColor(kBlue);
  //   graphL->SetLineStyle(3);
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
  th = new TText(290., 1.e-1, "NLO+NLL");
  th->SetTextColor(kBlue);
  th->SetTextFont(42);
  th->SetTextSize(0.035);
  th->Draw();

  // not explored label
  ne = new TText(115., 1.1e-1, "Not Sensitive");
  ne->SetTextColor(kRed+1);
  ne->SetTextFont(42);
  ne->SetTextAngle(66);
  ne->SetTextSize(0.035);
  ne->Draw();

  blurb->Draw();

  canvas->Print("massPlot.pdf");
  canvas->Print("massPlot.C");

  // calculate intercept
  // set which bin to use
  unsigned theoryBin = 2;
  unsigned dataBin = 1;

  double mt = ( log10(theoryXS[theoryBin+1]-theoryBand[theoryBin+1]) - log10(theoryXS[theoryBin]-theoryBand[theoryBin]) ) / (theoryMass[theoryBin+1]-theoryMass[theoryBin]);
  double ct = log10(theoryXS[theoryBin+1]-theoryBand[theoryBin+1]) - (mt*theoryMass[theoryBin+1]);

  // expected limit
  double mexp = ( log10(excXS_exp[dataBin+1]) - log10(excXS_exp[dataBin]) ) / (mass[dataBin+1]-mass[dataBin]);
  double cexp = log10(excXS_exp[dataBin+1]) - (mexp*mass[dataBin+1]);

  // best limit
  double m1 = ( log10(excXS1[dataBin+1]) - log10(excXS1[dataBin]) ) / (mass[dataBin+1]-mass[dataBin]);
  double c1 = log10(excXS1[dataBin+1]) - (m1*mass[dataBin+1]);

  // plateau limit
  double m2 = ( log10(excXS2[dataBin+1]) - log10(excXS2[dataBin]) ) / (mass[dataBin+1]-mass[dataBin]);
  double c2 = log10(excXS2[dataBin+1]) - (m2*mass[dataBin+1]);

  // time profile limit
  double ml = (log10(excXSL[dataBin+1])-log10(excXSL[dataBin])) / (mass[dataBin+1]-mass[dataBin]);
  double cl = log10(excXSL[dataBin+1]) - (ml*mass[dataBin+1]);

  double mass_excexp = (cexp - ct) / (mt - mexp);
  double mass_exc1 = (c1 - ct) / (mt - m1);
  double mass_exc2 = (c2 - ct) / (mt - m2);
  double mass_excL = (cl - ct) / (mt - ml);

  cout << "Expected excluded mass (counting expt) = " << mass_excexp << endl;
  cout << "Best excluded mass (counting expt) = " << mass_exc1 << endl;
  cout << "Plateau excluded mass (counting expt) = " << mass_exc2 << endl;
  cout << "Excluded mass (time profile fit) = " << mass_excL << endl;

  
}

