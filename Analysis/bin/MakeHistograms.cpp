//
// Program to make some histograms from a StoppedHSCP TTree
// Jim Brooke, April 2010
// 

#include "StoppedHSCP/Analysis/interface/Analyser.h"

#include "StoppedHSCP/Ntuples/interface/StoppedHSCPEvent.h"


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
  // Store list of input files
  std::vector<std::string> filenames;
  filenames.clear();

  // Use string to specify output directory
  std::string outdir="";

  // identify output directory from command line
  for (int i=1;i<argc;++i)
    {
      if (stat(argv[i],&st)==0 && S_ISDIR(st.st_mode) )
	{
	  outdir=string(argv[i]);
	  break;
	}
    }

  // identify input file(s) from command line
  for (int i=1;i<argc;++i)
    {
      if (strncmp(argv[i],"-",1)==0)
	continue;
      stat(argv[i],&st);

      // Check if file ends in .root 
      if (((string)argv[i]).find(".root")!=string::npos // file ends with root
	  && !(S_ISDIR(st.st_mode)) // not a directory (sanity check)
	  && S_ISREG(st.st_mode)    // regular file
	  )
	{
	  filenames.push_back(string(argv[i]));
	}
    }
  
  // options
  ULong64_t nlimit=0;
  //bool dump=false;
  bool isMC=false;
  bool doControl=false;
  bool doSearch=false;
  unsigned cutVer=0;

  po::options_description desc("Allowed options");
  po::positional_options_description poptd;

  desc.add_options()
    ("help,h", "Display this message")
    ("num,n",po::value<unsigned long long>()->default_value(0),
     "<integer> Number of events to process")
    //("dump,p",
    // "Dump out information (default is false)")
    ("isMC,m",
     "Turn on MC running")
    ("doControl,b",
     "Use control trigger only")
    ("doSearch,s",
     "Use search trigger only")
    ("cuts,c",po::value<unsigned>()->default_value(0),
     "Set cuts version to apply");

  po::variables_map vm;
  po::store(po::parse_command_line(argc, argv,desc), vm);
  po::notify(vm);    
  
  if (vm.count("num") && vm["num"].as<unsigned long long>()>0) // overrides nlimit
    nlimit=ULong64_t(vm["num"].as<unsigned long long>());
  if (vm.count("isMC"))
    isMC=true;
  if (vm.count("doControl"))
    doControl=true;
  if (vm.count("doSearch"))
    doSearch=true;
  if (vm.count("cuts"))
    cutVer=vm["cuts"].as<unsigned>();
  //if (vm.count("dump")) dump=true;

//   // convert run list to vector
//   std::vector<unsigned> runs(0);

//   for (int i=1;i<argc;++i)
//     {
//       // Don't count arguments that come directly after a command-line option.
//       // This isn't the optimal solution, but it should do the trick for now.
//       if (strncmp(argv[i-1],"-",1)==0)
// 	continue;

//       // Skip args that have already been assigned to filename or outdir
//       if (outdir.size()>0 && strncmp(argv[i],outdir.c_str(),outdir.size())==0)
// 	continue;
//       bool isfile=false;
//       for (uint fs=0;fs<filenames.size();++fs)
// 	{
// 	  if (filenames[fs].size()>0 && strncmp(argv[i],filenames[fs].c_str(),filenames[fs].size())==0)
// 	    {
// 	      isfile=true;
// 	      break;
// 	    }
// 	}
//       if (isfile==true) continue;

//       std::string runstr=std::string(argv[i]);
//       std::vector<std::string> strs;
//       // don't need to add 'space' in is_any_of, because space-separated values are automatically treated as new arguments
//       boost::split(strs, runstr, boost::is_any_of(std::string(","))); 
//       for (unsigned i=0; i<strs.size(); ++i) 
// 	{
// 	  unsigned run = (unsigned) atoi(strs.at(i).c_str());
// 	  if (run > 0) runs.push_back(run);
// 	}
//     }
  
  if (vm.count("help")) 
    {
      cout <<"MakeHistograms options information"<<endl;
      cout << desc << endl;
      if (vm.count("num")) 
	{
	  cout << "Number of Events  was set to " 
	       << vm["num"].as<unsigned long long>() <<endl;
	}
      cout <<"Max # of events = "<<nlimit<<endl;
      cout <<"isMC = "<<isMC<<endl;
      cout <<"INPUT FILE(S) = ";
      for (uint fs=0;fs<filenames.size();++fs)
	cout<<"\t"<<filenames[fs]<<endl;
      if (filenames.size()==0)
	cout <<"No input files specified!"<<endl;
      cout <<"OUTPUT DIRECTORY = '"<<outdir<<"'"<<endl;
//       if (runs.size()>0)
// 	{
// 	  cout <<"A total of "<<runs.size()<<" individual runs will be processed:"<<endl;
// 	  for (unsigned int i=0;i<runs.size();++i)
// 	    std::cout << "Run = "<<runs[i]<<std::endl;
// 	}
      return 1;
    }


  // Error condition 1:  No files found on command line
  if (filenames.size()==0)
    {
      std::cout <<"<MakeHistograms:ERROR>  No valid input file can be found on command line!"<<std::endl;
      return -1;
    }
  // Error condition 2:  No output directory specified on command line
  if (outdir =="")
    {
      std::cout <<"<MakeHistograms:ERROR>  No valid output directory can be found on command line!"<<std::endl;
      return -1;
    }


  // start print out
  if (nlimit>0) std::cout << "Running on " << nlimit << " events per run" << std::endl;


  // sum of squares error info for histograms
  TH1D::SetDefaultSumw2();

  // create analysis
  Analyser analyser(filenames, outdir, isMC, cutVer, doControl, doSearch);

  analyser.setup();

  analyser.cuts().print(std::cout);

  // make histograms for all events
  analyser.loop(nlimit);


}


