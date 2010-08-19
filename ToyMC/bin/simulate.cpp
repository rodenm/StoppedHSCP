#include <iostream>
#include <sstream>
#include <string>
#include <stdexcept>
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string.hpp>

#include "StoppedHSCP/ToyMC/interface/Simulator.h"

// read parameters from a file, then 

int main() {

  Experiment *e = new Experiment;

  TFile f("outfile.root", "RECREATE");
  TTree *tree = new TTree("T", "Experiments from the Stopped Particle MC");
  tree->Branch("Experiment", "Experiment", &e);

  std::string name, value_str;
  std::istringstream value;
  while (std::cin >> name >> value_str) {
    std::istringstream value(value_str);
    if (name == "isProjection") 
      e->isProjection = boost::lexical_cast<bool>(value_str);
    else if (name == "fills") {
      std::vector<std::string> strs;
      boost::split(strs, value_str, boost::is_any_of(",")); 
      for (unsigned i=0; i<strs.size(); ++i) {
	e->fills.push_back(atoi(strs.at(i).c_str()));
      }
    }
    else if (name == "bxStruct")
      value >> e->bxStruct;
    else if (name == "runningTime")
      value >> e->runningTime;
    else if (name == "lookwhere") {
      if (value_str == "BEAMGAP")
	e->lookwhere = e->BEAMGAP;
      else if (value_str == "BOTH")
	e->lookwhere = e->BOTH;
      else if (value_str == "INTERFILL")
	e->lookwhere = e->INTERFILL;
    }
    else if (name == "bgRate")
      value >> e->bgRate;
    else if (name == "errBgRate")
      value >> e->errBgRate;
    else if (name == "scale")
      value >> e->scale;
    else if (name == "bgScale")
      value >> e->bgScale;
    else if (name == "optimizeTimeCut") {
      if (value_str == "true")
	e->optimizeTimeCut = true;
      else if (value_str == "false")
	e->optimizeTimeCut = false;
      else {
	throw (std::invalid_argument("Specify bools as true or false (case sensitive)"));
      }
    }
    else if (name == "crossSection")
      value >> e->crossSection;
    else if (name == "mass")
      value >> e->mass;
    else if (name == "signalEff")
      value >> e->signalEff;
    else if (name == "lifetime")
      value >> e->lifetime;
    else if (name == "nObs")
      value >> e->nObs;
    else {
      throw (std::invalid_argument("Unrecognized parameter name "+name));
    }
  }

  Simulator sim;
  std::cout << "Running experiment" << std::endl;
  sim.run(*e);
  
  std::cout << *e;

  tree->Fill();
  f.cd();
  tree->Write();

  return 0;
}
