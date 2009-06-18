// significance as a fn of gluino mass (and cross-section)
// for a fixed running time

{

  TCanvas* c = new TCanvas("canvas");
  c->Clear(); 
  c->SetGrid();

  TLine * l1  = new TLine(0., 5., 300., 5.);
  l1->SetLineColor(2);
  l1->SetLineWidth(2);

  TLatex fs(220., 5.2, "5#sigma discovery");
  fs.SetTextSize(0.03);

  TLine * l2  = new TLine(0., 1.96, 300., 1.96);
  l2->SetLineColor(2);
  l2->SetLineWidth(2);

  TLatex fs2(220., 2.01, "95% C.L.");
  fs2.SetTextSize(0.03);

  TPaveText blurb(215., 9., 290., 10.8);
  TText* t2=blurb.AddText("#sqrt{s} = 10 TeV");
  TText* t3=blurb.AddText("L_{inst} = 10^{32}cm^{-2}s^{-1}");
  TText* t4=blurb.AddText("m_{#tilde{g}}=300 GeV");
  TText* t5=blurb.AddText("7 days");
  //TText* l6=blurb.AddText("60 pb^{-1}");
  blurb.SetFillColor(0);
  blurb.SetTextAlign(12);
  blurb.SetShadowColor(0);
  //  blurb.SetMargin(0.1);

  TLatex p(25., 0.5, "CMS Preliminary");
  p.SetTextSize(0.06);
  p.SetTextColor(9);


  // beamgap expt 30 days
  TH1F * h = c->DrawFrame(0., 0., 300., 11.);
  h->SetTitle("Beamgap Expt");
  h->SetYTitle("Significance");
  h->SetXTitle("m_{#chi} (GeV)");

  TGraph * graph1 = toy->getMassCurve(7., 1.e-6, 1);
  graph1->SetLineColor(1);
  graph1->SetLineStyle(1);
  graph1->SetLineWidth(2);
  graph1->Draw("C");
//   TLatex t1(205., 13., "1 #mus");
//   t1.SetTextSize(0.03);
//   t1.Draw();

  TGraph * graph2 = toy->getMassCurve(7., 1.e-3, 1);
  graph2->SetLineColor(2);
  graph2->SetLineStyle(1);
  graph2->SetLineWidth(2);
  graph2->Draw("C");
//   TLatex t2(205., 17., "1ms");
//   t2.SetTextSize(0.03);
//   t2.Draw();

  TGraph * graph3 = toy->getMassCurve(7., 3600., 1);
  graph3->SetLineColor(4);
  graph3->SetLineStyle(1);
  graph3->SetLineWidth(2);
  graph3->Draw("C");
//   TLatex t3(205., 15., "1h");
//   t3.SetTextSize(0.03);
//   t3.Draw();

  TGraph * graph4 = toy->getMassCurve(7., 43200., 1);
  graph4->SetLineColor(1);
  graph4->SetLineStyle(2);
  graph4->SetLineWidth(2);
  graph4->Draw("C");
//   TLatex t4(205., 9., "12h");
//   t4.SetTextSize(0.03);
//   t4.Draw();

  TGraph * graph5 = toy->getMassCurve(7., 86400, 1);
  graph5->SetLineColor(2);
  graph5->SetLineStyle(2);
  graph5->SetLineWidth(2);
  graph5->Draw("C");
//   TLatex t5(205., 8., "1d");
//   t5.SetTextSize(0.03);
//   t5.Draw();

  TGraph * graph6 = toy->getMassCurve(7., 604800, 1);
  graph6->SetLineColor(4);
  graph6->SetLineStyle(2);
  graph6->SetLineWidth(2);
  graph6->Draw("C");
//   TLatex t6(205., 6., "1w");
//   t6.SetTextSize(0.03);
//   t6.Draw();

  TLegend leg(215., 6., 290., 8.8, "Gluino lifetime", ""); //#tau_{#tilde{g}}", "");
  //  leg.SetHeader("#tau_{#tilde{g}}");
  leg.SetFillColor(0);
  //  leg.SetMargin(0.05);
  leg.AddEntry(graph1, "1 #mus", "l");
  leg.AddEntry(graph2, "1ms", "l");
  leg.AddEntry(graph3, "1h", "l");
  leg.AddEntry(graph4, "12h", "l");
  leg.AddEntry(graph5, "1d", "l");
  leg.AddEntry(graph6, "1w", "l");

  leg.Draw();
  l1->Draw();
  fs.Draw();
//   l2->Draw();
//   fs2.Draw();
  blurb.Draw();
  p.Draw();

  c->Update();
  c->Print("SigVsChi0Mass_Beamgap_7days.png");
  c->Print("SigVsChi0Mass_Beamgap_7days.eps");


  // interfill expt 30 days
  c->Clear(); 

  TH1F * h = c->DrawFrame(0., 0., 300., 11.);
  h->SetTitle("Interfill Expt");
  h->SetYTitle("Significance");
  h->SetXTitle("m_{#chi} (GeV)");

  TGraph * graph1 = toy->getMassCurve(7., 1.e-6, 2);
  graph1->SetLineColor(1);
  graph1->SetLineWidth(2);
  graph1->SetLineStyle(1);
  //  graph1->Draw("C");
//   TLatex t1(205., 5.5, "1 #mus");
//   t1.SetTextSize(0.03);
//   t1.Draw();

  TGraph * graph2 = toy->getMassCurve(7., 1.e-3, 2);
  graph2->SetLineColor(2);
  graph2->SetLineStyle(1);
  graph2->SetLineWidth(2);
  //  graph2->Draw("C");
//   TLatex t2(205., 7., "1ms");
//   t2.SetTextSize(0.03);
//   t2.Draw();

  TGraph * graph3 = toy->getMassCurve(7., 3600., 2);
  graph3->SetLineColor(4);
  graph3->SetLineStyle(1);
  graph3->SetLineWidth(2);
  graph3->Draw("C");
//   TLatex t3(205., 1., "1h");
//   t3.SetTextSize(0.03);
//   t3.Draw();

  TGraph * graph4 = toy->getMassCurve(7., 43200., 2);
  graph4->SetLineColor(1);
  graph4->SetLineStyle(2);
  graph4->SetLineWidth(2);
  graph4->Draw("C");
//   TLatex t4(205., 8.2, "12h");
//   t4.SetTextSize(0.03);
//   t4.Draw();

  TGraph * graph5 = toy->getMassCurve(7., 86400, 2);
  graph5->SetLineColor(2);
  graph5->SetLineStyle(2);
  graph5->SetLineWidth(2);
  graph5->Draw("C");
//   TLatex t5(205., 7.5, "1d");
//   t5.SetTextSize(0.03);
//   t5.Draw();

  TGraph * graph6 = toy->getMassCurve(7., 604800, 2);
  graph6->SetLineColor(4);
  graph6->SetLineStyle(2);
  graph6->SetLineWidth(2);
  graph6->Draw("C");
//   TLatex t6(205., 3.5, "1w");
//   t6.SetTextSize(0.03);
//   t6.Draw();

  leg.Draw();
  l1->Draw();
  fs.Draw();
//   l2->Draw();
//   fs2.Draw();
  blurb.Draw();
  p.Draw();

  c->Update();
  c->Print("SigVsChi0Mass_Interfill_7days.png");
  c->Print("SigVsChi0Mass_Interfill_7days.eps");


  // interfill expt 30 days
  c->Clear(); 

  TH1F * h = c->DrawFrame(0., 0., 300., 11.);
  h->SetTitle("Interfill Expt");
  h->SetYTitle("Significance");
  h->SetXTitle("m_{#chi} (GeV)");

  TGraph * graph1 = toy->getMassCurve(7., 1.e-6, 0);
  graph1->SetLineColor(1);
  graph1->SetLineStyle(1);
  graph1->SetLineWidth(2);
  graph1->Draw("C");
//   TLatex t1(205., 5.5, "1 #mus");
//   t1.SetTextSize(0.03);
//   t1.Draw();

  TGraph * graph2 = toy->getMassCurve(7., 1.e-3, 0);
  graph2->SetLineColor(2);
  graph2->SetLineStyle(1);
  graph2->SetLineWidth(2);
  graph2->Draw("C");
//   TLatex t2(205., 7., "1ms");
//   t2.SetTextSize(0.03);
//   t2.Draw();

  TGraph * graph3 = toy->getMassCurve(7., 3600., 0);
  graph3->SetLineColor(4);
  graph3->SetLineStyle(1);
  graph3->SetLineWidth(2);
  graph3->Draw("C");
//   TLatex t3(205., 1., "1h");
//   t3.SetTextSize(0.03);
//   t3.Draw();

  TGraph * graph4 = toy->getMassCurve(7., 43200., 0);
  graph4->SetLineColor(1);
  graph4->SetLineStyle(2);
  graph4->SetLineWidth(2);
  graph4->Draw("C");
//   TLatex t4(205., 8.2, "12h");
//   t4.SetTextSize(0.03);
//   t4.Draw();

  TGraph * graph5 = toy->getMassCurve(7., 86400, 0);
  graph5->SetLineColor(2);
  graph5->SetLineStyle(2);
  graph5->SetLineWidth(2);
  graph5->Draw("C");
//   TLatex t5(205., 7.5, "1d");
//   t5.SetTextSize(0.03);
//   t5.Draw();

  TGraph * graph6 = toy->getMassCurve(7., 604800, 0);
  graph6->SetLineColor(4);
  graph6->SetLineStyle(2);
  graph6->SetLineWidth(2);
  graph6->Draw("C");
//   TLatex t6(205., 3.5, "1w");
//   t6.SetTextSize(0.03);
//   t6.Draw();

  leg.Draw();
  l1->Draw();
  fs.Draw();
//   l2->Draw();
//   fs2.Draw();
  blurb.Draw();
  p.Draw();

  c->Update();
  c->Print("SigVsChi0Mass_Combined_7days.png");
  c->Print("SigVsChi0Mass_Combined_7days.eps");


//   // beamgap expt 7 days
//   TH1F * h = c->DrawFrame(0., 0., 300., 11.);
//   h->SetTitle("Beamgap Expt");
//   h->SetYTitle("z-value");
//   h->SetXTitle("Gluino mass/GeV");

//   TGraph * graph1 = toy->getMassCurve(7., 1.e-6, 1);
//   graph1->Draw("C");
//   TLatex t1(205., 6.5, "1 #mus");
//   t1.SetTextSize(0.03);
//   t1.Draw();

//   TGraph * graph2 = toy->getMassCurve(7., 1.e-3, 1);
//   //  graph2->SetLineColor(2);
//   graph2->Draw("C");
//   TLatex t2(205., 8., "1ms");
//   t2.SetTextSize(0.03);
//   t2.Draw();

//   TGraph * graph3 = toy->getMassCurve(7., 3600., 1);
//   //  graph3->SetLineColor(3);
//   graph3->Draw("C");
//   TLatex t3(205., 7.5, "1h");
//   t3.SetTextSize(0.03);
//   t3.Draw();

//   TGraph * graph4 = toy->getMassCurve(7., 43200., 1);
//   //  graph4->SetLineColor(4);
//   graph4->Draw("C");
//   TLatex t4(205., 4., "12h");
//   t4.SetTextSize(0.03);
//   t4.Draw();

//   TGraph * graph5 = toy->getMassCurve(7., 86400, 1);
//   //  graph5->SetLineColor(5);
//   graph5->Draw("C");
//   TLatex t5(205., 3.5, "1d");
//   t5.SetTextSize(0.03);
//   t5.Draw();

//   TGraph * graph6 = toy->getMassCurve(7., 604800, 1);
//   //  graph6->SetLineColor(6);
//   graph6->Draw("C");
//   TLatex t6(205., 1.5, "1w");
//   t6.SetTextSize(0.03);
//   t6.Draw();



//   c->Update();
//   c->Print("SigVsChi0Mass_Beamgap_7days.png");



//   // interfill expt 7 days
//   TH1F * h = c->DrawFrame(0., 0., 300., 11.);
//   h->SetTitle("Interfill Expt");
//   h->SetYTitle("z-value");
//   h->SetXTitle("Gluino mass/GeV");

// //   TGraph * graph1 = toy->getMassCurve(7., 1.e-6, 2);
// //   graph1->Draw("C");
// //   TLatex t1(205., 5.5, "1 #mus");
// //   t1.SetTextSize(0.03);
// //   t1.Draw();

// //   TGraph * graph2 = toy->getMassCurve(7., 1.e-3, 2);
// //     graph2->SetLineColor(2);
// //   graph2->Draw("C");
// //   TLatex t2(205., 7., "1ms");
// //   t2.SetTextSize(0.03);
// //   t2.Draw();

//   TGraph * graph3 = toy->getMassCurve(7., 3600., 2);
//   //    graph3->SetLineColor(3);
//   graph3->Draw("C");
//   TLatex t3(205., 1., "1h");
//   t3.SetTextSize(0.03);
//   t3.Draw();

//   TGraph * graph4 = toy->getMassCurve(7., 43200., 2);
//   //    graph4->SetLineColor(4);
//   graph4->Draw("C");
//   TLatex t4(205., 8.2, "12h");
//   t4.SetTextSize(0.03);
//   t4.Draw();

//   TGraph * graph5 = toy->getMassCurve(7., 86400, 2);
//   //   graph5->SetLineColor(5);
//   graph5->Draw("C");
//   TLatex t5(205., 7.5, "1d");
//   t5.SetTextSize(0.03);
//   t5.Draw();

//   TGraph * graph6 = toy->getMassCurve(7., 604800, 2);
//   //    graph6->SetLineColor(6);
//   graph6->Draw("C");
//   TLatex t6(205., 3.5, "1w");
//   t6.SetTextSize(0.03);
//   t6.Draw();

//   c->Update();
//   c->Print("SigVsChi0Mass_Interfill_7days.png");


}
