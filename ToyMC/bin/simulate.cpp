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
  std::cout << "From file : " << paramfile << std::endl;
  std::cout << *e << std::endl;

  // setup tree to write out
  TFile f("outfile.root", "RECREATE");
  TTree *tree = new TTree("T", "Experiments from the Stopped Particle MC");
  tree->Branch("Experiment", "Experiment", &e);

  // fills file
  std::ofstream fillsfile;
  fillsfile.open("fills.txt");

  // setup simulation
  Simulator sim;

  // set parameters
  sim.setParameters(e);

  // set observed events
  sim.setupObservedEvents();

  // set up luminosity data
  sim.setupLumi(false, false, true, e->lumiFile);

  // set up lifetime mask
  sim.setupLifetimeMask();

  //  sim.getLhcFills().print(std::cout);
  
  // loop over fills
  for (unsigned f=0; f!=e->fills.size(); ++f) {

    unsigned fill = e->fills.at(f);
    
    std::cout << "Simulating fill " << fill << std::endl;

    std::cout << "With filling scheme " << sim.getLhcFills().getFillingScheme(fill) << std::endl;

    sim.reset();

    //sim.printMaskInfo(fill);

    // expected background
    sim.calculateExpectedBG(fill, fill);

    // get observed events
    sim.calculateObservedEvents(fill, fill);

    // run MC
    sim.simulateSignal(fill, fill);

    // write fills file
    fillsfile << fill << "\t" << sim.getEffLumi() << "\t" << sim.getNObs() << "\t" << sim.getNExp() << "\t" << sim.getNExpErr() << std::endl;

    std::cout << std::endl;

  }

  // calculate limit
  sim.calculateLimit();

  std::cout << std::endl;

  // write results summary
  std::ofstream summaryfile;
  summaryfile.open("summary.txt", std::ios::app);
  e->summary(summaryfile);
  summaryfile.close();

  std::cout << *e << std::endl;

  tree->Fill();
  f.cd();
  tree->Write();

  fillsfile.close();

  return 0;
}
