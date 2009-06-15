#include "Workspace/ConfigurableAnalysis/interface/StringBasedNTupler.h"

#include "DataFormats/PatCandidates/interface/Jet.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/MET.h"
#include "DataFormats/PatCandidates/interface/Electron.h"
#include "DataFormats/PatCandidates/interface/Photon.h"
#include "DataFormats/PatCandidates/interface/Tau.h"
#include "DataFormats/PatCandidates/interface/Hemisphere.h"

#include "SimDataFormats/Track/interface/SimTrack.h"

#include "DataFormats/HepMCCandidate/interface/GenParticle.h"

#include "DataFormats/HcalDigi/interface/HBHEDataFrame.h"
#include "DataFormats/JetReco/interface/CaloJet.h"
#include "DataFormats/CaloTowers/interface/CaloTower.h"
#include "DataFormats/METReco/interface/HcalNoiseSummary.h"
#include "DataFormats/METReco/interface/HcalNoiseHPD.h"
#include "DataFormats/METReco/interface/HcalNoiseRBX.h"

//------------------------------------------------------------------------------
//just define here a list of objects you would like to be able to have a branch 
//------------------------------------------------------------------------------
#define ANOTHER_CLASS(C) if (class_==#C) return StringBranchHelper<C>(*this, iEvent)()

TreeBranch::value TreeBranch::branch(const edm::Event& iEvent){
  ANOTHER_CLASS(reco::Muon);
  else ANOTHER_CLASS(reco::CaloJet);
  else ANOTHER_CLASS(reco::GenParticle);
  else ANOTHER_CLASS(HBHEDataFrame);
  else ANOTHER_CLASS(CaloTower);
  else ANOTHER_CLASS(HcalNoiseSummary);
  else ANOTHER_CLASS(reco::HcalNoiseHPD);
  else ANOTHER_CLASS(reco::HcalNoiseRBX);
  else {
    edm::LogError("TreeBranch")<<branchName()<<" failed to recognized class type : "<<class_;
    return TreeBranch::value(new std::vector<float>());
  }
}
#undef ANOTHER_CLASS

#include "FWCore/PluginManager/interface/ModuleDef.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/Framework/interface/ModuleFactory.h"
#include "FWCore/ServiceRegistry/interface/ServiceMaker.h"

DEFINE_SEAL_MODULE();


#include "DataFormats/HepMCCandidate/interface/GenParticleFwd.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "PhysicsTools/UtilAlgos/interface/ObjectSelector.h"
#include "PhysicsTools/UtilAlgos/interface/SortCollectionSelector.h"
#include "PhysicsTools/Utilities/interface/PtComparator.h"

typedef ObjectSelector<SortCollectionSelector<reco::GenParticleCollection,GreaterByPt<reco::GenParticle> > > GenParticleSorterByPt;

DEFINE_FWK_MODULE(GenParticleSorterByPt);

//#include "Workspace/ConfigurableAnalysis/interface/ProcessIdSplitter.h"
//DEFINE_EDM_PLUGIN(CachingVariableFactory, ProcessIdSplitter, "ProcessIdSplitter");


#include "Workspace/ConfigurableAnalysis/interface/StringBasedNTupler.h"
DEFINE_EDM_PLUGIN(NTuplerFactory, StringBasedNTupler, "StringBasedNTupler");
