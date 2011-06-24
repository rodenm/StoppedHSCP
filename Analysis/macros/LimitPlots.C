

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


void LimitPlots::calculateCrossSections(unsigned gluinoIndex, unsigned stopIndex, unsigned toyIndex, unsigned tpIndex) {

	std::cout << "Using gluino mass point " << gluinoIndex << std::endl;
	std::cout << "  mg=" << gluinoMass[gluinoIndex] << " mchi0=" << gluinoChi0Mass[gluinoIndex] 
		<< " stopEff=" << gluinoEffStopCM[gluinoIndex] << " recoEff=" << gluinoEffReco[gluinoIndex] << std::endl;

  	std::cout << "Lifetime,XSlimit,ExpLimit,-1sigma,+1sigma,-2sigma,+2sigma" << std::endl;
  	for (int l=0; l<nToyLifetime; ++l) {
	
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

	std::cout << "Using toy MC lifetime point " << toyLifetime[toyIndex] << std::endl;
	std::cout << "Using time profile lifetime point " << tpLifetime[tpIndex] << std::endl;
		
	for (unsigned i=0; i<gluinoMass.size(); ++i) {
		
		if (gluinoEffStopCM[i] * gluinoEffReco[i] > 0.) {
			massGluino.push_back(gluinoMass[i]);

			//observed
			xsProdMassGluino.push_back( toyObsLimit[toyIndex] / (toyEffLumi[toyIndex] * gluinoEffStopCM[i] * gluinoEffReco[i]) );
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

void LimitPlots::calculateIntercepts() {
	// calculate intercept
//  double mt = ( log10(theoryXS[theoryBin+1]-theoryBand[theoryBin+1]) - log10(theoryXS[theoryBin]-theoryBand[theoryBin]) ) / (theoryMass[theoryBin+1]-theoryMass[theoryBin]);
//  double ct = log10(theoryXS[theoryBin+1]-theoryBand[theoryBin+1]) - (mt*theoryMass[theoryBin+1]);

  // expected limit
//  double mexp = ( log10(excXS_exp[dataBin+1]) - log10(excXS_exp[dataBin]) ) / (m_g[dataBin+1]-m_g[dataBin]);
//  double cexp = log10(excXS_exp[dataBin+1]) - (mexp*m_g[dataBin+1]);

  // plateau limit
//  double mobs = ( log10(excXS2[dataBin+1]) - log10(excXS2[dataBin]) ) / (m_g[dataBin+1]-m_g[dataBin]);
//  double cobs = log10(excXS2[dataBin+1]) - (mobs*m_g[dataBin+1]);

  // EM limit
//  double mem = ( log10(excXS_em[dataBin+1]) - log10(excXS_em[dataBin]) ) / (m_g[dataBin+1]-m_g[dataBin]);
//  double cem = log10(excXS_em[dataBin+1]) - (mem*m_g[dataBin+1]);

  // time profile limit
//  double tpml = (log10(excXS_tp[dataBin+1])-log10(excXS_tp[dataBin])) / (m_g[dataBin+1]-m_g[dataBin]);
//  double tpcl = log10(excXS_tp[dataBin+1]) - (tpml*m_g[dataBin+1]);

//  double massLimit_exp = (cexp - ct) / (mt - mexp);
//  double massLimit_obs = (cobs - ct) / (mt - mobs);
//  double massLimit_EM = (cem - ct) / (mt - mem);
//  double massLimit_TP = (tpcl - ct) / (mt - tpml);

//  cout << "Mass limit - counting expt expected = " << massLimit_exp << endl;
//  cout << "Mass limit - counting expt observed = " << massLimit_obs << endl;
//  cout << "Mass limit - counting expt obs (EM) = " << massLimit_EM << endl;
//  cout << "Mass limit - time profile           = " << massLimit_TP << endl;	
	
}


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

