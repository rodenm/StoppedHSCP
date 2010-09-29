
#include "StoppedHSCP/Analysis/interface/LhcFills.h"


#include <iostream>
#include <fstream>
#include <boost/algorithm/string.hpp>
//#include <boost/lexical_cast.hpp>


LhcFills::LhcFills() {

  std::cout << "Setting up LHC fills data" << std::endl;

  // open fills file
  std::string fillsname(getenv("CMSSW_BASE"));
  fillsname+=std::string("/src/StoppedHSCP/Analysis/data/fills.txt");
  std::cout << "Getting fills from " << fillsname << std::endl;
  std::ifstream fills(fillsname.c_str(), std::ifstream::in);

  // open filling schemes file
  std::string schemesname(getenv("CMSSW_BASE"));
  schemesname+=("/src/StoppedHSCP/Analysis/data/fillingSchemes.txt");
  std::cout << "Getting filling scheme from " << schemesname << std::endl;
  std::ifstream schemes(schemesname.c_str(), std::ifstream::in);

  // read data
  std::string line;
  if (!fills.fail() && !schemes.fail()) {

    // skip header line
    getline(fills, line);

    // read remainder of file
    while (!fills.eof()) {
      
      getline(fills, line);
      std::vector<std::string> strs;
      boost::split(strs, line, boost::is_any_of("\t\v\f\r \n"));

      if (atoi(strs.at(0).c_str()) > 0) {

// 	for (std::vector<std::string>::iterator itr=strs.begin(); itr!=strs.end();) {
// 	  if (itr->length()==0) strs.erase(itr);
// 	  else ++itr;
// 	}

	Fill fill;

	// first token is fill number
	fill.number = atoi(strs.at(0).c_str());
	
	// second token is scheme name
	fill.scheme = strs.at(1);
	
	// 3rd token is csv run list
	std::vector<std::string> runstrs;
	boost::split(runstrs, strs.at(2), boost::is_any_of(",")); 
	for (unsigned i=0; i<runstrs.size(); ++i) {
	  fill.runs.push_back(atoi(runstrs.at(i).c_str()));
	}
	
	// get bunch structure

	// reset filling scheme file
	schemes.clear();
	schemes.seekg(0, std::ios::beg);
	std::string sline;

	// scan file until found scheme
	while ((sline.find(fill.scheme)!=0) && !schemes.eof() ) {
	  getline(schemes, sline);
	}
	if (!schemes.eof()) {

	  // first line after scheme is beam 1
	  getline(schemes, sline);	    
	  std::vector<std::string> bxstrs;
	  boost::split(bxstrs, sline, boost::is_any_of(",")); 
	  for (unsigned i=0; i<bxstrs.size(); ++i) {
	    fill.beam1.push_back(atoi(bxstrs.at(i).c_str()));
	  }
	  
	  // second line after scheme is beam 2
	  getline(schemes, sline);
	  boost::split(bxstrs, sline, boost::is_any_of(",")); 
	  for (unsigned i=0; i<bxstrs.size(); ++i) {
	    fill.beam2.push_back(atoi(bxstrs.at(i).c_str()));
	  }
	}
	
	fills_.push_back(fill);
	
      }
      
    }
    
  }

  std::cout << std::endl;

}


LhcFills::~LhcFills() {

}


std::vector<unsigned long> LhcFills::getRuns(unsigned fill) {

  for (unsigned f=0; f<fills_.size(); ++f) {
    if (fills_.at(f).number == fill) return fills_.at(f).runs;
  }
  return std::vector<unsigned long>(0);

}


std::string LhcFills::getFillingScheme(unsigned fill) {

  for (unsigned f=0; f<fills_.size(); ++f) {
    if (fills_.at(f).number == fill) return fills_.at(f).scheme;
  }
  return std::string();

}


std::vector<unsigned> LhcFills::getCollisions(unsigned fill) {

  std::vector<unsigned> colls(0);

  for (unsigned f=0; f<fills_.size(); ++f) {
    if (fills_.at(f).number == fill) {
      for (unsigned b1=0; b1<fills_.at(f).beam1.size(); ++b1) {
	for (unsigned b2=0; b2<fills_.at(f).beam2.size(); ++b2) {
	  if (fills_.at(f).beam1.at(b1) == fills_.at(f).beam2.at(b2)) {
	    colls.push_back(fills_.at(f).beam1.at(b1));
	  }
	}
      }

    }

  }

  return colls;

}


std::vector<unsigned> LhcFills::getBunches(unsigned fill) {

  std::vector<unsigned> bxs(0);

  for (unsigned f=0; f<fills_.size(); ++f) {

    if (fills_.at(f).number == fill) {
      for (unsigned b1=0; b1<fills_.at(f).beam1.size(); ++b1) {
	bxs.push_back(fills_.at(f).beam1.at(b1));
      }
      for (unsigned b2=0; b2<fills_.at(f).beam2.size(); ++b2) {
	bxs.push_back(fills_.at(f).beam2.at(b2));
      }
    }
    
  }

  sort(bxs.begin(), bxs.end());
  bxs.erase(std::unique(bxs.begin(), bxs.end()), bxs.end());  

  return bxs;

}


unsigned long LhcFills::getFillFromRun(unsigned long run) {

  for (unsigned f=0; f<fills_.size(); ++f) {
    for (unsigned r=0; r<fills_.at(f).runs.size(); ++r) {
      if (fills_.at(f).runs.at(r) == run) return fills_.at(f).number;
    }
  }
  return 0;

}


std::string LhcFills::getFillingSchemeFromRun(unsigned long run) {
  return getFillingScheme(getFillFromRun(run));
}


std::vector<unsigned> LhcFills::getCollisionsFromRun(unsigned long run) {
  return getCollisions(getFillFromRun(run));
}


std::vector<unsigned> LhcFills::getBunchesFromRun(unsigned long run) {
  return getBunches(getFillFromRun(run));
}


void LhcFills::printSummary(std::ostream& o) {
  o << "Fill Summary" << std::endl;
  for (unsigned i=0; i<fills_.size(); ++i) {
    o << fills_.at(i).number << "\t" << fills_.at(i).scheme << std::endl;
  }
  o << std::endl;
}


void LhcFills::print(std::ostream& o) {
  o << "Fill Information" << std::endl;
  for (unsigned i=0; i<fills_.size(); ++i) {
    o << "Fill " << fills_.at(i).number << std::endl;
    o << "\t" << "Runs   : ";
    for (unsigned j=0; j<fills_.at(i).runs.size(); ++j) {
      o << fills_.at(i).runs.at(j) << ",";
    }
    o << std::endl;
    o << "\t" << "Scheme : " << fills_.at(i).scheme << std::endl;
    o << "\t" << "Beam 1 : ";
    for (unsigned j=0; j<fills_.at(i).beam1.size(); ++j) {
      o << fills_.at(i).beam1.at(j) << ",";
    }
    o << std::endl;
    o << "\t" << "Beam 2 : ";
    for (unsigned j=0; j<fills_.at(i).beam2.size(); ++j) {
      o << fills_.at(i).beam2.at(j) << ",";
    }
    o << std::endl;
  }
  o << std::endl;
}


// this is a temporary measure
// write file of same format as used previous to set masks
void LhcFills::writeBunchMaskFile() {

  std::ofstream ofile;
  ofile.open("bx_mask.csv");

  for (unsigned f=0; f<fills_.size(); ++f) {

    for (unsigned r=0; r<fills_.at(f).runs.size(); ++r) {

      std::vector<unsigned> mask(0);

      for (unsigned b=0; b<fills_.at(f).beam1.size(); ++b) {
	mask.push_back( fills_.at(f).beam1.at(b)-1 );
	mask.push_back( fills_.at(f).beam1.at(b) );
	mask.push_back( fills_.at(f).beam1.at(b)+1 );
      }
      for (unsigned b=0; b<fills_.at(f).beam2.size(); ++b) {
	mask.push_back( fills_.at(f).beam2.at(b)-1 );
	mask.push_back( fills_.at(f).beam2.at(b) );
	mask.push_back( fills_.at(f).beam2.at(b)+1 );
      }

      // sort and remove duplicates
      sort(mask.begin(), mask.end());
      mask.erase(std::unique(mask.begin(), mask.end()), mask.end());

      ofile << fills_.at(f).runs.at(r) << ",";

      for (unsigned i=0; i<mask.size(); ++i) {
	ofile << mask.at(i) << ",";
      }

      ofile << std::endl;
    }

  }

}
