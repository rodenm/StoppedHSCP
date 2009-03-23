// significance as a fn of gluino mass (and cross-section)
// for a fixed running time

{

  TCanvas* c = new TCanvas("canvas");
  c->Clear(); 
  c->SetGrid();

  
  // beamgap expt 30 days
  TH1F * h = c->DrawFrame(0., 0., 1000., 11.);
  h->SetTitle("Beamgap Expt");
  h->SetYTitle("Significance");
  h->SetXTitle("Gluino mass/GeV");


  TGraph * graph1 = toy->getMassCurve(30., 1.e-6, 1);
  graph1->SetLineColor(1);
  graph1->Draw("L");

  TGraph * graph2 = toy->getMassCurve(30., 1.e-3, 1);
  graph2->SetLineColor(2);
  graph2->Draw("L");

  TGraph * graph3 = toy->getMassCurve(30., 3600., 1);
  graph3->SetLineColor(4);
  graph3->Draw("L");

  TGraph * graph4 = toy->getMassCurve(30., 43200., 1);
  graph4->SetLineColor(1);
  graph4->SetLineStyle(2);
  graph4->Draw("L");

  TGraph * graph5 = toy->getMassCurve(30., 86400, 1);
  graph5->SetLineColor(2);
  graph5->SetLineStyle(2);
  graph5->Draw("L");

  TGraph * graph6 = toy->getMassCurve(30., 604800, 1);
  graph6->SetLineColor(4);
  graph6->SetLineStyle(2);
  graph6->Draw("L");

  TLine * l2 = new TLine(0., 5., 1000., 5.);
  l2->SetLineColor(2);
  l2->Draw();

  c->Update();
  c->Print("SigVsMass_Beamgap_30days.png");


  // interfill expt 30 days
  c->Clear();  
  TH1F * h = c->DrawFrame(0., 0., 1000., 11.);  
  h->SetTitle("Beamgap Expt");
  h->SetYTitle("Significance");
  h->SetXTitle("Gluino mass/GeV");

  TGraph * graph1 = toy->getMassCurve(30., 1.e-6, 2);
  graph1->SetLineColor(1);
  graph1->Draw("L");

  TGraph * graph2 = toy->getMassCurve(30., 1.e-3, 2);
  graph2->SetLineColor(2);
  graph2->Draw("L");

  TGraph * graph3 = toy->getMassCurve(30., 3600., 2);
  graph3->SetLineColor(4);
  graph3->Draw("L");

  TGraph * graph4 = toy->getMassCurve(30., 43200., 2);
  graph4->SetLineColor(1);
  graph4->SetLineStyle(2);
  graph4->Draw("L");

  TGraph * graph5 = toy->getMassCurve(30., 86400, 2);
  graph5->SetLineColor(2);
  graph5->SetLineStyle(2);
  graph5->Draw("L");

  TGraph * graph6 = toy->getMassCurve(30., 604800, 2);
  graph6->SetLineColor(4);
  graph6->SetLineStyle(2);
  graph6->Draw("L");

  TLine * l2 = new TLine(0., 5., 1000., 5.);
  l2->SetLineColor(2);
  l2->Draw();

  c->Update();
  c->Print("SigVsMass_Interfill_30days.png");


  // beamgap expt 360 days
  c->Clear();  
  TH1F * h = c->DrawFrame(0., 0., 1000., 11.);  
  h->SetTitle("Beamgap Expt");
  h->SetYTitle("Significance");
  h->SetXTitle("Gluino mass/GeV");

  TGraph * graph1 = toy->getMassCurve(360., 1.e-6, 1);
  graph1->SetLineColor(1);
  graph1->Draw("L");

  TGraph * graph2 = toy->getMassCurve(360., 1.e-3, 1);
  graph2->SetLineColor(2);
  graph2->Draw("L");

  TGraph * graph3 = toy->getMassCurve(360., 3600., 1);
  graph3->SetLineColor(4);
  graph3->Draw("L");

  TGraph * graph4 = toy->getMassCurve(360., 43200., 1);
  graph4->SetLineColor(1);
  graph4->SetLineStyle(2);
  graph4->Draw("L");

  TGraph * graph5 = toy->getMassCurve(360., 86400, 1);
  graph5->SetLineColor(2);
  graph5->SetLineStyle(2);
  graph5->Draw("L");

  TGraph * graph6 = toy->getMassCurve(360., 604800, 1);
  graph6->SetLineColor(4);
  graph6->SetLineStyle(2);
  graph6->Draw("L");

  TLine * l2 = new TLine(0., 5., 1000., 5.);
  l2->SetLineColor(2);
  l2->Draw();

  c->Update();
  c->Print("SigVsMass_Beamgap_1 year.png");


  // interfill expt 360 days
  c->Clear();  
  TH1F * h = c->DrawFrame(0., 0., 1000., 11.);  
  h->SetTitle("Interfill Expt");
  h->SetYTitle("Significance");
  h->SetXTitle("Gluino mass/GeV");

  TGraph * graph1 = toy->getMassCurve(360., 1.e-6, 2);
  graph1->SetLineColor(1);
  graph1->Draw("L");

  TGraph * graph2 = toy->getMassCurve(360., 1.e-3, 2);
  graph2->SetLineColor(2);
  graph2->Draw("L");

  TGraph * graph3 = toy->getMassCurve(360., 3600., 2);
  graph3->SetLineColor(4);
  graph3->Draw("L");

  TGraph * graph4 = toy->getMassCurve(360., 43200., 2);
  graph4->SetLineColor(1);
  graph4->SetLineStyle(2);
  graph4->Draw("L");

  TGraph * graph5 = toy->getMassCurve(360., 86400, 2);
  graph5->SetLineColor(2);
  graph5->SetLineStyle(2);
  graph5->Draw("L");

  TGraph * graph6 = toy->getMassCurve(360., 604800, 2);
  graph6->SetLineColor(4);
  graph6->SetLineStyle(2);
  graph6->Draw("L");

  TLine * l2 = new TLine(0., 5., 1000., 5.);
  l2->SetLineColor(2);
  l2->Draw();

  c->Update();
  c->Print("SigVsMass_Interfill_1year.png");


  // beamgap expt 3 years
  c->Clear();  
  TH1F * h = c->DrawFrame(0., 0., 1000., 11.);  
  h->SetTitle("Beamgap Expt");
  h->SetYTitle("Significance");
  h->SetXTitle("Gluino mass/GeV");

  TGraph * graph1 = toy->getMassCurve(1080., 1.e-6, 1);
  graph1->SetLineColor(1);
  graph1->Draw("L");

  TGraph * graph2 = toy->getMassCurve(1080., 1.e-3, 1);
  graph2->SetLineColor(2);
  graph2->Draw("L");

  TGraph * graph3 = toy->getMassCurve(1080., 3600., 1);
  graph3->SetLineColor(4);
  graph3->Draw("L");

  TGraph * graph4 = toy->getMassCurve(1080., 43200., 1);
  graph4->SetLineColor(1);
  graph4->SetLineStyle(2);
  graph4->Draw("L");

  TGraph * graph5 = toy->getMassCurve(1080., 86400, 1);
  graph5->SetLineColor(2);
  graph5->SetLineStyle(2);
  graph5->Draw("L");

  TGraph * graph6 = toy->getMassCurve(1080., 604800, 1);
  graph6->SetLineColor(4);
  graph6->SetLineStyle(2);
  graph6->Draw("L");

  TLine * l2 = new TLine(0., 5., 1000., 5.);
  l2->SetLineColor(2);
  l2->Draw();

  c->Update();
  c->Print("SigVsMass_Beamgap_3years.png");


  // interfill expt 3 years
  c->Clear();  
  TH1F * h = c->DrawFrame(0., 0., 1000., 11.);  
  h->SetTitle("Interfill Expt");
  h->SetYTitle("Significance");
  h->SetXTitle("Gluino mass/GeV");

  TGraph * graph1 = toy->getMassCurve(1080., 1.e-6, 2);
  graph1->SetLineColor(1);
  graph1->Draw("L");

  TGraph * graph2 = toy->getMassCurve(1080., 1.e-3, 2);
  graph2->SetLineColor(2);
  graph2->Draw("L");

  TGraph * graph3 = toy->getMassCurve(1080., 3600., 2);
  graph3->SetLineColor(4);
  graph3->Draw("L");

  TGraph * graph4 = toy->getMassCurve(1080., 43200., 2);
  graph4->SetLineColor(1);
  graph4->SetLineStyle(2);
  graph4->Draw("L");

  TGraph * graph5 = toy->getMassCurve(1080., 86400, 2);
  graph5->SetLineColor(2);
  graph5->SetLineStyle(2);
  graph5->Draw("L");

  TGraph * graph6 = toy->getMassCurve(1080., 604800, 2);
  graph6->SetLineColor(4);
  graph6->SetLineStyle(2);
  graph6->Draw("L");

  TLine * l2 = new TLine(0., 5., 1000., 5.);
  l2->SetLineColor(2);
  l2->Draw();

  c->Update();
  c->Print("SigVsMass_Interfill_3years.png");

}
