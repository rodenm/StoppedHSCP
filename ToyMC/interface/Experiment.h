// Class to store parameters and results of a stopped HSCP experiment
//
// Jim Brooke
//

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
  double interfillSig;
  double beamgapSig;
  double combinedSig;
};

std::ostream& operator<<(std::ostream& s, const Experiment& e);

