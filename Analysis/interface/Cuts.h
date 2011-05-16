#ifndef Cuts_h
#define Cuts_h

#include "StoppedHSCP/Analysis/interface/StoppedHSCPEvent.h"

#include <string>
#include <vector>

class StoppedHSCPEvent;

class Cuts {
 public:

  typedef bool (Cuts::*CutFn)() const;

 public:

  Cuts(StoppedHSCPEvent* event,
       bool isMC, 
       unsigned version);

  ~Cuts();

  // the cut methods themselves
  bool triggerCut() const;      // require event passed main trigger
  bool controlTrigger() const;  // event fired control trigger
  bool bptxVeto() const;        // cut on time wrt BPTX signal
  bool bxVeto() const;          // cut on BX wrt expected collisions
  bool vertexVeto() const;      // no vertex
  bool haloVeto() const;        // no halo ID
  bool hfVeto() const;          // no HF activity
  bool trackVeto() const;        // require no tracks
  bool cosmicVeto() const;      // no cosmic muon
  bool hcalNoiseVeto() const;   // std HCAL noise veto
  bool looseJetCut() const;     // low Et threshold
  bool jetEnergyCut() const;    // require jet above Et threshold
  bool jetN60Cut() const;       // jet n60
  bool jetN90Cut() const;       // jet n90
  bool towersIPhiCut() const;   // cut on N leading towers at same iphi
  bool iPhiFractionCut() const; // Et fraction at leading iphi
  bool hpdR1Cut() const;        // timing R1 cut from HPD
  bool hpdR2Cut() const;        // timing R2 cut from HPD
  bool hpdRPeakCut() const;     // timing Rp cut from HPD
  bool hpdROuterCut() const;    // timing Ro cut from HPD
  bool digiR1Cut() const;       // timing R1 cut from digis
  bool digiR2Cut() const;       // timing R2 cut from digis
  bool digiRPeakCut() const;    // timing Rp cut from digis
  bool digiROuterCut() const;   // timing Ro cut from digis
  bool geometryHaloCut() const; // cut events with halo-like CSCSegments

  // get cut version
  unsigned cutVersion() const { return version_; }

  // set current event
  void setEvent(StoppedHSCPEvent* event) { event_ = event; }

  // get number of cuts
  unsigned nCuts() const { return cuts_.size(); }

  // n-th cut result for current event
  bool cutN(unsigned n) const;

  // cut name for histogram bins
  const std::string cutName(unsigned n) const { return names_.at(n); }

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

  // pretty print
  void print(std::ostream& os) const;

 private:

  // setup method
  void addCut(Cuts::CutFn, std::string name);

 private:

  // pointer to the event
  StoppedHSCPEvent* event_;

  // this is MC data
  bool isMC_;

  // cuts version
  unsigned version_;

  // vector of cut methods
  std::vector<CutFn> cuts_;

  // vector of cut names
  std::vector<std::string> names_;
  
};

#endif
