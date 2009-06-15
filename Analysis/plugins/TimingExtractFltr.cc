// -*- C++ -*-
//
// Package:    TimingExtractFltr
// Class:      TimingExtractFltr
// 
/**\class TimingExtractFltr TimingExtractFltr.cc GluinoFilter/TimingExtractFltr/src/TimingExtractFltr.cc

 Description: <one line class summary>

 Implementation:
     <Notes on implementation>
*/
//
// Original Author:  Benjamin JONES
//         Created:  Wed Jan 28 23:34:31 CET 2009
// $Id: TimingExtractFltr.cc,v 1.1 2009/04/17 14:30:53 bjones Exp $
//
//


// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDFilter.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include <fstream>
#include <iostream>


//
// class declaration
//

class TimingExtractFltr : public edm::EDFilter {
   public:
      explicit TimingExtractFltr(const edm::ParameterSet&);
      ~TimingExtractFltr();

   private:
      virtual void beginJob(const edm::EventSetup&) ;
      virtual bool filter(edm::Event&, const edm::EventSetup&);
      virtual void endJob() ;
  std::ifstream EventList;
  std::map<long,bool> Keepers;
  edm::FileInPath InputFile_;
      
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
TimingExtractFltr::TimingExtractFltr(const edm::ParameterSet& iConfig):
  InputFile_(iConfig.getParameter<edm::FileInPath>("InputFile"))
{
   //now do what ever initialization is needed
 

  char Buf[1024];
  int EventID, RunID;
  EventList.open(InputFile_.fullPath().c_str());
  std::cout<<"ATTEMPTING TO OPEN FILE " << InputFile_.fullPath()<<std::endl;
  if(EventList.is_open())
    {
      do 
	{
	  EventList.getline(Buf,1023);
	  sscanf(Buf,"%i,%i",&EventID,&RunID);
	  std::cout<<"Run : " <<RunID <<" Event : " <<EventID << std::endl;
	  Keepers[EventID]=true;
	} while (!EventList.eof());
      EventList.close();
    }
  else
    {
      EventList.close();
      std::cout<<"ERROR : NO FILE FOUND"<<std::endl;
    }
}


TimingExtractFltr::~TimingExtractFltr()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called on each new Event  ------------
bool
TimingExtractFltr::filter(edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   using namespace edm;
   
   if(Keepers[iEvent.id().event()])
     {
       return true;
       std::cout<<"Event " << iEvent.id().event() << " passed"<<std::endl;
     }
   else 
     return false;
}

// ------------ method called once each job just before starting event loop  ------------
void 
TimingExtractFltr::beginJob(const edm::EventSetup&)
{
}

// ------------ method called once each job just after ending the event loop  ------------
void 
TimingExtractFltr::endJob() {
}

//define this as a plug-in
DEFINE_FWK_MODULE(TimingExtractFltr);
