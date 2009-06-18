// significance as fn of running time
// for a single mass point

{

  TCanvas* c = new TCanvas("canvas");

  c->Clear();  
  c->SetGrid();

  TLine * l1  = new TLine(0., 5., 30., 5.);
  l1->SetLineColor(2);
  l1->SetLineWidth(2);

  TLatex fs(21., 5.05, "5#sigma discovery");
  fs.SetTextSize(0.03);

  TLine * l2  = new TLine(0., 1.96, 30., 1.96);
  l2->SetLineColor(2);
  l2->SetLineWidth(2);

  TLatex fs2(4., 2.01, "95% C.L.");
  fs2.SetTextSize(0.03);

  TPaveText blurb(22., 9., 29., 10.8);
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

  TLatex p(12., 1., "CMS Preliminary");
  p.SetTextSize(0.06);
  p.SetTextColor(9);

  // beamgap expt 30 days
  TH1F * h = c->DrawFrame(0., 0., 30., 11.);
  h->SetTitle("Beamgap Expt");
  h->SetYTitle("Significance");
  h->SetXTitle("Days");

  TGraph * graph1 = toy->getZbCurve(300., 1.e-6, 1);
  graph1->SetLineColor(1);
  graph1->SetLineStyle(1);
  graph1->SetLineWidth(2);
  graph1->Draw("C");
//   TLatex t1(7., 9.5, "1 #mus");
//   t1.SetTextSize(0.03);
//   t1.Draw();

  TGraph * graph2 = toy->getZbCurve(300., 1.e-3, 1);
  graph2->SetLineColor(2);
  graph2->SetLineStyle(1);
  graph2->SetLineWidth(2);
  graph2->Draw("C");
//   TLatex t2(2.5, 10.3, "1ms");
//   t2.SetTextSize(0.03);
//   t2.Draw();

  TGraph * graph3 = toy->getZbCurve(300., 3600., 1);
  graph3->SetLineColor(4);
  graph3->SetLineStyle(1);
  graph3->SetLineWidth(2);
  graph3->Draw("C");
//   TLatex t3(6.0, 10.3, "1h");
//   t3.SetTextSize(0.03);
//   t3.Draw();

  TGraph * graph4 = toy->getZbCurve(300., 43200., 1);
  graph4->SetLineColor(1);
  graph4->SetLineStyle(2);
  graph4->SetLineWidth(2);
  graph4->Draw("C");
//   TLatex t4(12.2, 10., "12h");
//   t4.SetTextSize(0.03);
//   t4.Draw();

  TGraph * graph5 = toy->getZbCurve(300., 86400, 1);
  graph5->SetLineColor(2);
  graph5->SetLineStyle(2);
  graph5->SetLineWidth(2);
  graph5->Draw("C");
//   TLatex t5(15.5, 9., "1d");
//   t5.SetTextSize(0.03);
//   t5.Draw();

  TGraph * graph6 = toy->getZbCurve(300., 604800, 1);
  graph6->SetLineColor(4);
  graph6->SetLineStyle(2);
  graph6->SetLineWidth(2);
  graph6->Draw("C");
//   TLatex t6(23.5, 7.5, "#tau_{g} = 1w");
//   t6.SetTextSize(0.03);
//   t6.Draw();

  TLegend leg(22., 6., 29., 8.8, "Gluino lifetime", ""); //#tau_{#tilde{g}}", "");
  //  leg.SetHeader("#tau_{#tilde{g}}");
  leg.SetFillColor(0);
  //  leg.SetMargin(0.05);
  leg.AddEntry(graph1, "1 #mus", "l");
  leg.AddEntry(graph2, "1ms", "l");
  leg.AddEntry(graph3, "1h", "l");
  leg.AddEntry(graph4, "12h", "l");
  leg.AddEntry(graph5, "1d", "l");
  leg.AddEntry(graph6, "1w", "l");

  p.Draw();
  l1->Draw();
  fs.Draw();
  //  l2->Draw();
  //  fs2.Draw();
  blurb.Draw();
  leg.Draw();

  c->Update();
  c->Print("SigVsTime_Beamgap_m300.png");
  c->Print("SigVsTime_Beamgap_m300.eps");



  // Interfill expt 30 days
  c->Clear();  
  TH1F * h = c->DrawFrame(0., 0., 30., 11.);
  h->SetTitle("Interfill Expt");
  h->SetYTitle("Significance");
  h->SetXTitle("Days");

  TGraph * graph1 = toy->getZbCurve(300., 1.e-6, 2);
  graph1->SetLineColor(1);
  graph1->SetLineStyle(1);
  graph1->SetLineWidth(2);
  //  graph1->Draw("C");
//   TLatex t1(8.5, 10.3, "1 #mus");
//   t1.SetTextSize(0.03);
//   t1.Draw();

  TGraph * graph2 = toy->getZbCurve(300., 1.e-3, 2);
  graph2->SetLineColor(2);
  graph2->SetLineStyle(1);
  graph2->SetLineWidth(2);
  //  graph2->Draw("C");
//   TLatex t2(8.5, 10.3, "1ms");
//   t2.SetTextSize(0.03);
//   t2.Draw();

  TGraph * graph3 = toy->getZbCurve(300., 3600., 2);
  graph3->SetLineColor(4);
  graph3->SetLineStyle(1);
  graph3->SetLineWidth(2);
  graph3->Draw("C");
//   TLatex t3(21., 3.2, "1h");
//   t3.SetTextSize(0.03);
//   t3.Draw();

  TGraph * graph4 = toy->getZbCurve(300., 43200., 2);
  graph4->SetLineColor(1);
  graph4->SetLineStyle(2);
  graph4->SetLineWidth(2);
  graph4->Draw("C");
//   TLatex t4(2.2., 9.5, "12h");
//   t4.SetTextSize(0.03);
//   t4.Draw();

  TGraph * graph5 = toy->getZbCurve(300., 86400, 2);
  graph5->SetLineColor(2);
  graph5->SetLineStyle(2);
  graph5->SetLineWidth(2);
  graph5->Draw("C");
//   TLatex t5(5., 9.5, "1d");
//   t5.SetTextSize(0.03);
//   t5.Draw();

  TGraph * graph6 = toy->getZbCurve(300., 604800, 2);
  graph6->SetLineColor(4);
  graph6->SetLineStyle(2);
  graph6->SetLineWidth(2);
  graph6->Draw("C");
//   TLatex t6(12.2, 9., "1w");
//   t6.SetTextSize(0.03);
//   t6.Draw();

  leg.Draw();
  l1->Draw();
  //  l2->Draw();
  //  fs2.Draw();
  blurb->Draw();
  fs->Draw();
  p.Draw();

  c->Update();
  c->Print("SigVsTime_Interfill_m300.png");
  c->Print("SigVsTime_Interfill_m300.eps");


  // Combined expt 30 days
  c->Clear();  
  TH1F * h = c->DrawFrame(0., 0., 30., 11.);
  h->SetTitle("Interfill Expt");
  h->SetYTitle("Significance");
  h->SetXTitle("Days");

  TGraph * graph1 = toy->getZbCurve(300., 1.e-6, 0);
  graph1->SetLineColor(1);
  graph1->SetLineStyle(1);
  graph1->SetLineWidth(2);
  graph1->Draw("C");
//   TLatex t1(21., 7., "1 #mus");
//   t1.SetTextSize(0.03);
//   t1.Draw();

  TGraph * graph2 = toy->getZbCurve(300., 1.e-3, 0);
  graph2->SetLineColor(2);
  graph2->SetLineStyle(1);
  graph2->SetLineWidth(2);
  graph2->Draw("C");
//   TLatex t2(21., 8.5, "1ms");
//   t2.SetTextSize(0.03);
//   t2.Draw();

  TGraph * graph3 = toy->getZbCurve(300., 3600., 0);
  graph3->SetLineColor(4);
  graph3->SetLineStyle(1);
  graph3->SetLineWidth(2);
  graph3->Draw("C");
//   TLatex t3(15., 9., "1h");
//   t3.SetTextSize(0.03);
//   t3.Draw();

  TGraph * graph4 = toy->getZbCurve(300., 43200., 0);
  graph4->SetLineColor(1);
  graph4->SetLineStyle(2);
  graph4->SetLineWidth(2);
  graph4->Draw("C");
//   TLatex t4(1.5., 9.5, "12h");
//   t4.SetTextSize(0.03);
//   t4.Draw();

  TGraph * graph5 = toy->getZbCurve(300., 86400, 0);
  graph5->SetLineColor(2);
  graph5->SetLineStyle(2);
  graph5->SetLineWidth(2);
  graph5->Draw("C");
//   TLatex t5(4.8, 9.5, "1d");
//   t5.SetTextSize(0.03);
//   t5.Draw();

  TGraph * graph6 = toy->getZbCurve(300., 604800, 0);
  graph6->SetLineColor(4);
  graph6->SetLineStyle(2);
  graph6->SetLineWidth(2);
  graph6->Draw("C");
//   TLatex t6(12., 9.5, "1w");
//   t6.SetTextSize(0.03);
//   t6.Draw();

//   TLatex t7(20., 9., "Gluino lifetime");
//   t7.SetTextSize(0.03);
//   t7.Draw();

  leg.Draw();
  l1->Draw();
  //  l2->Draw();
  //  fs2.Draw();
  blurb->Draw();
  fs->Draw();
  p.Draw();

  c->Update();
  c->Print("SigVsTime_Combined_m300.png");
  c->Print("SigVsTime_Combined_m300.eps");


}


