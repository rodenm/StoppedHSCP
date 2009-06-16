#include "StoppedHSCP/Analysis/interface/StoppedHSCPEvent.h"

//#include "StoppedHSCP/Analysis/interface/StoppedHSCPJet.h"

StoppedHSCPEvent::StoppedHSCPEvent() :
  nJets_(0)
{ }

StoppedHSCPEvent::~StoppedHSCPEvent() { }
  
void StoppedHSCPEvent::setEventInfo(unsigned evt,
				    unsigned bx,
				    unsigned orbit,
				    unsigned ls,
				    unsigned run,
				    unsigned fill,
				    unsigned timestamp){
  event_ = evt;
  bx_ = bx;
  orbit_ = orbit;
  lumisection_ = ls;
  run_ = run;
  fill_ = fill;
  timestamp_ = timestamp;
}

// void StoppedHSCPEvent::addTower(Tower t) {
//   //  towers_.push_back(t);
// }

// void StoppedHSCPEvent::addHPD(HPD h) {
//   //  hpds_.push_back(h); 
// }

// void StoppedHSCPEvent::addJet(StoppedHSCPJet j) {
//   if (nJets_ < MAX_N_JETS) {
//     jets_[nJets_+1] = j;
//     ++nJets_;
//   }
// }


// void StoppedHSCPEvent::addMuon(Muon m) { 
//   //  muons_.push_back(m);
// }

#if !defined(__CINT__)
  ClassImp(StoppedHSCPEvent)
  //  ClassImp(StoppedHSCPEvent::StoppedHSCPJet)
#endif
