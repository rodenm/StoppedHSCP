
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

  TH2D* hSegmentZR_;
  TH2D* hSegmentEtaR_;
  TH2D* hSegmentZTime_;
  TH2D* hSegmentRPhi_;
  TH2D* hSegmentXY_;
  TH2D* hSegmentXYzoom_;
  TH2D* hSegmentThetaDir_;

  TH2D* hSegmentLayersVRadius_;
  TH2D* hSegmentLayersVPhi_;

  // Calculate inefficiency binned by CSCSegmentR and CSCSegmentPhi (avg)
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

  /**
  hAverageRPhi_
  hAverageErrRPhi_
  hIncomingRPhi_
  hOutgoingRPhi_
  hBothRPhi_
  hIneffNumRPhi_
  hIneffDenRPhi_
  hIneffFractionRPhi_
  hIneffCountRPhi_
  hMinusOneHaloRPhi_
  */

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

  TH1D* hPaperIncomingEta_;
  TH1D* hPaperOutgoingEta_;
  TH1D* hPaperBothEta_;
  TH1D* hPaperIneffNum_;
  TH1D* hPaperIneffDen_;
  TH1D* hPaperIneffEta_;
  TH1D* hPaperIneffEta2_;
  TH1D* hPaperMinusOneHaloEta_ ;

  TH1D* hMinusOneHaloEta_ ;
  TH1D* hMinusOneCscSegments_;

};

#endif


// this is the event loop
void HaloBackground::loop() {

  // DO ANY SETUP HERE

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
  hPaperIncomingEta_ = new TH1D("hPaperIncomingEta", "", 40, -2.0, 2.0);
  hPaperOutgoingEta_ = new TH1D("hPaperOutgoingEta", "", 40, -2.0, 2.0);
  hPaperBothEta_     = new TH1D("hPaperBothEta", "", 40, -2.0, 2.0);
  hIncomingE_ = new TH1D("hIncomingE", "", 200, 0, 200.0);
  hOutgoingE_ = new TH1D("hOutgoingE", "", 200, 0, 200.0);
  hBothE_     = new TH1D("hBothE", "", 200, 0, 200.0);
  hIneffNum_     = new TH1D("hIneffNum", "", 40, -2.0, 2.0);
  hIneffDen_     = new TH1D("hIneffDen", "", 40, -2.0, 2.0);
  hIneffEta_     = new TH1D("hIneffEta", "", 40, -2.0, 2.0);
  hIneffEta2_     = new TH1D("hIneffEta2", "", 40, -2.0, 2.0);

  hPaperIneffNum_     = new TH1D("hPaperIneffNum", "", 40, -2.0, 2.0);
  hPaperIneffDen_     = new TH1D("hPaperIneffDen", "", 40, -2.0, 2.0);
  hPaperIneffEta_     = new TH1D("hPaperIneffEta", "", 40, -2.0, 2.0);
  hPaperIneffEta2_     = new TH1D("hPaperIneffEta2", "", 40, -2.0, 2.0);
  hMinusOneHaloEta_ = new TH1D("hMinusOneHaloEta", "", 40, -2.0, 2.0);
  hPaperMinusOneHaloEta_ = new TH1D("hPaperMinusOneHaloEta", "", 40, -2.0, 2.0);
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
    bool haloSample = cuts_.triggerCut() && event_->cscSeg_N > 0 && event_->jet_N > 0;
    if (!haloSample) continue;

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
    }

    // For events with halo segments in 3+ layers, we want to determine
    // which of the incoming/outgoing legs are detected
    // NOTE: if you remove this requirement, be sure to replace hasMatchingPhi!
    bool threepluslayers = nLayers.size() >= 3; 

    // Fill histograms showing eta distribution of incoming, outgoing, and both
    // halo "tracks". 
    // Eta is flipped if halo muons are traveling in -Z direction
    // ^ Only for hPaper*Eta plots because otherwise this messed up final N-1 multiplication
    // (from Fig 17 of AN2012_002_v8)
    double jetetaflipped = jeteta;
    if (haloDirection > 0.) jetetaflipped = -jeteta; // +haloDirection == -Z direction
    if (haloSample && threepluslayers && hasMatchingPhi) {
      if (nIncoming > 0 && nOutgoing == 0) {        //Incoming only
	hIncomingEta_->Fill(jeteta);
	hIncomingE_->Fill(jete);
	hPaperIncomingEta_->Fill(jetetaflipped);
	hIncomingR_->Fill(eventR);
	hIncomingPhi_->Fill(eventPhi);
	hIncomingRPhi_->Fill(eventR,eventPhi);
      } else if (nIncoming == 0 && nOutgoing > 0) { // Outgoing only
	hOutgoingEta_->Fill(jeteta);
	hOutgoingE_->Fill(jete);
	hPaperOutgoingEta_->Fill(jetetaflipped);
	hOutgoingR_->Fill(eventR);
	hOutgoingPhi_->Fill(eventPhi);
	hOutgoingRPhi_->Fill(eventR,eventPhi);
      } else if (nIncoming > 0 && nOutgoing > 0) {  // Both
	hBothEta_->Fill(jeteta);
	hBothE_->Fill(jete);
	hPaperBothEta_->Fill(jetetaflipped);
	hBothR_->Fill(eventR);
	hBothPhi_->Fill(eventPhi);
	hBothRPhi_->Fill(eventR,eventPhi);
      } 
    }

    // Need eta distribution of halo events that pass all other cuts for final background count
    //std::vector<unsigned> minuscuts = {4,5};
    //if (cuts_.cutNMinusSome(minuscuts) && event_->cscSeg_N > 0) {
    if (cuts_.cutNMinusOne(4) && event_->cscSeg_N > 0) {
      hMinusOneHaloEta_->Fill(jeteta);
      hPaperMinusOneHaloEta_->Fill(jetetaflipped);
      hMinusOneCscSegments_->Fill(event_->cscSeg_N);
      hMinusOneHaloR_->Fill(eventR);
      hMinusOneHaloPhi_->Fill(eventPhi);
      hMinusOneHaloRPhi_->Fill(eventR,eventPhi);
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
  std::cout <<std::endl << "Data for sideband subrtraction for uncorrelated CSCSegments...(not used yet)" 
	    << std::endl;
  std::cout << "minus \t plus \t avg \t sig \t fraction" <<std::endl;
  std::cout << minusSideband << "\t" << plusSideband <<"\t" << sidebandN << "\t"
	    << signalN << "\t" << (signalN - sidebandN)/signalN
	    << std::endl;

    
  // Finish Fedor's second method by calculating inefficiency by eta bin
  std::cout << std::endl << "Halo estimate - using original jetEta" <<std::endl;
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

  double n_inc = hIncomingEta_->GetEntries();
  double n_out = hOutgoingEta_->GetEntries();
  double n_both = hBothEta_->GetEntries();
  double eps = n_inc*n_out/(n_both*n_both);
  double eps_err = eps*sqrt(1./n_inc + 1./n_out + 4./n_both);
  std::cout<<  "";
  //std::cout<<  "Events vetoed by delta-phi &/ 3+ layer requirement: " << nLayerVeto << std::endl;
  std::cout<<  "" << std::endl;
  std::cout<<  "       N_incoming * N_outgoing      " << n_inc << " * " << n_out << std::endl;
  std::cout<<  " eps = -----------------------  =  ---------------- " << std::endl;
  std::cout<<  "               N_both^2               (" << n_both << ")^2" << std::endl;
  std::cout<<  "" << std::endl;
  std::cout<<  " eps = " <<eps<< " +/- " << eps_err << std::endl;
  std::cout<<  " N_haloEvents = " << hMinusOneHaloEta_->Integral() << std::endl;
  std::cout<<  "" << std::endl;
  Double_t error = 0;
  Double_t integ = hIneffEta2_->IntegralAndError(1,hIneffEta2_->GetNbinsX(),error);
  std::cout<<  " background = " << integ << " +/- " << error << std::endl;



  // Finish Fedor's second method by calculating inefficiency by eta bin - with eta flipped for -Z direction
  std::cout << std::endl << "Halo estimate - jetEta flipped for -Z halo" <<std::endl;
  hPaperIncomingEta_->Sumw2();
  hPaperOutgoingEta_->Sumw2();
  hPaperBothEta_->Sumw2();
  hPaperIneffNum_->Multiply(hPaperIncomingEta_, hPaperOutgoingEta_, 1., 1.);
  hPaperIneffDen_->Multiply(hPaperBothEta_, hPaperBothEta_, 1., 1.);
  hPaperIneffNum_->Sumw2();
  hPaperIneffDen_->Sumw2();
  hPaperIneffEta_->Divide(hPaperIneffNum_, hPaperIneffDen_, 1., 1.);
  hPaperIneffEta_->Sumw2();
  hPaperIneffEta2_->Multiply(hPaperIneffEta_, hPaperMinusOneHaloEta_, 1., 1.);

  double n_incP = hPaperIncomingEta_->GetEntries();
  double n_outP = hPaperOutgoingEta_->GetEntries();
  double n_bothP = hPaperBothEta_->GetEntries();
  double epsP = n_incP*n_outP/(n_bothP*n_bothP);
  double eps_errP = epsP*sqrt(1./n_incP + 1./n_outP + 4./n_bothP);
  std::cout<<  "";
  std::cout<<  "" << std::endl;
  std::cout<<  "       N_incoming * N_outgoing      " << n_incP << " * " << n_outP << std::endl;
  std::cout<<  " eps = -----------------------  =  ---------------- " << std::endl;
  std::cout<<  "               N_both^2               (" << n_bothP << ")^2" << std::endl;
  std::cout<<  "" << std::endl;
  std::cout<<  " eps = " <<epsP<< " +/- " << eps_errP << std::endl;
  std::cout<<  " N_haloEvents = " << hPaperMinusOneHaloEta_->Integral() << std::endl;
  std::cout<<  "" << std::endl;
  Double_t errorP = 0;
  Double_t integP = hPaperIneffEta2_->IntegralAndError(1,hPaperIneffEta2_->GetNbinsX(),errorP);
  std::cout<<  " background = " << integP << " +/- " << errorP << std::endl;


  // Finish halo estimate using average radius of CSCSegments
  std::cout << std::endl << "Halo estimate - using average CSCSegment radius" <<std::endl;
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
  std::cout<<  "";
  std::cout<<  "" << std::endl;
  std::cout<<  "       N_incoming * N_outgoing      " << n_incR << " * " << n_outR << std::endl;
  std::cout<<  " eps = -----------------------  =  ---------------- " << std::endl;
  std::cout<<  "               N_both^2               (" << n_bothR << ")^2" << std::endl;
  std::cout<<  "" << std::endl;
  std::cout<<  " eps = " << epsR << " +/- " << eps_errR << std::endl;
  std::cout<<  " N_haloEvents = " << hMinusOneHaloR_->Integral() << std::endl;
  std::cout<<  "" << std::endl;
  Double_t errorR = 0;
  Double_t integR = hIneffCountR_->IntegralAndError(1,hIneffCountR_->GetNbinsX(),errorR);
  std::cout<<  " background = " << integR << " +/- " << errorR << std::endl;


  // Finish halo estimate using average phi of CSCSegments
  std::cout << std::endl << "Halo estimate - using average CSCSegment phi" <<std::endl;
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
  std::cout<<  "";
  std::cout<<  "" << std::endl;
  std::cout<<  "       N_incoming * N_outgoing      " << n_incPhi << " * " << n_outPhi << std::endl;
  std::cout<<  " eps = -----------------------  =  ---------------- " << std::endl;
  std::cout<<  "               N_both^2               (" << n_bothPhi << ")^2" << std::endl;
  std::cout<<  "" << std::endl;
  std::cout<<  " eps = " << epsPhi << " +/- " << eps_errPhi << std::endl;
  std::cout<<  " N_haloEvents = " << hMinusOneHaloPhi_->Integral() << std::endl;
  std::cout<<  "" << std::endl;
  Double_t errorPhi = 0;
  Double_t integPhi = hIneffCountPhi_->IntegralAndError(1,hIneffCountPhi_->GetNbinsX(),errorPhi);
  std::cout<<  " background = " << integPhi << " +/- " << errorPhi << std::endl;

  // Finish halo estimate using average radius & phi of CSCSegments
  std::cout << std::endl << "Halo estimate - using average CSCSegment radius & phi" <<std::endl;
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
  std::cout<<  "";
  std::cout<<  "" << std::endl;
  std::cout<<  "       N_incoming * N_outgoing      " << n_incRPhi << " * " << n_outRPhi << std::endl;
  std::cout<<  " eps = -----------------------  =  ---------------- " << std::endl;
  std::cout<<  "               N_both^2               (" << n_bothRPhi << ")^2" << std::endl;
  std::cout<<  "" << std::endl;
  std::cout<<  " eps = " << epsRPhi << " +/- " << eps_errRPhi << std::endl;
  std::cout<<  " N_haloEvents = " << hMinusOneHaloRPhi_->Integral() << std::endl;
  std::cout<<  "" << std::endl;

  // IntegralAndError(Int_t binx1, Int_t binx2, Int_t biny1, Int_t biny2, Double_t& err, Option_t* option = "")
  Double_t errorRPhi = 0;
  Double_t integRPhi = hIneffCountRPhi_->IntegralAndError(1,hIneffCountRPhi_->GetNbinsX(),
							  1,hIneffCountRPhi_->GetNbinsY(),
							  errorRPhi);
  std::cout<<  " background = " << integRPhi << " +/- " << errorRPhi << std::endl;


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

  hSegmentZR_->Write("",TObject::kOverwrite);
  hSegmentEtaR_->Write("",TObject::kOverwrite);
  hSegmentZTime_->Write("",TObject::kOverwrite);
  hSegmentRPhi_->Write("",TObject::kOverwrite);
  hSegmentXY_->Write("",TObject::kOverwrite);
  hSegmentXYzoom_->Write("",TObject::kOverwrite);
  hSegmentThetaDir_->Write("",TObject::kOverwrite);

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
  hMinusOneCscSegments_->Write("",TObject::kOverwrite);
  hPaperIncomingEta_->Write("",TObject::kOverwrite);
  hPaperOutgoingEta_->Write("",TObject::kOverwrite);
  hPaperBothEta_->Write("",TObject::kOverwrite);
  hPaperMinusOneHaloEta_->Write("",TObject::kOverwrite);
  hPaperIneffNum_->Write("",TObject::kOverwrite);
  hPaperIneffDen_->Write("",TObject::kOverwrite);
  hPaperIneffEta_->Write("",TObject::kOverwrite);
  hPaperIneffEta2_->Write("",TObject::kOverwrite);
  
  
  
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
