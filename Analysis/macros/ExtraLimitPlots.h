#include "TGraph.h"
#include "TGraphAsymmErrors.h"
#include "TCanvas.h"
#include "TFile.h"
#include "TH1.h"
#include "TH1F.h"
#include "TLegend.h"
#include "TLatex.h"
#include "TPaveText.h"

#include <cstdlib>
#include <fstream>
#include <iostream> 

#include <vector>
#include <string>

class ExtraLimitPlots {
	public:

  ExtraLimitPlots(double tpLumi);
  ~ExtraLimitPlots();
  
  void readToyFile(std::string filename);
  void readTimeProfileFile(std::string filename);
  void readGluinoData(std::string filename);
  void readStopData(std::string filename);
  void readStauData(std::string filename);
  
  void calculateCrossSections(unsigned gluinoIndex,
			      unsigned stopIndex,
			      unsigned stauIndex,
			      unsigned toyIndex,
			      unsigned tpIndex);
  
  void calculateIntercepts();
  double calculateMassLimits(TGraph* gTheory, TGraph* gData);
  std::vector<double> calculateMassLimitsWithErrors(TGraph* gTheory, TGraphAsymmErrors* gData);
  
  // limit as fn of lifetime

  TGraph* getObsLimit();
  TGraph* getExpLimit();
  TGraphAsymmErrors* getExpLimit1Sig();
  TGraphAsymmErrors* getExpLimit2Sig();
 
  TGraph* getLimitGluinoBasic();
  TGraph* getLimitGluino();
  TGraph* getLimitGluinoNB();
  TGraph* getLimitGluinoEM();
  TGraph* getLimitGluinoTP();
  
  TGraph* getExpLimitGluino();
  TGraphAsymmErrors* getExpLimitGluino1Sig();
  TGraphAsymmErrors* getExpLimitGluino2Sig();
  
  TGraph* getLimitStopBasic();
  TGraph* getLimitStop();
  TGraph* getLimitStopNB();
  TGraph* getLimitStopEM();
  TGraph* getLimitStopTP();
  
  TGraph* getExpLimitStop();
  TGraphAsymmErrors* getExpLimitStop1Sig();
  TGraphAsymmErrors* getExpLimitStop2Sig();
  
  TGraph* getLimitStauBasic();
  TGraph* getLimitStau();
  TGraph* getLimitStauTP();
  TGraph* getExpLimitStau();
  TGraphAsymmErrors* getExpLimitStau1Sig();
  TGraphAsymmErrors* getExpLimitStau2Sig();
  
  
  // limit as fn of mass
  
  TGraph* getMassLimitGluino();
  TGraph* getMassLimitGluinoTP();
  
  TGraph* getExpMassLimitGluino();
  TGraphAsymmErrors* getExpMassLimitGluino1Sig();
  TGraphAsymmErrors* getExpMassLimitGluino2Sig();
  
  TGraph* getMassLimitStop();
  TGraph* getMassLimitStopTP();
  
  TGraph* getExpMassLimitStop();
  TGraphAsymmErrors* getExpMassLimitStop1Sig();
  TGraphAsymmErrors* getExpMassLimitStop2Sig();
  
  TGraph* getMassLimitStau();
  TGraph* getMassLimitStauTP();
  
  TGraph* getExpMassLimitStau();
  TGraphAsymmErrors* getExpMassLimitStau1Sig();
  TGraphAsymmErrors* getExpMassLimitStau2Sig();
  
  // theory xs as fn of mass
  TGraph* getGluinoTheory();
  TGraph* getStopTheory();
  TGraph* getStauTheory();
  
 private:
  
  // lumi for TP XS
  double tpLumi_;
  
  // toy MC results
  int nToyLifetime;
  std::vector<double> toyLifetime;
  std::vector<double> toyEffLumi;
  std::vector<double> toyExpBG;
  std::vector<double> toyExpBGErr;
  std::vector<double> toyObs;
  std::vector<double> toyObsLimit;
  std::vector<double> toyExpLimit;
  std::vector<double> toyExpLimitLo1Sig;
  std::vector<double> toyExpLimitHi1Sig;
  std::vector<double> toyExpLimitLo2Sig;
  std::vector<double> toyExpLimitHi2Sig;
  
  // time profile results
  int nTPLifetime;
  std::vector<double> tpLifetime;
  std::vector<double> tpObsLimit;
  
  // gluino info
  std::vector<double> gluinoMass;
  std::vector<double> gluinoChi0Mass;
  std::vector<double> gluinoEffStopCM;
  std::vector<double> gluinoEffStopNB;
  std::vector<double> gluinoEffStopEM;
  std::vector<double> gluinoEffReco;
  
  // gluino theory info
  std::vector<double> gluinoTheoryMass;
  std::vector<double> gluinoTheoryXS;
  
  // stop info
  std::vector<double> stopMass;
  std::vector<double> stopChi0Mass;
  std::vector<double> stopEffStopCM;
  std::vector<double> stopEffStopNB;
  std::vector<double> stopEffStopEM;
  std::vector<double> stopEffReco;
  
  // stop theory
  std::vector<double> stopTheoryMass;
  std::vector<double> stopTheoryXS;
  
  // stau info
  std::vector<double> stauMass;
  std::vector<double> stauChi0Mass;
  std::vector<double> stauEffStop;
  std::vector<double> stauEffReco;
  
  // stau theory
  std::vector<double> stauTheoryMass;
  std::vector<double> stauTheoryXS;
  
  // observed limit
  std::vector<double> xsLimitToy;
  std::vector<double> xsProdExpLimitToy;
  std::vector<double> xsProdExpLimitLo1SigToy;
  std::vector<double> xsProdExpLimitHi1SigToy;
  std::vector<double> xsProdExpLimitLo2SigToy;
  std::vector<double> xsProdExpLimitHi2SigToy;

 // observed limits on gluino	
  std::vector<double> xsLimitToyGluino;
  std::vector<double> xsProdLimitToyGluino;
  std::vector<double> xsProdLimitToyGluinoNB;
  std::vector<double> xsProdLimitToyGluinoEM;
  std::vector<double> xsProdLimitTPGluino;
  
  // observed limits on stop
  std::vector<double> xsLimitToyStop;
  std::vector<double> xsProdLimitToyStop;
  std::vector<double> xsProdLimitToyStopNB;
  std::vector<double> xsProdLimitToyStopEM;
  std::vector<double> xsProdLimitTPStop;
  
  // observed limits on stau
  std::vector<double> xsLimitToyStau;
  std::vector<double> xsProdLimitToyStau;
  std::vector<double> xsProdLimitTPStau;
  
  // expected limits on gluino
  std::vector<double> xsProdExpLimitToyGluino;
  std::vector<double> xsProdExpLimitLo1SigToyGluino;
  std::vector<double> xsProdExpLimitHi1SigToyGluino;
  std::vector<double> xsProdExpLimitLo2SigToyGluino;
  std::vector<double> xsProdExpLimitHi2SigToyGluino;
  
  // expected limits on stop
  std::vector<double> xsProdExpLimitToyStop;
  std::vector<double> xsProdExpLimitLo1SigToyStop;
  std::vector<double> xsProdExpLimitHi1SigToyStop;
  std::vector<double> xsProdExpLimitLo2SigToyStop;
  std::vector<double> xsProdExpLimitHi2SigToyStop;
  
  // expected limits on stop
  std::vector<double> xsProdExpLimitToyStau;
  std::vector<double> xsProdExpLimitLo1SigToyStau;
  std::vector<double> xsProdExpLimitHi1SigToyStau;
  std::vector<double> xsProdExpLimitLo2SigToyStau;
  std::vector<double> xsProdExpLimitHi2SigToyStau;
  
  // observed mass limit gluino
  std::vector<double> massGluino;
  std::vector<double> xsProdMassGluino;
  std::vector<double> xsProdMassTPGluino;
  
  std::vector<double> xsProdExpMassGluino;
  std::vector<double> xsProdExpLo1SigMassGluino;
  std::vector<double> xsProdExpHi1SigMassGluino;
  std::vector<double> xsProdExpLo2SigMassGluino;
  std::vector<double> xsProdExpHi2SigMassGluino;
  
  // observed stop
  std::vector<double> massStop;
  std::vector<double> xsProdMassStop;
  std::vector<double> xsProdMassTPStop;	
  
  // expected stop
  std::vector<double> xsProdExpMassStop;
  std::vector<double> xsProdExpLo1SigMassStop;
  std::vector<double> xsProdExpHi1SigMassStop;
  std::vector<double> xsProdExpLo2SigMassStop;
  std::vector<double> xsProdExpHi2SigMassStop;
  
  // observed stau
  std::vector<double> massStau;
  std::vector<double> xsProdMassStau;
  std::vector<double> xsProdMassTPStau;	
  
  // expected stop
  std::vector<double> xsProdExpMassStau;
  std::vector<double> xsProdExpLo1SigMassStau;
  std::vector<double> xsProdExpHi1SigMassStau;
  std::vector<double> xsProdExpLo2SigMassStau;
  std::vector<double> xsProdExpHi2SigMassStau;
  
};
