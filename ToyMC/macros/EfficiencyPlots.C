// significance as fn of running time
// for a single mass point

{

  TCanvas* c = new TCanvas("canvas");

  c->Clear();  
  c->SetGrid();
  c->SetLogx();

  // bunch length
  TLine * l1  = new TLine(25e-9, 0, 25e-9, .64);
  l1->SetLineColor(3);
  l1->SetLineStyle(7);
  l1->SetLineWidth(2);

  // orbit length
  TLine * l2  = new TLine(8.91e-5, 0, 8.91e-5, .64);
  l2->SetLineColor(3);
  l2->SetLineStyle(7);
  l2->SetLineWidth(2);

  // fill length
  TLine * l3  = new TLine(43200, 0, 43200, .64);
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

  TText ft(3e-8, 0.4, "One Bunch");
  ft.SetTextSize(0.02);

  TText ft2(1.5e-4, 0.4, "One Orbit");
  ft2.SetTextSize(0.02);

  TText ft3(7e-4, 0.58, "1 - Fill ratio * 2808/3564");
  ft3.SetTextSize(0.02);

  TText ft4(7e-4, 0.22, "1 - 2808/3564");
  ft4.SetTextSize(0.02);

  TText ft5(6.5e4, 0.4, "One Fill");
  ft5.SetTextSize(0.02);

  /*
  TLatex fs(21., 5.05, "5#sigma discovery");
  fs.SetTextSize(0.03);

  TLatex fs2(4., 2.01, "95% C.L.");
  fs2.SetTextSize(0.03);
  */

  /*
  TPaveText blurb(3e-8, 0.50, 1e-4, 0.62);
  TText* t2=blurb.AddText("#sqrt{s} = 10 TeV");
  TText* t3=blurb.AddText("L_{inst} = 10^{32}cm^{-2}s^{-1}");
  //TText* t3a=blurb.AddText("N_{BX} = 2808");
  //  TText* l5=blurb.AddText("30 days");
  TText* t4=blurb.AddText("m_{#tilde{g}}=300 GeV");
  TText* t5=blurb.AddText("m_{#tilde{#chi}}=100 GeV");
  //TText* l6=blurb.AddText("60 pb^{-1}");
  blurb.SetFillColor(0);
  blurb.SetShadowColor(0);
  blurb.SetTextAlign(12);
  //  blurb.SetMargin(0.1);
  */

  TLatex p(1.e-2, 0.04, "CMS Preliminary");
  p.SetTextSize(0.06);
  p.SetTextColor(9);

  // beamgap expt 30 days
  TH1F * h = c->DrawFrame(1e-8, 0., 3e5, .64);
  h->SetTitle("Timing Efficiency");
  h->SetYTitle("Timing Efficiency");
  h->SetXTitle("Lifetime (s)");

  TGraph * graph1 = toy->getEfficiencyCurve(300., 90, 0);
  graph1->SetLineColor(1);
  graph1->SetLineStyle(1);
  graph1->SetLineWidth(2);
  graph1->Draw("*");

  TGraph * graph2 = toy->getEfficiencyCurve(300., 90, 1);
  graph2->Draw("*");
  graph2->SetMarkerStyle(2);

  TGraph * graph3 = toy->getEfficiencyCurve(300., 90, 2);
  graph3->Draw("*");
  graph3->SetMarkerStyle(5);

  TLegend leg(3e-8, .54, 1e-4, .62, "Experiment", ""); //#tau_{#tilde{g}}", "");
  //  leg.SetHeader("#tau_{#tilde{g}}");
  leg.SetFillColor(0);
  //  leg.SetMargin(0.05);
  leg.AddEntry(graph1, "Combined", "p");
  leg.AddEntry(graph2, "Beamgap", "p");
  leg.AddEntry(graph3, "Interfill", "p");
  /*
  leg.AddEntry(graph4, "12h", "l");
  leg.AddEntry(graph5, "1d", "l");
  leg.AddEntry(graph6, "1w", "l");
  */

  //  p.Draw();
  l1->Draw();
  l2->Draw();
  l3->Draw();
  l4->Draw();
  l5->Draw();
  //  blurb.Draw();
  leg.Draw();
  ft.Draw();
  ft2.Draw();
  ft3.Draw();
  ft4.Draw();
  ft5.Draw();

  c->Update();
  c->Print("Efficiency_90days.png");
  c->Print("Efficiency_90days.eps");

}


