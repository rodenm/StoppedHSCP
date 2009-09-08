// Generates decays according to LUMI profile
// F.Ratnikov, Aug. 21, 2009
#ifndef SHSCP_LUMI_DECAU_MC_H
#define SHSCP_LUMI_DECAU_MC_H

#include <map>

class TRandom; // ROOT random class

namespace shscp {

  class LumiReader;

  class LumiDecayMC {
  public:
    // Limit generation to profile time range
    // generate time of the decay
    double generate (double fTBegin, double fTEnd, double fLifetime);
    // generate time of the decay for flat decay distribution
    double generateFlat (double fTBegin, double fTEnd);
    static LumiDecayMC* getLumiDecayMC (LumiReader* fLumiReader);
  private:
    std::map<double, int64_t> mLumiIntegral;
    LumiReader* mLumiReader;
    double mTotalLumi;
    int mTMin;
    int mTMax;
    static std::map <LumiReader*, LumiDecayMC*> mIndex; 
    static TRandom* mRandom;

    // all private constructors
    LumiDecayMC (LumiReader* fLumiReader);
    ~LumiDecayMC ();
    LumiDecayMC (LumiDecayMC&);
    LumiDecayMC& operator= (LumiDecayMC&);
      

    void init ();
  };
}
#endif
