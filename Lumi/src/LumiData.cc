#include <iostream>
#include <fstream>
#include <sstream>
#include <set>

#include "StoppedHSCP/Lumi/interface/LumiData.h"
#include "StoppedHSCP/Lumi/interface/LumiDBReader.h"

using namespace std;
using namespace oracle::occi;

namespace shscp {

  AllLumiData::AllLumiData () {}

  AllLumiData::AllLumiData (const std::string& fFileName) {
    ifstream input (fFileName.c_str());
    while (input) {
      string buffer;
      getline (input, buffer);
      if (buffer[0] != '#') {
	stringstream inputline (buffer);
	DeliveredLumi dl;
	long begin, end;
	inputline >> dl.fill >> dl.run >> dl.section >> begin >> end 
		  >> dl.integratedLumi  >> dl.sensitiveFraction   >> dl.status; 
	dl.begin = (time_t) begin;
	dl.end = (time_t) end;
	mData[dl.run][dl.section] = dl;
	std::vector<int>& runsOfFill = mFills[dl.fill];
	bool newRun = true;
	for (size_t i = 0; i < runsOfFill.size(); ++i) {
	  if (runsOfFill[i] == dl.run) {
	    newRun = false;
	    break;
	  }
	}
	if (newRun) runsOfFill.push_back(dl.run);
      }
    }
  }

  AllLumiData::AllLumiData (LumiDBReader& fDBReader) {
    vector<int> fills (fDBReader.getAllFills ());
    for (size_t ifill = 0; ifill < fills.size(); ++ifill) {
      int fill = fills[ifill];
      cout << "AllLumiData::AllLumiData-> Processing fill " << fill << ' ';
      vector<int> runs (fDBReader.getAllRuns (fill));
      for (size_t irun = 0; irun < runs.size(); ++irun) {
	cout << '.' << flush;
	int run = runs[irun];
	RunSummaryRecord rsr;
	fDBReader.getRunSummary (run, &rsr);
	time_t runStart = rsr.startTime;
	std::vector<LumiSummaryRecord> summaries;
	std::vector<LumiDetailsRecord> details;
	fDBReader.getRunSectionData (run, &summaries, &details);
	for (size_t isection = 0; isection < summaries.size(); ++isection) {
	  DeliveredLumi deliveredLumi;
	  deliveredLumi.sensitiveFraction = 0;
	  deliveredLumi.status = 0;
	  const LumiSummaryRecord& lsr = summaries[isection];
	  const LumiDetailsRecord& ldr = details[isection];
	  int section = lsr.sectionLUMI;
	  // check lumi fraction
	  double maxLumi = ldr.lumi[0];
	  for (int i = 1; i < BXINORBIT; ++i) if (ldr.lumi[i] > maxLumi) maxLumi = ldr.lumi[i];
	  for (int i = 1; i < BXINORBIT; ++i) {
	    if (ldr.lumi[i] > 0.01*maxLumi) {
	      deliveredLumi.sensitiveFraction += 1.;
	      if (ldr.lumi[i] < 0.75*maxLumi) {
		deliveredLumi.status = 1;
		// 		cout << "UNDERFILLED BUNCH: fill/run/section/bx "
		// 		     << fill << '/' << run << '/' << section << '/' << i
		// 		     << " lumi: " << ldr.lumi[i] << ", max: " << maxLumi
		// 		     << endl;
	      }
	    }
	  }
	  deliveredLumi.sensitiveFraction /= BXINORBIT;
	  // section record
	  deliveredLumi.fill = fill;
	  deliveredLumi.run = run;
	  deliveredLumi.section = section;
	  deliveredLumi.begin = runStart + time_t(double (BXINORBIT*lsr.startOrbit)/LHCRATE);
	  deliveredLumi.end = deliveredLumi.begin + time_t (double (BXINORBIT*lsr.numOrbits)/LHCRATE);
	  deliveredLumi.integratedLumi = lsr.instLumi*lsr.numOrbits;
	  // fill data
	  mData[run][section] = deliveredLumi;
	  std::vector<int>& runsOfFill = mFills[fill];
	  bool newRun = true;
	  for (size_t i = 0; i < runsOfFill.size(); ++i) {
	    if (runsOfFill[i] == run) {
	      newRun = false;
	      break;
	    }
	  }
	  if (newRun) runsOfFill.push_back(run);
	}
      }
      cout << endl;
    }
  }

  bool AllLumiData::dumpToFile (const std::string& fFileName) const {
    ofstream out (fFileName.c_str());
    LumiData::const_iterator irun = mData.begin();
    for (; irun != mData.end(); ++irun) {
      int run = irun->first;
      const LumiRun& lumiRun = irun->second;
      LumiRun::const_iterator isec = lumiRun.begin();
      for (; isec != lumiRun.end(); ++isec) {
	int section = isec->first;
	const DeliveredLumi& deliveredLumi = isec->second;
	out << deliveredLumi.fill << ' ' << deliveredLumi.run << ' ' << deliveredLumi.section 
	    << ' ' << (long)deliveredLumi.begin << ' ' << (long)deliveredLumi.end 
	    << ' ' << deliveredLumi.integratedLumi << ' ' << deliveredLumi.sensitiveFraction
	    << ' ' << deliveredLumi.status
	    << endl;
      }
    }
    return true;
  }

  std::vector<int> AllLumiData::getAllSections (int fRun) const {
    vector<int> result;
    LumiData::const_iterator iRun = mData.find (fRun);
    if (iRun != mData.end()) {
      const LumiRun& run = iRun->second;
      LumiRun::const_iterator iSection = run.begin();
      for (; iSection != run.end(); ++iSection) {
	result.push_back (iSection->first);
      }
    }
    return result;
  }

  std::vector<int> AllLumiData::getAllRuns (int fFill) const {
    vector<int> result;
    LumiData::const_iterator iRun = mData.begin();
    for (; iRun != mData.end(); ++iRun) {
      result.push_back (iRun->first);
    }
    return result;
  }

  std::vector<int> AllLumiData::getAllFills () {
    set<int> fills;
    LumiData::const_iterator iRun = mData.begin();
    for (; iRun != mData.end(); ++iRun) {
      const LumiRun& run = iRun->second;
      if (!run.empty()) fills.insert (run.begin()->second.fill);
    }
    
    vector<int> result (fills.size());
    copy (fills.begin(), fills.end(), result.begin());
    return result;
  }

  const DeliveredLumi* AllLumiData::getLumiData (int fRun, int fSection) const {
    LumiData::const_iterator iRun = mData.find (fRun);
    if (iRun == mData.end()) return 0;
    const LumiRun& run = iRun->second;
    LumiRun::const_iterator iSection = run.find(fSection);
    if (iSection == run.end()) return 0;
    return &iSection->second;
  }
}
