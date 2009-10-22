#ifndef StoppedHSCPEvent_h
#define StoppedHSCPEvent_h

// -*- C++ -*-
//
// Package:    StoppedHSCP/Analysis
// Class:      StoppedHSCPEvent
// 
/**\class StoppedHSCPEvent StoppedHSCPEvent.h StoppedHSCP/Analysis/interface/StoppedHSCPEvent.h

 Description: Defines the Stopped HSCP TTree

 Implementation:

*/
//
// Original Author:  Jim Brooke
// $Id: StoppedHSCPEvent.h,v 1.9 2009/09/09 14:58:43 jbrooke Exp $
//
//


#include <vector>
#include "TObject.h"

//#include "StoppedHSCP/Analysis/interface/StoppedHSCPJet.h"

namespace shscp {

  struct Event {
  Event() : id(0),bx(0),orbit(0),lumisection(0),run(0),fill(0),time0(0), time1(0) { }
    unsigned id;
    unsigned bx;
    unsigned orbit;
    unsigned lumisection;
    unsigned run;
    unsigned fill;
    unsigned time0;
    unsigned time1;
    ClassDef(Event,1);
  };
  
  struct Trigger {
  Trigger() : gtTrigWord0(0),gtTrigWord1(0),l1BptxPlus(0),l1BptxMinus(0),hltBit(0) { }
    unsigned gtTrigWord0;
    unsigned gtTrigWord1;
    unsigned l1BptxPlus;
    unsigned l1BptxMinus;
    unsigned hltBit;
    ClassDef(Trigger,2);
  };
    
  struct TrigJet {
  TrigJet() : type(0), e(0.), et(0.), eta(0.), phi(0.) { }
    unsigned type;   // 0 - L1 jet, 1 - L1 tau, 2, HLT jet
    double e;
    double et;
    double eta;
    double phi;
    ClassDef(TrigJet, 1);
  };

  struct MC {
  MC() : vtxX(0.),vtxY(0.),vtxZ(0.),vtxR(0.),vtxT(0.),rHadPdgId(0),rHadE(0.),rHadPx(0.),rHadPy(0.),rHadPz(0.),rHadPt(0.) { } 
    double vtxX;
    double vtxY;
    double vtxZ;
    double vtxR;
    double vtxT;
    unsigned rHadPdgId;
    double rHadE;
    double rHadPx;
    double rHadPy;
    double rHadPz;
    double rHadPt;
    ClassDef(MC,1);
  };

  struct MCDecay {
  MCDecay() : pdgId(0),vtxX(0.),vtxY(0.),vtxZ(0.),vtxT(0.),e(0.),px(0.),py(0.),pz(0.),pt(0.) { }
    unsigned pdgId;
    double vtxX;
    double vtxY;
    double vtxZ;
    double vtxR;
    double vtxT;
    double e;
    double px;
    double py;
    double pz;
    double pt;
    ClassDef(MCDecay,1);
  };
  
  struct Tower {
  Tower() : e(0.),et(0.),eta(0.),phi(0.),ieta(0),iphi(0),nJet(0),eHad(0.),etHad(0.),eEm(0.),etEm(0.) { }
    double e;
    double et;
    double eta;
    double phi;
    unsigned ieta;
    unsigned iphi;
    unsigned nJet;
    double eHad;
    double etHad;
    double eEm;
    double etEm;
    ClassDef(Tower,1);
  };
  
  struct HPD {
  HPD() : id(0),eta(0),phi(0),totalZeros(0),maxZeros(0),nJet(0),
      fc0(0.), fc1(0.), fc2(0.), fc3(0.), fc4(0.), fc5(0.), fc6(0.), fc7(0.), fc8(0.), fc9(0.),
      fc5_0(0.), fc5_1(0.), fc5_2(0.), fc5_3(0.), fc5_4(0.), fc5_5(0.), fc5_6(0.), fc5_7(0.), fc5_8(0.), fc5_9(0.) { }
    unsigned id;
    double eta;
    double phi;
    unsigned totalZeros;
    unsigned maxZeros;
    unsigned nJet;
    double fc0, fc1, fc2, fc3, fc4, fc5, fc6, fc7, fc8, fc9;  // ROOT screws up an array :-(
    double fc5_0, fc5_1, fc5_2, fc5_3, fc5_4, fc5_5, fc5_6, fc5_7, fc5_8, fc5_9;
    ClassDef(HPD,1);
  };
  
  struct HcalDigi {
  HcalDigi() : id(0),eta(0),phi(0),nJet(0),
      fc0(0.), fc1(0.), fc2(0.), fc3(0.), fc4(0.), fc5(0.), fc6(0.), fc7(0.), fc8(0.), fc9(0.) { }
    unsigned id;
    double eta;
    double phi;
    unsigned nJet;
    double fc0, fc1, fc2, fc3, fc4, fc5, fc6, fc7, fc8, fc9;  // ROOT screws up an array :-(
    ClassDef(HcalDigi,1);
  };

  struct Jet {
  Jet() : e(0.),et(0.),eta(0.),phi(0.),eHad(0.),eEm(0.),eMaxEcalTow(0.),eMaxHcalTow(0.),n60(0),n90(0),
      r1(0.),r2(0.),rp(0.),ro(0.),r1_top5(0.),r2_top5(0.),rp_top5(0.),ro_top5(0.) { }
    double e;
    double et;
    double eta;
    double phi;
    double eHad;
    double eEm;
    double eMaxEcalTow;
    double eMaxHcalTow;
    unsigned n60;
    unsigned n90;
    double r1;
    double r2;
    double rp;
    double ro;
    double r1_top5;
    double r2_top5;
    double rp_top5;
    double ro_top5;
    ClassDef(Jet,2);
  };
  
  struct Muon {
  Muon() : pt(0.),eta(0.),phi(0.),hcalEta(0.),hcalPhi(0.) { }
    double type;        // type of muon (standalone/global/cosmic/regular)
    double pt;
    double eta;
    double phi;
    double hcalEta;     // track intersection with HCAL front-face (?)
    double hcalPhi;
    ClassDef(Muon,1);
  };
  
}

class StoppedHSCPEvent : public TObject {
 public:
  
  enum { MAX_N_TRIGJETS=10 };
  enum { MAX_N_MCDECAYS=10 };
  enum { MAX_N_JETS=20 };
  enum { MAX_N_MUONS=4 };
  enum { MAX_N_TOWERS=100 };
  enum { MAX_N_HPDS=10 };
  enum { MAX_N_DIGIS=100 };

 public:
  StoppedHSCPEvent();
  ~StoppedHSCPEvent();
  
  void setEventInfo(unsigned evt,
		    unsigned bx,
		    unsigned orbit,
		    unsigned ls,
		    unsigned run,
		    unsigned fill,
		    unsigned ts0,
		    unsigned ts1);

  void setTriggerInfo(unsigned gtTrigWord0,
		      unsigned gtTrigWord1,
		      unsigned l1BptxPlus,
		      unsigned l1BptxMinus,
		      unsigned hltBit);

  void addL1Jet(shscp::TrigJet j);
  void addHltJet(shscp::TrigJet j);
  void addJet(shscp::Jet j);
  void addMuon(shscp::Muon m);
  void addTower(shscp::Tower t);
  void addHPD(shscp::HPD h);
  void addDigi(shscp::HcalDigi d);

  void setMC(shscp::MC mcEvt);
  void addMCDecay(shscp::MCDecay d);

  // getters
  unsigned nL1Jets() { return nL1Jet; }
  unsigned nHltJets() { return nHltJet; }
  unsigned nJets() { return nJet; }
  unsigned nMuons() { return nMuon; }
  unsigned nTows() { return nTower; }
  unsigned nHpds() { return nHpd; }
  unsigned nDigis() { return nDigi; }

  shscp::TrigJet getL1Jet(unsigned i);
  shscp::TrigJet getHltJet(unsigned i);
  shscp::MCDecay getMCDecay(unsigned i);
  shscp::Jet getJet(unsigned i);
  shscp::Muon getMuon(unsigned i);
  shscp::Tower getTower(unsigned i);
  shscp::HPD getHPD(unsigned i);
  shscp::HcalDigi getDigi(unsigned i);

 private:

  shscp::Event event;

  shscp::Trigger trigger;

  shscp::MC mc;

  unsigned nL1Jet;
  shscp::TrigJet l1Jets[MAX_N_TRIGJETS];

  unsigned nHltJet;
  shscp::TrigJet hltJets[MAX_N_TRIGJETS];

  unsigned nMCDecay;
  shscp::MCDecay mcDecays[MAX_N_MCDECAYS];

  unsigned nJet;
  shscp::Jet jets[MAX_N_JETS];

  unsigned nMuon;
  shscp::Muon muons[MAX_N_MUONS];

  unsigned nTower;
  shscp::Tower towers[MAX_N_TOWERS];

  unsigned nHpd;
  shscp::HPD hpds[MAX_N_HPDS];

  unsigned nDigi;
  shscp::HcalDigi digis[MAX_N_DIGIS];

  ClassDef(StoppedHSCPEvent,2);

};

#endif