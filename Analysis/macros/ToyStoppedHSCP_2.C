//------------------------------------------------
//
//  Toy Stopped HSCP experiment
//  Run repeated
//
//------------------------------------------------

#include <cmath>
#include <iostream>
#include <vector>

#include "TObject.h"
#include "TFile.h"
#include "TTree.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TRandom.h"
#include "TGraph.h"
#include "TCanvas.h"

class Experiment { //: public TObject {
public:
  Experiment();
  ~Experiment();
  // particle parameters
  double mass;
  double crossSection;
  double lifetime;
  // experiment parameters
  double lumi;
  double bxStruct;
  double runningTime;
  double bgRate;
  double signalEff;
  // experiment outcomes
  double interfillSig;
  double beamgapSig;
  double combinedSig;
};

Experiment::Experiment() :
  mass(0.),
  crossSection(0.),
  lifetime(0.),
  lumi(0.),
  bxStruct(0.),
  runningTime(0.),
  bgRate(0.),
  signalEff(0.),
  interfillSig(0.),
  beamgapSig(0.),
  combinedSig(0.)
  { }

Experiment::~Experiment() { }


class ToyStoppedHSCP {
public:

  ToyStoppedHSCP(char * fname);
  ~ToyStoppedHSCP();

  // setup bunch structure
  void setupBunchStructure(int bx_struct);  // use 2808 for now

  // one experiment and add to vector
  void run(Experiment exp);

  // number of experiments
  unsigned nExperiments() { return experiments_.size(); }

  // get vector of experiments
  std::vector<Experiment> getExperiments() { return experiments_; }

  // get experiment
  Experiment getExperiment(unsigned i) { 
    if (i<experiments_.size()) return experiments_.at(i);
    else return Experiment();
  }

  // get plot of significance as fn of running time for given mass/lifetime
  // expt : 0 = combined, 1 = beam gap, 2 = interfill
  TGraph * getLifetimeCurve(double mass, double lifetime, unsigned expt);

  // get plot of significance as fn of mass for a given lifetime/running time
  // expt : 0 = combined, 1 = beam gap, 2 = interfill
  TGraph * getMassCurve(double runtime, double lifetime, unsigned expt);

  // get 2D plot of significance as fn of mass/lifetime for a given running time
  // expt : 0 = combined, 1 = beam gap, 2 = interfill
  void get2DMassLifetimePlot(double runtime, unsigned expt, TH2D *);

private:

  // bunch structure
  static const unsigned bxs = 3564; //  = 3564;
  int bunchStruct;    // LHC filling pattern 
  double bctime;    //  = 25e-9 bunch crossing time
  unsigned bxs_on;
  unsigned bxs_off;
  unsigned char beam[3564];

//   TH1D* hdecays;
//   TH1D* hdecaysReg;
//   TH1D* hperday;
//   TH1D* hinday;

  // output file
  TFile* tfile_;
  
  // TTree
  TTree* ttree_;

  // single experiment result
  //  Experiment expt_;

  // Multiple experiment parameters
  std::vector<Experiment> experiments_;

};


ToyStoppedHSCP::ToyStoppedHSCP(char * fname) :
  bxs_on(0),
  bxs_off(0),
  bunchStruct(2808),
  bctime(25e-9)
{

  // open output file
  tfile_ = new TFile(fname,"RECREATE");

  // create a TTree
  ttree_ = new TTree("T","experiment results");

  // create one branch with all information from the stucture
  //  tree->Branch("expts",&expt_,


  setupBunchStructure(2808);

  // setup BX structure histograms - TODO

  // setup single exp histograms
//     hdecays = new TH1D("hdecays","Number of Reconstructable Stopped Gluinos", bxs, 0, bxs);//days*24,0,days);
  
//   hdecaysReg = new TH1D("hdecaysReg","Number of Reconstructable Stopped Gluinos", bxs, 0, bxs);//cycle);//days*24,0,days);
//   hperday = new TH1D("hperday","Number of Reconstructed Stopped Gluinos", days,0,days);
//   hinday = new TH1D("hinday", "Number of Reconstructed Stopped Gluinos", 100, 0, 24*3600);
  // hperday->SetMinimum(0);

  //  TH1D::SetDefaultSumw2 (true);


}

ToyStoppedHSCP::~ToyStoppedHSCP() {

}


void ToyStoppedHSCP::setupBunchStructure(int bx_struct) {

  // set up bunch structure
  int i, j, k, l, m, counter = 0;

  bunchStruct = bx_struct;

  if (bunchStruct == 156) {
    
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
  else if (bunchStruct == 2808) {
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

  cout << "LHC bunch scenario : " << bunchStruct << "x" << bunchStruct << endl;
  cout << "  Bunches on  : " << bxs_on << endl;
  cout << "  Bunches off : " << bxs_off << endl;
  cout << "  Total       : " << counter << endl;

  // fill BX structure histogram - TODO
  
}

void ToyStoppedHSCP::run(Experiment exp) {

  if (exp.bxStruct != bunchStruct) setupBunchStructure(exp.bxStruct);

  double lumi = exp.lumi;
  double xsection = exp.crossSection;
  double lifetime = exp.lifetime;
  double days = exp.runningTime;
  double bg_per_day = exp.bgRate * 60 * 60 * 24;
  double efficiency = exp.signalEff;

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
  
//   hdecays->Reset();
//   hdecaysReg->Reset();
//   hperday->Reset();
//   hinday->Reset();

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
	  
// 	  hdecays->Fill (cycletime*bxs, 1./scale);
	  
	  //      if (cycletime > dutycycle) {
	  // at t==0, counter == 0, so rounding is correct:
	  
	  //      cout << "cycles " << cycles << endl;
	  
	  // Hope this is precise enough...
	  double quotient = (cycles + orbit)/(nOrbits+nOrbitsOff);
	  double remainder = (cycles + orbit) - floor(quotient)*(nOrbits+nOrbitsOff);
	  if (quotient+day >= days) continue;
	  if (remainder < nOrbits && !beam[ int(cycletime * bxs) ]) {
	    s_beam_counts+= 1/scale;
	    
// 	    hdecaysReg->Fill (cycletime*bxs, 1./scale);
// 	    hperday->Fill (quotient+day, 1./scale); 
// 	    hinday->Fill(remainder*bxs*bctime, 1./scale);
	  }
	  else if (remainder > nOrbits ) {
	    s_cosmic_counts+= 1/scale;
	    
// 	    hperday->Fill (quotient+day, 1./scale);
// 	    hinday->Fill(remainder*bxs*bctime, 1./scale);
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
	
// 	hdecays->Fill(bunch, 1./bgscale);
	if (orbit <= nOrbits && !beam[ bunch ]) {
	  b_beam_counts+=1./bgscale;
	  
// 	  hdecaysReg->Fill (bunch, 1./bgscale);
// 	  hperday->Fill (i, 1./bgscale); 
// 	  hinday->Fill((bunch+((double)orbit)*bxs)*bctime, 1./bgscale);
	}
	else if (orbit > nOrbits ) {
	  b_cosmic_counts+=1./bgscale;
	  
// 	  hperday->Fill (i, 1./bgscale);
// 	  hinday->Fill((bunch+((double)orbit)*bxs)*bctime, 1./bgscale);
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

  exp.combinedSig = (s_total_counts)/sqrt(expected_total);
  exp.beamgapSig = (s_beam_counts)/sqrt(expected_beam);
  exp.interfillSig = (s_cosmic_counts)/sqrt(expected_cosmic);

  experiments_.push_back(exp);

  
//   cout << "Combined experiment" << endl;
//   //  cout << "  Total counts: " << total_counts << endl;
//   //  cout << "  Expected N bg = " << expected_total << endl;
//   //  cout << "  sigma:   " << sqrt(expected_total) << endl;
//   cout << "  Experiment sig  : " << (total_counts - expected_total)/sqrt(expected_total) << endl;
//   cout << "  Expected sig    : " << (s_total_counts)/sqrt(expected_total) << endl << endl;

//   cout << "Beam experiment" << endl;
//   cout << "  N signal       : " << s_beam_counts << endl;
//   cout << "  N bg           : " << b_beam_counts << endl;
//   cout << "  Expected N bg  : " << expected_beam << endl;
//   cout << "  Experiment sig : " << (beam_counts - expected_beam)/sqrt(expected_beam) << endl;
//   cout << "  Expected sig   : " << (s_beam_counts)/sqrt(expected_beam) << endl << endl;
  
//   cout << "Cosmic experiment" << endl;
//   cout << "  N signal       : " << s_cosmic_counts << endl;
//   cout << "  N bg           : " << b_cosmic_counts << endl;
//   cout << "  Expected N bg  : " << expected_cosmic << endl;
//   cout << "  Experiment sig : " << (cosmic_counts - expected_cosmic)/sqrt(expected_cosmic) << endl;
//   cout << "  Expected sig   : " << (s_cosmic_counts)/sqrt(expected_cosmic) << endl << endl;
 
//   cout << endl << endl;
 
}


// find all experiments matching mass and lifetime
// and plot significance as a fn of running time
// expt 0 = combined, 1 = beamgap, 2 = interfill
TGraph * ToyStoppedHSCP::getLifetimeCurve(double mass, double lifetime, unsigned expt) {

  double xpoints[100];
  double ypoints[100];
  unsigned point=0;

  for (unsigned i=0; i<getExperiments().size(); ++i) {
    if (getExperiment(i).mass == mass && 
	getExperiment(i).lifetime == lifetime) {
      xpoints[point] = getExperiment(i).runningTime;
      if (expt == 0) ypoints[point]  = getExperiment(i).combinedSig;
      else if (expt == 1) ypoints[point]  = getExperiment(i).beamgapSig;
      else if (expt == 2) ypoints[point]  = getExperiment(i).interfillSig;
      else ypoints[point] = 0.;
      ++point;
    }
  }

  return new TGraph(point, xpoints, ypoints);

}
// find all experiments matching mass and lifetime
// and plot significance as a fn of running time
// expt 0 = combined, 1 = beamgap, 2 = interfill
TGraph * ToyStoppedHSCP::getMassCurve(double runtime, double lifetime, unsigned expt) {

  double xpoints[100];
  double ypoints[100];
  unsigned point=0;

  for (unsigned i=0; i<getExperiments().size(); ++i) {
    if (getExperiment(i).runningTime == runtime && 
	getExperiment(i).lifetime == lifetime) {
      xpoints[point] = getExperiment(i).mass;
      if (expt == 0) ypoints[point]  = getExperiment(i).combinedSig;
      else if (expt == 1) ypoints[point]  = getExperiment(i).beamgapSig;
      else if (expt == 2) ypoints[point]  = getExperiment(i).interfillSig;
      else ypoints[point] = 0.;
      ++point;
    }
  }

  return new TGraph(point, xpoints, ypoints);

}



// get a histogram showing significance as fun of mass/lifetime
// after a given running time
void ToyStoppedHSCP::get2DMassLifetimePlot(double runtime, unsigned expt, TH2D * hist) {

  for (unsigned i=0; i<getExperiments().size(); ++i) {
    if (getExperiment(i).runningTime == runtime) {
      double x = getExperiment(i).mass;
      double y = getExperiment(i).lifetime;
      double sig = getExperiment(i).beamgapSig;
//       if (expt == 0) sig = getExperiment(i).combinedSig;
//       else if (expt == 1) sig = getExperiment(i).beamgapSig;
//       else if (expt == 2) sig = getExperiment(i).interfillSig;
      hist->Fill(x, y, sig);
    }
  }

}
