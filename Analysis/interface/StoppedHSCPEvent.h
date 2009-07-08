#ifndef StoppedHSCPEvent_h
#define StoppedHSCPEvent_h

#include <vector>
#include "TObject.h"

//#include "StoppedHSCP/Analysis/interface/StoppedHSCPJet.h"

namespace shscp {
  struct Event {
  Event() : id(0),bx(0),orbit(0),lumisection(0),run(0),fill(0),timestamp(0) {}
    unsigned id;
    unsigned bx;
    unsigned orbit;
    unsigned lumisection;
    unsigned run;
    unsigned fill;
    unsigned timestamp;
    ClassDef(Event,1);
  };
  
  struct MC {
  MC() : vtxX(0.),vtxY(0.),vtxZ(0.),vtxR(0.),vtxT(0.),rHadPDG(0),eJet(0.),ptJetX(0.),ptJetY(0.),ptJetZ(0.),ptJetR(0.) { } 
    double vtxX;
    double vtxY;
    double vtxZ;
    double vtxR;
    double vtxT;
    unsigned rHadPDG;
    double eJet;
    double ptJetX;
    double ptJetY;
    double ptJetZ;
    double ptJetR;
    ClassDef(MC,1);
  };
  
  struct Tower {
  Tower() : e(0.),et(0.),eta(0.),phi(0.),ieta(0),iphi(0),eHad(0.),etHad(0.),eEm(0.),etEm(0.) { }
    double e;
    double et;
    double eta;
    double phi;
    unsigned ieta;
    unsigned iphi;
    double eHad;
    double etHad;
    double eEm;
    double etEm;
    ClassDef(Tower,1);
  };
  
  struct HPD {
  HPD() : id(0),totalZeros(0),maxZeros(0),
      fcBx0(0.),fcBx1(0.),fcBx2(0.),fcBx3(0.),fcBx4(0.),fcBx5(0.),fcBx6(0.),fcBx7(0.),fcBx8(0.),fcBx9(0.),
      fc5Bx0(0.),fc5Bx1(0.),fc5Bx2(0.),fc5Bx3(0.),fc5Bx4(0.),fc5Bx5(0.),fc5Bx6(0.),fc5Bx7(0.),fc5Bx8(0.),fc5Bx9(0.) { }
    unsigned id;
    unsigned totalZeros;
    unsigned maxZeros;
    double fcBx0;
    double fcBx1;
    double fcBx2;
    double fcBx3;
    double fcBx4;
    double fcBx5;
    double fcBx6;
    double fcBx7;
    double fcBx8;
    double fcBx9;
    double fc5Bx0;
    double fc5Bx1;
    double fc5Bx2;
    double fc5Bx3;
    double fc5Bx4;
    double fc5Bx5;
    double fc5Bx6;
    double fc5Bx7;
    double fc5Bx8;
    double fc5Bx9;
    ClassDef(HPD,1);
  };
  
  struct RBX {
  RBX() : id(0),totalZeros(0),maxZeros(0),
      fcAllBx0(0.),fcAllBx1(0.),fcAllBx2(0.),fcAllBx3(0.),fcAllBx4(0.),
      fcAllBx5(0.),fcAllBx6(0.),fcAllBx7(0.),fcAllBx8(0.),fcAllBx9(0.) { }
    unsigned id;
    unsigned totalZeros;
    unsigned maxZeros;
    double fcAllBx0;
    double fcAllBx1;
    double fcAllBx2;
    double fcAllBx3;
    double fcAllBx4;
    double fcAllBx5;
    double fcAllBx6;
    double fcAllBx7;
    double fcAllBx8;
    double fcAllBx9;
    ClassDef(RBX,1);
  };
  
  struct Jet {
  Jet() : e(0.),et(0.),eta(0.),phi(0.),eHad(0.),eEm(0.),eMaxEcalTow(0.),eMaxHcalTow(0.),n60(0),n90(0) { }
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
    ClassDef(Jet,1);
  };
  
  struct Muon {
  Muon() : pt(0.),eta(0.),phi(0.),hcalEta(0.),hcalPhi(0.) { }
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
  
  enum { MAX_N_TOWERS=50 };
  enum { MAX_N_HPDS=10 };
  enum { MAX_N_RBXS=10 };
  enum { MAX_N_JETS=10 };
  enum { MAX_N_MUONS=4 };

 public:
  StoppedHSCPEvent();
  ~StoppedHSCPEvent();
  
  void setEventInfo(unsigned e,
		    unsigned b,
		    unsigned o,
		    unsigned ls,
		    unsigned r,
		    unsigned f,
		    unsigned ts);

  void addTower(shscp::Tower t);
  void addHPD(shscp::HPD h);
  void addRBX(shscp::RBX r);
  void addJet(shscp::Jet j);
  void addMuon(shscp::Muon m);

  void setMC(shscp::MC mcEvt);

  // getters
  unsigned nTow() { return nTowers; }
  unsigned nHpd() { return nHpds; }
  unsigned nRbx() { return nRbxs; }
  unsigned nJet() { return nJets; }
  unsigned nMuon() { return nMuons; }

 private:

  shscp::Event event;

  shscp::MC mc;

  unsigned nTowers;
  shscp::Tower towers[MAX_N_TOWERS];

  unsigned nHpds;
  shscp::HPD hpds[MAX_N_HPDS];

  unsigned nRbxs;
  shscp::RBX rbxs[MAX_N_RBXS];

  unsigned nJets;
  shscp::Jet jets[MAX_N_JETS];

  unsigned nMuons;
  shscp::Muon muons[MAX_N_MUONS];

  ClassDef(StoppedHSCPEvent,1);

};

#endif
