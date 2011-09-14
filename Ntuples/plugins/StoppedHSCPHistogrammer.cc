
#include "StoppedHSCP/Ntuples/plugins/StoppedHSCPHistogrammer.h"

StoppedHSCPHistogrammer::StoppedHSCPHistogrammer() {

  fs_->mkdir("histograms");
  fs_->mkdir("histograms/fills");

}

StoppedHSCPHistogrammer::~StoppedHSCPHistogrammer() {

}

void StoppedHSCPHistogrammer::beginJob() {

}

void StoppedHSCPHistogrammer::beginRun(const edm::Run& iRun, const edm::EventSetup& iSetup) {

  unsigned long fill = fills_.getFillFromRun(iRun.runAuxiliary().run());

  // check if this run has already been booked
  std::vector<unsigned long>::const_iterator itr = find(fillList_.begin(), fillList_.end(), fill);

  // if not, fill histograms
  if (fillList_.end() == itr) {
    makeBXNormHistogram(fill);
    fillList_.push_back(fill);
  }

}

void StoppedHSCPHistogrammer::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup) {

}

void StoppedHSCPHistogrammer::endJob() {

}

void StoppedHSCPHistogrammer::makeBXNormHistogram(unsigned long fill) {

  //  fs_->cd("histograms/fills");
  
  std::stringstream fillstr;
  fillstr << fill;

  // create histogram
  if (bxNormHistos_.size() < fill+1) bxNormHistos_.resize(fill+1, 0);
  bxNormHistos_.at(fill) =  new TH1D((std::string("hNormRelBX")+fillstr.str()).c_str(), "N rel BX slots", 2000, -1000., 1000.);

  // fill it
  for (unsigned i=0; i<3564; ++i) {
    bxNormHistos_.at(fill)->Fill( fills_.getBxWrtBunch(fill, i) );
  }

}


