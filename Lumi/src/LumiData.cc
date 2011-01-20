#include <cmath>
#include <iostream>
#include <fstream>
#include <sstream>
#include <set>
#include "boost/filesystem.hpp"

#include "TTimeStamp.h"

#include "StoppedHSCP/Lumi/interface/LumiData.h"
#include "StoppedHSCP/Lumi/interface/LumiDBReader.h"

using namespace std;
using namespace oracle::occi;

namespace shscp {

  AllLumiData::AllLumiData () {}

  AllLumiData::AllLumiData (const std::string& fFileName) {
    ifstream input (fFileName.c_str());
    int currentRun = 0;
    int currentLS = 0;
    time_t currentLSend = 0;
    time_t timeOffset = 0;
    while (input) {
      string buffer;
      getline (input, buffer);
      if (!buffer.empty() && buffer[0] != '#') {
	stringstream inputline (buffer);
	DeliveredLumi dl;
	long begin, end;
	inputline >> dl.fill >> dl.run >> dl.section >> begin >> end 
		  >> dl.integratedLumi  >> dl.sensitiveFraction   >> dl.status; 
	if (dl.run != currentRun) {
	  timeOffset = 0;
	  currentRun = dl.run;
	}
	else {
	  if (dl.section == currentLS+1) {
	    if (begin + timeOffset < currentLSend) {
	      timeOffset += currentLSend-begin;
	      cerr<<"AllLumiData-> LS reset: " << dl.run<<'/'<<dl.section
 		  <<'/'<<begin
 		  <<" previous LS end: "<<currentLSend
 		  <<" set time offset: "<<timeOffset<< endl;
	    }
	  }
	}
	dl.begin = (time_t) begin + timeOffset;
	dl.end = (time_t) end + timeOffset;

	currentLS = dl.section;
	currentLSend = dl.end;

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

  AllLumiData::AllLumiData (LumiDBReader& fDBReader, bool fDetails) {
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
	fDBReader.getRunSectionData (run, &summaries, fDetails ? &details : 0);
	for (size_t isection = 0; isection < summaries.size(); ++isection) {
	  DeliveredLumi deliveredLumi;
	  deliveredLumi.sensitiveFraction = 0;
	  deliveredLumi.status = 0;
	  const LumiSummaryRecord& lsr = summaries[isection];
	  int section = lsr.sectionLUMI;
	  if (fDetails) {
	    const LumiDetailsRecord& ldr = details[isection];
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
	  }
	  deliveredLumi.sensitiveFraction /= BXINORBIT;
	  // section record
	  deliveredLumi.fill = fill;
	  deliveredLumi.run = run;
	  deliveredLumi.section = section;
	  deliveredLumi.begin = runStart + time_t(BXINORBIT*double (lsr.startOrbit)/LHCRATE);
	  deliveredLumi.end = runStart + time_t (BXINORBIT*double(lsr.startOrbit+lsr.numOrbits)/LHCRATE);
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
  
  AllLumiData::AllLumiData (LumiDBReader& fDBReader, const std::string& fLHCLumiDir) {
    // first get all LHC files fills and BXs
    TTimeStamp beginOfAgeStamp (2010, 01, 01, 0, 0, 0, 0, kTRUE, -1*60*60);
    time_t beginOfAge = beginOfAgeStamp.GetSec();
    typedef map<int, vector<pair<int, string> > > LHCFiles;
    LHCFiles lhcFiles;
    namespace fs = boost::filesystem;
    fs::path dir (fLHCLumiDir);
    if (!fs::exists(dir) || !fs::is_directory(dir)) {
      cerr << "AllLumiData-> Can't open directory " << fLHCLumiDir << endl;
      return;
    }
    for (fs::directory_iterator dir_itr(dir); dir_itr != fs::directory_iterator(); ++dir_itr) {
      string filename = dir_itr->path().filename();
      // parse file name
      string::size_type pos1 = filename.find('_');
      if (pos1 == string::npos) continue;
      string::size_type pos2 = filename.find('_', ++pos1);
      if (pos2 == string::npos) continue;
      string::size_type pos3 = filename.find('_', ++pos2);
      if (pos3 == string::npos) continue;
      ++pos3;
      if (filename.substr (pos1, pos2-pos1) == "lumi_" && filename.substr (pos3) == "CMS.txt") {
	int fill = atoi (filename.substr (0, pos1-1).c_str());
	if (fill <=0) continue;
	int bx = atoi (filename.substr (pos2, pos3-pos2-1).c_str());
	if (bx <= 0) continue;
	lhcFiles[fill].push_back(pair<int,string> (bx,dir_itr->path().string()));
      }
    }
    double allMissingLumi = 0;
    double allLumi = 0;
    // process fill by fill
    vector<int> allFills = fDBReader.getAllFills ();
    int lastRunPreviousFill = 0;
    for (size_t iFill = 0; iFill < allFills.size(); ++iFill) {
      int fill = allFills[iFill];
      //      cout << "AllLumiData-> processing fill " << fill << endl;
      // get all runs of the fill
      map<time_t, int> beginRuns;
      vector<int> allRuns = fDBReader.getAllRuns (fill);
      double lumiInFill = 0;
      for (size_t iRun = 0; iRun < allRuns.size(); ++iRun) {
	RunSummaryRecord rsr;
	fDBReader.getRunSummary (allRuns[iRun], &rsr);
	beginRuns[rsr.startTime] = allRuns[iRun];
	std::vector<LumiSummaryRecord> lsr;
	fDBReader.getRunSectionData (allRuns[iRun], &lsr, 0);
	for (size_t i = 0; i < lsr.size(); ++i) lumiInFill += lsr[i].instLumi*LSTIME;	  
      }
      LHCFiles::const_iterator lhcData = lhcFiles.find (fill);
      allLumi += lumiInFill;
      if (lhcData == lhcFiles.end()) {
	// estimate missing LUMI
	allMissingLumi += lumiInFill;
	cerr << "AllLumiData-> No fill in LHC data: " << fill << " missing LUMI: " << lumiInFill << endl;
	continue;
      }
      // get all data from LHC files
      map <time_t, double> lhcLumis;
      vector<pair<int, string> > fillFiles = lhcData->second;
      for (size_t iBx = 0; iBx < fillFiles.size(); ++iBx) {
	const std::string& lhcFile = fillFiles[iBx].second;
	//	cout << "AllLumiData-> processing LHC file " << lhcFile << endl;
	ifstream inFile (lhcFile.c_str());
	while (inFile) {
	  int i1, i2;
	  time_t timeStamp0;
	  double lumi, d1, d2, d3;
	  inFile >> i1 >> i2 >> timeStamp0 >> lumi >> d1 >> d2 >> d3;
	  if (timeStamp0 < 7500000) continue;
	  time_t timeStamp = timeStamp0 + beginOfAge; // UTC
	  if (timeStamp < beginRuns.begin()->first) { //add artificial run
	    int extraRun = beginRuns.begin()->second - 1;
	    if (extraRun > lastRunPreviousFill) {
	      beginRuns[timeStamp] = extraRun;
	      cout << "added artificial run " << extraRun << " with timestamp " << timeStamp << " to fill " << fill << " timestamp " << timeStamp0 << '/' << lhcFile << endl;
	    }
	    else {
	      cerr << "AllLumiData-> Can not add artificial run " << extraRun 
		   << " to fill " << fill << " the run exists in previous fill" << endl; 
	    }
	  }
	  map<time_t, int>::iterator iRun = beginRuns.upper_bound (timeStamp);
	  if (iRun != beginRuns.begin()) {
	    --iRun;
	    time_t beginRun = iRun->first;
	    int run = iRun->second;
	    if (mData.find (run) == mData.end()) mFills[fill].push_back(run);
	    LumiRun& lumiRun = mData[run];    
	    int section = int(floor(double(timeStamp-beginRun)/LSTIME))+1;
	    time_t sectionBegin = beginRun+time_t(floor((section-1)*LSTIME));
	    time_t sectionEnd = beginRun+time_t(floor(section*LSTIME));
	    pair<LumiRun::iterator, bool> isec = lumiRun.insert (pair<int, DeliveredLumi> (section, DeliveredLumi()));
	    DeliveredLumi& dl = isec.first->second;
	    if (isec.second) { // new section
	      dl.fill = fill;
	      dl.run = run;
	      dl.section = section;
	      dl.begin = sectionBegin;
	      dl.end = sectionEnd;
	      dl.integratedLumi = lumi*LSTIME;
	      dl.sensitiveFraction = 1.;
	      dl.status = 1;
	    }
	    else {
	      if (dl.fill != fill || dl.run != run || dl.section != section ||
		  dl.begin != sectionBegin || dl.end != sectionEnd) {
		cerr << "AllLumiData-> unmatched entry in " << lhcFile << ": "  
		     << fill<<'/'<<run<<'/'<<section<<'/'<<sectionBegin<<'/'<<sectionEnd
		     << " vs "
		     << dl.fill<<'/'<<dl.run<<'/'<<dl.section<<'/'<<dl.begin<<'/'<<dl.end
		     << endl;
	      }
	      else {
		dl.integratedLumi += lumi*LSTIME;
	      }
	    }
	    dl.sensitiveFraction -= 1./double(BXINORBIT);
	  }
	  else {
	    cerr << "AllLumiData->  Missing run for fill " << fill << " timestamp " << timeStamp0<<'/'<<timeStamp << endl; 
	  }
	}
      }
      sort (mFills[fill].begin(), mFills[fill].end());
      if (!mFills[fill].empty()) lastRunPreviousFill = mFills[fill].back();
    }
    cout << "AllLumiData->  Total LUMI missing in LHC files: " << allMissingLumi 
	 << " of total " << allLumi << " that is " << allMissingLumi/allLumi << endl;
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

  std::vector<int> AllLumiData::getAllRuns () const {
    std::vector<int> result;
    result.reserve (mData.size());
    LumiData::const_iterator iRun = mData.begin();
    for (; iRun != mData.end(); ++iRun) result.push_back (iRun->first);
    return result;
  }

  std::vector<int> AllLumiData::getAllRuns (int fFill) const {
    std::map<int,std::vector<int> >::const_iterator iFill = mFills.find (fFill);
    if (iFill != mFills.end()) return iFill->second;
    return vector<int> (0);
  }

  std::vector<int> AllLumiData::getAllFills () const {
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

  void AllLumiData::runTime (int fRun, time_t* fBegin, time_t* fEnd) const {
    LumiData::const_iterator iRun = mData.find (fRun);
    if (iRun != mData.end() && !iRun->second.empty()) {
      *fBegin = iRun->second.begin()->second.begin;
      *fEnd = iRun->second.rbegin()->second.end;
    }
    else {
      fBegin = fEnd = 0;
    }
  }

  void AllLumiData::fillTime (int fFill, time_t* fBegin, time_t* fEnd) const {
    std::vector<int> runs = getAllRuns (fFill);
    time_t dummy = 0;
    runTime (runs.front(), fBegin, &dummy);
    runTime (runs.back(), &dummy, fEnd);
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
