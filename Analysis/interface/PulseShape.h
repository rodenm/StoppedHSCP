#ifndef PulseShape_h
#define PulseShape_h

// store time sample for some collection of towers/digis
// and calculate pulse shape variables

#include <vector>

class StoppedHSCPEvent;

class PulseShape {
 public:

  PulseShape();
  ~PulseShape();

  void addSample(unsigned bx, double val);
  
  void addJet(StoppedHSCPEvent* evt, unsigned njet);

  void findPeak();

  unsigned getPeak();
  double getPeakValue();
  double getP1ToP0();
  double getP2ToP1();
  double getP0ToTotal();
  double getOuterToTotal();

 private:

  std::vector<double> samples_;
  unsigned nPeak_;
  double total_;
};

#endif
