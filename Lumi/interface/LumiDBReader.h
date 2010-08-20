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
  bool validRun (int fRun);
  bool validSection (int fRun, int fSection);
  std::vector<int> getAllCMSSections (int fRun);
  std::vector<int> getAllSections (int fRun);
  bool getSummary (int fRun, int fSection, LumiSummaryRecord* fRecord);
  bool getDetails (int fSummaryId, LumiDetailsRecord* fRecord);
 private:
  oracle::occi::Environment* mEnv;
  oracle::occi::Connection* mConn;
};

#endif
