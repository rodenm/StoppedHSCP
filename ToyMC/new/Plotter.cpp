#include <TH1.h>
#include <TLine.h>
#include <TText.h>
#include <TROOT.h>
#include <TStyle.h>
#include <TPaveText.h>
#include <TLegend.h>
#include <TLatex.h>
#include "Plotter.h"


Plotter::Plotter()
{
    Style();
}

TCanvas *Plotter::getEfficiencyPlot(TGraph *combined)
{
    TCanvas *canvas = new TCanvas("TimingEfficiency");

    canvas->SetGrid();
    canvas->SetLogx();
    TH1 * h = canvas->DrawFrame(1e-8, 0, 3e5, 1.0); //0.64
    h->SetTitle("Timing Efficiency;Lifetime (s);Timing Effiency");

    // bunch length
    TLine * l1  = new TLine(25e-9, 0, 25e-9, 1.0);
    l1->SetLineColor(3);
    l1->SetLineStyle(7);
    l1->SetLineWidth(2);

    // orbit length
    TLine * l2  = new TLine(8.91e-5, 0, 8.91e-5, 1.0);
    l2->SetLineColor(3);
    l2->SetLineStyle(7);
    l2->SetLineWidth(2);

    // fill length
    TLine * l3  = new TLine(43200, 0, 43200, 1.0);
    l3->SetLineColor(3);
    l3->SetLineStyle(7);
    l3->SetLineWidth(2);

    // Fraction of off-bunches
    TLine * l4  = new TLine(1e-8, .2121, 3e5, .2121);
    l4->SetLineColor(3);
    l4->SetLineStyle(7);
    l4->SetLineWidth(2);

    // Fraction of off-bunches
    TLine * l5  = new TLine(1e-8, .6061, 3e5, .6061);
    l5->SetLineColor(3);
    l5->SetLineStyle(7);
    l5->SetLineWidth(2);

    TText *ft = new TText(3e-8, 0.4, "One Bunch");
    ft->SetTextSize(0.02);

    TText *ft2 = new TText(1.5e-4, 0.4, "One Orbit");
    ft2->SetTextSize(0.02);

    TText *ft3 = new TText(7e-4, 0.58, "1 - Fill ratio * 2808/3564");
    ft3->SetTextSize(0.02);

    TText *ft4 = new TText(7e-4, 0.22, "1 - 2808/3564");
    ft4->SetTextSize(0.02);

    TText *ft5 = new TText(6.5e4, 0.4, "One Fill");
    ft5->SetTextSize(0.02);

    l1->Draw();
    l2->Draw();
    l3->Draw();
    l4->Draw();
    l5->Draw();
    ft ->Draw();
    ft2->Draw();
    ft3->Draw();
    ft4->Draw();
    ft5->Draw();

    combined->Draw("*");

    canvas->Print("Efficiency.eps");
    return canvas;
}

TCanvas *Plotter::getZbPlot(TGraph *graph1,
			    TGraph *graph2,
			    TGraph *graph3,
			    TGraph *graph4,
			    TGraph *graph5,
			    TGraph *graph6) {

  TCanvas *c = new TCanvas("Zb");

  c->Clear();
  c->SetGrid();

  TH1 * h = c->DrawFrame(0, 0, 30, 24);
  h->SetTitle("Discovery Significance;Running Time (days);Significance (sigma)");

  TLine * l1  = new TLine(0., 5., 30., 5.);
  l1->SetLineColor(2);
  l1->SetLineWidth(2);
  l1->Draw();

  TLatex *fs = new TLatex(21., 5.05, "5#sigma discovery");
  fs->SetTextSize(0.03);
  fs->Draw();

  TPaveText *blurb = new TPaveText(22., 18., 29., 21.6);
  blurb->AddText("#sqrt{s} = 10 TeV");
  blurb->AddText("L_{inst} = 10^{32}cm^{-2}s^{-1}");
  //TText* t3a=blurb.AddText("N_{BX} = 2808");
  //  TText* l5=blurb.AddText("30 days");
  blurb->AddText("m_{#tilde{g}}=300 GeV");
  blurb->AddText("m_{#tilde{#chi}}=100 GeV");
  //TText* l6=blurb.AddText("60 pb^{-1}");
  blurb->SetFillColor(0);
  blurb->SetShadowColor(0);
  blurb->SetTextAlign(12);
  blurb->Draw();

  graph1->SetLineColor(1);
  graph1->SetLineStyle(1);
  graph1->SetLineWidth(2);
  graph1->Draw("C");

  graph2->SetLineColor(2);
  graph2->SetLineStyle(1);
  graph2->SetLineWidth(2);
  graph2->Draw("C");

  graph3->SetLineColor(4);
  graph3->SetLineStyle(1);
  graph3->SetLineWidth(2);
  graph3->Draw("C");

  graph4->SetLineColor(1);
  graph4->SetLineStyle(2);
  graph4->SetLineWidth(2);
  graph4->Draw("C");

  graph5->SetLineColor(2);
  graph5->SetLineStyle(2);
  graph5->SetLineWidth(2);
  graph5->Draw("C");

  graph6->SetLineColor(4);
  graph6->SetLineStyle(2);
  graph6->SetLineWidth(2);
  graph6->Draw("C");

  TLegend *leg = new TLegend(22., 12., 29., 17.6, "Gluino lifetime", "");
  //#tau_{#tilde{g}}", "\");
  //  leg.SetHeader("#tau_{#tilde{g}}");
  leg->SetFillColor(0);
  //  leg.SetMargin(0.05);
  leg->AddEntry(graph1, "1 #mus", "l");
  leg->AddEntry(graph2, "1ms", "l");
  leg->AddEntry(graph3, "1h", "l");
  leg->AddEntry(graph4, "12h", "l");
  leg->AddEntry(graph5, "1d", "l");
  leg->AddEntry(graph6, "1w", "l");
  leg->Draw();

  c->Print("Discovery.eps");

  return c;
}

TCanvas *Plotter::getExclusionPlot(TGraph *graph1,
				   TGraph *graph2,
				   TGraph *graph3,
				   TGraph *graph4) {

  TCanvas *canvas = new TCanvas("MassExclusion");

  canvas->SetGrid();
  canvas->SetLogx();
  TH1 * h = canvas->DrawFrame(1e-8, 0, 1e7, 1000);
  h->SetTitle("Combined Expt;#tau_{#tilde{g}} (s); m_{#tilde{g}} excluded at 95% CL (GeV)");

  TText *t1 = new TText();
  /*
  TPaveText *blurb = new TPaveText(1e2, 80, 1e5, 300);
  blurb->AddText("#sqrt{s} = 10 TeV");
  blurb->AddText("L_{inst} = 10^{32}cm^{-2}s^{-1}");
  blurb->AddText("t_{data} = 17 days");
  blurb->SetFillColor(0);
  blurb->SetShadowColor(0);
  blurb->SetTextAlign(12);
  */

  graph1->SetLineColor(1);
  graph1->SetLineStyle(1);
  graph1->SetLineWidth(2);
  graph1->Draw("l");
  
  graph2->SetLineColor(1);
  graph2->SetLineStyle(2);
  graph2->SetLineWidth(2);
  graph2->Draw("l");
  
  graph3->SetLineColor(2);
  graph3->SetLineStyle(1);
  graph3->SetLineWidth(2);
  graph3->Draw("l");

  graph4->SetLineColor(2);
  graph4->SetLineStyle(2);
  graph4->SetLineWidth(2);
  graph4->Draw("l");

  TLegend *leg = new TLegend(1e-2, 600, 1e6, 980, "m_{#tilde{g}} - m_{#tilde{#chi}}","");
  leg->SetFillColor(0);
  leg->AddEntry(graph1, "250 GeV", "l");
  leg->AddEntry(graph2, "250 GeV + syst. uncert.", "l");
  leg->AddEntry(graph3, "100 GeV", "l");
  leg->AddEntry(graph4, "100 GeV + syst. uncert.", "l");

  leg->AddEntry(t1, "", "");
  leg->AddEntry(t1, "#sqrt{s} = 10 TeV", "");
  leg->AddEntry(t1, "L_{inst} = 10^{32}cm^{-2}s^{-1}", "");
  leg->AddEntry(t1, "t_{data} = 17 days", "");

  leg->Draw();

  canvas->Print("MassExclusion.eps");
  return canvas;
}

void Plotter::Style()
{
    gROOT->SetStyle("Plain");

    gStyle->SetCanvasColor(0);
    gStyle->SetPalette(1,0);
    gStyle->SetOptTitle(1);
    gStyle->SetTitleFillColor(0);
    gStyle->SetStatColor(0);
    gStyle->SetOptFit(1111);
    gStyle->SetCanvasBorderMode(0);
    gStyle->SetTitleBorderSize(0);
    gStyle->SetOptStat(0);

    gStyle->SetTitleXOffset(.9);
    gStyle->SetTitleXSize(0.047);
    gStyle->SetTitleYOffset(1.3);
    gStyle->SetTitleYSize(0.047);
    gStyle->SetOptTitle(0);

    gStyle->SetTitleX(0.04);
    gStyle->SetTitleY(0.99);
    gStyle->SetTitleW(0.88);
    gStyle->SetTitleH(0.06);

    gStyle->SetAxisColor(1, "XYZ");
    gStyle->SetStripDecimals(kTRUE);
    gStyle->SetTickLength(0.03, "XYZ");
    gStyle->SetNdivisions(510, "XYZ");
    gStyle->SetPadTickX(1);  // To get tick marks on the opposite side of the frame
    gStyle->SetPadTickY(1);
    gStyle->SetCanvasBorderMode(0);
    gStyle->SetCanvasColor(kWhite);
    gStyle->SetCanvasDefH(600); //Height of canvas
    gStyle->SetCanvasDefW(600); //Width of canvas
    gStyle->SetCanvasDefX(0);   //POsition on screen
    gStyle->SetCanvasDefY(0);

    gStyle->SetPadTopMargin(0.09);


    gStyle->SetPadBottomMargin(0.105);

    gStyle->SetPadLeftMargin(0.13);

    gStyle->SetPadRightMargin(0.07);
}

