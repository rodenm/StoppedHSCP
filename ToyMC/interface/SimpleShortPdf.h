#ifndef SIMPLESHORTPDF_H
#define SIMPLESHORTPDF_H

#include "RooAbsPdf.h"
#include "RooRealProxy.h"
#include "RooAbsReal.h"

class SimpleShortPdf : public RooAbsPdf {
 public:
  SimpleShortPdf(const SimpleShortPdf &, const char *);
  SimpleShortPdf(const char *, const char *,
	      RooAbsReal &);
  virtual TObject *clone(const char *) const;

 protected:
  Double_t evaluate() const;
  virtual Int_t getAnalyticalIntegral(RooArgSet &,
				      RooArgSet &,
				      const char *) const;
  virtual Double_t analyticalIntegral(Int_t, const char *) const;

 private:
  std::vector<double> sensitivity;
  RooRealProxy t;
};

#endif
