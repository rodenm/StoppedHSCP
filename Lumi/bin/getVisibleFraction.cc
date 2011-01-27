#include <stdlib.h>
#include <limits>
#include <cmath>
#include <iostream>
#include <map>
#include "StoppedHSCP/Lumi/interface/JsonFileReader.h"
#include "StoppedHSCP/Lumi/interface/LumiData.h"
#include "StoppedHSCP/Lumi/interface/LumiDBReader.h"

using namespace std;
using namespace shscp;

map<int, map<int,double> > lumiIntegral (const shscp::AllLumiData& ald, 
					    double tau) {
  map<int, map<int,double> > result;
  double sum = 1e-100; // place holder
  time_t previousTime = 0;
  double previousSinh = 0;
  double ignoredLumi = 0;
  int counter = 0;
  AllLumiData::LumiData::const_iterator irun = ald.data().begin();
  for (; irun != ald.data().end(); ++irun) {
    const AllLumiData::LumiRun& run = irun->second;
    AllLumiData::LumiRun::const_iterator isec = run.begin();
    for (; isec != run.end(); ++isec) {
      const DeliveredLumi& section = isec->second;
      double lumi = section.integratedLumi;
      const double lumiThreshold = 1e-3; // 10^-3 /mkb
      if (lumi < lumiThreshold) {
	ignoredLumi += lumi;
	lumi = 0;
      }
      time_t lsTime = section.time();
      if (lsTime < previousTime) {
	cout << "lumiIntegral-> section out of order: "<<section.run<<'/'<<section.section
	     <<' '<<section.begin<<'/'<<lsTime<<'/'<<previousTime<<" break execution"<<endl;
	ignoredLumi += section.integratedLumi;
	return result;
	continue;
      }
      double sinh0 = sinh (0.5*double(section.dtime())/tau);
      if (previousTime > 0) {
	double previousSum = sum;
	sum *= exp(-double (lsTime - previousTime)/tau)/previousSinh*sinh0;
	if (sum!=sum || sum==numeric_limits<double>::infinity() || sum==-numeric_limits<double>::infinity()) {
	  cout<<"lumiIntegral->"<<section.run<<'/'<<section.section<<' '<<previousSum<<' '<<lsTime<<'/'<<previousTime<<'/'<<exp(-double (lsTime - previousTime)/tau)<<'/'<<previousSinh<<'/'<<sinh0<<'/'<<sum<<endl;
	  return result;
	}
      }
      result[section.run][section.section] = sum;

      double thisLumi = lumi*4.*tau*sinh0*sinh0;
      sum += thisLumi;
      previousTime = lsTime;
      previousSinh = sinh0;
      ++counter;
    }
  }
  // cout << "lumiIntegral-> Ignored lumi: " << ignoredLumi*1e-3 << " 1/mb" << endl;
  return result;
}

double lumiEffectPrevious (const shscp::DeliveredLumi& dlFrom, 
			   const shscp::DeliveredLumi& dlTo, 
			   double tau) {
  if (dlFrom.run > dlTo.run) return 0;
  if (dlFrom.run == dlTo.run && dlFrom.section >= dlTo.section) return 0;
  
  double lsTimeFrom = dlFrom.time();
  double lsDTimeFrom = dlFrom.dtime();
  double lsTimeTo = dlTo.time();
  double lsDTimeTo = dlTo.dtime();
  return dlFrom.integratedLumi*4.*tau*exp(-(lsTimeTo-lsTimeFrom)/tau)
    *sinh(lsDTimeFrom/2/tau)*sinh(lsDTimeTo/2/tau);
}

double lumiSelfEffect (const shscp::DeliveredLumi& dl, double tau) {
  double lsDTime = dl.end - dl.begin;
  return dl.integratedLumi*(lsDTime-tau*(1.-exp(-lsDTime/tau)));
}


double lumiEffect (const shscp::DeliveredLumi& dlFrom, 
		   const shscp::DeliveredLumi& dlTo, 
		   double tau) {
  return (dlFrom.run == dlTo.run && dlFrom.section == dlTo.section) ?
    lumiSelfEffect (dlTo, tau) :
    lumiEffectPrevious (dlFrom, dlTo, tau);
}

time_t dataTime (const JsonFileReader& jfr, AllLumiData& ald) {
  int lsAdded = 0;
  time_t result = 0;
  std::vector<int> runs = jfr.allRuns();
  for (size_t imr = 0; imr < runs.size(); ++imr) {
    int run = runs[imr];
    std::vector<int> sections = jfr.allLumiBlocks (run);
    for (size_t ims = 0; ims < sections.size(); ++ims) {
      int section = sections[ims];
      const shscp::DeliveredLumi* lumiData = ald.getLumiData (run, section);
      if (lumiData) {
	result += lumiData->dtime();
      }
      else {
	if (ald.data().find (run) !=  ald.data().end()) {
	  // cout << "dataTime-> adding empty LUMI run/section " << run << '/' << section << endl;
	  ald.AddSection (run, section);
	  result += ald.getLumiData (run, section)->dtime();
	  lsAdded++;
	}
	else {
	  cerr << "dataTime-> missing RUN " << run << endl;
	  result += LSTIME;
	}
      }
    }
  }
  if (lsAdded > 0) cout << "dataTime-> added " <<  lsAdded << " empty LUMI sections" << endl;
  return result;
}

void getVisibleFraction (double tau, const JsonFileReader& jfr, const AllLumiData& ald, 
			 double* fractionTotal, double* fractionLimited) {
  time_t timeTolerance (floor (tau*20+0.5));
  *fractionTotal = *fractionLimited = 0;
  // loop over measured sections
  std::vector<int> measuredRuns = jfr.allRuns();
  for (size_t imr = 0; imr < measuredRuns.size(); ++imr) {
    int measuredRun = measuredRuns[imr];
    double runLumiContribution = 0;
    double runLumiContributionLimited = 0;
    std::vector<int> measuredSections = jfr.allLumiBlocks (measuredRun);
    // cout << "processing run " <<  measuredRun << " good sections: " << measuredSections.size() << flush;
    for (size_t ims = 0; ims < measuredSections.size(); ++ims) {
      int measuredSection = measuredSections[ims];
      const shscp::DeliveredLumi* lumiDataTo = ald.getLumiData (measuredRun, measuredSection);
      if (!lumiDataTo) {
	// cerr << "missing information for run/section " << measuredRun << '/' <<  measuredSection << endl;
	continue;
      }
      time_t sectionBegin = lumiDataTo->begin;
      time_t sectionEnd = lumiDataTo->end;
      // loop over LUMI sections
      vector<int> fills = ald.getAllFills ();
      for (unsigned ifill = 0; ifill < fills.size(); ++ifill) {
	int fill = fills[ifill];
	time_t fillBegin, fillEnd;
	ald.fillTime (fill, &fillBegin, &fillEnd);
	if (fillEnd + timeTolerance < sectionBegin) continue;
	if (fillBegin > sectionEnd) break;
	vector<int> runs = ald.getAllRuns(fill);
	for (unsigned irun = 0; irun < runs.size(); ++irun) {
	  int run = runs[irun];
	  time_t runBegin, runEnd;
	  ald.runTime (run, &runBegin, &runEnd);
	  if (runEnd + timeTolerance < sectionBegin) continue;
	  if (runBegin > sectionEnd) break;
	  vector<int> sections = ald.getAllSections(run);
	  for (unsigned isection = 0; isection < sections.size(); ++isection) {
	    int section = sections[isection];
	    const shscp::DeliveredLumi* lumiDataFrom = ald.getLumiData (run, section);
	    if (lumiDataFrom) {
	      double contribution = lumiEffect (*lumiDataFrom, *lumiDataTo, tau);
	      *fractionTotal += contribution;
	      runLumiContribution += contribution;
	      if (jfr.goodLB (run, section)) {
		runLumiContributionLimited += contribution;
		*fractionLimited += contribution;
	      }
	      //if (section == 1) cout << "contributing " << run << '/' << section << "  " << contribution << endl;
	    }
	  }
	}
      }
    }
//     cout << "  total contribution: " <<  runLumiContribution << '/' << runLumiContributionLimited 
//     	 << " " << runLumiContribution-runLumiContributionLimited << endl;
  }
}

void getVisibleFraction2 (double tau, const JsonFileReader& jfr, const AllLumiData& ald, 
			 double* fractionTotal) {
  *fractionTotal = 0;
  map<int, map<int,double> > integralLumi = lumiIntegral (ald, tau);
  // loop over measured sections
  std::vector<int> measuredRuns = jfr.allRuns();
  for (size_t imr = 0; imr < measuredRuns.size(); ++imr) {
    int measuredRun = measuredRuns[imr];
    double runLumiContribution = 0;
    std::vector<int> measuredSections = jfr.allLumiBlocks (measuredRun);
    // cout << "processing run " <<  measuredRun << " good sections: " << measuredSections.size() << flush;
    for (size_t ims = 0; ims < measuredSections.size(); ++ims) {
      int measuredSection = measuredSections[ims];
      const shscp::DeliveredLumi* lumiDataTo = ald.getLumiData (measuredRun, measuredSection);
      if (!lumiDataTo) {
	// cerr << "missing information for run/section " << measuredRun << '/' <<  measuredSection << endl;
	continue;
      }
      time_t sectionTime = lumiDataTo->time();
      double lumiPrevious = integralLumi[measuredRun][measuredSection];
      double contribution = lumiPrevious + lumiSelfEffect (*lumiDataTo, tau);
      //double contribution = lumiSelfEffect (*lumiDataTo, tau);
      *fractionTotal += contribution;
      runLumiContribution += contribution;
//         if (!(measuredSection % 10))
//         cout << "getVisibleFraction2-> run/section: " << measuredRun << '/' <<  measuredSection
//   	   << " lumi contributions: " << lumiPrevious << '/' << lumiSelfEffect (*lumiDataTo, tau)
//   	   << '/' << contribution << " sum: " << runLumiContribution << endl;
    }
    //    cout << "  total contribution: " <<  runLumiContribution << endl;
  }
}


int main (int argc, const char* argv[]) {
  if (argc < 1) {
    cout << "Use: " << argv[0] << " [json file (def=runs_SE_146804_148032.json)]" << std::endl;
    return -1;
  }
  std::string jfrName = (argc < 2) ? "runs_SE_146804_148032.json" : string(argv[1]);

  JsonFileReader jfr (jfrName);
  //  AllLumiData ald ("allLumiData_2.txt");
  AllLumiData ald ("allLumiData2010_extended.txt");

  double taus[] = {1, 3, 10, 30, 100, 300, 1e3, 3e3, 1e4, 3e4, 1e5, 3e5, 1e6, 3e6, 1e7, 3e7, 1e8};
  // double taus[] = {1e8};
  const int nTaus = sizeof(taus)/sizeof(double);
  double fractionTotal[nTaus];
  double fractionTotalLimited[nTaus];

  time_t measurementTime = dataTime(jfr, ald);
  cout << "Total data sample lifetime: " << measurementTime << " seconds i.e. " 
       << double(measurementTime)*6.9e-5 << " expected bkg evens" << endl;
  
  for (int i = 0; i < nTaus; ++i) {
    fractionTotal[i] = fractionTotalLimited[i] = 0;
    //    getVisibleFraction (taus[i], jfr, ald, fractionTotal+i, fractionTotalLimited+i); 
    getVisibleFraction2 (taus[i], jfr, ald, fractionTotal+i); 
    cout << "processed tau " << taus[i] << ": " << fractionTotal[i] << '/' << fractionTotalLimited[i] << endl;
  }

  cout << "tau ";  for (int i = 0; i < nTaus; ++i) cout << taus[i] << ", "; cout << endl;
  cout << "fractionTotal ";  for (int i = 0; i < nTaus; ++i) cout << fractionTotal[i] << ", "; cout << endl;
  cout << "fractionTotalLimited ";  for (int i = 0; i < nTaus; ++i) cout << fractionTotalLimited[i] << ", "; cout << endl;
  return 0;
}

