
#include "FWCore/PluginManager/interface/ModuleDef.h"
#include "FWCore/Framework/interface/MakerMacros.h"
DEFINE_SEAL_MODULE ();

#include "SimG4Core/Watcher/interface/SimWatcherFactory.h"
#include "RHStopTracer.h"
DEFINE_SIMWATCHER(RHStopTracer);

#include "RHDecay.h"
DEFINE_ANOTHER_FWK_MODULE(RHDecay);
