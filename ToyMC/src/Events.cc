#include "StoppedHSCP/ToyMC/interface/Events.h"

#include <iostream>
#include <fstream>
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>

Events::Events(std::string filename) :
  events_(0)
{
  
  std::cout << "Setting up events" << std::endl;
  std::cout << "file : " << filename << std::endl;

  if (filename != "") {

    // open  file
    std::ifstream file(filename.c_str(), std::ifstream::in);
    
    // read data
    std::string line;
    if (!file.fail()) {
      
      // read remainder of file
      while (!file.eof()) {
	
	getline(file, line);
	std::vector<std::string> strs;
	boost::split(strs, line, boost::is_any_of(","));
	
	if (strs.size() == 5 && atoi(strs.at(0).c_str()) > 0) {
	  
	  Event evt;
	  evt.run   = atoi(strs.at(0).c_str());
	  evt.ls    = atoi(strs.at(1).c_str());
	  evt.orbit = atoi(strs.at(2).c_str());
	  evt.bx    = atoi(strs.at(3).c_str());
	  evt.id    = atoi(strs.at(4).c_str());
	  
	  events_.push_back(evt);
	}
	
      }
      
    }
    
  }

  std::cout << events_.size() << " events found" << std::endl;

}

Events::~Events() {

}


// if bool mask is true, event is not counted
unsigned Events::countAfterBXMask(std::vector<bool> mask) {

  unsigned count=0;

  for (unsigned i=0; i<events_.size(); ++i) {
    if ( !(mask.at(events_.at(i).bx)) ) ++count;
  }

  return count;

}


void Events::print(std::ostream& o) {

  for (unsigned e=0; e<events_.size(); ++e) {
    std::cout << events_.at(e).run << "," << events_.at(e).ls << "," << events_.at(e).orbit << "," << events_.at(e).bx << "," << events_.at(e).id << std::endl;
  }

}
