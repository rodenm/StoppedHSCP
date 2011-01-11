#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>

#include <algorithm>

#include "StoppedHSCP/Lumi/interface/JsonFileReader.h"

using namespace std;

JsonFileReader::JsonFileReader (const std::string& fJasonFile) {
  char flatName [L_tmpnam];
  tmpnam (flatName);
  std::string dumpCommand = "jsonFileDumper.py " + fJasonFile + "  " + std::string(flatName);
  std::cout << dumpCommand << std::endl;
  system (dumpCommand.c_str());
  std::ifstream data (flatName);
  while (data) {
    int run, lsFirst, lsLast;
    run=lsFirst=lsLast=0;
    data >> run >> lsFirst >> lsLast;
    if (lsLast > 0) {
      mData[run].push_back (std::pair<int, int> (lsFirst, lsLast));
    }
  }
  remove (flatName);
}


typedef std::map<int, std::vector <std::pair<int, int> > > AllData;
typedef std::vector <std::pair<int, int> > RunData;

bool JsonFileReader::goodLB (int fRun, int fSection) const {
  AllData::const_iterator adi = mData.find(fRun);
  if (adi != mData.end()) {
    for (RunData::const_iterator rdi = adi->second.begin(); rdi != adi->second.end(); ++rdi) {
      if (fSection >= rdi->first && fSection <= rdi->second) return true;
    }
  }
  return false;
}

std::vector<int> JsonFileReader::allRuns () const {
  std::vector<int> result;
  AllData::const_iterator adi = mData.begin();
  for (;adi != mData.end(); ++adi) {
    result.push_back(adi->first);
  }
  return result;
}

std::vector<int> JsonFileReader::allLumiBlocks (int fRun) const {
  std::vector<int> result;
  AllData::const_iterator adi = mData.find(fRun);
  if (adi != mData.end()) {
    for (RunData::const_iterator rdi = adi->second.begin(); rdi != adi->second.end(); ++rdi) {
      for (int lb = rdi->first; lb <= rdi->second; ++lb) {
	result.push_back(lb);
      }
    }
//     std::sort (result.begin(), result.end());
//     result.erase (std::unique(result.begin(), result.end()), result.end());
  }
  return result;
}
