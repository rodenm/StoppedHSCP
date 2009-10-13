// -*- C++ -*-
//
// Package:    HcalTiming
// Class:      HcalTiming
// 

//
// Original Author:  Kenneth Case Rossato
//         Created:  Fri Oct 17 16:17:21 CEST 2008
// $Id: HcalTiming.cc,v 1.1 2009/10/13 20:15:38 jbrooke Exp $
// Copied and became HcalTiming.cc 2009/01/21
// 


// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "FWCore/ServiceRegistry/interface/Service.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "FWCore/Framework/interface/EventSetup.h"

#include "PhysicsTools/UtilAlgos/interface/TFileService.h"
#include "DataFormats/HcalDigi/interface/HcalDigiCollections.h"

#include "TH1D.h"
#include "TH2D.h"

//
// class decleration
//

class HcalTiming : public edm::EDAnalyzer {
   public:
      explicit HcalTiming(const edm::ParameterSet&);
      ~HcalTiming();


   private:
      virtual void beginJob(const edm::EventSetup&) ;
      virtual void analyze(const edm::Event&, const edm::EventSetup&);
      virtual void endJob() ;

  //  unsigned int getFibNOrbMsgBCN(const HcalHTRData &, int);
      // ----------member data ---------------------------

  edm::Service<TFileService> fs;

  TH1D *leading_digi;
  TH1D *p0_to_p1;
  TH1D *p1_to_p2;
  TH2D *p0p1_vs_p1p2;
  TH1D *peak_location;
  TH1D *weighted_peak_location;
  TH1D *weighted_peak_location_2;
  TH2D *p0p1_vs_loc;
  TH1D *p0p1_to_total;
  TH1D *lumi_segments;

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
HcalTiming::HcalTiming(const edm::ParameterSet& iConfig)
{
   //now do what ever initialization is needed


}


HcalTiming::~HcalTiming()
{
 
   // do anything here that needs to be done at desctruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

/*
unsigned int HcalTiming::getFibNOrbMsgBCN(const HcalHTRData &htr, int n) {

  switch (n) {
  case 1:
    return htr.getFib1OrbMsgBCN(); break;
  case 2:
    return htr.getFib2OrbMsgBCN(); break;
  case 3:
    return htr.getFib3OrbMsgBCN(); break;
  case 4:
    return htr.getFib4OrbMsgBCN(); break;
  case 5:
    return htr.getFib5OrbMsgBCN(); break;
  case 6:
    return htr.getFib6OrbMsgBCN(); break;
  case 7:
    return htr.getFib7OrbMsgBCN(); break;
  case 8:
    return htr.getFib8OrbMsgBCN(); break;
  }

  throw std::range_error("Fiber number not 1-8");
  return 0;
}
*/

// ------------ method called to for each event  ------------
void
HcalTiming::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   using namespace edm;

   Handle<HBHEDigiCollection> digis;
   iEvent.getByType(digis);
   double leading_total = 0;
   HBHEDigiCollection::const_iterator leading_index;

   for (HBHEDigiCollection::const_iterator cit = digis->begin();
	cit != digis->end(); cit++) {
     
     double running_total = 0;
     for (int i = 0; i < cit->size(); i++)
       running_total += cit->sample(i).nominal_fC();

     if (running_total > leading_total) {
       leading_total = running_total;
       leading_index = cit;
     }
   }

   int peak = 0;
   double p0 = 0;
   double total = 0;
   for (int i = 0; i < leading_index->size(); i++) {
     if (leading_index->sample(i).nominal_fC() > p0) {
       peak = i; p0 = leading_index->sample(i).nominal_fC();
     }
     leading_digi->Fill(i, leading_index->sample(i).nominal_fC());
     if (i != 0 && i != 9)
       total += leading_index->sample(i).nominal_fC();
   }
   double p1 = 0;
   double p2 = 0;
   if (peak < leading_index->size() - 1) {
     p1 = leading_index->sample(peak + 1).nominal_fC();
     p0_to_p1->Fill(p0 / p1);
     p0p1_to_total->Fill((p0 + p1)/total);
     p0p1_vs_loc->Fill(peak, p0 / p1);
   }
   if (peak < leading_index->size() - 2) {
     p2 = leading_index->sample(peak + 2).nominal_fC();
     p1_to_p2->Fill(p1 / p2);
     p0p1_vs_p1p2->Fill(p0 / p1, p1 / p2);
   }
   peak_location->Fill(peak);
   weighted_peak_location->Fill(peak, p0);
   weighted_peak_location_2->Fill(peak, p0*p0);

   lumi_segments->Fill(iEvent.luminosityBlock());
}


// ------------ method called once each job just before starting event loop  ------------
void 
HcalTiming::beginJob(const edm::EventSetup&iSetup)
{    

    leading_digi = fs->make<TH1D>("leading_digi", "ADCs for the Leading Digi",
				  10, -.5, 9.5);
    p0_to_p1 = fs->make<TH1D>("p0_to_p1", "Peak to peak-plus-one",
			      100, 0, 20);
    p1_to_p2 = fs->make<TH1D>("p1_to_p2", "Peak-plus-one to peak-plus-two",
			      100, 0, 20);
    p0p1_vs_p1p2 = fs->make<TH2D>("p0p1_vs_p1p2", "P0-P1-P2 discrimination",
				  100, 0, 20, 100, 0, 20);
    peak_location = fs->make<TH1D>("peak_location", "Location of the peak of the leading digi", 10, -.5, 9.5);
    p0p1_vs_loc = fs->make<TH2D>("p0p1_vs_loc", "Peak-to-plus-one ratio against Peak location", 10, -.5, 9.5, 100, 0, 20);
    weighted_peak_location = fs->make<TH1D>("weighted_peak_location", "Peak Location weighted by peak height", 10, -.5, 9.5);
    weighted_peak_location_2 = fs->make<TH1D>("weighted_peak_location_2", "Peak Location weighted by peak height^2", 10, -.5, 9.5);

    p0p1_to_total = fs->make<TH1D>("p0p1_to_total", "Peak and neighbor over all-but-0/9",
				   20, 0, 1);
    lumi_segments = fs->make<TH1D>("lumi_segments", "Occupancy per Lumi Section", 100, 0, 100);
}

// ------------ method called once each job just after ending the event loop  ------------
void 
HcalTiming::endJob() {
}

//define this as a plug-in
DEFINE_FWK_MODULE(HcalTiming);
