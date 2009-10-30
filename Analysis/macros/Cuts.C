// define cuts in one place for convenience

#include <iostream>

// custom headers
#include "interface/StoppedHSCPEvent.h"
#include "interface/PulseShape.h"


// cut values
double CutJetEnergyCut = 50.;
double CutJetEtaCut = 1.3;
double CutJetN60Cut = 6.;
double CutJetN90Cut = 3.;
double CutMuonVeto = 1.;

double CutR1Min = 0.15;
double CutR1Max = 1.0;
double CutR2Min = 0.1;
double CutR2Max = 0.5;
double CutRPMin = 0.4;
double CutRPMax = 0.7;
double CutROMin = 0.0;
double CutROMax = 0.1;


// give this method a binary number with a 1 for each cut to apply
// eg.  0x1 will evaluate the 1st cut, 0x3 will evaluate 1st and 2nd, etc.
bool Cut(StoppedHSCPEvent* evt, unsigned cuts) {

  bool result=true;

  if ((cuts & 0x1) > 0) {
    for (unsigned i=0; i<evt->nJets(); ++i) {
      if (evt->getJet(i).e > CutJetEnergyCut &&
	  evt->getJet(i).eta < CutJetEtaCut) result = result && true;
    }
  }

  if ((cuts & 0x4) > 0) result = result && (evt->getJet(0).n60 < CutJetN60Cut);
  if ((cuts & 0x8) > 0) result = result && (evt->getJet(0).n90 > CutJetN90Cut);
  if ((cuts & 0x10) > 0) result = result && (evt->nMuons() < CutMuonVeto);

  if (cuts & 0x1e0 > 0) {
    
    PulseShape ps;
    ps.addJet(evt, 0);
    double r1 = ps.getP1ToP0();
    double r2 = ps.getP2ToP1();
    double rp = ps.getP0ToTotal();
    double ro = ps.getOuterToTotal();

    if ((cuts & 0x20) > 0) result = result && (r1 > CutR1Min && r1 < CutR1Max);
    if ((cuts & 0x40) > 0) result = result && (r2 > CutR2Min && r2 < CutR2Max);
    if ((cuts & 0x80) > 0) result = result && (rp > CutRPMin && rp < CutRPMax);
    if ((cuts & 0x100) > 0) result = result && (ro > CutROMin && ro < CutROMax);
  }
  
  return result;
  
}

bool JetCuts(StoppedHSCPEvent* evt) {
  return Cut(evt, 0xf);
}

bool MuonCuts(StoppedHSCPEvent* evt) {
  return Cut(evt, 0x10);
}

bool JetAndMuonCuts(StoppedHSCPEvent* evt) {
  return Cut(evt, 0x1f);
}


// timing cuts a la Ben
// sum 5 "highest" digis, then calculate peak+1/peak ratios etc
bool TimingCuts(StoppedHSCPEvent* evt) {
  return Cut(evt, 0x1e0);
}

bool AllCuts(StoppedHSCPEvent* evt) {
  return Cut(evt, 0x1ff);
}
