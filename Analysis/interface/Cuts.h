#ifndef Cuts_h
#define Cuts_h

#include "StoppedHSCP/Analysis/interface/StoppedHSCPEvent.h"

#include <string>
#include <vector>

class StoppedHSCPEvent;

class Cuts {
 public:
  Cuts(StoppedHSCPEvent* event, bool isMC);
  ~Cuts();

  // setup BX masks
  void readMaskedBXs(std::string filename, unsigned run);

  // set current event
  void setEvent(StoppedHSCPEvent* event) {event_ = event; }

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

  // result of cuts after smearing, for systematics
  bool cutNSyst(unsigned n, double smear) const;

  // number of std HCAL noise cuts
  unsigned nHcalCuts() const;

  // standard HCAL noise cuts
  bool stdHcalCutN(unsigned n) const;

  // event is in masked BX
  bool inMaskedBX() const;


 private:

  StoppedHSCPEvent* event_;

  std::vector<unsigned> maskedBXs_;

  bool isMC_;

};

#endif
