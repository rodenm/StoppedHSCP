/*****************************************************************************
 * Project: RooFit                                                           *
 *                                                                           *
 * PDF corresponding to gluino decays with lifetime tau                      * 
 *****************************************************************************/

#ifndef ROOHCSPPDF
#define ROOHCSPPDF

#include "RooAbsPdf.h"
#include "RooRealProxy.h"
#include "RooCategoryProxy.h"
#include "RooAbsReal.h"
#include "RooAbsCategory.h"

namespace shscp {
  class LumiReader;
  class LumiDecayMC;
}
 
class RooHCSPPdf : public RooAbsPdf {public:
  RooHCSPPdf() {} ; 
  RooHCSPPdf(const char *name, const char *title,
	     RooAbsReal& _t,
	     RooAbsReal& _logtau,
	     const std::string& lumiFile);
  RooHCSPPdf(const RooHCSPPdf& other, const char* name = 0) ;
  RooHCSPPdf& operator= (const RooHCSPPdf& other) ;
  virtual ~RooHCSPPdf ();
  virtual TObject* clone(const char* newname) const { return new RooHCSPPdf(*this,newname); }
  
  // effective luminosity taking into account lifetime and no-beam registration efficiency
  double integratedEffectiveLumi (double fTMin, double fTMax) const;

 protected:
  
  RooRealProxy t ;
  RooRealProxy logtau ;
  
  Double_t evaluate() const ;
  virtual Int_t getAnalyticalIntegral(RooArgSet& allVars, RooArgSet& analVars, const char* /*rangeName*/) const;
  virtual Double_t analyticalIntegral(Int_t code, const char* rangeName) const;
  virtual Int_t getGenerator(const RooArgSet& directVars, RooArgSet &generateVars, Bool_t /*staticInitOK*/) const;
  virtual void generateEvent(Int_t code);
  
 private:
  std::string mLumiFileName;
  shscp::LumiReader* mLumiReader;
  shscp::LumiDecayMC* mLumiDecayMC;
  mutable double mCacheIntegral;
  mutable double mCacheTmin;
  mutable double mCacheTmax;
  
  ClassDef(RooHCSPPdf,1) 
};
    
class RooHCSPBkgPdf : public RooAbsPdf {public:
  RooHCSPBkgPdf() {} ; 
  RooHCSPBkgPdf(const char *name, const char *title,
		RooAbsReal& _t,
		const std::string& lumiFile);
  RooHCSPBkgPdf(const RooHCSPBkgPdf& other, const char* name = 0) ;
  RooHCSPBkgPdf& operator= (const RooHCSPBkgPdf& other) ;
  virtual ~RooHCSPBkgPdf ();
  virtual TObject* clone(const char* newname) const { return new RooHCSPBkgPdf(*this,newname); }

  // effective production rate correction taking into account no-beam registration efficiency
  double integratedEffectiveRateCorrection (double fTMin, double fTMax) const;
  
 protected:
  
  RooRealProxy t ;
  
  Double_t evaluate() const ;
  virtual Int_t getAnalyticalIntegral(RooArgSet& allVars, RooArgSet& analVars, const char* /*rangeName*/) const;
  virtual Double_t analyticalIntegral(Int_t code, const char* rangeName) const;
  virtual Int_t getGenerator(const RooArgSet& directVars, RooArgSet &generateVars, Bool_t /*staticInitOK*/) const;
  virtual void generateEvent(Int_t code);
  
 private:
  std::string mLumiFileName;
  shscp::LumiReader* mLumiReader;
  shscp::LumiDecayMC* mLumiDecayMC;
  mutable double mCacheIntegral;
  mutable double mCacheTmin;
  mutable double mCacheTmax;
  
  ClassDef(RooHCSPBkgPdf,1) 
};

#endif
