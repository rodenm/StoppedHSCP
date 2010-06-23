#include "StoppedHSCP/ToyMC/interface/SimpleBGPdf.h"

SimpleBGPdf::SimpleBGPdf(const SimpleBGPdf &other,
			 const char *name)
  : RooAbsPdf(other, name),
    sensitivity(other.sensitivity),
    t("t", this, other.t)
{}
    

SimpleBGPdf::SimpleBGPdf(const char *name,
			 const char *title,
			 RooAbsReal &_t)
  : RooAbsPdf(name, title),
    t("ls", "ls", this, _t)
{
  sensitivity.clear();
  sensitivity.reserve(32*924);

  for (int i = 0; i < 32; i++) {
    for (int j = 0; j < 308; j++)
      sensitivity.push_back(1.-2808./3564.);
    for (int j = 0; j < 616; j++)
      sensitivity.push_back(1);
  }

}

TObject *SimpleBGPdf::clone(const char *othername) const {
  SimpleBGPdf *the_new_one = new SimpleBGPdf(*this, othername);
  return the_new_one;
}

Double_t SimpleBGPdf::evaluate() const {

  unsigned int current_time = t;
  
  return sensitivity[current_time];

}

Int_t SimpleBGPdf::getAnalyticalIntegral(RooArgSet &allVars,
					 RooArgSet &anaVars,
					 const char *) const {

  if (matchArgs(allVars, anaVars, t)) return 1;
  return 0;

}

Double_t SimpleBGPdf::analyticalIntegral(Int_t,
					 const char *rangeName) const {
  double tMin = t.min(rangeName);
  double tMax = t.max(rangeName);

  unsigned int tMin_i = (unsigned int) tMin;
  unsigned int tMax_i = (unsigned int) tMax;

  double running_total = 0;
  running_total += (1 - (tMin - tMin_i))
    * sensitivity[tMin_i];
  running_total += (tMax - tMax_i)
    * sensitivity[tMax_i];
  for (uint32_t index = tMin_i + 1;
       index < tMax_i; index++)
    running_total += sensitivity[index];

  return running_total;
}
