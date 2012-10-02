#ifndef Histograms_h
#define Histograms_h


#include "StoppedHSCP/Analysis/interface/Cuts.h"

#include "StoppedHSCP/Ntuples/interface/StoppedHSCPEvent.h"

#include "TFile.h"
#include "TH1D.h"
#include "TH2D.h"

#include <vector>

class TDirectory;

class Histograms {

 public:

  Histograms(TFile* file, Cuts* cuts);
  ~Histograms();

  void book();

  void fill(StoppedHSCPEvent& event);

  void save();

  void summarise();

  void cutAxisLabels(TH1D* h);

  //  TH1D rateDist(TH1D&, unsigned nbins);

 private:

  Cuts* cuts_;
  TDirectory* base_;

  std::vector<unsigned> nMinusJetN90_;


  //MLR
  TH1D* hjeteta_halo_;
  TH1D* hjeteta_N90_;
  TH1D* hjeteta_N_;

  TH1D* hbx_;
  TH1D* horb_;
  TH1D* htime_;
  TH1D* hrelbx_;
  TH1D* hl1bits_;
  TH1D* hl1et_;
  TH1D* hl1eta_;
  TH1D* hl1phi_;
  TH1D* hl1type_;
  TH1D* hbptx_;
  TH1D* hhltbits_;
  TH1D* hhlte_;
  TH1D* hhlteta_;
  TH1D* hhltphi_;
  TH1D* hjete_;
  TH1D* hjeteta_;
  TH1D* hjetphi_;
  TH2D* hjetetaphi_;
  TH1D* hjeteem_;
  TH1D* hjetehad_;
  TH1D* hjetemf_;
  TH1D* hjetn60_;
  TH1D* hjetn90_;
  TH1D* hjetn90hits_;
  TH1D* hjetfhpd_;
  TH1D* htowiphifrac_;
  TH1D* hnmu_;
  TH2D* hmuetaphi_;
  TH1D* hntowsameiphi_;
  TH2D* htowietaiphi_;
  TH1D* hhalo_;
  TH1D* hpksample_;
  TH1D* hr1_;
  TH1D* hr2_;
  TH1D* hrpk_;
  TH1D* hrout_;
  TH2D* hr1r2_;
  TH2D* hpkout_;
  TH1D* hr1_old_;
  TH1D* hr2_old_;
  TH1D* hrpk_old_;
  TH1D* hrout_old_;
  TH1D* hr1_jetmu_;
  TH1D* hr2_jetmu_;
  TH1D* hrpk_jetmu_;
  TH1D* hrout_jetmu_;
  TH2D* hr1r2_jetmu_;
  TH2D* hpkout_jetmu_;
  TH1D* hbxup_;
  
  TH1D* hncutind_;
  TH1D* hncutcum_;
  TH1D* hnminus1cut_;

  TH1D* hncutsystlo_;
  TH1D* hncutsysthi_;
  TH1D* hncutsystg_;
  TH1D* holdcutind_;
  TH1D* holdcutcum_;
  TH1D* hhcalcutind_;
  TH1D* hhcalcutcum_;
  
  // N-1 variable distributions
  TH1D* hnmu_nmo_;
  TH1D* hjete_nmo_;
  TH1D* hjetn60_nmo_;
  TH1D* hjetn90_nmo_;
  TH1D* hntowiphi_nmo_;
  TH1D* hiphifrac_nmo_;
  TH1D* hr1_nmo_;
  TH1D* hr2_nmo_;
  TH1D* hrpk_nmo_;
  TH1D* hrout_nmo_;
  TH1D* hjetemf_nmo_;

  // eta/phi/time distributions after N-1 cuts
  std::vector<TH1D*> hbx_nm1_;
  std::vector<TH1D*> hrelbx_nm1_;
  std::vector<TH1D*> hjete_nm1_;
  std::vector<TH1D*> hjeteta_nm1_;
  std::vector<TH1D*> hjetphi_nm1_;
  std::vector<TH2D*> hjetetaphi_nm1_;

  
  // histograms after each cut
/*   std::vector<TH1D*> hjete_cuts_; */
/*   std::vector<TH1D*> hjetn60_cuts_; */
/*   std::vector<TH1D*> hjetn90_cuts_; */
/*   std::vector<TH1D*> hnmu_cuts_; */
/*   std::vector<TH1D*> hr1_cuts_; */
/*   std::vector<TH1D*> hr2_cuts_; */
/*   std::vector<TH1D*> hrpk_cuts_; */
/*   std::vector<TH1D*> hrout_cuts_; */
/*   std::vector<TH2D*> hjetetaphi_cuts_; */
/*   std::vector<TH2D*> hmuetaphi_cuts_; */
/*   std::vector<TH1D*> hbx_cuts_; */
/*   std::vector<TH1D*> hjetemf_cuts_; */
/*   std::vector<TH1D*> hlifetime_cuts_; */

  TH2D* hCTNM1EtaPhi_;
  TH2D* hCTNM1IEtaIPhi_;
  TH1D* hCTNM1LeadingIPhi_;

  TH2D* hN90NM1EtaPhi_;
  TH2D* hN90NM1IEtaIPhi_;
  TH1D* hN90NM1LeadingIPhi_;

  TH2D* hNM2_;
  TH1D* hNM1Test_;
  TH1D* hNM1Test2_;

  // look at n60 and n90 distributions right before respective cuts are made
  TH1D* hjetn60_e70cut_;
  TH1D* hjetn90_e70cut_;
  TH1D* hiphifrac_e70cut_;

  TH1D* hjetn60_n60cut_;
  TH1D* hjetn90_n60cut_;
  TH1D* hiphifrac_n60cut_;

  TH1D* hjetn60_n90cut_;
  TH1D* hjetn90_n90cut_;
  TH1D* hiphifrac_n90cut_;

  TH1D* hjetn60_ntowiphicut_;
  TH1D* hjetn90_ntowiphicut_;
  TH1D* hiphifrac_ntowiphicut_;

  TH1D* hjetn60_iphifraccut_;
  TH1D* hjetn90_iphifraccut_;
  TH1D* hiphifrac_iphifraccut_;

};

#endif

