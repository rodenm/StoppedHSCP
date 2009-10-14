
#include <string>
#include <sstream>
#include <iostream>

#include "TChain.h"
#include "TCanvas.h"
#include "TPDF.h"
#include "TH1.h"
#include "TFile.h"

//#include "interface/StoppedHSCPEvent.h"



void RateHistos(TChain* chain, unsigned run,unsigned maxlumi) { // TH1D* ratebyls, TH1D* ratedist) {

  // make title
  std::stringstream o;
  o << "ratebyls_" << run;
  string name1 = o.str();
  o.str("");
  o << "ratedist_" << run; 
  string name2 = o.str();
  o.str("");
  o << "jete_" << run; 
  string name3 = o.str();
  o.str("");

  TH1D* ratebyls = new TH1D(name1.c_str(), name1.c_str(), maxlumi, 0., maxlumi);
  TH1D* ratedist = new TH1D(name2.c_str(), name2.c_str(), 40, 0., 20.);
  TH1D* jete = new TH1D(name3.c_str(), name3.c_str(), 100, 0., 100.);
 
  // make run selection cut
  o << "event.run==" << run;
  string cut = o.str();
  o.str("");
  o << "event.lumisection>>" << name1;
  string draw = o.str();
  o.str("");

  chain->Draw(draw.c_str(), cut.c_str());
  ratebyls->Scale(1/(25.e-9 * 3564 * 1048576));

  // make rate distribution
  for (int i=0; i<ratebyls->GetXaxis()->GetXmax(); ++i) {
    if (ratebyls->GetBinContent(i) > 0.) {
      ratedist->Fill(ratebyls->GetBinContent(i));
    }
  }
  
  // plot jet e
  o << "jets.e[0]>>" << name3;
  string jetdraw = o.str();
  o.str("");

  chain->Draw(jetdraw.c_str(), cut.c_str());

  ratebyls->Write();
  ratedist->Write();
  jete->Write();

}


void RatePlot(TFile* file, TCanvas* canvas, unsigned run) { 

  // make title
  std::stringstream o;
  o << "ratebyls_" << run;
  string name1 = o.str();
  o.str("");
  o << "ratedist_" << run; 
  string name2 = o.str();
  o.str("");
  o << "jete_" << run; 
  string name3 = o.str();
  o.str("");

  o << "Run " << run;
  string srun = o.str();


  TH1D* ratebyls = (TH1D*)file->Get(name1.c_str());
  ratebyls->SetXTitle("N_{LS}");
  ratebyls->SetYTitle("Hz");
  ratebyls->SetTitle(srun.c_str());
  ratebyls->Draw("HIST");
  canvas->Update();

  TH1D* ratedist = (TH1D*)file->Get(name2.c_str());
  ratedist->SetXTitle("Hz");
  ratedist->SetYTitle("Number of LS");
  ratedist->SetTitle(srun.c_str());
  ratedist->Draw("HIST");
  canvas->Update();

  TH1D* jete = (TH1D*)file->Get(name3.c_str());
  jete->SetXTitle("GeV");
  jete->SetYTitle("N events");
  jete->SetTitle(srun.c_str());
  jete->Draw("HIST");
  canvas->Update();

}
