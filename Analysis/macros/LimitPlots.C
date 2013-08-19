

#include "LimitPlots.h"


LimitPlots::LimitPlots(double tpLumi) :
  tpLumi_(tpLumi)
{

  readToyFile(std::string("toymc.txt"));
  readTimeProfileFile(std::string("time_profile.txt"));

  readGluinoData(std::string("mcGluino.txt"));
  readStopData(std::string("mcStop.txt"));
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

  double m(0.), mchi(0.), escm(0.), esnb(0.), esem(0.), er(0.), xst(0.);

  std::string line;
  getline(file, line);
  getline(file, line);
  
  while (file >> m >> mchi >> escm >> esnb >> esem >> er >> xst) {
    
    //std::cout << "gluino mass " << m << std::endl;

    gluinoMass.push_back(m);
    gluinoChi0Mass.push_back(mchi);
    gluinoEffStopCM.push_back(escm);
    gluinoEffStopNB.push_back(esnb);
    gluinoEffStopEM.push_back(esem);
    gluinoEffReco.push_back(er);
    
    // gluino theory info
    if (xst > 0.) {
      gluinoTheoryMass.push_back(m);
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
  
  double m(0.), mchi(0.), escm(0.), esnb(0.), esem(0.), er(0.), xst(0.);
  
  while (file >> m >> mchi >> escm >> esnb >> esem >> er >> xst) {
    
    stopMass.push_back(m);
    stopChi0Mass.push_back(mchi);
    stopEffStopCM.push_back(escm);
    stopEffStopNB.push_back(esnb);
    stopEffStopEM.push_back(esem);
    stopEffReco.push_back(er);
    
    // stop theory info
    if (xst > 0.) {
      stopTheoryMass.push_back(m);
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
  
  double m(0.), mchi(0.), escm(0.), esnb(0.), esem(0.), er(0.), xst(0.);
  
  while (file >> m >> mchi >> escm >> esnb >> esem >> er >> xst) {
    
    //       stopMass.push_back(m);
    //       stopChi0Mass.push_back(mchi);
    //       stopEffStopCloud.push_back(escm);
    //       stopEffStopNB.push_back(esnb);
    //       stopEffStopEM.push_back(esem);
    //       stopEffReco.push_back(er);
    
    //       // stop theory info
    //       if (xst > 0.) {
    // 	stopTheoryMass.push_back(m);
    // 	stopTheoryXS.push_back(xst);
    //       }
    
    count++;

  }

  std::cout << "Read " << count << " stau mass points" << std::endl;

}


// toyIndex is not used because it should vary with different threshold hypotheses 
void LimitPlots::calculateCrossSections(unsigned gluinoIndex, unsigned stopIndex, unsigned toyIndex, unsigned tpIndex) {

  std::cout << "Using gluino mass point " << gluinoIndex << std::endl;
  std::cout << "  mg=" << gluinoMass[gluinoIndex] << " mchi0=" << gluinoChi0Mass[gluinoIndex] 
	    << " stopEff=" << gluinoEffStopCM[gluinoIndex] << " recoEff=" << gluinoEffReco[gluinoIndex] << std::endl;

  std::cout << "Lifetime,XSlimit,ExpLimit,-1sigma,+1sigma,-2sigma,+2sigma" << std::endl;
  for (int l=0; l<nToyLifetime; ++l) {
	
    // Pick toyIndex to correspond to 1 sec lifetime hypothesis to assure that mass limits
    // are taken from the middle/stable part of the lifetime distribution
    if (toyLifetime[l] > 0.5 && toyLifetime[l] < 1.5)
      toyIndex = l;


    // basic limit
    xsLimitToyGluino.push_back( toyObsLimit[l] / (toyEffLumi[l] * gluinoEffReco[gluinoIndex]) );
    xsLimitToyStop.push_back( toyObsLimit[l] / (toyEffLumi[l] * stopEffReco[stopIndex]) );
	
    // observed limits
    xsProdLimitToyGluino.push_back( toyObsLimit[l] / (toyEffLumi[l] * gluinoEffStopCM[gluinoIndex] * gluinoEffReco[gluinoIndex]) );
    xsProdLimitToyGluinoNB.push_back( toyObsLimit[l] / (toyEffLumi[l] * gluinoEffStopNB[gluinoIndex] * gluinoEffReco[gluinoIndex]) );
    xsProdLimitToyGluinoEM.push_back( toyObsLimit[l] / (toyEffLumi[l] * gluinoEffStopEM[gluinoIndex] * gluinoEffReco[gluinoIndex]) );

    // observed limits stop
    xsProdLimitToyStop.push_back( toyObsLimit[l] / (toyEffLumi[l] * stopEffStopCM[stopIndex] * stopEffReco[stopIndex]) );
    xsProdLimitToyStopNB.push_back( toyObsLimit[l] / (toyEffLumi[l] * stopEffStopNB[stopIndex] * stopEffReco[stopIndex]) );
    xsProdLimitToyStopEM.push_back( toyObsLimit[l] / (toyEffLumi[l] * stopEffStopEM[stopIndex] * stopEffReco[stopIndex]) );

    // expected limit and bands
    xsProdExpLimitToyGluino.push_back( toyExpLimit[l] / (toyEffLumi[l] * gluinoEffStopCM[gluinoIndex] * gluinoEffReco[gluinoIndex]) );
    xsProdExpLimitLo1SigToyGluino.push_back( (toyExpLimit[l]-toyExpLimitLo1Sig[l]) / (toyEffLumi[l] * gluinoEffStopCM[gluinoIndex] * gluinoEffReco[gluinoIndex]) );
    xsProdExpLimitHi1SigToyGluino.push_back( (toyExpLimitHi1Sig[l]-toyExpLimit[l]) / (toyEffLumi[l] * gluinoEffStopCM[gluinoIndex] * gluinoEffReco[gluinoIndex]) );
    xsProdExpLimitLo2SigToyGluino.push_back( (toyExpLimit[l]-toyExpLimitLo2Sig[l]) / (toyEffLumi[l] * gluinoEffStopCM[gluinoIndex] * gluinoEffReco[gluinoIndex]) );
    xsProdExpLimitHi2SigToyGluino.push_back( (toyExpLimitHi2Sig[l]-toyExpLimit[l]) / (toyEffLumi[l] * gluinoEffStopCM[gluinoIndex] * gluinoEffReco[gluinoIndex]) );

    // expected limit and bands - stop
    xsProdExpLimitToyStop.push_back( toyExpLimit[l] / (toyEffLumi[l] * stopEffStopCM[stopIndex] * stopEffReco[stopIndex]) );
    xsProdExpLimitLo1SigToyStop.push_back( (toyExpLimit[l]-toyExpLimitLo1Sig[l]) / (toyEffLumi[l] * stopEffStopCM[stopIndex] * stopEffReco[stopIndex]) );
    xsProdExpLimitHi1SigToyStop.push_back( (toyExpLimitHi1Sig[l]-toyExpLimit[l]) / (toyEffLumi[l] * stopEffStopCM[stopIndex] * stopEffReco[stopIndex]) );
    xsProdExpLimitLo2SigToyStop.push_back( (toyExpLimit[l]-toyExpLimitLo2Sig[l]) / (toyEffLumi[l] * stopEffStopCM[stopIndex] * stopEffReco[stopIndex]) );
    xsProdExpLimitHi2SigToyStop.push_back( (toyExpLimitHi2Sig[l]-toyExpLimit[l]) / (toyEffLumi[l] * stopEffStopCM[stopIndex] * stopEffReco[stopIndex]) );

    // print out
    std::cout << toyLifetime[l] << "," << xsProdLimitToyGluino[l] << "," << xsProdExpLimitToyGluino[l] << "," << xsProdExpLimitLo1SigToyGluino[l] << "," << xsProdExpLimitHi1SigToyGluino[l] << "," << xsProdExpLimitLo2SigToyGluino[l] << "," << xsProdExpLimitHi2SigToyGluino[l] << std::endl;
  }
  std::cout << std::endl;

  // time profile XS
  std::cout << "Lifetime, time profile limit" << std::endl;
  for (int i=0; i<nTPLifetime; ++i) {
    xsProdLimitTPGluino.push_back( tpObsLimit[i] / (tpLumi_ * gluinoEffStopCM[gluinoIndex] * gluinoEffReco[gluinoIndex]) );
    xsProdLimitTPStop.push_back( tpObsLimit[i] / (tpLumi_ * stopEffStopCM[stopIndex] * stopEffReco[stopIndex]) );
    std::cout << tpLifetime[i] << "," << xsProdLimitTPGluino[i] << std::endl;
  }

  std::cout << "Using toy MC lifetime point " << toyLifetime[toyIndex] << " sec" << std::endl;
  if (tpLifetime.size()>tpIndex)
    std::cout << "Using time profile lifetime point " << tpLifetime[tpIndex] << std::endl;
  else
    std::cout <<" Time Profile size is < "<<tpIndex<<".  Is time profile txt file provided?"<<std::endl;
  for (unsigned i=0; i<gluinoMass.size(); ++i) {
		
    if (gluinoEffStopCM[i] * gluinoEffReco[i] > 0.) {
      massGluino.push_back(gluinoMass[i]);

      //observed
      xsProdMassGluino.push_back( toyObsLimit[toyIndex] / (toyEffLumi[toyIndex] * gluinoEffStopCM[i] * gluinoEffReco[i]) );
      if (tpLifetime.size()>tpIndex)
			  
	xsProdMassTPGluino.push_back( tpObsLimit[tpIndex] / (tpLumi_ * gluinoEffStopCM[i] * gluinoEffReco[i]) );

      //expected gluino
      xsProdExpMassGluino.push_back( toyExpLimit[toyIndex] / (toyEffLumi[toyIndex] * gluinoEffStopCM[i] * gluinoEffReco[i]) );
      xsProdExpLo1SigMassGluino.push_back( (toyExpLimit[toyIndex]-toyExpLimitLo1Sig[toyIndex]) / (toyEffLumi[toyIndex] * gluinoEffStopCM[i] * gluinoEffReco[i]) );
      xsProdExpHi1SigMassGluino.push_back( (toyExpLimitHi1Sig[toyIndex]-toyExpLimit[toyIndex]) / (toyEffLumi[toyIndex] * gluinoEffStopCM[i] * gluinoEffReco[i]) );
      xsProdExpLo2SigMassGluino.push_back( (toyExpLimit[toyIndex]-toyExpLimitLo2Sig[toyIndex]) / (toyEffLumi[toyIndex] * gluinoEffStopCM[i] * gluinoEffReco[i]) );
      xsProdExpHi2SigMassGluino.push_back( (toyExpLimitHi2Sig[toyIndex]-toyExpLimit[toyIndex]) / (toyEffLumi[toyIndex] * gluinoEffStopCM[i] * gluinoEffReco[i]) );

      std::cout << " mass=" << gluinoMass.at(i) << " stopEff=" << gluinoEffStopCM[i] << " recoEff=" << gluinoEffReco[i] << std::endl;

    }


  }
	
  for (unsigned i=0; i<stopMass.size(); ++i) {
	
    if (stopEffStopCM[i] * stopEffReco[i] > 0.) {
			
      massStop.push_back( stopMass[i] );

      // observed stop
      xsProdMassStop.push_back( toyObsLimit[toyIndex] / (toyEffLumi[toyIndex] * stopEffStopCM[i] * stopEffReco[i]) );
      if (tpLifetime.size()>tpIndex)
			  
	xsProdMassTPStop.push_back( tpObsLimit[tpIndex] / (tpLumi_ * stopEffStopCM[i] * stopEffReco[i]) );
		
      // expected stop
      xsProdExpMassStop.push_back( toyExpLimit[toyIndex] / (toyEffLumi[toyIndex] * stopEffStopCM[i] * stopEffReco[i]) );
      xsProdExpLo1SigMassStop.push_back( (toyExpLimit[toyIndex]-toyExpLimitLo1Sig[toyIndex]) / (toyEffLumi[toyIndex] * stopEffStopCM[i] * stopEffReco[i]) );
      xsProdExpHi1SigMassStop.push_back( (toyExpLimitHi1Sig[toyIndex]-toyExpLimit[toyIndex]) / (toyEffLumi[toyIndex] * stopEffStopCM[i] * stopEffReco[i]) );
      xsProdExpLo2SigMassStop.push_back( (toyExpLimit[toyIndex]-toyExpLimitLo2Sig[toyIndex]) / (toyEffLumi[toyIndex] * stopEffStopCM[i] * stopEffReco[i]) );
      xsProdExpHi2SigMassStop.push_back( (toyExpLimitHi2Sig[toyIndex]-toyExpLimit[toyIndex]) / (toyEffLumi[toyIndex] * stopEffStopCM[i] * stopEffReco[i]) );
		
      std::cout << " mass=" << stopMass.at(i) << std::endl;

    }
		
  }


}

void LimitPlots::calculateIntercepts(){
  
  TGraph* g_theory       = getGluinoTheory();
  TGraph* g_expected     = getExpMassLimitGluino();
  TGraphAsymmErrors* g_expected_asym= getExpMassLimitGluino1Sig();
  TGraph* g_observed     = getMassLimitGluino();
  TGraph* g_NB           = getLimitGluinoNB();
  TGraph* g_EM           = getLimitGluinoEM();
  TGraph* g_TP           = getLimitGluinoTP();

  std::cout <<"Calculating Gluino Mass Limits"<<std::endl;
  std::cout <<"\tCalculating Expected Limit"<<std::endl; 
  //double g_massLimit_exp= calculateMassLimits(g_theory, g_expected); 
  std::vector<double> g_MASS=calculateMassLimitsWithErrors(g_theory, g_expected_asym);
  double g_massLimit_exp=g_MASS[0];
  std::cout <<"\tCalculating Observed Limit"<<std::endl;
  double g_massLimit_obs= calculateMassLimits(g_theory, g_observed);
  std::cout <<"\tCalculating NB Limit"<<std::endl;
  double g_massLimit_NB = calculateMassLimits(g_theory, g_NB);
  std::cout <<"\tCalculating EM Limit"<<std::endl;
  double g_massLimit_EM = calculateMassLimits(g_theory, g_EM);
  std::cout <<"\tCalculating TP Limit"<<std::endl;
  double g_massLimit_TP = calculateMassLimits(g_theory, g_TP);
  std::cout <<"\n"<<std::endl;

  TGraph* s_theory       = getStopTheory();
  TGraph* s_expected     = getExpMassLimitStop();
  TGraphAsymmErrors* s_expected_asym= getExpMassLimitStop1Sig();
  TGraph* s_observed     = getMassLimitStop();
  TGraph* s_NB           = getLimitStopNB();
  TGraph* s_EM           = getLimitStopEM();
  TGraph* s_TP           = getLimitStopTP();

  std::cout <<"Calculating Stop Mass Limits"<<std::endl;
  std::cout <<"\tCalculating Expected Limit"<<std::endl; 
  //double s_massLimit_exp= calculateMassLimits(s_theory, s_expected); 
  std::vector<double> s_MASS=calculateMassLimitsWithErrors(s_theory, s_expected_asym);
  double s_massLimit_exp=s_MASS[0];
  std::cout <<"\tCalculating Observed Limit"<<std::endl;
  double s_massLimit_obs= calculateMassLimits(s_theory, s_observed);
  std::cout <<"\tCalculating NB Limit"<<std::endl;
  double s_massLimit_NB = calculateMassLimits(s_theory, s_NB);
  std::cout <<"\tCalculating EM Limit"<<std::endl;
  double s_massLimit_EM = calculateMassLimits(s_theory, s_EM);
  std::cout <<"\tCalculating TP Limit"<<std::endl;
  double s_massLimit_TP = calculateMassLimits(s_theory, s_TP);
  std::cout <<"\n"<<std::endl;

  if (g_massLimit_exp>-1){
    std::cout <<"Gluino mass limit - counting expt expected = " << g_massLimit_exp; 
    if (g_MASS[1]>0) std::cout<<"  "<<g_MASS[1]-g_massLimit_exp;
    else std::cout <<"  - N/A";
    if (g_MASS[2]>0) std::cout<<"  +"<<g_MASS[2]-g_massLimit_exp;
    else std::cout <<"  + N/A";
    std::cout <<std::endl;
  }
  else
    std::cout <<"Gluino mass limit - counting expt expected:  Could not be determined!"<<std::endl;
  if (g_massLimit_obs>-1)
    std::cout <<"Gluino mass limit - counting expt observed = " << g_massLimit_obs << endl;
  else
    std::cout <<"Gluino mass limit - counting expt observed:  Could not be determined!"<<std::endl;
  if (g_massLimit_NB>-1)
    std::cout <<"Gluino mass limit - counting expt observed (NB) = " << g_massLimit_NB << endl;
  else
    std::cout <<"Gluino mass limit - counting expt observed (NB):  Could not be determined!"<<std::endl;
  if (g_massLimit_EM>-1)
    std::cout <<"Gluino mass limit - counting expt observed (EM)= " << g_massLimit_EM << endl;
  else
    std::cout <<"Gluino mass limit - counting expt observed (EM):  Could not be determined!"<<std::endl;
  if (g_massLimit_TP>-1)
    std::cout <<"Gluino mass limit - counting expt observed (TP)= " << g_massLimit_TP << endl;
  else
    std::cout <<"Gluino mass limit - counting expt observed (TP):  Could not be determined!"<<std::endl;
  std::cout <<"\n"<<std::endl;

  // Now dump out stop limits
  if (s_massLimit_exp>-1)
    {
    std::cout <<"Stop mass limit - counting expt expected = " << s_massLimit_exp; 
    if (s_MASS[1]>0) std::cout<<"  "<<s_MASS[1]-s_massLimit_exp;
    else std::cout <<"  - N/A";
    if (s_MASS[2]>0) std::cout<<"  +"<<s_MASS[2]-s_massLimit_exp;
    else std::cout <<"  + N/A";
    std::cout <<std::endl;
  }
  else
    std::cout <<"Stop mass limit - counting expt expected:  Could not be determined!"<<std::endl;
  if (s_massLimit_obs>-1)
    std::cout <<"Stop mass limit - counting expt observed = " << s_massLimit_obs << endl;
  else
    std::cout <<"Stop mass limit - counting expt observed:  Could not be determined!"<<std::endl;
  if (s_massLimit_NB>-1)
    std::cout <<"Stop mass limit - counting expt observed (NB) = " << s_massLimit_NB << endl;
  else
    std::cout <<"Stop mass limit - counting expt observed (NB):  Could not be determined!"<<std::endl;
  if (s_massLimit_EM>-1)
    std::cout <<"Stop mass limit - counting expt observed (EM)= " << s_massLimit_EM << endl;
  else
    std::cout <<"Stop mass limit - counting expt observed (EM):  Could not be determined!"<<std::endl;
  if (s_massLimit_TP>-1)
    std::cout <<"Stop mass limit - counting expt observed (TP)= " << s_massLimit_TP << endl;
  else
    std::cout <<"Stop mass limit - counting expt observed (TP):  Could not be determined!"<<std::endl;
  std::cout <<"\n"<<std::endl;



} // void LimitPlots::calculateMassLimits()



double LimitPlots::calculateMassLimits(TGraph* gTheory, TGraph* gData) {
  /* Takes two TGraphs (a theory cross section "gTheory",
     and a measured/expected cross section "gData"), and 
     finds the point at which they meet.
     Intersection is found by looking at consecutive points in each TGraph,
     where (x1a, y1a) and (x2a, y2a) are consectuive points for data,
     and (x1b, y1b) and (x2b, y2b) are consecutive theory points.
     To find the intersect, the following must be true:
        y1a <= y1b   (theory starts above data value)
        y2a >= y2b    (theory ends below data value)
        x1b > x2a    (so that data range and theory range overlap)
    If no intersection if found, a value of '-1' is returned.  Otherwise, the 
    mass limit (x coordinate of intersection) is returned.  The intersection is 
    found by a linear fit to the log of the cross sections:
    (log y1) = m1*x1+b1
    (log y2) = m2*x2+b2
    Intersection at (log y1 = logy2) and (x1=x2==x):
       x = (b1-b2)/(m2-m1)
  */
  
  // TO DO:  Allow theory uncertainty?  Find intercept for +1/-1sigma variations in data?

  double massLimit = -1;

  // Look for crossing point between the expected and theory curve

  bool massRangeFound=false;
  Double_t x1a, y1a, x2a, y2a = 0;
  Double_t x1b, y1b, x2b, y2b = 0;

  for(int a_i = 0; a_i < gData->GetN()-1; ++a_i)
   {
     gData->GetPoint(a_i, x1a, y1a);
     gData->GetPoint(a_i+1, x2a, y2a);
     //std::cout <<"a = ("<<x1a<<", "<<y1a<<")"<<std::endl;
     // Loop over all points in the other TGraph
     for(int b_i = 0; b_i < gTheory->GetN()-1; ++b_i)
       {
	 gTheory->GetPoint(b_i, x1b, y1b);
	 gTheory->GetPoint(b_i+1, x2b, y2b);
	 //std::cout <<"b = ("<<x1b<<", "<<y1b<<")"<<std::endl;
	 if (x2a<=x1b) continue;  // need to overlap in x
	 if ((y2b<=y2a && y1b>=y1a) ||(y2b>=y2a && y1b<=y1a))  // cross point found!
	   {
	     // TO DO:  Add in special handling if y2b==y2a and y1b==y1a?
	     // These cout statements can be removed later, once we have confidence in the output of the intercept finding
	     std::cout <<"\t\tFOUND CROSSING POINT!  EXP= ("<<x1a<<", "<<y1a<<") -> ("<<x2a<<", "<<y2a<<")"<<std::endl;
	     std::cout <<"\t\tFOUND CROSSING POINT!  THEORY= ("<<x1b<<", "<<y1b<<") -> ("<<x2b<<", "<<y2b<<")"<<std::endl;
	     massRangeFound=true;
	     break;
	   }
	 if (massRangeFound==true) break;
       } // loop over theory points
     if (massRangeFound==true) break;
   } // loop over expected points
      
  // overlap between theory, expected found; interpolate crossing point
  // assuming that each drops exponentially with mass
  if (massRangeFound==false)
    return massLimit;

  // get slope and intercept; (log y) = mx+b;
  double m_theory = (log10(y2b)-log10(y1b))/(x2b-x1b);
  double b_theory =log10(y2b)-m_theory*x2b;
  
  double m_exp = (log10(y2a)-log10(y1a))/(x2a-x1a);
  double b_exp = log10(y1a)-m_exp*x1a;
  
  massLimit=(b_theory-b_exp)/(m_exp-m_theory);
  return massLimit;
}


std::vector<double> LimitPlots::calculateMassLimitsWithErrors(TGraph* gTheory, TGraphAsymmErrors* gData) {
  /* 
     Works like above "calculateMassLimits" function, but runs algorithm three times, returning the vector
     <mass limit for nominal, mass limit for +1 sigma, mass limit for -1 sigma>
  */
  
  // TO DO:  Allow theory uncertainty?  Find intercept for +1/-1sigma variations in data?

  std::vector <double> results;
  double massLimit = -1;

  // Look for crossing point between the expected and theory curve

  bool massRangeFound=false;
  Double_t x1a, y1a, x2a, y2a = 0;
  Double_t x1b, y1b, x2b, y2b = 0;

  for(int a_i = 0; a_i < gData->GetN()-1; ++a_i)
   {
     gData->GetPoint(a_i, x1a, y1a);
     gData->GetPoint(a_i+1, x2a, y2a);
     //std::cout <<"a = ("<<x1a<<", "<<y1a<<")"<<std::endl;
     // Loop over all points in the other TGraph
     for(int b_i = 0; b_i < gTheory->GetN()-1; ++b_i)
       {
	 gTheory->GetPoint(b_i, x1b, y1b);
	 gTheory->GetPoint(b_i+1, x2b, y2b);
	 //std::cout <<"b = ("<<x1b<<", "<<y1b<<")"<<std::endl;
	 if (x2a<=x1b) continue;  // need to overlap in x
	 if ((y2b<=y2a && y1b>=y1a) ||(y2b>=y2a && y1b<=y1a))  // cross point found!
	   {
	     // TO DO:  Add in special handling if y2b==y2a and y1b==y1a?
	     std::cout <<"\t\tFOUND CROSSING POINT!  EXP= ("<<x1a<<", "<<y1a<<") -> ("<<x2a<<", "<<y2a<<")"<<std::endl;
	     std::cout <<"\t\tFOUND CROSSING POINT!  THEORY= ("<<x1b<<", "<<y1b<<") -> ("<<x2b<<", "<<y2b<<")"<<std::endl;
	     massRangeFound=true;
	     break;
	   }
	 if (massRangeFound==true) break;
       } // loop over theory points
     if (massRangeFound==true) break;
   } // loop over expected points
      
  // overlap between theory, expected found; interpolate crossing point
  // assuming that each drops exponentially with mass
  if (massRangeFound==true)
    {
      // get slope and intercept; (log y) = mx+b;
      double m_theory = (log10(y2b)-log10(y1b))/(x2b-x1b);
      double b_theory =log10(y2b)-m_theory*x2b;
      
      double m_exp = (log10(y2a)-log10(y1a))/(x2a-x1a);
      double b_exp = log10(y1a)-m_exp*x1a;
      
      massLimit=(b_theory-b_exp)/(m_exp-m_theory);
    } 
  results.push_back(massLimit);

  // Now repeat for +1 sigma data point
  massLimit = -1;
  massRangeFound=false;
  for(int a_i = 0; a_i < gData->GetN()-1; ++a_i)
    {
     gData->GetPoint(a_i, x1a, y1a);
     gData->GetPoint(a_i+1, x2a, y2a);
     y1a+=gData->GetErrorYhigh(a_i);
     y2a+=gData->GetErrorYhigh(a_i+1);
     // Loop over all points in the other TGraph
     for(int b_i = 0; b_i < gTheory->GetN()-1; ++b_i)
       {
	 gTheory->GetPoint(b_i, x1b, y1b);
	 gTheory->GetPoint(b_i+1, x2b, y2b);
	 if (x2a<=x1b) continue;  // need to overlap in x
	 if ((y2b<=y2a && y1b>=y1a) ||(y2b>=y2a && y1b<=y1a))  // cross point found!
	   {
	     // TO DO:  Add in special handling if y2b==y2a and y1b==y1a?
	     std::cout <<"FOUND CROSSING POINT!  EXP= ("<<x1a<<", "<<y1a<<") -> ("<<x2a<<", "<<y2a<<")"<<std::endl;
	     std::cout <<"FOUND CROSSING POINT!  THEORY= ("<<x1b<<", "<<y1b<<") -> ("<<x2b<<", "<<y2b<<")"<<std::endl;
	     massRangeFound=true;
	     break;
	   }
	 if (massRangeFound==true) break;
       } // loop over theory points
     if (massRangeFound==true) break;
   } // loop over expected points
      
  // overlap between theory, expected found; interpolate crossing point
  // assuming that each drops exponentially with mass
  if (massRangeFound==true)
    {
      // get slope and intercept; (log y) = mx+b;
      double m_theory = (log10(y2b)-log10(y1b))/(x2b-x1b);
      double b_theory =log10(y2b)-m_theory*x2b;
      
      double m_exp = (log10(y2a)-log10(y1a))/(x2a-x1a);
      double b_exp = log10(y1a)-m_exp*x1a;
      
      massLimit=(b_theory-b_exp)/(m_exp-m_theory);
    } 
  results.push_back(massLimit);

  // finally, repeat for negative error
  massLimit = -1;
  massRangeFound=false;
  for(int a_i = 0; a_i < gData->GetN()-1; ++a_i)
    {
     gData->GetPoint(a_i, x1a, y1a);
     gData->GetPoint(a_i+1, x2a, y2a);
     std::cout <<"ERROR LOW = "<<gData->GetErrorYlow(a_i)<<std::endl;
     y1a-=gData->GetErrorYlow(a_i);
     y2a-=gData->GetErrorYlow(a_i+1);
     // Loop over all points in the other TGraph
     for(int b_i = 0; b_i < gTheory->GetN()-1; ++b_i)
       {
	 gTheory->GetPoint(b_i, x1b, y1b);
	 gTheory->GetPoint(b_i+1, x2b, y2b);
	 if (x2a<=x1b) continue;  // need to overlap in x
	 if ((y2b<=y2a && y1b>=y1a) ||(y2b>=y2a && y1b<=y1a))  // cross point found!
	   {
	     // TO DO:  Add in special handling if y2b==y2a and y1b==y1a?
	     std::cout <<"FOUND CROSSING POINT!  EXP= ("<<x1a<<", "<<y1a<<") -> ("<<x2a<<", "<<y2a<<")"<<std::endl;
	     std::cout <<"FOUND CROSSING POINT!  THEORY= ("<<x1b<<", "<<y1b<<") -> ("<<x2b<<", "<<y2b<<")"<<std::endl;
	     massRangeFound=true;
	     break;
	   }
	 if (massRangeFound==true) break;
       } // loop over theory points
     if (massRangeFound==true) break;
   } // loop over expected points
      
  // overlap between theory, expected found; interpolate crossing point
  // assuming that each drops exponentially with mass
  if (massRangeFound==true)
    {
      // get slope and intercept; (log y) = mx+b;
      double m_theory = (log10(y2b)-log10(y1b))/(x2b-x1b);
      double b_theory =log10(y2b)-m_theory*x2b;
      
      double m_exp = (log10(y2a)-log10(y1a))/(x2a-x1a);
      double b_exp = log10(y1a)-m_exp*x1a;
      
      massLimit=(b_theory-b_exp)/(m_exp-m_theory);
    } 
  results.push_back(massLimit);

  return results;
} //calculateMassLimitsWithErrors



TGraph* LimitPlots::getLimitGluinoBasic() {
	return new TGraph(xsLimitToyGluino.size(), &toyLifetime[0], &xsLimitToyGluino[0]);
}
TGraph* LimitPlots::getLimitGluino() {
	return new TGraph(xsProdLimitToyGluino.size(), &toyLifetime[0], &xsProdLimitToyGluino[0]);
}
TGraph* LimitPlots::getLimitGluinoNB() {
	return new TGraph(xsProdLimitToyGluinoNB.size(), &toyLifetime[0], &xsProdLimitToyGluinoNB[0]);
}
TGraph* LimitPlots::getLimitGluinoEM(){
	return new TGraph(xsProdLimitToyGluinoEM.size(), &toyLifetime[0], &xsProdLimitToyGluinoEM[0]);
}
TGraph* LimitPlots::getLimitGluinoTP(){
	return new TGraph(xsProdLimitTPGluino.size(), &tpLifetime[0], &xsProdLimitTPGluino[0]);
}

TGraph* LimitPlots::getExpLimitGluino() {
	return new TGraph(xsProdExpLimitToyGluino.size(), &toyLifetime[0], &xsProdExpLimitToyGluino[0]);
}
TGraphAsymmErrors* LimitPlots::getExpLimitGluino1Sig() {
	return new TGraphAsymmErrors(xsProdExpLimitToyGluino.size(),
								&toyLifetime[0],
								&xsProdExpLimitToyGluino[0],
								0,
								0,
								&xsProdExpLimitLo1SigToyGluino[0],
								&xsProdExpLimitHi1SigToyGluino[0]);
}
TGraphAsymmErrors* LimitPlots::getExpLimitGluino2Sig() {
	return new TGraphAsymmErrors(xsProdExpLimitToyGluino.size(),
								&toyLifetime[0],
								&xsProdExpLimitToyGluino[0],
								0,
								0,
								&xsProdExpLimitLo2SigToyGluino[0],
								&xsProdExpLimitHi2SigToyGluino[0]);
}

TGraph* LimitPlots::getLimitStopBasic() {
	return new TGraph(xsLimitToyStop.size(), &toyLifetime[0], &xsLimitToyStop[0]);
}
TGraph* LimitPlots::getLimitStop() {
	return new TGraph(xsProdLimitToyStop.size(), &toyLifetime[0], &xsProdLimitToyStop[0]);
}
TGraph* LimitPlots::getLimitStopNB() {
	return new TGraph(xsProdLimitToyStopNB.size(), &toyLifetime[0], &xsProdLimitToyStopNB[0]);
}
TGraph* LimitPlots::getLimitStopEM() {
	return new TGraph(xsProdLimitToyStopEM.size(), &toyLifetime[0], &xsProdLimitToyStopEM[0]);
}
TGraph* LimitPlots::getLimitStopTP() {
	return new TGraph(xsProdLimitTPStop.size(), &tpLifetime[0], &xsProdLimitTPStop[0]);
}

TGraph* LimitPlots::getExpLimitStop() {
	return new TGraph(xsProdExpLimitToyStop.size(), &toyLifetime[0], &xsProdExpLimitToyStop[0]);
}
TGraphAsymmErrors* LimitPlots::getExpLimitStop1Sig() {	
	return new TGraphAsymmErrors(xsProdExpLimitToyStop.size(),
								&toyLifetime[0],
								&xsProdExpLimitToyStop[0],
								0,
								0,
								&xsProdExpLimitLo1SigToyStop[0],
								&xsProdExpLimitHi1SigToyStop[0]);
}

TGraphAsymmErrors* LimitPlots::getExpLimitStop2Sig() {
	return new TGraphAsymmErrors(xsProdExpLimitToyStop.size(),
								&toyLifetime[0],
								&xsProdExpLimitToyStop[0],
								0,
								0,
								&xsProdExpLimitLo2SigToyStop[0],
								&xsProdExpLimitHi2SigToyStop[0]);
}


TGraph* LimitPlots::getMassLimitGluino() {
	return new TGraph(xsProdMassGluino.size(), &massGluino[0], &xsProdMassGluino[0]);
}

TGraph* LimitPlots::getMassLimitGluinoTP() {
	return new TGraph(xsProdMassTPGluino.size(), &massGluino[0], &xsProdMassTPGluino[0]);	
}

TGraph* LimitPlots::getExpMassLimitGluino(){
	return new TGraph(xsProdExpMassGluino.size(), &massGluino[0], &xsProdExpMassGluino[0]);
}

TGraphAsymmErrors* LimitPlots::getExpMassLimitGluino1Sig(){
	return new TGraphAsymmErrors(xsProdExpMassGluino.size(),
				     &massGluino[0],
				     &xsProdExpMassGluino[0],
				     0,
				     0,
				     &xsProdExpLo1SigMassGluino[0],
				     &xsProdExpHi1SigMassGluino[0]);
}

TGraphAsymmErrors* LimitPlots::getExpMassLimitGluino2Sig() {
	return new TGraphAsymmErrors(xsProdExpMassGluino.size(),
				     &massGluino[0],
				     &xsProdExpMassGluino[0],
				     0,
				     0,
				     &xsProdExpLo2SigMassGluino[0],
				     &xsProdExpHi2SigMassGluino[0]);
}

TGraph* LimitPlots::getMassLimitStop() {
	return new TGraph(xsProdMassStop.size(), &massStop[0], &xsProdMassStop[0]);
}

TGraph* LimitPlots::getMassLimitStopTP() {
	return new TGraph(xsProdMassTPStop.size(), &massStop[0], &xsProdMassTPStop[0]);	
}

TGraph* LimitPlots::getExpMassLimitStop() {
	return new TGraph(xsProdExpMassStop.size(), &massStop[0], &xsProdExpMassStop[0]);	
}

TGraphAsymmErrors* LimitPlots::getExpMassLimitStop1Sig() {
	return new TGraphAsymmErrors(xsProdExpMassStop.size(),
				     &massStop[0],
				     &xsProdExpMassStop[0],
				     0,
				     0,
				     &xsProdExpLo1SigMassStop[0],
				     &xsProdExpHi1SigMassStop[0]);
}

TGraphAsymmErrors* LimitPlots::getExpMassLimitStop2Sig() {
	return new TGraphAsymmErrors(xsProdExpMassStop.size(),
				     &massStop[0],
				     &xsProdExpMassStop[0],
				     0,
				     0,
				     &xsProdExpLo2SigMassStop[0],
				     &xsProdExpHi2SigMassStop[0]);	
}

TGraph* LimitPlots::getGluinoTheory() {
	return new TGraph(gluinoTheoryMass.size(), &gluinoTheoryMass[0], &gluinoTheoryXS[0]);
}

TGraph* LimitPlots::getStopTheory() {
	return new TGraph(stopTheoryMass.size(), &stopTheoryMass[0], &stopTheoryXS[0]);	
}

