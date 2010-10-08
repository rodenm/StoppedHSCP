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
  //  lifetimeMasks_(NBXS_PER_ORBIT, false),
  tree_("events", "Event time structure")
{
  tree_.Branch("ls", &ls_, "ls/I");
  tree_.Branch("orbit", &orbit_, "orbit/I");
  tree_.Branch("bx", &bx_, "bx/I");

  std::cout << "Some parameters " << std::endl;
  std::cout << "Time per BX " << TIME_PER_BUNCH << std::endl;

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

  std::cout << "Using filling scheme " << fills_.getFillingScheme(fill) << std::endl;

  prodFill_ = fill;
  decayFill_ = fill;
  
  // TODO - set BX to be masked because of "L1 gap"

  std::cout << "N collisions : " << fills_.getCollisions(prodFill_).size() << std::endl;
  //  std::cout << "N masked BX  : " << fills_.getMask(decayFill_).size() << std::endl;
  std::cout << std::endl;

}


void Simulator::setupLifetimeMask() {
  fills_.setupLifetimeMask(expt_->lifetime);
}


void Simulator::simulateSignal() {

  std::cout << "Simulating signal" << std::endl;

  //  double runTimeSeconds = 24 * 3600 * expt_->runningTime;
  unsigned nTotalEvents = 0;
  double nTotalDecays = 0.;
  double effLumi=0.;

  // loop over lumi-sections
  for (unsigned long i = 0; i < lumi_.size(); i++) {

    unsigned long prodRun = lumi_.at(i).run;

    unsigned nEvents=0;

    // don't simulate decays from lumisections with no luminosity
    if (lumi_.at(i).lumi < Luminosity::THRESHOLD) continue;

    // generate some decays
    for (unsigned d=0; d<expt_->nTrialsSignal; ++d) {

      // assign production BX and orbit
      // ie. assume productions are evenly distributed within LS
      unsigned prodBX = fills_.getCollisionsFromRun(prodRun).at((random_.Integer(fills_.getCollisions(prodRun).size())));
      unsigned prodOrbit = random_.Integer(NORBITS_PER_LS);
      unsigned long prodLSIndex = i;

      // pull lifetime from exponential
      double time = random_.Exp(expt_->lifetime);

      // calculate time in units of BX/orbit/LS
      unsigned long timeLS     = (unsigned) floor(time / TIME_PER_LS);
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
      unsigned long decayLSIndex = prodLSIndex + timeLS + orbitRemainder;
      unsigned decayRun       = ( (decayLSIndex < lumi_.size()) ? lumi_.at(decayLSIndex).run : 0);

      // cross-check
      unsigned long long check2 = (decayLSIndex - prodLSIndex) * NBXS_PER_ORBIT * NORBITS_PER_LS;
      check2 += (decayOrbit - prodOrbit) * NBXS_PER_ORBIT;
      check2 += (decayBX - prodBX);
      assert((time*TIME_PER_BUNCH - check2) < 1);
      assert(decayBX < NBXS_PER_ORBIT);
      assert(decayOrbit < NORBITS_PER_LS);

      // if decay happens during sensitive period, check if it triggers
      // TODO - add interfill expt lifetime mask!!!
      bool passBunchMask   = !(fills_.getMaskFromRun(decayRun).at(decayBX));
      bool passSensitiveLS = (decayLSIndex < lumi_.size()) && lumi_.cmsSensitive(decayLSIndex);
      bool passLifetimeMask= !(fills_.getLifetimeMask(decayRun).at(decayBX)) || !(expt_->optimizeTimeCut);

      if(passSensitiveLS && passBunchMask && passLifetimeMask) {
	++nEvents;
	++nTotalEvents;
      }
      
      ++nTotalDecays;

    }

    // add to effective lumi sum
    effLumi += lumi_.luminosity(i) * nEvents / expt_->nTrialsSignal;

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


/// this method not currently used - probably needs updating
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
    
    unsigned int lsi   = random_.Integer(lumi_.size());
    //    unsigned int orbit = random_.Integer(NORBITS_PER_LS);
    unsigned int bx    = random_.Integer(NBXS_PER_ORBIT);
    unsigned run = lumi_.at(lsi).run;

    // check if event can trigger - assume beamgap for now
    bool passBunchMask   = !(fills_.getMaskFromRun(run).at(bx));
    bool passSensitiveLS = (lsi < lumi_.size()) && lumi_.cmsSensitive(lsi);
    bool passLifetimeMask= !(fills_.getLifetimeMaskFromRun(run).at(bx)) || !(expt_->optimizeTimeCut);

    if (passBunchMask && passSensitiveLS && passLifetimeMask) {
      ++background_events;
    }

  }

  expt_->nBG_MC = (unsigned int)(background_events / expt_->nTrialsBackground);

  std::cout << "N background MC : " << expt_->nBG_MC << std::endl;
  std::cout << std::endl;

}


void Simulator::calculateExpectedBG() {

  std::cout << "Calculating expected background" << std::endl;

  double livetime=0.;
  double totalTime=0.;
  
  // set N masked bunches for first LS
  unsigned nMaskedBX=0;
  unsigned run=lumi_.at(0).run;
  for (unsigned bx=0; bx<NBXS_PER_ORBIT; ++bx) {
    if (fills_.getMaskFromRun(run).at(bx) || fills_.getLifetimeMaskFromRun(run).at(bx)) nMaskedBX++;
  }


  // loop over lumi sections, recording how much livetime we had
  for (unsigned long lsi = 0; lsi < lumi_.size(); lsi++) {

    // ignore lumi-sections where cms not sensitive
    if (lumi_.cmsSensitive(lsi)) {

      totalTime  += TIME_PER_LS;

      // update number of masked BX if run changed
      if (lumi_.at(lsi).run != run) {
	run=lumi_.at(lsi).run;
	nMaskedBX=0;
	for (unsigned bx=0; bx<NBXS_PER_ORBIT; ++bx) {
	  if (fills_.getMaskFromRun(run).at(bx) || fills_.getLifetimeMaskFromRun(run).at(bx)) nMaskedBX++;
	}
      }
      
      double beamgapMaskedFraction = (double)nMaskedBX / (double)NBXS_PER_ORBIT;

      // TODO - check if this lumi-section is beamgap or interfill
      // for now assume beamgap
      livetime   += TIME_PER_LS * (1. - beamgapMaskedFraction);

    }

  }

  expt_->livetime = livetime;
  expt_->expBackground = livetime * expt_->bgRate;
  expt_->expBackground_e = livetime * expt_->bgRate_e;

  std::cout << "Live time              : " << livetime << std::endl;
  std::cout << "Fraction of BX masked  : " << 1. - (livetime/totalTime) << std::endl;
  std::cout << "Expected background    : " << livetime * expt_->bgRate << " +/- " << livetime * expt_->bgRate_e << std::endl;
  std::cout << std::endl;

}


void Simulator::calculateObservedEvents() {

  std::cout << "Getting observed events" << std::endl;

  unsigned nEvents=0;

  // loop over events
  for (Events::const_iterator e=events_.begin(); e!=events_.end(); ++e) {

    unsigned run = e->run;
    unsigned bx  = e->bx;
    if (!(fills_.getMaskFromRun(run).at(bx)) &&
	!(fills_.getLifetimeMaskFromRun(run).at(bx)) ) nEvents++;

  }

  expt_->nObserved = nEvents;

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
    if (fills_.getMask(prodFill_).at(bx)) std::cout << bx << ",";
  }
  std::cout <<std::endl;

  std::cout << "Lifetime masked BX :" << std::endl;
  for (unsigned bx=0; bx<NBXS_PER_ORBIT; ++bx) {
    if (fills_.getLifetimeMask(prodFill_).at(bx)) std::cout << bx << ",";
  }
  std::cout <<std::endl;

}

