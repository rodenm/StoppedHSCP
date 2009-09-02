#include "Simulator.h"
#include <assert.h>
#include <iostream>

Simulator::Simulator() 
  : bx_struct(0)
{
}

void Simulator::clearPlots() {
  for (std::map<std::string, TH1D *>::iterator it = run_specific_plots.begin();
       it != run_specific_plots.end(); it++)
    delete it->second;
  run_specific_plots.clear();
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
}

void Simulator::setupLumi(std::istream &input) {

  // ignore input for now, flat lumi assumption

  lumis_by_section.clear();
  lumis_by_section.reserve(32*924); // so the "new"s don't take forever

  for (int i = 0; i < 32; i++) {
    for (int j = 0; j < 308; j++) //8hr
      //for (int j = 0; j < 462; j++) //12hr
      lumis_by_section.push_back(1e32);
    for (int j = 0; j < 616; j++) //16hr
      //for (int j = 0; j < 462; j++)
      lumis_by_section.push_back(0);
  }
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

  if (bx_struct == 156) {

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

  assert(bxs_on  == bx_struct);
  assert(counter == NBXS_PER_ORBIT);
}

void Simulator::run(Experiment &e) {
  setupBxStructure(e.bxStruct);
  clearPlots();
  setupPlots();

  for (unsigned int i = 0; i < on_bxs.size(); i++) {
    run_specific_plots["bunch_structure"]->Fill(on_bxs[i]);
  }

  simulateSignal(e);
  simulateBackground(e);
}

void Simulator::simulateSignal(Experiment &e) {

  unsigned int signal_events = 0;
  double generated_decays = 0;

  //Steps involved in running:

  for (unsigned ls = 0; ls < lumis_by_section.size(); ls++) {
    if (ls * TIME_PER_LS > 24*3600*e.runningTime) break;

    // calculate decays for an on-bunch
    
    double nDecays =
      // Amount of time 
      e.scale * TIME_PER_LS
      // Events / time
      * e.crossSection * lumis_by_section[ls]
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
      
      double decay_within_bx =
	rndm.Rndm() * TIME_PER_BUNCH;
      
      // Store the result
      
      if (decay_ls > lumis_by_section.size() ||
	  (decay_ls * TIME_PER_LS > e.runningTime * 24. * 3600))
	continue;

      run_specific_plots["decays_in_beam"]->Fill(decay_bx);

      bool take_event = false;
      if ((e.lookwhere == e.BEAMGAP || e.lookwhere == e.BOTH)
	  && lumis_by_section[decay_ls] > 1 // have beam
	  && !beam[decay_bx]) {
	take_event = true;
	// do specific beamgap stuff
      }
      else if ((e.lookwhere == e.INTERFILL || e.lookwhere == e.BOTH)
	&& lumis_by_section[decay_ls] < 1) { // no beam
	take_event = true;

	if (e.optimizeTimeCut) {
	  unsigned int i;
	  for (i = decay_ls; lumis_by_section[i] < 1; i--);
	  if ((decay_ls - i - 1) * TIME_PER_LS >
	      e.lifetime * 1.256) 
	    take_event = false;
	}
	    
	// do specific interfill stuff
      }
      if (take_event) {
	// do common beamgap AND interfill stuff
	signal_events++;
	run_specific_plots["longtime"]->Fill((decay_ls * TIME_PER_LS +
					      decay_orbit * TIME_PER_ORBIT)
					     / 24 / 3600);
	run_specific_plots["sensitive_in_beam"]->Fill(decay_bx);
      }
    }
  }

  e.nSig = (unsigned int) (signal_events/e.scale);
  e.nGeneratedDecays = (unsigned int) (generated_decays/e.scale);
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
	&& lumis_by_section[ls] > 1 // have beam
	&& !beam[bx]) {
      take_event = true;
      // do specific beamgap stuff
    }
    else if ((e.lookwhere == e.INTERFILL || e.lookwhere == e.BOTH)
	     && lumis_by_section[ls] < 1) { // no beam
      take_event = true;

      if (e.optimizeTimeCut) {
	unsigned int i;
	for (i = ls; lumis_by_section[i] < 1; i--);
	if ((ls - i - 1) * TIME_PER_LS >
	    e.lifetime * 1.256) 
	  take_event = false;
      }    
      
      // do specific interfill stuff
    }
    if (take_event) {
      // do common beamgap AND interfill stuff
      ++background_events;
    }
  }

  e.nBg = (unsigned int)(background_events / e.bgScale);
}
