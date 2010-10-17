#include "StoppedHSCP/Analysis/interface/RateCalculator.h"

#include <iostream>
#include <sstream>
#include <cmath>

RateCalculator::RateCalculator (const std::string& name,
				const std::string& ifile,
				const std::string& ofile) :
  mName(name),
  BasicAnalyser(ifile, false),
  ofile_(ofile.c_str(), "recreate")
{
  mCurrentRun = mCollector.end();
}

// RateCalculator::RateCalculator (const std::string& fName, const std::vector<int>& xCuts, const std::vector<int>& yCuts) {
//   mCurrentRun = mCollector.end();
//   mXCuts = xCuts;
//   mYCuts = yCuts;
//   mName = fName;
// }

RateCalculator::~RateCalculator() { }


void RateCalculator::addXcut (int cut) {mXCuts.push_back(cut);}
void RateCalculator::addYcut (int cut) {mYCuts.push_back(cut);}


void RateCalculator::process () {
  int run = event_->run;
  int lb = event_->lb;
  if (mCurrentRun == mCollector.end() || mCurrentRun->first != run) {
    mCurrentRun = mCollector.find (run);
    if (mCurrentRun == mCollector.end()) {
      mCurrentRun = mCollector.insert (MapRun::value_type(run, RunStats())).first;
      }
  }
  Counts& counts = mCurrentRun->second[lb];
  bool ix = true;
  for (unsigned i = 0; i < mXCuts.size(); ++i) {
    ix &= mXCuts[i] >= 0 ? cuts_.cutN(mXCuts[i]) : !cuts_.cutN(-mXCuts[i]);
  }
  bool iy = true;
  for (unsigned i = 0; i < mYCuts.size(); ++i) {
    iy &= mYCuts[i] >= 0 ? cuts_.cutN(mYCuts[i]) : !cuts_.cutN(-mYCuts[i]);
  }
  if (ix) counts.countsX += 1;
  if (iy) counts.countsY += 1;
}

std::string RateCalculator::xTitle () {
  std::ostringstream title("");
  for (unsigned i = 0; i < mXCuts.size(); ++i) {
    if (i != 0) title << '&';
    if (mXCuts[i] >= 0) title << cuts_.cutName(mXCuts[i]);
    else title << '!' << cuts_.cutName(-mXCuts[i]);
  }
  return title.str();
}

std::string RateCalculator::yTitle () {
  std::ostringstream title("");
    for (unsigned i = 0; i < mYCuts.size(); ++i) {
      if (i != 0) title << '&';
      if (mYCuts[i] >= 0) title << cuts_.cutName(mYCuts[i]);
      else title << '!' << cuts_.cutName(-mYCuts[i]);
    }
    return title.str();
}

void RateCalculator::printOut () {
  std::cout << mName << ": Summary for rates. X:" << xTitle() << " Y:" << yTitle() << std::endl;
    double sumTime = 0;
    int sumPassX = 0;
    int sumPassY = 0;
    for (MapRun::iterator irun = mCollector.begin(); irun != mCollector.end(); ++irun) {
      int run = irun->first;
      const RunStats& rs = irun->second;
      int lBlocks = 0;
      int xEntries = 0;
      int yEntries = 0;
      for (RunStats::const_iterator ilb = rs.begin(); ilb != rs.end(); ++ilb) {
	lBlocks += 1;
	xEntries += ilb->second.countsX;
	yEntries += ilb->second.countsY;
      }
      double timeAll = lBlocks*lbSeconds;
      sumTime += timeAll;
      sumPassX += xEntries;
      double xRate = double(xEntries) / timeAll;
      double dxRate = sqrt(double(xEntries)) / timeAll;
      sumPassY += yEntries;
      double yRate = double(yEntries) / timeAll;
      double dyRate = sqrt(double(yEntries)) / timeAll;
      //       cout << "run:" << run << " time:" << timeAll 
      // 	   << " X:" << xEntries << ":" << xRate << "+-" << dxRate
      // 	   << " Y:" << yEntries << ":" << yRate << "+-" << dyRate
      // 	   << endl;
    }
    std::cout << "ALL runs:" << mCollector.size() << " time:" << sumTime
	 << " X:" << sumPassX << ":" << double (sumPassX)/sumTime << "+-" << sqrt (double (sumPassX))/sumTime
	 << " Y:" << sumPassY << ":" << double (sumPassY)/sumTime << "+-" << sqrt (double (sumPassY))/sumTime
	 << std::endl;
    
}

TH1D* RateCalculator::plotByRunProjection (bool x) {
  std::vector<int> runs; 
  std::vector<double> rates;
  std::vector<double> drates;
  int allEvents = 0;
  double allTime = 0;
  for (MapRun::iterator irun = mCollector.begin(); irun != mCollector.end(); ++irun) {
    int run = irun->first;
    int events = 0;
    int lBlocks = 0;
    const RunStats& rs = irun->second;
    for (RunStats::const_iterator ilb = rs.begin(); ilb != rs.end(); ++ilb) {
      lBlocks += 1;
      events += x ? ilb->second.countsX : ilb->second.countsY;
    }
    double times = lBlocks*lbSeconds;
    allEvents += events;
    allTime += times;
    runs.push_back(run);
    rates.push_back(double (events) / times);
    drates.push_back(sqrt(double (events)) / times);
  }
  int nRuns = runs.size();
  std::string name = mName+ (x ? "_plotByRunX" : "_plotByRunY");
  std::string title = std::string ("Rate:") + (x ? xTitle() : yTitle());
  TH1D* result = new TH1D (name.c_str(), title.c_str(), nRuns+1, 0., nRuns+1);
  char label[64];
  for (int i = 0; i < nRuns; ++i) {
    sprintf (label, "%d", runs[i]);
    result->GetXaxis()->SetBinLabel (i+2, label);
    result->SetBinContent (i+2, rates[i]);
    result->SetBinError (i+2, drates[i]);
  }
  
  result->GetXaxis()->SetBinLabel (1, "ALL");
  result->SetBinContent (1, allEvents/allTime);
  result->SetBinError (1, sqrt(double(allEvents))/allTime);
  
  result->LabelsOption("v");
  result->SetMarkerStyle (20);
  result->SetMarkerSize (1);
  result->SetMinimum(0);
  result->SetMaximum(result->GetBinContent(result->GetMaximumBin())*1.1);
  result->SetStats(false);
  return result;
}

TGraphErrors* RateCalculator::plotByRun () {
  const int maxSize = 1024;
  double ratesX[maxSize];
  double dratesX[maxSize];
  double ratesY[maxSize];
  double dratesY[maxSize];
  int i = 0;
  for (MapRun::iterator irun = mCollector.begin(); irun != mCollector.end(); ++irun) {
    ratesX[i] = 0;
    ratesY[i] = 0;
    int lBlocks = 0;
    const RunStats& rs = irun->second;
    for (RunStats::const_iterator ilb = rs.begin(); ilb != rs.end(); ++ilb) {
      lBlocks += 1;
      ratesX[i] += ilb->second.countsX;
      ratesY[i] += ilb->second.countsY;
    }
    dratesX[i] = sqrt(ratesX[i])/(lBlocks*lbSeconds);
    ratesX[i] /= lBlocks*lbSeconds;
    dratesY[i] = sqrt(ratesY[i])/(lBlocks*lbSeconds);
    ratesY[i] /= lBlocks*lbSeconds;
    if (++i >= maxSize) break;
  }
  std::string name = mName+"_plotByRun";
  std::string title = std::string ("Rate: ") + yTitle() + std::string (" vs ") + xTitle();
  TGraphErrors* result = new TGraphErrors (i, ratesX, ratesY, dratesX, dratesY);
  result->SetNameTitle (name.c_str(), title.c_str());
  //    result->GetXaxis()->SetTitle (xTitle().c_str());
  result->GetXaxis()->SetLimits (0, result->GetXaxis()->GetXmax());
  //    result->GetYaxis()->SetTitle (yTitle().c_str());
  result->SetMinimum(0);
  return result;
}

TGraphErrors* RateCalculator::plotByPeriod (int fPeriods) {
  int allLS = 0;
  for (MapRun::iterator irun = mCollector.begin(); irun != mCollector.end(); ++irun) {
    allLS += irun->second.size();
  }
  const int maxSize = 1024;
  double ratesX[maxSize];
  double dratesX[maxSize];
  double ratesY[maxSize];
  double dratesY[maxSize];
  int i = 0;
  int processedLS = 0;
  int countedLS = 0;
  int countedX = 0;
  int countedY = 0;
  for (MapRun::iterator irun = mCollector.begin(); irun != mCollector.end(); ++irun) {
    const RunStats& rs = irun->second;
    for (RunStats::const_iterator ilb = rs.begin(); ilb != rs.end(); ++ilb) {
      countedLS += 1;
      processedLS += 1;
      countedX += ilb->second.countsX;
      countedY += ilb->second.countsY;
      if (processedLS > double (allLS) * (i+1) / double (fPeriods) || processedLS == allLS) {
	double allTime = countedLS * lbSeconds;
	ratesX[i] = double (countedX) / allTime;
	dratesX[i] = sqrt(double (countedX)) / allTime;
	ratesY[i] = double (countedY) / allTime;
	dratesY[i] = sqrt(double (countedY)) / allTime;
	// cout << "mName->" << i<<':'<<countedLS<<'/'<<countedX<<'/'<<countedY<<' '<<ratesX[i]<<'/'<<ratesY[i]<<endl;
	countedLS = countedX = countedY = 0;
	++i;
      }
    }
  }
  std::string name = mName+"_plotByPeriod";
  std::string title = std::string ("Rate: ") + yTitle() + std::string (" vs ") + xTitle();
  TGraphErrors* result = new TGraphErrors (i, ratesX, ratesY, dratesX, dratesY);
  result->SetNameTitle (name.c_str(), title.c_str());
  //    result->GetXaxis()->SetTitle (xTitle().c_str());
  result->GetXaxis()->SetLimits (0, result->GetXaxis()->GetXmax());
  //    result->GetYaxis()->SetTitle (yTitle().c_str());
  result->SetMinimum(0);
  return result;
}


void RateCalculator::loop() {

  reset();

  // run loop
  for (unsigned long i=0; i<nEvents_; ++i, nextEvent()) {
    
    if (i%100000==0) {
      std::cout << "Processing " << i << "th event" << std::endl;
    }
    
    process();

  }


}
