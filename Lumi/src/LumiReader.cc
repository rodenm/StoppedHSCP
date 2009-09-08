// Accessor to LUMI information stored in one or many files
// F.Ratnikov, Jul. 23, 2009

#include <iostream>
#include <cmath>

#include "TBranch.h"
#include "TChain.h"

#include "StoppedHSCP/Lumi/interface/LumiReader.h"

namespace {
  const char* LUMI_TREE = "LumiTree";
  const double BX_TIME = 24.95e-9; // 24.95 ns
  double endtime (const shscp::LumiSectionHeader& header) {
    return double(header.timestamp)+double(header.timestamp_micros)*1e-6+header.numOrbits * header.numBunches * BX_TIME;
  }
}

namespace shscp {

  std::map <std::string, LumiReader*> LumiReader::mIndex;

  LumiReader* LumiReader::getLumiReader (const std::string& fLumiFile) {
    if (mIndex.find (fLumiFile) == mIndex.end ())  mIndex[fLumiFile] = new LumiReader (fLumiFile);
    return mIndex[fLumiFile];
  }
  
  LumiReader::LumiReader (const std::string& fFileName) 
    : mHeader (new LumiSectionHeader), mHeaderBranch (0), mHeaderIndex (-1),
      mSummary (new LumiSummary), mSummaryBranch (0), mSummaryIndex (-1),
      mDetail (new LumiDetail), mDetailBranch (0), mDetailIndex (-1),
      mChain (0)
  {
    mFiles.push_back (fFileName);
    init();
  }

  LumiReader::LumiReader (const std::vector <std::string>& fFileNames) 
    : mFiles(fFileNames),
      mHeader (new LumiSectionHeader), mHeaderBranch (0), mHeaderIndex (-1),
      mSummary (new LumiSummary), mSummaryBranch (0), mSummaryIndex (-1),
      mDetail (new LumiDetail), mDetailBranch (0), mDetailIndex (-1),
      mChain (0)
  {
    init ();
  }
  
  LumiReader::~LumiReader () {
    delete mChain;
    delete mHeader;
    delete mSummary;
    delete mDetail;
  }

  LumiReader::LumiReader (const LumiReader& fOther) 
    : mFiles (fOther.mFiles)
  {
    init ();
  }

  LumiReader& LumiReader::operator= (const LumiReader& fOther) {
    mFiles = fOther.mFiles;
    init();
    return *this;
  }
  
  bool LumiReader::initHeader () {
    if (!mHeaderBranch) {
      mHeaderBranch = mChain->GetBranch ("Header");
      if (mHeaderBranch) mHeaderBranch->SetAddress (&mHeader);
      else std::cout << "Can not initiate 'Header' branch" << std::endl;
    }
    return mHeaderBranch;
  }

  bool LumiReader::initSummary () {
    if (!mSummaryBranch) {
      mSummaryBranch = mChain->GetBranch ("Summary");
      if (mSummaryBranch) mSummaryBranch->SetAddress (&mSummary);
      else std::cout << "Can not initiate 'Summary' branch" << std::endl;
    }
    
    return mSummaryBranch;
  }

  bool LumiReader::initDetail () {
    if (!mDetailBranch) {
      mDetailBranch = mChain->GetBranch ("Detail");
      if (mDetailBranch) mDetailBranch->SetAddress (&mDetail);
      else std::cout << "Can not initiate 'Detail' branch" << std::endl;
    }
    return mDetailBranch;
  }
  
  bool LumiReader::initIndex () {
    if (!mTimestampIndex.empty()) return true;
    if (!initHeader ()) return false;
    mTotalEntries = mChain->GetEntries ();
    for (int64_t i = 0; i < entries(); ++i) {
      mHeaderBranch->GetEntry (i);
      mTimestampIndex [uint32_t(floor(endtime (*mHeader)))] = i;
      mRunsectionIndex [LumiRunSection(mHeader->runNumber, mHeader->sectionNumber).runsection()] = i;
//       std::cout << "LumiReader::initIndex-> " << i 
// 		<< '/' << mHeader->timestamp << '/' << mHeader->runNumber << '/' << mHeader->sectionNumber 
// 		<< '/' << std::hex << LumiRunSection(mHeader->runNumber, mHeader->sectionNumber).runsection() << std::dec
// 		<< std::endl;
    }
    return !mTimestampIndex.empty();
  }

  void LumiReader::init () {
    mHeader = new LumiSectionHeader;
    mHeaderBranch = 0;
    mSummary = new LumiSummary;
    mSummaryBranch = 0;
    mDetail = new LumiDetail;
    mDetailBranch =0;
    mChain = new TChain (LUMI_TREE);
    for (size_t i = 0; i < mFiles.size(); ++i) mChain->Add (mFiles[i].c_str());
    initIndex ();
  }
  
  std::vector<LumiRunSection> LumiReader::getAllRunsections () const {
    std::vector<LumiRunSection> result;
    result.reserve (mRunsectionIndex.size());
    std::map <uint64_t, int64_t>::const_iterator i = mRunsectionIndex.begin ();
    for (; i != mRunsectionIndex.end (); ++i) {
      result.push_back (LumiRunSection (i->first));
    }
    return result;
  }

  std::vector<uint32_t> LumiReader::getAllTimestamps () const {
    std::vector<uint32_t> result;
    result.reserve (mTimestampIndex.size());
    std::map <uint32_t, int64_t>::const_iterator i = mTimestampIndex.begin ();
    for (; i != mTimestampIndex.end (); ++i) {
      result.push_back (i->first);
    }
    return result;
  }

  int64_t LumiReader::getIndex (const LumiRunSection& fRunSectionuin) {
    if (!initIndex ()) return -1;
    if (mRunsectionIndex.find (fRunSectionuin.runsection()) == mRunsectionIndex.end()) return -1;
    return (mRunsectionIndex.find (fRunSectionuin.runsection()))->second;
    
  } 
  int64_t LumiReader::getIndex (uint32_t fTime) {
    if (!initIndex ()) return -1;
    std::map <uint32_t, int64_t>::const_iterator it = mTimestampIndex.lower_bound (fTime);
    if (it != mTimestampIndex.end()) return it->second;
    return -1;
  }

int64_t LumiReader::getIndex (double mTime) {return getIndex (uint32_t (floor (mTime)));}

  const LumiSectionHeader* LumiReader::getLumiHeaderByIndex (int64_t fIndex) {
    if (fIndex != mHeaderIndex) {
      if (!initHeader ()) return 0;
      mHeaderBranch->GetEntry (fIndex);
      mHeaderIndex = fIndex;
    }
    return mHeader;
  }

  const LumiSummary* LumiReader::getLumiSummaryByIndex (int64_t fIndex) {
    if (fIndex != mSummaryIndex) {
      if (!initSummary ()) return 0;
      mSummaryBranch->GetEntry (fIndex);
      mSummaryIndex = fIndex;
    }
    return mSummary;
  }

  const LumiDetail* LumiReader::getLumiDetailByIndex (int64_t fIndex) {
    if (fIndex != mDetailIndex) {
      if (!initDetail ()) return 0;
      mDetailBranch->GetEntry (fIndex);
      mDetailIndex = fIndex;
    }
    return mDetail;
  }    
  
  const LumiSectionHeader* LumiReader::getLumiHeader (const LumiRunSection& fRunSection) {
    int64_t index = getIndex (fRunSection);
    if (index < 0) return 0;
    return getLumiHeaderByIndex (index);
  }

  const LumiSummary* LumiReader::getLumiSummary (const LumiRunSection& fRunSection) {
    int64_t index = getIndex (fRunSection);
    if (index < 0) return 0;
    return getLumiSummaryByIndex (index);
  }

  const LumiDetail* LumiReader::getLumiDetail (const LumiRunSection& fRunSection) {
    int64_t index = getIndex (fRunSection);
    if (index < 0) return 0;
    return getLumiDetailByIndex (index);
  }    
  
  const LumiSectionHeader* LumiReader::getLumiHeader (uint32_t mTime) {
    int64_t index = getIndex (mTime);
    if (index < 0) return 0;
    return getLumiHeaderByIndex (index);

  }

  const LumiSummary* LumiReader::getLumiSummary (uint32_t mTime) {
    int64_t index = getIndex (mTime);
    if (index < 0) return 0;
    return getLumiSummaryByIndex (index);
  }

  const LumiDetail* LumiReader::getLumiDetail (uint32_t mTime) {
    int64_t index = getIndex (mTime);
    if (index < 0) return 0;
    return getLumiDetailByIndex (index);
  }

  const LumiSummary* LumiReader::getLumiSummary (uint32_t fRun, uint32_t fSection) {
    return getLumiSummary (LumiRunSection (fRun, fSection));
  }
  

  double LumiReader::instantLuminosity (int64_t fIndex) {
      const LumiSummary* summary = getLumiSummaryByIndex (fIndex);
      return summary ? summary->InstantLumi : 0;
  }

  double LumiReader::integratedLuminosity (int64_t fIndex) {
    const LumiSectionHeader* header = getLumiHeaderByIndex (fIndex);
    const LumiSummary* summary = getLumiSummaryByIndex (fIndex);
    if (header && summary) {
      return summary->InstantLumi * header->numOrbits * header->numBunches * BX_TIME;
    } 
    return 0; // no data
  }
  
  double LumiReader::sectionStartTime (int64_t fIndex) {
    const LumiSectionHeader* header = getLumiHeaderByIndex (fIndex);
    if (header) {
      return double (header->timestamp) + double (header->timestamp_micros) * 1e-6; 
    }
    return 0;
  }

  double LumiReader::sectionEndTime (int64_t fIndex) {
    const LumiSectionHeader* header = getLumiHeaderByIndex (fIndex);
    if (header) {
      return endtime (*header);
    }
    return 0;
  }

  double LumiReader::sectionEmptyBunchesFraction (int64_t fIndex) {
    const LumiSectionHeader* header = getLumiHeaderByIndex (fIndex);
    if (header) {
      return double (header->numUnfilledBunches) / double (header->numBunches);
    }
    return 0;
  }
						       

}
