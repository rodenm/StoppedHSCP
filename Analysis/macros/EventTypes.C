{

  TCanvas c1("c1", "c1", 700, 600);
  c1.SetLogy();

  //  TH1D::SetDefaultSumw2();

  TFile file("ntuples/stoppedHSCP_tree_DCSOnly_383d_Fills_1443_1453.root");
  TTree* tree = (TTree*) file.Get("stoppedHSCPTree/StoppedHSCPTree");

  TH1D* h0 = new TH1D("h0", "HLT_StoppedHSCP:E [GeV]:N_{evts}", 100, 0., 500.);
  TH1D* h1 = new TH1D("h1", ":E [GeV]:N_{evts}", 100, 0., 500.);
  TH1D* h2 = new TH1D("h2", ":E [GeV]:N_{evts}", 100, 0., 500.);
  TH1D* h3 = new TH1D("h3", ":E [GeV]:N_{evts}", 100, 0., 500.);
  TH1D* h4 = new TH1D("h4", ":E [GeV]:N_{evts}", 100, 0., 500.);

  tree->Draw("jetE[0]>>h0", "jetE[0]>20.");
  tree->Draw("jetE[0]>>h1", "jetE[0]>20.&&!noiseFilterResult");
  tree->Draw("jetE[0]>>h2", "jetE[0]>20.&&beamHalo_CSCLoose");
  tree->Draw("jetE[0]>>h3", "jetE[0]>20.&&nVtx>0");
  tree->Draw("jetE[0]>>h4", "jetE[0]>20.&&jet_N>4");

  h1.SetLineColor(kRed);
  h2.SetLineColor(kBlue);
  h3.SetLineColor(kGreen);
  h4.SetLineColor(7);

  TLegend leg(0.6, 0.6, 0.8, 0.8);
  leg.AddEntry(h0, "All", "l");
  leg.AddEntry(h1, "HBHE noise", "l");
  leg.AddEntry(h2, "Halo", "l");
  leg.AddEntry(h3, "Vertex", "l");
  leg.AddEntry(h4, "N_{jet}>4", "l");
  leg.SetFillColor(kWhite);
  
  h0->SetTitle("HLT_StoppedHSCP events");
  h0->SetXTitle("E [GeV]");
  h0->SetYTitle("N_{evts}");

  h0->Draw("");
  h1->Draw("SAME H");
  h2->Draw("SAME H");
  h3->Draw("SAME H");
  h4->Draw("SAME H");
  h0->Draw("SAME");

  leg.Draw();

  //  TText text(0.2, 0.85, "Events passing HLT_StoppedHSCP");
  //  text.Draw();

  c1.Print("EventTypes.pdf");

}
