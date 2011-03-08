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
#include <boost/program_options.hpp>

namespace po = boost::program_options;
using namespace std;

int main(int argc, char* argv[]) {



  struct stat st;
  std::string filename="";
  std::string outdir="";

  for (int i=1;i<argc;++i)
    {
      stat(argv[i],&st);
      if (S_ISREG(st.st_mode) && !(S_ISDIR(st.st_mode)))
	{
	  filename=string(argv[i]);
	  break;
	}
    }
  for (int i=1;i<argc;++i)
    {
      if (stat(argv[i],&st)==0 && S_ISDIR(st.st_mode) )
	{
	  outdir=string(argv[i]);
	  break;
	}
    }
  
  // options
  Long64_t nlimit=-1;
  bool dump=false;
  bool doByRun=true;
  bool isMC=false;

  po::options_description desc("Allowed options");
  po::positional_options_description poptd;

  desc.add_options()
    ("help,h", "Display this message")
    ("num,n",po::value<int>()->default_value(-1),
     "<integer> Number of events to process")
    ("dump,p",
     "Dump out information (default is false)")
    ("nlimit,d",
     "Set limit of number of events to 1000.  Overridden by -n option")
    ("dontDoByRun,q",
     "Sets doByRun value to false")
    ("isMC,m",
     "Turn on MC running")
     ;
  
  po::variables_map vm;
  po::store(po::parse_command_line(argc, argv,desc), vm);
  po::notify(vm);    

  if (vm.count("nlimit"))
    nlimit=1000;
  if (vm.count("num") && vm["num"].as<int>()>-1) // overrides nlimit
    nlimit=vm["num"].as<int>();
  if (vm.count("dump"))
    dump=true;
  if (vm.count("dontDoByRun"))
    doByRun=false;
  if (vm.count("isMC"))
    isMC=true;


  // convert run list to vector
  std::vector<unsigned> runs(0);
  

  // Allow for runs that are separate by either commas or spaces
  for (int i=1;i<argc;++i)
    {
      // Don't count arguments that come directly after a command-line option.
      // This isn't the optimal solution, but it should do the trick for now.
      if (strncmp(argv[i-1],"-",1)==0)
	continue;

      // Skip args that have already been assigned to filename or outdir
      if ((filename.size()>0 && strncmp(argv[i],filename.c_str(),filename.size())==0) ||
	  (outdir.size()>0 && strncmp(argv[i],outdir.c_str(),outdir.size())==0))
	continue;

      std::string runstr=std::string(argv[i]);
      std::vector<std::string> strs;
      // don't need to add 'space' in is_any_of, because space-separated values are automatically treated as new arguments
      boost::split(strs, runstr, boost::is_any_of(std::string(","))); 
      for (unsigned i=0; i<strs.size(); ++i) 
	{
	  unsigned run = (unsigned) atoi(strs.at(i).c_str());
	  if (run > 0) runs.push_back(run);
	}
    }
  
  if (vm.count("help")) 
    {
      cout <<"MakeHistograms options information"<<endl;
      cout << desc << endl;
      if (vm.count("num")) 
	{
	  cout << "Number of Events  was set to " 
	       << vm["num"].as<int>() <<endl;
	}
      cout <<"Max # of events = "<<nlimit<<endl;
      cout <<"dump = "<<dump<<endl;
      cout <<"doByRun = "<<doByRun<<endl;
      cout <<"isMC = "<<isMC<<endl;
      cout <<"INPUT FILE = '"<<filename<<"'"<<endl;
      cout <<"OUTPUT DIRECTORY = '"<<outdir<<"'"<<endl;
      if (runs.size()>0)
	{
	  cout <<"A total of "<<runs.size()<<" individual runs will be processed:"<<endl;
	  for (unsigned int i=0;i<runs.size();++i)
	    std::cout << "Run = "<<runs[i]<<std::endl;
	}
      return 1;
    }


  if (filename=="")
    {
      std::cout <<"<MakeHistograms:ERROR>  No valid input file can be found on command line!"<<std::endl;
      return -1;
    }
  if (outdir =="")
    {
      std::cout <<"<MakeHistograms:ERRO>  No valid output directory can be found on command line!"<<std::endl;
      return -1;
    }

  if (nlimit>-1) std::cout << "Running on " << nlimit << " events per run" << std::endl;


  // sum of squares error info for histograms
  TH1D::SetDefaultSumw2();

  // create analysis
  Analyser analyser(filename, outdir, runs, isMC);

  analyser.setup();

  // make histograms for all events
  analyser.loop(nlimit);


}


