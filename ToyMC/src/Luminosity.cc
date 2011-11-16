#include "StoppedHSCP/ToyMC/interface/Luminosity.h"

//#include "StoppedHSCP/ToyMC/interface/jsonxx.h"

#include "OnlineDB/Oracle/interface/Oracle.h" 

#include "TFile.h"
#include "TH1D.h"

#include <algorithm>

#include <fstream>
#include <iostream>
#include <sstream>
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>

const double Luminosity::LUMIFILE_TO_PB = 1e-6;
const double Luminosity::THRESHOLD = 0.00001;  // threshold below which lumi is ignored (in pb-1)

Luminosity::Luminosity() {

}

Luminosity::~Luminosity() {

}


unsigned int Luminosity::size() const {
  return lumis_.size();
}


void Luminosity::makePlots() const {
  TCanvas *c = new TCanvas("lumi_dist");
  
  c->cd();

  TH1D *lumi_dist_h = new TH1D("lumi_dist_h", "Luminosity distribution",
			       lumis_.size(), -0.5, lumis_.size() -0.5);
  TH1D *cms_dist_h = new TH1D("cms_dist_h", "CMS Sensitivity",
			       lumis_.size(), -0.5, lumis_.size() -0.5);

  unsigned int counter = 0;
  for (std::vector<struct LumiBlock>::const_iterator cit = lumis_.begin();
       cit != lumis_.end(); cit++) {
    lumi_dist_h->Fill(counter, cit->lumi);
    cms_dist_h->Fill(counter++, (cit->good?
				 1. : 0));
  }

  lumi_dist_h->Draw();
  cms_dist_h->Draw("same");
  cms_dist_h->SetLineColor(4);
  cms_dist_h->SetFillColor(4);
  cms_dist_h->SetFillStyle(3005);
  c->Print("lumi_dist.eps");
  c->Write();

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

  // loop over runs
  for (unsigned run=lumiFirstRun; run<=lumiLastRun; ++run) {

    // get all sections
    std::vector<int> lumiList;
    char query [4096];
    sprintf (query, "select LUMILSNUM from cms_lumi_prod.LUMISUMMARY where RUNNUM=%d ORDER BY LUMILSNUM", run);
    oracle::occi::Statement *stmt = dbConn->createStatement(query);
    oracle::occi::ResultSet *result1 = stmt->executeQuery();

    while (result1->next()) {
      lumiList.push_back(result1->getInt(1));
    }
    stmt->closeResultSet(result1);
    dbConn->terminateStatement(stmt);

//   // get run info
//   char query [4096];
//   sprintf (query, "select RUNNUM, HLTKEY, FILLNUM, STARTTIME, STOPTIME from cms_lumi_prod.cmsrunsummary where RUNNUM=%d", fRun);
//   Statement *stmt = mConn->createStatement(query);
//   ResultSet *rs = stmt->executeQuery();
//   if (!rs->next()) return false;
//   fRecord->run = rs->getInt(1);
//   fRecord->hltKey = rs->getString(2);
//   fRecord->fill = rs->getInt(3);
//   time_t utime = 0;
//   convertTimestamp (rs->getTimestamp(4), &utime);
//   fRecord->startTime = utime;
//   convertTimestamp (rs->getTimestamp(5), &utime);
//   fRecord->stopTime = utime;

    std::cout << "Getting lumi data for run " << run << std::endl;

    // loop over lumis?
    std::vector<int>::const_iterator ls;
    for (ls=lumiList.begin(); ls!=lumiList.end(); ++ls) {

      char query2 [4096];
      sprintf (query2, "select RUNNUM, CMSLSNUM, INSTLUMI from cms_lumi_prod.LUMISUMMARY where RUNNUM=%d and LUMILSNUM=%d", run, (*ls));
      //      sprintf (query2, "select LUMISUMMARY_ID, RUNNUM, CMSLSNUM, LUMILSNUM, LUMIVERSION, DTNORM, LHCNORM, INSTLUMI, INSTLUMIERROR, INSTLUMIQUALITY, CMSALIVE, STARTORBIT, NUMORBIT, LUMISECTIONQUALITY, BEAMENERGY, BEAMSTATUS from cms_lumi_prod.LUMISUMMARY where RUNNUM=%d and LUMILSNUM=%d", run, *ls);

      //      std::cout << "Querying lumi DB about run " << run << ", LS " << (*ls) << std::endl;
      oracle::occi::Statement *stmt2 = dbConn->createStatement(query2);
      oracle::occi::ResultSet *result2 = stmt2->executeQuery();

      if (!result2->next()) {
	std::cerr << "Failed to retrieve lumi info for run " << run << ", LS " << (*ls) << std::endl;
	continue;
      }

      // create and fill lumi block
      LumiBlock lb;

      lb.run  = run;
      lb.ls   = (unsigned long) result2->getInt(2);
      lb.lumi = result2->getDouble(3);

      stmt2->closeResultSet(result2);
      dbConn->terminateStatement(stmt2);

      lb.good = goodData(lb.run, lb.ls);
      
      totalLumi += lb.lumi;
      lumis_.push_back(lb);

    }

  }

  // clean up DB connection
  if (dbConn) {
    dbEnv->terminateConnection(dbConn);
    dbConn = 0;
  }

  oracle::occi::Environment::terminateEnvironment (dbEnv);
  
}


void Luminosity::buildFromFile(std::vector<unsigned long> runs,
			       bool useHists,
			       std::string goodLSFile,
			       unsigned lumiFirstRun,
			       unsigned lumiLastRun) {

  std::cout << "Setting up Lumi data" << std::endl;

  // open file with lumi info
  std::string filename(getenv("CMSSW_BASE"));
  filename+=std::string("/src/StoppedHSCP/Analysis/data/lumi_all.csv");
  std::cout << "Reading lumi info from " << filename << std::endl;
  std::ifstream lumifile(filename.c_str());
  
  // open GOODLS file with CMS live info
  openGoodLSFile(useHists, goodLSFile);

  // setup lumi info
  lumis_.clear();
  totalLumi = 0.;
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

	totalLumi += lb.lumi;
	lumis_.push_back(lb);

      }

    }

  }
  else {
    std::cerr << "Could not open lumi file : " << filename << std::endl;
  }

  // count good lumis
  nGoodLS = 0;
  for (unsigned i=0; i<lumis_.size(); ++i) {
    if (lumis_.at(i).good) ++nGoodLS;
  }

  dump(std::cout, false);
  std::cout << std::endl;

  makePlots();

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
}


void Luminosity::dump(ostream& o, bool full) {

  if (full) {
    for (unsigned i=0; i<lumis_.size(); ++i) {
      if (lumis_.at(i).good) {
	o << "Good lumi : " << lumis_.at(i).run << "," << lumis_.at(i).ls << " : " << lumis_.at(i).lumi << std::endl;
      }
    }
  }

  std::cout << "Total lumi                 : " << totalLumi << " /pb" << std::endl;
  std::cout << "N lumi sections good/total : " << nGoodLS << "/" << lumis_.size() << std::endl;
  if (lumis_.size() > 0) {
    std::cout << "First run                  : " << lumis_.begin()->run << std::endl;
    std::cout << "Last run                   : " << --(lumis_.end())->run << std::endl;
  }

}
