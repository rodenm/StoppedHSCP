#include "StoppedHSCP/ToyMC/interface/Simulator.h"

#include "StoppedHSCP/Statistics/interface/CLsCountingExperiment.h"
#include "StoppedHSCP/Statistics/interface/CL95CMSCountingExperiment.h"

#include "TMath.h"
#include <assert.h>
#include <iostream>

static const unsigned int NBXS_PER_ORBIT = 3564;
static const unsigned int NORBITS_PER_LS = 262144; //2^18

static const double TIME_PER_BUNCH = 25e-9;
static const double TIME_PER_ORBIT = TIME_PER_BUNCH * NBXS_PER_ORBIT;
static const double TIME_PER_LS = TIME_PER_BUNCH * NBXS_PER_ORBIT * NORBITS_PER_LS;


Simulator::Simulator() :
  random_(),
  expt_(0),
  fills_(),
  lumi_(),
  events_(),
  nColls_(0),
  nMasks_(0),
  collisions_(NBXS_PER_ORBIT, false),
  masks_(NBXS_PER_ORBIT, false),
  lifetimeMasks_(NBXS_PER_ORBIT, false),
  tree_("events", "Event time structure")
{
  tree_.Branch("ls", &ls_, "ls/I");
  tree_.Branch("orbit", &orbit_, "orbit/I");
  tree_.Branch("bx", &bx_, "bx/I");

}


Simulator::~Simulator() { }


void Simulator::setParameters(Experiment* e) {
  expt_ = e;
}


void Simulator::setupObservedEvents() {
  events_ = Events(expt_->eventsFile);
}


void Simulator::setupLumi() {

  // get runs for all fills
  std::vector<unsigned long> runs;
  for (unsigned i=0; i<expt_->fills.size(); ++i) {
    std::vector<unsigned long> r = fills_.getRuns(expt_->fills.at(i));
    runs.insert(runs.end(),r.begin(), r.end());
  }	

  // build lumi from runs
  //lumi_.buildFromFile(runs, false, expt_->jsonFile, expt_->lumiFirstRun, expt_->lumiLastRun);
  lumi_.buildFromFile(runs, true, expt_->histFile, expt_->lumiFirstRun, expt_->lumiLastRun);

}


void Simulator::setFillScheme(unsigned fill) {

  fill_ = fill;

  std::cout << "Using filling scheme " << fills_.getFillingScheme(fill) << std::endl;

  // reset vectors
  for (unsigned bx=0; bx<NBXS_PER_ORBIT; ++bx) {
    collisions_.at(bx) = false;
    masks_.at(bx) = false;
  }

  // loop over collisions
  nColls_ = 0;
  for (unsigned c=0; c<fills_.getCollisions(fill_).size(); ++c) {
    unsigned bx = fills_.getCollisions(fill_).at(c);
    collisions_.at(bx) = true;
    ++nColls_;
  }

  // loop over filled bunches
  nMasks_ = 0;
  for (unsigned b=0; b<fills_.getBunches(fill_).size(); ++b) {
    unsigned bx = fills_.getBunches(fill_).at(b);
    masks_.at((bx-1)%NBXS_PER_ORBIT) = true;
    masks_.at(bx) = true;
    masks_.at((bx+1)%NBXS_PER_ORBIT) = true;
    nMasks_ = nMasks_+3;
  }

  // TODO - set BX to be masked because of "L1 gap"

  std::cout << "N collisions : " << nColls_ << std::endl;
  std::cout << "N masked BX  : " << nMasks_ << std::endl;
  std::cout << std::endl;

}


void Simulator::setupLifetimeBxMasking() {

  std::cout << "Setting up lifetime mask" << std::endl;

  // clear mask
  for (unsigned int bx=0; bx < NBXS_PER_ORBIT; ++bx) {
    lifetimeMasks_.at(bx) = false;
  }

  int lastColl = -1;
  nLifetimeMasks_=0;
  // loop over orbit
  for (unsigned int bx=0; bx < NBXS_PER_ORBIT; ++bx) {

    // if this is a collision, set lastColl index
    if (collisions_.at(bx)) lastColl = bx;

    // mask the BX if the time since last collision is more than 1.256 x lifetime
    double tSinceLastColl = (bx - lastColl) * TIME_PER_BUNCH;
    lifetimeMasks_.at(bx) = (tSinceLastColl > (1.256 * expt_->lifetime));

    // count N masks
    if (lifetimeMasks_.at(bx)) ++nLifetimeMasks_;

  }

  std::cout << "N BX masked : " << nLifetimeMasks_ << std::endl;
  std::cout << std::endl;

}


void Simulator::simulateSignal() {

  std::cout << "Simulating signal" << std::endl;

  double runTimeSeconds = 24 * 3600 * expt_->runningTime;
  unsigned nTotalEvents = 0;
  double nTotalDecays = 0.;
  double effLumi=0.;

  // loop over lumi-sections
  for (unsigned long ls = 0; ls < lumi_.size(); ls++) {

    unsigned nEvents=0;

    // generate some decays
    for (unsigned d=0; d<expt_->nTrialsSignal; ++d) {

      // assign production BX and orbit
      // ie. assume productions are evenly distributed within LS
      unsigned prodBX = fills_.getCollisions(fill_).at((random_.Integer(fills_.getCollisions(fill_).size())));
      unsigned prodOrbit = random_.Integer(NORBITS_PER_LS);
      unsigned long prodLS = ls;

      // pull lifetime from exponential
      double time = random_.Exp(expt_->lifetime);

      // calculate time in units of BX/orbit/LS
      unsigned timeLS          = (unsigned) floor(time / TIME_PER_LS);
      double remainder1        = time - (timeLS * TIME_PER_LS);
      unsigned long timeOrbits = (unsigned long) floor(remainder1 / TIME_PER_ORBIT);
      double remainder2        = remainder1 - (timeOrbits * TIME_PER_ORBIT);
      unsigned timeBX          = (unsigned) floor(remainder2 / TIME_PER_BUNCH);

      // cross-check
      double check = (timeLS * TIME_PER_LS) + 
	(timeOrbits * TIME_PER_ORBIT) + 
	(timeBX * TIME_PER_BUNCH);
//             std::cout << time << " - " << check << " = " << time-check << std::endl;
//             std::cout << timeLS << " " << timeOrbits << " " << timeBX << std::endl;
      assert ((time - check) < 1.1 * TIME_PER_BUNCH);

      // calculate decay time by long addition
      unsigned decayBX        = (prodBX + timeBX) % NBXS_PER_ORBIT;
      unsigned bxRemainder    = (unsigned) (prodBX + timeBX)/NBXS_PER_ORBIT;
      unsigned decayOrbit     = (prodOrbit + timeOrbits + bxRemainder) % NORBITS_PER_LS;
      unsigned orbitRemainder = (unsigned) (prodOrbit + timeOrbits + bxRemainder) / NORBITS_PER_LS;
      unsigned decayLS        = prodLS + timeLS + orbitRemainder;

      // cross-check
      unsigned long long check2 = (decayLS - prodLS) * NBXS_PER_ORBIT * NORBITS_PER_LS;
      check2 += (decayOrbit - prodOrbit) * NBXS_PER_ORBIT;
      check2 += (decayBX - prodBX);
      assert((time*TIME_PER_BUNCH - check2) < 1);
      assert(decayBX < NBXS_PER_ORBIT);
      assert(decayOrbit < NORBITS_PER_LS);

      // if decay happens during sensitive period, check if it triggers
      if (decayLS < lumi_.size()) {
	if(lumi_.cmsSensitive(decayLS)
	   && !masks_.at(decayBX)
	   && (!lifetimeMasks_.at(decayBX) || !expt_->optimizeTimeCut))  {
	  ++nEvents;
	  ++nTotalEvents;
	}
      }

      ++nTotalDecays;

    }

    // add to effective lumi sum
    effLumi += lumi_.luminosity(ls) * nEvents / expt_->nTrialsSignal;

  }

  // set expected signal
  expt_->expSignal   = (nTotalEvents/nTotalDecays)/expt_->signalEff;
  expt_->expSignal_e = (sqrt(nTotalEvents)/nTotalEvents) * expt_->expSignal;
  expt_->effLumi     = effLumi;
  expt_->effLumi_e   = effLumi * (sqrt(nTotalEvents)/nTotalEvents);

  std::cout << "Effective lumi  : " << expt_->effLumi << std::endl;
  std::cout << "Expected signal : " << expt_->expSignal << std::endl;
  std::cout << "Total N decays  : " << expt_->nDecays_MC << std::endl;
  std::cout << std::endl;

}


void Simulator::simulateBackground() {

  std::cout << "Simulating background" << std::endl;

  double nHits =
    expt_->bgRate * expt_->nTrialsBackground * TIME_PER_LS * lumi_.size();

  assert (nHits < 4294967296.); // 2^32, too many hits!!

  unsigned int background_events = 0;

  for (unsigned hit = 1; hit < nHits + 1; hit ++) {
    // Don't truncate the last fraction of an event:
    //  Randomly determine whether to use it
    if (hit > nHits && 
	(random_.Rndm() < hit-nHits)) break;
    
    unsigned int ls    = random_.Integer(lumi_.size());
    //    unsigned int orbit = random_.Integer(NORBITS_PER_LS);
    unsigned int bx    = random_.Integer(NBXS_PER_ORBIT);

    if (ls * TIME_PER_LS > 3600 * 24 * expt_->runningTime) continue;

    // check if event can trigger - assume beamgap for now
    bool take_event = false;
    if (lumi_.cmsSensitive(ls)
	&& !masks_.at(bx)
	&& (!lifetimeMasks_.at(bx) || !expt_->optimizeTimeCut)) take_event = true;

//     else if ((expt_->lookwhere == expt_->INTERFILL || expt_->lookwhere == expt_->BOTH)
// 	     && lumi_.cmsSensitive(ls)
// 	     && lumi_.luminosity(ls) < 1) { // no beam
//       take_event = true;

//       if (expt_->optimizeTimeCut) {
// 	unsigned int i;
// 	for (i = ls; lumi_.luminosity(i) < 1 && i > 0; i--);
// 	if (i==0) take_event = false;
// 	if ((ls - i - 1) * TIME_PER_LS >
// 	    expt_->lifetime * 1.256) 
// 	  take_event = false;
//       }    
      
//       // do specific interfill stuff
//     }

    if (take_event) {
      ++background_events;
//       if (expt_->sendToLifetimeFit &&
// 	  random_.Integer((unsigned int)expt_->nTrialsBackground) == 0)
// 	sendEventToLifetimeFit(ls, orbit, bx);
    }
  }

  expt_->nBG_MC = (unsigned int)(background_events / expt_->nTrialsBackground);

  std::cout << "N background MC : " << expt_->nBG_MC << std::endl;
  std::cout << std::endl;

}


void Simulator::calculateExpectedBG() {

  std::cout << "Calculating expected background" << std::endl;

  double livetime=0.;
  
  // calculate fraction of in-fill LS that can be used
  unsigned nMaskedBX=0;
  for (unsigned bx=0; bx<NBXS_PER_ORBIT; ++bx) {
    if (masks_.at(bx) || lifetimeMasks_.at(bx)) nMaskedBX++;
  }

  double beamgapLiveFraction = (double)nMaskedBX / (double)NBXS_PER_ORBIT;

  // loop over lumi sections, recording how much livetime we had
  for (unsigned long ls = 0; ls < lumi_.size(); ls++) {

    // ignore lumi-sections where cms not sensitive
    if (lumi_.cmsSensitive(ls)) {

      // TODO - check if this lumi-section is beamgap or interfill
      // for now assume beamgap
      livetime += TIME_PER_LS * (1. - beamgapLiveFraction);

    }

  }

  expt_->livetime = livetime;
  expt_->expBackground = livetime * expt_->bgRate;
  expt_->expBackground_e = livetime * expt_->bgRate_e;

  std::cout << "Fraction of BXs masked : " << beamgapLiveFraction << std::endl;
  std::cout << "Livetime               : " << livetime << std::endl;
  std::cout << "Expected background    : " << livetime * expt_->bgRate << " +/- " << livetime * expt_->bgRate_e << std::endl;
  std::cout << std::endl;

}


void Simulator::calculateObservedEvents() {

  std::cout << "Getting observed events" << std::endl;

  //  events_.print(std::cout);

  unsigned nTotalMasked=0;
  std::vector<bool> overallMask(3564, false);
  for (unsigned bx=0; bx<NBXS_PER_ORBIT; ++bx) {
    if (masks_.at(bx) || lifetimeMasks_.at(bx)) {
      overallMask.at(bx) = true;
      ++nTotalMasked;
    }
  }

  expt_->nObserved = events_.countAfterBXMask(overallMask);

  std::cout << "N BXs masked : " << nTotalMasked << std::endl;
  std::cout << "N obs : " << expt_->nObserved << std::endl;
  std::cout << std::endl;

}


void Simulator::calculateLimit() {

  std::cout << "Calculating limits" << std::endl;

//   expt_->expBackground = 1.;
//   expt_->expBackground_e = 1.;

  CLsCountingExperiment ce (expt_->expBackground, expt_->expBackground_e, 1, expt_->scaleUncert);
  //CL95CMSCountingExperiment ce (expt_->expBackground, expt_->expBackground_e, 1, expt_->scaleUncert);

  expt_->limit95cl = ce.cl95limit(expt_->nObserved);

  std::cout << "95CL limit : " << ce.cl95limit(expt_->nObserved) << std::endl;
  std::cout << std::endl;

}


void Simulator::printMaskInfo() {

  std::cout << "Masked BX :" << std::endl;
  for (unsigned bx=0; bx<NBXS_PER_ORBIT; ++bx) {
    if (masks_.at(bx)) std::cout << bx << ",";
  }
  std::cout <<std::endl;

  std::cout << "Lifetime masked BX :" << std::endl;
  for (unsigned bx=0; bx<NBXS_PER_ORBIT; ++bx) {
    if (lifetimeMasks_.at(bx)) std::cout << bx << ",";
  }
  std::cout <<std::endl;

}

// // unclear what these are for
// bool Simulator::collisionHasL1A(double rate) {
//   return random_.Rndm() < rate * TIME_PER_BUNCH * nBxOn_ / NBXS_PER_ORBIT;
// }


// bool Simulator::isTriggerBlocked(const Experiment &e, unsigned int bx,
// 				 unsigned int bxs_from_originating_l1a) {
//   unsigned int other_l1as = 0;
//   int new_bx;
//   if (bxs_from_originating_l1a != 0 &&
//       bxs_from_originating_l1a < 3) return true;
//   for (new_bx = bx - 1; new_bx >= ((int)bx) - 2; new_bx--) {
//     int bx_to_check = (new_bx >= 0 ? new_bx : new_bx + NBXS_PER_ORBIT);
//     if (beam_[bx_to_check] && collisionHasL1A(expt_->collisionL1Arate)) return true;
//   }
//   if (bxs_from_originating_l1a >= 3 &&
//       bxs_from_originating_l1a < 8) other_l1as++;
//   for (; new_bx >= ((int)bx) - 7; new_bx--) {
//     int bx_to_check = (new_bx >= 0 ? new_bx : new_bx + NBXS_PER_ORBIT);
//     if (beam_[bx_to_check] && collisionHasL1A(expt_->collisionL1Arate))
//       other_l1as++;
//   }
//   if (other_l1as > 1) return true;
//   if (bxs_from_originating_l1a >= 8 &&
//       bxs_from_originating_l1a < 100) other_l1as++;
//   for (; new_bx >= ((int)bx) - 99; new_bx--) {
//     int bx_to_check = (new_bx >= 0 ? new_bx : new_bx + NBXS_PER_ORBIT);
//     if (beam_[bx_to_check] && collisionHasL1A(expt_->collisionL1Arate))
//       other_l1as++;
//   }
//   if (other_l1as > 2) return true;
//   if (bxs_from_originating_l1a >= 100 &&
//       bxs_from_originating_l1a < 240) other_l1as++;
//   for (; new_bx >= ((int)bx) - 239; new_bx--) {
//     int bx_to_check = (new_bx >= 0 ? new_bx : new_bx + NBXS_PER_ORBIT);
//     if (beam_[bx_to_check] && collisionHasL1A(expt_->collisionL1Arate))
//       other_l1as++;
//   }
//   if (other_l1as > 3) return true;
//   return false;
// }




// /// plot stuff
// void Simulator::setupPlots() {
//   run_specific_plots["longtime"] =
//     new TH1D("longtime", "Stopped Gluino decays", 500, 0, 30);
//   run_specific_plots["decays_in_beam"] =
//     new TH1D("decays_in_beam", "Decays within bunch structure",
// 	     3564, -.5, 3563.5);
//   run_specific_plots["sensitive_in_beam"] =
//     new TH1D("sensitive_in_beam", "Sensitive Decays within bunch structure",
// 	     3564, -.5, 3563.5);
//   run_specific_plots["bunch_structure"] =
//     new TH1D("bunch_structure", "Bunch Structure",
// 	     3564, -.5, 3563.5);
//   run_specific_plots["vetoed_events"] =
//     new TH1D("vetoed_events", "Vetoed Events",
// 	     3564, -.5, 3563.5);    
// }


// void Simulator::clearPlots() {
//   for (std::map<std::string, TH1D *>::iterator it = run_specific_plots.begin();
//        it != run_specific_plots.end(); it++)
//     delete it->second;
//   run_specific_plots.clear();
// }



// // lifetime fit stuff
// void Simulator::sendEventToLifetimeFit(unsigned int ls,
// 				       unsigned int orbit,
// 				       unsigned int bx) {

//   //  event[0] = (int)ls;
//   ls_ = (int)ls;
//   orbit_ = (int)orbit;
//   bx_ = (int)bx;

//   tree_.Fill();

// }


// void Simulator::writeOutLifetimeFit() {
//   lifetimeFitOutput_.cd();
//   tree_.Write();
// }

