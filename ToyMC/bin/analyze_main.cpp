#include <iostream>
#include "StoppedHSCP/ToyMC/interface/Experiment.h"
#include "StoppedHSCP/ToyMC/interface/Reducer.h"
#include "StoppedHSCP/ToyMC/interface/Plotter.h"
#include "TFile.h"
#include "TTree.h"

int main() {

  std::vector<Experiment> exps;
  Experiment *e = new Experiment;
  TTree *tree;
  
  {
    TFile infile("experiments1.root");
    
    gDirectory->GetObject("T", tree);
    
    tree->SetBranchAddress("Experiment", &e);
    for (int i = 0; i < tree->GetEntries(); i++) {
      tree->GetEntry(i);
      //e->Dump();
      exps.push_back(*e);
    }
  }
  
  {
    TFile infile("experiments2.root");  

    gDirectory->GetObject("T", tree);
    
    Experiment *e = new Experiment;
    tree->SetBranchAddress("Experiment", &e);
    for (int i = 0; i < tree->GetEntries(); i++) {
      tree->GetEntry(i);
      exps[i] = exps[i] + *e;
      exps[i].Dump();
    }
  }

  std::cout << "Reducing experiments..." << std::endl;
  Reducer reducer(exps);
  TGraph *effPlot = reducer.getEfficiencyPlot();
  TGraph *vPlot = reducer.getVetoesPlot();  
  TGraph *zbPlot1 = reducer.getZbPlot(1e-6);
  TGraph *zbPlot2 = reducer.getZbPlot(1e-3);
  TGraph *zbPlot3 = reducer.getZbPlot(3600);
  TGraph *zbPlot4 = reducer.getZbPlot(43200);
  TGraph *zbPlot5 = reducer.getZbPlot(86400);
  TGraph *zbPlot6 = reducer.getZbPlot(604800);
  TGraph *exclPlot1 = reducer.getExclusionPlot(300);
  TGraph *exclPlot2 = reducer.getExclusionPlot(400);
  TGraph *exclPlot3 = reducer.getExclusionPlot(500);
  TGraph *exclPlot4 = reducer.getExclusionPlot(600);

  TGraph *CSexclPlot1 = reducer.getCrossSectionPlot(200, true);
  TGraph *CSexclPlot2 = reducer.getCrossSectionPlot(200, false);

  /*  TGraph *CSexclPlot2 = reducer.getCrossSectionPlot(400);
  TGraph *CSexclPlot3 = reducer.getCrossSectionPlot(500);
  TGraph *CSexclPlot4 = reducer.getCrossSectionPlot(600);
  */

  std::cout << "Plotting experiments..." << std::endl;  
  Plotter plotter;
  TCanvas *effPlotted = plotter.getEfficiencyPlot(effPlot);
  TCanvas *vPlotted = plotter.getVetoesPlot(vPlot);
  TCanvas *zbPlotted = plotter.getZbPlot(zbPlot1,
					 zbPlot2,
					 zbPlot3,
					 zbPlot4,
					 zbPlot5,
					 zbPlot6);
  TCanvas *exclPlotted = plotter.getExclusionPlot(exclPlot1,
						  exclPlot2,
						  exclPlot3,
						  exclPlot4);

  TCanvas *CSexclPlotted = plotter.getCSExclusionPlot(CSexclPlot1,
						      CSexclPlot2);

  TFile outfile("plots.root", "RECREATE");
  effPlotted->Write();
  vPlotted->Write();
  zbPlotted->Write();
  exclPlotted->Write();
  CSexclPlotted->Write();


  std::cout << std::endl << "Lifetime   Expected Sig   Expected Bg   Observed" << std::endl;
  for (unsigned int i = 0; i < exps.size(); i++) {
    std::cout << exps[i].lifetime << "   " << exps[i].nSig_d << "   "
	      << exps[i].nExpectedBg << "   " << exps[i].nObs << std::endl;
  }

  return 0;
}
