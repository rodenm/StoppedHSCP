//------------------------------------------------
//
//  Toy Stopped HSCP experiment
//  Run repeated
//
//------------------------------------------------


#include <iostream>

#include "TH1D.h"
#include "TRandom.h"
#include "TGraph.h"
#include "TCanvas.h"

class ToyStoppedHSCP {
public:

  ToyStoppedHSCP();
  ~ToyStoppedHSCP();

  // setup bunch structure
  void setupBunches(int bx_struct);  // use 2808 for now

  // one experiment
  void setLumi(double l) { lumi = l; }
  void setCrossSection(double xs) { xsection = xs; }
  void setLifetime(double l) { lifetime = l; }
  void setRunningTime(int nd) { days = nd; }
  void runOnce();

  // multiple experiments
  void readParams();

  void makeSigGraphs(int nlifetimes, int npoints);


  // plot stuff
  void plotSig();


private:

  // bunch structure
  static const unsigned bxs = 3564; //  = 3564;
  int bx_struct;    // LHC filling pattern 
  double bctime;    //  = 25e-9 bunch crossing time
  unsigned bxs_on;
  unsigned bxs_off;
  unsigned char beam[3564];

  // Single experiment parameters
  double lumi;
  double xsection;
  // m~g 200 GeV, 1e-32
  // m~g 300 GeV, 1e-33
  // m~g 500 GeV, 1e-34
  // m~g 900 GeV, 0.5e-36
  // m~g 1200 GeV, 1e-36 
  double lifetime;
  int days;

  // Single experiment results
  double interFillSignificance;
  double bunchGapSignificance;
  double combinedSignificance;

  TH1D* hdecays;
  TH1D* hdecaysReg;
  TH1D* hperday;
  TH1D* hinday;
  
  // Multiple experiment parameters
  double lifetimes[10];
  double ndays[10];

  // graphs
  TGraph* cosmicSigGraph[10];
  TGraph* beamSigGraph[10];

};


ToyStoppedHSCP::ToyStoppedHSCP() :
  bxs_on(0),
  bxs_off(0),
  bx_struct(2808),
  bctime(25e-9)
{

  // setup BX structure histograms - TODO

  // setup single exp histograms
  TH1D::SetDefaultSumw2 (true);
  hdecays = new TH1D("hdecays","Number of Reconstructable Stopped Gluinos", bxs, 0, bxs);//days*24,0,days);
  
  hdecaysReg = new TH1D("hdecaysReg","Number of Reconstructable Stopped Gluinos", bxs, 0, bxs);//cycle);//days*24,0,days);
  hperday = new TH1D("hperday","Number of Reconstructed Stopped Gluinos", days,0,days);
  hinday = new TH1D("hinday", "Number of Reconstructed Stopped Gluinos", 100, 0, 24*3600);
  // hperday->SetMinimum(0);

}

ToyStoppedHSCP::~ToyStoppedHSCP() {

}


void ToyStoppedHSCP::setupBunches(int bx_struct) {

  // set up bunch structure
  int i, j, k, l, m, counter = 0;

  if (bx_struct == 156) {
    
    for (i=0; i<4; i++) {
      for (j=0; j<3; j++) {
	int n=12;
	if (i==0 && j==0) n=8;
	if (i!=0 && j==2) n=16;
	for (k=0; k<n; k++) {
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
  else if (bx_struct == 2808) {
    for (i = 1; i <= 4; i++) {
      
      for (j = 1; j <= 3; j++) {
	
	for (k = 1; k <= (j == 3 && i < 4 ? 4 : 3); k++) {
	  for (l = 1; l <= 72; l++) {
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
  
  cout << "LHC bunch scenario : " << bx_struct << "x" << bx_struct << endl;
  cout << "  Bunches on  : " << bxs_on << endl;
  cout << "  Bunches off : " << bxs_off << endl;
  cout << "  Total       : " << counter << endl;

  // fill BX structure histogram - TODO
  
}

void ToyStoppedHSCP::runOnce() {

  double bg_per_day = 43.2;    // background rate per day
  double efficiency = 0.16    // stopping efficiency from Fedor???
                    * 0.08;  // online+offline eff (wrt all stopped particles)

  cout << " Stopped HSCP Toy Experiment" << endl;
  cout << "  Lumi            = " << lumi << endl;
  cout << "  X-section       = " << xsection << endl;
  cout << "  Lifetime        = " << lifetime << endl;
  cout << "  Running time    = " << days << endl;
  cout << "  Sel eff         = " << efficiency << endl;
  cout << "  BG per day      = " << bg_per_day << endl;


  // experiment parameters
  
  double nOrbits    = 473000000; // number of orbits beam on???
  double nOrbitsOff = 473000000; // number of orbits beam off???

  //  program control
  bool signal_on = true;
  bool background_on = true;

  double scale = 1000;   // increase these parameters to increase precision
  double bgscale = 100;  // at the cost of running time.  100 or 1000 are good numbers to try

  double cycle = bctime*bxs;  // orbit length

  double tstep = bctime; //0.1 / (lumi * xsection * efficiency);
  double nDecays = lumi * tstep * xsection * efficiency;
  
  hdecays->Reset();
  hdecaysReg->Reset();
  hperday->Reset();
  hinday->Reset();

  TRandom rndm;
  
  
  int n;
  double t;
  
  double total_counts = 0, beam_counts = 0, cosmic_counts = 0;
  double s_total_counts = 0, s_beam_counts = 0, s_cosmic_counts = 0;
  double b_total_counts = 0, b_beam_counts = 0, b_cosmic_counts = 0;
  
  if (signal_on)
    for (t = 0, n = 0; n < bxs && signal_on; t += tstep, n++) {
      if (beam[n]) {
	int nRandomDecays = scale*nDecays*nOrbits*days; //rndm.Poisson;
	for (int ig = 0; ig < nRandomDecays ; ig++) {
	  
	  double tau = rndm.Exp (lifetime);
	  double tdecay = t + tau;
	  double cycletime = tdecay/cycle - floor (tdecay/cycle);
	  double cycles = tdecay/cycle;
	  
	  unsigned long orbit = rndm.Integer(nOrbits);
	  int day = rndm.Integer(days);
	  
	  hdecays->Fill (cycletime*bxs, 1./scale);
	  
	  //      if (cycletime > dutycycle) {
	  // at t==0, counter == 0, so rounding is correct:
	  
	  //      cout << "cycles " << cycles << endl;
	  
	  // Hope this is precise enough...
	  double quotient = (cycles + orbit)/(nOrbits+nOrbitsOff);
	  double remainder = (cycles + orbit) - floor(quotient)*(nOrbits+nOrbitsOff);
	  if (quotient+day >= days) continue;
	  if (remainder < nOrbits && !beam[ int(cycletime * bxs) ]) {
	    s_beam_counts+= 1/scale;
	    
	    hdecaysReg->Fill (cycletime*bxs, 1./scale);
	    hperday->Fill (quotient+day, 1./scale); 
	    hinday->Fill(remainder*bxs*bctime, 1./scale);
	  }
	  else if (remainder > nOrbits ) {
	    s_cosmic_counts+= 1/scale;
	    
	    hperday->Fill (quotient+day, 1./scale);
	    hinday->Fill(remainder*bxs*bctime, 1./scale);
	  }
	}
      }
    }
  
  // BACKGROUND
  if (background_on)
    for (int i = 0; i < days; i++) {
      
      int todays_rate = bg_per_day*bgscale;//rndm.Poisson(bg_per_day);
      
      for (int j = 0; j < todays_rate; j++) {
	
	// pick an orbit
	
	unsigned long orbit = rndm.Integer(nOrbits+nOrbitsOff);
	
	// pick a bin
	
	unsigned int bunch = rndm.Integer(bxs);
	
	// fill
	
	hdecays->Fill(bunch, 1./bgscale);
	if (orbit <= nOrbits && !beam[ bunch ]) {
	  b_beam_counts+=1./bgscale;
	  
	  hdecaysReg->Fill (bunch, 1./bgscale);
	  hperday->Fill (i, 1./bgscale); 
	  hinday->Fill((bunch+((double)orbit)*bxs)*bctime, 1./bgscale);
	}
	else if (orbit > nOrbits ) {
	  b_cosmic_counts+=1./bgscale;
	  
	  hperday->Fill (i, 1./bgscale);
	  hinday->Fill((bunch+((double)orbit)*bxs)*bctime, 1./bgscale);
	}
      }
    }
  
  beam_counts = s_beam_counts + b_beam_counts;
  cosmic_counts = s_cosmic_counts + b_cosmic_counts;
  s_total_counts = s_beam_counts + s_cosmic_counts;
  b_total_counts = b_beam_counts + b_cosmic_counts;
  total_counts = beam_counts + cosmic_counts;
  
  double expected_cosmic = bg_per_day * (nOrbitsOff)/(nOrbits+nOrbitsOff)*days;
  double expected_total = bg_per_day * (nOrbits*bxs_off/bxs + nOrbitsOff)/(nOrbits+nOrbitsOff)*days;
  double expected_beam = bg_per_day * (nOrbits*bxs_off/bxs)/(nOrbits+nOrbitsOff)*days;
  
  cout << "Combined experiment" << endl;
  //  cout << "  Total counts: " << total_counts << endl;
  //  cout << "  Expected N bg = " << expected_total << endl;
  //  cout << "  sigma:   " << sqrt(expected_total) << endl;
  cout << "  Experiment sig : " << (total_counts - expected_total)/sqrt(expected_total) << endl;
  cout << "  Expected sig   : " << (s_total_counts)/sqrt(expected_total) << endl << endl;
  combinedSignificance = (s_total_counts)/sqrt(expected_total);

  cout << "Beam experiment" << endl;
  cout << "  N signal      = " << s_beam_counts << endl;
  cout << "  N bg          = " << b_beam_counts << endl;
  //  cout << "  Expected N bg = " << expected_beam << endl;
  //  cout << "  sigma:   " << sqrt(expected_beam) << endl;
  cout << "  Experiment sig : " << (beam_counts - expected_beam)/sqrt(expected_beam) << endl;
  cout << "  Expected sig   : " << (s_beam_counts)/sqrt(expected_beam) << endl << endl;
  bunchGapSignificance = (s_beam_counts)/sqrt(expected_beam);
  
  cout << "Cosmic experiment" << endl;
  cout << "  N signal      = " << s_cosmic_counts << endl;
  cout << "  N bg          = " << b_cosmic_counts << endl;
  //  cout << "  Expected N bg = " << expected_cosmic << endl;
  //  cout << "  sigma:   " << sqrt(expected_cosmic) << endl;
  cout << "  Experiment sig : " << (cosmic_counts - expected_cosmic)/sqrt(expected_cosmic) << endl;
  cout << "  Expected sig   : " << (s_cosmic_counts)/sqrt(expected_cosmic) << endl << endl;
  interFillSignificance = (s_cosmic_counts)/sqrt(expected_cosmic);
 
  cout << endl << endl;
 
}


// method to setup for multiple experiments
void ToyStoppedHSCP::readParams() {

  // TODO - read all this from file

  setupBunches(2808);
  setCrossSection(0.5e-33);

  setLumi(1e32);

  lifetimes[0] = 1.E-6;
  lifetimes[1] = 1.E-3;
  lifetimes[2] = 3600.;
  lifetimes[3] = 43200.;
  lifetimes[4] = 86400.;
  lifetimes[5] = 604800.;

  ndays[0] = 3;
  ndays[1] = 7;
  ndays[2] = 14;
  ndays[3] = 30;
  ndays[4] = 90;
  ndays[5] = 360;

}

void ToyStoppedHSCP::makeSigGraphs(int nlifetimes, int npoints) {

  int nc = nlifetimes;
  if (nc > 10) nc = 10;
  int np = npoints;
  if (np > 10) np = 10;

  // generic params
  readParams();

  for (int i=0; i<nc; ++i) {

    double cSigs[10];
    double cosmicSigs[10];
    double beamSigs[10];

    for (int j=0; j<np; ++j) {

      setLifetime(lifetimes[i]);
      setRunningTime(ndays[j]);
      runOnce();
      
      cSigs[j] = combinedSignificance;
      cosmicSigs[j] = interFillSignificance;
      beamSigs[j] = bunchGapSignificance;
      
    }

    cosmicSigGraph[i] = new TGraph(npoints, ndays, cosmicSigs);
    beamSigGraph[i] = new TGraph(npoints, ndays, beamSigs);

  }  

}


void ToyStoppedHSCP::plotSig() {

  TCanvas* c = new TCanvas("canvas");


  // beam plots

  for (int i=0; i<10; ++i) {   
    if (beamSigGraph[i] != 0) {
      beamSigGraph[i]->SetLineColor(i);
      if (i==0) beamSigGraph[i]->Draw("AC");
      else beamSigGraph[i]->Draw("C");
    }
  }

  c->Update();
  c->Print("beamSignificance.png");


  // cosmic plots

  for (int i=0; i<10; ++i) {
    if (cosmicSigGraph[i] != 0) {
      cosmicSigGraph[i]->SetLineColor(i);
      if (i==0) cosmicSigGraph[i]->Draw("AC");
      else cosmicSigGraph[i]->Draw("C");
    }
  }

  c->Update();
  c->Print("cosmicSignificance.png");

}
