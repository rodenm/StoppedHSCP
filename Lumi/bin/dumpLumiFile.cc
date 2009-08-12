#include <math.h>
#include <iostream>

#include "StoppedHSCP/Lumi/interface/LumiReader.h"
#include "TSystem.h"
#include "FWCore/FWLite/interface/AutoLibraryLoader.h"

using namespace shscp;

int main (int argc, char *argv[]) {
  if (argc < 2) {
    std::cout << "Usage: " << argv[0] << " <lumi file name>" << std::endl;
    return 1;
  }
  // use REFLEX dictionaries
  gSystem->Load("libFWCoreFWLite.so");
  AutoLibraryLoader::enable();

  std::string filename (argv[1]);
  shscp::LumiReader lumiReader (filename);
  std::vector<LumiRunSection> runsections = lumiReader.getAllRunsections ();
  for (size_t i = 0; i <  runsections.size(); ++i) {
    uint32_t run = runsections[i].run();
    uint32_t section = runsections[i].section();
    std::cout << "run:" << run << " section:" << section 
	      << " begin:" << int (floor(lumiReader.sectionStartTime (run, section)))
	      << " end:" << int (floor (lumiReader.sectionEndTime (run, section)))
	      << " period:" << int (floor (lumiReader.sectionEndTime (run, section) - lumiReader.sectionStartTime (run, section)))
	      << " integrated LUMI:" << lumiReader.integratedLuminosity (run, section)
	      << std::endl;
  }
  return 0;
}
