#ifndef StoppedHSCPLumiSection_h
#define StoppedHSCPLumiSection_h

#include "FWCore/Framework/interface/LuminosityBlock.h"

#include <vector>

#include "TObject.h"

class StoppedHSCPLumiSection : public TObject {

 public:

  StoppedHSCPLumiSection();
  ~StoppedHSCPLumiSection();

  unsigned ls;
  unsigned run;
  unsigned fill;

  // LS start/stop times
  ULong64_t startTime;
  ULong64_t stopTime;

  // run start/stop times
  ULong64_t runStartTime;
  ULong64_t runStopTime;

  // deadtime
  Double_t deadtime;

  ClassDef(StoppedHSCPLumiSection, 1);

};

#endif
