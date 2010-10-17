
#include "StoppedHSCP/Analysis/interface/RateCalculator.h"

//"plotByPeriod" method makes graph with rates for requested number of equal time periods,
//"plotByRun" plots rate correlation for different runs
//"plotByRunProjection" makes 1D projection of this graph, the first bin being an everege over the entire period.
#include <vector>

#include <stdlib.h>
#include <boost/algorithm/string.hpp>



int main(int argc, char* argv[]) {

  // arguments
  std::string filename = std::string(argv[argc-2]);
  std::string odir = std::string(argv[argc-1]);
//   std::string runstr=std::string(argv[argc-1]);

//   // convert run list to vector
//   std::vector<unsigned> runs(0);
//   std::vector<std::string> strs;
//   boost::split(strs, runstr, boost::is_any_of(",")); 
//   for (unsigned i=0; i<strs.size(); ++i) {
//     unsigned run = (unsigned) atoi(strs.at(i).c_str());
//     if (run > 0) runs.push_back(run);
//   }

  std::string ofilename=odir+std::string("/background.root");

  std::vector<RateCalculator*> mRates;

//   std::vector<int> hltbxgtcut;
//   for (int i = 0; i < 3; ++i)  hltbxgtcut.push_back(i);
  RateCalculator* newRate  = new RateCalculator ("RateN90VsNtowersFinal", filename, ofilename);
  newRate->addXcut(0);
  newRate->addXcut(1);
  newRate->addXcut(2);
  newRate->addXcut(3);
  newRate->addXcut(4);
  newRate->addXcut(5);
  newRate->addXcut(6);
  newRate->addXcut(7);
  newRate->addXcut(8);
  newRate->addXcut(9);
  newRate->addXcut(11);
  newRate->addXcut(12);
  newRate->addXcut(13);
  newRate->addXcut(14);
  newRate->addXcut(15);

  newRate->addYcut(0);
  newRate->addYcut(1);
  newRate->addYcut(2);
  newRate->addYcut(3);
  newRate->addYcut(4);
  newRate->addYcut(5);
  newRate->addYcut(6);
  newRate->addYcut(7);
  newRate->addYcut(8);
  newRate->addYcut(9);
  newRate->addYcut(10);
  newRate->addYcut(12);
  newRate->addYcut(13);
  newRate->addYcut(14);
  newRate->addYcut(15);
  mRates.push_back (newRate);

  newRate  = new RateCalculator ("RateFinalVsMu", filename, ofilename);
  newRate->addXcut(0);
  newRate->addXcut(1);
  newRate->addXcut(2);
  newRate->addXcut(3);
  newRate->addXcut(4);

  newRate->addYcut(0);
  newRate->addYcut(1);
  newRate->addYcut(2);
  newRate->addYcut(3);
  newRate->addYcut(4);
  newRate->addYcut(5);
  newRate->addYcut(6);
  newRate->addYcut(7);
  newRate->addYcut(8);
  newRate->addYcut(9);
  newRate->addYcut(10);
  newRate->addYcut(11);
  newRate->addYcut(12);
  newRate->addYcut(13);
  newRate->addYcut(14);
  newRate->addYcut(15);
  mRates.push_back (newRate);


//   newRate  = new RateCalculator ("E50VsNtowersFinal", filename); 
//   newRate->addXcut(0);
//   newRate->addXcut(1);
//   newRate->addXcut(2);
//   newRate->addXcut(3);
//   newRate->addXcut(5);
//   newRate->addXcut(6);
//   newRate->addXcut(8);
//   newRate->addXcut(9);
//   newRate->addXcut(10);
//   newRate->addXcut(11);
//   newRate->addXcut(12);

//   newRate->addYcut(0);
//   newRate->addYcut(1);
//   newRate->addYcut(2);
//   newRate->addYcut(3);
//   newRate->addYcut(4);
//   newRate->addYcut(6);
//   newRate->addYcut(7);
//   newRate->addYcut(8);
//   newRate->addYcut(9);
//   newRate->addYcut(10);
//   newRate->addYcut(11);
//   newRate->addYcut(12);
//   mRates.push_back (newRate);
  
//   newRate  = new RateCalculator ("E50VsN90", filename) ;
//   newRate->addXcut(0);
//   newRate->addXcut(1);
//   newRate->addXcut(2);
//   newRate->addXcut(3);
//   newRate->addXcut(5);
//   newRate->addXcut(6);
//   newRate->addXcut(7);
//   newRate->addXcut(9);
//   newRate->addXcut(10);
//   newRate->addXcut(11);
//   newRate->addXcut(12);

//   newRate->addYcut(0);
//   newRate->addYcut(1);
//   newRate->addYcut(2);
//   newRate->addYcut(3);
//   newRate->addYcut(4);
//   newRate->addYcut(6);
//   newRate->addYcut(7);
//   newRate->addYcut(8);
//   newRate->addYcut(9);
//   newRate->addYcut(10);
//   newRate->addYcut(11);
//   newRate->addYcut(12);
//   mRates.push_back (newRate);

  for (unsigned i=0; i<mRates.size(); ++i) {
    mRates[i]->setup();
  }


  //process events
  for (unsigned i = 0; i < mRates.size(); ++i) {
    mRates[i]->loop();
  }
  
  //  make plots
  for (unsigned i = 0; i < mRates.size(); ++i) {
    std::cout << std::endl;
    mRates[i]->printOut();
    mRates[i]->plotByRunProjection(true)->Write("",TObject::kOverwrite);
    mRates[i]->plotByRunProjection(false)->Write("",TObject::kOverwrite);
    mRates[i]->plotByRun()->Write("",TObject::kOverwrite);
    mRates[i]->plotByPeriod(5)->Write("",TObject::kOverwrite);
  }
  
  //  cleaned like
  for (unsigned i = 0; i < mRates.size(); ++i) delete mRates[i];
  mRates.clear();
  
  
  
  //  So, as a result we have graph with rates for periods in the output histogram file.

}
