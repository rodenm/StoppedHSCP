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
  
  // set up LHC filling scheme
  // this just uses first fill in the list!
  // TODO - something more intelligent
  std::cout << "Using fill " << e->fills.at(0) << " to set filling scheme" << std::endl;
  sim.setFillScheme(e->fills.at(0));

  // set up lifetime mask
  sim.setupLifetimeMask();

  //sim.printMaskInfo();

  // expected background
  sim.calculateExpectedBG();

  // get observed events
  sim.calculateObservedEvents();

  // run MC
  sim.simulateSignal();
  //  sim.simulateBackground();

  // calculate limit
  sim.calculateLimit();

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
