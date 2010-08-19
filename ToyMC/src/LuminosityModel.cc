#include "StoppedHSCP/ToyMC/interface/LuminosityModel.h"

#include "TH1D.h"

#include <algorithm>

#include <fstream>
#include <iostream>


LuminosityModel::LuminosityModel() {

}

double LuminosityModel::operator[](unsigned int index) const {
  return lumis[index].lumi;
}

unsigned int LuminosityModel::size() const {
  return lumis.size();
}

TCanvas *LuminosityModel::draw() const {
  TCanvas *c = new TCanvas("lumi_dist");
  
  c->cd();

  TH1D *lumi_dist_h = new TH1D("lumi_dist_h", "Luminosity distribution",
			       lumis.size(), -0.5, lumis.size() -0.5);
  TH1D *cms_dist_h = new TH1D("cms_dist_h", "CMS Sensitivity",
			       lumis.size(), -0.5, lumis.size() -0.5);

  unsigned int counter = 0;
  for (std::vector<struct lumi_info>::const_iterator cit = lumis.begin();
       cit != lumis.end(); cit++) {
    lumi_dist_h->Fill(counter, cit->lumi);
    cms_dist_h->Fill(counter++, (cit->cms_sensitivity>0.01?
				 50e27 : 0));
  }

  lumi_dist_h->Draw();
  cms_dist_h->Draw("same");
  cms_dist_h->SetLineColor(4);
  cms_dist_h->SetFillColor(4);
  cms_dist_h->SetFillStyle(3005);
  c->Print("lumi_dist.eps");
  c->Write();

  return c;
}

void LuminosityModel::build_from_file(std::vector<unsigned long> runs) {
  
  std::string filename("StoppedHSCP/ToyMC/data/lumi_record.txt");

  std::ifstream infile(filename.c_str());

  lumis.clear();

  struct lumi_info l;

  double total_lumi = 0, sensitive_lumi = 0;
  unsigned int goodLS = 0;

  // Run LS pass pass pass Lumi  
  while (infile >> l.run >> l.ls >> l.lumi >> l.cms_sensitivity) {

    // check this is a run we are simulating
    std::vector<unsigned long>::iterator p = find(runs.begin(), runs.end(), l.run);
    if (p != runs.end()) {
      l.lumi *= 1e30;
      if (/*l.lumi > 0.01e30 &&*/ l.cms_sensitivity > 0.01) {
	goodLS++;
	sensitive_lumi += l.lumi; //pow(2,18)
      }
      total_lumi += l.lumi;
      
      l.lumi /= (25e-9*3564*262144);  //pow(2,18)
      lumis.push_back(l);
    }
    
  }
 
  std::cerr << "N good LS " << goodLS 
	    << " - " << goodLS*3564*25e-9*262144 << " s"
	    << std::endl
	    << "Sensitive lumi " << sensitive_lumi << std::endl
	    << "Total lumi     " << total_lumi << std::endl;
  
  draw();
}

void LuminosityModel::build_from_cycle(unsigned int cycles, 
					unsigned int units_on, unsigned int units_off,
					double amt) {
  lumis.clear();
  lumis.reserve(cycles*(units_on+units_off));
  
  struct lumi_info l;
  l.run = 1;
  l.ls = 1;
  l.cms_sensitivity = 1;
  unsigned int i,j;
  for (i = 0; i < cycles; i++) {
    for (j = 0; j < units_on; j++) {
      l.ls++;
      l.lumi = amt;
      lumis.push_back(l);
    }
    for (j = 0; j < units_off; j++) {
      l.ls++;
      l.lumi = 0;
      lumis.push_back(l);
    }
  }
}
