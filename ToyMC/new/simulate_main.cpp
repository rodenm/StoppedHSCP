#include "Simulator.h"
#include "Experiment.h"
#include <vector>
#include <iostream>
#include <TFile.h>
#include <TTree.h>

int main() {

  // Set up the experiments

  Experiment *e = new Experiment;

  TFile outfile("experiments.root", "RECREATE");
  TTree *tree = new TTree("T", "Experiments from the Stopped Particle MC");
  tree->Branch("Experiment", "Experiment", &e);

  // global parameters
  //  e->beamOffTime = 12*3600;
  //e->beamOnTime  = 12*3600;
  e->bxStruct    = 156;
  //e->lumi        = 1e32;
  e->runningTime = 17;
  e->lookwhere   = e->BOTH;
  e->bgRate      = 0.00039;
  e->scale       = 1e2;
  e->bgScale     = 10;

  //per-experiment parameters
  e->crossSection = 5e-34;
  e->mass         = 300;
  e->signalEff    = 0.158 * 0.162;
  e->lifetime     = 1;

  double runtimes[100] =
    {
      3, 7, 14, 30
    };
  
  double lifetimes[100] =
    {
      1e-6,
      1e-3,
      3600,
      43200,
      86400,
      604800

      /*
      5e-8,
      1e-7,
      2e-7,
      1.e-6,
      1e-5,
      1.e-3,
      1,
      5e2,
      2e3,
      3600.,
      6e3,
      1e4,
      2e4,
      3e4,
      5e4,
      1e5,
      3e5,
      1e6,
      1e7
      */
    };

  double mass[4] = {
    300, 400, 500, 600
  };

  double efficiencies[4] = {
    0.158 * 0.162, //selection * stopping
    0.158 * 0.162 * 0.347, // syst uncert
    0.104 * 0.162,
    0.104 * 0.162 * 0.347
  };

  Simulator sim;
  sim.setupLumi(std::cin);

  for (int j = 0; j < 4; j++) {
    //    e->mass = mass[j];
    //    e->signalEff = efficiencies[j];
    e->runningTime = runtimes[j];
    for (int i = 0; i < 6; i++)
      {
	e->lifetime = lifetimes[i];
	std::cerr << "Running experiment " << j*19+i << "... "
		  << std::endl;
	sim.run(*e);
	/*
	if (i == 6) {
	  sim.run_specific_plots["decays_in_beam"]->Write();
	  sim.run_specific_plots["sensitive_in_beam"]->Write();
	  sim.run_specific_plots["bunch_structure"]->Write();
	}
	*/
	tree->Fill();
      }
  }

  tree->Write();
  //  sim.run_specific_plots["longtime"]->Write();
  return 0;
}
