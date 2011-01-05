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
  void setMaskedBXs(std::vector<bool> bxMask);

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

  // is event masked
  bool inMaskedBX() const;

  // jet leading iphi fraction
  double leadingIPhiFraction() const;

  unsigned jetCaloTowers() const;

 public:

  struct Tower {
    unsigned iphi;
    double e;
  };

  struct tow_gt : public std::binary_function<Tower, Tower, bool> {
    bool operator()(const Tower& x, const Tower& y) {
      return x.e > y.e;
    }
  };

 private:

  // poitner to the event
  StoppedHSCPEvent* event_;

  // this is MC data
  bool isMC_;

  // list of BXs to mask
  std::vector<bool> bxMask_;


};

#endif
