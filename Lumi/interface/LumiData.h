#ifndef LUMI_DATA_H
#define LUMI_DATA_H
//
// Author: Fedor.Ratnikov@cern.ch, KIT, Jan.10, 2011 
//

#include <string>
#include <vector>
#include <map>

namespace shscp {

  class LumiDBReader;
  
  struct DeliveredLumi {
    int fill;
    int run;
    int section;
    time_t begin;
    time_t end;
    double integratedLumi;
    double sensitiveFraction;
    int status;
  };
  
  class AllLumiData {
  public:
    typedef std::map <int, DeliveredLumi> LumiRun;
    typedef std::map <int, LumiRun> LumiData;
    AllLumiData ();
    AllLumiData (const std::string& fFileName);
    AllLumiData (LumiDBReader& fDBReader, bool fDetails = true);
    bool dumpToFile (const std::string& fFileName) const;

    std::vector<int> getAllSections (int fRun) const;
    std::vector<int> getAllRuns (int fFill) const;
    std::vector<int> getAllFills ();

    const DeliveredLumi* getLumiData (int fRun, int fSection) const;
  private:
    LumiData mData;
    std::map<int,std::vector<int> > mFills;
  };
}
#endif

