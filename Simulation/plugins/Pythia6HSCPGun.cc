#include <iostream>
#include <fstream>
#include <stdio.h>

#include "Pythia6HSCPGun.h"

#include "FWCore/Utilities/interface/Exception.h"

#include "FWCore/Framework/interface/EDProducer.h"
#include "FWCore/Framework/interface/EventSetup.h"
#include "FWCore/Framework/interface/Event.h"

#include "FWCore/MessageLogger/interface/MessageLogger.h"

#include "SimDataFormats/GeneratorProducts/interface/HepMCProduct.h"

#include "FWCore/Framework/interface/MakerMacros.h"
#include "GeneratorInterface/Pythia6Interface/interface/Pythia6Declarations.h"

using namespace edm;
using namespace gen;

namespace {
  const int specialNumber = 32;
  const int specialPid [specialNumber] = {
    1000993,1009213,1009313,1009323,1009113,
    1009223,1009333,1091114,1092114,1092214,
    1092224,1093114,1093214,1093224,1093314,
    1093324,1093334,
    1000612,1000622,1000632,1000642,1000652,
    1006113,1006211,1006213,1006223,1006311,
    1006313,1006321,1006323,1006333,
    1000015
  };
  const std::string specialName [specialNumber] = {
      "~g_glueball","~g_rho+","~g_K*0","~g_K*+","~g_rho0",
      "~g_omega","~g_phi","~g_Delta-","~g_Delta0","~g_Delta+",
      "~g_Delta++","~g_Sigma*-","~g_Sigma*0","~g_Sigma*+","~g_Xi*-",
      "~g_Xi*0 ","~g_Omega-",
      "~T+","~T0","~T_s+","~T_c0","~T_b+",
      "~T_dd10","~T_ud0+","~T_ud1+","~T_uu1++","~T_sd00",
      "~T_sd10","~T_su0+","~T_su1+","~T_ss10",
      "tau1"
  };
  const std::string specialAntiName [specialNumber] = {
    "~g_glueball","~g_rho-","~g_K*bar0","~g_K*-","~g_rho0",
    "~g_omega","~g_phi","~g_Deltabar+","~g_Deltabar0","~g_Deltabar-",
    "~g_Deltabar--","~g_Sigma*bar+","~g_Sigma*bar0","~g_Sigma*bar-","~g_Xi*bar+",
    "~g_Xi*bar0","~g_Omegabar+",
    "~Tbar-","~Tbar0","~Tbar_s-","~Tbar_c0","~Tbar_b-",
    "~Tbar_dd10","~Tbar_ud0-","~Tbar_ud1-","~Tbar_uu1--","~Tbar_sd00",
    "~Tbar_sd10","~Tbar_su0-","~Tbar_su1-","~Tbar_ss10",
    "~tau1"
  };
  int getSpecialId (const std::string& fName) {
    for (int i = 0; i < specialNumber; ++i) {
      if (fName == specialName[i]) return specialPid[i];
      if (fName == specialAntiName[i]) return -specialPid[i];
    }
    return 0;
  }

  void writeCommon (std::ofstream& file) {
    char buffer[1024];
    sprintf (buffer, "DECAY 1000022 0.\n"); 
    file << buffer;
    sprintf (buffer, "DECAY 1000021 1.e-12 \n"); 
    file << buffer; // gluino
    sprintf (buffer, "     1.00000000E+00   2   1000022   21 \n"); 
    file << buffer;
    sprintf (buffer, "DECAY 1000006 1.e-12 \n"); 
    file << buffer; // stop
    sprintf (buffer, "     1.00000000E+00   2   1000022    6 \n"); 
    file << buffer;
    sprintf (buffer, "DECAY 1000015 1.e-12 \n"); 
    file << buffer; // stau
    sprintf (buffer, "     1.00000000E+00   2   1000022   15 \n"); 
    file << buffer;
  }

  void writeRHadron (std::ofstream& file) {
    char buffer[1024];
    for (int id = 0; id < 17; ++id) {
      const char* name = specialName[id].c_str();
      int pid = specialPid[id];
      if ((pid % 100000) > 90000) { // R-Baryon
	int quark [3];
	int charge = 0;
	int qid = (pid % 10000) / 10;
	for (int i = 0; i < 3; ++i) {
	  quark[i] = qid % 10;
	  if (quark[i] == 2) charge+=2;
	  else --charge;
	  qid = qid / 10;
	}
	sprintf (buffer, "DECAY     %7d     1.00000000E-05\n", pid); file << buffer;
	sprintf (buffer, "     1.0000000E+00   3   %1d%1d03   %1d   1000021\n",
		 quark[2],quark[1],quark[0]); // decay to quark+diquark+gluino
	file << buffer;
	
	sprintf (buffer, "BLOCK QNUMBERS %7d # %s \n", pid, name); file << buffer;
	sprintf (buffer, "         1 %d \n", charge); file << buffer;
	sprintf (buffer, "         2 2 \n"); file << buffer;
	sprintf (buffer, "         3 1 \n"); file << buffer;
	sprintf (buffer, "         4 1 \n"); file << buffer;
      }
      else if ((pid % 10000) > 9000) { // R-Meson
	int quark [2];
	int qid = (pid % 1000) / 10;
	for (int i = 0; i < 2; ++i) {
	  quark[i] = qid % 10;
	  qid = qid / 10;
	}
	int charge = 0;
	if (quark[0] == 2) charge-=2;
	else charge+=1;
	if (quark[1] == 2) charge+=2;
	else charge-=1;
	
	sprintf (buffer, "DECAY     %7d     1.00000000E-05\n", pid); file << buffer;
	sprintf (buffer, "     1.00000000E+00   3   -%1d   %1d   1000021\n",
		 quark[0], quark[1]); // decay to quark+antiquark+gluino
	file << buffer;
	
	sprintf (buffer, "BLOCK QNUMBERS %7d # %s \n", pid, name); file << buffer;
	sprintf (buffer, "         1 %d \n", charge); file << buffer;
	sprintf (buffer, "         2 2 \n"); file << buffer;
	sprintf (buffer, "         3 1 \n"); file << buffer;
	sprintf (buffer, "         4 1 \n"); file << buffer;
      }
      else { // glueball
	sprintf (buffer, "DECAY     %7d     1.00000000E-05\n", pid); file << buffer;
	sprintf (buffer, "     1.00000000E+00   2   21   1000021\n");
	file << buffer;
	sprintf (buffer, "BLOCK QNUMBERS %7d # %s\n", pid, name); file << buffer;
	sprintf (buffer, "         1 0 \n"); file << buffer;
	sprintf (buffer, "         2 2 \n"); file << buffer;
	sprintf (buffer, "         3 1 \n"); file << buffer;
	sprintf (buffer, "         4 1 \n"); file << buffer;
      }
    }
  }

  void writeStopHadron (std::ofstream& file) {
    char buffer[1024];
    for (int id = 17; id < 31; ++id) {
      const char* name = specialName[id].c_str();
      int pid = specialPid[id];
      if ((pid % 10000) > 6000) { // T-Baryon
	int quark [3];
	int charge = 0;
	int qid = (pid % 10000) / 10;
	for (int i = 0; i < 3; ++i) {
	  quark[i] = qid % 10;
	  if (quark[i] % 2) charge-=1; // d,s,b
	  else charge+=2; // u,c,t
	  qid = qid / 10;
	}
	if (quark[2] != 6) {
	  std::cout << "writeStopHadron-> STOP R-hadron is expected, " << pid << " is found" << std::endl;
	  return;
	}
	sprintf (buffer, "DECAY     %7d     1.00000000E-05\n", pid); file << buffer;
	sprintf (buffer, "     1.0000000E+00   2   %1d%1d03   1000006\n",
		 quark[1],quark[0]); // decay to stop+diquark
	file << buffer;
	
	sprintf (buffer, "BLOCK QNUMBERS %7d # %s \n", pid, name); file << buffer;
	sprintf (buffer, "         1 %d \n", charge); file << buffer;
	sprintf (buffer, "         2 2 \n"); file << buffer;
	sprintf (buffer, "         3 1 \n"); file << buffer;
	sprintf (buffer, "         4 1 \n"); file << buffer;
      }
      else if ((pid % 10000) > 600) { // STOP-Meson
	int quark [2];
	int qid = (pid % 1000) / 10;
	for (int i = 0; i < 2; ++i) {
	  quark[i] = qid % 10;
	  qid = qid / 10;
	}
	if (quark[1] != 6) {
	  std::cout << "writeStopHadron-> STOP R-hadron is expected, " << pid << " is found" << std::endl;
	  return;
	}
	int charge = 0;
	if (quark[0] % 2) charge+=1; // anti d,s,b
	else charge-=2; // anti u,c,t
	if (quark[1] % 2) charge-=1; // d,s,b
	else charge+=2; // u,c,t
	
	sprintf (buffer, "DECAY     %7d     1.00000000E-05\n", pid); file << buffer;
	sprintf (buffer, "     1.00000000E+00   2   -%1d   1000006\n",
		 quark[0]); // decay to quark+antiquark+gluino
	file << buffer;
	
	sprintf (buffer, "BLOCK QNUMBERS %7d # %s \n", pid, name); file << buffer;
	sprintf (buffer, "         1 %d \n", charge); file << buffer;
	sprintf (buffer, "         2 2 \n"); file << buffer;
	sprintf (buffer, "         3 1 \n"); file << buffer;
	sprintf (buffer, "         4 1 \n"); file << buffer;
      }
      else {
	std::cout << "writeStopHadron-> Unknown STop R-hadron: " << pid << std::endl;
      }
    }
  }

  void writeStau (std::ofstream& file) {
  }

  void setAllMasses (std::ofstream& file, double sparticleMass, double neutralinoMass) {
    char buffer[1024];
    sprintf (buffer, "BLOCK_MASS\n"); file << buffer;
    sprintf (buffer, "   1000022   %6.1f\n", neutralinoMass); file << buffer;
    sprintf (buffer, "   1000021   %6.1f\n", sparticleMass); file << buffer;
    sprintf (buffer, "   1000006   %6.1f\n", sparticleMass); file << buffer;
    sprintf (buffer, "   1000015   %6.1f\n", sparticleMass); file << buffer;
    double hadronMass = sparticleMass + 2.;
    for (int i = 0; i < specialNumber; ++i) {
      int pid = specialPid[i];
      sprintf (buffer, "   %7d   %6.1f\n", pid, hadronMass); file << buffer;
    }
  }

  void makeParticleTable (const std::string& fName, 
			  double fSparticleMass, double fNeutralinoMass) {
    std::ofstream file (fName.c_str());
    writeCommon (file);
    writeRHadron (file);
    //writeStopHadron (file);
    writeStau (file);
    setAllMasses (file, fSparticleMass, fNeutralinoMass);
    std::cout << "***** " << fName.c_str() << std::endl;
  }

}// unnamed namespace

Pythia6HSCPGun::Pythia6HSCPGun( const ParameterSet& pset ) :
  Pythia6ParticleGun(pset),
  mReadFromFile(pset.getUntrackedParameter<bool>("readFromFile", true)),
  mStopPointProducer(pset.getUntrackedParameter<std::string>("stopPointInputTag", "g4SimHits")),
  mFileName(pset.getParameter<std::string>("stoppedData")),
  mPID(0),
  mVx(0.),
  mVy(0.),
  mVz(0.)
{
  if (mReadFromFile) {
    mFile = new std::ifstream (mFileName.c_str());
  }
  
  ParameterSet pgun_params = pset.getParameter<ParameterSet>("PGunParameters");
  std::string decayTable = (pgun_params.getParameter<std::string>( "decayTable"));
  double sparticleMass = (pgun_params.getParameter<double>( "sparticleMass"));
  double neutralinoMass = (pgun_params.getParameter<double>( "neutralinoMass"));
  bool diJetGluino = (pgun_params.getParameter<bool>( "diJetGluino"));  
  makeParticleTable (decayTable,sparticleMass, neutralinoMass);
 
}

Pythia6HSCPGun::~Pythia6HSCPGun()
{
}


// copied from Pythia6Gun::produce
void Pythia6HSCPGun::produce(edm::Event& evt, const edm::EventSetup& iSetup) {
  bool isStoppedEvent = false;
  std::string name("none");
  mPID=0;
  mVx=0.;
  mVy=0.;
  mVz=0.;

  // get stopping point info
  if (mReadFromFile) {   // read stopping info from file
    
    char buf [1024];
    mFile->getline (buf, 1023);
    if (!mFile->good() || buf[0]=='\n') { // end file: rewind
      delete mFile;
      mFile = new std::ifstream (mFileName.c_str());
      mFile->getline (buf, 1023);
      if (!mFile->good() || buf[0]=='\n') { // something wrong
	edm::LogError("FileError") << "Pythia6HSCPGun::generateEvent-> ERROR: failed to get data from file" << std::endl;
      }
    }
    char nn[32];
    sscanf (buf, "%s %f %f %f", nn, &mVx, &mVy, &mVz);
    name = std::string(nn);
    mPID = getSpecialId(name);
    isStoppedEvent = true;
  }
  else {  // or from the event

    edm::Handle<std::vector<std::string> > names;
    evt.getByLabel (mStopPointProducer, "StoppedParticlesName", names);
    edm::Handle<std::vector<float> > xs;
    evt.getByLabel (mStopPointProducer, "StoppedParticlesX", xs);
    edm::Handle<std::vector<float> > ys;
    evt.getByLabel (mStopPointProducer, "StoppedParticlesY", ys);
    edm::Handle<std::vector<float> > zs;
    evt.getByLabel (mStopPointProducer, "StoppedParticlesZ", zs);
    
    if (names->size() != xs->size() || xs->size() != ys->size() || ys->size() != zs->size()) {
      edm::LogError ("Pythia6HSCPGun") << "mismatch array sizes name/x/y/z:"
				       << names->size() << '/' << xs->size() << '/' << ys->size() << '/' << zs->size()
				       << std::endl;
    }
     else {

       // TODO - what about when we have two stopped particles?!?
       // currently take the first one, not sure there is anything we can do about this.
       if (names->size() > 0) {
	 name = names->at(0);
	 mPID = getSpecialId(names->at(0));
	 mVx  = xs->at(0);
	 mVy  = ys->at(0);
	 mVz  = zs->at(0);
	 isStoppedEvent = true;
       }

     }

    edm::LogInfo("Pythia6HSCPGun") << "Pythia6HSCPGun::generateEvent-> name/pid vertex: "
				   << name << '/' << mPID << '/' << ' '
				   << mVx << '/' << mVy << '/' << mVz 
				   << std::endl; 

  }
  
  if (isStoppedEvent) {
    generateEvent() ;
    
    fEvt->set_beam_particles(0,0);
    fEvt->set_event_number(evt.id().event()) ;
    fEvt->set_signal_process_id(pypars.msti[0]) ;  
    
    attachPy6DecaysToGenEvent();
    
    int evtN = evt.id().event();
    if ( evtN <= fMaxEventsToPrint ) {
	if ( fPylistVerbosity ) {
	    call_pylist(fPylistVerbosity);
	}
	if ( fHepMCVerbosity ) {
	  if ( fEvt ) fEvt->print();
	}
    }
    loadEvent( evt );
  }
}

void Pythia6HSCPGun::generateEvent()
{

  // check the case where no stopped particle found
  // need to check this doesn't break stuff
  if (mPID==0) {
    return;
  }

  Pythia6Service::InstanceWrapper guard(fPy6Service);	// grab Py6 instance
  
  // 1st, primary vertex
   //
  HepMC::GenVertex* Vtx = new HepMC::GenVertex( HepMC::FourVector(mVx, mVy, mVz));
  
  // here re-create fEvt (memory)
  //
  fEvt = new HepMC::GenEvent() ;
  
  int ip=1;
  
  int particleID = mPID;
  int py6PID = HepPID::translatePDTtoPythia( particleID );
  double mass = pymass_(particleID);
  
  // fill p(ip,5) (in PYJETS) with mass value right now,
  // because the (hardcoded) mstu(10)=1 will make py1ent
  // pick the mass from there
  pyjets.p[4][ip-1]=mass; 	 
  
  double phi = 0.;
  double ee   = mass;
  double eta  = 0;
  double the  = 2.*atan(exp(-eta));
  
  py1ent_(ip, py6PID, ee, the, phi);
  
  double px     = pyjets.p[0][ip-1]; // pt*cos(phi) ;
  double py     = pyjets.p[1][ip-1]; // pt*sin(phi) ;
  double pz     = pyjets.p[2][ip-1]; // mom*cos(the) ;
  
  HepMC::FourVector p(px,py,pz,ee) ;
  HepMC::GenParticle* Part = new HepMC::GenParticle(p,particleID,1);
  Part->suggest_barcode( ip ) ;
  Vtx->add_particle_out(Part);
  
  fEvt->add_vertex(Vtx);
  
  // run pythia
  pyexec_();
  
  return;
}

DEFINE_FWK_MODULE(Pythia6HSCPGun);
