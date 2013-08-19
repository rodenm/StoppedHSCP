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

class LimitPlots {
	public:

  LimitPlots(double tpLumi);
  ~LimitPlots();
  
  void readToyFile(std::string filename);
  void readTimeProfileFile(std::string filename);
  void readGluinoData(std::string filename);
  void readStopData(std::string filename);
  void readStauData(std::string filename);
  
  void calculateCrossSections(unsigned gluinoIndex,
			      unsigned stopIndex,
			      unsigned toyIndex,     // toyIndex resets to index of 1 sec data point
			      unsigned tpIndex);
  
  void calculateIntercepts();
  double calculateMassLimits(TGraph* gTheory, TGraph* gData);
  std::vector<double> calculateMassLimitsWithErrors(TGraph* gTheory, TGraphAsymmErrors* gData);
  
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
  
  TGraph* getGluinoTheory();
  TGraph* getStopTheory();
  
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
  
  //stop theory
  std::vector<double> stopTheoryMass;
  std::vector<double> stopTheoryXS;
  
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
		
};
