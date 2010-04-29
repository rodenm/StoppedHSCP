#ifndef StoppedHSCPRun_h
#define StoppedHSCPRun_h

#include <vector>

#include "TObject.h"

class StoppedHSCPRun : public TObject {

 public:

  StoppedHSCPRun();
  ~StoppedHSCPRun();

  void addLumiBlock();

  unsigned run;

  ULong64_t startTime;
  ULong64_t stopTime;

  // DAQ pause/resume  -  can't get this yet?
  std::vector<ULong64_t> daqPauseTimes;
  std::vector<ULong64_t> daqResumeTimes;
  
  // lumi sections
  unsigned nls;
  std::vector<ULong64_t> deadtimeSCAL;
  std::vector<ULong64_t> physTrigLostSCAL;
  std::vector<bool> hasEvent;

  ClassDef(StoppedHSCPRun, 1);

};

#endif
