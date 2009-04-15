{

  for (unsigned i=0; i<toy->nExperiments(); ++i) {
    cout << toy->getExperiment(i).lifetime << std::endl;
  }

  TCanvas* c = new TCanvas("canvas");
  // plot 2D histogram of significances

  c->SetGrid();

  // lifetimes { 1.e-6, 1.e-3, 1.e-1, 1., 1.e1, 1.e3, 1.e6 };
  const double ybins[8] = { 1.e-7,
			    5.e-5,
			    1.e-2,
			    5.e-1,
			    5.e0,
			    1.e2,
			    5.e4,
			    1.e7 };
			     
  TStyle::SetPalette(1);


  // 30 days significance contours
  TH2D * hist = new TH2D("test", "Beamgap expt - 30 days", 7, 250., 950., 7, ybins);
  toy->get2DMassLifetimePlot(30., 1, hist);
  hist->SetOption("CONT1Z");
  c->SetLogy(1);
  hist->SetMaximum(10.);
  hist->Draw();
  
  c->Update();
  c->Print("SigContours_Beamgap_30days.png");

  // interfill 30 days 
  TH2D * hist = new TH2D("test", "Beamgap expt - 30 days", 7, 250., 950., 7, ybins);
  toy->get2DMassLifetimePlot(30., 2, hist);
  hist->SetOption("CONT1Z");
  c->SetLogy(1);
  hist->SetMaximum(10.);
  hist->Draw();
  
  c->Update();
  c->Print("SigContours_Interfill_30days.png");


  // beamgap 1 year
  TH2D * hist = new TH2D("test", "Beamgap expt - 1 year", 7, 250., 950., 7, ybins);
  toy->get2DMassLifetimePlot(360., 1, hist);
  hist->SetOption("CONT1Z");
  TStyle::SetPalette(1);
  c->SetLogy(1);
  hist->SetMaximum(10.);
  hist->Draw();

  c->Update();
  c->Print("SigContours_Beamgap_1year.png");


  // interfill 1 year
  TH2D * hist = new TH2D("test", "Interfill expt - 1 year", 7, 250., 950., 7, ybins);
  toy->get2DMassLifetimePlot(360., 2, hist);
  hist->SetOption("CONT1Z");
  TStyle::SetPalette(1);
  c->SetLogy(1);
  hist->SetMaximum(10.);
  hist->Draw();

  c->Update();
  c->Print("SigContours_Interfill_1year.png");


  // beamgap 3 years
  TH2D * hist = new TH2D("test", "Beamgap expt - 3 years", 7, 250., 950., 7, ybins);
  toy->get2DMassLifetimePlot(1080., 1, hist);
  hist->SetOption("CONT1Z");
  TStyle::SetPalette(1);
  c->SetLogy(1);
  hist->SetMaximum(10.);
  hist->Draw();

  c->Update();
  c->Print("SigContours_Beamgap_3years.png");


  // interfill 3 years
  TH2D * hist = new TH2D("test", "Interfill expt - 3 years", 7, 250., 950., 7, ybins);
  toy->get2DMassLifetimePlot(1080., 1, hist);
  hist->SetOption("CONT1Z");
  TStyle::SetPalette(1);
  c->SetLogy(1);
  hist->SetMaximum(10.);
  hist->Draw();

  c->Update();
  c->Print("SigContours_Interfill_3years.png");

}
