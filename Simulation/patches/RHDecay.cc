
#include "IOMC/EventVertexGenerators/interface/RHDecay.h"

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <ios>

#include "TMath.h"

#include "HepMC/SimpleVector.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"

#include "CLHEP/Random/RandFlat.h"
#include "CLHEP/Units/SystemOfUnits.h"
#include "CLHEP/Units/PhysicalConstants.h"

#include "TTree.h"
#include "PhysicsTools/UtilAlgos/interface/TFileService.h"
#include "FWCore/ServiceRegistry/interface/Service.h"


/*
  Operation Modes:
 
  0 - Positions from file
  1 - Sample from radial and z histograms generated from file, phi random
  5 - Sample randomly in all allowed volume

*/



RHDecay::RHDecay(const edm::ParameterSet & p) 
  : BaseEvtVtxGenerator(p),
    mFilePath (p.getParameter<edm::FileInPath>( "stoppedData")),
    mTimeMin (p.getParameter<double>( "timeOffsetMin") * ns * c_light),
    mTimeMax (p.getParameter<double>( "timeOffsetMax") * ns * c_light),
    Silent (p.getUntrackedParameter<bool>("Silent",false)),
    MakeRCuts (p.getUntrackedParameter<bool>("MakeRCuts",false)),
    MakeCuts (p.getUntrackedParameter<bool>("MakeCuts",true)),
    MinRadius (p.getUntrackedParameter<double>("MinRadius",1310)),
    MaxRadius (p.getUntrackedParameter<double>("MaxRadius",2950)),
    MinZ (p.getUntrackedParameter<double>("MinZ",-5600)),
    MaxZ (p.getUntrackedParameter<double>("MaxZ",5600)),
    MinPhi (p.getUntrackedParameter<double>("MinPhi",0)),
    MaxPhi (p.getUntrackedParameter<double>("MaxPhi",6.28318530)),
    OperationMode (p.getUntrackedParameter<int>("OperationMode",0)),
    RDivs (p.getUntrackedParameter<int>("RDivs",40)),
    ZDivs (p.getUntrackedParameter<int>("ZDivs",40))
{
 


  RDist = fs->make<TH1D>("RDist","RDist",RDivs,MinRadius,MaxRadius);
  ZDist = fs->make<TH1D>("ZDist","ZDist",ZDivs,MinZ,MaxZ);
  InTree = fs->make<TTree>("InTree","Data from file");
  PlaceTree = fs->make<TTree>("PlaceTree","Positions of vertices");
 
  InTree->Branch("xIn",&xIn,"xIn/F");
  InTree->Branch("yIn",&yIn,"yIn/F");
  InTree->Branch("zIn",&zIn,"zIn/F");
  InTree->Branch("rIn",&rIn,"rIn/F");

  PlaceTree->Branch("xPlace",&xPlace,"xPlace/F");
  PlaceTree->Branch("yPlace",&yPlace,"yPlace/F");
  PlaceTree->Branch("zPlace",&zPlace,"zPlace/F");
  PlaceTree->Branch("rPlace",&rPlace,"rPlace/F");
  PlaceTree->Branch("tPlace",&tPlace,"tPlace/F");

  
  bool ReadFromFile=false;
  if((OperationMode==0)||(OperationMode==1))
    ReadFromFile=true;
  
  std::ostringstream o;

  if(ReadFromFile)
    {
      char buf [1024];
      mFile = new std::ifstream (mFilePath.fullPath().c_str());
      bool stoprun=false;
      char name[32];
      float xvi,yvi,zvi;
      for(int i=0; stoprun!=true; i++)
	{  
	  mFile->getline (buf, 1023);
	  if (!mFile->good() || buf[0]=='\n')
	    {     
	      TotalNumber=i-1;
	      edm::LogInfo("RHDecay") <<"RHDecay EOF at "<< TotalNumber<<" of lines"<<std::endl;
	      stoprun=true;
	    }
	  else
	    {
	      sscanf (buf, "%s %f %f %f", name, &xvi, &yvi, &zvi);
	      xIn = xv[i] = xvi;
	      yIn = yv[i] = yvi;
	      zIn = zv[i] = zvi;
	      rIn=pow(pow(xIn,2)+pow(yIn,2),0.5);
	      
	      if(MakeCuts)
		{
		  
		  if((rIn < MaxRadius && rIn > MinRadius)&&(zIn > MinZ && zIn < MaxZ))
		    {
		      InTree->Fill();
		      RDist->Fill(rIn);
		      ZDist->Fill(zIn);
		      o << "RHDecay Got decay point:" << xvi << "   " << yvi << "   "  << zvi << " cm " << "  r = " << rIn << std::endl; 
		    }
		  else
		    {
		      i--;
		    }
		}
	      else 
		{
		  InTree->Fill();
		  o << "RHDecay Got decay point:" << xvi << "   " << yvi << "   "  << zvi << " cm " << std::endl; 
		}
	    }
	} 
    }
  
  edm::LogVerbatim("RHDecay") << o.str();
  o.clear();



  // set up file based rand generator for r direction 

  if(! rng.isAvailable())
    {
      throw cms::Exception("Error, no random number generator available for RHDecay");
    }

 
  for(int i=0; i<RDivs; i++)
    {
      // std::cout << i <<std::endl;
      RArray[i]=RDist->GetBinContent(i);
    }
  for(int i=0; i<ZDivs; i++)
    {
      // std::cout<< i << std::endl;
      ZArray[i]=ZDist->GetBinContent(i);
    }




  RSample = new RandGeneral(rng->getEngine(),RArray,RDivs);
  ZSample = new RandGeneral(rng->getEngine(),ZArray,ZDivs);
  

  // Set up r^2 array and rand generator for geometric radial dist (mode 5)
  double RadialDistFunc[200];
  for(int i=1; i<200; i++)
    {
      RadialDistFunc[i]=pow(i,2);
    }
  RGeometric = new RandGeneral(rng->getEngine(),RadialDistFunc,200);

  //Set up flat distribution for T sampling
  FlatRand = new RandFlat(rng->getEngine());
    





}
	  
RHDecay::~RHDecay() {}

HepMC::FourVector* RHDecay::newVertex() {
  
  double t, x, y, z;
  double r, phi;
  

  
  t=FlatRand->shoot (mTimeMin, mTimeMax);
  if(OperationMode==0)
    {
      int RecordNo(CLHEP::RandFlat::shoot (double(0.),double(TotalNumber)));
      x = xv[RecordNo];
      y = yv[RecordNo];
      z = zv[RecordNo];
    }
  else if(OperationMode==1)
    {
      r = RSample->shoot()*(MaxRadius-MinRadius)+MinRadius;
      phi = FlatRand->shoot(MinPhi,MaxPhi);
      z = ZSample->shoot()*(MaxZ-MinZ)+MinZ;
      x = r * TMath::Cos(phi);
      y = r * TMath::Sin(phi);
    }
  else if(OperationMode==5)
    {
      r = RGeometric->shoot();
      phi = FlatRand->shoot(MinPhi,MaxPhi);
      z = FlatRand->shoot(MinZ,MaxZ);
      x = r * TMath::Cos(phi);
      y = r * TMath::Sin(phi);
    }
  else
    {
      throw cms::Exception("This RHDecay operation mode has not yet been implemented");
    }

	  

  if(!Silent) edm::LogInfo("RHDecay") << "RHDecay Placing particle at decay point:" << x << "   " << y << "   "  << z << " cm,    " << t<<" ns"<<std::endl; 

  if (!fVertex) fVertex = new HepMC::FourVector(x, y, z, t);
  else fVertex->set (x, y, z, t);

  xPlace=x;
  yPlace=y;
  zPlace=z;
  tPlace=t;
  rPlace=pow(pow(x,2)+pow(y,2),0.5);

  PlaceTree->Fill();

  return fVertex;
}

