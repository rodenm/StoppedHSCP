#ifndef Cuts_h
#define Cuts_h

#include "StoppedHSCP/Analysis/interface/StoppedHSCPEvent.h"

#include <string>
#include <vector>

class StoppedHSCPEvent;

class Cuts {
 public:

  Cuts(StoppedHSCPEvent* event,
       bool isMC, 
       unsigned version);

  ~Cuts();

  unsigned cutVersion() const;

  // read BX masks form file - old method
  //  void readMaskedBXs(std::string filename, unsigned run);

  // set BX masks from filled bunches and window
  //  void setMaskedBXs(std::vector<bool> bxMask);

  // set current event
  void setEvent(StoppedHSCPEvent* event) {event_ = event; }

  // turn on/off digi-based cuts

  //  void setDigiCuts(bool digicut=false){useDigiCuts_=digicut;}

  // number of cuts
  unsigned nCuts() const;

  // n-th cut result for current event
  bool cutN(unsigned n) const;

  // cut name for histogram bins
  const std::string cutName(unsigned n) const;

  // result of first N cuts
  bool allCutN(unsigned n) const;

  // result of all cuts
  bool cut() const;

  // result of n minus one cuts
  bool cutNMinusOne(unsigned n) const;

  // result after selected cuts
  bool cutNMinusSome(std::vector<unsigned int> n) const;

  // result of cuts after smearing, for systematics
  bool cutNSyst(unsigned n, double smear) const;

 private:

  // pointer to the event
  StoppedHSCPEvent* event_;

  // this is MC data
  bool isMC_;

  // cuts version
  unsigned version_;

  // list of BXs to mask
  //  std::vector<bool> bxMask_;

  // if enabled, will use digi-based noise cuts
  //  bool useDigiCuts_;

};

#endif
