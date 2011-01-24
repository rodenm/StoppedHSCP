#include <stdlib.h>
#include <math.h>
#include <iostream>
#include "StoppedHSCP/Lumi/interface/LumiDBReader.h"
#include "StoppedHSCP/Lumi/interface/JsonFileReader.h"
#include "StoppedHSCP/Lumi/interface/LumiData.h"
#include "TFile.h"
#include "TDatime.h"
#include "TH1F.h"


using namespace std;
using namespace shscp;

int main (int argc, const char* argv[]) {
  const double ORBITTIME = BXINORBIT/40.08e6;
  const double LSTIME = ORBITTIME * double(0x40000);

  JsonFileReader  jfr ("GoodRuns_2010AB.json");
  AllLumiData ald ("allLumiData2.txt");
  //  AllLumiData ald ("allLumiData_LHC.txt");

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

  vector<int> fills = ald.getAllFills ();
  for (unsigned ifill = 0; ifill < fills.size(); ++ifill) {
    int fill = fills[ifill];
    // cout << "Processing fill " << fill << endl;
    vector<int> runs = ald.getAllRuns(fill);
    for (unsigned irun = 0; irun < runs.size(); ++irun) {
      int run = runs[irun];
      vector<int> sections = ald.getAllSections(run);
      if (sections.size() <= 0) {
	cout << "CAUTION: no runsections in run " << run << endl;
      }
      for (unsigned isection = 0; isection < sections.size(); ++isection) {
	int section = sections[isection];
	const DeliveredLumi* lumiData = ald.getLumiData (run, section);
	if (lumiData) {
	  time_t sectionStartTime = lumiData->begin;
	  time_t sectionStopTime = lumiData->end;
	  time_t sectionRelativeTime = sectionStartTime - startHistUTime;
	  double sectionLength = sectionStopTime - sectionStartTime;
	  int  nOrbits = sectionLength / ORBITTIME;
	  double lumi = lumiData->integratedLumi / nOrbits * 1406 / 60.21 / 1.e-30 / LSTIME; // cm^-2
	  double instLumi = lumi / sectionLength; // s^-1*cm^-2
	  hLumiScan.Fill (sectionRelativeTime, 0.1 * instLumi);
	  cout << "fill-> " << run << '/' << section
	       << "  " << hLumiScan.GetXaxis()->FindBin(sectionRelativeTime)
	       << "/" << sectionRelativeTime
	       << " " << instLumi << '/' << lumi << endl;
	  if (jfr.goodLB (run, section)) hLumiScanGood.Fill (sectionRelativeTime, 0.1 * instLumi);
	  if (fill >= 1375 && fill <= 1427)  {
	    hLumiScanData.Fill (sectionRelativeTime, instLumi);
	    if (jfr.goodLB (run, section)) 	hLumiScanGoodData.Fill (sectionRelativeTime, instLumi);
// 	    cout << "run/section/time/lumi: " << run << '/' << section << '/' 
// 		 << sectionRelativeTime << '/' 
// 		 << sectionStartTime << "/" << sectionStopTime << ' '  
// 		 << instLumi << '/' << lumi << endl;
	  }
	}
	else {
	  cout << "Can not get info about run/section " << run << '/' << section << endl; 
	}
      }
    }
  }
  hLumiScan.Write();
  hLumiScanData.Write();
  hLumiScanGood.Write();
  hLumiScanGoodData.Write();
  file.Close();
}
