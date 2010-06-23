#ifndef SIMPLEBGPDF_H
#define SIMPLEBGPDF_H

#include "RooAbsPdf.h"
#include "RooRealProxy.h"
#include "RooAbsReal.h"

class SimpleBGPdf : public RooAbsPdf {
 public:
  SimpleBGPdf(const SimpleBGPdf &, const char *);
  SimpleBGPdf(const char *, const char *,
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
