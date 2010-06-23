#ifndef LIFETIMEPDF_H
#define LIFETIMEPDF_H

#include "RooAbsPdf.h"
#include "RooRealProxy.h"
#include "RooAbsReal.h"

class LifetimePdf : public RooAbsPdf {
 public:
  LifetimePdf(const LifetimePdf &, const char *);
  LifetimePdf(const char *, const char *,
	      RooAbsReal &,
	      RooAbsReal &);
  virtual TObject *clone(const char *) const;

 protected:
  Double_t evaluate() const;
  virtual Int_t getAnalyticalIntegral(RooArgSet &,
				      RooArgSet &,
				      const char *) const;
  virtual Double_t analyticalIntegral(Int_t, const char *) const;

 private:
  void prepareCache(double) const;

  std::vector<double> sensitivity;
  mutable std::vector<double> n;
  RooRealProxy t;
  RooRealProxy tau;
  mutable double cachedTau;
};

#endif
