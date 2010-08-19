#include "StoppedHSCP/ToyMC/interface/Simulator.h"
#include "TMath.h"
#include <assert.h>
#include <iostream>

Simulator::Simulator() 
  : beamStructure_(0), 
    maskedBXs_(NBXS_PER_ORBIT, 0),
    lifetimeMask_(NBXS_PER_ORBIT, 0),    
    lifetimeFitOutput_("events.root", "RECREATE"),
    tree_("events", "Event time structure")
{
  tree_.Branch("ls", &ls_, "ls/I");
  tree_.Branch("orbit", &orbit_, "orbit/I");
  tree_.Branch("bx", &bx_, "bx/I");

}

void Simulator::writeOutLifetimeFit() {
  lifetimeFitOutput_.cd();
  tree_.Write();
}

void Simulator::clearPlots() {
  for (std::map<std::string, TH1D *>::iterator it = run_specific_plots.begin();
       it != run_specific_plots.end(); it++)
    delete it->second;
  run_specific_plots.clear();
}

void Simulator::sendEventToLifetimeFit(unsigned int ls,
				       unsigned int orbit,
				       unsigned int bx) {

  //  event[0] = (int)ls;
  ls_ = (int)ls;
  orbit_ = (int)orbit;
  bx_ = (int)bx;

  tree_.Fill();

}

bool Simulator::collisionHasL1A(double rate) {
  return random_.Rndm() < rate * TIME_PER_BUNCH * nBxOn_ / NBXS_PER_ORBIT;
}

bool Simulator::isTriggerBlocked(const Experiment &e, unsigned int bx,
				 unsigned int bxs_from_originating_l1a) {
  unsigned int other_l1as = 0;
  int new_bx;
  if (bxs_from_originating_l1a != 0 &&
      bxs_from_originating_l1a < 3) return true;
  for (new_bx = bx - 1; new_bx >= ((int)bx) - 2; new_bx--) {
    int bx_to_check = (new_bx >= 0 ? new_bx : new_bx + NBXS_PER_ORBIT);
    if (beam_[bx_to_check] && collisionHasL1A(e.collisionL1Arate)) return true;
  }
  if (bxs_from_originating_l1a >= 3 &&
      bxs_from_originating_l1a < 8) other_l1as++;
  for (; new_bx >= ((int)bx) - 7; new_bx--) {
    int bx_to_check = (new_bx >= 0 ? new_bx : new_bx + NBXS_PER_ORBIT);
    if (beam_[bx_to_check] && collisionHasL1A(e.collisionL1Arate))
      other_l1as++;
  }
  if (other_l1as > 1) return true;
  if (bxs_from_originating_l1a >= 8 &&
      bxs_from_originating_l1a < 100) other_l1as++;
  for (; new_bx >= ((int)bx) - 99; new_bx--) {
    int bx_to_check = (new_bx >= 0 ? new_bx : new_bx + NBXS_PER_ORBIT);
    if (beam_[bx_to_check] && collisionHasL1A(e.collisionL1Arate))
      other_l1as++;
  }
  if (other_l1as > 2) return true;
  if (bxs_from_originating_l1a >= 100 &&
      bxs_from_originating_l1a < 240) other_l1as++;
  for (; new_bx >= ((int)bx) - 239; new_bx--) {
    int bx_to_check = (new_bx >= 0 ? new_bx : new_bx + NBXS_PER_ORBIT);
    if (beam_[bx_to_check] && collisionHasL1A(e.collisionL1Arate))
      other_l1as++;
  }
  if (other_l1as > 3) return true;
  return false;
}

void Simulator::setupPlots() {
  run_specific_plots["longtime"] =
    new TH1D("longtime", "Stopped Gluino decays", 500, 0, 30);
  run_specific_plots["decays_in_beam"] =
    new TH1D("decays_in_beam", "Decays within bunch structure",
	     3564, -.5, 3563.5);
  run_specific_plots["sensitive_in_beam"] =
    new TH1D("sensitive_in_beam", "Sensitive Decays within bunch structure",
	     3564, -.5, 3563.5);
  run_specific_plots["bunch_structure"] =
    new TH1D("bunch_structure", "Bunch Structure",
	     3564, -.5, 3563.5);
  run_specific_plots["vetoed_events"] =
    new TH1D("vetoed_events", "Vetoed Events",
	     3564, -.5, 3563.5);    
}

void Simulator::setupLumi(std::vector<unsigned long> fillsToSimulate) {

  // get runs for all fills
  std::vector<unsigned long> runs;

  for (unsigned i=0; i<fillsToSimulate.size(); ++i) {
    std::vector<unsigned long> r = fills_.getRuns(fillsToSimulate.at(i));
    runs.insert(runs.end(),r.begin(), r.end());
  }	

  lumi_.buildFromFile(runs);

}

void Simulator::setupBxStructure(unsigned int bx_struct_in) {
  if (beamStructure_ == bx_struct_in) return;

  // set up bunch structure
  unsigned int i, j, k, l, counter = 0;

  beamStructure_ = bx_struct_in;
  nBxOn_    = 0;
  nBxOff_   = 0;
  collisions_.clear();
  collisions_.reserve(bx_struct_in);

  // December 09 run 124230
  if (beamStructure_ == 2) {
    for (i = 0; i < NBXS_PER_ORBIT; i++) {
      //      if (i ==    0 ||
      //	  i == 1782) {
      if (i ==    1 ||
	  i == 1786) {
	collisions_.push_back(i);
	beam_[counter] = 1;
	maskedBXs_[counter-1] = 1;
	maskedBXs_[counter] = 1;
	maskedBXs_[counter+1] = 1;
	counter++;
	nBxOn_++;
      }
      else {
	beam_[counter++] = 0;
	nBxOff_++;
      }
    } 
    maskedBXs_[891] = 1;
    maskedBXs_[892] = 1;
    maskedBXs_[893] = 1;
    maskedBXs_[894] = 1;
    maskedBXs_[895] = 1;
    maskedBXs_[896] = 1;

  }
  else if (beamStructure_ == 3) {
    for (i = 0; i < NBXS_PER_ORBIT; i++) {
      if (i ==    1 ||
	  i ==  201 ||
	  i ==  401) {

	maskedBXs_[counter] = 1;
	if (counter != 0)
	  maskedBXs_[counter-1] = 1;
	if (counter != NBXS_PER_ORBIT-1)
	  maskedBXs_[counter+1] = 1;

	collisions_.push_back(i);
	beam_[counter++] = 1;
	nBxOn_++;
      }
      else {
	beam_[counter++] = 0;
	nBxOff_++;
      }
    }     
  }
  else if (beamStructure_ == 4) {
    for (i = 0; i < NBXS_PER_ORBIT; i++) {
      if (i ==    1 ||
	  i ==  101 ||
	  i == 1786 ||
	  i == 1886) {

	maskedBXs_[counter] = 1;
	if (counter != 0)
	  maskedBXs_[counter-1] = 1;
	if (counter != NBXS_PER_ORBIT-1)
	  maskedBXs_[counter+1] = 1;

	collisions_.push_back(i);
	beam_[counter++] = 1;
	nBxOn_++;
      }
      else {
	if (i ==  401 ||
	    i ==  501 ||
	    i ==  892 ||
	    i ==  893 ||
	    i ==  894 ||
	    i ==  895 ||
	    i ==  992 ||
	    i ==  993 ||
	    i ==  994 ||
	    i ==  995) {
	maskedBXs_[counter] = 1;
	if (counter != 0)
	  maskedBXs_[counter-1] = 1;
	if (counter != NBXS_PER_ORBIT-1)
	  maskedBXs_[counter+1] = 1;
	}
	beam_[counter++] = 0;
	nBxOff_++;
      }
    } 
  }
  else if (beamStructure_ == 5) {
    // Single_10b_4_2_4
    for (i = 0; i < NBXS_PER_ORBIT; i++) {
      if (i ==    1 ||
	  i ==  201 ||
	  i ==  401 ||
	  i ==  601) {

	maskedBXs_[counter] = 1;
	if (counter != 0)
	  maskedBXs_[counter-1] = 1;
	if (counter != NBXS_PER_ORBIT-1)
	  maskedBXs_[counter+1] = 1;

	collisions_.push_back(i);
	beam_[counter++] = 1;
	nBxOn_++;
      }
      else {
	if (i ==  101 ||
	    i ==  501 ||
	    i ==  892 ||
	    i ==  895 ||
	    i ==  992 ||
	    i ==  995 ||
	    i == 1786 ||
	    i == 1886
	    ) {
	maskedBXs_[counter] = 1;
	if (counter != 0)
	  maskedBXs_[counter-1] = 1;
	if (counter != NBXS_PER_ORBIT-1)
	  maskedBXs_[counter+1] = 1;
	}
	beam_[counter++] = 0;
	nBxOff_++;
      }
    } 
  }
  else if (beamStructure_ == 6) {
    for (i = 0; i < NBXS_PER_ORBIT; i++) {
      if (i ==    1 ||
	  i ==  201 ||
	  i ==  401 ||
	  i == 1786 ||
	  i == 1986 ||
	  i == 2186) {

	maskedBXs_[counter] = 1;
	if (counter != 0)
	  maskedBXs_[counter-1] = 1;
	if (counter != NBXS_PER_ORBIT-1)
	  maskedBXs_[counter+1] = 1;

	collisions_.push_back(i);
	beam_[counter++] = 1;
	nBxOn_++;
      }
      else {
	if (i ==  892 ||
	    i ==  895 ||
	    i == 1092 ||
	    i == 1095 ||
	    i == 1292 ||
	    i == 1295
	    ) {
	maskedBXs_[counter] = 1;
	if (counter != 0)
	  maskedBXs_[counter-1] = 1;
	if (counter != NBXS_PER_ORBIT-1)
	  maskedBXs_[counter+1] = 1;
	}
	beam_[counter++] = 0;
	nBxOff_++;
      }
    } 
  }
  else if (beamStructure_ == 8) {
    // Single_13b_8_8_8 before
    for (i = 0; i < NBXS_PER_ORBIT; i++) {
      if (i ==    1 ||
	  i ==  101 ||
	  i ==  201 ||
	  i ==  301 ||
	  i == 1786 ||
	  i == 1886 ||
	  i == 1986 ||
	  i == 2086 ) {

	maskedBXs_[counter] = 1;
	if (counter != 0)
	  maskedBXs_[counter-1] = 1;
	if (counter != NBXS_PER_ORBIT-1)
	  maskedBXs_[counter+1] = 1;

	collisions_.push_back(i);
	beam_[counter++] = 1;
	nBxOn_++;
      }
      else {
	if (i ==  894 ||
	    i ==  994 ||
	    i == 1094 ||
	    i == 1194) {
	maskedBXs_[counter] = 1;
	if (counter != 0)
	  maskedBXs_[counter-1] = 1;
	if (counter != NBXS_PER_ORBIT-1)
	  maskedBXs_[counter+1] = 1;
	}
	beam_[counter++] = 0;
	nBxOff_++;
      }
    } 
  }
  else if (beamStructure_ == 10) {
    // Single_13b_8_8_8 after
    for (i = 0; i < NBXS_PER_ORBIT; i++) {
      if (i ==    1 ||
	  i ==  101 ||
	  i ==  201 ||
	  i ==  301 ||
	  i == 1786 ||
	  i == 1886 ||
	  i == 1986 ||
	  i == 2086 ) {

	maskedBXs_[counter] = 1;
	if (counter != 0)
	  maskedBXs_[counter-1] = 1;
	if (counter != NBXS_PER_ORBIT-1)
	  maskedBXs_[counter+1] = 1;

	collisions_.push_back(i);
	beam_[counter++] = 1;
	nBxOn_++;
      }
      else {
	if (i ==  501 ||
	    i ==  601 ||
	    i ==  892 ||
	    i ==  895 ||
	    i ==  992 ||
	    i ==  995 ||
	    i == 1092 ||
	    i == 1095 ||
	    i == 1192 ||
	    i == 1195) {
	maskedBXs_[counter] = 1;
	if (counter != 0)
	  maskedBXs_[counter-1] = 1;
	if (counter != NBXS_PER_ORBIT-1)
	  maskedBXs_[counter+1] = 1;
	}
	beam_[counter++] = 0;
	nBxOff_++;
      }
    } 
  }
  else if (beamStructure_ == 11) {
    // Single_12b_8_8_8
    for (i = 0; i < NBXS_PER_ORBIT; i++) {
      if (i ==    1 ||
	  i ==  201 ||
	  i ==  401 ||
	  i ==  601 ||
	  i == 1786 ||
	  i == 1986 ||
	  i == 2186 ||
	  i == 2386 ) {

	maskedBXs_[counter] = 1;
	if (counter != 0)
	  maskedBXs_[counter-1] = 1;
	if (counter != NBXS_PER_ORBIT-1)
	  maskedBXs_[counter+1] = 1;

	collisions_.push_back(i);
	beam_[counter++] = 1;
	nBxOn_++;
      }
      else {
	if (i ==  892 ||
	    i ==  895 ||
	    i == 1092 ||
	    i == 1095 ||
	    i == 1292 ||
	    i == 1295 ||
	    i == 1492 ||
	    i == 1495
	    ) {
	maskedBXs_[counter] = 1;
	if (counter != 0)
	  maskedBXs_[counter-1] = 1;
	if (counter != NBXS_PER_ORBIT-1)
	  maskedBXs_[counter+1] = 1;
	}
	beam_[counter++] = 0;
	nBxOff_++;
      }
    }
  }
  else if (beamStructure_ == 9) {
    for (i = 0; i < NBXS_PER_ORBIT; i++) {
      if (i ==   51 ||
	  i ==  151 ||
	  i ==  232 ||
	  i == 1042 ||
	  i == 1123 ||
	  i == 1933 ||
	  i == 2014 ||
	  i == 2824 ||
	  i == 2905) {
	collisions_.push_back(i);
	beam_[counter++] = 1;
	nBxOn_++;
      }
      else {
	beam_[counter++] = 0;
	nBxOff_++;
      }
    } 
  }
  else if (beamStructure_ == 156) {

    for (i=0; i<4; i++) {
      for (j=0; j<3; j++) {
        unsigned int n=12;
        if (i==0 && j==0) n=8;
        if (j==2) n=16;
        for (k=0; k<n; k++) {
	  collisions_.push_back(counter);
          beam_[counter++]=1;
          nBxOn_++;
          for (l=0; l<20; l++) {
            beam_[counter++]=0;
            nBxOff_++;
          }
        }
        for (k=0; k<17; k++) {
          beam_[counter++]=0;
          nBxOff_++;
        }
      }
    }

    for (l=0; l<84; l++) {
      beam_[counter++]=0;
      nBxOff_++;
    }

  }

  // 75ns spacing
  else if (beamStructure_ == 936) {
    for (i = 1; i <= 4; i++) {

      for (j = 1; j <= 3; j++) {

        for (k = 1; k <= (j == 3 && i < 4 ? 4 : 3); k++) {
          for (l = 1; l <= 72; l++) {
            if (l % 3 == 1) {
	      collisions_.push_back(counter);
              beam_[counter++] = 1;
              nBxOn_++;
            }
            else {
              beam_[counter++] = 0;
              nBxOff_++;
            }
          }
          for (l = 1; l <= 8; l++) {
            beam_[counter++] = 0;
            nBxOff_++;
          }
        }

        for (k = 1; k <= 30; k++) {
          beam_[counter++] = 0;
          nBxOff_++;
        }

      }

      beam_[counter++] = 0;
      nBxOff_++;
    }

    for (i = 1; i <= 8 + 72; i++) {
      beam_[counter++] = 0;
      nBxOff_++;
    }
  }

    else if (beamStructure_ == 2808) {
    for (i = 1; i <= 4; i++) {

      for (j = 1; j <= 3; j++) {

        for (k = 1; k <= (j == 3 && i < 4 ? 4 : 3); k++) {
          for (l = 1; l <= 72; l++) {
	    collisions_.push_back(counter);
            beam_[counter++] = 1;
            nBxOn_++;
          }
          for (l = 1; l <= 8; l++) {
            beam_[counter++] = 0;
            nBxOff_++;
          }
        }

        for (k = 1; k <= 30; k++) {
          beam_[counter++] = 0;
          nBxOff_++;
        }

      }

      beam_[counter++] = 0;
      nBxOff_++;
    }

    for (i = 1; i <= 8 + 72; i++) {
      beam_[counter++] = 0;
      nBxOff_++;
    }
  }
  else
    assert(0); //Unknown bunch structure!

  //  assert(bxs_on  == bx_struct);
  assert(counter == NBXS_PER_ORBIT);
}


void Simulator::setFillScheme(unsigned fill) {

  std::cout << "Using filling scheme " << fills_.getFillingScheme(fill) << std::endl;

  std::vector<unsigned> colls = fills_.getCollisions(fill);
  std::vector<unsigned> bunches = fills_.getBunches(fill);

  // loop over orbit
  for (unsigned i=0; i<NBXS_PER_ORBIT; ++i) {

    // first do collisions
    for (unsigned j=0; j<colls.size(); ++j) {
      if (colls.at(j) == i) {
	nBxOn_++;
	beam_[i] = true;
      }
      else {
	nBxOff_++;
	beam_[i] = false;
      }
    }

    // then do masks
    maskedBXs_.at(i) = false;
    for (unsigned j=0; j<colls.size(); ++j) {
      unsigned bunch=bunches.at(j);
      if (bunch >= i-1 && bunch <= i+1) maskedBXs_.at(i) = true;
    }

  }

  collisions_ = colls;

}


void Simulator::run(Experiment &e) {

  // set up luminosity data
  setupLumi(e.fills);
  
  // set up LHC filling scheme
  if (!e.isProjection) {
    std::cout << "Simulating fill " << e.fills.at(0) << std::endl;
    setFillScheme(e.fills.at(0));
  }
  else {
    setupBxStructure(e.bxStruct);
  }
  
  // reset plots
  clearPlots();
  setupPlots();

  for (unsigned int i = 0; i < collisions_.size(); i++) {
    run_specific_plots["bunch_structure"]->Fill(collisions_[i]);
  }

  setupLifetimeBxMasking(e.lifetime);

  simulateSignal(e);
  simulateBackground(e);
}

void Simulator::setupLifetimeBxMasking(double lifetime) {

  unsigned int unmaskedBxs = 0;

  int mostRecentOn = -1;
  for (unsigned int i = 0; i < NBXS_PER_ORBIT; i++) {
    if (beam_[i]) {
      mostRecentOn = i;
      lifetimeMask_[i] = false; // but will be blocked by other factors
    }
    else if (mostRecentOn == -1) {
      lifetimeMask_[i] = true;
    }
    else {
      lifetimeMask_[i] =
	(( i - mostRecentOn ) * TIME_PER_BUNCH > 1.256 * lifetime);
    }
    if (!lifetimeMask_[i] && !maskedBXs_[i])
      unmaskedBxs++;
  }
  mostRecentOn -= NBXS_PER_ORBIT;
  for (unsigned int i = 0; i < NBXS_PER_ORBIT && !beam_[i]; i++) {
      lifetimeMask_[i] =
	(( i - mostRecentOn ) * TIME_PER_BUNCH > 1.256 * lifetime);    
      if (!lifetimeMask_[i] && !maskedBXs_[i])
	unmaskedBxs++;
  }

  std::cerr << "Bxs available for observation: "
	    << unmaskedBxs << std::endl;
}

void Simulator::simulateSignal(Experiment &e) {

  unsigned int signal_events = 0;
  double generated_decays = 0;
  unsigned vetoes = 0;

  //Steps involved in running:

  for (unsigned ls = 0; ls < lumi_.size(); ls++) {
    if (ls * TIME_PER_LS > 24*3600*e.runningTime) break;
    //    if (lumi_.lumis[ls].cms_sensitivity < 0.01) continue;

    // calculate decays for an on-bunch
    
    double nDecays =
      // Amount of time 
      e.scale * TIME_PER_LS
      // Events / time
      * e.crossSection * lumi_.luminosity(ls)
      // Efficiencies
      * e.signalEff;

    assert (nDecays < 4294967296.); // 2^32, too many decays!!
    generated_decays += nDecays;

    for (unsigned int decay = 1; decay < nDecays + 1; decay++) {
      // Don't truncate the last fraction of an event:
      //  Randomly determine whether to use it
      if (decay > nDecays && 
	  (random_.Rndm() < decay-nDecays)) break;

      // Find the time of a decay
      
      double       tau                  = random_.Exp(e.lifetime);
      unsigned int tau_in_LSs           = 
	(unsigned int) (tau / TIME_PER_LS);
      unsigned int tau_remainder_in_bxs = 
	(unsigned int) ((tau - tau_in_LSs) / TIME_PER_BUNCH);

      unsigned int bxs_from_originating_l1a = 0;
      if (tau <= 240 * TIME_PER_BUNCH)
	bxs_from_originating_l1a = (unsigned int)(tau/TIME_PER_BUNCH);
      
      // Since each productions are approx equally distributed among
      // orbits in a LS, simulate all of them at once,
      // and randomly assign them.
      unsigned int start_bx = collisions_[random_.Integer(collisions_.size())];      
      unsigned int start_orbit = random_.Integer(NORBITS_PER_LS);
      
      unsigned int tau_remainder_in_orbits    =  
	(tau_remainder_in_bxs / NBXS_PER_ORBIT);
      unsigned int tau_remainder_within_orbit =
	(tau_remainder_in_bxs % NBXS_PER_ORBIT);
      unsigned int decay_bx = start_bx + tau_remainder_within_orbit;
      if (decay_bx >= NBXS_PER_ORBIT) {
	decay_bx -= NBXS_PER_ORBIT;
	++tau_remainder_in_orbits;
      }
      assert(decay_bx < NBXS_PER_ORBIT);
      
      unsigned int decay_orbit =
	start_orbit + tau_remainder_in_orbits;
      while (decay_orbit >= NORBITS_PER_LS) {
	decay_orbit -= NORBITS_PER_LS;
	++tau_in_LSs;
      }      
      
      unsigned int decay_ls =
	ls + tau_in_LSs;
      
      /*
      double decay_within_bx =
	random_.Rndm() * TIME_PER_BUNCH;
      */      

      // Store the result
      
      if (decay_ls > lumi_.size() ||
	  (decay_ls * TIME_PER_LS > e.runningTime * 24. * 3600))
	continue;

      run_specific_plots["decays_in_beam"]->Fill(decay_bx);

      bool take_event = false;
      if ((e.lookwhere == e.BEAMGAP || e.lookwhere == e.BOTH)
	  //&& lumi_[decay_ls] > 4.28e26 // have beam
	  //&& lumi_[decay_ls] > 1 // have beam
	  && lumi_.cmsSensitive(decay_ls)
	  && !beam_[decay_bx]
	  && !maskedBXs_[decay_bx]
	  && (!lifetimeMask_[decay_bx] || !e.optimizeTimeCut)
	  ) {
	take_event = true;
	// do specific beamgap stuff
      }
      else if ((e.lookwhere == e.INTERFILL || e.lookwhere == e.BOTH)
	       && lumi_.cmsSensitive(decay_ls)
	       && lumi_.luminosity(decay_ls) < 1) { // no beam
	take_event = true;

	if (e.optimizeTimeCut) {
	  unsigned int i;
	  for (i = decay_ls; lumi_.luminosity(i) < 1; i--);
	  if ((decay_ls - i - 1) * TIME_PER_LS >
	      e.lifetime * 1.256) 
	    take_event = false;
	}
	    
	// do specific interfill stuff
      }
      if (take_event) {
	// do common beamgap AND interfill stuff
	if (isTriggerBlocked(e, decay_bx,
			     bxs_from_originating_l1a)) {
	  vetoes++;
	  run_specific_plots["vetoed_events"]->Fill(decay_bx);
	  //continue;
	}
	signal_events++;
	run_specific_plots["longtime"]->Fill((decay_ls * TIME_PER_LS +
					      decay_orbit * TIME_PER_ORBIT)
					     / 24 / 3600);
	run_specific_plots["sensitive_in_beam"]->Fill(decay_bx);

	if (e.sendToLifetimeFit &&
	    random_.Integer((unsigned int)e.scale) == 0)
	  sendEventToLifetimeFit(decay_ls, decay_orbit, decay_bx);
      }
    }
  }

  e.nSig_d = signal_events / e.scale;
  e.nSig_d_statErr = TMath::Sqrt(signal_events) / e.scale;
  e.nSig = (unsigned int) (signal_events/e.scale);
  e.nGeneratedDecays = (generated_decays/e.scale);
  e.nVetoes = (vetoes/e.scale);
}

void Simulator::simulateBackground(Experiment &e) {

  double nHits =
    e.bgRate * e.bgScale * TIME_PER_LS * lumi_.size();

  assert (nHits < 4294967296.); // 2^32, too many hits!!

  unsigned int background_events = 0;

  for (unsigned hit = 1; hit < nHits + 1; hit ++) {
    // Don't truncate the last fraction of an event:
    //  Randomly determine whether to use it
    if (hit > nHits && 
	(random_.Rndm() < hit-nHits)) break;
    
    unsigned int ls    = random_.Integer(lumi_.size());
    unsigned int orbit = random_.Integer(NORBITS_PER_LS);
    unsigned int bx    = random_.Integer(NBXS_PER_ORBIT);

    if (ls * TIME_PER_LS > 3600 * 24 * e.runningTime) continue;

    bool take_event = false;
    if ((e.lookwhere == e.BEAMGAP || e.lookwhere == e.BOTH)
	//&& lumi_[ls] > 4.28e26 // have beam
	//&& lumi_[ls] > 1 // have beam
	&& lumi_.cmsSensitive(ls)
	&& !beam_[bx]
	&& !maskedBXs_[bx]
	&& (!lifetimeMask_[bx] || !e.optimizeTimeCut)) {      take_event = true;
      // do specific beamgap stuff
    }
    else if ((e.lookwhere == e.INTERFILL || e.lookwhere == e.BOTH)
	     && lumi_.cmsSensitive(ls)
	     && lumi_.luminosity(ls) < 1) { // no beam
      take_event = true;

      if (e.optimizeTimeCut) {
	unsigned int i;
	for (i = ls; lumi_.luminosity(i) < 1 && i > 0; i--);
	if (i==0) take_event = false;
	if ((ls - i - 1) * TIME_PER_LS >
	    e.lifetime * 1.256) 
	  take_event = false;
      }    
      
      // do specific interfill stuff
    }
    if (take_event) {
      // do common beamgap AND interfill stuff
      ++background_events;
      if (e.sendToLifetimeFit &&
	  random_.Integer((unsigned int)e.bgScale) == 0)
	sendEventToLifetimeFit(ls, orbit, bx);
    }
  }

  e.nBg = (unsigned int)(background_events / e.bgScale);
  e.nExpectedBg = background_events / e.bgScale;
  e.nExpectedBg_statErr = TMath::Sqrt(background_events)/e.bgScale;
}
