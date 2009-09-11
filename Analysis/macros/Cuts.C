// define cuts in one place for convenience

#include <iostream>

// custom headers
#include "interface/StoppedHSCPEvent.h"

// cut values
double CutJetEnergyCut = 50.;
double CutJetEtaCut = 1.3;
double CutJetN60Cut = 6.;
double CutJetN90Cut = 3.;
double CutMuonVeto = 1.;

// give this method a binary number with a 1 for each cut to apply
// eg.  0x1 will evaluate the 1st cut, 0x3 will evaluate 1st and 2nd, etc.
bool Cut(StoppedHSCPEvent* evt, unsigned cuts) {

  bool result=true;

  if ((cuts & 0x1) > 0) result = result && (evt->getJet(0).e > CutJetEnergyCut);
  if ((cuts & 0x2) > 0) result = result && (fabs(evt->getJet(0).eta) < CutJetEtaCut);
  if ((cuts & 0x4) > 0) result = result && (evt->getJet(0).n60 < CutJetN60Cut);
  if ((cuts & 0x8) > 0) result = result && (evt->getJet(0).n90 > CutJetN90Cut);
  if ((cuts & 0x10) > 0) result = result && (evt->nMuon() < CutMuonVeto);

 if (cuts & 0x1e0 > 0) {

    // sum 5 highest digis
    double fc[11]={ 0., 0., 0., 0., 0., 0., 0., 0., 0., 0., 0. };
    for (unsigned i=0; i<5; ++i) {
      fc[0] += evt->getDigi(i).fc0;  // ugly because ROOT seems to screw up an array :-(
      fc[1] += evt->getDigi(i).fc1;
      fc[2] += evt->getDigi(i).fc2;
      fc[3] += evt->getDigi(i).fc3;
      fc[4] += evt->getDigi(i).fc4;
      fc[5] += evt->getDigi(i).fc5;
      fc[6] += evt->getDigi(i).fc6;
      fc[7] += evt->getDigi(i).fc7;
      fc[8] += evt->getDigi(i).fc8;
      fc[9] += evt->getDigi(i).fc9;
    }
    
    // find peak and total
    unsigned npeak=0;
    double peakval=0.;
    double totval=0.;
    for (unsigned i=0; i<10; ++i) {
      totval += fc[i];
      if (fc[i] > peakval) {
	npeak=i;
	peakval=fc[i];
      }
    }
    double outval=fc[0]+fc[1]+fc[2]+fc[7]+fc[8]+fc[9];
    
    // calculate ratios
    double r1 = fc[npeak+1]/fc[npeak];
    double r2 = fc[npeak+2]/fc[npeak+1];
    double peakfrac = peakval/totval;
    double outfrac = outval/totval;
    
    if ((cuts & 0x20) > 0) result = result && (r1 > 0.15 && r2 > 0.1);
    if ((cuts & 0x40) > 0) result = result && (r2 > 0.5);
    if ((cuts & 0x80) > 0) result = result && (peakfrac > 0.4 && peakfrac < 0.7);
    if ((cuts & 0x100) > 0) result = result && (outfrac < 0.1);
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
