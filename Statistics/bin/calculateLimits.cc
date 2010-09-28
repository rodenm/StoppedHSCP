#include <iostream>
#include <fstream>
#include <math.h>
#include <vector>
#include <set>
#include <algorithm>

#include "StoppedHSCP/Statistics/interface/CL95CMSCountingExperiment.h"
#include "StoppedHSCP/Statistics/interface/CLsCountingExperiment.h"

const int BX_IN_ORBIT = 3564;
bool useCLs = false;

namespace {
  void addTrain (std::vector<int>& beam, int rfBucket, int bunchSpace, int nBunches) {
    int ibx = (rfBucket / 10) + 1;
    int step = bunchSpace / 25;
    while (--nBunches >= 0) {
      beam.push_back(ibx);
      ibx += step;
    }
  }
}

int main () {
  std::vector<int> beam1;
  std::vector<int> beam2;
  // 1000ns_50b_35_14_35
  addTrain (beam1,     1, 1000, 4);
  addTrain (beam2,     1, 1000, 4);
  addTrain (beam1,  1601, 1000, 3);
  addTrain (beam2,  1601, 1000, 3);
  addTrain (beam1,  2801, 1000, 4);
  addTrain (beam2,  2801, 1000, 4);
  addTrain (beam1,  4401, 1000, 3);
  addTrain (beam2,  4401, 1000, 3);
  addTrain (beam1,  8941, 1000, 4);
  addTrain (beam2,  6601,   25, 1);
  addTrain (beam1, 10541, 1000, 3);
  addTrain (beam2,  8911, 1000, 4);
  addTrain (beam1, 11741, 1000, 4);
  addTrain (beam2, 10511, 1000, 3);
  addTrain (beam1, 13341, 1000, 3);
  addTrain (beam2, 11741, 1000, 4);
  addTrain (beam1, 17301,   25, 1);
  addTrain (beam2, 13341, 1000, 3);
  addTrain (beam1, 17851, 1000, 4);
  addTrain (beam2, 14541, 1000, 4);
  addTrain (beam1, 19451, 1000, 3);
  addTrain (beam2, 16141, 1000, 3);
  addTrain (beam1, 20681, 1000, 4);
  addTrain (beam2, 17851, 1000, 4);
  addTrain (beam1, 22281, 1000, 3);
  addTrain (beam2, 19451, 1000, 3);
  addTrain (beam1, 23481, 1000, 4);
  addTrain (beam2, 20681, 1000, 4);
  addTrain (beam1, 25081, 1000, 3);
  addTrain (beam2, 22281, 1000, 3);

  // look for collision bunches
  std::set<int> collisionBX;
  for (unsigned i1 = 0; i1 < beam1.size(); ++i1) {
    for (unsigned i2 = 0; i2 < beam2.size(); ++i2) {
      if (beam1[i1] == beam2[i2]) {
	collisionBX.insert (beam1[i1]);
	break;
      }
    }
  }

  std::cout << "Colliding bunches: " << collisionBX.size() << " All bunches: " << beam1.size() << 'x' << beam2.size() << std::endl;

  // signal events
  int signalBX [] = {2024, 5, 705, 470, 475};
  int nSignals = sizeof(signalBX)/sizeof(int);

  // get lifetime points
  std::vector<double> bxDelays;
  int i = 0;
  for (i = 0; i < nSignals; ++i) {
    int eventDelay = 0;
    int closestBX = 0;
    std::set<int>::iterator iClosestBX = collisionBX.lower_bound (signalBX[i]);
    if (iClosestBX != collisionBX.begin()) {
      eventDelay = signalBX[i] - (*(--iClosestBX));
      closestBX = *iClosestBX;
    }
    else {
      eventDelay = signalBX[i] + BX_IN_ORBIT - (*(--collisionBX.end()));
      closestBX = *(--collisionBX.end());
    }
    std::cout << "Event " << signalBX[i] << " closest BX " << closestBX << ", delay: " << eventDelay << std::endl;
    bxDelays.push_back (double(eventDelay)*25e-9/1.256);
  }
  std::sort (bxDelays.begin(), bxDelays.end());
  for (i = 0; i < int(bxDelays.size()); ++i) {
    std::cout << "delay " << i << ": " << bxDelays[i] << std::endl;
  }

  // combine standard and event-based points
  double baseLifetimes [] = {5e-8, 1e-7, 2e-7, 1e-6, 1e-5, 1e-3, 1, 5e2, 2e3, 
			     3.6e3, 6e3, 1e4, 2e4, 3e4, 5e4, 1e5, 3e5, 1e6, 1e7};
  std::vector<std::pair<int,double> > lifetimes;
  int nObserved = 0;
  for (i = 0; i < int(sizeof(baseLifetimes)/sizeof(double)); ++i) {
    while ((nObserved < int(bxDelays.size())) && (baseLifetimes[i] >= bxDelays[nObserved])) {
      lifetimes.push_back (std::pair<int,double>  (nObserved, bxDelays[nObserved]-1e-8));
      if ((nObserved == int(bxDelays.size())-1) || (bxDelays[nObserved+1] > bxDelays[nObserved]+1e-8)) {
	lifetimes.push_back (std::pair<int,double>  (nObserved+1, bxDelays[nObserved]));
      }
      ++nObserved;
    }
    lifetimes.push_back (std::pair<int,double>  (nObserved, baseLifetimes[i]));
  }

  // background
  const double BACKGROUND = 7.85742 * BX_IN_ORBIT / (BX_IN_ORBIT-65*3); // 35+15+15=65
  const double SIGMA_BACKGROUND = 1.82404 * BX_IN_ORBIT / (BX_IN_ORBIT-65*3);

  // main loop over lifetimes
  for (i = 0; i < int(lifetimes.size()); ++i) {
    double lifetime = lifetimes[i].second;

    // calculate sensitive interval
    bool sensitiveBX[BX_IN_ORBIT];
    if (lifetime > BX_IN_ORBIT * 25e-9) for (int jBX = 0; jBX < BX_IN_ORBIT; ++jBX) sensitiveBX[jBX] = true; // all
    else {
      int iTimeWindow = int(floor(lifetime*1.256/25e-9+0.5));
      std::cout << "Time Window: " << iTimeWindow << std::endl;
      for (int jBX = 0; jBX < BX_IN_ORBIT; ++jBX) {
	sensitiveBX[jBX] = false;
	for (unsigned ib = 0; ib < beam1.size(); ++ib) {
	  int ibx = beam1[ib];
	  if (collisionBX.find(ibx) != collisionBX.end() && jBX > ibx && jBX-ibx < iTimeWindow) {
	    sensitiveBX[jBX] = true;
	    break;
	  }
	}
      }
    }
    // take out collision BXs
    for (unsigned ib = 0; ib < beam1.size(); ++ib) {
      int ibx = beam1[ib];
      if (ibx-1 >= 0)  sensitiveBX[ibx-1] = false;
      sensitiveBX[ibx] = false;
      if (ibx+1 < BX_IN_ORBIT)  sensitiveBX[ibx+1] = false;
    }
    for (unsigned ib = 0; ib < beam2.size(); ++ib) {
      int ibx = beam2[ib];
      if (ibx-1 >= 0)  sensitiveBX[ibx-1] = false;
      sensitiveBX[ibx] = false;
      if (ibx+1 < BX_IN_ORBIT)  sensitiveBX[ibx+1] = false;
    }
    int nSensitiveBX = 0;
    for (int jBX = 0; jBX < BX_IN_ORBIT; ++jBX) if (sensitiveBX[jBX]) ++nSensitiveBX;
    std::cout << "sensitive BXs: " << nSensitiveBX << std::endl;

    // data
    double expectedBackground = BACKGROUND * double (nSensitiveBX) / double (BX_IN_ORBIT);
    double sigmaBackground = SIGMA_BACKGROUND * double (nSensitiveBX) / double (BX_IN_ORBIT);
    int nObserved = lifetimes[i].first;
    std::cout << i << " lifetime=" << lifetimes[i].second << " nObserved:" << lifetimes[i].first 
	      << " Background: " << expectedBackground << "+-" << sigmaBackground
	      << " Scale: 1+-0.13"
	      << std::endl;

    // get limit
    CountingExperiment* ce = useCLs ? static_cast<CountingExperiment*> (new CLsCountingExperiment (expectedBackground, sigmaBackground, 1, 0.13)) 
      : static_cast<CountingExperiment*> (new CL95CMSCountingExperiment (expectedBackground, sigmaBackground, 1, 0.13));
    double limit = ce->cl95limit (nObserved);
    std::vector<double>  expectedLimit = ce->cl95ExpectedLimit ();
    delete ce; ce = 0;
    
    char buffer[10000];
    sprintf (buffer, "%s lifetime: %6.3e  bkg: %5.3f observed: %3i limit: %5.3f expectedmean: %5.3f rms1sigma:  %5.3f %5.3f rms2sigma: %5.3f %5.3f  expectedmed: %5.3f qtile1sigma: %5.3f %5.3f qtile2sigma: %5.3f %5.3f", 
	     useCLs ? "CLs" : "CL95CMS",
	     lifetime, expectedBackground, nObserved, limit,
	     expectedLimit[5], expectedLimit[6], expectedLimit[7], expectedLimit[8], expectedLimit[9], 
	     expectedLimit[0], expectedLimit[1], expectedLimit[2], expectedLimit[3], expectedLimit[4]); 
    std::ofstream outdata ("lifetimePoint_out.txt", std::ios_base::app);
    outdata << buffer << std::endl;
    outdata.close();

  }

  
  return 0;
}
