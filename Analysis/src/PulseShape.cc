
#include "StoppedHSCP/Analysis/interface/PulseShape.h"

#include "StoppedHSCP/Analysis/interface/StoppedHSCPEvent.h"

// calculate pulse shape ratios for a given jet in a given event
// returns values in :
// r1 - peak / peak+1
// r2 - peak+1 / peak+2
// rp - peak / total
// ro - outer / total

PulseShape::PulseShape() :
  samples_(10),
  nPeak_(4),
  total_(0.)
{

}

PulseShape::~PulseShape() 
{

}


void PulseShape::addSample(unsigned bx, double val) {
  if (bx >= 0 && bx < 10) {
    samples_.at(bx) += val;
  }
}

void PulseShape::findPeak() {
  double peakval=0.;
  for (unsigned i=0; i<10; ++i) {
    if (samples_.at(i) > peakval) {
      nPeak_=i;
      peakval = samples_.at(i);
      total_ += samples_.at(i);
    }
  }

}

unsigned PulseShape::getPeak() {
  return nPeak_;
}

double PulseShape::getPeakValue() {
  return samples_.at(nPeak_);
}

double PulseShape::getP1ToP0() 
{
  if (nPeak_ < 9) return samples_.at(nPeak_+1) / samples_.at(nPeak_);
  else return 0.;
}

double PulseShape::getP2ToP1()
{
  if (nPeak_ < 8) return samples_.at(nPeak_+2) / samples_.at(nPeak_+1);
  else return 0.;
}

double PulseShape::getP0ToTotal()
{
  return samples_.at(nPeak_) / total_;
}

double PulseShape::getOuterToTotal()
{
  double outer=0.;
  for (unsigned i=0; i<10; ++i) {
    if (i < (nPeak_-1) || i > (nPeak_+2)) outer += samples_.at(i);
  }
  return outer / total_;
}

void PulseShape::addJet(StoppedHSCPEvent* evt, unsigned njet)
{
  //  double fc[11]={ 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0. };

  for (unsigned i=0; i<evt->nDigis(); ++i) {
    if (evt->getDigi(i).nJet == njet) {
      this->addSample(0, evt->getDigi(i).fc0);
      this->addSample(1, evt->getDigi(i).fc1);
      this->addSample(2, evt->getDigi(i).fc2);
      this->addSample(3, evt->getDigi(i).fc3);
      this->addSample(4, evt->getDigi(i).fc4);
      this->addSample(5, evt->getDigi(i).fc5);
      this->addSample(6, evt->getDigi(i).fc6);
      this->addSample(7, evt->getDigi(i).fc7);
      this->addSample(8, evt->getDigi(i).fc8);
      this->addSample(9, evt->getDigi(i).fc9);
    }
  }
  
  this->findPeak();
  
}

