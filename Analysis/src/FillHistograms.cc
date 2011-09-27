#include "StoppedHSCP/Analysis/interface/FillHistograms.h"

#include "StoppedHSCP/Ntuples/interface/Constants.h"

#include "TMath.h"

#include <sstream>
#include <iostream>

FillHistograms::FillHistograms(TFile* file, Cuts* cuts, LhcFills* fills) :
  cuts_(cuts),
  base_(),
  lhcFills_(fills),
  fills_(0),
  nEvts_(0),
  lb_(0),
  nm1_(),
  nFin_(0),
  hbx_(0),
  hrelbx_(0),
  hrelbxvtx_(0),
  hrelbxhalo_(0),
  hrelbxbg_(0),
  hrelbxcos_(0),
  hrelbxnoise_(0),
  hrelbxnoid_(0),
  hbxB_(0),
  hnm1_(0),
  hcolls_(0),
  hbunches_(0),
  hnormrelbx_(0)
{
 
  // create directory structure
  file->mkdir("fills");
  base_ = file->GetDirectory("fills");

  // these histograms will be booked on the fly
  //  book();

}


FillHistograms::~FillHistograms() {

  // print list of fills found
  sort(fills_.begin(), fills_.end());
  std::cout << std::endl;
  std::cout << "Fills : ";
  for (unsigned i=0; i<fills_.size(); ++i) {
    std::cout << fills_.at(i);
    if (i<fills_.size()-1) std::cout << ",";
  }
  std::cout << std::endl;

  // clean up memory
  std::vector<TH1D*>::iterator itr;

  for (itr=hbx_.begin(); itr!=hbx_.end(); ++itr) delete (*itr);
  for (itr=hrelbx_.begin(); itr!=hrelbx_.end(); ++itr) delete (*itr);
  for (itr=hrelbxvtx_.begin(); itr!=hrelbxvtx_.end(); ++itr) delete (*itr);
  for (itr=hrelbxhalo_.begin(); itr!=hrelbxhalo_.end(); ++itr) delete (*itr);
  for (itr=hrelbxbg_.begin(); itr!=hrelbxbg_.end(); ++itr) delete (*itr);
  for (itr=hrelbxcos_.begin(); itr!=hrelbxcos_.end(); ++itr) delete (*itr);
  for (itr=hrelbxnoise_.begin(); itr!=hrelbxnoise_.end(); ++itr) delete (*itr);
  for (itr=hrelbxnoid_.begin(); itr!=hrelbxnoid_.end(); ++itr) delete (*itr);
  for (itr=hbxB_.begin(); itr!=hbxB_.end(); ++itr) delete (*itr);
  for (itr=hnm1_.begin(); itr!=hnm1_.end(); ++itr) delete (*itr);
  for (itr=hcolls_.begin(); itr!=hcolls_.end(); ++itr) delete (*itr);
  for (itr=hbunches_.begin(); itr!=hbunches_.end(); ++itr) delete (*itr);
  for (itr=hnormrelbx_.begin(); itr!=hnormrelbx_.end(); ++itr) delete (*itr);

  hbx_.clear();
  hbxB_.clear();
  hrelbx_.clear();
  hrelbxvtx_.clear();
  hrelbxhalo_.clear();
  hrelbxbg_.clear();
  hrelbxcos_.clear();
  hrelbxnoise_.clear();
  hrelbxnoid_.clear();
  hnm1_.clear();
  hcolls_.clear();
  hbunches_.clear();
  hnormrelbx_.clear();

}



void FillHistograms::book(unsigned long fill) {

  // check if this run has already been booked and bail if so
  std::vector<unsigned long>::const_iterator itr = find(fills_.begin(), fills_.end(), fill);
  if (itr != fills_.end()) return;

  std::cout << "Creating histograms for new fill #" << fill << std::endl;

  // set up new run directory 
  std::stringstream fillstr;
  fillstr << fill;
  base_->mkdir(fillstr.str().c_str());

  // resize vectors if need be, without creating histograms
  if (nEvts_.size() < fill+1) nEvts_.resize(fill+1, 0);
  if (nLB_.size() < fill+1) nLB_.resize(fill+1, 0);
  if (nm1_.size() < fill+1) nm1_.resize(fill+1, std::vector<unsigned long>(cuts_->nCuts()));
  if (nFin_.size() < fill+1) nFin_.resize(fill+1, 0);

  if (nm1Test0_.size() < fill+1) nm1Test0_.resize(fill+1, 0);
  if (nm1Test1_.size() < fill+1) nm1Test1_.resize(fill+1, 0);
  if (nm1Test2_.size() < fill+1) nm1Test2_.resize(fill+1, 0);
  if (nm1Test3_.size() < fill+1) nm1Test3_.resize(fill+1, 0);
  if (nm1Test4_.size() < fill+1) nm1Test4_.resize(fill+1, 0);
  if (nm1Test5_.size() < fill+1) nm1Test5_.resize(fill+1, 0);
  if (nm1Test6_.size() < fill+1) nm1Test6_.resize(fill+1, 0);

  if (hbx_.size() < fill+1) hbx_.resize(fill+1, 0);
  if (hrelbx_.size() < fill+1) hrelbx_.resize(fill+1, 0);
  if (hrelbxvtx_.size() < fill+1) hrelbxvtx_.resize(fill+1, 0);
  if (hrelbxhalo_.size() < fill+1) hrelbxhalo_.resize(fill+1, 0);
  if (hrelbxbg_.size() < fill+1) hrelbxbg_.resize(fill+1, 0);
  if (hrelbxcos_.size() < fill+1) hrelbxcos_.resize(fill+1, 0);
  if (hrelbxnoise_.size() < fill+1) hrelbxnoise_.resize(fill+1, 0);
  if (hrelbxnoid_.size() < fill+1) hrelbxnoid_.resize(fill+1, 0);
  if (hbxB_.size() < fill+1) hbxB_.resize(fill+1, 0);
  if (hnm1_.size() < fill+1) hnm1_.resize(fill+1, 0);
  if (hcolls_.size() < fill+1) hcolls_.resize(fill+1, 0);
  if (hbunches_.size() < fill+1) hbunches_.resize(fill+1, 0);
  if (hnormrelbx_.size() < fill+1) hnormrelbx_.resize(fill+1, 0);

  // and book histograms
  hbx_.at(fill) = new TH1D((std::string("hbx")+fillstr.str()).c_str(), "BX number", 3564, 0., 3564.);
  hrelbx_.at(fill) = new TH1D((std::string("hrelbx")+fillstr.str()).c_str(), "BX wrt bunch", 2000, -1000., 1000.);
  hbxB_.at(fill) = new TH1D((std::string("hbxB")+fillstr.str()).c_str(), "BX number", 3564, 0., 3564.);
  //hnm1_.at(fill) = new TH1D((std::string("hnm1")+fillstr.str()).c_str(), "N-1 counts", 20, 0., 20.);
  hrelbxhalo_.at(fill) = new TH1D((std::string("hrelbxhalo")+fillstr.str()).c_str(), "RelBX - halo", 2000, -1000., 1000.);
  hrelbxvtx_.at(fill) = new TH1D((std::string("hrelbxvtx")+fillstr.str()).c_str(), "Rel BX - collisions", 2000, -1000., 1000.);
  hrelbxbg_.at(fill) = new TH1D((std::string("hrelbxbg")+fillstr.str()).c_str(), "Rel BX - beam-gas", 2000, -1000., 1000.);
  hrelbxcos_.at(fill) = new TH1D((std::string("hrelbxcos")+fillstr.str()).c_str(), "Rel BX - cosmics", 2000, -1000., 1000.);
  hrelbxnoise_.at(fill) = new TH1D((std::string("hrelbxnoise")+fillstr.str()).c_str(), "Rel BX - noise", 2000, -1000., 1000.);
  hrelbxnoid_.at(fill) = new TH1D((std::string("hrelbxnoid")+fillstr.str()).c_str(), "Rel BX - no ID", 2000, -1000., 1000.);

  // book and fill filling scheme histos
  hcolls_.at(fill) = new TH1D((std::string("hcolls")+fillstr.str()).c_str(), "Collisions", 3564, 0., 3564.);
  hbunches_.at(fill) = new TH1D((std::string("hbunches")+fillstr.str()).c_str(), "Bunches", 3564, 0., 3564.);
  hnormrelbx_.at(fill) =  new TH1D((std::string("hnormrelbx")+fillstr.str()).c_str(), "N rel BX slots", 2000, -1000., 1000.);

  std::vector<unsigned long> colls = lhcFills_->getCollisions(fill);
  std::vector<unsigned long> bunches = lhcFills_->getBunches(fill);

  for (unsigned i=0; i<colls.size(); ++i) {
    hcolls_.at(fill)->Fill(colls.at(i));
  }
  for (unsigned i=0; i<bunches.size(); ++i) {
    hbunches_.at(fill)->Fill(bunches.at(i));
  }

  // relative BX normalisation histogram
  for (unsigned i=0; i<3564; ++i) {
    hnormrelbx_.at(fill)->Fill( lhcFills_->getBxWrtBunch(fill, i) );
  }

  // record the fact we booked this fill already
  fills_.push_back(fill);

}


void FillHistograms::fill(StoppedHSCPEvent& event) {

  // get fill number
  unsigned long fill = event.fill;

  // book histos
  book(fill);
  
  // count stuff
  nEvts_.at(fill) += 1;
  
  std::pair<unsigned long, unsigned long> lb(event.run, event.lb);
  if (find(lb_.begin(), lb_.end(), lb) == lb_.end()) {
    lb_.push_back(lb);
    nLB_.at(fill) += 1;
  }
  
  // N-1 histo
  for (unsigned cut=0; cut<cuts_->nCuts(); ++cut) {
    if (cuts_->cutNMinusOne(cut)) nm1_.at(fill).at(cut) += 1;
  }

  if (cuts_->cut()) nFin_.at(fill) += 1;

  std::vector<unsigned> noise;
  noise.push_back(6);
  noise.push_back(9);
  noise.push_back(11);
  noise.push_back(12);
  std::vector<unsigned> timing;
  timing.push_back(13);
  timing.push_back(14);
  timing.push_back(15);
  timing.push_back(16);
  if (cuts_->cutNMinusOne(2)) nm1Test0_.at(fill) += 1.;
  if (cuts_->cutNMinusOne(3)) nm1Test1_.at(fill) += 1.;
  if (cuts_->cutNMinusOne(4)) nm1Test2_.at(fill) += 1.;
  if (cuts_->cutNMinusOne(5)) nm1Test3_.at(fill) += 1.;
  if (cuts_->cutNMinusSome(noise)) nm1Test4_.at(fill) += 1.;
  if (cuts_->cutNMinusOne(10)) nm1Test5_.at(fill) += 1.;
  if (cuts_->cutNMinusSome(timing)) nm1Test6_.at(fill) += 1.;
 
  // fill histos
  hbx_.at(fill)->Fill(event.bx);
  hrelbx_.at(fill)->Fill(event.bxWrtBunch);

  if (cuts_->allCutN(8)) {
    hbxB_.at(fill)->Fill(event.bx);
  }

  if (event.jet_N>0 && event.jetE[0]>30. && event.jetEta[0]<1.3) {
    if (event.vtx_N>0) hrelbxvtx_.at(fill)->Fill(event.bxWrtBunch);
    if (event.vtx_N==0 && event.track_N>1) hrelbxbg_.at(fill)->Fill(event.bxWrtBunch);
    if (event.vtx_N==0 && event.track_N<2 && event.beamHalo_CSCLoose) hrelbxhalo_.at(fill)->Fill(event.bxWrtBunch);
    if (event.vtx_N==0 && event.track_N<2 && !event.beamHalo_CSCLoose && event.mu_N>0) hrelbxcos_.at(fill)->Fill(event.bxWrtBunch);
    if (event.vtx_N==0 && event.track_N<2 && !event.beamHalo_CSCLoose && event.mu_N==0 && !event.noiseFilterResult) hrelbxnoise_.at(fill)->Fill(event.bxWrtBunch);
    
    if (event.vtx_N==0 && event.track_N<2 && !event.beamHalo_CSCLoose && event.mu_N==0 && event.noiseFilterResult) hrelbxnoid_.at(fill)->Fill(event.bxWrtBunch);
  }

}


void FillHistograms::save() {

  // loop over fills
  std::vector<unsigned long>::const_iterator itr;
  for (itr=fills_.begin(); itr!=fills_.end(); ++itr) {

    // cd to directory
    std::stringstream fillstr;
    fillstr << (*itr);
    base_->cd(fillstr.str().c_str());

    // save histograms
    hbx_.at(*itr)->Write("",TObject::kOverwrite);
    hrelbx_.at(*itr)->Write("",TObject::kOverwrite);
    hrelbxvtx_.at(*itr)->Write("",TObject::kOverwrite);
    hrelbxhalo_.at(*itr)->Write("",TObject::kOverwrite);
    hrelbxbg_.at(*itr)->Write("",TObject::kOverwrite);
    hrelbxcos_.at(*itr)->Write("",TObject::kOverwrite);
    hrelbxnoise_.at(*itr)->Write("",TObject::kOverwrite);
    hrelbxnoid_.at(*itr)->Write("",TObject::kOverwrite);
    hbxB_.at(*itr)->Write("",TObject::kOverwrite);
    //    hnm1_.at(*itr)->Write("",TObject::kOverwrite);

    hcolls_.at(*itr)->Write("",TObject::kOverwrite);
    hbunches_.at(*itr)->Write("",TObject::kOverwrite);
    hnormrelbx_.at(*itr)->Write("",TObject::kOverwrite);

  }

}


void FillHistograms::summarise() {

  unsigned nFills = fills_.size();

  // book histograms
  TH1D* hnevt       = new TH1D("hfillnevt", "HLT counts", nFills, 0., 0.);
  TH1D* hlivetime   = new TH1D("hfilltime", "Live time", nFills, 0., 0.);
  TH1D* hnfin       = new TH1D("hfillnfin", "Final counts", nFills, 0., 0.);

  // N-1 histos
  std::vector<TH1D*> hnm1counts;
  std::vector<TH1D*> hnm1rates;
  std::string nbasec("hfillnm1count_");
  std::string nbaser("hfillnm1rate_");
  std::string lbase("N-1 rate : ");
  std::stringstream str;
  for (unsigned i=0; i<cuts_->nCuts(); ++i) {
    str << i;
    std::string namec=nbasec+str.str();
    std::string namer=nbaser+str.str();
    std::string label=lbase+str.str();
    hnm1counts.push_back(new TH1D(namec.c_str(), label.c_str(), nFills, 0., 0.));
    hnm1rates.push_back(new TH1D(namer.c_str(), label.c_str(), nFills, 0., 0.));
    str.str("");
  }

  // N-1 test histos
  std::vector<TH1D*> hnm1test;
  std::string nametest("hfillnm1test_");
  std::string labeltest("N-1 rate : ");
  hnm1test.push_back(new TH1D("hfilltest_bx", "BX N-1", nFills, 0., 0.));
  hnm1test.push_back(new TH1D("hfilltest_vtx", "Vtx N-1", nFills, 0., 0.));
  hnm1test.push_back(new TH1D("hfilltest_halo", "Halo N-1", nFills, 0., 0.));
  hnm1test.push_back(new TH1D("hfilltest_cos", "Cosmic N-1", nFills, 0., 0.));
  hnm1test.push_back(new TH1D("hfilltest_noise", "Wide Noise N-1", nFills, 0., 0.));
  hnm1test.push_back(new TH1D("hfilltest_n90", "n90 N-1", nFills, 0., 0.));
  hnm1test.push_back(new TH1D("hfilltest_timing", "Timing N-1", nFills, 0., 0.));

  // fill them
  std::vector<unsigned long>::const_iterator itr;
  unsigned bin=1;

  sort(fills_.begin(), fills_.end());

  for (itr=fills_.begin();
       itr!=fills_.end();
       ++itr, ++bin) {

    unsigned long fill = *itr;

    std::stringstream fillss;
    fillss << (*itr);
    std::string fillstr=fillss.str();

    // # events passing HLT
    hnevt->Fill(fillstr.c_str(), nEvts_.at(fill));
    hnevt->SetBinError(bin, sqrt(nEvts_.at(fill)));

    // live time
    double livetime = nLB_.at(fill) * TIME_PER_LS * lhcFills_->getLiveFraction(fill);
    hlivetime->Fill(fillstr.c_str(), livetime);
    
    for (unsigned cut=0; cut<cuts_->nCuts(); ++cut) {
      unsigned long count = nm1_.at(fill).at(cut);

      hnm1counts.at(cut)->Fill(fillstr.c_str(), count);
      if (count > 0) hnm1counts.at(cut)->SetBinError(bin, sqrt(count));
      else hnm1counts.at(cut)->SetBinError(bin, 1.);

      hnm1rates.at(cut)->Fill(fillstr.c_str(), count/livetime);
      if (count > 0) hnm1rates.at(cut)->SetBinError(bin, sqrt(count)/livetime);
      else hnm1rates.at(cut)->SetBinError(bin, 1/livetime);
    }

    // final counts
    unsigned long nfin = nFin_.at(fill);
    hnfin->Fill(fillstr.c_str(), nfin);
    if (nfin>0) hnfin->SetBinError(bin, sqrt(nfin));
    else hnfin->SetBinError(bin, 1.);

    unsigned long count = nm1Test0_.at(fill);
    hnm1test.at(0)->Fill(fillstr.c_str(), count);
    if (count > 0) hnm1test.at(0)->SetBinError(bin, sqrt(count));
    else hnm1test.at(0)->SetBinError(bin, 1.);

    count = nm1Test1_.at(fill);
    hnm1test.at(1)->Fill(fillstr.c_str(), count);
    if (count > 0) hnm1test.at(1)->SetBinError(bin, sqrt(count));
    else hnm1test.at(1)->SetBinError(bin, 1.);

    count = nm1Test2_.at(fill);
    hnm1test.at(2)->Fill(fillstr.c_str(), count);
    if (count > 0) hnm1test.at(2)->SetBinError(bin, sqrt(count));
    else hnm1test.at(2)->SetBinError(bin, 1.);

    count = nm1Test3_.at(fill);
    hnm1test.at(3)->Fill(fillstr.c_str(), count);
    if (count > 0) hnm1test.at(3)->SetBinError(bin, sqrt(count));
    else hnm1test.at(3)->SetBinError(bin, 1.);

    count = nm1Test4_.at(fill);
    hnm1test.at(4)->Fill(fillstr.c_str(), count);
    if (count > 0) hnm1test.at(4)->SetBinError(bin, sqrt(count));
    else hnm1test.at(4)->SetBinError(bin, 1.);

    count = nm1Test5_.at(fill);
    hnm1test.at(5)->Fill(fillstr.c_str(), count);
    if (count > 0) hnm1test.at(5)->SetBinError(bin, sqrt(count));
    else hnm1test.at(5)->SetBinError(bin, 1.);

    count = nm1Test6_.at(fill);
    hnm1test.at(6)->Fill(fillstr.c_str(), count);
    if (count > 0) hnm1test.at(6)->SetBinError(bin, sqrt(count));
    else hnm1test.at(6)->SetBinError(bin, 1.);

  }

  


  // save them
  base_->cd();

  hnevt->Write("",TObject::kOverwrite);
  hlivetime->Write("",TObject::kOverwrite);
  hnfin->Write("",TObject::kOverwrite);

  for (unsigned i=0; i<cuts_->nCuts(); ++i) {
      hnm1counts.at(i)->Write("",TObject::kOverwrite);
      hnm1rates.at(i)->Write("",TObject::kOverwrite);
    }

  for (unsigned i=0; i<7; ++i) {
    hnm1test.at(i)->Write("",TObject::kOverwrite);
  }




}


// void FillHistograms::doFillingSchemes() {

//   std::vector<TH1D*> fillSchemes;
//   std::vector<std::string> fillSchemeNames;

//   for (unsigned i=0; i<lhcFills_.size(); ++i) {

//     if

//   }

// }
