
// define TChain in one place for convenience

#include "TChain.h"

TChain* Chain() {

  TChain* chain = new TChain("stoppedHSCPTree/StoppedHSCPTree");
  chain->Add("/castor/cern.ch/cms/store/caf/user/jbrooke/CRAFT09_v3/CRAFT09_v3_1.root");
  chain->Add("/castor/cern.ch/cms/store/caf/user/jbrooke/CRAFT09_v3/CRAFT09_v3_2.root");
  
  return chain;

}
