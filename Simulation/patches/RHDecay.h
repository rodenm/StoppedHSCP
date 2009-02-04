#include "IOMC/EventVertexGenerators/interface/BaseEvtVtxGenerator.h"
#include "FWCore/ParameterSet/interface/FileInPath.h"
#include "TTree.h"
#include "PhysicsTools/UtilAlgos/interface/TFileService.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "TH1D.h"
#include "CLHEP/Random/RandGeneral.h"
#include "FWCore/Utilities/interface/RandomNumberGenerator.h"
#include "CLHEP/Random/Randomize.h"
#include <fstream>

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
  edm::FileInPath mFilePath;
  std::ifstream* mFile;
  double mTimeMin;
  double mTimeMax;
  int TotalNumber;
  bool Silent;

  bool MakeCuts;
  bool MakeRCuts;

  double MaxRadius;
  double MinRadius;
  double MinZ;
  double MaxZ;
  double MinPhi;
  double MaxPhi;
  
  int OperationMode;

  int ZDivs;
  int RDivs;

  Double_t ZArray[500];
  Double_t RArray[500];

  TH1D * RDist;
  TH1D * ZDist;
  TH1D * RZDist;
  RandGeneral * RSample;
  RandGeneral * ZSample;
  
  RandFlat * FlatRand;
 
  
  RandGeneral * RGeometric;


  edm::Service<TFileService> fs;
  edm::Service<edm::RandomNumberGenerator> rng;

  std::map<int,double> xv;
  std::map<int,double> yv;
  std::map<int,double> zv;


  TTree * InTree;
  TTree * PlaceTree;

  Float_t xIn;
  Float_t yIn;
  Float_t zIn;
  Float_t rIn;
 
  Float_t xPlace;
  Float_t yPlace;
  Float_t zPlace;
  Float_t rPlace;
  Float_t tPlace;

};
