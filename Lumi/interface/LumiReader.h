// Accessor to LUMI information stored in one or many files
// F.Ratnikov, Jul. 23, 2009
#ifndef SHSCP_LUMI_READER_H
#define SHSCP_LUMI_READER_H

#include <stdint.h>
#include <string>
#include <vector>
#include <map>

#include "StoppedHSCP/Lumi/interface/LumiObjects.h"

class TChain;
class TBranch;

namespace shscp {

  class LumiRunSection {
  public:
    LumiRunSection (uint32_t fRun = 0, uint32_t fSection = 0) : mRunsection ((uint64_t(fRun) << 32) + fSection) {}
    uint32_t run () const {return ((mRunsection >> 32) & 0xffffffff);}
    uint32_t section () const {return (mRunsection &  0xffffffff);}
    uint64_t runsection () const {return mRunsection;}
  private:
    uint64_t mRunsection;
    };

  class LumiReader {
  public:
    LumiReader (const std::string& fFileName = "");
    LumiReader (const std::vector <std::string>& fFileNames);
    ~LumiReader ();

    int64_t getIndex (const LumiRunSection& fRunSectionuin); 
    int64_t getIndex (uint32_t mTime);

    std::vector<LumiRunSection> getAllRunsections () const;
    std::vector<uint32_t> getAllTimestamps () const;

    const LumiSectionHeader* getLumiHeaderByIndex (uint64_t fIndex);
    

    const LumiSectionHeader* getLumiHeader (const LumiRunSection& fRunSection);
    const LumiSummary* getLumiSummary (const LumiRunSection& fRunSection);
    const LumiDetail* getLumiDetail (const LumiRunSection& fRunSection);
    
    const LumiSectionHeader* getLumiHeader (uint32_t mTime);
    const LumiSummary* getLumiSummary (uint32_t mTime);
    const LumiDetail* getLumiDetail (uint32_t mTime);
    
    const LumiSummary* getLumiSummary (uint32_t fRun, uint32_t fSection);



    static bool importLumiData (const std::string& fLumiGroupFileName = "", const std::string& fNewFileName);

  private:
    LumiSectionHeader* mHeader;
    TBranch* mHeaderBranch;
    LumiSummary* mSummary;
    TBranch* mSummaryBranch;
    LumiDetail* mDetail;
    TBranch* mDetailBranch;
    TChain* mChain;
    std::map <uint64_t, int64_t> mRunsectionIndex;
    std::map <uint32_t, int64_t> mTimestampIndex;

    int64_t getGlobalIndex (int64_t fLocalIndex);
    bool initHeader ();
    bool initSummary ();
    bool initDetail ();
    bool initIndex ();
  };
}
#endif
