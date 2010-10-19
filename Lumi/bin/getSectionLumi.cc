#include <stdlib.h>
#include <iostream>
#include "StoppedHSCP/Lumi/interface/LumiDBReader.h"

using namespace std;
using namespace shscp;

int main (int argc, const char* argv[]) {
  if (argc < 2) {
    cout << "Use: " << argv[0] << " run# [section#]" << std::endl;
    return -1;
  }
  int run = atoi (argv[1]);
  LumiDBReader reader;
  if (argc >=3) {
    int section = atoi (argv[2]);
    LumiSummaryRecord summary;
    if (reader.getSummary (run, section, &summary)) {
      LumiDetailsRecord details;
      if (reader.getDetails (summary.id, &details)) {
	for (int i = 0; i < BXINORBIT; ++i) {
	  if (details.lumi[i] > 1e-4) {
	    cout << i << ':' << details.lumi[i] << endl;
	  }
	}
      }
    }
  }
  else {
    std::vector<int> sections = reader.getAllSections (run);
    for (unsigned i = 0; i < sections.size(); ++i) {
      LumiSummaryRecord summary;
      reader.getSummary (run, sections[i], &summary);
      cout << sections[i] << " " << summary.instLumi << "+-" << summary.instLumiError
	   << " beam: " << summary.beamEnergy << '/' << summary.beamStatus 
	   << " orbits: " << summary.startOrbit << '/' << summary.numOrbits
	   << endl;
    }
    cout << "Total " << sections.size() << " sections for run " << run << endl;
  }
}
