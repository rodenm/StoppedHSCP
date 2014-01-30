#ifndef NoiseSystematics_h
#define NoiseSystematics_h

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sys/stat.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <boost/program_options.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/filesystem.hpp>

#include "TFile.h"
#include "TChain.h"
#include "TH1D.h"
#include "TRandom2.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TLine.h"

#include <boost/program_options.hpp>


using namespace std;
namespace po = boost::program_options;

class NoiseSystematics {

public:
  NoiseSystematics(int argc, char* argv[]) {
    ofilename_ = std::string("NoiseSystematics.root");  /// SET YOUR OUTPUT FILENAME HERE

  // get options
  po::options_description desc("Allowed options");
  
  desc.add_options()
    ("help,h", "Display this message")
    ("outdir,o", po::value<std::string>(), "Output directory")
    ("num,n", po::value<unsigned long long>()->default_value(0), "Number of events to process");
  
  po::variables_map vm;
  po::store(po::command_line_parser(argc, argv).options(desc).allow_unregistered().run(), vm);  
  po::notify(vm);
  
  // help
  if (vm.count("help")) {
    std::cout << desc << std::endl;
    std::exit(1);
  }
  
  // set output directory & create it if it doesn't exist already
  if (vm.count("outdir")) {
    outdir_ = vm["outdir"].as<std::string>();

    boost::filesystem::path opath(outdir_);
    if (!exists(opath)) {
      std::cout << "Creating output directory : " << outdir_ << std::endl;
      boost::filesystem::create_directory(opath);
    }
  }
  
  // print some info & catch some error conditions
  std::cout << "Caclulate Limits Demo" << std::endl;

  // output directory
  if (outdir_ == std::string("")) {
    std::cout <<"LimitsDemo Error : no output directory specified!"<<std::endl;
    std::exit(-1);
  }

  }
  
  ~NoiseSystematics() { };
  
  virtual void run();
  
private:

  // output file
  std::string outdir_;
  std::string ofilename_;
  TFile* ofile_;

  // YOUR CODE HERE
  TH1D* myHistogram_;

};

#endif


// this is the event loop
void NoiseSystematics::run() {
  /**
  // DO ANY SETUP HERE
  myHistogram_ = new TH1D("test", "", 10, 0., 10.);

  // YOUR CODE HERE
  myHistogram_->Fill(1);

    
  std::cout << "Hello world!" << std::endl;

  // SAVE HISTOGRAMS HERE
  myHistogram_->Write("",TObject::kOverwrite);
  */
}



// this is the main program, no need to do anything here
int main(int argc, char* argv[]) {

  // sum of squares error info for histograms
  TH1D::SetDefaultSumw2();

  // create analysis
  // NoiseSystematics analyser(argc, argv);
  // analyser.run();

  TFile* ofile = new TFile("NoiseSystematics.root", "RECREATE");
  std::cout << "Output file        : " << ofile->GetName() << std::endl;

  if (ofile->IsZombie()) {
    std::exit(2);
  }

  TH1F hcosmic("hcosmic","",10,0,10);
  TH1F hobs("hobs",";# expected events;",10,0,10);
  TH1F hnoise("hnoise","",10,0,10);

  TRandom2 rndm;

  for (int i = 0; i < 10000; i++) {
    // DT by RPC background: 0.96061 +/- 0.559146
    double ncos = rndm.Poisson(rndm.Gaus (0.96, 0.56));
    double nobs = rndm.PoissonD(2.); 
    hcosmic.Fill(ncos);
    hobs.Fill(nobs);
    hnoise.Fill(nobs-ncos);
    //std::cout << ncos << "\t" << nobs << "\t" << nobs-ncos << std::endl;
  }

  double nq = 1;
  Double_t xq[1] = {0.68};  // position where to compute the quantiles in [0,1]
  Double_t yq[1] = {0.};  // array to contain the quantiles
  hnoise.GetQuantiles(nq,yq,xq);

  std::cout << xq[0] << "\t" << yq[0] << std::endl;

  ofile->cd();
  ofile->Write("",TObject::kOverwrite);
  
  TCanvas c("c");
  hnoise.SetStats(0);
  hobs.SetStats(0);
  hcosmic.SetStats(0);

  hcosmic.SetLineColor(kRed);
  //hcosmic.Scale(1.4);

  hobs.SetLineColor(kBlue);

  hnoise.SetLineColor(kBlack);

  hcosmic.SetMaximum(hcosmic.GetMaximum()*1.1);
  hcosmic.Draw("hist");
  hobs.Draw("hist same");
  hnoise.Draw("hist same");
  c.Update();

  TLine line(yq[0],0,yq[0],hcosmic.GetMaximum());
  line.SetLineColor(kBlack);
  line.SetLineStyle(5);
  line.SetLineWidth(2);
  line.Draw();

  TLegend leg(0.6, 0.70, 0.88, 0.85);
  leg.SetFillColor(kWhite);
  leg.AddEntry("hcosmic", "N_{cosmic}", "l");
  leg.AddEntry("hobs", "N_{obs} [#lambda = 2]","l");
  leg.AddEntry("hnoise", "n_{noise} = N_{obs} - N_{cosmic}","l");
  leg.SetBorderSize(0);
  leg.Draw();

  c.SaveAs("NoiseSystematics.pdf");
  return 0;

}
