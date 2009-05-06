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

  TLine * l2  = new TLine(0., 1.96, 30., 1.96);
  l2->SetLineColor(2);
  l2->SetLineWidth(2);

  TLatex fs2(23., 2.01, "95% C.L.");
  fs2.SetTextSize(0.03);

  TPaveText blurb(22., 8., 29., 10.8);
  TText* t2=blurb.AddText("#sqrt{s} = 10 TeV");
  TText* t3=blurb.AddText("L_{inst} = 10^{32}cm^{-2}s^{-1}");
  TText* t4=blurb.AddText("m_{#tilde{g}}=300 GeV");
  TText* t5=blurb.AddText("m_{#tilde{#chi}}=100 GeV");
  TText* t5a=blurb.AddText("#tau_{#tilde{g}}=1day");
  TText* t6=blurb.AddText("30 days");
  //TText* l6=blurb.AddText("60 pb^{-1}");
  blurb.SetFillColor(0);
  blurb.SetShadowColor(0);
  blurb.SetTextAlign(12);
  //  blurb.SetMargin(0.1);

  TLatex p(12., 0.5, "CMS Preliminary");
  p.SetTextSize(0.06);
  p.SetTextColor(9);



  // beamgap expt 30 days
  TH1F * h = c->DrawFrame(0., 0., 30., 11.);
  h->SetTitle("Beamgap Expt");
  h->SetYTitle("z-value");
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
  upper->Draw("L");

  TBox box1(1., 0., 5., 2.);
  box1.SetFillColor(4);
  box1.SetLineColor(4);
  box1.Draw();

//   TBox box2(7., 7., 30., 11.);
//   box2.SetFillColor(4);
//   box2.SetLineColor(4);
//   box2.Draw();

  lower->SetLineWidth(-20001);
  lower->SetFillColor(0);
  lower->SetLineColor(0);
  lower->Draw("C");

  TBox box3(1., 0., 5., 0.5);
  box3.SetFillColor(0);
  box3.SetLineColor(0);
  box3.Draw();

  central->SetLineWidth(2);
  central->Draw("C");


  l1->Draw();
  fs.Draw();
//   l2->Draw();
//   fs2.Draw();
  blurb.SetShadowColor(4);
  blurb.Draw();
  p.Draw();
  h.GetXaxis().Draw();

  c->Update();
  c->Print("SigVsTime_Beamgap_m300_band.png");
  c->Print("SigVsTime_Beamgap_m300_band.eps");


  // interfill expt 30 days
  TH1F * h = c->DrawFrame(0., 0., 30., 11.);
  h->SetTitle("Beamgap Expt");
  h->SetYTitle("z-value");
  h->SetXTitle("Days");

//   TGraphAsymmErrors graph1 = toy->getTimeCurveWithUncertainty(300., 86400., 1);
//   graph1->SetLineColor(1);
//   graph1->SetLineStyle(1);
//   graph1->SetLineWidth(2);
//   graph1->Draw("AC3");

  TMultiGraph* graphs = toy->getTimeCurveBand(300., 86400., 2);

  TGraph lower = (TGraph) graphs->GetListOfGraphs().At(0);
  TGraph central = (TGraph) graphs->GetListOfGraphs().At(1);
  TGraph upper = (TGraph) graphs->GetListOfGraphs().At(2);

  upper->SetLineWidth(-20001);
  upper->SetFillColor(4);
  upper->SetLineColor(4);
  upper->Draw("L");

  TBox box4(1., 0., 7., 6.25);
  box4.SetFillColor(4);
  box4.SetLineColor(4);
  box4.Draw();

//   TBox box5(7., 7., 30., 11.);
//   box5.SetFillColor(4);
//   box5.SetLineColor(4);
//   box5.Draw();

  lower->SetLineWidth(-20001);
  lower->SetFillColor(0);
  lower->SetLineColor(0);
  lower->Draw("C");

  TBox box6(1., 0., 7., 1.5);
  box6.SetFillColor(0);
  box6.SetLineColor(0);
  box6.Draw();

  central->SetLineWidth(2);
  central->Draw("C");


  l1->Draw();
  fs.Draw();
//   l2->Draw();
//   fs2.Draw();
  blurb.Draw();
  blurb.SetShadowColor(0);
  p.Draw();
  h.GetXaxis().Draw();

  c->Update();
  c->Print("SigVsTime_Interfill_m300_band.png");
  c->Print("SigVsTime_Interfill_m300_band.eps");


  // combined expt 30 days
  TH1F * h = c->DrawFrame(0., 0., 30., 11.);
  h->SetTitle("Beamgap Expt");
  h->SetYTitle("z-value");
  h->SetXTitle("Days");

//   TGraphAsymmErrors graph1 = toy->getTimeCurveWithUncertainty(300., 86400., 1);
//   graph1->SetLineColor(1);
//   graph1->SetLineStyle(1);
//   graph1->SetLineWidth(2);
//   graph1->Draw("AC3");

  TMultiGraph* graphs = toy->getTimeCurveBand(300., 86400., 0);

  TGraph lower = (TGraph) graphs->GetListOfGraphs().At(0);
  TGraph central = (TGraph) graphs->GetListOfGraphs().At(1);
  TGraph upper = (TGraph) graphs->GetListOfGraphs().At(2);

  upper->SetLineWidth(-20001);
  upper->SetFillColor(4);
  upper->SetLineColor(4);
  upper->Draw("L");

  TBox box7(1., 0., 7., 5.6);
  box7.SetFillColor(4);
  box7.SetLineColor(4);
  box7.Draw();

//   TBox box8(7., 7., 30., 11.);
//   box8.SetFillColor(4);
//   box8.SetLineColor(4);
//   box8.Draw();

  lower->SetLineWidth(-20001);
  lower->SetFillColor(0);
  lower->SetLineColor(0);
  lower->Draw("C");

  TBox box9(1., 0., 7., 1.95);
  box9.SetFillColor(0);
  box9.SetLineColor(0);
  box9.Draw();

  central->SetLineWidth(2);
  central->Draw("C");


  l1->Draw();
  fs.Draw();
//   l2->Draw();
//   fs2.Draw();
  blurb.Draw();
  p.Draw();
  h.GetXaxis().Draw();

  c->Update();
  c->Print("SigVsTime_Combined_m300_band.png");
  c->Print("SigVsTime_Combined_m300_band.eps");



}


