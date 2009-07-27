// Accessor to LUMI information stored in one or many files
// F.Ratnikov, Jul. 23, 2009

#include "TBranch.h"
#include "TChain.h"

#include "StoppedHSCP/Lumi/interface/LumiReader.h"

namespace {
  const char* LUMI_TREE = "LumiTree";
}

namespace shscp {

  int64_t LumiReader::getGlobalIndex (int64_t fLocalIndex) {return mChain->LoadTree(fLocalIndex);}

  bool LumiReader::initHeader () {
    if (!mHeaderBranch) {
      mHeaderBranch = mChain->GetBranch ("Header");
      if (mHeaderBranch) mHeaderBranch->SetAddress (&mHeader);
    }
    return mHeaderBranch;
  }

  bool LumiReader::initSummary () {
    if (!mSummaryBranch) {
      mSummaryBranch = mChain->GetBranch ("Summary");
      if (mSummaryBranch) mSummaryBranch->SetAddress (&mSummary);
    }
    return mSummaryBranch;
  }

  bool LumiReader::initDetail () {
    if (!mDetailBranch) {
      mDetailBranch = mChain->GetBranch ("Detail");
      if (mDetailBranch) mDetailBranch->SetAddress (&mDetail);
    }
    return mDetailBranch;
  }
  
  bool LumiReader::initIndex () {
    if (!mTimestampIndex.empty()) return true;
    if (!initHeader ()) return false;
    int64_t totalEntries = mChain->GetEntries ();
    for (int64_t i = 0; i < totalEntries; ++i) {
      mHeaderBranch->GetEntry (i);
      mTimestampIndex [mHeader->timestamp] = i;
      if (mHeader->bCMSLive) mRunsectionIndex [LumiRunSection(mHeader->runNumber, mHeader->sectionNumber).runsection()] = i;
    }
    return !mTimestampIndex.empty();
  }
  
  LumiReader::LumiReader (const std::string& fFileName) 
    : mHeader (new LumiSectionHeader), mHeaderBranch (0),
      mSummary (new LumiSummary), mSummaryBranch (0),
      mDetail (new LumiDetail), mDetailBranch (0),
      mChain (0)
  {
    mChain = new TChain (LUMI_TREE);
    if (!fFileName.empty()) mChain->Add (fFileName.c_str());
  }

  LumiReader::LumiReader (const std::vector <std::string>& fFileNames) 
    : mHeader (new LumiSectionHeader), mHeaderBranch (0),
      mSummary (new LumiSummary), mSummaryBranch (0),
      mDetail (new LumiDetail), mDetailBranch (0),
      mChain (0)
  {
    mChain = new TChain (LUMI_TREE);
    
    for (size_t i = 0; i < fFileNames.size(); ++i) mChain->Add (fFileNames[i].c_str());
  }
  
  LumiReader::~LumiReader () {
    delete mHeader;
    delete mHeaderBranch;
    delete mSummary;
    delete mSummaryBranch;
    delete mDetail;
    delete mDetailBranch ;
    delete mChain;
  }

  int64_t LumiReader::getIndex (const LumiRunSection& fRunSectionuin) {
    if (!initIndex ()) return -1;
    if (mRunsectionIndex.find (fRunSectionuin.runsection()) == mRunsectionIndex.end()) return -1;
    return (*(mRunsectionIndex.find (fRunSectionuin.runsection()))).second;
    
  } 
  int64_t LumiReader::getIndex (uint32_t fTime) {
    if (!initIndex ()) return -1;
    if (mTimestampIndex.find (fTime) == mTimestampIndex.end()) return -1;
    return (*(mTimestampIndex.find (fTime))).second;
  }

  std::vector<LumiRunSection> LumiReader::getAllRunsections () const {
    std::vector<LumiRunSection> result;
    result.reserve (mRunsectionIndex.size());
    std::map <uint64_t, int64_t>::const_iterator i = mRunsectionIndex.begin ();
    for (; i != mRunsectionIndex.end (); ++i) {
      result.push_back ((*i).second);
    }
    return result;
  }

  std::vector<uint32_t> LumiReader::getAllTimestamps () const {
    std::vector<uint32_t> result;
    result.reserve (mTimestampIndex.size());
    std::map <uint32_t, int64_t>::const_iterator i = mTimestampIndex.begin ();
    for (; i != mTimestampIndex.end (); ++i) {
      result.push_back ((*i).second);
    }
    return result;
  }

  const LumiSectionHeader* LumiReader::getLumiHeaderByIndex (uint64_t fIndex) {
    if (!initHeader ()) return 0;
    mHeaderBranch->GetEntry (fIndex);
    return mHeader;
  }

  const LumiSectionHeader* LumiReader::getLumiHeader (const LumiRunSection& fRunSection) {
    int64_t index = getIndex (fRunSection);
    if (index < 0) return 0;
    return getLumiHeaderByIndex (index);
  }

  const LumiSummary* LumiReader::getLumiSummary (const LumiRunSection& fRunSection) {
    int64_t index = getIndex (fRunSection);
    if (index < 0) return 0;
    if (!initSummary ()) return 0;
    mSummaryBranch->GetEntry (index);
    return mSummary;
  }

  const LumiDetail* LumiReader::getLumiDetail (const LumiRunSection& fRunSection) {
    int64_t index = getIndex (fRunSection);
    if (index < 0) return 0;
    if (!initDetail ()) return 0;
    mDetailBranch->GetEntry (index);
    return mDetail;
  }    
  
  const LumiSectionHeader* LumiReader::getLumiHeader (uint32_t mTime) {
    int64_t index = getIndex (mTime);
    if (index < 0) return 0;
    return getLumiHeaderByIndex (index);

  }

  const LumiSummary* LumiReader::getLumiSummary (uint32_t mTime) {
    int64_t index = getIndex (mTime);
    if (index < 0) return 0;
    if (!initSummary ()) return 0;
    mSummaryBranch->GetEntry (index);
    return mSummary;
  }

  const LumiDetail* LumiReader::getLumiDetail (uint32_t mTime) {
    int64_t index = getIndex (mTime);
    if (index < 0) return 0;
    if (!initDetail ()) return 0;
    mDetailBranch->GetEntry (index);
    return mDetail;
  }
  
//   bool  LumiReader::importLumiData (const std::string& fLumiGroupFileName, 
// 				    const std::string& fNewFileName);




}
