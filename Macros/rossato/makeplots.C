{
  int n_lifetimes = 6;
  int n_runtimes = 4;
  int n_data = 24;

  std::cout << "Starting up..." << std::endl;
  std::ifstream infile("discovery_input_lumi32_feb02_09.txt");

  float lifetimes[n_lifetimes] = {1e-6, 1e-3, 3600, 43200, 86400, 604800};
  float runtimes [n_runtimes ] = {3, 7, 14, 30};
  std::string s_lifetimes[n_lifetimes] = { "1e-6 s", "1e-3 s", "1 hr", "12 hr", "1 day", "1 wk" };

  float bounds_x[2] = {0, 30};
  float bounds_y[2] = {0, 12};

  /* These are good for the 10^31 calculations
  int n_lifetimes = 6;
  int n_runtimes = 5;
  int n_data = 30;

  std::cout << "Starting up..." << std::endl;
  std::ifstream infile("discovery_input_lumi31_revised.txt");

  float lifetimes[n_lifetimes] = {1e-6, 1e-3, 1, 60, 3600, 86400};
  float runtimes [n_runtimes ] = {7, 14, 30, 90, 360};
  std::string s_lifetimes[n_lifetimes] = { "1e-6 s", "1e-3 s", "1 s", "1 m", "1 hr", "1 day" };

  float bounds_x[2] = {0, 360};
  float bounds_y[2] = {0, 5};
  */

  // no more parameters to adjust after this line

  float total_input[n_data];
  float beam_input[n_data];
  float cosmic_input[n_data];

  std::string junk;
  for (int i = 0; i < n_data; i++) {
    infile >> junk >> junk >> total_input[i] >> beam_input[i] >> cosmic_input[i];
  }
  infile.close();

  TGraph *total_graphs [n_lifetimes];
  TGraph *beam_graphs  [n_lifetimes];
  TGraph *cosmic_graphs[n_lifetimes];
  TText  *t_lifetimes[n_lifetimes];
  
  for (int i = 0; i < n_lifetimes; i++) {
    total_graphs[i]  = new TGraph(n_runtimes, runtimes, total_input  + (i*n_runtimes));
    beam_graphs[i]   = new TGraph(n_runtimes, runtimes, beam_input   + (i*n_runtimes));
    cosmic_graphs[i] = new TGraph(n_runtimes, runtimes, cosmic_input + (i*n_runtimes));

    t_lifetimes[i] = new TText(bounds_x[1], total_input[(i+1)*n_runtimes-1], s_lifetimes[i].c_str());
  }

  TCanvas ca, cb, cc;
  ca.cd();
  
  // make total chart

  TGraph *bounds = new TGraph(2, bounds_x, bounds_y);
  bounds->Draw("a*");
  bounds->SetMarkerColor(0);
  bounds->SetMarkerStyle(kDot);

  bounds->GetXaxis()->SetTitle("Days");
  bounds->GetYaxis()->SetTitle("Significance");

  for (int i = 0; i < n_lifetimes; i++) {
    total_graphs[i]->Draw("c");
    t_lifetimes[i]->Draw();
  }

  TText total_title(0, 5, "Beam and Interfill Periods");
  total_title.Draw();
  TText tx_lifetime(bounds_x[1], 5, "Lifetime");
  tx_lifetime.Draw();

  TLine l(bounds_x[0], 5, bounds_x[1], 5);
  l.SetLineColor(42);
  l.SetLineWidth(3);
  l.Draw();


  // make beam plot
  cb.cd();
  bounds->Draw("a*");
  TText *b_lifetimes[n_lifetimes];
  for (int i = 0; i < n_lifetimes; i++) {
    beam_graphs[i]->Draw("c");
    b_lifetimes[i] = new TText(bounds_x[1], beam_input[(i+1)*n_runtimes-1], s_lifetimes[i].c_str());
    b_lifetimes[i]->Draw();
  }

  TText beam_title(0, 5, "Beam Periods Only");
  beam_title.Draw();
  tx_lifetime.Draw();
  l.Draw();
  
  
  // make cosmic plot
  cc.cd();
  bounds->Draw("a*");
  TText *c_lifetimes[n_lifetimes];
  for (int i = 0; i < n_lifetimes; i++) {
    cosmic_graphs[i]->Draw("c");
    c_lifetimes[i] = new TText(bounds_x[1], cosmic_input[(i+1)*n_runtimes-1], s_lifetimes[i].c_str());
    c_lifetimes[i]->Draw();
  }

  TText cosmic_title(0, 5, "Interfill Periods Only");
  cosmic_title.Draw();
  tx_lifetime.Draw();
  l.Draw();
  
}
