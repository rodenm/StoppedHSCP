/*****************************************************************************
 * Project: RooFit                                                           *
 *                                                                           *
 * PDF corresponding to gluino decays with lifetime tau                      * 
 *****************************************************************************/

#ifndef ROOHCSPINORBITPDF
#define ROOHCSPINORBITPDF

#ifndef __CINT__
#include "RooAbsPdf.h"
#include "RooRealProxy.h"
#include "RooCategoryProxy.h"
#include "RooAbsReal.h"
#include "RooAbsCategory.h"
#endif

const int BX_IN_ORBIT = 3564;
const double BX_TIME = 24.95e-9;
 
class RooHCSPInOrbitPdf : public RooAbsPdf {
 public:
  RooHCSPInOrbitPdf() {} ; 
  RooHCSPInOrbitPdf(const char *name, const char *title,
		    RooAbsReal& _bx,
		    RooAbsReal& _logtau);
  RooHCSPInOrbitPdf(const RooHCSPInOrbitPdf& other, const char* name = 0) ;
  RooHCSPInOrbitPdf& operator= (const RooHCSPInOrbitPdf& other) ;
  virtual ~RooHCSPInOrbitPdf ();
  virtual TObject* clone(const char* newname) const { return new RooHCSPInOrbitPdf(*this,newname); }
  void setInstantLumi (int fBX, double fLumi);
  void setInsensitive (int fBX);
  double getInstantLumi (int fBX) const {return int(fBX) < BX_IN_ORBIT ? mInstantLumi [fBX] : 0;}
  double getSensitive (int fBX) const {return int(fBX) < BX_IN_ORBIT ? mSensitiveBX [fBX] : false;}
  void fillCache () const;

 protected:
  
  RooRealProxy bx ;
  RooRealProxy logtau ;
  
  Double_t evaluate() const ;
  virtual Int_t getAnalyticalIntegral(RooArgSet& allVars, RooArgSet& analVars, const char* /*rangeName*/) const;
  virtual Double_t analyticalIntegral(Int_t code, const char* rangeName) const;
  virtual Int_t getGenerator(const RooArgSet& directVars, RooArgSet &generateVars, Bool_t /*staticInitOK*/) const;
  virtual void generateEvent(Int_t code);

  double offLumiFraction () const; 

  
 private:
  mutable bool mSensitiveBX[BX_IN_ORBIT];
  mutable double mInstantLumi[BX_IN_ORBIT];
  mutable double mLumiCache[BX_IN_ORBIT];
  mutable double mOffLumiFraction;
  mutable double mLogTauCache;
  mutable bool mCacheReady;
  
  ClassDef(RooHCSPInOrbitPdf,1) 
};
    
class RooHCSPBkgInOrbitPdf : public RooAbsPdf {
public:
  RooHCSPBkgInOrbitPdf() {} ; 
  RooHCSPBkgInOrbitPdf(const char *name, const char *title,
		       RooAbsReal& _bx,
		       const RooHCSPInOrbitPdf* lumiPdf = 0);
  RooHCSPBkgInOrbitPdf(const RooHCSPBkgInOrbitPdf& other, const char* name = 0) ;
  RooHCSPBkgInOrbitPdf& operator= (const RooHCSPBkgInOrbitPdf& other) ;
  virtual ~RooHCSPBkgInOrbitPdf ();
  virtual TObject* clone(const char* newname) const { return new RooHCSPBkgInOrbitPdf(*this,newname); }

  void setSensitive (int fBX, bool fSensitive);
  bool getSensitive (int fBX) const {return int(fBX) < BX_IN_ORBIT ? mSensitiveBX [fBX] : false;}
 protected:
  
  RooRealProxy bx ;
  
  Double_t evaluate() const ;
  virtual Int_t getAnalyticalIntegral(RooArgSet& allVars, RooArgSet& analVars, const char* /*rangeName*/) const;
  virtual Double_t analyticalIntegral(Int_t code, const char* rangeName) const;
  virtual Int_t getGenerator(const RooArgSet& directVars, RooArgSet &generateVars, Bool_t /*staticInitOK*/) const;
  virtual void generateEvent(Int_t code);
  
  
 private:
  bool mSensitiveBX[BX_IN_ORBIT];
  mutable int mEmptyBunches;
  mutable bool mCacheReady;
  void fillCache () const;
  
  ClassDef(RooHCSPBkgInOrbitPdf,1) 
};

#endif
