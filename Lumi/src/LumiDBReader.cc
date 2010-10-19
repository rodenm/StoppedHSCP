#include <iostream>

#include "StoppedHSCP/Lumi/interface/LumiDBReader.h"
#include "OnlineDB/Oracle/interface/Oracle.h" 

using namespace std;
using namespace oracle::occi;

namespace shscp {

namespace {
  void fillBXValues (Blob& dbData, double data[BXINORBIT]) {
    if (dbData.isNull()) {
      cout << "fillBXValues-> Null DB data" << endl;
    }
    else {
      dbData.open(OCCI_LOB_READONLY);
      int dblength = dbData.length();
      if (dblength == sizeof(float)*BXINORBIT) {
	float buffer[BXINORBIT];
	dbData.read (dbData.length(), (unsigned char*)buffer, sizeof (buffer));  
	for (int i = 0; i < BXINORBIT; ++i) data[i] = buffer[i];
      }
      else if (dblength == sizeof(short)*BXINORBIT) {
	short buffer[BXINORBIT];
	dbData.read (dbData.length(), (unsigned char*)buffer, sizeof (buffer));  
	for (int i = 0; i < BXINORBIT; ++i) data[i] = buffer[i];
      }
      else {
	cout << "fillBXValues-> size mismatch: " 
	     << dbData.length() << '/' << double (dbData.length())/BXINORBIT << endl;
      }
      dbData.close();
    }
  }

  void convertTimestamp (const Timestamp& timestamp, unsigned* utime) {
    struct tm timeinfo;
    int t0;
    unsigned t1,t2,t3,t4;
    timestamp.getDate(t0, t2, t3);
    timeinfo.tm_year = t0 - 1900;
    timeinfo.tm_mon = int(t2) - 1;
    timeinfo.tm_mday = int(t3);
    timestamp.getTime (t1, t2, t3, t4);
    timeinfo.tm_hour = int(t1);
    timeinfo.tm_min = int(t2);
    timeinfo.tm_sec = int(t3);
    timeinfo.tm_isdst = -1;
    *utime = mktime (&timeinfo);
  }
}

LumiDBReader::LumiDBReader ()
  : mEnv (Environment::createEnvironment()),
    mConn (0)
{}

LumiDBReader::~LumiDBReader () {
  closeConnection ();
  Environment::terminateEnvironment (mEnv);
}

void LumiDBReader::openConnection () {
  const string userName = "cms_runinfo_r";
  const string password = "mickey2mouse";
  const string connectString = "cms_orcoff_prod";
  if (mConn) return;
  mConn = mEnv->createConnection(userName, password, connectString);
}

void LumiDBReader::closeConnection () {
  if (mConn) {
    mEnv->terminateConnection(mConn);
    mConn = 0;
  }
}
  
  bool LumiDBReader::getRunSummary (int fRun, RunSummaryRecord* fRecord) {
    if (!fRecord) return false;
    openConnection ();
    char query [4096];
    sprintf (query, "select RUNNUM, HLTKEY, FILLNUM, STARTTIME, STOPTIME from cms_lumi_prod.cmsrunsummary where RUNNUM=%d", fRun);
  Statement *stmt = mConn->createStatement(query);
  ResultSet *rs = stmt->executeQuery();
  if (!rs->next()) return false;
  fRecord->run = rs->getInt(1);
  fRecord->hltKey = rs->getString(2);
  fRecord->fill = rs->getInt(3);
  unsigned utime = 0;
  convertTimestamp (rs->getTimestamp(5), &utime);
  fRecord->startTime = utime;
  convertTimestamp (rs->getTimestamp(6), &utime);
  fRecord->stopTime = utime;
  if (rs->next()) {
    cout << "LumiDBReader::getRunSummary-> More than one record for run: "
	 << fRun 
	 << endl;
  }
  stmt->closeResultSet(rs);
  mConn->terminateStatement(stmt);
  return true;
}

bool LumiDBReader::getSummary (int fRun, int fSection, LumiSummaryRecord* fRecord) {
  openConnection ();
  char query [4096];
  if (fRecord) {
    sprintf (query, "select LUMISUMMARY_ID, RUNNUM, CMSLSNUM, LUMILSNUM, LUMIVERSION, DTNORM, LHCNORM, INSTLUMI, INSTLUMIERROR, INSTLUMIQUALITY, CMSALIVE, STARTORBIT, NUMORBIT, LUMISECTIONQUALITY, BEAMENERGY, BEAMSTATUS from cms_lumi_prod.LUMISUMMARY where RUNNUM=%d and LUMILSNUM=%d", fRun, fSection);
  }
  else {
    sprintf (query, "select RUNNUM,  from cms_lumi_prod.LUMISUMMARY where RUNNUM=%d and LUMILSNUM=%d", fRun, fSection);
  }
  Statement *stmt = mConn->createStatement(query);
  ResultSet *rs = stmt->executeQuery();
  if (!rs->next()) return false;
  if (fRecord) {
    fRecord->id = rs->getInt(1);
    fRecord->run = rs->getInt(2);
    fRecord->sectionCMS = rs->getInt(3);
    fRecord->sectionLUMI = rs->getInt(4);
    fRecord->version = rs->getString(5);
    fRecord->dtNorm = rs->getDouble(6);
    fRecord->lhcNorm = rs->getDouble(7);
    fRecord->instLumi = rs->getDouble(8);
    fRecord->instLumiError = rs->getDouble(9);
    fRecord->instLumiQuality = rs->getInt(10);
    fRecord->cmsAlive = rs->getInt(11);
    fRecord->startOrbit = rs->getInt(12);
    fRecord->numOrbits = rs->getInt(13);
    fRecord->quality = rs->getInt(14);
    fRecord->beamEnergy = rs->getDouble(15);
    fRecord->beamStatus = rs->getString(16);
  }
  if (rs->next()) {
    cout << "LumiDBReader::getSummary-> More than one record for run/section: "
	 << fRun << '/' << fSection 
	 << endl;
  }
  stmt->closeResultSet(rs);
  mConn->terminateStatement(stmt);
  return true;
}

std::vector<int> LumiDBReader::getAllSections (int fRun) {
  std::vector<int> result;
  openConnection ();
  char query [4096];
  sprintf (query, "select LUMILSNUM from cms_lumi_prod.LUMISUMMARY where RUNNUM=%d ORDER BY LUMILSNUM", fRun);
  Statement *stmt = mConn->createStatement(query);
  ResultSet *rs = stmt->executeQuery();
  while (rs->next()) {
    result.push_back(rs->getInt(1));
  }
  stmt->closeResultSet(rs);
  mConn->terminateStatement(stmt);
  return result;
}

std::vector<int> LumiDBReader::getAllCMSSections (int fRun) {
  std::vector<int> result;
  openConnection ();
  char query [4096];
  sprintf (query, "select CMSLSNUM from cms_lumi_prod.LUMISUMMARY where RUNNUM=%d ORDER BY CMSLSNUM", fRun);
  Statement *stmt = mConn->createStatement(query);
  ResultSet *rs = stmt->executeQuery();
  while (rs->next()) {
    int section = rs->getInt(1);
    if (section > 0) result.push_back(section);
  }
  stmt->closeResultSet(rs);
  mConn->terminateStatement(stmt);
  return result;
}
  std::vector<int> LumiDBReader::getAllRuns (int fFill) {
    std::vector<int> result;
    openConnection ();
    char query [4096];
    sprintf (query, "select RUNNUM from cms_lumi_prod.cmsrunsummary where FILLNUM=%d ORDER BY RUNNUM", fFill);
    Statement *stmt = mConn->createStatement(query);
    ResultSet *rs = stmt->executeQuery();
    while (rs->next()) {
      int run = rs->getInt(1);
      if (run > 0) result.push_back(run);
    }
    stmt->closeResultSet(rs);
    mConn->terminateStatement(stmt);
    return result;
  }


  bool LumiDBReader::getDetails (int fSummaryId, LumiDetailsRecord* fRecord, const char* fAlgorithm) {
  if (!fRecord) return false;
  openConnection ();
  char query [4096];
  sprintf (query, "select LUMIDETAIL_ID, LUMISUMMARY_ID, BXLUMIVALUE, BXLUMIERROR, BXLUMIQUALITY, ALGONAME from cms_lumi_prod.LUMIDETAIL where LUMISUMMARY_ID=%d and ALGONAME='%s'", fSummaryId, fAlgorithm);
  Statement *stmt = mConn->createStatement(query);
  ResultSet *rs = stmt->executeQuery();
  if (!rs->next()) return false;
  fRecord->id = rs->getInt(1);
  fRecord->summaryId = rs->getInt(2);
  Blob lumi = rs->getBlob(3);
  fillBXValues (lumi, fRecord->lumi);
  Blob lumiError = rs->getBlob(4);
  fillBXValues (lumiError, fRecord->lumiError);
  Blob lumiQuality = rs->getBlob(5);
  fillBXValues (lumiQuality, fRecord->lumiQuality);
  fRecord->algoName = rs->getString(6);
  if (rs->next()) {
    cout << "LumiDBReader::getDetails-> More than one record for SummaryID: " 
	 << fSummaryId
	 << endl;
  }
  stmt->closeResultSet(rs);
  mConn->terminateStatement(stmt);
  return true;
}

}
