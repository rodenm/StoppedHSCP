// macro to test cut code is working properly

{
  // custom libs
  gSystem->Load("libStoppedHSCPAnalysis");

  // macros
  gROOT->ProcessLine(".L macros/BasicHistos.C+");
  gROOT->ProcessLine(".L macros/EffHistos.C+");
  gROOT->ProcessLine(".L macros/PulseShapeHistos.C+");
  gROOT->ProcessLine(".L macros/Cuts.C+");
  gROOT->ProcessLine(".L macros/WriteSelection.C+");
  gROOT->ProcessLine(".L macros/Style.C");

  // set plot style
  setTDRStyle();
  gROOT->ForceStyle();


  TChain* chain = new TChain("stoppedHSCPTree/StoppedHSCPTree");
  chain->Add(" /storage/phjjb/StoppedHSCP_CRAFT09_v4/stoppedHSCPTree.root");
 
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

    if (Cut(evt, 1))  hTestJetE->Fill(evt->getJet(0).e);
    if (Cut(evt, 2))  hTestJetEta->Fill(evt->getJet(0).eta);
    if (Cut(evt, 4))  hTestJetN60->Fill(evt->getJet(0).n60);
    if (Cut(evt, 8))  hTestJetN90->Fill(evt->getJet(0).n90);
    if (Cut(evt, 16)) hTestMuVeto->Fill(evt->nMuon());

  }

  TPostScript* ps = new TPostScript("TestCutPlots.ps", 112);
  TCanvas* canvas = new TCanvas("canvas");

  canvas->SetLogy();

  hTestJetE->Draw();
  canvas->Update();

  hTestJetEta->Draw();
  canvas->Update();

  hTestJetN90->Draw();
  canvas->Update();

  hTestJetN60->Draw();
  canvas->Update();

  hTestMuVeto->Draw();
  canvas->Update();

  ps->Close();


}
