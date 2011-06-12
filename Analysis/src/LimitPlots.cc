
#include "StoppedHSCP/Analysis/interface/LimitPlots.h"

#include "TGraph.h"
#include "TGraphAsymmErrors.h"
#include "TCanvas.h"
#include "TFile.h"
#include "TH1.h"
#include "TH1F.h"
#include "TLegend.h"
#include "TLatex.h"
#include "TPaveText.h"

#include <cstdlib>
#include <fstream>
#include <iostream> 


LimitPlots::LimitPlots(double tpLumi, std::string toyFile, std::string tpFile) :
  tpLumi_(tpLumi)
{

  readToyFile(toyFile);
  readTimeProfileFile(tpFile);

  std::string cmssw( getenv("CMSSW_BASE"));
  readGluinoData(cmssw+std::string("/src/StoppedHSCP/Analysis/data/mcGluino.txt"));
  readStopData(cmssw+std::string("/src/StoppedHSCP/Analysis/data/mcStop.txt"));
  //  readStauData(cmssw+std::string("/src/StoppedHSCP/Analysis/data/mcStau.txt");

}

LimitPlots::~LimitPlots() {

}

void LimitPlots::readToyFile(std::string filename) {

  std::cout << "Reading Toy MC results from " << filename << std::endl;

  unsigned count=0;

  ifstream file;
  file.open(filename.c_str());
  
  double t(0.), el(0.), es(0.), b(0.), eb(0.), cl(0.);
  double exmean(0.), lo1sig(0.), hi1sig(0.), lo2sig(0.), hi2sig(0.);
  unsigned n(0);
  std::string z;
  
  while (file >> t >> el >> es >> b >> eb >> n >> cl >> exmean >> lo1sig >> hi1sig >> lo2sig >> hi2sig) {
    toyLifetime.push_back(t);
    toyEffLumi.push_back(el);
    toyExpBG.push_back(b);
    toyExpBGErr.push_back(eb);
    toyObs.push_back(n);
    toyObsLimit.push_back(cl);
    toyExpLimit.push_back(exmean);
    toyExpLimitLo1Sig.push_back(lo1sig);
    toyExpLimitHi1Sig.push_back(hi1sig);
    toyExpLimitLo2Sig.push_back(lo2sig);
    toyExpLimitHi2Sig.push_back(hi2sig);
    ++count;
  }
  
  file.close();

  nToyLifetime = count;
  std::cout << "Read " << count << " lifetime points for counting experiment" << std::endl;

  // print out to check
  for (unsigned c=0; c<count; ++c) {
    std::cout << toyLifetime[c] << " " << toyEffLumi[c] << " " << toyObsLimit[c] << " " << toyExpLimit[c] << " " << toyExpLimitLo1Sig[c] << " " << toyExpLimitHi1Sig[c] << " " << toyExpLimitLo2Sig[c] << " " << toyExpLimitHi2Sig[c] << std::endl;
  }

}


void LimitPlots::readTimeProfileFile(std::string filename) {

  std::cout << "Reading Time Profile results from " << filename << std::endl;

  unsigned count=0 ;

  ifstream file;
  file.open(filename.c_str());
  
  double ltp(0.), cltp(0.);
  
  while (file >> ltp >> cltp) {
    tpLifetime.push_back(ltp);
    tpObsLimit.push_back(cltp);
    ++count;
  }

  nTPLifetime = count;
  std::cout << "Read " << count << " lifetime points for time profile fit" << std::endl;

}


void LimitPlots::readGluinoData(std::string filename) {

  std::cout << "Reading gluino data from " << filename << std::endl;

  unsigned count=0 ;

  ifstream file;
  file.open(filename.c_str());

  double m(0.), mchi(0.), escm(0.), esnb(0.), esem(0.), er(0.), mt(0.), xst(0.);

  std::string line;
  getline(file, line);
  getline(file, line);
  
  while (file >> m >> mchi >> escm >> esnb >> esem >> er >> mt >> xst) {
    
    gluinoMass.push_back(m);
    gluinoChi0Mass.push_back(mchi);
    gluinoEffStopCM.push_back(escm);
    gluinoEffStopNB.push_back(esnb);
    gluinoEffStopEM.push_back(esem);
    gluinoEffReco.push_back(er);
    
    // gluino theory info
    if (mt > 0.) {
      gluinoTheoryMass.push_back(mt);
      gluinoTheoryXS.push_back(xst);
    }
    
    count++;
    
  }

  std::cout << "Read " << count << " gluino mass points" << std::endl;

}


void LimitPlots::readStopData(std::string filename) {

  std::cout << "Reading stop data from " << filename << std::endl;

  unsigned count=0 ;

  ifstream file;
  file.open(filename.c_str());

  std::string line;
  getline(file, line);
  getline(file, line);
  
  double m(0.), mchi(0.), escm(0.), esnb(0.), esem(0.), er(0.), mt(0.), xst(0.);
  
  while (file >> m >> mchi >> escm >> esnb >> esem >> er >> mt >> xst) {
    
    stopMass.push_back(m);
    stopChi0Mass.push_back(mchi);
    stopEffStopCM.push_back(escm);
    stopEffStopNB.push_back(esnb);
    stopEffStopEM.push_back(esem);
    stopEffReco.push_back(er);
    
    // stop theory info
    if (mt > 0.) {
      stopTheoryMass.push_back(mt);
      stopTheoryXS.push_back(xst);
    }
    
    count++;
    
  }

  std::cout << "Read " << count << " stop mass points" << std::endl;

}


void LimitPlots::readStauData(std::string filename) {

  std::cout << "Reading stau data from " << filename << std::endl;

  unsigned count=0 ;

  ifstream file;
  file.open(filename.c_str());

  std::string line;
  getline(file, line);
  getline(file, line);
  
  double m(0.), mchi(0.), escm(0.), esnb(0.), esem(0.), er(0.), mt(0.), xst(0.);
  
  while (file >> m >> mchi >> escm >> esnb >> esem >> er >> mt >> xst) {
    
    //       stopMass.push_back(m);
    //       stopChi0Mass.push_back(mchi);
    //       stopEffStopCloud.push_back(escm);
    //       stopEffStopNB.push_back(esnb);
    //       stopEffStopEM.push_back(esem);
    //       stopEffReco.push_back(er);
    
    //       // stop theory info
    //       if (mt > 0.) {
    // 	stopTheoryMass.push_back(mt);
    // 	stopTheoryXS.push_back(xst);
    //       }
    
    count++;

  }

  std::cout << "Read " << count << " stau mass points" << std::endl;

}


void LimitPlots::calculateCrossSections(unsigned massIndex) {

  std::cout << "Lifetime,XSlimit,ExpLimit,-1sigma,+1sigma,-2sigma,+2sigma" << std::endl;
  for (int l=0; l<nToyLifetime; ++l) {

    // observed limits
    xsProdLimitToyGluino.push_back( toyObsLimit[l] / (toyEffLumi[l] * gluinoEffStopCM[massIndex] * gluinoEffReco[massIndex]) );
    xsProdLimitToyGluinoNB.push_back( toyObsLimit[l] / (toyEffLumi[l] * gluinoEffStopNB[massIndex] * gluinoEffReco[massIndex]) );
    xsProdLimitToyGluinoEM.push_back( toyObsLimit[l] / (toyEffLumi[l] * gluinoEffStopEM[massIndex] * gluinoEffReco[massIndex]) );
    xsProdLimitToyStop.push_back( toyObsLimit[l] / (toyEffLumi[l] * stopEffStopCM[massIndex] * stopEffReco[massIndex]) );

    // expected limit and bands
    xsProdExpLimitToyGluino.push_back( toyExpLimit[l] / (toyEffLumi[l] * gluinoEffStopCM[massIndex] * gluinoEffReco[massIndex]) );
    xsProdExpLimitLo1SigToyGluino.push_back( (toyExpLimit[l]-toyExpLimitLo1Sig[l]) / (toyEffLumi[l] * gluinoEffStopCM[massIndex] * gluinoEffReco[massIndex]) );
    xsProdExpLimitHi1SigToyGluino.push_back( (toyExpLimitHi1Sig[l]-toyExpLimit[l]) / (toyEffLumi[l] * gluinoEffStopCM[massIndex] * gluinoEffReco[massIndex]) );
    xsProdExpLimitLo2SigToyGluino.push_back( (toyExpLimit[l]-toyExpLimitLo2Sig[l]) / (toyEffLumi[l] * gluinoEffStopCM[massIndex] * gluinoEffReco[massIndex]) );
    xsProdExpLimitHi2SigToyGluino.push_back( (toyExpLimitHi2Sig[l]-toyExpLimit[l]) / (toyEffLumi[l] * gluinoEffStopCM[massIndex] * gluinoEffReco[massIndex]) );

    // print out
    std::cout << toyLifetime[l] << "," << xsProdLimitToyGluino[l] << "," << xsProdExpLimitToyGluino[l] << "," << xsProdExpLimitLo1SigToyGluino[l] << "," << xsProdExpLimitHi1SigToyGluino[l] << "," << xsProdExpLimitLo2SigToyGluino[l] << "," << xsProdExpLimitHi2SigToyGluino[l] << std::endl;
  }
  std::cout << std::endl;

  // time profile XS
  std::cout << "Lifetime, time profile limit" << std::endl;
  for (int i=0; i<nTPLifetime; ++i) {
    xsProdLimitTPGluino.push_back( tpObsLimit[i] / (tpLumi_ * gluinoEffStopCM[massIndex] * gluinoEffReco[massIndex]) );
    std::cout << tpLifetime[i] << "," << xsProdLimitTPGluino[i] << std::endl;
  }

}


void LimitPlots::makeLifetimePlot() {

  // graphs - observed
  TGraph* g_obs    = new TGraph(nToyLifetime, &toyLifetime[0], &xsProdLimitToyGluino[0]);
  TGraph* g_obs_em = new TGraph(nToyLifetime, &toyLifetime[0], &xsProdLimitToyGluinoEM[0]);
  TGraph* g_obs_nb = new TGraph(nToyLifetime, &toyLifetime[0], &xsProdLimitToyGluinoNB[0]);
  TGraph* g_obs_stop = new TGraph(nToyLifetime, &toyLifetime[0], &xsProdLimitToyStop[0]);
  TGraph* g_obs_tp = new TGraph(nTPLifetime, &tpLifetime[0], &xsProdLimitTPGluino[0]);

  // graphs - expected
  TGraph* g_exp      = new TGraph(nToyLifetime, &toyLifetime[0],  &xsProdExpLimitToyGluino[0]);
  TGraph* g_exp_1sig = new TGraphAsymmErrors(nToyLifetime, &toyLifetime[0], &xsProdExpLimitToyGluino[0], 0, 0, &xsProdExpLimitLo1SigToyGluino[0], &xsProdExpLimitHi1SigToyGluino[0]);
  TGraph* g_exp_2sig = new TGraphAsymmErrors(nToyLifetime, &toyLifetime[0], &xsProdExpLimitToyGluino[0], 0, 0, &xsProdExpLimitLo2SigToyGluino[0], &xsProdExpLimitHi2SigToyGluino[0]);

  TFile outfile("plots2.root", "RECREATE");


//   // expected limit
//   TGraph* g_exp = 0;
//   if (g_exp_1sig) g_exp = new TGraph(g_exp_1sig->GetN(),g_exp_1sig->GetX(),g_exp_1sig->GetY());

  TCanvas *canvas;
  canvas = new TCanvas("lifetimeLimit");

  //canvas->SetGrid();
  canvas->SetLogx();
  canvas->SetLogy();

  TH1 * h;
  TPaveText *blurb;

  h = canvas->DrawFrame(7.5e-8, .1, 1e6, 5e3);
  //  h->SetTitle("Beamgap Expt;#tau_{#tilde{g}} [s]; #sigma(pp #rightarrow #tilde{g}#tilde{g}) [cm^{2}]");
  h->SetTitle("Beamgap Expt;#tau_{#tilde{g}} [s]; #sigma(pp #rightarrow #tilde{g}#tilde{g}) #times BR(#tilde{g} #rightarrow g#tilde{#chi}^{0}) [pb]");

  blurb = new TPaveText(9e-8, 8e1, 2e-3, 4e3);
  blurb->AddText("CMS Preliminary 2011");
  blurb->AddText("#int L dt = 132 pb^{-1}");
  blurb->AddText("L^{max}_{inst} = 5 x 10^{32} cm^{-2}s^{-1}");
  blurb->AddText("#sqrt{s} = 7 TeV");
  blurb->AddText("m_{#tilde{g}} - m_{#tilde{#chi}^{0}} = 100 GeV/c^{2}");
  //blurb->AddText("m_{#tilde{g}} = 300 GeV/c^{2}");
  //blurb->AddText("m_{#tilde{#chi}^{0}} = 200 GeV/c^{2}");
  blurb->SetTextFont(42);
  blurb->SetBorderSize(0);
  blurb->SetFillColor(0);
  blurb->SetShadowColor(0);
  blurb->SetTextAlign(12);
  blurb->SetTextSize(0.033);
  blurb->Draw();

  TLegend *leg = new TLegend(2e-3, 8e1 /*4e-30*/, 8e4, 4e3,"95% C.L. Limits:","");
  leg->SetTextSize(0.033);
  leg->SetBorderSize(0);
  leg->SetTextFont(42);
  leg->SetFillColor(0);
  leg->AddEntry(g_exp, "Expected: Counting Exp.", "l");
  leg->AddEntry(g_exp_1sig, "Expected #pm1#sigma: Counting Exp.", "f");
  leg->AddEntry(g_exp_2sig, "Expected #pm2#sigma: Counting Exp.", "f");
  leg->AddEntry(g_obs,     "Obs.: Counting Exp.", "l");
  leg->AddEntry(g_obs_stop,"Obs.: Counting Exp. (#tilde{t})", "l");
  leg->AddEntry(g_obs_nb,  "Obs.: Counting Exp. (Neutral R-Baryon)", "l");
  leg->AddEntry(g_obs_em,  "Obs.: Counting Exp. (EM only)", "l");
  leg->AddEntry(g_obs_tp,  "Obs.: Timing Profile", "l");
  leg->Draw();

  // 2 sigma band
  if (g_exp_2sig) {
    g_exp_2sig->SetLineColor(0);
    g_exp_2sig->SetLineStyle(0);
    g_exp_2sig->SetLineWidth(0);
    g_exp_2sig->SetFillColor(kYellow);
    g_exp_2sig->SetFillStyle(1001);
    g_exp_2sig->Draw("3");
  }

  // 1 sigma band
  if (g_exp_1sig) {
    //    g_exp_1sig->SetLineColor(8);
    g_exp_1sig->SetLineColor(0);
    g_exp_1sig->SetLineStyle(0);
    g_exp_1sig->SetLineWidth(0);
    //    g_exp_1sig->SetFillColor(8);    
    g_exp_1sig->SetFillColor(kGreen);    
    g_exp_1sig->SetFillStyle(1001);
    //    g_exp_1sig->SetFillStyle(3005);
    g_exp_1sig->Draw("3");
    // g_exp_1sig->Draw("lX");
  }

  //lifetime fit
  if (g_obs_tp) {
    g_obs_tp->SetLineColor(kRed);
    g_obs_tp->SetLineStyle(3);    
    g_obs_tp->SetLineWidth(3);
    g_obs_tp->Draw("l3");
  }  

  // epxected limit
  if (g_exp) {
    g_exp->SetLineColor(1);
    g_exp->SetLineStyle(2);
    g_exp->SetLineWidth(1);
    g_exp->Draw("l");
  }

  TLine *l;
  l = new TLine(7.5e-8, 8.98, 1e6, 8.98); //300 GeV
  //l = new TLine(7.5e-8, 57.2, 1e6, 57.2); //300 GeV
  //l = new TLine(7.5e-8, 606, 1e6, 606); //200 GeV
  //  l = new TLine(1e-8, 3.75e-34, 1e7, 3.75e-34);
  l->SetLineColor(kBlue);
  l->SetLineWidth(1);
  l->Draw();

  //uncertainty band
//   TBox *syst = new TBox(1e-8, 515, 1e7, 697);
//   syst->SetFillStyle(3001);
//   syst->SetFillColor(kBlue-4);
//   syst->Draw();

  TLatex *t1;
  //t1 = new TLatex(1.e2, 70., "NLO+NLL");
  t1 = new TLatex(0.1, 10., "NLO+NLL (m_{#tilde{g}} = 400 GeV/c^{2})");
  t1->SetTextColor(kBlue);
  t1->SetTextFont(42);
  t1->SetTextSize(0.035);
  t1->Draw();

  // observed limit
  if (g_obs) {
    g_obs->SetLineColor(1);
    g_obs->SetLineStyle(1);
    g_obs->SetLineWidth(2);
    g_obs->Draw("l");
  }
  
  // EM model
  if (g_obs_em) {
    g_obs_em->SetLineColor(kGray+2);
    g_obs_em->SetLineWidth(2);
    g_obs_em->SetLineStyle(5);
    g_obs_em->Draw("l");
  }

  // NB model
  if (g_obs_nb) {
    g_obs_nb->SetLineColor(kGray+1);
    g_obs_nb->SetLineWidth(2);
    g_obs_nb->SetLineStyle(5);
    g_obs_nb->Draw("l");
  }

  // stop
  if (g_obs_stop) {
    g_obs_stop->SetLineColor(kRed+1);
    g_obs_stop->SetLineWidth(2);
    g_obs_stop->SetLineStyle(5);
    g_obs_stop->Draw("l");
  }


  canvas->RedrawAxis();

  canvas->Print("lifetimeLimit.png");
  canvas->Print("lifetimeLimit.pdf");
  canvas->Print("lifetimeLimit.C");
  canvas->Write();

}


void LimitPlots::makeBasicPlot() {

}


void LimitPlots::makeMassPlot() {

}
