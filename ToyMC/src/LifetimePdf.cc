#include "StoppedHSCP/ToyMC/interface/LifetimePdf.h"
#include "TMath.h"
#include <assert.h>
#include <iostream>

LifetimePdf::LifetimePdf(const LifetimePdf &other,
			 const char *name)
  : RooAbsPdf(other, name),
    sensitivity(other.sensitivity),
    n(other.n),
    t("t", this, other.t),
    tau("tau", this, other.tau)
{}
    

LifetimePdf::LifetimePdf(const char *name,
			 const char *title,
			 RooAbsReal &_t,
			 RooAbsReal &_tau)
  : RooAbsPdf(name, title),
    n(32*924, 0),
    t("ls", "ls", this, _t),
    tau("tau", "tau", this, _tau)
{
  sensitivity.clear();
  sensitivity.reserve(32*924);

  for (int i = 0; i < 32; i++) {
    for (int j = 0; j < 308; j++)
      sensitivity.push_back(1.-(2808./3564.));
    for (int j = 0; j < 616; j++)
      sensitivity.push_back(1);
  }
}

void LifetimePdf::prepareCache(double lifetime) const {
  if (cachedTau==lifetime) return;
  cachedTau = lifetime;

  n.clear();
  n.reserve(32*924);

  double n0 = 0;
  int t0 = -1;
  int counter = 0;

  for (int i = 0; i < 32; i++) {
    for (int j = 0; j < 308; j++, counter++) {
      n[counter] = 1 - (1 - n0) * TMath::Exp(-(counter - t0) * 93.43 / lifetime);
      if (n[counter] <= 0) n[counter] = 0;
    }
    t0 = counter - 1;
    n0 = n[t0];
    for (int j = 0; j < 616; j++, counter++) {
      n[counter] = n0 * TMath::Exp(-(counter - t0) * 93.43 / lifetime);
      if (n[counter] <= 0) n[counter] = 0;
    }
    t0 = counter - 1;
    n0 = n[t0];
  }
}

TObject *LifetimePdf::clone(const char *othername) const {
  LifetimePdf *the_new_one = new LifetimePdf(*this, othername);
  return the_new_one;
}

Double_t LifetimePdf::evaluate() const {

  unsigned int current_time = t;
  double lifetime = tau;
  
  prepareCache(lifetime);

  return sensitivity[current_time] * n[current_time];

}

Int_t LifetimePdf::getAnalyticalIntegral(RooArgSet &allVars,
					 RooArgSet &anaVars,
					 const char *) const {

  if (matchArgs(allVars, anaVars, t)) return 1;
  return 0;

}

Double_t LifetimePdf::analyticalIntegral(Int_t,
					 const char *rangeName) const {
  double lifetime = tau;
  prepareCache(lifetime);

  double tMin = t.min(rangeName);
  double tMax = t.max(rangeName);

  unsigned int tMin_i = (unsigned int) tMin;
  unsigned int tMax_i = (unsigned int) tMax;

  double running_total = 0;
  running_total += (1 - (tMin - tMin_i))
    * sensitivity[tMin_i] * n[tMin_i];
  running_total += (tMax - tMax_i)
    * sensitivity[tMax_i] * n[tMax_i];
  for (uint32_t index = tMin_i + 1;
       index < tMax_i; index++)
    running_total += sensitivity[index] * n[index];

  return running_total;
}
