#include "StoppedHSCP/ToyMC/interface/Luminosity.h"

#include "TH1D.h"

#include <algorithm>

#include <fstream>
#include <iostream>


Luminosity::Luminosity() {

}

Luminosity::~Luminosity() {

}

//double Luminosity::operator[](unsigned int index) const {
//  return lumis_[index].lumi;
//}

unsigned int Luminosity::size() const {
  return lumis_.size();
}

void Luminosity::makePlots() const {
  TCanvas *c = new TCanvas("lumi_dist");
  
  c->cd();

  TH1D *lumi_dist_h = new TH1D("lumi_dist_h", "Luminosity distribution",
			       lumis_.size(), -0.5, lumis_.size() -0.5);
  TH1D *cms_dist_h = new TH1D("cms_dist_h", "CMS Sensitivity",
			       lumis_.size(), -0.5, lumis_.size() -0.5);

  unsigned int counter = 0;
  for (std::vector<struct LumiBlock>::const_iterator cit = lumis_.begin();
       cit != lumis_.end(); cit++) {
    lumi_dist_h->Fill(counter, cit->lumi);
    cms_dist_h->Fill(counter++, (cit->cmsSensitivity>0.01?
				 50e27 : 0));
  }

  lumi_dist_h->Draw();
  cms_dist_h->Draw("same");
  cms_dist_h->SetLineColor(4);
  cms_dist_h->SetFillColor(4);
  cms_dist_h->SetFillStyle(3005);
  c->Print("lumi_dist.eps");
  c->Write();

}

void Luminosity::buildFromFile(std::vector<unsigned long> runs) {
  
  std::string filename("StoppedHSCP/ToyMC/data/lumi_record.txt");

  std::ifstream infile(filename.c_str());

  lumis_.clear();

  LumiBlock l;

  double total_lumi = 0, sensitive_lumi = 0;
  unsigned int goodLS = 0;

  // Run LS pass pass pass Lumi  
  while (infile >> l.run >> l.ls >> l.lumi >> l.cmsSensitivity) {

    // check this is a run we are simulating
    std::vector<unsigned long>::iterator p = find(runs.begin(), runs.end(), l.run);
    if (p != runs.end()) {
      l.lumi *= 1e30;
      if (l.cmsSensitivity > 0.01) {
	goodLS++;
	sensitive_lumi += l.lumi; //pow(2,18)
      }
      total_lumi += l.lumi;
      
      l.lumi /= (25e-9*3564*262144);  //pow(2,18)
      lumis_.push_back(l);
    }
    
  }
 
  std::cerr << "N good LS " << goodLS 
	    << " - " << goodLS*3564*25e-9*262144 << " s"
	    << std::endl
	    << "Sensitive lumi " << sensitive_lumi << std::endl
	    << "Total lumi     " << total_lumi << std::endl;
  
  makePlots();
}

void Luminosity::buildFromModel(unsigned int cycles, 
				unsigned int units_on, 
				unsigned int units_off,
				double amt) {
  lumis_.clear();
  lumis_.reserve(cycles*(units_on+units_off));
  
  LumiBlock l;
  l.run = 1;
  l.ls = 1;
  l.cmsSensitivity = 1;
  unsigned int i,j;
  for (i = 0; i < cycles; i++) {
    for (j = 0; j < units_on; j++) {
      l.ls++;
      l.lumi = amt;
      lumis_.push_back(l);
    }
    for (j = 0; j < units_off; j++) {
      l.ls++;
      l.lumi = 0;
      lumis_.push_back(l);
    }
  }
}
