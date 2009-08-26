
// define TChain in one place for convenience

#include "TChain.h"

TChain* Chain() {

  //  TChain* chain = new TChain("stoppedHSCPTree/StoppedHSCPTree");
  //  chain->Add("CRAFT09_v3_1.root");
  //  chain->Add("CRAFT09_v3_2.root");

  TChain* chain = new TChain("StoppedHSCPTree");
  chain->Add("SelectedEvents.root");
  
  return chain;

}
