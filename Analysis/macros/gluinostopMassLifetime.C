#include <sstream>

#include "TGraph.h"
#include "TGaxis.h"
#include "TF1.h"
#include "TGraphAsymmErrors.h"
#include "TCanvas.h"
#include "TFile.h"
#include "TH1.h"
#include "TH1F.h"
#include "TLegend.h"
#include "TLatex.h"
#include "TPaveText.h"
#include "TArrow.h"

#include "ExtraLimitPlots.h"

class Xsection {
  vector<double> masses;
  vector<double> logXsecs;
public:
  Xsection (const vector<double>& m, const double* xs) {
    masses = m;
    for (size_t i = 0; i < masses.size(); ++i) logXsecs.push_back (xs[i]);
  }
  double mass2xsec (double mass) {
    double logXsec = 0;
    if (mass < masses.front() || mass > masses.back()) {
      cerr << "gluinoXsection::mass2xsec-> mass is beyond the range: " << mass << endl;
      return 0;
    }
    int index = 0;
    while (mass > masses[index]) ++index;
    if (index == 0) logXsec = logXsecs[0];
    else logXsec = logXsecs[index-1] + (mass-masses[index-1])*(logXsecs[index]-logXsecs[index-1])/(masses[index]-masses[index-1]);
    return 1.e-3*pow(10, logXsec/20.);
  }
  double xsec2mass (double xsec) {
    double logXsec = log10(xsec/1e-3)*20.;
    if (logXsec > logXsecs.front() || logXsec < logXsecs.back()) {
      cerr << "gluinoXsection::xsec2mass-> xsec is beyond the range: " 
	   << xsec << '/' << logXsec << '/' <<logXsecs.front() << '/' << logXsecs.back() << endl;
      return 0;
    }
    double mass = 0;
    int index = 0;
    while (logXsec < logXsecs[index]) ++index;
    if (index == 0) mass = masses[0];
    else mass = masses[index-1] + (logXsec-logXsecs[index-1])*(masses[index]-masses[index-1])/(logXsecs[index]-logXsecs[index-1]);
    // cout << "xsec2mass -> "<<xsec<< " ("<<logXsec<<") -> " << mass << endl;
    return mass;
  }

  void xsec2mass (TGraph* g) {
    for (int i = 0; i < g->GetN(); ++i) {
      g->GetY()[i] = xsec2mass (g->GetY()[i]);
    }
  }

  void xsec2mass (TGraphAsymmErrors* g) {
    for (int i = 0; i < g->GetN(); ++i) {
      double xs = g->GetY()[i];
      double xsPlus = g->GetEYhigh()[i];
      double xsMius = g->GetEYlow()[i];
      g->GetY()[i] = xsec2mass (xs);
      g->GetEYhigh()[i] = xsec2mass (xs-xsMius) -  g->GetY()[i];
      g->GetEYlow()[i] = g->GetY()[i] - xsec2mass (xs+xsPlus);
    }
  }
};

void gluinostopMassLifetime(double lumi=4560., double maxInstLumi=5000.) {

  ExtraLimitPlots plots(lumi);
  plots.calculateCrossSections(7,4,3,39,9);

  // xsecs as extracted from nllfast http://web.physik.rwth-aachen.de/service/wiki/bin/view/Main/SquarksandGluinos
  // gluino (m_squark=m_gluino):  "nllfast gg mstw <mass> <mass>"
  // gluino (m_squark>>m_gluino): "nllfast gdcpl mstw <mass>"
  // stop: "nllfast st mstw <mass>"
  double g_mass [21] = {  
    200 ,     250 ,     300 ,     350 ,     400 ,   
    450 ,     500 ,     550 ,     600 ,     650 ,   
    700 ,     750 ,     800 ,     850 ,     900 ,   
    950 ,    1000 ,    1050 ,    1100 ,    1150 ,   
    1200 };
  double g_xsec [21] = {  
    1010,      302,     106,     42.6,     18.9,
    8.93,     4.52,    2.39,     1.31,    0.744,
    0.434,   0.259,   0.157,   0.0967,   0.0603,
    0.0381, 0.0244,  0.0157,   0.0102,  0.00667,
    0.00440
  };
  double g_xsecdcpl [21] = {  
    1010,      302,     106,     42.6,     18.9,
    8.93,     4.52,    2.39,     1.31,    0.744,
    0.434,   0.259,   0.157,   0.0967,   0.0603,
    0.0381, 0.0244,  0.0157,   0.0102,  0.00667,
    0.00440
  };
  double s_mass [21] = {  
    100 ,     150 ,     200 ,     250 ,     300 ,   
    350 ,     400 ,     450 ,     500 ,     550 ,   
    600 ,     650 ,     700 ,     750 ,     800 ,   
    850 ,     900 ,     950 ,    1000 ,    1050 ,   
    1100 };
  double s_xsec [21] = {  
    560,       80.3,     18.5,     5.58,     2.00,
    0.807,    0.357,    0.170,   0.0856,   0.0452,
    0.0248,  0.0140,  0.00811,  0.00480,  0.00290,
    0.00177,0.00110, 0.000687, 0.000435, 0.000278,
    0.000180
  };

  //gluino xsec
  vector<double> masses;
  for (int i = 0; i < 21; ++i)  {
    masses.push_back(g_mass[i]);
    g_xsec [i] = log10 (g_xsec [i]*1e3) * 20.;
    g_xsecdcpl [i] = log10 (g_xsecdcpl [i]*1e3) * 20.;
  }
  //  Xsection gluino_xs (masses, g_xsec);
  Xsection gluino_xs (masses, g_xsecdcpl);
  
  //stop xsec
  masses.clear();
  for (int i = 0; i < 19; ++i)  {
    masses.push_back(s_mass[i]);
    s_xsec [i] = log10 (s_xsec [i]*1e3) * 20.;
  }
  Xsection stop_xs (masses, s_xsec);
  
  // graphs
  TGraph* g_obs     = new TGraph (*plots.getLimitGluino());
  gluino_xs.xsec2mass (g_obs);

  TGraph* g_exp      = new TGraph (*plots.getExpLimitGluino());
  gluino_xs.xsec2mass (g_exp);
  TGraphAsymmErrors* g_exp_1sig = new TGraphAsymmErrors (*plots.getExpLimitGluino1Sig());
  gluino_xs.xsec2mass (g_exp_1sig);
  TGraphAsymmErrors* g_exp_2sig = new TGraphAsymmErrors (*plots.getExpLimitGluino2Sig());
  gluino_xs.xsec2mass (g_exp_2sig);

  TGraph* stop_obs     = new TGraph (*plots.getLimitStop());
  stop_xs.xsec2mass (stop_obs);

  TGraph* stop_exp      = new TGraph (*plots.getExpLimitStop());
  stop_xs.xsec2mass (stop_exp);
  TGraphAsymmErrors* stop_exp_1sig = new TGraphAsymmErrors (*plots.getExpLimitStop1Sig());
  stop_xs.xsec2mass (stop_exp_1sig);
  TGraphAsymmErrors* stop_exp_2sig = new TGraphAsymmErrors (*plots.getExpLimitStop2Sig());
  stop_xs.xsec2mass (stop_exp_2sig);

  
  TCanvas *canvas = new TCanvas("allMassLifetime", "allMassLifetime", 800, 600);
  
  canvas->SetLogx();
  canvas->SetGridy();

  
  TH1F* h = new TH1F ("h", "", 1,  7.5e-8, 1e6);
  h->SetStats (0);
  h->SetMinimum (300);
  h->SetMaximum (1500);
  h->SetTitle("Beamgap Expt");
  //  h->GetXaxis()->SetTitle("#tau_{#tilde{g},#tilde{t},#tilde{#tau}} [s]");
  h->GetXaxis()->SetTitle("#tau [s]");
  h->GetYaxis()->SetTitle("m [GeV]  ");
  h->Draw ("");

  
  
  // limit arrows
  double* x = g_obs->GetX();
  for (int i = 0; i < g_obs->GetN(); ++i) {
    if (x[i] > 0.5) {
      double y =  g_obs->GetY()[i];
      TArrow* arrow = new TArrow (x[i], y, h->GetXaxis()->GetXmin(), y, 0.02);
      arrow->SetLineColor (kRed);
      arrow->SetLineWidth (2);
      arrow->Draw();
      cout << "GLUINO mass limit @ " << x[i] << "sec is found: " << y << endl;
      break;
    }
  }
  x = g_obs->GetX();
  for (int i = 0; i < stop_obs->GetN(); ++i) {
    if (x[i] > 0.5) {
      double y =  stop_obs->GetY()[i];
      TArrow* arrow = new TArrow (x[i], y, h->GetXaxis()->GetXmin(), y, 0.02);
      arrow->SetLineColor (kBlue);
      arrow->SetLineWidth (2);
      arrow->Draw();
      cout << "STOP mass limit @ " << x[i] << "sec is found: " << y << endl;
      break;
    }
  }
 
  // gluino  
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
  
  
  // epxected limit
  if (g_exp) {
    g_exp->SetLineColor(kRed);
    g_exp->SetLineStyle(4);
    g_exp->SetLineWidth(2);
    g_exp->Draw("l3");
  }
  

  // observed limit
  if (g_obs) {
    g_obs->SetLineColor(kRed);
    g_obs->SetLineStyle(1);
    g_obs->SetLineWidth(2);
    g_obs->Draw("l");
  }
  
  // stop  
  // 2 sigma band
  if (stop_exp_2sig) {
    stop_exp_2sig->SetLineColor(0);
    stop_exp_2sig->SetLineStyle(0);
    stop_exp_2sig->SetLineWidth(0);
    stop_exp_2sig->SetFillColor(kYellow);
    stop_exp_2sig->SetFillStyle(1001);
    stop_exp_2sig->Draw("3");
  }
  
  // 1 sigma band
  if (stop_exp_1sig) {
    // stop_exp_1sig->SetLineColor(8);
    stop_exp_1sig->SetLineColor(0);
    stop_exp_1sig->SetLineStyle(0);
    stop_exp_1sig->SetLineWidth(0);
    // stop_exp_1sig->SetFillColor(8);
    stop_exp_1sig->SetFillColor(kGreen);
    stop_exp_1sig->SetFillStyle(1001);
    // stop_exp_1sig->SetFillStyle(3005);
    stop_exp_1sig->Draw("3");
    // stop_exp_1sig->Draw("lX");
  }
  
  
  // epxected limit
  if (stop_exp) {
    stop_exp->SetLineColor(kBlue);
    stop_exp->SetLineStyle(3);
    stop_exp->SetLineWidth(2);
    stop_exp->Draw("l3");
  }
  

  // observed limit
  if (stop_obs) {
    stop_obs->SetLineColor(kBlue);
    stop_obs->SetLineStyle(2);
    stop_obs->SetLineWidth(2);
    stop_obs->Draw("l");
  }
  
  

  TPaveText* blurb = new TPaveText(0.20, 0.63, 0.60, 0.90, "NDC");
  blurb->AddText("CMS Preliminary 2012");
  //blurb->AddText("CMS 2012");
  blurb->AddText("#int L dt = 18.6 fb^{-1}"); //,  #int L_{eff} dt = 935 pb^{-1}");
  //blurb->AddText("L^{max}_{inst} = 3.5 #times 10^{33} cm^{-2}s^{-1}");

  // std::stringstream label;
  // label<<"#int L dt = "<<lumi<<" pb^{-1}";
  // blurb->AddText(label.str().c_str());
  // double peakInstLumi=maxInstLumi;
  // int exponent=30;
  // while (peakInstLumi>10) {
  //   peakInstLumi/=10;
  //   ++exponent;
  // }
  // std::stringstream label2;
  // label2<<"L^{max}_{inst} = "<<peakInstLumi<<" x 10^{"<<exponent<<"} cm^{-2}s^{-1}";
//  blurb->AddText(label2.str().c_str());
  blurb->AddText("#sqrt{s} = 8 TeV");
  blurb->AddText("E_{gluon} > 120 GeV, E_{top} > 150 GeV");
  blurb->SetTextFont(42);
  blurb->SetBorderSize(0);
  blurb->SetFillColor(0);
  blurb->SetShadowColor(0);
  blurb->SetTextAlign(12);
  blurb->SetTextSize(0.033);
  blurb->Draw();

  TLegend* leg = new TLegend(0.6, 0.62, 0.87, 0.90,"95% CL Limits:","NDC");
  leg->SetTextSize(0.033);
  leg->SetBorderSize(0);
  leg->SetTextFont(42);
  leg->SetFillColor(0);

  leg->AddEntry(g_obs, " #tilde{g} observed", "l");
  leg->AddEntry(stop_obs, " #tilde{t} observed", "l");

  TGraph* expectedStyle1 = new TGraph (*g_exp);
  expectedStyle1->SetFillColor (g_exp_1sig->GetFillColor());
  TGraph* expectedStyle2 = new TGraph (*g_exp);
  expectedStyle2->SetFillColor (g_exp_2sig->GetFillColor());
  leg->AddEntry(expectedStyle1, " #tilde{g} expected #pm1#sigma", "lf");
  leg->AddEntry(expectedStyle2, " #tilde{g} expected #pm2#sigma", "lf");

  expectedStyle1 = new TGraph (*stop_exp);
  expectedStyle1->SetFillColor (stop_exp_1sig->GetFillColor());
  expectedStyle2 = new TGraph (*stop_exp);
  expectedStyle2->SetFillColor (stop_exp_2sig->GetFillColor());
  leg->AddEntry(expectedStyle1, " #tilde{t} expected #pm1#sigma", "lf");
  leg->AddEntry(expectedStyle2, " #tilde{t} expected #pm2#sigma", "lf");
  leg->Draw();

  h->Draw("sameaxis");

  canvas->Print("gluinostopMassLifetime.png");
  canvas->Print("gluinostopMassLifetime.pdf");
}
