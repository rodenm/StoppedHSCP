#include "StoppedHSCP/ToyMC/interface/Luminosity.h"

#include "StoppedHSCP/Ntuples/interface/Constants.h"

//#include "StoppedHSCP/ToyMC/interface/jsonxx.h"

#include "OnlineDB/Oracle/interface/Oracle.h" 

#include "TFile.h"
#include "TH1D.h"

#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>

const double Luminosity::LUMIFILE_TO_PB = 1e-6;
const double Luminosity::THRESHOLD = 0.00001;  // threshold below which lumi is ignored (in pb-1)

time_t convertOracleTimestamp(const oracle::occi::Timestamp& timestamp) {
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
  time_t output = localTime - epochTime;
  return output;
}

time_t convertTimestamp(std::string timestamp) {

  // string input format is "mm/dd/yy HH:MM:SS"

  struct tm epoch;
  epoch.tm_year = 1970 - 1900;
  epoch.tm_mon = 1;
  epoch.tm_mday = 1;
  epoch.tm_hour = 0;
  epoch.tm_min = 0;
  epoch.tm_sec = 0;
  epoch.tm_isdst = 0;
  time_t epochTime = mktime (&epoch);

  struct tm local;
  std::vector<std::string> vals;
  boost::split(vals, timestamp, boost::is_any_of("/ :"));
//   std::cout << timestamp << std::endl;
//   std::cout << vals.at(0) << " " << vals.at(1) << " " << vals.at(2) << " " << vals.at(3) << " " << vals.at(4) << " " << vals.at(5) << std::endl;
  local.tm_year = 100+boost::lexical_cast<int>(vals.at(2));
  local.tm_mon  = boost::lexical_cast<int>(vals.at(0));
  local.tm_mday = boost::lexical_cast<int>(vals.at(1));
  local.tm_hour = boost::lexical_cast<int>(vals.at(3));
  local.tm_min  = boost::lexical_cast<int>(vals.at(4));
  local.tm_sec  = boost::lexical_cast<int>(vals.at(5));
  time_t localTime = mktime(&local);

  time_t output = localTime - epochTime;
  //  std::cout << ctime(&output);
  return output;
		     
}


Luminosity::Luminosity() :
  useHists_(false),
  histFile_(0),
  lumis_(0),
  totalLumi_(0),
  nGoodLS_(0)
{

}

Luminosity::~Luminosity() {

}


unsigned int Luminosity::size() const {
  return lumis_.size();
}


void Luminosity::makePlots() const {

  std::cout << "Making plots of " << lumis_.size() << " LS" << std::endl;

  TCanvas *c = new TCanvas("cLumi", "", 1500, 300);
  
  c->cd();

  TH1D* hLumi = new TH1D("hLumiDist", "Delivered luminosity", lumis_.size(), -0.5, lumis_.size() -0.5);
  TH1D* hGood = new TH1D("hSensitive", "CMS Sensitivity", lumis_.size(), -0.5, lumis_.size() -0.5);

  for (unsigned i=0; i<lumis_.size(); ++i) {
    hLumi->Fill(i, lumis_.at(i).lumi);
    hGood->Fill(i, lumis_.at(i).good ? 1. : 0. );
  }

  hLumi->Draw();
  c->Print("LumiDist.png");

  hGood->SetLineColor(4);
  hGood->Draw();
  c->Print("GoodDataDist.png");

  hLumi->Scale(10./hLumi->GetMaximum());
  hLumi->Draw();
  hGood->Draw("SAME");
  c->Print("LumiDist2.png");

}


void Luminosity::openGoodLSFile(bool useHists,
				std::string goodLSFile) {

  useHists_ = useHists;

  // open GOODLS file with CMS live info
  std::cout << "Reading good LS info from " << goodLSFile << std::endl;

  if (useHists_) {
    histFile_ = new TFile(goodLSFile.c_str(), "read");
  }
  else {

    std::ifstream goodLSfile(goodLSFile.c_str());
    std::string line;
    getline(goodLSfile, line);
    std::istringstream iss(line);

    jsonxx::Object::parse(iss, goodLumis_);
    std::cout << "Found " << goodLumis_.kv_map().size() << " runs in good LS file" << std::endl;
  }

}


bool Luminosity::goodData(unsigned run, unsigned ls) {

  bool good=false;

  std::string runstr = boost::lexical_cast<std::string>(run);
  //  std::string lsstr = boost::lexical_cast<std::string>(run);

  if (useHists_) {
    std::string hstr = std::string("runs/")+runstr+std::string("/hlb")+runstr;
    //	  std::cout << histFile << " " << hstr << std::endl;
    TH1D* hlb = (TH1D*) histFile_->Get(hstr.c_str());
    if (hlb != NULL) {
      good = (hlb->GetBinContent(ls+1) > 0);
    }
    else {
      // do nothing - probably just means this entire run was not marked good
      //      std::cerr << "ERROR : NULL histogram found in Luminosity::goodData() - " << hstr << std::endl;
    }
    
  }
  else {
    if (goodLumis_.has<jsonxx::Array>(runstr)) {
      // loop over good LS ranges
      for (unsigned i=0; i<goodLumis_.get<jsonxx::Array>(runstr).size(); ++i) {
	
	// get range
	if (goodLumis_.get<jsonxx::Array>(runstr).has<jsonxx::Array>(i)) {
	  if (goodLumis_.get<jsonxx::Array>(runstr).get<jsonxx::Array>(i).has<double>(0) &&
	      goodLumis_.get<jsonxx::Array>(runstr).get<jsonxx::Array>(i).has<double>(1)) {
	    if (ls >= (unsigned) goodLumis_.get<jsonxx::Array>(runstr).get<jsonxx::Array>(i).get<double>(0) ||
		ls <= (unsigned) goodLumis_.get<jsonxx::Array>(runstr).get<jsonxx::Array>(i).get<double>(1) ) {
	      good = true;
	    }
	  }
	}   
      }	
    }    	    
    
  }
  
  return good;

}


void Luminosity::buildFromDB(std::vector<unsigned long> runs,
			     bool useHists,
			     std::string goodLSFile,
			     unsigned lumiFirstRun,
			     unsigned lumiLastRun) {
  
  // reset stuff
  lumis_.clear();
  totalLumi_ = 0.;
  nGoodLS_   = 0;

  // connect to DB
  oracle::occi::Environment* dbEnv = oracle::occi::Environment::createEnvironment();
  oracle::occi::Connection* dbConn;
  
  const std::string userName = "cms_runinfo_r";
  const std::string password = "mickey2mouse";
  const std::string connectString = "cms_orcoff_prod";

  dbConn = dbEnv->createConnection(userName, password, connectString);
  std::cout << "Succesfully opened DB connection" << std::endl;

  // read good data file
  openGoodLSFile(useHists, goodLSFile);

  // prepare query
   std::string query( "SELECT cms_lumi_prod.lumisummary.runnum, cms_lumi_prod.lumisummary.lumilsnum, cms_lumi_prod.lumisummary.cmslsnum, cms_lumi_prod.lumisummary.instlumi, cms_lumi_prod.lumisummary.lumiversion, cms_lumi_prod.lumisummary.numorbit, cms_lumi_prod.cmsrunsummary.starttime FROM cms_lumi_prod.cmsrunsummary INNER JOIN cms_lumi_prod.lumisummary ON cms_lumi_prod.cmsrunsummary.runnum=cms_lumi_prod.lumisummary.runnum WHERE cms_lumi_prod.cmsrunsummary.runnum>= " );
   query.append( boost::lexical_cast<std::string>(lumiFirstRun) );
   query.append( " AND cms_lumi_prod.cmsrunsummary.runnum<=" );
   query.append( boost::lexical_cast<std::string>(lumiLastRun) );
   query.append( " ORDER BY cms_lumi_prod.lumisummary.runnum,cms_lumi_prod.lumisummary.lumilsnum " );

   std::cout << std::endl << query << std::endl << std::endl;

  // execute query
  oracle::occi::Statement *stmt = dbConn->createStatement(query.c_str());
  oracle::occi::ResultSet *result = stmt->executeQuery();

  // loop over returned lumi sections and store
  while (result->next() ){
    
    LumiBlock lb;
    
    lb.run  = (unsigned long) result->getInt(1);
    lb.id   = (unsigned long) result->getInt(2);
    lb.ls   = (unsigned long) result->getInt(3);
    lb.lumi = result->getDouble(4);
    int ver = result->getInt(5);
    lb.good = goodData(lb.run, lb.ls);	

    lb.orbit = result->getInt(6);
    // calculate timestamp from run start + orbits
    lb.timestamp = 0.;

    //std::cout << "Run " << lb.run << ", LS " << lb.ls << ", lumi " << lb.lumi << ", ver " << ver << std::endl;
    
    lumis_.push_back(lb);
    
    totalLumi_ += lb.lumi;
    if (lb.good) ++nGoodLS_;
   
  }
  
  // terminate query
  stmt->closeResultSet(result);
  dbConn->terminateStatement(stmt);
  
  // close DB connection
  if (dbConn) {
    dbEnv->terminateConnection(dbConn);
    dbConn = 0;
  }

  oracle::occi::Environment::terminateEnvironment (dbEnv);
  
  makePlots();

  dump(std::cout, false);

}


void Luminosity::buildFromFile(std::string filename,
			       std::vector<unsigned long> runs,
			       bool useHists,
			       std::string goodLSFile,
			       unsigned lumiFirstRun,
			       unsigned lumiLastRun) {

  std::cout << "Setting up Lumi data" << std::endl;

  // open file with lumi info
  std::cout << "Reading lumi info from " << filename << std::endl;
  std::ifstream lumifile(filename.c_str());
  
  // open GOODLS file with CMS live info
  openGoodLSFile(useHists, goodLSFile);

  // setup lumi info
  lumis_.clear();
  totalLumi_ = 0.;
  nGoodLS_   = 0;

  if (!lumifile.fail()) {

    // read header
    std::string line;
    getline(lumifile, line);

    // loop over lines
    while (!lumifile.eof()) {

      getline(lumifile, line);

      // split into tokens
      std::vector<std::string> strs;
      boost::split(strs, line, boost::is_any_of(",\n"));

      // convert to lumi block info
      if (strs.size() > 3) {

	LumiBlock lb;
	lb.run  = boost::lexical_cast<unsigned long>(strs.at(0));
	lb.ls   = boost::lexical_cast<unsigned long>(strs.at(1));
	//	try {
	lb.lumi = LUMIFILE_TO_PB * boost::lexical_cast<double>(strs.at(2));
// 	}
// 	catch(...) {
// 	  std::cout << strs.at(0) << "," << strs.at(1) << "," << strs.at(2) << "," << strs.at(3) << std::endl;
// 	}
	lb.good = false;
	
	// ignore anything before the first lumi run
	if (lb.run < lumiFirstRun) continue;

	// stop if we went past the last lumi run
	if (lb.run > lumiLastRun) break;

	// set good data flag
	lb.good = goodData(lb.run, lb.ls);

	lumis_.push_back(lb);

	totalLumi_ += lb.lumi;
	if (lb.good) ++nGoodLS_;

      }

    }

  }
  else {
    std::cerr << "Could not open lumi file : " << filename << std::endl;
  }

  makePlots();

  dump(std::cout, false);

}


void Luminosity::buildFromFile2(std::string filename,
				std::vector<unsigned long> runs,
				bool useHists,
				std::string goodLSFile,
				unsigned lumiFirstRun,
				unsigned lumiLastRun) {

  std::cout << "Setting up Lumi data" << std::endl;

  // open file with lumi info
  std::cout << "Reading lumi info from " << filename << std::endl;
  std::ifstream lumifile(filename.c_str());
  
  // open GOODLS file with CMS live info
  openGoodLSFile(useHists, goodLSFile);

  // setup lumi info
  lumis_.clear();
  totalLumi_ = 0.;
  nGoodLS_   = 0;

  if (!lumifile.fail()) {

    // read header
    std::string line;
    getline(lumifile, line);

    // loop over lines
    while (!lumifile.eof()) {

      getline(lumifile, line);

      // split into tokens
      std::vector<std::string> strs;
      boost::split(strs, line, boost::is_any_of(",\n"));

      // convert to lumi block info
      if (strs.size() > 5) {

	LumiBlock lb;

	// strs.at(0) = run
	// strs.at(1) = ls:ls ???
	// strs.at(2) = timestamp in format "mm/dd/yy HH:MM:SS"
	// strs.at(3) = beam mode
	// strs.at(4) = beam energy
	// strs.at(5) = delivered lumi
	// strs.at(6) = recorded lumi (deadtime corrected)
	
	//	std::cout << strs.at(0) << " " << strs.at(1) << " " << strs.at(2) << " " << strs.at(3) << " " << strs.at(4) << " " << strs.at(5) << " " << strs.at(6) << std::endl;

	// run
	std::vector<std::string> rfstrs;
	boost::split(rfstrs, strs.at(0), boost::is_any_of(":"));
	//	std::cout << strs.at(0) << " " << rfstrs.size() << std::endl;

	lb.run  = boost::lexical_cast<unsigned long>(rfstrs.at(0));

	// ignore anything before the first lumi run
	if (lb.run < lumiFirstRun) continue;

	// stop if we went past the last lumi run
	if (lb.run > lumiLastRun) break;
	
	// LS
	std::vector<std::string> tmp;
	boost::split(tmp, strs.at(1), boost::is_any_of(":"));
	lb.ls   = boost::lexical_cast<unsigned long>(tmp.at(0));

	// time
	lb.timestamp = convertTimestamp(strs.at(2));

	// lumi
	lb.lumi = LUMIFILE_TO_PB * boost::lexical_cast<double>(strs.at(5));

	// data good
	lb.good = false;
	
	// set good data flag
	lb.good = goodData(lb.run, lb.ls);

	//	std::cout << "This LS : " << lb.run << "/" << lb.ls << " at " << ctime(&(lb.timestamp));

	// check if this lb comes immediately after the previous one
	// and insert blank lumi sections if not
	if (lumis_.size()>0) {

	  LumiBlock last = lumis_.at(lumis_.size()-1);
	  double diff = difftime(lb.timestamp, last.timestamp);
	  int nLBToInsert = (int) ( (diff-TIME_PER_LS) / TIME_PER_LS );

	  if (nLBToInsert > 1) {

	    // adjacent LS in the same run, should not be inserting any LS
	    if (last.run == lb.run && (lb.ls-last.ls)==1) {
	      std::cerr << "ERROR : Time between adjacent LS > 23 seconds" << std::endl;
	      std::cerr << "  Last LS : " << last.run << "/" << last.ls << " at " << ctime(&(last.timestamp));
	      std::cerr << "  This LS : " << lb.run << "/" << lb.ls << " at " << ctime(&(lb.timestamp));
	      std::cerr << "  Time between is " << diff << " seconds" << std::endl;
	      std::cerr << "  Want to insert " << nLBToInsert << " LS" << std::endl;
	      std::cerr << "  Not going to insert any LS" << std::endl;
	      continue;
	    }
	    
	    // LS missing from a run
	    if (last.run == lb.run && (lb.ls-last.ls)>1) {
	      std::cout << "WARNING : Inserting LS within a run" << std::endl;
	      std::cout << "  Last LS : " << last.run << "/" << last.ls << " at " << ctime(&(last.timestamp));
	      std::cout << "  This LS : " << lb.run << "/" << lb.ls << " at " << ctime(&(lb.timestamp));
	      std::cout << "  Time between is " << diff << " seconds" << std::endl;
	      std::cout << "  Wanted to insert " << nLBToInsert << " LS" << std::endl;
	      std::cout << "  Going to insert " << (lb.ls-last.ls)-1 << " LS" << std::endl;
	      nLBToInsert = (int) (lb.ls-last.ls)-1;
	    }

	    // debug print out
// 	    std::cout << "Last LS : " << last.run << "/" << last.ls << " at " << ctime(&(last.timestamp));
// 	    std::cout << "This LS : " << lb.run << "/" << lb.ls << " at " << ctime(&(lb.timestamp));
// 	    std::cout << "Time between is " << diff << " seconds" << std::endl;
// 	    std::cout << "Want to insert " << nLBToInsert << " LS" << std::endl;
	    
	    // do it
	    for (int i=1; i<=nLBToInsert; ++i) {
	      LumiBlock tmp;
	      tmp.run = last.run;
	      tmp.ls  = last.ls+i;
	      lumis_.push_back(tmp);
	    }
	  }
	  
	}

	// add the real lumi block
	lumis_.push_back(lb);

	// keep a tally
	totalLumi_ += lb.lumi;
	if (lb.good) ++nGoodLS_;

      }
      else {
	std::cout << "Bad line in lumi file : " << line << std::endl;
      }

    }

  }
  else {
    std::cerr << "Could not open lumi file : " << filename << std::endl;
  }

  makePlots();

  dump(std::cout, false);

}


void Luminosity::buildFromModel(unsigned int cycles, 
				unsigned int units_on, 
				unsigned int units_off,
				double amt) {
  lumis_.clear();
  lumis_.reserve(cycles*(units_on+units_off));
  
  LumiBlock l;
  l.run = 1;
  l.ls = 1;
  l.good = true;
  unsigned int i,j;
  for (i = 0; i < cycles; i++) {
    for (j = 0; j < units_on; j++) {
      l.ls++;
      l.lumi = amt;
      lumis_.push_back(l);
    }
    for (j = 0; j < units_off; j++) {
      l.ls++;
      l.lumi = 0;
      lumis_.push_back(l);
    }
  }

  makePlots();

  dump(std::cout, false);

}


void Luminosity::dump(ostream& o, bool full) {

  if (full) {
    for (unsigned i=0; i<lumis_.size(); ++i) {
      if (lumis_.at(i).good) {
	o << "Good lumi : " << lumis_.at(i).run << "," << lumis_.at(i).ls << " : " << lumis_.at(i).lumi << std::endl;
      }
    }
  }

  std::cout << "Total lumi                 : " << totalLumi_ << " /pb" << std::endl;
  std::cout << "N lumi sections good/total : " << nGoodLS_ << "/" << lumis_.size() << std::endl;
  if (lumis_.size() > 0) {
    std::cout << "First run                  : " << lumis_.begin()->run << std::endl;
    std::cout << "Last run                   : " << lumis_.at(lumis_.size()-1).run << std::endl;
  }

  std::cout << std::endl;

}
