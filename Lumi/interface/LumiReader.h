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

  // combines run# and lumi section# in single 64 bit word
  class LumiRunSection {
  public:
    LumiRunSection (uint64_t fRunsection = 0) : mRunsection (fRunsection) {}
    LumiRunSection (uint32_t fRun, uint32_t fSection) : mRunsection ((uint64_t(fRun) << 32) + fSection) {}
    uint32_t run () const {return ((mRunsection >> 32) & 0xffffffff);}
    uint32_t section () const {return (mRunsection &  0xffffffff);}
    uint64_t runsection () const {return mRunsection;}
  private:
    uint64_t mRunsection;
  };

  // gathers information from the LUMI NTUPLE
  class LumiReader {
  public:
    // use single file
    LumiReader (const std::string& fFileName = "");

    // use chain of files 
    LumiReader (const std::vector <std::string>& fFileNames);

    ~LumiReader ();

    // all available run/section    
    std::vector<LumiRunSection> getAllRunsections () const;
    // all available timestamps aka start of run/section
    std::vector<uint32_t> getAllTimestamps () const;

    // accessors to different internal LUMI objects by different means    
    const LumiSectionHeader* getLumiHeaderByIndex (uint64_t fIndex);
    const LumiSectionHeader* getLumiHeader (const LumiRunSection& fRunSection);
    const LumiSummary* getLumiSummary (const LumiRunSection& fRunSection);
    const LumiDetail* getLumiDetail (const LumiRunSection& fRunSection);
    const LumiSectionHeader* getLumiHeader (uint32_t mTime);
    const LumiSummary* getLumiSummary (uint32_t mTime);
    const LumiDetail* getLumiDetail (uint32_t mTime);
    const LumiSummary* getLumiSummary (uint32_t fRun, uint32_t fSection);

    // instant LUMI for given run/section
    double instantLuminosity (uint32_t fRun, uint32_t fSection);

    // integrated LUMI for given run/section
    double integratedLuminosity (uint32_t fRun, uint32_t fSection);

    // start time of the run/section
    double sectionStartTime (uint32_t fRun, uint32_t fSection);

    // start time of the run/section
    double sectionEndTime (uint32_t fRun, uint32_t fSection);
    

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

    // internal routines
    bool initHeader ();
    bool initSummary ();
    bool initDetail ();
    bool initIndex ();
    int64_t getIndex (const LumiRunSection& fRunSectionuin); 
    int64_t getIndex (uint32_t mTime);

  };
}
#endif
