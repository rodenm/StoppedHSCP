#include <iostream>
#include <fstream>
#include <math.h>
#include <vector>
#include <set>
#include <algorithm>

#include "StoppedHSCP/Statistics/interface/CL95CMSCountingExperiment.h"
#include "StoppedHSCP/Statistics/interface/CLsCountingExperiment.h"

const int BX_IN_ORBIT = 3564;
const double BX_TIME = 25e-9;
bool useCLs = true;

using namespace std;

namespace {

  class BeamStructure {
  public:
    BeamStructure ();
    void addLumiBx (int beam, int bx);
    void addTrain (int beam, int rfBucket, int bunchSpace, int nBunches);
    void fillCache ();
    bool isSensitive (int bx) {fillCache (); return sensitiveBX.find(bx) != sensitiveBX.end();}
    bool isLumi (int bx) {fillCache (); return lumiBX.find(bx) != lumiBX.end();}
    vector<int> allLumiBX ();
    int closestLumiOffset (int bx);
    double getLumiFraction (int bx, double lifetime);
    double getLumiEfficiency (double lifetime);
    double getSensitiveFraction (double lifetime);
  private:
    vector<int> beam1;
    vector<int> beam2;
    set<int> sensitiveBX;
    set<int> lumiBX;
    bool cacheFilled;
  };

  BeamStructure::BeamStructure () 
    : cacheFilled (false)
  {}

  void BeamStructure::addLumiBx (int beam, int bx) {
    vector<int>* aBeam = (beam == 1) ? &beam1 : ((beam == 2) ? &beam2 : 0);
    if (!aBeam) {
      cout << "BeamStructure::addLumiBx-> wrong beam # " << beam << endl;
      return;
   }
    aBeam->push_back(bx);
    cacheFilled = false; 
  }


  void BeamStructure::addTrain (int beam, int rfBucket, int bunchSpace, int nBunches) {
    int ibx = (rfBucket / 10) + 1;
    int step = bunchSpace / 25;
    while (--nBunches >= 0) {
      addLumiBx (beam, ibx);
      ibx += step;
    }
  }
  
  void BeamStructure::fillCache () {
    if (cacheFilled) return;
    // look for collision bunches
    for (unsigned i1 = 0; i1 < beam1.size(); ++i1) {
      for (unsigned i2 = 0; i2 < beam2.size(); ++i2) {
	if (beam1[i1] == beam2[i2]) {
	  lumiBX.insert (beam1[i1]);
	  break;
	}
      }
    }
    vector<bool> maskedBX (BX_IN_ORBIT, false);
    for (unsigned i1 = 0; i1 < beam1.size(); ++i1) {
      int bx = beam1[i1];
      maskedBX [bx == 0 ? BX_IN_ORBIT-1 : bx-1] = true; 
      maskedBX [bx] = true; 
      maskedBX [bx+1 == BX_IN_ORBIT ? 0 : bx+1] = true; 
    }
    for (unsigned i2 = 0; i2 < beam2.size(); ++i2) {
      int bx = beam2[i2];
      maskedBX [bx == 0 ? BX_IN_ORBIT-1 : bx-1] = true; 
      maskedBX [bx] = true; 
      maskedBX [bx+1 == BX_IN_ORBIT ? 0 : bx+1] = true; 
    }
    for (int ibx = 0; ibx < BX_IN_ORBIT; ++ibx) {
      if (!maskedBX[ibx]) sensitiveBX.insert(ibx);
    }
    cacheFilled = true;
    cout << "BeamStructure::fillCache-> colliding bunches: " << lumiBX.size() 
	 << " masked bunches: " << BX_IN_ORBIT-sensitiveBX.size()
	 << " all bunches: " << beam1.size() << 'x' << beam2.size()
	 << endl;
  }
  
  vector<int> BeamStructure::allLumiBX () {
    fillCache ();
    vector<int> result; result.reserve (lumiBX.size());
    set<int>::iterator i = lumiBX.begin();
    for (; i != lumiBX.end(); ++i) {
      result.push_back (*i);
    }
    return result;
  }

  int BeamStructure::closestLumiOffset (int bx) {
    fillCache ();
    if (!lumiBX.size()) return 0; 
    set<int>::iterator i = lumiBX.lower_bound (bx);
    if (i == lumiBX.begin()) i = lumiBX.end();
    return bx - (*(--i));
  }

  double BeamStructure::getLumiFraction (int bx, double lifetime) {
    fillCache ();
    double result = 0;
    for (set<int>::iterator i = lumiBX.begin(); i != lumiBX.end(); ++i) {
      int delay = bx - *i;
      if (delay < 0) delay += BX_IN_ORBIT;
      double timeFrac = BX_TIME / lifetime;
      double expFrac = exp (-timeFrac);
      double lumi = 0;
      double sinhFrac = sinh(0.5*timeFrac);
      double fracContribution = 4./timeFrac*sinhFrac*sinhFrac;
      if (delay == 0) {  // itself
	lumi = 1 - 1./timeFrac*(1.-expFrac);
	lumi += fracContribution*pow(expFrac, BX_IN_ORBIT) / (1.-exp (-BX_IN_ORBIT*BX_TIME/lifetime));
      }
      else {
	lumi = fracContribution*pow(expFrac, delay) / (1.-exp (-BX_IN_ORBIT*BX_TIME/lifetime));
      }
      result += lumi;
    }
    return result / lumiBX.size();
  }

  double BeamStructure::getLumiEfficiency (double lifetime) {
    double sum = 0;
    for (int bx = 0; bx < BX_IN_ORBIT; ++bx) {
      if (isSensitive (bx)) sum += getLumiFraction (bx, lifetime);
    }
    return sum;
  }
 
  double BeamStructure::getSensitiveFraction (double lifetime) {
    int timeWindow = int(floor(lifetime*1.256/BX_TIME+0.5));
    int sensitiveBXs = 0;
    for (int bx = 0; bx < BX_IN_ORBIT; ++bx) {
      if (isSensitive(bx)) {
	if ((lifetime > BX_IN_ORBIT * BX_TIME) || (closestLumiOffset (bx) < timeWindow)) ++sensitiveBXs;
	//cout << bx << '/' << isSensitive(bx) << '/' << closestLumiOffset (bx) << '/' << timeWindow << endl;
      }
    }
    return double (sensitiveBXs) / BX_IN_ORBIT;
  }
}

int main () {
  // test
  BeamStructure bs;
  // 1000ns_50b_35_14_35
  bs.addTrain (1,     1, 1000, 4);
  bs.addTrain (2,     1, 1000, 4);
  bs.addTrain (1,  1601, 1000, 3);
  bs.addTrain (2,  1601, 1000, 3);
  bs.addTrain (1,  2801, 1000, 4);
  bs.addTrain (2,  2801, 1000, 4);
  bs.addTrain (1,  4401, 1000, 3);
  bs.addTrain (2,  4401, 1000, 3);
  bs.addTrain (1,  8941, 1000, 4);
  bs.addTrain (2,  6601,   25, 1);
  bs.addTrain (1, 10541, 1000, 3);
  bs.addTrain (2,  8911, 1000, 4);
  bs.addTrain (1, 11741, 1000, 4);
  bs.addTrain (2, 10511, 1000, 3);
  bs.addTrain (1, 13341, 1000, 3);
  bs.addTrain (2, 11741, 1000, 4);
  bs.addTrain (1, 17301,   25, 1);
  bs.addTrain (2, 13341, 1000, 3);
  bs.addTrain (1, 17851, 1000, 4);
  bs.addTrain (2, 14541, 1000, 4);
  bs.addTrain (1, 19451, 1000, 3);
  bs.addTrain (2, 16141, 1000, 3);
  bs.addTrain (1, 20681, 1000, 4);
  bs.addTrain (2, 17851, 1000, 4);
  bs.addTrain (1, 22281, 1000, 3);
  bs.addTrain (2, 19451, 1000, 3);
  bs.addTrain (1, 23481, 1000, 4);
  bs.addTrain (2, 20681, 1000, 4);
  bs.addTrain (1, 25081, 1000, 3);
  bs.addTrain (2, 22281, 1000, 3);


  // signal events
  int signalBX [] = {2024, 5, 705, 470, 475};
  int nSignals = sizeof(signalBX)/sizeof(int);

  // get lifetime points
  std::vector<double> bxDelays;
  int i = 0;
  for (i = 0; i < nSignals; ++i) {
    int eventDelay = bs.closestLumiOffset (signalBX[i]);
    std::cout << "Event " << signalBX[i] << " delay: " << eventDelay << std::endl;
    bxDelays.push_back (double(eventDelay)*BX_TIME/1.256);
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
    double sensitiveFraction = bs.getSensitiveFraction (lifetime);
    std::cout << "sensitive BXs: " << sensitiveFraction*BX_IN_ORBIT << std::endl;
    
    // data
    double expectedBackground = BACKGROUND * sensitiveFraction;
    double sigmaBackground = SIGMA_BACKGROUND * sensitiveFraction;
    int nObserved = lifetimes[i].first;
    std::cout << i << " lifetime=" << lifetimes[i].second << " nObserved:" << lifetimes[i].first 
	      << " Background: " << expectedBackground << "+-" << sigmaBackground
	      << " Scale: 1+-0.13"
	      << std::endl;
    
    // get limit
    CountingExperiment* ce = useCLs ? static_cast<CountingExperiment*> (new CLsCountingExperiment (expectedBackground, sigmaBackground, 1, 0.083)) 
      : static_cast<CountingExperiment*> (new CL95CMSCountingExperiment (expectedBackground, sigmaBackground, 1, 0.083));
    double limit = ce->cl95limit (nObserved);
    std::vector<double>  expectedLimit = ce->cl95ExpectedLimit ();
    delete ce; ce = 0;
    
    char buffer[10000];
    sprintf (buffer, "%s lifetime: %6.3e lumiEff: %5.4f  bkg: %5.3f observed: %3i limit: %5.3f expectedmean: %5.3f rms1sigma:  %5.3f %5.3f rms2sigma: %5.3f %5.3f  expectedmed: %5.3f qtile1sigma: %5.3f %5.3f qtile2sigma: %5.3f %5.3f", 
	     useCLs ? "CLs" : "CL95CMS",
	     lifetime, bs.getLumiEfficiency (lifetime), expectedBackground, nObserved, limit,
	     expectedLimit[5], expectedLimit[6], expectedLimit[7], expectedLimit[8], expectedLimit[9], 
	     expectedLimit[0], expectedLimit[1], expectedLimit[2], expectedLimit[3], expectedLimit[4]); 
    std::ofstream outdata ("lifetimePoint_out.txt", std::ios_base::app);
    outdata << buffer << std::endl;
    outdata.close();
    
  }
  
  
  return 0;
}
