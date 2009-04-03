// significance as fn of running time
// for a single mass point

{

  TCanvas* c = new TCanvas("canvas");

  c->Clear();  
  c->SetGrid();

  // beamgap expt 30 days
  TH1F * h = c->DrawFrame(0., 0., 30., 11.);
  h->SetTitle("Beamgap Expt");
  h->SetYTitle("Significance");
  h->SetXTitle("Days");

  TGraph * graph1 = toy->getLifetimeCurve(300., 1.e-6, 1);
  graph1->Draw("C");
  TLatex t1(9., 9.5, "1 #mus");
  t1.SetTextSize(0.03);
  t1.Draw();

  TGraph * graph2 = toy->getLifetimeCurve(300., 1.e-3, 1);
  graph2->Draw("C");
  TLatex t2(3.8, 10.3, "1ms");
  t2.SetTextSize(0.03);
  t2.Draw();

  TGraph * graph3 = toy->getLifetimeCurve(300., 3600., 1);
  graph3->Draw("C");
  TLatex t3(8., 10.3, "1h");
  t3.SetTextSize(0.03);
  t3.Draw();

  TGraph * graph4 = toy->getLifetimeCurve(300., 43200., 1);
  graph4->Draw("C");
  TLatex t4(15.5, 10., "12h");
  t4.SetTextSize(0.03);
  t4.Draw();

  TGraph * graph5 = toy->getLifetimeCurve(300., 86400, 1);
  graph5->Draw("C");
  TLatex t5(19, 9., "1d");
  t5.SetTextSize(0.03);
  t5.Draw();

  TGraph * graph6 = toy->getLifetimeCurve(300., 604800, 1);
  graph6->Draw("C");
  TLatex t6(23., 7.5, "1w");
  t6.SetTextSize(0.03);
  t6.Draw();

//   TLatex t7(20., 9., "Gluino lifetime");
//   t7.SetTextSize(0.03);
//   t7.Draw();

  TLine * l1  = new TLine(0., 5., 30., 5.);
  l1->SetLineColor(2);
  l1->Draw();

  TLatex p(12., 2.2, "CMS Preliminary");
  p.SetTextSize(0.06);
  p.SetTextColor(9);
  p.Draw();

  c->Update();
  c->Print("SigVsTime_Beamgap_m300.png");

  // Interfill expt 30 days
  c->Clear();  
  TH1F * h = c->DrawFrame(0., 0., 30., 11.);
  h->SetTitle("Interfill Expt");
  h->SetYTitle("Significance");
  h->SetXTitle("Days");

//   TGraph * graph1 = toy->getLifetimeCurve(300., 1.e-6, 2);
//   graph1->Draw("C");
//   TLatex t1(8.5, 10.3, "1 #mus");
//   t1.SetTextSize(0.03);
//   t1.Draw();

//   TGraph * graph2 = toy->getLifetimeCurve(300., 1.e-3, 2);
//   graph2->Draw("C");
//   TLatex t2(8.5, 10.3, "1ms");
//   t2.SetTextSize(0.03);
//   t2.Draw();

  TGraph * graph3 = toy->getLifetimeCurve(300., 3600., 2);
  graph3->Draw("C");
  TLatex t3(21., 2.8, "1h");
  t3.SetTextSize(0.03);
  t3.Draw();

  TGraph * graph4 = toy->getLifetimeCurve(300., 43200., 2);
  graph4->Draw("C");
  TLatex t4(3.6., 9.5, "12h");
  t4.SetTextSize(0.03);
  t4.Draw();

  TGraph * graph5 = toy->getLifetimeCurve(300., 86400, 2);
  graph5->Draw("C");
  TLatex t5(6.5, 9.5, "1d");
  t5.SetTextSize(0.03);
  t5.Draw();

  TGraph * graph6 = toy->getLifetimeCurve(300., 604800, 2);
  graph6->Draw("C");
  TLatex t6(11., 9., "1w");
  t6.SetTextSize(0.03);
  t6.Draw();

//   TLatex t7(20., 9., "Gluino lifetime");
//   t7.SetTextSize(0.03);
//   t7.Draw();

  l1->Draw();

  TLatex p(12., 6.8, "CMS Preliminary");
  p.SetTextSize(0.06);
  p.SetTextColor(9);
  p.Draw();

  c->Update();
  c->Print("SigVsTime_Interfill_m300.png");




}


