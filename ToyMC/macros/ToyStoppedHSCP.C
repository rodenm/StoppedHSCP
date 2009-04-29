
//------------------------------------------------
//
//  Toy Stopped HSCP experiment
//
//------------------------------------------------



#include <cmath>
#include <iostream>
#include <fstream>
#include <vector>

#include "TSystem.h"
#include "TObject.h"
#include "TFile.h"
#include "TTree.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TRandom3.h"
#include "TGraph.h"
#include "TMultiGraph.h"
#include "TGraphAsymmErrors.h"
#include "TCanvas.h"
#include "TLimit.h"
#include "TLimitDataSource.h"
#include "TConfidenceLevel.h"

#include "Math/Math.h"
#include "Math/ProbFuncMathCore.h"
#include "Math/SpecFuncMathCore.h"


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
  // event counts
  unsigned nSigBeamgap;
  unsigned nBgBeamgap;
  unsigned nSigInterfill;
  unsigned nBgInterfill;
  // expected background
  double nExpectedBeamgap;
  double nExpectedInterfill;
  // experiment outcomes
  double interfillPVal;
  double beamgapPVal;
  double combinedPVal;
  double interfillSig;
  double beamgapSig;
  double combinedSig;
};

std::ostream& operator<<(std::ostream& s, const Experiment& e);

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

std::ostream& operator<<(std::ostream& s, const Experiment& e) {
  s << "Stopped HSCP experiment" << endl;
  s << " Physics" << endl;
  s << "  Gluino mass      : " << e.mass << endl;
  s << "  Cross-section    : " << e.crossSection << endl;
  s << "  Lifetime         : " << e.lifetime << endl;
  s << " Expt parameters " << endl;
  s << "  Lumi             : " << e.lumi << endl;
  s << "  BX structure     : " << e.bxStruct << endl;
  s << "  BG rate          : " << e.bgRate << endl;
  s << "  Sig eff          : " << e.signalEff << endl;
  s << "  Running time     : " << e.runningTime << endl;
  s << " Results" << endl;
  s << "  Ns beamgap       : " << e.nSigBeamgap << endl;
  s << "  Nb beamgap       : " << e.nBgBeamgap << endl;
  s << "  Ns interfill     : " << e.nSigInterfill << endl;
  s << "  Nb interfill     : " << e.nBgInterfill << endl;
  s << "  Expctd beamgap   : " << e.nExpectedBeamgap << endl;
  s << "  Expctd interfill : " << e.nExpectedInterfill << endl;
  s << "  Sig beamgap      : " << e.beamgapSig << endl;
  s << "  Sig interfill    : " << e.interfillSig << endl;
  s << "  Sig combined     : " << e.combinedSig << endl;
  s << "  PVal beamgap      : " << e.beamgapPVal << endl;
  s << "  PVal interfill    : " << e.interfillPVal << endl;
  s << "  PVal combined     : " << e.combinedPVal << endl;
  s << endl;
}



class ToyStoppedHSCP {
public:

  ToyStoppedHSCP(char * rootfile, char * logfile);
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


  // files
  void save();


  // get plot of significance as fn of running time for given mass/lifetime
  // expt : 0 = combined, 1 = beam gap, 2 = interfill
  TGraph * getLifetimeCurve(double mass, double lifetime, unsigned expt);

  // get multi-graph of nominal value + upper/lower bounds
  TGraphAsymmErrors getTimeCurveWithUncertainty(double mass, double lifetime, unsigned expt);

  TMultiGraph* getTimeCurveBand(double mass, double lifetime, unsigned expt);

  // get plot of significance as fn of mass for a given lifetime/running time
  // expt : 0 = combined, 1 = beam gap, 2 = interfill
  TGraph * getMassCurve(double runtime, double lifetime, unsigned expt);

  // get 2D plot of significance as fn of mass/lifetime for a given running time
  // expt : 0 = combined, 1 = beam gap, 2 = interfill
  void get2DMassLifetimePlot(double runtime, unsigned expt, TH2D *);

private:

  // some constants
  static const unsigned nBucketsPerOrbit_;
  static const double   bunchCrossingTime_;
  static const unsigned nOrbitsPerDay_;


  int bunchStruct;    // LHC filling pattern 
  unsigned bxs_on;
  unsigned bxs_off;
  unsigned char beam[3564];

  TH1D* hBxStruct_;

  TH1D* hdecays;
  TH1D* hdecaysReg;
  TH1D* hperday;
  TH1D* hinday;

  // log file
  ofstream lfile_;

  // root file
  TFile* tfile_;
  
  // TTree
  TTree* ttree_;

  // single experiment result
  //  Experiment expt_;

  // Multiple experiment parameters
  std::vector<Experiment> experiments_;

};

using namespace std;

const unsigned ToyStoppedHSCP::nBucketsPerOrbit_  = 3564;
const double   ToyStoppedHSCP::bunchCrossingTime_ = 25.e-9;
const unsigned ToyStoppedHSCP::nOrbitsPerDay_     = 9.46e8;


ToyStoppedHSCP::ToyStoppedHSCP(char * rootfile, char * logfile) :
  bxs_on(0),
  bxs_off(0),
  bunchStruct(156)
{

  cout << "StoppedHSCP Toy MY" << endl;

  // open log file
  lfile_.open(logfile);

  // open root file
  tfile_ = new TFile(rootfile,"RECREATE");

  // seutp TTree
  ttree_ = new TTree("T","experiment results");
  
  // create one branch with all information from the struct
  //  tree->Branch("expts",&expt_,



  // setup histograms
  hBxStruct_ = new TH1D("bxStruct", "Filled BX", nBucketsPerOrbit_, 0., (double)nBucketsPerOrbit_);

  // setup single exp histograms
    hdecays = new TH1D("hdecays","Number of Reconstructable Stopped Gluinos", nBucketsPerOrbit_, 0, nBucketsPerOrbit_);//days*24,0,days);
  
  hdecaysReg = new TH1D("hdecaysReg","Number of Reconstructable Stopped Gluinos", nBucketsPerOrbit_, 0, nBucketsPerOrbit_);//cycle);//days*24,0,days);
  hperday = new TH1D("hperday","Number of Reconstructed Stopped Gluinos", 30,0,30);
  hinday = new TH1D("hinday", "Number of Reconstructed Stopped Gluinos", 100, 0, 24*3600);
  hperday->SetMinimum(0);

  TH1D::SetDefaultSumw2 (true);


  setupBunchStructure(bunchStruct);

}

ToyStoppedHSCP::~ToyStoppedHSCP() {

  save();
  tfile_->Close();
  lfile_.close();

}


void ToyStoppedHSCP::setupBunchStructure(int bx_struct) {

  hBxStruct_->Reset();

  // set up bunch structure
  int i, j, k, l, m, counter = 0;

  bunchStruct = bx_struct;
  bxs_on =0;
  bxs_off =0;

  if (bunchStruct == 156) {
    
    for (i=0; i<4; i++) {
      for (j=0; j<3; j++) {
	int n=12;
	if (i==0 && j==0) n=8;
	if (j==2) n=16;
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

  lfile_ << "LHC bunch scenario : " << bunchStruct << "x" << bunchStruct << endl;
  lfile_ << "  Bunches on  : " << bxs_on << endl;
  lfile_ << "  Bunches off : " << bxs_off << endl;
  lfile_ << "  Total       : " << counter << endl;

  // fill BX struct histogram
  for (unsigned a=0; a<nBucketsPerOrbit_; ++a) {
    if (beam[a] == 1) hBxStruct_->Fill(a);
  }

}

void ToyStoppedHSCP::run(Experiment exp) {

  // reset stuff
  hdecays->Reset();
  hdecaysReg->Reset();
  hperday->Reset();
  hinday->Reset();

  // setup BX if not already set
  if (exp.bxStruct != bunchStruct) setupBunchStructure(exp.bxStruct);

  // experiment parameters
  double lumi = exp.lumi;
  double xsection = exp.crossSection;
  double lifetime = exp.lifetime;
  double days = exp.runningTime;
  double bg_per_day = exp.bgRate * 60 * 60 * 24;
  double efficiency = exp.signalEff;

  // optimised time cut
  double timeCut = lifetime * 1.256;

  double nOrbitsOn  = nOrbitsPerDay_/2;
  double nOrbitsOff = nOrbitsPerDay_/2;

  //  program control
  bool signal_on = true;
  bool background_on = true;

  double scale = 1000;   // increase these parameters to increase precision
  double bgscale = 100;  // at the cost of running time.  100 or 1000 are good numbers to try


  double tOrbit = bunchCrossingTime_*nBucketsPerOrbit_;  // orbit length

  double tstep = bunchCrossingTime_; //0.1 / (lumi * xsection * efficiency);

  // numfer of decays per BX ????
  double nDecays = lumi * tstep * xsection * efficiency;
  

  TRandom3 rndm;
  
  
  int n;
  double t;
  
  double total_counts = 0, beam_counts = 0, cosmic_counts = 0;
  double s_total_counts = 0, s_beam_counts = 0, s_cosmic_counts = 0;
  double b_total_counts = 0, b_beam_counts = 0, b_cosmic_counts = 0;
  

  // do signal
  for (t = 0, n = 0; n < nBucketsPerOrbit_; t += tstep, n++) {
    if (beam[n]) {
      int nRandomDecays = scale*nDecays*nOrbitsOn*days; //rndm.Poisson;
      for (int ig = 0; ig < nRandomDecays ; ig++) {
	
	double tau = rndm.Exp (lifetime);
	double tdecay = t + tau;
	double cycletime = tdecay/tOrbit - floor (tdecay/tOrbit);
	double cycles = tdecay/tOrbit;
	
	unsigned long orbit = rndm.Integer(nOrbitsOn);
	int day = rndm.Integer(days);
	
	hdecays->Fill (cycletime*nBucketsPerOrbit_, 1./scale);
	
	//      if (cycletime > dutycycle) {
	// at t==0, counter == 0, so rounding is correct:
	
	//      cout << "cycles " << cycles << endl;
	
	// Hope this is precise enough...
	double quotient = (cycles + orbit)/(nOrbitsOn+nOrbitsOff);
	double remainder = (cycles + orbit) - floor(quotient)*(nOrbitsOn+nOrbitsOff);
	if (quotient+day >= days) continue;
	if (remainder < nOrbitsOn && !beam[ int(cycletime * nBucketsPerOrbit_) ]) {
	  s_beam_counts+= 1/scale;
	  
	  hdecaysReg->Fill (cycletime*nBucketsPerOrbit_, 1./scale);
	  hperday->Fill (quotient+day, 1./scale); 
	  hinday->Fill(remainder*nBucketsPerOrbit_*bunchCrossingTime_, 1./scale);
	}
	else if (remainder > nOrbitsOn ) {
	  if (timeCut < 0 || (remainder - nOrbitsOn)*tOrbit < timeCut) {
	    s_cosmic_counts+= 1/scale;
	  }
	  
	  hperday->Fill (quotient+day, 1./scale);
	  hinday->Fill(remainder*nBucketsPerOrbit_*bunchCrossingTime_, 1./scale);
	}
      }
    }
  }
  
  // do background
  for (int i = 0; i < days; i++) {
    
    int todays_rate = bg_per_day*bgscale;//rndm.Poisson(bg_per_day);
    
    for (int j = 0; j < todays_rate; j++) {
      
      // pick an orbit
      unsigned long orbit = rndm.Integer(nOrbitsOn+nOrbitsOff);
      
      // pick a bin
      unsigned int bunch = rndm.Integer(nBucketsPerOrbit_);
      
      // fill
      hdecays->Fill(bunch, 1./bgscale);
      
      if (orbit <= nOrbitsOn && !beam[ bunch ]) {
	b_beam_counts+=1./bgscale;
	
	hdecaysReg->Fill (bunch, 1./bgscale);
	hperday->Fill (i, 1./bgscale); 
	hinday->Fill((bunch+((double)orbit)*nBucketsPerOrbit_)*bunchCrossingTime_, 1./bgscale);
      }
      else if (orbit > nOrbitsOn ) {
	if (timeCut < 0 || (orbit - nOrbitsOn)*tOrbit < timeCut) {
	  b_cosmic_counts+=1./bgscale;
	}
	
	hperday->Fill (i, 1./bgscale);
	hinday->Fill((bunch+((double)orbit)*nBucketsPerOrbit_)*bunchCrossingTime_, 1./bgscale);
      }
    }
  }
  
  beam_counts = s_beam_counts + b_beam_counts;
  cosmic_counts = s_cosmic_counts + b_cosmic_counts;
  s_total_counts = s_beam_counts + s_cosmic_counts;
  b_total_counts = b_beam_counts + b_cosmic_counts;
  total_counts = beam_counts + cosmic_counts;
  double frac_of_cosmics = timeCut / (tOrbit * nOrbitsOff);

  if (frac_of_cosmics > 1) frac_of_cosmics = 1;
  
  // expected backgrounds

  double expected_cosmic = bg_per_day * nOrbitsOff*frac_of_cosmics/nOrbitsPerDay_*days;
  double expected_beam = bg_per_day * (nOrbitsOn*bxs_off/nBucketsPerOrbit_)/nOrbitsPerDay_*days;
  double expected_total = expected_cosmic + expected_beam;


  lfile_ << expected_beam << endl;
  lfile_ << expected_cosmic << endl;
  lfile_ << expected_total << endl;

  exp.nSigBeamgap = s_beam_counts;
  exp.nBgBeamgap = b_beam_counts;
  exp.nSigInterfill = s_cosmic_counts;
  exp.nBgInterfill = b_cosmic_counts;
  exp.nExpectedBeamgap = expected_beam;
  exp.nExpectedInterfill = expected_cosmic;

  //double pval_poiss = ROOT::Math::poisson_cdf_c(s_total_counts+expected_total,expected_total)	
  //double pval_gauss = ROOT::Math::(double x, double sigma=1, double x0=0)

  // Create some 1-bin histograms
  TH1D* background = new TH1D("background","The expected background",1,0,1);
  TH1D* signal     = new TH1D("signal","the expected signal",1,0,1);
  TH1D* data       = new TH1D("data","some fake data points",1,0,1);

  //Fill with exp signal & bkg
//   for (int i=0; i < s_total_counts; i++) {
//     signal->Fill(0.99);
//   }
//   for (int i=0; i < expected_total; i++) {
//     background->Fill(0.99);
//   }
//   for (int i=0; i < (s_total_counts+expected_total); i++) {
//     data->Fill(0.99);
//   }
  
  TLimitDataSource* mydatasource = new TLimitDataSource(signal,background,data);
  TConfidenceLevel *myconfidence = TLimit::ComputeLimit(mydatasource,1000);
  //cout << "CLs    : "   << myconfidence->CLs()  << endl;
  //cout << "CLsb   : "   << myconfidence->CLsb() << endl;
  //cout << "CLb    : "   << myconfidence->CLb()  << endl;
  //cout << "< CLs >  : " << myconfidence->GetExpectedCLs_b()  << endl;
  //cout << "< CLsb > : " << myconfidence->GetExpectedCLsb_b() << endl;
  //cout << "< CLb >  : " << myconfidence->GetExpectedCLb_b()  << endl;  

  //  exp.combinedSig = myconfidence->GetExpectedCLb_b();

  exp.combinedSig = (s_total_counts)/sqrt(expected_total + s_total_counts);
  exp.beamgapSig = (s_beam_counts)/sqrt(expected_beam + s_beam_counts);
  exp.interfillSig = (s_cosmic_counts)/sqrt(expected_cosmic + s_cosmic_counts);

  exp.combinedPVal = ROOT::Math::poisson_cdf_c(expected_total + s_total_counts, expected_total);
  exp.beamgapPVal = ROOT::Math::poisson_cdf_c(expected_beam + s_beam_counts, expected_beam);
  exp.interfillPVal = ROOT::Math::poisson_cdf_c(expected_cosmic + s_cosmic_counts, expected_cosmic);
  //  exp.beamgapPVal = ROOT::Math::gaussian_cdf_c(nb+ns, sqrt(nb), nb)


  experiments_.push_back(exp);

  // log experiment
  lfile_ << exp;

}












// save histos, tree etc
void ToyStoppedHSCP::save() {
  //  tfile_->Write();
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
      if (expt == 0) ypoints[point]  = getExperiment(i).combinedPVal;
      else if (expt == 1) ypoints[point]  = getExperiment(i).beamgapPVal;
      else if (expt == 2) ypoints[point]  = getExperiment(i).interfillPVal;
      else ypoints[point] = 0.;
      ++point;
    }
  }

  return new TGraph(point, xpoints, ypoints);

}


TGraphAsymmErrors ToyStoppedHSCP::getTimeCurveWithUncertainty(double mass, double lifetime, unsigned expt) {

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

  double x[100];
  double exLo[100];
  double exHi[100];
  double y[100];
  double eyLo[100];
  double eyHi[100];
  unsigned npoints=floor(point/3);

  // this code assumes for now that points arrive in order
  // lower, centre, upper
  for (unsigned i=0; i<npoints; ++i) {
    x[i] = xpoints[i*3];
    exLo[i] = 0.;
    exHi[i] = 0.;
    y[i] = ypoints[(i*3)+1];
    eyLo[i] = y[i] - ypoints[i*3];
    eyHi[i] = ypoints[(i*3)+2]- y[i];
  }

  return TGraphAsymmErrors(npoints, x, y, exLo, exHi, eyLo, eyHi);

}


TMultiGraph * ToyStoppedHSCP::getTimeCurveBand(double mass, double lifetime, unsigned expt) {

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

  double x[100];
  double xLo[100];
  double xHi[100];
  double y[100];
  double yLo[100];
  double yHi[100];
  unsigned npoints=floor(point/3);

  // this code assumes for now that points arrive in order
  // lower, centre, upper
  for (unsigned i=0; i<npoints; ++i) {
    x[i] = xpoints[i*3];
    xLo[i] = 0.;
    xHi[i] = 0.;
    y[i] = ypoints[(i*3)+1];
    yLo[i] = ypoints[i*3];
    yHi[i] = ypoints[(i*3)+2];
  }

  TMultiGraph * output = new TMultiGraph;
  output->Add(new TGraph(npoints, x, yLo));
  output->Add(new TGraph(npoints, x, y));
  output->Add(new TGraph(npoints, x, yHi));
						     
  return output;

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
