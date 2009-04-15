{
CraftRun * Run68021= new CraftRun("../CraftBackground/68021/Calo_v3_V9",280);
SignalOneFile * s1f = new SignalOneFile("../SignalOutput/GenSimReco_300_50.root");
SignalDataCompare * SDC = new SignalDataCompare(Run68021, s1f);

CraftCutsNoTiming * CC = new CraftCutsNoTiming();

SDC->GetSigBackPlot(3,"LeadingJetEta",CC->GetNMinus1Cut("Eta < 1.3"),100,-3,3,"Leading Reco Jet Eta",0)->SaveAs("Plots/Eta_NMinus1.pdf");
SDC->GetSigBackPlot(3,"LeadingCenJetn90",CC->GetNMinus1Cut("n90 > 3"),15,0,15,"Leading Reco Jet n90",0)->SaveAs("Plots/n90_NMinus1.pdf");
SDC->GetSigBackPlot(3,"LeadingCenJetn60",CC->GetNMinus1Cut("n60 < 6"),25,0,25,"Leading Reco Jet n60",0)->SaveAs("Plots/n60_NMinus1.pdf");
SDC->GetSigBackPlot(3,"LeadingCenJetEnergy",CC->GetNMinus1Cut("Energy > 50"), 100,0,200,"Leading Reco Jet Energy",0)->SaveAs("Plots/Energy_NMinus1.pdf");
SDC->GetSigBackPlot(3,"NoOfMuons",CC->GetNMinus1Cut("Muon Veto"), 6,0,6,"Number of Reco Muon Tracks",0)->SaveAs("Plots/Muons_NMinus1.pdf");

SDC->GetSigBackPlot(3,"LeadingJetEta","",100,-3,3,"Leading Reco Jet Eta", 0)->SaveAs("Eta_Sequence1.pdf");
SDC->GetSigBackPlot(3,"LeadingCenJetn90",CC->GetSequenceCut("Eta < 1.3"),15,0,15,"Leading Reco Jet n90", 0)->SaveAs("Plots/n90_Sequence2.pdf");
SDC->GetSigBackPlot(3,"LeadingCenJetn60",CC->GetSequenceCut("n90 > 3"),25,0,25,"Leading Reco Jet n60", 0)->SaveAs("Plots/n60_Sequence3.pdf");
SDC->GetSigBackPlot(3,"LeadingCenJetEnergy",CC->GetSequenceCut("n60 < 6"),100,0,200,"Leading Reco Jet Energy",0)->SaveAs("Plots/Energy_Sequence4.pdf");
SDC->GetSigBackPlot(3,"NoOfMuons",CC->GetSequenceCut("Energy > 50"),6,0,6,"Number of Reco Muon Tracks",0)->SaveAs("Plots/Muons_Sequence5.pdf");


CraftTiming * Timing68021 = new CraftTiming("../




}
