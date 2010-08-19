#include "StoppedHSCP/ToyMC/interface/Simulator.h"
#include "TMath.h"
#include <assert.h>
#include <iostream>

Simulator::Simulator() 
  : bx_struct(0), 
    parasitic(NBXS_PER_ORBIT, 0),
    lifetimeMask(NBXS_PER_ORBIT, 0),    
    lifetimeFitOutput("events.root", "RECREATE"),
    t("events", "Event time structure")
{
  t.Branch("ls", &_ls, "ls/I");
  t.Branch("orbit", &_orbit, "orbit/I");
  t.Branch("bx", &_bx, "bx/I");

}

void Simulator::writeOutLifetimeFit() {
  lifetimeFitOutput.cd();
  t.Write();
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
  _ls = (int)ls;
  _orbit = (int)orbit;
  _bx = (int)bx;

  t.Fill();

}

bool Simulator::collisionHasL1A(double rate) {
  return rndm.Rndm() < rate * TIME_PER_BUNCH * bxs_on / NBXS_PER_ORBIT;
}

bool Simulator::isTriggerBlocked(const Experiment &e, unsigned int bx,
				 unsigned int bxs_from_originating_l1a) {
  unsigned int other_l1as = 0;
  int new_bx;
  if (bxs_from_originating_l1a != 0 &&
      bxs_from_originating_l1a < 3) return true;
  for (new_bx = bx - 1; new_bx >= ((int)bx) - 2; new_bx--) {
    int bx_to_check = (new_bx >= 0 ? new_bx : new_bx + NBXS_PER_ORBIT);
    if (beam[bx_to_check] && collisionHasL1A(e.collisionL1Arate)) return true;
  }
  if (bxs_from_originating_l1a >= 3 &&
      bxs_from_originating_l1a < 8) other_l1as++;
  for (; new_bx >= ((int)bx) - 7; new_bx--) {
    int bx_to_check = (new_bx >= 0 ? new_bx : new_bx + NBXS_PER_ORBIT);
    if (beam[bx_to_check] && collisionHasL1A(e.collisionL1Arate))
      other_l1as++;
  }
  if (other_l1as > 1) return true;
  if (bxs_from_originating_l1a >= 8 &&
      bxs_from_originating_l1a < 100) other_l1as++;
  for (; new_bx >= ((int)bx) - 99; new_bx--) {
    int bx_to_check = (new_bx >= 0 ? new_bx : new_bx + NBXS_PER_ORBIT);
    if (beam[bx_to_check] && collisionHasL1A(e.collisionL1Arate))
      other_l1as++;
  }
  if (other_l1as > 2) return true;
  if (bxs_from_originating_l1a >= 100 &&
      bxs_from_originating_l1a < 240) other_l1as++;
  for (; new_bx >= ((int)bx) - 239; new_bx--) {
    int bx_to_check = (new_bx >= 0 ? new_bx : new_bx + NBXS_PER_ORBIT);
    if (beam[bx_to_check] && collisionHasL1A(e.collisionL1Arate))
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

  lumis_by_section.buildFromFile(runs);

}

void Simulator::setupBxStructure(unsigned int bx_struct_in) {
  if (bx_struct == bx_struct_in) return;

  // set up bunch structure
  unsigned int i, j, k, l, counter = 0;

  bx_struct = bx_struct_in;
  bxs_on    = 0;
  bxs_off   = 0;
  on_bxs.clear();
  on_bxs.reserve(bx_struct_in);

  // December 09 run 124230
  if (bx_struct == 2) {
    for (i = 0; i < NBXS_PER_ORBIT; i++) {
      //      if (i ==    0 ||
      //	  i == 1782) {
      if (i ==    1 ||
	  i == 1786) {
	on_bxs.push_back(i);
	beam[counter] = 1;
	parasitic[counter-1] = 1;
	parasitic[counter] = 1;
	parasitic[counter+1] = 1;
	counter++;
	bxs_on++;
      }
      else {
	beam[counter++] = 0;
	bxs_off++;
      }
    } 
    parasitic[891] = 1;
    parasitic[892] = 1;
    parasitic[893] = 1;
    parasitic[894] = 1;
    parasitic[895] = 1;
    parasitic[896] = 1;

  }
  else if (bx_struct == 3) {
    for (i = 0; i < NBXS_PER_ORBIT; i++) {
      if (i ==    1 ||
	  i ==  201 ||
	  i ==  401) {

	parasitic[counter] = 1;
	if (counter != 0)
	  parasitic[counter-1] = 1;
	if (counter != NBXS_PER_ORBIT-1)
	  parasitic[counter+1] = 1;

	on_bxs.push_back(i);
	beam[counter++] = 1;
	bxs_on++;
      }
      else {
	beam[counter++] = 0;
	bxs_off++;
      }
    }     
  }
  else if (bx_struct == 4) {
    for (i = 0; i < NBXS_PER_ORBIT; i++) {
      if (i ==    1 ||
	  i ==  101 ||
	  i == 1786 ||
	  i == 1886) {

	parasitic[counter] = 1;
	if (counter != 0)
	  parasitic[counter-1] = 1;
	if (counter != NBXS_PER_ORBIT-1)
	  parasitic[counter+1] = 1;

	on_bxs.push_back(i);
	beam[counter++] = 1;
	bxs_on++;
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
	parasitic[counter] = 1;
	if (counter != 0)
	  parasitic[counter-1] = 1;
	if (counter != NBXS_PER_ORBIT-1)
	  parasitic[counter+1] = 1;
	}
	beam[counter++] = 0;
	bxs_off++;
      }
    } 
  }
  else if (bx_struct == 5) {
    // Single_10b_4_2_4
    for (i = 0; i < NBXS_PER_ORBIT; i++) {
      if (i ==    1 ||
	  i ==  201 ||
	  i ==  401 ||
	  i ==  601) {

	parasitic[counter] = 1;
	if (counter != 0)
	  parasitic[counter-1] = 1;
	if (counter != NBXS_PER_ORBIT-1)
	  parasitic[counter+1] = 1;

	on_bxs.push_back(i);
	beam[counter++] = 1;
	bxs_on++;
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
	parasitic[counter] = 1;
	if (counter != 0)
	  parasitic[counter-1] = 1;
	if (counter != NBXS_PER_ORBIT-1)
	  parasitic[counter+1] = 1;
	}
	beam[counter++] = 0;
	bxs_off++;
      }
    } 
  }
  else if (bx_struct == 6) {
    for (i = 0; i < NBXS_PER_ORBIT; i++) {
      if (i ==    1 ||
	  i ==  201 ||
	  i ==  401 ||
	  i == 1786 ||
	  i == 1986 ||
	  i == 2186) {

	parasitic[counter] = 1;
	if (counter != 0)
	  parasitic[counter-1] = 1;
	if (counter != NBXS_PER_ORBIT-1)
	  parasitic[counter+1] = 1;

	on_bxs.push_back(i);
	beam[counter++] = 1;
	bxs_on++;
      }
      else {
	if (i ==  892 ||
	    i ==  895 ||
	    i == 1092 ||
	    i == 1095 ||
	    i == 1292 ||
	    i == 1295
	    ) {
	parasitic[counter] = 1;
	if (counter != 0)
	  parasitic[counter-1] = 1;
	if (counter != NBXS_PER_ORBIT-1)
	  parasitic[counter+1] = 1;
	}
	beam[counter++] = 0;
	bxs_off++;
      }
    } 
  }
  else if (bx_struct == 8) {
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

	parasitic[counter] = 1;
	if (counter != 0)
	  parasitic[counter-1] = 1;
	if (counter != NBXS_PER_ORBIT-1)
	  parasitic[counter+1] = 1;

	on_bxs.push_back(i);
	beam[counter++] = 1;
	bxs_on++;
      }
      else {
	if (i ==  894 ||
	    i ==  994 ||
	    i == 1094 ||
	    i == 1194) {
	parasitic[counter] = 1;
	if (counter != 0)
	  parasitic[counter-1] = 1;
	if (counter != NBXS_PER_ORBIT-1)
	  parasitic[counter+1] = 1;
	}
	beam[counter++] = 0;
	bxs_off++;
      }
    } 
  }
  else if (bx_struct == 10) {
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

	parasitic[counter] = 1;
	if (counter != 0)
	  parasitic[counter-1] = 1;
	if (counter != NBXS_PER_ORBIT-1)
	  parasitic[counter+1] = 1;

	on_bxs.push_back(i);
	beam[counter++] = 1;
	bxs_on++;
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
	parasitic[counter] = 1;
	if (counter != 0)
	  parasitic[counter-1] = 1;
	if (counter != NBXS_PER_ORBIT-1)
	  parasitic[counter+1] = 1;
	}
	beam[counter++] = 0;
	bxs_off++;
      }
    } 
  }
  else if (bx_struct == 11) {
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

	parasitic[counter] = 1;
	if (counter != 0)
	  parasitic[counter-1] = 1;
	if (counter != NBXS_PER_ORBIT-1)
	  parasitic[counter+1] = 1;

	on_bxs.push_back(i);
	beam[counter++] = 1;
	bxs_on++;
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
	parasitic[counter] = 1;
	if (counter != 0)
	  parasitic[counter-1] = 1;
	if (counter != NBXS_PER_ORBIT-1)
	  parasitic[counter+1] = 1;
	}
	beam[counter++] = 0;
	bxs_off++;
      }
    }
  }
  else if (bx_struct == 9) {
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
	on_bxs.push_back(i);
	beam[counter++] = 1;
	bxs_on++;
      }
      else {
	beam[counter++] = 0;
	bxs_off++;
      }
    } 
  }
  else if (bx_struct == 156) {

    for (i=0; i<4; i++) {
      for (j=0; j<3; j++) {
        unsigned int n=12;
        if (i==0 && j==0) n=8;
        if (j==2) n=16;
        for (k=0; k<n; k++) {
	  on_bxs.push_back(counter);
          beam[counter++]=1;
          bxs_on++;
          for (l=0; l<20; l++) {
            beam[counter++]=0;
            bxs_off++;
          }
        }
        for (k=0; k<17; k++) {
          beam[counter++]=0;
          bxs_off++;
        }
      }
    }

    for (l=0; l<84; l++) {
      beam[counter++]=0;
      bxs_off++;
    }

  }

  // 75ns spacing
  else if (bx_struct == 936) {
    for (i = 1; i <= 4; i++) {

      for (j = 1; j <= 3; j++) {

        for (k = 1; k <= (j == 3 && i < 4 ? 4 : 3); k++) {
          for (l = 1; l <= 72; l++) {
            if (l % 3 == 1) {
	      on_bxs.push_back(counter);
              beam[counter++] = 1;
              bxs_on++;
            }
            else {
              beam[counter++] = 0;
              bxs_off++;
            }
          }
          for (l = 1; l <= 8; l++) {
            beam[counter++] = 0;
            bxs_off++;
          }
        }

        for (k = 1; k <= 30; k++) {
          beam[counter++] = 0;
          bxs_off++;
        }

      }

      beam[counter++] = 0;
      bxs_off++;
    }

    for (i = 1; i <= 8 + 72; i++) {
      beam[counter++] = 0;
      bxs_off++;
    }
  }

    else if (bx_struct == 2808) {
    for (i = 1; i <= 4; i++) {

      for (j = 1; j <= 3; j++) {

        for (k = 1; k <= (j == 3 && i < 4 ? 4 : 3); k++) {
          for (l = 1; l <= 72; l++) {
	    on_bxs.push_back(counter);
            beam[counter++] = 1;
            bxs_on++;
          }
          for (l = 1; l <= 8; l++) {
            beam[counter++] = 0;
            bxs_off++;
          }
        }

        for (k = 1; k <= 30; k++) {
          beam[counter++] = 0;
          bxs_off++;
        }

      }

      beam[counter++] = 0;
      bxs_off++;
    }

    for (i = 1; i <= 8 + 72; i++) {
      beam[counter++] = 0;
      bxs_off++;
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
	bxs_on++;
	beam[i] = true;
      }
      else {
	bxs_off++;
	beam[i] = false;
      }
    }

    // then do masks
    parasitic.at(i) = false;
    for (unsigned j=0; j<colls.size(); ++j) {
      unsigned bunch=bunches.at(j);
      if (bunch >= i-1 && bunch <= i+1) parasitic.at(i) = true;
    }

  }

  on_bxs = colls;

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

  for (unsigned int i = 0; i < on_bxs.size(); i++) {
    run_specific_plots["bunch_structure"]->Fill(on_bxs[i]);
  }

  setupLifetimeBxMasking(e.lifetime);

  simulateSignal(e);
  simulateBackground(e);
}

void Simulator::setupLifetimeBxMasking(double lifetime) {

  unsigned int unmaskedBxs = 0;

  int mostRecentOn = -1;
  for (unsigned int i = 0; i < NBXS_PER_ORBIT; i++) {
    if (beam[i]) {
      mostRecentOn = i;
      lifetimeMask[i] = false; // but will be blocked by other factors
    }
    else if (mostRecentOn == -1) {
      lifetimeMask[i] = true;
    }
    else {
      lifetimeMask[i] =
	(( i - mostRecentOn ) * TIME_PER_BUNCH > 1.256 * lifetime);
    }
    if (!lifetimeMask[i] && !parasitic[i])
      unmaskedBxs++;
  }
  mostRecentOn -= NBXS_PER_ORBIT;
  for (unsigned int i = 0; i < NBXS_PER_ORBIT && !beam[i]; i++) {
      lifetimeMask[i] =
	(( i - mostRecentOn ) * TIME_PER_BUNCH > 1.256 * lifetime);    
      if (!lifetimeMask[i] && !parasitic[i])
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

  for (unsigned ls = 0; ls < lumis_by_section.size(); ls++) {
    if (ls * TIME_PER_LS > 24*3600*e.runningTime) break;
    //    if (lumis_by_section.lumis[ls].cms_sensitivity < 0.01) continue;

    // calculate decays for an on-bunch
    
    double nDecays =
      // Amount of time 
      e.scale * TIME_PER_LS
      // Events / time
      * e.crossSection * lumis_by_section.luminosity(ls)
      // Efficiencies
      * e.signalEff;

    assert (nDecays < 4294967296.); // 2^32, too many decays!!
    generated_decays += nDecays;

    for (unsigned int decay = 1; decay < nDecays + 1; decay++) {
      // Don't truncate the last fraction of an event:
      //  Randomly determine whether to use it
      if (decay > nDecays && 
	  (rndm.Rndm() < decay-nDecays)) break;

      // Find the time of a decay
      
      double       tau                  = rndm.Exp(e.lifetime);
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
      unsigned int start_bx = on_bxs[rndm.Integer(on_bxs.size())];      
      unsigned int start_orbit = rndm.Integer(NORBITS_PER_LS);
      
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
	rndm.Rndm() * TIME_PER_BUNCH;
      */      

      // Store the result
      
      if (decay_ls > lumis_by_section.size() ||
	  (decay_ls * TIME_PER_LS > e.runningTime * 24. * 3600))
	continue;

      run_specific_plots["decays_in_beam"]->Fill(decay_bx);

      bool take_event = false;
      if ((e.lookwhere == e.BEAMGAP || e.lookwhere == e.BOTH)
	  //&& lumis_by_section[decay_ls] > 4.28e26 // have beam
	  //&& lumis_by_section[decay_ls] > 1 // have beam
	  && lumis_by_section.cmsSensitive(decay_ls)
	  && !beam[decay_bx]
	  && !parasitic[decay_bx]
	  && (!lifetimeMask[decay_bx] || !e.optimizeTimeCut)
	  ) {
	take_event = true;
	// do specific beamgap stuff
      }
      else if ((e.lookwhere == e.INTERFILL || e.lookwhere == e.BOTH)
	       && lumis_by_section.cmsSensitive(decay_ls)
	       && lumis_by_section.luminosity(decay_ls) < 1) { // no beam
	take_event = true;

	if (e.optimizeTimeCut) {
	  unsigned int i;
	  for (i = decay_ls; lumis_by_section.luminosity(i) < 1; i--);
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
	    rndm.Integer((unsigned int)e.scale) == 0)
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
    e.bgRate * e.bgScale * TIME_PER_LS * lumis_by_section.size();

  assert (nHits < 4294967296.); // 2^32, too many hits!!

  unsigned int background_events = 0;

  for (unsigned hit = 1; hit < nHits + 1; hit ++) {
    // Don't truncate the last fraction of an event:
    //  Randomly determine whether to use it
    if (hit > nHits && 
	(rndm.Rndm() < hit-nHits)) break;
    
    unsigned int ls    = rndm.Integer(lumis_by_section.size());
    unsigned int orbit = rndm.Integer(NORBITS_PER_LS);
    unsigned int bx    = rndm.Integer(NBXS_PER_ORBIT);

    if (ls * TIME_PER_LS > 3600 * 24 * e.runningTime) continue;

    bool take_event = false;
    if ((e.lookwhere == e.BEAMGAP || e.lookwhere == e.BOTH)
	//&& lumis_by_section[ls] > 4.28e26 // have beam
	//&& lumis_by_section[ls] > 1 // have beam
	&& lumis_by_section.cmsSensitive(ls)
	&& !beam[bx]
	&& !parasitic[bx]
	&& (!lifetimeMask[bx] || !e.optimizeTimeCut)) {      take_event = true;
      // do specific beamgap stuff
    }
    else if ((e.lookwhere == e.INTERFILL || e.lookwhere == e.BOTH)
	     && lumis_by_section.cmsSensitive(ls)
	     && lumis_by_section.luminosity(ls) < 1) { // no beam
      take_event = true;

      if (e.optimizeTimeCut) {
	unsigned int i;
	for (i = ls; lumis_by_section.luminosity(i) < 1 && i > 0; i--);
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
	  rndm.Integer((unsigned int)e.bgScale) == 0)
	sendEventToLifetimeFit(ls, orbit, bx);
    }
  }

  e.nBg = (unsigned int)(background_events / e.bgScale);
  e.nExpectedBg = background_events / e.bgScale;
  e.nExpectedBg_statErr = TMath::Sqrt(background_events)/e.bgScale;
}
