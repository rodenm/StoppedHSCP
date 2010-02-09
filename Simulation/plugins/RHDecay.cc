#include "RHDecay.h"

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <ios>

#include "HepMC/SimpleVector.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "CLHEP/Random/RandFlat.h"
#include "CLHEP/Units/SystemOfUnits.h"
#include "CLHEP/Units/PhysicalConstants.h"

// dirty trick to work around encapsulation of EventVertexGenerators package
#include "IOMC/EventVertexGenerators/src/BaseEvtVtxGenerator.cc" 

RHDecay::RHDecay(const edm::ParameterSet & p) 
  : BaseEvtVtxGenerator(p),
    //    mFileName (p.getParameter<edm::FileInPath>( "stoppedData").fullPath()),
    mFileName (p.getParameter<std::string>( "stoppedData")),
    mTimeMin (p.getParameter<double>( "timeOffsetMin") * ns * c_light),
    mTimeMax (p.getParameter<double>( "timeOffsetMax") * ns * c_light),
    mRandom (new CLHEP::RandFlat(getEngine())),
    mVerbose (p.getUntrackedParameter<bool> ("verbose", false))
{
  mFile = new std::ifstream (mFileName.c_str());
}

RHDecay::~RHDecay() {}

HepMC::FourVector* RHDecay::newVertex() {
  char buf [1024];
  mFile->getline (buf, 1023);
  if (!mFile->good() || buf[0]=='\n') { // end file: rewind
    delete mFile;
    mFile = new std::ifstream (mFileName.c_str());
    mFile->getline (buf, 1023);
    if (!mFile->good() || buf[0]=='\n') { // something wrong
      std::cerr << "RHDecay::newVertex-> ERROR: failed to get data from file" << std::endl;
    }
  }
  char name[32];
  float xv;
  float yv;
  float zv;
  sscanf (buf, "%s %f %f %f", name, &xv, &yv, &zv);

  double tv = CLHEP::RandFlat::shoot (mTimeMin, mTimeMax);
  if (!fVertex) fVertex = new HepMC::FourVector(xv, yv, zv, tv);
  else fVertex->set (xv, yv, zv, tv);
  if (mVerbose) std::cout << "RHDecay::newVertex-> Got decay point:" << xv << '/' << yv << '/' << zv << " cm, " << tv / (ns * c_light) << " ns" << std::endl; 
  return fVertex;
}

