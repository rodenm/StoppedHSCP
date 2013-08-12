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
  tree_("events", "Event time structure"),
  effLumi_(0.),
  nObs_(0),
  nExp_(0.),
  nExp_e_(0.)
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


void Simulator::setupLumi(bool buildFromDB,
			  bool lumiCalc2,
			  bool useHists,
			  std::string file) {

  // get runs for all fills
  std::vector<unsigned long> runs;
  for (unsigned i=0; i<expt_->fills.size(); ++i) {
    std::vector<unsigned long> r = fills_.getRuns(expt_->fills.at(i));
    runs.insert(runs.end(),r.begin(), r.end());
  }	

  // build lumi from runs
  std::string goodDataFile;
  if (useHists) goodDataFile = expt_->histFile;
  else goodDataFile = expt_->jsonFile;

  if (buildFromDB) {
    lumi_.buildFromDB(runs, useHists, goodDataFile, expt_->lumiFirstRun, expt_->lumiLastRun);
  }
  else {
    if (lumiCalc2) {
      lumi_.buildFromFile2(file, runs, useHists, goodDataFile, expt_->lumiFirstRun, expt_->lumiLastRun);
    }
    else {
      lumi_.buildFromFile(file, runs, useHists, goodDataFile, expt_->lumiFirstRun, expt_->lumiLastRun);
    }
  }

}


// void Simulator::setFillScheme(unsigned fill) {

//   std::cout << "Using filling scheme " << fills_.getFillingScheme(fill) << std::endl;

//   prodFill_ = fill;
//   decayFill_ = fill;
  
//   // TODO - set BX to be masked because of "L1 gap"

//   std::cout << "N collisions : " << fills_.getCollisions(prodFill_).size() << std::endl;
//   //  std::cout << "N masked BX  : " << fills_.getMask(decayFill_).size() << std::endl;
//   std::cout << std::endl;

// }


void Simulator::setupLifetimeMask() {
  fills_.setupLifetimeMask(expt_->lifetime);
}


void Simulator::simulateSignal(unsigned firstFill, unsigned lastFill) {

  std::cout << "Simulating signal" << std::endl;

  //  double runTimeSeconds = 24 * 3600 * expt_->runningTime;
  unsigned nTotalEvents = 0;
  double nTotalDecays = 0.;
  double effLumi=0.;

  // loop over lumi-sections
  for (unsigned long i = 0; i < lumi_.size(); i++) {

    unsigned long prodRun = lumi_.at(i).run;

    unsigned nEvents=0;

    // dont simulate deacys from fills outside fill range
    if (fills_.getFillFromRun(prodRun) < firstFill) continue;
    if (fills_.getFillFromRun(prodRun) > lastFill) break;

    // don't simulate decays from lumisections with no luminosity
    if (lumi_.at(i).lumi < Luminosity::THRESHOLD) continue;

    // generate some decays
    for (unsigned d=0; d<expt_->nTrialsSignal; ++d) {

      /** assign production BX and orbit **/
      // ie. assume productions are evenly distributed within LS
      unsigned rndColl = random_.Integer(fills_.getCollisionsFromRun(prodRun).size());
      unsigned prodBX = 0;
      if (rndColl < fills_.getCollisionsFromRun(prodRun).size()) {
	prodBX = fills_.getCollisionsFromRun(prodRun).at(rndColl);
      }
      else {
	std::cerr << "No collisions in fill : " << fills_.getFillFromRun(prodRun) << std::endl;
	break;
      }
      unsigned prodOrbit = random_.Integer(NORBITS_PER_LS);
      unsigned long prodLSIndex = i;

      // pull lifetime from exponential
      double time = random_.Exp(expt_->lifetime);

      // calculate time in units of BX/orbit/LS
      unsigned long timeLS     = (unsigned long) floor(time / TIME_PER_LS);
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
      bool passFillPeriod  = fills_.getFillFromRun(decayRun) >= firstFill && fills_.getFillFromRun(decayRun) <= lastFill;
      bool passLifetimeMask= !(fills_.getLifetimeMaskFromRun(decayRun).at(decayBX)) || !(expt_->optimizeTimeCut);

      if(passSensitiveLS && passFillPeriod && passBunchMask && passLifetimeMask) {
	++nEvents;
	++nTotalEvents;
      }
      
      ++nTotalDecays;

    }

    // add to effective lumi sum
    effLumi += lumi_.luminosity(i) * nEvents / expt_->nTrialsSignal;

  }

  // set expected signal
  expt_->nDecays_MC  += nTotalDecays;
  expt_->nObs_MC     += nTotalEvents;
  expt_->effLumi     += effLumi;

  if (expt_->nDecays_MC > 0) {
    expt_->expSignal   = (expt_->nObs_MC/expt_->nDecays_MC) * expt_->signalEff * expt_->effLumi * expt_->crossSection;
    expt_->expSignal_e = expt_->expSignal * (sqrt(expt_->nObs_MC)/expt_->nDecays_MC);
    expt_->effLumi_e   = expt_->effLumi * (sqrt(expt_->nObs_MC)/expt_->nDecays_MC);
  }

  std::cout << "Effective lumi  : " << effLumi << std::endl;
  std::cout << "Expected signal : " << expt_->expSignal << std::endl;
  std::cout << "Total N decays  : " << expt_->nDecays_MC << std::endl;
  std::cout << std::endl;

  effLumi_ = effLumi;

}


/// this method not currently used - probably needs updating
// void Simulator::simulateBackground() {

//   std::cout << "Simulating background" << std::endl;

//   double nHits =
//     expt_->bgRate * expt_->nTrialsBackground * TIME_PER_LS * lumi_.size();

//   assert (nHits < 4294967296.); // 2^32, too many hits!!

//   unsigned int background_events = 0;

//   for (unsigned hit = 1; hit < nHits + 1; hit ++) {
//     // Don't truncate the last fraction of an event:
//     //  Randomly determine whether to use it
//     if (hit > nHits && 
// 	(random_.Rndm() < hit-nHits)) break;
    
//     unsigned int lsi   = random_.Integer(lumi_.size());
//     //    unsigned int orbit = random_.Integer(NORBITS_PER_LS);
//     unsigned int bx    = random_.Integer(NBXS_PER_ORBIT);
//     unsigned run = lumi_.at(lsi).run;

//     // check if event can trigger - assume beamgap for now
//     bool passBunchMask   = !(fills_.getMaskFromRun(run).at(bx));
//     bool passSensitiveLS = (lsi < lumi_.size()) && lumi_.cmsSensitive(lsi);
//     bool passLifetimeMask= !(fills_.getLifetimeMaskFromRun(run).at(bx)) || !(expt_->optimizeTimeCut);

//     if (passBunchMask && passSensitiveLS && passLifetimeMask) {
//       ++background_events;
//     }

//   }

//   expt_->nBG_MC = (unsigned int)(background_events / expt_->nTrialsBackground);

//   std::cout << "N background MC : " << expt_->nBG_MC << std::endl;
//   std::cout << std::endl;

// }


void Simulator::calculateExpectedBG(unsigned firstFill, unsigned lastFill) {

  std::cout << "Calculating expected background" << std::endl;

  double livetime=0.;
  double totalTime=0.;
  
  // set N masked bunches for first LS
  unsigned nMaskedBX=0;
  unsigned run=lumi_.at(0).run;
  for (unsigned bx=0; bx<NBXS_PER_ORBIT; ++bx) {
    if (fills_.getMaskFromRun(run).at(bx) || fills_.getLifetimeMaskFromRun(run).at(bx)) ++nMaskedBX;
  }


  // loop over lumi sections, recording how much livetime we had
  for (unsigned long lsi = 0; lsi < lumi_.size(); lsi++) {

    // ignore fills outside fill range
    if (fills_.getFillFromRun(lumi_.at(lsi).run) < firstFill) continue;
    if (fills_.getFillFromRun(lumi_.at(lsi).run) > lastFill) break;

    // ignore lumisections with no luminosity
    //    if (lumi_.at(lsi).lumi < Luminosity::THRESHOLD) continue;    

    // ignore lumi-sections where cms not sensitive
    if (!lumi_.cmsSensitive(lsi)) continue;

    // update number of masked BX if run changed
    if (lumi_.at(lsi).run != run) {

      run=lumi_.at(lsi).run;
      nMaskedBX=0;
      for (unsigned bx=0; bx<NBXS_PER_ORBIT; ++bx) {
	if (fills_.getMaskFromRun(run).at(bx) || fills_.getLifetimeMaskFromRun(run).at(bx)) nMaskedBX++;
      }
    }

    // update total time
    totalTime  += TIME_PER_LS;
    
    // calculate fraction of time available & background contribution from this LS
    double beamgapMaskedFraction = (double)nMaskedBX / (double)NBXS_PER_ORBIT;
    livetime   += TIME_PER_LS * (1. - beamgapMaskedFraction);

  }

  expt_->livetime        += livetime;

  expt_->expBackground   = expt_->livetime * expt_->bgRate;
  expt_->expBackground_e = expt_->livetime * expt_->bgRate_e;

  std::cout << "Total time             : " << totalTime << std::endl;
  std::cout << "Live time              : " << livetime << std::endl;
  std::cout << "Fraction of BX masked  : " << 1. - (livetime/totalTime) << std::endl;
  std::cout << "Expected background    : " << livetime * expt_->bgRate << " +/- " << livetime * expt_->bgRate_e << std::endl;

  nExp_   = livetime * expt_->bgRate;
  nExp_e_ = livetime * expt_->bgRate_e;

}


void Simulator::calculateObservedEvents(unsigned firstFill, unsigned lastFill) {

  std::cout << "Getting observed events" << std::endl;

  unsigned nEvents=0;

  // loop over events
  for (Events::const_iterator e=events_.begin(); e!=events_.end(); ++e) {

    unsigned run = e->run;
    unsigned bx  = e->bx;
    
    //    std::cout <<  "Event : " << fills_.getFillFromRun(run) << " " << e->run << "\t" << e->ls << "\t" << e->bx << "\t" << e->id << std::endl;
    

    // ignore events outside fill range
    if (fills_.getFillFromRun(run) < firstFill) continue;
    if (fills_.getFillFromRun(run) > lastFill) continue; 

    if (!(fills_.getMaskFromRun(run).at(bx)) &&
	!(fills_.getLifetimeMaskFromRun(run).at(bx)) ) {
      nEvents++;
      std::cout << "Event : " << e->run << "\t" << e->ls << "\t" << e->bx << "\t" << e->id << std::endl;
    }
    
  }

  expt_->nObserved += nEvents;

  std::cout << "N obs : " << nEvents << std::endl;
  std::cout << std::endl;

  nObs_ = nEvents;

}


void Simulator::calculateLimit() {

  std::cout << "Calculating limits" << std::endl;

  // if no signal or background expected, skip this
  if (expt_->expBackground == 0. && expt_->effLumi == 0.) {
    std::cout << "Background and L_eff both zero, skipping limits" << std::endl;
    std::cout << std::endl;
    return;
  }

//   expt_->expBackground = 1.;
//   expt_->expBackground_e = 1.;

  CLsCountingExperiment ce (expt_->expBackground, expt_->expBackground_e, 1, expt_->scaleUncert);
  //CL95CMSCountingExperiment ce (expt_->expBackground, expt_->expBackground_e, 1, expt_->scaleUncert);

  expt_->limit95cl = ce.cl95limit(expt_->nObserved);

  std::vector<double>  expectedLimit = ce.cl95ExpectedLimit ();
  expt_->expLimit = expectedLimit[5];
  expt_->expLim1SigLo = expectedLimit[1];
  expt_->expLim1SigHi = expectedLimit[2];
  expt_->expLim2SigLo = expectedLimit[3];
  expt_->expLim2SigHi = expectedLimit[4];

  // code shamelessly copied from StoppedHSCP/Statistics/bin/calculateLimits.cc :
  //    sprintf (buffer, "%s lifetime: %6.3e lumiEff: %5.4f  bkg: %5.3f observed: %3i limit: %5.3f 
  // expectedmean: %5.3f rms1sigma:  %5.3f %5.3f rms2sigma: %5.3f %5.3f  
  // expectedmed: %5.3f qtile1sigma: %5.3f %5.3f qtile2sigma: %5.3f %5.3f", 
  //         useCLs ? "CLs" : "CL95CMS",
  //         lifetime, bs.getLumiEfficiency (lifetime), expectedBackground, nObserved, limit,
  //         expectedLimit[5], expectedLimit[6], expectedLimit[7], expectedLimit[8], expectedLimit[9], 
  //         expectedLimit[0], expectedLimit[1], expectedLimit[2], expectedLimit[3], expectedLimit[4]); 
  
  std::cout << "Observed limit (95CL) : " << expt_->limit95cl << std::endl;
  std::cout << "Expected limit        : " << expt_->expLimit << std::endl;
  std::cout << "Expected limit (-1sigma) : " << expt_->expLim1SigLo << std::endl;
  std::cout << "Expected limit (+1sigma) : " << expt_->expLim1SigHi << std::endl;
  std::cout << "Expected limit (-2sigma) : " << expt_->expLim2SigLo << std::endl;
  std::cout << "Expected limit (+2sigma) : " << expt_->expLim2SigHi << std::endl;

  std::cout << std::endl;

}


void Simulator::printMaskInfo(unsigned fill) {

  std::cout << "Masked BX :" << std::endl;
  for (unsigned bx=0; bx<NBXS_PER_ORBIT; ++bx) {
    if (fills_.getMask(fill).at(bx)) std::cout << bx << ",";
  }
  std::cout <<std::endl;

  std::cout << "Lifetime masked BX :" << std::endl;
  for (unsigned bx=0; bx<NBXS_PER_ORBIT; ++bx) {
    if (fills_.getLifetimeMask(fill).at(bx)) std::cout << bx << ",";
  }
  std::cout <<std::endl;

}

