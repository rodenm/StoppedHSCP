/*****************************************************************************
 * Project: RooFit                                                           *
 *                                                                           *
 * PDF corresponding to gluino decays with lifetime tau                      * 
 *****************************************************************************/

#ifndef ROOHSCPINORBITPDF
#define ROOHSCPINORBITPDF

#include "RooAbsPdf.h"
#include "RooRealProxy.h"
#include "RooCategoryProxy.h"
#include "RooAbsReal.h"
#include "RooAbsCategory.h"

const int BX_IN_ORBIT = 3564;
const double BX_TIME = 24.95e-9;
 
class RooHSCPInOrbitPdf : public RooAbsPdf {
 public:
  RooHSCPInOrbitPdf() {} ; 
  RooHSCPInOrbitPdf(const char *name, const char *title,
		    RooAbsReal& _bx,
		    RooAbsReal& _logtau);
  RooHSCPInOrbitPdf(const RooHSCPInOrbitPdf& other, const char* name = 0) ;
  RooHSCPInOrbitPdf& operator= (const RooHSCPInOrbitPdf& other) ;
  virtual ~RooHSCPInOrbitPdf ();
  virtual TObject* clone(const char* newname) const { return new RooHSCPInOrbitPdf(*this,newname); }
  void setInstantLumi (int fBX, double fLumi);
  void setInsensitive (int fBX);
  double getInstantLumi (int fBX) const {return int(fBX) < BX_IN_ORBIT ? mInstantLumi [fBX] : 0;}
  bool getSensitive (int fBX) const {return int(fBX) < BX_IN_ORBIT ? mSensitiveBX [fBX] : false;}
  void fillCache () const;

 public:
  
  RooRealProxy bx ;
  RooRealProxy logtau ;
  
  Double_t evaluate() const ;
  virtual Int_t getAnalyticalIntegral(RooArgSet& allVars, RooArgSet& analVars, const char* /*rangeName*/) const;
  virtual Double_t analyticalIntegral(Int_t code, const char* rangeName) const;
  virtual Int_t getGenerator(const RooArgSet& directVars, RooArgSet &generateVars, Bool_t /*staticInitOK*/) const;
  virtual void generateEvent(Int_t code);

  double offLumiFraction () const; 
  double effectiveLumi (int fBX) const;
  double fractionInGap (int fFirstBX, int fLength) const;
  

 
 private:
  mutable bool mSensitiveBX[BX_IN_ORBIT];
  mutable double mInstantLumi[BX_IN_ORBIT];
  mutable double mLumiCache[BX_IN_ORBIT];
  mutable double mOffLumiFraction;
  mutable double mLogTauCache;
  mutable bool mCacheReady;
  
};
    
class RooHSCPBkgInOrbitPdf : public RooAbsPdf {
public:
  RooHSCPBkgInOrbitPdf() {} ; 
  RooHSCPBkgInOrbitPdf(const char *name, const char *title,
		       RooAbsReal& _bx,
		       const RooHSCPInOrbitPdf* lumiPdf = 0);
  RooHSCPBkgInOrbitPdf(const RooHSCPBkgInOrbitPdf& other, const char* name = 0) ;
  RooHSCPBkgInOrbitPdf& operator= (const RooHSCPBkgInOrbitPdf& other) ;
  virtual ~RooHSCPBkgInOrbitPdf ();
  virtual TObject* clone(const char* newname) const { return new RooHSCPBkgInOrbitPdf(*this,newname); }

  void setSensitive (int fBX, bool fSensitive);
  bool getSensitive (int fBX) const {return int(fBX) < BX_IN_ORBIT ? mSensitiveBX [fBX] : false;}
 public:
  
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
  
};

#endif
