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

#include "ExtraLimitPlots.h"

struct ExtraAxis {
  vector<TObject*> objects;
  void Add (TObject* object) {objects.push_back(object);}
  void Draw () {
    for (size_t i = 0; i < objects.size(); ++i) objects[i]->Draw(); 
  }
};

ExtraAxis anotherScale (const TH1* refHist, double scale, int color, const char* title, double offset) {
  ExtraAxis result;
  double x0 = refHist->GetXaxis()->GetXmin();
  double x1 = refHist->GetXaxis()->GetXmax();
  double y0 = refHist->GetMinimum();
  double y1 = refHist->GetMaximum();
  // double y0 = refHist->GetYaxis()->GetXmin();
  // double y1 = refHist->GetYaxis()->GetXmax();
  double xoffset = exp (log(x0) - (log(x1) - log(x0))*offset);

  TGaxis* axis = new TGaxis(xoffset, y0, xoffset, y1, y0*scale,y1*scale,510,"-GS");
  axis->ImportAxisAttributes (refHist->GetXaxis());
  axis->SetTitle(title);
  axis->SetTextColor (color);
  axis->SetLineColor (color);
  axis->SetLineWidth (1);
  axis->SetTextColor (color);
  axis->SetLabelColor (color);
  axis->SetLabelOffset (0.);
  axis->SetTitleOffset (0.65);
  axis->SetTickSize(0.015);	
  result.Add (axis);

  TLine* line = new TLine (xoffset, y0, xoffset, y1);
  line->SetLineColor (color);
  line->SetLineWidth (2);
  result.Add (line);

  line = new TLine (x0, y0, xoffset, y0);
  line->SetLineColor (kGray);
  line->SetLineWidth (2);
  result.Add (line);
  
  line = new TLine (x0, y1, xoffset, y1);
  line->SetLineColor (kGray);
  line->SetLineWidth (2);
  result.Add (line);

  return result;
}

void allInOneLifetime(double lumi=4560., double maxInstLumi=5000.) {

  ExtraLimitPlots plots(lumi);
  plots.calculateCrossSections(7,4,3,39,9);
  
  // graphs - observed
  TGraph* g_obs      = plots.getObsLimit();
  TGraph* g_exp      = plots.getExpLimit();
  TGraphAsymmErrors* g_exp_1sig = plots.getExpLimit1Sig();
  TGraphAsymmErrors* g_exp_2sig = plots.getExpLimit2Sig();

  TGraph* g_obs_gluino = plots.getLimitGluino();
  double gluino2ref    = g_obs_gluino->GetY()[0] / g_obs->GetY()[0];
  TGraph* g_obs_stop   = plots.getLimitStop();
  double stop2ref      = g_obs_stop->GetY()[0] / g_obs->GetY()[0];
  TGraph* g_obs_stau   = plots.getLimitStau();
  double stau2ref      = g_obs_stau->GetY()[0] / g_obs->GetY()[0];

  cout << "scales: " << g_obs->GetY()[0] 
       << '/' <<g_obs_gluino->GetY()[0]
       << '/' <<g_obs_stop->GetY()[0]
       << '/' <<g_obs_stau->GetY()[0]
       <<endl;

  
  TCanvas *canvas = new TCanvas("allLifetime", "allLifetime", 1000, 600);
  
  canvas->SetLogx();
  canvas->SetLogy();

  canvas->SetRightMargin(0.8*canvas->GetLeftMargin());
  canvas->SetLeftMargin(1.2*canvas->GetLeftMargin());
  canvas->SetTicks (canvas->GetTickx(), 0);
  
  TH1F* h = new TH1F ("h", "", 1, 7.5e-8, 1e6);
  h->SetStats (0);
  h->SetMinimum (.0001);
  h->SetMaximum (0.99e1);
  // TH1* h = canvas->DrawFrame(7.5e-8, .001, 1e6, 1e2, "Y+");
  h->SetTitle("Beamgap Expt");
  //  h->GetXaxis()->SetTitle("#tau_{#tilde{g},#tilde{t},#tilde{#tau}} [s]");
  h->GetXaxis()->SetTitle("#tau [s]");
  h->GetYaxis()->SetTitle("#sigma #times BF #times #varepsilon_{stop} #times #varepsilon_{det}   [pb]  ");
  h->Draw ("Y+");

  ExtraAxis aGluino = anotherScale (h, gluino2ref, kRed+2, "#sigma(pp #rightarrow #tilde{g}#tilde{g}) #times BF(#tilde{g} #rightarrow g#tilde{#chi}^{0})   [pb]  ", 0.0);

  ExtraAxis aStop = anotherScale (h, stop2ref, kBlue+2, "#sigma(pp #rightarrow #tilde{t}#tilde{t}) #times BF(#tilde{t} #rightarrow t#tilde{#chi}^{0})   [pb]  ", 0.2);

  ExtraAxis aStau = anotherScale (h, stau2ref, kGreen+2, "#sigma(pp #rightarrow #tilde{#tau}#tilde{#tau}) #times BF(#tilde{#tau} #rightarrow #tau#tilde{#chi}^{0})   [pb]  ", 0.4);


  
  
  TPaveText* blurb = new TPaveText(0.25, 0.57, 0.50, 0.87, "NDC");

  blurb->AddText("CMS Preliminary 2012");
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
  // blurb->AddText(label2.str().c_str());

  //blurb->AddText("CMS 2011");
  blurb->AddText("#int L dt = 18.6 fb^{-1}");//,  #int L_{eff} dt = 935 pb^{-1}");
  //blurb->AddText("L^{max}_{inst} = 3.5 #times 10^{33} cm^{-2}s^{-1}");
  blurb->AddText("#sqrt{s} = 8 TeV");
  blurb->AddText("E_{gluon} > 120 GeV, E_{top} > 150 GeV");
  //blurb->AddText("m_{#tilde{g}} = 300 GeV/c^{2}");
  //blurb->AddText("m_{#tilde{#chi}^{0}} = 200 GeV/c^{2}");
  blurb->SetTextFont(42);
  blurb->SetBorderSize(0);
  blurb->SetFillColor(0);
  blurb->SetShadowColor(0);
  blurb->SetTextAlign(12);
  blurb->SetTextSize(0.033);
  blurb->Draw();
  
  
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
  
  
  // GLUINO LIMIT
  if (g_exp) {
    g_exp->SetLineColor(1);
    g_exp->SetLineStyle(4);
    g_exp->SetLineWidth(2);
    g_exp->Draw("l3");
  }
  
  TLine *l;
  l = new TLine(7.5e-8, 1.3/gluino2ref, 1e6, 1.3/gluino2ref); //600 GeV
  l->SetLineColor(kRed);
  l->SetLineWidth(2);
  l->Draw();
  
  TLatex *t1;
  t1 = new TLatex(0.1, 0.6/gluino2ref, "#sigma_{theory} (m_{#tilde{g}} = 600 GeV)");
  t1->SetTextColor(kRed);
  t1->SetTextFont(42);
  t1->SetTextSize(0.035);
  t1->Draw();

  // STOP LIMIT
  TLine *ltop = new TLine(7.5e-8, 0.025/stop2ref, 1e6, 0.025/stop2ref); //600 GeV
  ltop->SetLineColor(kBlue);
  ltop->SetLineWidth(2);
  ltop->Draw();
  
  TLatex *t1top;
  t1top = new TLatex(0.1, 0.01/stop2ref, "#sigma_{theory} (m_{#tilde{t}} = 600 GeV)");
  t1top->SetTextColor(kBlue);
  t1top->SetTextFont(42);
  t1top->SetTextSize(0.035);
  t1top->Draw();
  

  // observed limit
  if (g_obs) {
    g_obs->SetLineColor(1);
    g_obs->SetLineStyle(1);
    g_obs->SetLineWidth(2);
    g_obs->Draw("l");
  }
  
  

  TLegend* leg = new TLegend(0.67, 0.65, 0.82, 0.87,"95% CL Limits:","NDC");
  leg->SetTextSize(0.033);
  leg->SetBorderSize(0);
  leg->SetTextFont(42);
  leg->SetFillColor(0);
  TGraph* expectedStyle1 = new TGraph (*g_exp);
  expectedStyle1->SetFillColor (g_exp_1sig->GetFillColor());
  TGraph* expectedStyle2 = new TGraph (*g_exp);
  expectedStyle2->SetFillColor (g_exp_2sig->GetFillColor());
  cout << "colors: " << g_exp_1sig->GetFillColor() << ':' << g_exp_2sig->GetFillColor() << endl;
  leg->AddEntry(g_obs, "Observed", "l");
  leg->AddEntry(expectedStyle1, "Expected #pm1#sigma", "lf");
  leg->AddEntry(expectedStyle2, "Expected #pm2#sigma", "lf");
  //leg->AddEntry(g_obs_stop,"Obs.: Counting Exp. (#tilde{t})", "l");
  //leg->AddEntry(g_obs_nb, "Obs.: Counting Exp. (Neutral R-Baryon)", "l");
  //leg->AddEntry(g_obs_em, "Observed: Counting Exp. (EM only)", "l");
  //leg->AddEntry(g_obs_tp, "Observed: Timing Profile", "l");
  leg->Draw();

  h->Draw("sameaxis y+");
  aGluino.Draw();
  aStop.Draw();
  //aStau.Draw();

  canvas->Print("allInOneLifetime.png");
  canvas->Print("allInOneLifetime.pdf");
}
