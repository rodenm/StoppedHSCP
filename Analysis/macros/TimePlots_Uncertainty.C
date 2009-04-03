// significance as fn of running time
// for a single mass point

{

  TCanvas* c = new TCanvas("canvas");

  c->Clear();  
  //  c->SetGrid();

  TLine * l1  = new TLine(0., 5., 30., 5.);
  l1->SetLineColor(2);
  l1->SetLineWidth(2);

  TLatex fs(23., 5.05, "5#sigma discovery");
  fs.SetTextSize(0.03);

  TPaveText blurb(22., 8., 29., 10.8);
  TText* l2=blurb.AddText("#sqrt{s} = 10 TeV");
  TText* l3=blurb.AddText("L_{inst} = 10^{32}cm^{-2}s^{-1}");
  TText* l4=blurb.AddText("m_{#tilde{g}}=300 GeV");
  TText* l5=blurb.AddText("#tau_{#tilde{g}}=1day");
  TText* l6=blurb.AddText("30 days");
  //TText* l6=blurb.AddText("60 pb^{-1}");
  blurb.SetFillColor(0);
  blurb.SetShadowColor(4);
  blurb.SetTextAlign(12);
  //  blurb.SetMargin(0.1);

  TLatex p(12., 0.5, "CMS Preliminary");
  p.SetTextSize(0.06);
  p.SetTextColor(9);

  // beamgap expt 30 days
  TH1F * h = c->DrawFrame(0., 0., 30., 11.);
  h->SetTitle("Beamgap Expt");
  h->SetYTitle("Significance");
  h->SetXTitle("Days");

//   TGraphAsymmErrors graph1 = toy->getTimeCurveWithUncertainty(300., 86400., 1);
//   graph1->SetLineColor(1);
//   graph1->SetLineStyle(1);
//   graph1->SetLineWidth(2);
//   graph1->Draw("AC3");

  TMultiGraph* graphs = toy->getTimeCurveBand(300., 86400., 1);

  TGraph lower = (TGraph) graphs->GetListOfGraphs().At(0);
  TGraph central = (TGraph) graphs->GetListOfGraphs().At(1);
  TGraph upper = (TGraph) graphs->GetListOfGraphs().At(2);

  upper->SetLineWidth(-20001);
  upper->SetFillColor(4);
  upper->SetLineColor(4);
  upper->Draw("C");

  TBox box1(1., 0., 5., 2.);
  box1.SetFillColor(4);
  box1.SetLineColor(4);
  box1.Draw();

  TBox box2(7., 7., 30., 11.);
  box2.SetFillColor(4);
  box2.SetLineColor(4);
  box2.Draw();

  lower->SetLineWidth(-10001);
  lower->SetFillColor(0);
  lower->SetLineColor(0);
  lower->Draw("C");

  TBox box3(1., 0., 3., 0.5);
  box3.SetFillColor(0);
  box3.SetLineColor(0);
  box3.Draw();

  central->SetLineWidth(2);
  central->Draw("C");


  l1->Draw();
  fs.Draw();
  blurb.Draw();
  p.Draw();

  c->Update();
  c->Print("SigVsTime_Beamgap_band.png");
  c->Print("SigVsTime_Beamgap_band.eps");

}


