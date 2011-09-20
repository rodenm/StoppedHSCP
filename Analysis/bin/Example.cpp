#ifndef Example_h
#define Example_h

#include "StoppedHSCP/Analysis/interface/BasicAnalyser.h"

#include "TFile.h"
#include "TChain.h"
#include "TH1D.h"

#include <string>
#include <vector>
#include <fstream>
#include <sys/stat.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <boost/program_options.hpp>

namespace po = boost::program_options;

using namespace std;

class Example : public BasicAnalyser {

public:
  Example(std::vector<std::string> ifiles,
	  std::string ofile, 
	  bool isMC) : BasicAnalyser (ifiles, ofile, isMC) { }
  
  ~Example() { };
  
  virtual void loop(ULong64_t maxEvents);
  
private:

  // YOUR CODE HERE
  TH1D* myHistogram_;

};

#endif


// this is the event loop
void Example::loop(ULong64_t maxEvents) {

  if (maxEvents!=0) {
    std::cout << "Going to run over " << maxEvents << " events" << std::endl;
  }
  else {
    std::cout << "Going to run over all events" << std::endl;
  }

  reset();
 
  if (maxEvents==0) maxEvents=nEvents();

  nextEvent();

  for (ULong64_t i=0; i<maxEvents; ++i, nextEvent()) {

    // occasional print out
    if (i%100000==0) {
      std::cout << "Processing " << i << "th event of " <<maxEvents<< std::endl;
    }

    // YOUR CODE HERE

  }

}


// this handles program control, no need to do anything here
int main(int argc, char* argv[]) {


  // SET YOUR OUTPUT FILENAME HERE
  std::string ofile("Example.root");

  // options
  ULong64_t nEvents=0;
  bool isMC=false;
  std::string outdir("");
  std::string indir("");
  std::vector<std::string> filenames;

  // get options
  po::options_description desc("Allowed options");
  po::positional_options_description poptd;

  desc.add_options()
    ("help,h", "Display this message")
    ("outdir,o", po::value<string>(), "Output directory")
    ("indir,i", po::value<string>(), "Input directory")
    ("num,n", po::value<unsigned long long>()->default_value(0), "Number of events to process")
    ("mc,m", "Run on MC");

  po::variables_map vm;
  po::store(po::parse_command_line(argc, argv,desc), vm);
  po::notify(vm);

  // help
  if (vm.count("help")) {
    std::cout << desc << std::endl;
    return 1;
  }

  // set output directory
  if (vm.count("outdir")) 
    outdir = vm["outdir"].as<string>();

  // set input directory
  if (vm.count("indir"))
    indir=vm["indir"].as<string>();

  // set number of events
  if (vm.count("num") && vm["num"].as<unsigned long long>()>0)
    nEvents=ULong64_t(vm["num"].as<unsigned long long>());

  /// set if is this MC
  if (vm.count("mc"))
    isMC=true;  
  

  // get list of input files
  DIR *dp;
  struct dirent *dirp;
  if((dp  = opendir(indir.c_str())) == NULL) {
    cout << "Error(" << errno << ") opening " << indir << endl;
    return errno;
  }
  
  while ((dirp = readdir(dp)) != NULL) {
    std::string filename(dirp->d_name);
    if (filename.find(std::string(".root")) != std::string::npos) {
      filenames.push_back(indir+std::string("/")+filename);
    }
  }
  closedir(dp);
  

  // now run the program


  // sum of squares error info for histograms
  TH1D::SetDefaultSumw2();

  // create analysis
  Example analyser(filenames, outdir+ofile, isMC);

  analyser.setup();

  analyser.cuts().print(std::cout);

  // make histograms for all events
  analyser.loop(nEvents);

  return 0;

}
