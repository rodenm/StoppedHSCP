// -*- C++ -*-
//
// Package:    TimingExtract
// Class:      TimingExtract
// 
/**\class TimingExtract TimingExtract.cc GluinoAnalyzers/TimingExtract/src/TimingExtract.cc

 Description: <one line class summary>

 Implementation:
     <Notes on implementation>
*/
//
// Original Author:  Benjamin Jones
//         Created:  Wed Jan 28 17:01:48 CET 2009
// $Id: TimingExtract.cc,v 1.1 2009/04/17 14:30:53 bjones Exp $
//
//


// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include <fstream>
#include <iostream>

//
// class decleration
//

class TimingExtract : public edm::EDAnalyzer {
   public:
      explicit TimingExtract(const edm::ParameterSet&);
      ~TimingExtract();


   private:
      virtual void beginJob(const edm::EventSetup&) ;
      virtual void analyze(const edm::Event&, const edm::EventSetup&);
      virtual void endJob() ;
      std::ofstream EventList;
      std::string FileName_;
  // ----------member data ---------------------------
};

//
// constants, enums and typedefs
//

//
// static data member definitions
//

//
// constructors and destructor
//
TimingExtract::TimingExtract(const edm::ParameterSet& iConfig):
  FileName_(iConfig.getUntrackedParameter("FileName",std::string("EventList.txt")))

{
   //now do what ever initialization is needed
  EventList.open(FileName_.c_str());
}

TimingExtract::~TimingExtract()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)
  EventList.close();
}


//
// member functions
//

// ------------ method called to for each event  ------------
void
TimingExtract::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   using namespace edm;
   EventList << iEvent.id().event() << ",";
   EventList << iEvent.id().run() << std::endl;
}





// ------------ method called once each job just before starting event loop  ------------
void 
TimingExtract::beginJob(const edm::EventSetup&)
{
}

// ------------ method called once each job just after ending the event loop  ------------
void 
TimingExtract::endJob() {
}

//define this as a plug-in
DEFINE_FWK_MODULE(TimingExtract);
