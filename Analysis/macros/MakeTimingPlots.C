{
TCanvas *TC1 = new TCanvas;
TC1->cd();
TC1->SetLogy();
TH1D * hist1 = new TH1D("hist1","hist1",30,0,1);
timingchain->Draw("(1-TimingFracInCentralFour)>>hist1");
hist1->SetXTitle("Energy Fraction in Outer BX's");

TCanvas *TC2 = new TCanvas;
TC2->cd();
TC2->SetLogy();
TH1D * hist2 = new TH1D("hist2","hist2",100,0,400);
timingchain->Draw("TimingFirstBin+TimingLast2Bins>>hist2");
hist2->SetXTitle("Energy in Outer Bins / fC");
hist2->SetYTitle("Arbitrary Units");

TCanvas *TC3 = new TCanvas;
TC3->cd();
TH2D * hist3 = new TH2D("hist3","hist3",20,0,1,20,0,1);
timingchain->Draw("TimingRightPeak:TimingFracRightNextRight>>hist3");
hist3->SetYTitle("BX_Peak+1 / BX_Peak");
hist3->SetXTitle("BX_Peak+2 / BX_Peak+1");
hist3->Draw("cont0");

TCanvas * TC4= new TCanvas;
TC4->cd();
hist3->Draw("surf1");

TCanvas * TC5 = new TCanvas;
TC5->cd();
TH1D * hist5 = new TH1D("hist5","hist5",50,0,1);
timingchain->Draw("TimingFracInLeader>>hist5");
hist5->SetXTitle("Fraction Of Energy In Peak BX");
hist5->SetYTitle("Arbitrary Units");
hist5->Draw();


}
