// -*- C++ -*-
//
// Package:    MCStoppedEventFilter
// Class:      MCStoppedEventFilter
// 
/**\class MCStoppedEventFilter MCStoppedEventFilter.cc 

 Description: This filter requires that there is at least one stopped point in order
              to continue processing.

 Implementation: Checks the length of StoppedParticlesX for this event. If > 0, returns true.
    
*/
//
// Original Author:  Marissa Rodenburg
//         Created:  Fri Oct 21 09:18:50 EDT 2011
// $Id$


// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDFilter.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"

//
// class declaration
//

class MCStoppedEventFilter : public edm::EDFilter {
public:
  explicit MCStoppedEventFilter(const edm::ParameterSet&);
  ~MCStoppedEventFilter();
  
  static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);
  
private:
  virtual void beginJob() ;
  virtual bool filter(edm::Event&, const edm::EventSetup&);
  virtual void endJob() ;
  
  virtual bool beginRun(edm::Run&, edm::EventSetup const&);
  virtual bool endRun(edm::Run&, edm::EventSetup const&);
  virtual bool beginLuminosityBlock(edm::LuminosityBlock&, edm::EventSetup const&);
  virtual bool endLuminosityBlock(edm::LuminosityBlock&, edm::EventSetup const&);
  
  // ----------member data ---------------------------
  std::string mStopPointProducer_;
  //edm::InputTag stoppedParticlesXLabel_;
};

//
// constructors and destructor
//
MCStoppedEventFilter::MCStoppedEventFilter(const edm::ParameterSet& iConfig) :
  mStopPointProducer_(iConfig.getUntrackedParameter<std::string>("stopPointInputTag", "g4SimHits"))
{
  //stoppedParticlesXLabel_ = iConfig.getParameter<edm::InputTag>("StoppedParticlesXLabel");
}


MCStoppedEventFilter::~MCStoppedEventFilter() {}


//
// member functions
//

// ------------ method called on each new Event  ------------
bool
MCStoppedEventFilter::filter(edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  edm::Handle<std::vector<float> > xs;
  iEvent.getByLabel(mStopPointProducer_, "StoppedParticlesX", xs);
  if (xs->size() > 0)
    return true;
  else
    return false;
}

// ------------ method called once each job just before starting event loop  ------------
void MCStoppedEventFilter::beginJob() {}

// ------------ method called once each job just after ending the event loop  ------------
void MCStoppedEventFilter::endJob() {}

// ------------ method called when starting to processes a run  ------------
bool MCStoppedEventFilter::beginRun(edm::Run&, edm::EventSetup const&) { 
  return true;
}

// ------------ method called when ending the processing of a run  ------------
bool MCStoppedEventFilter::endRun(edm::Run&, edm::EventSetup const&) {
  return true;
}

// ------------ method called when starting to processes a luminosity block  ------------
bool MCStoppedEventFilter::beginLuminosityBlock(edm::LuminosityBlock&, edm::EventSetup const&) {
  return true;
}

// ------------ method called when ending the processing of a luminosity block  ------------
bool MCStoppedEventFilter::endLuminosityBlock(edm::LuminosityBlock&, edm::EventSetup const&) {
  return true;
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void MCStoppedEventFilter::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}
//define this as a plug-in
DEFINE_FWK_MODULE(MCStoppedEventFilter);
