#include <fstream>
#include "StoppedHSCP/ToyMC/interface/Luminosity.h"
#include "TH1D.h"

Luminosity_Model::Luminosity_Model() {

}

double Luminosity_Model::operator[](unsigned int index) const {
  return lumis[index].lumi;
}

unsigned int Luminosity_Model::size() const {
  return lumis.size();
}

TCanvas *Luminosity_Model::draw() const {
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

void Luminosity_Model::build_from_file(const char *filename) {
  std::ifstream infile(filename);

  // Run LS pass pass pass Lumi

  lumis.clear();

  struct lumi_info l;
  
  while (infile >> l.run >> l.ls >> l.lumi >> l.cms_sensitivity) {
    lumis.push_back(l);
  }

  draw();
}

void Luminosity_Model::build_from_cycle(unsigned int cycles, 
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
