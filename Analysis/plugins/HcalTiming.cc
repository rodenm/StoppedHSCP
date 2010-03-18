// -*- C++ -*-
//
// Package:    HcalTiming
// Class:      HcalTiming
// 

//
// Original Author:  Kenneth Case Rossato
//         Created:  Fri Oct 17 16:17:21 CEST 2008
// $Id: HcalTiming.cc,v 1.2 2009/10/28 20:48:41 rossato Exp $
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

#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "DataFormats/HcalDigi/interface/HcalDigiCollections.h"

#include "TH1D.h"
#include "TH2D.h"

#include <list>

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
  TH1D *p1_to_p0;
  TH1D *p2_to_p1;
  TH2D *p2p1_vs_p1p0;
  TH1D *peak_location;
  TH1D *weighted_peak_location;
  TH1D *weighted_peak_location_2;
  TH2D *p1p0_vs_loc;
  TH1D *p0_to_total;
  TH1D *p0p1_to_total;
  TH1D *outer_to_total;
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

typedef std::pair<HBHEDigiCollection::const_iterator, double> DIGI;

bool lt(const DIGI &a, const DIGI &b) {
  return a.second < b.second;
}

// ------------ method called to for each event  ------------
void
HcalTiming::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   using namespace edm;

   Handle<HBHEDigiCollection> digis;
   iEvent.getByType(digis);
   std::list<DIGI> leading(5, DIGI(digis->begin(), 0));

   //   double leading_total[5] = {0,0,0,0,0};
   //   HBHEDigiCollection::const_iterator leading_index[5];

   for (HBHEDigiCollection::const_iterator cit = digis->begin();
	cit != digis->end(); cit++) {
     
     double running_total = 0;
     for (int i = 0; i < cit->size(); i++)
       running_total += cit->sample(i).nominal_fC();
     
     leading.push_front(DIGI(cit, running_total));
     leading.sort();
     leading.pop_front();
   }

   std::vector<double> sumTopFive(digis->begin()->size(), 0);
   for (std::list<DIGI>::const_iterator cit = leading.begin();
	cit != leading.end(); cit++)
     for (unsigned int j = 0; j < sumTopFive.size(); j++)
       sumTopFive[j] += cit->first->sample(j).nominal_fC();

   unsigned int peak = 0;
   double p0 = 0;
   double last = 0;
   //   double first = sumTopFive[0];
     //leading_index->sample(0).nominal_fC();
   double total = 0;
   for (unsigned int i = 0; i < sumTopFive.size(); i++) {
     if (sumTopFive[i] > p0) {
       peak = i; p0 = sumTopFive[i];
     }
     leading_digi->Fill(i, sumTopFive[i]);
     last = sumTopFive[i];
     total += last;
   }
   double outer_total = 0;
   for (unsigned int i = 0; i < sumTopFive.size(); i++) {
     if ( i < peak - 1 || i > peak + 2)
       outer_total += sumTopFive[i];
   }
   outer_to_total->Fill(outer_total / total);

   double p1 = 0;
   double p2 = 0;
   p0_to_total->Fill(p0 / total);
   if (peak < sumTopFive.size() - 1) {
     p1 = sumTopFive[peak + 1];
     p1_to_p0->Fill(p1 / p0);
     p0p1_to_total->Fill((p0 + p1)/total);
     p1p0_vs_loc->Fill(peak, p1 / p0);
   }
   if (peak < sumTopFive.size() - 2) {
     p2 = sumTopFive[peak + 2];
     p2_to_p1->Fill(p2 / p1);
     p2p1_vs_p1p0->Fill(p1 / p0, p2 / p1);
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
    p1_to_p0 = fs->make<TH1D>("p1_to_p0", "Peak-plus-one to peak",
			      100, 0, 1);
    p2_to_p1 = fs->make<TH1D>("p2_to_p1", "Peak-plus-two to peak-plus-one",
			      100, 0, 1);
    p2p1_vs_p1p0 = fs->make<TH2D>("p2p1_vs_p1p0", "Peak-plus-2 to -1 vs -1 to -0",
				  100, 0, 1, 100, 0, 1);
    peak_location = fs->make<TH1D>("peak_location", "Location of the peak of the leading digi", 10, -.5, 9.5);
    p1p0_vs_loc = fs->make<TH2D>("p1p0_vs_loc", "Peak-plus-one-to-peak ratio against Peak location", 10, -.5, 9.5, 100, 1, 1);
    weighted_peak_location = fs->make<TH1D>("weighted_peak_location", "Peak Location weighted by peak height", 10, -.5, 9.5);
    weighted_peak_location_2 = fs->make<TH1D>("weighted_peak_location_2", "Peak Location weighted by peak height^2", 10, -.5, 9.5);

    p0_to_total   = fs->make<TH1D>("p0_to_total", "Peak over total",
				   100, 0, 1);
    p0p1_to_total = fs->make<TH1D>("p0p1_to_total", "Peak and neighbor over total",
				   100, 0, 1);
    outer_to_total = fs->make<TH1D>("outer_to_total", "Outer bins over total",
				    100, 0, 1);
    lumi_segments = fs->make<TH1D>("lumi_segments", "Occupancy per Lumi Section", 100, 0, 100);
}

// ------------ method called once each job just after ending the event loop  ------------
void 
HcalTiming::endJob() {
}

//define this as a plug-in
DEFINE_FWK_MODULE(HcalTiming);
