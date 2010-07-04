#include "StoppedHSCP/ToyMC/interface/Simulator.h"
#include "StoppedHSCP/ToyMC/interface/Experiment.h"
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
  e->bxStruct    = 8;
  //e->lumi        = 1e32;
  e->runningTime = 7;
  //  e->lookwhere   = e->BOTH;
  e->lookwhere   = e->BEAMGAP;
  e->bgRate      = 0.000103;
  e->errBgRate   = 0.000025;
  e->scale       = 1e8;
  e->bgScale     = 1e6;
  e->sendToLifetimeFit = false;
  e->optimizeTimeCut = true;


  //e->collisionL1Arate = 100000;
  e->collisionL1Arate = 0;

  //per-experiment parameters
  e->crossSection = .375e-33;
  //  e->crossSection = 5e-34 * .25;
  //e->crossSection = 5e-28;
  // Newest figures for 300/100
  e->mass         = 200;
  e->signalEff    = .188 * .179;
  //  e->signalEff    = .205 * .199;
  //  e->signalEff    = 0.158 * 0.162;
  e->lifetime     = 1;

  double runtimes[100] =
    {
      1, 7, 30, 60
    };
  
  double lifetimes[100] =
    {
      /*
      1e-8,
      1e-7,
      1e-6,
      1e-3,
      3600,
      43200,
      86400,
      604800
      // 8
      */ 
      
      5.e-8,
      1.e-7,
      2.e-7,
      5.e-7,
      7.e-7,
      1.e-6,
      2.73e-6,
      2.77e-6,
      5.06e-6,
      5.1e-6,
      1.e-5,
      1.152e-5,
      1.156e-5,
      1.761e-5,
      1.765e-5,
      2.e-5,
      3.e-5,
      4.e-5,
      5.e-5,
      7.e-5,
      1.e-4,
      2.e-4,
      5.e-4,
      7.e-4,
      1.e-3,
      5.e2,
      1.e3,
      2.e3,
      3600.,
      6.e3,
      1.e4,
      2.e4,
      3.e4,
      5.e4,
      1.e5,
      3.e5,
      1.e6,
      1.e7
      //19
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

  for (int j = 3; j < 4; j++) {
    //e->mass = mass[j];
    //e->signalEff = efficiencies[j];
    e->runningTime = runtimes[j];
    for (int i = 0; i < 38; i++)
      {
	e->lifetime = lifetimes[i];
	//	if (i == 5) e->sendToLifetimeFit = true;
	//else e->sendToLifetimeFit = false;
	std::cerr << "Running experiment " << j*19+i << "... "
		  << std::endl;
	sim.run(*e);

	e->nObs = (i <= 4 ? 0 : 2);

	outfile.cd();
	/*
	if (i == 0) {
	  sim.run_specific_plots["sensitive_in_beam"]->Write();
	  sim.run_specific_plots["longtime"]->Write();
	  sim.run_specific_plots["vetoed_events"]->Write();
	}
	if (i == 2) {
	  sim.run_specific_plots["longtime"]->Write();
	}
	*/
	//if (i == 5) {
	//  sim.run_specific_plots["longtime"]->Write();
	//}
	tree->Fill();
      }
  }

  sim.writeOutLifetimeFit();
  outfile.cd();
  tree->Write();
  //  sim.run_specific_plots["longtime"]->Write();
  return 0;
}
