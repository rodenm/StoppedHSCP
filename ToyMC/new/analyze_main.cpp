#include <iostream>
#include "Experiment.h"
#include "Reducer.h"
#include "Plotter.h"
#include "TFile.h"
#include "TTree.h"

int main() {

  TFile infile("experiments.root");

  TTree *tree;
  gDirectory->GetObject("T", tree);

  std::vector<Experiment> exps;

  Experiment *e = new Experiment;
  tree->SetBranchAddress("Experiment", &e);
  for (int i = 0; i < tree->GetEntries(); i++) {
    tree->GetEntry(i);
    e->Dump();
    exps.push_back(*e);
  }

  std::cout << "Reducing experiments..." << std::endl;
  Reducer reducer(exps);
  TGraph *effPlot = reducer.getEfficiencyPlot();
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

  std::cout << "Plotting experiments..." << std::endl;  
  Plotter plotter;
  TCanvas *effPlotted = plotter.getEfficiencyPlot(effPlot);
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

  TFile outfile("plots.root", "RECREATE");
  effPlotted->Write();
  zbPlotted->Write();
  exclPlotted->Write();

  return 0;
}
