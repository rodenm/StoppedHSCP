{

MuonCut * CC = new MuonCut();
TCut Topological = TCut("");

CraftRun * CR = new CraftRun("../CraftBackground/68021/OldVersions/68021v3skim",100);

TCanvas *TC1 = new TCanvas;
TC1->cd();
TH1D * hist1 = new TH1D("hist1","hist1",30,0,1);
CR->GetChain(3)->Draw("(1-TimingFracInCentralFour)>>hist1",Topological);
hist1->SetXTitle("Energy Fraction in Outer BX's");
TC1->SaveAs("Plots/TimingAllCraftOuter.pdf");


TCanvas *TC3 = new TCanvas;
TC3->cd();
TH2D * hist3 = new TH2D("hist3","hist3",20,0,1,20,0,1);
CR->GetChain(3)->Draw("TimingRightPeak:TimingFracRightNextRight>>hist3",(Topological && TCut("TimingRightPeak>0") && TCut("TimingFracRightNextRight>0")));
hist3->SetYTitle("BX_Peak+1 / BX_Peak");
hist3->SetXTitle("BX_Peak+2 / BX_Peak+1");
hist3->Draw("cont0");
TC3->SaveAs("Plots/TimingAllCraft2d.pdf");

TCanvas * TC4= new TCanvas;
TC4->cd();
hist3->Draw("surf1");
TC4->SaveAs("Plots/TimingAllCraft3d.pdf");

TCanvas * TC5 = new TCanvas;
TC5->cd();
TH1D * hist5 = new TH1D("hist5","hist5",50,0,1);
CR->GetChain(3)->Draw("TimingFracInLeader>>hist5",Topological);
hist5->SetXTitle("Fraction Of Energy In Peak BX");
hist5->SetYTitle("Arbitrary Units");
hist5->Draw();
TC5->SaveAs("Plots/TimingAllCraftFracLeader.pdf");


}
