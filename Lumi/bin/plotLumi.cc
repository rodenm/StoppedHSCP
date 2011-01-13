#include <stdlib.h>
#include <math.h>
#include <iostream>
#include "StoppedHSCP/Lumi/interface/JsonFileReader.h"
#include "StoppedHSCP/Lumi/interface/LumiDBReader.h"
#include "TFile.h"
#include "TDatime.h"
#include "TH1F.h"


using namespace std;
using namespace shscp;

int main (int argc, const char* argv[]) {
  const double ORBITTIME = BXINORBIT/40.08e6;
  const double LSTIME = ORBITTIME * double(0x40000);
  JsonFileReader jfr ("GoodRuns_2010AB.json");
  TFile file ("plotLumi.root", "RECREATE");
  TDatime startHistTime (2010, 03, 25, 12, 00, 00);
  time_t startHistUTime = startHistTime.Convert();
  TDatime endHistTime (2010, 11, 15, 12, 00, 00);
  time_t totalSeconds = endHistTime.Convert()-startHistTime.Convert();

  TH1F hLumiScan ("hLumiScan","",0.1*totalSeconds/LSTIME, 0, totalSeconds);
  hLumiScan.GetXaxis()->SetTimeDisplay(1);
  hLumiScan.GetXaxis()->SetTimeOffset(startHistTime.Convert());
  hLumiScan.SetStats(kFALSE);

  TH1F hLumiScanGood ("hLumiScanGood","",0.1*totalSeconds/LSTIME, 0, totalSeconds);
  hLumiScanGood.GetXaxis()->SetTimeDisplay(1);
  hLumiScanGood.GetXaxis()->SetTimeOffset(startHistTime.Convert());
  hLumiScanGood.SetStats(kFALSE);

  TH1F hLumiScanData ("hLumiScanData","",totalSeconds/LSTIME, 0, totalSeconds);
  hLumiScanData.GetXaxis()->SetTimeDisplay(1);
  hLumiScanData.GetXaxis()->SetTimeOffset(startHistTime.Convert());
  hLumiScanData.SetStats(kFALSE);

  TH1F hLumiScanGoodData ("hLumiScanGoodData","",totalSeconds/LSTIME, 0, totalSeconds);
  hLumiScanGoodData.GetXaxis()->SetTimeDisplay(1);
  hLumiScanGoodData.GetXaxis()->SetTimeOffset(startHistTime.Convert());
  hLumiScanGoodData.SetStats(kFALSE);

  TH1F hLastSection ("hLastSection","hLastSection",1000, 0, 1000);
  TH1F hLastSectionOffset ("hLastSectionOffset","hLastSectionOffset",1000, 0, 1000);
 
  LumiDBReader reader;
  vector<int> fills = reader.getAllFills ();
  for (unsigned ifill = 0; ifill < fills.size(); ++ifill) {
    int fill = fills[ifill];
    long fillSecondsMissing = 0;
    //    if (fill < 1375 || fill > 1427) continue; 
    //if (fill < 1393 || fill > 1393) continue; 
    cout << "Processing fill " << fill << endl;
    vector<int> runs = reader.getAllRuns(fill);
    int previousRun = 0;
    time_t endPreviousRun = 0;
    for (unsigned irun = 0; irun < runs.size(); ++irun) {
      int run = runs[irun];
      RunSummaryRecord runSummary;
      reader.getRunSummary (run, &runSummary);
      time_t runStartTime = runSummary.startTime;
      if (runStartTime < startHistUTime) continue;
      cout << "Processing run " << run << " start time: " << runStartTime 
	   << '(' << time_t(runStartTime-startHistUTime) << " offset)"
	   << " stop time: " << runSummary.stopTime
	   << endl;
      // offset from previous run
      if (run == previousRun+1) {
	hLastSectionOffset.Fill (long(runStartTime)-long(endPreviousRun));
	cout << "offset to previous run end: " << long(runStartTime)-long(endPreviousRun) 
	     << "seconds. LUMI information is missing?" << endl;
	fillSecondsMissing += long(runStartTime)-long(endPreviousRun);
      }
      else if (previousRun > 0) {
	cout << "missing LUMI information between runs " << previousRun << " and " << run 
	     << ", " << long(runStartTime)-long(endPreviousRun) << " seconds are missing in " 
	     << run-1-previousRun << " run(s)?" << endl;
	fillSecondsMissing += long(runStartTime)-long(endPreviousRun);
      }
      vector<int> sections = reader.getAllSections(run);
      if (sections.size() <= 0) {
	cout << "CAUTION: no runsections in run " << run << endl;
      }
      for (unsigned isection = 0; isection < sections.size(); ++isection) {
	int section = sections[isection];
	LumiSummaryRecord lumiData;
	if (reader.getSummary(run, section, &lumiData)) {
	  time_t sectionStartTime = runStartTime + time_t(lumiData.startOrbit*ORBITTIME);
	  time_t sectionStopTime = runStartTime + time_t((lumiData.startOrbit+lumiData.numOrbits)*ORBITTIME);
	  time_t sectionRelativeTime = sectionStartTime - startHistUTime;
	  double sectionLength = lumiData.numOrbits*ORBITTIME;
	  double instLumi = lumiData.instLumi * 1406 / 60.21 / 1.e-30 / LSTIME; // s^-1*cm^-2
	  double lumi = lumiData.instLumi*sectionLength;
	  hLumiScan.Fill (sectionRelativeTime, 0.1 * instLumi);
	  if (jfr.goodLB (run, section)) hLumiScanGood.Fill (sectionRelativeTime, 0.1 * instLumi);
	      if (fill >= 1375 && fill <= 1427)  {
		hLumiScanData.Fill (sectionRelativeTime, instLumi);
		if (jfr.goodLB (run, section)) 	hLumiScanGoodData.Fill (sectionRelativeTime, instLumi);
	      }
// 	  cout << "section/time/lumi: " << section << '/' << sectionRelativeTime << '/' 
// 	       << lumiData.startOrbit << '/' << sectionStartTime << "/" << sectionStopTime << ' '  
// 	       << lumi << endl;
	  if (isection == sections.size()-1) { // last section
	    // cache run data
	    previousRun = run;
	    endPreviousRun = runStartTime + time_t((lumiData.startOrbit+lumiData.numOrbits)*ORBITTIME);
	    hLastSection.Fill (lumiData.numOrbits);
	    cout << "Last section " << run << '/' << section 
		 << ": start orbit/#orbits/endtime offset/end time "
		 << lumiData.startOrbit << '/' << lumiData.numOrbits << '/' 
		 << time_t((lumiData.startOrbit+lumiData.numOrbits)*ORBITTIME) << '/'
		 << endPreviousRun
		 << endl;
	  }
	}
	else {
	  cout << "Can not get info about run/section " << run << '/' << section << endl; 
	}
      }
    }
    cout << "Total LUMI seconds missed in fill " << fill << ": " << fillSecondsMissing << endl;
  }
  hLumiScan.Write();
  hLumiScanData.Write();
  hLumiScanGood.Write();
  hLumiScanGoodData.Write();
  hLastSectionOffset.Write();
  hLastSection.Write();
  file.Close();
}
