#ifndef Validation_Stage2Watcher_H
#define Validation_Stage2Watcher_H
#include "SimG4Core/Watcher/interface/SimWatcher.h"
#include "SimG4Core/Notification/interface/Observer.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "SimG4Core/Notification/interface/EndOfEvent.h"
#include "SimG4Core/Notification/interface/BeginOfEvent.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "TH1D.h"
#include "TTree.h"

#include <iostream>
#include <vector>
#include <map>
#include <string>

class BeginOfJob;
class BeginOfRun;
class G4LogicalVolume;
class G4VPhysicalVolume;
class G4Step;

typedef std::multimap< G4LogicalVolume*, G4VPhysicalVolume*, std::less<G4LogicalVolume*> > mmlvpv;

class Stage2Watcher : public SimWatcher,
                      public Observer<const G4Step *>,
                      public Observer<const EndOfEvent *>,
                      public Observer<const BeginOfEvent *>
                       {

public:

  Stage2Watcher(edm::ParameterSet const & p);
  ~Stage2Watcher();

private:


  void update(const G4Step * );
  void update(const EndOfEvent * );
  void update(const BeginOfEvent *);
 

  TH1D * GlobalTimingHisto;
  TH1D * LocalTimingHisto;  
  TH1D * ProperTimingHisto;  
  TTree * EventTree;

  Float_t PosX, PosY, PosZ;
  Float_t PosR, PosRho, PosPhi;
  Float_t Time;
  Float_t EnergyDep;
  
  bool TimeHists_;


private:
  edm::Service<TFileService> fs;

};

#endif
