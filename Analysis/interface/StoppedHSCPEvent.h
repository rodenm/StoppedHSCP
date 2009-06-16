#ifndef StoppedHSCPEvent_h
#define StoppedHSCPEvent_h

#include <vector>
#include "TObject.h"

//#include "StoppedHSCP/Analysis/interface/StoppedHSCPJet.h"

class StoppedHSCPEvent : public TObject {
 public:

/*   struct Tower { */
/*   }; */

/*   struct HPD { */
/*   }; */

/*   struct RBX { */
/*   }; */

/* struct StoppedHSCPJet { */
/*   double et; */
/*   double eta; */
/*   double phi; */
/* }; */

/*   struct Muon { */
/*     double pt; */
/*     double eta; */
/*     double phi; */
/*   }; */

 public:
  
  enum { MAX_N_TOWERS=10 };
  enum { MAX_N_HPDS=10 };
  enum { MAX_N_RBXS=10 };
  enum { MAX_N_JETS=10 };
  enum { MAX_N_MUONS=10 };

 public:
  StoppedHSCPEvent();
  ~StoppedHSCPEvent();
  
  void setEventInfo(unsigned evt,
		    unsigned bx,
		    unsigned orbit,
		    unsigned ls,
		    unsigned run,
		    unsigned fill,
		    unsigned timestamp);

/*   void addTower(Tower t); */
/*   void addHPD(HPD h); */
/*   void addJet(StoppedHSCPJet j); */
/*   void addMuon(Muon m); */

 private:

  unsigned event_;
  unsigned bx_;
  unsigned orbit_;
  unsigned lumisection_;
  unsigned run_;
  unsigned fill_;
  unsigned timestamp_;

/*   std::vector<Tower> towers_; */
/*   std::vector<HPD> hpds_; */
/*   std::vector<RBX> rbxs_; */
  unsigned nJets_;
/*   StoppedHSCPJet jets_[MAX_N_JETS]; */
/*   std::vector<Muon> muons_; */
  ClassDef(StoppedHSCPEvent,1);

};

#endif
