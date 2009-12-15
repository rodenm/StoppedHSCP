

{

  gROOT->ProcessLine(".L macros/Style.C");

  // set plot style
  setTDRStyle();
  gROOT->ForceStyle();

  gStyle->SetHistFillStyle(0);
  gStyle->SetHistLineStyle(1);
  gStyle->SetHistLineColor(1);

  TFile craft08("22X_Ben/BasicHistos_Ben_CRAFT08_22x_Ben.root","read");
  TFile craft09("v12/BasicHistos_Ben_CRAFT09_31X.root","read");


  TPostScript* ps = new TPostScript("CRAFT08_22X_vs_CRAFT09_31X.ps");
  TCanvas* canvas = new TCanvas("canvas");

  canvas->SetLogy(0);


//   TH1D* hl1et = (TH1D*)craft09.Get("hl1et");
//   hl1et->SetXTitle("E (GeV)");
//   hl1et->SetYTitle("Hz / 2 GeV");
//   hl1et->Draw("HIST");
//   TH1D* hl1et08 = (TH1D*)craft08.Get("hl1et");
//   hl1et08->SetLineColor(2);
//   hl1et08->Draw("HIST SAME");
//   canvas->Update();

//   TH1D* hl1eta = (TH1D*)craft09.Get("hl1eta");
//   hl1eta->SetXTitle("#eta");
//   hl1eta->SetYTitle("Hz / 0.1");
//   hl1eta->Draw("HIST");
//   TH1D* hl1eta08 = (TH1D*)craft08.Get("hl1eta");
//   hl1eta08->SetLineColor(2);
//   hl1eta08->Draw("HIST SAME");
//   //  canvas->Update();

//   TH1D* hl1phi = (TH1D*)craft09.Get("hl1phi");
//   hl1phi->SetXTitle("E (GeV)");
//   hl1phi->SetYTitle("Hz / #pi/30");
//   hl1phi->Draw("HIST");
//   TH1D* hl1phi08 = (TH1D*)craft08.Get("hl1phi");
//   hl1phi08->SetLineColor(2);
//   hl1phi08->Draw("HIST SAME");
  //  canvas->Update();

  TH1D* hjete08 = (TH1D*)craft08.Get("hjete2");
  hjete08->SetXTitle("E (GeV)");
  hjete08->SetYTitle("Hz / 2 GeV");
  hjete08->SetLineColor(2);
  TH1D* hjete = (TH1D*)craft09.Get("hjete2");
  hjete->SetXTitle("E (GeV)");
  hjete->SetYTitle("Hz / 2 GeV");
  hjete->Draw("HIST");
  hjete08->Draw("HIST SAME");
  canvas->Update();

  TH1D* hjeteta08 = (TH1D*)craft08.Get("hjeteta");
  hjeteta08->SetXTitle("#eta");
  hjeteta08->SetYTitle("Hz / 0.1");
  hjeteta08->SetLineColor(2);
  TH1D* hjeteta = (TH1D*)craft09.Get("hjeteta");
  hjeteta->SetXTitle("#eta");
  hjeteta->SetYTitle("Hz / 0.1");
  hjeteta08->Draw("HIST");
  hjeteta->Draw("HIST SAME");
  canvas->Update();

  TH1D* hjetphi = (TH1D*)craft09.Get("hjetphi");
  hjetphi->SetXTitle("#phi");
  hjetphi->SetYTitle("Hz / #pi/30");
  TH1D* hjetphi08 = (TH1D*)craft08.Get("hjetphi");
  hjetphi08->SetXTitle("#phi");
  hjetphi08->SetYTitle("Hz / #pi/30");
  hjetphi08->SetLineColor(2);
  hjetphi08->Draw("HIST");
  hjetphi->Draw("HIST SAME");
  canvas->Update();

  TH1D* hjetem = (TH1D*)craft09.Get("hjetem");
  hjetem->SetXTitle("E_{ECAL} / GeV");
  hjetem->SetYTitle("Hz / 2 GeV");
  TH1D* hjetem08 = (TH1D*)craft08.Get("hjetem");
  hjetem08->SetXTitle("E_{ECAL} / GeV");
  hjetem08->SetYTitle("Hz / 2 GeV");
  hjetem08->SetLineColor(2);
  hjetem08->Draw("HIST");
  hjetem->Draw("HIST SAME");
  canvas->Update();

  TH1D* hjethad = (TH1D*)craft09.Get("hjethad");
  hjethad->SetXTitle("E_{HCAL} / GeV");
  hjethad->SetYTitle("Hz / 2 GeV");
  TH1D* hjethad08 = (TH1D*)craft08.Get("hjethad");
  hjethad08->SetXTitle("E_{HCAL} / GeV");
  hjethad08->SetYTitle("Hz / 2 GeV");
  hjethad08->SetLineColor(2);
  hjethad08->Draw("HIST");
  hjethad->Draw("HIST SAME");
  canvas->Update();

  TH1D* hjetn60 = (TH1D*)craft09.Get("hjetn60");
  hjetn60->SetXTitle("n60");
  hjetn60->SetYTitle("N");
  TH1D* hjetn6008 = (TH1D*)craft08.Get("hjetn60");
  hjetn60->SetXTitle("n60");
  hjetn60->SetYTitle("N");
  hjetn6008->SetLineColor(2);
  hjetn6008->Draw("HIST");
  hjetn60->Draw("HIST SAME");
  canvas->Update();

  TH1D* hjetn90 = (TH1D*)craft09.Get("hjetn90");
  hjetn90->SetXTitle("n90");
  hjetn90->SetYTitle("N");
  TH1D* hjetn9008 = (TH1D*)craft08.Get("hjetn90");
  hjetn9008->SetXTitle("n90");
  hjetn9008->SetYTitle("N");
  hjetn9008->SetLineColor(2);
  hjetn9008->Draw("HIST");
  hjetn90->Draw("HIST SAME");
  canvas->Update();

  TH1D* hnmu = (TH1D*)craft09.Get("hnmu");
  hnmu->SetXTitle("N_{#mu}");
  hnmu->SetYTitle("Hz");
  TH1D* hnmu08 = (TH1D*)craft08.Get("hnmu");
  hnmu08->SetXTitle("N_{#mu}");
  hnmu08->SetYTitle("Hz");
  hnmu08->SetLineColor(2);
  hnmu08->Draw("HIST");
  hnmu->Draw("HIST SAME");
  canvas->Update();

//   TH1D* hmupt = (TH1D*)craft09.Get("hmupt");
//   hmupt->SetXTitle("p_{t}^{#mu}");
//   hmupt->SetYTitle("Hz / 1 GeV");
//   hmupt->Draw("HIST");
//   TH1D* hmupt08 = (TH1D*)craft08.Get("hmupt");
//   hmupt08->SetLineColor(2);
//   hmupt08->Draw("HIST SAME");
//   canvas->Update();

//   TH1D* hntow = (TH1D*)craft09.Get("hntow");
//   hntow->SetXTitle("N_{towers}");
//   hntow->SetYTitle("Hz");
//   hntow->Draw("HIST");
//   TH1D* hntow08 = (TH1D*)craft08.Get("hntow");
//   hntow08->SetLineColor(2);
//   hntow08->Draw("HIST SAME");
//   canvas->Update();

//   TH1D* htowe = (TH1D*)craft09.Get("htowe");
//   htowe->SetXTitle("E (GeV)");
//   htowe->SetYTitle("Hz / 2 GeV");
//   htowe->Draw("HIST");
//   TH1D* htowe08 = (TH1D*)craft08.Get("htowe");
//   htowe08->SetLineColor(2);
//   htowe08->Draw("HIST SAME");
//   canvas->Update();

//   TH1D* htowem = (TH1D*)craft09.Get("htowem");
//   htowem->SetXTitle("E (GeV)");
//   htowem->SetYTitle("Hz / 2 GeV");
//   htowem->Draw("HIST");
//   TH1D* htowem08 = (TH1D*)craft08.Get("htowem");
//   htowem08->SetLineColor(2);
//   htowem08->Draw("HIST SAME");
//   canvas->Update();

//   TH1D* htowhad = (TH1D*)craft09.Get("htowhad");
//   htowhad->SetXTitle("E (GeV)");
//   htowhad->SetYTitle("Hz / 2 GeV");
//   htowhad->Draw("HIST");
//   TH1D* htowhad08 = (TH1D*)craft08.Get("htowhad");
//   htowhad08->SetLineColor(2);
//   htowhad08->Draw("HIST SAME");
//   canvas->Update();

  TH1D* hEffJetE = (TH1D*)craft09.Get("heffjete");
  TH1D* hEffJetE08 = (TH1D*)craft08.Get("heffjete");
  hEffJetE08->SetLineColor(2);
  hEffJetE08->Draw("HIST");
  hEffJetE->Draw("HIST SAME");
  canvas->Update();

//   TH1D* hEffJetEta08 = (TH1D*)craft08.Get("heffjeteta");
//   hEffJetEta08->SetLineColor(2);
//   hEffJetEta08->Draw("HIST");
//   TH1D* hEffJetEta = (TH1D*)craft09.Get("heffjeteta");
//   hEffJetEta->Draw("SAME HIST");
//   canvas->Update();

  TH1D* hEffJetN60 = (TH1D*)craft09.Get("heffjetn60");
  TH1D* hEffJetN6008 = (TH1D*)craft08.Get("heffjetn60");
  hEffJetN6008->SetLineColor(2);
  hEffJetN6008->Draw("HIST");
  hEffJetN60->Draw("HIST SAME");
  canvas->Update();

  TH1D* hEffJetN90 = (TH1D*)craft09.Get("heffjetn90");
  TH1D* hEffJetN9008 = (TH1D*)craft08.Get("heffjetn90");
  hEffJetN9008->SetLineColor(2);
  hEffJetN9008->Draw("HIST");
  hEffJetN90->Draw("HIST SAME");
  canvas->Update();

  TH1D* hEffMuVeto = (TH1D*)craft09.Get("heffnmu");
  TH1D* hEffMuVeto08 = (TH1D*)craft08.Get("heffnmu");
  hEffMuVeto08->SetLineColor(2);
  hEffMuVeto->Draw("HIST");
  hEffMuVeto08->Draw("HIST SAME");
  canvas->Update();


//   TFile psCraft08all("PulseShapeHistos08.root","read");
//   TFile psCraft09all("PulseShapeHistos.root","read");

//   TH1D* hpeakall = (TH1D*)psCraft09all.Get("peakfrac");
//   hpeakall->SetXTitle("s_{peak}/s_{total}");
//   hpeakall->SetYTitle("Hz");
//   hpeakall->Draw("HIST");
//   TH1D* hpeak08all = (TH1D*)psCraft08all.Get("peakfrac");
//   hpeak08all->SetLineColor(2);
//   hpeak08all->Draw("HIST SAME");
//   canvas->Update();

//   TH1D* houtall = (TH1D*)psCraft09all.Get("outfrac");
//   houtall->SetXTitle("s_{outer}/s_{total}");
//   houtall->SetYTitle("Hz");
//   houtall->Draw("HIST");
//   TH1D* hout08all = (TH1D*)psCraft08all.Get("outfrac");
//   hout08all->SetLineColor(2);
//   hout08all->Draw("HIST SAME");
//   canvas->Update();

//   TFile psCraft08("PulseShapeHistos_JetMuCuts08.root","read");
//   TFile psCraft09("PulseShapeHistos_JetMuCuts.root","read");

//   TH1D* hpeak08 = (TH1D*)psCraft08.Get("peakfrac");
//   hpeak08->SetXTitle("s_{peak}/s_{total}");
//   hpeak08->SetYTitle("Hz");
//   hpeak08->SetLineColor(2);
//   hpeak08->Draw("HIST");
//   TH1D* hpeak = (TH1D*)psCraft09.Get("peakfrac");
//   hpeak->Draw("HIST SAME");
//   canvas->Update();

//   TH1D* hout08 = (TH1D*)psCraft08.Get("outfrac");
//   hout08->SetXTitle("s_{outer}/s_{total}");
//   hout08->SetYTitle("Hz");
//   hout08->SetLineColor(2);
//   hout08->Draw("HIST");
//   TH1D* hout = (TH1D*)psCraft09.Get("outfrac");
//   hout->Draw("HIST SAME");
//   canvas->Update();

//   canvas->SetLogy(0);

//   TText cft08(0.2, 0.2, "CRAFT 08");
//   cft08->SetNDC();
//   TText cft09(0.2, 0.2, "CRAFT 09");
//   cft09->SetNDC();

//   TH2D* h1 = (TH2D*)psCraft09.Get("r1r2");
//   h1->SetXTitle("BX_{+2}/BX_{+1}");
//   h1->SetYTitle("BX_{+1}/BX_{0}");
//   h1->SetZTitle("Hz");
//   h1->Draw("COLZ");
//   cft09->Draw();
//   canvas->Update();

//   TH2D* h108 = (TH2D*)psCraft08.Get("r1r2");
//   h108->SetXTitle("BX_{+2}/BX_{+1}");
//   h108->SetYTitle("BX_{+1}/BX_{0}");
//   h108->SetZTitle("Hz");
//   h108->Draw("COLZ");
//   cft08->Draw();
//   canvas->Update();

//   TH2D* h2 = (TH2D*)psCraft09.Get("rpro");
//   h2->SetXTitle("s_{peak}/s_{total}");
//   h2->SetYTitle("s_{outer}/s_{total}");
//   h2->SetZTitle("Hz");
//   h2->Draw("COLZ");
//   cft09->Draw();
//   canvas->Update();

//   TH2D* h208 = (TH2D*)psCraft08.Get("rpro");
//   h208->SetXTitle("s_{peak}/s_{total}");
//   h208->SetYTitle("s_{outer}/s_{total}");
//   h208->SetZTitle("Hz");
//   h208->Draw("COLZ");
//   cft08->Draw();
//   canvas->Update();

  ps->Close();


}
