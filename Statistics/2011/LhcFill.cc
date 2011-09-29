// 
// Manages LHC filling scheme. Initiated by the standard LHC data
// fedor.ratnikov@cern.ch 16 May 2011
// 

#include <cmath>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>

#include "StoppedHSCP/Analysis/interface/Constants.h"
#include "StoppedHSCP/Analysis/interface/LhcFill.h"

using namespace std;

namespace {
  const int VETOED = -1;
  const int  PARASITIC = -2;

  int normalizeBX (int fBX) {
    while (fBX < 0) fBX += NBX_PER_ORBIT;
    while (fBX >= int(NBX_PER_ORBIT)) fBX -= NBX_PER_ORBIT;
    return fBX;
  }
}

LhcFill::LhcFill (const std::string& fBeamStructure) 
  : mBunches (NBX_PER_ORBIT, 0.),
    mName ("NA")
{
  if (!fBeamStructure.empty()) {
    mName = fBeamStructure;
    const char* cmssw = getenv ("CMSSW_BASE");
    if (!cmssw) {
      cout << "LhcFill::LhcFill-> CMSSW is not set" << endl;
      return;
    }
    string fileName (cmssw);
    fileName += "/src/StoppedHSCP/Analysis/data/" + fBeamStructure;
    fileName += ".beam";
    // read beam structure
    ifstream input (fileName.c_str());
    if (!input) {
      cout << "LhcFill::LhcFill-> Can not find fill structure file: " << fileName << endl;
      return;
    }
    vector<float> beam1 (NBX_PER_ORBIT, 0);
    vector<float> beam2 (NBX_PER_ORBIT, 0);
    while (input) {
      string line;
      if (getline (input, line)) {
	if (line[0] == '#') continue;
	int i1, i2, rfBucket, bunchSpace, bunchesInTrain, spaceSPS, psTrains;
	string ringName;
	double population;
	istringstream inLine (line);
	inLine >> i1 >> i2 >> ringName >> rfBucket >> bunchSpace >> bunchesInTrain >> spaceSPS >> psTrains >> population;
	bool isBeam1 =  ringName.find ("_1") != string::npos;
	vector<float>& beam = isBeam1 ? beam1 : beam2;
	int ibx0 = (rfBucket / 10) + 1;
	int trainOffset = spaceSPS / 25;
	int step = bunchSpace / 25;
	for (int train = 0; train < psTrains; ++train) {
	  int ibx = ibx0 + trainOffset * train;
	  for (int i = 0; i < bunchesInTrain; ++i) {
	    beam[ibx] = population;
	    ibx += step;
	  }
	}
      }
    }
    double sum = 0;
    for (size_t i = 0; i < NBX_PER_ORBIT; ++i) {
      sum += mBunches [i] = beam1[i]*beam2[i];
    }
    for (size_t i = 0; i < NBX_PER_ORBIT; ++i) {
      if (mBunches [i] > 0) {
	if (sum > 0)  mBunches [i] /= sum;
      }
      else if (beam1[i]+beam2[i] > 0) {
	mBunches [i] = PARASITIC;
      }
    }
  }
} 


void LhcFill::vetoCollision (int fMin, int fMax) {
  int iBX = NBX_PER_ORBIT;
  while (--iBX >= 0) {
    if (mBunches [iBX] > 0) {
      for (int vetoBX = iBX + fMin; vetoBX <= iBX + fMax; ++vetoBX) {
	float& vetoBunch = mBunches[normalizeBX (vetoBX)];
	if (vetoBunch == 0) vetoBunch = VETOED;
      }
    }
  }
}

void LhcFill::vetoParasitic (int fMin, int fMax) {
  int iBX = NBX_PER_ORBIT;
  while (--iBX >= 0) {
    if (int (mBunches [iBX]) == PARASITIC) {
      for (int vetoBX = iBX + fMin; vetoBX <= iBX + fMax; ++vetoBX) {
	float& vetoBunch = mBunches[normalizeBX (vetoBX)];
	if (vetoBunch == 0) vetoBunch = VETOED;
      }
    }
  }
}

void LhcFill::vetoLate (double fTimeWindow) {
  int timeWindow = int (floor (fTimeWindow / TIME_PER_BX));
  int iBX = -timeWindow;
  int lastCollisionBX = iBX;
  while (++iBX < int(NBX_PER_ORBIT)) {
    if (collisionBX (iBX)) {
      lastCollisionBX = iBX;
    }
    else if (iBX > lastCollisionBX + timeWindow) {
      if (mBunches [iBX] == 0) mBunches [iBX] = VETOED;
    }
  }
}

double LhcFill::expectedLumi (int fBX) const {
  int iBX = normalizeBX (fBX);
  return  mBunches [iBX] > 0 ? mBunches [iBX] : 0; 
}

bool LhcFill::collisionBX (int fBX) const {
  return mBunches [normalizeBX (fBX)] > 0;
}

bool LhcFill::vetoedBX (int fBX) const {
  return int (mBunches [normalizeBX (fBX)]) == VETOED ;
}

bool LhcFill::sensitiveBX (int fBX) const {
  return mBunches [normalizeBX (fBX)] == 0;
}

vector<int> LhcFill::collisionBXs () const {
  vector<int> result;
  for (size_t i = 0; i < NBX_PER_ORBIT; ++i) {
    if (mBunches [i] > 0) result.push_back (int (i));
  }
  return result;
}

vector<int> LhcFill::sensitiveBXs () const {
  vector<int> result;
  for (size_t i = 0; i < NBX_PER_ORBIT; ++i) {
    if (mBunches [i] == 0) result.push_back (int (i));
  }
  return result;
}

vector<int> LhcFill::insensitiveBXs () const {
  vector<int> result;
  for (size_t i = 0; i < NBX_PER_ORBIT; ++i) {
    if (mBunches [i] != 0) result.push_back (int (i));
  }
  return result;
}

vector<pair<int, int> > LhcFill::sensitivePeriods () const {
  vector<pair<int, int> > result;
  int currentBX = 0;
  int firstBX = -1;
  while (1) {
    if (firstBX < 0 && sensitiveBX (currentBX)) { // new gap
      firstBX = currentBX;
    }
    else if (firstBX >=0 && !sensitiveBX (currentBX)) { // end gap
      result.push_back (pair<int,int>(firstBX, currentBX-firstBX));
      cout << "new gap: " << firstBX << " : " << currentBX-firstBX << endl;
      firstBX = -1;
    }
    ++currentBX;
    if (firstBX < 0 && currentBX >= int (NBX_PER_ORBIT)) break;
  }
  return result;
}

void LhcFill::printSummary (ostream& fOut) {
  fOut << "LhcFill: " << name () << " Collision BXs: " << collisionBXs().size() << " sensitive BXs: " << sensitiveBXs().size() << endl; 
}
