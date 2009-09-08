// macro to test cut code is working properly

{

  gSystem->Load("libStoppedHSCPAnalysis");
  gROOT->ProcessLine(".L macros/Chain.C+");
  gROOT->ProcessLine(".L macros/Cuts.C+");

  TChain* chain = Chain(); 
 
  TH1::SetDefaultSumw2();

  // create histograms
  TH1D* hTestJetE = new TH1D("hTestJetE", "Test jet E", 100, 0., 200.);
  TH1D* hTestJetEta = new TH1D("hTestJetEta", "Test jet #eta", 70, -3.0, 3.0);
  TH1D* hTestJetN90 = new TH1D("hTestJetN90", "Test jet n90", 25, 0., 25.);
  TH1D* hTestJetN60 = new TH1D("hTestJetN60", "Test jet n60", 25, 0., 25.);
  TH1D* hTestMuVeto = new TH1D("hTestMuVeto", "Test #mu veto", 5, 0., 5.);
  
  // create custom event object
  //  gSystem->Load("libStoppedHSCPAnalysis");
  StoppedHSCPEvent *evt   = new StoppedHSCPEvent();
  chain->SetBranchAddress("events",&evt);
  
  // loop over events
  Int_t nentries = (Int_t)chain->GetEntries();  
  for (Int_t i=0;i<nentries; i++) {

    chain->GetEntry(i);

    if (cut(evt, 0x1)) hTestJetE->Fill(evt->getJet(0).e);
    if (cut(evt, 0x2)) hTestJetEta->Fill(evt->getJet(0).eta);
    if (cut(evt, 0x4)) hTestJetN90->Fill(evt->getJet(0).n90);
    if (cut(evt, 0x8)) hTestJetN60->Fill(evt->getJet(0).n60);
    if (cut(evt, 0x10)) hTestMuVeto->Fill(evt->nMuon());

  }

  TPDF* pdf = new TPDF("EffPlots.pdf");
  TCanvas* canvas = new TCanvas("canvas");

  TH1D* hTestJetE = (TH1D*)file.Get("hTestJetE");
  hTestJetE->SetLineStyle(1);
  hTestJetE->Draw();
  canvas->Update();

  TH1D* hTestJetEta = (TH1D*)file.Get("hTestJetEta");
  hTestJetEta->Draw();
  canvas->Update();

  TH1D* hTestJetN90 = (TH1D*)file.Get("hTestJetN90");
  hTestJetN90->Draw();
  canvas->Update();

  TH1D* hTestJetN60 = (TH1D*)file.Get("hTestJetN60");
  hTestJetN60->Draw();
  canvas->Update();

  TH1D* hTestMuVeto = (TH1D*)file.Get("hTestMuVeto");
  hTestMuVeto->Draw();
  canvas->Update();

  pdf->Close();


}
