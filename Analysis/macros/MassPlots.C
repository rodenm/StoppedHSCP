// significance as a fn of gluino mass (and cross-section)
// for a fixed running time

{

  TCanvas* c = new TCanvas("canvas");
  c->Clear(); 
  c->SetGrid();

  TLine * l1  = new TLine(200., 5., 700., 5.);
  l1->SetLineColor(2);
  l1->SetLineWidth(2);

  TLatex fs(575., 5.05, "5#sigma discovery");
  fs.SetTextSize(0.03);

  TPaveText blurb(565., 9., 680., 10.8);
  TText* l2=blurb.AddText("#sqrt{s} = 10 TeV");
  TText* l3=blurb.AddText("L_{inst} = 10^{32}cm^{-2}s^{-1}");
  TText* l4=blurb.AddText("m_{#tilde{#chi}}=100 GeV");
  TText* l5=blurb.AddText("30 days");
  //TText* l6=blurb.AddText("60 pb^{-1}");
  blurb.SetFillColor(0);
  blurb.SetShadowColor(0);
  blurb.SetTextAlign(12);
  //  blurb.SetMargin(0.1);
  

  // beamgap expt 30 days
  TH1F * h = c->DrawFrame(200., 0., 700., 11.);
  h->SetTitle("Beamgap Expt");
  h->SetYTitle("Significance");
  h->SetXTitle("m_{#tilde{g}} (GeV)");

  TGraph * graph1 = toy->getMassCurve(30., 1.e-6, 1);
  graph1->SetLineColor(1);
  graph1->SetLineStyle(1);
  graph1->SetLineWidth(2);
  graph1->Draw("C");
//   TLatex t1(300., 10., "1 #mus");
//   t1.SetTextSize(0.03);
//   t1.Draw();

  TGraph * graph2 = toy->getMassCurve(30., 1.e-3, 1);
  graph2->SetLineColor(2);
  graph2->SetLineStyle(1);
  graph2->SetLineWidth(2);
  graph2->Draw("C");
//   TLatex t2(425., 8.5, "1ms");
//   t2.SetTextSize(0.03);
//   t2.Draw();

  TGraph * graph3 = toy->getMassCurve(30., 3600., 1);
  graph3->SetLineColor(4);
  graph3->SetLineStyle(1);
  graph3->SetLineWidth(2);
   graph3->Draw("C");
  
  TGraph * graph4 = toy->getMassCurve(30., 43200., 1);
  graph4->SetLineColor(1);
  graph4->SetLineStyle(2);
  graph4->SetLineWidth(2);
   graph4->Draw("C");
  
  TGraph * graph5 = toy->getMassCurve(30., 86400, 1);
  graph5->SetLineColor(2);
  graph5->SetLineStyle(2);
  graph5->SetLineWidth(2);
    graph5->Draw("C");
  
  TGraph * graph6 = toy->getMassCurve(30., 604800, 1);
  graph6->SetLineColor(4);
  graph6->SetLineStyle(2);
  graph6->SetLineWidth(2);
   graph6->Draw("C");
//   TLatex t6(275., 7.5, "1w");
//   t6.SetTextSize(0.03);
//   t6.Draw();

  TLegend leg(565., 6., 680., 8.8, "Gluino lifetime", ""); //#tau_{#tilde{g}}", "");
  //  leg.SetHeader("#tau_{#tilde{g}}");
  leg.SetFillColor(0);
  //  leg.SetMargin(0.05);
  leg.AddEntry(graph1, "1 #mus", "l");
  leg.AddEntry(graph2, "1ms", "l");
  leg.AddEntry(graph3, "1h", "l");
  leg.AddEntry(graph4, "12h", "l");
  leg.AddEntry(graph5, "1d", "l");
  leg.AddEntry(graph6, "1w", "l");


  TLatex p(225., 0.5, "CMS Preliminary");
  p.SetTextSize(0.06);
  p.SetTextColor(9);
  p.Draw();

  l1->Draw();
  fs.Draw();
  blurb.Draw();
  leg.Draw();

  c->Update();
  c->Print("SigVsMass_Beamgap_30days.png");
  c->Print("SigVsMass_Beamgap_30days.eps");


  // interfill expt 30 days
  c->Clear();  
  TH1F * h = c->DrawFrame(200., 0., 700., 11.);  
  h->SetTitle("Beamgap Expt");
  h->SetYTitle("Significance");
  h->SetXTitle("m_{#tilde{g}} (GeV)");

//   TGraph * graph1 = toy->getMassCurve(30., 1.e-6, 2);
//   graph1->SetLineColor(1);
//   graph1->SetLineStyle(1);
//  graph1->SetLineWidth(2);
//   graph1->Draw("C");

//   TGraph * graph2 = toy->getMassCurve(30., 1.e-3, 2);
//   graph2->SetLineColor(2);
//   graph2->SetLineStyle(1);
//  graph2->SetLineWidth(2);
//   graph2->Draw("C");

//   TGraph * graph3 = toy->getMassCurve(30., 3600., 2);
//   graph3->SetLineColor(4);
//   graph3->SetLineStyle(1);
//  graph3->SetLineWidth(2);
//   graph3->Draw("C");
//   TLatex t3(400., 8.5, "1h");
//   t3.SetTextSize(0.03);
//   t3.Draw();

  TGraph * graph4 = toy->getMassCurve(30., 43200., 2);
  graph4->SetLineColor(1);
  graph4->SetLineStyle(2);
  graph4->SetLineWidth(2);
  graph4->Draw("C");

  TGraph * graph5 = toy->getMassCurve(30., 86400, 2);
  graph5->SetLineColor(2);
  graph5->SetLineStyle(2);
  graph5->SetLineWidth(2);
  graph5->Draw("C");
//   TLatex t5(410., 8.5, "1d");
//   t5.SetTextSize(0.03);
//   t5.Draw();

  TGraph * graph6 = toy->getMassCurve(30., 604800, 2);
  graph6->SetLineColor(4);
  graph6->SetLineStyle(2);
  graph6->SetLineWidth(2);
  graph6->Draw("C");
//   TLatex t6(310., 7.5, "1w");
//   t6.SetTextSize(0.03);
//   t6.Draw();

  TLatex p(225., 0.5, "CMS Preliminary");
  p.SetTextSize(0.06);
  p.SetTextColor(9);
  p.Draw();

  leg.Draw();
  l1->Draw();
  fs.Draw();
  blurb.Draw();

  c->Update();
  c->Print("SigVsMass_Interfill_30days.png");
  c->Print("SigVsMass_Interfill_30days.eps");


  // combined expt 30 days
  c->Clear();  
  TH1F * h = c->DrawFrame(200., 0., 700., 11.);  
  h->SetTitle("Combined Expt");
  h->SetYTitle("Significance");
  h->SetXTitle("m_{#tilde{g}} (GeV)");

  TGraph * graph1 = toy->getMassCurve(30., 1.e-6, 0);
  graph1->SetLineColor(1);
  graph1->SetLineStyle(1);
  graph1->SetLineWidth(2);
  graph1->Draw("C");
//   TLatex t1(285., 6.5, "1 #mus");
//   t1.SetTextSize(0.03);
//   t1.Draw();

  TGraph * graph2 = toy->getMassCurve(30., 1.e-3, 0);
  graph2->SetLineColor(2);
  graph2->SetLineStyle(1);
  graph2->SetLineWidth(2);
  graph2->Draw("C");
//   TLatex t2(250., 9.5, "#tau_{#tilde{g}} = 1ms");
//   t2.SetTextSize(0.025);
//   t2.Draw();

  TGraph * graph3 = toy->getMassCurve(30., 3600., 0);
  graph3->SetLineColor(4);
  graph3->SetLineStyle(1);
  graph3->SetLineWidth(2);
  graph3->Draw("C");
//   TLatex t3(335., 10., "1h");
//   t3.SetTextSize(0.03);
//   t3.Draw();

  TGraph * graph4 = toy->getMassCurve(30., 43200., 0);
  graph4->SetLineColor(1);
  graph4->SetLineStyle(2);
  graph4->SetLineWidth(2);
  graph4->Draw("C");

  TGraph * graph5 = toy->getMassCurve(30., 86400, 0);
  graph5->SetLineColor(2);
  graph5->SetLineStyle(2);
  graph5->SetLineWidth(2);
  graph5->Draw("C");
//   TLatex t5(420., 8.5, "1d");
//   t5.SetTextSize(0.03);
//   t5.Draw();

  TGraph * graph6 = toy->getMassCurve(30., 604800, 0);
  graph6->SetLineColor(4);
  graph6->SetLineStyle(2);
  graph6->SetLineWidth(2);
  graph6->Draw("C");
//   TLatex t6(370., 7.5, "1w");
//   t6.SetTextSize(0.03);
//   t6.Draw();

  TLatex p(225., 0.5, "CMS Preliminary");
  p.SetTextSize(0.06);
  p.SetTextColor(9);
  p.Draw();

  leg.Draw();
  l1->Draw();
  fs.Draw();
  blurb.Draw();

  c->Update();
  c->Print("SigVsMass_Combined_30days.png");
  c->Print("SigVsMass_Combined_30days.eps");


//   // beamgap expt 360 days
//   c->Clear();  
//   TH1F * h = c->DrawFrame(0., 0., 1000., 11.);  
//   h->SetTitle("Beamgap Expt");
//   h->SetYTitle("Significance");
//   h->SetXTitle("Gluino mass/GeV");

//   TGraph * graph1 = toy->getMassCurve(360., 1.e-6, 1);
//   graph1->Draw("C");
//   TLatex t1(400., 9.5, "1 #mus");
//   t1.SetTextSize(0.03);
//   t1.Draw();

//   TGraph * graph2 = toy->getMassCurve(360., 1.e-3, 1);
//   graph2->Draw("C");
//   TLatex t2(525., 8.5, "1ms");
//   t2.SetTextSize(0.03);
//   t2.Draw();

// //   TGraph * graph3 = toy->getMassCurve(360., 3600., 1);
// //   graph3->SetLineColor(3);
// //   graph3->Draw("C");

// //   TGraph * graph4 = toy->getMassCurve(360., 43200., 1);
// //   graph4->SetLineColor(1);
// //   graph4->SetLineStyle(2);
// //   graph4->Draw("C");

// //   TGraph * graph5 = toy->getMassCurve(360., 86400, 1);
// //   graph5->SetLineColor(2);
// //   graph5->SetLineStyle(2);
// //   graph5->Draw("C");

//   TGraph * graph6 = toy->getMassCurve(360., 604800, 1);
//   graph6->Draw("C");
//   TLatex t6(400., 7.5, "1w");
//   t6.SetTextSize(0.03);
//   t6.Draw();

//   TLine * l2 = new TLine(0., 5., 1000., 5.);
//   l2->SetLineColor(2);
//   l2->Draw();

//   TLatex p(25., 1.0, "CMS Preliminary");
//   p.SetTextSize(0.06);
//   p.SetTextColor(9);
//   p.Draw();

//   c->Update();
//   c->Print("SigVsMass_Beamgap_1 year.png");


//   // interfill expt 360 days
//   c->Clear();  
//   TH1F * h = c->DrawFrame(0., 0., 1000., 11.);  
//   h->SetTitle("Interfill Expt");
//   h->SetYTitle("Significance");
//   h->SetXTitle("Gluino mass/GeV");

// //   TGraph * graph1 = toy->getMassCurve(360., 1.e-6, 2);
// //   graph1->SetLineColor(1);
// //   graph1->Draw("C");

// //   TGraph * graph2 = toy->getMassCurve(360., 1.e-3, 2);
// //   graph2->SetLineColor(2);
// //   graph2->Draw("C");

//   TGraph * graph3 = toy->getMassCurve(360., 3600., 2);
//   graph3->Draw("C");
//   TLatex t3(300., 6.5, "1h");
//   t3.SetTextSize(0.03);
//   t3.Draw();

// //   TGraph * graph4 = toy->getMassCurve(360., 43200., 2);
// //   graph4->Draw("C");

// //   TGraph * graph5 = toy->getMassCurve(360., 86400, 2);
// //   graph5->Draw("C");
// //   TLatex t5(450., 7.5, "1d");
// //   t5.SetTextSize(0.03);
// //   t5.Draw();

//   TGraph * graph6 = toy->getMassCurve(360., 604800, 2);
//   graph6->Draw("C");
//   TLatex t6(525., 8.5, "1w");
//   t6.SetTextSize(0.03);
//   t6.Draw();

//   TLine * l2 = new TLine(0., 5., 1000., 5.);
//   l2->SetLineColor(2);
//   l2->Draw();

//   TLatex p(25., 1.0, "CMS Preliminary");
//   p.SetTextSize(0.06);
//   p.SetTextColor(9);
//   p.Draw();

//   c->Update();
//   c->Print("SigVsMass_Interfill_1year.png");


//   // beamgap expt 3 years
//   c->Clear();  
//   TH1F * h = c->DrawFrame(0., 0., 1000., 11.);  
//   h->SetTitle("Beamgap Expt");
//   h->SetYTitle("Significance");
//   h->SetXTitle("Gluino mass/GeV");

//   TGraph * graph1 = toy->getMassCurve(1080., 1.e-6, 1);
//   graph1->SetLineColor(1);
//   graph1->Draw("C");

//   TGraph * graph2 = toy->getMassCurve(1080., 1.e-3, 1);
//   graph2->SetLineColor(2);
//   graph2->Draw("C");

//   TGraph * graph3 = toy->getMassCurve(1080., 3600., 1);
//   graph3->SetLineColor(4);
//   graph3->Draw("C");

//   TGraph * graph4 = toy->getMassCurve(1080., 43200., 1);
//   graph4->SetLineColor(1);
//   graph4->SetLineStyle(2);
//   graph4->Draw("C");

//   TGraph * graph5 = toy->getMassCurve(1080., 86400, 1);
//   graph5->SetLineColor(2);
//   graph5->SetLineStyle(2);
//   graph5->Draw("C");

//   TGraph * graph6 = toy->getMassCurve(1080., 604800, 1);
//   graph6->SetLineColor(4);
//   graph6->SetLineStyle(2);
//   graph6->Draw("C");

//   TLine * l2 = new TLine(0., 5., 1000., 5.);
//   l2->SetLineColor(2);
//   l2->Draw();

//   c->Update();
//   c->Print("SigVsMass_Beamgap_3years.png");


//   // interfill expt 3 years
//   c->Clear();  
//   TH1F * h = c->DrawFrame(0., 0., 1000., 11.);  
//   h->SetTitle("Interfill Expt");
//   h->SetYTitle("Significance");
//   h->SetXTitle("Gluino mass/GeV");

//   TGraph * graph1 = toy->getMassCurve(1080., 1.e-6, 2);
//   graph1->SetLineColor(1);
//   graph1->Draw("C");

//   TGraph * graph2 = toy->getMassCurve(1080., 1.e-3, 2);
//   graph2->SetLineColor(2);
//   graph2->Draw("C");

//   TGraph * graph3 = toy->getMassCurve(1080., 3600., 2);
//   graph3->SetLineColor(4);
//   graph3->Draw("C");

//   TGraph * graph4 = toy->getMassCurve(1080., 43200., 2);
//   graph4->SetLineColor(1);
//   graph4->SetLineStyle(2);
//   graph4->Draw("C");

//   TGraph * graph5 = toy->getMassCurve(1080., 86400, 2);
//   graph5->SetLineColor(2);
//   graph5->SetLineStyle(2);
//   graph5->Draw("C");

//   TGraph * graph6 = toy->getMassCurve(1080., 604800, 2);
//   graph6->SetLineColor(4);
//   graph6->SetLineStyle(2);
//   graph6->Draw("C");

//   TLine * l2 = new TLine(0., 5., 1000., 5.);
//   l2->SetLineColor(2);
//   l2->Draw();

//   c->Update();
//   c->Print("SigVsMass_Interfill_3years.png");

}
