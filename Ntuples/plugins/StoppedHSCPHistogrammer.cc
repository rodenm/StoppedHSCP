
#include "StoppedHSCP/Ntuples/plugins/StoppedHSCPHistogrammer.h"

StoppedHSCPHistogrammer::StoppedHSCPHistogrammer(const edm::ParameterSet& iPSet)
{

}

StoppedHSCPHistogrammer::~StoppedHSCPHistogrammer() {

  std::vector<TH1D*>::iterator itr;
  for (itr=bxNormHistos_.begin(); itr!=bxNormHistos_.end(); ++itr) delete (*itr);

  bxNormHistos_.clear();

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
  return;
  // loop over fills
  std::vector<unsigned long>::const_iterator itr;
  for (itr=fillList_.begin(); itr!=fillList_.end(); ++itr) {

    // cd to directory
    std::stringstream fillstr;
    fillstr << (*itr);
    //    fillsDir_->cd();

    // save histograms
    bxNormHistos_.at(*itr)->Write("",TObject::kOverwrite);

  }

}

void StoppedHSCPHistogrammer::makeBXNormHistogram(unsigned long fill) {

  TFileDirectory dir = fs_->mkdir("fills");

  std::stringstream fillstr;
  fillstr << fill;

  // create histogram
  if (bxNormHistos_.size() < fill+1) bxNormHistos_.resize(fill+1, 0);
  bxNormHistos_.at(fill) =  dir.make<TH1D>((std::string("hNormRelBX_")+fillstr.str()).c_str(), "N rel BX slots", 2000, -1000., 1000.);

  // fill it
  for (unsigned i=0; i<3564; ++i) {
    bxNormHistos_.at(fill)->Fill( fills_.getBxWrtBunch(fill, i) );
  }

}




//define this as a plug-in
DEFINE_FWK_MODULE(StoppedHSCPHistogrammer);
