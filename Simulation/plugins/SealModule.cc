#include "FWCore/PluginManager/interface/ModuleDef.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "SimG4Core/Watcher/interface/SimWatcherFactory.h"

#include "RHDecay.h"
#include "RHStopTracer.h"
#include "Stage2Watcher.h"


//DEFINE_SEAL_MODULE ();

DEFINE_FWK_MODULE(RHDecay) ;
DEFINE_SIMWATCHER(RHStopTracer);
DEFINE_SIMWATCHER(Stage2Watcher);
