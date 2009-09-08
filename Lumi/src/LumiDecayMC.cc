// Generates decays according to LUMI profile
// F.Ratnikov, Aug. 21, 2009
#include <math.h>
#include <iostream>
#include <iomanip>

#include "TRandom2.h"

#include "StoppedHSCP/Lumi/interface/LumiObjects.h"
#include "StoppedHSCP/Lumi/interface/LumiReader.h"
#include "StoppedHSCP/Lumi/interface/LumiDecayMC.h"

using namespace std;

namespace shscp {

  std::map <LumiReader*, LumiDecayMC*> LumiDecayMC::mIndex;
  TRandom* LumiDecayMC::mRandom = new TRandom2();

  LumiDecayMC* LumiDecayMC::getLumiDecayMC (LumiReader* fLumiReader) {
    if (mIndex.find (fLumiReader) == mIndex.end ())  mIndex[fLumiReader] = new LumiDecayMC (fLumiReader);
    return mIndex[fLumiReader];
  }
  
    // Limit generation to profile time range
  LumiDecayMC::LumiDecayMC (LumiReader* fLumiReader)
    : mLumiReader (fLumiReader),
      mTotalLumi (-1),
      mTMin (-1),
      mTMax (-1)
  {
  }
  
  LumiDecayMC::~LumiDecayMC () {
  }
  
    // generate time of the decay
  double LumiDecayMC::generate (double fTBegin, double fTEnd, double fLifetime) {
    const double HISTORY_MARGIN = log (1.e9);
    int tBegin = int (floor (fTBegin-fLifetime*HISTORY_MARGIN+0.5));
    int tEnd = int (floor (fTEnd+0.5));
    if (tBegin != mTMin || tEnd != mTMax || mTotalLumi < 0) { // init new interval
      mTMin = tBegin;
      mTMax = tEnd;
      init ();
    }
    // simulate production and decays
    while (1) {
      // pick section
      double lumi = mRandom->Uniform (mTotalLumi);
      std::map<double, int64_t>::const_iterator it = mLumiIntegral.lower_bound (lumi);
      if (it == mLumiIntegral.end()) {
	std::cerr << "LumiDecayMC::generate-> Failed find section for LUMI " << lumi << ", maximum LUMI: " << mLumiIntegral.rbegin()->first << std::endl;
	return 0;
      }
      int64_t index = it->second;
      double production_time = mRandom->Uniform (mLumiReader->sectionStartTime (index), mLumiReader->sectionEndTime (index));
      double lifetime = mRandom->Exp (fLifetime);
      double decay_time = production_time + lifetime;
      if (decay_time < fTBegin || decay_time > fTEnd) continue;
      // add empty bunches efficiency
      int64_t indexDecay = mLumiReader->getIndex (decay_time);
      double fraction = indexDecay >= 0 ? mLumiReader->sectionEmptyBunchesFraction (indexDecay) : 0;
      if (mRandom->Uniform (1.) > fraction) continue;
      return decay_time;
    }
  }

    // generate time of the decay for flat decay distribution
  double LumiDecayMC::generateFlat (double fTBegin, double fTEnd) {
    while (1) {
      double production_time = mRandom->Uniform (fTBegin, fTEnd);
      int64_t index = mLumiReader->getIndex (production_time);
      if (index > 0) {
	// add empty bunches efficiency
	double fraction = mLumiReader->sectionEmptyBunchesFraction (index);
	if (fraction > 0 && mRandom->Uniform (1.) < fraction) {
	  return production_time;
	}
      }
    }
  }

  void LumiDecayMC::init () {
    mLumiIntegral.clear();
    double lumiIntegral = 0;
    for (int64_t index = 0; index < mLumiReader->entries(); ++index) {
      // consider only alive sections in requested time interval 
      if (int (floor (mLumiReader->sectionEndTime (index)+1.)) < mTMin) continue;
      if (int (floor (mLumiReader->sectionStartTime (index)-1.)) > mTMax) continue;
      double lumi = mLumiReader->integratedLuminosity (index);
      if (lumi <= 0) continue;
      lumiIntegral += lumi;
      mLumiIntegral [lumiIntegral] = index;
      // std::cout << "LumiDecayMC::init-> " << index << '/' << mTMin << '/' << mTMax << setprecision(12) << '/' << mLumiReader->sectionStartTime (index) << '/' << mLumiReader->sectionEndTime (index) << '/' <<  lumi << '/' << lumiIntegral << std::endl;
    }
    mTotalLumi = lumiIntegral;
  }
}
