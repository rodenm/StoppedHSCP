#ifndef Backgrounds_h
#define Backgrounds_h

#include "StoppedHSCP/Analysis/interface/BasicAnalyser.h"
#include "StoppedHSCP/Analysis/interface/MultiHistogram1D.h"
#include "StoppedHSCP/Ntuples/interface/Constants.h"

#include "TMath.h"
#include "TH1D.h"
#include "TH2D.h"

#include <cmath>
#include <vector>
#include <utility>
#include <algorithm>
#include <iostream>
#include <sstream>

using namespace std;

class Backgrounds : public BasicAnalyser {

public:
  Backgrounds(int argc, char* argv[]) :
    BasicAnalyser(argc, argv) {
    ofilename_ = std::string("Backgrounds.root");  /// SET YOUR OUTPUT FILENAME HERE
    TH1::SetDefaultSumw2();
  }
  
  ~Backgrounds() { };

  void cutAxisLabels(TH1D* h);
  
  virtual void loop();
  
private:

  // YOUR CODE HERE

  std::vector<unsigned long> fillList_;
  MultiHistogram1D normBX_;
  MultiHistogram1D normBXUP_;

  // noise
  TH1D* noiseJetE_;
  TH1D* noiseJetEta_;
  TH1D* noiseJetPhi_;
  TH1D* noiseJetN60_;
  TH1D* noiseJetN90_;
  TH1D* noiseNtow_;
  TH1D* noiseIPhiFrac_;
  TH1D* noiseNMu_;
  TH1D* noiseNCSC_;
  TH1D* noiseBHFlag_;
  TH1D* noiseNTrack_;
  TH1D* noiseNVtx_;
  TH1D* noiseBX_;
  TH1D* noiseBXUP_;
  TH1D* noiseR1_;
  TH1D* noiseR2_;
  TH1D* noiseRP_;
  TH1D* noiseRO_;

  // cosmic
  TH1D* cosmicJetE_;
  TH1D* cosmicJetEta_;
  TH1D* cosmicJetPhi_;
  TH1D* cosmicJetN60_;
  TH1D* cosmicJetN90_;
  TH1D* cosmicNtow_;
  TH1D* cosmicIPhiFrac_;
  TH1D* cosmicNMu_;
  TH1D* cosmicNCSC_;
  TH1D* cosmicBHFlag_;
  TH1D* cosmicNTrack_;
  TH1D* cosmicNVtx_;
  TH1D* cosmicBX_;
  TH1D* cosmicBXUP_;
  TH1D* cosmicR1_;
  TH1D* cosmicR2_;
  TH1D* cosmicRP_;
  TH1D* cosmicRO_;

  // Beam halo
  TH1D* beamHaloJetE_;
  TH1D* beamHaloJetEta_;
  TH1D* beamHaloJetPhi_;
  TH1D* beamHaloJetN60_;
  TH1D* beamHaloJetN90_;
  TH1D* beamHaloNtow_;
  TH1D* beamHaloIPhiFrac_;
  TH1D* beamHaloNMu_;
  TH1D* beamHaloNCSC_;
  TH1D* beamHaloBHFlag_;
  TH1D* beamHaloNTrack_;
  TH1D* beamHaloNVtx_;
  TH1D* beamHaloBX_;
  TH1D* beamHaloBXUP_;
  TH1D* beamHaloR1_;
  TH1D* beamHaloR2_;
  TH1D* beamHaloRP_;
  TH1D* beamHaloRO_;

  // beam gas
  TH1D* beamGasJetE_;
  TH1D* beamGasJetEta_;
  TH1D* beamGasJetPhi_;
  TH1D* beamGasJetN60_;
  TH1D* beamGasJetN90_;
  TH1D* beamGasNtow_;
  TH1D* beamGasIPhiFrac_;
  TH1D* beamGasNMu_;
  TH1D* beamGasNCSC_;
  TH1D* beamGasBHFlag_;
  TH1D* beamGasNTrack_;
  TH1D* beamGasNVtx_;
  TH1D* beamGasBX_;
  TH1D* beamGasBXUP_;
  TH1D* beamGasR1_;
  TH1D* beamGasR2_;
  TH1D* beamGasRP_;
  TH1D* beamGasRO_;

  // vertex
  TH1D* vertexJetE_;
  TH1D* vertexJetEta_;
  TH1D* vertexJetPhi_;
  TH1D* vertexJetN60_;
  TH1D* vertexJetN90_;
  TH1D* vertexNtow_;
  TH1D* vertexIPhiFrac_;
  TH1D* vertexNMu_;
  TH1D* vertexNCSC_;
  TH1D* vertexBHFlag_;
  TH1D* vertexNTrack_;
  TH1D* vertexNVtx_;
  TH1D* vertexBX_;
  TH1D* vertexBXUP_;
  TH1D* vertexR1_;
  TH1D* vertexR2_;
  TH1D* vertexRP_;
  TH1D* vertexRO_;

  // unidentified
  TH1D* unidJetE_;
  TH1D* unidJetEta_;
  TH1D* unidJetPhi_;
  TH1D* unidJetN60_;
  TH1D* unidJetN90_;
  TH1D* unidNtow_;
  TH1D* unidIPhiFrac_;
  TH1D* unidNMu_;
  TH1D* unidNCSC_;
  TH1D* unidBHFlag_;
  TH1D* unidNTrack_;
  TH1D* unidNVtx_;
  TH1D* unidBX_;
  TH1D* unidBXUP_;
  TH1D* unidR1_;
  TH1D* unidR2_;
  TH1D* unidRP_;
  TH1D* unidRO_;

  TH2D* overlap_;

  // Cut values - plots of values used in cuts for all events passing trigger
  TH1D* hnvertex_;
  TH1D* hncsc_;
  TH1D* hnmu_;
  TH1D* hndt_;
  TH1D* hnrpc_;
  TH1D* hnoise_;
  TH1D* hjete_;
  TH1D* hn60_;
  TH1D* hn90_;
  TH1D* hntowiphi_;
  TH1D* hiphifrac_;
  TH1D* hr1_;
  TH1D* hr2_;
  TH1D* hrpeak_;
  TH1D* hrouter_;
  TH1D* hncutcum_;
  TH1D* hnminus1_;
  TH1D* hncutind_;

  TH1D* hremainingDTR_;
  TH1D* hremainingRPCR_;

  TH1D* hDTphidirection_;

  TH1D* hDTdeltaphi_;
  TH1D* hDTdeltajetphi_;
  TH1D* hRPCdeltaphi_;
  TH1D* hRPCdeltajetphi_;
  TH1D* hDTinnerouterfrac_;
  TH1D* hRPCinnerouterfrac_;
  TH1D* hNRPCpairs_;
  TH1D* hDTouter_;
  TH1D* hRPCouter_;
  TH1D* hcosmiccum_;

  int ncosmic;
  int ncut1;
  int ncut2;
  int ncut3;
  int ncut4;
  int ncut5;
  int ncut6;
  int ncut7;
  int ncut8;
}; 

#endif

void Backgrounds::cutAxisLabels(TH1D* h) {

  for (unsigned i=0; i<cuts_.nCuts(); ++i) {
    h->GetXaxis()->SetBinLabel(i+1, cuts_.cutName(i).c_str());
  }

}

// this is the event loop
void Backgrounds::loop() {

  // DO ANY SETUP HERE
  normBX_.setup(ofile_, "hNormBX", "Relative BX norm", 2000, -999.5, 1000.5);
  normBXUP_.setup(ofile_, "hNormBXUP", "Relative BX norm (UP)", 2000, -999.5, 1000.5);

  noiseJetE_     = new TH1D("hNoiseJetE",    "Noise - jet E",    200, 0., 200.);
  noiseJetEta_   = new TH1D("hNoiseJetEta",  "Noise - jet #eta", 70, -3.5, 3.5);
  noiseJetPhi_   = new TH1D("hNoiseJetPhi",  "Noise - jet #phi", 72, -1 * TMath::Pi(), TMath::Pi());
  noiseJetN60_   = new TH1D("hNoiseJetN60",  "Noise - jet n60",  25, -0.5, 24.5);
  noiseJetN90_   = new TH1D("hNoiseJetN90",  "Noise - jet n90",  30, -0.5, 29.5);
  noiseNtow_     = new TH1D("hNoiseNtow",    "Noise - N_{tow}",  20, -0.5, 19.5);
  noiseIPhiFrac_ = new TH1D("hNoiseIPhiFrac","Noise - f_{iphi}", 50, 0., 2.);
  noiseNMu_      = new TH1D("hNoiseNMu",     "Noise - N_{#mu}",  10, -0.5, 9.5);
  noiseNCSC_     = new TH1D("hNoiseNCSC",    "Noise - N_{CSC}",  20, -0.5, 19.5);
  noiseBHFlag_   = new TH1D("hNoiseBHFlag",  "Noise - Beam Halo flag", 2, -0.5, 1.5);
  noiseNTrack_   = new TH1D("hNoiseNTrack",  "Noise - N_{track}",      20, -0.5, 19.5);
  noiseNVtx_     = new TH1D("hNoiseNVtx",    "Noise - N_{vertex}",     10, -0.5, 9.5);
  noiseBX_       = new TH1D("hNoiseBX",      "Noise - BX_{wrt bunch}",     2000, -999.5, 1000.5);
  noiseBXUP_     = new TH1D("hNoiseBXUP",    "Noise - BX_{wrt UP bunch}",  2000, -999.5, 1000.5);
  noiseR1_       = new TH1D("hNoiseR1",      "Noise - R_{1}", 50, 0., 1.);
  noiseR2_       = new TH1D("hNoiseR2",      "Noise - R_{2}", 50, 0., 1.);
  noiseRP_       = new TH1D("hNoiseRP",      "Noise - R_{peak}", 50, 0., 1.);
  noiseRO_       = new TH1D("hNoiseRO",      "Noise - R_{outer}", 50, 0., 1.);

  // cosmic
  cosmicJetE_     = new TH1D("hCosmicJetE",    "Cosmic - jet E",    200, 0., 200.);
  cosmicJetEta_   = new TH1D("hCosmicJetEta",  "Cosmic - jet #eta", 70, -3.5, 3.5);
  cosmicJetPhi_   = new TH1D("hCosmicJetPhi",  "Cosmic - jet #phi", 72, -1 * TMath::Pi(), TMath::Pi());
  cosmicJetN60_   = new TH1D("hCosmicJetN60",  "Cosmic - jet n60",  25, -0.5, 24.5);
  cosmicJetN90_   = new TH1D("hCosmicJetN90",  "Cosmic - jet n90",  30, -0.5, 29.5);
  cosmicNtow_     = new TH1D("hCosmicNtow",    "Cosmic - N_{tow}",  20, -0.5, 19.5);
  cosmicIPhiFrac_ = new TH1D("hCosmicIPhiFrac","Cosmic - f_{iphi}", 50, 0., 2.);
  cosmicNMu_      = new TH1D("hCosmicNMu",     "Cosmic - N_{#mu}",  10, -0.5, 9.5);
  cosmicNCSC_     = new TH1D("hCosmicNCSC",    "Cosmic - N_{CSC}",  20, -0.5, 19.5);
  cosmicBHFlag_   = new TH1D("hCosmicBHFlag",  "Cosmic - Beam Halo flag", 2, -0.5, 1.5);
  cosmicNTrack_   = new TH1D("hCosmicNTrack",  "Cosmic - N_{track}",      20, -0.5, 19.5);
  cosmicNVtx_     = new TH1D("hCosmicNVtx",    "Cosmic - N_{vertex}",     10, -0.5, 9.5);
  cosmicBX_       = new TH1D("hCosmicBX",      "Cosmic - BX_{wrt bunch}",     2000, -999.5, 1000.5);
  cosmicBXUP_     = new TH1D("hCosmicBXUP",    "Cosmic - BX_{wrt UP bunch}",  2000, -999.5, 1000.5);
  cosmicR1_       = new TH1D("hCosmicR1",      "Cosmic - R_{1}", 50, 0., 1.);
  cosmicR2_       = new TH1D("hCosmicR2",      "Cosmic - R_{2}", 50, 0., 1.);
  cosmicRP_       = new TH1D("hCosmicRP",      "Cosmic - R_{peak}", 50, 0., 1.);
  cosmicRO_       = new TH1D("hCosmicRO",      "Cosmic - R_{outer}", 50, 0., 1.);
  
  // beam halo
  beamHaloJetE_     = new TH1D("hBeamHaloJetE",    "BeamHalo - jet E",    200, 0., 200.);
  beamHaloJetEta_   = new TH1D("hBeamHaloJetEta",  "BeamHalo - jet #eta", 70, -3.5, 3.5);
  beamHaloJetPhi_   = new TH1D("hBeamHaloJetPhi",  "BeamHalo - jet #phi", 72, -1 * TMath::Pi(), TMath::Pi());
  beamHaloJetN60_   = new TH1D("hBeamHaloJetN60",  "BeamHalo - jet n60",  25, -0.5, 24.5);
  beamHaloJetN90_   = new TH1D("hBeamHaloJetN90",  "BeamHalo - jet n90",  30, -0.5, 29.5);
  beamHaloNtow_     = new TH1D("hBeamHaloNtow",    "BeamHalo - N_{tow}",  20, -0.5, 19.5);
  beamHaloIPhiFrac_ = new TH1D("hBeamHaloIPhiFrac","BeamHalo - f_{iphi}", 50, 0., 2.);
  beamHaloNMu_      = new TH1D("hBeamHaloNMu",     "BeamHalo - N_{#mu}",  10, -0.5, 9.5);
  beamHaloNCSC_     = new TH1D("hBeamHaloNCSC",    "BeamHalo - N_{CSC}",  20, -0.5, 19.5);
  beamHaloBHFlag_   = new TH1D("hBeamHaloBHFlag",  "BeamHalo - Beam Halo flag", 2, -0.5, 1.5);
  beamHaloNTrack_   = new TH1D("hBeamHaloNTrack",  "BeamHalo - N_{track}",      20, -0.5, 19.5);
  beamHaloNVtx_     = new TH1D("hBeamHaloNVtx",    "BeamHalo - N_{vertex}",     10, -0.5, 9.5);
  beamHaloBX_       = new TH1D("hBeamHaloBX",      "BeamHalo - BX_{wrt bunch}",     2000, -999.5, 1000.5);
  beamHaloBXUP_     = new TH1D("hBeamHaloBXUP",    "BeamHalo - BX_{wrt UP bunch}",  2000, -999.5, 1000.5);
  beamHaloR1_       = new TH1D("hBeamHaloR1",      "BeamHalo - R_{1}", 50, 0., 1.);
  beamHaloR2_       = new TH1D("hBeamHaloR2",      "BeamHalo - R_{2}", 50, 0., 1.);
  beamHaloRP_       = new TH1D("hBeamHaloRP",      "BeamHalo - R_{peak}", 50, 0., 1.);
  beamHaloRO_       = new TH1D("hBeamHaloRO",      "BeamHalo - R_{outer}", 50, 0., 1.);
  
  // beam gas
  beamGasJetE_     = new TH1D("hBeamGasJetE",    "BeamGas - jet E",    200, 0., 200.);
  beamGasJetEta_   = new TH1D("hBeamGasJetEta",  "BeamGas - jet #eta", 70, -3.5, 3.5);
  beamGasJetPhi_   = new TH1D("hBeamGasJetPhi",  "BeamGas - jet #phi", 72, -1 * TMath::Pi(), TMath::Pi());
  beamGasJetN60_   = new TH1D("hBeamGasJetN60",  "BeamGas - jet n60",  25, -0.5, 24.5);
  beamGasJetN90_   = new TH1D("hBeamGasJetN90",  "BeamGas - jet n90",  30, -0.5, 29.5);
  beamGasNtow_     = new TH1D("hBeamGasNtow",    "BeamGas - N_{tow}",  20, -0.5, 19.5);
  beamGasIPhiFrac_ = new TH1D("hBeamGasIPhiFrac","BeamGas - f_{iphi}", 50, 0., 2.);
  beamGasNMu_      = new TH1D("hBeamGasNMu",     "BeamGas - N_{#mu}",  10, -0.5, 9.5);
  beamGasNCSC_     = new TH1D("hBeamGasNCSC",    "BeamGas - N_{CSC}",  20, -0.5, 19.5);
  beamGasBHFlag_   = new TH1D("hBeamGasBHFlag",  "BeamGas - Beam Halo flag", 2, -0.5, 1.5);
  beamGasNTrack_   = new TH1D("hBeamGasNTrack",  "BeamGas - N_{track}",      20, -0.5, 19.5);
  beamGasNVtx_     = new TH1D("hBeamGasNVtx",    "BeamGas - N_{vertex}",     10, -0.5, 9.5);
  beamGasBX_       = new TH1D("hBeamGasBX",      "BeamGas - BX_{wrt bunch}",     2000, -999.5, 1000.5);
  beamGasBXUP_     = new TH1D("hBeamGasBXUP",    "BeamGas - BX_{wrt UP bunch}",  2000, -999.5, 1000.5);
  beamGasR1_       = new TH1D("hBeamGasR1",      "BeamGas - R_{1}", 50, 0., 1.);
  beamGasR2_       = new TH1D("hBeamGasR2",      "BeamGas - R_{2}", 50, 0., 1.);
  beamGasRP_       = new TH1D("hBeamGasRP",      "BeamGas - R_{peak}", 50, 0., 1.);
  beamGasRO_       = new TH1D("hBeamGasRO",      "BeamGas - R_{outer}", 50, 0., 1.);
  
  // vertex
  vertexJetE_     = new TH1D("hVertexJetE",    "Vertex - jet E",    200, 0., 200.);
  vertexJetEta_   = new TH1D("hVertexJetEta",  "Vertex - jet #eta", 70, -3.5, 3.5);
  vertexJetPhi_   = new TH1D("hVertexJetPhi",  "Vertex - jet #phi", 72, -1 * TMath::Pi(), TMath::Pi());
  vertexJetN60_   = new TH1D("hVertexJetN60",  "Vertex - jet n60",  25, -0.5, 24.5);
  vertexJetN90_   = new TH1D("hVertexJetN90",  "Vertex - jet n90",  30, -0.5, 29.5);
  vertexNtow_     = new TH1D("hVertexNtow",    "Vertex - N_{tow}",  20, -0.5, 19.5);
  vertexIPhiFrac_ = new TH1D("hVertexIPhiFrac","Vertex - f_{iphi}", 50, 0., 2.);
  vertexNMu_      = new TH1D("hVertexNMu",     "Vertex - N_{#mu}",  10, -0.5, 9.5);
  vertexNCSC_     = new TH1D("hVertexNCSC",    "Vertex - N_{CSC}",  20, -0.5, 19.5);
  vertexBHFlag_   = new TH1D("hVertexBHFlag",  "Vertex - Beam Halo flag", 2, -0.5, 1.5);
  vertexNTrack_   = new TH1D("hVertexNTrack",  "Vertex - N_{track}",      20, -0.5, 19.5);
  vertexNVtx_     = new TH1D("hVertexNVtx",    "Vertex - N_{vertex}",     10, -0.5, 9.5);
  vertexBX_       = new TH1D("hVertexBX",      "Vertex - BX_{wrt bunch}",     2000, -999.5, 1000.5);
  vertexBXUP_     = new TH1D("hVertexBXUP",    "Vertex - BX_{wrt UP bunch}",  2000, -999.5, 1000.5);
  vertexR1_       = new TH1D("hVertexR1",      "Vertex - R_{1}", 50, 0., 1.);
  vertexR2_       = new TH1D("hVertexR2",      "Vertex - R_{2}", 50, 0., 1.);
  vertexRP_       = new TH1D("hVertexRP",      "Vertex - R_{peak}", 50, 0., 1.);
  vertexRO_       = new TH1D("hVertexRO",      "Vertex - R_{outer}", 50, 0., 1.);
  
  // unidentified
  unidJetE_     = new TH1D("hUnidJetE",    "Unid - jet E",    200, 0., 200.);
  unidJetEta_   = new TH1D("hUnidJetEta",  "Unid - jet #eta", 70, -3.5, 3.5);
  unidJetPhi_   = new TH1D("hUnidJetPhi",  "Unid - jet #phi", 72, -1 * TMath::Pi(), TMath::Pi());
  unidJetN60_   = new TH1D("hUnidJetN60",  "Unid - jet n60",  25, -0.5, 24.5);
  unidJetN90_   = new TH1D("hUnidJetN90",  "Unid - jet n90",  30, -0.5, 29.5);
  unidNtow_     = new TH1D("hUnidNtow",    "Unid - N_{tow}",  20, -0.5, 19.5);
  unidIPhiFrac_ = new TH1D("hUnidIPhiFrac","Unid - f_{iphi}", 50, 0., 2.);
  unidNMu_      = new TH1D("hUnidNMu",     "Unid - N_{#mu}",  10, -0.5, 9.5);
  unidNCSC_     = new TH1D("hUnidNCSC",    "Unid - N_{CSC}",  20, -0.5, 19.5);
  unidBHFlag_   = new TH1D("hUnidBHFlag",  "Unid - Beam Halo flag", 2, -0.5, 1.5);
  unidNTrack_   = new TH1D("hUnidNTrack",  "Unid - N_{track}",      20, -0.5, 19.5);
  unidNVtx_     = new TH1D("hUnidNVtx",    "Unid - N_{vertex}",     10, -0.5, 9.5);
  unidBX_       = new TH1D("hUnidBX",      "Unid - BX_{wrt bunch}",     2000, -999.5, 1000.5);
  unidBXUP_     = new TH1D("hUnidBXUP",    "Unid - BX_{wrt UP bunch}",  2000, -999.5, 1000.5);
  unidR1_       = new TH1D("hUnidR1",      "Unid - R_{1}", 50, 0., 1.);
  unidR2_       = new TH1D("hUnidR2",      "Unid - R_{2}", 50, 0., 1.);
  unidRP_       = new TH1D("hUnidRP",      "Unid - R_{peak}", 50, 0., 1.);
  unidRO_       = new TH1D("hUnidRO",      "Unid - R_{outer}", 50, 0., 1.);

  overlap_     = new TH2D("hOverlap", "Overlap", 7, -0.5, 6.5, 7, -0.5, 6.5);
  overlap_->GetXaxis()->SetBinLabel(1,"All");
  overlap_->GetYaxis()->SetBinLabel(1,"All");
  overlap_->GetXaxis()->SetBinLabel(2,"Noise");
  overlap_->GetYaxis()->SetBinLabel(2,"Noise");
  overlap_->GetXaxis()->SetBinLabel(3,"Cosmic");
  overlap_->GetYaxis()->SetBinLabel(3,"Cosmic");
  overlap_->GetXaxis()->SetBinLabel(4,"Beam Halo");
  overlap_->GetYaxis()->SetBinLabel(4,"Beam Halo");
  overlap_->GetXaxis()->SetBinLabel(5,"Beam Gas");
  overlap_->GetYaxis()->SetBinLabel(5,"Beam Gas");
  overlap_->GetXaxis()->SetBinLabel(6,"Vertex");
  overlap_->GetYaxis()->SetBinLabel(6,"Vertex");
  overlap_->GetXaxis()->SetBinLabel(7,"Un ID");
  overlap_->GetYaxis()->SetBinLabel(7,"Un ID");

  hnvertex_ = new TH1D("nvertex", "", 10, 0, 10);
  hncsc_ = new TH1D("ncsc", "", 20, 0, 20);
  hnmu_ = new TH1D("nmu", "", 10, 0, 10);
  hndt_ = new TH1D("ndt", "", 20, 0, 20); 
  hnrpc_ = new TH1D("nrpc", "", 20, 0, 20); 

  hnoise_ = new TH1D("noise", "", 2, -0.5, 1.5);
  hnoise_->GetXaxis()->SetBinLabel(1,"true");
  hnoise_->GetXaxis()->SetBinLabel(2,"false");
  hnoise_->SetMinimum(0);

  hjete_ = new TH1D("jete", "", 70, 0, 700);
  hn60_ = new TH1D("n60", "", 15, 0, 15);
  hn90_ = new TH1D("n90", "", 15, 0, 15);
  hntowiphi_ = new TH1D("ntowiphi", "", 10, 0, 10);
  hiphifrac_ = new TH1D("iphifrac", "",20, 0, 1.0); 
  hr1_ = new TH1D("r1", "", 20, 0, 1.0);
  hr2_ = new TH1D("r2", "",20, 0, 1.0);
  hrpeak_ = new TH1D("rpeak", "",20, 0, 1.0);
  hrouter_ = new TH1D("router", "",20, 0, 1.0);

  hncutcum_ = new TH1D("ncutcum", "", 20, 0., 20.);
  cutAxisLabels(hncutcum_);
  hnminus1_ = new TH1D("nminus1", "", 20, 0., 20.);
  cutAxisLabels(hnminus1_);
  hncutind_ = new TH1D("ncutind", "", 20, 0., 20.);
  cutAxisLabels(hncutind_);

  hremainingDTR_ = new TH1D("remainingDTR", "r of DTSegements for events passing N-1(cosmic);r [cm]", 200, 0, 800);
  hremainingRPCR_ = new TH1D("remaininRPCR", "r of rpcHits for events passing N-1(cosmic); r [cm]", 200, 0, 800);

  hDTdeltaphi_ = new TH1D("DTdeltaphi", "", 32, 0., TMath::Pi());
  hDTdeltajetphi_ = new TH1D("DTdeltajetphi", "", 32, 0., TMath::Pi());
  hRPCdeltaphi_ = new TH1D("RPCdeltaphi", "", 32, 0., TMath::Pi());
  hRPCdeltajetphi_ = new TH1D("RPCdeltajetphi", "", 32, 0., TMath::Pi());

  hDTphidirection_ = new TH1D("DTphidirection", "", 63, -TMath::Pi(), TMath::Pi());

  hDTinnerouterfrac_ = new TH1D("DTinnerouterfrac", "", 30, 0., 10.);
  hRPCinnerouterfrac_ = new TH1D("RPCinnerouterfrac", "", 30, 0., 10.);
  hNRPCpairs_ = new TH1D("NRPCpairs", "", 20, 0., 20.);

  hDTouter_ = new TH1D("DTouter", "", 20, 0., 20.);
  hRPCouter_ = new TH1D("RPCouter", "", 20, 0., 20.);

  hcosmiccum_ = new TH1D("cosmiccum", "", 8, -0.5, 7.5);

  reset();
  nextEvent();

  ncosmic = 0;
  ncut1 = 0;
  ncut2 = 0;
  ncut3 = 0;
  ncut4 = 0;
  ncut5 = 0;
  ncut6 = 0;
  ncut7 = 0;
  ncut8 = 0;

  for (unsigned long i=0; i<maxEvents_; ++i, nextEvent()) {

    // occasional print out
    if (i%50000==0) {
      std::cout << "Processing " << i << "th event of " <<maxEvents_<< std::endl;
    }

    // YOUR CODE HERE
    livetime_.newEvent(event_->fill, event_->run, event_->lb);

    // fill normalisation histograms once per fill
    unsigned long fill=event_->fill;
    std::vector<unsigned long>::const_iterator itr = find(fillList_.begin(), fillList_.end(), fill);

    if (itr == fillList_.end()) {
      
      for (unsigned i=0; i<3564; ++i) {

	int bxWrtBunch = lhcFills_.getBxWrtBunch(fill, i);
	int bxWrtColl  = lhcFills_.getBxWrtCollision(fill, i);

	if ( abs(abs(bxWrtBunch) - abs(bxWrtColl)) < 2) normBX_.fill( fill, bxWrtBunch );
	else if (abs(bxWrtBunch) < (abs(bxWrtColl)-1)) normBXUP_.fill( fill, bxWrtBunch );
	else std::cerr << "Found a BX where bxWrtBunch=" << bxWrtBunch << " and bxWrtCollision=" << bxWrtColl << std::endl;

      }

      fillList_.push_back(fill);

    }

    if (event_->jet_N==0) continue;

    // event quantities
    bool trig       = cuts_.triggerCut();
    int bxWrtBunch  = event_->bxWrtBunch;
    int bxWrtColl   = event_->bxWrtCollision;
    double e        = event_->jetE[0];
    double eta      = event_->jetEta[0];
    double phi      = event_->jetPhi[0];
    unsigned n60    = event_->jetN60[0];
    unsigned n90    = event_->jetN90[0];
    unsigned ntow   = event_->nTowerSameiPhi;
    double fiphi    = event_->leadingIPhiFractionValue;
    bool bh         = event_->beamHalo_CSCLoose;
    unsigned nmu    = event_->mu_N;
    unsigned ncsc   = event_->cscSeg_N;
    unsigned ntrk   = event_->track_N;
    unsigned nvtx   = event_->nVtx;
    double r1       = event_->topHPD5R1;
    double r2       = event_->topHPD5R2;
    double rp       = event_->topHPD5RPeak;
    double ro       = event_->topHPD5ROuter;

    // event classes (very loose right now!)
    bool isNoise    = !event_->noiseFilterResult;
    bool isCosmic   = nmu > 0;
    bool isBeamHalo = ncsc > 0;
    bool isBeamGas  = ntrk > 1;
    bool isVtx      = nvtx > 0;
    bool isUnid     = (!isNoise && !isCosmic && !isBeamHalo && !isBeamGas && !isVtx);

    unsigned overlap = 0;

    // Create histograms showing distribution of cut values for all events passing the trigger.
    //if (trig) {
    // Nevermind, look at these quantities for cosmic-like events

    if (trig && e>70 && ncsc==0 && event_->noiseFilterResult){
      hnvertex_->Fill(nvtx);
      hncsc_->Fill(ncsc);
      hnmu_->Fill(nmu);
      hndt_->Fill(event_->DTSegment_N);
      hnrpc_->Fill(event_->rpcHit_N);
      int setNoise = isNoise? 0 : 1;
      hnoise_->Fill(setNoise);
      //hnoise_->GetXaxis()->SetBinLabel(1,"true");
      //hnoise_->GetXaxis()->SetBinLabel(2,"false");
      
      hjete_->Fill(e);
      hn60_->Fill(n60);
      hn90_->Fill(n90);
      hntowiphi_->Fill(ntow);
      hiphifrac_->Fill(fiphi);
      hr1_->Fill(r1);
      hr2_->Fill(r2);
      hrpeak_->Fill(rp);
      hrouter_->Fill(ro);
    }
    /**
    if (cuts_.cut()) {
      for (i=0; i<event_->DTSegment_N; i++) {
	hremainingDTR_->Fill(event_->DTSegR[i]);
      }
      for (i=0; i<event_->rpcHit_N; i++) {
	hremainingRPCR_->Fill(event_->rpcHitR[i]);
      }
    }
    */

    // Look at distributions for candidate cosmic events
    //
    // NOTE: MAKE SURE TO EDIT THE PRINTLINE AT LINE 1040 IF
    //       YOU CHANGE THE CONDITION HERE.
    //
    if(trig && e>70 && !isBeamHalo && event_->noiseFilterResult){
      hcosmiccum_->Fill(0);

      double innerDT = 0;
      double outerDT = 0.0000001; // protect against divide by 0

      double innerRPC = 0; 
      double outerRPC = 0.000001; // protect against divide by 0
      
      //std::cout << "Testing DTs...";

      double testPhi;
      double maxDeltaPhi = -1;
      double maxDeltaJetPhi = -1.;
      for (unsigned idt = 0; idt<event_->DTSegment_N; idt++) {
	
	if (idt == 0)
	  testPhi = event_->DTSegPhi[0];
	else {
	  double deltaPhi = acos(cos(event_->DTSegPhi[idt] - testPhi));
	  if (deltaPhi > maxDeltaPhi) maxDeltaPhi = deltaPhi;
	}
	double deltajetphi = acos(cos(event_->DTSegPhi[idt] - event_->jetPhi[0]));
	if (deltajetphi > maxDeltaJetPhi) maxDeltaJetPhi = deltajetphi;

	/**
	if (event_->DTSegY[idt] > -100000) { //only upper hits will differ in direction
	  //double phidir = acos(cos(event_->DTSegPhi[idt] - event_->DTSegPhiDir[idt]));
	  //hDTphidirection_->Fill(phidir);
	  hDTphidirection_->Fill(event_->DTSegYDir[idt]);
	}
	*/

	if (event_->DTSegR[idt] > 560) outerDT++;
	else innerDT++;
      }
      hDTdeltajetphi_->Fill(maxDeltaJetPhi); 
      hDTdeltaphi_->Fill(maxDeltaPhi);

      //std::cout << "testing dt frac...";
      double frac = innerDT/outerDT;
      hDTinnerouterfrac_->Fill(frac);
      hDTouter_->Fill(outerDT);


      //std::cout << "testing RPCs...";
      double maxRPCDeltaJetPhi = -1.;
      double maxRPCDeltaPhi = -1.;
      for (unsigned irpc = 0; irpc<event_->rpcHit_N; irpc++) {
	if (irpc == 0)
	  testPhi = event_->rpcHitPhi[0];
	else {
	  double deltaPhi = acos(cos(event_->rpcHitPhi[irpc] - testPhi));
	  if (deltaPhi > maxRPCDeltaPhi) maxRPCDeltaPhi = deltaPhi;
	}
	double deltajetphi = acos(cos(event_->rpcHitPhi[irpc] - event_->jetPhi[0]));
	if (deltajetphi > maxRPCDeltaJetPhi) maxRPCDeltaJetPhi = deltajetphi;

	if (event_->rpcHitR[irpc] > 560) outerRPC++;
	else innerRPC++;
      }
      hRPCdeltajetphi_->Fill(maxRPCDeltaJetPhi); 
      hRPCdeltaphi_->Fill(maxRPCDeltaPhi);

      hRPCinnerouterfrac_->Fill(1.*innerRPC/outerRPC);
      hRPCouter_->Fill(outerRPC);      
      

      //std::cout << "testing RPC pairs...";
      unsigned nCloseRPCPairs = 0;
      for (unsigned irpc = 0; irpc < event_->rpcHit_N; irpc++) {
	if (event_->rpcHitR[irpc] < 385) continue;
	for (unsigned jrpc = irpc+1; jrpc < event_->rpcHit_N; jrpc++) {
	  if (event_->rpcHitR[jrpc] < 385) continue;
	  double deltaZ = fabs(event_->rpcHitZ[irpc] - event_->rpcHitZ[jrpc]);
	  double deltaPhi = acos(cos(event_->rpcHitPhi[irpc] - event_->rpcHitPhi[jrpc]));
	  
	  // Require hits to be localized in z or in phi
	  if (deltaZ < 40.0 || deltaPhi > TMath::Pi()/2.) { //  || deltaPhi < 0.2
	    nCloseRPCPairs++;
	  }
	}
      }
      hNRPCpairs_->Fill(nCloseRPCPairs);


      // Calculate cutflow for each condition
      if (maxDeltaPhi > TMath::Pi()/2.) {
	hcosmiccum_->Fill(1);
	if (maxDeltaJetPhi > 1.0) {
	  hcosmiccum_->Fill(2);
	  // cosmic if DT hits are separated in phi
	  if (maxRPCDeltaPhi > TMath::Pi()/2.) {
	    hcosmiccum_->Fill(3);
	    if (outerDT >= 1) {
	      hcosmiccum_->Fill(4);
	      if (outerRPC >= 2) {
		hcosmiccum_->Fill(5);
	      }
	    }
	  }
	}
      } else {
      	hcosmiccum_->Fill(6);
      }
      //ncut 7++;
      
    }
    

    // loop over cuts
    bool fail=false;
    for (unsigned c=0; c<cuts_.nCuts(); c++) {

      // N-1
      if (cuts_.cutNMinusOne(c)) {
	hnminus1_->Fill(c);
      }
      // passes this cut
      if (cuts_.cutN(c)) {
	hncutind_->Fill(c);
      }
      else fail |= true;
      
      // vetoed by this or a previous cut
      if (!fail) {
	hncutcum_->Fill(c);
      }
    }



    // only consider events passing main trigger with jet in barrel
    if ( !(trig && e>50. && fabs(eta)<1.3) ) continue;

    // fill BX histograms
    if ( abs(abs(bxWrtBunch) - abs(bxWrtColl)) < 2) {
      if (isNoise && !isCosmic  && !isVtx && !isBeamGas && !isBeamHalo) {
	noiseBX_->Fill(bxWrtColl);
      }
      if (isCosmic  && !isVtx && !isBeamGas && !isBeamHalo) {
	cosmicBX_->Fill(bxWrtColl);
      }
      if (isBeamHalo && !isVtx && !isBeamGas) {
	beamHaloBX_->Fill(bxWrtColl);
      }
      if (isBeamGas && !isVtx ) {
	beamGasBX_->Fill(bxWrtColl);
      }
      if (isVtx ) {
	vertexBX_->Fill(bxWrtColl);
      }
      if (isUnid) {
	unidBX_->Fill(bxWrtColl);
      }
    }
    else if (abs(bxWrtBunch) < (abs(bxWrtColl)-1) ) {  // closer to a unpaired bunch than a collision
      if (isNoise && !isCosmic  && !isVtx && !isBeamGas && !isBeamHalo) {
	noiseBXUP_->Fill(bxWrtBunch);
      }
      if (isCosmic  && !isVtx && !isBeamGas && !isBeamHalo) {
	cosmicBXUP_->Fill(bxWrtBunch);
      }
      if (isBeamHalo && !isVtx && !isBeamGas) {
	beamHaloBXUP_->Fill(bxWrtBunch);
      }
      if (isBeamGas && !isVtx ) {
	beamGasBXUP_->Fill(bxWrtBunch);
      }
      if (isVtx ) {
	vertexBXUP_->Fill(bxWrtBunch);
      }
      if (isUnid) {
	unidBXUP_->Fill(bxWrtBunch);
      }
    }

    // for remaining distributions, require BX cut
    if ( !(abs(bxWrtBunch)>2) ) continue;

    if (isNoise && !isCosmic  && !isVtx && !isBeamGas && !isBeamHalo) {
      noiseJetE_->Fill(e);
      noiseJetEta_->Fill(eta);
      noiseJetPhi_->Fill(phi);
      noiseJetN60_->Fill(n60);
      noiseJetN90_->Fill(n90);
      noiseNtow_->Fill(ntow);
      noiseIPhiFrac_->Fill(fiphi);
      noiseNMu_->Fill(nmu);
      noiseNCSC_->Fill(ncsc);
      noiseBHFlag_->Fill(bh);
      noiseNTrack_->Fill(ntrk);
      noiseNVtx_->Fill(nvtx);
      noiseR1_->Fill(r1);
      noiseR2_->Fill(r2);
      noiseRP_->Fill(rp);
      noiseRO_->Fill(ro);
    }
    
    if (isCosmic  && !isVtx && !isBeamGas && !isBeamHalo) {
      cosmicJetE_->Fill(e);
      cosmicJetEta_->Fill(eta);
      cosmicJetPhi_->Fill(phi);
      cosmicJetN60_->Fill(n60);
      cosmicJetN90_->Fill(n90);
      cosmicNtow_->Fill(ntow);
      cosmicIPhiFrac_->Fill(fiphi);
      cosmicNMu_->Fill(nmu);
      cosmicNCSC_->Fill(ncsc);
      cosmicBHFlag_->Fill(bh);
      cosmicNTrack_->Fill(ntrk);
      cosmicNVtx_->Fill(nvtx);
      cosmicR1_->Fill(r1);
      cosmicR2_->Fill(r2);
      cosmicRP_->Fill(rp);
      cosmicRO_->Fill(ro);
    }

    if (isBeamHalo && !isVtx && !isBeamGas) {
      beamHaloJetE_->Fill(e);
      beamHaloJetEta_->Fill(eta);
      beamHaloJetPhi_->Fill(phi);
      beamHaloJetN60_->Fill(n60);
      beamHaloJetN90_->Fill(n90);
      beamHaloNtow_->Fill(ntow);
      beamHaloIPhiFrac_->Fill(fiphi);
      beamHaloNMu_->Fill(nmu);
      beamHaloNCSC_->Fill(ncsc);
      beamHaloBHFlag_->Fill(bh);
      beamHaloNTrack_->Fill(ntrk);
      beamHaloNVtx_->Fill(nvtx);
      beamHaloR1_->Fill(r1);
      beamHaloR2_->Fill(r2);
      beamHaloRP_->Fill(rp);
      beamHaloRO_->Fill(ro);
    }

    if (isBeamGas && !isVtx ) {
      beamGasJetE_->Fill(e);
      beamGasJetEta_->Fill(eta);
      beamGasJetPhi_->Fill(phi);
      beamGasJetN60_->Fill(n60);
      beamGasJetN90_->Fill(n90);
      beamGasNtow_->Fill(ntow);
      beamGasIPhiFrac_->Fill(fiphi);
      beamGasNMu_->Fill(nmu);
      beamGasNCSC_->Fill(ncsc);
      beamGasBHFlag_->Fill(bh);
      beamGasNTrack_->Fill(ntrk);
      beamGasNVtx_->Fill(nvtx);
      beamGasR1_->Fill(r1);
      beamGasR2_->Fill(r2);
      beamGasRP_->Fill(rp);
      beamGasRO_->Fill(ro);
    }

    if (isVtx) {
      vertexJetE_->Fill(e);
      vertexJetEta_->Fill(eta);
      vertexJetPhi_->Fill(phi);
      vertexJetN60_->Fill(n60);
      vertexJetN90_->Fill(n90);
      vertexNtow_->Fill(ntow);
      vertexIPhiFrac_->Fill(fiphi);
      vertexNMu_->Fill(nmu);
      vertexNCSC_->Fill(ncsc);
      vertexBHFlag_->Fill(bh);
      vertexNTrack_->Fill(ntrk);
      vertexNVtx_->Fill(nvtx);
      vertexR1_->Fill(r1);
      vertexR2_->Fill(r2);
      vertexRP_->Fill(rp);
      vertexRO_->Fill(ro);
    }

    if (isUnid) {
      unidJetE_->Fill(e);
      unidJetEta_->Fill(eta);
      unidJetPhi_->Fill(phi);
      unidJetN60_->Fill(n60);
      unidJetN90_->Fill(n90);
      unidNtow_->Fill(ntow);
      unidIPhiFrac_->Fill(fiphi);
      unidNMu_->Fill(nmu);
      unidNCSC_->Fill(ncsc);
      unidBHFlag_->Fill(bh);
      unidNTrack_->Fill(ntrk);
      unidNVtx_->Fill(nvtx);
      unidR1_->Fill(r1);
      unidR2_->Fill(r2);
      unidRP_->Fill(rp);
      unidRO_->Fill(ro);
    }


    overlap                 |= 0x1;
    if (isNoise)    overlap |= 0x2;
    if (isCosmic)   overlap |= 0x4;
    if (isBeamHalo) overlap |= 0x8;
    if (isBeamGas)  overlap |= 0x10;
    if (isVtx)      overlap |= 0x20;
    if (isUnid)     overlap |= 0x40;

    for (int j=0; j<8; ++j) {
      for (int k=0; k<8; ++k) {
	if (((overlap>>j)&0x1 > 0) && ((overlap>>k)&0x1 > 0)) overlap_->Fill(j, k);
      }
    }

  }

  // normalise BX distributions
  TH1D* tmpNormBX = new TH1D("tmpNormBX", "", 2000, -999.5, 1000.5);
  TH1D* tmpNormBXUP = new TH1D("tmpNormBXUP", "", 2000, -999.5, 1000.5);

  for (unsigned f=0; f<fillList_.size(); ++f) {
    unsigned long fill = fillList_.at(f);
    if (fill != 0) {
      double livetime=livetime_.getLivetimeByFill(fill);
      tmpNormBX->Add(normBX_.histogram(fill), livetime);
      tmpNormBXUP->Add(normBXUP_.histogram(fill), livetime);
    }
  }

  for (int bin=1; bin<2001; ++bin) {
    tmpNormBX->SetBinError(bin, 0.);
    tmpNormBXUP->SetBinError(bin, 0.);
  }

  noiseBX_->Divide(tmpNormBX);
  noiseBXUP_->Divide(tmpNormBXUP);
  cosmicBX_->Divide(tmpNormBX);
  cosmicBXUP_->Divide(tmpNormBXUP);
  beamHaloBX_->Divide(tmpNormBX);
  beamHaloBXUP_->Divide(tmpNormBXUP);
  beamGasBX_->Divide(tmpNormBX);
  beamGasBXUP_->Divide(tmpNormBXUP);
  vertexBX_->Divide(tmpNormBX);
  vertexBXUP_->Divide(tmpNormBXUP);
  unidBX_->Divide(tmpNormBX);
  unidBXUP_->Divide(tmpNormBXUP);

  // SAVE HISTOGRAMS
  ofile_->cd();
  hnvertex_->Write("",TObject::kOverwrite);
  hncsc_->Write("",TObject::kOverwrite);
  hnmu_->Write("",TObject::kOverwrite);
  hndt_->Write("",TObject::kOverwrite);
  hnrpc_->Write("",TObject::kOverwrite);
  hnoise_->Write("",TObject::kOverwrite);
  hjete_->Write("",TObject::kOverwrite);
  hn60_->Write("",TObject::kOverwrite);
  hn90_->Write("",TObject::kOverwrite);
  hntowiphi_->Write("",TObject::kOverwrite);
  hiphifrac_->Write("",TObject::kOverwrite);
  hr1_->Write("",TObject::kOverwrite);
  hr2_->Write("",TObject::kOverwrite);
  hrpeak_->Write("",TObject::kOverwrite);
  hrouter_->Write("",TObject::kOverwrite);
  hncutcum_->Write("",TObject::kOverwrite);
  hnminus1_->Write("",TObject::kOverwrite);
  hncutind_->Write("",TObject::kOverwrite);

  hremainingDTR_->Write("",TObject::kOverwrite);
  hremainingRPCR_->Write("",TObject::kOverwrite);

  hDTphidirection_->Write("",TObject::kOverwrite);

  hDTdeltaphi_->Write("",TObject::kOverwrite);
  hDTdeltajetphi_->Write("",TObject::kOverwrite);
  hRPCdeltaphi_->Write("",TObject::kOverwrite);
  hRPCdeltajetphi_->Write("",TObject::kOverwrite);
  hDTinnerouterfrac_->Write("",TObject::kOverwrite);
  hRPCinnerouterfrac_->Write("",TObject::kOverwrite);
  hNRPCpairs_->Write("",TObject::kOverwrite);
  hDTouter_->Write("",TObject::kOverwrite);
  hRPCouter_->Write("",TObject::kOverwrite);

  /**
  // Show individual results for cosmic conditions
  hcosmiccum_->Fill(1,ncosmic);
  hcosmiccum_->Fill(2,ncut1);
  hcosmiccum_->Fill(3,ncut2);
  hcosmiccum_->Fill(4,ncut3);
  hcosmiccum_->Fill(5,ncut4);
  hcosmiccum_->Fill(6,ncut5);
  hcosmiccum_->Fill(7,ncut6);
  hcosmiccum_->Fill(8,ncut7);
  */
  hcosmiccum_->Write("",TObject::kOverwrite);


  noiseJetE_->Write("",TObject::kOverwrite);
  noiseJetEta_->Write("",TObject::kOverwrite);
  noiseJetPhi_->Write("",TObject::kOverwrite);
  noiseJetN60_->Write("",TObject::kOverwrite);
  noiseJetN90_->Write("",TObject::kOverwrite);
  noiseNtow_->Write("",TObject::kOverwrite);
  noiseIPhiFrac_->Write("",TObject::kOverwrite);
  noiseNMu_->Write("",TObject::kOverwrite);
  noiseNCSC_->Write("",TObject::kOverwrite);
  noiseBHFlag_->Write("",TObject::kOverwrite);
  noiseNTrack_->Write("",TObject::kOverwrite);
  noiseNVtx_->Write("",TObject::kOverwrite);
  noiseBX_->Write("",TObject::kOverwrite);
  noiseBXUP_->Write("",TObject::kOverwrite);
  noiseR1_->Write("",TObject::kOverwrite);
  noiseR2_->Write("",TObject::kOverwrite);
  noiseRP_->Write("",TObject::kOverwrite);
  noiseRO_->Write("",TObject::kOverwrite);

  // cosmic
  cosmicJetE_->Write("",TObject::kOverwrite);
  cosmicJetEta_->Write("",TObject::kOverwrite);
  cosmicJetPhi_->Write("",TObject::kOverwrite);
  cosmicJetN60_->Write("",TObject::kOverwrite);
  cosmicJetN90_->Write("",TObject::kOverwrite);
  cosmicNtow_->Write("",TObject::kOverwrite);
  cosmicIPhiFrac_->Write("",TObject::kOverwrite);
  cosmicNMu_->Write("",TObject::kOverwrite);
  cosmicNCSC_->Write("",TObject::kOverwrite);
  cosmicBHFlag_->Write("",TObject::kOverwrite);
  cosmicNTrack_->Write("",TObject::kOverwrite);
  cosmicNVtx_->Write("",TObject::kOverwrite);
  cosmicBX_->Write("",TObject::kOverwrite);
  cosmicBXUP_->Write("",TObject::kOverwrite);
  cosmicR1_->Write("",TObject::kOverwrite);
  cosmicR2_->Write("",TObject::kOverwrite);
  cosmicRP_->Write("",TObject::kOverwrite);
  cosmicRO_->Write("",TObject::kOverwrite);
  
  // beam halo
  beamHaloJetE_->Write("",TObject::kOverwrite);
  beamHaloJetEta_->Write("",TObject::kOverwrite);
  beamHaloJetPhi_->Write("",TObject::kOverwrite);
  beamHaloJetN60_->Write("",TObject::kOverwrite);
  beamHaloJetN90_->Write("",TObject::kOverwrite);
  beamHaloNtow_->Write("",TObject::kOverwrite);
  beamHaloIPhiFrac_->Write("",TObject::kOverwrite);
  beamHaloNMu_->Write("",TObject::kOverwrite);
  beamHaloNCSC_->Write("",TObject::kOverwrite);
  beamHaloBHFlag_->Write("",TObject::kOverwrite);
  beamHaloNTrack_->Write("",TObject::kOverwrite);
  beamHaloNVtx_->Write("",TObject::kOverwrite);
  beamHaloBX_->Write("",TObject::kOverwrite);
  beamHaloBXUP_->Write("",TObject::kOverwrite);
  beamHaloR1_->Write("",TObject::kOverwrite);
  beamHaloR2_->Write("",TObject::kOverwrite);
  beamHaloRP_->Write("",TObject::kOverwrite);
  beamHaloRO_->Write("",TObject::kOverwrite);
  
  // beam gas
  beamGasJetE_->Write("",TObject::kOverwrite);
  beamGasJetEta_->Write("",TObject::kOverwrite);
  beamGasJetPhi_->Write("",TObject::kOverwrite);
  beamGasJetN60_->Write("",TObject::kOverwrite);
  beamGasJetN90_->Write("",TObject::kOverwrite);
  beamGasNtow_->Write("",TObject::kOverwrite);
  beamGasIPhiFrac_->Write("",TObject::kOverwrite);
  beamGasNMu_->Write("",TObject::kOverwrite);
  beamGasNCSC_->Write("",TObject::kOverwrite);
  beamGasBHFlag_->Write("",TObject::kOverwrite);
  beamGasNTrack_->Write("",TObject::kOverwrite);
  beamGasNVtx_->Write("",TObject::kOverwrite);
  beamGasBX_->Write("",TObject::kOverwrite);
  beamGasBXUP_->Write("",TObject::kOverwrite);
  beamGasR1_->Write("",TObject::kOverwrite);
  beamGasR2_->Write("",TObject::kOverwrite);
  beamGasRP_->Write("",TObject::kOverwrite);
  beamGasRO_->Write("",TObject::kOverwrite);
  
  // vertex
  vertexJetE_->Write("",TObject::kOverwrite);
  vertexJetEta_->Write("",TObject::kOverwrite);
  vertexJetPhi_->Write("",TObject::kOverwrite);
  vertexJetN60_->Write("",TObject::kOverwrite);
  vertexJetN90_->Write("",TObject::kOverwrite);
  vertexNtow_->Write("",TObject::kOverwrite);
  vertexIPhiFrac_->Write("",TObject::kOverwrite);
  vertexNMu_->Write("",TObject::kOverwrite);
  vertexNCSC_->Write("",TObject::kOverwrite);
  vertexBHFlag_->Write("",TObject::kOverwrite);
  vertexNTrack_->Write("",TObject::kOverwrite);
  vertexNVtx_->Write("",TObject::kOverwrite);
  vertexBX_->Write("",TObject::kOverwrite);
  vertexBXUP_->Write("",TObject::kOverwrite);
  vertexR1_->Write("",TObject::kOverwrite);
  vertexR2_->Write("",TObject::kOverwrite);
  vertexRP_->Write("",TObject::kOverwrite);
  vertexRO_->Write("",TObject::kOverwrite);
  
  // unidentified
  unidJetE_->Write("",TObject::kOverwrite);
  unidJetEta_->Write("",TObject::kOverwrite);
  unidJetPhi_->Write("",TObject::kOverwrite);
  unidJetN60_->Write("",TObject::kOverwrite);
  unidJetN90_->Write("",TObject::kOverwrite);
  unidNtow_->Write("",TObject::kOverwrite);
  unidIPhiFrac_->Write("",TObject::kOverwrite);
  unidNMu_->Write("",TObject::kOverwrite);
  unidNCSC_->Write("",TObject::kOverwrite);
  unidBHFlag_->Write("",TObject::kOverwrite);
  unidNTrack_->Write("",TObject::kOverwrite);
  unidNVtx_->Write("",TObject::kOverwrite);
  unidBX_->Write("",TObject::kOverwrite);
  unidBXUP_->Write("",TObject::kOverwrite);
  unidR1_->Write("",TObject::kOverwrite);
  unidR2_->Write("",TObject::kOverwrite);
  unidRP_->Write("",TObject::kOverwrite);
  unidRO_->Write("",TObject::kOverwrite);

  overlap_->Write("",TObject::kOverwrite);

  std::cout << "\n------------------- Cuts for plots ------------------------" << std::endl;
  std::cout << "    trig && e>70 && ncsc==0 && event_->noiseFilterResult" << std::endl;
  std::cout << "-----------------------------------------------------------\n" << std::endl;
  

}



// this is the main program, no need to do anything here
int main(int argc, char* argv[]) {

  // sum of squares error info for histograms
  TH1D::SetDefaultSumw2();

  // create analysis
  Backgrounds analyser(argc, argv);

  analyser.setup();

  analyser.cuts().print(std::cout);

  analyser.loop();

  return 0;

}
