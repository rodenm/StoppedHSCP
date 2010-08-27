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

  // read BX masks form file - old method
  void readMaskedBXs(std::string filename, unsigned run);

  // set BX masks from filled bunches and window
  void setMaskedBXs(std::vector<unsigned> filledBXs);

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

  // poitner to the event
  StoppedHSCPEvent* event_;

  // this is MC data
  bool isMC_;

  // how many BX either side of a bunch to mask
  int bxWindow_;

  // list of BXs to mask
  std::vector<unsigned> maskedBXs_;


};

#endif
