
#include <vector>
#include <string>

class LimitPlots {
 public:

  LimitPlots(double tpLumi, std::string toyfile, std::string tpfile);
  ~LimitPlots();

  void readToyFile(std::string filename);

  void readTimeProfileFile(std::string filename);

  void readGluinoData(std::string filename);

  void readStopData(std::string filename);

  void readStauData(std::string filename);

  void calculateCrossSections(unsigned massIndex);

  void makeBasicPlot();

  void makeLifetimePlot();

  void makeMassPlot();

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

  // cross-section limits
  std::vector<double> xsLimitToyGluino;
  std::vector<double> xsProdLimitToyGluino;
  std::vector<double> xsProdLimitToyGluinoNB;
  std::vector<double> xsProdLimitToyGluinoEM;
  std::vector<double> xsProdLimitToyStop;
  std::vector<double> xsProdLimitTPGluino;

  std::vector<double> xsProdExpLimitToyGluino;
  std::vector<double> xsProdExpLimitLo1SigToyGluino;
  std::vector<double> xsProdExpLimitHi1SigToyGluino;
  std::vector<double> xsProdExpLimitLo2SigToyGluino;
  std::vector<double> xsProdExpLimitHi2SigToyGluino;

};
