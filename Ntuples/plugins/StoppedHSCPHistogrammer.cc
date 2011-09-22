
#include "StoppedHSCP/Ntuples/plugins/StoppedHSCPHistogrammer.h"

StoppedHSCPHistogrammer::StoppedHSCPHistogrammer(const edm::ParameterSet& iPSet)
{

}


StoppedHSCPHistogrammer::~StoppedHSCPHistogrammer() {

  std::vector<TH1D*>::iterator itr;

  for (itr=runLSHistos_.begin(); itr!=runLSHistos_.end(); ++itr) delete (*itr);
  for (itr=runEventLSHistos_.begin(); itr!=runEventLSHistos_.end(); ++itr) delete (*itr);
  for (itr=bxNormHistos_.begin(); itr!=bxNormHistos_.end(); ++itr) delete (*itr);

  runLSHistos_.clear();
  runEventLSHistos_.clear();
  bxNormHistos_.clear();

}


void StoppedHSCPHistogrammer::beginJob() {

}


void StoppedHSCPHistogrammer::beginRun(const edm::Run& iRun, const edm::EventSetup& iSetup) {

  // book per-run histograms
  unsigned long run = iRun.runAuxiliary().run();
  std::vector<unsigned long>::const_iterator itr1 = find(runList_.begin(), runList_.end(), run);

  if (runList_.end() == itr1) {
    bookPerRunHistograms(run);
    runList_.push_back(run);
  }


  // book per-fill histograms
  unsigned long fill = fills_.getFillFromRun(iRun.runAuxiliary().run());
  std::vector<unsigned long>::const_iterator itr2 = find(fillList_.begin(), fillList_.end(), fill);

  if (fillList_.end() == itr2) {
    bookPerFillHistograms(fill);
    fillList_.push_back(fill);
  }

}


void StoppedHSCPHistogrammer::beginLuminosityBlock(const edm::LuminosityBlock& iBlock, const edm::EventSetup& iSetup) {

  unsigned long run = iBlock.luminosityBlockAuxiliary().run();
  unsigned long ls  = iBlock.luminosityBlockAuxiliary().luminosityBlock();

  runLSHistos_.at(run)->Fill(ls);

}


void StoppedHSCPHistogrammer::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup) {

  unsigned long run = iEvent.id().run();
  unsigned long ls  = iEvent.luminosityBlock();

  // fill run event LS histogram
  runEventLSHistos_.at(run)->Fill(ls);

}


void StoppedHSCPHistogrammer::endJob() {

  // save per-run histos
  TFileDirectory dir1 = fs_->mkdir("runs");
  dir1.cd();
  std::vector<unsigned long>::const_iterator itr1;
  for (itr1=runList_.begin(); itr1!=runList_.end(); ++itr1) {
    runLSHistos_.at(*itr1)->Write();
    runEventLSHistos_.at(*itr1)->Write();
  }

  // save per-fill histos
  TFileDirectory dir2 = fs_->mkdir("fills");
  dir2.cd();
  std::vector<unsigned long>::const_iterator itr2;
  for (itr2=fillList_.begin(); itr2!=fillList_.end(); ++itr2) {
    bxNormHistos_.at(*itr2)->Write();
  }

}


void StoppedHSCPHistogrammer::bookPerRunHistograms(unsigned long run) {

  TFileDirectory dir = fs_->mkdir("runs");

  std::stringstream runstr;
  runstr << run;

  if (runLSHistos_.size() < run+1) runLSHistos_.resize(run+1, 0);
  runLSHistos_.at(run) = dir.make<TH1D>((std::string("hLS_")+runstr.str()).c_str(), "Lumi block", 5000, 0., 5000.);

  if (runEventLSHistos_.size() < run+1) runEventLSHistos_.resize(run+1, 0);
  runEventLSHistos_.at(run) = dir.make<TH1D>((std::string("hEventLS_")+runstr.str()).c_str(), "Lumi block", 5000, 0., 5000.);

}


void StoppedHSCPHistogrammer::bookPerFillHistograms(unsigned long fill) {

  TFileDirectory dir = fs_->mkdir("fills");

  std::stringstream fillstr;
  fillstr << fill;

  // create histograms
  if (bxNormHistos_.size() < fill+1) bxNormHistos_.resize(fill+1, 0);
  bxNormHistos_.at(fill) =  dir.make<TH1D>((std::string("hNormRelBX_")+fillstr.str()).c_str(), "N rel BX slots", 2000, -1000., 1000.);


  // BX normalisation histograms are filled here too!
  for (unsigned i=0; i<3564; ++i) {
    bxNormHistos_.at(fill)->Fill( fills_.getBxWrtBunch(fill, i) );
  }

}




//define this as a plug-in
DEFINE_FWK_MODULE(StoppedHSCPHistogrammer);
