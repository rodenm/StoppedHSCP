// define cuts in one place for convenience

// custom headers
#include "interface/StoppedHSCPEvent.h"

// cut values
double offJetEtaCut = 1.3;
double offJetN60Cut = 6;
double offJetN90Cut = 3;
double offJetEnergyCut = 50;
double offMuonVeto = 1;

bool ApplyAllCuts(StoppedHSCPEvent* evt) {

  if (evt->getJet(0).eta < offJetEtaCut &&
      evt->getJet(0).n60 < offJetN60Cut &&
      evt->getJet(0).n90 > offJetN90Cut &&
      evt->getJet(0).e < offJetEnergyCut &&
      evt->nMuon() < offMuonVeto) {
    return true;
  }
  else {
    return false;
  }

}
