#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

#include "StoppedHSCP/ToyMC/interface/Simulator.h"
#include "StoppedHSCP/ToyMC/interface/Experiment.h"


int main(int argc, char* argv[]) {

  if (argc < 2) {
    std::cout << "Insufficient arguments" << std::endl;
    std::cout << "Usage : simulate <params file>" << std::endl;
    exit(1);
  }

  // arguments
  std::string paramfile = std::string(argv[1]);


  Experiment* e;


  // read parameters from file and create experiment object
  e = new Experiment(paramfile);
  std::cout << "Simulation parameters" << std::endl;
  std::cout << *e << std::endl;

  // setup tree to write out
  TFile f("outfile.root", "RECREATE");
  TTree *tree = new TTree("T", "Experiments from the Stopped Particle MC");
  tree->Branch("Experiment", "Experiment", &e);

  // setup simulation
  Simulator sim;

  // set parameters
  sim.setParameters(e);

  // set observed events
  sim.setupObservedEvents();

  // set up luminosity data
  sim.setupLumi();

  // set up lifetime mask
  sim.setupLifetimeMask();
  
  // loop over fills
  for (unsigned f=0; f!=e->fills.size(); ++f) {

    unsigned fill = e->fills.at(f);
    
    std::cout << "Simulating fill " << fill << std::endl;

    //sim.printMaskInfo(fill);

    // expected background
    sim.calculateExpectedBG(fill, fill);

    // get observed events
    sim.calculateObservedEvents(fill, fill);

    // run MC
    sim.simulateSignal(fill, fill);

    std::cout << std::endl;
  }

  // calculate limit
  sim.calculateLimit();

  std::cout << std::endl;

  // write results summary
  std::ofstream summaryfile;
  summaryfile.open("../summary.txt", std::ios::app);
  e->summary(summaryfile);


  std::cout << *e << std::endl;

  tree->Fill();
  f.cd();
  tree->Write();

  return 0;
}
