#include "StoppedHSCP/ToyMC/interface/Experiment.h"

#include <fstream>
#include <sstream>
#include <iostream>
#include <stdexcept>
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string.hpp>

ClassImp(Experiment)

Experiment::Experiment(std::string filename) :
  mass(0.),
  crossSection(1.),
  lifetime(1E-6),

  signalEff(0.1),
  signalEff_e(0.01),
  bgRate(1E-5),
  bgRate_e(0.2E-5),
  scaleUncert(0.),
  optimizeTimeCut(false),

  histFile("histograms.root"),
  lumiFile("lumi_all.csv"),
  lumiFirstRun(0),
  lumiLastRun(0),
  jsonFile("json.txt"),
  fills(0),
  eventsFile("eventList.log"),

  nTrialsSignal(1000),
  nTrialsBackground(100),
  simulateExpt(false),
  fillScheme("Multi_25b_16_16_16"),
  beamOnTime(0.),
  beamOffTime(0.),
  instLumi(0.),
  runningTime(0.),

  livetime(0.),
  effLumi(0.),
  effLumi_e(0.),
  expSignal(0.),
  expSignal_e(0.),
  expBackground(0.),
  expBackground_e(0.),
  nObserved(0),
  nDecays_MC(0),
  nObs_MC(0),
  nSig_MC(0),
  nBG_MC(0),
  limit95cl(0.),
  expLimit(0.),
  expLim1SigLo(0.),
  expLim1SigHi(0.),
  expLim2SigLo(0.),
  expLim2SigHi(0.)
{

  if (filename!="") {

    std::ifstream file(filename.c_str());
    
    std::string name, value_str;
    while (file >> name >> value_str) {
      
      std::istringstream value(value_str);
      
      // particle parameters
      if (name == "mass")
	value >> mass;
      else if (name == "crossSection")
	value >> crossSection;
      else if (name == "lifetime")
	value >> lifetime;
      

      // analysis parameters
      else if (name == "signalEff")
	value >> signalEff;
      else if (name == "signalEff_e")
	value >> signalEff_e;
      else if (name == "bgRate")
	value >> bgRate;
      else if (name == "bgRate_e")
	value >> bgRate_e;
      else if (name == "scaleUncert")
	value >> scaleUncert;
      else if (name == "optimizeTimeCut") {
	optimizeTimeCut = (value_str=="1");
      }
      
      // real experiment parameters
      else if (name == "histFile")
	value >> histFile;
      else if (name == "lumiFile")
	value >> lumiFile;
      else if (name == "lumiFirstRun")
	value >> lumiFirstRun;
      else if (name == "lumiLastRun")
	value >> lumiLastRun;
      else if (name == "jsonFile")
	value >> jsonFile;
      else if (name == "eventsFile")
	value >> eventsFile;
      else if (name == "fills") {
	std::vector<std::string> strs;
	boost::split(strs, value_str, boost::is_any_of(",")); 
	for (unsigned i=0; i<strs.size(); ++i) {
	  fills.push_back(atoi(strs.at(i).c_str()));
	}
      }
      
      // Toy parameters
      else if (name == "nTrialsSignal")
	value >> nTrialsSignal;
      else if (name == "nTrialsBackground")
	value >> nTrialsBackground;
      else if (name == "simulateExpt") 
	simulateExpt = (value_str=="1");
      else if (name == "fillScheme")
	value >> fillScheme;
      else if (name == "beamOnTime")
	value >> beamOnTime;
      else if (name == "beamOffTime")
	value >> beamOffTime;
      else if (name == "instLumi")
	value >> instLumi;
      else if (name == "runningTime")
	value >> runningTime;
      
      else {
	throw (std::invalid_argument("Unrecognized parameter name "+name));
      }
    }

  }

}


Experiment::~Experiment() {

}


void Experiment::summary(ostream& o) {

  o << lifetime << "\t";
  o << effLumi   << "\t";
  o << expSignal << "\t";
  o << expBackground << "\t";
  o << expBackground_e << "\t";
  o << nObserved << "\t";
  o << limit95cl << "\t";
  o << expLimit << "\t";
  o << expLim1SigLo << "\t";
  o << expLim1SigHi << "\t";
  o << expLim2SigLo << "\t";
  o << expLim2SigHi << "\t";
  o << std::endl;

}

std::ostream &operator<<(std::ostream &o, const Experiment &e) {
  o << "Mass             : " << e.mass << std::endl;
  o << "Cross-section    : " << e.crossSection << std::endl;
  o << "Lifetime         : " << e.lifetime << std::endl;

  o << "Signal eff       : " << e.signalEff << std::endl;
  o << "Signal eff E     : " << e.signalEff_e << std::endl;
  o << "BG rate          : " << e.bgRate << std::endl;
  o << "BG rate E        : " << e.bgRate_e << std::endl;
  o << "Scale Uncert     : " << e.scaleUncert << std::endl;
  o << "Optimize tcut    : " << e.optimizeTimeCut << std::endl;

  o << "Hist file        : " << e.histFile << std::endl;
  o << "Lumi file        : " << e.lumiFile << std::endl;
  o << "Lumi first run   : " << e.lumiFirstRun << std::endl;
  o << "Lumi last run    : " << e.lumiLastRun << std::endl;
  o << "JSON file        : " << e.jsonFile << std::endl;
  //o << "Fills            : " << e.fills << std::endl;
  o << "Events file      : " << e.eventsFile << std::endl;

  o << "N trials sig     : " << e.nTrialsSignal << std::endl;
  o << "N trials BG      : " << e.nTrialsBackground << std::endl;
  o << "Simulate Expt    : " << e.simulateExpt << std::endl;
  o << "Filling scheme   : " << e.fillScheme << std::endl;
  o << "Beam on time     : " << e.beamOnTime << std::endl;
  o << "Beam off time    : " << e.beamOffTime << std::endl;
  o << "Inst Lumi        : " << e.instLumi << std::endl;
  o << "Run time         : " << e.runningTime << std::endl;

  o << "Effective lumi   : "<< e.effLumi << std::endl;
  o << "Effective lumi E : "<< e.effLumi_e << std::endl;
  o << "N signal exp     : "<< e.expSignal << std::endl;
  o << "N signal exp E   : "<< e.expSignal_e << std::endl;
  o << "N BG exp         : "<< e.expBackground << std::endl;
  o << "N BG exp E       : "<< e.expBackground_e << std::endl;
  o << "N Observed       : "<< e.nObserved << std::endl;
  o << "N decays MC      : "<< e.nDecays_MC << std::endl;
  o << "N obs MC         : "<< e.nObs_MC << std::endl;
  o << "N sig MC         : "<< e.nSig_MC << std::endl;
  o << "N BG MC          : "<< e.nBG_MC << std::endl;
  o << "95 CL limit      : "<< e.limit95cl << std::endl;
  return o;
}

