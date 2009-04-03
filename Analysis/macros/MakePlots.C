// Make plots from Toy MC
// run RunMany first!

{

  for (unsigned i=0; i<toy->nExperiments(); ++i) {
    cout << toy->getExperiment(i).lifetime << std::endl;
  }

  TCanvas* c = new TCanvas("canvas");

  // plot significance as fn of running time
  // interfill expt, 300 GeV gluino, various lifetimes

  c->Clear();  
  c->SetGrid();
  TH1F * h = c->DrawFrame(0., 0., 35., 11.);
  h->SetTitle("Beamgap Expt");
  h->SetYTitle("Significance");
  h->SetYTitle("Days");

  TGraph * graph1 = toy->getLifetimeCurve(300., 1.e-6, 1);
  graph1->SetLineColor(1);
  graph1->Draw("C");

  TGraph * graph1 = toy->getLifetimeCurve(300., 1.e-3, 1);
  graph1->SetLineColor(2);
  graph1->Draw("C");

  TGraph * graph1 = toy->getLifetimeCurve(300., 3600., 1);
  graph1->SetLineColor(3);
  graph1->Draw("C");

  TGraph * graph1 = toy->getLifetimeCurve(300., 43200., 1);
  graph1->SetLineColor(4);
  graph1->Draw("C");

  TGraph * graph2 = toy->getLifetimeCurve(300., 86400, 1);
  graph2->SetLineColor(5);
  graph2->Draw("C");

  TGraph * graph3 = toy->getLifetimeCurve(300., 604800, 1);
  graph3->SetLineColor(6);
  graph3->Draw("C");

  TLine * l1  = new TLine(0., 5., 35., 5.);
  l1->SetLineColor(2);
  l1->Draw();

  c->Update();
  c->Print("beamgapSig_300_100.png");

  // plot significance as fn of running time
  // interfill expt, 300 GeV gluino, various lifetimes
  c->Clear();  
  TH1F * h = c->DrawFrame(0., 0., 35., 11.);
  h->SetTitle("Interfill Expt");
  h->SetYTitle("Significance");
  h->SetYTitle("Days");

  TGraph * graph1 = toy->getLifetimeCurve(300., 1.e-6, 2);
  graph1->SetLineColor(1);
  graph1->Draw("C");

  TGraph * graph1 = toy->getLifetimeCurve(300., 1.e-3, 2);
  graph1->SetLineColor(2);
  graph1->Draw("C");

  TGraph * graph1 = toy->getLifetimeCurve(300., 3600., 2);
  graph1->SetLineColor(3);
  graph1->Draw("C");

  TGraph * graph1 = toy->getLifetimeCurve(300., 43200., 2);
  graph1->SetLineColor(4);
  graph1->Draw("C");

  TGraph * graph2 = toy->getLifetimeCurve(300., 86400, 2);
  graph2->SetLineColor(5);
  graph2->Draw("C");

  TGraph * graph3 = toy->getLifetimeCurve(300., 604800, 2);
  graph3->SetLineColor(6);
  graph3->Draw("C");

  l1->Draw();

  c->Update();
  c->Print("interfillSig_300_100.png");


  // mass plots
  c->Clear();  
  TH1F * h = c->DrawFrame(0., 0., 1000., 11.);
  h->SetTitle("Beamgap Expt");
  h->SetYTitle("Significance");
  h->SetXTitle("Gluino mass/GeV");


  TGraph * graph1 = toy->getMassCurve(30., 1.e-6, 1);
  graph1->SetLineColor(1);
  graph1->Draw("L");

  TGraph * graph1 = toy->getMassCurve(30., 1.e-3, 1);
  graph1->SetLineColor(2);
  graph1->Draw("L");

  TGraph * graph1 = toy->getMassCurve(30., 3600., 1);
  graph1->SetLineColor(3);
  graph1->Draw("L");

  TGraph * graph1 = toy->getMassCurve(30., 43200., 1);
  graph1->SetLineColor(4);
  graph1->Draw("L");

  TGraph * graph2 = toy->getMassCurve(30., 86400, 1);
  graph2->SetLineColor(5);
  graph2->Draw("L");

  TGraph * graph3 = toy->getMassCurve(30., 604800, 1);
  graph3->SetLineColor(6);
  graph3->Draw("L");

  TLine * l2 = new TLine(0., 5., 1000., 5.);
  l2->SetLineColor(2);
  l2->Draw();

  c->Update();
  c->Print("beamgapSig_30days.png");



  // mass plots
  c->Clear();  
  TH1F * h = c->DrawFrame(0., 0., 1000., 11.);  
  h->SetTitle("Beamgap Expt");
  h->SetYTitle("Significance");
  h->SetXTitle("Gluino mass/GeV");

  TGraph * graph1 = toy->getMassCurve(360., 1.e-6, 1);
  graph1->SetLineColor(1);
  graph1->Draw("L");

  TGraph * graph1 = toy->getMassCurve(360., 1.e-3, 1);
  graph1->SetLineColor(2);
  graph1->Draw("L");

  TGraph * graph1 = toy->getMassCurve(360., 3600., 1);
  graph1->SetLineColor(3);
  graph1->Draw("L");

  TGraph * graph1 = toy->getMassCurve(360., 43200., 1);
  graph1->SetLineColor(4);
  graph1->Draw("L");

  TGraph * graph2 = toy->getMassCurve(360., 86400, 1);
  graph2->SetLineColor(5);
  graph2->Draw("L");

  TGraph * graph3 = toy->getMassCurve(360., 604800, 1);
  graph3->SetLineColor(6);
  graph3->Draw("L");

  TLine * l2 = new TLine(0., 5., 1000., 5.);
  l2->SetLineColor(2);
  l2->Draw();

  c->Update();
  c->Print("beamgapSig_360days.png");


  // test
  TGraph * graph4 = toy->getLifetimeCurve(300., 1., 1);
  graph4->SetLineColor(1);
  graph4->Draw("C");

  c->Update();
  c->Print("test.png");


}


