#include "IOMC/EventVertexGenerators/interface/BaseEvtVtxGenerator.h"
#include <fstream>

namespace CLHEP {
  class RandFlat;
}


class RHDecay : public BaseEvtVtxGenerator 
{
public:
  RHDecay(const edm::ParameterSet & p);
  virtual ~RHDecay();

  /// return a new event vertex
  //virtual CLHEP::Hep3Vector* newVertex();
  virtual HepMC::FourVector* newVertex() ;
  
  virtual TMatrixD* GetInvLorentzBoost() {
    return 0;
  }
private:
  std::string mFileName;
  std::ifstream* mFile;
  double mTimeMin;
  double mTimeMax;
  CLHEP::RandFlat*  mRandom ;
  bool mVerbose;
};
