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
  h->SetYTitle("Days");

  TGraph * graph1 = toy->getLifetimeCurve(300., 1.e-6, 1);
  graph1->SetLineColor(1);
  graph1->Draw("C");

  TGraph * graph2 = toy->getLifetimeCurve(300., 1.e-3, 1);
  graph2->SetLineColor(2);
  graph2->Draw("C");

  TGraph * graph3 = toy->getLifetimeCurve(300., 3600., 1);
  graph3->SetLineColor(4);
  graph3->Draw("C");

  TGraph * graph4 = toy->getLifetimeCurve(300., 43200., 1);
  graph4->SetLineColor(1);
  graph4->SetLineStyle(2);
  graph4->Draw("C");

  TGraph * graph5 = toy->getLifetimeCurve(300., 86400, 1);
  graph5->SetLineColor(2);
  graph5->SetLineStyle(2);
  graph5->Draw("C");

  TGraph * graph6 = toy->getLifetimeCurve(300., 604800, 1);
  graph6->SetLineColor(4);
  graph6->SetLineStyle(2);
  graph6->Draw("C");

  TLine * l1  = new TLine(0., 5., 35., 5.);
  l1->SetLineColor(2);
  l1->Draw();

  c->Update();
  c->Print("SigVsTime_Beamgap_m300.png");

  // Interfill expt 30 days
  c->Clear();  
  TH1F * h = c->DrawFrame(0., 0., 30., 11.);
  h->SetTitle("Interfill Expt");
  h->SetYTitle("Significance");
  h->SetYTitle("Days");

  TGraph * graph1 = toy->getLifetimeCurve(300., 1.e-6, 2);
  graph1->SetLineColor(1);
  graph1->Draw("C");

  TGraph * graph2 = toy->getLifetimeCurve(300., 1.e-3, 2);
  graph2->SetLineColor(2);
  graph2->Draw("C");

  TGraph * graph3 = toy->getLifetimeCurve(300., 3600., 2);
  graph3->SetLineColor(4);
  graph3->Draw("C");

  TGraph * graph4 = toy->getLifetimeCurve(300., 43200., 2);
  graph4->SetLineColor(1);
  graph4->SetLineStyle(2);
  graph4->Draw("C");

  TGraph * graph5 = toy->getLifetimeCurve(300., 86400, 2);
  graph5->SetLineColor(2);
  graph5->SetLineStyle(2);
  graph5->Draw("C");

  TGraph * graph6 = toy->getLifetimeCurve(300., 604800, 2);
  graph6->SetLineColor(4);
  graph6->SetLineStyle(2);
  graph6->Draw("C");

  l1->Draw();

  c->Update();
  c->Print("SigVsTime_Interfill_m300.png");




}


