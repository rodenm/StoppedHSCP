
#ifndef HaloBackground_h
#define HaloBackground_h

#include "StoppedHSCP/Analysis/interface/BasicAnalyser.h"

#include "StoppedHSCP/Analysis/interface/MultiHistogram1D.h"

#include "TFile.h"
#include "TMath.h"
#include "TChain.h"
#include "TH1D.h"

using namespace std;

class HaloBackground : public BasicAnalyser {

public:
  HaloBackground(int argc, char* argv[]) :
    BasicAnalyser(argc, argv) {
    ofilename_ = std::string("HaloBackground.root");  /// SET YOUR OUTPUT FILENAME HERE
  }
  
  ~HaloBackground() { };
  
  virtual void loop();
  
private:

  // YOUR CODE HERE
  std::vector<unsigned long> fillList_;

  // control trigger
  TH1D* hControlTrigJetE_;
  TH1D* hControlTrigJetEta_;
  TH1D* hControlTrigJetPhi_;
  TH1D* hControlTrigTaggedJetE_;
  TH1D* hControlTrigTaggedJetEta_;
  TH1D* hControlTrigTaggedJetPhi_;

  // control region : BX==-1, n_trk==0
  TH1D* hControlJetE_;
  TH1D* hControlJetEta_;
  TH1D* hControlJetPhi_;

  MultiHistogram1D hByFillControlJetE_;
  MultiHistogram1D hByFillControlJetEta_;
  MultiHistogram1D hByFillControlJetPhi_;

  // tagged in control region
  TH1D* hControlTaggedJetE_;
  TH1D* hControlTaggedJetEta_;
  TH1D* hControlTaggedJetPhi_;

  MultiHistogram1D hByFillControlTaggedJetE_;
  MultiHistogram1D hByFillControlTaggedJetEta_;
  MultiHistogram1D hByFillControlTaggedJetPhi_;

  // normalisation region : |BX|>2, halo ID, 50<E<70
  TH1D* hNormTaggedJetE_;
  TH1D* hNormTaggedJetEta_;
  TH1D* hNormTaggedJetPhi_;

  MultiHistogram1D hByFillNormTaggedJetE_;
  MultiHistogram1D hByFillNormTaggedJetEta_;
  MultiHistogram1D hByFillNormTaggedJetPhi_;

  // signal region : |BX|>2, E>70
  TH1D* hSignalTaggedJetE_;
  TH1D* hSignalTaggedJetEta_;
  TH1D* hSignalTaggedJetPhi_;
  TH1D* hSignalTaggedNMu_;

  MultiHistogram1D hByFillSignalTaggedJetE_;
  MultiHistogram1D hByFillSignalTaggedJetEta_;
  MultiHistogram1D hByFillSignalTaggedJetPhi_;

  // unidentified halo histograms
  TH1D* hExpJetE_;
  TH1D* hExpJetEta_;
  TH1D* hExpJetPhi_;

  MultiHistogram1D hByFillExpJetE_;
  MultiHistogram1D hByFillExpJetEta_;
  MultiHistogram1D hByFillExpJetPhi_;


  // Fedor's method
  TH1D* hHBJetE_;
  TH1D* hHEJetE_;
  TH1D* hHEJetEta_;
  TH1D* hHEJetPhi_;

  TH1D* hHBHEdPhi_;
  TH1D* hHBCSCdPhi_;
  TH1D* hHECSCdPhi_;

  TH1D* hHEMatchedHEJetE_;
  TH1D* hHEMatchedHaloFlag_;

  TH1D* hHESidebandHaloFlag_;

  unsigned nMinusTwoHaloMuon_;
  unsigned nMinusOneHalo_;
  unsigned nMinusOneMuon_;

};

#endif


// this is the event loop
void HaloBackground::loop() {

  // DO ANY SETUP HERE

  // control trigger/region
  ofile_->cd();
  hControlTrigJetE_ = new TH1D("hControlTrigJetE", "Control E", 50, 0., 200.);
  hControlTrigJetEta_ = new TH1D("hControlTrigJetEta", "Control #eta", 70, -3.5, 3.5);
  hControlTrigJetPhi_ = new TH1D("hControlTrigJetPhi", "Control #phi", 72, -1 * TMath::Pi(),  TMath::Pi());
  hControlTrigTaggedJetE_ = new TH1D("hControlTrigTaggedJetE", "Control (tagged) E", 50, 0., 200.);
  hControlTrigTaggedJetEta_ = new TH1D("hControlTrigTaggedJetEta", "Control (tagged) #eta", 70, -3.5, 3.5);
  hControlTrigTaggedJetPhi_ = new TH1D("hControlTrigTaggedJetPhi", "Control (tagged) #phi", 72, -1 * TMath::Pi(),  TMath::Pi());

  // control region
  ofile_->cd();
  hControlJetE_ = new TH1D("hControlJetE", "Control E", 50, 0., 200.);
  hControlJetEta_ = new TH1D("hControlJetEta", "Control #eta", 70, -3.5, 3.5);
  hControlJetPhi_ = new TH1D("hControlJetPhi", "Control #phi", 72, -1 * TMath::Pi(),  TMath::Pi());
  
  hByFillControlJetE_.setup(ofile_, "ByFillControlJetE", "Control E", 50, 0., 200.);
  hByFillControlJetEta_.setup(ofile_, "ByFillControlJetEta", "Control #eta", 70, -3.5, 3.5);
  hByFillControlJetPhi_.setup(ofile_, "ByFillControlJetPhi", "Control #phi", 72, -1 * TMath::Pi(),  TMath::Pi());
  
  // control region, tagged
  ofile_->cd();
  hControlTaggedJetE_ = new TH1D("hControlTaggedJetE", "Control (tagged) E", 50, 0., 200.);
  hControlTaggedJetEta_ = new TH1D("hControlTaggedJetEta", "Control (tagged) #eta", 70, -3.5, 3.5);
  hControlTaggedJetPhi_ = new TH1D("hControlTaggedJetPhi", "Control (tagged) #phi", 72, -1 * TMath::Pi(),  TMath::Pi());
  
  hByFillControlTaggedJetE_.setup(ofile_, "ByFillControlTaggedJetE", "Control (tagged) E", 50, 0., 200.);
  hByFillControlTaggedJetEta_.setup(ofile_, "ByFillControlTaggedJetEta", "Control (tagged) #eta", 70, -3.5, 3.5);
  hByFillControlTaggedJetPhi_.setup(ofile_, "ByFillControlTaggedJetPhi", "Control (tagged) #phi", 72, -1 * TMath::Pi(),  TMath::Pi());

  // normalisation region : |BX|>2, halo ID, 50<E<70
  ofile_->cd();
  hNormTaggedJetE_ = new TH1D("hNormTaggedJetE", "Norm (tagged) E", 50, 0., 200.);
  hNormTaggedJetEta_ = new TH1D("hNormTaggedJetEta", "Norm (tagged) #eta", 70, -3.5, 3.5);
  hNormTaggedJetPhi_ = new TH1D("hNormTaggedJetPhi", "Norm (tagged) #phi", 72, -1 * TMath::Pi(),  TMath::Pi());
  
  hByFillNormTaggedJetE_.setup(ofile_, "ByFillNormTaggedJetE", "Norm (tagged) E", 50, 0., 200.);
  hByFillNormTaggedJetEta_.setup(ofile_, "ByFillNormTaggedJetEta", "Norm (tagged) #eta", 70, -3.5, 3.5);
  hByFillNormTaggedJetPhi_.setup(ofile_, "ByFillNormTaggedJetPhi", "Norm (tagged) #phi", 72, -1 * TMath::Pi(),  TMath::Pi());
  
  // signal region : |BX|>2, E>70
  ofile_->cd();
  hSignalTaggedJetE_ = new TH1D("hSignalTaggedJetE", "Signal (tagged) E", 50, 0., 200.);
  hSignalTaggedJetEta_ = new TH1D("hSignalTaggedJetEta", "Signal (tagged) #eta", 70, -3.5, 3.5);
  hSignalTaggedJetPhi_ = new TH1D("hSignalTaggedJetPhi", "Signal (tagged) #phi", 72, -1 * TMath::Pi(),  TMath::Pi());
  
  hByFillSignalTaggedJetE_.setup(ofile_, "ByFillSignalTaggedJetE", "Signal (tagged) E", 50, 0., 200.);
  hByFillSignalTaggedJetEta_.setup(ofile_, "ByFillSignalTaggedJetEta", "Signal (tagged) #eta", 70, -3.5, 3.5);
  hByFillSignalTaggedJetPhi_.setup(ofile_, "ByFillSignalTaggedJetPhi", "Signal (tagged) #phi", 72, -1 * TMath::Pi(),  TMath::Pi());
  
  hSignalTaggedNMu_ = new TH1D("hSignalTaggedMu", "Signal (tagged) N_{#mu}", 5, 0, 5.);
  
  // prediction
  ofile_->cd();
  hExpJetE_ = new TH1D("hExpJetE", "Prediction E", 50, 0., 200.);
  hExpJetEta_ = new TH1D("hExpJetEta", "Prediction #eta", 70, -3.5, 3.5);
  hExpJetPhi_ = new TH1D("hExpJetPhi", "Prediction #phi", 72, -1 * TMath::Pi(),  TMath::Pi());
  
  hByFillExpJetE_.setup(ofile_, "ByFillExpJetE", "Prediction E", 50, 0., 200.);
  hByFillExpJetEta_.setup(ofile_, "ByFillExpJetEta", "Prediction #eta", 70, -3.5, 3.5);
  hByFillExpJetPhi_.setup(ofile_, "ByFillExpJetPhi", "Prediction #phi", 72, -1 * TMath::Pi(),  TMath::Pi());

  // Fedor's method
  hHBJetE_      = new TH1D("hHBJetE", "HE Jet E", 50, 0., 50.);
  hHEJetE_      = new TH1D("hHEJetE", "HE Jet E", 50, 0., 50.);
  hHEJetEta_    = new TH1D("hHEJetEta", "HE Jet #eta", 70, -3.5, 3.5);
  hHEJetPhi_    = new TH1D("hHEJetPhi", "HE Jet #phi", 72, -1 * TMath::Pi(),  TMath::Pi());

  hHBHEdPhi_   = new TH1D("hHBHEdPhi", "HB-HE d#phi", 72, -2 * TMath::Pi(),  2 * TMath::Pi());
  hHBCSCdPhi_  = new TH1D("hHBCSCdPhi", "HB-CSC d#phi", 72, -2 * TMath::Pi(),  2 * TMath::Pi());
  hHECSCdPhi_  = new TH1D("hHECSCdPhi", "HE-CSC d#phi", 72, -2 * TMath::Pi(),  2 * TMath::Pi());

  hHEMatchedHEJetE_ = new TH1D("hMatchedHEJetE", "HE Matched E", 50, 0., 50.);
  hHEMatchedHaloFlag_ = new TH1D("hHEMatchedHaloFlag", "HE matched halo flag", 2, -0.5, 1.5);
  hHESidebandHaloFlag_ = new TH1D("hHESidebandHaloFlag", "HE matched halo flag", 2, -0.5, 1.5);

  nMinusTwoHaloMuon_=0;
  nMinusOneHalo_=0;
  nMinusOneMuon_=0;

  reset();
  nextEvent();

  for (unsigned long i=0; i<maxEvents_; ++i, nextEvent()) {

    // occasional print out
    if (i%100000==0) {
      std::cout << "Processing " << i << "th event of " <<maxEvents_<< std::endl;
    }

    // YOUR CODE HERE

    // keep a record of fills covered
    unsigned long fill=event_->fill;
    std::vector<unsigned long>::const_iterator itr = find(fillList_.begin(), fillList_.end(), fill);
    if (itr == fillList_.end()) fillList_.push_back(fill);

    // check there is a jet
    if (event_->jet_N==0) continue;

    // regions
    bool control = (event_->bxWrtBunch==-1 && event_->vtx_N==0 && event_->track_N==0 && event_->noiseFilterResult);
    bool norm    = (abs(event_->bxWrtBunch)>2 && event_->jetE[0]>50 && event_->jetE[0]<70);
    bool signal  = (abs(event_->bxWrtBunch)>2 && event_->jetE[0]>70);

    // triggers
    bool conTrig = event_->hltJetNoBptx;

    // tag
    bool tag     = event_->beamHalo_CSCLoose;

    // jet properties
    double e   = event_->jetE[0];
    double eta = event_->jetEta[0];
    double phi = event_->jetPhi[0];

    if (conTrig && control) {
      hControlTrigJetE_->Fill(e);
      hControlTrigJetEta_->Fill(eta);
      hControlTrigJetPhi_->Fill(phi);
    }

    if (conTrig && control && tag) {
      hControlTrigTaggedJetE_->Fill(e);
      hControlTrigTaggedJetEta_->Fill(eta);
      hControlTrigTaggedJetPhi_->Fill(phi);
    }

    if (control) {
      hControlJetE_->Fill(e);
      hControlJetEta_->Fill(eta);
      hControlJetPhi_->Fill(phi);
      hByFillControlJetE_.fill(fill, e, 1.);
      hByFillControlJetEta_.fill(fill, eta, 1.);
      hByFillControlJetPhi_.fill(fill, phi, 1.);

      hExpJetE_->Fill(e);
      hExpJetEta_->Fill(eta);
      hExpJetPhi_->Fill(phi);
      hByFillExpJetE_.fill(fill, e, 1.);
      hByFillExpJetEta_.fill(fill, eta, 1.);
      hByFillExpJetPhi_.fill(fill, phi, 1.);
    }

    if (control && tag) {
      hControlTaggedJetE_->Fill(e);
      hControlTaggedJetEta_->Fill(eta);
      hControlTaggedJetPhi_->Fill(phi);
      hByFillControlTaggedJetE_.fill(fill, e, 1.);
      hByFillControlTaggedJetEta_.fill(fill, eta, 1.);
      hByFillControlTaggedJetPhi_.fill(fill, phi, 1.);
    }

    if (norm && tag) {
      hNormTaggedJetE_->Fill(e);
      hNormTaggedJetEta_->Fill(eta);
      hNormTaggedJetPhi_->Fill(phi);
      hByFillNormTaggedJetE_.fill(fill, e, 1.);
      hByFillNormTaggedJetEta_.fill(fill, eta, 1.);
      hByFillNormTaggedJetPhi_.fill(fill, phi, 1.);
    }

    if (signal && tag) {
      hSignalTaggedJetE_->Fill(e);
      hSignalTaggedJetEta_->Fill(eta);
      hSignalTaggedJetPhi_->Fill(phi);
      hSignalTaggedNMu_->Fill(event_->mu_N);
      hByFillSignalTaggedJetE_.fill(fill, e, 1.);
      hByFillSignalTaggedJetEta_.fill(fill, eta, 1.);
      hByFillSignalTaggedJetPhi_.fill(fill, phi, 1.);
    }
    // Fedor's method

    // HB jet
    bool isHB = (event_->bxWrtBunch>2 && e > 70.);
    
    // HE jet
    bool isHE = (event_->studyJet_N > 0);
    double he_e = 999.;
    double he_eta = 999.;
    double he_phi = 999.;
    if (isHE) {
      he_e = event_->studyJetE[0];
      he_eta = event_->studyJetEta[0];
      he_phi = event_->studyJetPhi[0];
    }

    double he_dphi  = phi - he_phi;    
    bool heMatch    = (fabs(he_dphi) < 0.15 && he_eta > 1.4);
    bool heSideband = (0.25 < fabs(he_dphi) && fabs(he_dphi) < 0.4);

    // CSC segment
    double csc_z=999999.;
    double csc_phi = 999.;
    
    for (unsigned i=0; i<event_->cscSeg_N; ++i) {
      if (event_->cscSegZ[i] < csc_z) {
	csc_z   = event_->cscSegZ[i];
	csc_phi = event_->cscSegPhi[i];
      }
    }

    double csc_dphi  = phi - csc_phi;
    bool cscMatch    = (fabs(csc_dphi) < 0.4);
    bool cscSideband = (0.5 < fabs(csc_dphi) && fabs(csc_dphi) < 0.9);
    
    int haloFlag = (event_->beamHalo_CSCLoose ? 1 : 0);

    // there is a HB jet
    if (isHB && isHE) {
      hHBJetE_->Fill(e);
      hHEJetE_->Fill(he_e);    
      hHEJetEta_->Fill(he_eta);    
      hHEJetPhi_->Fill(he_phi);    
      hHBHEdPhi_->Fill(he_dphi);
    }

    if (isHB) {
      hHBCSCdPhi_->Fill(csc_dphi);
    }
    
    // there is a tag
    if (isHB && isHE && heMatch) {
      hHEMatchedHEJetE_->Fill(he_e);
      hHEMatchedHaloFlag_->Fill(haloFlag);
    }

    // sidebands
    if (isHB && isHE && heSideband) {
      hHESidebandHaloFlag_->Fill(haloFlag);
    }
    
    if (cuts_.triggerCut() &&
	cuts_.bptxVeto() &&
	cuts_.bxVeto() &&
	cuts_.vertexVeto() &&
	cuts_.hcalNoiseVeto() &&
	cuts_.jetEnergyCut() &&
	cuts_.jetN60Cut() &&
	cuts_.jetN90Cut() &&
	cuts_.towersIPhiCut() &&
	cuts_.iPhiFractionCut() &&
	cuts_.hpdR1Cut() &&
	cuts_.hpdR2Cut() &&
	cuts_.hpdRPeakCut() && 
	cuts_.hpdROuterCut()) nMinusTwoHaloMuon_++;


    if (cuts_.triggerCut() &&
	cuts_.bptxVeto() &&
	cuts_.bxVeto() &&
	cuts_.vertexVeto() &&
	cuts_.cosmicVeto() &&
	cuts_.hcalNoiseVeto() &&
	cuts_.jetEnergyCut() &&
	cuts_.jetN60Cut() &&
	cuts_.jetN90Cut() &&
	cuts_.towersIPhiCut() &&
	cuts_.iPhiFractionCut() &&
	cuts_.hpdR1Cut() &&
	cuts_.hpdR2Cut() &&
	cuts_.hpdRPeakCut() && 
	cuts_.hpdROuterCut()) nMinusOneHalo_++;


    if (cuts_.triggerCut() &&
	cuts_.bptxVeto() &&
	cuts_.bxVeto() &&
	cuts_.vertexVeto() &&
	cuts_.haloVeto() &&
	cuts_.hcalNoiseVeto() &&
	cuts_.jetEnergyCut() &&
	cuts_.jetN60Cut() &&
	cuts_.jetN90Cut() &&
	cuts_.towersIPhiCut() &&
	cuts_.iPhiFractionCut() &&
	cuts_.hpdR1Cut() &&
	cuts_.hpdR2Cut() &&
	cuts_.hpdRPeakCut() && 
	cuts_.hpdROuterCut()) nMinusOneMuon_++;

  }

  // estimate halo BG
  for (std::vector<unsigned long>::const_iterator f=fillList_.begin(); f!=fillList_.end(); ++f) {

    std::cout << "Estimating BG for fill " << (*f) << std::endl;

    // get normalisation constant
    double norm =0.;
    if (hByFillNormTaggedJetE_.histogram(*f) == 0 || 
	hByFillControlJetE_.histogram(*f) == 0)  continue;

    norm = hByFillNormTaggedJetE_.histogram(*f)->Integral(14,18);
    norm /= hByFillControlJetE_.histogram(*f)->Integral(14,18);
    
    if (hByFillExpJetE_.hist(*f) != 0) {
      hByFillExpJetE_.hist(*f)->Scale(norm);
      hByFillExpJetEta_.hist(*f)->Scale(norm);
      hByFillExpJetPhi_.hist(*f)->Scale(norm);
    }

  }


  // SAVE HISTOGRAMS HERE
  ofile_->cd();
  hControlTrigJetE_->Write("",TObject::kOverwrite);
  hControlTrigJetEta_->Write("",TObject::kOverwrite);
  hControlTrigJetPhi_->Write("",TObject::kOverwrite);
  hControlTrigTaggedJetE_->Write("",TObject::kOverwrite);
  hControlTrigTaggedJetEta_->Write("",TObject::kOverwrite);
  hControlTrigTaggedJetPhi_->Write("",TObject::kOverwrite);

  ofile_->cd();
  hControlJetE_->Write("",TObject::kOverwrite);
  hControlJetEta_->Write("",TObject::kOverwrite);
  hControlJetPhi_->Write("",TObject::kOverwrite);
  hByFillControlJetE_.save();
  hByFillControlJetEta_.save();
  hByFillControlJetPhi_.save();

  ofile_->cd();
  hControlTaggedJetE_->Write("",TObject::kOverwrite);
  hControlTaggedJetEta_->Write("",TObject::kOverwrite);
  hControlTaggedJetPhi_->Write("",TObject::kOverwrite);
  hByFillControlTaggedJetE_.save();
  hByFillControlTaggedJetEta_.save();
  hByFillControlTaggedJetPhi_.save();

  
  // normalisation region : |BX|>2, halo ID, 50<E<70
  ofile_->cd();
  hNormTaggedJetE_->Write("",TObject::kOverwrite);
  hNormTaggedJetEta_->Write("",TObject::kOverwrite);
  hNormTaggedJetPhi_->Write("",TObject::kOverwrite);
  
  hByFillNormTaggedJetE_.save();
  hByFillNormTaggedJetEta_.save();
  hByFillNormTaggedJetPhi_.save();
  
  // signal region : |BX|>2, E>70
  ofile_->cd();
  hSignalTaggedJetE_->Write("",TObject::kOverwrite);
  hSignalTaggedJetEta_->Write("",TObject::kOverwrite);
  hSignalTaggedJetPhi_->Write("",TObject::kOverwrite);
  hSignalTaggedNMu_->Write("",TObject::kOverwrite);
  
  hByFillSignalTaggedJetE_.save();
  hByFillSignalTaggedJetEta_.save();
  hByFillSignalTaggedJetPhi_.save();
 
  // nonID halo
  ofile_->cd();
  hExpJetE_->Write("",TObject::kOverwrite);
  hExpJetEta_->Write("",TObject::kOverwrite);
  hExpJetPhi_->Write("",TObject::kOverwrite);
  
  hByFillExpJetE_.save();
  hByFillExpJetEta_.save();
  hByFillExpJetPhi_.save();

  // Fedor's method
  int matchFlags = hHEMatchedHaloFlag_->GetBinContent(2);
  int matchNoflags = hHEMatchedHaloFlag_->GetBinContent(1);
  int sidebandFlags = hHESidebandHaloFlag_->GetBinContent(2);
  int sidebandNoflags = hHESidebandHaloFlag_->GetBinContent(1);

  std::cout << std::endl;
  std::cout << "HE Tag&Probe results :" << std::endl;
  std::cout << "  HE matched events.  CSC flags=" << hHEMatchedHaloFlag_->GetBinContent(2) << "  Unflagged=" << hHEMatchedHaloFlag_->GetBinContent(1) << std::endl;
  std::cout << "  HE sideband events.  CSC flags=" << hHESidebandHaloFlag_->GetBinContent(2) << "  Unflagged=" << hHESidebandHaloFlag_->GetBinContent(1) << std::endl;
  std::cout << std::endl;
  int tot = (matchFlags -sidebandFlags) + (matchNoflags - sidebandNoflags);
  std::cout << "  CSC flag efficiency=" << 1.0*(matchFlags-sidebandFlags)/(tot) << std::endl;

  std::cout <<std::endl;
  std::cout << "N-2 (halo, muon) counts = " << nMinusTwoHaloMuon_ << std::endl;
  std::cout << "N-1 (halo) counts = " << nMinusOneHalo_ << std::endl;
  std::cout << "N-1 (muon) counts = " << nMinusOneMuon_ << std::endl;
  std::cout << "Estimated BG = " << nMinusTwoHaloMuon_ * matchNoflags/(matchNoflags+matchFlags) << std::endl;

  ofile_->cd();
  hHBJetE_->Write("",TObject::kOverwrite);
  hHEJetE_->Write("",TObject::kOverwrite);
  hHEJetEta_->Write("",TObject::kOverwrite);
  hHEJetPhi_->Write("",TObject::kOverwrite);
  hHBHEdPhi_->Write("",TObject::kOverwrite);
  hHBCSCdPhi_->Write("",TObject::kOverwrite);
  hHECSCdPhi_->Write("",TObject::kOverwrite);
  hHEMatchedHEJetE_->Write("",TObject::kOverwrite);
  hHEMatchedHaloFlag_->Write("",TObject::kOverwrite);
  hHESidebandHaloFlag_->Write("",TObject::kOverwrite);

}



// this is the main program, no need to do anything here
int main(int argc, char* argv[]) {

  // sum of squares error info for histograms
  TH1D::SetDefaultSumw2();

  // create analysis
  HaloBackground analyser(argc, argv);

  analyser.setup();

  analyser.cuts().print(std::cout);

  analyser.loop();

  return 0;

}
