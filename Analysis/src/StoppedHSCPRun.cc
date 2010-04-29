
#include "StoppedHSCP/Analysis/interface/StoppedHSCPRun.h"


StoppedHSCPRun::StoppedHSCPRun() :
  run(0),
  startTime(0),
  stopTime(0),
  daqPauseTimes(0),
  daqResumeTimes(0),
  nls(0),
  deadtimeSCAL(0),
  physTrigLostSCAL(0),
  hasEvent(0)
{

}


StoppedHSCPRun::~StoppedHSCPRun() 
{

}


void
StoppedHSCPRun::addLumiBlock() {
  deadtimeSCAL.push_back(0);
  physTrigLostSCAL.push_back(0);
  hasEvent.push_back(false);
  nls++;
}
