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

    DeliveredLumi () :fill(0), run(0), section(0), begin(0), end(0), integratedLumi(0), sensitiveFraction(0), status(0) {}
    time_t time () const {return begin + (end-begin)/2;}
    time_t dtime() const {return end-begin;}
  };
  
  class AllLumiData {
  public:
    typedef std::map <int, DeliveredLumi> LumiRun;
    typedef std::map <int, LumiRun> LumiData;
    AllLumiData ();
    AllLumiData (const std::string& fFileName);
    AllLumiData (LumiDBReader& fDBReader, bool fDetails = true);
    AllLumiData (LumiDBReader& fDBReader, const std::string& fLHCLumiDir
		 // = "/afs/cern.ch/cms/CAF/CMSCOMM/COMM_GLOBAL/LHCFILES"
		 );

    void AddRun (int fFill, int fRun, const char* fStart, int fSections, double fLumi = 0);
    void AddSections (int fRun, int fFirst, int fLast, double fLumi = 0);
    void AddSection (int fRun, int fSection, double fLumi = 0);

    bool dumpToFile (const std::string& fFileName) const;

    std::vector<int> getAllSections (int fRun) const;
    std::vector<int> getAllRuns () const;
    std::vector<int> getAllRuns (int fFill) const;
    std::vector<int> getAllFills () const;

    void runTime (int fRun, time_t* fBegin, time_t* fEnd) const; 
    void fillTime (int fFill, time_t* fBegin, time_t* fEnd) const;
    const LumiData& data() const {return mData;}

    const DeliveredLumi* getLumiData (int fRun, int fSection) const;
  private:
    LumiData mData;
    std::map<int,std::vector<int> > mFills;
  };
}
#endif

