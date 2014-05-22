#ifndef HaloBackground_h
#define HaloBackground_h

#include "StoppedHSCP/Analysis/interface/BasicAnalyser.h"

#include "StoppedHSCP/Analysis/interface/MultiHistogram1D.h"

#include "TFile.h"
#include "TMath.h"
#include "TChain.h"
#include "TH1D.h"
#include "TH2D.h"

#include <set>

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

  // Shamelessly stolen from DataFormats/MuonDetId/src/CSCDetId.cc#100
  int chamberType(int iStation, int iRing) {
    int i = 2*iStation + iRing;
    if (iStation == 1) {
      i = i - 1;
      if (i>4) i = 1;
    }
    return i;
  }

  // Standard CMS delta phi calculation. Robbed from DataFormats/Math/interface/deltaPhi.h
  double deltaPhi(double phi1, double phi2) { 
    double result = phi1 - phi2;
    while (result > M_PI) result -= 2*M_PI;
    while (result <= -M_PI) result += 2*M_PI;
    return result;
  }
		  

  // YOUR CODE HERE
  std::vector<unsigned long> fillList_;
  std::ofstream dumpFile_;

  // Fedor's second method
  TH1D* hDphi_;
  TH1D* hAverageDphi_;
  TH1D* hIncomingEta_;
  TH1D* hOutgoingEta_;
  TH1D* hBothEta_;
  TH1D* hHaloPlusZEta_;
  TH1D* hHaloMinusZEta_;
  TH1D* hSegmentLayer_;
  TH1D* hSegmentDirection_;
  TH1D* hSelectedJetPhi_;

  // CSCSegment studies
  TH1D* hSegmentTime_;
  TH1D* hSegmentR_;
  TH1D* hSegmentZ_;
  TH1D* hMinusOneCscSegments_;

  TH2D* hSegmentZR_;
  TH2D* hSegmentEtaR_;
  TH2D* hSegmentZTime_;
  TH2D* hSegmentRPhi_;
  TH2D* hSegmentXY_;
  TH2D* hSegmentXYzoom_;
  TH2D* hSegmentThetaDir_;

  TH2D* hSegmentLayersVRadius_;
  TH2D* hSegmentLayersVPhi_;

  // Jet stuff
  TH1D* hJetEtaMean_;
  TH1D* hJetPhiMean_;
  TH1D* hJetEtaEtaMoment_;
  TH1D* hJetEtaPhiMoment_;
  TH1D* hJetPhiPhiMoment_;
  TH1D* hHaloJetEtaMean_;
  TH1D* hHaloJetPhiMean_;
  TH1D* hHaloJetEtaEtaMoment_;
  TH1D* hHaloJetEtaPhiMoment_;
  TH1D* hHaloJetPhiPhiMoment_;



  /** 
   ** Splitting the estimate out into beam 1 and beam 2 for both the
   ** 2D CSCSegment estimate and the jetEta[0] estimate
   ** Beam 1 -->     clockwise     --> -z direction
   ** Beam 2 --> counter-clockwise --> +z direction
   **/

  // Calculate inefficiency binned by jetEta[0] - beam 1
  TH1D* hIncomingJetEta1_;
  TH1D* hOutgoingJetEta1_;
  TH1D* hBothJetEta1_;
  TH1D* hIneffNumJetEta1_;
  TH1D* hIneffDenJetEta1_;
  TH1D* hIneffFractionJetEta1_;
  TH1D* hIneffCountJetEta1_;
  TH1D* hMinusOneHaloJetEta1_;

  // Calculate inefficiency binned by jetEta[0] - beam 2
  TH1D* hIncomingJetEta2_;
  TH1D* hOutgoingJetEta2_;
  TH1D* hBothJetEta2_;
  TH1D* hIneffNumJetEta2_;
  TH1D* hIneffDenJetEta2_;
  TH1D* hIneffFractionJetEta2_;
  TH1D* hIneffCountJetEta2_;
  TH1D* hMinusOneHaloJetEta2_;

  // Calculate inefficiency binned by CSCSegmentR and CSCSegmentPhi (avg) - beam 1
  TH2D* hAverageRPhi1_;
  TH2D* hAverageErrRPhi1_;
  TH2D* hIncomingRPhi1_;
  TH2D* hOutgoingRPhi1_;
  TH2D* hBothRPhi1_;
  TH2D* hnRPhi1_;
  TH2D* hIneffNumRPhi1_;
  TH2D* hIneffDenRPhi1_;
  TH2D* hIneffFractionRPhi1_;
  TH2D* hIneffCountRPhi1_;
  TH2D* hMinusOneHaloRPhi1_;
  
  // Calculate inefficiency binned by CSCSegmentR and CSCSegmentPhi (avg) - beam2
  TH2D* hAverageRPhi2_;
  TH2D* hAverageErrRPhi2_;
  TH2D* hIncomingRPhi2_;
  TH2D* hOutgoingRPhi2_;
  TH2D* hBothRPhi2_;
  TH2D* hnRPhi2_;
  TH2D* hIneffNumRPhi2_;
  TH2D* hIneffDenRPhi2_;
  TH2D* hIneffFractionRPhi2_;
  TH2D* hIneffCountRPhi2_;
  TH2D* hMinusOneHaloRPhi2_;

  // Calculate inefficiency binned by CSCSegmentXY (avg) - beam 1
  TH2D* hAverageXY1_;
  TH2D* hAverageErrXY1_;
  TH2D* hIncomingXY1_;
  TH2D* hOutgoingXY1_;
  TH2D* hBothXY1_;
  TH2D* hnXY1_;
  TH2D* hIneffNumXY1_;
  TH2D* hIneffDenXY1_;
  TH2D* hIneffFractionXY1_;
  TH2D* hIneffCountXY1_;
  TH2D* hMinusOneHaloXY1_;
  
  // Calculate inefficiency binned by CSCSegmentXY (avg) - beam2
  TH2D* hAverageXY2_;
  TH2D* hAverageErrXY2_;
  TH2D* hIncomingXY2_;
  TH2D* hOutgoingXY2_;
  TH2D* hBothXY2_;
  TH2D* hnXY2_;
  TH2D* hIneffNumXY2_;
  TH2D* hIneffDenXY2_;
  TH2D* hIneffFractionXY2_;
  TH2D* hIneffCountXY2_;
  TH2D* hMinusOneHaloXY2_;

  /** 
   ** Old 1D and beam 1+2 estimates 
   **/
  // Calculate inefficiency binned by CSCSegmentR and CSCSegmentPhi (avg) - beam2
  TH2D* hAverageRPhi_;
  TH2D* hAverageErrRPhi_;
  TH2D* hIncomingRPhi_;
  TH2D* hOutgoingRPhi_;
  TH2D* hBothRPhi_;
  TH2D* hIneffNumRPhi_;
  TH2D* hIneffDenRPhi_;
  TH2D* hIneffFractionRPhi_;
  TH2D* hIneffCountRPhi_;
  TH2D* hMinusOneHaloRPhi_;

  // Calculate inefficiency binned by CSCSegmentR (avg)
  TH1D* hAverageR_;
  TH1D* hAverageErrR_;
  TH1D* hIncomingR_;
  TH1D* hOutgoingR_;
  TH1D* hBothR_;
  TH1D* hIneffNumR_;
  TH1D* hIneffDenR_;
  TH1D* hIneffFractionR_;
  TH1D* hIneffCountR_;
  TH1D* hMinusOneHaloR_;

  // Calculate inefficiency binned by CSCSegmentPhi (avg)
  TH1D* hAveragePhi_;
  TH1D* hAverageErrPhi_;
  TH1D* hIncomingPhi_;
  TH1D* hOutgoingPhi_;
  TH1D* hBothPhi_;
  TH1D* hIneffNumPhi_;
  TH1D* hIneffDenPhi_;
  TH1D* hIneffFractionPhi_;
  TH1D* hIneffCountPhi_;
  TH1D* hMinusOneHaloPhi_;

  // Calculate inefficiency binned by jetEta[0]
  TH1D* hIncomingE_;
  TH1D* hOutgoingE_;
  TH1D* hBothE_;
  TH1D* hIneffNum_;
  TH1D* hIneffDen_;
  TH1D* hIneffEta_;
  TH1D* hIneffEta2_;
  TH1D* hMinusOneHaloEta_ ;

};

#endif


// this is the event loop
void HaloBackground::loop() {

  // DO ANY SETUP HERE

  // setup log files
  std::string fd(outdir_);
  fd+="/HaloBackground.txt";
  dumpFile_.open(fd.c_str());
  dumpFile_ << "Output from haloBackground analysis" << std::endl << std::endl;
  

  // Fedor's second method
  ofile_->cd();
  hDphi_             = new TH1D("hDphi","Dphi between all CSCSegments and leading jet", 160, -1.6, 1.6);
  hAverageDphi_      = new TH1D("hAverageDphi","Average Dphi between all CSCSegments and leading jet, per event", 160, -1.6, 1.6);
  //hNhits_ = new TH1D("hNCSCRechitsPerSeg","", 10, 0, 10);
  hHaloPlusZEta_     = new TH1D("hHaloPlusZEta", "jetEta[0] for halo traveling in +Z direction", 40, -2.0, 2.0);  
  hHaloMinusZEta_    = new TH1D("hHaloMinusZEta", "jetEta[0] for halo traveling in -Z direction", 40, -2.0, 2.0);  

  hSegmentLayer_     = new TH1D("hSegmentLayer", "", 20, -10, 10);
  hSegmentDirection_ = new TH1D("hSegmentDirection", ";;dir", 220, -1.1, 1.1);
  hSegmentTime_      = new TH1D("hSegmentTime", ";t[ns];", 300, -150., 150.);
  hSegmentR_         = new TH1D("hSegmentR", ";r [cm];", 800, 0., 800.);
  hSegmentZ_         = new TH1D("hSegmentZ", ";z [cm];", 2200., -1100., 1100.);

  // 2-D
  hSegmentZR_        = new TH2D("hSegmentZR",";z [cm];r [cm]",2200,-1100.,1100.,800, 0.,800.);
  hSegmentEtaR_      = new TH2D("hSegmentEtaR",";#eta;r [cm]",50, -2.5, 2.5,800,0.,800.);
  hSegmentZTime_     = new TH2D("hSegmentZTime",";z [cm];t [ns]",550,-1100.,1100.,200, -100., 100.); 
  hSegmentRPhi_      = new TH2D("hSegmentRPhi",";r [cm];#phi",800,0.,800.,63, -3.15, 3.15);
  hSegmentXY_        = new TH2D("hSegmentXY",";x [cm]; y [cm]",800, -800., 800., 800, -800.,800.);
  hSegmentXYzoom_    = new TH2D("hSegmentXYzoom",";x [cm]; y [cm]",300, -300., 300., 300, -300.,300.);
  hSegmentThetaDir_  = new TH2D("hSegmentThetaDir",";#theta;dir",160,0.,3.2,11, -1.1, 1.1);

  hSegmentLayersVRadius_ = new TH2D("hSegmentLayersVRadius","",15,0,15,800,0,800);
  hSegmentLayersVPhi_    = new TH2D("hSegmentLayersVPhi","",20, 0, 20, 63, -3.15, 3.15);

  hSelectedJetPhi_ = new TH1D("hSelectedJetPhi",";#phi;",63, -3.15, 3.15);;


  hJetEtaMean_ = new TH1D("hJetEtaMean",";#eta_{jet};",100, -1.5, 1.5);
  hJetPhiMean_ = new TH1D("hJetPhiMean",";#phi_{jet};",100, -3.6, 3.6);
  hJetEtaEtaMoment_ = new TH1D("hJetEtaEtaMoment",";width of jet (#eta);",100, 0., 0.1);
  hJetEtaPhiMoment_ = new TH1D("hJetPhiPhiMoment",";width of jet (#phi);",100, 0., 0.1);
  hJetPhiPhiMoment_ = new TH1D("hJetEtaPhiMoment",";width of jet (#eta-#phi);",100, -0.03, 0.03);
  hHaloJetEtaMean_ = new TH1D("hHaloJetEtaMean",";#eta_{jet};",100, -1.5, 1.5);
  hHaloJetPhiMean_ = new TH1D("hHaloJetPhiMean",";#phi_{jet};",100, -3.6, 3.6);
  hHaloJetEtaEtaMoment_ = new TH1D("hHaloJetEtaEtaMoment",";width of jet (#eta);",100, 0., 0.1);
  hHaloJetEtaPhiMoment_ = new TH1D("hHaloJetPhiPhiMoment",";width of jet (#phi);",100, 0., 0.1);;
  hHaloJetPhiPhiMoment_ = new TH1D("hHaloJetEtaPhiMoment",";width of jet (#eta-#phi);",100, -0.03, 0.03);;


  /************* Separated into beam1 and beam2 ******************/
  // 2D inefficiency with CSCSegmentR and CSCSegmentPhi (avg) - beam1
  hAverageRPhi1_         = new TH2D("hAverageRPhi1","",200,0,800,63, -3.15, 3.15);
  hAverageErrRPhi1_      = new TH2D("hAverageErrRPhi1","",200,0,200,63, -3.15, 3.15);
  hIncomingRPhi1_        = new TH2D("hIncomingRPhi1","", 200,0,800,63, -3.15, 3.15);
  hOutgoingRPhi1_        = new TH2D("hOutgoingRPhi1","",200,0,800,63, -3.15, 3.15);
  hBothRPhi1_            = new TH2D("hBothRPhi1","",200,0,800,63, -3.15, 3.15);
  hnRPhi1_            = new TH2D("hnRPhi1","",200,0,800,63, -3.15, 3.15);
  hIneffNumRPhi1_        = new TH2D("hIneffNumRPhi1","",200,0,800,63, -3.15, 3.15);
  hIneffDenRPhi1_        = new TH2D("hIneffDenRPhi1","",200,0,800,63, -3.15, 3.15);
  hIneffFractionRPhi1_   = new TH2D("hIneffFractionRPhi1","",200,0,800,63, -3.15, 3.15);
  hIneffCountRPhi1_      = new TH2D("hIneffCountRPhi1","",200,0,800,63, -3.15, 3.15);
  hMinusOneHaloRPhi1_    = new TH2D("hMinusOneHaloRPhi1","",200,0,800,63, -3.15, 3.15);

  // 2D inefficiency with CSCSegmentR and CSCSegmentPhi (avg) - beam2
  hAverageRPhi2_         = new TH2D("hAverageRPhi2","",200,0,800,63, -3.15, 3.15);
  hAverageErrRPhi2_      = new TH2D("hAverageErrRPhi2","",200,0,200,63, -3.15, 3.15);
  hIncomingRPhi2_        = new TH2D("hIncomingRPhi2","",200,0,800,63, -3.15, 3.15);
  hOutgoingRPhi2_        = new TH2D("hOutgoingRPhi2","",200,0,800,63, -3.15, 3.15);
  hBothRPhi2_            = new TH2D("hBothRPhi2","",200,0,800,63, -3.15, 3.15);
  hnRPhi2_            = new TH2D("hnRPhi2","",200,0,800,63, -3.15, 3.15);
  hIneffNumRPhi2_        = new TH2D("hIneffNumRPhi2","",200,0,800,63, -3.15, 3.15);
  hIneffDenRPhi2_        = new TH2D("hIneffDenRPhi2","",200,0,800,63, -3.15, 3.15);
  hIneffFractionRPhi2_   = new TH2D("hIneffFractionRPhi2","",200,0,800,63, -3.15, 3.15);
  hIneffCountRPhi2_      = new TH2D("hIneffCountRPhi2","",200,0,800,63, -3.15, 3.15);
  hMinusOneHaloRPhi2_    = new TH2D("hMinusOneHaloRPhi2","",200,0,800,63, -3.15, 3.15);

  // 2D inefficiency with CSCSegmentXY (avg) - beam1
  hAverageXY1_         = new TH2D("hAverageXY1",";x[cm];y[cm]",50,-400,400,50,-400,400);
  hAverageErrXY1_      = new TH2D("hAverageErrXY1",";x[cm];y[cm]",50,-400,400,50,-400,400);
  hIncomingXY1_        = new TH2D("hIncomingXY1",";x[cm];y[cm]",50,-400,400,50,-400,400);
  hOutgoingXY1_        = new TH2D("hOutgoingXY1",";x[cm];y[cm]",50,-400,400,50,-400,400);
  hBothXY1_            = new TH2D("hBothXY1",";x[cm];y[cm]",50,-400,400,50,-400,400);
  hnXY1_               = new TH2D("hnXY1",";x[cm];y[cm]",50,-400,400,50,-400,400);
  hIneffNumXY1_        = new TH2D("hIneffNumXY1",";x[cm];y[cm]",50,-400,400,50,-400,400);
  hIneffDenXY1_        = new TH2D("hIneffDenXY1",";x[cm];y[cm]",50,-400,400,50,-400,400);
  hIneffFractionXY1_   = new TH2D("hIneffFractionXY1",";x[cm];y[cm]",50,-400,400,50,-400,400);
  hIneffCountXY1_      = new TH2D("hIneffCountXY1",";x[cm];y[cm]",50,-400,400,50,-400,400);
  hMinusOneHaloXY1_    = new TH2D("hMinusOneHaloXY1",";x[cm];y[cm]",50,-400,400,50,-400,400);

  // 2D inefficiency with CSCSegmentXY (avg) - beam2
  hAverageXY2_         = new TH2D("hAverageXY2",";x[cm];y[cm]",20,-400,400,20,-400,400);
  hAverageErrXY2_      = new TH2D("hAverageErrXY2",";x[cm];y[cm]",20,-400,400,20,-400,400);
  hIncomingXY2_        = new TH2D("hIncomingXY2",";x[cm];y[cm]",20,-400,400,20,-400,400);
  hOutgoingXY2_        = new TH2D("hOutgoingXY2",";x[cm];y[cm]",20,-400,400,20,-400,400);
  hBothXY2_            = new TH2D("hBothXY2",";x[cm];y[cm]",20,-400,400,20,-400,400);
  hnXY2_               = new TH2D("hnXY2",";x[cm];y[cm]",20,-400,400,20,-400,400);
  hIneffNumXY2_        = new TH2D("hIneffNumXY2",";x[cm];y[cm]",20,-400,400,20,-400,400);
  hIneffDenXY2_        = new TH2D("hIneffDenXY2",";x[cm];y[cm]",20,-400,400,20,-400,400);
  hIneffFractionXY2_   = new TH2D("hIneffFractionXY2",";x[cm];y[cm]",20,-400,400,20,-400,400);
  hIneffCountXY2_      = new TH2D("hIneffCountXY2",";x[cm];y[cm]",20,-400,400,20,-400,400);
  hMinusOneHaloXY2_    = new TH2D("hMinusOneHaloXY2",";x[cm];y[cm]",20,-400,400,20,-400,400);

  // Calculate inefficiency binned by jetEta[0] - beam 1
  hIncomingJetEta1_      = new TH1D("hIncomingJetEta1", "", 40, -2.0, 2.0);
  hOutgoingJetEta1_      = new TH1D("hOutgoingJetEta1", "", 40, -2.0, 2.0);
  hBothJetEta1_          = new TH1D("hBothJetEta1", "", 40, -2.0, 2.0);
  hIneffNumJetEta1_      = new TH1D("hIneffNumJetEta1", "", 40, -2.0, 2.0);
  hIneffDenJetEta1_      = new TH1D("hIneffDenJetEta1", "", 40, -2.0, 2.0);
  hIneffFractionJetEta1_ = new TH1D("hIneffFractionJetEta1", "", 40, -2.0, 2.0);
  hIneffCountJetEta1_    = new TH1D("hIneffCountJetEta1", "", 40, -2.0, 2.0);
  hMinusOneHaloJetEta1_  = new TH1D("hMinusOneHaloJetEta1", "", 40, -2.0, 2.0);

  // Calculate inefficiency binned by jetEta[0] - beam 2
  hIncomingJetEta2_      = new TH1D("hIncomingJetEta2", "", 40, -2.0, 2.0);
  hOutgoingJetEta2_      = new TH1D("hOutgoingJetEta2", "", 40, -2.0, 2.0);
  hBothJetEta2_          = new TH1D("hBothJetEta2", "", 40, -2.0, 2.0);
  hIneffNumJetEta2_      = new TH1D("hIneffNumJetEta2", "", 40, -2.0, 2.0);
  hIneffDenJetEta2_      = new TH1D("hIneffDenJetEta2", "", 40, -2.0, 2.0);
  hIneffFractionJetEta2_ = new TH1D("hIneffFractionJetEta2", "", 40, -2.0, 2.0);
  hIneffCountJetEta2_    = new TH1D("hIneffCountJetEta2", "", 40, -2.0, 2.0);
  hMinusOneHaloJetEta2_  = new TH1D("hMinusOneHaloJetEta2", "", 40, -2.0, 2.0);


  /*********** Estimates with both beams together ******************/
  // 2D inefficiency with CSCSegmentR and CSCSegmentPhi (avg)
  hAverageRPhi_         = new TH2D("hAverageRPhi","",800,0,800,63, -3.15, 3.15);
  hAverageErrRPhi_      = new TH2D("hAverageErrRPhi","",200,0,200,63, -3.15, 3.15);
  hIncomingRPhi_        = new TH2D("hIncomingRPhi","",800,0,800,63, -3.15, 3.15);
  hOutgoingRPhi_        = new TH2D("hOutgoingRPhi","",800,0,800,63, -3.15, 3.15);
  hBothRPhi_            = new TH2D("hBothRPhi","",800,0,800,63, -3.15, 3.15);
  hIneffNumRPhi_        = new TH2D("hIneffNumRPhi","",800,0,800,63, -3.15, 3.15);
  hIneffDenRPhi_        = new TH2D("hIneffDenRPhi","",800,0,800,63, -3.15, 3.15);
  hIneffFractionRPhi_   = new TH2D("hIneffFractionRPhi","",800,0,800,63, -3.15, 3.15);
  hIneffCountRPhi_      = new TH2D("hIneffCountRPhi","",800,0,800,63, -3.15, 3.15);
  hMinusOneHaloRPhi_    = new TH2D("hMinusOneHaloRPhi","",800,0,800,63, -3.15, 3.15);

  // Inefficiency estimate from CSCSegmentR (avg)
  hAverageR_         = new TH1D("hAverageR","",800,0,800);
  hAverageErrR_      = new TH1D("hAverageErrR","",200,0,200);
  hIncomingR_        = new TH1D("hIncomingR","",800,0,800);
  hOutgoingR_        = new TH1D("hOutgoingR","",800,0,800);
  hBothR_            = new TH1D("hBothR","",800,0,800);
  hIneffNumR_        = new TH1D("hIneffNumR","",800,0,800);
  hIneffDenR_        = new TH1D("hIneffDenR","",800,0,800);
  hIneffFractionR_   = new TH1D("hIneffFractionR","",800,0,800);
  hIneffCountR_      = new TH1D("hIneffCountR","",800,0,800);
  hMinusOneHaloR_    = new TH1D("hMinusOneHaloR","",800,0,800);

  // Inefficiency estimate from CSCSegmentPhi (avg)
  hAveragePhi_       = new TH1D("hAveragePhi","",63, -3.15, 3.15);
  hAverageErrPhi_    = new TH1D("hAverageErrPhi","",32, 0, 3.15);
  hIncomingPhi_      = new TH1D("hIncomingPhi","",63, -3.15, 3.15);
  hOutgoingPhi_      = new TH1D("hOutgoingPhi","",63, -3.15, 3.15);
  hBothPhi_          = new TH1D("hBothPhi","",63, -3.15, 3.15);
  hIneffNumPhi_      = new TH1D("hIneffNumPhi","",63, -3.15, 3.15);
  hIneffDenPhi_      = new TH1D("hIneffDenPhi","",63, -3.15, 3.15);
  hIneffFractionPhi_ = new TH1D("hIneffFractionPhi","",63, -3.15, 3.15);
  hIneffCountPhi_    = new TH1D("hIneffCountPhi","",63, -3.15, 3.15);
  hMinusOneHaloPhi_  = new TH1D("hMinusOneHaloPhi","",63, -3.15, 3.15);


  // Inefficiency estimate from jetEta[0]
  hIncomingEta_ = new TH1D("hIncomingEta", "", 40, -2.0, 2.0);
  hOutgoingEta_ = new TH1D("hOutgoingEta", "", 40, -2.0, 2.0);
  hBothEta_     = new TH1D("hBothEta", "", 40, -2.0, 2.0);
  hIncomingE_ = new TH1D("hIncomingE", "", 200, 0, 200.0);
  hOutgoingE_ = new TH1D("hOutgoingE", "", 200, 0, 200.0);
  hBothE_     = new TH1D("hBothE", "", 200, 0, 200.0);
  hIneffNum_     = new TH1D("hIneffNum", "", 40, -2.0, 2.0);
  hIneffDen_     = new TH1D("hIneffDen", "", 40, -2.0, 2.0);
  hIneffEta_     = new TH1D("hIneffEta", "", 40, -2.0, 2.0);
  hIneffEta2_     = new TH1D("hIneffEta2", "", 40, -2.0, 2.0);

  hMinusOneHaloEta_ = new TH1D("hMinusOneHaloEta", "", 40, -2.0, 2.0);
  hMinusOneCscSegments_ = new TH1D("hMinusOneCscSegments","", 20, -1.,19.);

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


    // Fedor's second method (tag & probe based on incoming/outgoing CSCSegments)
    // cscSeg_N and jetN cuts are probably redundant, but trigger requirement isn't
    bool searchSample = cuts_.triggerCut() && event_->jet_N > 0;
    if (!searchSample) continue;

    bool incoming = false;
    bool outgoing = false;
    int nIncoming = 0;
    int nOutgoing = 0;
    
    // jet properties
    double jete   = event_->jetE[0];
    double jeteta = event_->jetEta[0];
    double jetphi = event_->jetPhi[0];

    set<int> nLayers;
    bool hasMatchingPhi = false;
    double direction = 0.;
    double allDphi = 0.;
    TH1F hcscsegmentr("hcscsegmentr","",0,800,800);
    TH1F hcscsegmentphi("hcscsegmentphi","",63,-3.15,3.15);
    TH1F hcscsegmentx("hcscsegmentx","",0,800,800);
    TH1F hcscsegmenty("hcscsegmenty","",0,800,800);
    for (unsigned iSeg = 0; iSeg < event_->cscSeg_N; iSeg++) {
      // First - make histogram of CSCSegment "direction" (Fig 14 in AN2012_002_v8)      
      // Determine "direction" of each halo segment, average "direction" for whole event
      //    @ direction == -1, +1 corresponds to travel in the +Z, -Z direction. Convention
      //      set by Fedor for absolutely no reason at all.
      double iDir = 0;
      // This has a case of the dumbs, but I'm not feeling clever right now
      if (event_->cscSegTime[iSeg] < -10. && event_->cscSegZ[iSeg] < 0) iDir = -1.0;  // +Z direction
      if (event_->cscSegTime[iSeg] >= -10. && event_->cscSegZ[iSeg] > 0) iDir = -1.0;
      if (event_->cscSegTime[iSeg] < -10. && event_->cscSegZ[iSeg] > 0) iDir = 1.0;   // -Z direction
      if (event_->cscSegTime[iSeg] >= -10. && event_->cscSegZ[iSeg] < 0) iDir = 1.0;
      direction += iDir;

      //std::cout << "\t" << event_->cscSegZ[iSeg] << "\t" << event_->cscSegTime[iSeg] << "\t" << iDir << std::endl;


      // Next - plot dPhi(CSCSegment,jet[0]), which was used to determine
      //     the amount of non-halo contamination in the |dPhi| < 0.4 region.
      double jetcsc_dPhi = deltaPhi(jetphi, event_->cscSegPhi[iSeg]);
      allDphi += jetcsc_dPhi;
      hDphi_->Fill(jetcsc_dPhi);

      int chamber = chamberType(event_->cscSegStation[iSeg], event_->cscSegRing[iSeg]);
      int endcap = (event_->cscSegZ[iSeg] > 0) ? 1 : -1;
      int layer = chamber * endcap;
      
      // Signal region
      if (fabs(jetcsc_dPhi) < 0.4) {
	hasMatchingPhi = true;
	hSegmentLayer_->Fill(layer);
	nLayers.insert(layer);
	
	if (event_->cscSegTime[iSeg] < -10) {
	  incoming = true;
	  nIncoming++;
	} else {
	  outgoing = true;
	  nOutgoing++;
	}
      }

      // Also - we want to look at the characteristics of the CSCSegments
      //     tan(theta) = r/z
      // pseudorapidity = -log( tan(theta/2) )
      double cscr     = event_->cscSegR[iSeg];
      double cscz     = event_->cscSegZ[iSeg];
      double cscphi   = event_->cscSegPhi[iSeg];
      double csctime  = event_->cscSegTime[iSeg];
      double csctheta = event_->cscSegDirTheta[iSeg];
      
      double cscx     = cscr*cos(cscphi);
      double cscy     = cscr*sin(cscphi);
      double csceta   = -1.0*log(tan(atan(fabs(cscr/cscz))/ 2.));
      if (cscz < 0) {
	//std::cout << cscz << "\t" << csceta << std::endl;
	csceta = -1.0*csceta;
      }
      hcscsegmentx.Fill(cscx);
      hcscsegmenty.Fill(cscy);
      hcscsegmentr.Fill(cscr);
      hcscsegmentphi.Fill(cscphi);

      // 1-D
      hSegmentTime_->Fill(csctime);
      hSegmentR_->Fill(cscr);
      hSegmentZ_->Fill(cscz);

      // 2-D
      hSegmentZR_->Fill(cscz,cscr);
      hSegmentEtaR_->Fill(csceta,cscr);
      hSegmentZTime_->Fill(cscz,csctime);
      hSegmentXY_->Fill(cscx,cscy);
      hSegmentXYzoom_->Fill(cscx,cscy);

      // phi = 0 is the +x axis
      hSegmentRPhi_->Fill(cscr,cscphi);

      // theta = 0 is the +z axis, theta = pi is the -z axis
      // This plot is tricky. I really wish that we could use theta instead of
      // this rough direction calculation. I'm trying to prove we can. The thing
      // is that there are some segments that get the wrong direction so this
      // plot isn't perfect. Maybe exclude segments that are likely tagged wrong?
      //if (csctime < -10.0 || csctime > 0.)
      hSegmentThetaDir_->Fill(csctheta,iDir); 


      // TODO: it would be really nice to have a plot showing how the radius of the
      // halo muon correlates with the number of CSCSegments in the event.
      // Just neet to be clever about determining the halo radius (just use average?)
    }
   
    // Some helpful variables
    double haloDirection = direction/(1.0*event_->cscSeg_N);
    double eventX = hcscsegmentx.GetMean();
    double eventY = hcscsegmenty.GetMean();
    double eventR = hcscsegmentr.GetMean();
    double eventPhi = hcscsegmentphi.GetMean();
    
    // Only record summary quantities for events w/ dPhi < 0.4 for at least 1 CSCSegment
    if (hasMatchingPhi) {

      // Get the average & error of the CSCSegment r & phi for this event
      // TODO: change this calculation to get the mode?
      hAverageR_->Fill(hcscsegmentr.GetMean());
      hAverageErrR_->Fill(hcscsegmentr.GetMeanError());
      hAveragePhi_->Fill(hcscsegmentphi.GetMean());
      hAverageErrPhi_->Fill(hcscsegmentphi.GetMeanError());
      hAverageRPhi_->Fill(hcscsegmentr.GetMean(),hcscsegmentphi.GetMean());
      hAverageErrRPhi_->Fill(hcscsegmentr.GetMeanError(),hcscsegmentphi.GetMeanError());
      
      if (haloDirection >= 0) { // Beam 1
      hAverageRPhi1_->Fill(hcscsegmentr.GetMean(),hcscsegmentphi.GetMean());
      hAverageErrRPhi1_->Fill(hcscsegmentr.GetMeanError(),hcscsegmentphi.GetMeanError());
      hAverageXY1_->Fill(hcscsegmentx.GetMean(),hcscsegmenty.GetMean());
      hAverageErrXY1_->Fill(hcscsegmentx.GetMeanError(),hcscsegmenty.GetMeanError());
      }
      if (haloDirection < 0) {  // Beam 2
	hAverageRPhi2_->Fill(hcscsegmentr.GetMean(),hcscsegmentphi.GetMean());
	hAverageErrRPhi2_->Fill(hcscsegmentr.GetMeanError(),hcscsegmentphi.GetMeanError());
	hAverageXY2_->Fill(hcscsegmentx.GetMean(),hcscsegmenty.GetMean());
	hAverageErrXY2_->Fill(hcscsegmentx.GetMeanError(),hcscsegmenty.GetMeanError());
      }
      hSegmentLayersVRadius_->Fill(nLayers.size(),eventR);
      hSegmentLayersVPhi_->Fill(nLayers.size(),eventPhi);
    

      // std::cout << "hAverage = " << hcscsegmentr.GetMean() << " +/- " 
      //          << hcscsegmentr.GetMeanError() << std::endl;
      
      // Fill dPhi histogram w/ average dPhi of all CSCSegments in this event
      hAverageDphi_->Fill(allDphi/(1.0*event_->cscSeg_N));

      // Fill segment direction histogram with average "direction" for event
      hSegmentDirection_->Fill(haloDirection);
    
      // Plot jetEta[0] for halo traveling in each direction
      if (haloDirection < 0)
	hHaloPlusZEta_->Fill(jeteta);
      if (haloDirection >= 0)
	hHaloMinusZEta_->Fill(jeteta);
    
      // No matching phi -> this is not a halo jet!
      // But still require that it passes trigger cut and has > 0 jets (searchSample)
    } else {
      hJetEtaMean_->Fill(event_->jetEtaMean[0]);
      hJetPhiMean_->Fill(event_->jetPhiMean[0]);
      hJetEtaEtaMoment_->Fill(event_->jetEtaetaMoment[0]);
      hJetEtaPhiMoment_->Fill(event_->jetPhiphiMoment[0]);
      hJetPhiPhiMoment_->Fill(event_->jetEtaphiMoment[0]);
    }

    // For events with halo segments in 3+ layers, we want to determine
    // which of the incoming/outgoing legs are detected
    // NOTE: if you remove this requirement, be sure to replace hasMatchingPhi!
    bool threepluslayers = nLayers.size() >= 3; 

    // Fill histograms showing eta distribution of incoming, outgoing, and both
    // halo "tracks". 
    if (searchSample && threepluslayers && hasMatchingPhi) {

      // The jet is associated with halo i.e. this event shows halo contamination
      hHaloJetEtaMean_->Fill(event_->jetEtaMean[0]);
      hHaloJetPhiMean_->Fill(event_->jetPhiMean[0]);
      hHaloJetEtaEtaMoment_->Fill(event_->jetEtaetaMoment[0]);
      hHaloJetEtaPhiMoment_->Fill(event_->jetPhiphiMoment[0]);
      hHaloJetPhiPhiMoment_->Fill(event_->jetEtaphiMoment[0]);

      if (nIncoming > 0 && nOutgoing == 0) {        //Incoming only
	hIncomingEta_->Fill(jeteta);
	hIncomingE_->Fill(jete);
	hIncomingR_->Fill(eventR);
	hIncomingPhi_->Fill(eventPhi);
	hIncomingRPhi_->Fill(eventR,eventPhi);
	if (haloDirection < 0) {  // Beam 2
	  hIncomingJetEta2_->Fill(jeteta);
	  hIncomingRPhi2_->Fill(eventR,eventPhi);
	  hIncomingXY2_->Fill(eventX,eventY);
	}
	if (haloDirection >= 0) { // Beam 1
	  hIncomingJetEta1_->Fill(jeteta);
	  hIncomingXY1_->Fill(eventX,eventY);
	  hIncomingRPhi1_->Fill(eventR,eventPhi);
	}
      } else if (nIncoming == 0 && nOutgoing > 0) { // Outgoing only
	hOutgoingEta_->Fill(jeteta);
	hOutgoingE_->Fill(jete);
	hOutgoingR_->Fill(eventR);
	hOutgoingPhi_->Fill(eventPhi);
	hOutgoingRPhi_->Fill(eventR,eventPhi);
	if (haloDirection < 0) {  // Beam 2
	  hOutgoingJetEta2_->Fill(jeteta);
	  hOutgoingRPhi2_->Fill(eventR,eventPhi);
	  hOutgoingXY2_->Fill(eventX,eventY);
	}
	if (haloDirection >= 0) { // Beam 1
	  hOutgoingJetEta1_->Fill(jeteta);
	  hOutgoingRPhi1_->Fill(eventR,eventPhi);
	  hOutgoingXY1_->Fill(eventX,eventY);
	}
      } else if (nIncoming > 0 && nOutgoing > 0) {  // Both
	hBothEta_->Fill(jeteta);
	hBothE_->Fill(jete);
	hBothR_->Fill(eventR);
	hBothPhi_->Fill(eventPhi);
	hBothRPhi_->Fill(eventR,eventPhi);
	if (haloDirection < 0) {  // Beam 2
	  hBothJetEta2_->Fill(jeteta);
	  hBothRPhi2_->Fill(eventR,eventPhi);
	  hBothXY2_->Fill(eventX,eventY);
	}
	if (haloDirection >= 0) { // Beam 1
	  hBothJetEta1_->Fill(jeteta);
	  hBothRPhi1_->Fill(eventR,eventPhi);
	  hBothXY1_->Fill(eventX,eventY);
	}
      } 
      if (nIncoming > 0 || nOutgoing > 0) {  // N
	if (haloDirection < 0) {  // Beam 2
	  hnRPhi2_->Fill(eventR,eventPhi);
	  hnXY2_->Fill(eventX,eventY);
	}
	if (haloDirection >= 0) { // Beam 1
	  hnRPhi1_->Fill(eventR,eventPhi);
	  hnXY1_->Fill(eventX,eventY);
	}
      }
    }

    // Need eta distribution of halo events that pass all other cuts for final background count
    //std::vector<unsigned> minuscuts = {4,5};
    //if (cuts_.cutNMinusSome(minuscuts) && event_->cscSeg_N > 0) {
    //if (cuts_.cutNMinusOne(4) && event_->cscSeg_N > 0) {
    if (cuts_.cutNMinusOne(4) && !cuts_.cutN(4)) {
      hMinusOneHaloEta_->Fill(jeteta);
      hMinusOneCscSegments_->Fill(event_->cscSeg_N);
      hMinusOneHaloR_->Fill(eventR);
      hMinusOneHaloPhi_->Fill(eventPhi);
      hMinusOneHaloRPhi_->Fill(eventR,eventPhi);
      if (haloDirection < 0) {  // Beam 2
	hMinusOneHaloJetEta2_->Fill(jeteta);
	hMinusOneHaloRPhi2_->Fill(eventR,eventPhi);
	hMinusOneHaloXY2_->Fill(eventX,eventY);
      }
      if (haloDirection >= 0) { // Beam 1
	hMinusOneHaloJetEta1_->Fill(jeteta);
	hMinusOneHaloRPhi1_->Fill(eventR,eventPhi);
	hMinusOneHaloXY1_->Fill(eventX,eventY);
      }
    }

    if (cuts_.cut()) {
      hSelectedJetPhi_->Fill(event_->jetPhi[0]);
    }
    
  } // END EVENT LOOP

  // TODO: Encorporate sideband subtraction into results
  // calculate the fraction of contamination in the signal region via sideband subtraction to remove 
  // N_bkg,sig = (N_low + N_high)/2 * (width_sig/width_bkg)
  double minusSideband = hDphi_->Integral(hDphi_->FindBin(-0.9),hDphi_->FindBin(-0.5));
  double plusSideband = hDphi_->Integral(hDphi_->FindBin(0.5),hDphi_->FindBin(0.9));
  double sidebandN = (minusSideband + plusSideband)/2.0;
  double signalN = hDphi_->Integral(hDphi_->FindBin(-0.4),hDphi_->FindBin(0.4));
  dumpFile_ <<std::endl << "Data for sideband subrtraction for uncorrelated CSCSegments...(not used yet)" 
	    << std::endl;
  dumpFile_ << "minus \t plus \t avg \t sig \t fraction" <<std::endl;
  dumpFile_ << minusSideband << "\t" << plusSideband <<"\t" << sidebandN << "\t"
	    << signalN << "\t" << (signalN - sidebandN)/signalN
	    << std::endl;

    
  // Finish Fedor's second method by calculating inefficiency by eta bin
  dumpFile_ << std::endl << "Halo estimate - using original jetEta" <<std::endl;
  hIncomingEta_->Sumw2();
  hOutgoingEta_->Sumw2();
  hBothEta_->Sumw2();
  hIneffNum_->Multiply(hIncomingEta_, hOutgoingEta_, 1., 1.);
  hIneffDen_->Multiply(hBothEta_, hBothEta_, 1., 1.);
  hIneffNum_->Sumw2();
  hIneffDen_->Sumw2();
  hIneffEta_->Divide(hIneffNum_, hIneffDen_, 1., 1.);
  hIneffEta_->Sumw2();
  hIneffEta2_->Multiply(hIneffEta_, hMinusOneHaloEta_, 1., 1.);

  /**
  double n_inc = hIncomingEta_->GetEntries();
  double n_out = hOutgoingEta_->GetEntries();
  double n_both = hBothEta_->GetEntries();
  double eps = n_inc*n_out/(n_both*n_both);
  double eps_err = eps*sqrt(1./n_inc + 1./n_out + 4./n_both);
  dumpFile_<<  "";
  //dumpFile_<<  "Events vetoed by delta-phi &/ 3+ layer requirement: " << nLayerVeto << std::endl;
  dumpFile_<<  "" << std::endl;
  dumpFile_<<  "       N_incoming * N_outgoing      " << n_inc << " * " << n_out << std::endl;
  dumpFile_<<  " eps = -----------------------  =  ---------------- " << std::endl;
  dumpFile_<<  "               N_both^2               (" << n_both << ")^2" << std::endl;
  dumpFile_<<  "" << std::endl;
  dumpFile_<<  " eps = " <<eps<< " +/- " << eps_err << std::endl;
  dumpFile_<<  " N_haloEvents = " << hMinusOneHaloEta_->Integral() << std::endl;
  dumpFile_<<  "" << std::endl;
  Double_t error = 0;
  Double_t integ = hIneffEta2_->IntegralAndError(1,hIneffEta2_->GetNbinsX(),error);
  dumpFile_<<  " background = " << integ << " +/- " << error << std::endl;
  dumpFile_<< std::endl 
	   << "----------------------------------------------------------------"
	   << std::endl;

  // Finish halo estimate using average radius of CSCSegments
  dumpFile_ << std::endl << "Halo estimate - using average CSCSegment radius" <<std::endl;
  hIncomingR_->Sumw2();
  hOutgoingR_->Sumw2();
  hBothR_->Sumw2();
  hIneffNumR_->Multiply(hIncomingR_, hOutgoingR_, 1., 1.);
  hIneffDenR_->Multiply(hBothR_, hBothR_, 1., 1.);
  hIneffNumR_->Sumw2();
  hIneffDenR_->Sumw2();
  hIneffFractionR_->Divide(hIneffNumR_, hIneffDenR_, 1., 1.);
  hIneffFractionR_->Sumw2();
  hIneffCountR_->Multiply(hIneffFractionR_, hMinusOneHaloR_, 1., 1.);

  double n_incR   = hIncomingR_->GetEntries();
  double n_outR   = hOutgoingR_->GetEntries();
  double n_bothR  = hBothR_->GetEntries();
  double epsR     = n_incR*n_outR/(n_bothR*n_bothR);
  double eps_errR = epsR*sqrt(1./n_incR + 1./n_outR + 4./n_bothR);
  dumpFile_<<  "";
  dumpFile_<<  "" << std::endl;
  dumpFile_<<  "       N_incoming * N_outgoing      " << n_incR << " * " << n_outR << std::endl;
  dumpFile_<<  " eps = -----------------------  =  ---------------- " << std::endl;
  dumpFile_<<  "               N_both^2               (" << n_bothR << ")^2" << std::endl;
  dumpFile_<<  "" << std::endl;
  dumpFile_<<  " eps = " << epsR << " +/- " << eps_errR << std::endl;
  dumpFile_<<  " N_haloEvents = " << hMinusOneHaloR_->Integral() << std::endl;
  dumpFile_<<  "" << std::endl;
  Double_t errorR = 0;
  Double_t integR = hIneffCountR_->IntegralAndError(1,hIneffCountR_->GetNbinsX(),errorR);
  dumpFile_<<  " background = " << integR << " +/- " << errorR << std::endl;
  dumpFile_<< std::endl 
	   << "----------------------------------------------------------------"
	   << std::endl;


  // Finish halo estimate using average phi of CSCSegments
  dumpFile_ << std::endl << "Halo estimate - using average CSCSegment phi" <<std::endl;
  hIncomingPhi_->Sumw2();
  hOutgoingPhi_->Sumw2();
  hBothPhi_->Sumw2();
  hIneffNumPhi_->Multiply(hIncomingPhi_, hOutgoingPhi_, 1., 1.);
  hIneffDenPhi_->Multiply(hBothPhi_, hBothPhi_, 1., 1.);
  hIneffNumPhi_->Sumw2();
  hIneffDenPhi_->Sumw2();
  hIneffFractionPhi_->Divide(hIneffNumPhi_, hIneffDenPhi_, 1., 1.);
  hIneffFractionPhi_->Sumw2();
  hIneffCountPhi_->Multiply(hIneffFractionPhi_, hMinusOneHaloPhi_, 1., 1.);

  double n_incPhi   = hIncomingPhi_->GetEntries();
  double n_outPhi   = hOutgoingPhi_->GetEntries();
  double n_bothPhi  = hBothPhi_->GetEntries();
  double epsPhi     = n_incPhi*n_outPhi/(n_bothPhi*n_bothPhi);
  double eps_errPhi = epsPhi*sqrt(1./n_incPhi + 1./n_outPhi + 4./n_bothPhi);
  dumpFile_<<  "";
  dumpFile_<<  "" << std::endl;
  dumpFile_<<  "       N_incoming * N_outgoing      " << n_incPhi << " * " << n_outPhi << std::endl;
  dumpFile_<<  " eps = -----------------------  =  ---------------- " << std::endl;
  dumpFile_<<  "               N_both^2               (" << n_bothPhi << ")^2" << std::endl;
  dumpFile_<<  "" << std::endl;
  dumpFile_<<  " eps = " << epsPhi << " +/- " << eps_errPhi << std::endl;
  dumpFile_<<  " N_haloEvents = " << hMinusOneHaloPhi_->Integral() << std::endl;
  dumpFile_<<  "" << std::endl;
  Double_t errorPhi = 0;
  Double_t integPhi = hIneffCountPhi_->IntegralAndError(1,hIneffCountPhi_->GetNbinsX(),errorPhi);
  dumpFile_<<  " background = " << integPhi << " +/- " << errorPhi << std::endl;
  dumpFile_<< std::endl 
	   << "----------------------------------------------------------------"
	   << std::endl;

  // Finish halo estimate using average radius & phi of CSCSegments
  dumpFile_ << std::endl << "Halo estimate - using average CSCSegment radius & phi" <<std::endl;
  hIncomingRPhi_->Sumw2();
  hOutgoingRPhi_->Sumw2();
  hBothRPhi_->Sumw2();
  hIneffNumRPhi_->Multiply(hIncomingRPhi_, hOutgoingRPhi_, 1., 1.);
  hIneffDenRPhi_->Multiply(hBothRPhi_, hBothRPhi_, 1., 1.);
  hIneffNumRPhi_->Sumw2();
  hIneffDenRPhi_->Sumw2();
  hIneffFractionRPhi_->Divide(hIneffNumRPhi_, hIneffDenRPhi_, 1., 1.);
  hIneffFractionRPhi_->Sumw2();
  hIneffCountRPhi_->Multiply(hIneffFractionRPhi_, hMinusOneHaloRPhi_, 1., 1.);

  double n_incRPhi   = hIncomingRPhi_->GetEntries();
  double n_outRPhi   = hOutgoingRPhi_->GetEntries();
  double n_bothRPhi  = hBothRPhi_->GetEntries();
  double epsRPhi     = n_incRPhi*n_outRPhi/(n_bothRPhi*n_bothRPhi);
  double eps_errRPhi = epsRPhi*sqrt(1./n_incRPhi + 1./n_outRPhi + 4./n_bothRPhi);
  dumpFile_<<  "";
  dumpFile_<<  "" << std::endl;
  dumpFile_<<  "       N_incoming * N_outgoing      " << n_incRPhi << " * " << n_outRPhi << std::endl;
  dumpFile_<<  " eps = -----------------------  =  ---------------- " << std::endl;
  dumpFile_<<  "               N_both^2               (" << n_bothRPhi << ")^2" << std::endl;
  dumpFile_<<  "" << std::endl;
  dumpFile_<<  " eps = " << epsRPhi << " +/- " << eps_errRPhi << std::endl;
  dumpFile_<<  " N_haloEvents = " << hMinusOneHaloRPhi_->Integral() << std::endl;
  dumpFile_<<  "" << std::endl;
  Double_t errorRPhi = 0;
  Double_t integRPhi = hIneffCountRPhi_->IntegralAndError(1,hIneffCountRPhi_->GetNbinsX(),
							  1,hIneffCountRPhi_->GetNbinsY(),
							  errorRPhi);
  dumpFile_<<  " background = " << integRPhi << " +/- " << errorRPhi << std::endl;
  */



  /******************* Now with beams 1+2 separated *****************/
  

  /**
  dumpFile_<< std::endl 
	   << "****************************************************************"
	   << std::endl;

  // Finish halo estimate using average radius & phi of CSCSegments - beam 1
  dumpFile_ << std::endl << "Halo estimate - using jetEta[0] - beam 1" 
	    << std::endl;
  hIncomingJetEta1_->Sumw2();
  hOutgoingJetEta1_->Sumw2();
  hBothJetEta1_->Sumw2();
  hIneffNumJetEta1_->Multiply(hIncomingJetEta1_, hOutgoingJetEta1_, 1., 1.);
  hIneffDenJetEta1_->Multiply(hBothJetEta1_, hBothJetEta1_, 1., 1.);
  hIneffNumJetEta1_->Sumw2();
  hIneffDenJetEta1_->Sumw2();
  hIneffFractionJetEta1_->Divide(hIneffNumJetEta1_, hIneffDenJetEta1_, 1., 1.);
  hIneffFractionJetEta1_->Sumw2();
  hIneffCountJetEta1_->Multiply(hIneffFractionJetEta1_, hMinusOneHaloJetEta1_, 1., 1.);

  double n_incJetEta1   = hIncomingJetEta1_->GetEntries();
  double n_outJetEta1   = hOutgoingJetEta1_->GetEntries();
  double n_bothJetEta1  = hBothJetEta1_->GetEntries();
  double epsJetEta1     = n_incJetEta1*n_outJetEta1/(n_bothJetEta1*n_bothJetEta1);
  double eps_errJetEta1 = epsJetEta1*sqrt(1./n_incJetEta1 + 1./n_outJetEta1 + 4./n_bothJetEta1);
  dumpFile_<<  "";
  dumpFile_<<  "" << std::endl;
  dumpFile_<<  "       N_incoming * N_outgoing      " 
	   << n_incJetEta1 << " * " << n_outJetEta1 
	   << std::endl;
  dumpFile_<<  " eps = -----------------------  =  ---------------- " << std::endl;
  dumpFile_<<  "               N_both^2               (" << n_bothJetEta1 << ")^2" << std::endl;
  dumpFile_<<  "" << std::endl;
  dumpFile_<<  " eps = " << epsJetEta1 << " +/- " << eps_errJetEta1 << std::endl;
  dumpFile_<<  " N_haloEvents = " << hMinusOneHaloJetEta1_->Integral() << std::endl;
  dumpFile_<<  "" << std::endl;
  Double_t errorJetEta1 = 0;
  Double_t integJetEta1 = hIneffCountJetEta1_->IntegralAndError(1,hIneffCountJetEta1_->GetNbinsX(),
								errorJetEta1);
  dumpFile_<<  " background = " << integJetEta1 << " +/- " << errorJetEta1 << std::endl;
  dumpFile_<< std::endl 
	   << "----------------------------------------------------------------"
	   << std::endl;

  // Finish halo estimate using average radius & phi of CSCSegments - beam 2
  dumpFile_ << std::endl << "Halo estimate - using jetEta[0] - beam 2" 
	    << std::endl;
  hIncomingJetEta2_->Sumw2();
  hOutgoingJetEta2_->Sumw2();
  hBothJetEta2_->Sumw2();
  hIneffNumJetEta2_->Multiply(hIncomingJetEta2_, hOutgoingJetEta2_, 1., 1.);
  hIneffDenJetEta2_->Multiply(hBothJetEta2_, hBothJetEta2_, 1., 1.);
  hIneffNumJetEta2_->Sumw2();
  hIneffDenJetEta2_->Sumw2();
  hIneffFractionJetEta2_->Divide(hIneffNumJetEta2_, hIneffDenJetEta2_, 1., 1.);
  hIneffFractionJetEta2_->Sumw2();
  hIneffCountJetEta2_->Multiply(hIneffFractionJetEta2_, hMinusOneHaloJetEta2_, 1., 1.);

  double n_incJetEta2   = hIncomingJetEta2_->GetEntries();
  double n_outJetEta2   = hOutgoingJetEta2_->GetEntries();
  double n_bothJetEta2  = hBothJetEta2_->GetEntries();
  double epsJetEta2     = n_incJetEta2*n_outJetEta2/(n_bothJetEta2*n_bothJetEta2);
  double eps_errJetEta2 = epsJetEta2*sqrt(1./n_incJetEta2 + 1./n_outJetEta2 + 4./n_bothJetEta2);
  dumpFile_<<  "";
  dumpFile_<<  "" << std::endl;
  dumpFile_<<  "       N_incoming * N_outgoing      " << n_incJetEta2 << " * " << n_outJetEta2 << std::endl;
  dumpFile_<<  " eps = -----------------------  =  ---------------- " << std::endl;
  dumpFile_<<  "               N_both^2               (" << n_bothJetEta2 << ")^2" << std::endl;
  dumpFile_<<  "" << std::endl;
  dumpFile_<<  " eps = " << epsJetEta2 << " +/- " << eps_errJetEta2 << std::endl;
  dumpFile_<<  " N_haloEvents = " << hMinusOneHaloJetEta2_->Integral() << std::endl;
  dumpFile_<<  "" << std::endl;
  Double_t errorJetEta2 = 0;
  Double_t integJetEta2 = hIneffCountJetEta2_->IntegralAndError(1,hIneffCountJetEta2_->GetNbinsX(),
								errorJetEta2);
  dumpFile_<<  " background = " << integJetEta2 << " +/- " << errorJetEta2 << std::endl;
  dumpFile_<< std::endl 
	   << "----------------------------------------------------------------"
	   << std::endl;
  */
  // Finish halo estimate using average radius & phi of CSCSegments - beam 1
  dumpFile_ << std::endl << "Halo estimate - using average CSCSegment radius & phi - beam 1" 
	    << std::endl;
  hIncomingRPhi1_->Sumw2();
  hOutgoingRPhi1_->Sumw2();
  hBothRPhi1_->Sumw2();
  hnRPhi1_->Sumw2();
  hIneffNumRPhi1_->Multiply(hIncomingRPhi1_, hOutgoingRPhi1_, 1., 1.);
  hIneffDenRPhi1_->Multiply(hBothRPhi1_, hnRPhi1_, 1., 1.);
  hIneffNumRPhi1_->Sumw2();
  hIneffDenRPhi1_->Sumw2();
  hIneffFractionRPhi1_->Divide(hIneffNumRPhi1_, hIneffDenRPhi1_, 1., 1.);
  hIneffFractionRPhi1_->Sumw2();
  hIneffCountRPhi1_->Multiply(hIneffFractionRPhi1_, hMinusOneHaloRPhi1_, 1., 1.);

  double n_incRPhi1   = hIncomingRPhi1_->GetEntries();
  double n_outRPhi1   = hOutgoingRPhi1_->GetEntries();
  double n_bothRPhi1  = hBothRPhi1_->GetEntries();
  double n_RPhi1  = hnRPhi1_->GetEntries();
  double epsRPhi1     = n_incRPhi1*n_outRPhi1/(n_bothRPhi1*n_RPhi1);
  double eps_errRPhi1 = epsRPhi1*sqrt(1./n_incRPhi1 + 1./n_outRPhi1 + 4./n_bothRPhi1);
  dumpFile_<<  "";
  dumpFile_<<  "" << std::endl;
  dumpFile_<<  "       N_incoming * N_outgoing      " << n_incRPhi1 << " * " << n_outRPhi1 << std::endl;
  dumpFile_<<  " eps = -----------------------  =  ---------------- " << std::endl;
  dumpFile_<<  "               N_both*N            (" << n_bothRPhi1 << "*" << n_RPhi1 << ")" << std::endl;
  dumpFile_<<  "" << std::endl;
  dumpFile_<<  " eps = " << epsRPhi1 << " +/- " << eps_errRPhi1 << std::endl;
  dumpFile_<<  " N_haloEvents = " << hMinusOneHaloRPhi1_->Integral() << std::endl;
  dumpFile_<<  "" << std::endl;
  Double_t errorRPhi1 = 0;
  Double_t integRPhi1 = hIneffCountRPhi1_->IntegralAndError(1,hIneffCountRPhi1_->GetNbinsX(),
							    1,hIneffCountRPhi1_->GetNbinsY(),
							    errorRPhi1);
  dumpFile_<<  " background = " << integRPhi1 << " +/- " << errorRPhi1 << std::endl;
  dumpFile_<< std::endl 
	   << "----------------------------------------------------------------"
	   << std::endl;

  // Finish halo estimate using average radius & phi of CSCSegments - beam 2
  dumpFile_ << std::endl << "Halo estimate - using average CSCSegment radius & phi - beam 2" 
	    << std::endl;
  hIncomingRPhi2_->Sumw2();
  hOutgoingRPhi2_->Sumw2();
  hBothRPhi2_->Sumw2();
  hnRPhi2_->Sumw2();
  hIneffNumRPhi2_->Multiply(hIncomingRPhi2_, hOutgoingRPhi2_, 1., 1.);
  hIneffDenRPhi2_->Multiply(hBothRPhi2_, hBothRPhi2_, 1., 1.);
  hIneffNumRPhi2_->Sumw2();
  hIneffDenRPhi2_->Sumw2();
  hIneffFractionRPhi2_->Divide(hIneffNumRPhi2_, hIneffDenRPhi2_, 1., 1.);
  hIneffFractionRPhi2_->Sumw2();
  hIneffCountRPhi2_->Multiply(hIneffFractionRPhi2_, hMinusOneHaloRPhi2_, 1., 1.);

  double n_incRPhi2   = hIncomingRPhi2_->GetEntries();
  double n_outRPhi2   = hOutgoingRPhi2_->GetEntries();
  double n_bothRPhi2  = hBothRPhi2_->GetEntries();
  double n_RPhi2  = hnRPhi2_->GetEntries();
  double epsRPhi2     = n_incRPhi2*n_outRPhi2/(n_bothRPhi2*n_RPhi2);
  double eps_errRPhi2 = epsRPhi2*sqrt(1./n_incRPhi2 + 1./n_outRPhi2 + 4./n_bothRPhi2);
  dumpFile_<<  "";
  dumpFile_<<  "" << std::endl;
  dumpFile_<<  "       N_incoming * N_outgoing      " << n_incRPhi2 << " * " << n_outRPhi2 << std::endl;
  dumpFile_<<  " eps = -----------------------  =  ---------------- " << std::endl;
  dumpFile_<<  "               N_both*N            (" << n_bothRPhi2 << "*" << n_RPhi2 <<")" << std::endl;
  dumpFile_<<  "" << std::endl;
  dumpFile_<<  " eps = " << epsRPhi2 << " +/- " << eps_errRPhi2 << std::endl;
  dumpFile_<<  " N_haloEvents = " << hMinusOneHaloRPhi2_->Integral() << std::endl;
  dumpFile_<<  "" << std::endl;
  Double_t errorRPhi2 = 0;
  Double_t integRPhi2 = hIneffCountRPhi2_->IntegralAndError(1,hIneffCountRPhi2_->GetNbinsX(),
							    1,hIneffCountRPhi2_->GetNbinsY(),
							    errorRPhi2);
  dumpFile_<<  " background = " << integRPhi2 << " +/- " << errorRPhi2 << std::endl;
  dumpFile_<< std::endl 
	   << "----------------------------------------------------------------"
	   << std::endl;


  // Finish halo estimate using average x-y of CSCSegments - beam 1
  dumpFile_ << std::endl << "Halo estimate - using average CSCSegment x-y - beam 1" 
	    << std::endl;
  hIncomingXY1_->Sumw2();
  hOutgoingXY1_->Sumw2();
  hBothXY1_->Sumw2();
  hnXY1_->Sumw2();
  hIneffNumXY1_->Multiply(hIncomingXY1_, hOutgoingXY1_, 1., 1.);
  hIneffDenXY1_->Multiply(hBothXY1_, hnXY1_, 1., 1.);
  hIneffNumXY1_->Sumw2();
  hIneffDenXY1_->Sumw2();
  hIneffFractionXY1_->Divide(hIneffNumXY1_, hIneffDenXY1_, 1., 1.);
  hIneffFractionXY1_->Sumw2();
  hIneffCountXY1_->Multiply(hIneffFractionXY1_, hMinusOneHaloXY1_, 1., 1.);

  double n_incXY1   = hIncomingXY1_->GetEntries();
  double n_outXY1   = hOutgoingXY1_->GetEntries();
  double n_bothXY1  = hBothXY1_->GetEntries();
  double n_XY1 = hnXY1_->GetEntries();
  double epsXY1     = n_incXY1*n_outXY1/(n_bothXY1*n_XY1);
  double eps_errXY1 = epsXY1*sqrt(1./n_incXY1 + 1./n_outXY1 + 4./n_bothXY1);
  dumpFile_<<  "";
  dumpFile_<<  "" << std::endl;
  dumpFile_<<  "       N_incoming * N_outgoing      " << n_incXY1 << " * " << n_outXY1 << std::endl;
  dumpFile_<<  " eps = -----------------------  =  ---------------- " << std::endl;
  dumpFile_<<  "               N_both*N               (" << n_bothXY1 <<  " * " << n_XY1 << ")" << std::endl;
  dumpFile_<<  "" << std::endl;
  dumpFile_<<  " eps = " << epsXY1 << " +/- " << eps_errXY1 << std::endl;
  dumpFile_<<  " N_haloEvents = " << hMinusOneHaloXY1_->Integral() << std::endl;
  dumpFile_<<  "" << std::endl;
  Double_t errorXY1 = 0;
  Double_t integXY1 = hIneffCountXY1_->IntegralAndError(1,hIneffCountXY1_->GetNbinsX(),
							    1,hIneffCountXY1_->GetNbinsY(),
							    errorXY1);
  dumpFile_<<  " background = " << integXY1 << " +/- " << errorXY1 << std::endl;
  dumpFile_<< std::endl 
	   << "----------------------------------------------------------------"
	   << std::endl;

  // Finish halo estimate using average x-y CSCSegments - beam 2
  dumpFile_ << std::endl << "Halo estimate - using average CSCSegment x-y - beam 2" 
	    << std::endl;
  hIncomingXY2_->Sumw2();
  hOutgoingXY2_->Sumw2();
  hBothXY2_->Sumw2();
  hnXY2_->Sumw2();
  hIneffNumXY2_->Multiply(hIncomingXY2_, hOutgoingXY2_, 1., 1.);
  hIneffDenXY2_->Multiply(hBothXY2_, hnXY2_, 1., 1.);
  hIneffNumXY2_->Sumw2();
  hIneffDenXY2_->Sumw2();
  hIneffFractionXY2_->Divide(hIneffNumXY2_, hIneffDenXY2_, 1., 1.);
  hIneffFractionXY2_->Sumw2();
  hIneffCountXY2_->Multiply(hIneffFractionXY2_, hMinusOneHaloXY2_, 1., 1.);

  double n_incXY2   = hIncomingXY2_->GetEntries();
  double n_outXY2   = hOutgoingXY2_->GetEntries();
  double n_bothXY2  = hBothXY2_->GetEntries();
  double n_XY2 = hnXY2_->GetEntries();
  double epsXY2     = n_incXY2*n_outXY2/(n_bothXY2*n_XY2);
  double eps_errXY2 = epsXY2*sqrt(1./n_incXY2 + 1./n_outXY2 + 4./n_bothXY2);
  dumpFile_<<  "";
  dumpFile_<<  "" << std::endl;
  dumpFile_<<  "       N_incoming * N_outgoing      " << n_incXY2 << " * " << n_outXY2 << std::endl;
  dumpFile_<<  " eps = -----------------------  =  ---------------- " << std::endl;
  dumpFile_<<  "               N_both*N               (" << n_bothXY2 << " * " << n_XY2 << ")" << std::endl;
  dumpFile_<<  "" << std::endl;
  dumpFile_<<  " eps = " << epsXY2 << " +/- " << eps_errXY2 << std::endl;
  dumpFile_<<  " N_haloEvents = " << hMinusOneHaloXY2_->Integral() << std::endl;
  dumpFile_<<  "" << std::endl;
  Double_t errorXY2 = 0;
  Double_t integXY2 = hIneffCountXY2_->IntegralAndError(1,hIneffCountXY2_->GetNbinsX(),
							    1,hIneffCountXY2_->GetNbinsY(),
							    errorXY2);
  dumpFile_<<  " background = " << integXY2 << " +/- " << errorXY2 << std::endl;
  dumpFile_<< std::endl 
	   << "----------------------------------------------------------------"
	   << std::endl;
  
  dumpFile_<<  " Final = " << integXY2+integXY1 << " +/- " << sqrt(errorXY2*errorXY2+errorXY1*errorXY1)
	   << " +/- " << fabs(integXY2+integXY1-integRPhi2-integRPhi1)
	   << std::endl;

  dumpFile_<< std::endl 
	   << "----------------------------------------------------------------"
	   << std::endl;
  

  

  // SAVE HISTOGRAMS HERE
  ofile_->cd();
  hDphi_->Write("",TObject::kOverwrite);
  hAverageDphi_->Write("",TObject::kOverwrite);
  hHaloPlusZEta_->Write("",TObject::kOverwrite);
  hHaloMinusZEta_->Write("",TObject::kOverwrite);
  hSegmentLayer_->Write("",TObject::kOverwrite);
  hSegmentDirection_->Write("",TObject::kOverwrite);
  hSelectedJetPhi_->Write("",TObject::kOverwrite);
  hSegmentLayersVRadius_->Write("",TObject::kOverwrite);
  hSegmentLayersVPhi_->Write("",TObject::kOverwrite);

  // CSCSegment studies
  hSegmentTime_->Write("",TObject::kOverwrite);
  hSegmentR_->Write("",TObject::kOverwrite);
  hSegmentZ_->Write("",TObject::kOverwrite);
  hMinusOneCscSegments_->Write("",TObject::kOverwrite);

  hSegmentZR_->Write("",TObject::kOverwrite);
  hSegmentEtaR_->Write("",TObject::kOverwrite);
  hSegmentZTime_->Write("",TObject::kOverwrite);
  hSegmentRPhi_->Write("",TObject::kOverwrite);
  hSegmentXY_->Write("",TObject::kOverwrite);
  hSegmentXYzoom_->Write("",TObject::kOverwrite);
  hSegmentThetaDir_->Write("",TObject::kOverwrite);

  // jet stuff
  hJetEtaMean_->Write("",TObject::kOverwrite);
  hJetPhiMean_->Write("",TObject::kOverwrite);
  hJetEtaEtaMoment_->Write("",TObject::kOverwrite);
  hJetEtaPhiMoment_->Write("",TObject::kOverwrite);
  hJetPhiPhiMoment_->Write("",TObject::kOverwrite);
  hHaloJetEtaMean_->Write("",TObject::kOverwrite);
  hHaloJetPhiMean_->Write("",TObject::kOverwrite);
  hHaloJetEtaEtaMoment_->Write("",TObject::kOverwrite);
  hHaloJetEtaPhiMoment_->Write("",TObject::kOverwrite);
  hHaloJetPhiPhiMoment_->Write("",TObject::kOverwrite);




  /******* Estimates separated out by beam 1 and beam 2 *******/

  // Calculate inefficiency binned by jetEta[0] - beam 1
  hIncomingJetEta1_->Write("",TObject::kOverwrite);
  hOutgoingJetEta1_->Write("",TObject::kOverwrite);
  hBothJetEta1_->Write("",TObject::kOverwrite);
  hIneffNumJetEta1_->Write("",TObject::kOverwrite);
  hIneffDenJetEta1_->Write("",TObject::kOverwrite);
  hIneffFractionJetEta1_->Write("",TObject::kOverwrite);
  hIneffCountJetEta1_->Write("",TObject::kOverwrite);
  hMinusOneHaloJetEta1_->Write("",TObject::kOverwrite);
  
  // Calculate inefficiency binned by jetEta[0] - beam 2
  hIncomingJetEta2_->Write("",TObject::kOverwrite);
  hOutgoingJetEta2_->Write("",TObject::kOverwrite);
  hBothJetEta2_->Write("",TObject::kOverwrite);
  hIneffNumJetEta2_->Write("",TObject::kOverwrite);
  hIneffDenJetEta2_->Write("",TObject::kOverwrite);
  hIneffFractionJetEta2_->Write("",TObject::kOverwrite);
  hIneffCountJetEta2_->Write("",TObject::kOverwrite);
  hMinusOneHaloJetEta2_->Write("",TObject::kOverwrite);
  
  // Calculate inefficiency binned by CSCSegmentR and CSCSegmentPhi (avg) - beam 1
  hAverageRPhi1_->Write("",TObject::kOverwrite);
  hAverageErrRPhi1_->Write("",TObject::kOverwrite);
  hIncomingRPhi1_->Write("",TObject::kOverwrite);
  hOutgoingRPhi1_->Write("",TObject::kOverwrite);
  hBothRPhi1_->Write("",TObject::kOverwrite);
  hIneffNumRPhi1_->Write("",TObject::kOverwrite);
  hIneffDenRPhi1_->Write("",TObject::kOverwrite);
  hIneffFractionRPhi1_->Write("",TObject::kOverwrite);
  hIneffCountRPhi1_->Write("",TObject::kOverwrite);
  hMinusOneHaloRPhi1_->Write("",TObject::kOverwrite);
  
  // Calculate inefficiency binned by CSCSegmentR and CSCSegmentPhi (avg) - beam2
  hAverageRPhi2_->Write("",TObject::kOverwrite);
  hAverageErrRPhi2_->Write("",TObject::kOverwrite);
  hIncomingRPhi2_->Write("",TObject::kOverwrite);
  hOutgoingRPhi2_->Write("",TObject::kOverwrite);
  hBothRPhi2_->Write("",TObject::kOverwrite);
  hIneffNumRPhi2_->Write("",TObject::kOverwrite);
  hIneffDenRPhi2_->Write("",TObject::kOverwrite);
  hIneffFractionRPhi2_->Write("",TObject::kOverwrite);
  hIneffCountRPhi2_->Write("",TObject::kOverwrite);
  hMinusOneHaloRPhi2_->Write("",TObject::kOverwrite);

  // Calculate inefficiency binned by CSCSegmentXY (avg) - beam 1
  hAverageXY1_->Write("",TObject::kOverwrite);
  hAverageErrXY1_->Write("",TObject::kOverwrite);
  hIncomingXY1_->Write("",TObject::kOverwrite);
  hOutgoingXY1_->Write("",TObject::kOverwrite);
  hBothXY1_->Write("",TObject::kOverwrite);
  hIneffNumXY1_->Write("",TObject::kOverwrite);
  hIneffDenXY1_->Write("",TObject::kOverwrite);
  hIneffFractionXY1_->Write("",TObject::kOverwrite);
  hIneffCountXY1_->Write("",TObject::kOverwrite);
  hMinusOneHaloXY1_->Write("",TObject::kOverwrite);
  
  // Calculate inefficiency binned by CSCSegmentXY (avg) - beam2
  hAverageXY2_->Write("",TObject::kOverwrite);
  hAverageErrXY2_->Write("",TObject::kOverwrite);
  hIncomingXY2_->Write("",TObject::kOverwrite);
  hOutgoingXY2_->Write("",TObject::kOverwrite);
  hBothXY2_->Write("",TObject::kOverwrite);
  hIneffNumXY2_->Write("",TObject::kOverwrite);
  hIneffDenXY2_->Write("",TObject::kOverwrite);
  hIneffFractionXY2_->Write("",TObject::kOverwrite);
  hIneffCountXY2_->Write("",TObject::kOverwrite);
  hMinusOneHaloXY2_->Write("",TObject::kOverwrite);


  /******* Estimates with beams combined *******/
  // CSC Efficiency - r
  hAverageR_->Write("",TObject::kOverwrite);
  hAverageErrR_->Write("",TObject::kOverwrite);
  hIncomingR_->Write("",TObject::kOverwrite);
  hOutgoingR_->Write("",TObject::kOverwrite);
  hBothR_->Write("",TObject::kOverwrite);
  hIneffNumR_->Write("",TObject::kOverwrite);
  hIneffDenR_->Write("",TObject::kOverwrite);
  hIneffFractionR_->Write("",TObject::kOverwrite);
  hIneffCountR_->Write("",TObject::kOverwrite);
  hMinusOneHaloR_->Write("",TObject::kOverwrite);

  // CSC Efficiency - phi
  hAveragePhi_->Write("",TObject::kOverwrite);
  hAverageErrPhi_->Write("",TObject::kOverwrite);
  hIncomingPhi_->Write("",TObject::kOverwrite);
  hOutgoingPhi_->Write("",TObject::kOverwrite);
  hBothPhi_->Write("",TObject::kOverwrite);
  hIneffNumPhi_->Write("",TObject::kOverwrite);
  hIneffDenPhi_->Write("",TObject::kOverwrite);
  hIneffFractionPhi_->Write("",TObject::kOverwrite);
  hIneffCountPhi_->Write("",TObject::kOverwrite);
  hMinusOneHaloPhi_->Write("",TObject::kOverwrite);

  // CSC Efficiency - r-phi
  hAverageRPhi_->Write("",TObject::kOverwrite);
  hAverageErrRPhi_->Write("",TObject::kOverwrite);
  hIncomingRPhi_->Write("",TObject::kOverwrite);
  hOutgoingRPhi_->Write("",TObject::kOverwrite);
  hBothRPhi_->Write("",TObject::kOverwrite);
  hIneffNumRPhi_->Write("",TObject::kOverwrite);
  hIneffDenRPhi_->Write("",TObject::kOverwrite);
  hIneffFractionRPhi_->Write("",TObject::kOverwrite);
  hIneffCountRPhi_->Write("",TObject::kOverwrite);
  hMinusOneHaloRPhi_->Write("",TObject::kOverwrite);

  // All jets, given eta
  hIncomingEta_->Write("",TObject::kOverwrite);
  hOutgoingEta_->Write("",TObject::kOverwrite);
  hBothEta_->Write("",TObject::kOverwrite);
  hIncomingE_->Write("",TObject::kOverwrite);
  hOutgoingE_->Write("",TObject::kOverwrite);
  hBothE_->Write("",TObject::kOverwrite);
  hIneffNum_->Write("",TObject::kOverwrite);
  hIneffDen_->Write("",TObject::kOverwrite);
  hIneffEta_->Write("",TObject::kOverwrite);
  hIneffEta2_->Write("",TObject::kOverwrite);

  // All jets, sign of jetEta flipped for -z direction halo
  hMinusOneHaloEta_->Write("",TObject::kOverwrite);
  
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
