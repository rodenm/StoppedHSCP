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
  shscp::LumiReader* lumiReader = shscp::LumiReader::getLumiReader(filename);
  std::vector<LumiRunSection> runsections = lumiReader->getAllRunsections ();
  for (size_t i = 0; i <  runsections.size(); ++i) {
    uint32_t run = runsections[i].run();
    uint32_t section = runsections[i].section();
    int64_t index = lumiReader->getIndex (run, section);
    std::cout << " run:" << run 
	      << " section:" << section 
	      << " begin:" << int (floor(lumiReader->sectionStartTime (index)))
	      << " end:" << int (floor (lumiReader->sectionEndTime (index)))
	      << " period:" << int (floor (lumiReader->sectionEndTime (index) - lumiReader->sectionStartTime (index))) << "s"
	      << " instant LUMI:" << lumiReader->instantLuminosity (index) << " 1/cm^2/s"
	      << " integrated LUMI:" << lumiReader->integratedLuminosity (index) * 1.e-33 << " 1/nb"
	      << " empty bunches fraction: " << lumiReader->sectionEmptyBunchesFraction (index)
	      << std::endl;
  }
  return 0;
}
