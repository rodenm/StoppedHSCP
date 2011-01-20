#ifndef LUMI_DB_READER_H
#define LUMI_DB_READER_H

#include <string>
#include <vector>

namespace oracle {
  namespace occi {
    class Environment;
    class Connection;
  }
}

namespace shscp {

  struct RunSummaryRecord {
    int run;
    std::string hltKey;
    int fill;
    time_t startTime;
    time_t stopTime;
  };
  
  struct LumiSummaryRecord {
    int id;
    int run;
    int sectionCMS;
    int sectionLUMI;
    std::string version;
    double dtNorm;
    double lhcNorm;
    double instLumi;
    double instLumiError;
    int instLumiQuality;
    int cmsAlive;
    int startOrbit;
    int numOrbits;
    int quality;
    int beamEnergy;
    std::string beamStatus;
  };
  
  const int BXINORBIT = 3564;
  const double LHCRATE = 40.08e6; // 40MHz
  const int ORBITSINLS = 0x40000;
  const double LSTIME = double (BXINORBIT)*double(ORBITSINLS)/LHCRATE;
  struct LumiDetailsRecord {
    int id;
    int summaryId;
    double lumi[BXINORBIT];
    double lumiError[BXINORBIT];
    double lumiQuality[BXINORBIT];
    std::string algoName;
  };
  
  class LumiDBReader {
  public:
    LumiDBReader ();
    ~LumiDBReader ();
    void openConnection ();
    void closeConnection ();
    bool validRun (int fRun) {return getAllSections (fRun).size() > 0;}
    bool validSection (int fRun, int fSection) {return getSummary (fRun, fSection, 0);}
    std::vector<int> getAllCMSSections (int fRun);
    std::vector<int> getAllSections (int fRun);
    std::vector<int> getAllRuns (int fFill);
    std::vector<int> getAllFills ();
    bool getRunSummary (int fRun, RunSummaryRecord* fRecord);
    bool getSummary (int fRun, int fSection, LumiSummaryRecord* fRecord);
    bool getDetails (int fSummaryId, LumiDetailsRecord* fRecord, const char* fAlgorithm="OCC1");
    bool getRunSectionData (int fRun,
			    std::vector<LumiSummaryRecord>* fSummaryRecord,
			    std::vector<LumiDetailsRecord>* fDetailedRecord);
  private:
    oracle::occi::Environment* mEnv;
    oracle::occi::Connection* mConn;
  };
}
#endif
