#ifndef gen_Pythia6HSCPGun_h
#define gen_Pythia6HSCPGun_h

#include <fstream>

#include "GeneratorInterface/Pythia6Interface/plugins/Pythia6ParticleGun.h"


namespace gen {

   class Pythia6HSCPGun : public Pythia6ParticleGun
   {
   
      public:
      
        Pythia6HSCPGun( const edm::ParameterSet& );
        virtual ~Pythia6HSCPGun();

	void produce( edm::Event& fEvt, const edm::EventSetup& iSetup );
	  
   protected:
	void generateEvent();
	
   private:

	bool mReadFromFile;
	std::string mStopPointProducer;
	std::string mFileName;
	std::ifstream* mFile;

	int mPID;
	float mVx;
	float mVy;
	float mVz;

   };
  

}

#endif
