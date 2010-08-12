//
// Program to make some histograms from a StoppedHSCP TTree
// Jim Brooke, April 2010
// 

#include "StoppedHSCP/Analysis/interface/Analyser.h"
#include "StoppedHSCP/Analysis/interface/StoppedHSCPEvent.h"


#include <vector>

#include <string>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <iterator>


#include <sys/stat.h>
#include <stdlib.h>
#include <boost/algorithm/string.hpp>


int main(int argc, char* argv[]) {

  if (argc < 3) {
    std::cout << "Insufficient arguments" << std::endl;
    std::cout << "Usage : BasicHistograms <filename> <label>" << std::endl;
    exit(1);
  }

  // options
  unsigned nlimit=999999999;
  bool dump=false;
  bool doByRun=true;
  bool isMC=false;
  for (int i=1; i<argc; ++i) {
    // check option flags
    std::string opt = argv[i];
    if (opt=="-d") {
      nlimit=1000;
    }
    if (opt=="-p") {
      dump=true;
    }
    if (opt=="-q") {
      doByRun = false;
    }
    if (opt=="-m") {
      isMC=true;
      std::cout << "Running for MC" << std::endl;
    }
  }

  if (nlimit<999999999) std::cout << "Running on " << nlimit << " events per run" << std::endl;

  // arguments
  std::string filename = std::string(argv[argc-3]);
  std::string outdir=std::string(argv[argc-2]);
  std::string runstr=std::string(argv[argc-1]);

  // convert run list to vector
  std::vector<unsigned> runs(0);
  std::vector<std::string> strs;
  boost::split(strs, runstr, boost::is_any_of(",")); 
  for (unsigned i=0; i<strs.size(); ++i) {
    unsigned run = (unsigned) atoi(strs.at(i).c_str());
    if (run > 0) runs.push_back(run);
  }

  // clean output directory
  std::string command("mkdir ");
  command += outdir;
  system(command.c_str());
  command = std::string("ls ");
  command += outdir;
  system(command.c_str());

  // sum of squares error info for histograms
  TH1D::SetDefaultSumw2();

  // create analysis
  Analyser analyser(filename, outdir, runs, isMC);

  analyser.setup();

  // make histograms for all events
  analyser.loop();


}


