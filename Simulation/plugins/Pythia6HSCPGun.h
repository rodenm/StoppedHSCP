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
      
      protected:
         void generateEvent();
      
      private:
	 std::string mFileName;
	 std::ifstream* mFile;
   };


}

#endif
