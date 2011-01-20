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

  void convertTimestamp (const Timestamp& timestamp, time_t* utime) {
    struct tm timeinfo,epoch;
    
    epoch.tm_year = 1970 - 1900;
    epoch.tm_mon = 0;
    epoch.tm_mday = 1;
    epoch.tm_hour = 0;
    epoch.tm_min = 0;
    epoch.tm_sec = 0;
    epoch.tm_isdst = 0;
    time_t epochTime = mktime (&epoch);
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
    timeinfo.tm_isdst = 0;
    time_t localTime = mktime (&timeinfo);
    *utime = localTime - epochTime;
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
  time_t utime = 0;
  convertTimestamp (rs->getTimestamp(4), &utime);
  fRecord->startTime = utime;
  convertTimestamp (rs->getTimestamp(5), &utime);
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


  std::vector<int> LumiDBReader::getAllFills () {
    std::vector<int> result;
    openConnection ();
    char query [4096];
    sprintf (query, "select unique FILLNUM from cms_lumi_prod.cmsrunsummary ORDER BY FILLNUM");
    Statement *stmt = mConn->createStatement(query);
    ResultSet *rs = stmt->executeQuery();
    while (rs->next()) {
      int fill = rs->getInt(1);
      if (fill > 0) result.push_back(fill);
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

  bool LumiDBReader::getRunSectionData (int fRun, 
					std::vector<LumiSummaryRecord>* fSummaryRecord,
					std::vector<LumiDetailsRecord>* fDetailedRecord) {
    if (!fSummaryRecord) return false;
    bool getDetails = fDetailedRecord;
    fSummaryRecord->clear();
    if (getDetails) fDetailedRecord->clear();
    openConnection ();
    char query [4096];
    // grab number of LS   
    sprintf (query, "select count(*) from cms_lumi_prod.lumisummary where RUNNUM=%d", fRun);
    Statement *stmt0 = mConn->createStatement(query);
    ResultSet *rs0 = stmt0->executeQuery();
    if (!rs0->next()) return false;
    int nSections = rs0->getInt(1);
    stmt0->closeResultSet(rs0);
    mConn->terminateStatement(stmt0);

    *fSummaryRecord =  std::vector<LumiSummaryRecord> (nSections);
    if (getDetails) *fDetailedRecord = std::vector<LumiDetailsRecord> (nSections);

    if (getDetails) {
      sprintf (query, "select %s, %s from cms_lumi_prod.lumisummary S join cms_lumi_prod.lumidetail D on S.LUMISUMMARY_ID=D.LUMISUMMARY_ID where S.RUNNUM=%d and D.ALGONAME='OCC1' order by S.LUMILSNUM", 
	       "S.LUMISUMMARY_ID, S.RUNNUM, S.CMSLSNUM, S.LUMILSNUM, S.LUMIVERSION, S.DTNORM, S.LHCNORM, S.INSTLUMI, S.INSTLUMIERROR, S.INSTLUMIQUALITY, S.CMSALIVE, S.STARTORBIT, S.NUMORBIT, S.LUMISECTIONQUALITY, S.BEAMENERGY, S.BEAMSTATUS",
	       "D.LUMIDETAIL_ID, D.LUMISUMMARY_ID, D.BXLUMIVALUE, D.BXLUMIERROR, D.BXLUMIQUALITY, D.ALGONAME",
	       fRun);
    }
    else {
      sprintf (query, "select %s from cms_lumi_prod.lumisummary S where S.RUNNUM=%d order by S.LUMILSNUM", 
	       "S.LUMISUMMARY_ID, S.RUNNUM, S.CMSLSNUM, S.LUMILSNUM, S.LUMIVERSION, S.DTNORM, S.LHCNORM, S.INSTLUMI, S.INSTLUMIERROR, S.INSTLUMIQUALITY, S.CMSALIVE, S.STARTORBIT, S.NUMORBIT, S.LUMISECTIONQUALITY, S.BEAMENERGY, S.BEAMSTATUS",
	       fRun);
    }
    // cout << "Prepared query: " << query << endl;
    Statement *stmt = mConn->createStatement(query);
    ResultSet *rs = stmt->executeQuery();
    int counter = 0;
    while (rs->next()) {
      if (counter >= nSections) {
	cerr << "LumiDBReader::getRunSectionData-> size mismatch: " << nSections << '/' << counter << endl;
	fSummaryRecord->resize (counter+1);
	if (getDetails) fDetailedRecord->resize (counter+1);
      }
      LumiSummaryRecord& sr = (*fSummaryRecord)[counter];
      sr.id = rs->getInt(1);
      sr.run = rs->getInt(2);
      sr.sectionCMS = rs->getInt(3);
      sr.sectionLUMI = rs->getInt(4);
      sr.version = rs->getString(5);
      sr.dtNorm = rs->getDouble(6);
      sr.lhcNorm = rs->getDouble(7);
      sr.instLumi = rs->getDouble(8);
      sr.instLumiError = rs->getDouble(9);
      sr.instLumiQuality = rs->getInt(10);
      sr.cmsAlive = rs->getInt(11);
      sr.startOrbit = rs->getInt(12);
      sr.numOrbits = rs->getInt(13);
      sr.quality = rs->getInt(14);
      sr.beamEnergy = rs->getDouble(15);
      sr.beamStatus = rs->getString(16);
      int offset = 16;

      if (getDetails) {
	LumiDetailsRecord& dr = (*fDetailedRecord)[counter];
	dr.id = rs->getInt(offset+1);
	dr.summaryId = rs->getInt(offset+2);
	Blob lumi = rs->getBlob(offset+3);
	fillBXValues (lumi, dr.lumi);
	Blob lumiError = rs->getBlob(offset+4);
	fillBXValues (lumiError, dr.lumiError);
	Blob lumiQuality = rs->getBlob(offset+5);
	fillBXValues (lumiQuality, dr.lumiQuality);
	dr.algoName = rs->getString(offset+6);
      }
      //  cout << "Query processed " << fSummaryRecord->size() << ' ' << sr.sectionLUMI << endl;
      ++counter;
    }
    stmt->closeResultSet(rs);
    mConn->terminateStatement(stmt);
    if (counter != nSections) {
      cerr << "LumiDBReader::getRunSectionData-> final size mismatch: " << nSections << '/' << counter << endl;
      fSummaryRecord->resize (counter);
      if (getDetails) fDetailedRecord->resize (counter);
    }
    return fSummaryRecord->size();
  }


}
