
#include "StoppedHSCP/Analysis/interface/LhcFills.h"


#include <iostream>
#include <fstream>
#include <boost/algorithm/string.hpp>
//#include <boost/lexical_cast.hpp>


LhcFills::LhcFills() {

  // open fills file
  std::string fillsname("StoppedHSCP/Analysis/data/fills.txt");
  std::ifstream fills(fillsname.c_str(), std::ifstream::in);

  // open filling schemes file
  std::string schemesname("StoppedHSCP/Analysis/data/fillingSchemes.txt");
  std::ifstream schemes(schemesname.c_str(), std::ifstream::in);

  // read data
  std::string line;
  if (!fills.fail() && !schemes.fail()) {

    // skip header line
    getline(fills, line);

    // read remainder
    while (!fills.eof()) {
      
      getline(fills, line);
      std::vector<std::string> strs;
      boost::split(strs, line, boost::is_any_of("\t\v\f\r \n"));

      if (atoi(strs.at(0).c_str()) > 0) {

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

}

LhcFills::~LhcFills() {

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
