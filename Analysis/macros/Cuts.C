// define cuts in one place for convenience

// custom headers
#include "interface/StoppedHSCPEvent.h"

// cut values
double CutJetEtaCut = 1.3;
double CutJetN60Cut = 6.;
double CutJetN90Cut = 3.;
double CutJetEnergyCut = 50.;
double CutMuonVeto = 1.;


bool JetCuts(StoppedHSCPEvent* evt) {
  if (evt->getJet(0).eta < CutJetEtaCut &&
      evt->getJet(0).n60 < CutJetN60Cut &&
      evt->getJet(0).n90 > CutJetN90Cut &&
      evt->getJet(0).e > CutJetEnergyCut) return true;
  else return false;
}

bool MuonCuts(StoppedHSCPEvent* evt) {
  if (evt->nMuon() < CutMuonVeto) return true;
  else return false;
}

// timing cuts a la Ben
// sum 5 "highest" digis, then calculate peak+1/peak ratios etc
bool TimingCuts(StoppedHSCPEvent* evt) {

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

  if (r1 > 0.15 &&
      r2 > 0.1 &&
      r2 < 0.5 &&
      peakfrac > 0.4 &&
      peakfrac < 0.7 &&
      outfrac < 0.1) return true;
  else return false;
}

bool AllCuts(StoppedHSCPEvent* evt) {
  return JetCuts(evt) && MuonCuts(evt) && TimingCuts(evt);
}
